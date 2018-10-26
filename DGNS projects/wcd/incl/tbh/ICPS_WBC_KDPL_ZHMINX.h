/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:db2
�� �� ��:ICPS_WBC_KDPL_ZHMINX.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[fuwd22392]
����ʱ��:2018-06-12 10:00:00 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_WBC_KDPL_ZHMINX
˵    ��:���պ��������˺ţ����˺���������д�����ϸ��
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_WBC_KDPL_ZHMINX_H__
#define __ICPS_WBC_KDPL_ZHMINX_H__
typedef struct TDB_ICPS_WBC_KDPL_ZHMINX
{
	char		busi_date[8+1];            /*    ҵ������               */
	int			file_order;                /*     �ļ����              */ 
	char		zhanghao[40+1];            /*   ��ծ�˺�                */ 
	double		mxixuhao;                  /*   ��ϸ���                */ 
	char		jiaoyirq[8+1];             /*   ��������                */ 
	char		khjymxlb[1+1];             /*   �ͻ�������ϸ���        */ 
	char		jyyyjigo[10+1];            /*   ����Ӫҵ����            */ 
	char		kaihjigo[10+1];            /*   �˻���������            */ 
	char		zhhuzwmc[100+1];           /*   �˻�����                */ 
	char		jiedaibz[1+1];             /*   �����־              */   
	char		jiaoybiz[2+1];             /*   ���ױ���              */   
	char		chaohubz[1+1];             /*   �˻������־          */   
	double		jiaoyije;                  /*   ���׽��              */   
	double		zhanghye;                  /*   �˻����              */   
	char		kahaoooo[35+1];            /*   ����                  */   
	char		kehuzhao[35+1];            /*   �ͻ��˺�              */   
	char		zhhaoxuh[8+1];             /*   ���˻����            */   
	char		pngzzlei[4+1];             /*   ƾ֤����              */   
	char		pngzxhao[22+1];            /*   ƾ֤��                */   
	char		zhaiyodm[10+1];            /*   ժҪ����              */   
	char		zhaiyoms[80+1];            /*   ժҪ����              */   
	char		duifjgdm[20+1];            /*   �Է����ڻ���          */   
	char		duifjgmc[60+1];            /*   �Է����ڻ�������      */   
	char		duifkhzh[35+1];            /*   �Է��ͻ��˺�          */   
	char		duifminc[100+1];           /*   �Է�����              */   
	char		duifbezh[200+1];           /*   �Է���ע              */   
	char		beizhuuu[200+1];           /*   ��ע                  */   
	char		qixiriqi[8+1];             /*   ��Ϣ����              */   
	char		qdaoleix[3+1];             /*   ��������              */   
	char		waibclma[20+1];            /*   ���˴���              */   
	char		nbjoyima[10+1];            /*   �ڲ�������            */   
	char		xianzzbz[1+1];             /*   ��ת��־              */   
	char		guiylius[32+1];            /*   ��Ա��ˮ(��������ˮ)  */   
	char		caozguiy[8+1];             /*   ������Ա              */   
	char		zhujriqi[8+1];             /*   ��������              */   
	char		zjyilush[32+1];            /*   ��������ˮ            */   
	char		yewulush[32+1];            /*   ҵ����ˮ              */   
	char		jiaoyisj[16+1];            /*   ����ʱ��              */   
	char		bchongbz[1+1];             /*   ������ϸ״̬          */   
	char		cuozriqi[8+1];             /*   ԭ��������            */   
	char		cuozlius[32+1];            /*   ԭ���˽�����ˮ        */   
	char		yszjylsh[32+1];            /*   ԭʼ��������ˮ        */   
	char		ysyewush[32+1];            /*   ԭʼҵ����ˮ          */   
	char		czczflei[1+1];             /*   �������˷���          */   
	char		mozhanbz[1+1];             /*   Ĩ�˱�־              */   
	char		tokennnn[35+1];            /*   token                 */   
	char		dsftoken[35+1];            /*   ���ַ�token           */   
	double		lilvlilv;                  /*   ����                  */   
	char		jioyshij[10+1];            /*   �����¼�              */   
	char		huidxhao[80+1];            /*   �ص����              */   
	char		farendma[20+1];            /*   ���˴���              */   
	char		weihguiy[8+1];             /*   ά����Ա              */   
	char		weihjigo[10+1];            /*   ά������              */   
	char		weihriqi[8+1];             /*   ά������              */   
	double          shijchuo;                  /*   ʱ���                */   
	char		is_check_flag[1+1];                  /*'������˱�ʶ     */   
	char		extend_param1[100+1];                /*'��չ1            */   
	char		extend_param2[250+1];                /*'��չ2            */   
	char		extend_param3[40+1];                 /*'��չ3            */   
}ICPS_WBC_KDPL_ZHMINX;

#define SD_DATA  ICPS_WBC_KDPL_ZHMINX
#define SD_MEMBERS \ 
  APP_DEFSDMEMBER(T_STRING,  busi_date      ,0),\
  APP_DEFSDMEMBER(T_LONG,    file_order     ,0),\
  APP_DEFSDMEMBER(T_STRING,  zhanghao       ,0),\
  APP_DEFSDMEMBER(T_DOUBLE,  mxixuhao       ,2),\
  APP_DEFSDMEMBER(T_STRING,  jiaoyirq       ,0),\
  APP_DEFSDMEMBER(T_STRING,  khjymxlb       ,0),\
  APP_DEFSDMEMBER(T_STRING,  jyyyjigo       ,0),\
  APP_DEFSDMEMBER(T_STRING,  kaihjigo       ,0),\
  APP_DEFSDMEMBER(T_STRING,  zhhuzwmc       ,0),\
  APP_DEFSDMEMBER(T_STRING,  jiedaibz       ,0),\
  APP_DEFSDMEMBER(T_STRING,  jiaoybiz       ,0),\
  APP_DEFSDMEMBER(T_STRING,  chaohubz       ,0),\
  APP_DEFSDMEMBER(T_DOUBLE,  jiaoyije       ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,  zhanghye       ,2),\
  APP_DEFSDMEMBER(T_STRING,  kahaoooo       ,0),\
  APP_DEFSDMEMBER(T_STRING,  kehuzhao       ,0),\
  APP_DEFSDMEMBER(T_STRING,  zhhaoxuh       ,0),\
  APP_DEFSDMEMBER(T_STRING,  pngzzlei       ,0),\
  APP_DEFSDMEMBER(T_STRING,  pngzxhao       ,0),\
  APP_DEFSDMEMBER(T_STRING,  zhaiyodm       ,0),\
  APP_DEFSDMEMBER(T_STRING,  zhaiyoms       ,0),\
  APP_DEFSDMEMBER(T_STRING,  duifjgdm       ,0),\
  APP_DEFSDMEMBER(T_STRING,  duifjgmc       ,0),\
  APP_DEFSDMEMBER(T_STRING,  duifkhzh       ,0),\
  APP_DEFSDMEMBER(T_STRING,  duifminc       ,0),\
  APP_DEFSDMEMBER(T_STRING,  duifbezh       ,0),\
  APP_DEFSDMEMBER(T_STRING,  beizhuuu       ,0),\
  APP_DEFSDMEMBER(T_STRING,  qixiriqi       ,0),\
  APP_DEFSDMEMBER(T_STRING,  qdaoleix       ,0),\
  APP_DEFSDMEMBER(T_STRING,  waibclma       ,0),\
  APP_DEFSDMEMBER(T_STRING,  nbjoyima       ,0),\
  APP_DEFSDMEMBER(T_STRING,  xianzzbz       ,0),\
  APP_DEFSDMEMBER(T_STRING,  guiylius       ,0),\
  APP_DEFSDMEMBER(T_STRING,  caozguiy       ,0),\
  APP_DEFSDMEMBER(T_STRING,  zhujriqi       ,0),\
  APP_DEFSDMEMBER(T_STRING,  zjyilush       ,0),\
  APP_DEFSDMEMBER(T_STRING,  yewulush       ,0),\
  APP_DEFSDMEMBER(T_STRING,  jiaoyisj       ,0),\
  APP_DEFSDMEMBER(T_STRING,  bchongbz       ,0),\
  APP_DEFSDMEMBER(T_STRING,  cuozriqi       ,0),\
  APP_DEFSDMEMBER(T_STRING,  cuozlius       ,0),\
  APP_DEFSDMEMBER(T_STRING,  yszjylsh       ,0),\
  APP_DEFSDMEMBER(T_STRING,  ysyewush       ,0),\
  APP_DEFSDMEMBER(T_STRING,  czczflei       ,0),\
  APP_DEFSDMEMBER(T_STRING,  mozhanbz       ,0),\
  APP_DEFSDMEMBER(T_STRING,  tokennnn       ,0),\
  APP_DEFSDMEMBER(T_STRING,  dsftoken       ,0),\
  APP_DEFSDMEMBER(T_DOUBLE,  lilvlilv       ,6),\
  APP_DEFSDMEMBER(T_STRING,  jioyshij       ,0),\
  APP_DEFSDMEMBER(T_STRING,  huidxhao       ,0),\
  APP_DEFSDMEMBER(T_STRING,  farendma       ,0),\
  APP_DEFSDMEMBER(T_STRING,  weihguiy       ,0),\
  APP_DEFSDMEMBER(T_STRING,  weihjigo       ,0),\
  APP_DEFSDMEMBER(T_STRING,  weihriqi       ,0),\
  APP_DEFSDMEMBER(T_DOUBLE,  shijchuo       ,2),\
  APP_DEFSDMEMBER(T_STRING,  is_check_flag  ,0),\
  APP_DEFSDMEMBER(T_STRING,  extend_param1  ,0),\
  APP_DEFSDMEMBER(T_STRING,  extend_param2  ,0),\
  APP_DEFSDMEMBER(T_STRING,  extend_param3  ,0)
  APP_DECLAREFIELDS(SD_ICPS_WBC_KDPL_ZHMINX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WBC_KDPL_ZHMINX_H__*/
