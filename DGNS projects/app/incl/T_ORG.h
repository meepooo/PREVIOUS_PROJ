/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:t_org.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[�]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:t_org (������Ϣ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __T_ORG_H__
#define __T_ORG_H__
typedef struct TDB_T_ORG
{
  char   org_id[16+1];              /*������*/
              /*����*/
  char   org_name[50+1];              /*��������*/
              /**/
  char   org_desc[60+1];              /*��������*/
              /**/
  char   org_type[1+1];              /*�������*/
              /*�����������ֵ�� 0:���׻��� 1:�ǽ��׻���*/
  char org_level[1+1];              /*��������*/
              /**/
  char   above_org_id[16+1];              /*�ϼ�������*/
              /**/
  char   inner_org_id[27+1];              /*�ڲ�������ʶ*/
              /*�ڲ�������ʶ���ڳ����ڲ���ѯ���㣬�ڲ���ʶ����100Ϊ���ϼ�������һ����չ��100100,100100100,�Դ�����*/
  char   tel[32+1];              /*�����绰*/
              /**/
  char   email[50+1];              /*��������*/
              /**/
  char   org_adress[120+1];              /*������ַ*/
              /**/
  char   bak1[30+1];              /*������Ϣ1*/
              /**/
  char   bak2[60+1];              /*������Ϣ2*/
              /**/
  char   bak3[120+1];              /*������Ϣ3*/
              /**/
}T_ORG;

#define SD_DATA  T_ORG
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  org_id, 0),\
	DEFSDMEMBER(T_STRING,  org_name, 0),\
	DEFSDMEMBER(T_STRING,  org_desc, 0),\
	DEFSDMEMBER(T_STRING,  org_type, 0),\
	DEFSDMEMBER(T_STRING,  org_level, 0),\
	DEFSDMEMBER(T_STRING,  above_org_id, 0),\
	DEFSDMEMBER(T_STRING,  inner_org_id, 0),\
	DEFSDMEMBER(T_STRING,  tel, 0),\
	DEFSDMEMBER(T_STRING,  email, 0),\
	DEFSDMEMBER(T_STRING,  org_adress, 0),\
	DEFSDMEMBER(T_STRING,  bak1, 0),\
	DEFSDMEMBER(T_STRING,  bak2, 0),\
	DEFSDMEMBER(T_STRING,  bak3, 0)


	DECLAREFIELDS(SD_T_ORG)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __T_ORG_H__*/
