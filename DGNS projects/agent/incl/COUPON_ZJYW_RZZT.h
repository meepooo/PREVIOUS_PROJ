/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:COUPON_ZJYW_RZZT.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[�]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:COUPON_ZJYW_RZZT(��ȯƽ̨���˻��ܱ�)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __COUPON_ZJYW_RZZT_H__
#define __COUPON_ZJYW_RZZT_H__
typedef struct TDB_COUPON_ZJYW_RZZT
{
  char   ptrq[8+1];              /*ƽ̨����*/
  char   dzrq[8+1];              /*��������*/
  char   status[2+1];
  int    wiamp_zbs;   
  int    zjyw_zbs;
  char   extfld1[20+1];
  char   extfld2[20+1];
}COUPON_ZJYW_RZZT;

#define SD_DATA COUPON_ZJYW_RZZT 
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  ptrq, 0),\
	DEFSDMEMBER(T_STRING,  dzrq, 0),\
	DEFSDMEMBER(T_STRING,  status, 0),\
	DEFSDMEMBER(T_LONG,    wiamp_zbs, 0),\
	DEFSDMEMBER(T_LONG,    zjyw_zbs, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  extfld2, 0)

	DECLAREFIELDS(SD_COUPON_ZJYW_RZZT)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __COUPON_ZJYW_RZZT_H__*/

