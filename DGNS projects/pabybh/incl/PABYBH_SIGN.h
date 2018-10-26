#ifndef __PABYBH_SIGN_H__
#define __PABYBH_SIGN_H__ 

typedef struct TDB_PABYBH_SIGN
{
    char PROTOCOLNO[14+1];                 /*  ָ������  */
    char SIGNDATE[8+1];                 /*  ָ������  */
    char SIGNTIME[6+1];                 /*  ָ��ʱ��  */
    char COBANKNO[12+1];              /*  �����к�  */
    char ACCTNO[32+1]; 					/*  �����˺�  */
    char OLDACCTNO[32+1]; 					/* �� �����˺�  */
    char CERTTYPE[2+1]; 					    /* ֤������  */
    char CERTNO[32+1]; 					    /* ֤������ */
    char CUSTTYPE[2+1]; 					    /* �ͻ����� */
	char CUSTNAME[120+1]; 					    /* �ͻ����� */
	char STOCKCODE[8+1]; 					    /* ȯ�̴��� */
	char CAPITALACCTNO[30+1]; 		/* ֤ȯ�ʽ�̨�˺� */
	char SVRCODE[6+1]; 					/* ������� */
	char CURR[3+1]; 					/* ���� */
	char CUSTMANAGERID[20+1]; 					/* �ͻ������ */
	char CUSTMANAGERNAME[20+1]; 					/* �ͻ��������� */
	char OPENORG[10+1]; 					/* ��������� */
	char BUSITYPE[2+1]; 					/* ҵ������ */
	char STAT[1+1]; 					/* ǩԼ״̬ */
	char HOSTSTAT[1+1]; 					/* ����ǩԼ״̬ */
	char HOSTDATE[8+1]; 					/* ����ǩԼ���� */
	char HOSTSERIALNO[40+1]; 					/* ������ˮ*/
	char CHKFLAG[1+1]; 					/* ���˱�־*/
	char UPDATEDATE[8+1];				/* ��������*/
	char UPDATETIME[6+1];				/* ����ʱ��*/
	char TRANSORG[10+1];				/* ���׻���*/
	char TRANSOPER[20+1];				/* ���׹�Ա*/
    char AGENTNAME[80+1]           ;       /*�����˿ͻ�����*/
    char AGENTCERTY[2+1]           ;       /*������֤������*/
    char AGENTCERNO[32+1]          ;       /*������֤������*/
    char AGENTPHONE[20+1]          ;       /*��������ϵ��ʽ*/
    char MEMO[40+1];				/* ��ע*/
char EXTFLD1[32+1];                  /*  �����ֶ�1  */
    char EXTFLD2[32+1];                  /*  �����ֶ�2  */
    char EXTFLD3[64+1];                  /*  �����ֶ�3 */
    char EXTFLD4[64+1];                  /*  �����ֶ�4  */
    char EXTFLD5[64+1];                  /*  �����ֶ�5  */
    char EXTFLD6[64+1]               /*  �����ֶ�6 */
}PABYBH_SIGN;	

#define SD_DATA  PABYBH_SIGN
#define SD_MEMBERS \
    DEFSDMEMBER(T_STRING,  PROTOCOLNO, 0),\
    DEFSDMEMBER(T_STRING,  SIGNDATE, 0),\
    DEFSDMEMBER(T_STRING,  SIGNTIME, 0),\
    DEFSDMEMBER(T_STRING,  COBANKNO, 0),\
    DEFSDMEMBER(T_STRING,  ACCTNO, 0),\
    DEFSDMEMBER(T_STRING,  OLDACCTNO, 0),\
    DEFSDMEMBER(T_STRING,  CERTTYPE, 0),\
    DEFSDMEMBER(T_STRING,  CERTNO, 0),\
    DEFSDMEMBER(T_STRING,  CUSTTYPE, 0),\
    DEFSDMEMBER(T_STRING,  CUSTNAME, 0),\
    DEFSDMEMBER(T_STRING,  STOCKCODE, 0),\
    DEFSDMEMBER(T_STRING,  CAPITALACCTNO, 0),\
    DEFSDMEMBER(T_STRING,  SVRCODE, 0),\
    DEFSDMEMBER(T_STRING,  CURR, 0),\
    DEFSDMEMBER(T_STRING,  CUSTMANAGERID, 0),\
    DEFSDMEMBER(T_STRING,  CUSTMANAGERNAME, 0),\
    DEFSDMEMBER(T_STRING,  OPENORG, 0),\
    DEFSDMEMBER(T_STRING,  BUSITYPE, 0),\
    DEFSDMEMBER(T_STRING,  STAT, 0),\
    DEFSDMEMBER(T_STRING,  HOSTSTAT, 0),\
    DEFSDMEMBER(T_STRING,  HOSTDATE, 0),\
    DEFSDMEMBER(T_STRING,  HOSTSERIALNO, 0),\
    DEFSDMEMBER(T_STRING,  CHKFLAG, 0),\
    DEFSDMEMBER(T_STRING,  UPDATEDATE, 0),\
    DEFSDMEMBER(T_STRING,  UPDATETIME, 0),\
    DEFSDMEMBER(T_STRING,  TRANSORG, 0),\
    DEFSDMEMBER(T_STRING,  TRANSOPER, 0),\
    DEFSDMEMBER(T_STRING,  AGENTNAME, 0),\
    DEFSDMEMBER(T_STRING,  AGENTCERTY, 0),\
    DEFSDMEMBER(T_STRING,  AGENTCERNO, 0),\
    DEFSDMEMBER(T_STRING,  AGENTPHONE, 0),\
    DEFSDMEMBER(T_STRING,  MEMO, 0),\
    DEFSDMEMBER(T_STRING,  EXTFLD1, 0),\
    DEFSDMEMBER(T_STRING,  EXTFLD2, 0),\
    DEFSDMEMBER(T_STRING,  EXTFLD3, 0),\
    DEFSDMEMBER(T_STRING,  EXTFLD4, 0),\
    DEFSDMEMBER(T_STRING,  EXTFLD5, 0),\
    DEFSDMEMBER(T_STRING,  EXTFLD6, 0)

  DECLAREFIELDS(SD_PABYBH_SIGN)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __PAB_ICC_DLCG_CHKINFO_H__*/
