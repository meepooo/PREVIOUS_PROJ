/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:COUPON_DZBPB.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[�]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:COUPON_DZBPB(���ʲ�ƽ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __COUPON_DZBPB_H__
#define __COUPON_DZBPB_H__
typedef struct TDB_COUPON_DZBPB
{
  char   ptrq[8+1];              /*ƽ̨����*/
  char   dzrq[8+1];              /*��������*/
  char   changeorderno[128+1];
  char   weiorderno[128+1];
  char   couponno[128+1];
  char   status[2+1];
  int    wiamp_ordernum;   
  int    zjyw_ordernum;
  char   extfld1[20+1];
  char   extfld2[20+1];
}COUPON_DZBPB;

#define SD_DATA COUPON_DZBPB 
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  ptrq, 0),\
	DEFSDMEMBER(T_STRING,  dzrq, 0),\
	DEFSDMEMBER(T_STRING,  changeorderno, 0),\
	DEFSDMEMBER(T_STRING,  weiorderno, 0),\
	DEFSDMEMBER(T_STRING,  couponno, 0),\
	DEFSDMEMBER(T_STRING,  status, 0),\
	DEFSDMEMBER(T_LONG,    wiamp_ordernum, 0),\
	DEFSDMEMBER(T_LONG,    zjyw_ordernum, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  extfld2, 0)

	DECLAREFIELDS(SD_COUPON_DZBPB)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __COUPON_DZBPB_H__*/

