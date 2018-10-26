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
'Ԥ�㵥λ��Ϣ��';

comment on column TBL_JZZF_BGACCCODE.CZBM is
'��������';

comment on column TBL_JZZF_BGACCCODE.CZRQ is
'��������';

comment on column TBL_JZZF_BGACCCODE.FINANO is
'������ˮ��';

comment on column TBL_JZZF_BGACCCODE.CZY is
'����Ա';

comment on column TBL_JZZF_BGACCCODE.BGACCCODE is
'Ԥ���Ŀ����';

comment on column TBL_JZZF_BGACCCODE.BGACCSORTCODE is
'Ԥ���Ŀ����';

comment on column TBL_JZZF_BGACCCODE.BGACCKINDCODE is
'Ԥ���Ŀ�����';

comment on column TBL_JZZF_BGACCCODE.BGACCITEMCODE is
'Ԥ���Ŀ�����';

comment on column TBL_JZZF_BGACCCODE.BGCODE is
'Ԥ���Ŀ��׼��';

comment on column TBL_JZZF_BGACCCODE.BGACCNAME is
'Ԥ�㵥λ����';

comment on column TBL_JZZF_BGACCCODE.REMARK is
'��ע';

comment on column TBL_JZZF_BGACCCODE.STAT is
'���ñ�־';

comment on column TBL_JZZF_BGACCCODE.BY1 is
'����1';

comment on column TBL_JZZF_BGACCCODE.BY2 is
'����2';

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
'Ԥ�㵥λ��Ϣ��';

comment on column TBL_JZZF_BGDEPTCODE.CZBM is
'��������';

comment on column TBL_JZZF_BGDEPTCODE.CZRQ is
'��������';

comment on column TBL_JZZF_BGDEPTCODE.FINANO is
'������ˮ��';

comment on column TBL_JZZF_BGDEPTCODE.CZY is
'����Ա';

comment on column TBL_JZZF_BGDEPTCODE.BGDEPTCODE is
'Ԥ�㵥λ����';

comment on column TBL_JZZF_BGDEPTCODE.CHARGEBGDEPTCODE is
'���ܵ�λ����';

comment on column TBL_JZZF_BGDEPTCODE.BGCODELEVEL is
'Ԥ�㵥λ����';

comment on column TBL_JZZF_BGDEPTCODE.BGCODE is
'������';

comment on column TBL_JZZF_BGDEPTCODE.BGDEPTNAME is
'Ԥ�㵥λ����';

comment on column TBL_JZZF_BGDEPTCODE.BANKACCOUNT is
'Ԥ�㵥λ������˺�';

comment on column TBL_JZZF_BGDEPTCODE.ADDRESS is
'Ԥ�㵥λ��ַ';

comment on column TBL_JZZF_BGDEPTCODE.TELEPHONE is
'��ϵ�绰';

comment on column TBL_JZZF_BGDEPTCODE.REMARK is
'��ע';

comment on column TBL_JZZF_BGDEPTCODE.STAT is
'���ñ�־';

comment on column TBL_JZZF_BGDEPTCODE.BY1 is
'����1';

comment on column TBL_JZZF_BGDEPTCODE.BY2 is
'����2';

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
'ҵ���ұ�';

comment on column TBL_JZZF_BGORGCODE.CZBM is
'��������';

comment on column TBL_JZZF_BGORGCODE.CZRQ is
'��������';

comment on column TBL_JZZF_BGORGCODE.FINANO is
'������ˮ��';

comment on column TBL_JZZF_BGORGCODE.CZY is
'����Ա';

comment on column TBL_JZZF_BGORGCODE.BGORGCODE is
'ҵ���Ҵ���';

comment on column TBL_JZZF_BGORGCODE.BGORGNAME is
'ҵ��������';

comment on column TBL_JZZF_BGORGCODE.REMARK is
'��ע';

comment on column TBL_JZZF_BGORGCODE.STAT is
'���ñ�־';

comment on column TBL_JZZF_BGORGCODE.BY1 is
'����1';

comment on column TBL_JZZF_BGORGCODE.BY2 is
'����2';

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
'֧��ƾ֤�ǼǱ�';

comment on column TBL_JZZF_BILLNO.CZBM is
'��������';

comment on column TBL_JZZF_BILLNO.CZRQ is
'��������';

comment on column TBL_JZZF_BILLNO.FINANO is
'������ˮ��';

comment on column TBL_JZZF_BILLNO.CZY is
'����Ա';

comment on column TBL_JZZF_BILLNO.BILLNO is
'���ݺ�';

comment on column TBL_JZZF_BILLNO.BGORGCODE is
'ҵ����Ҵ���';

comment on column TBL_JZZF_BILLNO.BGDEPTCODE is
'Ԥ�㵥λ����';

comment on column TBL_JZZF_BILLNO.PROCDATE is
'ҵ������';

comment on column TBL_JZZF_BILLNO.CAPTORGION is
'�ʽ�����';

comment on column TBL_JZZF_BILLNO.FISCAL is
'������';

comment on column TBL_JZZF_BILLNO.FISPERD is
'����ڼ�';

comment on column TBL_JZZF_BILLNO.PAYMENTTYPE is
'֧����ʽ';

comment on column TBL_JZZF_BILLNO.BGACCCODE is
'Ԥ���Ŀ����';

comment on column TBL_JZZF_BILLNO.PROJECTCODE is
'Ԥ����Ŀ����';

comment on column TBL_JZZF_BILLNO.TYPEOFPAY is
'֧������';

comment on column TBL_JZZF_BILLNO.OUTLAYCODE is
'��������';

comment on column TBL_JZZF_BILLNO.PAYUSAGE is
'֧����;';

comment on column TBL_JZZF_BILLNO.RECEBANKACCOUNT is
'�տ����˺�';

comment on column TBL_JZZF_BILLNO.RECENAME is
'�տ�������';

comment on column TBL_JZZF_BILLNO.RECEBANKNODENAME is
'�տ��˿�����';

comment on column TBL_JZZF_BILLNO.PAYBANKACCOUNT is
'�������˺�';

comment on column TBL_JZZF_BILLNO.PAYNAME is
'����������';

comment on column TBL_JZZF_BILLNO.PAYBANKNODENAME is
'�����˿�����';

comment on column TBL_JZZF_BILLNO.PAYSUM is
'֧�����';

comment on column TBL_JZZF_BILLNO.REMARK is
'��ע';

comment on column TBL_JZZF_BILLNO.TRANSTYPE is
'ҵ������';

comment on column TBL_JZZF_BILLNO.OUTBANKTYPE is
'����� 1���� 2��� 3˰Ʊ 4ͬ�� 5���ǿ�';

comment on column TBL_JZZF_BILLNO.OUTBANKCODE is
'�д���';

comment on column TBL_JZZF_BILLNO.OUTBANKNAME is
'������';

comment on column TBL_JZZF_BILLNO.ACTIONSTEP is
'ƾ֤״̬';

comment on column TBL_JZZF_BILLNO.SENDFLAG is
'���ͱ�־';

comment on column TBL_JZZF_BILLNO.NOTE1 is
'��ע1';

comment on column TBL_JZZF_BILLNO.NOTE2 is
'��ע2';

comment on column TBL_JZZF_BILLNO.NOTE3 is
'��ע3';

comment on column TBL_JZZF_BILLNO.NOTE4 is
'��ע4';

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
'��BIN';

comment on column TBL_JZZF_CARDBIN.NOTE is
'��ע';

comment on column TBL_JZZF_CARDBIN.BY1 is
'����1';

comment on column TBL_JZZF_CARDBIN.BY2 is
'����2';

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
'֧����Ȼ��ܼ�¼';

comment on column TBL_JZZF_EDHZ.CZBM is
'��������';

comment on column TBL_JZZF_EDHZ.CZRQ is
'��������';

comment on column TBL_JZZF_EDHZ.FINANO is
'������ˮ��';

comment on column TBL_JZZF_EDHZ.CZY is
'����Ա';

comment on column TBL_JZZF_EDHZ.BILLNO is
'���ݺ�';

comment on column TBL_JZZF_EDHZ.BGDEPTCODE is
'��λ����';

comment on column TBL_JZZF_EDHZ.PROCDATE is
'ҵ������';

comment on column TBL_JZZF_EDHZ.CAPTORGION is
'�ʽ�����';

comment on column TBL_JZZF_EDHZ.FISCAL is
'������';

comment on column TBL_JZZF_EDHZ.FISPERD is
'����ڼ�';

comment on column TBL_JZZF_EDHZ.TOTALSUM is
'�ܶ��';

comment on column TBL_JZZF_EDHZ.REMARK is
'��ע';

comment on column TBL_JZZF_EDHZ.TRANSTYPE is
'ҵ������';

comment on column TBL_JZZF_EDHZ.BY1 is
'����1';

comment on column TBL_JZZF_EDHZ.BY2 is
'����2';

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
'֧�������ϸ';

comment on column TBL_JZZF_EDMX.CZBM is
'��������';

comment on column TBL_JZZF_EDMX.BILLNO is
'���ݺ�';

comment on column TBL_JZZF_EDMX.SEQU is
'���';

comment on column TBL_JZZF_EDMX.BGDEPTCODE is
'Ԥ�㵥λ����';

comment on column TBL_JZZF_EDMX.BGACCCODE is
'Ԥ���Ŀ����';

comment on column TBL_JZZF_EDMX.PROJECTCODE is
'Ԥ����Ŀ����';

comment on column TBL_JZZF_EDMX.BANKACCOUNT is
'Ԥ�㵥λ������˺�';

comment on column TBL_JZZF_EDMX.AUDITSUM is
'��Ȩ���';

comment on column TBL_JZZF_EDMX.CASHSUM is
'�����ֽ�';

comment on column TBL_JZZF_EDMX.BANKNODECODE is
'�����������';

comment on column TBL_JZZF_EDMX.REMARK1 is
'��ע';

comment on column TBL_JZZF_EDMX.STAT is
'���ñ�־ 0 ע�� 1����';

comment on column TBL_JZZF_EDMX.BY1 is
'����1';

comment on column TBL_JZZF_EDMX.BY2 is
'����2';

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
'�������ͱ�';

comment on column TBL_JZZF_OUTLAYCODE.CZBM is
'��������';

comment on column TBL_JZZF_OUTLAYCODE.CZRQ is
'��������';

comment on column TBL_JZZF_OUTLAYCODE.FINANO is
'������ˮ��';

comment on column TBL_JZZF_OUTLAYCODE.CZY is
'����Ա';

comment on column TBL_JZZF_OUTLAYCODE.OUTLAYCODE is
'�������ʹ���';

comment on column TBL_JZZF_OUTLAYCODE.SUPEROUTLAYCODE is
'�ϼ��������ʹ���';

comment on column TBL_JZZF_OUTLAYCODE.OUTLAYNAME is
'������������';

comment on column TBL_JZZF_OUTLAYCODE.REMARK is
'��ע';

comment on column TBL_JZZF_OUTLAYCODE.STAT is
'���ñ�־';

comment on column TBL_JZZF_OUTLAYCODE.BY1 is
'����1';

comment on column TBL_JZZF_OUTLAYCODE.BY2 is
'����2';

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
'��Ŀ����';

comment on column TBL_JZZF_PROJECTCLASSCODE.CZBM is
'��������';

comment on column TBL_JZZF_PROJECTCLASSCODE.CZRQ is
'��������';

comment on column TBL_JZZF_PROJECTCLASSCODE.FINANO is
'������ˮ��';

comment on column TBL_JZZF_PROJECTCLASSCODE.CZY is
'����Ա';

comment on column TBL_JZZF_PROJECTCLASSCODE.PROJECTCLASSCODE is
'��Ŀ������';

comment on column TBL_JZZF_PROJECTCLASSCODE.SUPERPROJCLASSCODE is
'�ϼ���Ŀ������';

comment on column TBL_JZZF_PROJECTCLASSCODE.PROJECTCLASSNAME is
'��Ŀ�������';

comment on column TBL_JZZF_PROJECTCLASSCODE.REMARK is
'��ע';

comment on column TBL_JZZF_PROJECTCLASSCODE.STAT is
'���ñ�־';

comment on column TBL_JZZF_PROJECTCLASSCODE.BY1 is
'����1';

comment on column TBL_JZZF_PROJECTCLASSCODE.BY2 is
'����2';

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
'Ԥ����Ŀ��';

comment on column TBL_JZZF_PROJECTCODE.CZBM is
'��������';

comment on column TBL_JZZF_PROJECTCODE.CZRQ is
'��������';

comment on column TBL_JZZF_PROJECTCODE.FINANO is
'������ˮ��';

comment on column TBL_JZZF_PROJECTCODE.CZY is
'����Ա';

comment on column TBL_JZZF_PROJECTCODE.PROJECTCLASSCODE is
'��Ŀ������';

comment on column TBL_JZZF_PROJECTCODE.PROJECTCODE is
'��Ŀ����';

comment on column TBL_JZZF_PROJECTCODE.PROJECTNAME is
'��Ŀ����';

comment on column TBL_JZZF_PROJECTCODE.BGDEPTCODE is
'Ԥ�㵥λ����';

comment on column TBL_JZZF_PROJECTCODE.REMARK is
'��ע';

comment on column TBL_JZZF_PROJECTCODE.STAT is
'���ñ�־';

comment on column TBL_JZZF_PROJECTCODE.BY1 is
'����1';

comment on column TBL_JZZF_PROJECTCODE.BY2 is
'����2';

