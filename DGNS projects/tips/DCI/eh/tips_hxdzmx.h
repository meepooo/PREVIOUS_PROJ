/***********************************************************************
��Ȩ����:��ҵ���пƼ��������з�����
��Ŀ����:TIPSר��ǰ�ò�Ʒ
��    ��:V3.0
����ϵͳ:AIX SCO LINUX SunOS HP-UX
�� �� ��:INFORMIX
�� �� ��:tips_hxdzmx.eh
�ļ�����:tips_hxdzmx;�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:TIPSר��ǰ�ò�Ʒ��
�� �� Ա:
����ʱ��:2009-3-5 14:07:20 [By GenEHFromPDMTools]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:tips_hxdzmx 
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�޸�����:
�� �� ��:
************************************************************************/
#ifndef __TIPS_HXDZMX_H__
#define __TIPS_HXDZMX_H__

typedef struct TDB_TIPS_HXDZMX
{
	char dzlx[1+1];/*��������*/
	char zjrq[8+1];/*��������*/
	char zjlsh[32+1];/*������ˮ��mod by tuql 20090908*/
	char zcyhzh[32+1];/*ת�������ʺ�*/ 
	double jyje;/*���׽��*/
	char qzrq[8+1];/*ǰ������*/
	int  qzlsh;/*ǰ����ˮ��*/
	char jydqdh[10+1];/*���׵�������*/
	char jyjgdh[10+1];/*���׻�������*/  
	char czbz[1+1];/*��������־*/
	char jydm[10+1];/*���״���*/
}SDB_TIPS_HXDZMX;

#define SD_DATA SDB_TIPS_HXDZMX
#define	SD_MEMBERS \
	DEFSDMEMBER(T_STRING,dzlx,0),\
	DEFSDMEMBER(T_STRING,zjrq,0),\
	DEFSDMEMBER(T_STRING,zjlsh,0),\
	DEFSDMEMBER(T_STRING,zcyhzh,0),\
	DEFSDMEMBER(T_DOUBLE,jyje,0),\
  DEFSDMEMBER(T_STRING,qzrq,0),\
	DEFSDMEMBER(T_LONG,qzlsh,0),\
  DEFSDMEMBER(T_STRING,jydqdh,0),\
	DEFSDMEMBER(T_STRING,jyjgdh,0),\
	DEFSDMEMBER(T_STRING,czbz,0),\
	DEFSDMEMBER(T_STRING,jydm,0)

 DECLAREFIELDS(SD_TIPS_HXDZMX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __TIPS_HXDZMX_H__*/
