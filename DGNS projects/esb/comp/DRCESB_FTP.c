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
#include "DRC_esb_const.h"

#define DRC_PUT_AUTH "101"
#define DRC_GET_AUTH "102"
#define DRC_PUT "201"
#define DRC_GET "202"
#define DRC_DEL "203"
#define DRC_RPUT "301"
#define DRC_SUCC "000000"
#define DRC_TIME_OUT 300

extern char * DRC_StrPack(char * );

/*********************************************************
��������:   �ͷ��ļ���socket���ڴ���Դ
������Ա:   chenhh
�޸�����:   2011-12-20
*********************************************************/
int DRC_cleanResource(HXMLTREE lXmlhandle,DRC_stFile * file,DRC_stFileBean * bean)
{
   LOG(LM_DEBUG,Fmtmsg("���[%s] �ͷ���Դ",fpub_GetCompname(lXmlhandle)),__func__)
   /* �ͷ��ļ���Դ */
   if (file!=NULL)
   {
      /* �ر�socket ���� */
      DRC_closeSock(file->sock);

      /* �ļ����*/
      if (file->destFile!=NULL)
      {
         fclose(file->destFile);
         file->destFile=NULL;
      }
      free(file);
      file=NULL;
   }

   /* �ͷ��ļ�bean��Դ */
   if (bean!=NULL)
   {
      free(bean);
      bean=NULL;
   }
   return 0;
}

/*********************************************************
��������:   ��ʼ��һ���ļ��������
������Ա:   chenhh
�޸�����:   2011-12-20
*********************************************************/
DRC_stFile * DRC_initFile(HXMLTREE lXmlhandle,char * remoteFileName,char* localFileName,int putFlag)
{
   char port[6];
   DRC_stFile * file = ( struct DRC_stFile * ) malloc( sizeof( struct DRC_stFile ) );
   if (file == NULL)
   {
      LOG(LM_STD,Fmtmsg("���[%s] �����ڴ�ʧ��",fpub_GetCompname(lXmlhandle)),__func__)
      return NULL;
   }

   memset(file,0x00,sizeof(DRC_stFile));
   sprintf(file->localFileName,"%s",localFileName);
   sprintf(file->tmpFileName,"%s.tmp",localFileName);
   sprintf(file->cfgFileName,"%s.cfg",localFileName);
   sprintf(file->remoteFileName,"%s",remoteFileName);
   file->putFlag=putFlag;

   DRC_GetConfig("FTP_SERV_IP", file->servIp);
   if (strlen(file->servIp) == 0) 
   {
      free(file);
      file=NULL;
      LOG(LM_STD,Fmtmsg("���[%s] not set remote ip",fpub_GetCompname(lXmlhandle)),__func__)
      return NULL;
   }

   memset(port,0x00,sizeof(port));
   DRC_GetConfig("FTP_SERV_PORT", port);
   if (strlen(port) == 0)
   {
      free(file);
      LOG(LM_STD,Fmtmsg("���[%s] not set remote port",fpub_GetCompname(lXmlhandle)),__func__)
      return NULL; 
   }
   file->servPort=atoi(port);

   LOG(LM_DEBUG,Fmtmsg("���[%s] ftp server is %s:%d",fpub_GetCompname(lXmlhandle),file->servIp,file->servPort),__func__)

   if (putFlag==1)
      file->destFile = fopen(file->localFileName,"r");
   else
      file->destFile = fopen(file->tmpFileName, "wb");
   if (file->destFile==NULL)
   {
      LOG(LM_STD,Fmtmsg("���[%s] ���ļ�����[%s]",fpub_GetCompname(lXmlhandle),file->localFileName),__func__)
      free(file);
      file=NULL;
      return NULL;
   }

   DRC_md5Init(&(file->struMd5Context));

   return file;
}

/*********************************************************
��������:   ��ʼ��һ��Bean����
������Ա:   chenhh
�޸�����:   2011-12-20
*********************************************************/
DRC_stFileBean * DRC_initFileBean(HXMLTREE lXmlhandle,char * remoteFileName,char * localFileName)
{
   char uid[80];
   char passwd[80];
   DRC_stFileBean * filebean = ( struct DRC_stFileBean * ) malloc( sizeof( struct DRC_stFileBean ) );
   if (filebean == NULL)
   {
      LOG(LM_STD,Fmtmsg("���[%s] �����ڴ�ʧ��",fpub_GetCompname(lXmlhandle)),__func__)
      return NULL;
   }

   DRC_GetConfig("FTP_SERV_PASSWD", passwd);
   DRC_GetConfig("FTP_SERV_UID", uid);

   memset(filebean,0x00,sizeof(DRC_stFileBean));
   memcpy(filebean->fileName,remoteFileName,strlen(remoteFileName));
   memcpy(filebean->clientFileName,localFileName,strlen(localFileName));
   memcpy(filebean->passwd,passwd,strlen(passwd));
   memcpy(filebean->uid,uid,strlen(uid));

   return filebean;

}

/*********************************************************
��������:   ���ļ������������������
������Ա:   chenhh
�޸�����:   2011-12-20
*********************************************************/
int DRC_doConnect(HXMLTREE lXmlhandle, DRC_stFile * file,DRC_stFileBean * bean)
{
   int addr;
   int i,ret;
   time_t tTimeStart, tTimeNow;
   addr = inet_addr(file->servIp);
   ret = DRC_Conn2Serv(lXmlhandle, addr, file->servPort, &file->sock, DRC_TIME_OUT);
   return ret;
}

/*********************************************************
��������:   ��XML���һ���ֶ�
������Ա:   chenhh
�޸�����:   2011-12-20
*********************************************************/
void DRC_appendToXml(char * xml,int * offset,char * name,char * value)
{
   char temp[1024];
   int len=0;
   memset(temp,0x00,sizeof(temp));
   sprintf(temp,"<%s>%s</%s>",name,value,name);
   len=strlen(temp);
   memcpy(xml+*offset,temp,len);
   *offset=*offset+len;
}

/*********************************************************
��������:   ��bean����ת����XML
������Ա:   chenhh
�޸�����:   2011-12-20
*********************************************************/
void DRC_convertBeanToXml(DRC_stFileBean * bean)
{
   memset(bean->headCont,0x00,sizeof(bean->headCont));
   char * xml = bean->headCont;
   int offset=0;
   char tmp[128];

   sprintf(xml,"<?xml version=\"1.0\" encoding=\"UTF-8\"?><FileRoot>");

   offset = strlen(xml);
   DRC_appendToXml(xml,&offset,"Uid",bean->uid);
   DRC_appendToXml(xml,&offset,"FileMsgFlag",bean->fileMsgFlag);
   DRC_appendToXml(xml,&offset,"Passwd",bean->passwd);
   DRC_appendToXml(xml,&offset,"ScrtFlag",bean->scrtFlag==0?"false":"true");
   DRC_appendToXml(xml,&offset,"FileName",bean->fileName);
   DRC_appendToXml(xml,&offset,"ClientFileName",bean->clientFileName);
   DRC_appendToXml(xml,&offset,"Md5",bean->md5);
   if (bean->fileIndex>0)
   {
      memset(tmp,0x00,sizeof(tmp));
      sprintf(tmp,"%d",bean->fileIndex);
      DRC_appendToXml(xml,&offset,"FileIndex",tmp);
   }

   if (bean->pieceNum>0)
   {
      memset(tmp,0x00,sizeof(tmp));
      sprintf(tmp,"%d",bean->pieceNum);
      DRC_appendToXml(xml,&offset,"PieceNum",tmp);
      memset(tmp,0x00,sizeof(tmp));
   }

   if (bean->lastPiece==1)
      DRC_appendToXml(xml,&offset,"LastPiece","true");

   sprintf(xml+offset,"</FileRoot>");
}

/*********************************************************
��������:   д����Ϣͷ��Ϣ
������Ա:   chenhh
�޸�����:   2011-12-20
*********************************************************/
int DRC_writeHead(HXMLTREE lXmlhandle,DRC_stFile * file,DRC_stFileBean * bean)
{
   int ret,headLen,len;
   char headLenCont[5];

   memset(headLenCont,0x00,sizeof(headLenCont));
   DRC_convertBeanToXml(bean);
   LOG(LM_DEBUG,Fmtmsg("���[%s] write head to server cont=[%s]",fpub_GetCompname(lXmlhandle),bean->headCont),__func__)

   headLen=strlen(bean->headCont);
   DRC_citoc(headLen,headLenCont);

   len = 4;
   ret = DRC_WritePacket(lXmlhandle,file->sock, headLenCont,len,DRC_TIME_OUT);
   if (ret < 0)
   {
      if (file->sock >= 0)
         DRC_closeSock(file->sock);
      LOG(LM_DEBUG,Fmtmsg("���[%s] send packet failed!",fpub_GetCompname(lXmlhandle)),__func__)
      return -1;
   }

   len=headLen;
   ret = DRC_WritePacket(lXmlhandle,file->sock, bean->headCont,len,DRC_TIME_OUT);
   if (ret < 0)
   {
      if (file->sock >= 0)
         DRC_closeSock(file->sock);
      LOG(LM_DEBUG,Fmtmsg("���[%s] send packet failed!",fpub_GetCompname(lXmlhandle)),__func__)
      return -1;
   }
   return 0;
}

/*********************************************************
��������:   ��ȡ��Ϣͷ��Ϣ
������Ա:   chenhh
�޸�����:   2011-12-20
*********************************************************/
int DRC_readHead(HXMLTREE lXmlhandle,DRC_stFile * file,DRC_stFileBean * bean)
{
   int ret,headLen;
   char headLenCont[5];

   LOG(LM_DEBUG,Fmtmsg("���[%s] start to read head",fpub_GetCompname(lXmlhandle)),__func__)

   memset(headLenCont,0x00,sizeof(headLenCont));
   long len=4;
   ret = DRC_ReadPacket(lXmlhandle,file->sock, headLenCont, &len,DRC_TIME_OUT);
   if (ret<0)
      return ret;
   DRC_cctoi(&headLen,headLenCont);
   len=headLen;

   memset(bean->headCont,0x00,sizeof(bean->headCont));
   ret = DRC_ReadPacket(lXmlhandle,file->sock, bean->headCont, &len,DRC_TIME_OUT);
   if (ret<0)
      return ret;
   LOG(LM_DEBUG,Fmtmsg("���[%s] xml=%s",fpub_GetCompname(lXmlhandle),bean->headCont),__func__)

   DRC_convertXmlToBean(lXmlhandle,bean);
   return ret;
}

/*********************************************************
��������:   ���ļ������������֤
������Ա:   chenhh
�޸�����:   2011-12-20
*********************************************************/
int DRC_doAuth(HXMLTREE lXmlhandle,DRC_stFile * file,DRC_stFileBean * bean)
{
   int ret;

   /*����״̬�����������Ϣ״̬��*/
   sprintf(bean->fileMsgFlag,file->putFlag==1?DRC_PUT_AUTH:DRC_GET_AUTH);

   /*��bean����ת����XML����*/
   DRC_convertBeanToXml(bean);

   /*���������ͷ��Ϣ*/
   ret= DRC_writeHead(lXmlhandle,file,bean);
   if (ret<0)
   {
      LOG(LM_STD,Fmtmsg("���[%s] д������ͷ��Ϣ����",fpub_GetCompname(lXmlhandle)),__func__)
      return -1;
   }

   /*��ȡ��Ӧ��ͷ��Ϣ*/
   ret= DRC_readHead(lXmlhandle,file,bean);

   /*�ж���֤��״̬*/
   if (bean->authFlag==1)
   {
      LOG(LM_DEBUG,Fmtmsg("���[%s] ��֤�ɹ�",fpub_GetCompname(lXmlhandle)),__func__)
      return 0;
   }
   else
   {
      LOG(LM_DEBUG,Fmtmsg("���[%s] ��֤ʧ��",fpub_GetCompname(lXmlhandle)),__func__)
      return -1;
   }
}

/*********************************************************
��������:   ��intת�����ַ�����
������Ա:   chenhh
�޸�����:   2011-12-20
*********************************************************/
int DRC_citoc(int k,unsigned char* value)
{
   value[0] = k >> 24 ;
   value[1] = (k << 8) >> 24;
   value[2] = (k << 16) >> 24;
   value[3] = (k << 24) >> 24;
   return 0;
}

/*********************************************************
��������:   ���ļ��ж�ȡ����
������Ա:   chenhh
�޸�����:   2011-12-20
*********************************************************/
int DRC_readFile(HXMLTREE lXmlhandle, DRC_stFile * file,DRC_stFileBean * bean)
{
   LOG(LM_DEBUG,Fmtmsg("���[%s] read from file,num=%d",fpub_GetCompname(lXmlhandle),bean->pieceNum),__func__)
   /*��ȡ�ļ�����*/
   memset(bean->fileCont,0x00,sizeof(bean->fileCont));
   bean->contLen=0;
   bean->contLen=fread(bean->fileCont,1,bean->pieceNum,file->destFile);

   /*�ж��Ƿ����һ����Ƭ*/
   if (bean->contLen!=bean->pieceNum||bean->contLen==-1)
      bean->lastPiece=1;

   /*md5���㲢����md5 ���ݽṹ*/
   if (-1!=bean->contLen)
   {
      DRC_md5Update(&(file->struMd5Context), bean->fileCont, bean->contLen);
   }

   /*���һ������,�������յ�32λmd5�ַ�*/
   if (1==bean->lastPiece)
   {
      DRC_md5Final32(bean->md5, &(file->struMd5Context));
   }
   LOG(LM_DEBUG,Fmtmsg("���[%s] read len=%d",fpub_GetCompname(lXmlhandle),bean->contLen),__func__)
   return 0;
}

/*********************************************************
��������:   д���ļ�����
������Ա:   chenhh
�޸�����:   2011-12-20
*********************************************************/
int DRC_writeCont(HXMLTREE lXmlhandle,DRC_stFile * file,DRC_stFileBean * bean)
{
   int ret,len,oLen;
   char fileLenCont[5];

   LOG(LM_DEBUG,Fmtmsg("���[%s] start to wriete cont",fpub_GetCompname(lXmlhandle)),__func__)
   if (bean->scrtFlag==1)
   {
      len=bean->contLen;
      oLen=0;
      memset(bean->desBuffer,0x00,sizeof(bean->desBuffer));
      DRC_encryptdes(bean->desBuffer,&oLen,bean->fileCont,len,bean->desKey);

      len=oLen;
      memset(fileLenCont,0x00,sizeof(fileLenCont));
      DRC_citoc(len,fileLenCont);
      ret = DRC_WritePacket(lXmlhandle,file->sock, fileLenCont, 4,DRC_TIME_OUT);
      if (ret<0)
         return ret;

      ret = DRC_WritePacket(lXmlhandle,file->sock, bean->desBuffer,oLen,DRC_TIME_OUT);
      if (ret<0)
         return ret;
   }
   else
   {
      len=bean->contLen;
      memset(fileLenCont,0x00,sizeof(fileLenCont));
      DRC_citoc(len,fileLenCont);
      len = 4;
      ret = DRC_WritePacket(lXmlhandle,file->sock, fileLenCont, len,DRC_TIME_OUT);
      if (ret<0)
         return ret;

      len=bean->contLen;
      ret = DRC_WritePacket(lXmlhandle,file->sock, bean->fileCont, len,DRC_TIME_OUT);
      if (ret<0)
         return ret;
   }

   return ret;   
}

/*********************************************************
��������:   ���Ҷ�Ӧ���ַ���
������Ա:   chenhh
�޸�����:   2011-12-20
*********************************************************/
int DRC_goToStr(char * xml,int * offset,int iLen,char * strValue)
{
   int len = strlen(strValue);
   while(*offset<iLen)
   {
      if (memcmp(xml+*offset,strValue,len)==0)
      {
         *offset=*offset+len;
         return 1;
      }
      *offset=*offset+1;
   }
   return 0;         
}

/*********************************************************
��������:   ����XML�е�һ��������
������Ա:   chenhh
�޸�����:   2011-12-20
*********************************************************/
int DRC_getOneField(char * xml,int * offset,int iLen,char * name,char * value)
{
   int s,e1,e2,ret;
   while(*offset<iLen)
   {
      /*��ȡ�ֶ�����*/
      if (DRC_goToStr(xml,offset,iLen,"<")==0)
         break;
      s=*offset;

      if (DRC_goToStr(xml,offset,iLen,">")==0)
         break;
      e1=*offset;
      memcpy(name,xml+s,e1-s-1);

      /*��ȡ�ֶ�����*/
      if (DRC_goToStr(xml,offset,iLen,"<")==0)
         break;
      e2=*offset;
      memcpy(value,xml+e1,e2-e1-1);
      DRC_goToStr(xml,offset,iLen,">");

      break;
   }
}

/*********************************************************
��������:   �������ݵ�bean��
������Ա:   chenhh
�޸�����:   2011-12-20
*********************************************************/
int DRC_setDataToBean(HXMLTREE lXmlhandle,DRC_stFileBean * bean,char * name,char * value)
{
   int len = strlen(name);
   int valLen = strlen(value);

   LOG(LM_DEBUG,Fmtmsg("���[%s] set value %s=[%s]",fpub_GetCompname(lXmlhandle),name,value),__func__)
   if (memcmp(name,"FileMsgFlag",len)==0)
   {
      memset(bean->fileMsgFlag,0x00,sizeof(bean->fileMsgFlag));
      memcpy(bean->fileMsgFlag,value,valLen);
   }
   else if (memcmp(name,"ServerName",len)==0)
   {
      memset(bean->serverName,0x00,sizeof(bean->serverName));
      memcpy(bean->serverName,value,valLen);
   }
   else if (memcmp(name,"ScrtFlag",len)==0)
   {
      if (memcmp(value,"true",4)==0)
         bean->scrtFlag=1;
      else
         bean->scrtFlag=0;
   }
   else if (memcmp(name,"AuthFlag",len)==0)
   {
      if (memcmp(value,"true",4)==0)
         bean->authFlag=1;
      else
         bean->authFlag=0;
   }
   else if (memcmp(name,"LastPiece",len)==0)
   {
      if (memcmp(value,"true",4)==0)
         bean->lastPiece=1;
      else
         bean->lastPiece=0;
   }
   else if (memcmp(name,"PieceNum",len)==0)
   {
      bean->pieceNum=atoi(value);      
   }
   else if (memcmp(name,"DesKey",len)==0)
   {
      long oLen = 0,iLen = 0;
      char tmp[80];
      char key[80];
      memset(tmp,0x00,sizeof(tmp));
      iLen = strlen(value);
      DRC_base64_decode(value,tmp,&oLen);
      memset(bean->desKey,0x00,sizeof(bean->desKey));
      memset(key,0x00,sizeof(key));
      DRC_GetConfig("FTP_SERV_KEY", key);
      iLen=oLen;
      DRC_decrypt3des(bean->desKey,&oLen ,tmp,iLen,key);
   }
   else if (memcmp(name,"Md5",len)==0)
   {
      memset(bean->md5,0x00,sizeof(bean->md5));
      memcpy(bean->md5,value,valLen);
   }

   return 0;
}

/*********************************************************
��������:   ת��XML���ݵ�bean����
������Ա:   chenhh
�޸�����:   2011-12-20
*********************************************************/
void DRC_convertXmlToBean(HXMLTREE lXmlhandle,DRC_stFileBean * bean)
{
   int ret=1;
   int offset=0;
   char name[80];
   char value[1024];
   int iLen=strlen(bean->headCont);

   DRC_goToStr(bean->headCont,&offset,iLen,"<?xml version=\"1.0\" encoding=\"UTF-8\"?>" );
   DRC_goToStr(bean->headCont,&offset,iLen,"<FileRoot>" );
   while(offset<iLen)
   {
      memset(name,0x00,sizeof(name));
      memset(value,0x00,sizeof(value));
      ret=DRC_getOneField(bean->headCont,&offset,iLen,name,value);
      DRC_setDataToBean(lXmlhandle,bean,name,value);
   }
}

/*********************************************************
��������:   ���ַ�����ת����int
������Ա:   chenhh
�޸�����:   2011-12-20
*********************************************************/
int DRC_cctoi(int * k,char* value)
{
   int ch1 = (int) value[0]&0xff;
   int ch2 = (int) value[1]&0xff;
   int ch3 = (int) value[2]&0xff;
   int ch4 = (int) value[3]&0xff;
   *k = (ch1 << 24) + (ch2 << 16) + (ch3 << 8) + (ch4 << 0);
   return *k;
}

/*********************************************************
��������:   ����ļ��ϴ�
������Ա:   chenhh
�޸�����:   2011-12-20
*********************************************************/
int DRC_doPutFile(HXMLTREE lXmlhandle,DRC_stFile * file,DRC_stFileBean * bean)
{
   int ret;
   bean->fileIndex=0;

   while(1)
   {
      /* �ļ���Ƭ��1 */
      bean->fileIndex++;

      /* �ļ������ļ��ϴ��ı�־ */
      memset(bean->fileMsgFlag,0x00,sizeof(bean->fileMsgFlag));
      sprintf(bean->fileMsgFlag,DRC_PUT);

      /* ��ȡ�ļ� */
      DRC_readFile(lXmlhandle,file,bean);

      /* ��ȡ��Ϣͷ */
      ret= DRC_writeHead(lXmlhandle,file,bean);
      if (ret<0)
      {
         LOG(LM_STD,Fmtmsg("���[%s] д����Ϣͷ����",fpub_GetCompname(lXmlhandle)),__func__)
         return -1;
      }

      /* д���ļ����� */
      ret = DRC_writeCont(lXmlhandle,file,bean);
      if (ret<0)
      {
         LOG(LM_STD,Fmtmsg("���[%s] д���ļ���Ƭ����",fpub_GetCompname(lXmlhandle)),__func__)
         return -1;
      }

      /*��ȡ��������Ӧ״̬*/
      ret= DRC_readHead(lXmlhandle,file,bean);
      if (ret<0)
      {
         LOG(LM_STD,Fmtmsg("���[%s] ��ȡ��������Ӧ״̬����",fpub_GetCompname(lXmlhandle)),__func__)
         return -1;
      }

      /* �жϷ�������Ӧ״̬ */
      if (memcmp(bean->fileMsgFlag,"000000",6)!=0)
      {
         LOG(LM_STD,Fmtmsg("���[%s] ������Ӧ״̬�쳣���쳣��[%s]",fpub_GetCompname(lXmlhandle),bean->fileMsgFlag),__func__)
         return -1;
      }

      /* �ж��Ƿ����ļ������һ����Ƭ */
      if (bean->lastPiece==1)
      {
         LOG(LM_STD,Fmtmsg("���[%s] �������һ����Ƭ",fpub_GetCompname(lXmlhandle)),__func__)
         break;
      }
   }

   return 0;
}

/*********************************************************
��������:   �ļ�����������ļ��ϴ�
������Ա:   chenhh
�޸�����:   2011-12-20
*********************************************************/
int DRC_ftpput(HXMLTREE lXmlhandle, char * remoteFileName,char * localFileName, char * localFileMd5, int scrtFlag)
{
   DRC_stFile * file;
   DRC_stFileBean * bean;
   int ret;

   remoteFileName=DRC_StrPack(remoteFileName);
   localFileName=DRC_StrPack(localFileName);
 
   /*��ʼ������*/
   ret = DRC_InitConfig();
   if (ret!=0)
      return -4;

   /*�����ļ�����*/
   file = DRC_initFile(lXmlhandle,remoteFileName,localFileName,1);
   bean = DRC_initFileBean(lXmlhandle,remoteFileName,localFileName);
   bean->scrtFlag = scrtFlag;

   /*�����ļ���ʼ���Ƿ�ɹ�*/
   if (file==NULL||bean==NULL)
   {
      DRC_cleanResource(lXmlhandle,file,bean);
      return -1;
   }

   /*��������*/
   ret=DRC_doConnect(lXmlhandle,file,bean);
   if (ret<0)
   {
      LOG(LM_STD,Fmtmsg("���[%s] ��������ʧ��", fpub_GetCompname(lXmlhandle)),__func__)
      DRC_cleanResource(lXmlhandle,file,bean);
      return -1;
   }

   /*��ȫ��֤*/
   ret=DRC_doAuth(lXmlhandle,file,bean);
   if (ret<0)
   {
      LOG(LM_STD,Fmtmsg("���[%s] Ȩ����֤ʧ��", fpub_GetCompname(lXmlhandle)),__func__)
      DRC_cleanResource(lXmlhandle,file,bean);
      return -1;
   }

   /*�ϴ��ļ�*/
   ret=DRC_doPutFile(lXmlhandle,file,bean);
   if (ret<0)
   {
      LOG(LM_STD,Fmtmsg("���[%s] �ļ�����ʧ��", fpub_GetCompname(lXmlhandle)),__func__)
      DRC_cleanResource(lXmlhandle,file,bean);
      return -1;
   }

   /*����MD5У����*/
   memcpy(localFileMd5, bean->md5, sizeof(bean->md5));

   /*�ͷ���Դ*/
   DRC_cleanResource(lXmlhandle,file,bean);
   return 0;
}

/*********************************************************
��������:   ��ȡ�ļ�����
������Ա:   chenhh
�޸�����:   2011-12-20
*********************************************************/
int DRC_readCont(HXMLTREE lXmlhandle,DRC_stFile * file,DRC_stFileBean * bean)
{
   int ret,fileLen;
   char fileLenCont[5];

   memset(fileLenCont,0x00,sizeof(fileLenCont));
   long len = 4;
   ret = DRC_ReadPacket(lXmlhandle,file->sock, fileLenCont, &len,DRC_TIME_OUT);
   if (ret<0)
      return ret;
   DRC_cctoi(&fileLen,fileLenCont);

   LOG(LM_DEBUG,Fmtmsg("���[%s] scrtFlag=%d",fpub_GetCompname(lXmlhandle),bean->scrtFlag),__func__)
   if (bean->scrtFlag==1)
   {
      memset(bean->desBuffer,0x00,sizeof(bean->desBuffer));
      len=fileLen;
      ret = DRC_ReadPacket(lXmlhandle,file->sock, bean->desBuffer, &len,DRC_TIME_OUT);
      if (ret<0)
         return ret;
      long oLen = 0;
      memset(bean->fileCont,0x00,sizeof(bean->fileCont));
      DRC_decryptdes(bean->fileCont,&oLen ,bean->desBuffer,len,bean->desKey);
      bean->contLen=oLen;
   }
   else
   {
      memset(bean->fileCont,0x00,sizeof(bean->fileCont));
      len=fileLen;
      ret = DRC_ReadPacket(lXmlhandle,file->sock, bean->fileCont, &len,DRC_TIME_OUT);
      bean->contLen=len;
      if (ret<0)
         return ret;
   }
   LOG(LM_DEBUG,Fmtmsg("���[%s] ��ȡ���ݳ���len=%d",fpub_GetCompname(lXmlhandle),fileLen),__func__)
   return ret;
}

/*********************************************************
��������:   д�����ݵ��ļ�
������Ա:   chenhh
�޸�����:   2011-12-20
*********************************************************/
int DRC_writeFile(HXMLTREE lXmlhandle,DRC_stFile * file,DRC_stFileBean * bean)
{
   LOG(LM_DEBUG,Fmtmsg("���[%s] write to file,len=[%d]",fpub_GetCompname(lXmlhandle),bean->contLen),__func__)
   fwrite(bean->fileCont,1,bean->contLen,file->destFile);

   /*md5���㲢����md5 ���ݽṹ*/
   if (-1!=bean->contLen)
   {
      DRC_md5Update(&(file->struMd5Context), bean->fileCont, bean->contLen);
   }

   return 0;
}

/*********************************************************
��������:   ����ļ����أ�������Ϊ��ʵ�ļ���
������Ա:   chenhh
�޸�����:   2011-12-20
*********************************************************/
int DRC_finishFile(HXMLTREE lXmlhandle,DRC_stFile * file,DRC_stFileBean * bean)
{
   int ret=-1;
   char md5[33];

   fclose(file->destFile);
   file->destFile=NULL;

   memset(md5,0x00,sizeof(md5));
   DRC_md5Final32(md5, &(file->struMd5Context));

   LOG(LM_DEBUG,Fmtmsg("���[%s] file md5 remotevalue=[%s],localvalue=[%s]",fpub_GetCompname(lXmlhandle),md5,bean->md5),__func__)
   if (memcmp(md5,bean->md5,32)==0)
   {
      LOG(LM_DEBUG,Fmtmsg("���[%s] checking md5 of download file is successed:%s",fpub_GetCompname(lXmlhandle),md5),__func__)
      ret=rename(file->tmpFileName,file->localFileName);
      if (0!=ret)
      {
         remove(file->tmpFileName);  
      }
   }
   else
   {
      LOG(LM_DEBUG,Fmtmsg("���[%s] checking md5 of download file is error:remotevalue=[%s],localvalue=[%s]",fpub_GetCompname(lXmlhandle),md5,bean->md5),__func__)
      remove(file->tmpFileName);
   }
   return ret;
}

/*********************************************************
��������:   ����ļ�����
������Ա:   chenhh
�޸�����:   2011-12-20
*********************************************************/
int DRC_doGetFile(HXMLTREE lXmlhandle,DRC_stFile * file,DRC_stFileBean * bean)
{
   int ret;
   bean->fileIndex=0;

   while(1)
   {
      /* �ļ���Ƭ��1 */
      bean->fileIndex++;

      /* �ļ������ļ��ϴ��ı�־ */
      memset(bean->fileMsgFlag,0x00,sizeof(bean->fileMsgFlag));
      sprintf(bean->fileMsgFlag,DRC_GET);

      /* д����Ϣͷ */
      ret= DRC_writeHead(lXmlhandle,file,bean);
      if (ret<0)
      {
         LOG(LM_STD,Fmtmsg("���[%s] д����Ϣͷ����",fpub_GetCompname(lXmlhandle)),__func__)
         return -1;
      }

      /* ��ȡ��Ϣͷ */
      ret= DRC_readHead(lXmlhandle,file,bean);
      if (ret<0)
      {
         LOG(LM_STD,Fmtmsg("���[%s] ��ȡ��Ϣͷ����",fpub_GetCompname(lXmlhandle)),__func__)
         return -1;
      }

      /* �жϴ���״̬ */
      if (memcmp(bean->fileMsgFlag,"000000",6)==0)
      {
         ret=DRC_readCont(lXmlhandle,file,bean);
         if (ret<0)
         {
            LOG(LM_STD,Fmtmsg("���[%s] ��ȡ����ʧ��",fpub_GetCompname(lXmlhandle)),__func__)
            return -1;
         }
         
         /* д�뵽�ļ��� */
         DRC_writeFile(lXmlhandle,file,bean);
         if (bean->lastPiece==1)
         {
             /*���һ����Ƭ*/
             LOG(LM_DEBUG,Fmtmsg("���[%s] ��ȡ�����һ���ļ���Ƭ",fpub_GetCompname(lXmlhandle)),__func__)
             break;
         }
         
      }
      else
      {
         LOG(LM_STD,Fmtmsg("���[%s] ����ʧ�ܣ����������ص�״̬��[%s]",fpub_GetCompname(lXmlhandle),bean->fileMsgFlag),__func__)
         return -1;
      }   
   }
   
   /* ����ļ����� */
   ret=DRC_finishFile(lXmlhandle,file,bean);
   return ret;
}

/*********************************************************
��������:   �ļ�����������ļ�����
������Ա:   chenhh
�޸�����:   2011-12-20
*********************************************************/
int DRC_ftpget(HXMLTREE lXmlhandle,char * remoteFileName,char * localFileName, char * localFileMd5, int scrtFlag)
{
   DRC_stFile * file;
   DRC_stFileBean * bean;
   int ret;

   remoteFileName=DRC_StrPack(remoteFileName);
   localFileName=DRC_StrPack(localFileName);

   /*��ʼ������*/
   ret = DRC_InitConfig();
   if (ret!=0)
      return -4;

   /*�����ļ�����*/
   file = DRC_initFile(lXmlhandle,remoteFileName,localFileName,0);
   bean = DRC_initFileBean(lXmlhandle,remoteFileName,localFileName);
   bean->scrtFlag = scrtFlag;

   /*�����ļ���ʼ���Ƿ�ɹ�*/
   if (file==NULL||bean==NULL)
   {
      DRC_cleanResource(lXmlhandle,file,bean);
      return -1;
   }

   /*��������*/
   ret=DRC_doConnect(lXmlhandle,file,bean);
   if (ret<0)
   {
      LOG(LM_STD,Fmtmsg("���[%s] ��������ʧ��",fpub_GetCompname(lXmlhandle)),__func__)
      DRC_cleanResource(lXmlhandle,file,bean);
      return -1;
   }

   /*��ȫ��֤*/
   ret=DRC_doAuth(lXmlhandle,file,bean);
   if (ret<0)
   {
      LOG(LM_STD,Fmtmsg("���[%s] Ȩ����֤ʧ��",fpub_GetCompname(lXmlhandle)),__func__)
      DRC_cleanResource(lXmlhandle,file,bean);
      return -1;
   }
    
   /*�����ļ�*/
   ret=DRC_doGetFile(lXmlhandle,file,bean);
   if (ret<0)
   {
      LOG(LM_STD,Fmtmsg("���[%s] �ļ�����ʧ��",fpub_GetCompname(lXmlhandle)),__func__)
      DRC_cleanResource(lXmlhandle,file,bean);
      return -1;
   }

   /*�ļ���MD5У��*/
   memcpy(localFileMd5, bean->md5, sizeof(bean->md5));
    
   /*�ͷ���Դ*/
   DRC_cleanResource(lXmlhandle,file,bean);
   return 0;
}

/************************************************************************
��̬�����������
�����������:DRC_FTPPUT
�������:DRC_FTPPUT
�������:
�������:
 ��� ��������  ��������         ��Դ���     ȱʡֵ  �ɿ�  ����˵��
  1   1-����   Ŀ���ļ���     416-                     N    Ŀ���ļ���
  2   1-����   �����ļ���     416-                     N    �����ļ���
  3   1-����   ���ܱ�־       416-                     N    ���ܱ�־ 0-������ 1-����
  4   1-���   MD5ֵ�ڵ�      401-                     N    MD5ֵ�ڵ�

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
IRESULT DRC_FTPPUT(HXMLTREE lXmlhandle)
{
   char md5node[256], md5[33];
   char sbuf[256],lfilename[256],rfilename[256];
   int  iParas, iret, mflag;

   fpub_InitSoComp(lXmlhandle);

   LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),__func__)

   memset(md5node,0x00,sizeof(md5node));

   COMP_PARACOUNTCHKMIN(4)
   memset(sbuf,0x00,sizeof(sbuf));
   COMP_GETPARSEPARAS(1,sbuf,"Ŀ���ļ���");
   memset(rfilename,0x00,sizeof(rfilename));
   pstrcopy(rfilename,sbuf,sizeof(rfilename));

   memset(sbuf,0x00,sizeof(sbuf));
   COMP_GETPARSEPARAS(2,sbuf,"�����ļ���");
   memset(lfilename,0x00,sizeof(lfilename));
   pstrcopy(lfilename,sbuf,sizeof(lfilename));

   memset(sbuf,0x00,sizeof(sbuf));
   COMP_GETPARSEPARAS(3,sbuf,"���ܱ�־");
   mflag=sbuf[0] - '0';

   COMP_GETPARSEPARAS(4,md5node,"MD5ֵ�ڵ�")
 
   memset(md5,0x00,sizeof(md5));
   LOG(LM_DEBUG,Fmtmsg("���[%s] rfilename[%s],lfilename[%s],md5[%s],mflag[%d]",fpub_GetCompname(lXmlhandle),rfilename,lfilename,md5,mflag),__func__)
   iret=DRC_ftpput(lXmlhandle,rfilename,lfilename,md5,mflag);
   if (iret !=0)
   {
      fpub_SetMsg(lXmlhandle,MID_YW_ERROR,Fmtmsg("�ļ�PUTʧ��"));
      fpub_SetCompStatus(lXmlhandle,-1);
      return -1;
   }
   COMP_SOFTSETXML(md5node,md5);
   fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
#ifdef DEBUG
   LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)),__func__)
#endif
   return 0;
}

/************************************************************************
��̬�����������
�����������:DRC_FTPGET
�������:DRC_FTPGET
�������:
�������:
 ��� ��������  ��������         ��Դ���     ȱʡֵ  �ɿ�  ����˵��
  1   1-����   Ŀ���ļ���     416-                     N    Ŀ���ļ���
  2   1-����   �����ļ���     416-                     N    �����ļ���
  3   1-����   ���ܱ�־       416-                     N    ���ܱ�־ 0-������ 1-����
  4   1-���   MD5ֵ·��      401-                     N    MD5ֵ·��

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
IRESULT DRC_FTPGET(HXMLTREE lXmlhandle)
{
   char md5node[256], md5[33];
   char sbuf[256],lfilename[256],rfilename[256];
   int  iParas, iret, mflag;

   fpub_InitSoComp(lXmlhandle);

#ifdef DEBUG
   LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),__func__)
#endif

   memset(md5node,0x00,sizeof(md5node));

   COMP_PARACOUNTCHKMIN(4)
   memset(sbuf,0x00,sizeof(sbuf));
   COMP_GETPARSEPARAS(1,sbuf,"Ŀ���ļ���");
   memset(rfilename,0x00,sizeof(rfilename));
   pstrcopy(rfilename,sbuf,sizeof(rfilename));

   memset(sbuf,0x00,sizeof(sbuf));
   COMP_GETPARSEPARAS(2,sbuf,"�����ļ���");
   memset(lfilename,0x00,sizeof(lfilename));
   pstrcopy(lfilename,sbuf,sizeof(lfilename));

   memset(sbuf,0x00,sizeof(sbuf));
   COMP_GETPARSEPARAS(3,sbuf,"���ܱ�־");
   mflag=sbuf[0] - '0';

   COMP_GETPARSEPARAS(4,md5node,"MD5ֵ�ڵ�")
 
#ifdef DEBUG
   LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)),__func__)
#endif
   memset(md5,0x00,sizeof(md5));
   iret=DRC_ftpget(lXmlhandle,rfilename,lfilename,md5,mflag);
   if (iret !=0)
   {
      fpub_SetMsg(lXmlhandle,MID_YW_ERROR,Fmtmsg("�ļ�GETʧ��"));
      fpub_SetCompStatus(lXmlhandle,-1);
      return -1;
   }
   COMP_SOFTSETXML(md5node,md5);
   fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
   return 0;
}
