/********************************************************************
版权所有:杭州恒生电子股份有限公司
项目名称:中间业务平台项目(AGENT2.0)
版    本:V3.2
操作系统:
文件名称:DRCESB_COMM
文件描述:GAPS与东莞农商行ESB通讯组件
项 目 组:
程 序 员:
发布日期:2015年07月21日
修    订:
修改日期:
*********************************************************************/
#include <stdio.h>
#include <math.h>
#include <dlfcn.h>
#include <string.h>
#include <openssl/rsa.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <sys/timeb.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <iconv.h>

#include "gaps_head.h"

#include "DRC_esb_const.h"

#define SOCOMPBUILDNO BUILDDATETIME
#define SOCOMPVERSION "4.0.01"

#define  MAX_CFG     30
#define  KEY_LGH     80
#define  VALUE_LGH   200
#define  SYN_KEY_TIME_OUT       10
#define  IS32BITPROGRAM 0
#define  SYN_WORKKEY_FLAG  "LL"
#define  REQ_BUSS_FLAG  "AA"
#define  TIME_INFINITE         60
#define  MAX_SOCK_BUF_SIZE     1024*1024
#define  MASTER_KEY_BEGIN       3
#define  MASTER_KEY_LENGTH       24
#define  KEY_LIVE_TIME       24*3600*1000

#ifndef    TRUE
#define    TRUE                  1
#endif
#ifndef    FALSE
#define    FALSE                 0
#endif

struct  DRC_CfgData
{
   char  key[KEY_LGH];
   char  value[VALUE_LGH];
   int   flag;
};
static struct DRC_CfgData DRC_dcfs_stCfgData [MAX_CFG];

static struct DRC_stKey *DRC_key=NULL;

static char DRC_uid[20]="";
static int DRC_initflag = 0;     /* 加载参数标志 0：未加载 1 已加载 */
static char * DRC_UID = "uid";
static char base64_table[] =
"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

const static char DRC_masterKeyPool[40] = {
   0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x10,
   0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x10,
   0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x10,
   0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x10
   };
static char DRC_masterkey[25]="";

pthread_mutex_t DRC_lock;

int ShowSocompVersion(char *sinfo,int isize)
{
   char sversion[]="<?xml version=\"1.0\" encoding=\"GB2312\"?>\
      <root>\
         <soname>SCOMM_CALLGXP.so</soname>\
         <sosrcname>SCOMM_CALLGXP.c</sosrcname>\
         <sonote>GXP通讯组件集合</sonote>\
         <version>\
           <rec ver=\"4.0.01\" modify=\"2009-6-11 10:43\" programer=\"Wangt Chendh\" filesize=\"70096\">整理为ASPKV4环境GXP通讯组件</rec>\
         </version>\
      </root>";
   printf("\n================动态组件基本信息================\n");
   printf("SOCOMPBUILDNO:%s\n",SOCOMPBUILDNO);
   printf("SOCOMPVERSION:%s\n",SOCOMPVERSION);
   printf("%s-%s\n",__PROJECTSNAME,__VERSION);
   if (strlen(sversion) >= isize)
   {
      printf(" -->取详细信息失败...\n");
      return -2;
   }
   strcpy(sinfo,sversion);
   printf(" -->请查看详细信息...\n");
   return 0;      
}

/************************************************************************
功能：      取系统毫秒级时间
输入：      无
输出：      long型的整数
返回：      距离1970年1月1日至今的毫秒数
注意：      32位程序long将存储不下,只能用于64位程序
开发人员:   PengLiyang
修改日期:   2013-08-16
************************************************************************/
long DRC_getMillitmSystemTime()
{
   struct timeb t;
   ftime(&t);
   return 1000*t.time + t.millitm;
}

/*********************************************************
功能描述:   对一行的数据进行处理，去除空格，tab，\r,\n等字符
开发人员:   chenhh
修改日期:   2012-01-17
*********************************************************/
char * DRC_StrPack( char * str )
{
   int i;
   int b1,e1;

   for (i = 0; str[i]==' '|| str[i]=='\t'|| str[i]==0x0A || str[i]==0x0D; i++) ;
   b1 = i;
   for (i = strlen(str)-1; i >= b1 && (str[i] == ' ' || str[i] == '\t' || str[i] == 0x0A || str[i]==0x0D); i--);
      e1 = i;
   if (e1 >= b1)
      memcpy( str, str+b1, e1-b1+1 );
   str[e1 - b1 + 1] = 0;
   return str;
}

int DRC_InitConfig(void)
{
   int LineChar = 1024;
   int i;
   FILE *fp;
   char Line[1024], value[100], key1[200];
   char *StrP;
   char CFG_FILE[300];

   if (DRC_initflag)
      return 0;

   memset(CFG_FILE, 0x00, sizeof(CFG_FILE));
   memset((char *)&DRC_dcfs_stCfgData,0x00,sizeof(DRC_dcfs_stCfgData));

   i = 0;
 
   if (getenv("ESB_CAPI_CFG") ==NULL)
   {
      sprintf(CFG_FILE, "%s/etc/cfg.ini", getenv("HOME"));
   } else {
      sprintf(CFG_FILE, "%s", getenv("ESB_CAPI_CFG"));
   }

   if ((fp = fopen(CFG_FILE,"r")) == NULL)
   {
      return -1;
   }
   memset(Line,0x00,sizeof(Line));
   while (fgets(Line,LineChar,fp)!=NULL)
   {
      if ((StrP=strchr(Line,'#'))!=NULL)
      {
         *StrP=0x00;
      }

      DRC_StrPack(Line);

      if (*Line=='#' || strlen(Line) == 0) continue;
      if((StrP=strchr(Line,'=')) == NULL) continue;

      memset(value,0x00,sizeof(value));
      memset(key1,0x00,sizeof(key1));
      if ( strlen(StrP + 1) < sizeof(value))
         strcpy(value,StrP + 1);
      else
          memcpy(value,StrP + 1,sizeof(value)-1);

      if (StrP-Line < sizeof(key1))
         strncpy(key1,Line,StrP-Line);
      else
          memcpy(key1,Line,sizeof(key1)-1);

      memcpy(DRC_dcfs_stCfgData[i].key, DRC_StrPack(key1),sizeof(DRC_dcfs_stCfgData[i].key)-1);
      memcpy(DRC_dcfs_stCfgData[i].value, DRC_StrPack(value),sizeof(DRC_dcfs_stCfgData[i].value)-1);

      memset(Line,0x00,sizeof(Line));
      i++;
      if (i>MAX_CFG) 
      {
         /* printf("error load config file: the Line Number big [%d]", MAX_CFG); */
         fclose(fp);
         return -2;
      }
   }
   fclose(fp);

   memset(DRC_uid,0x00,sizeof(DRC_uid));
   DRC_initflag=1;
   return 0;
}

/*********************************************************
功能描述:   从输入字段中查找某个属性的值,各属性的分割符是'&'
开发人员:   chenhh
修改日期:   2012-01-17
*********************************************************/
int DRC_findValue(const char * input , char * key ,char * value)
{
   long input_len = strlen(input);
   long key_len = strlen(key);

   int i= 0,s = 0 , e =0;
   for (i = 0; i<input_len; i++)
   {
       if (i==0 || input[i]=='&')
       {
          s=i==0?i:i+1;
          if (memcmp(key,input+s,key_len)==0)
          {
             for (e=i+1;e<input_len;e++)
             {
                 if (input[e]=='&')
                    break;
             }
             i=e;
             memcpy(value,input+s+key_len+1,e-s-key_len-1);
             return 0;
          }
       }
   }
   return -1;
}

int DRC_getUid(HXMLTREE lXmlhandle,char user[80])
{
   if (strlen(DRC_uid)==0)
       DRC_setUid(lXmlhandle);

   /* LOG(LM_DEBUG,Fmtmsg("组件[%s] get uid is %s.",fpub_GetCompname(lXmlhandle),DRC_uid),__func__) */
   sprintf(user,"%s",DRC_uid);
   return 0;
}

int DRC_GetConfig(const char *key,char* value)
{
   int i;
 
   for (i=0;i<MAX_CFG;i++)
   {
      if (!strcmp(DRC_dcfs_stCfgData[i].key, key))
      {
         strcpy(value, DRC_dcfs_stCfgData[i].value);
         return 0;
      }
   }
   if (i==MAX_CFG)
   { 
      strcpy(value,"null");
      return -1;
   }
   return 0;   
}

int DRC_setUid(HXMLTREE lXmlhandle)
{
   char tmp[256];
   int ret;

   /* LOG(LM_DEBUG,Fmtmsg("组件[%s] now going to set the uid.",fpub_GetCompname(lXmlhandle)),__func__) */
   memset(DRC_uid,0x00,sizeof(DRC_uid));
   ret = DRC_GetConfig(DRC_UID,tmp);
   if (ret!=0)
   {
      LOG(LM_STD,Fmtmsg("组件[%s] could not load uid from cfg file",fpub_GetCompname(lXmlhandle)),__func__)
      return -1;
   }
   else
   {
      int len = strlen(tmp);
      memcpy(DRC_uid,tmp,len);
   }

   /* LOG(LM_DEBUG,Fmtmsg("组件[%s] the uid is %s.",fpub_GetCompname(lXmlhandle),DRC_uid),__func__) */
   return ret;
}

/*********************************************************
功能描述:   对报文进行MD5的计算后,使用3des进行加密
开发人员:   chenhh
修改日期:   2012-01-17
*********************************************************/
int DRC_encodeXmlPack(HXMLTREE lXmlhandle,char * input,char * out_value,long * out_len)
{
   int ret =0;
   char des[41],md5[33],code[256];
   long len;
   int inputLen;

   /* md5计算 */
   memset(md5,0x00,sizeof(md5));
   inputLen = strlen(input);
   DRC_getMd5Str(input,inputLen,md5);

   /* LOG(LM_DEBUG,Fmtmsg("组件[%s] The md5 of input is [%s]",fpub_GetCompname(lXmlhandle),md5),__func__) */
   /* 3des加密 */
   len = 40;
   memset(des,0x00,sizeof(des));
   ret = DRC_encrypt3des(des,&len,md5,32,DRC_key->macKey);
   if (ret <0)
      return ret;

   /* base64编码 */
   memset(code,0x00,sizeof(code));
   ret = DRC_base64_encode(des,40,code);
   if (ret <0)
      return ret;

   /* 拷贝信息到输出参数中 */
   *out_len = strlen(code);
   memcpy(out_value,code,*out_len);

   return ret;
}

/*********************************************************
功能描述:   组成系统头
开发人员:   chenhh
修改日期:   2012-01-13
*********************************************************/
int DRC_packHeadStr(HXMLTREE lXmlhandle,char * input,char * head,int * olen,int flag)
{
   int ret;
   char headLen[5];
   int len;
   char code[256];
   long code_len;
   char user[80];
   char esbservinfo[256];
   char sTmp[256];

   if (flag==1)
   {
      memset(user,0x00,sizeof(user));
      DRC_getUid(lXmlhandle,user);
      sprintf(head+4,"flag=%s&uid=%s",SYN_WORKKEY_FLAG,user);
   }
   else
   {
      /* 生成报文的验证码*/
      memset(code,0x00,sizeof(code)); 
      ret = DRC_encodeXmlPack(lXmlhandle,input,code, &code_len);
      if (ret <0)
      {
         LOG(LM_STD,Fmtmsg("组件[%s] encodeXmlPack",fpub_GetCompname(lXmlhandle)),__func__)
         return -1;
      }
      /* 形成请求的报文头信息*/
      //COMP_GETPARSEPARAS(2, esbservinfo, "esbservinfo") ;
      //xml_GetElement(lXmlhandle, "/pub/servinfo", esbservinfo, sizeof(esbservinfo));
      //trim(esbservinfo);
      memset(sTmp, 0, sizeof(sTmp)) ;
      memset(esbservinfo, 0, sizeof(esbservinfo)) ;
      xml_GetElement(lXmlhandle, "/service/sys-header/SYS_HEAD/struct/SERVICE_CODE", sTmp, sizeof(sTmp));
      trim(sTmp);
      strcat(esbservinfo, sTmp) ;
      xml_GetElement(lXmlhandle, "/service/sys-header/SYS_HEAD/struct/SERVICE_SCENE", sTmp, sizeof(sTmp));
      trim(sTmp);
      strcat(esbservinfo, sTmp) ;
      xml_GetElement(lXmlhandle, "/service/sys-header/SYS_HEAD/struct/SERVICE_VERSION", sTmp, sizeof(sTmp));
      trim(sTmp);
      strcat(esbservinfo, sTmp) ;
      sprintf(head+4,"flag=%s&uid=%s&&workdate=%s&series=%s&servInfo=%s",REQ_BUSS_FLAG,DRC_key->uid,DRC_key->workDate,code,esbservinfo);
      //sprintf(head+4,"flag=%s&uid=%s&&workdate=%s&series=%s",REQ_BUSS_FLAG,DRC_key->uid,DRC_key->workDate,code);
   }
 
   len = strlen((head+4));
   sprintf(headLen,"%04d",len);
   memcpy(head,headLen,4);
   *olen = 4 + len;

   /* LOG(LM_DEBUG,Fmtmsg("组件[%s] pack head data is [%s]",fpub_GetCompname(lXmlhandle),head),__func__) */
   LOG(LM_DEBUG,Fmtmsg("组件[%s] pack head data is [%s]",fpub_GetCompname(lXmlhandle),head),__func__)

   return 0;
}

/*********************************************************
功能描述: 使用openssl中的base64进行解码
开发人员:   chenhh
修改日期:   2012-01-13
*********************************************************/
int DRC_open_base64_decode(unsigned char *in,int len,char * out,int * olen)
{
   BIO      *b64, *bmem;
   b64 = BIO_new(BIO_f_base64());
   bmem = BIO_new_mem_buf(in, len);
   bmem = BIO_push(b64, bmem);
   *olen=BIO_read(bmem, out, len);
   BIO_free_all(bmem);
   return *olen;
}

/*base64编码函数*/
int DRC_base64_encode(unsigned char * bin_data,long bin_size,char * base64_data)
{
   unsigned long i,j,k,blk_size,remain_size;
   unsigned char *p, left[3];
   if (bin_data == NULL) {
      return -1;
   }
 
   blk_size = bin_size / 3;
   remain_size = bin_size % 3;
 
   p = bin_data;
   j = 0;
 
   for(i=0;i<blk_size;i++){
      k = (p[0] & 0xFC) >> 2;
      base64_data[j++] = base64_table[k];
      k = ((p[0] & 0x03) << 4) | (p[1] >> 4);
      base64_data[j++] = base64_table[k];
      k = ((p[1] & 0x0F) << 2) | (p[2] >> 6);
      base64_data[j++] = base64_table[k];
      k = p[2] & 0x3F;
      base64_data[j++] = base64_table[k];
      p += 3;
   }
 
   switch(remain_size){
      case 0:
         break;
 
      case 1:
         left[0] = p[0];
         left[1] = 0;
         p = left;
 
         k = (p[0] & 0xFC) >> 2;
         base64_data[j++] = base64_table[k];
         k = ((p[0] & 0x03) << 4) | (p[1] >> 4);
         base64_data[j++] = base64_table[k];
 
         base64_data[j++] = '=';
         base64_data[j++] = '=';
         break;
 
      case 2:
         left[0] = p[0];
         left[1] = p[1];
         left[2] = 0;
         p = left;
 
         k = (p[0] & 0xFC) >> 2;
         base64_data[j++] = base64_table[k];
         k = ((p[0] & 0x03) << 4) | (p[1] >> 4);
         base64_data[j++] = base64_table[k];
         k = ((p[1] & 0x0F) << 2) | (p[2] >> 6);
         base64_data[j++] = base64_table[k];
         base64_data[j++] = '=';
         break;

      default:
         break;
   }

   base64_data[j] = 0;
   return 0;
}

/*base64解码函数*/
int DRC_base64_decode(char * base64_data, unsigned char * bin_data,long * bin_size)
{
   unsigned long i,j,k,m,n,l;
   unsigned char four_bin[4];
   char four_char[4],c;
 
   if (base64_data == NULL) {
      return -1;
   }
 
   j = strlen(base64_data);
   i = 0;
   l = 0;
 
   for(;;){
      if ((i+4) > j){
         break;
      }
 
      for (k=0;k<4;k++){
         if (i == j){
            break;
         }
 
         c = base64_data[i++];
         if ((c == '+') || (c == '/') || (c == '=') ||
            ((c >= '0') && (c <= '9')) ||
            ((c >= 'A') && (c <= 'Z')) ||
            ((c >= 'a') && (c <= 'z'))){
            four_char[k] = c;
         }
      }
 
      if (k != 4){
         return -1;
      }

      n = 0;
      for (k=0;k<4;k++){
         if (four_char[k] != '='){
            for (m=0;m<64;m++){
               if (base64_table[m] == four_char[k]){
                  four_bin[k] = (unsigned char)m;
               }
            }
         }
         else{
            n++;
         }
      }
 
      switch(n){
         case 0:
            bin_data[l++] = (four_bin[0] << 2) | (four_bin[1] >> 4);
            bin_data[l++] = (four_bin[1] << 4) | (four_bin[2] >> 2);
            bin_data[l++] = (four_bin[2] << 6) | four_bin[3]; 
            break;

         case 1:
            bin_data[l++] = (four_bin[0] << 2) | (four_bin[1] >> 4);
            bin_data[l++] = (four_bin[1] << 4) | (four_bin[2] >> 2);
            break;

         case 2:
            bin_data[l++] = (four_bin[0] << 2) | (four_bin[1] >> 4);
            break;

         default:
            break;
      }
 
      if (n != 0){
         break;
      }
   }
 
   /*l++;*/
   *bin_size = l;

   return 0;
}

int DRC_setMasterKey(HXMLTREE lXmlhandle)
{
   char keyfile[100];
   char des[1024];
   int ret ;
   int len;
   long outlen = 0;
   FILE *fp;

   char name[100];
   char passwd[100];
   char scrtKey[25];
 
   /* LOG(LM_DEBUG,Fmtmsg("组件[%s] now going to set the masterkey",fpub_GetCompname(lXmlhandle)),__func__) */
   memset(keyfile,0x00,sizeof(keyfile));
   ret = DRC_GetConfig("keyfile",keyfile);
   if (ret!=0)
   {
      LOG(LM_STD,Fmtmsg("组件[%s] could not load masterkey from keyfile",fpub_GetCompname(lXmlhandle)),__func__)
      return -1;
   }
   else
   {
      if ((fp = fopen(keyfile,"r")) == NULL)
      {
         LOG(LM_STD,Fmtmsg("组件[%s] cannot not open key file masterkey",fpub_GetCompname(lXmlhandle)),__func__)
         return -1;
      }

      memset(name,0x00,sizeof(name));
      fgets(name,100,fp);
      memset(passwd,0x00,sizeof(passwd));
      fgets(passwd,100,fp);

      memset(des,0x00,sizeof(des));

      /*ret = drc_esb_open_base64_decode(passwd,strlen(passwd),des,&outlen);*/
      DRC_base64_decode(passwd,des,&outlen);

      /* LOG(LM_DEBUG,Fmtmsg("组件[%s] get des is [%s],[%d]",fpub_GetCompname(lXmlhandle),des,outlen),__func__) */
      memcpy(scrtKey,DRC_masterKeyPool + MASTER_KEY_BEGIN,MASTER_KEY_LENGTH);
      outlen = 0;

      DRC_decrypt3des(DRC_masterkey,&outlen,des,16,scrtKey);
   }

   fclose(fp);
   return ret;
}

int DRC_getMasterKey(HXMLTREE lXmlhandle,char key[25])
{
   if (strlen(DRC_masterkey)==0)
      DRC_setMasterKey(lXmlhandle);
   memcpy(key,DRC_masterkey,24);
   key[24]=0x00;
   return 0;
}

/*********************************************************
功能描述:   解密keystore文件
开发人员:   chenjie
修改日期:   2012-03-02
*********************************************************/
int DRC_decodeKeyStoreFile(HXMLTREE lXmlhandle,char *keyDataFile)
{
   FILE *in_stream;
   FILE *out_stream;
   char fileCont[1024];
   char dest[1024];
   long readLen;
   int len2;
   long outlen = 0;
   char keyPasswd[25];
   int ret = 0;
   
   /*added by dpl 20180918 添加变量*/
   char keyFileTmpName[200] = {0};
   char keyFileTail[100] = {0};

   memset(keyPasswd,0x00,sizeof(keyPasswd));
   DRC_getMasterKey(lXmlhandle,keyPasswd);

   while(strlen(keyPasswd) < 24){
      strcat(keyPasswd,"0");
   }

   in_stream=fopen(keyDataFile, "rb");

   if (in_stream == NULL)
   { 
      LOG(LM_STD,Fmtmsg("组件[%s] Could not open data file [%s]",fpub_GetCompname(lXmlhandle),keyDataFile),__func__)
      return -1;
   }

   /*modified by dpl 20180913 
    * 临时文件名后缀修改为加系统日期+pid号
    * 且修改临时文件存放路径
   strcat(keyDataFile,".temp");*/
   memset(keyFileTmpName,0x00,sizeof(keyFileTmpName));
   memset(keyFileTail,0x00,sizeof(keyFileTail));
   DRC_GetConfig("keystoretmpfile",keyFileTmpName);
   sprintf(keyFileTail, ".%s.%d",GetSysDate(),getpid());
   strcat(keyFileTmpName,keyFileTail);
   strcpy(keyDataFile,keyFileTmpName);

   LOG(LM_DEBUG,Fmtmsg("组件[%s] keyDataFile=[%s]",fpub_GetCompname(lXmlhandle),keyDataFile),__func__)
   out_stream=fopen(keyDataFile, "wb");

   while ((readLen = fread(fileCont,sizeof(char),1024,in_stream))>0)
   {
      ret = DRC_decrypt3des(dest,&outlen,fileCont,readLen,keyPasswd);
      if (ret < 0)
      {
         LOG(LM_STD,Fmtmsg("组件[%s], decrypt3des exec error",fpub_GetCompname(lXmlhandle)),__func__)
         fclose(in_stream);
         fclose(out_stream);
         return ret;
      }

      len2 = fwrite(dest,sizeof(char),outlen,out_stream);
      fflush(out_stream);
   }
   fclose(in_stream);
   fclose(out_stream);

   return 0;
}

/*********************************************************
功能描述:   解密keystore文件
开发人员:   chenjie
修改日期:   2012-03-02
*********************************************************/
int DRC_clearKeyStoreFile(char *keyDataFile)
{
   FILE *out_stream;
 
   out_stream=fopen(keyDataFile, "wb");

   if (out_stream == NULL)
   { 
      return -1;
   }
 
   fclose(out_stream);
   return 0;
}

/*********************************************************
功能描述: 更新Key对象
开发人员:   chenhh
修改日期:   2012-01-13
*********************************************************/
int DRC_decodeKey(HXMLTREE lXmlhandle,unsigned char * indata,int inLen,unsigned char * outdata,int * outLen)
{
   char keyFileName[256];
   int ret = 0;
 
   FILE* private_file=NULL;
   RSA* prikey;
   int keysize,len;
   char keyPasswd[25];

   memset(keyFileName,0x00,sizeof(keyFileName));
   DRC_GetConfig("keystorefile",keyFileName);
 
   ret = DRC_decodeKeyStoreFile(lXmlhandle,keyFileName);
   LOG(LM_DEBUG,Fmtmsg("组件[%s] DRC_decodeKeyStoreFile ret=[%d]",fpub_GetCompname(lXmlhandle),ret),__func__)
   if (ret < 0)
   {
      LOG(LM_STD,Fmtmsg("组件[%s] decrypt keystore file error",fpub_GetCompname(lXmlhandle)),__func__)
      return ret;
   }
   private_file = fopen(keyFileName, "r");

   if (private_file==NULL)
   {
      return -1;
   }

   prikey = PEM_read_RSAPrivateKey(private_file, NULL, NULL, "123123");   /* 系统函数 */
   if (prikey==NULL)
   {
      fclose(private_file);
      return -2;
   }
   keysize = RSA_size(prikey);      /* 系统函数 */
 
   /* LOG(LM_DEBUG,Fmtmsg("组件[%s] keysize is %d",fpub_GetCompname(lXmlhandle),keysize),__func__) */
   *outLen = RSA_private_decrypt(keysize, (unsigned char*)indata, (unsigned char*)outdata, prikey, 1);  /* 系统函数 */
 
   fclose(private_file);
   RSA_free(prikey);   /* 系统函数 */

   DRC_clearKeyStoreFile(keyFileName);
   return ret;
}

/*********************************************************
功能描述:   使用本地私钥解码工作密钥
开发人员:   chenhh
修改日期:   2012-01-17
*********************************************************/
int DRC_decodeKeyValue(HXMLTREE lXmlhandle,char * key,char * out_value,int *out_len)
{
   int ret =0;
   int len = 0,keyLen;
   char des[1024],key_tmp[1024];

   /* base64解码 */
   memset(des,0x00,sizeof(des));
   ret = DRC_open_base64_decode(key,strlen(key),des,&len);
   LOG(LM_STD,Fmtmsg("组件[%s] DRC_open_base64_decode, ret=[%d]",fpub_GetCompname(lXmlhandle),ret),__func__)
   if (ret<0)
   {
      LOG(LM_STD,Fmtmsg("组件[%s] DRC_open_base64_decode is error:return value is [%d]",fpub_GetCompname(lXmlhandle),ret),__func__)
   }

   /* 用私钥解密 */
   memset(key_tmp,0x00,sizeof(key_tmp));
 
   ret = DRC_decodeKey(lXmlhandle,des,len,out_value,out_len); 
   LOG(LM_STD,Fmtmsg("组件[%s] DRC_decodeKey, out_value=[%s], ret=[%d]",fpub_GetCompname(lXmlhandle),out_value,ret),__func__)
   if (ret<0)
   {
      LOG(LM_STD,Fmtmsg("组件[%s] decodeKey is error:return value is [%d]",fpub_GetCompname(lXmlhandle),ret),__func__)
   }

   return ret;
}

/*********************************************************
功能描述: 创建Key对象
开发人员:   chenhh
修改日期:   2012-01-13
*********************************************************/
DRC_stKey * DRC_new_Key()
{
   struct DRC_stKey * newKey = ( struct DRC_stKey * ) malloc( sizeof( struct DRC_stKey ) );
   memset(newKey,0x00,sizeof( struct DRC_stKey ));
   return newKey;
}

/*********************************************************
功能描述: 释放Key对象
开发人员:   chenhh
修改日期:   2012-01-13
*********************************************************/
int DRC_free_Key(struct DRC_stKey * freeKey)
{
   if (freeKey!=NULL)
   {
      free(freeKey);
      freeKey=NULL;
   }
}

/*********************************************************
功能描述: 更新Key对象
开发人员:   chenhh
修改日期:   2012-01-13
*********************************************************/
int DRC_setEsbKey(HXMLTREE lXmlhandle,char * macKey,char * pinKey,char * workDate,long ltime)
{
   struct DRC_stKey * newKey = NULL;
   struct DRC_stKey * tmpKey = NULL;
   time_t t;
   long lt;
   char user[80];

   newKey = DRC_new_Key();
   memcpy(newKey->macKey,macKey,24);
   memcpy(newKey->pinKey,pinKey,24);
   memcpy(newKey->workDate,workDate,8);

   if (IS32BITPROGRAM)
   {
      /* 32位程序,用秒计算,且需将服务器下发的毫秒数换算成秒数 */
      time(&t);
      lt = t+(long)ltime/1000;
   } else {
      /* 64位程序,用毫秒计算 */
      lt= DRC_getMillitmSystemTime()+(long)ltime;
   }
   newKey->time=lt;
   memset(user,0x00,sizeof(user));
   DRC_getUid(lXmlhandle,user);
   sprintf(newKey->uid,"%s",user);

   tmpKey=DRC_key;
   DRC_key=newKey;
   DRC_free_Key(tmpKey);
   
   /*added by dpl 没有返回值*/
   return 0;
}

/*********************************************************
功能描述:   设置工作密钥
开发人员:   chenhh
修改日期:   2012-01-17
*********************************************************/
int DRC_updateWorkkey(HXMLTREE lXmlhandle,char * head)
{
   int ret;
   char tmp    [1024];
   char keytmp[1024];
   int  len;
   long olen;
   char macKey[25];
   char pinKey[25];
   char checkValue[17];
   char checkDay[17];
   char workDate[9];

   long liveTime = KEY_LIVE_TIME;
   char keyLiveTime[20];
LOG(LM_DEBUG,Fmtmsg("组件[%s],DRC_updateWorkkey begin----",fpub_GetCompname(lXmlhandle)),__func__)
   /* LOG(LM_DEBUG,Fmtmsg("组件[%s] begin updateWorkkey",fpub_GetCompname(lXmlhandle)),__func__) */
   /* deal with workdate */
   memset(workDate,0x00,sizeof(workDate));
   ret = DRC_findValue(head,"workdate",workDate);
   if (ret <0)
      return -1;

   LOG(LM_DEBUG,Fmtmsg("组件[%s] find workdate ok,workdate = [%s]",fpub_GetCompname(lXmlhandle),workDate),__func__) 

   /* deal with esbey */
   memset(tmp,0x00,sizeof(tmp));
   ret = DRC_findValue(head,"esbkey",tmp);
   if (ret <0)
      return -1;

   LOG(LM_DEBUG,Fmtmsg("组件[%s] find esbkey ok,esbkey = [%s]",fpub_GetCompname(lXmlhandle),tmp),__func__)

   memset(keytmp,0x00,sizeof(keytmp));
   /** modified by dpl 20180912 增加返回值判断 begin
   DRC_decodeKeyValue(lXmlhandle,tmp,keytmp,&len);  **/
   ret = DRC_decodeKeyValue(lXmlhandle,tmp,keytmp,&len);
   LOG(LM_STD,Fmtmsg("组件[%s] DRC_decodeKeyValue, ret=[%d]",fpub_GetCompname(lXmlhandle),ret),__func__)
   if (ret != 0)
   {
      LOG(LM_STD,Fmtmsg("组件[%s] DRC_decodeKeyValue is error:return value is [%d]",fpub_GetCompname(lXmlhandle),ret),__func__)
      return -1;
   }
   LOG(LM_STD,Fmtmsg("组件[%s] DRC_decodeKeyValue, keytmp=[%s]",fpub_GetCompname(lXmlhandle),keytmp),__func__)
   /** modified by dpl 20180912 end **/
 
   /* 1~24 is macKey  */
   memset(macKey,0x00,sizeof(macKey));
   memcpy(macKey,keytmp,24);
   LOG(LM_DEBUG,Fmtmsg("组件[%s] find macKey ok,macKey =[%s]",fpub_GetCompname(lXmlhandle),macKey),__func__)

   /* 25~48 is pinKey */
   memset(pinKey,0x00,sizeof(pinKey));
   memcpy(pinKey,keytmp+24,24);

   LOG(LM_DEBUG,Fmtmsg("组件[%s] find pinKey ok,pinKey =[%s]",fpub_GetCompname(lXmlhandle),pinKey),__func__) 

   /* 49~64 is checkValue */
   memset(checkValue,0x00,sizeof(checkValue));
   memcpy(checkValue,keytmp+48,16);

   /* LOG(LM_DEBUG,Fmtmsg("组件[%s] find checkValue ok,checkValue =[%s]",fpub_GetCompname(lXmlhandle),checkValue),__func__) */

   /* use mackey to decrypt checkValue to checkDay,compare checkDay with workdate  */
   memset(checkDay,0x00,sizeof(checkDay));
   /** modified by dpl 20180912 增加返回值判断 begin
     DRC_decrypt3des(checkDay,&olen,checkValue,16,macKey);
    **/
   ret = DRC_decrypt3des(checkDay,&olen,checkValue,16,macKey);
   LOG(LM_STD,Fmtmsg("组件[%s] ret=[%d]",fpub_GetCompname(lXmlhandle),ret),__func__)
   if (ret < 0)
   {
      LOG(LM_STD,Fmtmsg("组件[%s] DRC_decrypt3des is error:return value is [%d]",fpub_GetCompname(lXmlhandle),ret),__func__)
      return -1;
   }
   LOG(LM_STD,Fmtmsg("组件[%s] checkDay=[%s]",fpub_GetCompname(lXmlhandle),checkDay),__func__)
   /** modified by dpl 20180912 end **/
   
   /* LOG(LM_DEBUG,Fmtmsg("组件[%s] begin set esbkey,checkDate[%s] workDate[%s] ",fpub_GetCompname(lXmlhandle),checkDay,workDate),__func__) */

   /* 如果服务器端下发密钥存活时长,使用服务器端下发的,否则使用模式的 */
   memset(keyLiveTime,0x00,sizeof(keyLiveTime));
   ret = DRC_findValue(head,"liveTime",keyLiveTime);
   /* 新API服务器下发的是距离当天24点剩余的毫秒数 */
   if (ret < 0)
   {
      liveTime = KEY_LIVE_TIME;
   } else {
      liveTime = atol(keyLiveTime);
      /* LOG(LM_DEBUG,Fmtmsg("组件[%s] begin set liveTime,esbliveTime[%s] ms liveTime[%ld] ms",fpub_GetCompname(lXmlhandle),keyLiveTime,liveTime),__func__) */
   }

   if (memcmp(checkDay,workDate,8)==0)
   {
      LOG(LM_DEBUG,Fmtmsg("组件[%s] check key is ok",fpub_GetCompname(lXmlhandle)),__func__)
      
      /** modified by dpl 20180912 begin **/
      ret = DRC_setEsbKey(lXmlhandle,macKey,pinKey,workDate,liveTime);
      LOG(LM_STD,Fmtmsg("组件[%s] ret=[%d]",fpub_GetCompname(lXmlhandle),ret),__func__)
      if (ret != 0)
      {
          LOG(LM_STD,Fmtmsg("组件[%s] DRC_setEsbKey is error:return value is [%d]",fpub_GetCompname(lXmlhandle),ret),__func__)
          return -1;
      }
      /** modified by dpl 20180912 end **/
   }
   else
   {
      LOG(LM_STD,Fmtmsg("组件[%s] check key is error:checkDate[%s]=workDate[%s]",fpub_GetCompname(lXmlhandle),checkDay,workDate),__func__)
      return -1;
   }
LOG(LM_DEBUG,Fmtmsg("组件[%s],DRC_updateWorkkey end----",fpub_GetCompname(lXmlhandle)),__func__)  
   /** added by dpl 20180912 **/
   return 0; 
}

/*********************************************************
功能描述: 拆解信息头到head和xml中，并解析信息头
开发人员:   chenhh
修改日期:   2012-01-13
*********************************************************/
int DRC_unpackHeadStr(HXMLTREE lXmlhandle,char * rspMsg,int rspLen,char * head,int *headLen,char * xml ,int * xmlLen)
{
   char s_tmp[10];
   char l_tmp[1024];
   int ret;
   int hl;

LOG(LM_DEBUG,Fmtmsg("组件[%s],DRC_unpackHeadStr begin----",fpub_GetCompname(lXmlhandle)),__func__)

   if (rspMsg == NULL||rspLen<4)
   {
      LOG(LM_STD,Fmtmsg("组件[%s] rspMsg、rspLen could not be NULL.",fpub_GetCompname(lXmlhandle)),__func__)
      return -1;
   }

   if (head==NULL||headLen==NULL)
   {
      LOG(LM_STD,Fmtmsg("组件[%s] head、headLen could not be NULL.",fpub_GetCompname(lXmlhandle)),__func__)
      return -1;
   }

   memset(s_tmp,0x00,sizeof(s_tmp));
   memcpy(s_tmp,rspMsg,4);
   hl = atoi(s_tmp);
   *headLen = hl;
   memcpy(head,rspMsg+4,hl);

   *xmlLen = rspLen-4-hl;
   if (*xmlLen>0)
   {
      memcpy(xml,rspMsg+4+hl,*xmlLen);
      xml[*xmlLen]=0x00;
   }

   /*LOG(LM_DEBUG,Fmtmsg("组件[%s] Response head data is[%s]",fpub_GetCompname(lXmlhandle),head),__func__)
   LOG(LM_DEBUG,Fmtmsg("组件[%s] Response XML data is[%s]",fpub_GetCompname(lXmlhandle),xml),__func__)
   */

   memset(s_tmp,0x00,sizeof(s_tmp));
   ret = DRC_findValue(head,"flag",s_tmp);
   if (s_tmp[0]!='S')
   {
      memset(l_tmp,0x00,sizeof(l_tmp));
      ret = DRC_findValue(head,"msg",l_tmp);
      LOG(LM_STD,Fmtmsg("组件[%s] esb response error:flag=[%s],msg=[%s]",fpub_GetCompname(lXmlhandle),s_tmp,l_tmp),__func__)
   }

   /* 判断是否有系统切换*/
   memset(l_tmp,0x00,sizeof(l_tmp));
   ret = DRC_findValue(head,"esbkey",l_tmp);
   if (ret == 0)
   {
      /* add by PengLiyang 2140714 */
      pthread_mutex_lock(&DRC_lock);
      
      /* modified by dpl 20180912 begin 增加返回值判断*/
      ret = DRC_updateWorkkey(lXmlhandle,head);
      LOG(LM_DEBUG,Fmtmsg("组件[%s],DRC_updateWorkkey ret=[%d]",fpub_GetCompname(lXmlhandle),ret),__func__)
      if ( ret != 0 )
      {
      		LOG(LM_DEBUG,Fmtmsg("组件[%s],DRC_updateWorkkey Error",fpub_GetCompname(lXmlhandle)),__func__)
      		pthread_mutex_unlock(&DRC_lock);
      		return -1;
      }
      /* modified by dpl 20180912 end */
      pthread_mutex_unlock(&DRC_lock);
   }

LOG(LM_DEBUG,Fmtmsg("组件[%s],DRC_unpackHeadStr end----",fpub_GetCompname(lXmlhandle)),__func__)
   /* modified by dpl 20180912 return 1改成 return 0
    * return 1;
    */
   return 0;   
}

/*********************************************************
功能描述:       关闭Socket连接
开发人员:       chenhh
修改日期:       2009-12-23
*********************************************************/
void DRC_closeSock(int sock)
{
   if (sock>0)
      close(sock);
   return;
}

/*********************************************************
功能描述:   建立与远程主机的Socket连接
开发人员:   chenhh
修改日期:   2009-12-23
*********************************************************/
static int DRC_TcpSockConnect(HXMLTREE lXmlhandle, int *sock, struct sockaddr_in inaddr, int timeOut)
{
   int rval = -1;
   int elapsedTime = 0;
   void (*OldAction)(int );
   time_t startTime,endTime;

   startTime = time( NULL );
   while( (elapsedTime < timeOut) && ( rval == -1 ) )
   {
      rval = connect( *sock,(struct sockaddr*)&inaddr,sizeof(inaddr) );
      if ( rval == 0 )
         return 0;
      endTime = time( NULL );
      elapsedTime = endTime - startTime;
      usleep(100);
   }
   if ((elapsedTime >= timeOut) && (*sock > 0))
   {
      return -1;
   }
   return rval;
}

/*********************************************************
功能描述:   连接到远程主机
开发人员:   chenhh
修改日期:   2009-12-23
*********************************************************/
int DRC_Conn2Serv(HXMLTREE lXmlhandle,unsigned int addr, int port, int *sock, int timeOut)
{
   struct sockaddr_in serverAddr;
   unsigned long nameLen;
   int rtnVal;
   char* tmp;

   /* LOG(LM_DEBUG,Fmtmsg("组件[%s] Start to conn to server.",fpub_GetCompname(lXmlhandle)),__func__) */

   *sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
   if (*sock < 0)
      return -1;
   serverAddr.sin_family = AF_INET;
   serverAddr.sin_addr.s_addr = addr;
   serverAddr.sin_port = htons(port);
   rtnVal = DRC_TcpSockConnect(lXmlhandle,sock, serverAddr, 5);

   /* LOG(LM_DEBUG,Fmtmsg("组件[%s] end conn to server ret[%d].",fpub_GetCompname(lXmlhandle),rtnVal),__func__) */
   return rtnVal;
}

/*********************************************************
功能描述:   判断连接是否准备好输出
开发人员:   chenhh
修改日期:   2009-12-23
*********************************************************/
int DRC_IsReadyToWrite(int sock, int timeOut )
{
   struct timeval tv;
   struct timeval * ptv;
   fd_set ready;
   int rtnVal;
   int len;

   if ( timeOut != TIME_INFINITE )
   {
      tv.tv_sec = timeOut;
      tv.tv_usec = 0;
      ptv = &tv;
   }else
   {
      ptv = 0;
   }
   FD_ZERO(&ready);
   FD_SET(sock, &ready);
   rtnVal = select(sock + 1, 0,&ready,  0, ptv);
   switch ( rtnVal )
   {
      case 0: return FALSE;  /* time expired */
      case -1:return FALSE; /* error occured */
   }
   /* rtnVal >0 */
   if ( FD_ISSET(sock,&ready) )
   {
      return TRUE;
   } else {
      return FALSE;
   }
}

int DRC_IsReadyToRead(int sock, int timeOut )
{
   struct timeval tv;
   struct timeval * ptv;
   fd_set ready;
   int rtnVal;
   int len;

   if ( timeOut != TIME_INFINITE )
   {
      tv.tv_sec = timeOut;
      tv.tv_usec = 0;
      ptv = &tv;
   }else
   {
      ptv = 0;
   }
   FD_ZERO(&ready);
   FD_SET(sock, &ready);
   rtnVal = select(sock + 1, &ready, 0, 0, ptv);
   switch ( rtnVal )
   {
       case 0: return FALSE;  /* time expired */
       case -1:return FALSE; /* error occured */
   }

   /* rtnVal >0 */
   if ( FD_ISSET(sock,&ready) )
      return TRUE;
   else
      return FALSE;
}

/*********************************************************
功能描述:   写一定的数据到远程主机
开发人员:   chenhh
修改日期:   2009-12-23
*********************************************************/
int DRC_WritePacket(HXMLTREE lXmlhandle,int sock, const char *dataBuff, int length, int timeOut)
{
   int rtnVal,counter,wantLen;
   int elapsedTime = 0;
   time_t startTime,endTime;
   startTime = time( NULL );

   /* LOG(LM_STD,Fmtmsg("组件[%s] Start to write request data.sock=[%d] timeOut=[%d]",fpub_GetCompname(lXmlhandle),sock,timeOut),__func__) */

   counter = 0;
   wantLen = length;
   while ( counter != length  && elapsedTime <= timeOut)
   {
      if ( DRC_IsReadyToWrite(sock,timeOut ) == TRUE )
      {
         rtnVal = write(sock,dataBuff + counter,wantLen);
         if ( rtnVal < 0 )
         {
            return -1;
         }
         counter += rtnVal  ;
         wantLen = length - counter;
         endTime = time( NULL );
         elapsedTime = endTime - startTime;
 
      }
      else
      {
         LOG(LM_STD,Fmtmsg("组件[%s] 发送超时.",fpub_GetCompname(lXmlhandle)),__func__)
         return -1;
      }
   }
   /* LOG(LM_STD,Fmtmsg("组件[%s] End for writing.",fpub_GetCompname(lXmlhandle)),__func__) */
   return counter;
}

/*********************************************************
功能描述:   发送数据到远程主机
开发人员:   chenhh
修改日期:   2009-12-23
*********************************************************/
int DRC_Send2Serv(HXMLTREE lXmlhandle,int sock, const char *data, int len, int timeout)
{
   int rtnVal;

   rtnVal = DRC_WritePacket(lXmlhandle,sock,data,len,timeout);
   switch ( rtnVal )
   {
      case 0: /* connection disconnected */
         return -1;
      case -1: /* can not send */
         return -2;
   }
   return rtnVal;
}

/*********************************************************
功能描述:   根据从远处主机读取一定的信息
开发人员:   chenhh
修改日期:   2009-12-23
*********************************************************/
int DRC_ReadPacket(HXMLTREE lXmlhandle,int sock, char *dataBuff, long* olen, int timeOut)
{
   int counter,wantLen,elapsedTime,rtnVal;
   time_t startTime,endTime;

   /* LOG(LM_STD,Fmtmsg("组件[%s] Start to read response data.",fpub_GetCompname(lXmlhandle)),__func__) */
   elapsedTime = 0;
   startTime = time( NULL );
   counter = 0;
   wantLen = *olen;
 
   if (dataBuff == NULL)
   {
      return -3;
   }
 
   /* 由调用方在传递参数前进行memset */
   while (wantLen>0 && elapsedTime <= timeOut)
   {
      if (DRC_IsReadyToRead(sock,timeOut) == TRUE)
      {
         rtnVal = read(sock,dataBuff + counter,wantLen);
         if (rtnVal <= 0 )
            break;

         wantLen -= rtnVal;
         counter += rtnVal;
         endTime = time( NULL );
         elapsedTime = endTime - startTime;
      }else{
         return -1;
      }
   }
   /* LOG(LM_STD,Fmtmsg("组件[%s] End for reading. counter=[%d],wantLen=[%d]",fpub_GetCompname(lXmlhandle),counter,wantLen),__func__) */
   return counter;
}

/*********************************************************
功能描述:   与远程主机进行通信
开发人员:   chenhh
开发日期:   2009-12-23

修改记录:   添加交易超时时间参数t_out
修改人  :   PengLiyang
修改日期:   20150122
*********************************************************/
int DRC_docomm(HXMLTREE lXmlhandle,char * head, char * input, char* output, long* len,const int t_out)
{
   int addr, port, sock, rtnVal, timeout;
   char * iData = NULL;
   int ilen;
   char oHead[9];
   char * oData = NULL;
   long olen;
   time_t tTimeStart, tTimeNow;
   char ip_value[200], port_value[5], tm_value[10], rs_value[5],stmp[10];
   int resendtimes, i, ret;
   struct hostent *host;

   tTimeStart = time(NULL);   
   /* 获取IP */
   DRC_GetConfig("IP", ip_value);
   if (strlen(ip_value) == 0) 
   {
      LOG(LM_STD,Fmtmsg("组件[%s] not set remote ip",fpub_GetCompname(lXmlhandle)),__func__)
      return -1;
   }
   addr = inet_addr(ip_value);

   if (addr<0)
   {
      host = gethostbyname(ip_value); 
      if (host == NULL) 
      {
         LOG(LM_STD,Fmtmsg("组件[%s] error in gethostbyname %s",fpub_GetCompname(lXmlhandle),ip_value),__func__)
         LOG(LM_STD,Fmtmsg("组件[%s] I cant't get the server ip address on [linux OS],pls check the ip config!",fpub_GetCompname(lXmlhandle)),__func__)
      }
      else 
      {
         addr=inet_addr(inet_ntoa(*(struct in_addr*)host->h_addr_list[0]));
      }
   }

   /* 获取端口 */
   DRC_GetConfig("PORT", port_value);
   if (strlen(port_value) == 0) 
   {
      LOG(LM_STD,Fmtmsg("组件[%s] not set port",fpub_GetCompname(lXmlhandle)),__func__)
      return -1;
   }
   port = atoi(port_value);

   /* 重发次数 */
   DRC_GetConfig("RESENDTIMES", rs_value);
   if (strlen(rs_value) == 0) 
   {
      resendtimes = 1;
   }
   resendtimes = atoi(rs_value);

   /* 超时时间 */
   DRC_GetConfig("TIMEOUT", tm_value);
   if (strlen(tm_value) == 0)
   {
      LOG(LM_STD,Fmtmsg("组件[%s] not set timeout",fpub_GetCompname(lXmlhandle)),__func__)
      return -1;
   }
   /* 支持指定超时时间 add by PengLiyang 20150122 */
   if (t_out > 0)
   {
      timeout = t_out;
   } else {
      timeout = atoi(tm_value);
   }

   /* 日志 */
   /* LOG(LM_DEBUG,Fmtmsg("组件[%s] 连接到远程服务器[%s:%s]",fpub_GetCompname(lXmlhandle),ip_value,port_value),__func__) */

   /* 判断获取远程IP是否成功 */
   if (addr == 0) 
   {
      LOG(LM_STD,Fmtmsg("组件[%s] get remote ip failed!",fpub_GetCompname(lXmlhandle)),__func__)
      return -1;
   }

   /* 建立与远程机器对应端口的连接 */
   for (i = 0; i < resendtimes; i++) /* resend times */
   {
      tTimeNow = time(NULL);
      tTimeNow = (tTimeNow > tTimeStart) ? tTimeNow : tTimeStart;
      timeout = timeout - (tTimeNow - tTimeStart);
      rtnVal = DRC_Conn2Serv(lXmlhandle,addr, port, &sock, timeout);
      if ( rtnVal == 0 )
      {
         break;
      }
      else
         DRC_closeSock(sock);
   }

   /* 判断建立连接是否成功,小于0不成功,直接返回 */
   if (rtnVal < 0) 
   {
      LOG(LM_STD,Fmtmsg("组件[%s] make connect failed![%d][%d]",fpub_GetCompname(lXmlhandle),addr,port),__func__)
      return -1;
   }

   /* 建立连接成功， */
   if ( rtnVal == 0 ) 
   {
      /* 计算超时时间 */
      tTimeNow = time(NULL);
      tTimeNow = (tTimeNow > tTimeStart) ? tTimeNow : tTimeStart;
      timeout = timeout - (tTimeNow - tTimeStart);

      /* 数组改成临时堆 20140714 by PengLiyang */
      /* 组合请求数据,8位的包长+头信息+XML报文 */
      ilen = strlen(input)+strlen(head);
      iData =  (char * ) malloc( sizeof(char) * MAX_SOCK_BUF_SIZE);
      if ( NULL == iData)
      {
         DRC_closeSock(sock);
         return -1;
      }
      /* memset(iData, 0x00, sizeof(char) * MAX_SOCK_BUF_SIZE); */
      sprintf(iData,"%08d%s%s",ilen,head,input);
      iData[ilen+8]='\0';

      /* 发送请求的报文，8位10进制的包长加报文的内容 */
      rtnVal = DRC_Send2Serv(lXmlhandle,sock, (char*)iData, ilen+8, timeout);
      free(iData);
      iData = NULL;

      if (rtnVal <= 0) {
         if (sock >= 0)
            DRC_closeSock(sock);
              
         LOG(LM_STD,Fmtmsg("组件[%s] send packet failed!",fpub_GetCompname(lXmlhandle)),__func__)
         return -1;
      }
 
      /* 计算超时时间 */
      tTimeNow = time(NULL);
      tTimeNow = (tTimeNow > tTimeStart) ? tTimeNow : tTimeStart;
      timeout = timeout - (tTimeNow - tTimeStart);

      /* 读取相应包长度 */
      olen =8;
      memset(oHead,0x00,sizeof(oHead));
      rtnVal = DRC_ReadPacket(lXmlhandle,sock, (char*)oHead, &olen, timeout);
      if (rtnVal > 0)
      {
         olen = atof(oHead);
      }
      else
      {
         DRC_closeSock(sock);     
         return -2;
      }

      /* 读取请求的报文体 */
      /* 数组改成临时堆 20140714 by PengLiyang */
      oData =  (char * ) malloc( sizeof(char) * MAX_SOCK_BUF_SIZE);
      if ( NULL == oData)
      {
         DRC_closeSock(sock);
         return -2;
      }
      /* memset(oData, 0x00, sizeof(char) * MAX_SOCK_BUF_SIZE); */
      rtnVal = DRC_ReadPacket(lXmlhandle,sock, (char*)oData, &olen, timeout);
 
      if (rtnVal >0)
      {
         memcpy(output, oData, olen);
         *len = olen;
      }
      free(oData);
      oData = NULL;
   }
   DRC_closeSock( sock );
   return 1;
}

/*********************************************************
功能描述:   与远程主机进行通信
开发人员:   chenhh
开发日期:   2009-12-23

修改记录:   添加交易超时时间参数t_out
修改人  :   PengLiyang
修改日期:   20150122
*********************************************************/
int DRC_docomm_NLGXP(HXMLTREE lXmlhandle,char * head, char * input, char* output, long* len,const int t_out)
{
   int addr, port, sock, rtnVal, timeout;
   char * iData = NULL;
   int ilen;
   char oHead[9];
   char * oData = NULL;
   long olen;
   time_t tTimeStart, tTimeNow;
   char ip_value[200], port_value[5], tm_value[10], rs_value[5],stmp[10];
   int resendtimes, i, ret;
   struct hostent *host;

   tTimeStart = time(NULL);   
   /* 获取IP */
   DRC_GetConfig("COMMIP", ip_value);
   if (strlen(ip_value) == 0) 
   {
      LOG(LM_STD,Fmtmsg("组件[%s] not set remote ip",fpub_GetCompname(lXmlhandle)),__func__)
      return -1;
   }
   addr = inet_addr(ip_value);

   if (addr<0)
   {
      host = gethostbyname(ip_value); 
      if (host == NULL) 
      {
         LOG(LM_STD,Fmtmsg("组件[%s] error in gethostbyname %s",fpub_GetCompname(lXmlhandle),ip_value),__func__)
         LOG(LM_STD,Fmtmsg("组件[%s] I cant't get the server ip address on [linux OS],pls check the ip config!",fpub_GetCompname(lXmlhandle)),__func__)
      }
      else 
      {
         addr=inet_addr(inet_ntoa(*(struct in_addr*)host->h_addr_list[0]));
      }
   }

   /* 获取端口 */
   DRC_GetConfig("COMMPORT", port_value);
   if (strlen(port_value) == 0) 
   {
      LOG(LM_STD,Fmtmsg("组件[%s] not set port",fpub_GetCompname(lXmlhandle)),__func__)
      return -1;
   }
   port = atoi(port_value);

   /* 重发次数 */
   DRC_GetConfig("RESENDTIMES", rs_value);
   if (strlen(rs_value) == 0) 
   {
      resendtimes = 1;
   }
   resendtimes = atoi(rs_value);

   /* 超时时间 */
   DRC_GetConfig("TIMEOUT", tm_value);
   if (strlen(tm_value) == 0)
   {
      LOG(LM_STD,Fmtmsg("组件[%s] not set timeout",fpub_GetCompname(lXmlhandle)),__func__)
      return -1;
   }
   /* 支持指定超时时间 add by PengLiyang 20150122 */
   if (t_out > 0)
   {
      timeout = t_out;
   } else {
      timeout = atoi(tm_value);
   }

   /* 日志 */
   /* LOG(LM_DEBUG,Fmtmsg("组件[%s] 连接到远程服务器[%s:%s]",fpub_GetCompname(lXmlhandle),ip_value,port_value),__func__) */

   /* 判断获取远程IP是否成功 */
   if (addr == 0) 
   {
      LOG(LM_STD,Fmtmsg("组件[%s] get remote ip failed!",fpub_GetCompname(lXmlhandle)),__func__)
      return -1;
   }

   /* 建立与远程机器对应端口的连接 */
   for (i = 0; i < resendtimes; i++) /* resend times */
   {
      tTimeNow = time(NULL);
      tTimeNow = (tTimeNow > tTimeStart) ? tTimeNow : tTimeStart;
      timeout = timeout - (tTimeNow - tTimeStart);
      rtnVal = DRC_Conn2Serv(lXmlhandle,addr, port, &sock, timeout);
      if ( rtnVal == 0 )
      {
         break;
      }
      else
         DRC_closeSock(sock);
   }

   /* 判断建立连接是否成功,小于0不成功,直接返回 */
   if (rtnVal < 0) 
   {
      LOG(LM_STD,Fmtmsg("组件[%s] make connect failed![%d][%d]",fpub_GetCompname(lXmlhandle),addr,port),__func__)
      return -1;
   }

   /* 建立连接成功， */
   if ( rtnVal == 0 ) 
   {
      /* 计算超时时间 */
      tTimeNow = time(NULL);
      tTimeNow = (tTimeNow > tTimeStart) ? tTimeNow : tTimeStart;
      timeout = timeout - (tTimeNow - tTimeStart);

      /* 数组改成临时堆 20140714 by PengLiyang */
      /* 组合请求数据,8位的包长+头信息+XML报文 */
      ilen = strlen(input)+strlen(head);
      iData =  (char * ) malloc( sizeof(char) * MAX_SOCK_BUF_SIZE);
      if ( NULL == iData)
      {
         DRC_closeSock(sock);
         return -1;
      }
      /* memset(iData, 0x00, sizeof(char) * MAX_SOCK_BUF_SIZE); */
      sprintf(iData,"%08d%s%s",ilen,head,input);
      iData[ilen+8]='\0';

      /* 发送请求的报文，8位10进制的包长加报文的内容 */
      rtnVal = DRC_Send2Serv(lXmlhandle,sock, (char*)iData, ilen+8, timeout);
      free(iData);
      iData = NULL;

      if (rtnVal <= 0) {
         if (sock >= 0)
            DRC_closeSock(sock);
              
         LOG(LM_STD,Fmtmsg("组件[%s] send packet failed!",fpub_GetCompname(lXmlhandle)),__func__)
         return -1;
      }
 
      /* 计算超时时间 */
      tTimeNow = time(NULL);
      tTimeNow = (tTimeNow > tTimeStart) ? tTimeNow : tTimeStart;
      timeout = timeout - (tTimeNow - tTimeStart);

      /* 读取相应包长度 */
      olen =8;
      memset(oHead,0x00,sizeof(oHead));
      rtnVal = DRC_ReadPacket(lXmlhandle,sock, (char*)oHead, &olen, timeout);
      if (rtnVal > 0)
      {
         olen = atof(oHead);
      }
      else
      {
         DRC_closeSock(sock);     
         return -2;
      }

      /* 读取请求的报文体 */
      /* 数组改成临时堆 20140714 by PengLiyang */
      oData =  (char * ) malloc( sizeof(char) * MAX_SOCK_BUF_SIZE);
      if ( NULL == oData)
      {
         DRC_closeSock(sock);
         return -2;
      }
      /* memset(oData, 0x00, sizeof(char) * MAX_SOCK_BUF_SIZE); */
      rtnVal = DRC_ReadPacket(lXmlhandle,sock, (char*)oData, &olen, timeout);
 
      if (rtnVal >0)
      {
         memcpy(output, oData, olen);
         *len = olen;
      }
      free(oData);
      oData = NULL;
   }
   DRC_closeSock( sock );
   return 1;
}

/*********************************************************
功能描述:   同步工作密钥
开发人员:   chenhh
修改日期:   2012-01-17
*********************************************************/
int DRC_synWorkKey(HXMLTREE lXmlhandle)
{
   int ret;
   int head_len;
   char head [256];
   char tmp    [2048];
   char tmp1 [2048];
   char tmp2 [2048];
   long len1;
   int len2,len3;
   time_t t;
   long lt;
   int t_out = SYN_KEY_TIME_OUT;
LOG(LM_DEBUG,Fmtmsg("组件[%s],DRC_synWorkKey begin----",fpub_GetCompname(lXmlhandle)),__func__)
   /* 判断是否已经同步密钥 */
   if (DRC_key!=NULL) 
   {
      if (IS32BITPROGRAM)
      {
         /* 32位程序,用秒计算 */
         time(&t);
         lt=t;
      } else {
         /* 64位程序,用毫秒计算 */
         lt= DRC_getMillitmSystemTime();
      }
      if (lt<DRC_key->time)
      {
         if (IS32BITPROGRAM)
         {
            /* 32位程序,用秒计算 */
            LOG(LM_DEBUG,Fmtmsg("组件[%s] Esb key live time is [%ld]s",fpub_GetCompname(lXmlhandle),DRC_key->time-lt),__func__)
         } else {
            /* 64位程序,用毫秒计算 */
            LOG(LM_DEBUG,Fmtmsg("组件[%s] Esb key live time is [%ld]s",fpub_GetCompname(lXmlhandle),DRC_key->time-lt),__func__)
         }
         return 1;
      }
      if (IS32BITPROGRAM)
      {
         /* 32位程序,用秒计算 */
         LOG(LM_DEBUG,Fmtmsg("组件[%s] Esb key is timeout:currtime=%lds,maxtime=%lds",fpub_GetCompname(lXmlhandle),lt,DRC_key->time),__func__)
      } else {
         /* 64位程序,用毫秒计算 */
         LOG(LM_DEBUG,Fmtmsg("组件[%s] Esb key is timeout:currtime=%lds,maxtime=%lds",fpub_GetCompname(lXmlhandle),lt,DRC_key->time),__func__)
      }
   }
   else
   {
      LOG(LM_DEBUG,Fmtmsg("组件[%s] Esb key is NULL",fpub_GetCompname(lXmlhandle)),__func__)
   }

   /* 获取请求的头信息 */
   memset(head,0x00,sizeof(head));

   /* 组成系统头 */
   ret = DRC_packHeadStr(lXmlhandle,head,head,&head_len,1);
   if (ret<0)
   {
      LOG(LM_STD,Fmtmsg("组件[%s] Get Head Str is ERROR",fpub_GetCompname(lXmlhandle)),__func__)
      return -1;
   }

   memset(tmp,0x00,sizeof(tmp));
   /**LOG(LM_DEBUG,Fmtmsg("组件[%s] synWorkKey request->%s",fpub_GetCompname(lXmlhandle),head),__func__)**/
   ret = DRC_docomm(lXmlhandle,head,"test",tmp, &len1,t_out);
   /**LOG(LM_STD,Fmtmsg("组件[%s] synWorkKey response->%s",fpub_GetCompname(lXmlhandle),tmp),__func__)**/
   if (ret==1)
   {
      memset(tmp1,0x00,sizeof(tmp1));
      memset(tmp2,0x00,sizeof(tmp2));
      /*modified by dpl 20180913 添加返回值判断
       *DRC_unpackHeadStr(lXmlhandle,tmp,len1,tmp1,&len2,tmp2,&len3);
       */
      ret = DRC_unpackHeadStr(lXmlhandle,tmp,len1,tmp1,&len2,tmp2,&len3);
      LOG(LM_STD,Fmtmsg("组件[%s] ret=[%d]",fpub_GetCompname(lXmlhandle),ret),__func__)
      if (ret != 0)
      {
         LOG(LM_STD,Fmtmsg("组件[%s] DRC_unpackHeadStr is error:return value is [%d]",fpub_GetCompname(lXmlhandle),ret),__func__)
         return -1;
      }      
   }
   else
   {
      LOG(LM_STD,Fmtmsg("组件[%s] could not get the workkey",fpub_GetCompname(lXmlhandle)),__func__)
      return ret;
   }
LOG(LM_DEBUG,Fmtmsg("组件[%s],DRC_synWorkKey end----",fpub_GetCompname(lXmlhandle)),__func__)
   return 1;
}

/************************************************************************
功能：      同步工作密钥(服务端)
同步过程：   当做服务端时，ESB送过来的日期与本
         地保存日期不一致或存活期已过则重新同步密钥
输入：      recvHead - ESB请求API时报文头内容,为空时则workDay不作为判断条件
         flag - 是否强制同步密钥标志，0:不强制，使用存活时间和recvHead中的workDay进行判断；1：强制同步
输出：      无
返回：      等于1 - 正常(不需同步或同步成功);  不等于1 - 异常
注意：      
开发人员:   PengLiyang
修改日期:   2013-07-08
************************************************************************/
int DRC_synWorkKey2(HXMLTREE lXmlhandle,const char *recvHead, const int flag)
{
   int ret;
   int head_len;
   char head [256];
   char tmp    [2048];
   char tmp1 [2048];
   char tmp2 [2048];
   long len1;
   int len2,len3;
   time_t t;
   long lt;
   char tmpWorkDate[9];
   int sameWorkDay = 1;
   int t_out = SYN_KEY_TIME_OUT;
LOG(LM_DEBUG,Fmtmsg("组件[%s],DRC_synWorkKey2 begin----",fpub_GetCompname(lXmlhandle)),__func__)
   /* 判断是否已经同步密钥,key不空且flag值不是强制同步(1)才进入是否要同步处理流程 */
   if ((DRC_key!=NULL) && (0 == flag))
   {
      /* 从接收的请求报文头中找到工作日期 */
      memset(tmpWorkDate,0x00,sizeof(tmpWorkDate));
      if (NULL != recvHead){
         ret = DRC_findValue(recvHead,"workDay",tmpWorkDate);
         if (ret <0)
            return -1;
      }
      LOG(LM_DEBUG,Fmtmsg("组件[%s] find recv workdate,workdate = [%s]",fpub_GetCompname(lXmlhandle),tmpWorkDate),__func__)

      if (IS32BITPROGRAM)
      {
         /* 32位程序,用秒计算 */
         time(&t);
         lt=t;
      } else {
         /* 64位程序,用毫秒计算 */
         lt= DRC_getMillitmSystemTime();
      }

      if ((NULL != tmpWorkDate) && (NULL != DRC_key->workDate))
      {
         sameWorkDay = memcmp(tmpWorkDate,DRC_key->workDate,8*sizeof(char));
      }
      /* 接收的工作日期与本地密钥中的工作日期相同，且在存活时间内，则不同步 */
LOG(LM_DEBUG,Fmtmsg("组件[%s] Esb key live time is lt [%ld] , DRC_key->time [%ld] ms,Esb workDate is[%s],key->workDate is [%s] sameWordDay [%d]",fpub_GetCompname(lXmlhandle),lt,DRC_key->time,tmpWorkDate,DRC_key->workDate,sameWorkDay),__func__);
      if ((0 == sameWorkDay) && (lt<DRC_key->time))
      {
         if (IS32BITPROGRAM)
         {
            /* 32位程序,用秒计算 */
            LOG(LM_DEBUG,Fmtmsg("组件[%s] Esb key live time is [%ld] s,Esb workDate is[%s],key->workDate is [%s]",fpub_GetCompname(lXmlhandle),DRC_key->time-lt,tmpWorkDate,DRC_key->workDate),__func__);
         } else {
            /* 64位程序,用毫秒计算 */
            LOG(LM_DEBUG,Fmtmsg("组件[%s] Esb key live time is [%ld] ms,Esb workDate is[%s],key->workDate is [%s]",fpub_GetCompname(lXmlhandle),DRC_key->time-lt,tmpWorkDate,DRC_key->workDate),__func__);
         }
         return 1;
      }
      if (IS32BITPROGRAM)
      {
         /* 32位程序,用秒计算 */
         LOG(LM_DEBUG,Fmtmsg("组件[%s] Esb key is timeout:currtime=%ld s,key maxtime=%ld s,Esb workDate is[%s],key->workDate is [%s]",fpub_GetCompname(lXmlhandle),lt,DRC_key->time,tmpWorkDate,DRC_key->workDate),__func__);
      } else {
         LOG(LM_DEBUG,Fmtmsg("组件[%s] Esb key is timeout:currtime=%ld ms,key maxtime=%ld ms,Esb workDate is[%s],key->workDate is [%s]",fpub_GetCompname(lXmlhandle),lt,DRC_key->time,tmpWorkDate,DRC_key->workDate),__func__);
      }
   }
   else
   {
      if (DRC_key == NULL){
         LOG(LM_DEBUG,Fmtmsg("组件[%s] Esb key is NULL.",fpub_GetCompname(lXmlhandle)),__func__);
      }else{
         LOG(LM_DEBUG,Fmtmsg("组件[%s] Forced synWorkKey excuted.",fpub_GetCompname(lXmlhandle)),__func__);
      }
   }
      
   /* 获取请求的头信息 */
   memset(head,0x00,sizeof(head));
      
   /* 组成系统头 */
   ret = DRC_packHeadStr(lXmlhandle,head,head,&head_len,1);
   if (ret<0)
   {
      LOG(LM_STD,Fmtmsg("组件[%s] Get Head Str is ERROR.",fpub_GetCompname(lXmlhandle)),__func__);
      return -1;
   }

   memset(tmp,0x00,sizeof(tmp));
   ret = DRC_docomm(lXmlhandle,head,"test",tmp, &len1,t_out);
   if (ret==1)
   {
      memset(tmp1,0x00,sizeof(tmp1));
      memset(tmp2,0x00,sizeof(tmp2));
      /*modified by dpl 20180913 添加返回值判断
       *DRC_unpackHeadStr(lXmlhandle,tmp,len1,tmp1,&len2,tmp2,&len3);
       */
      ret = DRC_unpackHeadStr(lXmlhandle,tmp,len1,tmp1,&len2,tmp2,&len3);
      LOG(LM_STD,Fmtmsg("组件[%s] ret=[%d]",fpub_GetCompname(lXmlhandle),ret),__func__)
      if (ret != 0)
      {
         LOG(LM_STD,Fmtmsg("组件[%s] DRC_unpackHeadStr is error:return value is [%d]",fpub_GetCompname(lXmlhandle),ret),__func__)
         return -1;
      }  
   }
   else
   {
      LOG(LM_STD,Fmtmsg("组件[%s] could not get the workkey",fpub_GetCompname(lXmlhandle)),__func__);
      return ret;
   }
LOG(LM_DEBUG,Fmtmsg("组件[%s],DRC_synWorkKey2 end----",fpub_GetCompname(lXmlhandle)),__func__)
   return 1;
}

/*********************************************************
功能描述:   对比返回报文对比串
开发人员:   chenjie
修改日期:   2012-03-02
*********************************************************/
int DRC_checkResponseSeries(HXMLTREE lXmlhandle,char * head,char * output)
{
   char series[100];
   char code[100];
   int ret;
   long code_len;
 
   /* LOG(LM_DEBUG,Fmtmsg("组件[%s] begin check series",fpub_GetCompname(lXmlhandle)),__func__) */

   memset(series,0x00,sizeof(series));
   ret = DRC_findValue(head,"series",series);

   if (ret == 0)
   { 
      /* 生成报文的验证码*/
      memset(code,0x00,sizeof(code)); 
      ret = DRC_encodeXmlPack(lXmlhandle,output,code, &code_len);

      LOG(LM_STD,Fmtmsg("组件[%s] series=[%s]",fpub_GetCompname(lXmlhandle),series),__func__)
      LOG(LM_STD,Fmtmsg("组件[%s] code=[%s] len=[%d]",fpub_GetCompname(lXmlhandle),code,code_len),__func__)
      LOG(LM_STD,Fmtmsg("组件[%s] output=[%s]",fpub_GetCompname(lXmlhandle),output),__func__)
      if(memcmp(series,code,code_len)==0)
      {
         /* LOG(LM_STD,Fmtmsg("组件[%s] check response series is ok",fpub_GetCompname(lXmlhandle)),__func__) */
         return 1;
      } 

      LOG(LM_STD,Fmtmsg("组件[%s] 对比返回报文对比串不一致,接收返回报文不完整",fpub_GetCompname(lXmlhandle)),__func__)
      return -1;
   } 

   return 1;
}

int DRC_convert(char *src, char *dest, char *input, size_t ilen, char *output, size_t *olen)
{
   char **pin=&input;
   char **pout=&output;

   iconv_t cd=iconv_open(dest,src);
   if (cd == (iconv_t)-1)
   {
      return -1;
   }
   if (iconv(cd,pin,&ilen,pout,olen))
   {
      iconv_close(cd);
      return -1;
   }
   iconv_close(cd);
   return 0;
}

/************************************************************************
动态组件函数定义
组件函数名称:DRC_COMTOESB
组件名称:DRC_COMTOESB
组件功能:
组件参数:
 序号 参数类型  参数名称         资源类别     缺省值  可空  参数说明
  1   1-输入    通讯缓冲区     401-XML结点    /commbuf   N    通讯缓冲区结点      

组件结果状态:
  结果状态码         结果说明
  缺省

日志信息:
  日志级别           日志宏

响应信息:
  内部响应码         内部响应信息

主要操作元素:
  元素路径          操作

主要操作库表:
  表名              操作

使用限制:

项 目 组: 
程 序 员:
发布日期:
修改日期:2008-12-1 16:10:24[Gen]
参数使用示例:
************************************************************************/
IRESULT DRC_COMTOESB(HXMLTREE lXmlhandle)
{
   char scommbufnode[256];
   char head[2048],workDate[9];
   int  iParas,ilen_send, iret, ilen_recv,hl;
   char *scont_recv, *scont_send=NULL, *oData=NULL, *indata, *outdata;
   long olen;
   int iTimeout=0;

   fpub_InitSoComp(lXmlhandle);

#ifdef DEBUG
   LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),__func__)
#endif

   memset(scommbufnode,0x00,sizeof(scommbufnode));

   COMP_PARACOUNTCHKMIN(1)
   COMP_GETPARSEPARAS(1,scommbufnode,"通讯缓冲区")

   /*add by llh 20180928 增加超时时间控制*/
   memset(scommbufnode,0x00,sizeof(scommbufnode));
   COMP_SOFTGETXML("/agent/req/timeout", scommbufnode);
   trim(scommbufnode);
   iTimeout=atoi(scommbufnode);
   memset(scommbufnode,0x00,sizeof(scommbufnode));
   /*add by llh 20180928 增加超时时间控制*/
 
   /*请求包长度,动态分配*/
   ilen_send=xml_GetElementLen(lXmlhandle, scommbufnode);
   if (ilen_send <= 0)
   {
      LOG(LM_STD,Fmtmsg("  -->通讯失败,通讯缓冲区数据长度不正确[%d],msg[%s]", ilen_send,GETXMLERR),"ERROR");
      fpub_SetMsg(lXmlhandle,MID_YW_ERROR,Fmtmsg("与ESB通讯失败"));
      fpub_SetCompStatus(lXmlhandle,-1);      /*异常时,组件返回-1*/
      return -1;
   }      
   ilen_send = ilen_send/2;
   scont_send = malloc(ilen_send+1);
   if (scont_send == NULL)
   {
      LOG(LM_STD, Fmtmsg("malloc分配内存失败,errmsg=[%s]", strerror(errno)), __func__);     
      fpub_SetMsg(lXmlhandle,MID_YW_ERROR,Fmtmsg("申请内存失败，与ESB通讯失败"));
      fpub_SetCompStatus(lXmlhandle,-1);      /*异常时,组件返回-1*/
      free(scont_send);
      return -1;
   }
   iret=xml_GetBinElement(lXmlhandle, scommbufnode, scont_send, ilen_send+1); 
   if (iret < 0)
   {
      LOG(LM_STD,Fmtmsg("  -->通讯失败,获取通讯缓冲区数据失败,msg[%s]",GETXMLERR),"ERROR");
      fpub_SetMsg(lXmlhandle,MID_YW_ERROR,Fmtmsg("获取发送数据失败，与ESB通讯失败"));
      fpub_SetCompStatus(lXmlhandle,-1);      /*异常时,组件返回-1*/
      free(scont_send);
      return -1;
   }
#ifdef DEBUG
   LOG(LM_STD, Fmtmsg("发送GXP请求报文体:iPackageLen[%d],[%s]", ilen_send,scont_send), "INFO");
#endif

   /*** 以下为ESB的函数 */
/****
   if (DRC_key == NULL)
   {
      if ((DRC_key = ( struct DRC_stKey * ) malloc( sizeof( struct DRC_stKey ) )) == NULL)
      {
         LOG(LM_STD,Fmtmsg("申请内存失败"),"ERROR");
         fpub_SetMsg(lXmlhandle,MID_YW_ERROR,Fmtmsg("申请内存失败"));
         fpub_SetCompStatus(lXmlhandle,-1); 
         free(scont_send);
         return -1;
      }
      memset(DRC_key,0x00,sizeof( struct DRC_stKey ));
   }
***/

   /* 0 把GAPS的GB18030转换为UTF-8 */
   indata =  (char * ) malloc( sizeof(char) * MAX_SOCK_BUF_SIZE);
   if (indata == NULL)
   {
      free(scont_send);
      LOG(LM_STD,Fmtmsg("申请内存失败"),"ERROR");
      fpub_SetMsg(lXmlhandle,MID_YW_ERROR,Fmtmsg("申请内存失败，与ESB通讯失败"));
      fpub_SetCompStatus(lXmlhandle,-1);      /*异常时,组件返回-1*/
      return -1;
   }
   memset(indata, 0x00, sizeof(char) * MAX_SOCK_BUF_SIZE) ;

   LOG(LM_DEBUG, Fmtmsg("发送ESB请求报文体: [%s]", scont_send), "INFO");
   ilen_recv=MAX_SOCK_BUF_SIZE;
   if (DRC_convert("GB18030","UTF-8", scont_send, ilen_send, indata, &ilen_recv) !=0)
   {
      LOG(LM_STD,Fmtmsg("GB18030转UTF-8失败."),"ERROR");
      fpub_SetMsg(lXmlhandle,MID_YW_ERROR,Fmtmsg("GB18030转UTF-8失败，与ESB通讯失败"));
      fpub_SetCompStatus(lXmlhandle,-1);      /*异常时,组件返回-1*/
      free(scont_send);
      free(indata);
      return -1;
   }
   free(scont_send);
   ilen_send=MAX_SOCK_BUF_SIZE-ilen_recv;

   /* 1 初始化系统*/
   iret = DRC_InitConfig();
   if (iret !=0)
   {
      LOG(LM_STD,Fmtmsg("  -->获取ESB配置信息失败"),"ERROR");
      fpub_SetMsg(lXmlhandle,MID_YW_ERROR,Fmtmsg("获取ESB配置信息失败"));
      fpub_SetCompStatus(lXmlhandle,-1);      /*异常时,组件返回-1*/
      free(indata);
      return -1;
   }

   /* 2 同步密钥 */
   iret = DRC_synWorkKey(lXmlhandle);
   LOG(LM_STD, Fmtmsg("DRC_synWorkKey iret=[%d]", iret), "INFO")
   if (iret<0)
   {
      LOG(LM_STD,Fmtmsg("  -->同步ESB密钥失败"),"ERROR");
      fpub_SetMsg(lXmlhandle,MID_YW_ERROR,Fmtmsg("同步ESB密钥失败"));
      fpub_SetCompStatus(lXmlhandle,-1);      /*异常时,组件返回-1*/
      free(indata);
      return -1;
   }

   /* 获取系统头 */
   memset(head,0x00,sizeof(head));
   iret = DRC_packHeadStr(lXmlhandle,indata,head,&hl,2);
   if (iret<0)
   {
      LOG(LM_STD,Fmtmsg("Get Head Str is ERROR."),"ERROR");
      fpub_SetMsg(lXmlhandle,MID_YW_ERROR,Fmtmsg("组报文头失败"));
      fpub_SetCompStatus(lXmlhandle,-1);      /*异常时,组件返回-1*/
      free(indata);
      return -1;
   }
   /*for DEBUG*/
   LOG(LM_STD, Fmtmsg("request services head is [%s]", head), "INFO");
 
   /* 请求交易*/
   oData =  (char * ) malloc( sizeof(char) * MAX_SOCK_BUF_SIZE);
   if (oData == NULL)
   {
      free(indata);
      LOG(LM_STD,Fmtmsg("申请内存失败"),"ERROR");
      fpub_SetMsg(lXmlhandle,MID_YW_ERROR,Fmtmsg("申请内存失败，与ESB通讯失败"));
      fpub_SetCompStatus(lXmlhandle,-1);      /*异常时,组件返回-1*/
      return -1;
   }
   /* memset(oData, 0x00, sizeof(char) * MAX_SOCK_BUF_SIZE);*/
   /*iret = DRC_docomm_NLGXP(lXmlhandle,head,indata,oData, &olen,0);  去掉默认超时时间0,增加iTimeout的控制*/
   iret = DRC_docomm_NLGXP(lXmlhandle,head,indata,oData, &olen,iTimeout);
   if (iret !=1 )
   {
      LOG(LM_STD,Fmtmsg("Invoke function docomm is ERROR[%d].",iret),"ERROR");
      fpub_SetCompStatus(lXmlhandle,iret);      /*异常时,组件返回-1*/
      free(indata);
      free(oData);
      return iret;
   }
   free(indata);
   oData[olen]='\0';

   if ((scont_recv=(char *)malloc(MAX_SOCK_BUF_SIZE)) == NULL)
   {
      LOG(LM_STD,Fmtmsg("malloc scont_recv is ERROR."),"ERROR");
      fpub_SetCompStatus(lXmlhandle,iret);      /*异常时,组件返回-1*/
      free(oData);
      return iret;
   }

   /* 拆解通讯报文头 */
   memset(head,0x00,sizeof(head));
   iret = DRC_unpackHeadStr(lXmlhandle,oData,olen,head,&hl,scont_recv,&ilen_recv);
   /*modified by dpl 20180913 添加返回值判断*/
   LOG(LM_STD,Fmtmsg("组件[%s] iret=[%d]",fpub_GetCompname(lXmlhandle),iret),__func__)
   if (iret != 0)
   {
      LOG(LM_STD,Fmtmsg("组件[%s] DRC_unpackHeadStr is error:return value is [%d]",fpub_GetCompname(lXmlhandle),iret),__func__)
      return -1;
   }  
   
   /* 释放临时堆 20140714 by PengLiyang */
   free(oData);

   /* 对比series */
   iret = DRC_checkResponseSeries(lXmlhandle,head,scont_recv);
   if (iret <0)
   {
      free(scont_recv);
      LOG(LM_STD,Fmtmsg("DRC_checkResponseSeries is ERROR."),"ERROR");
      fpub_SetCompStatus(lXmlhandle,-2);      /*异常时,组件返回-1*/
      return -2;
   }

   /* UTF-8 转换为GBK */
   if ((outdata=(char *)malloc(MAX_SOCK_BUF_SIZE)) == NULL)
   {
      LOG(LM_STD,Fmtmsg("malloc outdata is ERROR."),"ERROR");
      fpub_SetCompStatus(lXmlhandle,-2);      /*异常时,组件返回-1*/
      free(scont_recv);
      return -2;
   }

   ilen_send=MAX_SOCK_BUF_SIZE;
   if (DRC_convert("UTF-8", "GB18030", scont_recv, ilen_recv, outdata, &ilen_send) !=0)
   {
      LOG(LM_STD,Fmtmsg("DRC_covert is ERROR."),"ERROR");
      fpub_SetCompStatus(lXmlhandle,-2);      /*异常时,组件返回-1*/
      free(scont_recv);
      free(outdata);
      return -2;
   }
   free(scont_recv);
   ilen_send = MAX_SOCK_BUF_SIZE - ilen_send;
   outdata[ilen_send]='\0';

   /** ESB函数执行完毕 **/

   LOG(LM_DEBUG, Fmtmsg("接收ESB应答报文体:iPackageLen [%d],[%s]", ilen_send,outdata), "INFO");
   if (xml_SetBinElement(lXmlhandle,XMLNM_COMMBUF,outdata,ilen_send +1)== FAIL)
   {
      LOG(LM_STD,Fmtmsg("  -->通讯成功,写回XML失败(可能需冲正),msg[%s]",GETXMLERR),"ERROR");
      fpub_SetMsg(lXmlhandle,MID_YW_ERROR,Fmtmsg("与ESB通讯失败"));
      fpub_SetCompStatus(lXmlhandle,-2);      /*异常时,组件返回-2*/
      free(outdata);
      return -2;
   }
   free(outdata);
 
#ifdef DEBUG
   LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)),__func__)
#endif

   fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
   return 0;
}

/************************************************************************
动态组件函数定义
组件函数名称:DRC_UNPACKESB
组件名称:DRC_UNPACKESB
组件功能:
组件参数:
 序号 参数类型  参数名称         资源类别     缺省值  可空  参数说明
  1   1-输入   通讯缓冲区     401-XML结点    /commbuf   N    通讯缓冲区结点      

组件结果状态:
  结果状态码         结果说明
  缺省

日志信息:
  日志级别           日志宏

响应信息:
  内部响应码         内部响应信息

主要操作元素:
  元素路径          操作

主要操作库表:
  表名              操作

使用限制:

项 目 组: 
程 序 员:
发布日期:
修改日期:2008-12-1 16:10:24[Gen]
参数使用示例:
************************************************************************/
IRESULT DRC_UNPACKESB(HXMLTREE lXmlhandle)
{
   char scommbufnode[256];
   char sbuf[5],head[2048],workDate[9];
   int  iParas,ilen_send, iret, ilen_recv,hl;
   char *indata, *outdata;
   long olen;
 
   fpub_InitSoComp(lXmlhandle);

#ifdef DEBUG
   LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),__func__)
#endif

   memset(scommbufnode,0x00,sizeof(scommbufnode));

   COMP_PARACOUNTCHKMIN(1)
   COMP_GETPARSEPARAS(1,scommbufnode,"通讯缓冲区")
 
   /*请求包长度,动态分配*/
   ilen_send=xml_GetElementLen(lXmlhandle, scommbufnode);
   if (ilen_send <= 0)
   {
      LOG(LM_STD,Fmtmsg("  -->通讯失败,通讯缓冲区数据长度不正确[%d],msg[%s]", ilen_send,GETXMLERR),"ERROR");
      fpub_SetMsg(lXmlhandle,MID_YW_ERROR,Fmtmsg("与ESB通讯失败"));
      fpub_SetCompStatus(lXmlhandle,-1);      /*异常时,组件返回-1*/
      return -1;
   }      
   ilen_send = ilen_send/2;
   indata = malloc(sizeof(char) * MAX_SOCK_BUF_SIZE);
   if (indata == NULL)
   {
      LOG(LM_STD, Fmtmsg("malloc分配内存失败,errmsg=[%s]", strerror(errno)), __func__);     
      fpub_SetMsg(lXmlhandle,MID_YW_ERROR,Fmtmsg("申请内存失败，与ESB通讯失败"));
      fpub_SetCompStatus(lXmlhandle,-1);      /*异常时,组件返回-1*/
      return -1;
   }   
   iret=xml_GetBinElement(lXmlhandle, scommbufnode, indata, ilen_send+1); 
   if (iret < 0)
   {
      LOG(LM_STD,Fmtmsg("  -->通讯失败,获取通讯缓冲区数据失败,msg[%s]",GETXMLERR),"ERROR");
      fpub_SetMsg(lXmlhandle,MID_YW_ERROR,Fmtmsg("获取发送数据失败，与ESB通讯失败"));
      fpub_SetCompStatus(lXmlhandle,-1);      /*异常时,组件返回-1*/
      free(indata);
      return -1;
   }
   indata[ilen_send]='\0';
#ifdef DEBUG
   LOG(LM_STD, Fmtmsg("发送GXP请求报文体:iPackageLen[%d],[%s]", ilen_send,scont_send), "INFO");
#endif

   /*** 以下为ESB的函数 */

   /* 1 初始化系统*/
   iret = DRC_InitConfig();
   if (iret !=0)
   {
      LOG(LM_STD,Fmtmsg("  -->获取ESB配置信息失败"),"ERROR");
      fpub_SetMsg(lXmlhandle,MID_YW_ERROR,Fmtmsg("获取ESB配置信息失败"));
      fpub_SetCompStatus(lXmlhandle,-1);      /*异常时,组件返回-1*/
      free(indata);
      return -1;
   }

   outdata =  (char * ) malloc( sizeof(char) * MAX_SOCK_BUF_SIZE);
   if (outdata == NULL)
   {
      free(indata);
      LOG(LM_STD,Fmtmsg("申请内存失败"),"ERROR");
      fpub_SetMsg(lXmlhandle,MID_YW_ERROR,Fmtmsg("申请内存失败，与ESB通讯失败"));
      fpub_SetCompStatus(lXmlhandle,-1);      /*异常时,组件返回-1*/
      return -1;
   }

   /* 拆解通讯报文头 */
   memset(head,0x00,sizeof(head));
   memset(sbuf,0x00,sizeof(sbuf));
   memcpy(sbuf,indata,4);
   hl = atoi(sbuf);
   memcpy(head,indata+4,hl);
   ilen_recv = ilen_send-4-hl;
   memcpy(outdata,indata+4+hl,ilen_recv);
   outdata[ilen_recv]='\0';

   /* 2 同步密钥 */    
   iret=DRC_synWorkKey2(lXmlhandle,head,0);
   if (iret<0)
   {
      LOG(LM_STD,Fmtmsg("  -->同步ESB密钥失败"),"ERROR");
      fpub_SetMsg(lXmlhandle,MID_YW_ERROR,Fmtmsg("同步ESB密钥失败"));
      fpub_SetCompStatus(lXmlhandle,-1);
      free(indata);
      free(outdata);
      return -1;
   }

   /* 对比series */
   iret = DRC_checkResponseSeries(lXmlhandle,head,outdata);
   if (iret <0)
   {
      free(indata);
      free(outdata);
      LOG(LM_STD,Fmtmsg("DRC_checkResponseSeries is ERROR."),"ERROR");
      fpub_SetCompStatus(lXmlhandle,-2);      /*异常时,组件返回-1*/
      return -2;
   }

   ilen_send=MAX_SOCK_BUF_SIZE;
   if (DRC_convert("UTF-8", "GB18030", outdata, ilen_recv, indata, &ilen_send) !=0)
   {
      LOG(LM_STD,Fmtmsg("DRC_covert is ERROR."),"ERROR");
      fpub_SetCompStatus(lXmlhandle,-2);      /*异常时,组件返回-1*/
      free(indata);
      free(outdata);
      return -2;
   }
   free(outdata);
   ilen_send = MAX_SOCK_BUF_SIZE - ilen_send;
   indata[ilen_send]='\0';

   /** ESB函数执行完毕 **/

   LOG(LM_DEBUG, Fmtmsg("接收ESB应答报文体:iPackageLen [%d],[%s]", ilen_send,indata), "INFO");
   if (xml_SetBinElement(lXmlhandle,XMLNM_COMMBUF,indata,ilen_send +1)== FAIL)
   {
      LOG(LM_STD,Fmtmsg("  -->通讯成功,写回XML失败(可能需冲正),msg[%s]",GETXMLERR),"ERROR");
      fpub_SetMsg(lXmlhandle,MID_YW_ERROR,Fmtmsg("与ESB通讯失败"));
      fpub_SetCompStatus(lXmlhandle,-2);      /*异常时,组件返回-2*/
      free(indata);
      return -2;
   }
   free(indata);

#ifdef DEBUG
   LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)),__func__)
#endif

   fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
   return 0;
}

/************************************************************************
动态组件函数定义
组件函数名称:DRC_GBKTOUTF
组件名称:DRC_GBKTOUTF
组件功能:
组件参数:
 序号 参数类型  参数名称         资源类别     缺省值  可空  参数说明
  1   1-输入   通讯缓冲区     401-XML结点    /commbuf   N    通讯缓冲区结点      

组件结果状态:
  结果状态码         结果说明
  缺省

日志信息:
  日志级别           日志宏

响应信息:
  内部响应码         内部响应信息

主要操作元素:
  元素路径          操作

主要操作库表:
  表名              操作

使用限制:

项 目 组: 
程 序 员:
发布日期:
修改日期:2008-12-1 16:10:24[Gen]
参数使用示例:
************************************************************************/
IRESULT DRC_GBKTOUTF(HXMLTREE lXmlhandle)
{
   char scommbufnode[256];
   char sbuf[5],head[2048];
   int  iParas,ilen_send, iret, ilen_recv,hl;
   char *indata, *outdata;
   long olen;
 
   fpub_InitSoComp(lXmlhandle);

#ifdef DEBUG
   LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),__func__)
#endif

   memset(scommbufnode,0x00,sizeof(scommbufnode));

   COMP_PARACOUNTCHKMIN(1)
   COMP_GETPARSEPARAS(1,scommbufnode,"通讯缓冲区")
 
   /*请求包长度,动态分配*/
   ilen_send=xml_GetElementLen(lXmlhandle, scommbufnode);
   if (ilen_send <= 0)
   {
      LOG(LM_STD,Fmtmsg("  -->通讯失败,通讯缓冲区数据长度不正确[%d],msg[%s]", ilen_send,GETXMLERR),"ERROR");
      fpub_SetMsg(lXmlhandle,MID_YW_ERROR,Fmtmsg("与ESB通讯失败"));
      fpub_SetCompStatus(lXmlhandle,-1);      /*异常时,组件返回-1*/
      return -1;
   }      
   ilen_send = ilen_send/2;
   indata = malloc(sizeof(char) * MAX_SOCK_BUF_SIZE);
   if (indata == NULL)
   {
      LOG(LM_STD, Fmtmsg("malloc分配内存失败,errmsg=[%s]", strerror(errno)), __func__);     
      fpub_SetMsg(lXmlhandle,MID_YW_ERROR,Fmtmsg("申请内存失败，与ESB通讯失败"));
      fpub_SetCompStatus(lXmlhandle,-1);      /*异常时,组件返回-1*/
      return -1;
   }   
   iret=xml_GetBinElement(lXmlhandle, scommbufnode, indata, ilen_send+1); 
   if (iret < 0)
   {
      LOG(LM_STD,Fmtmsg("  -->通讯失败,获取通讯缓冲区数据失败,msg[%s]",GETXMLERR),"ERROR");
      fpub_SetMsg(lXmlhandle,MID_YW_ERROR,Fmtmsg("获取发送数据失败，与ESB通讯失败"));
      fpub_SetCompStatus(lXmlhandle,-1);      /*异常时,组件返回-1*/
      free(indata);
      return -1;
   }
   indata[ilen_send]='\0';
#ifdef DEBUG
   LOG(LM_STD, Fmtmsg("发送ESB请求报文体:iPackageLen[%d],[%s]", ilen_send,scont_send), "INFO");
#endif

   outdata =  (char * ) malloc( sizeof(char) * MAX_SOCK_BUF_SIZE);
   if (outdata == NULL)
   {
      free(indata);
      LOG(LM_STD,Fmtmsg("申请内存失败"),"ERROR");
      fpub_SetMsg(lXmlhandle,MID_YW_ERROR,Fmtmsg("申请内存失败，与ESB通讯失败"));
      fpub_SetCompStatus(lXmlhandle,-1);      /*异常时,组件返回-1*/
      return -1;
   }

   ilen_recv=MAX_SOCK_BUF_SIZE;
   if (DRC_convert("GB18030","UTF-8", indata, ilen_send, outdata, &ilen_recv) !=0)
   {
      LOG(LM_STD,Fmtmsg("GB18030转UTF-8失败."),"ERROR");
      fpub_SetMsg(lXmlhandle,MID_YW_ERROR,Fmtmsg("GB18030转UTF-8失败，与ESB通讯失败"));
      fpub_SetCompStatus(lXmlhandle,-1);      /*异常时,组件返回-1*/
      free(outdata);
      free(indata);
      return -1;
   }
   ilen_recv = MAX_SOCK_BUF_SIZE - ilen_recv;
   outdata[ilen_recv]='\0';
   free(indata);

   /* LOG(LM_DEBUG, Fmtmsg("发送ESB应答报文体:iPackageLen [%d],[%s]", ilen_recv,indata), "INFO"); */
   if (xml_SetBinElement(lXmlhandle,XMLNM_COMMBUF,outdata,ilen_recv)== FAIL)
   {
      LOG(LM_STD,Fmtmsg("  -->通讯成功,写回XML失败(可能需冲正),msg[%s]",GETXMLERR),"ERROR");
      fpub_SetMsg(lXmlhandle,MID_YW_ERROR,Fmtmsg("与ESB通讯失败"));
      fpub_SetCompStatus(lXmlhandle,-2);      /*异常时,组件返回-2*/
      free(outdata);
      return -2;
   }
   free(outdata);
 
#ifdef DEBUG
   LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)),__func__)
#endif

   fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
   return 0;
}
