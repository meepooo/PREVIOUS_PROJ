/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:COUPON_WIAMP_DZLSB.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[�]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:COUPON_WIAMP_DZLSB(��ȯƽ̨������ˮ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __COUPON_WIAMP_DZLSB_H__
#define __COUPON_WIAMP_DZLSB_H__
typedef struct TDB_COUPON_WIAMP_DZLSB
{
  char   dzrq[8+1];              /*��������*/
  char   changeorderno[128+1];
  char   weiorderno[128+1];
  char   busses_id[20+1];
  char   couponno[128+1];
  char   user_id[20+1];
  int    couponnum;   
  char   gettime[20+1];
  double couponprize;
  char   orderstatus[2+1];
}COUPON_WIAMP_DZLSB;

#define SD_DATA COUPON_WIAMP_DZLSB 
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  dzrq, 0),\
	DEFSDMEMBER(T_STRING,  changeorderno, 0),\
	DEFSDMEMBER(T_STRING,  weiorderno, 0),\
	DEFSDMEMBER(T_STRING,  busses_id, 0),\
	DEFSDMEMBER(T_STRING,  couponno, 0),\
	DEFSDMEMBER(T_STRING,  user_id, 0),\
	DEFSDMEMBER(T_LONG,    couponnum, 0),\
	DEFSDMEMBER(T_STRING,  gettime, 0),\
	DEFSDMEMBER(T_DOUBLE,  couponprize, 2),\
	DEFSDMEMBER(T_STRING,  orderstatus, 0)

	DECLAREFIELDS(SD_COUPON_WIAMP_DZLSB)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __COUPON_WIAMP_DZLSB_H__*/

