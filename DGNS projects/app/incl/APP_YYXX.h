/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:APP_YYXX.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[�]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:APP_YYXX (Ӧ����Ϣ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __APP_YYXX_H__
#define __APP_YYXX_H__
typedef struct TDB_APP_YYXX
{
  char   yybs[8+1];              /*Ӧ�ñ�ʶ*/
              /*Ӧ�ñ�ʶ */
  char   yymc[40+1];              /*Ӧ������*/
              /*Ӧ������*/
  char   yysm[80+1];              /*Ӧ��˵��*/
              /*Ӧ��˵��*/
  char   yykfksrq[8+1];              /*Ӧ�ÿ�����ʼ����*/
              /*Ӧ�ÿ�����ʼ����*/
  char   yykfjsrq[8+1];              /*Ӧ�ÿ�����������*/
              /*Ӧ�ÿ�����������*/
  char   yyfbrq[8+1];              /*Ӧ�÷�������*/
              /*Ӧ�÷�������*/
  char   yybbh[20+1];              /*Ӧ�ð汾��*/
              /*Ӧ�ð汾��*/
  char   yhh[40+1];              /*�û���*/
              /*�û���*/
  char   sqh[40+1];              /*��Ȩ��*/
              /*��Ȩ��*/
  char   yykfjl[40+1];              /*Ӧ�ÿ�������*/
              /*Ӧ�ÿ�������*/
  char   yyzbjl[40+1];              /*Ӧ���ʱ�����*/
              /*Ӧ���ʱ�����*/
  char   yyzt[1+1];              /*Ӧ��״̬*/
              /*0���� 1�ر�*/
  char   extfld[40+1];              /*��չ�ֶ�*/
              /*��չ�ֶ�*/
}APP_YYXX;

#define SD_DATA  APP_YYXX
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  yybs, 0),\
	DEFSDMEMBER(T_STRING,  yymc, 0),\
	DEFSDMEMBER(T_STRING,  yysm, 0),\
	DEFSDMEMBER(T_STRING,  yykfksrq, 0),\
	DEFSDMEMBER(T_STRING,  yykfjsrq, 0),\
	DEFSDMEMBER(T_STRING,  yyfbrq, 0),\
	DEFSDMEMBER(T_STRING,  yybbh, 0),\
	DEFSDMEMBER(T_STRING,  yhh, 0),\
	DEFSDMEMBER(T_STRING,  sqh, 0),\
	DEFSDMEMBER(T_STRING,  yykfjl, 0),\
	DEFSDMEMBER(T_STRING,  yyzbjl, 0),\
	DEFSDMEMBER(T_STRING,  yyzt, 0),\
	DEFSDMEMBER(T_STRING,  extfld, 0)


	DECLAREFIELDS(SD_APP_YYXX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_YYXX_H__*/
