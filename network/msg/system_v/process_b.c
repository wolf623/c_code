#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

struct mymsgbuf
{
	long mtype;
	char mtext[8];
};
#define MSG_LEN (sizeof(struct mymsgbuf) - sizeof(long))

#define MSG_ID 589830;

int main(int argc, char *argv[])
{
	//key_t key = IPC_PRIVATE;
	key_t key = MSG_ID;
	int msgfd = msgget(key, 0666|IPC_CREAT);
	if(msgfd == -1)
	{
		printf("msgget failed! %s\n", strerror(errno));
		return -1;
	}

#if 0
	struct mymsgbuf buf;
	buf.mtype = 1;
	//buf.mtext[0] = 0;
	strcpy(buf.mtext, "Hello");

	printf("msg len %lu, struct len %lu, %lu\n", MSG_LEN, sizeof(struct mymsgbuf), sizeof(long));
	if(msgsnd(msgfd, &buf, MSG_LEN, 0) == -1)
	{
		printf("msgsnd failed! %s\n", strerror(errno));
		return -1;
	}
#endif

	struct msqid_ds info;
	if(msgctl(msgfd, IPC_STAT, &info) == 0)
	{
		printf("Before read: __msg_cbytes %lu, msg_qnum %lu, msg_qbytes %lu\n", (unsigned long)info.__msg_cbytes, (unsigned long)info.msg_qnum, (unsigned long)info.msg_qbytes); 
	}

	system("ipcs -q");

	int type = 0, flag = IPC_NOWAIT;
	struct mymsgbuf rcvbuf;
	if(msgrcv(msgfd, &rcvbuf, MSG_LEN, type, flag) == -1)
	{
		printf("msgrcv failed! %s\n", strerror(errno));
		if(msgctl(msgfd, IPC_RMID, NULL) == -1)
		{
			printf("remove failed! %s\n", strerror(errno));
			return -1;
		}

		return -1;
	}
	printf("rcv msg: mtype %lu, mtext %s\n", rcvbuf.mtype, rcvbuf.mtext);

	if(msgctl(msgfd, IPC_STAT, &info) == 0)
	{
		printf("After read: __msg_cbytes %lu, msg_qnum %lu, msg_qbytes %lu\n", (unsigned long)info.__msg_cbytes, (unsigned long)info.msg_qnum, (unsigned long)info.msg_qbytes); 
	}
	system("ipcs -q");
	
	if(msgctl(msgfd, IPC_RMID, NULL) == -1)
	{
		printf("remove failed! %s\n", strerror(errno));
		return -1;
	}

	system("ipcs -q");
	return 0;
}
