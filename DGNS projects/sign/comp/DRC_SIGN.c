/********************************************************************
��Ȩ����:���ݺ������ӹɷ����޹�˾
��Ŀ����:�м�ҵ��ƽ̨��Ŀ(AGENT2.0)
��    ��:V3.2
����ϵͳ:
�ļ�����:DRCESB_COMM
�ļ�����:GAPS�붫ݸũ����ESBͨѶ���
�� Ŀ ��:
�� �� Ա:
��������:2015��07��21��
��    ��:
�޸�����:
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
         <sonote>GXPͨѶ�������</sonote>\
         <version>\
           <rec ver=\"4.0.01\" modify=\"2009-6-11 10:43\" programer=\"Wangt Chendh\" filesize=\"70096\">����ΪASPKV4����GXPͨѶ���</rec>\
         </version>\
      </root>";
   printf("\n================��̬���������Ϣ================\n");
   printf("SOCOMPBUILDNO:%s\n",SOCOMPBUILDNO);
   printf("SOCOMPVERSION:%s\n",SOCOMPVERSION);
   printf("%s-%s\n",__PROJECTSNAME,__VERSION);
   if (strlen(sversion) >= isize)
   {
      printf(" -->ȡ��ϸ��Ϣʧ��...\n");
      return -2;
   }
   strcpy(sinfo,sversion);
   printf(" -->��鿴��ϸ��Ϣ...\n");
   return 0;      
}

/************************************************************************
���ܣ�      ȡϵͳ���뼶ʱ��
���룺      ��
�����      long�͵�����
���أ�      ����1970��1��1������ĺ�����
ע�⣺      32λ����long���洢����,ֻ������64λ����
������Ա:   PengLiyang
�޸�����:   2013-08-16
************************************************************************/
long DRC_getMillitmSystemTime()
{
   struct timeb t;
   ftime(&t);
   return 1000*t.time + t.millitm;
}

/************************************************************************
��̬�����������
�����������:DRC_CASIGN
�������:DRC_CASIGN
�������:
�������:
 ��� ��������  ��������         ��Դ���     ȱʡֵ  �ɿ�  ����˵��
  1   1-����   ͨѶ������     401-XML���    /commbuf   N    ͨѶ���������      

������״̬:
  ���״̬��         ���˵��
  ȱʡ

��־��Ϣ:
  ��־����           ��־��

��Ӧ��Ϣ:
  �ڲ���Ӧ��         �ڲ���Ӧ��Ϣ

��Ҫ����Ԫ��:
  Ԫ��·��          ����

��Ҫ�������:
  ����              ����

ʹ������:

�� Ŀ ��: 
�� �� Ա:
��������:
�޸�����:2008-12-1 16:10:24[Gen]
����ʹ��ʾ��:
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
   LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),__func__)
#endif

   memset(scommbufnode,0x00,sizeof(scommbufnode));

   COMP_PARACOUNTCHKMIN(4)

   COMP_GETPARSEPARAS(1, scommbuf, "��ǩ����");
   memset(szAlgo, 0, sizeof(szAlgo));
   COMP_GETPARSEPARAS(2, szAlgo, "�㷨");
   memset(szDescPath, 0, sizeof(szDescPath));
   COMP_GETPARSEPARAS(3, szDescPath, "Ŀ����xml�ڵ�");
   memset(szFilePath, 0, sizeof(szFilePath));
   COMP_GETPARSEPARAS(4, szFilePath, "ǩ��֤��·��");

#ifdef DEBUG
   LOG(LM_STD, Fmtmsg("��ǩ����:[%s]", scommbuf), "INFO");
   LOG(LM_STD, Fmtmsg("�㷨:[%s]", szAlgo), "INFO");
   LOG(LM_STD, Fmtmsg("Ŀ����xml�ڵ�:[%s]", szDescPath), "INFO");
   LOG(LM_STD, Fmtmsg("ǩ��֤��·��:[%s]", szFilePath), "INFO");
#endif

   outdata =  (char * ) malloc( sizeof(char) * MAX_SOCK_BUF_SIZE);
   if (outdata == NULL)
   {
      free(indata);
      LOG(LM_STD,Fmtmsg("�����ڴ�ʧ��"),"ERROR");
      fpub_SetMsg(lXmlhandle,MID_YW_ERROR,Fmtmsg("ǩ��ʧ��"));
      fpub_SetCompStatus(lXmlhandle,-1);      /*�쳣ʱ,�������-1*/
      return -1;
   }

   ilen_send=strlen(scommbuf);

   iret = prv_genca_wzj(lXmlhandle, scommbuf, ilen_send, outdata, &ilen_recv, szFilePath, szAlgo);
   if (iret<0)
   {
      LOG(LM_STD,Fmtmsg("CAǩ��ʧ��,iret=[%d]", iret),"ERROR");
      fpub_SetMsg(lXmlhandle,MID_YW_ERROR,Fmtmsg("CAǩ��ʧ��"));
      fpub_SetCompStatus(lXmlhandle,-1);
      free(outdata);
      free(indata);
      return -1;
   }

   outdata[ilen_recv]='\0';

   xml_SetElement(lXmlhandle, szDescPath, outdata);

   free(outdata);
 
#ifdef DEBUG
   LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)),__func__)
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
   LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),__func__)
#endif

   memset(scommbufnode,0x00,sizeof(scommbufnode));

   COMP_PARACOUNTCHKMIN(4)

   COMP_GETPARSEPARAS(1, scommbuf, "��ǩ����");
   memset(szAlgo, 0, sizeof(szAlgo));
   COMP_GETPARSEPARAS(2, szAlgo, "�㷨");
   memset(sign_buf, 0, sizeof(sign_buf));
   COMP_GETPARSEPARAS(3, sign_buf, "ǩ����");
   sign_len=strlen(sign_buf);
   memset(szFilePath, 0, sizeof(szFilePath));
   COMP_GETPARSEPARAS(4, szFilePath, "ǩ��֤��·��");

#ifdef DEBUG
   LOG(LM_STD, Fmtmsg("��ǩ����:[%s]", scommbuf), "INFO");
   LOG(LM_STD, Fmtmsg("�㷨:[%s]", szAlgo), "INFO");
   LOG(LM_STD, Fmtmsg("ǩ����[%s]", szDescPath), "INFO");
   LOG(LM_STD, Fmtmsg("ǩ��֤��·��:[%s]", szFilePath), "INFO");
#endif

   ilen_send=strlen(scommbuf);

   iret=prv_checkca_wzj(lXmlhandle, scommbuf, ilen_send,  sign_buf, sign_len, szFilePath, szAlgo);
   if (iret<0)
   {
      LOG(LM_STD,Fmtmsg("CAǩ����֤ʧ��,iret=[%d]", iret),"ERROR");
      fpub_SetMsg(lXmlhandle,MID_YW_ERROR,Fmtmsg("CAǩ����֤ʧ��"));
      fpub_SetCompStatus(lXmlhandle,-1);
      free(outdata);
      free(indata);
      return -1;
   }

#ifdef DEBUG
   LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)),__func__)
#endif

   fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
   return 0;
}
