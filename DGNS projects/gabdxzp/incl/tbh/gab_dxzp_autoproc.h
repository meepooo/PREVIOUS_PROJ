/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:gab_dxzp_autoproc.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[������]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:gab_dxzp_autoproc (����թƭ�Զ������)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __GAB_DXZP_AUTOPROC_H__
#define __GAB_DXZP_AUTOPROC_H__
typedef struct TDB_GAB_DXZP_AUTOPROC
{
	char   ywsqbh[36+1];  /*ҵ��������*/
		/*���󵥱�ʶ ������ˮ�ţ����ڱ�ʶ�������*/
	char   jjcd[2+1];  /*�����̶�*/
		/*�����̶� 01����������02����Ӽ�*/
	char   qqdzt[2+1];  /*����״̬*/
		/*����״̬ ��һλ��0-��ʼ 1-��� 2-����(�ύ) 3-��� 4-����  �ڶ�λ��0-��ʼ 1-���ɹ���2-�ɹ�; 3-��ʱ; 9-������*/
	char   zh[30+1];  /*�ʺ�*/
		/*�˺�*/

}GAB_DXZP_AUTOPROC;

#define SD_DATA  GAB_DXZP_AUTOPROC
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  ywsqbh, 0),\
	DEFSDMEMBER(T_STRING,  jjcd, 0),\
	DEFSDMEMBER(T_STRING,  qqdzt, 0),\
	DEFSDMEMBER(T_STRING,  zh, 0)

	DECLAREFIELDS(SD_GAB_DXZP_AUTOPROC)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __GAB_DXZP_AUTOPROC_H__*/
