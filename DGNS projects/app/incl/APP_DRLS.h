/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:APP_DRLS.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[�]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:APP_DRLS (ƽ̨������ˮ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __APP_DRLS_H__
#define __APP_DRLS_H__
typedef struct TDB_APP_DRLS
{
  char   ptrq[8+1];              /*ƽ̨����*/
              /*ƽ̨���� yyyymmdd*/
  int    ptls;              /*ƽ̨��ˮ��*/
              /*ƽ̨��ˮ��*/
  char   ptsj[6+1];              /*ƽ̨ʱ��*/
              /*ƽ̨ʱ�� hhmmss*/
  char   rzbz[1+1];              /*���ʱ�־*/
              /*���ʱ�־ 0���� 1������*/
  char   jylx[1+1];              /*��������*/
              /*�������� 0������ 1����� 9����*/
  int    yptls;              /*ԭƽ̨��ˮ��*/
              /*ԭƽ̨��ˮ��*/
  char   jyjg[16+1];              /*���׻���*/
              /*���׻���*/
  char   jygy[16+1];              /*���׹�Ա*/
              /*���׹�Ա*/
  char   qdbs[3+1];              /*������ʶ*/
              /*������ʶ */
  char   zdsbbh[8+1];              /*�ն��豸���*/
              /*�ն��豸���*/
  char   yybs[8+1];              /*Ӧ�ñ�ʶ*/
              /*Ӧ�ñ�ʶ */
  char   cpdm[16+1];              /*��Ʒ����*/
              /*��Ʒ����*/
  char   ywbh[16+1];              /*ҵ����*/
              /*ҵ����*/
  char   jydm[8+1];              /*���״���*/
              /*���״���*/
  char   yhbh[32+1];              /*�û����*/
              /*�û���� ���ֻ���*/
  char   xzbz[1+1];              /*��ת��־*/
              /*��ת��־  0�ֽ� 1ת��*/
  char   jdbz[1+1];              /*�����־*/
              /*�����־  �������ֵ�key=k_jdbz*/
  char   zhlx[2+1];              /*�ʻ�����*/
              /*�ʻ�����  �������ֵ�key=k_zhlx*/
  char   yhzh[32+1];              /*�����ʺ�*/
              /*�����ʺ�*/
  char   dfzh[32+1];              /*�Է��ʺ�*/
              /*�Է��ʺ�*/
  double  jyje;              /*���׽��*/
              /*���׽��*/
  double  sxf;              /*������*/
              /*������*/
  int    pcbh;              /*���α��*/
              /*���α��*/
  char   jyxym[8+1];              /*������Ӧ��*/
              /*������Ӧ��*/
  char   jyxyxx[60+1];              /*������Ӧ��Ϣ*/
              /*������Ӧ��Ϣ*/
  char   jyzt[1+1];              /*����״̬*/
              /*����״̬�������ֵ�KEY=K_JYZT*/
  char   extfld1[40+1];              /*��չ1*/
              /*��չ1*/
  char   extfld2[40+1];              /*��չ2*/
              /*��չ2*/
}APP_DRLS;

#define SD_DATA  APP_DRLS
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  ptrq, 0),\
	DEFSDMEMBER(T_LONG,  ptls, 0),\
	DEFSDMEMBER(T_STRING,  ptsj, 0),\
	DEFSDMEMBER(T_STRING,  rzbz, 0),\
	DEFSDMEMBER(T_STRING,  jylx, 0),\
	DEFSDMEMBER(T_LONG,  yptls, 0),\
	DEFSDMEMBER(T_STRING,  jyjg, 0),\
	DEFSDMEMBER(T_STRING,  jygy, 0),\
	DEFSDMEMBER(T_STRING,  qdbs, 0),\
	DEFSDMEMBER(T_STRING,  zdsbbh, 0),\
	DEFSDMEMBER(T_STRING,  yybs, 0),\
	DEFSDMEMBER(T_STRING,  cpdm, 0),\
	DEFSDMEMBER(T_STRING,  ywbh, 0),\
	DEFSDMEMBER(T_STRING,  jydm, 0),\
	DEFSDMEMBER(T_STRING,  yhbh, 0),\
	DEFSDMEMBER(T_STRING,  xzbz, 0),\
	DEFSDMEMBER(T_STRING,  jdbz, 0),\
	DEFSDMEMBER(T_STRING,  zhlx, 0),\
	DEFSDMEMBER(T_STRING,  yhzh, 0),\
	DEFSDMEMBER(T_STRING,  dfzh, 0),\
	DEFSDMEMBER(T_DOUBLE,  jyje, 2),\
	DEFSDMEMBER(T_DOUBLE,  sxf, 2),\
	DEFSDMEMBER(T_LONG,  pcbh, 0),\
	DEFSDMEMBER(T_STRING,  jyxym, 0),\
	DEFSDMEMBER(T_STRING,  jyxyxx, 0),\
	DEFSDMEMBER(T_STRING,  jyzt, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  extfld2, 0)


	DECLAREFIELDS(SD_APP_DRLS)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_DRLS_H__*/
