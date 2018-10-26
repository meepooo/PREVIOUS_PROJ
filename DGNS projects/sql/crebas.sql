--==============================================================
-- DBMS name:      IBM DB2 UDB 8.x Common Server
-- Created on:     2015/7/21 14:13:54
--==============================================================


drop table TBL_JZZF_BGACCCODE;

drop table TBL_JZZF_BGDEPTCODE;

drop table TBL_JZZF_BGORGCODE;

drop table TBL_JZZF_BILLNO;

drop table TBL_JZZF_CARDBIN;

drop table TBL_JZZF_EDHZ;

drop table TBL_JZZF_EDMX;

drop table TBL_JZZF_OUTLAYCODE;

drop table TBL_JZZF_PROJECTCLASSCODE;

drop table TBL_JZZF_PROJECTCODE;

--==============================================================
-- Table: TBL_JZZF_BGACCCODE
--==============================================================
create table TBL_JZZF_BGACCCODE
(
   CZBM                 CHAR(10)               not null,
   CZRQ                 CHAR(10),
   FINANO               CHAR(25),
   CZY                  CHAR(60),
   BGACCCODE            CHAR(8)                not null,
   BGACCSORTCODE        CHAR(2),
   BGACCKINDCODE        CHAR(8),
   BGACCITEMCODE        CHAR(100),
   BGCODE               CHAR(32),
   BGACCNAME            CHAR(100),
   REMARK               CHAR(125),
   STAT                 CHAR(1),
   BY1                  CHAR(1),
   BY2                  CHAR(10),
   constraint "P_Key_1" primary key (CZBM, BGACCCODE)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table TBL_JZZF_BGACCCODE is
'预算单位信息表';

comment on column TBL_JZZF_BGACCCODE.CZBM is
'财政编码';

comment on column TBL_JZZF_BGACCCODE.CZRQ is
'操作日期';

comment on column TBL_JZZF_BGACCCODE.FINANO is
'财政流水号';

comment on column TBL_JZZF_BGACCCODE.CZY is
'操作员';

comment on column TBL_JZZF_BGACCCODE.BGACCCODE is
'预算科目代码';

comment on column TBL_JZZF_BGACCCODE.BGACCSORTCODE is
'预算科目代码';

comment on column TBL_JZZF_BGACCCODE.BGACCKINDCODE is
'预算科目款编码';

comment on column TBL_JZZF_BGACCCODE.BGACCITEMCODE is
'预算科目项编码';

comment on column TBL_JZZF_BGACCCODE.BGCODE is
'预算科目标准码';

comment on column TBL_JZZF_BGACCCODE.BGACCNAME is
'预算单位名称';

comment on column TBL_JZZF_BGACCCODE.REMARK is
'备注';

comment on column TBL_JZZF_BGACCCODE.STAT is
'启用标志';

comment on column TBL_JZZF_BGACCCODE.BY1 is
'备用1';

comment on column TBL_JZZF_BGACCCODE.BY2 is
'备用2';

--==============================================================
-- Table: TBL_JZZF_BGDEPTCODE
--==============================================================
create table TBL_JZZF_BGDEPTCODE
(
   CZBM                 CHAR(10)               not null,
   CZRQ                 CHAR(10),
   FINANO               CHAR(25),
   CZY                  CHAR(20),
   BGDEPTCODE           CHAR(8)                not null,
   CHARGEBGDEPTCODE     CHAR(8),
   BGCODELEVEL          CHAR(2),
   BGCODE               CHAR(8),
   BGDEPTNAME           CHAR(100),
   BANKACCOUNT          CHAR(32),
   ADDRESS              CHAR(100),
   TELEPHONE            CHAR(20),
   REMARK               CHAR(125),
   STAT                 CHAR(1),
   BY1                  CHAR(1),
   BY2                  CHAR(10),
   constraint "P_Key_1" primary key (CZBM, BGDEPTCODE)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table TBL_JZZF_BGDEPTCODE is
'预算单位信息表';

comment on column TBL_JZZF_BGDEPTCODE.CZBM is
'财政编码';

comment on column TBL_JZZF_BGDEPTCODE.CZRQ is
'操作日期';

comment on column TBL_JZZF_BGDEPTCODE.FINANO is
'财政流水号';

comment on column TBL_JZZF_BGDEPTCODE.CZY is
'操作员';

comment on column TBL_JZZF_BGDEPTCODE.BGDEPTCODE is
'预算单位代码';

comment on column TBL_JZZF_BGDEPTCODE.CHARGEBGDEPTCODE is
'主管单位代码';

comment on column TBL_JZZF_BGDEPTCODE.BGCODELEVEL is
'预算单位级别';

comment on column TBL_JZZF_BGDEPTCODE.BGCODE is
'国标码';

comment on column TBL_JZZF_BGDEPTCODE.BGDEPTNAME is
'预算单位名称';

comment on column TBL_JZZF_BGDEPTCODE.BANKACCOUNT is
'预算单位零余额账号';

comment on column TBL_JZZF_BGDEPTCODE.ADDRESS is
'预算单位地址';

comment on column TBL_JZZF_BGDEPTCODE.TELEPHONE is
'联系电话';

comment on column TBL_JZZF_BGDEPTCODE.REMARK is
'备注';

comment on column TBL_JZZF_BGDEPTCODE.STAT is
'启用标志';

comment on column TBL_JZZF_BGDEPTCODE.BY1 is
'备用1';

comment on column TBL_JZZF_BGDEPTCODE.BY2 is
'备用2';

--==============================================================
-- Table: TBL_JZZF_BGORGCODE
--==============================================================
create table TBL_JZZF_BGORGCODE
(
   CZBM                 CHAR(10)               not null,
   CZRQ                 CHAR(10),
   FINANO               CHAR(25),
   CZY                  CHAR(60),
   BGORGCODE            CHAR(8)                not null,
   BGORGNAME            CHAR(125),
   REMARK               CHAR(125),
   STAT                 CHAR(1),
   BY1                  CHAR(1),
   BY2                  CHAR(10),
   constraint "P_Key_1" primary key (CZBM, BGORGCODE)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table TBL_JZZF_BGORGCODE is
'业务处室表';

comment on column TBL_JZZF_BGORGCODE.CZBM is
'财政编码';

comment on column TBL_JZZF_BGORGCODE.CZRQ is
'操作日期';

comment on column TBL_JZZF_BGORGCODE.FINANO is
'财政流水号';

comment on column TBL_JZZF_BGORGCODE.CZY is
'操作员';

comment on column TBL_JZZF_BGORGCODE.BGORGCODE is
'业务处室代码';

comment on column TBL_JZZF_BGORGCODE.BGORGNAME is
'业务处室名称';

comment on column TBL_JZZF_BGORGCODE.REMARK is
'备注';

comment on column TBL_JZZF_BGORGCODE.STAT is
'启用标志';

comment on column TBL_JZZF_BGORGCODE.BY1 is
'备用1';

comment on column TBL_JZZF_BGORGCODE.BY2 is
'备用2';

--==============================================================
-- Table: TBL_JZZF_BILLNO
--==============================================================
create table TBL_JZZF_BILLNO
(
   CZBM                 CHAR(10)               not null,
   CZRQ                 CHAR(10),
   FINANO               CHAR(25),
   CZY                  CHAR(60),
   BILLNO               CHAR(20)               not null,
   BGORGCODE            CHAR(125),
   BGDEPTCODE           CHAR(10),
   PROCDATE             CHAR(8),
   CAPTORGION           CHAR(4),
   FISCAL               CHAR(25),
   FISPERD              CHAR(20),
   PAYMENTTYPE          CHAR(125),
   BGACCCODE            CHAR(1),
   PROJECTCODE          CHAR(1),
   TYPEOFPAY            CHAR(10),
   OUTLAYCODE           CHAR(8),
   PAYUSAGE             CHAR(125),
   RECEBANKACCOUNT      CHAR(32),
   RECENAME             CHAR(125),
   RECEBANKNODENAME     CHAR(125),
   PAYBANKACCOUNT       CHAR(32),
   PAYNAME              CHAR(125),
   PAYBANKNODENAME      CHAR(125),
   PAYSUM               CHAR(20),
   REMARK               CHAR(125),
   TRANSTYPE            CHAR(2),
   OUTBANKTYPE          CHAR(1),
   OUTBANKCODE          CHAR(20),
   OUTBANKNAME          CHAR(50),
   ACTIONSTEP           CHAR(2),
   SENDFLAG             CHAR(1),
   NOTE1                CHAR(10),
   NOTE2                CHAR(10),
   NOTE3                CHAR(20),
   NOTE4                CHAR(30),
   constraint "P_Key_1" primary key (CZBM, BILLNO)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table TBL_JZZF_BILLNO is
'支付凭证登记表';

comment on column TBL_JZZF_BILLNO.CZBM is
'财政编码';

comment on column TBL_JZZF_BILLNO.CZRQ is
'操作日期';

comment on column TBL_JZZF_BILLNO.FINANO is
'财政流水号';

comment on column TBL_JZZF_BILLNO.CZY is
'操作员';

comment on column TBL_JZZF_BILLNO.BILLNO is
'单据号';

comment on column TBL_JZZF_BILLNO.BGORGCODE is
'业务科室代码';

comment on column TBL_JZZF_BILLNO.BGDEPTCODE is
'预算单位代码';

comment on column TBL_JZZF_BILLNO.PROCDATE is
'业务日期';

comment on column TBL_JZZF_BILLNO.CAPTORGION is
'资金性质';

comment on column TBL_JZZF_BILLNO.FISCAL is
'会计年度';

comment on column TBL_JZZF_BILLNO.FISPERD is
'会计期间';

comment on column TBL_JZZF_BILLNO.PAYMENTTYPE is
'支付方式';

comment on column TBL_JZZF_BILLNO.BGACCCODE is
'预算科目代码';

comment on column TBL_JZZF_BILLNO.PROJECTCODE is
'预算项目代码';

comment on column TBL_JZZF_BILLNO.TYPEOFPAY is
'支出类型';

comment on column TBL_JZZF_BILLNO.OUTLAYCODE is
'经费类型';

comment on column TBL_JZZF_BILLNO.PAYUSAGE is
'支出用途';

comment on column TBL_JZZF_BILLNO.RECEBANKACCOUNT is
'收款人账号';

comment on column TBL_JZZF_BILLNO.RECENAME is
'收款人名称';

comment on column TBL_JZZF_BILLNO.RECEBANKNODENAME is
'收款人开户行';

comment on column TBL_JZZF_BILLNO.PAYBANKACCOUNT is
'付款人账号';

comment on column TBL_JZZF_BILLNO.PAYNAME is
'付款人名称';

comment on column TBL_JZZF_BILLNO.PAYBANKNODENAME is
'付款人开户行';

comment on column TBL_JZZF_BILLNO.PAYSUM is
'支付金额';

comment on column TBL_JZZF_BILLNO.REMARK is
'备注';

comment on column TBL_JZZF_BILLNO.TRANSTYPE is
'业务类型';

comment on column TBL_JZZF_BILLNO.OUTBANKTYPE is
'行类别 1行内 2大额 3税票 4同城 5贷记卡';

comment on column TBL_JZZF_BILLNO.OUTBANKCODE is
'行代码';

comment on column TBL_JZZF_BILLNO.OUTBANKNAME is
'行名称';

comment on column TBL_JZZF_BILLNO.ACTIONSTEP is
'凭证状态';

comment on column TBL_JZZF_BILLNO.SENDFLAG is
'发送标志';

comment on column TBL_JZZF_BILLNO.NOTE1 is
'备注1';

comment on column TBL_JZZF_BILLNO.NOTE2 is
'备注2';

comment on column TBL_JZZF_BILLNO.NOTE3 is
'备注3';

comment on column TBL_JZZF_BILLNO.NOTE4 is
'备注4';

--==============================================================
-- Table: TBL_JZZF_CARDBIN
--==============================================================
create table TBL_JZZF_CARDBIN
(
   CARDBIN              CHAR(10)               not null,
   NOTE                 CHAR(60),
   BY1                  CHAR(10),
   BY2                  CHAR(20),
   constraint "P_Key_1" primary key (CARDBIN)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on column TBL_JZZF_CARDBIN.CARDBIN is
'卡BIN';

comment on column TBL_JZZF_CARDBIN.NOTE is
'备注';

comment on column TBL_JZZF_CARDBIN.BY1 is
'备用1';

comment on column TBL_JZZF_CARDBIN.BY2 is
'备用2';

--==============================================================
-- Table: TBL_JZZF_EDHZ
--==============================================================
create table TBL_JZZF_EDHZ
(
   CZBM                 CHAR(10)               not null,
   CZRQ                 CHAR(10),
   FINANO               CHAR(25),
   CZY                  CHAR(60),
   BILLNO               CHAR(20)               not null,
   BGDEPTCODE           CHAR(125),
   PROCDATE             CHAR(10),
   CAPTORGION           CHAR(8),
   FISCAL               CHAR(4),
   FISPERD              CHAR(25),
   TOTALSUM             CHAR(20),
   REMARK               CHAR(125),
   TRANSTYPE            CHAR(1),
   BY1                  CHAR(1),
   BY2                  CHAR(10),
   constraint "P_Key_1" primary key (CZBM, BILLNO)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table TBL_JZZF_EDHZ is
'支付额度汇总记录';

comment on column TBL_JZZF_EDHZ.CZBM is
'财政编码';

comment on column TBL_JZZF_EDHZ.CZRQ is
'操作日期';

comment on column TBL_JZZF_EDHZ.FINANO is
'财政流水号';

comment on column TBL_JZZF_EDHZ.CZY is
'操作员';

comment on column TBL_JZZF_EDHZ.BILLNO is
'单据号';

comment on column TBL_JZZF_EDHZ.BGDEPTCODE is
'单位代码';

comment on column TBL_JZZF_EDHZ.PROCDATE is
'业务日期';

comment on column TBL_JZZF_EDHZ.CAPTORGION is
'资金性质';

comment on column TBL_JZZF_EDHZ.FISCAL is
'会计年度';

comment on column TBL_JZZF_EDHZ.FISPERD is
'会计期间';

comment on column TBL_JZZF_EDHZ.TOTALSUM is
'总额度';

comment on column TBL_JZZF_EDHZ.REMARK is
'备注';

comment on column TBL_JZZF_EDHZ.TRANSTYPE is
'业务类型';

comment on column TBL_JZZF_EDHZ.BY1 is
'备用1';

comment on column TBL_JZZF_EDHZ.BY2 is
'备用2';

--==============================================================
-- Table: TBL_JZZF_EDMX
--==============================================================
create table TBL_JZZF_EDMX
(
   CZBM                 CHAR(10)               not null,
   BILLNO               CHAR(20)               not null,
   SEQU                 CHAR(125)              not null,
   BGDEPTCODE           CHAR(10),
   BGACCCODE            CHAR(8),
   PROJECTCODE          CHAR(8),
   BANKACCOUNT          CHAR(32),
   AUDITSUM             CHAR(20),
   CASHSUM              CHAR(20),
   BANKNODECODE         CHAR(8),
   REMARK1              CHAR(125),
   STAT                 CHAR(10),
   BY1                  CHAR(1),
   BY2                  CHAR(10),
   constraint "P_Key_1" primary key (CZBM, BILLNO, SEQU)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table TBL_JZZF_EDMX is
'支付额度明细';

comment on column TBL_JZZF_EDMX.CZBM is
'财政编码';

comment on column TBL_JZZF_EDMX.BILLNO is
'单据号';

comment on column TBL_JZZF_EDMX.SEQU is
'序号';

comment on column TBL_JZZF_EDMX.BGDEPTCODE is
'预算单位代码';

comment on column TBL_JZZF_EDMX.BGACCCODE is
'预算科目代码';

comment on column TBL_JZZF_EDMX.PROJECTCODE is
'预算项目代码';

comment on column TBL_JZZF_EDMX.BANKACCOUNT is
'预算单位零余额账号';

comment on column TBL_JZZF_EDMX.AUDITSUM is
'授权额度';

comment on column TBL_JZZF_EDMX.CASHSUM is
'其中现金';

comment on column TBL_JZZF_EDMX.BANKNODECODE is
'银行网点代码';

comment on column TBL_JZZF_EDMX.REMARK1 is
'备注';

comment on column TBL_JZZF_EDMX.STAT is
'启用标志 0 注销 1正常';

comment on column TBL_JZZF_EDMX.BY1 is
'备用1';

comment on column TBL_JZZF_EDMX.BY2 is
'备用2';

--==============================================================
-- Table: TBL_JZZF_OUTLAYCODE
--==============================================================
create table TBL_JZZF_OUTLAYCODE
(
   CZBM                 CHAR(10)               not null,
   CZRQ                 CHAR(10),
   FINANO               CHAR(25),
   CZY                  CHAR(60),
   OUTLAYCODE           CHAR(8)                not null,
   SUPEROUTLAYCODE      CHAR(8),
   OUTLAYNAME           CHAR(125),
   REMARK               CHAR(125),
   STAT                 CHAR(1),
   BY1                  CHAR(1),
   BY2                  CHAR(10),
   constraint "P_Key_1" primary key (CZBM, OUTLAYCODE)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table TBL_JZZF_OUTLAYCODE is
'经费类型表';

comment on column TBL_JZZF_OUTLAYCODE.CZBM is
'财政编码';

comment on column TBL_JZZF_OUTLAYCODE.CZRQ is
'操作日期';

comment on column TBL_JZZF_OUTLAYCODE.FINANO is
'财政流水号';

comment on column TBL_JZZF_OUTLAYCODE.CZY is
'操作员';

comment on column TBL_JZZF_OUTLAYCODE.OUTLAYCODE is
'经费类型代码';

comment on column TBL_JZZF_OUTLAYCODE.SUPEROUTLAYCODE is
'上级经费类型代码';

comment on column TBL_JZZF_OUTLAYCODE.OUTLAYNAME is
'经费类型名称';

comment on column TBL_JZZF_OUTLAYCODE.REMARK is
'备注';

comment on column TBL_JZZF_OUTLAYCODE.STAT is
'启用标志';

comment on column TBL_JZZF_OUTLAYCODE.BY1 is
'备用1';

comment on column TBL_JZZF_OUTLAYCODE.BY2 is
'备用2';

--==============================================================
-- Table: TBL_JZZF_PROJECTCLASSCODE
--==============================================================
create table TBL_JZZF_PROJECTCLASSCODE
(
   CZBM                 CHAR(10)               not null,
   CZRQ                 CHAR(10),
   FINANO               CHAR(25),
   CZY                  CHAR(60),
   PROJECTCLASSCODE     CHAR(8)                not null,
   SUPERPROJCLASSCODE   CHAR(8),
   PROJECTCLASSNAME     CHAR(125),
   REMARK               CHAR(125),
   STAT                 CHAR(1),
   BY1                  CHAR(1),
   BY2                  CHAR(10),
   constraint "P_Key_1" primary key (CZBM, PROJECTCLASSCODE)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table TBL_JZZF_PROJECTCLASSCODE is
'项目类别表';

comment on column TBL_JZZF_PROJECTCLASSCODE.CZBM is
'财政编码';

comment on column TBL_JZZF_PROJECTCLASSCODE.CZRQ is
'操作日期';

comment on column TBL_JZZF_PROJECTCLASSCODE.FINANO is
'财政流水号';

comment on column TBL_JZZF_PROJECTCLASSCODE.CZY is
'操作员';

comment on column TBL_JZZF_PROJECTCLASSCODE.PROJECTCLASSCODE is
'项目类别代码';

comment on column TBL_JZZF_PROJECTCLASSCODE.SUPERPROJCLASSCODE is
'上级项目类别代码';

comment on column TBL_JZZF_PROJECTCLASSCODE.PROJECTCLASSNAME is
'项目类别名称';

comment on column TBL_JZZF_PROJECTCLASSCODE.REMARK is
'备注';

comment on column TBL_JZZF_PROJECTCLASSCODE.STAT is
'启用标志';

comment on column TBL_JZZF_PROJECTCLASSCODE.BY1 is
'备用1';

comment on column TBL_JZZF_PROJECTCLASSCODE.BY2 is
'备用2';

--==============================================================
-- Table: TBL_JZZF_PROJECTCODE
--==============================================================
create table TBL_JZZF_PROJECTCODE
(
   CZBM                 CHAR(10)               not null,
   CZRQ                 CHAR(10),
   FINANO               CHAR(25),
   CZY                  CHAR(60),
   PROJECTCLASSCODE     CHAR(8),
   PROJECTCODE          CHAR(8)                not null,
   PROJECTNAME          CHAR(125),
   BGDEPTCODE           CHAR(8),
   REMARK               CHAR(125),
   STAT                 CHAR(1),
   BY1                  CHAR(1),
   BY2                  CHAR(10),
   constraint "P_Key_1" primary key (CZBM, PROJECTCODE)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table TBL_JZZF_PROJECTCODE is
'预算项目表';

comment on column TBL_JZZF_PROJECTCODE.CZBM is
'财政编码';

comment on column TBL_JZZF_PROJECTCODE.CZRQ is
'操作日期';

comment on column TBL_JZZF_PROJECTCODE.FINANO is
'财政流水号';

comment on column TBL_JZZF_PROJECTCODE.CZY is
'操作员';

comment on column TBL_JZZF_PROJECTCODE.PROJECTCLASSCODE is
'项目类别代码';

comment on column TBL_JZZF_PROJECTCODE.PROJECTCODE is
'项目代码';

comment on column TBL_JZZF_PROJECTCODE.PROJECTNAME is
'项目名称';

comment on column TBL_JZZF_PROJECTCODE.BGDEPTCODE is
'预算单位代码';

comment on column TBL_JZZF_PROJECTCODE.REMARK is
'备注';

comment on column TBL_JZZF_PROJECTCODE.STAT is
'启用标志';

comment on column TBL_JZZF_PROJECTCODE.BY1 is
'备用1';

comment on column TBL_JZZF_PROJECTCODE.BY2 is
'备用2';

