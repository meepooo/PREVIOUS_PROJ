#ifndef __PABYBH_SIGN_H__
#define __PABYBH_SIGN_H__ 

typedef struct TDB_PABYBH_SIGN
{
    char PROTOCOLNO[14+1];                 /*  指定日期  */
    char SIGNDATE[8+1];                 /*  指定日期  */
    char SIGNTIME[6+1];                 /*  指定时间  */
    char COBANKNO[12+1];              /*  合作行号  */
    char ACCTNO[32+1]; 					/*  银行账号  */
    char OLDACCTNO[32+1]; 					/* 老 银行账号  */
    char CERTTYPE[2+1]; 					    /* 证件类型  */
    char CERTNO[32+1]; 					    /* 证件号码 */
    char CUSTTYPE[2+1]; 					    /* 客户类型 */
	char CUSTNAME[120+1]; 					    /* 客户名称 */
	char STOCKCODE[8+1]; 					    /* 券商代码 */
	char CAPITALACCTNO[30+1]; 		/* 证券资金台账号 */
	char SVRCODE[6+1]; 					/* 服务代码 */
	char CURR[3+1]; 					/* 币种 */
	char CUSTMANAGERID[20+1]; 					/* 客户经理号 */
	char CUSTMANAGERNAME[20+1]; 					/* 客户经理名称 */
	char OPENORG[10+1]; 					/* 开户网点号 */
	char BUSITYPE[2+1]; 					/* 业务类型 */
	char STAT[1+1]; 					/* 签约状态 */
	char HOSTSTAT[1+1]; 					/* 核心签约状态 */
	char HOSTDATE[8+1]; 					/* 核心签约日期 */
	char HOSTSERIALNO[40+1]; 					/* 核心流水*/
	char CHKFLAG[1+1]; 					/* 对账标志*/
	char UPDATEDATE[8+1];				/* 更新日期*/
	char UPDATETIME[6+1];				/* 更新时间*/
	char TRANSORG[10+1];				/* 交易机构*/
	char TRANSOPER[20+1];				/* 交易柜员*/
    char AGENTNAME[80+1]           ;       /*代理人客户名称*/
    char AGENTCERTY[2+1]           ;       /*代理人证件类型*/
    char AGENTCERNO[32+1]          ;       /*代理人证件号码*/
    char AGENTPHONE[20+1]          ;       /*代理人联系方式*/
    char MEMO[40+1];				/* 备注*/
char EXTFLD1[32+1];                  /*  备用字段1  */
    char EXTFLD2[32+1];                  /*  备用字段2  */
    char EXTFLD3[64+1];                  /*  备用字段3 */
    char EXTFLD4[64+1];                  /*  备用字段4  */
    char EXTFLD5[64+1];                  /*  备用字段5  */
    char EXTFLD6[64+1]               /*  备用字段6 */
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
