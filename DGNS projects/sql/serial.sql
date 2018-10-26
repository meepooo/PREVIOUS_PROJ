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
    workDate            VARCHAR(8) not null,        --业务日期
    workSerialNo        VARCHAR(20) not null,       --业务流水号
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
    stockCode             VARCHAR(8),                         --券商代码 
    capitalType        VARCHAR(1),                  --资金类型,0 ---转出1--- 转入    
    svrCode             VARCHAR(10),                --服务代码   (存管、黄金等)
    custNo              VARCHAR(20),                --客户号
    custName           VARCHAR(80),                 --客户名称
    custType            VARCHAR(2),                 --客户类型 
    acctNo             VARCHAR(32),                 --银行账号         
    oriAcctNo             VARCHAR(32),                 --银行账号
    acctNo2             VARCHAR(32),                --帐号2   变更后的账户  
    capitalAcctNo       VARCHAR(32),                --资金帐号    
    transAmt             DECIMAL(16,2),                --交易金额      
    oriTransAmt             DECIMAL(16,2),                --交易金额
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
