drop table PABYBH_ORGCFG;
create table PABYBH_ORGCFG
(                
    coBankNo          VARCHAR(12) not null,            --合作行号【平安分配】                      
    coBankName        VARCHAR(100) ,           --合作行名称                     
    custManagerNo    VARCHAR(10) not null,             --平安虚拟客户经理号【平安分配】    
    acct1             VARCHAR(32),            --头寸账户
    acct1Name         VARCHAR(60),            --头寸账户名称
    acct2             VARCHAR(32),            --内部清算账户
    acct2Name         VARCHAR(60),            --内部清算账户名称 
    signStatus        VARCHAR(1) not null,             --签到状态，0-签到，1-签退
    areaCode          VARCHAR(20),            --地区代码【平安分配】
    coOrgNo           VARCHAR(20),            --合作行机构号【平安分配】
    workDate          VARCHAR(8) not null,             --业务日期
    workSerialNo        VARCHAR(32) ,          --业务流水号
    maintainDate      VARCHAR(8),                      --维护日期                       
    maintainTime      VARCHAR(6),                      --维护时间                       
    extFld1           VARCHAR(64),                     --扩展1
    extFld2           VARCHAR(64),                     --扩展2
    extFld3           VARCHAR(255) ,                    --扩展3
    extFld4           VARCHAR(255)                     --扩展4
);

alter table PABYBH_ORGCFG add constraint PK_PABYBH_ORGCFG primary key (coBankNo);