/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:AGENT_DZLSB.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[�]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:AGENT_DZLSB (������ˮ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __AGENT_DZLSB_H__
#define __AGENT_DZLSB_H__
typedef struct TDB_AGENT_DZLSB
{
  char   ptrq[8+1];              /*ƽ̨����*/
              /*ƽ̨����*/
  int    ptls;              /*ƽ̨��ˮ��*/
              /*ƽ̨��ˮ��*/
  char   zjrq[8+1];              /*��������*/
              /*��������*/
  char   zjls[32+1];              /*������ˮ��*/
              /*������ˮ��*/
  char   jyjg[16+1];              /*���׻���*/
              /*���׻���*/
  char   jygy[16+1];              /*���׹�Ա*/
              /*���׹�Ա*/
  char   jybz[3+1];              /*���ױ���*/
              /*���ױ��� �������ֵ� KE  K_JYBZ*/
  char   ywbh[16+1];              /*ҵ����*/
              /*ҵ����*/
  char   cpdm[16+1];              /*��Ʒ����*/
              /*��Ʒ����*/
  char   xzbz[1+1];              /*��ת��־*/
              /*��ת��־ 0�ֽ� 1ת��*/
  char   jdbz[1+1];              /*�����ʶ*/
              /*�����־(d �� C��)*/
  double  jyje;              /*���׽��*/
              /*���׽��*/
  char   jfzh[32+1];              /*�跽�ʺ�*/
              /*�跽�ʺ�*/
  char   jffzh[10+1];              /*�跽���ʺ�*/
              /*�跽���ʺ�*/
  char   dfzh[32+1];              /*�����ʺ�*/
              /*�����ʺ�*/
  char   dffzh[10+1];              /*�������ʺ�*/
              /*�������ʺ�*/
  char   extfld1[20+1];              /*��չ�ֶ�1*/
              /*��չ�ֶ�1*/
  char   extfld2[20+1];              /*��չ�ֶ�2*/
              /*��չ�ֶ�2*/
  char   extfld3[20+1];              /*��չ�ֶ�3*/
              /*��չ�ֶ�3*/
  char   jyzt[1+1];              /*����״̬*/
              /*����״̬ k_jyzt*/
  char   zjdzbz[1+1];              /*�������ʱ�־*/
              /*���ʱ�־  0 δ���  �  ƽ̨�  ƽ̨��*/
}AGENT_DZLSB;

#define SD_DATA  AGENT_DZLSB
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  ptrq, 0),\
	DEFSDMEMBER(T_LONG,  ptls, 0),\
	DEFSDMEMBER(T_STRING,  zjrq, 0),\
	DEFSDMEMBER(T_STRING,  zjls, 0),\
	DEFSDMEMBER(T_STRING,  jyjg, 0),\
	DEFSDMEMBER(T_STRING,  jygy, 0),\
	DEFSDMEMBER(T_STRING,  jybz, 0),\
	DEFSDMEMBER(T_STRING,  ywbh, 0),\
	DEFSDMEMBER(T_STRING,  cpdm, 0),\
	DEFSDMEMBER(T_STRING,  xzbz, 0),\
	DEFSDMEMBER(T_STRING,  jdbz, 0),\
	DEFSDMEMBER(T_DOUBLE,  jyje, 2),\
	DEFSDMEMBER(T_STRING,  jfzh, 0),\
	DEFSDMEMBER(T_STRING,  jffzh, 0),\
	DEFSDMEMBER(T_STRING,  dfzh, 0),\
	DEFSDMEMBER(T_STRING,  dffzh, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  extfld2, 0),\
	DEFSDMEMBER(T_STRING,  extfld3, 0),\
	DEFSDMEMBER(T_STRING,  jyzt, 0),\
	DEFSDMEMBER(T_STRING,  zjdzbz, 0)


	DECLAREFIELDS(SD_AGENT_DZLSB)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __AGENT_DZLSB_H__*/
