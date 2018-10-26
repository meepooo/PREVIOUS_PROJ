/********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合服务平台(GAPS)项目
版    本:V4.1.00
操作系统:AIX/Linux/HP-UX
数 据 库:
文件名称:fielddescri.h
文件描述:C语言结构字段的描述结构的头文件
项 目 组:GAPS研发组
程 序 员:沈勇
发布日期:2002.08.7
修    订:
修改日期:
*********************************************************************/
/*
修改记录
修 改 人:
修改日期:
修改内容:
*/

#ifndef _APP_DBOP_H_
#define _APP_DBOP_H_

#include <stdio.h>

/*********************************常量定义************************************/

/**********************************宏定义*************************************/
#define APP_MAX_SYM_LEN       30     /* 标示符最大长度 */

/*********************************类型定义************************************/
enum APP_ENUM_T_TYPE
{
  APP_TT_CHAR,       /* 字符型   */
  APP_TT_STRING,     /* 字符串型 */
  APP_TT_SHORT,      /* 短整形   */
  APP_TT_LONG,       /* 长整形   */
  APP_TT_DOUBLE,     /* 浮点型   */
  APP_TT_INVALID     /* 无效类型 */
};
typedef enum   APP_ENUM_T_TYPE  APP_T_TYPE;

/*******************************结构/联合定义*********************************/
typedef struct APP_STRUCT_FIELD_DESCRI
{
  char   name[APP_MAX_SYM_LEN];      /* 字段名称                   */
  APP_T_TYPE type;                   /* 字段类型                   */
  size_t offset;                 /* 在结构中的地址偏移量       */
  size_t maxlen;                 /* 字段的最大长度，对于SHORT、*/
  /* LONG和DOUBLE类型为转成字符 */
  /* 串的最大长度               */
  size_t extlen;                 /* 对于STRING类型为最小长度   */
  /* 对于DOUBLE类型为小数位数   */
}APP_FIELD_DESCRI;

typedef const APP_FIELD_DESCRI APP_FLD_DESC;

#define _APP_DEFSDMEMBER(datatype, mtype, column, extlen, cname)  \
    { cname, APP_T##mtype, (int)&(((datatype *)0)->column), \
      sizeof(((datatype *)0)->column), extlen}

#define APP_DEFSDMEMBER(mtype, column, extlen)  \
   _APP_DEFSDMEMBER(SD_DATA, mtype, column, extlen, #column)

#define NUMELE(array) (sizeof(array)/sizeof(array[0]))

#define APP_DECLAREFIELDS(fields)   \
          const static APP_FIELD_DESCRI fields[] = { SD_MEMBERS };

/*******************************外部变量声明**********************************/

/*******************************全局变量定义**********************************/

/*******************************函数原型声明**********************************/
#endif /*_APP_DBOP_H_*/

/*********************************文件结束************************************/
