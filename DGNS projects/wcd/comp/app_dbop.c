/********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϷ���ƽ̨(GAPS)��Ŀ
��    ��:V4.1.00
����ϵͳ:AIX/Linux/HP-UX
�� �� ��:
�ļ�����:dbcomm.c
�ļ�����:�������ݿ⹫�ú���
�� Ŀ ��:GAPS�з���
�� �� Ա:GAPS�з���
��������:2007-5-11
��    ��:
�޸�����:
*********************************************************************/
/*
�޸ļ�¼
�� �� ��:
�޸�����:
�޸�����:
*/
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "DCI.h"
#include "../incl/app_dbop.h"


static char Level_dbcomm_c[] = "{$Id: dbcomm.c 2721 2016-06-22 03:29:21Z zhangyao11598 $}";

/******************************************************************************
�������ơ�DBInsert
�������ܡø���������һ���ṹ���ݸ��±�
���������tb        -- ����
          desc_arr  -- �ṹ������Ϣ
          desc_num  -- �ṹ��������
          pstru     -- ����ָ��

���������errmsg    -- ������Ϣ
�� �� ֵ��>= 0      -- �ɹ�  Ӱ�������
         ����       -- ʧ��
******************************************************************************/
int APP_DBInsert(const char* tb, APP_FLD_DESC desc_arr[],
             int desc_num, void *pstru, char *errmsg)
{
  int  i, n;
  int  rowcount;
  char *stmt, *p;
  CURSOR cur;
  APP_FLD_DESC *pdesc;

  if (desc_num <= 0 || pstru == NULL)
    return 0;

  stmt = (char *)calloc(1, (APP_MAX_SYM_LEN + 3) * desc_num + strlen(tb) + 100);
  if (stmt == NULL)
  {
    if (errmsg)
      sprintf(errmsg, "�ڴ�������");
    return -1;
  }
  pdesc = desc_arr;

  n = sprintf(stmt, "insert into %s values (:%s", tb, pdesc->name);
  pdesc++;
  for (i = 1, p = stmt + n; i < desc_num; i++, pdesc++)
  {
    n = sprintf(p, ", :%s", pdesc->name);
    p += n;
  }
  strcat(p, ")");

  cur = DCIDeclareCursor(stmt, DCI_STMT_LOCATOR);
  if (cur == INVALID_CURSOR)
  {
    if (errmsg)
      strcpy(errmsg, DCILastError());
    free(stmt);
    return -1;
  }
  free(stmt);

  for (i = 0, pdesc = desc_arr; i < desc_num; i++, pdesc++)
  {
    int   datatype;
    int   datalen;
    double dv;
    char  dvbuf[64];

    char *pval = (char *)pstru + pdesc->offset;
    switch (pdesc->type)
    {
    case APP_TT_CHAR:
    case APP_TT_STRING:
      datatype = DCIT_CHAR;
#ifdef DB_MYSQL 
      datalen  = MAX(strlen(pval), pdesc->extlen);   
#else
      datalen  = MAX(strlen(pval)+1, pdesc->extlen);
#endif          
      break;

    case APP_TT_SHORT:
      datatype = DCIT_INTEGER;
      datalen  = sizeof(short);
      break;

   case APP_TT_LONG:
	   if ( sizeof(long) == sizeof(int ))
	   {
        datatype = DCIT_INTEGER;
        datalen  = sizeof(int);
        /* ����32λ�´����Ĳ��� */
        if(pdesc->maxlen == 8)
        {
          datatype = DCIT_LONG;
	        datalen = sizeof(long long);
        }
	   }
	   else
	   {
	      datatype = DCIT_LONG;
	      datalen = sizeof(long);
	      /* ��64λ��int�����ݴ��� */
	  	  if(pdesc->maxlen == 4)
	      {
	    	  datatype = DCIT_INTEGER;
	        datalen = sizeof(int);
	      }
	   }
      break;

    case APP_TT_DOUBLE:
      datatype = DCIT_DOUBLE;
      datalen  = sizeof(double);
      if (pdesc->extlen > 0)
      {
        snprintf(dvbuf, sizeof(dvbuf), "%.*lf", pdesc->extlen, *(double *)pval);
        dv = atof(dvbuf);
        memcpy(pval, &dv, sizeof(double));
      }
      break;

    default:
      if (errmsg)
        strcpy(errmsg, "δ֪���ֶ�����");
      DCIFreeCursor(cur);
      return -1;
    }

    if (DCIBindPara(cur, i, pval, datalen, datatype) == -1)
    {
      if (errmsg)
        strcpy(errmsg, DCILastError());
      PRINTF("pos = %d\n", i);
      DCIFreeCursor(cur);
      return -1;
    }
  }

  rowcount = DCIExecute(cur);
  if (rowcount == -1)
  {
    if (errmsg)
      strcpy(errmsg, DCILastError());
    DCIFreeCursor(cur);
    return -1;
  }

  DCIFreeCursor(cur);
  return rowcount;
}

/******************************************************************************
�������ơ�DBUpdate
�������ܡø���������һ���ṹ���ݸ��±�
���������tb        -- ����
          desc_arr  -- �ṹ������Ϣ
          desc_num  -- �ṹ��������
          pstru     -- ����ָ��
          condition -- �������ʽ (������where)

���������errmsg    -- ������Ϣ
�� �� ֵ��>= 0      -- �ɹ�  Ӱ�������
         ����       -- ʧ��
******************************************************************************/
int APP_DBUpdate(const char* tb, APP_FLD_DESC desc_arr[], int desc_num,
             void *pstru, const char *condition, char *errmsg)
{
  int  i, n;
  int  rowcount;
  char *stmt, *p;
  CURSOR cur;
  APP_FLD_DESC *pdesc;

  if (desc_num <= 0 || pstru == NULL)
    return 0;

  stmt = (char *)calloc(1, (APP_MAX_SYM_LEN + 6) * desc_num * 2 +
                        strlen(tb) + strlen(condition) + 100);
  if (stmt == NULL)
  {
    if (errmsg)
      sprintf(errmsg, "�ڴ�������");
    return -1;
  }
  pdesc = desc_arr;

  n = sprintf(stmt,
              "update %s set %s = :%s",
              tb, pdesc->name, pdesc->name);
  pdesc++;
  for (i = 1, p = stmt + n; i < desc_num; i++, pdesc++)
  {
    n = sprintf(p, ", %s = :%s", pdesc->name, pdesc->name);
    p += n;
  }
  sprintf(p, " where %s", condition);
  cur = DCIDeclareCursor(stmt, DCI_STMT_LOCATOR);
  if (cur == INVALID_CURSOR)
  {
    if (errmsg)
      strcpy(errmsg, DCILastError());
    free(stmt);
    return -1;
  }

  free(stmt);

  for (i = 0, pdesc = desc_arr; i < desc_num; i++, pdesc++)
  {
    int   datatype;
    int   datalen;
    double dv;
    char dvbuf[64] = { 0 };

    char *pval = (char *)pstru + pdesc->offset;
    switch (pdesc->type)
    {
    case APP_TT_CHAR:
    case APP_TT_STRING:
      datatype = DCIT_CHAR;
#ifdef DB_MYSQL 
      datalen  = MAX(strlen(pval), pdesc->extlen);   
#else
      datalen  = MAX(strlen(pval)+1, pdesc->extlen);
#endif          
      break;

    case APP_TT_SHORT:
      datatype = DCIT_INTEGER;
      datalen  = sizeof(short);
      break;

    case APP_TT_LONG:
	  if ( sizeof(long) == sizeof(int ))
	  {
      datatype = DCIT_INTEGER;
      datalen  = sizeof(int);
        /* ����32λ�´��� */
      if(pdesc->maxlen == 8)
      {
        datatype = DCIT_LONG;
	      datalen = sizeof(long long);
      }
	  }
	  else
	  {
	    datatype = DCIT_LONG;
	    datalen = sizeof(long);
	      /* ��64λ��int�����ݴ��� */
	    if(pdesc->maxlen == 4)
	    {
	  	  datatype = DCIT_INTEGER;
	      datalen = sizeof(int);
      }
	  }
    break;

    case APP_TT_DOUBLE:
      datatype = DCIT_DOUBLE;
      datalen  = sizeof(double);
      if (pdesc->extlen > 0)
      {
        snprintf(dvbuf, sizeof(dvbuf), "%.*lf", pdesc->extlen, *(double *)pval);
        dv = atof(dvbuf);
        memcpy(pval, &dv, sizeof(double));
      }

      break;

    default:
      if (errmsg)
        strcpy(errmsg, "δ֪���ֶ�����");
      DCIFreeCursor(cur);
      return -1;
    }

    if (DCIBindPara(cur, i, pval, datalen, datatype) == -1)
    {
      if (errmsg)
        strcpy(errmsg, DCILastError());
      DCIFreeCursor(cur);
      return -1;
    }
  }

  rowcount = DCIExecute(cur);
  if (rowcount == -1)
  {
    if (errmsg)
      strcpy(errmsg, DCILastError());
    DCIFreeCursor(cur);
    return -1;
  }

  DCIFreeCursor(cur);
  return rowcount;


}

/******************************************************************************
�������ơ�DBFetch
�������ܡø���������һ���ṹ���ݸ��±�
���������cur       -- �α���
          desc_arr  -- �ṹ������Ϣ
          desc_num  -- �ṹ��������
          pstru     -- ����ָ��

���������errmsg    -- ������Ϣ
�� �� ֵ��>= 0      -- �ɹ�  ��ȡ��������  0 �������

         ����       -- ʧ��
******************************************************************************/
int
APP_DBFetch(CURSOR cur, FLD_DESC desc_arr[], int desc_num, void *pstru, char *errmsg)
{
  int i;
  int rowcount;
  FLD_DESC *pdesc;
  const char *pstr = NULL;

  if ((rowcount = DCIFetch(cur)) == -1)
  {
    sprintf(errmsg, "DBFetch failed: %s", DCILastError());
    return -1;
  }

  if (rowcount > 0)
  {
    for (i = 0, pdesc = desc_arr; i < desc_num; i++, pdesc++)
    {
      char *pval = (char *)pstru + pdesc->offset;
      pstr = DCIFieldAsString(cur, i);
      if (NULL == pstr)
      {
        sprintf(errmsg, "DBFetch failed: %s", DCILastError());
        return -1;
      }

      switch (pdesc->type)
      {
      case APP_TT_CHAR:
      case APP_TT_STRING:

        if (pstr != NULL)
        {
          strncpy(pval, pstr, pdesc->maxlen - 1);
        }
        break;

      case APP_TT_SHORT:
        if (pstr != NULL)
        {
        	if (pdesc->maxlen == sizeof(short))
            *(short *) pval = atoi(pstr) & 0xFFFF;
          else if (pdesc->maxlen == sizeof(int))
          	*(int *) pval = atoi(pstr);
          else if (pdesc->maxlen == sizeof(long))
          	*(long *) pval = atol(pstr);
        }
        break;
      case APP_TT_LONG:
        if (pstr != NULL)
        {
        	if ( sizeof(long) == sizeof(int ))
        	{
        		*(int *) pval = atoi(pstr);
        		if(pdesc->maxlen == 8)
        			*(long long *) pval = atoll(pstr);
        	}
        	else
        	{
        		*(long *) pval = atol(pstr);
        		if(pdesc->maxlen == 4)
        			*(int *) pval = atoi(pstr);
        	} 		
        }
        break;

      case APP_TT_DOUBLE:
        if (pstr != NULL)
        {
          *(double *) pval = atof(pstr);
        }
        break;
      default:
        if (errmsg)
          strcpy(errmsg, "δ֪���ֶ�����");
        return -1;
      }
    }
  }

  return rowcount;
}
