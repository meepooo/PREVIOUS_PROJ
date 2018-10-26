#include <openssl/evp.h>
#include <time.h>
#include <openssl/stack.h>
#include <openssl/err.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/x509.h>
#include <openssl/x509v3.h>
#include <openssl/pkcs12.h>
#include <openssl/pkcs7.h>
#include <openssl/err.h>

#include "server.h"
#include "gaps_head.h"

int wzj_checkchar(char cin)
{
	if ( cin >= 48 && cin <= 57 )
		return cin-48 ;
	else if ( cin >= 65 && cin <= 70 )
		return cin-55 ;
	else if ( cin >= 97 && cin <= 102 )
		return cin-87 ;
	else
		return 0;
}

int wzj_char2hex(char *in, int in_len, char *out, int *out_len, int flag)
{
	int i=0;
	char highc,lowc;
	if ( flag!=1)
	{
		return -1;
	}
	
	for(i=0;i<in_len;)
	{
		out[i/2]=(wzj_checkchar(in[i]))*16 + wzj_checkchar(in[i+1]);
		i+=2 ;
	}
	*out_len=i/2;

	return 0;
}

/*生成ca码*/
int prv_genca_wzj(HXMLTREE lXmlhandle,char *commbuf, int isize, char *out, int *out_len, char *infile, char *algo)
{
    char *pstr;
    char spath[100],spath2[100],spfx[100],sfile_pfx[100];
    char sdllname[100],sfunc_name[100],sdllpath[100];
    int  iret,ilen,outlen,i;
    char sbuf_ret[10240+1];
    char sinifile[100];
    char scamm[256];
    char scamm2[256];
    char sBuf[256];
    char sGenCa[1+1];

    memset(sinifile, 0x00, sizeof(sinifile));
    snprintf(sinifile, sizeof(sinifile), "%s/%s", getenv("HOME"), infile);

    memset(spath2, 0x00, sizeof(spath2));
    /*获取数字证书路径*/
    if(ExGetCfgItem(sinifile,"CA_PFX","CAPATH",spath2,sizeof(spath2))<0)
    {
        ErrLogF(__FILE__,__LINE__,"--获取参数失败[%s][%s]--","CA_PFX","CAPATH");
        return -5;
    }
    memset(spath, 0x00, sizeof(spath));
    if ( spath2[0] != '/')
    {
        snprintf(spath, sizeof(spath), "%s/%s", getenv("HOME"), spath2);
    }else
    {
        pstrcopy(spath, spath2, sizeof(spath));
    }

    /* add by tuql 20100107 增加GENCA标志位，用于控制是否生成CA */
    memset(sBuf, 0x00, sizeof(sBuf));
    /*获取生成ca标志*/
    if(ExGetCfgItem(sinifile,"CA_PFX","GENCA",sBuf,sizeof(sBuf))<0)
    {
        ErrLogF(__FILE__,__LINE__,"--参数[%s][%s]不存在,缺省为1-生成CA--","CA_PFX","GENCA");
        sBuf[0]='1';
    }
    memset(sGenCa, 0x00, sizeof(sGenCa));
    sGenCa[0] = sBuf[0];

    /* 判断是否生成CA */
    if(sGenCa[0]=='0')
    {
       ErrLogF(__FILE__,__LINE__,"设置[%s][%s]值为[%s]-不生成CA--","CA_PFX","GENCA", sGenCa);
       iret=strlen(commbuf);
           return iret;
    }

    pstr = (char *)strstr(commbuf,"<!--");
    if (pstr != NULL)
    {
        pstr = 0;
    }

    memset(spfx, 0x00, sizeof(spfx));
    /*获取生成ca码要用到的数字证书名称 mod by tuql 20100107 GENCAPFX-->CAPFX*/
    if(ExGetCfgItem(sinifile,"CA_PFX","CAPFX",spfx,sizeof(spfx))<0)
    {
        ErrLogF(__FILE__,__LINE__,"--获取参数失败[%s][%s]--","CA_PFX","CAPFX");
        return -6;
    }

    memset(sfile_pfx, 0x00, sizeof(sfile_pfx));
    snprintf(sfile_pfx, sizeof(sfile_pfx), "%s/%s", spath, spfx);
    ErrLogF(__FILE__,__LINE__,"-prv_genca-sfile_pfx=[%s]--",sfile_pfx);
    memset(sbuf_ret,0x00,sizeof(sbuf_ret));

    sprintf(sfunc_name,"ca_createSign");

    memset(sdllname, 0x00, sizeof(sdllname));
    /*获取生成及校验ca码的动态库名称*/
    if(ExGetCfgItem(sinifile,"CA_PFX","CASHLIB",sdllname,sizeof(sdllname))<0)
    {
        ErrLogF(__FILE__,__LINE__,"--获取参数[%s][%s]失败,缺省为:func_ca.so--","CA_PFX","CASHLIB");
        strcpy(sdllname, "func_ca.so");
    }

    memset(scamm, 0x00, sizeof(scamm));
    /*获取CA证书密码*/
    if(ExGetCfgItem(sinifile,"CA_PFX","CAMM",scamm,sizeof(scamm))<0)
    {
        ErrLogF(__FILE__,__LINE__,"--获取参数失败[%s][%s]--","CA_PFX","CAMM");
        return -8;
    }
    memset(scamm2, 0x00, sizeof(scamm2));
    iret=gaps_encode(1, scamm ,scamm2,sizeof(scamm2));
    if(iret!=0)
    {
        ErrLogF(__FILE__,__LINE__,"--解密证书密码失败[%d][%s]--",iret,scamm);
        return -9;
    }

     EVP_PKEY *key=NULL;
     X509 *cert=NULL;
     BIO *bio=NULL;
     STACK_OF(X509) *ca = NULL;
     PKCS12 *p12=NULL;      

     if((bio=BIO_new_file((const char *)sfile_pfx, "r")) == NULL)
     {
        ErrLogF(__FILE__,__LINE__,"--BIO_new_file失败--");
	return -10;
     }
     SSLeay_add_all_algorithms();
     p12 = d2i_PKCS12_bio(bio, NULL);
     if (!PKCS12_parse(p12, (const char *)scamm2, &key, &cert, &ca)) 
     {      
        ErrLogF(__FILE__,__LINE__,"--BIO_new_file失败--");
	return -11;
     }
     BIO_free(bio);

    iret=do_sign((const char*)algo, (unsigned char*)out, (unsigned int*)&outlen, (EVP_PKEY*)key, (const char*)commbuf, strlen(commbuf));
    if ( iret < 0 )
    {
        ErrLogF(__FILE__,__LINE__,"--do_sign失败--");
	return -12;
    }

    memcpy(sbuf_ret,out,outlen);
    for ( i=0; i<outlen; i++ )
    {
	sprintf(out+i*2, "%02X", (unsigned char)sbuf_ret[i]);
    }

     *out_len=outlen*2;
     return outlen ;
}

int prv_checkca_wzj(HXMLTREE lXmlhandle, char *commbuf, int isize, char *sign_buf, int sign_len, char *infile, char *algo)
{
    char *pstr;
    char spath[100],spath2[100],spfx[100],sfile_pfx[100];
    char sdllname[100],sfunc_name[100],sdllpath[100];
    int  iret,ilen;
    char outbuf[2048];
    int  len_buf, outlen;
    char sinifile[100];
    char scamm[256];
    char scamm2[256];
    char sBuf[256];
    char sChkCa[1+1];

    memset(sinifile, 0x00, sizeof(sinifile));
    snprintf(sinifile, sizeof(sinifile), "%s/%s", getenv("HOME"), infile);

    memset(spath2, 0x00, sizeof(spath2));
    /*获取数字证书路径*/
    if(ExGetCfgItem(sinifile,"CA_PFX","CAPATH",spath2,sizeof(spath2))<0)
    {   
        ErrLogF(__FILE__,__LINE__,"--获取参数失败[%s][%s]--","CA_PFX","CAPATH");
        return -5;
    }
    memset(spath, 0x00, sizeof(spath));
    if ( spath2[0] != '/')
    {
        snprintf(spath, sizeof(spath), "%s/%s", getenv("HOME"), spath2);
    }else
    {
        pstrcopy(spath, spath2, sizeof(spath));
    }
    /* add by tuql 20100107 增加CHKCA标志位，用于控制是否校验CA */
    memset(sBuf, 0x00, sizeof(sBuf));
    /*获取校验ca标志*/
    if(ExGetCfgItem(sinifile,"CA_PFX","CHKCA",sBuf,sizeof(sBuf))<0)
    {
        ErrLogF(__FILE__,__LINE__,"--参数[%s][%s]不存在,缺省为1-校验CA--","CA_PFX","CHKCA");
        sBuf[0]='1';
    }
    memset(sChkCa, 0x00, sizeof(sChkCa));
    sChkCa[0] = sBuf[0];

    /* 判断是否校验CA */
    if(sChkCa[0]=='0')
    {
       ErrLogF(__FILE__,__LINE__,"设置[%s][%s]值为[%s]-不校验CA--","CA_PFX","CHKCA", sChkCa);
       return 0;
    }

    memset(spfx, 0x00, sizeof(spfx));
    /*获取校验ca码要用到的数字证书名称 mod by tuql 20100107 CHKCAPFX-->CAPFX*/
    if(ExGetCfgItem(sinifile,"CA_PFX","CAPFX",spfx,sizeof(spfx))<0)
    {
        ErrLogF(__FILE__,__LINE__,"--获取参数失败[%s][%s]--","CA_PFX","CAPFX");
        return -6;
    }

    memset(sfile_pfx, 0x00, sizeof(sfile_pfx));
    snprintf(sfile_pfx, sizeof(sfile_pfx), "%s/%s", spath, spfx);

    memset(sdllname, 0x00, sizeof(sdllname));
    /*获取生成及校验ca码的动态库名称*/
    if(ExGetCfgItem(sinifile,"CA_PFX","CASHLIB",sdllname,sizeof(sdllname))<0)
    {
        ErrLogF(__FILE__,__LINE__,"--获取参数[%s][%s]失败,缺省为:func_ca.so--","CA_PFX","CASHLIB");
        strcpy(sdllname, "func_ca.so");
    }

    memset(scamm, 0x00, sizeof(scamm));
    /*获取CA证书密码*/
    if(ExGetCfgItem(sinifile,"CA_PFX","CAMM",scamm,sizeof(scamm))<0)
    {
        ErrLogF(__FILE__,__LINE__,"--获取参数失败[%s][%s]--","CA_PFX","CAMM");
        return -8;
    }
    memset(scamm2, 0x00, sizeof(scamm2));
    iret=gaps_encode(1, scamm ,scamm2,sizeof(scamm2));
    if(iret!=0)
    {
        ErrLogF(__FILE__,__LINE__,"--解密证书密码失败[%d][%s]--",iret,scamm);
        return -9;
    }

    if (commbuf[strlen(commbuf)-1] == '\n')
        commbuf[strlen(commbuf)-1] = 0;
    len_buf=strlen(commbuf);

     EVP_PKEY *key=NULL;
     X509 *cert=NULL;
     BIO *bio=NULL;
     STACK_OF(X509) *ca = NULL;
     PKCS12 *p12=NULL;      

     if((bio=BIO_new_file((const char *)sfile_pfx, "r")) == NULL)
     {
        ErrLogF(__FILE__,__LINE__,"--BIO_new_file失败--");
	return -10;
     }
     SSLeay_add_all_algorithms();
     p12 = d2i_PKCS12_bio(bio, NULL);
     if (!PKCS12_parse(p12, (const char *)scamm2, &key, &cert, &ca)) 
     {      
        ErrLogF(__FILE__,__LINE__,"--BIO_new_file失败--");
	return -11;
     }
     BIO_free(bio);

     wzj_char2hex(sign_buf, strlen(sign_buf), outbuf, &outlen, 1);
     memcpy(sign_buf,outbuf,outlen);
     sign_len=outlen;

     iret=do_verify((const char*)algo, (unsigned char*)sign_buf, sign_len, (EVP_PKEY*)key, (unsigned char*)commbuf, len_buf);
    if ( iret < 0 )
    {
        ErrLogF(__FILE__,__LINE__,"--do_verify失败--");
	return -12;
    }

     return iret;
}

static void init_openssl() {
     static int openssl_inited = 0;
     if (!openssl_inited) {
	  ERR_load_crypto_strings();
	  OpenSSL_add_all_digests();
	  OpenSSL_add_all_ciphers();
	  openssl_inited = 1;
     }
}

/* 签名
 ** input:
 ** 证书, pem格式, 解析字符串
 ** 摘要算法, 字符串
 ** 待签名串, 16进制
 ** output:
 ** 签名, 16进制
 **
 ***/
int do_sign(const char* algo, unsigned char* out, unsigned int* out_len, EVP_PKEY* pkey, const char* text, int text_len)
{
  const EVP_MD* md;
  EVP_MD_CTX *md_ctx;
  int err;

  md = EVP_get_digestbyname(algo);
  if (!md) {
//    ErrLogF(__FILE__, __LINE__, "未知摘要算法");
    return -1;
  }
  md_ctx = EVP_MD_CTX_create();

  EVP_SignInit(md_ctx, md);
  EVP_SignUpdate(md_ctx, text, text_len);
  err = EVP_SignFinal(md_ctx, out, out_len, pkey);

  EVP_MD_CTX_destroy(md_ctx);
  char errbuf[1024];
  if (err != 1) {
//    ErrLogF(__FILE__, __LINE__, "签名失败: %s", errbuf);
    return -1;
  }

  return 0;
}

int do_verify(const char* algo,
              unsigned char* sigbuf,
              int siglen,
              EVP_PKEY* pkey,
              unsigned char* text,
              int text_len)
{
  const EVP_MD *md;
  EVP_MD_CTX *md_ctx;
  int err;

  md = EVP_get_digestbyname(algo);
  if (!md) {
//    ErrLogF(__FILE__, __LINE__, "未知摘要算法: %s", algo);
    return -1;
  }

  char errbuf[1024];
  md_ctx = EVP_MD_CTX_create();
  EVP_MD_CTX_init(md_ctx);
  err = EVP_VerifyInit(md_ctx, md);
  if (err != 1) {
    return -1;  }
  err = EVP_VerifyUpdate(md_ctx, text, text_len);
  if (err != 1) {
    return -1;  }
  err = EVP_VerifyFinal(md_ctx, sigbuf, siglen, pkey);
  if (err != 1) {
    return -1;  }
  
  EVP_MD_CTX_destroy(md_ctx);
//  ErrLogF(__FILE__, __LINE__, "验证失败: %s", errbuf);
  return 0;
}
  

/*
int main()
{
	char commbuf[10240]="head_business_id=1545121381909&head_msg_version=1.0&head_req_date=20180122&head_req_time=0122154512&head_rev_organ=402602000018&head_snd_organ=402602000018&head_tran_name=100011";
	char sign_buf[10240]="7C5B21637FA074C95FAC57F429B28C52202F4F86CEEA7FEC1D961E0F22F8A1C335338BDB481952E3E993C841F8FFDA7F99DB288320DF03C0CB67398F674DB019E354FF465334025513B8D4A47B85170533EEA6B8AA9D088F6AE23A311189F4FA312782C7CFEB8E5EBDFF1EB980511E04E081591A95F5B300FCEC7784FFE41205C08BB60AD2B9E533C119A6721F8675C2285C3769C6EB06ADABB71F8FAA1EB7C076EB8ECE75B2682C1C2F57E87F1FF43BD50E92DDC827272A4D1FBA7A3A7D7F96596C21505D7CC0D4CA406BA8988098DA53BC8A0C79ED3C012E158E6A7A4FE99451886156355A13BBB9EBEB1945DE564C5AF54427BEED3DF3E03EFA3DD8F8CAA5";
	int *ilen_buf ;
	char spath[60] ;
	char sfile[60] ;
	char scamm[60] ;
	char buf_ca[1024];
	char out[20480];
	char outhex[20480];
	char algo[]="md5";
	int iRet;

	int out_len;
	int flag=1;

	iRet = prv_genca_wzj(commbuf, sizeof(commbuf), out, &out_len, algo) ;
	printf("commbuf=[%s]iRet[%d]\n",commbuf, iRet) ;
	int i=0 ;
	for (i=0;i<iRet;i++)
        {
		sprintf(outhex+i*2, "%02X", (unsigned char)out[i]);
        }
	printf("outhex:[%s]\n", outhex) ;

	wzj_char2hex(sign_buf, strlen(sign_buf), out, &out_len, flag);
	printf("out[%s][%d]\n", out, out_len ) ;
	printf("out_len[%d]\n", out_len ) ;

	iRet = prv_checkca_wzj(commbuf, sizeof(commbuf), out, out_len, algo) ;
	printf("prv_checkca buf=[%s]\n",out) ;
	printf("iRet=[%d]\n",iRet) ;

	return 0 ;
}
*/
