#ifndef DRC_ESBMD5_H
#define DRC_ESBMD5_H

typedef unsigned char * POINTER;
typedef unsigned short int UINT2;
typedef unsigned int UINT4;

typedef struct DRC_Md5_ctx {
 UINT4 state[4];
 UINT4 count[2];
 unsigned char buffer[64];
} DRC_Md5_ctx;

void DRC_md5Init (DRC_Md5_ctx *context);
void DRC_md5Update(DRC_Md5_ctx *context, unsigned char *input,unsigned int inputLen);

void DRC_md5Final (unsigned char digest[16], DRC_Md5_ctx *context);
void DRC_md5Transform (UINT4 [4], unsigned char [64]) ;
void DRC_Encode(unsigned char *, UINT4 *, unsigned int);
void DRC_Decode (UINT4 *, unsigned char *, unsigned int);
void DRC_md5Memcpy(POINTER, POINTER, unsigned int);
void DRC_md5Memset(POINTER, int, unsigned int);

char * DRC_getMd5Str(char *string,int len,char *output);
char * DRC_getMd5File (char *filename,char *output);
void DRC_md5Final32(char * md5str, DRC_Md5_ctx *context);
int DRC_convMd5To32Byte(unsigned char digest[16],char * md5Str);
#endif
