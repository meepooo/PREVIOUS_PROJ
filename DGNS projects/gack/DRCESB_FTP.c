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
功能描述:   释放文件、socket和内存资源
开发人员:   chenhh
修改日期:   2011-12-20
*********************************************************/
int DRC_cleanResource(HXMLTREE lXmlhandle,DRC_stFile * file,DRC_stFileBean * bean)
{
   LOG(LM_DEBUG,Fmtmsg("组件[%s] 释放资源",fpub_GetCompname(lXmlhandle)),__func__)
   /* 释放文件资源 */
   if (file!=NULL)
   {
      /* 关闭socket 连接 */
      DRC_closeSock(file->sock);

      /* 文件句柄*/
      if (file->destFile!=NULL)
      {
         fclose(file->destFile);
         file->destFile=NULL;
      }
      free(file);
      file=NULL;
   }

   /* 释放文件bean资源 */
   if (bean!=NULL)
   {
      free(bean);
      bean=NULL;
   }
   return 0;
}

/*********************************************************
功能描述:   初始化一个文件传输对象
开发人员:   chenhh
修改日期:   2011-12-20
*********************************************************/
DRC_stFile * DRC_initFile(HXMLTREE lXmlhandle,char * remoteFileName,char* localFileName,int putFlag)
{
   char port[6];
   DRC_stFile * file = ( struct DRC_stFile * ) malloc( sizeof( struct DRC_stFile ) );
   if (file == NULL)
   {
      LOG(LM_STD,Fmtmsg("组件[%s] 申请内存失败",fpub_GetCompname(lXmlhandle)),__func__)
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
      LOG(LM_STD,Fmtmsg("组件[%s] not set remote ip",fpub_GetCompname(lXmlhandle)),__func__)
      return NULL;
   }

   memset(port,0x00,sizeof(port));
   DRC_GetConfig("FTP_SERV_PORT", port);
   if (strlen(port) == 0)
   {
      free(file);
      LOG(LM_STD,Fmtmsg("组件[%s] not set remote port",fpub_GetCompname(lXmlhandle)),__func__)
      return NULL; 
   }
   file->servPort=atoi(port);

   LOG(LM_DEBUG,Fmtmsg("组件[%s] ftp server is %s:%d",fpub_GetCompname(lXmlhandle),file->servIp,file->servPort),__func__)

   if (putFlag==1)
      file->destFile = fopen(file->localFileName,"r");
   else
      file->destFile = fopen(file->tmpFileName, "wb");
   if (file->destFile==NULL)
   {
      LOG(LM_STD,Fmtmsg("组件[%s] 打开文件出错[%s]",fpub_GetCompname(lXmlhandle),file->localFileName),__func__)
      free(file);
      file=NULL;
      return NULL;
   }

   DRC_md5Init(&(file->struMd5Context));

   return file;
}

/*********************************************************
功能描述:   初始化一个Bean对象
开发人员:   chenhh
修改日期:   2011-12-20
*********************************************************/
DRC_stFileBean * DRC_initFileBean(HXMLTREE lXmlhandle,char * remoteFileName,char * localFileName)
{
   char uid[80];
   char passwd[80];
   DRC_stFileBean * filebean = ( struct DRC_stFileBean * ) malloc( sizeof( struct DRC_stFileBean ) );
   if (filebean == NULL)
   {
      LOG(LM_STD,Fmtmsg("组件[%s] 申请内存失败",fpub_GetCompname(lXmlhandle)),__func__)
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
功能描述:   与文件传输服务器建立连接
开发人员:   chenhh
修改日期:   2011-12-20
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
功能描述:   给XML添加一个字段
开发人员:   chenhh
修改日期:   2011-12-20
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
功能描述:   将bean数据转换成XML
开发人员:   chenhh
修改日期:   2011-12-20
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
功能描述:   写入消息头信息
开发人员:   chenhh
修改日期:   2011-12-20
*********************************************************/
int DRC_writeHead(HXMLTREE lXmlhandle,DRC_stFile * file,DRC_stFileBean * bean)
{
   int ret,headLen,len;
   char headLenCont[5];

   memset(headLenCont,0x00,sizeof(headLenCont));
   DRC_convertBeanToXml(bean);
   LOG(LM_DEBUG,Fmtmsg("组件[%s] write head to server cont=[%s]",fpub_GetCompname(lXmlhandle),bean->headCont),__func__)

   headLen=strlen(bean->headCont);
   DRC_citoc(headLen,headLenCont);

   len = 4;
   ret = DRC_WritePacket(lXmlhandle,file->sock, headLenCont,len,DRC_TIME_OUT);
   if (ret < 0)
   {
      if (file->sock >= 0)
         DRC_closeSock(file->sock);
      LOG(LM_DEBUG,Fmtmsg("组件[%s] send packet failed!",fpub_GetCompname(lXmlhandle)),__func__)
      return -1;
   }

   len=headLen;
   ret = DRC_WritePacket(lXmlhandle,file->sock, bean->headCont,len,DRC_TIME_OUT);
   if (ret < 0)
   {
      if (file->sock >= 0)
         DRC_closeSock(file->sock);
      LOG(LM_DEBUG,Fmtmsg("组件[%s] send packet failed!",fpub_GetCompname(lXmlhandle)),__func__)
      return -1;
   }
   return 0;
}

/*********************************************************
功能描述:   读取消息头信息
开发人员:   chenhh
修改日期:   2011-12-20
*********************************************************/
int DRC_readHead(HXMLTREE lXmlhandle,DRC_stFile * file,DRC_stFileBean * bean)
{
   int ret,headLen;
   char headLenCont[5];

   LOG(LM_DEBUG,Fmtmsg("组件[%s] start to read head",fpub_GetCompname(lXmlhandle)),__func__)

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
   LOG(LM_DEBUG,Fmtmsg("组件[%s] xml=%s",fpub_GetCompname(lXmlhandle),bean->headCont),__func__)

   DRC_convertXmlToBean(lXmlhandle,bean);
   return ret;
}

/*********************************************************
功能描述:   与文件传输服务器认证
开发人员:   chenhh
修改日期:   2011-12-20
*********************************************************/
int DRC_doAuth(HXMLTREE lXmlhandle,DRC_stFile * file,DRC_stFileBean * bean)
{
   int ret;

   /*根据状态设置请求的消息状态码*/
   sprintf(bean->fileMsgFlag,file->putFlag==1?DRC_PUT_AUTH:DRC_GET_AUTH);

   /*将bean对象转换成XML报文*/
   DRC_convertBeanToXml(bean);

   /*发送请求的头消息*/
   ret= DRC_writeHead(lXmlhandle,file,bean);
   if (ret<0)
   {
      LOG(LM_STD,Fmtmsg("组件[%s] 写入请求头信息出错",fpub_GetCompname(lXmlhandle)),__func__)
      return -1;
   }

   /*读取响应的头消息*/
   ret= DRC_readHead(lXmlhandle,file,bean);

   /*判断认证的状态*/
   if (bean->authFlag==1)
   {
      LOG(LM_DEBUG,Fmtmsg("组件[%s] 认证成功",fpub_GetCompname(lXmlhandle)),__func__)
      return 0;
   }
   else
   {
      LOG(LM_DEBUG,Fmtmsg("组件[%s] 认证失败",fpub_GetCompname(lXmlhandle)),__func__)
      return -1;
   }
}

/*********************************************************
功能描述:   将int转换成字符数据
开发人员:   chenhh
修改日期:   2011-12-20
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
功能描述:   从文件中读取数据
开发人员:   chenhh
修改日期:   2011-12-20
*********************************************************/
int DRC_readFile(HXMLTREE lXmlhandle, DRC_stFile * file,DRC_stFileBean * bean)
{
   LOG(LM_DEBUG,Fmtmsg("组件[%s] read from file,num=%d",fpub_GetCompname(lXmlhandle),bean->pieceNum),__func__)
   /*读取文件内容*/
   memset(bean->fileCont,0x00,sizeof(bean->fileCont));
   bean->contLen=0;
   bean->contLen=fread(bean->fileCont,1,bean->pieceNum,file->destFile);

   /*判断是否最后一个分片*/
   if (bean->contLen!=bean->pieceNum||bean->contLen==-1)
      bean->lastPiece=1;

   /*md5运算并更新md5 内容结构*/
   if (-1!=bean->contLen)
   {
      DRC_md5Update(&(file->struMd5Context), bean->fileCont, bean->contLen);
   }

   /*最后一次运算,生成最终的32位md5字符*/
   if (1==bean->lastPiece)
   {
      DRC_md5Final32(bean->md5, &(file->struMd5Context));
   }
   LOG(LM_DEBUG,Fmtmsg("组件[%s] read len=%d",fpub_GetCompname(lXmlhandle),bean->contLen),__func__)
   return 0;
}

/*********************************************************
功能描述:   写入文件内容
开发人员:   chenhh
修改日期:   2011-12-20
*********************************************************/
int DRC_writeCont(HXMLTREE lXmlhandle,DRC_stFile * file,DRC_stFileBean * bean)
{
   int ret,len,oLen;
   char fileLenCont[5];

   LOG(LM_DEBUG,Fmtmsg("组件[%s] start to wriete cont",fpub_GetCompname(lXmlhandle)),__func__)
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
功能描述:   查找对应的字符串
开发人员:   chenhh
修改日期:   2011-12-20
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
功能描述:   处理XML中的一个数据域
开发人员:   chenhh
修改日期:   2011-12-20
*********************************************************/
int DRC_getOneField(char * xml,int * offset,int iLen,char * name,char * value)
{
   int s,e1,e2,ret;
   while(*offset<iLen)
   {
      /*提取字段名称*/
      if (DRC_goToStr(xml,offset,iLen,"<")==0)
         break;
      s=*offset;

      if (DRC_goToStr(xml,offset,iLen,">")==0)
         break;
      e1=*offset;
      memcpy(name,xml+s,e1-s-1);

      /*提取字段内容*/
      if (DRC_goToStr(xml,offset,iLen,"<")==0)
         break;
      e2=*offset;
      memcpy(value,xml+e1,e2-e1-1);
      DRC_goToStr(xml,offset,iLen,">");

      break;
   }
}

/*********************************************************
功能描述:   设置数据到bean中
开发人员:   chenhh
修改日期:   2011-12-20
*********************************************************/
int DRC_setDataToBean(HXMLTREE lXmlhandle,DRC_stFileBean * bean,char * name,char * value)
{
   int len = strlen(name);
   int valLen = strlen(value);

   LOG(LM_DEBUG,Fmtmsg("组件[%s] set value %s=[%s]",fpub_GetCompname(lXmlhandle),name,value),__func__)
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
功能描述:   转换XML数据到bean对象
开发人员:   chenhh
修改日期:   2011-12-20
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
功能描述:   将字符数组转换成int
开发人员:   chenhh
修改日期:   2011-12-20
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
功能描述:   完成文件上传
开发人员:   chenhh
修改日期:   2011-12-20
*********************************************************/
int DRC_doPutFile(HXMLTREE lXmlhandle,DRC_stFile * file,DRC_stFileBean * bean)
{
   int ret;
   bean->fileIndex=0;

   while(1)
   {
      /* 文件分片加1 */
      bean->fileIndex++;

      /* 文件设置文件上传的标志 */
      memset(bean->fileMsgFlag,0x00,sizeof(bean->fileMsgFlag));
      sprintf(bean->fileMsgFlag,DRC_PUT);

      /* 读取文件 */
      DRC_readFile(lXmlhandle,file,bean);

      /* 读取消息头 */
      ret= DRC_writeHead(lXmlhandle,file,bean);
      if (ret<0)
      {
         LOG(LM_STD,Fmtmsg("组件[%s] 写入消息头出错",fpub_GetCompname(lXmlhandle)),__func__)
         return -1;
      }

      /* 写入文件内容 */
      ret = DRC_writeCont(lXmlhandle,file,bean);
      if (ret<0)
      {
         LOG(LM_STD,Fmtmsg("组件[%s] 写入文件分片出错",fpub_GetCompname(lXmlhandle)),__func__)
         return -1;
      }

      /*读取服务器响应状态*/
      ret= DRC_readHead(lXmlhandle,file,bean);
      if (ret<0)
      {
         LOG(LM_STD,Fmtmsg("组件[%s] 读取服务器响应状态出错",fpub_GetCompname(lXmlhandle)),__func__)
         return -1;
      }

      /* 判断服务器响应状态 */
      if (memcmp(bean->fileMsgFlag,"000000",6)!=0)
      {
         LOG(LM_STD,Fmtmsg("组件[%s] 服务响应状态异常，异常码[%s]",fpub_GetCompname(lXmlhandle),bean->fileMsgFlag),__func__)
         return -1;
      }

      /* 判断是否是文件的最后一个分片 */
      if (bean->lastPiece==1)
      {
         LOG(LM_STD,Fmtmsg("组件[%s] 处理到最后一个分片",fpub_GetCompname(lXmlhandle)),__func__)
         break;
      }
   }

   return 0;
}

/*********************************************************
功能描述:   文件传输服务器文件上传
开发人员:   chenhh
修改日期:   2011-12-20
*********************************************************/
int DRC_ftpput(HXMLTREE lXmlhandle, char * remoteFileName,char * localFileName, char * localFileMd5, int scrtFlag)
{
   DRC_stFile * file;
   DRC_stFileBean * bean;
   int ret;

   remoteFileName=DRC_StrPack(remoteFileName);
   localFileName=DRC_StrPack(localFileName);
 
   /*初始化配置*/
   ret = DRC_InitConfig();
   if (ret!=0)
      return -4;

   /*构建文件对象*/
   file = DRC_initFile(lXmlhandle,remoteFileName,localFileName,1);
   bean = DRC_initFileBean(lXmlhandle,remoteFileName,localFileName);
   bean->scrtFlag = scrtFlag;

   /*创建文件初始化是否成功*/
   if (file==NULL||bean==NULL)
   {
      DRC_cleanResource(lXmlhandle,file,bean);
      return -1;
   }

   /*建立连接*/
   ret=DRC_doConnect(lXmlhandle,file,bean);
   if (ret<0)
   {
      LOG(LM_STD,Fmtmsg("组件[%s] 建立连接失败", fpub_GetCompname(lXmlhandle)),__func__)
      DRC_cleanResource(lXmlhandle,file,bean);
      return -1;
   }

   /*安全认证*/
   ret=DRC_doAuth(lXmlhandle,file,bean);
   if (ret<0)
   {
      LOG(LM_STD,Fmtmsg("组件[%s] 权限认证失败", fpub_GetCompname(lXmlhandle)),__func__)
      DRC_cleanResource(lXmlhandle,file,bean);
      return -1;
   }

   /*上传文件*/
   ret=DRC_doPutFile(lXmlhandle,file,bean);
   if (ret<0)
   {
      LOG(LM_STD,Fmtmsg("组件[%s] 文件下载失败", fpub_GetCompname(lXmlhandle)),__func__)
      DRC_cleanResource(lXmlhandle,file,bean);
      return -1;
   }

   /*设置MD5校验码*/
   memcpy(localFileMd5, bean->md5, sizeof(bean->md5));

   /*释放资源*/
   DRC_cleanResource(lXmlhandle,file,bean);
   return 0;
}

/*********************************************************
功能描述:   读取文件内容
开发人员:   chenhh
修改日期:   2011-12-20
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

   LOG(LM_DEBUG,Fmtmsg("组件[%s] scrtFlag=%d",fpub_GetCompname(lXmlhandle),bean->scrtFlag),__func__)
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
   LOG(LM_DEBUG,Fmtmsg("组件[%s] 读取数据长度len=%d",fpub_GetCompname(lXmlhandle),fileLen),__func__)
   return ret;
}

/*********************************************************
功能描述:   写入数据到文件
开发人员:   chenhh
修改日期:   2011-12-20
*********************************************************/
int DRC_writeFile(HXMLTREE lXmlhandle,DRC_stFile * file,DRC_stFileBean * bean)
{
   LOG(LM_DEBUG,Fmtmsg("组件[%s] write to file,len=[%d]",fpub_GetCompname(lXmlhandle),bean->contLen),__func__)
   fwrite(bean->fileCont,1,bean->contLen,file->destFile);

   /*md5运算并更新md5 内容结构*/
   if (-1!=bean->contLen)
   {
      DRC_md5Update(&(file->struMd5Context), bean->fileCont, bean->contLen);
   }

   return 0;
}

/*********************************************************
功能描述:   完成文件下载，重命名为真实文件名
开发人员:   chenhh
修改日期:   2011-12-20
*********************************************************/
int DRC_finishFile(HXMLTREE lXmlhandle,DRC_stFile * file,DRC_stFileBean * bean)
{
   int ret=-1;
   char md5[33];

   fclose(file->destFile);
   file->destFile=NULL;

   memset(md5,0x00,sizeof(md5));
   DRC_md5Final32(md5, &(file->struMd5Context));

   LOG(LM_DEBUG,Fmtmsg("组件[%s] file md5 remotevalue=[%s],localvalue=[%s]",fpub_GetCompname(lXmlhandle),md5,bean->md5),__func__)
   if (memcmp(md5,bean->md5,32)==0)
   {
      LOG(LM_DEBUG,Fmtmsg("组件[%s] checking md5 of download file is successed:%s",fpub_GetCompname(lXmlhandle),md5),__func__)
      ret=rename(file->tmpFileName,file->localFileName);
      if (0!=ret)
      {
         remove(file->tmpFileName);  
      }
   }
   else
   {
      LOG(LM_DEBUG,Fmtmsg("组件[%s] checking md5 of download file is error:remotevalue=[%s],localvalue=[%s]",fpub_GetCompname(lXmlhandle),md5,bean->md5),__func__)
      remove(file->tmpFileName);
   }
   return ret;
}

/*********************************************************
功能描述:   完成文件下载
开发人员:   chenhh
修改日期:   2011-12-20
*********************************************************/
int DRC_doGetFile(HXMLTREE lXmlhandle,DRC_stFile * file,DRC_stFileBean * bean)
{
   int ret;
   bean->fileIndex=0;

   while(1)
   {
      /* 文件分片加1 */
      bean->fileIndex++;

      /* 文件设置文件上传的标志 */
      memset(bean->fileMsgFlag,0x00,sizeof(bean->fileMsgFlag));
      sprintf(bean->fileMsgFlag,DRC_GET);

      /* 写入消息头 */
      ret= DRC_writeHead(lXmlhandle,file,bean);
      if (ret<0)
      {
         LOG(LM_STD,Fmtmsg("组件[%s] 写入消息头出错",fpub_GetCompname(lXmlhandle)),__func__)
         return -1;
      }

      /* 读取消息头 */
      ret= DRC_readHead(lXmlhandle,file,bean);
      if (ret<0)
      {
         LOG(LM_STD,Fmtmsg("组件[%s] 读取消息头出错",fpub_GetCompname(lXmlhandle)),__func__)
         return -1;
      }

      /* 判断处理状态 */
      if (memcmp(bean->fileMsgFlag,"000000",6)==0)
      {
         ret=DRC_readCont(lXmlhandle,file,bean);
         if (ret<0)
         {
            LOG(LM_STD,Fmtmsg("组件[%s] 读取内容失败",fpub_GetCompname(lXmlhandle)),__func__)
            return -1;
         }
         
         /* 写入到文件中 */
         DRC_writeFile(lXmlhandle,file,bean);
         if (bean->lastPiece==1)
         {
             /*最后一个分片*/
             LOG(LM_DEBUG,Fmtmsg("组件[%s] 读取到最后一个文件分片",fpub_GetCompname(lXmlhandle)),__func__)
             break;
         }
         
      }
      else
      {
         LOG(LM_STD,Fmtmsg("组件[%s] 处理失败，服务器返回的状态是[%s]",fpub_GetCompname(lXmlhandle),bean->fileMsgFlag),__func__)
         return -1;
      }   
   }
   
   /* 完成文件下载 */
   ret=DRC_finishFile(lXmlhandle,file,bean);
   return ret;
}

/*********************************************************
功能描述:   文件传输服务器文件下载
开发人员:   chenhh
修改日期:   2011-12-20
*********************************************************/
int DRC_ftpget(HXMLTREE lXmlhandle,char * remoteFileName,char * localFileName, char * localFileMd5, int scrtFlag)
{
   DRC_stFile * file;
   DRC_stFileBean * bean;
   int ret;

   remoteFileName=DRC_StrPack(remoteFileName);
   localFileName=DRC_StrPack(localFileName);

   /*初始化配置*/
   ret = DRC_InitConfig();
   if (ret!=0)
      return -4;

   /*构建文件对象*/
   file = DRC_initFile(lXmlhandle,remoteFileName,localFileName,0);
   bean = DRC_initFileBean(lXmlhandle,remoteFileName,localFileName);
   bean->scrtFlag = scrtFlag;

   /*创建文件初始化是否成功*/
   if (file==NULL||bean==NULL)
   {
      DRC_cleanResource(lXmlhandle,file,bean);
      return -1;
   }

   /*建立连接*/
   ret=DRC_doConnect(lXmlhandle,file,bean);
   if (ret<0)
   {
      LOG(LM_STD,Fmtmsg("组件[%s] 建立连接失败",fpub_GetCompname(lXmlhandle)),__func__)
      DRC_cleanResource(lXmlhandle,file,bean);
      return -1;
   }

   /*安全认证*/
   ret=DRC_doAuth(lXmlhandle,file,bean);
   if (ret<0)
   {
      LOG(LM_STD,Fmtmsg("组件[%s] 权限认证失败",fpub_GetCompname(lXmlhandle)),__func__)
      DRC_cleanResource(lXmlhandle,file,bean);
      return -1;
   }
    
   /*下载文件*/
   ret=DRC_doGetFile(lXmlhandle,file,bean);
   if (ret<0)
   {
      LOG(LM_STD,Fmtmsg("组件[%s] 文件下载失败",fpub_GetCompname(lXmlhandle)),__func__)
      DRC_cleanResource(lXmlhandle,file,bean);
      return -1;
   }

   /*文件的MD5校验*/
   memcpy(localFileMd5, bean->md5, sizeof(bean->md5));
    
   /*释放资源*/
   DRC_cleanResource(lXmlhandle,file,bean);
   return 0;
}

/************************************************************************
动态组件函数定义
组件函数名称:DRC_FTPPUT
组件名称:DRC_FTPPUT
组件功能:
组件参数:
 序号 参数类型  参数名称         资源类别     缺省值  可空  参数说明
  1   1-输入   目标文件名     416-                     N    目标文件名
  2   1-输入   本地文件名     416-                     N    本地文件名
  3   1-输入   加密标志       416-                     N    加密标志 0-不加密 1-加密
  4   1-输出   MD5值节点      401-                     N    MD5值节点

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
IRESULT DRC_FTPPUT(HXMLTREE lXmlhandle)
{
   char md5node[256], md5[33];
   char sbuf[256],lfilename[256],rfilename[256];
   int  iParas, iret, mflag;

   fpub_InitSoComp(lXmlhandle);

   LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),__func__)

   memset(md5node,0x00,sizeof(md5node));

   COMP_PARACOUNTCHKMIN(4)
   memset(sbuf,0x00,sizeof(sbuf));
   COMP_GETPARSEPARAS(1,sbuf,"目标文件名");
   memset(rfilename,0x00,sizeof(rfilename));
   pstrcopy(rfilename,sbuf,sizeof(rfilename));

   memset(sbuf,0x00,sizeof(sbuf));
   COMP_GETPARSEPARAS(2,sbuf,"本地文件名");
   memset(lfilename,0x00,sizeof(lfilename));
   pstrcopy(lfilename,sbuf,sizeof(lfilename));

   memset(sbuf,0x00,sizeof(sbuf));
   COMP_GETPARSEPARAS(3,sbuf,"加密标志");
   mflag=sbuf[0] - '0';

   COMP_GETPARSEPARAS(4,md5node,"MD5值节点")
 
   memset(md5,0x00,sizeof(md5));
   LOG(LM_DEBUG,Fmtmsg("组件[%s] rfilename[%s],lfilename[%s],md5[%s],mflag[%d]",fpub_GetCompname(lXmlhandle),rfilename,lfilename,md5,mflag),__func__)
   iret=DRC_ftpput(lXmlhandle,rfilename,lfilename,md5,mflag);
   if (iret !=0)
   {
      fpub_SetMsg(lXmlhandle,MID_YW_ERROR,Fmtmsg("文件PUT失败"));
      fpub_SetCompStatus(lXmlhandle,-1);
      return -1;
   }
   COMP_SOFTSETXML(md5node,md5);
   fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
#ifdef DEBUG
   LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)),__func__)
#endif
   return 0;
}

/************************************************************************
动态组件函数定义
组件函数名称:DRC_FTPGET
组件名称:DRC_FTPGET
组件功能:
组件参数:
 序号 参数类型  参数名称         资源类别     缺省值  可空  参数说明
  1   1-输入   目标文件名     416-                     N    目标文件名
  2   1-输入   本地文件名     416-                     N    本地文件名
  3   1-输入   加密标志       416-                     N    加密标志 0-不加密 1-加密
  4   1-输出   MD5值路径      401-                     N    MD5值路径

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
IRESULT DRC_FTPGET(HXMLTREE lXmlhandle)
{
   char md5node[256], md5[33];
   char sbuf[256],lfilename[256],rfilename[256];
   int  iParas, iret, mflag;

   fpub_InitSoComp(lXmlhandle);

#ifdef DEBUG
   LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),__func__)
#endif

   memset(md5node,0x00,sizeof(md5node));

   COMP_PARACOUNTCHKMIN(4)
   memset(sbuf,0x00,sizeof(sbuf));
   COMP_GETPARSEPARAS(1,sbuf,"目标文件名");
   memset(rfilename,0x00,sizeof(rfilename));
   pstrcopy(rfilename,sbuf,sizeof(rfilename));

   memset(sbuf,0x00,sizeof(sbuf));
   COMP_GETPARSEPARAS(2,sbuf,"本地文件名");
   memset(lfilename,0x00,sizeof(lfilename));
   pstrcopy(lfilename,sbuf,sizeof(lfilename));

   memset(sbuf,0x00,sizeof(sbuf));
   COMP_GETPARSEPARAS(3,sbuf,"加密标志");
   mflag=sbuf[0] - '0';

   COMP_GETPARSEPARAS(4,md5node,"MD5值节点")
 
#ifdef DEBUG
   LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)),__func__)
#endif
   memset(md5,0x00,sizeof(md5));
   iret=DRC_ftpget(lXmlhandle,rfilename,lfilename,md5,mflag);
   if (iret !=0)
   {
      fpub_SetMsg(lXmlhandle,MID_YW_ERROR,Fmtmsg("文件GET失败"));
      fpub_SetCompStatus(lXmlhandle,-1);
      return -1;
   }
   COMP_SOFTSETXML(md5node,md5);
   fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
   return 0;
}
