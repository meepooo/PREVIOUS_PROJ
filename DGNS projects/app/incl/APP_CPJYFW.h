/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:APP_CPJYFW.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[�]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:APP_CPJYFW (��Ʒ���׷����ϵ)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __APP_CPJYFW_H__
#define __APP_CPJYFW_H__
typedef struct TDB_APP_CPJYFW
{
  char   cpdm[16+1];              /*��Ʒ����*/
  char   jydm[8+1];              /*���״���*/
  char   sjkzbz[1+1];              /*ʱ����Ʊ�־*/
  char   qssj[6+1];              /*��ʼʱ��*/
  char   jssj[6+1];              /*����ʱ��*/
  char   xekzbz[1+1];              /*�޶���Ʊ�־*/
  double  zxxe;              /*��С�޶�*/
  double  zdxe;              /*����޶�*/
  char   qykzbz[1+1];              /*ǩԼ���Ʊ�־*/
  char   qxkz[8+1];              /*Ȩ�޿��Ʊ�־*/
  char   gyedkzfs[1+1];              /*��Ա��ȿ��Ʒ�ʽ*/
  char   jgedkzfs[1+1];              /*������ȿ��Ʒ�ʽ*/
  char   whjg[16+1];              /*ά������*/
  char   whgy[16+1];              /*ά����Ա*/
  char   whsj[14+1];              /*ά��ʱ��*/
  char   extfld1[40+1];              /*��չ����1*/
  char   extfld2[40+1];              /*��չ����2*/
  char   qtbz[1+1];              /*��ͣ��־*/
}APP_CPJYFW;

#define SD_DATA  APP_CPJYFW
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  cpdm, 0),\
	DEFSDMEMBER(T_STRING,  jydm, 0),\
	DEFSDMEMBER(T_STRING,  sjkzbz, 0),\
	DEFSDMEMBER(T_STRING,  qssj, 0),\
	DEFSDMEMBER(T_STRING,  jssj, 0),\
	DEFSDMEMBER(T_STRING,  xekzbz, 0),\
	DEFSDMEMBER(T_DOUBLE,  zxxe, 2),\
	DEFSDMEMBER(T_DOUBLE,  zdxe, 2),\
	DEFSDMEMBER(T_STRING,  qykzbz, 0),\
	DEFSDMEMBER(T_STRING,  qxkz, 0),\
	DEFSDMEMBER(T_STRING,  gyedkzfs, 0),\
	DEFSDMEMBER(T_STRING,  jgedkzfs, 0),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  extfld2, 0),\
	DEFSDMEMBER(T_STRING,  qtbz, 0)


	DECLAREFIELDS(SD_APP_CPJYFW)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_CPJYFW_H__*/
