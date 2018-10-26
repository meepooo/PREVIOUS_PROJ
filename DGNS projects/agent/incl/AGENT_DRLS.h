/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:AGENT_DRLS.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[�]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:AGENT_DRLS (���ո�Ӧ�õ�����ˮ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __AGENT_DRLS_H__
#define __AGENT_DRLS_H__
typedef struct TDB_AGENT_DRLS
{
  char   ptrq[8+1];              /*ƽ̨����*/
  char   ptsj[6+1];              /*ƽ̨ʱ��*/
  int    ptls;              /*ƽ̨��ˮ��*/
  int    jyxh;              /*�������к�*/
  int    yptlsh;              /*ԭƽ̨��ˮ��*/
  char   jyjg[16+1];              /*���׻���*/
  char   jygy[16+1];              /*���׹�Ա*/
  char   sqjg[16+1];              /*��Ȩ����*/
  char   sqgy[16+1];              /*��Ȩ��Ա*/
  char   qdbs[3+1];              /*������ʶ*/
  char   zdsbbh[8+1];              /*�ն��豸���*/
  char   cpdm[16+1];              /*��Ʒ����*/
  char   ywbh[16+1];              /*ҵ����*/
  char   ywrq[8+1];              /*ҵ������*/
  int    ywlsh;              /*ҵ����ˮ��*/
  char   jydm[8+1];              /*���״���*/
  char   khmc[80+1];              /*�ͻ�����*/
  char   khbh[32+1];              /*�ͻ����*/
  char   dqdm[8+1];              /*��������*/
  char   yhlx[16+1];              /*�û�����*/
  char   yhh1[32+1];              /*�û���*/
  char   yhbsh[32+1];              /*�û���ʶ��*/
  char   yhmc[80+1];              /*�û�����*/
  char   jybz[3+1];              /*���ױ���*/
  char   xzbz[1+1];              /*��ת��־*/
  char   jdbz[1+1];              /*�����־*/
  char   zhlx[2+1];              /*�ʻ�����*/
  char   yhzh[32+1];              /*�����ʺ�*/
  double  jyje;              /*���׽��*/
  double  jyje2;              /*���׽��2*/
  double  sxf;              /*������*/
  double  znj;              /*���ɽ�*/
  char   pzzl[3+1];              /*ƾ֤����*/
  char   pzhm[32+1];              /*ƾ֤����*/
  char   jfbsh[32+1];              /*�ɷѱ�ʶ��*/
  int    cxlsh;              /*��ѯ��ˮ��*/
  char   jyzy[40+1];              /*����ժҪ*/
  char   fqflsh[32+1];              /*������ˮ��*/
  char   fqfrq[8+1];              /*��������*/
  char   fqfsj[6+1];              /*����ʱ��*/
  char   fqfjydm[8+1];              /*���𷽽��״���*/
  char   dsflsh[22+1];              /*��������ˮ��*/
  char   dsfrq[14+1];              /*����������*/
  char   dsfjylx[8+1];              /*����������������*/
  char   dsfjydm[8+1];              /*���������״���*/
  char   dsfxym[8+1];              /*��������Ӧ��*/
  char   dsfxyxx[60+1];              /*��������Ӧ��Ϣ*/
  char   dsfjyzt[1+1];              /*����������״̬*/
  char   zjlsh[32+1];              /*������ˮ��*/
  char   zjrq[14+1];              /*��������*/
  char   zjjydm[8+1];              /*�������״���*/
  char   zjxym[8+1];              /*������Ӧ��*/
  char   zjxyxx[60+1];              /*������Ӧ��Ϣ*/
  char   zjjyzt[1+1];              /*��������״̬*/
  char   jyxym[8+1];              /*������Ӧ��*/
  char   jyxyxx[60+1];              /*������Ӧ��Ϣ*/
  char   jyzt[1+1];              /*����״̬*/
  char   dsfdzbz[1+1];              /*���������ʱ�־*/
  char   zjdzbz[1+1];              /*�������ʱ�־*/
  char   extfld1[40+1];              /*��չ1*/
  char   extfld2[40+1];              /*��չ2*/
  char   extfld3[40+1];              /*��չ3*/
  char   extfld4[40+1];              /*��չ4*/
  char   extfld5[40+1];              /*��չ5*/
  char   extfld6[40+1];              /*��չ6*/
}AGENT_DRLS;

#define SD_DATA  AGENT_DRLS
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  ptrq, 0),\
	DEFSDMEMBER(T_STRING,  ptsj, 0),\
	DEFSDMEMBER(T_LONG,  ptls, 0),\
	DEFSDMEMBER(T_LONG,  jyxh, 0),\
	DEFSDMEMBER(T_LONG,  yptlsh, 0),\
	DEFSDMEMBER(T_STRING,  jyjg, 0),\
	DEFSDMEMBER(T_STRING,  jygy, 0),\
	DEFSDMEMBER(T_STRING,  sqjg, 0),\
	DEFSDMEMBER(T_STRING,  sqgy, 0),\
	DEFSDMEMBER(T_STRING,  qdbs, 0),\
	DEFSDMEMBER(T_STRING,  zdsbbh, 0),\
	DEFSDMEMBER(T_STRING,  cpdm, 0),\
	DEFSDMEMBER(T_STRING,  ywbh, 0),\
	DEFSDMEMBER(T_STRING,  ywrq, 0),\
	DEFSDMEMBER(T_LONG,  ywlsh, 0),\
	DEFSDMEMBER(T_STRING,  jydm, 0),\
	DEFSDMEMBER(T_STRING,  khmc, 0),\
	DEFSDMEMBER(T_STRING,  khbh, 0),\
	DEFSDMEMBER(T_STRING,  dqdm, 0),\
	DEFSDMEMBER(T_STRING,  yhlx, 0),\
	DEFSDMEMBER(T_STRING,  yhh1, 0),\
	DEFSDMEMBER(T_STRING,  yhbsh, 0),\
	DEFSDMEMBER(T_STRING,  yhmc, 0),\
	DEFSDMEMBER(T_STRING,  jybz, 0),\
	DEFSDMEMBER(T_STRING,  xzbz, 0),\
	DEFSDMEMBER(T_STRING,  jdbz, 0),\
	DEFSDMEMBER(T_STRING,  zhlx, 0),\
	DEFSDMEMBER(T_STRING,  yhzh, 0),\
	DEFSDMEMBER(T_DOUBLE,  jyje, 2),\
	DEFSDMEMBER(T_DOUBLE,  jyje2, 2),\
	DEFSDMEMBER(T_DOUBLE,  sxf, 2),\
	DEFSDMEMBER(T_DOUBLE,  znj, 2),\
	DEFSDMEMBER(T_STRING,  pzzl, 0),\
	DEFSDMEMBER(T_STRING,  pzhm, 0),\
	DEFSDMEMBER(T_STRING,  jfbsh, 0),\
	DEFSDMEMBER(T_LONG,  cxlsh, 0),\
	DEFSDMEMBER(T_STRING,  jyzy, 0),\
	DEFSDMEMBER(T_STRING,  fqflsh, 0),\
	DEFSDMEMBER(T_STRING,  fqfrq, 0),\
	DEFSDMEMBER(T_STRING,  fqfsj, 0),\
	DEFSDMEMBER(T_STRING,  fqfjydm, 0),\
	DEFSDMEMBER(T_STRING,  dsflsh, 0),\
	DEFSDMEMBER(T_STRING,  dsfrq, 0),\
	DEFSDMEMBER(T_STRING,  dsfjylx, 0),\
	DEFSDMEMBER(T_STRING,  dsfjydm, 0),\
	DEFSDMEMBER(T_STRING,  dsfxym, 0),\
	DEFSDMEMBER(T_STRING,  dsfxyxx, 0),\
	DEFSDMEMBER(T_STRING,  dsfjyzt, 0),\
	DEFSDMEMBER(T_STRING,  zjlsh, 0),\
	DEFSDMEMBER(T_STRING,  zjrq, 0),\
	DEFSDMEMBER(T_STRING,  zjjydm, 0),\
	DEFSDMEMBER(T_STRING,  zjxym, 0),\
	DEFSDMEMBER(T_STRING,  zjxyxx, 0),\
	DEFSDMEMBER(T_STRING,  zjjyzt, 0),\
	DEFSDMEMBER(T_STRING,  jyxym, 0),\
	DEFSDMEMBER(T_STRING,  jyxyxx, 0),\
	DEFSDMEMBER(T_STRING,  jyzt, 0),\
	DEFSDMEMBER(T_STRING,  dsfdzbz, 0),\
	DEFSDMEMBER(T_STRING,  zjdzbz, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  extfld2, 0),\
	DEFSDMEMBER(T_STRING,  extfld3, 0),\
	DEFSDMEMBER(T_STRING,  extfld4, 0),\
	DEFSDMEMBER(T_STRING,  extfld5, 0),\
	DEFSDMEMBER(T_STRING,  extfld6, 0)


	DECLAREFIELDS(SD_AGENT_DRLS)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __AGENT_DRLS_H__*/

