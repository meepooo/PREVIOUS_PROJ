drop table PABYBH_ACCTO2N;

drop table PABYBH_ACCT_ENTRY_HIS;

drop table PABYBH_ACCT_ENTRY;

drop table PABYBH_CHECKCTL;

drop table PABYBH_COURSE_INFO;

drop table PABYBH_CUSTINFO;

drop index K_PABYBH_DEPCHKINFO_1;

drop table PABYBH_DEPCHKINFO;

drop index K_PABYBH_DEPCHKINFO_2;

drop table PABYBH_DEPCHKINFO_HIS;

drop index K_PABYBH_HOSCHKINFO_1;

drop table PABYBH_HOSCHKINFO;

drop index K_PABYBH_HOSCHKINFO_2;

drop table PABYBH_HOSCHKINFO_HIS;

drop index K_PABYBH_NOTBAL_1;

drop table PABYBH_NOTBAL;

drop index K_PABYBH_NOTBAL_2;

drop table PABYBH_NOTBAL_HIS;

drop table PABYBH_ORGCFG;

drop table PABYBH_PABTRANSCTL;

drop table PABYBH_SECKEY;

drop index K_PABYBH_SERIAL_3;

drop index K_PABYBH_SERIAL_2;

drop index K_PABYBH_SERIAL_1;

drop table PABYBH_SERIAL;

drop index K_PABYBH_SERIAL_6;

drop index K_PABYBH_SERIAL_5;

drop index K_PABYBH_SERIAL_4;

drop table PABYBH_SERIAL_HIS;

drop index K_PABYBH_SIGN_1;

drop table PABYBH_SIGN;

drop table PABYBH_SVRINFO;

drop table PABYBH_TRADER;

--==============================================================
-- Table: PABYBH_ACCTO2N
--==============================================================
create table PABYBH_ACCTO2N (
   COBANKNO             VARCHAR(12)            not null,
   OLDACCT              VARCHAR(32)            not null,
   OLDORG               VARCHAR(10),
   NEWACCT              VARCHAR(32)            not null,
   NEWORG               VARCHAR(10),
   EXTFLD1              VARCHAR(32),
   EXTFLD2              VARCHAR(64),
   EXTFLD3              VARCHAR(64),
   constraint PK_PABYBH_ACCTO2N primary key (COBANKNO, OLDACCT)
)
IN GAPS_DATA INDEX IN GAPS_INDEX;

comment on table PABYBH_ACCTO2N is
'���������˺�ӳ��';

comment on column PABYBH_ACCTO2N.COBANKNO is
'�����к�';

comment on column PABYBH_ACCTO2N.OLDACCT is
'���˺�';

comment on column PABYBH_ACCTO2N.OLDORG is
'�ϻ���';

comment on column PABYBH_ACCTO2N.NEWACCT is
'���˺�';

comment on column PABYBH_ACCTO2N.NEWORG is
'�»���';

comment on column PABYBH_ACCTO2N.EXTFLD1 is
'�����ֶ�1';

comment on column PABYBH_ACCTO2N.EXTFLD2 is
'�����ֶ�2';

comment on column PABYBH_ACCTO2N.EXTFLD3 is
'�����ֶ�3';

--==============================================================
-- Table: PABYBH_ACCT_ENTRY_HIS
--==============================================================
create table PABYBH_ACCT_ENTRY_HIS (
   CHECKDATE            VARCHAR(8)             not null,
   ID                   VARCHAR(32)            not null,
   COURSE_CODE          VARCHAR(50)            not null,
   COURSE_NAME          VARCHAR(50)            not null,
   COURSE_ACCOUNT       VARCHAR(32)            not null,
   CDFLAG               VARCHAR(1)             not null,
   TRANSAMT             DECIMAL(16,2),
   REMARKCODE           VARCHAR(32),
   EXTFLD1              VARCHAR(32),
   EXTFLD2              VARCHAR(64),
   EXTFLD3              VARCHAR(64)
)
IN GAPS_DATA INDEX IN GAPS_INDEX;

comment on table PABYBH_ACCT_ENTRY_HIS is
'��Ʒ�¼��ʷ��';

comment on column PABYBH_ACCT_ENTRY_HIS.CHECKDATE is
'������������';

comment on column PABYBH_ACCT_ENTRY_HIS.ID is
'��¼���';

comment on column PABYBH_ACCT_ENTRY_HIS.COURSE_CODE is
'��Ŀ����';

comment on column PABYBH_ACCT_ENTRY_HIS.COURSE_NAME is
'��Ŀ����';

comment on column PABYBH_ACCT_ENTRY_HIS.COURSE_ACCOUNT is
'��Ŀ�˺�';

comment on column PABYBH_ACCT_ENTRY_HIS.CDFLAG is
'�����־ 0-�� 1-��';

comment on column PABYBH_ACCT_ENTRY_HIS.TRANSAMT is
'���׽��';

comment on column PABYBH_ACCT_ENTRY_HIS.REMARKCODE is
'ժҪ��';

comment on column PABYBH_ACCT_ENTRY_HIS.EXTFLD1 is
'��չ�ֶ�1';

comment on column PABYBH_ACCT_ENTRY_HIS.EXTFLD2 is
'��չ�ֶ�2';

comment on column PABYBH_ACCT_ENTRY_HIS.EXTFLD3 is
'��չ�ֶ�3';


--==============================================================
-- Table: PABYBH_ACCT_ENTRY
--==============================================================
create table PABYBH_ACCT_ENTRY (
   CHECKDATE            VARCHAR(8)             not null,
   ID                   VARCHAR(32)            not null,
   COURSE_CODE          VARCHAR(50)            not null,
   COURSE_NAME          VARCHAR(50)            not null,
   COURSE_ACCOUNT       VARCHAR(32)            not null,
   CDFLAG               VARCHAR(1)             not null,
   TRANSAMT             DECIMAL(16,2),
   REMARKCODE           VARCHAR(32),
   EXTFLD1              VARCHAR(32),
   EXTFLD2              VARCHAR(64),
   EXTFLD3              VARCHAR(64),
   constraint PABYBH_ACCT_ENTRY_KEY primary key (CHECKDATE, ID)
)
IN GAPS_DATA INDEX IN GAPS_INDEX;

comment on table PABYBH_ACCT_ENTRY is
'��Ʒ�¼��';

comment on column PABYBH_ACCT_ENTRY.CHECKDATE is
'������������';

comment on column PABYBH_ACCT_ENTRY.ID is
'��¼���';

comment on column PABYBH_ACCT_ENTRY.COURSE_CODE is
'��Ŀ����';

comment on column PABYBH_ACCT_ENTRY.COURSE_NAME is
'��Ŀ����';

comment on column PABYBH_ACCT_ENTRY.COURSE_ACCOUNT is
'��Ŀ�˺�';

comment on column PABYBH_ACCT_ENTRY.CDFLAG is
'�����־ 0-�� 1-��';

comment on column PABYBH_ACCT_ENTRY.TRANSAMT is
'���׽��';

comment on column PABYBH_ACCT_ENTRY.REMARKCODE is
'ժҪ��';

comment on column PABYBH_ACCT_ENTRY.EXTFLD1 is
'��չ�ֶ�1';

comment on column PABYBH_ACCT_ENTRY.EXTFLD2 is
'��չ�ֶ�2';

comment on column PABYBH_ACCT_ENTRY.EXTFLD3 is
'��չ�ֶ�3';

--==============================================================
-- Table: PABYBH_CHECKCTL
--==============================================================
create table PABYBH_CHECKCTL (
   CHECKDATE            VARCHAR(8)             not null,
   COBANKNO             VARCHAR(12)            not null,
   SVRCODE              VARCHAR(6)             not null,
   MSGTYPE              VARCHAR(1)             not null,
   TOTALCOUNT           INTEGER,
   TOTALAMT             DECIMAL(16,2),
   INTOTCNT             INTEGER,
   INTOTAMT             DECIMAL(16,2),
   OUTTOTCNT            INTEGER,
   OUTTOTAMT            DECIMAL(16,2),
   BACKTOTALCOUNT       INTEGER,
   BACKTOTALAMT         DECIMAL(16,2),
   LOCALTOTALCOUNT      INTEGER,
   LOCALTOTALAMT        DECIMAL(16,2),
   LOCALBACKTOTALCOUNT  INTEGER,
   LOCALBACKTOTALAMT    DECIMAL(16,2),
   HOSTTOTALCOUNT       INTEGER,
   HOSTTOTALAMT         DECIMAL(16,2),
   HOSTBACKTOTALCOUNT   INTEGER,
   HOSTBACKTOTALAMT     DECIMAL(16,2),
   NETAMT               DECIMAL(16,2),
   NETTYPE              VARCHAR(1),
   IEPCHKFILE           VARCHAR(100),
   HOSTCHKFILE          VARCHAR(100),
   EXECSTEP             VARCHAR(2),
   EXECSTAT             VARCHAR(1),
   CHKDETAILRESULT      VARCHAR(1),
   CHKPABTOTALRESULT    VARCHAR(1),
   CHKHOSTTOTALRESULT   VARCHAR(1),
   SETTLEDATE           VARCHAR(8),
   SETTLESERNO          VARCHAR(40),
   TRANSDATE            VARCHAR(8),
   TRANSSERIALNO        VARCHAR(40),
   HOSTDATE             VARCHAR(40),
   HOSTSERIALNO         VARCHAR(40),
   TRANSORG             VARCHAR(10),
   TRANSOPER            VARCHAR(10),
   RESPCODE             VARCHAR(10),
   RESPMSG              VARCHAR(120),
   STAT                 VARCHAR(1),
   EXTFLD1              VARCHAR(32),
   EXTFLD2              VARCHAR(64),
   EXTFLD3              VARCHAR(128),
   constraint PK_PABYBH_CHECKCTL primary key (CHECKDATE, COBANKNO, 
SVRCODE, MSGTYPE)
)
IN GAPS_DATA INDEX IN GAPS_INDEX;

comment on table PABYBH_CHECKCTL is
'���˿��Ʊ�';

comment on column PABYBH_CHECKCTL.CHECKDATE is
'��������';

comment on column PABYBH_CHECKCTL.COBANKNO is
'�����к�';

comment on column PABYBH_CHECKCTL.SVRCODE is
'������';

comment on column PABYBH_CHECKCTL.MSGTYPE is
'��������0�ʽ���1�˻��ࣨ������2�˻��ࣨ��Լ&������';

comment on column PABYBH_CHECKCTL.TOTALCOUNT is
'�ܱ���';

comment on column PABYBH_CHECKCTL.TOTALAMT is
'�ܽ��';

comment on column PABYBH_CHECKCTL.INTOTCNT is
'ת���ܱ���';

comment on column PABYBH_CHECKCTL.INTOTAMT is
'ת���ܽ��';

comment on column PABYBH_CHECKCTL.OUTTOTCNT is
'ת���ܱ���';

comment on column PABYBH_CHECKCTL.OUTTOTAMT is
'ת���ܽ��';

comment on column PABYBH_CHECKCTL.BACKTOTALCOUNT is
'�����ܱ���';

comment on column PABYBH_CHECKCTL.BACKTOTALAMT is
'�����ܽ��';

comment on column PABYBH_CHECKCTL.LOCALTOTALCOUNT is
'ƽ̨�ܱ���';

comment on column PABYBH_CHECKCTL.LOCALTOTALAMT is
'ƽ̨�ܽ��';

comment on column PABYBH_CHECKCTL.LOCALBACKTOTALCOUNT is
'ƽ̨�����ܱ���';

comment on column PABYBH_CHECKCTL.LOCALBACKTOTALAMT is
'ƽ̨�����ܽ��';

comment on column PABYBH_CHECKCTL.HOSTTOTALCOUNT is
'�����ܱ���';

comment on column PABYBH_CHECKCTL.HOSTTOTALAMT is
'�����ܽ��';

comment on column PABYBH_CHECKCTL.HOSTBACKTOTALCOUNT is
'���������ܱ���';

comment on column PABYBH_CHECKCTL.HOSTBACKTOTALAMT is
'���������ܽ��';

comment on column PABYBH_CHECKCTL.NETAMT is
'������';

comment on column PABYBH_CHECKCTL.NETTYPE is
'����� ''0���� 1֧��''';

comment on column PABYBH_CHECKCTL.IEPCHKFILE is
'ƽ�������ļ���';

comment on column PABYBH_CHECKCTL.HOSTCHKFILE is
'���������ļ���';

comment on column PABYBH_CHECKCTL.EXECSTEP is
'ִ�в���''0-��ȡƽ��������Ϣ 1-ƽ�������ļ���� 2-ƽ����ϸ������� 3-�����ύ���� 4-��ȡ���������ļ�,�������ɶ����ļ���� 5
-������ϸ�������''';

comment on column PABYBH_CHECKCTL.EXECSTAT is
'ִ��״̬''0-�ɹ� 1-ʧ��''';

comment on column PABYBH_CHECKCTL.CHKDETAILRESULT is
'��ϸ���˽��''0 δ���� 1 ����ƽ 2���˲�ƽ 3���˳��� 9 ������''';

comment on column PABYBH_CHECKCTL.CHKPABTOTALRESULT is
'���Ķ����˽��''0 δ���� 1 ����ƽ 2���˲�ƽ 3���˳��� 9 ������''';

comment on column PABYBH_CHECKCTL.CHKHOSTTOTALRESULT is
'���Ķ����˽��''0 δ���� 1 ����ƽ 2���˲�ƽ 3���˳��� 9 ������''';

comment on column PABYBH_CHECKCTL.SETTLEDATE is
'��������';

comment on column PABYBH_CHECKCTL.SETTLESERNO is
'������ˮ��';

comment on column PABYBH_CHECKCTL.TRANSDATE is
'��������';

comment on column PABYBH_CHECKCTL.TRANSSERIALNO is
'������ˮ��';

comment on column PABYBH_CHECKCTL.HOSTDATE is
'�����������';

comment on column PABYBH_CHECKCTL.HOSTSERIALNO is
'���������ˮ��';

comment on column PABYBH_CHECKCTL.TRANSORG is
'���׻���';

comment on column PABYBH_CHECKCTL.TRANSOPER is
'���׹�Ա';

comment on column PABYBH_CHECKCTL.RESPCODE is
'��Ӧ��';

comment on column PABYBH_CHECKCTL.RESPMSG is
'��Ӧ��Ϣ';

comment on column PABYBH_CHECKCTL.STAT is
'����״̬ 0�ɹ� 1ʧ�� 6״̬δ֪ 7������ 8������ 9��ʼ';

comment on column PABYBH_CHECKCTL.EXTFLD1 is
'�����ֶ�1';

comment on column PABYBH_CHECKCTL.EXTFLD2 is
'�����ֶ�2';

comment on column PABYBH_CHECKCTL.EXTFLD3 is
'�����ֶ�3';

--==============================================================
-- Table: PABYBH_COURSE_INFO
--==============================================================
create table PABYBH_COURSE_INFO (
   ID                   VARCHAR(32)            not null,
   COURSE_CODE          VARCHAR(50)            not null,
   COURSE_NAME          VARCHAR(50)            not null,
   COURSE_ACCOUNT       VARCHAR(32)            not null,
   COURSE_DESC          VARCHAR(200),
   constraint PABYBH_COURSE_INFO_KEY primary key (ID)
)
IN GAPS_DATA INDEX IN GAPS_INDEX;

comment on table PABYBH_COURSE_INFO is
'��Ŀ��Ϣ��';

comment on column PABYBH_COURSE_INFO.ID is
'��� ';

comment on column PABYBH_COURSE_INFO.COURSE_CODE is
'��Ŀ���� ';

comment on column PABYBH_COURSE_INFO.COURSE_NAME is
'��Ŀ���� ';

comment on column PABYBH_COURSE_INFO.COURSE_ACCOUNT is
'��Ŀ�˺� ';

comment on column PABYBH_COURSE_INFO.COURSE_DESC is
'��Ŀ���� ';

--==============================================================
-- Table: PABYBH_CUSTINFO
--==============================================================
create table PABYBH_CUSTINFO (
   CERTTYPE             VARCHAR(2)             not null,
   CERTNO               VARCHAR(32)            not null,
   CUSTTYPE             VARCHAR(2),
   CUSTNAME             VARCHAR(120),
   POST                 VARCHAR(6),
   ADDR                 VARCHAR(128),
   EMAIL                VARCHAR(120),
   PHONE                VARCHAR(16),
   MOBILE               VARCHAR(11),
   FAX                  VARCHAR(16),
   UPDATEDATE           VARCHAR(8),
   UPDATETIME           VARCHAR(6),
   CREATEDATE           VARCHAR(8),
   CREATETIME           VARCHAR(6),
   EXTFLD1              VARCHAR(32),
   EXTFLD2              VARCHAR(64),
   EXTFLD3              VARCHAR(64),
   constraint PK_PABYBH_CUSTINFO primary key (CERTTYPE, CERTNO)
)
IN GAPS_DATA INDEX IN GAPS_INDEX;

comment on table PABYBH_CUSTINFO is
'�ͻ���Ϣ��';

comment on column PABYBH_CUSTINFO.CERTTYPE is
'֤������';

comment on column PABYBH_CUSTINFO.CERTNO is
'֤������';

comment on column PABYBH_CUSTINFO.CUSTTYPE is
'�ͻ����� 00-���� 01-����';

comment on column PABYBH_CUSTINFO.CUSTNAME is
'�ͻ�����';

comment on column PABYBH_CUSTINFO.POST is
'�ʱ�';

comment on column PABYBH_CUSTINFO.ADDR is
'��ַ';

comment on column PABYBH_CUSTINFO.EMAIL is
'����';

comment on column PABYBH_CUSTINFO.PHONE is
'��ϵ��ʽ';

comment on column PABYBH_CUSTINFO.MOBILE is
'�ֻ���';

comment on column PABYBH_CUSTINFO.FAX is
'����';

comment on column PABYBH_CUSTINFO.UPDATEDATE is
'��������';

comment on column PABYBH_CUSTINFO.UPDATETIME is
'����ʱ��';

comment on column PABYBH_CUSTINFO.CREATEDATE is
'��������';

comment on column PABYBH_CUSTINFO.CREATETIME is
'����ʱ��';

comment on column PABYBH_CUSTINFO.EXTFLD1 is
'��չ�ֶ�1';

comment on column PABYBH_CUSTINFO.EXTFLD2 is
'��չ�ֶ�2';

comment on column PABYBH_CUSTINFO.EXTFLD3 is
'��չ�ֶ�3';

--==============================================================
-- Table: PABYBH_DEPCHKINFO
--==============================================================
create table PABYBH_DEPCHKINFO (
   CHECKDATE            VARCHAR(8)             not null,
   TRANSDATE            VARCHAR(8)             not null,
   TRANSTIME            VARCHAR(6),
   TRANSFERTYPE         VARCHAR(1),
   ACCTNO               VARCHAR(32),
   STOCKCODE            VARCHAR(8)             not null,
   CAPITALACCTNO        VARCHAR(30)            not null,
   AMT                  DECIMAL(16,2),
   WORKSERIALNO         VARCHAR(30),
   IEPSERIALNO          VARCHAR(30)            not null,
   COBANKNO             VARCHAR(12)            not null,
   EXTFLD1              VARCHAR(32),
   EXTFLD2              VARCHAR(64),
   constraint PK_PABYBH_DEPCHKINFO primary key (CHECKDATE, IEPSERIALNO)

)
IN GAPS_DATA INDEX IN GAPS_INDEX;

comment on table PABYBH_DEPCHKINFO is
'ƽ�����д�ܶ�����ϸ��';

comment on column PABYBH_DEPCHKINFO.CHECKDATE is
'��������';

comment on column PABYBH_DEPCHKINFO.TRANSDATE is
'��������';

comment on column PABYBH_DEPCHKINFO.TRANSTIME is
'����ʱ��';

comment on column PABYBH_DEPCHKINFO.TRANSFERTYPE is
'�ʽ�����''0--��ת֤1--֤ת��''      ';

comment on column PABYBH_DEPCHKINFO.ACCTNO is
'�����˺�';

comment on column PABYBH_DEPCHKINFO.STOCKCODE is
'ȯ�̴���';

comment on column PABYBH_DEPCHKINFO.CAPITALACCTNO is
'֤ȯ�ʽ�̨�˺�';

comment on column PABYBH_DEPCHKINFO.AMT is
'���';

comment on column PABYBH_DEPCHKINFO.WORKSERIALNO is
'��������ˮ��';

comment on column PABYBH_DEPCHKINFO.IEPSERIALNO is
'��Eͨ��ˮ��';

comment on column PABYBH_DEPCHKINFO.COBANKNO is
'�����к�';

comment on column PABYBH_DEPCHKINFO.EXTFLD1 is
'�����ֶ�1';

comment on column PABYBH_DEPCHKINFO.EXTFLD2 is
'�����ֶ�2';

--==============================================================
-- Index: K_PABYBH_DEPCHKINFO_1
--==============================================================
create index K_PABYBH_DEPCHKINFO_1 on PABYBH_DEPCHKINFO (
   CHECKDATE            ASC,
   COBANKNO             ASC,
   WORKSERIALNO         ASC
);

--==============================================================
-- Table: PABYBH_DEPCHKINFO_HIS
--==============================================================
create table PABYBH_DEPCHKINFO_HIS (
   CHECKDATE            VARCHAR(8)             not null,
   TRANSDATE            VARCHAR(8)             not null,
   TRANSTIME            VARCHAR(6),
   TRANSFERTYPE         VARCHAR(1),
   ACCTNO               VARCHAR(32),
   STOCKCODE            VARCHAR(8)             not null,
   CAPITALACCTNO        VARCHAR(30)            not null,
   AMT                  DECIMAL(16,2),
   WORKSERIALNO         VARCHAR(30),
   IEPSERIALNO          VARCHAR(30)            not null,
   COBANKNO             VARCHAR(12)            not null,
   EXTFLD1              VARCHAR(32),
   EXTFLD2              VARCHAR(64),
   constraint PK_PABYBH_DEPCHKINFO_HIS primary key (CHECKDATE, 
IEPSERIALNO)
)
IN GAPS_DATA INDEX IN GAPS_INDEX;

comment on table PABYBH_DEPCHKINFO_HIS is
'ƽ�����д�ܶ�����ϸ��';

comment on column PABYBH_DEPCHKINFO_HIS.CHECKDATE is
'��������';

comment on column PABYBH_DEPCHKINFO_HIS.TRANSDATE is
'��������';

comment on column PABYBH_DEPCHKINFO_HIS.TRANSTIME is
'����ʱ��';

comment on column PABYBH_DEPCHKINFO_HIS.TRANSFERTYPE is
'�ʽ�����''0--��ת֤1--֤ת��''      ';

comment on column PABYBH_DEPCHKINFO_HIS.ACCTNO is
'�����˺�';

comment on column PABYBH_DEPCHKINFO_HIS.STOCKCODE is
'ȯ�̴���';

comment on column PABYBH_DEPCHKINFO_HIS.CAPITALACCTNO is
'֤ȯ�ʽ�̨�˺�';

comment on column PABYBH_DEPCHKINFO_HIS.AMT is
'���';

comment on column PABYBH_DEPCHKINFO_HIS.WORKSERIALNO is
'��������ˮ��';

comment on column PABYBH_DEPCHKINFO_HIS.IEPSERIALNO is
'��Eͨ��ˮ��';

comment on column PABYBH_DEPCHKINFO_HIS.COBANKNO is
'�����к�';

comment on column PABYBH_DEPCHKINFO_HIS.EXTFLD1 is
'�����ֶ�1';

comment on column PABYBH_DEPCHKINFO_HIS.EXTFLD2 is
'�����ֶ�2';

--==============================================================
-- Index: K_PABYBH_DEPCHKINFO_2
--==============================================================
create index K_PABYBH_DEPCHKINFO_2 on PABYBH_DEPCHKINFO_HIS (
   CHECKDATE            ASC,
   COBANKNO             ASC,
   WORKSERIALNO         ASC
);

--==============================================================
-- Table: PABYBH_HOSCHKINFO
--==============================================================
create table PABYBH_HOSCHKINFO (
   COBANKNO             VARCHAR(10)            not null,
   CHECKDATE            VARCHAR(8)             not null,
   WORKSERIALNO         VARCHAR(32)            not null,
   HOSTDATE             VARCHAR(8)             not null,
   HOSTSERIALNO         VARCHAR(32)            not null,
   HOSTBACKDATE         VARCHAR(8)             not null,
   HOSTBACKSERNO        VARCHAR(32)            not null,
   HOSTTRANSCODE        VARCHAR(16),
   ACCTNO               VARCHAR(32),
   TRANSAMT             DECIMAL(16,2),
   TRANSFARE            DECIMAL(16,2),
   CASHFLAG             VARCHAR(1),
   STAT                 VARCHAR(1),
   CDFLAG               VARCHAR(1),
   SVRTYPE              VARCHAR(10),
   REMARKCODE           VARCHAR(32),
   REMARK               VARCHAR(50),
   TRANSBRANCHNO        VARCHAR(10),
   TRANSORG             VARCHAR(10),
   TRANSOPER            VARCHAR(10),
   JOINCHKFLAG          VARCHAR(1),
   EXTFLD1              VARCHAR(32),
   EXTFLD2              VARCHAR(64),
   EXTFLD3              VARCHAR(64),
   constraint PK_PABYBH_HOSCHKINFO primary key (HOSTDATE, HOSTSERIALNO)

)
IN GAPS_DATA INDEX IN GAPS_INDEX;

comment on table PABYBH_HOSCHKINFO is
'����������Ϣ';

comment on column PABYBH_HOSCHKINFO.COBANKNO is
'�����к�';

comment on column PABYBH_HOSCHKINFO.CHECKDATE is
'��������';

comment on column PABYBH_HOSCHKINFO.WORKSERIALNO is
'ƽ̨ҵ����ˮ��';

comment on column PABYBH_HOSCHKINFO.HOSTDATE is
'��������';

comment on column PABYBH_HOSCHKINFO.HOSTSERIALNO is
'������ˮ��';

comment on column PABYBH_HOSCHKINFO.ACCTNO is
'�����˺�';

comment on column PABYBH_HOSCHKINFO.TRANSAMT is
'���׽��';

comment on column PABYBH_HOSCHKINFO.TRANSFARE is
'������';

comment on column PABYBH_HOSCHKINFO.CASHFLAG is
'��ת��־1-�ֽ� 2-ת��';

comment on column PABYBH_HOSCHKINFO.STAT is
'����״̬0-���� 7-������ 8-������ 1-ʧ��';

comment on column PABYBH_HOSCHKINFO.CDFLAG is
'�����־';

comment on column PABYBH_HOSCHKINFO.SVRTYPE is
'ҵ������';

comment on column PABYBH_HOSCHKINFO.REMARKCODE is
'ժҪ��';

comment on column PABYBH_HOSCHKINFO.REMARK is
'ժҪ��Ϣ';

comment on column PABYBH_HOSCHKINFO.TRANSBRANCHNO is
'��������';

comment on column PABYBH_HOSCHKINFO.TRANSORG is
'���׻���';

comment on column PABYBH_HOSCHKINFO.TRANSOPER is
'���׹�Ա';

comment on column PABYBH_HOSCHKINFO.JOINCHKFLAG is
'������˱�־��0-�����룬1-����';

comment on column PABYBH_HOSCHKINFO.EXTFLD1 is
'�����ֶ�1';

comment on column PABYBH_HOSCHKINFO.EXTFLD2 is
'�����ֶ�2';

comment on column PABYBH_HOSCHKINFO.EXTFLD3 is
'�����ֶ�3';

--==============================================================
-- Index: K_PABYBH_HOSCHKINFO_1
--==============================================================
create index K_PABYBH_HOSCHKINFO_1 on PABYBH_HOSCHKINFO (
   CHECKDATE            ASC,
   COBANKNO             ASC,
   WORKSERIALNO         ASC
);

--==============================================================
-- Table: PABYBH_HOSCHKINFO_HIS
--==============================================================
create table PABYBH_HOSCHKINFO_HIS (
   COBANKNO             VARCHAR(10)            not null,
   CHECKDATE            VARCHAR(8)             not null,
   WORKSERIALNO         VARCHAR(32)            not null,
   HOSTDATE             VARCHAR(8)             not null,
   HOSTSERIALNO         VARCHAR(32)            not null,
   HOSTBACKDATE         VARCHAR(8)             not null,
   HOSTBACKSERNO        VARCHAR(32)            not null,
   HOSTTRANSCODE        VARCHAR(16),
   ACCTNO               VARCHAR(32),
   TRANSAMT             DECIMAL(16,2),
   TRANSFARE            DECIMAL(16,2),
   CASHFLAG             VARCHAR(1),
   STAT                 VARCHAR(1),
   CDFLAG               VARCHAR(1),
   SVRTYPE              VARCHAR(10),
   REMARKCODE           VARCHAR(32),
   REMARK               VARCHAR(50),
   TRANSBRANCHNO        VARCHAR(10),
   TRANSORG             VARCHAR(10),
   TRANSOPER            VARCHAR(10),
   JOINCHKFLAG          VARCHAR(1),
   EXTFLD1              VARCHAR(32),
   EXTFLD2              VARCHAR(64),
   EXTFLD3              VARCHAR(64),
   constraint PK_PABYBH_HOSCHKINFO_HIS primary key (HOSTDATE, 
HOSTSERIALNO)
)
IN GAPS_DATA INDEX IN GAPS_INDEX;

comment on table PABYBH_HOSCHKINFO_HIS is
'����������Ϣ';

comment on column PABYBH_HOSCHKINFO_HIS.COBANKNO is
'�����к�';

comment on column PABYBH_HOSCHKINFO_HIS.CHECKDATE is
'��������';

comment on column PABYBH_HOSCHKINFO_HIS.WORKSERIALNO is
'ƽ̨ҵ����ˮ��';

comment on column PABYBH_HOSCHKINFO_HIS.HOSTDATE is
'��������';

comment on column PABYBH_HOSCHKINFO_HIS.HOSTSERIALNO is
'������ˮ��';

comment on column PABYBH_HOSCHKINFO_HIS.ACCTNO is
'�����˺�';

comment on column PABYBH_HOSCHKINFO_HIS.TRANSAMT is
'���׽��';

comment on column PABYBH_HOSCHKINFO_HIS.TRANSFARE is
'������';

comment on column PABYBH_HOSCHKINFO_HIS.CASHFLAG is
'��ת��־1-�ֽ� 2-ת��';

comment on column PABYBH_HOSCHKINFO_HIS.STAT is
'����״̬0-���� 7-������ 8-������ 1-ʧ��';

comment on column PABYBH_HOSCHKINFO_HIS.CDFLAG is
'�����־';

comment on column PABYBH_HOSCHKINFO_HIS.SVRTYPE is
'ҵ������';

comment on column PABYBH_HOSCHKINFO_HIS.REMARKCODE is
'ժҪ��';

comment on column PABYBH_HOSCHKINFO_HIS.REMARK is
'ժҪ��Ϣ';

comment on column PABYBH_HOSCHKINFO_HIS.TRANSBRANCHNO is
'��������';

comment on column PABYBH_HOSCHKINFO_HIS.TRANSORG is
'���׻���';

comment on column PABYBH_HOSCHKINFO_HIS.TRANSOPER is
'���׹�Ա';

comment on column PABYBH_HOSCHKINFO_HIS.JOINCHKFLAG is
'������˱�־��0-�����룬1-����';

comment on column PABYBH_HOSCHKINFO_HIS.EXTFLD1 is
'�����ֶ�1';

comment on column PABYBH_HOSCHKINFO_HIS.EXTFLD2 is
'�����ֶ�2';

comment on column PABYBH_HOSCHKINFO_HIS.EXTFLD3 is
'�����ֶ�3';

--==============================================================
-- Index: K_PABYBH_HOSCHKINFO_2
--==============================================================
create index K_PABYBH_HOSCHKINFO_2 on PABYBH_HOSCHKINFO_HIS (
   CHECKDATE            ASC,
   COBANKNO             ASC,
   WORKSERIALNO         ASC
);

--==============================================================
-- Table: PABYBH_NOTBAL
--==============================================================
create table PABYBH_NOTBAL (
   CHECKDATE            VARCHAR(8)             not null,
   COBANKNO             VARCHAR(12)            not null,
   SVRCODE              VARCHAR(4)             not null,
   TRANSFERTYPE         VARCHAR(1),
   STOCKCODE            VARCHAR(8),
   CAPITALACCTNO        VARCHAR(30),
   WORKSERIALNO         VARCHAR(30),
   BANKSTAT             VARCHAR(1),
   BANKACCTNO           VARCHAR(32),
   BANKAMT              DECIMAL(16,2),
   BANKTRANSCODE        VARCHAR(8),
   IEPSERIALNO          VARCHAR(30),
   IEPSTAT              VARCHAR(1),
   IEPACCTNO            VARCHAR(32),
   IEPAMT               DECIMAL(16,2),
   IEPTRANSCODE         VARCHAR(8),
   HOSTDATE             VARCHAR(8),
   HOSTSERIALNO         VARCHAR(30),
   HOSTSTAT             VARCHAR(1),
   HOSTACCTNO           VARCHAR(32),
   HOSTAMT              DECIMAL(16,2),
   HOSTTRANSCODE        VARCHAR(8),
   CHECKSTAT            VARCHAR(1),
   ADJUSTSTAT           VARCHAR(1),
   ADJUSTTRANSORG       VARCHAR(10),
   ADJUSTTRANSOPER      VARCHAR(10),
   ADJUSTDATE           VARCHAR(8),
   ADJUSTSERIALNO       VARCHAR(32),
   ADJUSTHOSTBSIDATE    VARCHAR(8),
   ADJUSTHOSTSERIALNO   VARCHAR(32),
   ADJUSTRESPCODE       VARCHAR(10),
   ADJUSTRESPMSG        VARCHAR(120),
   EXTFLD1              VARCHAR(32),
   EXTFLD2              VARCHAR(64)
)
IN GAPS_DATA INDEX IN GAPS_INDEX;

comment on table PABYBH_NOTBAL is
'���˲�ƽ��ϸ';

comment on column PABYBH_NOTBAL.CHECKDATE is
'��������';

comment on column PABYBH_NOTBAL.COBANKNO is
'�����к�';

comment on column PABYBH_NOTBAL.SVRCODE is
'�������';

comment on column PABYBH_NOTBAL.TRANSFERTYPE is
'�ʽ�����''0--������ת֤1--֤ת�������''';

comment on column PABYBH_NOTBAL.STOCKCODE is
'ȯ�̴���';

comment on column PABYBH_NOTBAL.CAPITALACCTNO is
'֤ȯ�ʽ�̨�˺�';

comment on column PABYBH_NOTBAL.WORKSERIALNO is
'��������ˮ��';

comment on column PABYBH_NOTBAL.BANKSTAT is
'������״̬';

comment on column PABYBH_NOTBAL.BANKACCTNO is
'ƽ̨�����˺�';

comment on column PABYBH_NOTBAL.BANKAMT is
'ƽ̨���׽��';

comment on column PABYBH_NOTBAL.BANKTRANSCODE is
'ƽ̨���״���';

comment on column PABYBH_NOTBAL.IEPSERIALNO is
'��Eͨ��ˮ��';

comment on column PABYBH_NOTBAL.IEPSTAT is
'��Eͨ״̬';

comment on column PABYBH_NOTBAL.IEPACCTNO is
'��Eͨ�����˺�';

comment on column PABYBH_NOTBAL.IEPAMT is
'��Eͨ���׽��';

comment on column PABYBH_NOTBAL.IEPTRANSCODE is
'��Eͨ���״���';

comment on column PABYBH_NOTBAL.HOSTDATE is
'��������';

comment on column PABYBH_NOTBAL.HOSTSERIALNO is
'������ˮ��';

comment on column PABYBH_NOTBAL.HOSTSTAT is
'����״̬';

comment on column PABYBH_NOTBAL.HOSTACCTNO is
'���������˺�';

comment on column PABYBH_NOTBAL.HOSTAMT is
'�������׽��';

comment on column PABYBH_NOTBAL.HOSTTRANSCODE is
'�������״���';

comment on column PABYBH_NOTBAL.CHECKSTAT is
'���˽����־,0-δ����1-�Ѷ�ƽ2-ƽ����3-���Ķ�  4-�˺Ų��� 5-���� 6-״̬���� ';

comment on column PABYBH_NOTBAL.ADJUSTSTAT is
'����״̬ 0-�ɹ� 1-ʧ�� 7-��ʱ 9-��ʼ ';

comment on column PABYBH_NOTBAL.ADJUSTTRANSORG is
'���˽��׻���';

comment on column PABYBH_NOTBAL.ADJUSTTRANSOPER is
'���˽��׹�Ա';

comment on column PABYBH_NOTBAL.ADJUSTDATE is
'��������';

comment on column PABYBH_NOTBAL.ADJUSTSERIALNO is
'����ҵ����ˮ��';

comment on column PABYBH_NOTBAL.ADJUSTHOSTBSIDATE is
'����������������';

comment on column PABYBH_NOTBAL.ADJUSTHOSTSERIALNO is
'����������ˮ��';

comment on column PABYBH_NOTBAL.ADJUSTRESPCODE is
'������Ӧ��';

comment on column PABYBH_NOTBAL.ADJUSTRESPMSG is
'������Ӧ��Ϣ';

comment on column PABYBH_NOTBAL.EXTFLD1 is
'�����ֶ�1';

comment on column PABYBH_NOTBAL.EXTFLD2 is
'�����ֶ�2';

--==============================================================
-- Index: K_PABYBH_NOTBAL_1
--==============================================================
create index K_PABYBH_NOTBAL_1 on PABYBH_NOTBAL (
   CHECKDATE            ASC,
   COBANKNO             ASC,
   SVRCODE              ASC
);

--==============================================================
-- Table: PABYBH_NOTBAL_HIS
--==============================================================
create table PABYBH_NOTBAL_HIS (
   CHECKDATE            VARCHAR(8)             not null,
   COBANKNO             VARCHAR(12)            not null,
   SVRCODE              VARCHAR(4)             not null,
   TRANSFERTYPE         VARCHAR(1),
   STOCKCODE            VARCHAR(8),
   CAPITALACCTNO        VARCHAR(30),
   WORKSERIALNO         VARCHAR(30),
   BANKSTAT             VARCHAR(1),
   BANKACCTNO           VARCHAR(32),
   BANKAMT              DECIMAL(16,2),
   BANKTRANSCODE        VARCHAR(8),
   IEPSERIALNO          VARCHAR(30),
   IEPSTAT              VARCHAR(1),
   IEPACCTNO            VARCHAR(32),
   IEPAMT               DECIMAL(16,2),
   IEPTRANSCODE         VARCHAR(8),
   HOSTDATE             VARCHAR(8),
   HOSTSERIALNO         VARCHAR(30),
   HOSTSTAT             VARCHAR(1),
   HOSTACCTNO           VARCHAR(32),
   HOSTAMT              DECIMAL(16,2),
   HOSTTRANSCODE        VARCHAR(8),
   CHECKSTAT            VARCHAR(1),
   ADJUSTSTAT           VARCHAR(1),
   ADJUSTTRANSORG       VARCHAR(10),
   ADJUSTTRANSOPER      VARCHAR(10),
   ADJUSTDATE           VARCHAR(8),
   ADJUSTSERIALNO       VARCHAR(32),
   ADJUSTHOSTBSIDATE    VARCHAR(8),
   ADJUSTHOSTSERIALNO   VARCHAR(32),
   ADJUSTRESPCODE       VARCHAR(10),
   ADJUSTRESPMSG        VARCHAR(120),
   EXTFLD1              VARCHAR(32),
   EXTFLD2              VARCHAR(64)
)
IN GAPS_DATA INDEX IN GAPS_INDEX;

comment on table PABYBH_NOTBAL_HIS is
'���˲�ƽ��ϸ';

comment on column PABYBH_NOTBAL_HIS.CHECKDATE is
'��������';

comment on column PABYBH_NOTBAL_HIS.COBANKNO is
'�����к�';

comment on column PABYBH_NOTBAL_HIS.SVRCODE is
'�������';

comment on column PABYBH_NOTBAL_HIS.TRANSFERTYPE is
'�ʽ�����''0--������ת֤1--֤ת�������''';

comment on column PABYBH_NOTBAL_HIS.STOCKCODE is
'ȯ�̴���';

comment on column PABYBH_NOTBAL_HIS.CAPITALACCTNO is
'֤ȯ�ʽ�̨�˺�';

comment on column PABYBH_NOTBAL_HIS.WORKSERIALNO is
'��������ˮ��';

comment on column PABYBH_NOTBAL_HIS.BANKSTAT is
'������״̬';

comment on column PABYBH_NOTBAL_HIS.BANKACCTNO is
'ƽ̨�����˺�';

comment on column PABYBH_NOTBAL_HIS.BANKAMT is
'ƽ̨���׽��';

comment on column PABYBH_NOTBAL_HIS.BANKTRANSCODE is
'ƽ̨���״���';

comment on column PABYBH_NOTBAL_HIS.IEPSERIALNO is
'��Eͨ��ˮ��';

comment on column PABYBH_NOTBAL_HIS.IEPSTAT is
'��Eͨ״̬';

comment on column PABYBH_NOTBAL_HIS.IEPACCTNO is
'��Eͨ�����˺�';

comment on column PABYBH_NOTBAL_HIS.IEPAMT is
'��Eͨ���׽��';

comment on column PABYBH_NOTBAL_HIS.IEPTRANSCODE is
'��Eͨ���״���';

comment on column PABYBH_NOTBAL_HIS.HOSTDATE is
'��������';

comment on column PABYBH_NOTBAL_HIS.HOSTSERIALNO is
'������ˮ��';

comment on column PABYBH_NOTBAL_HIS.HOSTSTAT is
'����״̬';

comment on column PABYBH_NOTBAL_HIS.HOSTACCTNO is
'���������˺�';

comment on column PABYBH_NOTBAL_HIS.HOSTAMT is
'�������׽��';

comment on column PABYBH_NOTBAL_HIS.HOSTTRANSCODE is
'�������״���';

comment on column PABYBH_NOTBAL_HIS.CHECKSTAT is
'���˽����־,0-δ����1-�Ѷ�ƽ2-ƽ����3-���Ķ�  4-�˺Ų��� 5-���� 6-״̬���� ';

comment on column PABYBH_NOTBAL_HIS.ADJUSTSTAT is
'����״̬ 0-�ɹ� 1-ʧ�� 7-��ʱ 9-��ʼ ';

comment on column PABYBH_NOTBAL_HIS.ADJUSTTRANSORG is
'���˽��׻���';

comment on column PABYBH_NOTBAL_HIS.ADJUSTTRANSOPER is
'���˽��׹�Ա';

comment on column PABYBH_NOTBAL_HIS.ADJUSTDATE is
'��������';

comment on column PABYBH_NOTBAL_HIS.ADJUSTSERIALNO is
'����ҵ����ˮ��';

comment on column PABYBH_NOTBAL_HIS.ADJUSTHOSTBSIDATE is
'����������������';

comment on column PABYBH_NOTBAL_HIS.ADJUSTHOSTSERIALNO is
'����������ˮ��';

comment on column PABYBH_NOTBAL_HIS.ADJUSTRESPCODE is
'������Ӧ��';

comment on column PABYBH_NOTBAL_HIS.ADJUSTRESPMSG is
'������Ӧ��Ϣ';

comment on column PABYBH_NOTBAL_HIS.EXTFLD1 is
'�����ֶ�1';

comment on column PABYBH_NOTBAL_HIS.EXTFLD2 is
'�����ֶ�2';

--==============================================================
-- Index: K_PABYBH_NOTBAL_2
--==============================================================
create index K_PABYBH_NOTBAL_2 on PABYBH_NOTBAL_HIS (
   CHECKDATE            ASC,
   COBANKNO             ASC,
   SVRCODE              ASC
);

--==============================================================
-- Table: PABYBH_ORGCFG
--==============================================================
create table PABYBH_ORGCFG (
   COBANKNO             VARCHAR(12)            not null,
   COBANKNAME           VARCHAR(100),
   CUSTMANAGERNO        VARCHAR(10),
   ACCT                 VARCHAR(32),
   ACCTNAME             VARCHAR(60),
   ACCT1                VARCHAR(32),
   ACCT1NAME            VARCHAR(60),
   ACCT2                VARCHAR(32),
   ACCT2NAME            VARCHAR(60),
   ACCT3                VARCHAR(32),
   ACCT3NAME            VARCHAR(60),
   ACCT4                VARCHAR(32),
   ACCT4NAME            VARCHAR(60),
   SIGNSTATUS           VARCHAR(1)             not null,
   AREACODE             VARCHAR(20),
   COORGNO              VARCHAR(20),
   WORKDATE             VARCHAR(8)             not null,
   WORKSERIALNO         VARCHAR(32),
   MAINTAINDATE         VARCHAR(8),
   MAINTAINTIME         VARCHAR(6),
   EXTFLD1              VARCHAR(64),
   EXTFLD2              VARCHAR(64),
   EXTFLD3              VARCHAR(64),
   EXTFLD4              VARCHAR(64),
   EXTFLD5              VARCHAR(255),
   EXTFLD6              VARCHAR(255),
   constraint PK_PABYBH_ORGCFG primary key (COBANKNO)
)
IN GAPS_DATA INDEX IN GAPS_INDEX;

comment on table PABYBH_ORGCFG is
'���������Ϣ';

comment on column PABYBH_ORGCFG.COBANKNO is
'�����к�';

comment on column PABYBH_ORGCFG.COBANKNAME is
'����������';

comment on column PABYBH_ORGCFG.CUSTMANAGERNO is
'����ͻ������';

comment on column PABYBH_ORGCFG.ACCT is
'ͷ���˺�';

comment on column PABYBH_ORGCFG.ACCTNAME is
'ͷ���˻�����';

comment on column PABYBH_ORGCFG.ACCT1 is
'�ڲ�������ɻ�1';

comment on column PABYBH_ORGCFG.ACCT1NAME is
'�ڲ�������ɻ�����1';

comment on column PABYBH_ORGCFG.ACCT2 is
'�ڲ�������ɻ�2';

comment on column PABYBH_ORGCFG.ACCT2NAME is
'�ڲ�������ɻ�����2';

comment on column PABYBH_ORGCFG.ACCT3 is
'�ڲ�������ɻ�3';

comment on column PABYBH_ORGCFG.ACCT3NAME is
'�ڲ�������ɻ�����3';

comment on column PABYBH_ORGCFG.ACCT4 is
'�ڲ�������ɻ�4';

comment on column PABYBH_ORGCFG.ACCT4NAME is
'�ڲ�������ɻ�����4';

comment on column PABYBH_ORGCFG.SIGNSTATUS is
'ǩ��״̬0-ǩ�� 1-ǩ��';

comment on column PABYBH_ORGCFG.AREACODE is
'��������';

comment on column PABYBH_ORGCFG.COORGNO is
'�����л�����';

comment on column PABYBH_ORGCFG.WORKDATE is
'ҵ������';

comment on column PABYBH_ORGCFG.WORKSERIALNO is
'ҵ����ˮ��';

comment on column PABYBH_ORGCFG.MAINTAINDATE is
'ά������';

comment on column PABYBH_ORGCFG.MAINTAINTIME is
'ά��ʱ��';

comment on column PABYBH_ORGCFG.EXTFLD1 is
'�����ֶ�1';

comment on column PABYBH_ORGCFG.EXTFLD2 is
'�����ֶ�2';

comment on column PABYBH_ORGCFG.EXTFLD3 is
'�����ֶ�3';

comment on column PABYBH_ORGCFG.EXTFLD4 is
'�����ֶ�4';

comment on column PABYBH_ORGCFG.EXTFLD5 is
'�����ֶ�5';

comment on column PABYBH_ORGCFG.EXTFLD6 is
'�����ֶ�6';

--==============================================================
-- Table: PABYBH_PABTRANSCTL
--==============================================================
create table PABYBH_PABTRANSCTL (
   TRANSCODE            VARCHAR(10)            not null,
   TRANSNAME            VARCHAR(100)           not null,
   SVRCODE              VARCHAR(6)             not null,
   MACFLAG              VARCHAR(1)             not null,
   EXTFLD1              VARCHAR(32),
   EXTFLD2              VARCHAR(32),
   EXTFLD3              VARCHAR(32),
   constraint PK_PABYBH_PABTRANSCTL primary key (TRANSCODE, SVRCODE)
)
IN GAPS_DATA INDEX IN GAPS_INDEX;

comment on table PABYBH_PABTRANSCTL is
'ƽ�����������';

comment on column PABYBH_PABTRANSCTL.TRANSCODE is
'���״���';

comment on column PABYBH_PABTRANSCTL.TRANSNAME is
'��������';

comment on column PABYBH_PABTRANSCTL.SVRCODE is
'�������';

comment on column PABYBH_PABTRANSCTL.MACFLAG is
'MACУ���־''1--��0--��''';

comment on column PABYBH_PABTRANSCTL.EXTFLD1 is
'�����ֶ�1';

comment on column PABYBH_PABTRANSCTL.EXTFLD2 is
'�����ֶ�2';

comment on column PABYBH_PABTRANSCTL.EXTFLD3 is
'�����ֶ�3';

--==============================================================
-- Table: PABYBH_SECKEY
--==============================================================
create table PABYBH_SECKEY (
   COBANKNO             VARCHAR(12)            not null,
   ENCRYPTIP            VARCHAR(32),
   ENCRYPTPORT          VARCHAR(32),
   ENCRYPTSYSID         VARCHAR(32),
   ENCRYPTEXTID         VARCHAR(32),
   ZMK                  VARCHAR(255),
   ZAK                  VARCHAR(255)           not null,
   IEPZPK               VARCHAR(255)           not null,
   COUNTERZPK           VARCHAR(255),
   HOSTZPK              VARCHAR(255),
   EXTFLD1              VARCHAR(64),
   EXTFLD2              VARCHAR(64),
   EXTFLD3              VARCHAR(255),
   EXTFLD4              VARCHAR(255),
   constraint PK_PABYBH_SECKEY primary key (COBANKNO)
)
IN GAPS_DATA INDEX IN GAPS_INDEX;

comment on table PABYBH_SECKEY is
'��Կ��Ϣ';

comment on column PABYBH_SECKEY.COBANKNO is
'�����к�';

comment on column PABYBH_SECKEY.ENCRYPTIP is
'����ƽ̨��ַ';

comment on column PABYBH_SECKEY.ENCRYPTPORT is
'����ƽ̨�˿�';

comment on column PABYBH_SECKEY.ENCRYPTSYSID is
'����ƽ̨ϵͳID';

comment on column PABYBH_SECKEY.ENCRYPTEXTID is
'����ƽ̨�ⲿID';

comment on column PABYBH_SECKEY.ZMK is
'ZMK';

comment on column PABYBH_SECKEY.ZAK is
'ZAK';

comment on column PABYBH_SECKEY.IEPZPK is
'ZPK ƽ��';

comment on column PABYBH_SECKEY.COUNTERZPK is
'ZPK ����';

comment on column PABYBH_SECKEY.HOSTZPK is
'ZPK ������';

comment on column PABYBH_SECKEY.EXTFLD1 is
'��չ1';

comment on column PABYBH_SECKEY.EXTFLD2 is
'��չ2';

comment on column PABYBH_SECKEY.EXTFLD3 is
'��չ3';

comment on column PABYBH_SECKEY.EXTFLD4 is
'��չ4';

--==============================================================
-- Table: PABYBH_SERIAL
--==============================================================
create table PABYBH_SERIAL (
   TRANSDATE            VARCHAR(8)             not null,
   TRANSSERIALNO        VARCHAR(40)            not null,
   ORITRANSDATE         VARCHAR(8),
   ORITRANSSERIALNO     VARCHAR(40),
   TRANSTIME            VARCHAR(8)             not null,
   WORKDATE             VARCHAR(8)             not null,
   WORKSERIALNO         VARCHAR(40)            not null,
   REQDATE              VARCHAR(8)             not null,
   REQSERIALNO          VARCHAR(40)            not null,
   CLUSTERNODENAME      VARCHAR(30),
   CLUSTERNODEIP        VARCHAR(20),
   COBANKNO             VARCHAR(12)            not null,
   TRANSORG             VARCHAR(10),
   TRANSOPER            VARCHAR(10),
   AUTHORG              VARCHAR(10),
   AUTHOPER             VARCHAR(10),
   CNLTYPE              VARCHAR(5),
   TERMEQUINO           VARCHAR(20),
   TRANSCODE            VARCHAR(12),
   TRANSCODE1           VARCHAR(1),
   CUACOUNTYPE          VARCHAR(1),
   TRANSNAME            VARCHAR(100),
   CAPITALTYPE          VARCHAR(1),
   SVRCODE              VARCHAR(10),
   CUSTNAME             VARCHAR(80),
   CUSTTYPE             VARCHAR(2),
   ACCTNO               VARCHAR(32),
   ORIACCTNO            VARCHAR(32),
   ACCTNO2              VARCHAR(32),
   STOCKCODE            VARCHAR(8),
   CAPITALACCTNO        VARCHAR(32),
   TRANSAMT             DECIMAL(16,2),
   ORITRANSAMT          DECIMAL(16,2),
   AMT2                 DECIMAL(16,2),
   AMT3                 DECIMAL(16,2),
   CURR                 VARCHAR(3),
   CASHFLAG             VARCHAR(1),
   IEPSVRCODE           VARCHAR(8),
   IEPTRANSCODE         VARCHAR(16),
   IEPBSIDATE           VARCHAR(8),
   IEPTRADATE           VARCHAR(8),
   IEPSERIALNO          VARCHAR(32),
   ORIIEPBSIDATE        VARCHAR(8),
   ORIIEPSERIALNO       VARCHAR(32),
   IEPRESPCODE          VARCHAR(12),
   IEPRESPMSG           VARCHAR(120),
   HOSTBSIDATE          VARCHAR(8),
   HOSTSERIALNO         VARCHAR(32),
   HOSTTRANSCODE        VARCHAR(16),
   HOSTRESPCODE         VARCHAR(12),
   HOSTRESPMSG          VARCHAR(120),
   RESPCODE             VARCHAR(10),
   RESPMSG              VARCHAR(120),
   IEPSTAT              VARCHAR(1),
   HOSTSTAT             VARCHAR(1),
   STAT                 VARCHAR(1),
   ORISTAT              VARCHAR(1),
   CERTTYPE             VARCHAR(2),
   CERTNO               VARCHAR(32),
   PHONE                VARCHAR(20),
   AGENTNAME            VARCHAR(80),
   AGENTCERTY           VARCHAR(2),
   AGENTCERNO           VARCHAR(32),
   AGENTPHONE           VARCHAR(20),
   CHKFLAG              VARCHAR(1),
   MEMO                 VARCHAR(128),
   EXTFLD1              VARCHAR(64),
   EXTFLD2              VARCHAR(64),
   EXTFLD3              VARCHAR(128),
   EXTFLD4              VARCHAR(128),
   constraint PK_PABYBH_SERIAL primary key (TRANSDATE, TRANSSERIALNO)
)
IN GAPS_DATA INDEX IN GAPS_INDEX;

comment on table PABYBH_SERIAL is
'������ˮ��';

comment on column PABYBH_SERIAL.TRANSDATE is
'��������';

comment on column PABYBH_SERIAL.TRANSSERIALNO is
'������ˮ��';

comment on column PABYBH_SERIAL.ORITRANSDATE is
'ԭ��������';

comment on column PABYBH_SERIAL.ORITRANSSERIALNO is
'ԭ������ˮ��';

comment on column PABYBH_SERIAL.TRANSTIME is
'����ʱ��';

comment on column PABYBH_SERIAL.WORKDATE is
'ҵ������';

comment on column PABYBH_SERIAL.WORKSERIALNO is
'ҵ����ˮ��';

comment on column PABYBH_SERIAL.REQDATE is
'��������';

comment on column PABYBH_SERIAL.REQSERIALNO is
'������ˮ�� Y-���ķ��� G-���ڹ��淢�� T-����̨����';

comment on column PABYBH_SERIAL.CLUSTERNODENAME is
'��Ⱥ����������';

comment on column PABYBH_SERIAL.CLUSTERNODEIP is
'��Ⱥ������IP';

comment on column PABYBH_SERIAL.COBANKNO is
'�����к�';

comment on column PABYBH_SERIAL.TRANSORG is
'���׻���';

comment on column PABYBH_SERIAL.TRANSOPER is
'���׹�Ա';

comment on column PABYBH_SERIAL.AUTHORG is
'��Ȩ����';

comment on column PABYBH_SERIAL.AUTHOPER is
'��Ȩ��Ա';

comment on column PABYBH_SERIAL.CNLTYPE is
'�������� 403-ƽ������ 200-����̨ 201-����';

comment on column PABYBH_SERIAL.TERMEQUINO is
'�ն��豸���';

comment on column PABYBH_SERIAL.TRANSCODE is
'���״���';

comment on column PABYBH_SERIAL.TRANSCODE1 is
'���ӽ��״���  944302-��0 ���� 1 ��� 2���������� 3 ���򹤱��ѣ�
944316-�����˲��㣩';

comment on column PABYBH_SERIAL.CUACOUNTYPE is
'�����˱�־ 0-���� 1-����';

comment on column PABYBH_SERIAL.TRANSNAME is
'��������';

comment on column PABYBH_SERIAL.CAPITALTYPE is
'�ʽ�����,0 ---ת��1--- ת��';

comment on column PABYBH_SERIAL.CUSTNAME is
'�ͻ�����';

comment on column PABYBH_SERIAL.CUSTTYPE is
'�ͻ����� 00-���� 01-����';

comment on column PABYBH_SERIAL.ACCTNO is
'�����˺�';

comment on column PABYBH_SERIAL.ORIACCTNO is
'�������Ķ��˱���ԭ�����˺�';

comment on column PABYBH_SERIAL.ACCTNO2 is
'�ʺ�2   �������˻�';

comment on column PABYBH_SERIAL.STOCKCODE is
'ȯ�̴���';

comment on column PABYBH_SERIAL.CAPITALACCTNO is
'�ʽ��ʺ�';

comment on column PABYBH_SERIAL.TRANSAMT is
'���׽��';

comment on column PABYBH_SERIAL.ORITRANSAMT is
'�������Ķ��˱���ԭ���׽��';

comment on column PABYBH_SERIAL.AMT2 is
'���2';

comment on column PABYBH_SERIAL.AMT3 is
'���3';

comment on column PABYBH_SERIAL.CURR is
'����';

comment on column PABYBH_SERIAL.CASHFLAG is
'�����ʶ';

comment on column PABYBH_SERIAL.IEPSVRCODE is
'��Eͨ�������';

comment on column PABYBH_SERIAL.IEPTRANSCODE is
'��Eͨ���״���';

comment on column PABYBH_SERIAL.IEPBSIDATE is
'��Eͨҵ������';

comment on column PABYBH_SERIAL.IEPTRADATE is
'��Eͨ��������';

comment on column PABYBH_SERIAL.IEPSERIALNO is
'��Eͨ��ˮ��';

comment on column PABYBH_SERIAL.ORIIEPBSIDATE is
'ԭ��Eͨҵ������';

comment on column PABYBH_SERIAL.ORIIEPSERIALNO is
'ԭ��Eͨ��ˮ��';

comment on column PABYBH_SERIAL.IEPRESPCODE is
'��Eͨ��Ӧ����';

comment on column PABYBH_SERIAL.IEPRESPMSG is
'��Eͨ��Ӧ��Ϣ';

comment on column PABYBH_SERIAL.HOSTBSIDATE is
'������������';

comment on column PABYBH_SERIAL.HOSTSERIALNO is
'������ˮ��';

comment on column PABYBH_SERIAL.HOSTTRANSCODE is
'�������״���';

comment on column PABYBH_SERIAL.HOSTRESPCODE is
'������Ӧ����';

comment on column PABYBH_SERIAL.HOSTRESPMSG is
'������Ӧ��Ϣ';

comment on column PABYBH_SERIAL.RESPCODE is
'��Ӧ��';

comment on column PABYBH_SERIAL.RESPMSG is
'��Ӧ��Ϣ';

comment on column PABYBH_SERIAL.IEPSTAT is
'���Ľ���״̬''0�ɹ� 1ʧ�� 6״̬δ֪ 7������ 8������ 9��ʼ''';

comment on column PABYBH_SERIAL.HOSTSTAT is
'���Ľ���״̬''0�ɹ� 1ʧ�� 6״̬δ֪ 7������ 8������ 9��ʼ''';

comment on column PABYBH_SERIAL.STAT is
'����״̬''0�ɹ� 1ʧ�� 6״̬δ֪ 7������ 8������ 9��ʼ''';

comment on column PABYBH_SERIAL.ORISTAT is
'�������Ķ��˱���ԭ����״̬ ''0�ɹ� 1ʧ�� 6״̬δ֪ 7������ 8������ 9��ʼ XԴ��ˮ������''';

comment on column PABYBH_SERIAL.CERTTYPE is
'֤������';

comment on column PABYBH_SERIAL.CERTNO is
'֤������';

comment on column PABYBH_SERIAL.CHKFLAG is
'���˱�־,0-δ����1-�Ѷ�ƽ2-ƽ����3-���Ķ� X-ƽ���Ѷ��� ';

comment on column PABYBH_SERIAL.MEMO is
'��ע';

comment on column PABYBH_SERIAL.EXTFLD1 is
'�����ֶ�1 ';

comment on column PABYBH_SERIAL.EXTFLD2 is
'�����ֶ�2';

comment on column PABYBH_SERIAL.EXTFLD3 is
'�����ֶ�3';

comment on column PABYBH_SERIAL.EXTFLD4 is
'�����ֶ�4';

--==============================================================
-- Index: K_PABYBH_SERIAL_1
--==============================================================
create unique index K_PABYBH_SERIAL_1 on PABYBH_SERIAL (
   REQSERIALNO          ASC
);

--==============================================================
-- Index: K_PABYBH_SERIAL_2
--==============================================================
create unique index K_PABYBH_SERIAL_2 on PABYBH_SERIAL (
   WORKDATE             ASC,
   WORKSERIALNO         ASC
);

--==============================================================
-- Index: K_PABYBH_SERIAL_3
--==============================================================
create index K_PABYBH_SERIAL_3 on PABYBH_SERIAL (
   WORKDATE             ASC,
   COBANKNO             ASC,
   SVRCODE              ASC,
   TRANSCODE            ASC
);

--==============================================================
-- Table: PABYBH_SERIAL_HIS
--==============================================================
create table PABYBH_SERIAL_HIS (
   TRANSDATE            VARCHAR(8)             not null,
   TRANSSERIALNO        VARCHAR(40)            not null,
   ORITRANSDATE         VARCHAR(8),
   ORITRANSSERIALNO     VARCHAR(40),
   TRANSTIME            VARCHAR(8)             not null,
   WORKDATE             VARCHAR(8)             not null,
   WORKSERIALNO         VARCHAR(40)            not null,
   REQDATE              VARCHAR(8)             not null,
   REQSERIALNO          VARCHAR(40)            not null,
   CLUSTERNODENAME      VARCHAR(30),
   CLUSTERNODEIP        VARCHAR(20),
   COBANKNO             VARCHAR(12)            not null,
   TRANSORG             VARCHAR(10),
   TRANSOPER            VARCHAR(10),
   AUTHORG              VARCHAR(10),
   AUTHOPER             VARCHAR(10),
   CNLTYPE              VARCHAR(5),
   TERMEQUINO           VARCHAR(20),
   TRANSCODE            VARCHAR(12),
   TRANSCODE1           VARCHAR(1),
   CUACOUNTYPE          VARCHAR(1),
   TRANSNAME            VARCHAR(100),
   CAPITALTYPE          VARCHAR(1),
   SVRCODE              VARCHAR(10),
   CUSTNAME             VARCHAR(80),
   CUSTTYPE             VARCHAR(2),
   ACCTNO               VARCHAR(32),
   ORIACCTNO            VARCHAR(32),
   ACCTNO2              VARCHAR(32),
   STOCKCODE            VARCHAR(8),
   CAPITALACCTNO        VARCHAR(32),
   TRANSAMT             DECIMAL(16,2),
   ORITRANSAMT          DECIMAL(16,2),
   AMT2                 DECIMAL(16,2),
   AMT3                 DECIMAL(16,2),
   CURR                 VARCHAR(3),
   CASHFLAG             VARCHAR(1),
   IEPSVRCODE           VARCHAR(8),
   IEPTRANSCODE         VARCHAR(16),
   IEPBSIDATE           VARCHAR(8),
   IEPTRADATE           VARCHAR(8),
   IEPSERIALNO          VARCHAR(32),
   ORIIEPBSIDATE        VARCHAR(8),
   ORIIEPSERIALNO       VARCHAR(32),
   IEPRESPCODE          VARCHAR(12),
   IEPRESPMSG           VARCHAR(120),
   HOSTBSIDATE          VARCHAR(8),
   HOSTSERIALNO         VARCHAR(32),
   HOSTTRANSCODE        VARCHAR(16),
   HOSTRESPCODE         VARCHAR(12),
   HOSTRESPMSG          VARCHAR(120),
   RESPCODE             VARCHAR(10),
   RESPMSG              VARCHAR(120),
   IEPSTAT              VARCHAR(1),
   HOSTSTAT             VARCHAR(1),
   STAT                 VARCHAR(1),
   ORISTAT              VARCHAR(1),
   CERTTYPE             VARCHAR(2),
   CERTNO               VARCHAR(32),
   PHONE                VARCHAR(20),
   AGENTNAME            VARCHAR(80),
   AGENTCERTY           VARCHAR(2),
   AGENTCERNO           VARCHAR(32),
   AGENTPHONE           VARCHAR(20),
   CHKFLAG              VARCHAR(1),
   MEMO                 VARCHAR(128),
   EXTFLD1              VARCHAR(64),
   EXTFLD2              VARCHAR(64),
   EXTFLD3              VARCHAR(128),
   EXTFLD4              VARCHAR(128),
   constraint PK_PABYBH_SERIAL_HIS primary key (TRANSDATE, 
TRANSSERIALNO)
)
IN GAPS_DATA INDEX IN GAPS_INDEX;

comment on table PABYBH_SERIAL_HIS is
'������ˮ��';

comment on column PABYBH_SERIAL_HIS.TRANSDATE is
'��������';

comment on column PABYBH_SERIAL_HIS.TRANSSERIALNO is
'������ˮ��';

comment on column PABYBH_SERIAL_HIS.ORITRANSDATE is
'ԭ��������';

comment on column PABYBH_SERIAL_HIS.ORITRANSSERIALNO is
'ԭ������ˮ��';

comment on column PABYBH_SERIAL_HIS.TRANSTIME is
'����ʱ��';

comment on column PABYBH_SERIAL_HIS.WORKDATE is
'ҵ������';

comment on column PABYBH_SERIAL_HIS.WORKSERIALNO is
'ҵ����ˮ��';

comment on column PABYBH_SERIAL_HIS.REQDATE is
'��������';

comment on column PABYBH_SERIAL_HIS.REQSERIALNO is
'������ˮ�� Y-���ķ��� G-���ڹ��淢�� T-����̨����';

comment on column PABYBH_SERIAL_HIS.CLUSTERNODENAME is
'��Ⱥ����������';

comment on column PABYBH_SERIAL_HIS.CLUSTERNODEIP is
'��Ⱥ������IP';

comment on column PABYBH_SERIAL_HIS.COBANKNO is
'�����к�';

comment on column PABYBH_SERIAL_HIS.TRANSORG is
'���׻���';

comment on column PABYBH_SERIAL_HIS.TRANSOPER is
'���׹�Ա';

comment on column PABYBH_SERIAL_HIS.AUTHORG is
'��Ȩ����';

comment on column PABYBH_SERIAL_HIS.AUTHOPER is
'��Ȩ��Ա';

comment on column PABYBH_SERIAL_HIS.CNLTYPE is
'�������� 403-ƽ������ 200-����̨ 201-����';

comment on column PABYBH_SERIAL_HIS.TERMEQUINO is
'�ն��豸���';

comment on column PABYBH_SERIAL_HIS.TRANSCODE is
'���״���';

comment on column PABYBH_SERIAL_HIS.TRANSCODE1 is
'���ӽ��״���  944302-��0 ���� 1 ��� 2���������� 3 ���򹤱��ѣ�
944316-�����˲��㣩';

comment on column PABYBH_SERIAL_HIS.CUACOUNTYPE is
'�����˱�־ 0-���� 1-����';

comment on column PABYBH_SERIAL_HIS.TRANSNAME is
'��������';

comment on column PABYBH_SERIAL_HIS.CAPITALTYPE is
'�ʽ�����,0 ---ת��1--- ת��';

comment on column PABYBH_SERIAL_HIS.CUSTNAME is
'�ͻ�����';

comment on column PABYBH_SERIAL_HIS.CUSTTYPE is
'�ͻ����� 00-���� 01-����';

comment on column PABYBH_SERIAL_HIS.ACCTNO is
'�����˺�';

comment on column PABYBH_SERIAL_HIS.ORIACCTNO is
'�������Ķ��˱���ԭ�����˺�';

comment on column PABYBH_SERIAL_HIS.ACCTNO2 is
'�ʺ�2   �������˻�';

comment on column PABYBH_SERIAL_HIS.STOCKCODE is
'ȯ�̴���';

comment on column PABYBH_SERIAL_HIS.CAPITALACCTNO is
'�ʽ��ʺ�';

comment on column PABYBH_SERIAL_HIS.TRANSAMT is
'���׽��';

comment on column PABYBH_SERIAL_HIS.ORITRANSAMT is
'�������Ķ��˱���ԭ���׽��';

comment on column PABYBH_SERIAL_HIS.AMT2 is
'���2';

comment on column PABYBH_SERIAL_HIS.AMT3 is
'���3';

comment on column PABYBH_SERIAL_HIS.CURR is
'����';

comment on column PABYBH_SERIAL_HIS.CASHFLAG is
'�����ʶ';

comment on column PABYBH_SERIAL_HIS.IEPSVRCODE is
'��Eͨ�������';

comment on column PABYBH_SERIAL_HIS.IEPTRANSCODE is
'��Eͨ���״���';

comment on column PABYBH_SERIAL_HIS.IEPBSIDATE is
'��Eͨҵ������';

comment on column PABYBH_SERIAL_HIS.IEPTRADATE is
'��Eͨ��������';

comment on column PABYBH_SERIAL_HIS.IEPSERIALNO is
'��Eͨ��ˮ��';

comment on column PABYBH_SERIAL_HIS.ORIIEPBSIDATE is
'ԭ��Eͨҵ������';

comment on column PABYBH_SERIAL_HIS.ORIIEPSERIALNO is
'ԭ��Eͨ��ˮ��';

comment on column PABYBH_SERIAL_HIS.IEPRESPCODE is
'��Eͨ��Ӧ����';

comment on column PABYBH_SERIAL_HIS.IEPRESPMSG is
'��Eͨ��Ӧ��Ϣ';

comment on column PABYBH_SERIAL_HIS.HOSTBSIDATE is
'������������';

comment on column PABYBH_SERIAL_HIS.HOSTSERIALNO is
'������ˮ��';

comment on column PABYBH_SERIAL_HIS.HOSTTRANSCODE is
'�������״���';

comment on column PABYBH_SERIAL_HIS.HOSTRESPCODE is
'������Ӧ����';

comment on column PABYBH_SERIAL_HIS.HOSTRESPMSG is
'������Ӧ��Ϣ';

comment on column PABYBH_SERIAL_HIS.RESPCODE is
'��Ӧ��';

comment on column PABYBH_SERIAL_HIS.RESPMSG is
'��Ӧ��Ϣ';

comment on column PABYBH_SERIAL_HIS.IEPSTAT is
'���Ľ���״̬''0�ɹ� 1ʧ�� 6״̬δ֪ 7������ 8������ 9��ʼ''';

comment on column PABYBH_SERIAL_HIS.HOSTSTAT is
'���Ľ���״̬''0�ɹ� 1ʧ�� 6״̬δ֪ 7������ 8������ 9��ʼ''';

comment on column PABYBH_SERIAL_HIS.STAT is
'����״̬''0�ɹ� 1ʧ�� 6״̬δ֪ 7������ 8������ 9��ʼ''';

comment on column PABYBH_SERIAL_HIS.ORISTAT is
'�������Ķ��˱���ԭ����״̬ ''0�ɹ� 1ʧ�� 6״̬δ֪ 7������ 8������ 9��ʼ XԴ��ˮ������''';

comment on column PABYBH_SERIAL_HIS.CERTTYPE is
'֤������';

comment on column PABYBH_SERIAL_HIS.CERTNO is
'֤������';

comment on column PABYBH_SERIAL_HIS.CHKFLAG is
'���˱�־,0-δ����1-�Ѷ�ƽ2-ƽ����3-���Ķ� X-ƽ���Ѷ��� ';

comment on column PABYBH_SERIAL_HIS.MEMO is
'��ע';

comment on column PABYBH_SERIAL_HIS.EXTFLD1 is
'�����ֶ�1 ';

comment on column PABYBH_SERIAL_HIS.EXTFLD2 is
'�����ֶ�2';

comment on column PABYBH_SERIAL_HIS.EXTFLD3 is
'�����ֶ�3';

comment on column PABYBH_SERIAL_HIS.EXTFLD4 is
'�����ֶ�4';

--==============================================================
-- Index: K_PABYBH_SERIAL_4
--==============================================================
create unique index K_PABYBH_SERIAL_4 on PABYBH_SERIAL_HIS (
   REQSERIALNO          ASC
);

--==============================================================
-- Index: K_PABYBH_SERIAL_5
--==============================================================
create unique index K_PABYBH_SERIAL_5 on PABYBH_SERIAL_HIS (
   WORKDATE             ASC,
   WORKSERIALNO         ASC
);

--==============================================================
-- Index: K_PABYBH_SERIAL_6
--==============================================================
create index K_PABYBH_SERIAL_6 on PABYBH_SERIAL_HIS (
   WORKDATE             ASC,
   COBANKNO             ASC,
   SVRCODE              ASC,
   TRANSCODE            ASC
);

--==============================================================
-- Table: PABYBH_SIGN
--==============================================================
create table PABYBH_SIGN (
   PROTOCOLNO           VARCHAR(14)            not null,
   SIGNDATE             VARCHAR(8)             not null,
   SIGNTIME             VARCHAR(6),
   COBANKNO             VARCHAR(12)            not null,
   ACCTNO               VARCHAR(32)            not null,
   OLDACCTNO            VARCHAR(32),
   CERTTYPE             VARCHAR(2)             not null,
   CERTNO               VARCHAR(32)            not null,
   CUSTTYPE             VARCHAR(2),
   CUSTNAME             VARCHAR(120),
   STOCKCODE            VARCHAR(8)             not null,
   CAPITALACCTNO        VARCHAR(30)            not null,
   SVRCODE              VARCHAR(6)             not null,
   CURR                 VARCHAR(3),
   CUSTMANAGERID        VARCHAR(20),
   CUSTMANAGERNAME      VARCHAR(20),
   OPENORG              VARCHAR(10),
   BUSITYPE             VARCHAR(2)             not null,
   STAT                 VARCHAR(1),
   HOSTSTAT             VARCHAR(1),
   HOSTDATE             VARCHAR(8),
   HOSTSERIALNO         VARCHAR(40),
   CHKFLAG              VARCHAR(1),
   UPDATEDATE           VARCHAR(8),
   UPDATETIME           VARCHAR(6),
   TRANSORG             VARCHAR(10),
   TRANSOPER            VARCHAR(20),
   AGENTNAME            VARCHAR(80),
   AGENTCERTY           VARCHAR(2),
   AGENTCERNO           VARCHAR(32),
   AGENTPHONE           VARCHAR(20),
   MEMO                 VARCHAR(40),
   EXTFLD1              VARCHAR(32),
   EXTFLD2              VARCHAR(32),
   EXTFLD3              VARCHAR(64),
   EXTFLD4              VARCHAR(64),
   EXTFLD5              VARCHAR(64),
   EXTFLD6              VARCHAR(64),
   constraint PK_PABYBH_SIGN primary key (STOCKCODE, CAPITALACCTNO, 
BUSITYPE)
)
IN GAPS_DATA INDEX IN GAPS_INDEX;

comment on table PABYBH_SIGN is
'ǩԼ��';

comment on column PABYBH_SIGN.PROTOCOLNO is
'Э���';

comment on column PABYBH_SIGN.SIGNDATE is
'ǩԼ����';

comment on column PABYBH_SIGN.SIGNTIME is
'ǩԼʱ��';

comment on column PABYBH_SIGN.COBANKNO is
'�����к�';

comment on column PABYBH_SIGN.ACCTNO is
'�����˺�';

comment on column PABYBH_SIGN.OLDACCTNO is
'�������˺�';

comment on column PABYBH_SIGN.CERTTYPE is
'֤������';

comment on column PABYBH_SIGN.CERTNO is
'֤������';

comment on column PABYBH_SIGN.CUSTTYPE is
'�ͻ�����00-���� 01-����';

comment on column PABYBH_SIGN.CUSTNAME is
'�ͻ�����';

comment on column PABYBH_SIGN.STOCKCODE is
'ȯ�̴���';

comment on column PABYBH_SIGN.CAPITALACCTNO is
'�ʽ��˺�';

comment on column PABYBH_SIGN.SVRCODE is
'�������0802-�������';

comment on column PABYBH_SIGN.CURR is
'����';

comment on column PABYBH_SIGN.CUSTMANAGERID is
'�ͻ������';

comment on column PABYBH_SIGN.CUSTMANAGERNAME is
'�ͻ�������';

comment on column PABYBH_SIGN.OPENORG is
'��������';

comment on column PABYBH_SIGN.BUSITYPE is
'ҵ������';

comment on column PABYBH_SIGN.STAT is
'ǩԼ״̬''9-��У��1-ǩԼ2-��Լ3-�ϳ�''';

comment on column PABYBH_SIGN.HOSTSTAT is
'����״̬ ''9-��У��1-ǩԼ2-��Լ��';

comment on column PABYBH_SIGN.HOSTDATE is
'��������';

comment on column PABYBH_SIGN.HOSTSERIALNO is
'������ˮ��';

comment on column PABYBH_SIGN.CHKFLAG is
'���˱�־''0-δ����1-�Ѷ���''';

comment on column PABYBH_SIGN.UPDATEDATE is
'�������� ';

comment on column PABYBH_SIGN.UPDATETIME is
'����ʱ��';

comment on column PABYBH_SIGN.TRANSORG is
'���׻���';

comment on column PABYBH_SIGN.TRANSOPER is
'���׹�Ա';

comment on column PABYBH_SIGN.AGENTNAME is
'����������';

comment on column PABYBH_SIGN.AGENTCERTY is
'֤������';

comment on column PABYBH_SIGN.AGENTCERNO is
'֤������';

comment on column PABYBH_SIGN.AGENTPHONE is
'�������ֻ���';

comment on column PABYBH_SIGN.MEMO is
'��ע';

comment on column PABYBH_SIGN.EXTFLD1 is
'�����ֶ�1';

comment on column PABYBH_SIGN.EXTFLD2 is
'�����ֶ�2';

comment on column PABYBH_SIGN.EXTFLD3 is
'�����ֶ�3';

comment on column PABYBH_SIGN.EXTFLD4 is
'�����ֶ�4';

comment on column PABYBH_SIGN.EXTFLD5 is
'�����ֶ�5';

comment on column PABYBH_SIGN.EXTFLD6 is
'�����ֶ�6';

--==============================================================
-- Index: K_PABYBH_SIGN_1
--==============================================================
create unique index K_PABYBH_SIGN_1 on PABYBH_SIGN (
   PROTOCOLNO           ASC
);

--==============================================================
-- Table: PABYBH_SVRINFO
--==============================================================
create table PABYBH_SVRINFO (
   COBANKNO             VARCHAR(12)            not null,
   SVRCODE              VARCHAR(6)             not null,
   SVRNAME              VARCHAR(100)           not null,
   WORKTIME             VARCHAR(32),
   SVRSTATUS            VARCHAR(1)             not null,
   EXTFLD1              VARCHAR(128),
   EXTFLD2              VARCHAR(128),
   EXTFLD3              VARCHAR(128),
   constraint PK_PABYBH_SVRINFO primary key (COBANKNO, SVRCODE)
)
IN GAPS_DATA INDEX IN GAPS_INDEX;

comment on table PABYBH_SVRINFO is
'ҵ����Ϣ';

comment on column PABYBH_SVRINFO.COBANKNO is
'�����б��';

comment on column PABYBH_SVRINFO.SVRCODE is
'�������';

comment on column PABYBH_SVRINFO.SVRNAME is
'��������';

comment on column PABYBH_SVRINFO.WORKTIME is
'ҵ��չʱ���';

comment on column PABYBH_SVRINFO.SVRSTATUS is
'����״̬';

comment on column PABYBH_SVRINFO.EXTFLD1 is
'�����ֶ�1';

comment on column PABYBH_SVRINFO.EXTFLD2 is
'�����ֶ�2';

comment on column PABYBH_SVRINFO.EXTFLD3 is
'�����ֶ�3';


--==============================================================
-- Table: PABYBH_TRADER
--==============================================================
create table PABYBH_TRADER (
   STOCKCODE            VARCHAR(8)             not null,
   STOCKNAME            VARCHAR(120),
   ONESTEP              VARCHAR(1),
   ONLINETIME           VARCHAR(8),
   EXTFLD1              VARCHAR(32),
   EXTFLD2              VARCHAR(64),
   EXTFLD3              VARCHAR(64),
   constraint PK_PABYBH_TRADER primary key (STOCKCODE)
)
IN GAPS_DATA INDEX IN GAPS_INDEX;

comment on table PABYBH_TRADER is
'ȯ�̴�����Ϣ';

comment on column PABYBH_TRADER.STOCKCODE is
'ȯ�̴���';

comment on column PABYBH_TRADER.STOCKNAME is
'ȯ������';

comment on column PABYBH_TRADER.ONESTEP is
'�Ƿ�һ��ʽǩԼ 1-�� 0-��';

comment on column PABYBH_TRADER.ONLINETIME is
'����ʱ��';

comment on column PABYBH_TRADER.EXTFLD1 is
'��չ�ֶ�1';

comment on column PABYBH_TRADER.EXTFLD2 is
'��չ�ֶ�2';

comment on column PABYBH_TRADER.EXTFLD3 is
'��չ�ֶ�3';
