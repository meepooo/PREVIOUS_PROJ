/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:APP_CPQDGX.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[�]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:APP_CPQDGX (��Ʒ������ϵ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __APP_CPQDGX_H__
#define __APP_CPQDGX_H__
typedef struct TDB_APP_CPQDGX
{
  char   cpdm[16+1];              /*��Ʒ����*/
              /*��Ʒ����*/
  char   qdbs[3+1];              /*������ʶ*/
              /*������ʶ*/
  char   sjkzbz[1+1];              /*ʱ����Ʊ�־*/
              /*ʱ����Ʊ�־  0���� 1������*/
  char   qssj[6+1];              /*��ʼʱ��*/
              /*��ʼʱ��*/
  char   jssj[6+1];              /*����ʱ��*/
              /*����ʱ��*/
  char   xekzbz[1+1];              /*�޶���Ʊ�־*/
              /*�޶���Ʊ�־ 0���� 1������*/
  double  zxxe;              /*��С�޶�*/
              /*��С�޶�*/
  double  zdxe;              /*����޶�*/
              /*����޶�*/
  char   czbz[1+1];              /*������־*/
              /*�Ƿ��������  0���� 1������*/
  char   zdczbz[1+1];              /*�Զ�������־*/
              /*ϵͳ�쳣�Ƿ��Զ�����  0�� 1��*/
  char   fpbcbz[1+1];              /*��Ʊ�����־*/
              /*��Ʊ�����־ 0���� 1������*/
  char   fpcsfs[1+1];              /*��Ʊ���䷽ʽ*/
              /*��Ʊ���䷽ʽ 0���� 1�ļ�*/
  char   whjg[16+1];              /*ά������*/
              /**/
  char   whgy[16+1];              /*ά����Ա*/
              /**/
  char   whsj[14+1];              /*ά��ʱ��*/
              /**/
  char   extfld1[40+1];              /*��չ����1*/
              /*��չ����1*/
  char   extfld2[40+1];              /*��չ����2*/
              /*��չ����2*/
  char   zt[1+1];              /*״̬*/
              /*״̬ 0���� 1������*/
}APP_CPQDGX;

#define SD_DATA  APP_CPQDGX
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  cpdm, 0),\
	DEFSDMEMBER(T_STRING,  qdbs, 0),\
	DEFSDMEMBER(T_STRING,  sjkzbz, 0),\
	DEFSDMEMBER(T_STRING,  qssj, 0),\
	DEFSDMEMBER(T_STRING,  jssj, 0),\
	DEFSDMEMBER(T_STRING,  xekzbz, 0),\
	DEFSDMEMBER(T_DOUBLE,  zxxe, 2),\
	DEFSDMEMBER(T_DOUBLE,  zdxe, 2),\
	DEFSDMEMBER(T_STRING,  czbz, 0),\
	DEFSDMEMBER(T_STRING,  zdczbz, 0),\
	DEFSDMEMBER(T_STRING,  fpbcbz, 0),\
	DEFSDMEMBER(T_STRING,  fpcsfs, 0),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  extfld2, 0),\
	DEFSDMEMBER(T_STRING,  zt, 0)


	DECLAREFIELDS(SD_APP_CPQDGX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_CPQDGX_H__*/
