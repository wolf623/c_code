#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

//tftp packet
struct tftp_package
{
	unsigned short optcode;				/*packet type*/
	union
	{
		unsigned short blocknum;		/*block # */
		unsigned short errcode;			/*error code*/
	}u;
	unsigned char data[0];				/*data or error string*/

}__attribute__((__packed__));


#define WELL_KNOW_PORT 69 /*Well known TFTP port # */
#define TIMEOUT 5000UL  /*Millisecs to timeout for lost pkt*/


#ifndef CONFIG_NET_RETRY_COUNT
#define TIMEOUT_COUNT 10 /*# of timeouts before giving up*/
#else
#define TIMEOUT_COUNT (CONFIG_NET_RETRY_COUNT * 2)
#endif 

#define HASHES_PER_LINE 65	/* Number of "loading" hashes per line	*/

/*512 is poor choice for ethernet,MTU is typically 1500.
 *Minus eth.hdrs thats 1468.Can get 2x better throughput with
 *almost-MTU block sizes,At least try ... fall back to 512 if need be.
 */
#ifdef CONFIG_TFTP_BLOCKSIZE
#define TFTP_BLOCKSIZE CONFIG_TFTP_BLOCKSIZE
#else
#define TFTP_BLOCKSIZE 1468
#endif 

static unsigned short TftpBlkSizeOption=TFTP_BLOCKSIZE;


/*Tftp send/recv MTU size*/
#define TFTP_MTU_SIZE TFTP_BLOCKSIZE + 4

/*
 *TFTP operations
 */
#define TFTP_RRQ	 1
#define TFTP_WRQ 	 2
#define TFTP_DATA 	 3
#define TFTP_ACK 	 4
#define TFTP_ERROR 	 5
#define TFTP_OACK	 6

static unsigned long TftpTimeoutMSecs = TIMEOUT;
static int TftpTimeoutCountMax = TIMEOUT_COUNT;

/*
 *TFTP state
 */
#define STATE_RRQ 			1
#define STATE_DATA 	 		2
#define STATE_TOO_LARGE 	3
#define STATE_BAD_MAGIC 	4
#define STATE_OACK 			5

/*
 *TFTP error code
 */

enum{
	TFTP_ERR_UNDEFINED 				= 0,
	TFTP_ERR_FILE_NOT_FOUND 		= 1,
	TFTP_ERR_ACCESS_DENIED			= 2,
	TFTP_ERR_DISK_FULL				= 3,
	TFTP_ERR_UNEXPECTED_OPCODE 		= 4,
	TFTP_ERR_UNKNOWN_TRANSFER_ID	= 5,
	TFTP_ERR_FILE_ALREADY_EXISTS	= 6,
};

#define MAX 1024
#define MAX_LEN 128

/*
 *tftp send/recv buf
 */
unsigned char TftpSendBuf[TFTP_MTU_SIZE];
unsigned char TftpRecvBuf[TFTP_MTU_SIZE];

/**/
static unsigned long TftpBlock;/*packet sequence number*/
static unsigned long TftpLastBlock;/*last packet sequence number received*/
static int TftpState;

/*tftp request filename*/
static char tftp_filename[MAX_LEN] = "zImage";

/*鐩爣绔湴鍧€*/
struct sockaddr_in dest_addr;

void TftpSend(int sockfd)
{
	int len = 0;
	unsigned char *pkt = TftpSendBuf;
	unsigned char *xp;
	unsigned short *s = NULL;

	switch(TftpState)
	{
	case STATE_RRQ:
		xp = pkt;
		s  = (unsigned short *)pkt;
		*s ++ = htons(TFTP_RRQ);
		pkt = (unsigned char *)s;
		strcpy((char *)pkt,tftp_filename);
		pkt += strlen(tftp_filename) + 1;
		strcpy((char *)pkt,"octet");
		pkt += 5/*strlen("octet")*/ + 1;
		strcpy((char *)pkt,"timeout");
		pkt += 7/*strlen("timeout")*/ + 1;
		sprintf((char *)pkt,"%lu",TftpTimeoutMSecs / 1000);
		pkt += strlen((char *)pkt) + 1;
		/*try for more effic .blk size*/
		pkt += sprintf((char *)pkt,"blksize%c%d%c",0,TftpBlkSizeOption,0);
		len = pkt - xp;
		break;

	case STATE_OACK:
	case STATE_DATA:
		xp = pkt;
		s = (unsigned short *)pkt;
		*s ++ = htons(TFTP_ACK);
		*s ++ = htons(TftpBlock);
		pkt   = (unsigned char *)s;
		len = pkt - xp;
		break;
	
	}

	sendto(sockfd,TftpSendBuf,len,0,(struct sockaddr *)&dest_addr,sizeof(struct sockaddr));

	return;
}

int store_block(int file_fd,unsigned char *buf,int len)
{
	if(write(file_fd,buf,len) < 0)
	{
		perror("Faile store block");
		return -1;
	}

	return 0;
}

static void TftpRecv(int sockfd,int file_fd)
{
	int size;
	int i = 0,optcode;
	socklen_t addrlen = sizeof(struct sockaddr);
	struct tftp_package *tpkt = (struct tftp_package *)TftpRecvBuf;

	while(1)
	{
		size = recvfrom(sockfd,TftpRecvBuf,sizeof(TftpRecvBuf),0,(struct sockaddr *)&dest_addr,&addrlen);
		optcode = tpkt->optcode;
		switch(ntohs(optcode))
		{
			case TFTP_OACK:
				TftpState = STATE_OACK;
				TftpSend(sockfd);
				break;

			case TFTP_DATA:
				TftpState = STATE_DATA;
				TftpBlock = ntohs(tpkt->u.blocknum);
				
				if((TftpBlock - 1) % 10 == 0)
					printf("#");
				else if (((TftpBlock) % (10 * HASHES_PER_LINE)) == 0){
					printf("\n\t");
				}
	
				if(TftpBlock == TftpLastBlock)
				{
					/*
					 *Same block again; ignore it.
					 */
					break;
				}
				
				TftpLastBlock = TftpBlock;
				store_block(file_fd,tpkt->data,size-4);
				TftpSend(sockfd);

				/*鏈€鍚庝竴涓暟鎹寘*/
				if(size < TftpBlkSizeOption)
				{
					printf("\n");
					return;
				}
				break;	
			
			case TFTP_ERROR:
				switch(ntohs(tpkt->u.errcode))
				{
					case TFTP_ERR_FILE_NOT_FOUND:
						printf("Error : %s\n",tpkt->data);
						break;

					case TFTP_ERR_UNKNOWN_TRANSFER_ID:
						printf("Error : Unknown Transfer ID.\n");
						break;

					case TFTP_ERR_UNEXPECTED_OPCODE:
						printf("Error : Bad TFTP optcode");
						break;
				
					default:
						printf("Error : ...\n");
						break;
			 }
		}
	
	}

	return;
}

void TftpStart(char *ip,int sockfd,char *filename)
{
	
	memcpy(tftp_filename,filename,strlen(filename) + 1);
	/*濉厖鐩爣绔湴鍧€缁撴瀯:
	 *PORT = 69
	 *IP = ip
	 */
	bzero(&dest_addr,sizeof(dest_addr));
	dest_addr.sin_family = AF_INET;
	dest_addr.sin_port   = htons(WELL_KNOW_PORT);
	dest_addr.sin_addr.s_addr = inet_addr(ip);
	
	TftpState = STATE_RRQ;
	TftpSend(sockfd);

	printf("Loading:*\b");
	
	return;
}

int main(int argc,char *argv[])
{
	int socket_fd,file_fd;
	struct sockaddr netaddr;

	if(argc < 3)
	{
		fprintf(stderr,"usage : %s argv[1] argv[2].\n",argv[0]);
		return -1;
	}

	if((socket_fd = socket(AF_INET,SOCK_DGRAM,0)) < 0)
	{
		perror("Fail to create socket");
		return -1;
	}

	if((file_fd = open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,0666)) < 0)
	{
		fprintf(stderr,"Fail to open %s : %s.\n",argv[2],strerror(errno));
		return 0;
	}
	
	TftpStart(argv[1],socket_fd,argv[2]);
	
	TftpRecv(socket_fd,file_fd);

	close(socket_fd);
	close(file_fd);

	return 0;
}
