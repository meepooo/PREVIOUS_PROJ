-------------------------------------------------------------------------------- 
--  表空间名：  "TBS_PAYY_DAT_32K"
--
----------------------------------------

-- 表名: PABYBH_ORGCFG
-- 描述: 机构配置表
-------------------------------------------------------------------------------- 
drop table PABYBH_ORGCFG;
create table PABYBH_ORGCFG
(
    bankOrgNo         VARCHAR(12) not null,            --法人机构号                     
    bankOrgName       VARCHAR(120),                    --法人机构号名称                 
    coBankNo          VARCHAR(12) not null,            --合作行号【平安分配】                      
    coBankName        VARCHAR(100) not null,           --合作行名称                     
    custManagerNo    VARCHAR(10) not null,             --平安虚拟客户经理号【平安分配】    
    acct1             VARCHAR(32) not null,            --头寸账户
    acct1Name         VARCHAR(60) not null,            --头寸账户名称
    acct2             VARCHAR(32) not null,            --内部清算账户
    acct2Name         VARCHAR(60) not null,            --内部清算账户名称 
    signStatus        VARCHAR(1) not null,             --签到状态，0-签到，1-签退
    areaCode          VARCHAR(20) not null,            --地区代码【平安分配】
    coOrgNo           VARCHAR(20) not null,            --合作行机构号【平安分配】
    workDate          VARCHAR(8) not null,             --业务日期
    workSerialNo        VARCHAR(32) not null,          --业务流水号
    maintainDate      VARCHAR(8),                      --维护日期                       
    maintainTime      VARCHAR(6),                      --维护时间                       
    extFld1           VARCHAR(64),                     --扩展1
    extFld2           VARCHAR(64),                     --扩展2
    extFld3           VARCHAR(255) ,                    --扩展3
    extFld4           VARCHAR(255)                     --扩展4
);

alter table PABYBH_ORGCFG add constraint PK_PABYBH_ORGCFG primary key (coBankNo);

create unique index K_PABYBH_ORGCFG_1 on PABYBH_ORGCFG 
(
bankOrgNo
);


--新增秘钥信息表
drop table PABYBH_SECKEY;
create table PABYBH_SECKEY
(
    coBankNo         VARCHAR(12) not null,               --合作行号  
    encryptIp           VARCHAR(32) not null,            --加密平台地址           
    encryptPort        VARCHAR(32) not null,            --加密平台端口
    encryptSysId      VARCHAR(32) not null,            --加密平台系统ID
    encryptExtId       VARCHAR(32) not null,            --加密平台外部ID
    zmk              	   VARCHAR(255),                      --ZMK
    zak               	   VARCHAR(255) not null,             --ZAK
    iepZpk                 VARCHAR(255) not null,           --ZPK 平安
    counterZpk          VARCHAR(255) not null,       --ZPK 柜面
    hostZpk               VARCHAR(255) not null,          --ZPK 核心组
    extFld1           VARCHAR(64),                       --扩展1
    extFld2           VARCHAR(64),                       --扩展2
    extFld3           VARCHAR(255),                     --扩展3
    extFld4           VARCHAR(255)                       --扩展4
);                                                       

 
-------------------------------------------------------------------------------- 
-- 表名: PABYBH_DLCG_APPOINT
-- 描述: 三方存管预指定关系表 
-------------------------------------------------------------------------------- 
drop table PABYBH_SIGN;
create table PABYBH_SIGN
(
    signDate        VARCHAR(8) not null,                    --指定日期  aptDate     
    signTime        VARCHAR(6),                             --指定时间  apt_tmie
    coBankNo        VARCHAR(12) not null,                   --合作行号                       
    coBankName      VARCHAR(100),                           --合作行名称           
    acctNo          VARCHAR(32) not null,                   --银行账号 
    oldAcctNo          VARCHAR(32) not null,                --老银行账号     
    certType        VARCHAR(2) not null,                    --证件类型      
    certNo          VARCHAR(32) not null,                   --证件号码  
    custType          VARCHAR(2),                           --客户类型      
    custName          VARCHAR(120),                         --客户名称      
    stockCode       VARCHAR(8) not null,                    --券商代码      
    capitalAcctNo   VARCHAR(30) not null,                   --证券资金台账号 
    svrCode       			VARCHAR(6) not null,											--服务代码
   	curr             VARCHAR(3), 														--币种
--   	openfare        VARCHAR(10),                          --开户手续费
--    areaCode        VARCHAR(20),                          --地区代码 
--    gradeid         VARCHAR(1),                           --客户级别 
    custManagerId   VARCHAR(20),                            --客户经理号
    custManagerName  VARCHAR(20),                           --客户经理名称
    openOrg          VARCHAR(10),                           --开户网点号 
   	busiType			   VARCHAR(1),														--业务类型 
--   	trantype        VARCHAR(2),                           --交易选项 1新开卡签约  2-持黄金卡签约     
    stat            VARCHAR(1),                             --签约状态'9-待校验1-签约2-解约'  
    hostStat        VARCHAR(1),                             --核心签约状态'9-待校验1-签约2-解约'  
    hostDate        VARCHAR(8),                                --核心签约日期
    hostSerialNo    VARCHAR(20),                            --核心流水   
    chkFlag          VARCHAR(1),                            --对账标志'0-未对账1-已对账'      
    updateDate      VARCHAR(8),                             --更新日期      
    updateTime      VARCHAR(6),                             --更新时间      
    transOrg         VARCHAR(10),                           --交易机构      
    transOper        VARCHAR(20),                           --交易柜员 
    authOrg         VARCHAR(10),                            --授权机构 
    authOper           VARCHAR(20),                         --授权柜员       
    memo             VARCHAR(40),                           --备注          
    extFld1          VARCHAR(32),                           --备用字段1   
    extFld2          VARCHAR(32),                           --备用字段2   
    extFld3          VARCHAR(64),                           --备用字段3  
    extFld4          VARCHAR(64),                           --备用字段4 
    extFld5          VARCHAR(64),                           --备用字段5  
    extFld6          VARCHAR(64)                         --备用字段6 
   -- CONSTRAINT PK_PABYBH_SIGN PRIMARY KEY (stockCode, capitalAcctNo, svrCode)
);
alter table PABYBH_SIGN add constraint PK_PABYBH_SIGN primary key (stockCode, capitalAcctNo, svrCode);
-----------------------
--客户信息表 PABYBH_CUSTINFO
-----------------------
drop table PABYBH_CUSTINFO;
create table PABYBH_CUSTINFO
(
		certType        VARCHAR(2) not null,                   --证件类型     
    certNo          VARCHAR(32) not null,                  --证件号码      
    custType        VARCHAR(2),                            --客户类型      
    custName        VARCHAR(120),                          --客户名称 
 		post          VARCHAR(6),                              --邮政编码      
    addr          VARCHAR(128),                            --联系地址      
    email         VARCHAR(120),                            --电子邮件地址  
    phone         VARCHAR(16),                             --联系电话      
    mobile        VARCHAR(11),                             --移动电话      
    fax           VARCHAR(16),                             --传真          
    updateDate   VARCHAR(8),                               --更新日期      
    updateTime   VARCHAR(6),                               --更新时间   
    createDate   VARCHAR(8)	,													     --创建日期
		createTime   VARCHAR(6)	,															 --创建时间
		extFld1       VARCHAR(32),                             --备用字段1   
    extFld2       VARCHAR(64),                             --备用字段2   
    extFld3       VARCHAR(64)                            --备用字段3  
		 --CONSTRAINT PK_PABYBH_CUSTINFO PRIMARY KEY (certType, certNo)
);
 alter table PABYBH_CUSTINFO add constraint PK_PABYBH_CUSTINFO primary key (certType, certNo);
-------------------------------------------------------------------------------- 
-- 表名: PABYBH_SVRINFO
-- 描述:  业务信息
-------------------------------------------------------------------------------- 
drop table PABYBH_SVRINFO;
create table PABYBH_SVRINFO
(
  svrCode      VARCHAR(6) not null,                     --服务代码	            
  svrName      VARCHAR(100) not null,                   --服务名称             
--  workDate     VARCHAR(10) not null,                    --工作日期              
  workTime     VARCHAR(32),                             --业务开展时间段        
  svrStatus    VARCHAR(1) not null,                     --服务状态              
  extFld1      VARCHAR(128),                            --备用字段1             
  extFld2      VARCHAR(128),                            --备用字段2                          
  extFld3      VARCHAR(128)                             --备用字段3
);
 
alter table PABYBH_SVRINFO add constraint PK_PABYBH_SVRINFO primary key (svrCode);
 
-------------------------------------------------------------------------------- 
-- 表名: PABYBHTransCTL
-- 描述: 中心交易控制表
-------------------------------------------------------------------------------- 
drop table PABYBH_PABTRANSCTL;
create table PABYBH_PABTRANSCTL
(
  transCode VARCHAR(10) not null,                       --交易代码   
  transName VARCHAR(100) not null,                      --交易名称   
  svrCode   VARCHAR(6) not null,                        --服务代码   
  openFlag  VARCHAR(1) not null,                        --开关标志'0--开1--关'  
  macFlag   VARCHAR(1) not null,                        --MAC校验标志'0--开1--关'
  extFld1   VARCHAR(32),                                --备用字段1  
  extFld2   VARCHAR(32),                                --备用字段2  
  extFld3   VARCHAR(32)                                 --备用字段3  
);

alter table PABYBH_PABTRANSCTL add constraint PK_PABYBH_PABTRANSCTL primary key (transCode, svrCode);
 
-------------------------------------------------------------------------------- 
-- 表名: PABYBHSerial
-- 描述: 交易流水表
-------------------------------------------------------------------------------- 
drop table PABYBH_SERIAL;
create table PABYBH_SERIAL
(
    transDate           VARCHAR(8) not null,        --平台日期      
    transSerialNo        VARCHAR(20) not null,      --平台流水号
    oritransDate           VARCHAR(8) ,             --原平台日期      
    oriTransSerialNo       VARCHAR(20) ,            --原平台流水号
    transTime           VARCHAR(8) not null,        --交易时间
    workDate            VARCHAR(8),                 --业务日期
    workSerialNo        VARCHAR(20),                --业务流水号
    reqDate             VARCHAR(8) not null,        --发起方日期
    reqSerialNo          VARCHAR(20) not null,      --发起方流水号
    clusterNodeName     VARCHAR(30),                --集群节点机器名称
    clusterNodeIp       VARCHAR(20),                --集群节点机器IP 
    coBankNo            VARCHAR(12) not null,       --合作行号                       
    coBankName          VARCHAR(100),               --合作行名称 
    transOrg            VARCHAR(10),                --交易机构      
    transOper           VARCHAR(10),                --交易柜员
    authOrg            VARCHAR(10),                 --授权机构      
    authOper           VARCHAR(10),                 --授权柜员
    cnlType             VARCHAR(5),                 --渠道类型 
    termEquiNo          VARCHAR(20),                --终端设备编号
    transCode           VARCHAR(12),                --交易代码 
    transCode1           VARCHAR(1),                      --附加交易代码 0 出金 1 入金 2开户手续费 3 补打工本费
    cuAcounType          VARCHAR(1),                       --来往账标志 0-往账 1-来账
    transName           VARCHAR(100),               --交易名称   
    capitalType        VARCHAR(1),                  --资金类型,0 ---转出1--- 转入    
    svrCode             VARCHAR(10),                --服务代码   (存管、黄金等)
    custNo              VARCHAR(20),                --客户号
    custName           VARCHAR(80),                 --客户名称
    custType            VARCHAR(2),                 --客户类型 
    acctNo             VARCHAR(32),                 --银行账号         
    acctNo2             VARCHAR(32),                --帐号2   变更后的账户  
    capitalAcctNo       VARCHAR(32),                --资金帐号    
    transAmt             DECIMAL(16,2),                --交易金额      
    amt2                 DECIMAL(16,2),                --金额2         
    amt3                DECIMAL(16,2),                --金额3 
    curr                VARCHAR(3),                 --币种
    cashFlag            VARCHAR(1),                 --钞汇标识 
    iepSvrCode         VARCHAR(8),                  --行E通服务代码 
    iepTransCode       VARCHAR(16),                 --行E通交易代码 
    iepBsiDate         VARCHAR(8),                  --行E通业务日期
    iepTraDate         VARCHAR(8),                  --行E通交易日期 
    iepSerialNo        VARCHAR(32),                 --行E通流水号   区别？
    oriIepBsiDate     VARCHAR(8),                   --原行E通业务日期
    oriIepSerialNo    VARCHAR(32),                  --原行E通流水号         
    iepRespCode        VARCHAR(12),                 --行E通响应代码 
    iepRespMsg         VARCHAR(120),                --行E通响应信息            
    hostBsiDate        VARCHAR(8),                  --主机账务日期  
    hostSerialNo       VARCHAR(32),                 --主机流水号   
    hostTransCode      VARCHAR(16),                 --主机交易代码     
    hostRespCode       VARCHAR(12),                 --主机响应代码  
    hostRespMsg        VARCHAR(120),                --主机响应信息  
    respCode            VARCHAR(10),                --响应码        
    respMsg             VARCHAR(120),               --响应信息     
    iepStat                VARCHAR(1),              --中心交易状态'0成功 1失败 6状态未知 7被冲正 8被撤销 9初始'      
    hostStat                VARCHAR(1),             --核心交易状态'0成功 1失败 6状态未知 7被冲正 8被撤销 9初始'      
    stat                VARCHAR(1),                 --交易状态'0成功 1失败 6状态未知 7被冲正 8被撤销 9初始'   原始->0-成功，00-成功；第一位表示核心，第二位表示第3方；0--成功2--失败8--未发送此渠道9--初始'          
    oriStat             VARCHAR(1),                       --平台同步中心状态前原状态 '0成功 1失败 6状态未知 7被冲正 8被撤销 9初始'
    certType            VARCHAR(2),                 --证件类型    
    certNo              VARCHAR(32),                --证件号码
    chkFlag             VARCHAR(1),                 --对账标志,0-未对账1-已对平2-平安多3-核心多4-双方无记账 
    memo                  VARCHAR(128),             --备注
    extFld1             VARCHAR(32),                --备用字段1     
    extFld2             VARCHAR(64),                --备用字段2     
    extFld3             VARCHAR(128)                --备用字段3     
);

alter table PABYBH_SERIAL add constraint PK_PABYBH_SERIAL primary key (transDate, transSerialNo);

create unique index K_PABYBH_SERIAL_1 on PABYBH_SERIAL 
(
iepSerialNo
);
create unique index K_PABYBH_SERIAL_2 on PABYBH_SERIAL 
(
reqDate,reqSerialNo
);
-------------------------------------------------------------------------------- 
-- 表名: PABYBH_BBSJ
-- 描述: 报表数据 【暂不需要】
-------------------------------------------------------------------------------- 
DROP TABLE PABYBH_BBSJ;
CREATE TABLE PABYBH_BBSJ                                                                               
(                                                                                                     
    transDate       VARCHAR (8)  NOT NULL,      --交易日期                                            
    transOrg        VARCHAR (10) NOT NULL,      --交易机构                                             
    transOrgNAME    VARCHAR(256) NOT NULL,      --交易机构名称      
    DLHJKH          VARCHAR (17),               --代理黄金开户                                         
    DLHJXH          VARCHAR (17),               --代理黄金销户                                         
    DLHJCL          VARCHAR (17),               --代理黄金存量                                         
    DLCGKH          VARCHAR (17),               --代理存管开户                                         
    DLCGXH          VARCHAR (17),               --代理存管销户                                         
    DLCGCL          VARCHAR (17),               --代理存管存量                                         
    DLHJZRBS        INTEGER,               --代理黄金转入笔数                                     
    DLHJZRJE         DECIMAL(16,2) ,               --代理黄金转入金额                                     
    DLHJZCBS        INTEGER,               --代理黄金转出笔数                                     
    DLHJZCJE         DECIMAL(16,2),               --代理黄金转出金额                                     
    DLCGZRBS       INTEGER,               --代理存管转入笔数                                     
    DLCGZRJE         DECIMAL(16,2),               --代理存管转入金额                                     
    DLCGZCBS       INTEGER,               --代理存管转出笔数                                     
    DLCGZCJE        DECIMAL(16,2)             --代理存管转出金额                                     
	--CONSTRAINT PK_PABYBH_BBSJ PRIMARY KEY (transDate, transOrg)                                       
);                                                                                                                                            
                                                                 
alter table PABYBH_BBSJ add constraint PK_PABYBH_BBSJ primary key (transDate, transOrg);

 
--create index idx_PABYBH_DLHJ_ZHBG_1 ON PABYBH_BBSJ(CLRQ, acctNo, stat);

-------------------------------------------------------------------------------- 
-- 表名: PABYBH_CHECKCTL
-- 描述: 对账控制表
-------------------------------------------------------------------------------- 
DROP TABLE PABYBH_CHECKCTL;
create table PABYBH_CHECKCTL
(
    chTransDate             VARCHAR(8),                    --对账初始发起日期      
    chTransNo               VARCHAR(20),                   --对账初始发起流水号    
    checkDate              VARCHAR(8) not null,            --对账日期   
    coBankNo               VARCHAR(12) not null,           --合作行号
    svrCode                VARCHAR(6) not null,            --服务码 业务类型 
    msgType                VARCHAR(50) not null,           --对账类型0资金类1账户类（正常）2账户类（解约&销户）
    totalCount             INTEGER,                        --总笔数
    totalAmt               DECIMAL(16,2),                   --总金额
    backTotalCount         INTEGER,                        --冲正总笔数
    backTotalAmt           DECIMAL(16,2),                   --冲正总金额
    localTotalCount         INTEGER,                       --平台总笔数
    localTotalAmt           DECIMAL(16,2),                  --平台总金额
    localBackTotalCount         INTEGER,                   --平台冲正总笔数
    localBackTotalAmt           DECIMAL(16,2),              --平台冲正总金额
    hostTotalCount         INTEGER,                        --主机总笔数
    hostTotalAmt           DECIMAL(16,2),                   --主机总金额
    hostBackTotalCount         INTEGER,                    --主机冲正总笔数
    hostBackTotalAmt           DECIMAL(16,2),               --主机冲正总金额
    netAmt                DECIMAL(16,2),                    --轧差金额
    netType               VARCHAR(1),                            --轧差方向  '0收入 1支出'
    iepChkFile            VARCHAR(100),                    --平安对账文件名
    hostChkFile           VARCHAR(100),                    --主机对账文件名
    execTime               VARCHAR(30),                    --执行时间'开始时间|结束时间|'
    execStep               VARCHAR(2),                     --执行步点'0-获取平安对账信息 1-平安对账文件入库 2-平安明细对账完成 3-请求提交主机 4-获取主机对账文件,主机生成对账文件入库 5-主机明细对账完成'
    execStat               VARCHAR(1),                     --执行状态'1-成功 2-失败9-处理中'
    chkDetailResult           VARCHAR(1),                --明细对账结果'0 未对账 1 对账平 2对账不平 3对账出错 9 对账中'
    chkPabtotalResult           VARCHAR(1),              --中心对总账结果'0 未对账 1 对账平 2对账不平 3对账出错 9 对账中'
    chkHosttotalResult           VARCHAR(1),             --核心对总账结果'0 未对账 1 对账平 2对账不平 3对账出错 9 对账中'
    transDate             VARCHAR(8),                      --交易日期
    transSerialNo         VARCHAR(20),                     --前置流水号
    transOrg              VARCHAR(10),                     --交易机构      
    transOper             VARCHAR(10),                     --交易柜员
    respCode              VARCHAR(10),                     --响应码        
    respMsg               VARCHAR(120),                    --响应信息
    stat                  VARCHAR(1),                      --交易状态 0成功 1失败 6状态未知 7被冲正 8被撤销 9初始
    extFld1               VARCHAR(32),                     --备用字段1
    extFld2               VARCHAR(64),                     --备用字段2
    extFld3               VARCHAR(128)                   --备用字段3
   -- CONSTRAINT PK_PABYBH_CHECKCTL PRIMARY KEY (checkDate, coBankNo,svrCode,msgType)    
);

alter table PABYBH_CHECKCTL add constraint PK_PABYBH_CHECKCTL primary key (checkDate, coBankNo,svrCode,msgType);
-- 表名: PABYBH_DLCG_CHKINFO
-- 描述: 平安银行存管对账明细表 
-------------------------------------------------------------------------------- 
DROP TABLE PABYBH_DEPCHKINFO;
create table PABYBH_DEPCHKINFO
(
    checkDate           VARCHAR(8) not null,                --对账日期
    transDate           VARCHAR(8) not null,                --交易日期 
    transTime           VARCHAR(6),                         --交易时间      
    transferType        VARCHAR(1),                         --资金类型'0--银转证1--证转银'      
    acctNo              VARCHAR(32),                        --银行账号      
    stockCode           VARCHAR(8) not null,                --券商代码      
    capitalAcctNo       VARCHAR(30) not null,               --证券资金台账号
    amt                 DECIMAL(16,2),                        --金额          
    workSerialNo      VARCHAR(30),                          --合作行流水号  
    iepSerialNo       VARCHAR(30) not null,                 --行E通流水号   
    coBankNo            VARCHAR(12) not null,               --合作行号
    extFld1             VARCHAR(32),                        --备用字段1     
    extFld2             VARCHAR(64)                       --备用字段2    
   -- CONSTRAINT PK_PABYBH_DEPCHKINFO PRIMARY KEY (checkDate, iepSerialNo)  
);
 alter table PABYBH_DEPCHKINFO add constraint PK_PABYBH_DEPCHKINFO primary key (checkDate, iepSerialNo);
create index IDX_PABYBH_DEPCHKINFO_1 on PABYBH_DEPCHKINFO (checkDate, workSerialNo, coBankNo);


-------------------------------------------------------------------------------- 
-- 表名: PABYBH_DLCG_CHKBPINFO
-- 描述: 存管对账不平明细表
-------------------------------------------------------------------------------- 
DROP TABLE PABYBH_DLCG_CHKBPINFO;
create table PABYBH_DLCG_CHKBPINFO
(
    checkDate             VARCHAR(8) not null,                --对账日期  
    coBankNo              VARCHAR(12) not null,               --合作行号   
    transferType          VARCHAR(1),                         --资金类型'0--出金，银转证1--证转银，入金'      
    stockCode             VARCHAR(8),                         --券商代码       
    capitalAcctNo          VARCHAR(30),                       --证券资金台账号        
    workSerialNo          VARCHAR(30),                        --合作行流水号  
    bankStat              VARCHAR(1),                               --合作行状态
    bankAcctNo            VARCHAR(32),                        --平台银行账号 
    bankAmt               DECIMAL(16,2),                       --平台交易金额
    bankTranscode		VARCHAR(8),  								      --平台交易代码
    iepSerialNo           VARCHAR(30),                        --行E通流水号
    iepStat               VARCHAR(1),                               --行E通状态
    iepAcctNo              VARCHAR(32),                       --行E通银行账号 
    iepAmt                DECIMAL(16,2),                       --行E通交易金额 
    iepTranscode					 VARCHAR(8),  								      --行E通交易代码  
    hostSerialNo           VARCHAR(30),                       --主机流水号
    hostStat                VARCHAR(1),                             --主机状态    
    hostAcctNo               VARCHAR(32),                     --主机银行账号
    hostAmt                DECIMAL(16,2),                      --主机交易金额
    hostTranscode					 VARCHAR(8),  								      --主机交易代码  
    checkStat                VARCHAR(1),                      --对账结果标志,0-未对账1-已对平2-平安多3-核心多  
    stDesc                  VARCHAR(120),                     --对账结果描述      
    adjustStat               VARCHAR(1),                           --调账状态 0-成功 1-失败 7-超时 9-初始    
    adjustTransOrg            VARCHAR(10),                    --调账交易机构      
    adjustTransOper           VARCHAR(10),                    --调账交易柜员
    adjustDate                VARCHAR(8),                     --调账日期
    adjustSerialno            VARCHAR(32),                    --调账业务流水号
    adjustHostBsidate        VARCHAR(8),                      --主机账务日期  
    adjustHostSerialno       VARCHAR(32),                     --主机流水号
    adjustRespCode            VARCHAR(10),                    --调账响应码
    adjustRespMsg             VARCHAR(120),                   --调账响应信息
    extFld1                   VARCHAR(32),                    --备用字段1     
    extFld2                   VARCHAR(64)                     --备用字段2   
--   CONSTRAINT PK_PABYBH_DLCG_CHKBPINFO PRIMARY KEY (transDate, bankSerialNo)    
);
 
-- alter table PABYBH_DLCG_CHKBPINFO add constraint PK_PABYBH_DLCG_CHKBPINFO primary key (checkDate, );
-------------------------------------------------------------------------------- 
-- 表名: PABYBHHostCHKINFO
-- 描述:  主机对账信息  
-------------------------------------------------------------------------------- 
DROP TABLE PABYBH_HOSCHKINFO;
create table PABYBH_HOSCHKINFO
(
    coBankNo            VARCHAR(10),                            --合作行号
    checkDate             VARCHAR(8),                           --对账日期
    workSerialNo              VARCHAR(32)  not null,            --平台业务流水号
    hostDate            VARCHAR(8) not null,                    --主机日期
    hostSerialNo             VARCHAR(32) not null,              --主机流水号
    hostTransCode       VARCHAR(16),                            --核心交易代码  
    acctNo              VARCHAR(32),                            --账号
    transAmt             DECIMAL(16,2),                            --交易金额
    transfare           DECIMAL(16,2),                           --手续费
    cashFlag            VARCHAR(1),                             --现转标志1-现金 2-转账
    stat                VARCHAR(1),                             --交易状态0-正常 7-被冲正 8-被撤销 1-失败    
    cdFlag              VARCHAR(1),                             --借贷标志   
    svrType          VARCHAR(10),                               --业务种类
    remarkcode          VARCHAR(32),                            --摘要码
    remark              VARCHAR(50),                            --摘要信息
    transBranchNo       VARCHAR(10),                            --交易网点
    transOrg          VARCHAR(10),                              --交易机构
    transOper         VARCHAR(10),                              --交易柜员
    joinChkFlag             VARCHAR(1),                         --参与对账标志，0-不参与，1-参与
    extFld1             VARCHAR(32),                            --备用字段1     
    extFld2             VARCHAR(64),                            --备用字段2     
    extFld3             VARCHAR(64)                           --备用字段3  
   -- CONSTRAINT PK_PABYBH_HOSCHKINFO PRIMARY KEY (hostdate, hostSerialNo)   
);
 alter table PABYBH_HOSCHKINFO add constraint PK_PABYBH_HOSCHKINFO primary key (hostdate, hostSerialNo);
create index IDX_PABYBH_HOSCHKINFO_1 on PABYBH_HOSCHKINFO (coBankNo, checkDate);

create index IDX_PABYBH_HOSCHKINFO_2 on PABYBH_HOSCHKINFO (coBankNo, checkDate, workSerialNo);


COMMIT WORK;

--CONNECT RESET;

--TERMINATE;


