/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:gab_dxzp_dual.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[����ǿ]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:gab_dxzp_dual (����թƭҵ����ˮ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __GAB_DXZP_DUAL_H__
#define __GAB_DXZP_DUAL_H__
typedef struct TDB_GAB_DXZP_DUAL
{
	long   nextval;  /*ҵ����ˮ��*/
		/*ҵ����ˮ��*/
}GAB_DXZP_DUAL;

#define SD_DATA  GAB_DXZP_DUAL
#define SD_MEMBERS \
	DEFSDMEMBER(T_LONG,  nextval, 0)

	DECLAREFIELDS(SD_GAB_DXZP_DUAL)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __GAB_DXZP_DUAL_H__*/
