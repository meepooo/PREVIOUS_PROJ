/********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合服务平台(GAPS)项目
版    本:V4.1.00
操作系统:AIX/Linux/HP-UX
数 据 库:
文件名称:dbcomm.c
文件描述:操作数据库公用函数
项 目 组:GAPS研发组
程 序 员:GAPS研发组
发布日期:2007-5-11
修    订:
修改日期:
*********************************************************************/
/*
修改记录
修 改 人:
修改日期:
修改内容:
*/
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "DCI.h"
#include "../incl/app_dbop.h"


static char Level_dbcomm_c[] = "{$Id: dbcomm.c 2721 2016-06-22 03:29:21Z zhangyao11598 $}";

/******************************************************************************
函数名称∶DBInsert
函数功能∶根据条件用一个结构数据更新表
输入参数∶tb        -- 表名
          desc_arr  -- 结构描述信息
          desc_num  -- 结构描述长度
          pstru     -- 数据指针

输出参数∶errmsg    -- 错误信息
返 回 值∶>= 0      -- 成功  影响的行数
         其他       -- 失败
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
      sprintf(errmsg, "内存分配错误");
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
        /* 兼容32位下大数的插入 */
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
	      /* 对64位下int型数据处理 */
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
        strcpy(errmsg, "未知的字段类型");
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
函数名称∶DBUpdate
函数功能∶根据条件用一个结构数据更新表
输入参数∶tb        -- 表名
          desc_arr  -- 结构描述信息
          desc_num  -- 结构描述长度
          pstru     -- 数据指针
          condition -- 条件表达式 (不包括where)

输出参数∶errmsg    -- 错误信息
返 回 值∶>= 0      -- 成功  影响的行数
         其他       -- 失败
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
      sprintf(errmsg, "内存分配错误");
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
        /* 兼容32位下大数 */
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
	      /* 对64位下int型数据处理 */
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
        strcpy(errmsg, "未知的字段类型");
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
函数名称∶DBFetch
函数功能∶根据条件用一个结构数据更新表
输入参数∶cur       -- 游标句柄
          desc_arr  -- 结构描述信息
          desc_num  -- 结构描述长度
          pstru     -- 数据指针

输出参数∶errmsg    -- 错误信息
返 回 值∶>= 0      -- 成功  获取到的行数  0 到达最后

         其他       -- 失败
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
          strcpy(errmsg, "未知的字段类型");
        return -1;
      }
    }
  }

  return rowcount;
}
