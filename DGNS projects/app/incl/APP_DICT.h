/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:APP_DICT.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[�]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:APP_DICT (�����ֵ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __APP_DICT_H__
#define __APP_DICT_H__
typedef struct TDB_APP_DICT
{
	char   pkey;  /*KEYֵ*/
		/**/
	char   keyjs;  /*KEYֵ����*/
		/*KEYֵ����*/
	char   pval;  /*ֵ*/
		/**/
	char   prompt;  /*˵��*/
		/**/
	char   ssyy;  /*����Ӧ��*/
		/*Ӧ�ñ�ʶ*/
	char   whjg;  /*ά������*/
		/**/
	char   whgy;  /*ά����Ա*/
		/**/
	char   whsj;  /*ά��ʱ��*/
		/**/

}APP_DICT;

#define SD_DATA  APP_DICT
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  pkey, 0),\
	DEFSDMEMBER(T_STRING,  keyjs, 0),\
	DEFSDMEMBER(T_STRING,  pval, 0),\
	DEFSDMEMBER(T_STRING,  prompt, 0),\
	DEFSDMEMBER(T_STRING,  ssyy, 0),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0)


	DECLAREFIELDS(SD_APP_DICT)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_DICT_H__*/
