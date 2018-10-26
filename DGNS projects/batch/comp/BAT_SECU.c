/********************************************************************
版权所有:恒生电子股份有限公司（杭州）
项目名称:中间业务平台项目(AGENT2.1)
版    本:V4.1.0.1
操作系统:
文件名称:BAT_SECU.ec
文件描述:批量业务处理客户端加解密相关组件集
程 序 员:YangDong
发布日期:2012-12-03

程 序 员:YangDong
修改日期:20141018
修改说明:DCI改造

程 序 员:YangDong
修改日期:20150908
修改说明:批量客户端的客户编号替换成单位编号
*********************************************************************/
#include "gaps_head.h"
#include "app_head.h"
#include "batch_head.h"
#include "app_macro.h"
#include "app_xmlmacro.h"

BATCH_CLI_USER sdb_batch_cli_user;
char sKey[8+1];
char sKeyKey[16+1];
char sKhbh[32+1];
char sXybh[32+1];
int  iSend ;
char sSqlStr[512+1];

/* 默认加解密处理分段长度 */
#define BATCH_SECURITY_LEN 8 
#define BAT_KEY "handsome"
#define BAT_KEYKEY "37456411"
void FDES(unsigned char  *key,unsigned char  *text,unsigned char  *mtext);
void _FDES(unsigned char  *key,unsigned char  *mtext,unsigned char  *text);
void Fencrypt0(unsigned char  *text,unsigned char  *mtext);
void Fdiscrypt0(unsigned char  *mtext,unsigned char  *text);
void Fexpand0(unsigned char  *in,unsigned char  *out);
void Fcompress0(unsigned char  *out,unsigned char  *in);
void Fcompress016(unsigned char  *out,unsigned char  *in);
void Fsetkeystar(unsigned char  bits[64]);
void FLS(unsigned char  *bits,unsigned char  *buffer,int count);
void Fson(unsigned char  *cc,unsigned char  *dd,unsigned char  *kk);
void Fiip(unsigned char  *text,unsigned char  *ll,unsigned char  *rr);
void _Fiip(unsigned char  *text,unsigned char  *ll,unsigned char  *rr);
void FF(int n,unsigned char  *ll,unsigned char  *rr,unsigned char  *LL,unsigned char  *RR);
void Fs_box(unsigned char  *aa,unsigned char  *bb);
unsigned char  C[17][28],D[17][28],K[17][48];

char * hex2bytes( unsigned char* s16, char * sbytes )
{
    int i,m,temp=0,n;
    int j = 0;
    m=strlen(s16);//十六进制是按字符串传进来的，所以要获得他的长度
    for(i=0;i<m;i++)
    {
        if(s16[i]>='A'&&s16[i]<='F')//十六进制还要判断他是不是在A-F或者a-f之间a=10。。
            n=s16[i]-'A'+10;
        else if(s16[i]>='a'&&s16[i]<='f')
            n=s16[i]-'a'+10;
        else n=s16[i]-'0';
        temp=temp*16+n;
        if( i % 2 )
        {
             sbytes[j++] = temp ;
        }
    }
    return sbytes;
}

/*****************************************************************************
* function: DES
* parameter: unsigned char  * key ; key for encrypt
*   unsigned char  * text ; plain text 
*   unsigned char  * mtext ; encipher result
* return: none
*****************************************************************************/
void FDES(unsigned char  *key,unsigned char  *text,unsigned char  *mtext)
{
    unsigned char  tmp[64];
    Fexpand0(key,tmp);
    Fsetkeystar(tmp);
    Fencrypt0(text,mtext);
}
/*****************************************************************************
* function: DES
* parameter: unsigned char  * key ; key for encrypt
*   unsigned char  * mtext ; encipher data 
*   unsigned char  * text ; plain data
* return: none
*****************************************************************************/
void _FDES(unsigned char  *key,unsigned char  *mtext,unsigned char  *text)
{
    unsigned char  tmp[64];
    Fexpand0(key,tmp);
    Fsetkeystar(tmp);
    Fdiscrypt0(mtext,text);
}
void Fencrypt0(unsigned char  *text,unsigned char  *mtext)
{
    unsigned char  ll[64],rr[64],LL[64],RR[64];
    unsigned char  tmp[64];
    int i,j;
    Fiip(text,ll,rr);
    for (i=1;i<17;i++)
    {
        FF(i,ll,rr,LL,RR);
        for (j=0;j<32;j++)
        {
         ll[j]=LL[j];
         rr[j]=RR[j];
        }
    }
    _Fiip(tmp,rr,ll);
    Fcompress0(tmp,mtext);
}
void Fdiscrypt0(unsigned char  *mtext,unsigned char  *text)
{
    unsigned char  ll[64],rr[64],LL[64],RR[64];
    unsigned char  tmp[64];
    int i,j;
    Fiip(mtext,ll,rr);
    for (i=16;i>0;i--)
    {
        FF(i,ll,rr,LL,RR);
        for (j=0;j<32;j++)
        {
            ll[j]=LL[j];
            rr[j]=RR[j];
        }
    }
    _Fiip(tmp,rr,ll);
    Fcompress0(tmp,text);
}
void Fexpand0(unsigned char  *in,unsigned char  *out)
{
    int divide;
    int i,j;
    for (i=0;i<8;i++)
    {
        divide=0x80;
        for (j=0;j<8;j++)
        {
            *out++=(in[i]/divide)&1;
            divide/=2;
        }
    }
}

void Fcompress0(unsigned char  *out,unsigned char  *in)
{
    int times;
    int i,j;
    for (i=0;i<8;i++)
    {
        times=0x80;
        in[i]=0;
        for (j=0;j<8;j++)
        {
            in[i]+=(*out++)*times;
            times/=2;
        }
    }
}
void Fcompress016(unsigned char  *out,unsigned char  *in)
{
    int times;
    int i,j;
    for (i=0;i<16;i++)
    {
        times=0x8;
        in[i]='0';
        for (j=0;j<4;j++)
        {
            in[i]+=(*out++)*times;
            times/=2;
        }
    }
}
int pc_1_cp[28]={
57,49,41,33,25,17,9
,1,58,50,42,34,26,18
,10,2,59,51,43,35,27
,19,11,3,60,52,44,36};
int pc_1_dp[28]={
63,55,47,39,31,23,15
,7,62,54,46,38,30,22
,14,6,61,53,45,37,29
,21,13,5,28,20,12,4};
int pc_2p[48]={
14,17,11,24,1,5,
3,28,15,6,21,10,
23,19,12,4,26,8,
16,7,27,20,13,2,
41,52,31,37,47,55,
30,40,51,45,33,48,
44,49,39,56,34,53,
46,42,50,36,29,32};
int ls_countp[16]={
1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};
void Fsetkeystar(unsigned char  bits[64])
{
    int i,j;
    for (i=0;i<28;i++)
       C[0][i]=bits[pc_1_cp[i]-1];
    for (i=0;i<28;i++)
       D[0][i]=bits[pc_1_dp[i]-1];
    for (j=0;j<16;j++)
    {
       FLS(C[j],C[j+1],ls_countp[j]);
       FLS(D[j],D[j+1],ls_countp[j]);
       Fson(C[j+1],D[j+1],K[j+1]);
    }
}

void FLS(unsigned char  *bits,unsigned char  *buffer,int count)
{
    int i,j;
    for (i=0;i<28;i++)
    {
       buffer[i]=bits[(i+count)%28];
    }
}
void Fson(unsigned char  *cc,unsigned char  *dd,unsigned char  *kk)
{
    int i,j;
    unsigned char  buffer[56];
    for (i=0;i<28;i++)
       buffer[i]=*cc++;
    for (i=28;i<56;i++)
       buffer[i]=*dd++;
    for (i=0;i<48;i++)
       *kk++=buffer[pc_2p[i]-1];
}
int iip_tab_p[64]={
58,50,42,34,26,18,10,2,
60,52,44,36,28,20,12,4,
62,54,46,38,30,22,14,6,
64,56,48,40,32,24,16,8,
57,49,41,33,25,17,9,1,
59,51,43,35,27,19,11,3,
61,53,45,37,29,21,13,5,
63,55,47,39,31,23,15,7};
int _iip_tab_p[64]={
40,8,48,16,56,24,64,32,
39,7,47,15,55,23,63,31,
38,6,46,14,54,22,62,30,
37,5,45,13,53,21,61,29,
36,4,44,12,52,20,60,28,
35,3,43,11,51,19,59,27,
34,2,42,10,50,18,58,26,
33,1,41,9,49,17,57,25};
void Fiip(unsigned char  *text,unsigned char  *ll,unsigned char  *rr)
{
    int i,j;
    unsigned char  buffer[64];
    unsigned char  tmp[64];
    Fexpand0(text,buffer);
    for (i=0;i<32;i++)
       ll[i]=buffer[iip_tab_p[i]-1];
    for (i=0;i<32;i++)
       rr[i]=buffer[iip_tab_p[i+32]-1];
}
void _Fiip(unsigned char  *text,unsigned char  *ll,unsigned char  *rr)
{
   int i,j;
   unsigned char  tmp[64];
   for (i=0;i<32;i++)
      tmp[i]=ll[i];
   for (i=32;i<64;i++)
      tmp[i]=rr[i-32];
   for (i=0;i<64;i++)
      text[i]=tmp[_iip_tab_p[i]-1];
}

int e_r_p[48]={
32,1,2,3,4,5,4,5,6,7,8,9,
8,9,10,11,12,13,12,13,14,15,16,17,
16,17,18,19,20,21,20,21,22,23,24,25,
24,25,26,27,28,29,28,29,30,31,32,1};
int local_PP[32]={
16,7,20,21,29,12,28,17,
1,15,23,26,5,18,31,10,
2,8,24,14,32,27,3,9,
19,13,30,6,22,11,4,25};
int ccom_SSS_p[8][4][16]={
14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,/* err on */
4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13,
15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9,
10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12,
7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14, /* err on */
2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6, /* err on */
4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3,
12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,
9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13,
4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,
13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,
1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,
6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12,
13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11};

void FF(int n,unsigned char  *ll,unsigned char  *rr,unsigned char  *LL,unsigned char  *RR)
{
    int i,j;
    unsigned char  buffer[64],tmp[64];
    for (i=0;i<48;i++)
       buffer[i]=rr[e_r_p[i]-1];
    for (i=0;i<48;i++)
       buffer[i]=(buffer[i]+K[n][i])&1;
    Fs_box(buffer,tmp);
    for (i=0;i<32;i++)
       buffer[i]=tmp[local_PP[i]-1];
    for (i=0;i<32;i++)
       RR[i]=(buffer[i]+ll[i])&1;
    for (i=0;i<32;i++)
       LL[i]=rr[i];
}
void Fs_box(unsigned char  *aa,unsigned char  *bb)
{
    int i,j,k,m;
    int y,z;
    unsigned char  ss[8];
    m=0;
    for (i=0;i<8;i++)
    {
       j=6*i;
       y=aa[j]*2+aa[j+5];
       z=aa[j+1]*8+aa[j+2]*4+aa[j+3]*2+aa[j+4];
       ss[i]=ccom_SSS_p[i][y][z];
       y=0x08;
       for (k=0;k<4;k++)
       {
          bb[m++]=(ss[i]/y)&1;
          y/=2;
       }
    }
}

int des_ENCRYPT( unsigned char *key, unsigned char *s, unsigned char *d, unsigned short len )
{
    int i;
    for(i=0;i<len;i+=8)
        FDES(key,s+i,d+i);
    return i;
}

/*解密*/
int des_DECRYPT( unsigned char  *key, unsigned char *s, unsigned char *d, unsigned short len )
{
    int i;
    for(i=0;i<len;i+=8)_FDES(key,d+i,s+i);
    return i;
}

/***************************************************************************
动态组件函数定义
组件函数名称:SBATCH_DES_PROC
组件名称:SBATCH_DES_PROC
组件功能:文件简单DES加解密处理
组件参数:
序号 参数类型  参数名称          资源类别      缺省值     可空       参数说明
使用限制:
程 序 员: 
发布日期:
修改日期:
参数使用示例:
****************************************************************************/
IRESULT SBATCH_DES_PROC(HXMLTREE lXmlhandle)
{
    char sBuf[128];
    char sFileName[128];
    char sFileName_d[128];
    char sSource[8+1];
    char sDest[8+1];
    char sFlag[1+1];
    char sTmp[16+1];
    char sLineBuf[1024+1];
    char sRespMsg[60+1];
    int iRespCode = 0;
    int  iLen = 0;
    int  iParas;
    /*int  ret = -1;*/
    /*int  iFileSize = 0;*/
    int  i = 0, count = 0;
    int  n = 0;
    int  iFlag = 0; 
    char sSql1[1024];
    char sErrmsg[512];
    int iRet =-1;

    FILE* fp_s;   /* 源文件 */
    FILE* fp_d;   /* 目标文件 */
        
    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG")

    COMP_PARACOUNTCHKMIN(4)

    COMP_PARACOUNTCHKMIN(1)
    memset(sBuf,0,sizeof(sBuf));
    memset(sFileName,0,sizeof(sFileName));
    COMP_GETPARSEPARAS(1,sBuf,"待处理文件")
    pstrcopy(sFileName,sBuf,sizeof(sFileName));
    
    memset(sBuf,0,sizeof(sBuf));
    memset(sBuf,0,sizeof(sBuf));
    memset(sFileName_d,0,sizeof(sFileName_d));
    COMP_GETPARSEPARAS(2,sBuf,"处理后文件")
    pstrcopy(sFileName_d,sBuf,sizeof(sFileName_d));
    
    memset(sBuf,0,sizeof(sBuf));
    memset(sKey,0,sizeof(sKey));
    COMP_GETPARSEPARAS(3,sBuf,"密钥") 
    pstrcopy( sKey,sBuf,sizeof( sKey ));
    trim( sKey );

    memset(sBuf,0,sizeof(sBuf));
    memset(sFlag,0,sizeof(sFlag));
    COMP_GETPARSEPARAS(4,sBuf,"加解密标识")  /* 0 加密 1 解密 */
    pstrcopy( sFlag,sBuf,sizeof( sFlag ));

    if( sFlag[0] != '0' && sFlag[0] != '1' )
    {
        LOG(LM_STD,Fmtmsg("BATCH: 加解密标志=[%s]非法",sFlag ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_BATCH_DE_FLAG,MSG_BATCH_DE_FLAG );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    LOG(LM_DEBUG,Fmtmsg("source[%s] dest[%s] key[%s] flag[%s]", sFileName, sFileName_d, sKey, sFlag ),"DEBUG");

    /* 密钥处理 如果密钥不传入，从批量客户端信息表中获取 */
    if( strlen( sKey ) == 0 )
    {
        /*客户编号*/
        memset(sBuf,0,sizeof(sBuf));
        memset(sKhbh,0,sizeof(sKhbh));
        COMP_SOFTGETXML(XMLNM_BATCH_REQ_DWBH,sBuf);
        trim( sBuf );
        pstrcopy( sKhbh,sBuf,sizeof(sKhbh));
        
        /* 协议编号 */
        memset(sBuf,0,sizeof(sBuf));
        memset(sXybh,0,sizeof(sXybh));
        COMP_SOFTGETXML(XMLNM_BATCH_REQ_XYBH,sBuf);
        trim( sBuf );
        pstrcopy( sXybh,sBuf,sizeof(sXybh));

         /* 如果不传入批量客户端信息，默认取公共密钥 */
/* deleted by yangdong 20150909  不使用公共密钥
        if(  strlen( sKhbh ) == 0 && strlen( sXybh ) == 0  ) 
            strcpy( sKey, BAT_KEY );
        else
        { 
*/
        memset( sSql1, 0x00, sizeof( sSql1 ) );
        if(  strlen( sKhbh ) > 0 ) 
        {
            snprintf( sSql1, sizeof( sSql1 ) , "SELECT key FROM batch_cli_user WHERE user_id='%s'", sKhbh );
        }
        else /* 未传入客户编号，按协议编号查询 */
        {
            if(  strlen( sXybh ) > 0 )
            {
                snprintf( sSql1, sizeof( sSql1 ), "SELECT key FROM batch_cli_user WHERE contract_no='%s'", sXybh );
            }
            else /* 未传入单位编号,协议编号*/
            {
                /* modified by yangdong 20150909 
                   接口未传入，获取单位编号 
                fpub_SetMsg(lXmlhandle,MID_BATCH_NULL_CLI_BH,MSG_BATCH_NULL_CLI_BH);
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
                */
                memset(sBuf,0,sizeof(sBuf));
                COMP_SOFTGETXML(XMLNM_APP_DWCPXY_DWBH,sBuf);
                snprintf( sSql1, sizeof( sSql1 ) , "SELECT key FROM batch_cli_user WHERE user_id='%s'", sBuf );
            }
        }

        LOG(LM_DEBUG,Fmtmsg("sql[%s]", sSql1 ),"DEBUG")

        iRet = DBSelectToVarChar(sErrmsg, sKeyKey, sSql1); 
        if( iRet < 1 )
        {
            /*mod by zengzt 20160525 if( iRet > 0 ) */
            if( iRet == 0 )
                fpub_SetMsg(lXmlhandle,MID_BATCH_NO_CLIINFO,MSG_BATCH_NO_CLIINFO);
            else
                fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return -1;
        }
        /* 解密 */
        memset( sKey, 0x00, sizeof( sKey ) );
        memset( sTmp, 0x00, sizeof( sTmp ) );
        /* 存储的16进制字符串 */
        hex2bytes( sKeyKey, sTmp);
        i = des_DECRYPT( BAT_KEYKEY, (unsigned char *)sKey,(unsigned char *)sTmp, 8 );    
    }

    /* modified by guoliang 20130417 */
    memset(sBuf, 0x00, sizeof(sBuf));
    if( sFileName[0] == '~' )  /* ~代表HOME目录 */
    {
        sprintf( sBuf, "%s/%s" ,getenv("HOME"), sFileName+2 ); 
        strcpy( sFileName, sBuf );
        LOG(LM_DEBUG,Fmtmsg("BATCH: 源文件绝对路径[%s] ", sFileName ),"DEBUG")
    }
    else if( sFileName[0] != '/') /* 相对路径时 */
    {
        sprintf( sBuf, "%s/%s" ,getenv("HOME"), sFileName ); 
        strcpy( sFileName, sBuf );
        LOG(LM_DEBUG,Fmtmsg("BATCH: 源文件绝对路径[%s] ", sFileName ),"DEBUG")
    }
    memset(sBuf, 0x00, sizeof(sBuf));
    if( sFileName_d[0] == '~' )  /* ~代表HOME目录 */
    {
        sprintf( sBuf, "%s/%s" ,getenv("HOME"), sFileName_d+2 ); 
        strcpy( sFileName_d, sBuf );
        LOG(LM_DEBUG,Fmtmsg("BATCH: 目标文件绝对路径[%s] ", sFileName_d ),"DEBUG")
    }
    else if( sFileName_d[0] != '/') /* 相对路径时 */
    {
        sprintf( sBuf, "%s/%s" ,getenv("HOME"), sFileName_d ); 
        strcpy( sFileName_d, sBuf );
        LOG(LM_DEBUG,Fmtmsg("BATCH: 目标文件绝对路径[%s] ", sFileName_d ),"DEBUG")
    }
    /* modify end */
    if( ( fp_s = fopen( sFileName, "rb" ) ) == NULL )
    {
        LOG(LM_STD,Fmtmsg("打开文件失败,file=[%s],error=[%s]",sFileName,strerror(errno)),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_YW_ERROR,Fmtmsg("打开文件失败"));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    if( ( fp_d = fopen( sFileName_d, "wb" ) ) == NULL )
    {
        LOG(LM_STD,Fmtmsg("打开文件失败,file=[%s],error=[%s]",sFileName,strerror(errno)),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_YW_ERROR,Fmtmsg("打开文件失败"));
        fclose( fp_s );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    if( sFlag[0] == '1' ) /* 解密 */
    { 
        count = 0;
        memset( sTmp, 0x00, sizeof( sTmp ) );
        while( fgets( sLineBuf, 1024, fp_s ) != NULL )
        {
            /* 按行处理 */
            iLen = strlen( sLineBuf );

            /* 过滤换行回车  */
            if( sLineBuf[iLen-1] == 10 || sLineBuf[iLen-1] == 13    )
            {
                sLineBuf[iLen-1] = '\0';
                iLen --;
            }
            if( sLineBuf[iLen-2] == 10 || sLineBuf[iLen-2] == 13    )
            {
                sLineBuf[iLen-2] = '\0';
                iLen --;
            }

            /* 可能会有最后一行没有结束符 */
            if( ( ( iLen -1 ) % 16 ) != 0 && ( iLen  % 16 ) != 0  )
            {
                LOG(LM_STD,Fmtmsg("读取加密文件失败，加密文件不规则len[%d][%s]", iLen, sLineBuf ),"ERROR");
                /* modified by guoliang 20130513 */
                iRespCode = MID_BATCH_DES_FILEERR ;
                pstrcopy(sRespMsg, MSG_BATCH_DES_FILEERR, sizeof(sRespMsg));
                /* end */
                iFlag = -1;
                break;
            }

            for( count = 0; count < ( iLen - 1 );  )
            {
                memcpy( sTmp, sLineBuf+count, 16 );    

                memset( sDest, 0x00, sizeof( sDest ) );
                memset( sSource, 0x00, sizeof( sSource ) );
                /* 16进制串，读取16位，转为8位字节串 */
                hex2bytes( sTmp, sSource );
                i = des_DECRYPT((unsigned char *) sKey, (unsigned char *)sDest,(unsigned char *)sSource, 8 );    
                count += 16;

                if( count < ( iLen - 2 )  )
                {
                    i = fwrite( sDest, sizeof( char ), 8, fp_d );
                }
                else  /* 去除最后的 00 */
                {
                    /* 使用fputs */
                    i = fputs( sDest, fp_d );
                    /* 增加一个换行 */
                    i = fputs( "\n", fp_d );
                }
    
                if( i < 0 )
                {
                    LOG(LM_STD,Fmtmsg("写文件失败[%d]", i ),"ERROR");
                    /* modified by guoliang 20130513 */
                    iRespCode = MID_BATCH_DES_WRERR;
                    pstrcopy(sRespMsg, MSG_BATCH_DES_WRERR, sizeof(sRespMsg));
                    /* end */
                    iFlag = -2;
                    break;
                }

                memset( sTmp, 0x00, sizeof( sTmp ) );
            }
        }
    }
    else /* 加密 */
    {
        /* 一次加密8个字节 */
        memset( sLineBuf, 0x00, sizeof( sLineBuf) );
        while( fgets( sLineBuf, 1024, fp_s ) != NULL )
        {
            iLen = strlen( sLineBuf ) ;            
            /* 最后一个回车换行，不加密 */
            if( sLineBuf[iLen-1] == 10 ||  sLineBuf[iLen-1] == 13 )
                iLen --;
            if( sLineBuf[iLen-2] == 10 ||  sLineBuf[iLen-2] == 13 )
                iLen --;
/*
            LOG(LM_STD,Fmtmsg("source[%s]len[%d]", sLineBuf, iLen ),"INFO");
*/
            /* modified by guoliang 20131021 */
            /*for( count = 0; count < ( iLen - 1 );  )*/
            for( count = 0; count <= ( iLen - 1 );  )
            {
                n = 0;
                count += 8;
                /* modified by guoliang 20131021 */
                /* if( count >= ( iLen -1 ) ) */
                if( count > ( iLen -1 ) )
                    n = iLen -count + 8;
                else
                    n = 8;
                
                memcpy( sSource, sLineBuf+count-8, n );    
                memset( sDest, 0x00, sizeof( sDest ) );
                memset( sTmp, 0x00, sizeof( sTmp ) );

                i=des_ENCRYPT((unsigned char *) sKey, (unsigned char *)sSource,(unsigned char *)sDest, n );    
                /* 存储16进制字符串 */
                for( i = 0 ; i < 16/2 ; i ++ )
                {
                    sprintf( sTmp+2*i, "%02X", sDest[i] & 0xFF );
                }
             
                i = fwrite( sTmp, 16, sizeof( char ), fp_d );
                if( i < 0 )
                {
                    LOG(LM_STD,Fmtmsg("写文件失败[%d]", i ),"ERROR");
                    /* modified by guoliang 20130513 */
                    iRespCode = MID_BATCH_DES_WRERR;
                    pstrcopy(sRespMsg, MSG_BATCH_DES_WRERR, sizeof(sRespMsg));
                    /* end */
                    iFlag = -2;
                    break;
                }
                memset( sSource, 0x00, sizeof( sSource ) );
            }
            i = fputs( "\n", fp_d );
        }
    }

    fclose( fp_s );
    fclose( fp_d );

    if( iFlag != 0 )
    {
        /* modified by guoliang 20130513 */
        fpub_SetMsg(lXmlhandle, iRespCode, sRespMsg);
        /* end */
        fpub_SetCompStatus(lXmlhandle, COMPRET_FAIL );
        return COMPRET_FAIL;  
    }

    fpub_SetCompStatus(lXmlhandle, COMPRET_SUCC );

    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG")

    return COMPRET_SUCC;  
}

/************************************************************************
动态组件函数定义
组件函数名称:SBATCH_INS_CLIINFO
组件名称:BATCH_INS_CLIINFO
组件功能: 批量客户端信息登记
组件参数:
 序号 参数类型    参数名称                 资源类别         缺省值    可空    参数说明        
    
使用限制:
程 序 员: 
发布日期:
修改日期:
参数使用示例:
************************************************************************/
IRESULT SBATCH_INS_CLIINFO(HXMLTREE lXmlhandle)
{
    char sBuf[255];
    char sKey_s[2+1];
    char sKey_d1[2+1];
    char sKey_d2[2+1];
    char sKey_d3[2+1];
    char sKey_t1[2+1];
    char sKey_t2[2+1];
    char sKey_t3[2+1];
    char sTmp[4+1];
    char sbuf[2+1];
    int  iParas;
/* modified by yangdong 20150918 dci改造，兼容64位
    long iseqno=0;
*/
	int iseqno=0;
    int  iLen=0;
    int  i = 0;
    char sSql1[1024];
    char sErrmsg[256];
    int iRet =-1;

    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG")

    memset(&sdb_batch_cli_user,0,sizeof(sdb_batch_cli_user));

    /*客户编号*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_DWBH,sBuf);
    trim( sBuf );
    if(  strlen( sBuf ) > 0 ) 
        pstrcopy(sdb_batch_cli_user.user_id,sBuf,sizeof(sdb_batch_cli_user.user_id));
    else /* 未传入单位编号，则自动从序列获取 */
    {
/* modified by yangdong 20150909 未传入单位编号 领用客户端，必需要先单位签约
        if( fprv_getSeqno( BATCH_DWBH_XLJZ, &iseqno) < 0)
        {
            fpub_SetMsg(lXmlhandle,MID_BATCH_GEN_DWBH,MSG_BATCH_GEN_DWBH);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        sprintf(sdb_batch_cli_user.user_id,"%ld",iseqno);
*/
        memset(sBuf,0,sizeof(sBuf));
        COMP_SOFTGETXML(XMLNM_APP_DWCPXY_DWBH,sBuf);
        pstrcopy(sdb_batch_cli_user.user_id,sBuf,sizeof(sdb_batch_cli_user.user_id));
    }

    /*协议编号*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_XYBH,sBuf);
    trim( sBuf );
    if(  strlen( sBuf ) > 0 ) 
        pstrcopy(sdb_batch_cli_user.contract_no,sBuf,sizeof(sdb_batch_cli_user.contract_no));
    else /* 未传入单位编号，则自动从序列获取 */
    {
/* modified by yangdong 20150909 未传入协议编号，默认取业务编号 
        if( fprv_getSeqno(  BATCH_XYBH_XLJZ, &iseqno) < 0)
        {
            fpub_SetMsg(lXmlhandle,MID_BATCH_GEN_DWBH,MSG_BATCH_GEN_DWBH);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        sprintf(sdb_batch_cli_user.contract_no,"%ld",iseqno);
*/
        memset(sBuf,0,sizeof(sBuf));
        COMP_SOFTGETXML(XMLNM_BATCH_REQ_YWBH,sBuf);
        pstrcopy(sdb_batch_cli_user.contract_no,sBuf,sizeof(sdb_batch_cli_user.contract_no));
    }

    /*客户名称*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_KHMC,sBuf);
    trim( sBuf );
    pstrcopy(sdb_batch_cli_user.user_name,sBuf,sizeof(sdb_batch_cli_user.user_name));

    /*联系人*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_LXR,sBuf);
    trim( sBuf );
    pstrcopy(sdb_batch_cli_user.contact,sBuf,sizeof(sdb_batch_cli_user.contact));

    /*电话号码*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_DHHM,sBuf);
    trim( sBuf );
    pstrcopy(sdb_batch_cli_user.phone,sBuf,sizeof(sdb_batch_cli_user.phone));

    /*手机号码*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_SJHM,sBuf);
    trim( sBuf );
    pstrcopy(sdb_batch_cli_user.mobile,sBuf,sizeof(sdb_batch_cli_user.mobile));

    /*email*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_EMAIL,sBuf);
    trim( sBuf );
    pstrcopy(sdb_batch_cli_user.email,sBuf,sizeof(sdb_batch_cli_user.email));

    /*交易机构*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_JYJG,sBuf);
    trim( sBuf );
    pstrcopy(sdb_batch_cli_user.branch,sBuf,sizeof(sdb_batch_cli_user.branch));

    /*交易柜员*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_JYGY,sBuf);
    trim( sBuf );
    pstrcopy(sdb_batch_cli_user.oper,sBuf,sizeof(sdb_batch_cli_user.oper));

    /*客户经理*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_KHJL,sBuf);
    trim( sBuf );
    pstrcopy(sdb_batch_cli_user.acct_manager,sBuf,sizeof(sdb_batch_cli_user.acct_manager));

    /*签约账号*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_QYZH,sBuf);
    trim( sBuf );
    pstrcopy(sdb_batch_cli_user.acct_no,sBuf,sizeof(sdb_batch_cli_user.acct_no));

    /*签约户名*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_QYHM,sBuf);
    trim( sBuf );
    pstrcopy(sdb_batch_cli_user.acct_name,sBuf,sizeof(sdb_batch_cli_user.acct_name));

    /*提交日期*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_ZWRQ,sBuf);
    trim( sBuf );
    pstrcopy(sdb_batch_cli_user.ptrq,sBuf,sizeof(sdb_batch_cli_user.ptrq));

    /* 平台流水 */
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_ZHQZLSH,sBuf);
    pstrcopy(sdb_batch_cli_user.ptls,sBuf,sizeof(sdb_batch_cli_user.ptls));

    /*提交时间*/
    sprintf(sdb_batch_cli_user.tran_time,"%s",GetSysTime()); 

    /* 扩展字段 */
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_EXTFLD1,sBuf);
    trim( sBuf );
    pstrcopy(sdb_batch_cli_user.extfld1,sBuf,sizeof(sdb_batch_cli_user.extfld1));

    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_EXTFLD2,sBuf);
    trim( sBuf );
    pstrcopy(sdb_batch_cli_user.extfld2,sBuf,sizeof(sdb_batch_cli_user.extfld2));

    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_EXTFLD3,sBuf);
    trim( sBuf );
    pstrcopy(sdb_batch_cli_user.extfld3,sBuf,sizeof(sdb_batch_cli_user.extfld3));

    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_EXTFLD4,sBuf);
    trim( sBuf );
    pstrcopy(sdb_batch_cli_user.extfld4,sBuf,sizeof(sdb_batch_cli_user.extfld4));

    /* 生成密钥计算KEY */
    /* 8位密钥，不重复 难以直接猜测组成规则 来自：协议号后两位＋时间戳 */
    /* 取协议号后两位 */
    memset( sKey_s, 0x00, sizeof( sKey_s ) );
    iLen = strlen( sdb_batch_cli_user.contract_no  );
    if( iLen >= 2 )
        memcpy( sKey_s, sdb_batch_cli_user.contract_no+iLen-2 , 2 );
    else
        sprintf( sKey_s, "0%s", sdb_batch_cli_user.contract_no );

    /*日期 */
    memcpy( sKey_d1, sdb_batch_cli_user.ptrq+2, 2 );
    memcpy( sKey_d2, sdb_batch_cli_user.ptrq+4, 2 );
    memcpy( sKey_d3, sdb_batch_cli_user.ptrq+6, 2 );
    /*时间 */
    memcpy( sKey_t1, sdb_batch_cli_user.tran_time, 2 );
    memcpy( sKey_t2, sdb_batch_cli_user.tran_time+2, 2 );
    memcpy( sKey_t3, sdb_batch_cli_user.tran_time+4, 2 );
   
    memset( sKey, 0x00, sizeof( sKey ) );
    /* 日期与协议号乱序组合成密钥 */
    sKey[0] = sKey_d1[0] + sKey_t2[1] - '0' + 24;
    sKey[1] = sKey_d3[0] + sKey_t1[1] - '0' + 25;
    sKey[2] = sKey_s[1] + 24;
    sKey[3] = sKey_d2[1] + sKey_t2[0] - '0' + 24;
    sKey[4] = sKey_d1[1] + sKey_t1[0] - '0' + 24;
    sKey[5] = sKey_d3[1] + sKey_t3[1] - '0' + 24;
    sKey[6] = sKey_d2[0] + sKey_t3[0] - '0' + 24;
    sKey[7] = sKey_s[0] + 24;

    /* 对key进行des加密*/
    memset( sKeyKey, 0x00, sizeof( sKeyKey ) );
    i=des_ENCRYPT( BAT_KEYKEY, (unsigned char *)sKey,(unsigned char *)sKeyKey, 8 );    
    /* 存储16进制字符串 */
    for( i = 0 ; i < 16/2 ; i ++ )
    {
        sprintf( sdb_batch_cli_user.key+2*i, "%02X", sKeyKey[i] & 0xFF );
    }

    /* 签约状态 0- 正常 */
    sdb_batch_cli_user.status[0] ='0';

    iRet = DBInsert("batch_cli_user", SD_BATCH_CLI_USER, NUMELE(SD_BATCH_CLI_USER), &sdb_batch_cli_user, sErrmsg);

    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        sql_RollbackTrans();
        fpub_SetMsg(lXmlhandle,MID_BATCH_INS_PLRW,MSG_BATCH_INS_PLRW);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }                
    if( sql_CommitTrans() !=MID_SYS_SUCC )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /* modified by yangdong 20151105 统一为客户编号
    COMP_SOFTSETXML(XMLNM_BATCH_RESP_DWBH,sdb_batch_cli_user.user_id)
    */
    COMP_SOFTSETXML(XMLNM_BATCH_RESP_KHBH,sdb_batch_cli_user.user_id)

    COMP_SOFTSETXML(XMLNM_BATCH_RESP_XYBH,sdb_batch_cli_user.contract_no)
    COMP_SOFTSETXML(XMLNM_BATCH_RESP_KEY,sKey)

    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG")

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}

/************************************************************************
动态组件函数定义
组件函数名称:SBATCH_GET_CLIKEY
组件名称:BATCH_GET_CLIKEY
组件功能:获取批量客户端KEY信息
组件参数:
 序号 参数类型    参数名称                 资源类别         缺省值    可空    参数说明        
    
使用限制:
程 序 员: 
发布日期:
修改日期:
参数使用示例:
************************************************************************/
IRESULT SBATCH_GET_CLIKEY(HXMLTREE lXmlhandle)
{
    char sBuf[255];
    char sTmp[4+1];
    char sbuf[2+1];
    int  iParas;
    int  i = -1;
    char sSql1[1024];
    char sErrmsg[256];
    int iRet =-1;

    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG")

    memset(&sdb_batch_cli_user,0,sizeof(sdb_batch_cli_user));

    /*客户编号*/
    memset(sBuf,0,sizeof(sBuf));
    memset(sKhbh,0,sizeof(sKhbh));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_DWBH,sBuf);
    trim( sBuf );
    pstrcopy( sKhbh,sBuf,sizeof(sKhbh));
    iSend = 0;
    if(  strlen( sBuf ) > 0 ) 
    {
        snprintf( sSql1, sizeof( sSql1 ),"SELECT key, send_flag FROM batch_cli_user WHERE user_id='%s'", sKhbh );
    }
    else /* 未传入客户编号，按协议编号查询 */
    {
        memset(sBuf,0,sizeof(sBuf));
        memset(sXybh,0,sizeof(sXybh));
        COMP_SOFTGETXML(XMLNM_BATCH_REQ_XYBH,sBuf);
        trim( sBuf );
        pstrcopy( sXybh,sBuf,sizeof(sXybh));
        if(  strlen( sBuf ) > 0 )
        {
            snprintf( sSql1, sizeof( sSql1 ), "SELECT key, send_flag FROM batch_cli_user WHERE contract_no='%s'", sXybh );
        }
        else /* 未传入单位编号,协议编号*/
        {
             /* modified by yangdong 20150909 接口未传入，获取单位编号 
             fpub_SetMsg(lXmlhandle,MID_BATCH_NULL_CLI_BH,MSG_BATCH_NULL_CLI_BH);
             fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
             return COMPRET_FAIL;
             */
             memset(sBuf,0,sizeof(sBuf));
             COMP_SOFTGETXML(XMLNM_APP_DWCPXY_DWBH,sBuf);
             snprintf( sSql1, sizeof( sSql1 ),"SELECT key, send_flag FROM batch_cli_user WHERE user_id='%s'", sBuf );
        }
    }
    iRet = DBSelectToVarChar(sErrmsg, sBuf, sSql1);
    if( iRet < 1 )
    {
        if( iRet == 0 )
            fpub_SetMsg(lXmlhandle,MID_BATCH_NO_CLIINFO,MSG_BATCH_NO_CLIINFO);
        else
            fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return -1;
    }
    /* 解密 */
    memset( sKey, 0x00, sizeof( sKey ) );
    memset( sTmp, 0x00, sizeof( sTmp ) );
    hex2bytes( sBuf, sTmp);
    i = des_DECRYPT( BAT_KEYKEY, (unsigned char *)sKey,(unsigned char *)sTmp, 8 );    

    iSend += 1;
    /* 修改发送次数 */

    snprintf( sSql1, sizeof( sSql1 ) , "UPDATE batch_cli_user SET send_flag= %d \
                        WHERE user_id='%s' OR contract_no='%s'", iSend,  sKhbh, sXybh );
    iRet = DCIExecuteDirect( sSql1 );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return -1;
    }

    if( sql_CommitTrans() !=MID_SYS_SUCC )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    COMP_SOFTSETXML(XMLNM_BATCH_RESP_KEY,sKey )
    COMP_SOFTSETXML(XMLNM_BATCH_RESP_SEND, itoa( iSend ) )

    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG")

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}

/************************************************************************
动态组件函数定义
组件函数名称:SBATCH_UPD_CLIINFO
组件名称:BATCH_UPD_CLIINFO
组件功能: 批量客户端信息更新
组件参数:
 序号 参数类型    参数名称                 资源类别         缺省值    可空    参数说明        
    
使用限制:
程 序 员: 
发布日期:
修改日期:
参数使用示例:
************************************************************************/
IRESULT SBATCH_UPD_CLIINFO(HXMLTREE lXmlhandle)
{
    char sBuf[128+1];
    int iSqlLen=0;
    char sStrSetSql[900];
    char sSqlStr[1024];
    char sSqlCond[128];
    int iResult =-1;
    int  Flag=0;    

    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG");

    memset(&sdb_batch_cli_user,0,sizeof(sdb_batch_cli_user));

    /*客户编号*/
    memset(sBuf,0,sizeof(sBuf));
    memset(sKhbh,0,sizeof(sKhbh));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_DWBH,sBuf);
    trim( sBuf );
    pstrcopy(sdb_batch_cli_user.user_id,sBuf,sizeof(sdb_batch_cli_user.user_id));
    
    /*协议编号*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_XYBH,sBuf);
    trim( sBuf );
    pstrcopy(sdb_batch_cli_user.contract_no,sBuf,sizeof(sdb_batch_cli_user.contract_no));

    memset( sSqlCond, 0x00, sizeof( sSqlCond ) );
    if(  strlen( sdb_batch_cli_user.user_id ) > 0 )
    {
        sprintf( sSqlCond, " WHERE user_id='%s'", sdb_batch_cli_user.user_id );
    }
    else if(  strlen( sdb_batch_cli_user.contract_no ) > 0 )
    {
        sprintf( sSqlCond, " WHERE contract_no='%s'", sdb_batch_cli_user.contract_no );
    }
    else /* 未传入单位编号,协议编号*/
    {

        /* modified by yangdong 20150909
        接口未传入，获取单位编号
        fpub_SetMsg(lXmlhandle,MID_BATCH_NULL_CLI_BH,MSG_BATCH_NULL_CLI_BH);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
        */
        memset(sBuf,0,sizeof(sBuf));
        COMP_SOFTGETXML(XMLNM_APP_DWCPXY_DWBH,sBuf);
        if( strlen( sBuf ) < 1 )
            sprintf( sSqlCond, " WHERE user_id='%s'", sBuf);
        else
        {
            memset(sBuf,0,sizeof(sBuf));
            COMP_SOFTGETXML(XMLNM_BATCH_REQ_YWBH,sBuf);
            trim( sBuf );
            pstrcopy(sdb_batch_cli_user.contract_no,sBuf,sizeof(sdb_batch_cli_user.contract_no));
            sprintf( sSqlCond, " WHERE contract_no='%s'", sdb_batch_cli_user.contract_no );
        }
    }
    
    /*联系人*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_LXR,sBuf);
    trim( sBuf );
    pstrcopy(sdb_batch_cli_user.contact,sBuf,sizeof(sdb_batch_cli_user.contact));
    
    /*电话号码*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_DHHM,sBuf);
    trim( sBuf );
    pstrcopy(sdb_batch_cli_user.phone,sBuf,sizeof(sdb_batch_cli_user.phone));
    
    /*手机号码*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_SJHM,sBuf);
    trim( sBuf );
    pstrcopy(sdb_batch_cli_user.mobile,sBuf,sizeof(sdb_batch_cli_user.mobile));
    
    /*email*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_EMAIL,sBuf);
    trim( sBuf );
    pstrcopy(sdb_batch_cli_user.email,sBuf,sizeof(sdb_batch_cli_user.email));

    /*签约账号*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_QYZH,sBuf);
    trim( sBuf );
    pstrcopy(sdb_batch_cli_user.acct_no,sBuf,sizeof(sdb_batch_cli_user.acct_no));

    /*签约户名*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_QYHM,sBuf);
    trim( sBuf );
    pstrcopy(sdb_batch_cli_user.acct_name,sBuf,sizeof(sdb_batch_cli_user.acct_name));

    /*扩展信息*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_EXTFLD1,sBuf);
    trim( sBuf );
    pstrcopy(sdb_batch_cli_user.extfld1,sBuf,sizeof(sdb_batch_cli_user.extfld1));
    
    /*扩展信息*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_EXTFLD2,sBuf);
    trim( sBuf );
    pstrcopy(sdb_batch_cli_user.extfld2,sBuf,sizeof(sdb_batch_cli_user.extfld2));
    
    /*扩展信息*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_EXTFLD3,sBuf);
    trim( sBuf );
    pstrcopy(sdb_batch_cli_user.extfld3,sBuf,sizeof(sdb_batch_cli_user.extfld3));
    
    /*扩展信息*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_EXTFLD4,sBuf);
    trim( sBuf );
    pstrcopy(sdb_batch_cli_user.extfld4,sBuf,sizeof(sdb_batch_cli_user.extfld4));
    
    memset(sStrSetSql,0,sizeof(sStrSetSql));
    iSqlLen = 0;
    
    /*联系人*/
    if(  strlen( sdb_batch_cli_user.contact ) > 0 )
    {
        sprintf(sStrSetSql+iSqlLen, " contact='%s',",sdb_batch_cli_user.contact);
        iSqlLen = strlen(sStrSetSql);
        Flag++;
    }
    
    /*电话号码*/
    if(  strlen( sdb_batch_cli_user.phone ) > 0 )
    {
        sprintf(sStrSetSql+iSqlLen, "phone='%s',", sdb_batch_cli_user.phone);
        iSqlLen = strlen(sStrSetSql);
        Flag++;
    }
    
    /*手机号码*/
    if(  strlen( sdb_batch_cli_user.mobile ) > 0 )
    {
        sprintf(sStrSetSql+iSqlLen, "mobile='%s',", sdb_batch_cli_user.mobile);
        iSqlLen = strlen(sStrSetSql);
        Flag++;
    }
    
    /*email*/
    if(  strlen( sdb_batch_cli_user.email ) > 0 )
    {
        sprintf(sStrSetSql+iSqlLen, "email='%s',",    sdb_batch_cli_user.email);
        iSqlLen = strlen(sStrSetSql);
        Flag++;
    }
    
    /*签约账号*/
    if(  strlen( sdb_batch_cli_user.acct_no ) > 0 )
    {
        sprintf(sStrSetSql+iSqlLen, "acct_no='%s',",    sdb_batch_cli_user.acct_no );
        iSqlLen = strlen(sStrSetSql);
        Flag++;
    }
    
    /*签约户名*/
    if(  strlen( sdb_batch_cli_user.acct_name ) > 0 )
    {
        sprintf(sStrSetSql+iSqlLen, "acct_name ='%s',",    sdb_batch_cli_user.acct_name );
        iSqlLen = strlen(sStrSetSql);
        Flag++;
    }

    /*extfld*/
    if(  strlen( sdb_batch_cli_user.extfld1 ) > 0 )
    {
        sprintf(sStrSetSql+iSqlLen, "extfld1 ='%s',",    sdb_batch_cli_user.extfld1 );
        iSqlLen = strlen(sStrSetSql);
        Flag++;
    }
    
    /*extfld*/
    if(  strlen( sdb_batch_cli_user.extfld2 ) > 0 )
    {
        sprintf(sStrSetSql+iSqlLen, "extfld2 ='%s',",    sdb_batch_cli_user.extfld2 );
        iSqlLen = strlen(sStrSetSql);
        Flag++;
    }

    /*extfld*/
    if(  strlen( sdb_batch_cli_user.extfld3 ) > 0 )
    {
        sprintf(sStrSetSql+iSqlLen, "extfld3 ='%s',",    sdb_batch_cli_user.extfld3 );
        iSqlLen = strlen(sStrSetSql);
        Flag++;
    }
    /*extfld*/
    if(  strlen( sdb_batch_cli_user.extfld4 ) > 0 )
    {
        sprintf(sStrSetSql+iSqlLen, "extfld4 ='%s',",    sdb_batch_cli_user.extfld4 );
        iSqlLen = strlen(sStrSetSql);
        Flag++;
    }
    if(Flag==0)
    {
        LOG(LM_STD,Fmtmsg("缺少需要更新的数据"),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_BATCH_UPD_CLIINFO,MSG_BATCH_UPD_CLIINFO);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }        
    /* 去最后一个，*/
    sStrSetSql[iSqlLen-1] = '\0'; 
     
    /* 动态SQL实现 */
    memset(sSqlStr, 0, sizeof(sSqlStr));
    snprintf(sSqlStr,sizeof(sSqlStr),"update batch_cli_user set %s  %s",sStrSetSql, sSqlCond );

    /*sql_BeginTrans(); 用DCIBegin代替 2015-1-7 by chenxm */
    DCIBegin();
    
    if( sql_DynExec(sSqlStr,&iResult) !=0 || iResult<=0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        /*sql_RollbackTrans();*/
        DCIRollback();
        
        fpub_SetMsg(lXmlhandle,MID_BATCH_UPD_CLIINFO,MSG_BATCH_UPD_CLIINFO);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    /*if( sql_CommitTrans() != MID_SYS_SUCC )*/
    if(DCICommit() != 0)
    {
        DCIRollback();
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);

    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG")

    return COMPRET_SUCC;
}

/************************************************************************
动态组件函数定义
组件函数名称:SBATCH_QUY_CLIINFO
组件名称:BATCH_QUY_CLIINFO
组件功能: 批量客户端信息查询
组件参数:
 序号 参数类型    参数名称                 资源类别         缺省值    可空    参数说明        
    
使用限制:
程 序 员: 
发布日期:
修改日期:
参数使用示例:
************************************************************************/
IRESULT SBATCH_QUY_CLIINFO(HXMLTREE lXmlhandle)
{
    char sBuf[128+1];
    char sXmlnode[128+1];
    int iSqlLen=0;
    char sStrQuyCond[512];
    char sSqlStr[1024];
    /*int iResult =-1;*/
    int  Flag=0;
    char str[3+1];
    int  iCount = 0;
    CURSOR cur; 
    char sSql1[1024];
    char sErrmsg[256];
    int iRet =-1;

    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG");

    memset(&sdb_batch_cli_user,0,sizeof(sdb_batch_cli_user));
    
    /*协议编号*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_XYBH,sBuf);
    trim( sBuf );
    pstrcopy(sdb_batch_cli_user.contract_no,sBuf,sizeof(sdb_batch_cli_user.contract_no));
    
    /*客户编号*/
    memset(sBuf,0,sizeof(sBuf));
    /* modified by 杨东20151105  修改为客户编号，与接口文档一致
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_DWBH,sBuf);
    */
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_KHBH,sBuf);

    trim( sBuf );
    pstrcopy(sdb_batch_cli_user.user_id,sBuf,sizeof(sdb_batch_cli_user.user_id));
    
    /*登记日期*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_DJRQ,sBuf);
    trim( sBuf );
    pstrcopy(sdb_batch_cli_user.ptrq,sBuf,sizeof(sdb_batch_cli_user.ptrq));

    /* added by 杨东20151104 */
    /* 增加客户账号作为查询条件 */
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_QYZH,sBuf);
    trim( sBuf );
    pstrcopy(sdb_batch_cli_user.acct_no,sBuf,sizeof(sdb_batch_cli_user.acct_no));
    
    /*客户名称*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_KHMC,sBuf);
    trim( sBuf );
    pstrcopy(sdb_batch_cli_user.user_name,sBuf,sizeof(sdb_batch_cli_user.user_name));
    
    /*协议编号*/
    if(  strlen( sdb_batch_cli_user.contract_no ) > 0 )
    {
        sprintf(sStrQuyCond+iSqlLen, "  contract_no='%s' AND ",    sdb_batch_cli_user.contract_no);
        iSqlLen = strlen(sStrQuyCond);
        Flag++;
    }
    
    /*客户编号*/
    if(  strlen( sdb_batch_cli_user.user_id ) > 0 )
    {
        sprintf(sStrQuyCond+iSqlLen, " user_id='%s' AND ",    sdb_batch_cli_user.user_id);
        iSqlLen = strlen(sStrQuyCond);
        Flag++;
    }
    
    /*登记日期*/
    if(  strlen( sdb_batch_cli_user.ptrq ) > 0 )
    {
        sprintf(sStrQuyCond+iSqlLen, " ptrq='%s' AND ",    sdb_batch_cli_user.ptrq);
        iSqlLen = strlen(sStrQuyCond);
        Flag++;
    }

    /*客户账号 */
    if(  strlen( sdb_batch_cli_user.acct_no) > 0 )
    {
        sprintf(sStrQuyCond+iSqlLen, " acct_no='%s' AND ",    sdb_batch_cli_user.acct_no );
        iSqlLen = strlen(sStrQuyCond);
        Flag++;
    }
    
    /*客户名称*/
    if(  strlen( sdb_batch_cli_user.user_name ) > 0 )
    {
        sprintf(sStrQuyCond+iSqlLen, " user_name like '%%%s%%' AND ",sdb_batch_cli_user.user_name);
        iSqlLen = strlen(sStrQuyCond);
        Flag++;
    }
    
    if(Flag==0)
    {
        LOG(LM_STD,Fmtmsg("缺少搜索条件",fpub_GetCompname(lXmlhandle)),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_BATCH_QUYCON,MSG_BATCH_QUYCON);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }        

    memset(sSqlStr, 0, sizeof(sSqlStr));
    snprintf(sSqlStr,sizeof(sSqlStr),"SELECT * FROM batch_cli_user WHERE %s ROWNUM<100   ",sStrQuyCond);
    /* added by 杨东20151104 */
    if ((cur = DCIDeclareCursor(sSqlStr, DCI_STMT_LOCATOR)) == -1)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    if (DCIExecute(cur) == -1)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    /* end of add */

    while( ( iRet = DBFetch(cur, SD_BATCH_CLI_USER, NUMELE(SD_BATCH_CLI_USER), &sdb_batch_cli_user, sErrmsg ) ) > 0 )
    {
        iCount ++;
        /*协议编号*/
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "/batch/resp|%d/xybh", iCount );
        trim(sdb_batch_cli_user.contract_no);
        COMP_SOFTSETXML(sXmlnode, sdb_batch_cli_user.contract_no);

        /*客户编号*/
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "/batch/resp|%d/khbh", iCount );
        trim(sdb_batch_cli_user.user_id);
        COMP_SOFTSETXML(sXmlnode, sdb_batch_cli_user.user_id);

        /*客户名称*/
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "/batch/resp|%d/khmc", iCount );
        trim(sdb_batch_cli_user.user_name);
        COMP_SOFTSETXML(sXmlnode, sdb_batch_cli_user.user_name);

        /*联系人*/
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "/batch/resp|%d/lxr", iCount );
        trim(sdb_batch_cli_user.contact);
        COMP_SOFTSETXML(sXmlnode, sdb_batch_cli_user.contact);

        /*联系人电话*/
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "/batch/resp|%d/dhhm", iCount );
        trim(sdb_batch_cli_user.phone);
        COMP_SOFTSETXML(sXmlnode, sdb_batch_cli_user.phone);

        /*联系人手机号码*/
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "/batch/resp|%d/sjhm", iCount );
        trim(sdb_batch_cli_user.mobile);
        COMP_SOFTSETXML(sXmlnode, sdb_batch_cli_user.mobile);

        /*联系人email*/
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "/batch/resp|%d/email", iCount );
        trim(sdb_batch_cli_user.email);
        COMP_SOFTSETXML(sXmlnode, sdb_batch_cli_user.email);

        /*登记日期*/
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "/batch/resp|%d/djrq", iCount );
        trim(sdb_batch_cli_user.ptrq);
        COMP_SOFTSETXML(sXmlnode, sdb_batch_cli_user.ptrq); 

        /*登记时间*/
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "/batch/resp|%d/djsj", iCount );
        trim(sdb_batch_cli_user.tran_time);
        COMP_SOFTSETXML(sXmlnode, sdb_batch_cli_user.tran_time); 

        /*平台流水*/
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "/batch/resp|%d/ptls", iCount );
        trim(sdb_batch_cli_user.ptls);
        COMP_SOFTSETXML(sXmlnode, sdb_batch_cli_user.ptls); 

        /*交易机构*/
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "/batch/resp|%d/jyjg", iCount );
        trim(sdb_batch_cli_user.branch);
        COMP_SOFTSETXML(sXmlnode, sdb_batch_cli_user.branch); 

        /*交易柜员*/ 
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "/batch/resp|%d/jygy", iCount );
        trim(sdb_batch_cli_user.oper);
        COMP_SOFTSETXML(sXmlnode, sdb_batch_cli_user.oper); 

        /*客户经理*/
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "/batch/resp|%d/khjl", iCount );
        trim(sdb_batch_cli_user.acct_manager);
        COMP_SOFTSETXML(sXmlnode, sdb_batch_cli_user.acct_manager); 

        /*签约户名*/
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "/batch/resp|%d/qyhm", iCount );
        trim(sdb_batch_cli_user.acct_name);
        COMP_SOFTSETXML(sXmlnode, sdb_batch_cli_user.acct_name);                           

        /*签约帐号*/
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "/batch/resp|%d/qyzh", iCount );
        trim(sdb_batch_cli_user.acct_no);
        COMP_SOFTSETXML(sXmlnode, sdb_batch_cli_user.acct_no); 

        /*签约状态*/
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "/batch/resp|%d/qyzt", iCount );
        trim(sdb_batch_cli_user.status);
        COMP_SOFTSETXML(sXmlnode, sdb_batch_cli_user.status); 

        /*发送标志*/
        sprintf(str,"%d",sdb_batch_cli_user.send_flag); 
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "/batch/resp|%d/fsbz", iCount );
        trim(str);
        COMP_SOFTSETXML(sXmlnode, str); 

        /*扩展字段1*/
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "/batch/resp|%d/kzzd1", iCount );
        trim(sdb_batch_cli_user.extfld1);
        COMP_SOFTSETXML(sXmlnode, sdb_batch_cli_user.extfld1); 

        /*扩展字段2*/
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "/batch/resp|%d/kzzd2", iCount );
        trim(sdb_batch_cli_user.extfld2);
        COMP_SOFTSETXML(sXmlnode, sdb_batch_cli_user.extfld2); 

        /*扩展字段3*/
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "/batch/resp|%d/kzzd3", iCount );
        trim(sdb_batch_cli_user.extfld3);
        COMP_SOFTSETXML(sXmlnode, sdb_batch_cli_user.extfld3); 

        /*扩展字段4*/
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "/batch/resp|%d/kzzd4", iCount );
        trim(sdb_batch_cli_user.extfld4);
        COMP_SOFTSETXML(sXmlnode, sdb_batch_cli_user.extfld4); 

        memset( &sdb_batch_cli_user,0,sizeof( sdb_batch_cli_user ));
    }
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sql[%s]sqlerr[%s]",sSqlStr,DCILastError() ),"ERROR")
        DCIFreeCursor(cur);
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    DCIFreeCursor(cur);

    /* 查询返回记录数 */
    sprintf(str,"%d",iCount); 
    COMP_SOFTSETXML(XMLNM_BATCH_RESP_COUNT, str); 

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    
    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG")

    return COMPRET_SUCC;
}
