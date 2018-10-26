/********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺ�Ӧ��ƽ̨��GAPS����Ŀ
��    ��:V4.1.00
����ϵͳ:AIX/Linux/HP-UX
�ļ�����:ufunc_sample.c
�ļ�����:�û�����ʵ��
�� Ŀ ��:GAPS�з���
�� �� Ա:Tianhc
��������:
��    ��:Tianhc
�޸�����:2006-3-22 20:38
*********************************************************************/
/*
�޸ļ�¼
�޸�����:2009-3-25 20:10:39
�� �� ��:Tianhc
�޸�����:
  ������Һ�����ʹ��˵��
  ��Һ�������ʹ�ó�����
    1������ת�������У���Ҫ�����ݽ��ж��⴦����Ľ��ж��⴦��
       �磺�ڱ�����ָ������ΪHEX�ַ���ʽ��ʾ����ʱ��Ҫת��10�����ַ������ȷ��ɴ���
    2�����ļ�ת�����ж��⴦��

����ԭ�ͣ�
HXMLTREE iXmlhandle    --��ǰ��XML���
char     *sxmbuf          --��ǰ���ڴ����ֶΣ����������ѵõ�������,�޸ĺ�ᱻ��д
int      *ilen_src        --��ǰ���ڴ����ֶΣ����������ѵõ��ĳ��ȣ��޸ĺ�ᱻ��д
int      Maxlen           --sxmbuf����󳤶�
char     *spkg_buf        --ָ��ǰ�������ݵ�ָ��
int      *ilen_pkg        --�ݲ�ʹ��
int      *ipos_curr       --ָ��ǰ����λ�õ�ָ��
char     *para            --��ǰ������ʽ������
void     *pz_curr         --��ICXP�ͱ�����ΪNULL, ��8583�����У�ָ��bitmap��ָ��
void     *datalink        --��ICXP�ͱ�����ΪNULL����8583�����У�ָ��8583���������ݻ�������


extern IRESULT func_ConvertsHEX2sINT(HXMLTREE iXmlhandle,char *sxmbuf,int *ilen_src,int Maxlen,
           char * spkg_buf,int *ilen_pkg,int *ipos_curr,char *para,
           void *pz_curr,void * datalink)

���磺
   ICXP����У��õ������ֶ�����Ϊ '01',��Ҫת��Ϊ"USD"����
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
/*�ṩ���ļ�ת��ʹ�õĺ���,�����λ��*/
extern IRESULT func_reverse(HXMLTREE, char*, int, char*);


extern IRESULT SAMP_Func1(HXMLTREE iXmlhandle, char* sTmp)
{
  LOG(LM_DEBUG, sTmp, "SAMP_Func1")
  return 0;
}


/*ȡ�Ӵ�����*/
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
   ȡ�Ӵ�������������DATA_StrCat������÷���
   ����
     sxmbuf --��ǰ��ֵ
     para   --��ǰ�Ĳ���
     ��ʽӦ��Ϊ5,2
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
    LOG(LM_STD, Fmtmsg("����func_SubStrִ��ʧ��1,����[%s]��ʽ����ȷ!", para), "ERROR");
    return iret;
  }
  ipos1 = atoi(sbuf);
  iret = GetListbyDiv(para, 2, sbuf, ',', '\\');
  if (iret < 0)
  {
    LOG(LM_STD, Fmtmsg("����func_SubStrִ��ʧ��2,����[%s]��ʽ����ȷ!", para), "ERROR");
    return iret;
  }
  ilen1 = atoi(sbuf);
  snprintf(sbuf, sizeof(sbuf), "%s", sxmbuf);
  snprintf(sxmbuf, Maxlen, "%s", prv_substr(sxmbuf, ipos1, ilen1));
  /*
  LOG(LM_STD,Fmtmsg("func_SubStr����.[%s]==>[%s]",sbuf,sxmbuf),"DEBUG");
  */
  return 0;
}

/*
   Tianhc 2005-10-15 20:57
   ���������ݽ���LLVARת��
   ���ӳ��ȵ�ģʽ
     SLL   --�ַ���ʽ�ĳ��ȣ�2λ
     HLL     --HEX��ʽ�ĳ��ȣ�2λ
     BLL     --BIN��ʽ�ĳ��ȣ�2λ��4λ
     ���ʱ�����ǵ�����Ϊ0-1λ����0x05������ĳ��֣����뽫�ַ�������ΪHEX��
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
    LOG(LM_STD, Fmtmsg("����func_Getlenִ��ʧ��1,��������̫�����޷�����"), "ERROR");
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
        LOG(LM_STD, Fmtmsg("����func_Getlenִ��ʧ��1,��������̫��[%d]!", ilen), "ERROR");
        return -1;
      }
      LOG(LM_DEBUG, Fmtmsg("      --> func toLVAR,len[%d],cont[%s]", ilen, sxmbuf), "DEBUG");
      pchar = ilen ;
      /*memcpy(sxmbuf,&pchar,1);*/
      sxmbuf[0] = pchar;
      memcpy(sxmbuf + 1, sbuf, ilen);
      /*ת��HEX�ַ���ʽ*/
      memset(sbuf, 0, sizeof(sbuf));
      HEX_2_DSP(sxmbuf, sbuf, ilen + 1);
      /*LOG(LM_STD,Fmtmsg("ת��������[%s][%s],ilen[%d]",sxmbuf,sbuf,ilen),"DEBUG");*/
      strcpy(sxmbuf, sbuf);

    }
    else if (ilen2 == 2)
    {
      ilen_2 = ilen ;
      LOG(LM_DEBUG, Fmtmsg("      --> func toLLVAR,len[%d]", ilen), "DEBUG");
      memcpy(slen, &ilen_2, sizeof(ilen_2));
      memcpy(sxmbuf, slen, sizeof(ilen_2));
      memcpy(sxmbuf + sizeof(ilen_2), sbuf, ilen);
      /*ת��HEX�ַ���ʽ*/
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
      /*ת��HEX�ַ���ʽ*/
      memset(sbuf, 0, sizeof(sbuf));
      HEX_2_DSP(sxmbuf, sbuf, ilen + sizeof(ilen_4));
      strcpy(sxmbuf, sbuf);
    }
    else
    {
      LOG(LM_STD, Fmtmsg("����func_Getlenִ��ʧ��1,����[%s]��ʽ����ȷ!", para), "ERROR");
      return -1;
    }
  }
  else
  {
    LOG(LM_STD, Fmtmsg("����func_Getlenִ��ʧ��2,����[%s]��ʽ����ȷ!", para), "ERROR");
    return -2;
  }
  return 0;
}




/*
   Tianhc 2005-10-15 20:57
   16�����ַ���ʽת��10�������ַ�ʽ
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
   ��HEX�ַ���ʽ�ĳ��ȣ�תΪ�������ַ�������
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
    else  /*�������*/
    {
      LOG(LM_STD, Fmtmsg("����shex2sintִ��ʧ��,pchar[%c]����ȷ!", pchar), "ERROR");
      return -1;
    }
    lret = lret + ibit * oxflag[j];
  }
  sprintf(sdest, "%ld", lret);
  return 0;
}


/*
   Tianhc 2005-10-15 20:57
   �� char --> int
*/
extern IRESULT func_Char2Int(HXMLTREE iXmlhandle, char *sxmbuf, int *ilen_src, int Maxlen,
                               char * spkg_buf, int *ilen_pkg, int *ipos_curr, char *para,
                               void *pz_curr, void * datalink)
{
  char pchar;
  pchar = sxmbuf[0];
  if (*ilen_src != 1 )
  {
    LOG(LM_DEBUG, Fmtmsg("      --> func Char2Int err,����������Դ����ֻ��Ϊ1"), "ERROR");
    return -1;
  }
  LOG(LM_DEBUG, Fmtmsg("      --> func Char2Int,[%c]=>[%d]", pchar, pchar), "DEBUG");
  sprintf(sxmbuf, "%d", pchar);
  return 0;
}

/*
   Tianhc 2005-11-16 16:21
   �� int --> char
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
   ����һ�����ȵı�ͷ
   �����Ѿ�Ԥ�����ȱ���
   �����ܳ��Ȳ���,ֻ���滻ǰN���ַ�
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
      ilen_2 = htons(ilen_2);  /*תΪ�����ֽ���*/
      memcpy(slen, &ilen_2, sizeof(ilen_2));
      memcpy(spkg_buf, slen, sizeof(ilen_2));
    }
    else if (ilen2 == 4)
    {
      ilen_4 = *ipos_curr;
      ilen_4 = htonl(ilen_4);  /*תΪ�����ֽ���*/
      memcpy(slen, &ilen_4, sizeof(ilen_4));
      memcpy(spkg_buf, slen, sizeof(ilen_4));
    }
    else
    {
      LOG(LM_STD, Fmtmsg("����func_AddHeadִ��ʧ��1,����[%s]��ʽ����ȷ!", para), "ERROR");
      return -1;
    }
  }
  else
  {
    LOG(LM_STD, Fmtmsg("����func_AddHeadִ��ʧ��1,����[%s]��ʽ����ȷ!", para), "ERROR");
    return -2;
  }
  return 0;
}

/*
   �ṩ���ļ�ת��ʱʹ�õĺ���������4��������
   1.XML���
   2.�ֶ�ԭ����
   3.�û�������󳤶�
   4.�����Ĳ���
     ---���������ɹ��򷵻�0���޸Ļ��������ô���ĳ��ȱ�֤�������
   ���������ڲ��ԣ����ַ�����ת,����һ��/һ��,��unloadʱ��ת,loadʱ��ת����...
*/
extern IRESULT func_reverse(HXMLTREE Xmlhandle, char *sfldvalue , int isize, char *sfldpara)
{
  int i, pchar;
  LOG(LM_DEBUG, Fmtmsg("  -->����func_reverse����,fldvalue[%s]", sfldvalue), "DEBUG2");
  for (i = 0;i < strlen(sfldvalue) / 2;i++)
  {
    pchar = sfldvalue[i];
    sfldvalue[i] = sfldvalue[strlen(sfldvalue)-i-1] ;
    sfldvalue[strlen(sfldvalue)-i-1] = pchar;
  }
  return 0;
}

/************************************************************************
��������:
int gaps32_checkfldrule(char *scont, char *srule)
��������:

�������:
         char *scont          ��ǰ���������
         char *srule          ��ǰ�����ݹ���
��    ��: 0-OK,1-�����Ϲ���,-1-��������
��    ��: ��
�� Ŀ ��:
�� �� Ա:Tianhc
��������:
�޸�����:2006-5-15 15:40
˵����
  Ŀǰ֧�ֵı��ʽ��
          AN10    ���ֻ���ĸ(���ܰ����������)���ұ���Ϊ10λ����
          ANS[1..10]  �����ַ����ұ���Ϊ1-10λ����
          N6      ����Ϊ������6λ����(����+-.)��
          N[1..6]    ����Ϊ������1-6λ����(����+-.)��
  ����ֵ ��
    ����GAPSV4�������ֵ���򣬷���1ΪOK������Ϊ��OK

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
     LOG(LM_STD,Fmtmsg("  -->���ݹ�����Ϊ��!"),"ERROR");
     return -1;
  }
  s_end=srule[strlen(srule)-1];
  if ((s_end != ']') && (s_end < '0') && (s_end > '9'))
  {
     LOG(LM_STD,Fmtmsg("  -->���ݹ���[%s]����ȷ!",srule),"ERROR");
     return -2;
  }
  memset(sdatatype,0,sizeof(sdatatype));
  if ( s_end == ']'  )  /*�䳤,ȡmin,max*/
  {
     if ((pstr1 = strchr(srule,'[')) == NULL )
     {
         LOG(LM_STD,Fmtmsg("  -->���ݹ���[%s]����ȷ!",srule),"ERROR");
         return -3;
     }
     memcpy(sdatatype,srule,pstr1-srule);
     if ((pstr2 = strchr(pstr1,']')) == NULL )
     {
         LOG(LM_STD,Fmtmsg("  -->���ݹ���[%s]����ȷ!",srule),"ERROR");
         return -4;
     }
     memset(sbuf,0,sizeof(sbuf));
     memcpy(sbuf,pstr1+1,pstr2-pstr1-1);
     if ((pstr1=strstr(sbuf,"..")) == NULL )
     {
         LOG(LM_STD,Fmtmsg("  -->���ݹ���[%s]����ȷ!",srule),"ERROR");
         return -5;
     }
     *pstr1=0;
     len_min=atoi(sbuf);
     len_max=atoi(pstr1+2);
     if (len_max <= len_min)
     {
         LOG(LM_STD,Fmtmsg("  -->���ݹ���[%s]����ȷ!",srule),"ERROR");
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
         LOG(LM_STD,Fmtmsg("  -->���ݹ���[%s]����ȷ!",srule),"ERROR");
         return -7;
     }
     strcpy(sbuf,srule+i);
     len_min=atoi(sbuf);
     len_max=len_min;
  }
  /*LOG(LM_DEBUG,Fmtmsg("   DEBUG:type[%s],min[%d]-[%d] ...",sdatatype,len_min,len_max),"DEBUG");*/
  if ((strlen(scont)>len_max) || (strlen(scont)<len_min))
  {
     LOG(LM_STD,Fmtmsg("  -->�ֶ�����[%s]���Ȳ���ȷ,[%d]-[%d]",scont,len_min,len_max),"ERROR");
     return -11;
  }
  /*��������У��*/
  if (strcmp(sdatatype,"ANS")==0)   /*������õ�ANS,�������У��������*/
     return 1;
  if (strchr(sdatatype,'A')!=NULL)
     flag_A=1;
  if (strchr(sdatatype,'N')!=NULL)
     flag_N=1;
  if (strchr(sdatatype,'S')!=NULL)
     flag_S=1;
  if   ( flag_A+flag_N+flag_S == 0 )
  {
     LOG(LM_STD,Fmtmsg("  -->���ݹ���[%s]���Ͳ���ȷ,ֻ��ΪANS����!",srule),"ERROR");
     return -9;
  }
  for (i=0;i<strlen(scont);i++)
  {
    if (!flag_A)  /*����ΪA*/
    {
      if (((scont[i] >= 'A') &&  (scont[i] <= 'Z')) ||
            ((scont[i] >= 'a') &&  (scont[i] <= 'z')))
      return -22;
    }
    if (!flag_N)  /*����ΪN*/
    {
      if ((scont[i] >= '0') && (scont[i] <= '9'))
        return -23;
    }
    if (!flag_S)  /*����ΪS,��AN֮��������ַ���Ϊ��S*/
    {
     if (!((((scont[i] >= 'A') &&  (scont[i] <= 'Z')) || ((scont[i] >= 'a') &&  (scont[i] <= 'z'))) ||
           ((scont[i] >= '0') && (scont[i] <= '9'))))
        return -24;
    }
  }
  return 1;
}


