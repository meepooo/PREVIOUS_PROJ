/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:sfck_timeout.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[������]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:sfck_timeout (˾����س�ʱ��֤��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __SFCK_TIMEOUT_H__
#define __SFCK_TIMEOUT_H__
typedef struct TDB_SFCK_TIMEOUT
{
	char xtbh[16+1]; /*ϵͳ���*/
	    /*ϵͳ���*/
	char ywbm[20+1];/*ҵ�����*/
	    /*ҵ�����*/
	char   ywsqbh[36+1];  /*ҵ��������*/
		/*���󵥱�ʶ ������ˮ�ţ����ڱ�ʶ�������*/
	char   ywrq[8+1];  /*ҵ������*/
		/*ҵ������*/
	char   ywlsh[32+1];  /*ҵ����ˮ��*/
		/*ҵ����ˮ��*/
	char   qqdzt[2+1];  /*����״̬*/
		/*����״̬*/

}SFCK_TIMEOUT;

#define SD_DATA  SFCK_TIMEOUT
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  xtbh, 0),\
	DEFSDMEMBER(T_STRING,  ywbm, 0),\
	DEFSDMEMBER(T_STRING,  ywsqbh, 0),\
	DEFSDMEMBER(T_STRING,  ywrq, 0),\
	DEFSDMEMBER(T_STRING,  ywlsh, 0),\
	DEFSDMEMBER(T_STRING,  qqdzt, 0)

	DECLAREFIELDS(SD_SFCK_TIMEOUT)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __SFCK_TIMEOUT_H__*/
