/***********************************************************************
��Ȩ����:��ҵ���пƼ��������з�����
��Ŀ����:TIPSר��ǰ�ò�Ʒ
��    ��:V3.0
����ϵͳ:AIX SCO LINUX SunOS HP-UX
�� �� ��:INFORMIX
�� �� ��:tips_xibhxmx.eh
�ļ�����:tips_xibhxmx;�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:TIPSר��ǰ�ò�Ʒ��
�� �� Ա:
����ʱ��:2009-3-5 14:07:20 [By GenEHFromPDMTools]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:tips_xibhxmx (����Э����ű�)
˵    ��:������ţ���������Э�����
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�޸�����:
�� �� ��:
************************************************************************/
#ifndef __TIPS_XIBHXMX_H__
#define __TIPS_XIBHXMX_H__

typedef struct TDB_TIPS_XIBHXMX
{
	char  zwrq[70+1];
	char  khmc[70+1];
	char  khbh[20+1];
	char  khzh[32+1];
	double  jyje ;
	char  sprq[8+1];
	char  hxrq[8+1];
	char  hxcxrq[8+1];
	char  zy[20+1];
	char  status[20+1];
	char  bz[60+1];
	char  ztm[60+1];
	char  dzlsh[15+1];
	char  jgdh[12+1];
	char  dzbz[1+1];
}SDB_TIPS_XIBHXMX;

#define SD_DATA SDB_TIPS_XIBHXMX
#define	SD_MEMBERS \
	DEFSDMEMBER(T_STRING,zwrq,0),\
	DEFSDMEMBER(T_STRING,khmc,0),\
	DEFSDMEMBER(T_STRING,khbh,0),\
	DEFSDMEMBER(T_STRING,khzh,0),\
	DEFSDMEMBER(T_DOUBLE,jyje,2),\
	DEFSDMEMBER(T_STRING,sprq,0),\
	DEFSDMEMBER(T_STRING,hxrq,0),\
	DEFSDMEMBER(T_STRING,hxcxrq,0),\
	DEFSDMEMBER(T_STRING,zy,0),\
	DEFSDMEMBER(T_STRING,status,0),\
	DEFSDMEMBER(T_STRING,bz,0),\
	DEFSDMEMBER(T_STRING,ztm,0),\
	DEFSDMEMBER(T_STRING,dzlsh,0),\
	DEFSDMEMBER(T_STRING,jgdh,0),\
	DEFSDMEMBER(T_STRING,dzbz,0)

 DECLAREFIELDS(SD_TIPS_XIBHXMX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __TIPS_XIBHXMX_H__*/
