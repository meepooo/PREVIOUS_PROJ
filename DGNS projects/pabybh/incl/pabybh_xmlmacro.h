/********************************************************************
版权所有:杭州恒生电子股份有限公司
项目名称:综合应用平台（GAPS）项目
版    本:V1.0
操作系统:AIX SCO LINUX SunOS HP-UX
数 据 库:
文件名称:通用XML元素名称宏定义头文件
文件描述:pabybh_xmlmacro.h
项 目 组:
程 序 员:
发布日期:
修    订:
修改日期:
*********************************************************************/
/*
修改记录
修改日期:
修改内容:
修改人:
*/


#ifndef __PABYBH_XMLMACRO_H__
#define __PABYBH_XMLMACRO_H__

#define XMLNM_APP_JYXX_LSJLBZ           "/app/jyxx/lsjlbz"               /*流水记录标志 0 记录 1 不记录*/

/*一般XML节点   BEGIN-----*/
#define XMLNM_PABYBH_REQ_TRANSDATE             "/pabybh/req/transdate"            /*平台日期*/
#define XMLNM_PABYBH_REQ_TRANSSERIALNO         "/pabybh/req/transserialno"        /*平台流水号*/
#define XMLNM_PABYBH_REQ_ORITRANSDATE          "/pabybh/req/oritransdate"         /*原交易日期*/
#define XMLNM_PABYBH_REQ_ORITRANSSERIALNO      "/pabybh/req/oritransserialno"     /*原综合前置流水号*/
#define XMLNM_PABYBH_REQ_TRANSTIME             "/pabybh/req/transtime"            /*交易时间*/
#define XMLNM_PABYBH_REQ_WORKDATE              "/pabybh/req/workdate"             /*业务日期*/
#define XMLNM_PABYBH_REQ_WORKSERIALNO          "/pabybh/req/workserialno"         /*业务流水号*/
#define XMLNM_PABYBH_REQ_REQDATE               "/pabybh/req/reqdate"              /*发起方日期*/
#define XMLNM_PABYBH_REQ_REQSERIALNO           "/pabybh/req/reqserialno"          /*发起方流水号*/
#define XMLNM_PABYBH_REQ_CLUSTERNODENAME       "/pabybh/req/clusternodename"      /*集群节点机器名称*/
#define XMLNM_PABYBH_REQ_CLUSTERNODEIP         "/pabybh/req/clusternodeip"        /*集群节点机器IP*/
#define XMLNM_PABYBH_REQ_COBANKNO              "/pabybh/req/cobankno"             /*合作行号*/
#define XMLNM_PABYBH_REQ_COBANKNAME            "/pabybh/req/cobankname"           /*合作行名称*/
#define XMLNM_PABYBH_REQ_TRANSORG              "/pabybh/req/transorg"             /*交易机构*/
#define XMLNM_PABYBH_REQ_TRANSOPER             "/pabybh/req/transoper"            /*交易柜员*/
#define XMLNM_PABYBH_REQ_AUTHORG               "/pabybh/req/authorg"              /*授权机构*/
#define XMLNM_PABYBH_REQ_AUTHOPER              "/pabybh/req/authoper"             /*授权柜员*/
#define XMLNM_PABYBH_REQ_CNLTYPE               "/pabybh/req/cnltype"              /*渠道类型*/
#define XMLNM_PABYBH_REQ_TERMEQUINO            "/pabybh/req/termequino"           /*终端设备编号*/
#define XMLNM_PABYBH_REQ_TRANSCODE             "/pabybh/req/transcode"            /*交易代码*/
#define XMLNM_PABYBH_REQ_TRANSCODE1            "/pabybh/req/transcode1"           /*附加交易代码0出金1入金2开户手续费3补打工本费*/
#define XMLNM_PABYBH_REQ_TRANSNAME             "/pabybh/req/transname"            /*交易名称*/
#define XMLNM_PABYBH_REQ_CUACOUNTYPE           "/pabybh/req/cuacountype"            /*来往帐标志*/
#define XMLNM_PABYBH_REQ_CAPITALTYPE           "/pabybh/req/capitaltype"          /*资金类型,0---转出1---转入*/
#define XMLNM_PABYBH_REQ_SVRCODE               "/pabybh/req/svrcode"              /*服务代码(存管、黄金等)*/
#define XMLNM_PABYBH_REQ_CUSTNO                "/pabybh/req/custno"               /*客户号*/
#define XMLNM_PABYBH_REQ_CUSTNAME              "/pabybh/req/custname"             /*客户名称*/
#define XMLNM_PABYBH_REQ_CUSTTYPE              "/pabybh/req/custtype"             /*客户类型00-机构01-个人*/
#define XMLNM_PABYBH_REQ_ACCTNO                "/pabybh/req/acctno"               /*银行账号*/
#define XMLNM_PABYBH_REQ_ORIACCTNO             "/pabybh/req/oriacctno"               /*银行账号*/
#define XMLNM_PABYBH_REQ_ACCTNO2               "/pabybh/req/acctno2"              /*帐号2变更后的账户*/
#define XMLNM_PABYBH_REQ_STOCKCODE             "/pabybh/req/stockcode"            /*券商代码*/
#define XMLNM_PABYBH_REQ_CAPITALACCTNO         "/pabybh/req/capitalacctno"        /*资金帐号*/
#define XMLNM_PABYBH_REQ_TRANSAMT              "/pabybh/req/transamt"             /*交易金额*/
#define XMLNM_PABYBH_REQ_ORITRANSAMT           "/pabybh/req/oritransamt"             /*交易金额*/
#define XMLNM_PABYBH_REQ_AMT2                  "/pabybh/req/amt2"                 /*金额2*/
#define XMLNM_PABYBH_REQ_AMT3                  "/pabybh/req/amt3"                 /*金额3*/
#define XMLNM_PABYBH_REQ_CURR                  "/pabybh/req/curr"                 /*币种*/
#define XMLNM_PABYBH_REQ_CASHFLAG              "/pabybh/req/cashflag"             /*钞汇标识*/
#define XMLNM_PABYBH_REQ_IEPSVRCODE            "/pabybh/req/iepsvrcode"           /*行E通服务代码*/
#define XMLNM_PABYBH_REQ_IEPTRANSCODE          "/pabybh/req/ieptranscode"         /*行E通交易代码*/
#define XMLNM_PABYBH_REQ_IEPBSIDATE            "/pabybh/req/iepbsidate"           /*行E通业务日期*/
#define XMLNM_PABYBH_REQ_IEPTRADATE            "/pabybh/req/ieptradate"           /*行E通交易日期*/
#define XMLNM_PABYBH_REQ_IEPSERIALNO           "/pabybh/req/iepserialno"          /*行E通流水号*/
#define XMLNM_PABYBH_REQ_ORIIEPBSIDATE         "/pabybh/req/oriiepbsidate"        /*原行E通业务日期*/
#define XMLNM_PABYBH_REQ_ORIIEPSERIALNO        "/pabybh/req/oriiepserialno"       /*原行E通流水号*/
#define XMLNM_PABYBH_REQ_IEPRESPCODE           "/pabybh/req/ieprespcode"          /*行E通响应代码*/
#define XMLNM_PABYBH_REQ_IEPRESPMSG            "/pabybh/req/ieprespmsg"           /*行E通响应信息*/
#define XMLNM_PABYBH_REQ_HOSTBSIDATE           "/pabybh/req/hostbsidate"          /*主机账务日期*/
#define XMLNM_PABYBH_REQ_HOSTSERIALNO          "/pabybh/req/hostserialno"         /*主机流水号*/
#define XMLNM_PABYBH_REQ_HOSTTRANSCODE         "/pabybh/req/hosttranscode"        /*主机交易代码*/
#define XMLNM_PABYBH_REQ_HOSTRESPCODE          "/pabybh/req/hostrespcode"         /*主机响应代码*/
#define XMLNM_PABYBH_REQ_HOSTRESPMSG           "/pabybh/req/hostrespmsg"          /*主机响应信息*/
#define XMLNM_PABYBH_REQ_RESPCODE              "/pabybh/req/respcode"             /*响应码*/
#define XMLNM_PABYBH_REQ_RESPMSG               "/pabybh/req/respmsg"              /*响应信息*/
#define XMLNM_PABYBH_REQ_IEPSTAT               "/pabybh/req/iepstat"              /*交易状态'0成功1失败6状态未知7被冲正8被撤销9初始'*/
#define XMLNM_PABYBH_REQ_HOSTSTAT              "/pabybh/req/hoststat"             /*交易状态'0成功1失败6状态未知7被冲正8被撤销9初始'*/
#define XMLNM_PABYBH_REQ_STAT                  "/pabybh/req/stat"                 /*交易状态'0成功1失败6状态未知7被冲正8被撤销9初始'*/
#define XMLNM_PABYBH_REQ_ORISTAT               "/pabybh/req/oristat"              /*平台同步中心前原交易状态'0成功1失败6状态未知7被冲正8被撤销9初始 X原流水不存在'*/
#define XMLNM_PABYBH_REQ_CERTTYPE              "/pabybh/req/certtype"             /*证件类型*/
#define XMLNM_PABYBH_REQ_CERTNO                "/pabybh/req/certno"               /*证件号码*/
#define XMLNM_PABYBH_REQ_PHONE                 "/pabybh/req/phone"                /*联系方式*/
#define XMLNM_PABYBH_REQ_AGENTNAME             "/pabybh/req/agentname"            /*代理人客户名称*/
#define XMLNM_PABYBH_REQ_AGENTCERTY            "/pabybh/req/agentcerty"           /*代理人证件类型*/
#define XMLNM_PABYBH_REQ_AGENTCERNO            "/pabybh/req/agentcerno"           /*代理人证件号码*/
#define XMLNM_PABYBH_REQ_AGENTPHONE            "/pabybh/req/agentphone"           /*代理人联系方式*/
#define XMLNM_PABYBH_REQ_CHKFLAG               "/pabybh/req/chkflag"              /*对账标志,0-未对账1-已对平2-平安多3-核心多4-双方无记账*/
#define XMLNM_PABYBH_REQ_MEMO                  "/pabybh/req/memo"                 /*备注*/
#define XMLNM_PABYBH_REQ_EXTFLD1               "/pabybh/req/extfld1"              /*备用字段1*/
#define XMLNM_PABYBH_REQ_EXTFLD2               "/pabybh/req/extfld2"              /*备用字段2*/
#define XMLNM_PABYBH_REQ_EXTFLD3               "/pabybh/req/extfld3"              /*备用字段3*/
#define XMLNM_PABYBH_REQ_EXTFLD4               "/pabybh/req/extfld4"              /*备用字段4*/

#define XMLNM_PABYBH_REQ_OPERASTEP             "/pabybh/req/operastep"            /*操作标志0-重新对账 1-继续对账*/
#define XMLNM_PABYBH_REQ_CHECKDATE             "/pabybh/req/checkdate"            /*对账日期*/
#define XMLNM_PABYBH_REQ_FILENAME              "/pabybh/req/filename"             /*文件名称*/
#define XMLNM_PABYBH_REQ_SIGNSTATUS            "/pabybh/req/signstatus"           /*签到操作标志*/
#define XMLNM_PABYBH_REQ_CURRSTEP              "/pabybh/req/currstep"             /*当前步点*/
#define XMLNM_PABYBH_REQ_CURRSTAT              "/pabybh/req/currstat"             /*当前步点状态*/

#define XMLNM_PABYBH_RESP_OPENORG              "/pabybh/resp/openorg"             /*开户机构 ？？？？？*/


#define XMLNM_PABYBH_RESP_IEPBSIDATE            "/pabybh/resp/iepbsidate"           /*行E通交易日期*/
#define XMLNM_PABYBH_RESP_IEPSERIALNO           "/pabybh/resp/iepserialno"          /*行E通流水号*/
#define XMLNM_PABYBH_RESP_IEPRESPCODE           "/pabybh/resp/ieprespcode"          /*行E通响应代码*/
#define XMLNM_PABYBH_RESP_IEPRESPMSG            "/pabybh/resp/ieprespmsg"           /*行E通响应信息*/
#define XMLNM_PABYBH_RESP_HOSTBSIDATE           "/pabybh/resp/hostbsidate"          /*主机账务日期*/
#define XMLNM_PABYBH_RESP_HOSTSERIALNO          "/pabybh/resp/hostserialno"         /*主机流水号*/
#define XMLNM_PABYBH_RESP_HOSTTRANSCODE         "/pabybh/resp/hosttranscode"        /*主机交易代码*/
#define XMLNM_PABYBH_RESP_HOSTRESPCODE          "/pabybh/resp/hostrespcode"         /*主机响应代码*/
#define XMLNM_PABYBH_RESP_HOSTRESPMSG           "/pabybh/resp/hostrespmsg"          /*主机响应信息*/
#define XMLNM_PABYBH_RESP_RESPCODE              "/pabybh/resp/respcode"             /*响应码*/
#define XMLNM_PABYBH_RESP_RESPMSG               "/pabybh/resp/respmsg"              /*响应信息*/
/*END------------*/


/*清算机构表信息   BEGIN---*/               
#define XMLNM_PABYBH_ORGCFG_COBANKNO       "/pabybh/orgcfg/cobankno"       /*合作行号【平安分配】*/          
#define XMLNM_PABYBH_ORGCFG_COBANKNAME     "/pabybh/orgcfg/cobankname"     /*合作行名称*/                    
#define XMLNM_PABYBH_ORGCFG_CUSTMANAGERNO  "/pabybh/orgcfg/custmanagerno"  /*平安虚拟客户经理号【平安分配】*/
#define XMLNM_PABYBH_ORGCFG_ACCT1          "/pabybh/orgcfg/acct1"          /*头寸账户*/                      
#define XMLNM_PABYBH_ORGCFG_ACCT1NAME      "/pabybh/orgcfg/acct1name"      /*头寸账户名称*/                  
#define XMLNM_PABYBH_ORGCFG_ACCT2          "/pabybh/orgcfg/acct2"          /*内部清算账户*/                  
#define XMLNM_PABYBH_ORGCFG_ACCT2NAME      "/pabybh/orgcfg/acct2name"      /*内部清算账户名称*/              
#define XMLNM_PABYBH_ORGCFG_SIGNSTATUS     "/pabybh/orgcfg/signstatus"     /*签到状态，0-签到，1-签退*/      
#define XMLNM_PABYBH_ORGCFG_AREACODE       "/pabybh/orgcfg/areacode"       /*地区代码【平安分配】*/          
#define XMLNM_PABYBH_ORGCFG_COORGNO        "/pabybh/orgcfg/coorgno"        /*合作行机构号【平安分配】*/      
#define XMLNM_PABYBH_ORGCFG_WORKDATE       "/pabybh/orgcfg/workdate"       /*业务日期*/                      
#define XMLNM_PABYBH_ORGCFG_WORKSERIALNO   "/pabybh/orgcfg/workserialno"   /*业务流水号*/                    
#define XMLNM_PABYBH_ORGCFG_MAINTAINDATE   "/pabybh/orgcfg/maintaindate"   /*维护日期*/                      
#define XMLNM_PABYBH_ORGCFG_MAINTAINTIME   "/pabybh/orgcfg/maintaintime"   /*维护时间*/                      
#define XMLNM_PABYBH_ORGCFG_EXTFLD1        "/pabybh/orgcfg/extfld1"        /*扩展1*/                         
#define XMLNM_PABYBH_ORGCFG_EXTFLD2        "/pabybh/orgcfg/extfld2"        /*扩展2*/                         
#define XMLNM_PABYBH_ORGCFG_EXTFLD3        "/pabybh/orgcfg/extfld3"        /*扩展3*/                         
#define XMLNM_PABYBH_ORGCFG_EXTFLD4        "/pabybh/orgcfg/extfld4"        /*扩展4*/                         
/*END---------*/

/*秘钥信息    BEGIN----*/
#define XMLNM_PABYBH_SECKEY_COBANKNO       "/pabybh/seckey/cobankno"       /*合作行号*/
#define XMLNM_PABYBH_SECKEY_ENCRYPTIP      "/pabybh/seckey/encryptip"      /*加密平台地址*/
#define XMLNM_PABYBH_SECKEY_ENCRYPTPORT    "/pabybh/seckey/encryptport"    /*加密平台端口*/
#define XMLNM_PABYBH_SECKEY_ENCRYPTSYSID   "/pabybh/seckey/encryptsysid"   /*加密平台系统ID*/
#define XMLNM_PABYBH_SECKEY_ENCRYPTEXTID   "/pabybh/seckey/encryptextid"   /*加密平台外部ID*/
#define XMLNM_PABYBH_SECKEY_ZMK            "/pabybh/seckey/zmk"            /*ZMK*/
#define XMLNM_PABYBH_SECKEY_ZAK            "/pabybh/seckey/zak"            /*ZAK*/
#define XMLNM_PABYBH_SECKEY_IEPZPK         "/pabybh/seckey/iepzpk"         /*ZPK平安*/
#define XMLNM_PABYBH_SECKEY_COUNTERZPK     "/pabybh/seckey/counterzpk"     /*ZPK柜面*/
#define XMLNM_PABYBH_SECKEY_HOSTZPK        "/pabybh/seckey/hostzpk"        /*ZPK核心组*/
#define XMLNM_PABYBH_SECKEY_EXTFLD1        "/pabybh/seckey/extfld1"        /*扩展1*/
#define XMLNM_PABYBH_SECKEY_EXTFLD2        "/pabybh/seckey/extfld2"        /*扩展2*/
#define XMLNM_PABYBH_SECKEY_EXTFLD3        "/pabybh/seckey/extfld3"        /*扩展3*/
#define XMLNM_PABYBH_SECKEY_EXTFLD4        "/pabybh/seckey/extfld4"        /*扩展4*/
/*END----------*/

/*签约信息    BEGIN------*/
#define XMLNM_PABYBH_SIGN_SIGNDATE          "/pabybh/sign/signdate"             /*指定日期aptDate*/
#define XMLNM_PABYBH_SIGN_SIGNTMIE          "/pabybh/sign/signtmie"             /*指定时间apt_tmie*/
#define XMLNM_PABYBH_SIGN_COBANKNO          "/pabybh/sign/cobankno"             /*合作行号*/
#define XMLNM_PABYBH_SIGN_COBANKNAME        "/pabybh/sign/cobankname"           /*合作行名称*/
#define XMLNM_PABYBH_SIGN_ACCTNO            "/pabybh/sign/acctno"               /*银行账号*/
#define XMLNM_PABYBH_SIGN_OLDACCTNO         "/pabybh/sign/oldacctno"            /*老银行账号*/
#define XMLNM_PABYBH_SIGN_CERTTYPE          "/pabybh/sign/certtype"             /*证件类型*/
#define XMLNM_PABYBH_SIGN_CERTNO            "/pabybh/sign/certno"               /*证件号码*/
#define XMLNM_PABYBH_SIGN_CUSTTYPE          "/pabybh/sign/custtype"             /*客户类型*/
#define XMLNM_PABYBH_SIGN_CUSTNAME          "/pabybh/sign/custname"             /*客户名称*/
#define XMLNM_PABYBH_SIGN_STOCKCODE         "/pabybh/sign/stockcode"            /*券商代码*/
#define XMLNM_PABYBH_SIGN_CAPITALACCTNO     "/pabybh/sign/capitalacctno"        /*证券资金台账号*/
#define XMLNM_PABYBH_SIGN_CURR              "/pabybh/sign/curr"                 /*币种*/
#define XMLNM_PABYBH_SIGN_CUSTMANAGERID     "/pabybh/sign/custmanagerid"        /*客户经理号*/
#define XMLNM_PABYBH_SIGN_CUSTMANAGERNAME   "/pabybh/sign/custmanagername"      /*客户经理名称*/
#define XMLNM_PABYBH_SIGN_OPENORG           "/pabybh/sign/openorg"              /*开户网点号*/
#define XMLNM_PABYBH_SIGN_BUSITYPE          "/pabybh/sign/busitype"             /*业务类型*/
#define XMLNM_PABYBH_SIGN_STAT              "/pabybh/sign/stat"                 /*签约状态'9-待校验1-签约2-解约'*/
#define XMLNM_PABYBH_SIGN_HOSTSTAT          "/pabybh/sign/hoststat"             /*核心签约状态'9-待校验1-签约2-解约'*/
#define XMLNM_PABYBH_SIGN_HOSTDATE          "/pabybh/sign/hostdate"             /*核心签约日期*/
#define XMLNM_PABYBH_SIGN_HOSTSERIALNO      "/pabybh/sign/hostserialno"         /*核心流水*/
#define XMLNM_PABYBH_SIGN_CHKFLAG           "/pabybh/sign/chkflag"              /*对账标志'0-未对账1-已对账'*/
#define XMLNM_PABYBH_SIGN_UPDATEDATE        "/pabybh/sign/updatedate"           /*更新日期*/
#define XMLNM_PABYBH_SIGN_UPDATETIME        "/pabybh/sign/updatetime"           /*更新时间*/
#define XMLNM_PABYBH_SIGN_TRANSORG          "/pabybh/sign/transorg"             /*交易机构*/
#define XMLNM_PABYBH_SIGN_TRANSOPER         "/pabybh/sign/transoper"            /*交易柜员*/
#define XMLNM_PABYBH_SIGN_AUTHORG           "/pabybh/sign/authorg"              /*授权机构*/
#define XMLNM_PABYBH_SIGN_AUTHOPER          "/pabybh/sign/authoper"             /*授权柜员*/
#define XMLNM_PABYBH_SIGN_MEMO              "/pabybh/sign/memo"                 /*备注*/
#define XMLNM_PABYBH_SIGN_EXTFLD1           "/pabybh/sign/extfld1"              /*备用字段1*/
#define XMLNM_PABYBH_SIGN_EXTFLD2           "/pabybh/sign/extfld2"              /*备用字段2*/
#define XMLNM_PABYBH_SIGN_EXTFLD3           "/pabybh/sign/extfld3"              /*备用字段3*/
#define XMLNM_PABYBH_SIGN_EXTFLD4           "/pabybh/sign/extfld4"              /*备用字段4*/
#define XMLNM_PABYBH_SIGN_EXTFLD5           "/pabybh/sign/extfld5"              /*备用字段5*/
#define XMLNM_PABYBH_SIGN_EXTFLD6           "/pabybh/sign/extfld6"              /*备用字段6*/
/*END--------------*/


/*客户信息表     BEGIN-----*/
#define XMLNM_PABYBH_CUSTINFO_CERTTYPE      "/pabybh/custinfo/certType"       /*证件类型*/
#define XMLNM_PABYBH_CUSTINFO_CERTNO        "/pabybh/custinfo/certNo"         /*证件号码*/
#define XMLNM_PABYBH_CUSTINFO_CUSTTYPE      "/pabybh/custinfo/custType"       /*客户类型*/
#define XMLNM_PABYBH_CUSTINFO_CUSTNAME      "/pabybh/custinfo/custName"       /*客户名称*/
#define XMLNM_PABYBH_CUSTINFO_POST          "/pabybh/custinfo/post"           /*邮政编码*/
#define XMLNM_PABYBH_CUSTINFO_ADDR          "/pabybh/custinfo/addr"           /*联系地址*/
#define XMLNM_PABYBH_CUSTINFO_EMAIL         "/pabybh/custinfo/email"          /*电子邮件地址*/
#define XMLNM_PABYBH_CUSTINFO_PHONE         "/pabybh/custinfo/phone"          /*联系电话*/
#define XMLNM_PABYBH_CUSTINFO_MOBILE        "/pabybh/custinfo/mobile"         /*移动电话*/
#define XMLNM_PABYBH_CUSTINFO_FAX           "/pabybh/custinfo/fax"            /*传真*/
#define XMLNM_PABYBH_CUSTINFO_UPDATEDATE    "/pabybh/custinfo/updateDate"     /*更新日期*/
#define XMLNM_PABYBH_CUSTINFO_UPDATETIME    "/pabybh/custinfo/updateTime"     /*更新时间*/
#define XMLNM_PABYBH_CUSTINFO_CREATEDATE    "/pabybh/custinfo/createDate"     /*创建日期*/
#define XMLNM_PABYBH_CUSTINFO_CREATETIME    "/pabybh/custinfo/createTime"     /*创建时间*/
#define XMLNM_PABYBH_CUSTINFO_EXTFLD1       "/pabybh/custinfo/extfld1"        /*备用字段1*/
#define XMLNM_PABYBH_CUSTINFO_EXTFLD2       "/pabybh/custinfo/extfld2"        /*备用字段2*/
#define XMLNM_PABYBH_CUSTINFO_EXTFLD3       "/pabybh/custinfo/extfld3"        /*备用字段3*/
/*END--------------*/

/*服务信息      BEGIN-----*/
#define XMLNM_PABYBH_SVFINFO_SVRCODE       "/pabybh/svrinfo/svrcode"         /*服务代码	*/
#define XMLNM_PABYBH_SVFINFO_SVRNAME       "/pabybh/svrinfo/svrname"         /*服务名称*/
#define XMLNM_PABYBH_SVFINFO_WORKTIME      "/pabybh/svrinfo/worktime"        /*业务开展时间段*/
#define XMLNM_PABYBH_SVFINFO_SVRSTATUS     "/pabybh/svrinfo/svrstatus"       /*服务状态*/
#define XMLNM_PABYBH_SVFINFO_EXTFLD1       "/pabybh/svrinfo/extfld1"         /*备用字段1*/
#define XMLNM_PABYBH_SVFINFO_EXTFLD2       "/pabybh/svrinfo/extfld2"         /*备用字段2*/
#define XMLNM_PABYBH_SVFINFO_EXTFLD3       "/pabybh/svrinfo/extfld3"         /*备用字段3*/
/*END-------------*/                                                         

/*中心交易控制信息    BEGIN------*/
#define XMLNM_PABYBH_PABTRANSCTL_TRANSCODE     "/pabybh/pabtransctl/transcode"     /*交易代码*/
#define XMLNM_PABYBH_PABTRANSCTL_TRANSNAME     "/pabybh/pabtransctl/transname"     /*交易名称*/
#define XMLNM_PABYBH_PABTRANSCTL_SVRCODE       "/pabybh/pabtransctl/svrcode"       /*服务代码*/
#define XMLNM_PABYBH_PABTRANSCTL_OPENFLAG      "/pabybh/pabtransctl/openflag"      /*开关标志'0--开1--关'*/
#define XMLNM_PABYBH_PABTRANSCTL_MACFLAG       "/pabybh/pabtransctl/macflag"       /*MAC校验标志'0--开1--关'*/
#define XMLNM_PABYBH_PABTRANSCTL_EXTFLD1       "/pabybh/pabtransctl/extfld1"       /*备用字段1*/
#define XMLNM_PABYBH_PABTRANSCTL_EXTFLD2       "/pabybh/pabtransctl/extfld2"       /*备用字段2*/
#define XMLNM_PABYBH_PABTRANSCTL_EXTFLD3       "/pabybh/pabtransctl/extfld3"       /*备用字段3*/
/*END------------*/

/*当日流水表     BEGIN--------*/
#define XMLNM_PABYBH_SERIAL_TRANSDATE             "/pabybh/serial/transdate"            /*平台日期*/
#define XMLNM_PABYBH_SERIAL_TRANSSERIALNO         "/pabybh/serial/transserialno"        /*平台流水号*/
#define XMLNM_PABYBH_SERIAL_ORITRANSDATE          "/pabybh/serial/oritransdate"         /*原平台日期*/
#define XMLNM_PABYBH_SERIAL_ORITRANSSERIALNO      "/pabybh/serial/oritransserialno"     /*原平台流水号*/
#define XMLNM_PABYBH_SERIAL_TRANSTIME             "/pabybh/serial/transtime"            /*交易时间*/
#define XMLNM_PABYBH_SERIAL_WORKDATE              "/pabybh/serial/workdate"             /*业务日期*/
#define XMLNM_PABYBH_SERIAL_WORKSERIALNO          "/pabybh/serial/workserialno"         /*业务流水号*/
#define XMLNM_PABYBH_SERIAL_REQDATE               "/pabybh/serial/reqdate"              /*发起方日期*/
#define XMLNM_PABYBH_SERIAL_REQSERIALNO           "/pabybh/serial/reqserialno"          /*发起方流水号*/
#define XMLNM_PABYBH_SERIAL_CLUSTERNODENAME       "/pabybh/serial/clusternodename"      /*集群节点机器名称*/
#define XMLNM_PABYBH_SERIAL_CLUSTERNODEIP         "/pabybh/serial/clusternodeip"        /*集群节点机器IP*/
#define XMLNM_PABYBH_SERIAL_COBANKNO              "/pabybh/serial/cobankno"             /*合作行号*/
#define XMLNM_PABYBH_SERIAL_TRANSORG              "/pabybh/serial/transorg"             /*交易机构*/
#define XMLNM_PABYBH_SERIAL_TRANSOPER             "/pabybh/serial/transoper"            /*交易柜员*/
#define XMLNM_PABYBH_SERIAL_AUTHORG               "/pabybh/serial/authorg"              /*授权机构*/
#define XMLNM_PABYBH_SERIAL_AUTHOPER              "/pabybh/serial/authoper"             /*授权柜员*/
#define XMLNM_PABYBH_SERIAL_CNLTYPE               "/pabybh/serial/cnltype"              /*渠道类型*/
#define XMLNM_PABYBH_SERIAL_TERMEQUINO            "/pabybh/serial/termequino"           /*终端设备编号*/
#define XMLNM_PABYBH_SERIAL_TRANSCODE             "/pabybh/serial/transcode"            /*交易代码*/
#define XMLNM_PABYBH_SERIAL_TRANSCODE1            "/pabybh/serial/transcode1"           /*附加交易代码0出金1入金2开户手续费3补打工本费*/
#define XMLNM_PABYBH_SERIAL_TRANSNAME             "/pabybh/serial/transname"            /*交易名称*/
#define XMLNM_PABYBH_SERIAL_CUACOUNTYPE           "/pabybh/serial/cuacountype"            /*来往帐标志*/
#define XMLNM_PABYBH_SERIAL_CAPITALTYPE           "/pabybh/serial/capitaltype"          /*资金类型,0---转出1---转入*/
#define XMLNM_PABYBH_SERIAL_SVRCODE               "/pabybh/serial/svrcode"              /*服务代码(存管、黄金等)*/
#define XMLNM_PABYBH_SERIAL_CUSTNAME              "/pabybh/serial/custname"             /*客户名称*/
#define XMLNM_PABYBH_SERIAL_CUSTTYPE              "/pabybh/serial/custtype"             /*客户类型00-机构01-个人*/
#define XMLNM_PABYBH_SERIAL_ACCTNO                "/pabybh/serial/acctno"               /*银行账号*/
#define XMLNM_PABYBH_SERIAL_ORIACCTNO             "/pabybh/serial/oriacctno"               /*银行账号*/
#define XMLNM_PABYBH_SERIAL_ACCTNO2               "/pabybh/serial/acctno2"              /*帐号2变更后的账户*/
#define XMLNM_PABYBH_SERIAL_STOCKCODE             "/pabybh/serial/stockcode"          /*券商代码*/
#define XMLNM_PABYBH_SERIAL_CAPITALACCTNO         "/pabybh/serial/capitalacctno"        /*资金帐号*/
#define XMLNM_PABYBH_SERIAL_TRANSAMT              "/pabybh/serial/transamt"             /*交易金额*/
#define XMLNM_PABYBH_SERIAL_ORITRANSAMT           "/pabybh/serial/oritransamt"             /*交易金额*/
#define XMLNM_PABYBH_SERIAL_AMT2                  "/pabybh/serial/amt2"                 /*金额2*/
#define XMLNM_PABYBH_SERIAL_AMT3                  "/pabybh/serial/amt3"                 /*金额3*/
#define XMLNM_PABYBH_SERIAL_CURR                  "/pabybh/serial/curr"                 /*币种*/
#define XMLNM_PABYBH_SERIAL_CASHFLAG              "/pabybh/serial/cashflag"             /*钞汇标识*/
#define XMLNM_PABYBH_SERIAL_IEPSVRCODE            "/pabybh/serial/iepsvrcode"           /*行E通服务代码*/
#define XMLNM_PABYBH_SERIAL_IEPTRANSCODE          "/pabybh/serial/ieptranscode"         /*行E通交易代码*/
#define XMLNM_PABYBH_SERIAL_IEPBSIDATE            "/pabybh/serial/iepbsidate"           /*行E通业务日期*/
#define XMLNM_PABYBH_SERIAL_IEPTRADATE            "/pabybh/serial/ieptradate"           /*行E通交易日期*/
#define XMLNM_PABYBH_SERIAL_IEPSERIALNO           "/pabybh/serial/iepserialno"          /*行E通流水号*/
#define XMLNM_PABYBH_SERIAL_ORIIEPBSIDATE         "/pabybh/serial/oriiepbsidate"        /*原行E通业务日期*/
#define XMLNM_PABYBH_SERIAL_ORIIEPSERIALNO        "/pabybh/serial/oriiepserialno"       /*原行E通流水号*/
#define XMLNM_PABYBH_SERIAL_IEPRESPCODE           "/pabybh/serial/ieprespcode"          /*行E通响应代码*/
#define XMLNM_PABYBH_SERIAL_IEPRESPMSG            "/pabybh/serial/ieprespmsg"           /*行E通响应信息*/
#define XMLNM_PABYBH_SERIAL_HOSTBSIDATE           "/pabybh/serial/hostbsidate"          /*主机账务日期*/
#define XMLNM_PABYBH_SERIAL_HOSTSERIALNO          "/pabybh/serial/hostserialno"         /*主机流水号*/
#define XMLNM_PABYBH_SERIAL_HOSTTRANSCODE         "/pabybh/serial/hosttranscode"        /*主机交易代码*/
#define XMLNM_PABYBH_SERIAL_HOSTRESPCODE          "/pabybh/serial/hostrespcode"         /*主机响应代码*/
#define XMLNM_PABYBH_SERIAL_HOSTRESPMSG           "/pabybh/serial/hostrespmsg"          /*主机响应信息*/
#define XMLNM_PABYBH_SERIAL_RESPCODE              "/pabybh/serial/respcode"             /*响应码*/
#define XMLNM_PABYBH_SERIAL_RESPMSG               "/pabybh/serial/respmsg"              /*响应信息*/
#define XMLNM_PABYBH_SERIAL_IEPSTAT               "/pabybh/serial/iepstat"              /*中心交易状态'0成功1失败6状态未知7被冲正8被撤销9初始'*/
#define XMLNM_PABYBH_SERIAL_HOSTSTAT              "/pabybh/serial/hoststat"             /*核心交易状态'0成功1失败6状态未知7被冲正8被撤销9初始'*/
#define XMLNM_PABYBH_SERIAL_STAT                  "/pabybh/serial/stat"                 /*交易状态'0成功1失败6状态未知7被冲正8被撤销9初始'*/
#define XMLNM_PABYBH_SERIAL_ORISTAT               "/pabybh/serial/oristat"              /*平台同步中心前原交易状态'0成功1失败6状态未知7被冲正8被撤销9初始'*/
#define XMLNM_PABYBH_SERIAL_CERTTYPE              "/pabybh/serial/certtype"             /*证件类型*/
#define XMLNM_PABYBH_SERIAL_CERTNO                "/pabybh/serial/certno"               /*证件号码*/
#define XMLNM_PABYBH_SERIAL_PHONE                 "/pabybh/serial/phone"                /*联系方式*/
#define XMLNM_PABYBH_SERIAL_AGENTNAME             "/pabybh/serial/agentname"            /*代理人客户名称*/
#define XMLNM_PABYBH_SERIAL_AGENTCERTY            "/pabybh/serial/agentcerty"           /*代理人证件类型*/
#define XMLNM_PABYBH_SERIAL_AGENTCERNO            "/pabybh/serial/agentcerno"           /*代理人证件号码*/
#define XMLNM_PABYBH_SERIAL_AGENTPHONE            "/pabybh/serial/agentphone"           /*代理人联系方式*/
#define XMLNM_PABYBH_SERIAL_CHKFLAG               "/pabybh/serial/chkflag"              /*对账标志,0-未对账1-已对平2-平安多3-核心多4-双方无记账*/
#define XMLNM_PABYBH_SERIAL_MEMO                  "/pabybh/serial/memo"                 /*备注*/
#define XMLNM_PABYBH_SERIAL_EXTFLD1               "/pabybh/serial/extfld1"              /*备用字段1*/
#define XMLNM_PABYBH_SERIAL_EXTFLD2               "/pabybh/serial/extfld2"              /*备用字段2*/
#define XMLNM_PABYBH_SERIAL_EXTFLD3               "/pabybh/serial/extfld3"              /*备用字段3*/
#define XMLNM_PABYBH_SERIAL_EXTFLD4               "/pabybh/serial/extfld4"              /*备用字段4*/
/*END--------------*/

/*对账状态信息      BEGIN------*/
#define XMLNM_PABYBH_CHECKCTL_CHTRANSDATE                "/pabybh/checkctl/chtransdate"                /*对账发起日期*/
#define XMLNM_PABYBH_CHECKCTL_CHTRANSNO                  "/pabybh/checkctl/chtransno"                  /*对账发起流水号*/
#define XMLNM_PABYBH_CHECKCTL_CHECKDATE                  "/pabybh/checkctl/checkdate"                  /*对账日期*/
#define XMLNM_PABYBH_CHECKCTL_COBANKNO                   "/pabybh/checkctl/cobankno"                   /*合作行号*/
#define XMLNM_PABYBH_CHECKCTL_SVRCODE                    "/pabybh/checkctl/svrcode"                    /*服务码业务类型*/
#define XMLNM_PABYBH_CHECKCTL_MSGTYPE                    "/pabybh/checkctl/msgtype"                    /*对账类型0资金类1账户类（正常）2账户类（解约&销户）*/
#define XMLNM_PABYBH_CHECKCTL_TOTALCOUNT                 "/pabybh/checkctl/totalcount"                 /*总笔数*/
#define XMLNM_PABYBH_CHECKCTL_TOTALAMT                   "/pabybh/checkctl/totalamt"                   /*总金额*/
#define XMLNM_PABYBH_CHECKCTL_INTOTCNT                 "/pabybh/checkctl/intotcnt"                 /*转入总笔数*/
#define XMLNM_PABYBH_CHECKCTL_INTOTAMT                   "/pabybh/checkctl/intotamt"                   /*转入总金额*/
#define XMLNM_PABYBH_CHECKCTL_OUTTOTCNT                 "/pabybh/checkctl/outtotcnt"                 /*转出总笔数*/
#define XMLNM_PABYBH_CHECKCTL_OUTTOTAMT                   "/pabybh/checkctl/outtotamt"                   /*转出总金额*/
#define XMLNM_PABYBH_CHECKCTL_BACKTOTALCOUNT             "/pabybh/checkctl/backtotalcount"             /*冲正总笔数*/
#define XMLNM_PABYBH_CHECKCTL_BACKTOTALAMT               "/pabybh/checkctl/backtotalamt"               /*冲正总金额*/
#define XMLNM_PABYBH_CHECKCTL_LOCALTOTALCOUNT            "/pabybh/checkctl/localtotalcount"            /*平台总笔数*/
#define XMLNM_PABYBH_CHECKCTL_LOCALTOTALAMT              "/pabybh/checkctl/localtotalamt"              /*平台总金额*/
#define XMLNM_PABYBH_CHECKCTL_LOCALBACKTOTALCOUNT        "/pabybh/checkctl/localbacktotalcount"        /*平台冲正总笔数*/
#define XMLNM_PABYBH_CHECKCTL_LOCALBACKTOTALAMT          "/pabybh/checkctl/localbacktotalamt"          /*平台冲正总金额*/
#define XMLNM_PABYBH_CHECKCTL_HOSTTOTALCOUNT             "/pabybh/checkctl/hosttotalcount"             /*核心总笔数*/
#define XMLNM_PABYBH_CHECKCTL_HOSTTOTALAMT               "/pabybh/checkctl/hosttotalamt"               /*核心总金额*/
#define XMLNM_PABYBH_CHECKCTL_HOSTBACKTOTALCOUNT         "/pabybh/checkctl/hostbacktotalcount"         /*核心冲正总笔数*/
#define XMLNM_PABYBH_CHECKCTL_HOSTBACKTOTALAMT           "/pabybh/checkctl/hostbacktotalamt"           /*核心冲正总金额*/
#define XMLNM_PABYBH_CHECKCTL_NETAMT                     "/pabybh/checkctl/netamt"                     /*轧差金额*/
#define XMLNM_PABYBH_CHECKCTL_NETTYPE                    "/pabybh/checkctl/nettype"                    /*轧差方向'0收入1支出'*/
#define XMLNM_PABYBH_CHECKCTL_IEPCHKFILE                 "/pabybh/checkctl/iepchkfile"                 /*平安对账文件名*/
#define XMLNM_PABYBH_CHECKCTL_HOSTCHKFILE                "/pabybh/checkctl/hostchkfile"                /*主机对账文件名*/
#define XMLNM_PABYBH_CHECKCTL_EXECTIME                   "/pabybh/checkctl/exectime"                   /*执行时间'开始时间|结束时间|'*/
#define XMLNM_PABYBH_CHECKCTL_EXECSTEP                   "/pabybh/checkctl/execstep"                   /*执行步点'0-获取平安对账信息1-平安对账文件入库2-平安明细对账完成3-请求提交主机4-获取主机对账文件,主机生成对账文件入库5-主机明细对账完成'*/
#define XMLNM_PABYBH_CHECKCTL_EXECSTAT                   "/pabybh/checkctl/execstat"                   /*执行状态'1-成功2-失败9-处理中'*/
#define XMLNM_PABYBH_CHECKCTL_CHKDETAILRESULT            "/pabybh/checkctl/chkdetailresult"            /*明细对账结果'0未对账1对账平2对账不平3对账出错9对账中'*/
#define XMLNM_PABYBH_CHECKCTL_CHKPABTOTALRESULT          "/pabybh/checkctl/chkpabtotalresult"          /*中心对总账结果'0未对账1对账平2对账不平3对账出错9对账中'*/
#define XMLNM_PABYBH_CHECKCTL_CHKHOSTTOTALRESULT         "/pabybh/checkctl/chkhosttotalresult"         /*核心对总账结果'0未对账1对账平2对账不平3对账出错9对账中'*/
#define XMLNM_PABYBH_CHECKCTL_TRANSDATE                  "/pabybh/checkctl/transdate"                  /*交易日期*/
#define XMLNM_PABYBH_CHECKCTL_TRANSSERIALNO              "/pabybh/checkctl/transserialno"              /*前置流水号*/
#define XMLNM_PABYBH_CHECKCTL_SETTLEDATE                 "/pabybh/checkctl/settledate"                 /*清算日期*/
#define XMLNM_PABYBH_CHECKCTL_SETTLESERNO                "/pabybh/checkctl/settleserno"                /*清算流水号*/
#define XMLNM_PABYBH_CHECKCTL_HOSTDATE                   "/pabybh/checkctl/hostdate"                   /*核心日期*/
#define XMLNM_PABYBH_CHECKCTL_HOSTSERIALNO               "/pabybh/checkctl/hostserialno"               /*核心流水号*/
#define XMLNM_PABYBH_CHECKCTL_TRANSORG                   "/pabybh/checkctl/transorg"                   /*交易机构*/
#define XMLNM_PABYBH_CHECKCTL_TRANSOPER                  "/pabybh/checkctl/transoper"                  /*交易柜员*/
#define XMLNM_PABYBH_CHECKCTL_RESPCODE                   "/pabybh/checkctl/respcode"                   /*响应码*/
#define XMLNM_PABYBH_CHECKCTL_RESPMSG                    "/pabybh/checkctl/respmsg"                    /*响应信息*/
#define XMLNM_PABYBH_CHECKCTL_STAT                       "/pabybh/checkctl/stat"                       /*交易状态0成功1失败6状态未知7被冲正8被撤销9初始*/
#define XMLNM_PABYBH_CHECKCTL_EXTFLD1                    "/pabybh/checkctl/extfld1"                    /*备用字段1*/
#define XMLNM_PABYBH_CHECKCTL_EXTFLD2                    "/pabybh/checkctl/extfld2"                    /*备用字段2*/
#define XMLNM_PABYBH_CHECKCTL_EXTFLD3                    "/pabybh/checkctl/extfld3"                    /*备用字段3*/
/*END-------------*/

/*存管资金对账明细    BEGIN-------*/
#define XMLNM_PABYBH_DEPCHKINFO_CHECKDATE         "/pabybh/depchkinfo/checkdate"          /*对账日期*/
#define XMLNM_PABYBH_DEPCHKINFO_TRANSDATE         "/pabybh/depchkinfo/transdate"          /*交易日期*/
#define XMLNM_PABYBH_DEPCHKINFO_TRANSTIME         "/pabybh/depchkinfo/transtime"          /*交易时间*/
#define XMLNM_PABYBH_DEPCHKINFO_TRANSFERTYPE      "/pabybh/depchkinfo/transfertype"       /*资金类型'0--银转证1--证转银'*/
#define XMLNM_PABYBH_DEPCHKINFO_ACCTNO            "/pabybh/depchkinfo/acctno"             /*银行账号*/
#define XMLNM_PABYBH_DEPCHKINFO_STOCKCODE         "/pabybh/depchkinfo/stockcode"          /*券商代码*/
#define XMLNM_PABYBH_DEPCHKINFO_CAPITALACCTNO     "/pabybh/depchkinfo/capitalacctno"      /*证券资金台账号*/
#define XMLNM_PABYBH_DEPCHKINFO_AMT               "/pabybh/depchkinfo/amt"                /*金额*/
#define XMLNM_PABYBH_DEPCHKINFO_WORKSERIALNO      "/pabybh/depchkinfo/workserialno"       /*合作行流水号*/
#define XMLNM_PABYBH_DEPCHKINFO_IEPSERIALNO       "/pabybh/depchkinfo/iepserialno"        /*行E通流水号*/
#define XMLNM_PABYBH_DEPCHKINFO_COBANKNO          "/pabybh/depchkinfo/cobankno"           /*合作行号*/
#define XMLNM_PABYBH_DEPCHKINFO_EXTFLD1           "/pabybh/depchkinfo/extfld1"            /*备用字段1*/
#define XMLNM_PABYBH_DEPCHKINFO_EXTFLD2           "/pabybh/depchkinfo/extfld2"            /*备用字段2*/
/*END----------*/

/*资金对账不平明细    BEGIN-------*/
#define XMLNM_PABYBH_NOTBAL_CHECKDATE           "/pabybh/notbal/checkdate"               /*对账日期*/
#define XMLNM_PABYBH_NOTBAL_COBANKNO            "/pabybh/notbal/cobankno"                /*合作行号*/
#define XMLNM_PABYBH_NOTBAL_TRANSFERTYPE        "/pabybh/notbal/transfertype"            /*资金类型'0--出金，银转证1--证转银，入金'*/
#define XMLNM_PABYBH_NOTBAL_STOCKCODE           "/pabybh/notbal/stockcode"               /*券商代码*/
#define XMLNM_PABYBH_NOTBAL_CAPITALACCTNO       "/pabybh/notbal/capitalacctno"           /*证券资金台账号*/
#define XMLNM_PABYBH_NOTBAL_WORKSERIALNO        "/pabybh/notbal/workserialno"            /*合作行流水号*/
#define XMLNM_PABYBH_NOTBAL_BANKSTAT            "/pabybh/notbal/bankstat"                /*合作行状态*/
#define XMLNM_PABYBH_NOTBAL_BANKACCTNO          "/pabybh/notbal/bankacctno"              /*平台银行账号*/
#define XMLNM_PABYBH_NOTBAL_BANKAMT             "/pabybh/notbal/bankamt"                 /*平台交易金额*/
#define XMLNM_PABYBH_NOTBAL_BANKTRANSCODE				"/pabybh/notbal/banktranscode"           /*平台交易代码*/
#define XMLNM_PABYBH_NOTBAL_IEPSERIALNO         "/pabybh/notbal/iepserialno"             /*行E通流水号*/
#define XMLNM_PABYBH_NOTBAL_IEPSTAT             "/pabybh/notbal/iepstat"                 /*行E通状态*/
#define XMLNM_PABYBH_NOTBAL_IEPACCTNO           "/pabybh/notbal/iepacctno"               /*行E通银行账号*/
#define XMLNM_PABYBH_NOTBAL_IEPAMT              "/pabybh/notbal/iepamt"                  /*行E通交易金额*/
#define XMLNM_PABYBH_NOTBAL_IEPTRANSCODE				"/pabybh/notbal/ieptranscode"            /*行E通交易代码*/
#define XMLNM_PABYBH_NOTBAL_HOSTSERIALNO        "/pabybh/notbal/hostserialno"            /*主机流水号*/
#define XMLNM_PABYBH_NOTBAL_HOSTSTAT            "/pabybh/notbal/hoststat"                /*主机状态*/
#define XMLNM_PABYBH_NOTBAL_HOSTACCTNO          "/pabybh/notbal/hostacctno"              /*主机银行账号*/
#define XMLNM_PABYBH_NOTBAL_HOSTAMT             "/pabybh/notbal/hostamt"                 /*主机交易金额*/
#define XMLNM_PABYBH_NOTBAL_HOSTTRANSCODE				"/pabybh/notbal/hosttranscode"           /*主机交易代码*/
#define XMLNM_PABYBH_NOTBAL_CHECKSTAT           "/pabybh/notbal/checkstat"               /*对账结果标志,0-未对账1-已对平2-平安多3-核心多*/
#define XMLNM_PABYBH_NOTBAL_ADJUSTSTAT          "/pabybh/notbal/adjuststat"              /*调账状态0-成功1-失败7-超时9-初始*/
#define XMLNM_PABYBH_NOTBAL_ADJUSTTRANSORG      "/pabybh/notbal/adjusttransorg"          /*调账交易机构*/
#define XMLNM_PABYBH_NOTBAL_ADJUSTTRANSOPER     "/pabybh/notbal/adjusttransoper"         /*调账交易柜员*/
#define XMLNM_PABYBH_NOTBAL_ADJUSTDATE          "/pabybh/notbal/adjustdate"              /*调账日期*/
#define XMLNM_PABYBH_NOTBAL_ADJUSTSERIALNO      "/pabybh/notbal/adjustserialno"          /*调账业务流水号*/
#define XMLNM_PABYBH_NOTBAL_ADJUSTHOSTBSIDATE   "/pabybh/notbal/adjusthostbsidate"       /*主机账务日期*/
#define XMLNM_PABYBH_NOTBAL_ADJUSTHOSTSERIALNO  "/pabybh/notbal/adjusthostserialno"      /*主机流水号*/
#define XMLNM_PABYBH_NOTBAL_ADJUSTRESPCODE      "/pabybh/notbal/adjustrespcode"          /*调账响应码*/
#define XMLNM_PABYBH_NOTBAL_ADJUSTRESPMSG       "/pabybh/notbal/adjustrespmsg"           /*调账响应信息*/
#define XMLNM_PABYBH_NOTBAL_EXTFLD1             "/pabybh/notbal/extfld1"                 /*备用字段1*/
#define XMLNM_PABYBH_NOTBAL_EXTFLD2             "/pabybh/notbal/extfld2"                 /*备用字段2*/
/*END----------*/

/*主机对账明细    BEGIN-------*/
#define XMLNM_PABYBH_HOSCHKINFO_COBANKNO             "/pabybh/hoschkinfo/cobankno"                /*合作行号*/                            
#define XMLNM_PABYBH_HOSCHKINFO_CHECKDATE            "/pabybh/hoschkinfo/checkdate"               /*对账日期*/                            
#define XMLNM_PABYBH_HOSCHKINFO_WORKSERIALNO         "/pabybh/hoschkinfo/workserialno"            /*平台业务流水号*/                      
#define XMLNM_PABYBH_HOSCHKINFO_HOSTDATE             "/pabybh/hoschkinfo/hostdate"                /*主机日期*/                            
#define XMLNM_PABYBH_HOSCHKINFO_HOSTSERIALNO         "/pabybh/hoschkinfo/hostserialno"            /*主机流水号*/                          
#define XMLNM_PABYBH_HOSCHKINFO_HOSTTRANSCODE        "/pabybh/hoschkinfo/hosttranscode"           /*核心交易代码*/                        
#define XMLNM_PABYBH_HOSCHKINFO_ACCTNO               "/pabybh/hoschkinfo/acctno"                  /*账号*/                                
#define XMLNM_PABYBH_HOSCHKINFO_TRANSAMT             "/pabybh/hoschkinfo/transamt"                /*交易金额*/                            
#define XMLNM_PABYBH_HOSCHKINFO_TRANSFARE            "/pabybh/hoschkinfo/transfare"               /*手续费*/                              
#define XMLNM_PABYBH_HOSCHKINFO_CASHFLAG             "/pabybh/hoschkinfo/cashflag"                /*现转标志1-现金2-转账*/                
#define XMLNM_PABYBH_HOSCHKINFO_STAT                 "/pabybh/hoschkinfo/stat"                    /*有效标志0-正常1-被冲正2-被撤销9-失败*/
#define XMLNM_PABYBH_HOSCHKINFO_CDFLAG               "/pabybh/hoschkinfo/cdflag"                  /*借贷标志*/                            
#define XMLNM_PABYBH_HOSCHKINFO_SVRTYPE              "/pabybh/hoschkinfo/svrtype"                 /*业务种类*/                            
#define XMLNM_PABYBH_HOSCHKINFO_REMARKCODE           "/pabybh/hoschkinfo/remarkcode"              /*摘要码*/                              
#define XMLNM_PABYBH_HOSCHKINFO_REMARK               "/pabybh/hoschkinfo/remark"                  /*摘要信息*/                            
#define XMLNM_PABYBH_HOSCHKINFO_TRANSBRANCHNO        "/pabybh/hoschkinfo/transbranchno"           /*交易网点*/                            
#define XMLNM_PABYBH_HOSCHKINFO_TRANSORG             "/pabybh/hoschkinfo/transorg"                /*交易机构*/                            
#define XMLNM_PABYBH_HOSCHKINFO_TRANSOPER            "/pabybh/hoschkinfo/transoper"               /*交易柜员*/                            
#define XMLNM_PABYBH_HOSCHKINFO_JOINCHKFLAG          "/pabybh/hoschkinfo/joinchkflag"             /*参与对账标志，0-不参与，1-参与*/      
#define XMLNM_PABYBH_HOSCHKINFO_EXTFLD1              "/pabybh/hoschkinfo/extfld1"                 /*备用字段1*/                           
#define XMLNM_PABYBH_HOSCHKINFO_EXTFLD2              "/pabybh/hoschkinfo/extfld2"                 /*备用字段2*/                           
#define XMLNM_PABYBH_HOSCHKINFO_EXTFLD3              "/pabybh/hoschkinfo/extfld3"                 /*备用字段3*/                           
/*END----------*/

/*交易信息    */
#define XMLNM_APP_JYXX_JYDM          "/app/jyxx/jydm"              /*交易代码*/
#define XMLNM_APP_JYXX_JYMC          "/app/jyxx/jymc"              /*交易名称*/
#define XMLNM_APP_JYXX_JYLX          "/app/jyxx/jylx"              /*交易类型 0正交易 1反交易 9其它*/
#define XMLNM_APP_JYXX_LSJLBZ        "/app/jyxx/lsjlbz"            /*流水记录标志 0记录 1不记录*/
#define XMLNM_APP_JYXX_RZBZ          "/app/jyxx/rzbz"              /*入账标志 0入账 1非入账*/
#define XMLNM_APP_JYXX_BBBZ          "/app/jyxx/bbbz"              /*报表标志 0报表 1非报表*/
#define XMLNM_APP_JYXX_WHJG          "/app/jyxx/whjg"              /*维护机构*/
#define XMLNM_APP_JYXX_WHGY          "/app/jyxx/whgy"              /*维护柜员*/
#define XMLNM_APP_JYXX_WHSJ          "/app/jyxx/whsj"              /*维护时间*/
#define XMLNM_APP_JYXX_JYXE          "/app/jyxx/jyxe"              /*交易限额*/
#define XMLNM_APP_JYXX_XEFS          "/app/jyxx/xefs"              /*限额方式*/
#define XMLNM_APP_JYXX_EXTFLD1       "/app/jyxx/extfld1"           /*扩展字段1*/
#define XMLNM_APP_JYXX_EXTFLD2       "/app/jyxx/extfld2"           /*扩展字段2*/
#define XMLNM_APP_JYXX_QTBZ          "/app/jyxx/qtbz"              /*启停标志 0启动 1关闭*/
/*END-----------*/

/*参数定义   */
#define XMLNM_PABYBH_PARACTL_FILESPLIT     "/pabybh/paractl/filesplit"    /*文件分隔符*/
#define XMLNM_PABYBH_PARACTL_FILELINEFLAG  "/pabybh/paractl/filelineflag" /*文件首尾行标志*/   

#define XMLNM_PABYBH_PARACTL_SETTLEFUND    "/pabybh/paractl/settlefund"   /*联动清算资金  0不联动 1联动*/
#define XMLNM_PABYBH_PARACTL_HOSTSIGN      "/pabybh/paractl/hostsign"     /*核心签约登记 0不签约 1签约登记*/
#define XMLNM_PABYBH_PARACTL_HOSTCHE       "/pabybh/paractl/hostche"      /*联动主机对账 0不联动 1联动*/
#define XMLNM_PABYBH_PARACTL_GETHOSTFILE   "/pabybh/paractl/gethostfile"  /*联动获取主机对账文件 0不联动 1联动*/

#define XMLNM_PABYBH_PARACTL_FILEPATH      "/pabybh/paractl/filepath"     /*平安银百合文件目录*/
#define XMLNM_PABYBH_PARACTL_PABCOMM       "/pabybh/paractl/pabcomm"      /*中心通讯方式：1通过GXP 2直连中心*/

                                                                     
#define XMLNM_PABYBH_PARACTL_PABCHEFP      "/pabybh/paractl/pabchefp"    /*中心对账文件路径*/
#define XMLNM_PABYBH_PARACTL_HOSTCHEFP      "/pabybh/paractl/hostchefp"   /*核心对账文件路径*/

#define XMLNM_PABYBH_PARACTL_PABPARAFP   "/pabybh/paractl/pabparafp"  /*中心参数文件路径*/
#define XMLNM_PABYBH_PARACTL_LOCPARAFP    "/pabybh/paractl/locparafp"  /*本地参数文件路径*/





/*报文定义    */
/*平安请求报文  /iep/req  /iep/resp*/

/*核心报文  */

/*请求平安报文  /pabfe/req   /pabfe/resp*/

#endif
