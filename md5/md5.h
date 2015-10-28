#ifndef MD5_H
#define MD5_H 

#ifdef __alpha
typedef unsigned int uint32;
#else
typedef unsigned long uint32;
#endif

struct MD5Context {
		uint32 buf[4];
		uint32 bits[2];
		unsigned char in[64];
};

extern void MD5Init(struct MD5Context *ctx);
extern void MD5Update(struct MD5Context  *ctx, unsigned char const  *buf, unsigned len);
extern void MD5Final(unsigned char *digest, struct MD5Context  *ctx);
extern void MD5Transform(uint32 *buf, uint32  *in);
extern char *PKTCB_MD5(unsigned char buf[], 
                     unsigned len,
                     unsigned char res[16]);


#endif /* !MD5_H */
