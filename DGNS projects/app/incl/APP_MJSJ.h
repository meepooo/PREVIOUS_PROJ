/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:APP_MJSJ.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[�]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:APP_MJSJ (ö�����ݱ�)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __APP_MJSJ_H__
#define __APP_MJSJ_H__
typedef struct TDB_APP_MJSJ
{
  char   mjid[16+1];              /*ö��ID*/
              /*ö��ID*/
  char   mjsm[40+1];              /*ö��˵��*/
              /*ö��˵��*/
  int    sjxh;              /*�������*/
              /*�������*/
  char   qsbz[1+1];              /*ȱʡ��ʶ*/
              /*ȱʡ��ʶ  0�� 1��*/
  char   req1[40+1];              /*����1*/
              /**/
  char   req2[40+1];              /*����2*/
              /**/
  char   req3[40+1];              /*����3*/
              /**/
  char   req4[40+1];              /*����4*/
              /**/
  char   req5[40+1];              /*����5*/
              /**/
  char   req6[40+1];              /*����6*/
              /**/
  char   req7[40+1];              /*����7*/
              /**/
  char   req8[40+1];              /*����8*/
              /**/
  char   req9[40+1];              /*����9*/
              /**/
  char   req10[40+1];              /*����10*/
              /**/
  char   resp1[40+1];              /*���1*/
              /**/
  char   resp2[40+1];              /*���2*/
              /**/
  char   resp3[40+1];              /*���3*/
              /**/
  char   resp4[40+1];              /*���4*/
              /**/
  char   resp5[40+1];              /*���5*/
              /**/
  char   resp6[40+1];              /*���6*/
              /**/
  char   resp7[40+1];              /*���7*/
              /**/
  char   resp8[40+1];              /*���8*/
              /**/
  char   resp9[40+1];              /*���9*/
              /**/
  char   resp10[40+1];              /*���10*/
              /**/
  char   whjg[16+1];              /*ά������*/
              /**/
  char   whgy[16+1];              /*ά����Ա*/
              /**/
  char   whsj[14+1];              /*ά��ʱ��*/
              /**/
}APP_MJSJ;

#define SD_DATA  APP_MJSJ
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  mjid, 0),\
	DEFSDMEMBER(T_STRING,  mjsm, 0),\
	DEFSDMEMBER(T_LONG,  sjxh, 0),\
	DEFSDMEMBER(T_STRING,  qsbz, 0),\
	DEFSDMEMBER(T_STRING,  req1, 0),\
	DEFSDMEMBER(T_STRING,  req2, 0),\
	DEFSDMEMBER(T_STRING,  req3, 0),\
	DEFSDMEMBER(T_STRING,  req4, 0),\
	DEFSDMEMBER(T_STRING,  req5, 0),\
	DEFSDMEMBER(T_STRING,  req6, 0),\
	DEFSDMEMBER(T_STRING,  req7, 0),\
	DEFSDMEMBER(T_STRING,  req8, 0),\
	DEFSDMEMBER(T_STRING,  req9, 0),\
	DEFSDMEMBER(T_STRING,  req10, 0),\
	DEFSDMEMBER(T_STRING,  resp1, 0),\
	DEFSDMEMBER(T_STRING,  resp2, 0),\
	DEFSDMEMBER(T_STRING,  resp3, 0),\
	DEFSDMEMBER(T_STRING,  resp4, 0),\
	DEFSDMEMBER(T_STRING,  resp5, 0),\
	DEFSDMEMBER(T_STRING,  resp6, 0),\
	DEFSDMEMBER(T_STRING,  resp7, 0),\
	DEFSDMEMBER(T_STRING,  resp8, 0),\
	DEFSDMEMBER(T_STRING,  resp9, 0),\
	DEFSDMEMBER(T_STRING,  resp10, 0),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0)


	DECLAREFIELDS(SD_APP_MJSJ)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_MJSJ_H__*/

