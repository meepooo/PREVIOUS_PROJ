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

/************************************************************************
动态组件函数定义
组件函数名称:DRC_CASIGN
组件名称:DRC_CASIGN
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
IRESULT DRC_CASIGN(HXMLTREE lXmlhandle)
{
   char scommbufnode[256];
   char szAlgo[256];
   char szDescPath[256];
   char szFilePath[256];
   char sbuf[5],scommbuf[2048];
   int  iParas,ilen_send, iret, ilen_recv;
   char *indata, *outdata;
   long olen;
 
   fpub_InitSoComp(lXmlhandle);

#ifdef DEBUG
   LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),__func__)
#endif

   memset(scommbufnode,0x00,sizeof(scommbufnode));

   COMP_PARACOUNTCHKMIN(4)

   COMP_GETPARSEPARAS(1, scommbuf, "待签名串");
   memset(szAlgo, 0, sizeof(szAlgo));
   COMP_GETPARSEPARAS(2, szAlgo, "算法");
   memset(szDescPath, 0, sizeof(szDescPath));
   COMP_GETPARSEPARAS(3, szDescPath, "目标存放xml节点");
   memset(szFilePath, 0, sizeof(szFilePath));
   COMP_GETPARSEPARAS(4, szFilePath, "签名证书路径");

#ifdef DEBUG
   LOG(LM_STD, Fmtmsg("待签名串:[%s]", scommbuf), "INFO");
   LOG(LM_STD, Fmtmsg("算法:[%s]", szAlgo), "INFO");
   LOG(LM_STD, Fmtmsg("目标存放xml节点:[%s]", szDescPath), "INFO");
   LOG(LM_STD, Fmtmsg("签名证书路径:[%s]", szFilePath), "INFO");
#endif

   outdata =  (char * ) malloc( sizeof(char) * MAX_SOCK_BUF_SIZE);
   if (outdata == NULL)
   {
      free(indata);
      LOG(LM_STD,Fmtmsg("申请内存失败"),"ERROR");
      fpub_SetMsg(lXmlhandle,MID_YW_ERROR,Fmtmsg("签名失败"));
      fpub_SetCompStatus(lXmlhandle,-1);      /*异常时,组件返回-1*/
      return -1;
   }

   ilen_send=strlen(scommbuf);

   iret = prv_genca_wzj(lXmlhandle, scommbuf, ilen_send, outdata, &ilen_recv, szFilePath, szAlgo);
   if (iret<0)
   {
      LOG(LM_STD,Fmtmsg("CA签名失败,iret=[%d]", iret),"ERROR");
      fpub_SetMsg(lXmlhandle,MID_YW_ERROR,Fmtmsg("CA签名失败"));
      fpub_SetCompStatus(lXmlhandle,-1);
      free(outdata);
      free(indata);
      return -1;
   }

   outdata[ilen_recv]='\0';

   xml_SetElement(lXmlhandle, szDescPath, outdata);

   free(outdata);
 
#ifdef DEBUG
   LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)),__func__)
#endif

   fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
   return 0;
}

IRESULT DRC_CAVERIFY(HXMLTREE lXmlhandle)
{
   char scommbufnode[256];
   char szAlgo[256];
   char szDescPath[256];
   char szFilePath[256];
   char sbuf[5],scommbuf[2048], sign_buf[2048];
   int  iParas,ilen_send, iret, sign_len;
   char *indata, *outdata;
   long olen;
 
   fpub_InitSoComp(lXmlhandle);

#ifdef DEBUG
   LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),__func__)
#endif

   memset(scommbufnode,0x00,sizeof(scommbufnode));

   COMP_PARACOUNTCHKMIN(4)

   COMP_GETPARSEPARAS(1, scommbuf, "待签名串");
   memset(szAlgo, 0, sizeof(szAlgo));
   COMP_GETPARSEPARAS(2, szAlgo, "算法");
   memset(sign_buf, 0, sizeof(sign_buf));
   COMP_GETPARSEPARAS(3, sign_buf, "签名串");
   sign_len=strlen(sign_buf);
   memset(szFilePath, 0, sizeof(szFilePath));
   COMP_GETPARSEPARAS(4, szFilePath, "签名证书路径");

#ifdef DEBUG
   LOG(LM_STD, Fmtmsg("待签名串:[%s]", scommbuf), "INFO");
   LOG(LM_STD, Fmtmsg("算法:[%s]", szAlgo), "INFO");
   LOG(LM_STD, Fmtmsg("签名串[%s]", szDescPath), "INFO");
   LOG(LM_STD, Fmtmsg("签名证书路径:[%s]", szFilePath), "INFO");
#endif

   ilen_send=strlen(scommbuf);

   iret=prv_checkca_wzj(lXmlhandle, scommbuf, ilen_send,  sign_buf, sign_len, szFilePath, szAlgo);
   if (iret<0)
   {
      LOG(LM_STD,Fmtmsg("CA签名验证失败,iret=[%d]", iret),"ERROR");
      fpub_SetMsg(lXmlhandle,MID_YW_ERROR,Fmtmsg("CA签名验证失败"));
      fpub_SetCompStatus(lXmlhandle,-1);
      free(outdata);
      free(indata);
      return -1;
   }

#ifdef DEBUG
   LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)),__func__)
#endif

   fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
   return 0;
}
