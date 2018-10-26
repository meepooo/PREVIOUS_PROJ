#ifndef _DES_H
#define _DES_H

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define TRUE  1
#define FALSE 0

typedef unsigned long DRC_DES_KS[16][2];	/* Single-key DES key schedule */
typedef unsigned long DRC_DES3_KS[48][2];	/* Triple-DES key schedule */

int DRC_encryptdes(char * outdata, int * outlen, const char *indata , const int inlen, const char * key);
int DRC_decryptdes(char * outdata, long * outlen, const char *indata,const long inlen, const char * key);
int DRC_encrypt3des(char * outdata, long * outlen, const char * indata, const long inlen, const char * key);
int DRC_decrypt3des(char * outdata, long * outlen, const char * indata, const long inlen, const char * key);

void DRC_deskey(DRC_DES_KS,unsigned char *,int);
void DRC_des3key(DRC_DES3_KS,unsigned char *,int);

void DRC_des(DRC_DES_KS,unsigned char *,unsigned long [8][64]);
void DRC_des3(DRC_DES3_KS,unsigned char *,unsigned long [8][64]);
#endif
