#ifndef __PABYBH_SERIAL_H__
#define __PABYBH_SERIAL_H__ 

typedef struct TDB_PABYBH_SERIAL
{
	char TRANSDATE[8+1]            ;       /*平台日期*/
	char TRANSSERIALNO[40+1]       ;       /*平台流水号*/
	char ORITRANSDATE[8+1]         ;       /*原平台日期*/
	char ORITRANSSERIALNO[40+1]    ;       /*原平台流水号*/
	char TRANSTIME[8+1]            ;       /*交易时间*/
	char WORKDATE[8+1]             ;       /*业务日期*/
	char WORKSERIALNO[40+1]        ;       /*业务流水号*/
	char REQDATE[8+1]              ;       /*发起方日期*/
	char REQSERIALNO[40+1]         ;       /*发起方流水号*/
	char CLUSTERNODENAME[30+1]     ;       /*集群节点机器名称*/
	char CLUSTERNODEIP[20+1]       ;       /*集群节点机器IP*/
	char COBANKNO[12+1]            ;       /*合作行号*/
	char TRANSORG[10+1]            ;       /*交易机构*/
	char TRANSOPER[10+1]           ;       /*交易柜员*/
	char AUTHORG[10+1]             ;       /*授权机构*/
	char AUTHOPER[10+1]            ;       /*授权柜员*/
	char CNLTYPE[5+1]              ;       /*渠道类型*/
	char TERMEQUINO[20+1]          ;       /*终端设备编号*/
	char TRANSCODE[12+1]           ;       /*交易代码*/
	char TRANSCODE1[1+1]           ;       /*附加交易代码 0 出金 1 入金 2开户手续费 3 补打工本费*/
	char CUACOUNTYPE[1+1]          ;       /*来往账标志 0-往账 1-来账*/
	char TRANSNAME[100+1]          ;       /*交易名称*/
	char CAPITALTYPE[1+1]          ;       /*资金类型,0 ---转出1--- 转入*/
	char SVRCODE[10+1]             ;       /*服务代码   (存管、黄金等)*/
	char CUSTNAME[80+1]            ;       /*客户名称*/
	char CUSTTYPE[2+1]             ;       /*客户类型*/
	char ACCTNO[32+1]              ;       /*银行账号*/
	char ACCTNO2[32+1]             ;       /*帐号2   变更后的账户*/
	char ORIACCTNO[32+1]           ;       /*银行账号  同步*/
	char STOCKCODE[8+1]            ;       /*券商代码*/
	char CAPITALACCTNO[32+1]       ;       /*资金帐号*/
	double TRANSAMT                ;       /*交易金额*/
	double ORITRANSAMT             ;       /*交易金额*/
	double AMT2                    ;       /*金额2*/
	double AMT3                    ;       /*金额3*/
	char CURR[3+1]                 ;       /*币种*/
	char CASHFLAG[1+1]             ;       /*钞汇标识*/
	char IEPSVRCODE[8+1]           ;       /*行E通服务代码*/
	char IEPTRANSCODE[16+1]        ;       /*行E通交易代码*/
	char IEPBSIDATE[8+1]           ;       /*行E通业务日期*/
	char IEPTRADATE[8+1]           ;       /*行E通交易日期*/
	char IEPSERIALNO[32+1]         ;       /*行E通流水号   区别？*/
	char ORIIEPBSIDATE[8+1]        ;       /*原行E通业务日期*/
	char ORIIEPSERIALNO[32+1]      ;       /*原行E通流水号*/
	char IEPRESPCODE[12+1]         ;       /*行E通响应代码*/
	char IEPRESPMSG[120+1]         ;       /*行E通响应信息*/
	char HOSTBSIDATE[8+1]          ;       /*主机账务日期*/
	char HOSTSERIALNO[32+1]        ;       /*主机流水号*/
	char HOSTTRANSCODE[16+1]       ;       /*主机交易代码*/
	char HOSTRESPCODE[12+1]        ;       /*主机响应代码*/
	char HOSTRESPMSG[120+1]        ;       /*主机响应信息*/
	char RESPCODE[10+1]            ;       /*响应码*/
	char RESPMSG[120+1]            ;       /*响应信息*/
	char IEPSTAT[1+1]              ;       /*中心交易状态'0成功 1失败 6状态未知 7被冲正 8被撤销 9初始'*/
	char HOSTSTAT[1+1]             ;       /*核心交易状态'0成功 1失败 6状态未知 7被冲正 8被撤销 9初始'*/
	char STAT[1+1]                 ;       /*交易状态'0成功 1失败 6状态未知 7被冲正 8被撤销 9初始'*/
	char ORISTAT[1+1]              ;       /*平台同步中心状态前原状态 '0成功 1失败 6状态未知 7被冲正 8被撤销 9初始 X原流水不存在'*/
	char CERTTYPE[2+1]             ;       /*证件类型*/
	char CERTNO[32+1]              ;       /*证件号码*/
  char PHONE[20+1]               ;       /*联系方式      */
  char AGENTNAME[80+1]           ;       /*代理人客户名称*/
  char AGENTCERTY[2+1]           ;       /*代理人证件类型*/
  char AGENTCERNO[32+1]          ;       /*代理人证件号码*/
  char AGENTPHONE[20+1]          ;       /*代理人联系方式*/
	char CHKFLAG[1+1]              ;       /*对账标志,0-未对账1-已对平2-平安多3-核心多9-对账中*/
	char MEMO[128+1]               ;       /*备注*/
	char EXTFLD1[64+1]             ;       /*备用字段1*/
	char EXTFLD2[64+1]             ;       /*备用字段2*/
	char EXTFLD3[128+1]            ;       /*备用字段3*/
	char EXTFLD4[128+1]                    /*备用字段4*/
}PABYBH_SERIAL;	

#define SD_DATA  PABYBH_SERIAL
#define SD_MEMBERS \
  DEFSDMEMBER(T_STRING,  TRANSDATE, 0),\
  DEFSDMEMBER(T_STRING,  TRANSSERIALNO, 0),\
  DEFSDMEMBER(T_STRING,  ORITRANSDATE, 0),\
  DEFSDMEMBER(T_STRING,  ORITRANSSERIALNO, 0),\
  DEFSDMEMBER(T_STRING,  TRANSTIME, 0),\
  DEFSDMEMBER(T_STRING,  WORKDATE, 0),\
  DEFSDMEMBER(T_STRING,  WORKSERIALNO, 0),\
  DEFSDMEMBER(T_STRING,  REQDATE, 0),\
  DEFSDMEMBER(T_STRING,  REQSERIALNO, 0),\
  DEFSDMEMBER(T_STRING,  CLUSTERNODENAME, 0),\
  DEFSDMEMBER(T_STRING,  CLUSTERNODEIP, 0),\
  DEFSDMEMBER(T_STRING,  COBANKNO, 0),\
  DEFSDMEMBER(T_STRING,  TRANSORG, 0),\
  DEFSDMEMBER(T_STRING,  TRANSOPER, 0),\
  DEFSDMEMBER(T_STRING,  AUTHORG, 0),\
  DEFSDMEMBER(T_STRING,  AUTHOPER, 0),\
  DEFSDMEMBER(T_STRING,  CNLTYPE, 0),\
  DEFSDMEMBER(T_STRING,  TERMEQUINO, 0),\
  DEFSDMEMBER(T_STRING,  TRANSCODE, 0),\
  DEFSDMEMBER(T_STRING,  TRANSCODE1, 0),\
  DEFSDMEMBER(T_STRING,  CUACOUNTYPE, 0),\
  DEFSDMEMBER(T_STRING,  TRANSNAME, 0),\
  DEFSDMEMBER(T_STRING,  CAPITALTYPE, 0),\
  DEFSDMEMBER(T_STRING,  SVRCODE, 0),\
  DEFSDMEMBER(T_STRING,  CUSTNAME, 0),\
  DEFSDMEMBER(T_STRING,  CUSTTYPE, 0),\
  DEFSDMEMBER(T_STRING,  ACCTNO, 0),\
  DEFSDMEMBER(T_STRING,  ORIACCTNO, 0),\
  DEFSDMEMBER(T_STRING,  ACCTNO2, 0),\
  DEFSDMEMBER(T_STRING,  STOCKCODE, 0),\
  DEFSDMEMBER(T_STRING,  CAPITALACCTNO, 0),\
  DEFSDMEMBER(T_DOUBLE,  TRANSAMT, 0),\
  DEFSDMEMBER(T_DOUBLE,  ORITRANSAMT, 0),\
  DEFSDMEMBER(T_DOUBLE,  AMT2, 0),\
  DEFSDMEMBER(T_DOUBLE,  AMT3, 0),\
  DEFSDMEMBER(T_STRING,  CURR, 0),\
  DEFSDMEMBER(T_STRING,  CASHFLAG, 0),\
  DEFSDMEMBER(T_STRING,  IEPSVRCODE, 0),\
  DEFSDMEMBER(T_STRING,  IEPTRANSCODE, 0),\
  DEFSDMEMBER(T_STRING,  IEPBSIDATE, 0),\
  DEFSDMEMBER(T_STRING,  IEPTRADATE, 0),\
  DEFSDMEMBER(T_STRING,  IEPSERIALNO, 0),\
  DEFSDMEMBER(T_STRING,  ORIIEPBSIDATE, 0),\
  DEFSDMEMBER(T_STRING,  ORIIEPSERIALNO, 0),\
  DEFSDMEMBER(T_STRING,  IEPRESPCODE, 0),\
  DEFSDMEMBER(T_STRING,  IEPRESPMSG, 0),\
  DEFSDMEMBER(T_STRING,  HOSTBSIDATE, 0),\
  DEFSDMEMBER(T_STRING,  HOSTSERIALNO, 0),\
  DEFSDMEMBER(T_STRING,  HOSTTRANSCODE, 0),\
  DEFSDMEMBER(T_STRING,  HOSTRESPCODE, 0),\
  DEFSDMEMBER(T_STRING,  HOSTRESPMSG, 0),\
  DEFSDMEMBER(T_STRING,  RESPCODE, 0),\
  DEFSDMEMBER(T_STRING,  RESPMSG, 0),\
  DEFSDMEMBER(T_STRING,  IEPSTAT, 0),\
  DEFSDMEMBER(T_STRING,  HOSTSTAT, 0),\
  DEFSDMEMBER(T_STRING,  STAT, 0),\
  DEFSDMEMBER(T_STRING,  ORISTAT, 0),\
  DEFSDMEMBER(T_STRING,  CERTTYPE, 0),\
  DEFSDMEMBER(T_STRING,  CERTNO, 0),\
  DEFSDMEMBER(T_STRING,  PHONE, 0),\
  DEFSDMEMBER(T_STRING,  AGENTNAME, 0),\
  DEFSDMEMBER(T_STRING,  AGENTCERTY, 0),\
  DEFSDMEMBER(T_STRING,  AGENTCERNO, 0),\
  DEFSDMEMBER(T_STRING,  AGENTPHONE, 0),\
  DEFSDMEMBER(T_STRING,  CHKFLAG, 0),\
  DEFSDMEMBER(T_STRING,  MEMO, 0),\
  DEFSDMEMBER(T_STRING,  EXTFLD1, 0),\
  DEFSDMEMBER(T_STRING,  EXTFLD2, 0),\
  DEFSDMEMBER(T_STRING,  EXTFLD3, 0),\
  DEFSDMEMBER(T_STRING,  EXTFLD4, 0)

  DECLAREFIELDS(SD_PABYBH_SERIAL)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __PABYBH_SERIAL_H__*/
