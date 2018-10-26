/********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合应用平台（GAPS）项目
版    本:V4.1.00
操作系统:AIX/Linux/HP-UX
文件名称:ufunc_sample.c
文件描述:用户函数实例
项 目 组:GAPS研发组
程 序 员:Tianhc
发布日期:
修    订:Tianhc
修改日期:2006-3-22 20:38
*********************************************************************/
/*
修改记录
修改日期:2009-3-25 20:10:39
修 改 人:Tianhc
修改内容:
  关于外挂函数的使用说明
  外挂函数两种使用场景：
    1、报文转换过程中，需要对数据进行额外处理或报文进行额外处理
       如：在报文中指定长度为HEX字符方式表示，此时需要转成10进制字符串长度方可处理；
    2、对文件转换进行额外处理；

函数原型：
HXMLTREE iXmlhandle    --当前的XML句柄
char     *sxmbuf          --当前正在处理字段，根据配置已得到的内容,修改后会被回写
int      *ilen_src        --当前正在处理字段，根据配置已得到的长度，修改后会被回写
int      Maxlen           --sxmbuf的最大长度
char     *spkg_buf        --指向当前报文内容的指针
int      *ilen_pkg        --暂不使用
int      *ipos_curr       --指向当前解析位置的指针
char     *para            --当前函数格式化参数
void     *pz_curr         --在ICXP型报文中为NULL, 在8583报文中，指向bitmap的指针
void     *datalink        --在ICXP型报文中为NULL，在8583报文中，指向8583包文域内容缓冲链表


extern IRESULT func_ConvertsHEX2sINT(HXMLTREE iXmlhandle,char *sxmbuf,int *ilen_src,int Maxlen,
           char * spkg_buf,int *ilen_pkg,int *ipos_curr,char *para,
           void *pz_curr,void * datalink)

例如：
   ICXP解包中，得到报文字段内容为 '01',需要转换为"USD"，则
   if (strcmp(sxmbuf, "01") == 0)
   {
     strcpy(sxmbuf, "USD");
     *ilen_src = 3;
   }

*/
#include <stdio.h>
#include "gaps_head.h"


extern IRESULT SAMP_Func1(HXMLTREE, char*);
extern IRESULT func_SubStr(HXMLTREE, char*, int*, int, char*, int*, int*, char*, void*, void*);
extern IRESULT func_ConvertLLVAR(HXMLTREE, char*, int*, int, char*, int*, int*, char*, void*, void*);
extern IRESULT func_ConvertsHEX2sINT(HXMLTREE, char*, int*, int, char*, int*, int*, char*, void*, void*);
extern IRESULT func_Char2Int(HXMLTREE, char*, int*, int, char*, int*, int*, char*, void*, void*);
extern IRESULT func_Int2Char(HXMLTREE, char*, int*, int, char*, int*, int*, char*, void*, void*);
extern IRESULT func_AddHead(HXMLTREE, char*, int*, int, char*, int*, int*, char*, void*, void*);
/*提供给文件转换使用的函数,无相对位置*/
extern IRESULT func_reverse(HXMLTREE, char*, int, char*);


extern IRESULT SAMP_Func1(HXMLTREE iXmlhandle, char* sTmp)
{
  LOG(LM_DEBUG, sTmp, "SAMP_Func1")
  return 0;
}


/*取子串函数*/
static char *prv_substr(char *str, int index, int count)
{
  int len;
  static char buf[254];
  len = strlen(str);
  memset(buf, 0, sizeof(buf));
  if (( index <= len ) && ( index > 0 ))
  {
    if ( index + count > len + 1 )
      count = len - index + 1 ;
    memcpy(buf, str + index - 1, count);
  }
  return buf;
}


/*
   取子串函数，类似于DATA_StrCat组件的用法；
   传入
     sxmbuf --当前的值
     para   --当前的参数
     格式应该为5,2
*/
extern IRESULT func_SubStr(HXMLTREE iXmlhandle, char *sxmbuf, int *ilen_src, int Maxlen,
                             char * spkg_buf, int *ilen_pkg, int *ipos_curr, char *para,
                             void *pz_curr, void * datalink)
{
  int ipos1, ilen1, iret;
  char sbuf[254];
  printf(" --func_SubStr begin... buf[%s],para[%s]\n", sxmbuf, para);

  iret = GetListbyDiv(para, 1, sbuf, ',', '\\');
  if (iret < 0)
  {
    LOG(LM_STD, Fmtmsg("函数func_SubStr执行失败1,参数[%s]格式不正确!", para), "ERROR");
    return iret;
  }
  ipos1 = atoi(sbuf);
  iret = GetListbyDiv(para, 2, sbuf, ',', '\\');
  if (iret < 0)
  {
    LOG(LM_STD, Fmtmsg("函数func_SubStr执行失败2,参数[%s]格式不正确!", para), "ERROR");
    return iret;
  }
  ilen1 = atoi(sbuf);
  snprintf(sbuf, sizeof(sbuf), "%s", sxmbuf);
  snprintf(sxmbuf, Maxlen, "%s", prv_substr(sxmbuf, ipos1, ilen1));
  /*
  LOG(LM_STD,Fmtmsg("func_SubStr函数.[%s]==>[%s]",sbuf,sxmbuf),"DEBUG");
  */
  return 0;
}

/*
   Tianhc 2005-10-15 20:57
   将数据内容进行LLVAR转换
   增加长度的模式
     SLL   --字符方式的长度，2位
     HLL     --HEX方式的长度，2位
     BLL     --BIN方式的长度，2位或4位
     组包时，考虑到长度为0-1位，或0x05等情况的出现，必须将字符类型设为HEX型
*/
extern IRESULT func_ConvertLLVAR(HXMLTREE iXmlhandle, char *sxmbuf, int *ilen_src, int Maxlen,
                                   char * spkg_buf, int *ilen_pkg, int *ipos_curr, char *para,
                                   void *pz_curr, void * datalink)
{
  int ilen, ilen2;
  long ilen_4;
  short int ilen_2;
  char slen[50];
  char sbuf[4096], pchar;

  if (*ilen_src > sizeof(sbuf) + 10)
  {
    LOG(LM_STD, Fmtmsg("函数func_Getlen执行失败1,数据内容太长，无法处理"), "ERROR");
    return -1;
  }
  /*memcpy(sbuf,sxmbuf,*ilen_src);*/
  strcpy(sbuf, sxmbuf);

  ilen = strlen(sxmbuf);
  ilen2 = strlen(para + 1);
  if (para[0] == 'S')
  {
    sprintf(slen, "%0*d", ilen2, ilen);
    memcpy(sxmbuf, slen, strlen(slen));
    memcpy(sxmbuf + strlen(slen), sbuf, *ilen_src);
  }
  else if (para[0] == 'H')
  {
    sprintf(slen, "%0*X", ilen2, ilen);
    memcpy(sxmbuf, slen, strlen(slen));
    memcpy(sxmbuf + strlen(slen), sbuf, *ilen_src);
  }
  else if (para[0] == 'B' )
  {
    if (ilen2 == 1)
    {
      if (ilen > 255)
      {
        LOG(LM_STD, Fmtmsg("函数func_Getlen执行失败1,数据内容太长[%d]!", ilen), "ERROR");
        return -1;
      }
      LOG(LM_DEBUG, Fmtmsg("      --> func toLVAR,len[%d],cont[%s]", ilen, sxmbuf), "DEBUG");
      pchar = ilen ;
      /*memcpy(sxmbuf,&pchar,1);*/
      sxmbuf[0] = pchar;
      memcpy(sxmbuf + 1, sbuf, ilen);
      /*转成HEX字符方式*/
      memset(sbuf, 0, sizeof(sbuf));
      HEX_2_DSP(sxmbuf, sbuf, ilen + 1);
      /*LOG(LM_STD,Fmtmsg("转换后内容[%s][%s],ilen[%d]",sxmbuf,sbuf,ilen),"DEBUG");*/
      strcpy(sxmbuf, sbuf);

    }
    else if (ilen2 == 2)
    {
      ilen_2 = ilen ;
      LOG(LM_DEBUG, Fmtmsg("      --> func toLLVAR,len[%d]", ilen), "DEBUG");
      memcpy(slen, &ilen_2, sizeof(ilen_2));
      memcpy(sxmbuf, slen, sizeof(ilen_2));
      memcpy(sxmbuf + sizeof(ilen_2), sbuf, ilen);
      /*转成HEX字符方式*/
      memset(sbuf, 0, sizeof(sbuf));
      HEX_2_DSP(sxmbuf, sbuf, ilen + sizeof(ilen_2));
      strcpy(sxmbuf, sbuf);
    }
    else if (ilen2 == 4)
    {
      ilen_4 = ilen;
      LOG(LM_DEBUG, Fmtmsg("      --> func toLLLLVAR,len[%d]", ilen), "DEBUG");
      memcpy(slen, &ilen_4, sizeof(ilen_4));
      memcpy(sxmbuf, slen, sizeof(ilen_4));
      memcpy(sxmbuf + sizeof(ilen_4), sbuf, ilen);
      /*转成HEX字符方式*/
      memset(sbuf, 0, sizeof(sbuf));
      HEX_2_DSP(sxmbuf, sbuf, ilen + sizeof(ilen_4));
      strcpy(sxmbuf, sbuf);
    }
    else
    {
      LOG(LM_STD, Fmtmsg("函数func_Getlen执行失败1,参数[%s]格式不正确!", para), "ERROR");
      return -1;
    }
  }
  else
  {
    LOG(LM_STD, Fmtmsg("函数func_Getlen执行失败2,参数[%s]格式不正确!", para), "ERROR");
    return -2;
  }
  return 0;
}




/*
   Tianhc 2005-10-15 20:57
   16进制字符方式转成10进制数字方式
*/
extern IRESULT func_ConvertsHEX2sINT(HXMLTREE iXmlhandle, char *sxmbuf, int *ilen_src, int Maxlen,
                                       char * spkg_buf, int *ilen_pkg, int *ipos_curr, char *para,
                                       void *pz_curr, void * datalink)
{
  char sbuf[255];
  int iret;
  iret = prv_shex2sint(sxmbuf, sbuf);
  LOG(LM_DEBUG, Fmtmsg("      --> func shex2sint,[%s]=>[%s]", sxmbuf, sbuf), "DEBUG");
  strcpy(sxmbuf, sbuf);
  return iret;
}


/*
   Tianhc
   将HEX字符方式的长度，转为正常的字符串长度
*/
int prv_shex2sint(char *shex, char*sdest)
{

  int ilen, i, j, ibit;
  long lret = 0;
  unsigned int oxflag[] = {0x01, 0x10, 0x100, 0x1000, 0x10000, 0x100000, 0x1000000, 0x10000000};
  char pchar;
  strcpy(sdest, "0");
  ilen = strlen(shex);
  if (ilen == 0)
  {
    return 0;
  }
  if (ilen > 8)
    return -2;
  for ( j = 0, i = ilen - 1;i >= 0;i--, j++)
  {
    pchar = shex[i];
    if ( pchar >= 'a' && pchar <= 'f')
    {
      ibit = pchar - 'a' + 10 ;
    }
    else  if ( pchar >= 'A' && pchar <= 'F')
    {
      ibit = pchar - 'A' + 10 ;
    }
    else if ( pchar >= '0' && pchar <= '9')
    {
      ibit = pchar - '0' ;
    }
    else  /*输入错误*/
    {
      LOG(LM_STD, Fmtmsg("函数shex2sint执行失败,pchar[%c]不正确!", pchar), "ERROR");
      return -1;
    }
    lret = lret + ibit * oxflag[j];
  }
  sprintf(sdest, "%ld", lret);
  return 0;
}


/*
   Tianhc 2005-10-15 20:57
   将 char --> int
*/
extern IRESULT func_Char2Int(HXMLTREE iXmlhandle, char *sxmbuf, int *ilen_src, int Maxlen,
                               char * spkg_buf, int *ilen_pkg, int *ipos_curr, char *para,
                               void *pz_curr, void * datalink)
{
  char pchar;
  pchar = sxmbuf[0];
  if (*ilen_src != 1 )
  {
    LOG(LM_DEBUG, Fmtmsg("      --> func Char2Int err,本函数数据源长度只能为1"), "ERROR");
    return -1;
  }
  LOG(LM_DEBUG, Fmtmsg("      --> func Char2Int,[%c]=>[%d]", pchar, pchar), "DEBUG");
  sprintf(sxmbuf, "%d", pchar);
  return 0;
}

/*
   Tianhc 2005-11-16 16:21
   将 int --> char
*/
extern IRESULT func_Int2Char(HXMLTREE iXmlhandle, char *sxmbuf, int *ilen_src, int Maxlen,
                               char * spkg_buf, int *ilen_pkg, int *ipos_curr, char *para,
                               void *pz_curr, void * datalink)
{
  int inum;
  inum = atoi(sxmbuf);
  LOG(LM_DEBUG, Fmtmsg("      --> func Int2Char,[%s]=>[%c]", sxmbuf, inum), "DEBUG");
  sprintf(sxmbuf, "%c", inum);
  return 0;
}

/*
   增加一个长度的报头
   对于已经预留长度报文
   报文总长度不变,只是替换前N个字符
*/
extern IRESULT func_AddHead(HXMLTREE iXmlhandle, char *sxmbuf, int *ilen_src, int Maxlen,
                              char * spkg_buf, int *ilen_pkg, int *ipos_curr, char *para,
                              void *pz_curr, void * datalink)
{
  int ilen2;
  short int ilen_2;
  int ilen_4;
  char slen[20];
  LOG(LM_STD, Fmtmsg("  ipos_curr[%d],ilen_pkg[%d],ilen_src[%d],Maxlen[%d]...",
                     *ipos_curr, *ilen_pkg, *ilen_src, Maxlen), "DEBUG");
  ilen2 = strlen(para + 1);
  if (para[0] == 'S')
  {
    sprintf(slen, "%0*d", ilen2, *ipos_curr);
    memcpy(spkg_buf, slen, ilen2);
  }
  else if (para[0] == 'B')
  {
    if (ilen2 == 2)
    {
      ilen_2 = *ipos_curr;
      ilen_2 = htons(ilen_2);  /*转为网络字节序*/
      memcpy(slen, &ilen_2, sizeof(ilen_2));
      memcpy(spkg_buf, slen, sizeof(ilen_2));
    }
    else if (ilen2 == 4)
    {
      ilen_4 = *ipos_curr;
      ilen_4 = htonl(ilen_4);  /*转为网络字节序*/
      memcpy(slen, &ilen_4, sizeof(ilen_4));
      memcpy(spkg_buf, slen, sizeof(ilen_4));
    }
    else
    {
      LOG(LM_STD, Fmtmsg("函数func_AddHead执行失败1,参数[%s]格式不正确!", para), "ERROR");
      return -1;
    }
  }
  else
  {
    LOG(LM_STD, Fmtmsg("函数func_AddHead执行失败1,参数[%s]格式不正确!", para), "ERROR");
    return -2;
  }
  return 0;
}

/*
   提供给文件转换时使用的函数，包含4个参数：
   1.XML句柄
   2.字段原内容
   3.该缓冲区最大长度
   4.函数的参数
     ---处理结果，成功则返回0并修改缓冲区，用传入的长度保证不能溢出
   本函数用于测试，将字符串反转,用于一正/一反,即unload时反转,load时再转回来...
*/
extern IRESULT func_reverse(HXMLTREE Xmlhandle, char *sfldvalue , int isize, char *sfldpara)
{
  int i, pchar;
  LOG(LM_DEBUG, Fmtmsg("  -->进入func_reverse函数,fldvalue[%s]", sfldvalue), "DEBUG2");
  for (i = 0;i < strlen(sfldvalue) / 2;i++)
  {
    pchar = sfldvalue[i];
    sfldvalue[i] = sfldvalue[strlen(sfldvalue)-i-1] ;
    sfldvalue[strlen(sfldvalue)-i-1] = pchar;
  }
  return 0;
}

/************************************************************************
函数声明:
int gaps32_checkfldrule(char *scont, char *srule)
函数功能:

输入参数:
         char *scont          当前请求的内容
         char *srule          当前的数据规则
返    回: 0-OK,1-不符合规则,-1-其它错误
限    制: 无
项 目 组:
程 序 员:Tianhc
发布日期:
修改日期:2006-5-15 15:40
说明：
  目前支持的表达式：
          AN10    数字或字母(不能包含特殊符号)，且必须为10位长度
          ANS[1..10]  任意字符，且必须为1-10位长度
          N6      必须为数字型6位长度(包括+-.)；
          N[1..6]    必须为数字型1-6位长度(包括+-.)；
  返回值 ：
    根据GAPSV4中数据字典规则，返回1为OK，其余为不OK

************************************************************************/
int gaps32_checkfldrule(char *para, char *val)
{
  int len_min,len_max,i;
  char s_end;
  char *pstr1,*pstr2;
  char sbuf[255],sdatatype[20];
  int flag_A=0,flag_N=0,flag_S=0;
  char *scont, *srule;
  
  scont = val;
  srule = para;

  trim(srule);
  if (strlen(srule) == 0)
  {
     LOG(LM_STD,Fmtmsg("  -->数据规则不能为空!"),"ERROR");
     return -1;
  }
  s_end=srule[strlen(srule)-1];
  if ((s_end != ']') && (s_end < '0') && (s_end > '9'))
  {
     LOG(LM_STD,Fmtmsg("  -->数据规则[%s]不正确!",srule),"ERROR");
     return -2;
  }
  memset(sdatatype,0,sizeof(sdatatype));
  if ( s_end == ']'  )  /*变长,取min,max*/
  {
     if ((pstr1 = strchr(srule,'[')) == NULL )
     {
         LOG(LM_STD,Fmtmsg("  -->数据规则[%s]不正确!",srule),"ERROR");
         return -3;
     }
     memcpy(sdatatype,srule,pstr1-srule);
     if ((pstr2 = strchr(pstr1,']')) == NULL )
     {
         LOG(LM_STD,Fmtmsg("  -->数据规则[%s]不正确!",srule),"ERROR");
         return -4;
     }
     memset(sbuf,0,sizeof(sbuf));
     memcpy(sbuf,pstr1+1,pstr2-pstr1-1);
     if ((pstr1=strstr(sbuf,"..")) == NULL )
     {
         LOG(LM_STD,Fmtmsg("  -->数据规则[%s]不正确!",srule),"ERROR");
         return -5;
     }
     *pstr1=0;
     len_min=atoi(sbuf);
     len_max=atoi(pstr1+2);
     if (len_max <= len_min)
     {
         LOG(LM_STD,Fmtmsg("  -->数据规则[%s]不正确!",srule),"ERROR");
         return -6;
     }
  }  else
  {
     for (i=0;i<strlen(srule);i++)
     {
         if ((srule[i] >='0') &&  (srule[i] <='9'))
         {
            memcpy(sdatatype,srule,i);
            break;
         }
     }
     if (i==strlen(srule))
     {
         LOG(LM_STD,Fmtmsg("  -->数据规则[%s]不正确!",srule),"ERROR");
         return -7;
     }
     strcpy(sbuf,srule+i);
     len_min=atoi(sbuf);
     len_max=len_min;
  }
  /*LOG(LM_DEBUG,Fmtmsg("   DEBUG:type[%s],min[%d]-[%d] ...",sdatatype,len_min,len_max),"DEBUG");*/
  if ((strlen(scont)>len_max) || (strlen(scont)<len_min))
  {
     LOG(LM_STD,Fmtmsg("  -->字段内容[%s]长度不正确,[%d]-[%d]",scont,len_min,len_max),"ERROR");
     return -11;
  }
  /*数据类型校验*/
  if (strcmp(sdatatype,"ANS")==0)   /*对于最常用的ANS,不用逐个校验其内容*/
     return 1;
  if (strchr(sdatatype,'A')!=NULL)
     flag_A=1;
  if (strchr(sdatatype,'N')!=NULL)
     flag_N=1;
  if (strchr(sdatatype,'S')!=NULL)
     flag_S=1;
  if   ( flag_A+flag_N+flag_S == 0 )
  {
     LOG(LM_STD,Fmtmsg("  -->数据规则[%s]类型不正确,只能为ANS三种!",srule),"ERROR");
     return -9;
  }
  for (i=0;i<strlen(scont);i++)
  {
    if (!flag_A)  /*不能为A*/
    {
      if (((scont[i] >= 'A') &&  (scont[i] <= 'Z')) ||
            ((scont[i] >= 'a') &&  (scont[i] <= 'z')))
      return -22;
    }
    if (!flag_N)  /*不能为N*/
    {
      if ((scont[i] >= '0') && (scont[i] <= '9'))
        return -23;
    }
    if (!flag_S)  /*不能为S,除AN之外的所有字符认为是S*/
    {
     if (!((((scont[i] >= 'A') &&  (scont[i] <= 'Z')) || ((scont[i] >= 'a') &&  (scont[i] <= 'z'))) ||
           ((scont[i] >= '0') && (scont[i] <= '9'))))
        return -24;
    }
  }
  return 1;
}


