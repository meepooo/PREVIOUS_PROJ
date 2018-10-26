#include <stdio.h>
#include <math.h>
#include <dlfcn.h>
#include <string.h>
#include "gaps_head.h"

#include "DRC_esb_const.h"

#define DRC_S11 7
#define DRC_S12 12
#define DRC_S13 17
#define DRC_S14 22
#define DRC_S21 5
#define DRC_S22 9
#define DRC_S23 14
#define DRC_S24 20
#define DRC_S31 4
#define DRC_S32 11
#define DRC_S33 16
#define DRC_S34 23
#define DRC_S41 6
#define DRC_S42 10
#define DRC_S43 15
#define DRC_S44 21

#define DRC_F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define DRC_G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define DRC_H(x, y, z) ((x) ^ (y) ^ (z))
#define DRC_I(x, y, z) ((y) ^ ((x) | (~z)))

#define DRC_ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))


#define DRC_FF(a, b, c, d, x, s, ac) { \
 (a) += DRC_F((b), (c), (d)) + (x) + (UINT4)(ac); \
 (a) = DRC_ROTATE_LEFT ((a), (s)); \
 (a) += (b); \
 }
#define DRC_GG(a, b, c, d, x, s, ac) { \
 (a) += DRC_G ((b), (c), (d)) + (x) + (UINT4)(ac); \
 (a) = DRC_ROTATE_LEFT ((a), (s)); \
 (a) += (b); \
 }
#define DRC_HH(a, b, c, d, x, s, ac) { \
 (a) += DRC_H ((b), (c), (d)) + (x) + (UINT4)(ac); \
 (a) = DRC_ROTATE_LEFT ((a), (s)); \
 (a) += (b); \
 }
#define DRC_II(a, b, c, d, x, s, ac) { \
 (a) += DRC_I ((b), (c), (d)) + (x) + (UINT4)(ac); \
 (a) = DRC_ROTATE_LEFT ((a), (s)); \
 (a) += (b); \
 }

void DRC_md5Init (DRC_Md5_ctx *context)
{
   context->count[0] = context->count[1] = 0;
   context->state[0] = 0x67452301;
   context->state[1] = 0xefcdab89;
   context->state[2] = 0x98badcfe;
   context->state[3] = 0x10325476;
}


int DRC_convMd5To32Byte(unsigned char digest[16],char * md5Str)
{
   int i=0;
   for(i=0;i<16;i++)
       sprintf(&(md5Str[2*i]),"%02x",digest[i]);
   return 0;
}


void DRC_md5Memset (POINTER output,int value,unsigned int len)
{
   unsigned int i;
   for (i = 0; i < len; i++)
      ((char *)output)[i] = (char)value;
}

void DRC_md5Memcpy (POINTER output,POINTER input,unsigned int len)
{
   unsigned int i;
   for (i = 0; i < len; i++)
      output[i] = input[i];
}

void DRC_Decode (UINT4 *output,unsigned char *input,unsigned int len)
{
   unsigned int i, j;

   for (i = 0, j = 0; j < len; i++, j += 4)
     output[i] = ((UINT4)input[j]) | (((UINT4)input[j+1]) << 8) |
         (((UINT4)input[j+2]) << 16) | (((UINT4)input[j+3]) << 24);
}


void DRC_md5Transform (UINT4 state[4],unsigned char block[64])
{
   int i=0;

   UINT4 a = state[0], b = state[1], c = state[2], d = state[3], x[16];

   DRC_Decode (x, block, 64);

   /* Round 1 */
   DRC_FF (a, b, c, d, x[ 0], DRC_S11, 0xd76aa478); /* 1 */
   DRC_FF (d, a, b, c, x[ 1], DRC_S12, 0xe8c7b756); /* 2 */
   DRC_FF (c, d, a, b, x[ 2], DRC_S13, 0x242070db); /* 3 */
   DRC_FF (b, c, d, a, x[ 3], DRC_S14, 0xc1bdceee); /* 4 */
   DRC_FF (a, b, c, d, x[ 4], DRC_S11, 0xf57c0faf); /* 5 */
   DRC_FF (d, a, b, c, x[ 5], DRC_S12, 0x4787c62a); /* 6 */
   DRC_FF (c, d, a, b, x[ 6], DRC_S13, 0xa8304613); /* 7 */
   DRC_FF (b, c, d, a, x[ 7], DRC_S14, 0xfd469501); /* 8 */
   DRC_FF (a, b, c, d, x[ 8], DRC_S11, 0x698098d8); /* 9 */
   DRC_FF (d, a, b, c, x[ 9], DRC_S12, 0x8b44f7af); /* 10 */
   DRC_FF (c, d, a, b, x[10], DRC_S13, 0xffff5bb1); /* 11 */
   DRC_FF (b, c, d, a, x[11], DRC_S14, 0x895cd7be); /* 12 */
   DRC_FF (a, b, c, d, x[12], DRC_S11, 0x6b901122); /* 13 */
   DRC_FF (d, a, b, c, x[13], DRC_S12, 0xfd987193); /* 14 */
   DRC_FF (c, d, a, b, x[14], DRC_S13, 0xa679438e); /* 15 */
   DRC_FF (b, c, d, a, x[15], DRC_S14, 0x49b40821); /* 16 */

   /* Round 2 */
   DRC_GG (a, b, c, d, x[ 1], DRC_S21, 0xf61e2562); /* 17 */
   DRC_GG (d, a, b, c, x[ 6], DRC_S22, 0xc040b340); /* 18 */
   DRC_GG (c, d, a, b, x[11], DRC_S23, 0x265e5a51); /* 19 */
   DRC_GG (b, c, d, a, x[ 0], DRC_S24, 0xe9b6c7aa); /* 20 */
   DRC_GG (a, b, c, d, x[ 5], DRC_S21, 0xd62f105d); /* 21 */
   DRC_GG (d, a, b, c, x[10], DRC_S22, 0x2441453);  /* 22 */
   DRC_GG (c, d, a, b, x[15], DRC_S23, 0xd8a1e681); /* 23 */
   DRC_GG (b, c, d, a, x[ 4], DRC_S24, 0xe7d3fbc8); /* 24 */
   DRC_GG (a, b, c, d, x[ 9], DRC_S21, 0x21e1cde6); /* 25 */
   DRC_GG (d, a, b, c, x[14], DRC_S22, 0xc33707d6); /* 26 */
   DRC_GG (c, d, a, b, x[ 3], DRC_S23, 0xf4d50d87); /* 27 */
   DRC_GG (b, c, d, a, x[ 8], DRC_S24, 0x455a14ed); /* 28 */
   DRC_GG (a, b, c, d, x[13], DRC_S21, 0xa9e3e905); /* 29 */
   DRC_GG (d, a, b, c, x[ 2], DRC_S22, 0xfcefa3f8); /* 30 */
   DRC_GG (c, d, a, b, x[ 7], DRC_S23, 0x676f02d9); /* 31 */
   DRC_GG (b, c, d, a, x[12], DRC_S24, 0x8d2a4c8a); /* 32 */

   /* Round 3 */
   DRC_HH (a, b, c, d, x[ 5], DRC_S31, 0xfffa3942); /* 33 */
   DRC_HH (d, a, b, c, x[ 8], DRC_S32, 0x8771f681); /* 34 */
   DRC_HH (c, d, a, b, x[11], DRC_S33, 0x6d9d6122); /* 35 */
   DRC_HH (b, c, d, a, x[14], DRC_S34, 0xfde5380c); /* 36 */
   DRC_HH (a, b, c, d, x[ 1], DRC_S31, 0xa4beea44); /* 37 */
   DRC_HH (d, a, b, c, x[ 4], DRC_S32, 0x4bdecfa9); /* 38 */
   DRC_HH (c, d, a, b, x[ 7], DRC_S33, 0xf6bb4b60); /* 39 */
   DRC_HH (b, c, d, a, x[10], DRC_S34, 0xbebfbc70); /* 40 */
   DRC_HH (a, b, c, d, x[13], DRC_S31, 0x289b7ec6); /* 41 */
   DRC_HH (d, a, b, c, x[ 0], DRC_S32, 0xeaa127fa); /* 42 */
   DRC_HH (c, d, a, b, x[ 3], DRC_S33, 0xd4ef3085); /* 43 */
   DRC_HH (b, c, d, a, x[ 6], DRC_S34, 0x4881d05);  /* 44 */
   DRC_HH (a, b, c, d, x[ 9], DRC_S31, 0xd9d4d039); /* 45 */
   DRC_HH (d, a, b, c, x[12], DRC_S32, 0xe6db99e5); /* 46 */
   DRC_HH (c, d, a, b, x[15], DRC_S33, 0x1fa27cf8); /* 47 */
   DRC_HH (b, c, d, a, x[ 2], DRC_S34, 0xc4ac5665); /* 48 */

   /* Round 4 */
   DRC_II (a, b, c, d, x[ 0], DRC_S41, 0xf4292244); /* 49 */
   DRC_II (d, a, b, c, x[ 7], DRC_S42, 0x432aff97); /* 50 */
   DRC_II (c, d, a, b, x[14], DRC_S43, 0xab9423a7); /* 51 */
   DRC_II (b, c, d, a, x[ 5], DRC_S44, 0xfc93a039); /* 52 */
   DRC_II (a, b, c, d, x[12], DRC_S41, 0x655b59c3); /* 53 */
   DRC_II (d, a, b, c, x[ 3], DRC_S42, 0x8f0ccc92); /* 54 */
   DRC_II (c, d, a, b, x[10], DRC_S43, 0xffeff47d); /* 55 */
   DRC_II (b, c, d, a, x[ 1], DRC_S44, 0x85845dd1); /* 56 */
   DRC_II (a, b, c, d, x[ 8], DRC_S41, 0x6fa87e4f); /* 57 */
   DRC_II (d, a, b, c, x[15], DRC_S42, 0xfe2ce6e0); /* 58 */
   DRC_II (c, d, a, b, x[ 6], DRC_S43, 0xa3014314); /* 59 */
   DRC_II (b, c, d, a, x[13], DRC_S44, 0x4e0811a1); /* 60 */
   DRC_II (a, b, c, d, x[ 4], DRC_S41, 0xf7537e82); /* 61 */
   DRC_II (d, a, b, c, x[11], DRC_S42, 0xbd3af235); /* 62 */
   DRC_II (c, d, a, b, x[ 2], DRC_S43, 0x2ad7d2bb); /* 63 */
   DRC_II (b, c, d, a, x[ 9], DRC_S44, 0xeb86d391); /* 64 */

   state[0] += a;
   state[1] += b;
   state[2] += c;
   state[3] += d;

   DRC_md5Memset ((POINTER)x, 0, sizeof (x));
}

void DRC_Encode (unsigned char *output,UINT4 *input,unsigned int len)

{
   unsigned int i, j;

   for (i = 0, j = 0; j < len; i++, j += 4) 
   {
      output[j] = (unsigned char)(input[i] & 0xff);
      output[j+1] = (unsigned char)((input[i] >> 8) & 0xff);
      output[j+2] = (unsigned char)((input[i] >> 16) & 0xff);
      output[j+3] = (unsigned char)((input[i] >> 24) & 0xff);
   }
}

void DRC_md5Update (DRC_Md5_ctx *context, unsigned char *input,unsigned int inputLen )
{
   unsigned int i, index, partLen;

   /* Compute number of bytes mod 64 */
   index = (unsigned int)((context->count[0] >> 3) & 0x3F);

   /* Update number of bits */
   if ((context->count[0] += ((UINT4)inputLen << 3)) < ((UINT4)inputLen << 3))
      context->count[1]++;
   context->count[1] += ((UINT4)inputLen >> 29);

   partLen = 64 - index;
 
   if (inputLen >= partLen) {
      DRC_md5Memcpy((POINTER)&context->buffer[index], (POINTER)input, partLen);
      DRC_md5Transform (context->state, context->buffer);

      for (i = partLen; i + 63 < inputLen; i += 64)
         DRC_md5Transform (context->state, &input[i]);

      index = 0;
   }
   else
      i = 0;

   /* Buffer remaining input */
   DRC_md5Memcpy ((POINTER)&context->buffer[index], (POINTER)&input[i], inputLen-i);
}


void DRC_md5Final (unsigned char digest[16], DRC_Md5_ctx *context)
{
   unsigned char bits[8];
   unsigned int index, padLen;

   unsigned char padding[64] = {
     0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
   };

   DRC_Encode (bits, context->count, 8);

   index = (unsigned int)((context->count[0] >> 3) & 0x3f);
   padLen = (index < 56) ? (56 - index) : (120 - index);
   DRC_md5Update (context,(unsigned char*) padding, padLen);

   /* Append length (before padding) */
   DRC_md5Update (context, bits, 8);
   /* Store state in digest */
   DRC_Encode (digest, context->state, 16);

   DRC_md5Memset ((POINTER)context, 0, sizeof (*context));
}

void DRC_md5Final32(char * md5str, DRC_Md5_ctx *context)
{
	 unsigned char digest[16];
	 DRC_md5Final(digest,context);
	 DRC_convMd5To32Byte(digest,md5str);
	
}

char * DRC_getMd5Str(char *string,int len,char *output)
{
   DRC_Md5_ctx context;
   unsigned char digest[16];
   char output1[32];
   int i;

   DRC_md5Init (&context);
   DRC_md5Update (&context, (unsigned char*)string, len);
   DRC_md5Final (digest, &context);

   DRC_convMd5To32Byte(digest,output);
   return output;
}


char * DRC_getMd5File (char *filename,char *output)
{ 
   FILE *file;
   DRC_Md5_ctx context;
   int len;
   unsigned char buffer[1024], digest[16];
   int i;
   char output1[32];
 
   if ((file = fopen (filename, "rb")) == NULL)
   { 
   	  printf ("%s can't be openedn", filename);
      return 0;
   }
   else {
      DRC_md5Init (&context);
      while (len = fread (buffer, 1, 1024, file))
         DRC_md5Update (&context, buffer, len);
      DRC_md5Final (digest, &context);
      fclose (file);
 
      DRC_convMd5To32Byte(digest,output);
      return output;
   }
}
