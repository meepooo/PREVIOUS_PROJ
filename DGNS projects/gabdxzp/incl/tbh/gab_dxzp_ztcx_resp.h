/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:gab_dxzp_ztcx_resp.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[����ǿ]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:gab_dxzp_ztcx_resp (����թƭ�����ѯ��Ӧ)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __GAB_DXZP_ZTCX_RESP_H__
#define __GAB_DXZP_ZTCX_RESP_H__
typedef struct TDB_GAB_DXZP_ZTCX_RESP
{
	char   ywsqbh[36+1];  /*ҵ��������*/
		/*������������ˮ�ţ����ڱ�ʶ�������*/
	int   rwxh;  /*�������*/
		/*�������*/
	char   fkjgmc[150+1];  /*������������*/
		/*������������*/
	char   fksm[300+1];  /*��ѯ����˵��*/
		/*��ѯ����˵��*/
	char   zjlx[2+1];  /*��ѯ֤�����ʹ���*/
		/*��ѯ֤�����ʹ���*/
	char   zjhm[30+1];  /*��ѯ֤�պ���*/
		/*��ѯ֤�պ���*/
	char   ztmc[100+1];  /*��ѯ��������*/
		/*��ѯ��������*/
	char   lxsj[20+1];  /*��ϵ�ֻ�*/
		/*��ϵ�ֻ�*/
	char   dbrxm[60+1];  /*��/������������*/
		/*��/������������*/
	char   dbrzjlx[2+1];  /*��/��������֤������*/
		/*��/��������֤������*/
	char   dbrzjhm[30+1];  /*��/��������֤������*/
		/*��/��������֤������*/
	char   zzdz[150+1];  /*סլ��ַ*/
		/*סլ��ַ*/
	char   zzdh[20+1];  /*סլ�绰*/
		/*סլ�绰*/
	char   gzdw[100+1];  /*������λ*/
		/*������λ*/
	char   dwdz[150+1];  /*��λ��ַ*/
		/*��λ��ַ*/
	char   dwdh[20+1];  /*��λ�绰*/
		/*��λ�绰*/
	char   yxdz[60+1];  /*�����ַ*/
		/*�����ַ*/
	char   frdb[60+1];  /*���˴���*/
		/*���˴���*/
	char   frdbzjlx[15+1];  /*���˴���֤������*/
		/*���˴���֤������*/
	char   frdbzjhm[30+1];  /*���˴���֤������*/
		/*���˴���֤������*/
	char   khgszzhm[18+1];  /*�ͻ�����ִ�պ���*/
		/*�ͻ�����ִ�պ���*/
	char   gsnsh[20+1];  /*��˰��˰��*/
		/*��˰��˰��*/
	char   dsnsh[20+1];  /*��˰��˰��*/
		/*��˰��˰��*/
	char   zwrq[8+1];  /*gaps����*/
		/*gaps����*/
	char   systime[6+1];  /*gapsʱ��*/
		/*gapsʱ��*/
	char   by1[30+1];  /*����1*/
		/*����1*/
	char   by2[254+1];  /*����2*/
		/*����2*/
	char   by3[254+1];  /*����3*/
		/*����3*/

}GAB_DXZP_ZTCX_RESP;

#define SD_DATA  GAB_DXZP_ZTCX_RESP
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  ywsqbh, 0),\
	DEFSDMEMBER(T_LONG,  rwxh, 0),\
	DEFSDMEMBER(T_STRING,  fkjgmc, 0),\
	DEFSDMEMBER(T_STRING,  fksm, 0),\
	DEFSDMEMBER(T_STRING,  zjlx, 0),\
	DEFSDMEMBER(T_STRING,  zjhm, 0),\
	DEFSDMEMBER(T_STRING,  ztmc, 0),\
	DEFSDMEMBER(T_STRING,  lxsj, 0),\
	DEFSDMEMBER(T_STRING,  dbrxm, 0),\
	DEFSDMEMBER(T_STRING,  dbrzjlx, 0),\
	DEFSDMEMBER(T_STRING,  dbrzjhm, 0),\
	DEFSDMEMBER(T_STRING,  zzdz, 0),\
	DEFSDMEMBER(T_STRING,  zzdh, 0),\
	DEFSDMEMBER(T_STRING,  gzdw, 0),\
	DEFSDMEMBER(T_STRING,  dwdz, 0),\
	DEFSDMEMBER(T_STRING,  dwdh, 0),\
	DEFSDMEMBER(T_STRING,  yxdz, 0),\
	DEFSDMEMBER(T_STRING,  frdb, 0),\
	DEFSDMEMBER(T_STRING,  frdbzjlx, 0),\
	DEFSDMEMBER(T_STRING,  frdbzjhm, 0),\
	DEFSDMEMBER(T_STRING,  khgszzhm, 0),\
	DEFSDMEMBER(T_STRING,  gsnsh, 0),\
	DEFSDMEMBER(T_STRING,  dsnsh, 0),\
	DEFSDMEMBER(T_STRING,  zwrq, 0),\
	DEFSDMEMBER(T_STRING,  systime, 0),\
	DEFSDMEMBER(T_STRING,  by1, 0),\
	DEFSDMEMBER(T_STRING,  by2, 0),\
	DEFSDMEMBER(T_STRING,  by3, 0)


	DECLAREFIELDS(SD_GAB_DXZP_ZTCX_RESP)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __GAB_DXZP_ZTCX_RESP_H__*/
