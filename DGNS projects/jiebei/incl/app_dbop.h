/********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϷ���ƽ̨(GAPS)��Ŀ
��    ��:V4.1.00
����ϵͳ:AIX/Linux/HP-UX
�� �� ��:
�ļ�����:fielddescri.h
�ļ�����:C���Խṹ�ֶε������ṹ��ͷ�ļ�
�� Ŀ ��:GAPS�з���
�� �� Ա:����
��������:2002.08.7
��    ��:
�޸�����:
*********************************************************************/
/*
�޸ļ�¼
�� �� ��:
�޸�����:
�޸�����:
*/

#ifndef _APP_DBOP_H_
#define _APP_DBOP_H_

#include <stdio.h>

/*********************************��������************************************/

/**********************************�궨��*************************************/
#define APP_MAX_SYM_LEN       30     /* ��ʾ����󳤶� */

/*********************************���Ͷ���************************************/
enum APP_ENUM_T_TYPE
{
  APP_TT_CHAR,       /* �ַ���   */
  APP_TT_STRING,     /* �ַ����� */
  APP_TT_SHORT,      /* ������   */
  APP_TT_LONG,       /* ������   */
  APP_TT_DOUBLE,     /* ������   */
  APP_TT_INVALID     /* ��Ч���� */
};
typedef enum   APP_ENUM_T_TYPE  APP_T_TYPE;

/*******************************�ṹ/���϶���*********************************/
typedef struct APP_STRUCT_FIELD_DESCRI
{
  char   name[APP_MAX_SYM_LEN];      /* �ֶ�����                   */
  APP_T_TYPE type;                   /* �ֶ�����                   */
  size_t offset;                 /* �ڽṹ�еĵ�ַƫ����       */
  size_t maxlen;                 /* �ֶε���󳤶ȣ�����SHORT��*/
  /* LONG��DOUBLE����Ϊת���ַ� */
  /* ������󳤶�               */
  size_t extlen;                 /* ����STRING����Ϊ��С����   */
  /* ����DOUBLE����ΪС��λ��   */
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

/*******************************�ⲿ��������**********************************/

/*******************************ȫ�ֱ�������**********************************/

/*******************************����ԭ������**********************************/
#endif /*_APP_DBOP_H_*/

/*********************************�ļ�����************************************/
