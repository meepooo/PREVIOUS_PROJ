/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:APP_RWJKB.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[�]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:APP_RWJKB (Ӧ�������ر�)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __APP_RWJKB_H__
#define __APP_RWJKB_H__
typedef struct TDB_APP_RWJKB
{
  char   yybs[8+1];              /*Ӧ�ñ�ʶ*/
              /*Ӧ�ñ�ʶ*/
  char   yymc[40+1];              /*Ӧ������*/
              /*Ӧ������*/
  char   cpdm[16+1];              /*��Ʒ����*/
              /*��Ʒ����*/
  char   cpmc[40+1];              /*��Ʒ����*/
              /*��Ʒ����*/
  char   rwmc[50+1];              /*��������*/
              /*��������*/
  char   jydm[8+1];              /*���״���*/
              /*���״���*/
  char   jymc[40+1];              /*��������*/
              /*��������*/
  int    ptls;              /*ƽ̨��ˮ*/
              /*ƽ̨��ˮ*/
  char   ptrq[8+1];              /*ƽ̨����*/
              /*ƽ̨����*/
  char   jyjg[16+1];              /*���׻���*/
              /*���ѻ���*/
  char   jygy[16+1];              /*���׹�Ա*/
              /*���ѹ�Ա*/
  char   qdbs[3+1];              /*������ʶ*/
              /*������ʶ*/
  char   kssj[19+1];              /*��ʼʱ��*/
              /*��ʼʱ���*/
  char   jssj[19+1];              /*����ʱ��*/
              /*����ʱ���*/
  int    yxsj;              /*����ʱ��*/
              /*���к�����*/
  int    zxcs;              /*���д���*/
              /*���д���*/
  char   zxzt[1+1];              /*ִ��״̬*/
              /*ִ��״̬0:ִ�гɹ�1:ִ��ʧ��9:ִ����*/
  char   xym[5+1];              /*��Ӧ����*/
              /*��Ӧ����*/
  char   xyxx[60+1];              /*��Ӧ��Ϣ*/
              /*��Ӧ��Ϣ*/
  char   extfld1[20+1];              /*��չ�ֶ�1*/
              /*��չ1*/
  char   extfld2[20+1];              /*��չ�ֶ�2*/
              /*��չ2*/
}APP_RWJKB;

#define SD_DATA  APP_RWJKB
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  yybs, 0),\
	DEFSDMEMBER(T_STRING,  yymc, 0),\
	DEFSDMEMBER(T_STRING,  cpdm, 0),\
	DEFSDMEMBER(T_STRING,  cpmc, 0),\
	DEFSDMEMBER(T_STRING,  rwmc, 0),\
	DEFSDMEMBER(T_STRING,  jydm, 0),\
	DEFSDMEMBER(T_STRING,  jymc, 0),\
	DEFSDMEMBER(T_LONG,  ptls, 0),\
	DEFSDMEMBER(T_STRING,  ptrq, 0),\
	DEFSDMEMBER(T_STRING,  jyjg, 0),\
	DEFSDMEMBER(T_STRING,  jygy, 0),\
	DEFSDMEMBER(T_STRING,  qdbs, 0),\
	DEFSDMEMBER(T_STRING,  kssj, 0),\
	DEFSDMEMBER(T_STRING,  jssj, 0),\
	DEFSDMEMBER(T_LONG,  yxsj, 0),\
	DEFSDMEMBER(T_LONG,  zxcs, 0),\
	DEFSDMEMBER(T_STRING,  zxzt, 0),\
	DEFSDMEMBER(T_STRING,  xym, 0),\
	DEFSDMEMBER(T_STRING,  xyxx, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  extfld2, 0)


	DECLAREFIELDS(SD_APP_RWJKB)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_RWJKB_H__*/

