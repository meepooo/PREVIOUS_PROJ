/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:BATCH_MAPRESP.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[�]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:BATCH_MAPRESP (������Ӧ��ӳ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __BATCH_MAPRESP_H__
#define __BATCH_MAPRESP_H__
typedef struct TDB_BATCH_MAPRESP
{
	char   mapid[32+1];  /*ӳ���ʶ*/
		/**/
	char   note[40+1];  /*ӳ��˵��*/
		/**/
	char   resp_s[10+1];  /*Դ��Ӧ��*/
		/**/
	char   resp_d[10+1];  /*ӳ����Ӧ��*/
		/**/
	char   msg_d[40+1];  /*��Ӧ��Ϣ*/
		/**/
	char   bz[1+1];  /*Ĭ��ת����ʶ*/
		/*Ĭ��ת����ʶ 0 �  � Ĭ�  һ����Ӧ����Դ�����һ� Ĭ��ת��*/
	char   whjg[16+1];  /*ά������*/
		/**/
	char   whgy[16+1];  /*ά����Ա*/
		/**/
	char   whsj[14+1];  /*ά��ʱ��*/
		/**/

}BATCH_MAPRESP;

#define SD_DATA  BATCH_MAPRESP
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  mapid, 0),\
	DEFSDMEMBER(T_STRING,  note, 0),\
	DEFSDMEMBER(T_STRING,  resp_s, 0),\
	DEFSDMEMBER(T_STRING,  resp_d, 0),\
	DEFSDMEMBER(T_STRING,  msg_d, 0),\
	DEFSDMEMBER(T_STRING,  bz, 0),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0)


	DECLAREFIELDS(SD_BATCH_MAPRESP)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __BATCH_MAPRESP_H__*/
