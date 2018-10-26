drop table BATCH_AUDITINGCFG;

drop table BATCH_AUDITINGFUNC;

drop table BATCH_AUDITINGPARA;

drop table BATCH_AUDITINGREG;

drop table BATCH_CLI_PARA;

drop table BATCH_CLI_USER;

drop table BATCH_ENCRYPTREG;

drop table BATCH_FILECOLUMN;

drop index K_BAT_FILEMAP_1;
drop index K_BAT_FILEMAP_2;
drop index K_BAT_FILEMAP_3;
drop index K_BAT_FILEMAP_4;
drop table BATCH_FILEMAP;

drop table BATCH_FILESORT;

drop table BATCH_FILETYPE;

drop table BATCH_FLOWCFG;

drop index K_BAT_PLRW_2;

drop table BATCH_HIS_PLRW;

drop index K_BAT_WBWJDJ_2;

drop table BATCH_HIS_WBWJDJ;

drop table BATCH_MAPINFO;

drop table BATCH_MAPRESP;

drop index K_BAT_PLRW_1;
drop index K_BAT_PLRW_3;
drop index K_BAT_PLRW_4;
drop table BATCH_PLRW;


drop index K_BAT_PLRWBD_1;
drop table BATCH_PLRWBD;

drop table BATCH_RUNCTRL;

drop table BATCH_STEPATTRIB;

drop table BATCH_STEPCFG;

drop index K_BAT_WBWJDJ_1;
drop index K_BAT_WBWJDJ_3;
drop index K_BAT_WBWJDJ_4;
drop table BATCH_WBWJDJ;

--==============================================================
-- Table: BATCH_AUDITINGCFG
--==============================================================
create table BATCH_AUDITINGCFG
(
   AUDITINGID           VARCHAR(32)            not null,
   AUDITINGSN           INTEGER                not null,
   FUNCPARASN           INTEGER                not null,
   FUNCPARA             VARCHAR(128),
   SNOTE                VARCHAR(32),
   constraint PK_BATCH_AUDITINGCFG primary key (AUDITINGID, AUDITINGSN, FUNCPARASN)
);

--==============================================================
-- Table: BATCH_AUDITINGFUNC
--==============================================================
create table BATCH_AUDITINGFUNC
(
   AUDITINGID           VARCHAR(32)            not null,
   AUDITINGSN           INTEGER                not null,
   FUNCID               VARCHAR(32),
   SHSBBZ               VARCHAR(1),
   SNOTE                VARCHAR(32),
   WHJG                 VARCHAR(16),
   WHGY                 VARCHAR(16),
   WHSJ                 VARCHAR(14),
   constraint PK_BATCH_AUDITINGFUNC primary key (AUDITINGID, AUDITINGSN)
);

comment on column BATCH_AUDITINGFUNC.SHSBBZ is
'0�������ʧ�� 1�������ʧ����ϸ ��Ĭ��1 ������';

--==============================================================
-- Table: BATCH_AUDITINGPARA
--==============================================================
create table BATCH_AUDITINGPARA
(
   FUNCID               VARCHAR(32)            not null,
   PARASN               INTEGER                not null,
   PARAVALUE            VARCHAR(60),
   SNOTE                VARCHAR(32),
   constraint PK_BATCH_AUDITINGPARA primary key (FUNCID, PARASN)
);

--==============================================================
-- Table: BATCH_AUDITINGREG
--==============================================================
create table BATCH_AUDITINGREG
(
   FUNCID               VARCHAR(32)            not null,
   FUNCNAME             VARCHAR(32),
   FUNCRUN              VARCHAR(32),
   FUNCFILE             VARCHAR(32),
   SNOTE                VARCHAR(32),
   WHJG                 VARCHAR(16),
   WHGY                 VARCHAR(16),
   WHSJ                 VARCHAR(14),
   constraint PK_BATCH_AUDITINGREG primary key (FUNCID)
);

--==============================================================
-- Table: BATCH_CLI_PARA
--==============================================================
create table BATCH_CLI_PARA
(
   SJBCTS               INTEGER,
   SJBFLJ               VARCHAR(128),
   SNOTE                VARCHAR(120)
);

--==============================================================
-- Table: BATCH_CLI_USER
--==============================================================
create table BATCH_CLI_USER (
   CONTRACT_NO          VARCHAR(32)                    not null,
   USER_ID              VARCHAR(32)                    not null,
   USER_NAME            VARCHAR(80),
   CONTACT              VARCHAR(32),
   PHONE                VARCHAR(16),
   MOBILE               VARCHAR(12),
   EMAIL                VARCHAR(50),
   PTRQ                 VARCHAR(8),
   TRAN_TIME            VARCHAR(6),
   PTLS                 VARCHAR(16),
   BRANCH               VARCHAR(16),
   OPER                 VARCHAR(16),
   ACCT_MANAGER         VARCHAR(32),
   ACCT_NAME            VARCHAR(80),
   ACCT_NO              VARCHAR(32),
   STATUS               CHAR(1),
   SEND_FLAG            INTEGER,
   KEY                  VARCHAR(32),
   EXTFLD1              VARCHAR(16),
   EXTFLD2              VARCHAR(32),
   EXTFLD3              VARCHAR(50),
   EXTFLD4              VARCHAR(64),
   constraint PK_BATCH_CLI_USER primary key (CONTRACT_NO),
   constraint AK_KEY_2_BATCH_CL unique (USER_ID)
);

comment on column BATCH_CLI_USER.STATUS is
'0  ����';

comment on column BATCH_CLI_USER.SEND_FLAG is
'0 δ���� n ����n��';

--==============================================================
-- Table: BATCH_ENCRYPTREG
--==============================================================
create table BATCH_ENCRYPTREG
(
   ENCRYPTID            VARCHAR(50)            not null,
   ENCRYPTMODE          VARCHAR(1),
   ENCRYPTTYPE          VARCHAR(1),
   SVRNAME              VARCHAR(128),
   FILENAME             VARCHAR(128),
   FUNCNAME             VARCHAR(128),
   ENCRYNOTE            VARCHAR(120),
   WHJG                 VARCHAR(16),
   WHGY                 VARCHAR(16),
   WHSJ                 VARCHAR(14),
   constraint PK_BATCH_ENCRYPTREG primary key (ENCRYPTID)
);

comment on column BATCH_ENCRYPTREG.ENCRYPTMODE is
'0���� 1����';

comment on column BATCH_ENCRYPTREG.ENCRYPTTYPE is
'1���� 2Զ��';

comment on column BATCH_ENCRYPTREG.SVRNAME is
'Զ��ʱ�ķ�����';

comment on column BATCH_ENCRYPTREG.FILENAME is
'����ʱ��';

comment on column BATCH_ENCRYPTREG.FUNCNAME is
'����ʱ��';

--==============================================================
-- Table: BATCH_FILECOLUMN
--==============================================================
create table BATCH_FILECOLUMN
(
   FILEID               VARCHAR(32)            not null,
   FILECLASSSN          INTEGER                not null,
   COLUMNSN             INTEGER                not null,
   COLUMNID             VARCHAR(32),
   ISID                 VARCHAR(1),
   COLUMNNAME           VARCHAR(40),
   LSX                  VARCHAR(1),
   OFFSET               INTEGER,
   COLUMNLEN            INTEGER,
   IPRECISION           INTEGER,
   IZOOM                INTEGER,
   REGULAR              VARCHAR(1),
   IFILLER              INTEGER,
   FLDREF               VARCHAR(32),
   SNOTE                VARCHAR(32),
   EXTFLD1              VARCHAR(60),
   constraint PK_BATCH_FILECOLUMN primary key (FILEID, FILECLASSSN, COLUMNSN)
);

comment on column BATCH_FILECOLUMN.ISID is
'0��1��';

comment on column BATCH_FILECOLUMN.LSX is
' 0-���׽���ۼ�
 1-���׽���ۼ�
 4-ֵ����
 5-ֵ��ȡ
 6-���ܼ�¼����-���ܱ���
 7-���ܼ�¼����-���ܽ��
 8-�̻����κ�
';

comment on column BATCH_FILECOLUMN.REGULAR is
'���뷽ʽ����L �����,R �Ҷ��룩ȱʡΪL';

comment on column BATCH_FILECOLUMN.IFILLER is
'������ASCII����';

--==============================================================
-- Table: BATCH_FILEMAP
--==============================================================
create table BATCH_FILEMAP
(
   MAPID                VARCHAR(32)            not null,
   FLXH                 INTEGER                not null,
   COLUMNSN             INTEGER                not null,
   COLUMNID             VARCHAR(16),
   LYLX                 VARCHAR(1),
   LYWZ                 VARCHAR(60),
   ZJSZWZ               INTEGER,
   ZJJGWZ               INTEGER,
   THGXBZ               VARCHAR(1),
   HPWJWZ               INTEGER,
   constraint PK_BATCH_FILEMAP primary key (MAPID, FLXH, COLUMNSN)
);

comment on column BATCH_FILEMAP.COLUMNID is
'��Ӧҵ���ṹע����Ϣ���������';

comment on column BATCH_FILEMAP.LYLX is
'1�������ļ���ȡ��2��xml��ȡ��3���ļ����4����ˮ��ţ� 5������ 6���ۺ�ǰ����ˮ��';

comment on column BATCH_FILEMAP.LYWZ is
'������Դ������';

comment on column BATCH_FILEMAP.ZJSZWZ is
'���������ļ������';

comment on column BATCH_FILEMAP.ZJJGWZ is
'��������ļ������';

comment on column BATCH_FILEMAP.THGXBZ is
'1�������� 2 ��������';

comment on column BATCH_FILEMAP.HPWJWZ is
'�����ļ������';

--==============================================================
-- Index: K_BAT_FILEMAP_1
--==============================================================
create index K_BAT_FILEMAP_1 on BATCH_FILEMAP (
   MAPID                ASC,
   COLUMNSN             ASC
);

--==============================================================--
-- Index: K_BAT_FILEMAP_2                                       --
--==============================================================--
create index K_BAT_FILEMAP_2 on BATCH_FILEMAP (
   MAPID ASC,
   ZJSZWZ ASC
);

--==============================================================--
-- Index: K_BAT_FILEMAP_3                                       --
--==============================================================--
create index K_BAT_FILEMAP_3 on BATCH_FILEMAP (
   MAPID ASC,
   THGXBZ ASC,
   COLUMNSN ASC
);

--==============================================================--
-- Index: K_BAT_FILEMAP_4                                       --
--==============================================================--
create index K_BAT_FILEMAP_4 on BATCH_FILEMAP (
   MAPID ASC,
   HPWJWZ ASC
);

--==============================================================
-- Table: BATCH_FILESORT
--==============================================================
create table BATCH_FILESORT
(
   FILEID               VARCHAR(32)            not null,
   FILECLASSSN          INTEGER                not null,
   CLASSNAME            VARCHAR(40),
   CLASSTYPE            VARCHAR(1),
   HIGHERUPSN           INTEGER,
   POSITIONFLAG         VARCHAR(1),
   CLASSPOSITION        VARCHAR(32),
   COLUMNNO             INTEGER,
   ROWSPRTR             VARCHAR(32),
   SPRTRATTRIB          VARCHAR(1),
   COLUMNFLAG           VARCHAR(1),
   COLUMNSPRTR          VARCHAR(32),
   EXTFLD1              VARCHAR(60),
   constraint PK_BATCH_FILESORT primary key (FILEID, FILECLASSSN)
);

comment on column BATCH_FILESORT.CLASSTYPE is
'1�����ܣ�2����ϸ';

comment on column BATCH_FILESORT.POSITIONFLAG is
'����';

comment on column BATCH_FILESORT.CLASSPOSITION is
'����';

comment on column BATCH_FILESORT.ROWSPRTR is
'����';

comment on column BATCH_FILESORT.SPRTRATTRIB is
'����';

comment on column BATCH_FILESORT.COLUMNFLAG is
'1����2�ָ�';

--==============================================================
-- Table: BATCH_FILETYPE
--==============================================================
create table BATCH_FILETYPE
(
   FILEID               VARCHAR(32)            not null,
   FILEIDNOTE           VARCHAR(40),
   FILETYPE             VARCHAR(1),
   FILEFMT              VARCHAR(2),
   CODEFMT              VARCHAR(1)                     default '0',
   EXTFLD1              VARCHAR(32),
   WHJG                 VARCHAR(16),
   WHGY                 VARCHAR(16),
   WHSJ                 VARCHAR(14),
   constraint PK_BATCH_FILETYPE primary key (FILEID)
);

comment on column BATCH_FILETYPE.FILETYPE is
'0- txt 1-DBF 2-xls 3-xlsx 4-dbf  Ĭ�� 0';

comment on column BATCH_FILETYPE.FILEFMT is
'01  ����ϸ
02  ���ܣ�����ϸ
03  ����ϸ������
04  ���ܣ�����ϸ������
';

comment on column BATCH_FILETYPE.CODEFMT is
'�����ʽ 0-ascii 1-utf-8 2-base64';


--==============================================================
-- Table: BATCH_FLOWCFG
--==============================================================
create table BATCH_FLOWCFG
(
   FLOWID               VARCHAR(32)            not null,
   FLOWNAME             VARCHAR(40),
   FLOWSN               INTEGER                not null,
   STEPID               VARCHAR(32),
   STEPSN               INTEGER,
   STEPNAME             VARCHAR(32),
   EXTFLD1              VARCHAR(40),
   EXTFLD2              VARCHAR(40),
   WHJG                 VARCHAR(16),
   WHGY                 VARCHAR(16),
   WHSJ                 VARCHAR(14),
   constraint PK_BATCH_FLOWCFG primary key (FLOWID, FLOWSN)
);

--==============================================================
-- Table: BATCH_HIS_PLRW
--==============================================================
create table BATCH_HIS_PLRW
(
   PKRQ                 VARCHAR(8)             not null,
   PTPCH                VARCHAR(8)             not null,
   TASKPRI              VARCHAR(3),
   SHPCH                VARCHAR(32),
   ZJPCH                VARCHAR(32),
   YWBH                 VARCHAR(16)            not null,
   DWBH                 VARCHAR(16),
   TJRQ                 VARCHAR(8),
   TJSJ                 VARCHAR(6),
   CLRQ                 VARCHAR(8),
   CLSJ                 VARCHAR(6),
   ZJE                  NUMERIC(16,2),
   ZBS                  INTEGER,
   SJZJE                NUMERIC(16,2),
   SJZBS                INTEGER,
   CGZJE                NUMERIC(16,2),
   CGZBS                INTEGER,
   SBZJE                NUMERIC(16,2),
   SBZBS                INTEGER,
   SXFJE                NUMERIC(16,2),
   XKHBS                INTEGER,
   XKHJE                NUMERIC(16,2),
   LPWJM                VARCHAR(60),
   SCZJWJM              VARCHAR(60),
   ZJHFWJM              VARCHAR(60),
   SHCGWJM              VARCHAR(60),
   SHSBWJM              VARCHAR(60),
   DQBD                 VARCHAR(2),
   FZBD                 VARCHAR(2),
   BDZT                 VARCHAR(1),
   RWZT                 VARCHAR(1),
   XYDM                 VARCHAR(8),
   XYXX                 VARCHAR(60),
   BQTPKRQ              VARCHAR(8),
   BQTPTPCH             VARCHAR(8),
   QTBZ                 VARCHAR(1)                 default '0',
   QTPKRQ               VARCHAR(8),
   QTPTPCH              VARCHAR(8),
   constraint PK_BATCH_HIS_PLRW primary key (PKRQ, PTPCH)
);

comment on table BATCH_HIS_PLRW is
'����ҵ��������ʷ��';

comment on column BATCH_HIS_PLRW.PKRQ is
'��������(ƽ̨����)';

comment on column BATCH_HIS_PLRW.PTPCH is
'ƽ̨���κ�';

comment on column BATCH_HIS_PLRW.TASKPRI is
'�������ȼ�';

comment on column BATCH_HIS_PLRW.SHPCH is
'�̻����κ�';

comment on column BATCH_HIS_PLRW.ZJPCH is
'�������κ�';

comment on column BATCH_HIS_PLRW.YWBH is
'ҵ����';

comment on column BATCH_HIS_PLRW.DWBH is
'��λ���';

comment on column BATCH_HIS_PLRW.TJRQ is
'��Χ�ύ���������';

comment on column BATCH_HIS_PLRW.TJSJ is
'�ύʱ��';

comment on column BATCH_HIS_PLRW.CLRQ is
'�����������';

comment on column BATCH_HIS_PLRW.CLSJ is
'����ʱ��';

comment on column BATCH_HIS_PLRW.ZJE is
'�����ܽ�����';

comment on column BATCH_HIS_PLRW.ZBS is
'�����ܱ���������';

comment on column BATCH_HIS_PLRW.SJZJE is
'ʵ���ܽ��ļ��ڣ�';

comment on column BATCH_HIS_PLRW.SJZBS is
'ʵ���ܱ������ļ��ڣ�';

comment on column BATCH_HIS_PLRW.CGZJE is
'�ɹ��ܽ��';

comment on column BATCH_HIS_PLRW.CGZBS is
'�ɹ��ܱ���';

comment on column BATCH_HIS_PLRW.SBZJE is
'ʧ���ܽ��';

comment on column BATCH_HIS_PLRW.SBZBS is
'ʧ���ܱ���';

comment on column BATCH_HIS_PLRW.SXFJE is
'�����ѽ��';

comment on column BATCH_HIS_PLRW.XKHBS is
'�¿�������';

comment on column BATCH_HIS_PLRW.XKHJE is
'�¿������';

comment on column BATCH_HIS_PLRW.LPWJM is
'�̻������ļ���';

comment on column BATCH_HIS_PLRW.SCZJWJM is
'�ϴ������ļ���';

comment on column BATCH_HIS_PLRW.ZJHFWJM is
'�����ظ��ļ���';

comment on column BATCH_HIS_PLRW.SHCGWJM is
'�ظ��̻��ɹ��ļ����������ļ�����';

comment on column BATCH_HIS_PLRW.SHSBWJM is
'�ظ��̻�ʧ���ļ���';

comment on column BATCH_HIS_PLRW.DQBD is
'�������� 0 ��ȡ���� 1 ������� 2 ����У�� 3 �ύ���� 4�������  5����';

comment on column BATCH_HIS_PLRW.BDZT is
' 0��ֹ 1���� 2�ϵ� 3���� 4�ȴ� 9�ڴ�����  X ���� C���� Z��ֹ';

comment on column BATCH_HIS_PLRW.RWZT is
' 0��ֹ 1���� 2�ϵ� 3���� 4�ȴ� 9�ڴ�����  X ���� C���� Z��ֹ';

comment on column BATCH_HIS_PLRW.XYDM is
'��Ӧ����';

comment on column BATCH_HIS_PLRW.XYXX is
'��Ӧ��Ϣ';

comment on column BATCH_HIS_PLRW.BQTPKRQ is
'��Ƕ����������';

comment on column BATCH_HIS_PLRW.BQTPTPCH is
'��Ƕ��ƽ̨���κ�';

comment on column BATCH_HIS_PLRW.QTBZ is
'Ƕ�ױ�־ 0-��Ƕ�� 1-Ƕ�� 2-��Ƕ�� 3-�ȱ�Ƕ����Ƕ��';

comment on column BATCH_HIS_PLRW.QTPKRQ is
'Ƕ����������';

comment on column BATCH_HIS_PLRW.QTPTPCH is
'Ƕ��ƽ̨���κ�';

--==============================================================
-- Index: K_BAT_PLRW_2
--==============================================================
create index K_BAT_PLRW_2 on BATCH_HIS_PLRW (
   YWBH                 ASC,
   PKRQ                 ASC,
   PTPCH                ASC
);

--==============================================================
-- Table: BATCH_HIS_WBWJDJ
--==============================================================
create table BATCH_HIS_WBWJDJ
(
   DJRQ                 VARCHAR(8)             not null,
   DJLSH                INTEGER                not null,
   DJSJ                 VARCHAR(6),
   YWBH                 VARCHAR(16)            not null,
   DJJG                 VARCHAR(16)            not null,
   DJGY                 VARCHAR(16)            not null,
   SHJG                 VARCHAR(16),
   SHGY                 VARCHAR(16),
   SHPCH                VARCHAR(32),
   PKRQ                 VARCHAR(8),
   PTPCH                VARCHAR(8),
   LPWJLJ               VARCHAR(254),
   LPWJM                VARCHAR(60),
   ZBS                  VARCHAR(8),
   ZJE                  NUMERIC(16,2),
   THREADNO             INTEGER,
   TASKMODE             VARCHAR(1),
   PCZT                 VARCHAR(1),
   SHZT                 VARCHAR(1),
   NOTE                 VARCHAR(128),
   BREAKDATA            CLOB                   not compact not logged,
   EXTFLD1              VARCHAR(40),
   EXTFLD2              VARCHAR(40),
   EXTFLD3              VARCHAR(40),
   constraint PK_BATCH_HIS_WBWJDJ primary key (DJRQ, DJLSH)
);

comment on column BATCH_HIS_WBWJDJ.THREADNO is
'���߼�ѡ��Ĭ��Ϊ1��';

comment on column BATCH_HIS_WBWJDJ.TASKMODE is
'1��������2���ֶ���Ĭ��Ϊ1��';

comment on column BATCH_HIS_WBWJDJ.PCZT is
'1�������ϴ���2��������3�����ڴ���4���ѷ��أ�5������ʧ�ܣ�X������, C:������Z:��ֹ';

comment on column BATCH_HIS_WBWJDJ.SHZT is
'0�����ͨ����1��δ��ˣ�2�����ʧ��';

comment on column BATCH_HIS_WBWJDJ.SHJG is
'��˻���';

comment on column BATCH_HIS_WBWJDJ.SHGY is
'��˹�Ա';

--==============================================================
-- Index: K_BAT_WBWJDJ_2
--==============================================================
create index K_BAT_WBWJDJ_2 on BATCH_HIS_WBWJDJ (
   DJRQ                 ASC,
   SHPCH                ASC
);

--==============================================================
-- Table: BATCH_MAPINFO
--==============================================================
create table BATCH_MAPINFO
(
   MAPID                VARCHAR(32)            not null,
   MAPTYPE              VARCHAR(1)             not null,
   MAPIDNOTE            VARCHAR(40),
   YWBM                 VARCHAR(32),
   LPWJBS               VARCHAR(32),
   HPWJBS               VARCHAR(32),
   TJWJBS               VARCHAR(32),
   THWJBS               VARCHAR(32),
   JLSXZ                INTEGER                default 0,
   ZHBZ                 VARCHAR(1),
   ZHBS                 VARCHAR(32),
   WHJG                 VARCHAR(16),
   WHGY                 VARCHAR(16),
   WHSJ                 VARCHAR(14),
   constraint PK_BATCH_MAPINFO primary key (MAPID)
);

comment on column BATCH_MAPINFO.MAPTYPE is
'0 ��Χ�ļ�ӳ��
1 �����ļ�ӳ��';

comment on column BATCH_MAPINFO.JLSXZ is
'���������ļ�����¼�� Ĭ�� 0  ������';

comment on column BATCH_MAPINFO.ZHBZ is
'0 ת�� 1 ��ת��';

--==============================================================
-- Table: BATCH_MAPRESP
--==============================================================
create table BATCH_MAPRESP
(
   MAPID                VARCHAR(32)            not null,
   NOTE                 VARCHAR(40),
   RESP_S               VARCHAR(10)            not null,
   RESP_D               VARCHAR(20)            not null,
   MSG_D                VARCHAR(40),
   BZ                   VARCHAR(1),
   WHJG                 VARCHAR(16),
   WHGY                 VARCHAR(16),
   WHSJ                 VARCHAR(14),
   constraint PK_BATCH_MAPRESP primary key (MAPID, RESP_S)
);

comment on table BATCH_MAPRESP is
'��Ӧ����Դӳ��';

comment on column BATCH_MAPRESP.BZ is
'Ĭ��ת����ʶ
0 ��
1 ��
Ĭ�� 1
һ����Ӧ����Դ�����һ�� Ĭ��ת��';

--==============================================================
-- Table: BATCH_PLRW
--==============================================================
create table BATCH_PLRW
(
   PKRQ                 VARCHAR(8)             not null,
   PTPCH                VARCHAR(8)             not null,
   TASKPRI              VARCHAR(3),
   SHPCH                VARCHAR(32),
   ZJPCH                VARCHAR(32),
   YWBH                 VARCHAR(16)            not null,
   DWBH                 VARCHAR(16),
   TJRQ                 VARCHAR(8),
   TJSJ                 VARCHAR(6),
   CLRQ                 VARCHAR(8),
   CLSJ                 VARCHAR(6),
   ZJE                  NUMERIC(16,2),
   ZBS                  INTEGER,
   SJZJE                NUMERIC(16,2),
   SJZBS                INTEGER,
   CGZJE                NUMERIC(16,2),
   CGZBS                INTEGER,
   SBZJE                NUMERIC(16,2),
   SBZBS                INTEGER,
   SXFJE                NUMERIC(16,2),
   XKHBS                INTEGER,
   XKHJE                NUMERIC(16,2),
   LPWJM                VARCHAR(60),
   SCZJWJM              VARCHAR(60),
   ZJHFWJM              VARCHAR(60),
   SHCGWJM              VARCHAR(60),
   SHSBWJM              VARCHAR(60),
   DQBD                 VARCHAR(2),
   FZBD                 VARCHAR(2)                 default '00',
   BDZT                 VARCHAR(1),
   RWZT                 VARCHAR(1),
   XYDM                 VARCHAR(8),
   XYXX                 VARCHAR(120),
   BQTPKRQ              VARCHAR(8),
   BQTPTPCH             VARCHAR(8),
   QTBZ                 VARCHAR(1)                 default '0',
   QTPKRQ               VARCHAR(8),
   QTPTPCH              VARCHAR(8),
   constraint PK_BATCH_PLRW primary key (PKRQ, PTPCH)
);

comment on table BATCH_PLRW is
'����ҵ�������';

comment on column BATCH_PLRW.PKRQ is
'��������(ƽ̨����)';

comment on column BATCH_PLRW.PTPCH is
'ƽ̨���κ�';

comment on column BATCH_PLRW.TASKPRI is
'�������ȼ�';

comment on column BATCH_PLRW.SHPCH is
'�̻����κ�';

comment on column BATCH_PLRW.ZJPCH is
'�������κ�';

comment on column BATCH_PLRW.YWBH is
'ҵ����';

comment on column BATCH_PLRW.DWBH is
'��λ���';

comment on column BATCH_PLRW.TJRQ is
'��Χ�ύ���������';

comment on column BATCH_PLRW.TJSJ is
'�ύʱ��';

comment on column BATCH_PLRW.CLRQ is
'�����������';

comment on column BATCH_PLRW.CLSJ is
'����ʱ��';

comment on column BATCH_PLRW.ZJE is
'�����ܽ�����';

comment on column BATCH_PLRW.ZBS is
'�����ܱ���������';

comment on column BATCH_PLRW.SJZJE is
'ʵ���ܽ��ļ��ڣ�';

comment on column BATCH_PLRW.SJZBS is
'ʵ���ܱ������ļ��ڣ�';

comment on column BATCH_PLRW.CGZJE is
'�ɹ��ܽ��';

comment on column BATCH_PLRW.CGZBS is
'�ɹ��ܱ���';

comment on column BATCH_PLRW.SBZJE is
'ʧ���ܽ��';

comment on column BATCH_PLRW.SBZBS is
'ʧ���ܱ���';

comment on column BATCH_PLRW.SXFJE is
'�����ѽ��';

comment on column BATCH_PLRW.XKHBS is
'�¿�������';

comment on column BATCH_PLRW.XKHJE is
'�¿������';

comment on column BATCH_PLRW.LPWJM is
'�̻������ļ���';

comment on column BATCH_PLRW.SCZJWJM is
'�ϴ������ļ���';

comment on column BATCH_PLRW.ZJHFWJM is
'�����ظ��ļ���';

comment on column BATCH_PLRW.SHCGWJM is
'�ظ��̻��ɹ��ļ����������ļ�����';

comment on column BATCH_PLRW.SHSBWJM is
'�ظ��̻�ʧ���ļ���';

comment on column BATCH_PLRW.DQBD is
'�������� 0 ��ȡ���� 1 ������� 2 ����У�� 3 �ύ���� 4�������  5����';

comment on column BATCH_PLRW.FZBD is
'��������
����������Ϊ7������Ƕ��ʱ����Ч����������ʹ��00���������������99-������̬
00-������  09-������ 10-������  19-������ 11-�ѷ��� ';

comment on column BATCH_PLRW.BDZT is
' 0��ֹ 1���� 2�ϵ� 3���� 4�ȴ� 9�ڴ�����  X ���� C���� Z��ֹ';

comment on column BATCH_PLRW.RWZT is
' 0��ֹ 1���� 2�ϵ� 3���� 4�ȴ� 9�ڴ�����  X ���� C���� Z��ֹ';

comment on column BATCH_PLRW.XYDM is
'��Ӧ����';

comment on column BATCH_PLRW.XYXX is
'��Ӧ��Ϣ';

comment on column BATCH_PLRW.BQTPKRQ is
'��Ƕ����������';

comment on column BATCH_PLRW.BQTPTPCH is
'��Ƕ��ƽ̨���κ�';

comment on column BATCH_PLRW.QTBZ is
'Ƕ�ױ�־ 0-��Ƕ�� 1-Ƕ�� 2-��Ƕ�� 3-�ȱ�Ƕ����Ƕ��';

comment on column BATCH_PLRW.QTPKRQ is
'Ƕ����������';

comment on column BATCH_PLRW.QTPTPCH is
'Ƕ��ƽ̨���κ�';

--==============================================================
-- Index: K_BAT_PLRW_1
--==============================================================
create index K_BAT_PLRW_1 on BATCH_PLRW (
   YWBH                 ASC,
   PKRQ                 ASC,
   PTPCH                ASC
);

--==============================================================--
-- Index: K_BAT_PLRW_3                                          --
--==============================================================--
create index K_BAT_PLRW_3 on BATCH_PLRW (
   BQTPKRQ ASC,
   BQTPTPCH ASC
);

--==============================================================--
-- Index: K_BAT_PLRW_4                                          --
--==============================================================--
create index K_BAT_PLRW_4 on BATCH_PLRW (
   QTPKRQ ASC,
   QTPTPCH ASC
);

--==============================================================
-- Table: BATCH_PLRWBD
--==============================================================
create table BATCH_PLRWBD
(
   PKRQ                 VARCHAR(8)             not null,
   PTPCH                VARCHAR(8)             not null,
   FLOWSN               INTEGER               default 1 not null ,
   CZBD                 VARCHAR(2)                     not null,
   FZBD                 VARCHAR(2)                 default '00',
   BDZT                 VARCHAR(1),
   CLJG                 VARCHAR(16)            not null,
   CLGY                 VARCHAR(16)            not null,
   CLKSRQ               VARCHAR(8),
   CLKSSJ               VARCHAR(6),
   CLJSRQ               VARCHAR(8),
   CLJSSJ               VARCHAR(6),
   CLCS                 INTEGER,
   XYDM                 VARCHAR(8),
   XYXX                 VARCHAR(60),
   constraint PK_BATCH_PLRWBD primary key (PKRQ, PTPCH, FLOWSN, CZBD)
);

comment on table BATCH_PLRWBD is
'����ҵ�����񲽵���ϸ��';

comment on column BATCH_PLRWBD.PKRQ is
'��������(ƽ̨����)';

comment on column BATCH_PLRWBD.PTPCH is
'ƽ̨���κ�';

comment on column BATCH_PLRWBD.FLOWSN is
'����ִ�����';

comment on column BATCH_PLRWBD.CZBD is
'�������� 0 ��ȡ���� 1 ������� 2 ������� 3 �����ύ 4�������  5��ҵ����  ';

comment on column BATCH_PLRWBD.FZBD is
'��������
����������Ϊ7������Ƕ��ʱ����Ч����������ʹ��00���������������99-������̬
00-������  09-������ 10-������  19-������ 11-�ѷ��� ';


comment on column BATCH_PLRWBD.BDZT is
' 0��ֹ 1���� 2�ϵ� 3���� 4�ȴ� 9�ڴ����� ';

comment on column BATCH_PLRWBD.CLJG is
'�������';

comment on column BATCH_PLRWBD.CLGY is
'�����Ա';

comment on column BATCH_PLRWBD.XYDM is
'��Ӧ����';

comment on column BATCH_PLRWBD.XYXX is
'��Ӧ��Ϣ';

--==============================================================--
-- Index: K_BAT_PLRWBD_1                                      --
--==============================================================--
create index K_BAT_PLRWBD_1 on BATCH_PLRWBD (
   PKRQ ASC,
   PTPCH ASC,
   CZBD ASC
);

--==============================================================
-- Table: BATCH_RUNCTRL
--==============================================================
create table BATCH_RUNCTRL
(
   CPDM                 VARCHAR(16)            not null,
   FLOWID               VARCHAR(32),
   MAXTASK              VARCHAR(5),
   MAXTHREAD            VARCHAR(5),
   ZJYSBS               VARCHAR(32),
   WWYSBS               VARCHAR(32),
   SHBZ                 VARCHAR(1),
   TASKMODE             VARCHAR(1),
   TASKPRI              VARCHAR(3)                     default '0',
   PZBD                 VARCHAR(2),
   EXTFLD1              VARCHAR(60),
   WHJG                 VARCHAR(16),
   WHGY                 VARCHAR(16),
   WHSJ                 VARCHAR(14),
   constraint PK_BATCH_RUNCTRL primary key (CPDM)
);

comment on column BATCH_RUNCTRL.SHBZ is
'0����Ҫ����ⲿ�ļ���1������Ҫ����ⲿ�ļ�';

comment on column BATCH_RUNCTRL.TASKMODE is
'1��������2���ֶ���Ĭ��Ϊ1��';

comment on column BATCH_RUNCTRL.TASKPRI is
'�������ȼ� 0-�ͼ� 1-�м� 2-�߼�';

comment on column BATCH_RUNCTRL.PZBD is
'���ò���';

--==============================================================
-- Table: BATCH_STEPATTRIB
--==============================================================
create table BATCH_STEPATTRIB
(
   STEPID               VARCHAR(32)            not null,
   STEPNAME             VARCHAR(40),
   ATTRIBID             VARCHAR(16)            not null,
   ATTRIBNOTE           VARCHAR(32),
   ATTRIBVALUE          VARCHAR(32),
   constraint PK_BATCH_STEPATTRIB primary key (STEPID, ATTRIBID)
);

--==============================================================
-- Table: BATCH_STEPCFG
--==============================================================
create table BATCH_STEPCFG
(
   FLOWID               VARCHAR(32)            not null,
   FLOWSN               INTEGER               default 1 not null ,
   STEPID               VARCHAR(32)            not null,
   ATTRIBNOTE           VARCHAR(40),
   ATTRIBID             VARCHAR(16)            not null,
   ATTRIBTYPE           VARCHAR(1),
   ATTRIBVALUE          VARCHAR(60),
   constraint PK_BATCH_STEPCFG primary key (FLOWID, FLOWSN, STEPID, ATTRIBID)
);

comment on column BATCH_STEPCFG.ATTRIBTYPE is
'0 �������� 1��������';

comment on column BATCH_STEPCFG.FLOWSN is
'����ִ�����';

--==============================================================
-- Table: BATCH_WBWJDJ
--==============================================================
create table BATCH_WBWJDJ
(
   DJRQ                 VARCHAR(8)             not null,
   DJLSH                INTEGER                not null,
   DJSJ                 VARCHAR(6),
   YWBH                 VARCHAR(16)            not null,
   DJJG                 VARCHAR(16)            not null,
   DJGY                 VARCHAR(16)            not null,
   SHJG                 VARCHAR(16),
   SHGY                 VARCHAR(16),
   SHPCH                VARCHAR(32),
   PKRQ                 VARCHAR(8),
   PTPCH                VARCHAR(8),
   LPWJLJ               VARCHAR(254),
   LPWJM                VARCHAR(60),
   ZBS                  VARCHAR(8),
   ZJE                  NUMERIC(16,2),
   THREADNO             INTEGER,
   TASKMODE             VARCHAR(1),
   PCZT                 VARCHAR(1),
   SHZT                 VARCHAR(1),
   NOTE                 VARCHAR(128),
   BREAKDATA            CLOB                   not compact not logged,
   EXTFLD1              VARCHAR(40),
   EXTFLD2              VARCHAR(40),
   EXTFLD3              VARCHAR(40),
   constraint PK_BATCH_WBWJDJ primary key (DJRQ, DJLSH)
);

comment on column BATCH_WBWJDJ.THREADNO is
'���߼�ѡ��Ĭ��Ϊ1��';

comment on column BATCH_WBWJDJ.TASKMODE is
'1��������2���ֶ���Ĭ��Ϊ1��';

comment on column BATCH_WBWJDJ.PCZT is
'1�������ϴ���2��������3�����ڴ���4���ѷ��أ�5������ʧ�ܣ�X������, C:������Z:��ֹ';

comment on column BATCH_WBWJDJ.SHZT is
'0�����ͨ����1��δ��ˣ�2�����ʧ��';

comment on column BATCH_WBWJDJ.SHJG is
'��˻���';

comment on column BATCH_WBWJDJ.SHGY is
'��˹�Ա';


--==============================================================
-- Index: K_BAT_WBWJDJ_1
--==============================================================
create index K_BAT_WBWJDJ_1 on BATCH_WBWJDJ (
   SHPCH                ASC
);

--==============================================================--
-- Index: K_BAT_WBWJDJ_3                                        --
--==============================================================--
create index K_BAT_WBWJDJ_3 on BATCH_WBWJDJ (
   PKRQ ASC,
   PTPCH ASC
);

--==============================================================--
-- Index: K_BAT_WBWJDJ_4                                        --
--==============================================================--
create index K_BAT_WBWJDJ_4 on BATCH_WBWJDJ (
   LPWJM ASC
);

delete from app_yyxx where YYBS='002';
insert into app_yyxx (YYBS, YYMC, YYSM, YYKFKSRQ, YYKFJSRQ, YYFBRQ, YYBBH, YHH, SQH, YYKFJL, YYZBJL, YYZT, EXTFLD)
values ('002', 'batch', '������������', '', '', '20150820', '4.1.0.1', '', '', 'Tuql', 'Tuql', '0', '');

delete from APP_CSKZ where csjz='K_BATCH_MAXTASK';
insert into APP_CSKZ (csjz,cslx,cstj,jdm,jdz,remark,jzlx,whjg,whgy,whsj ) values('K_BATCH_MAXTASK','2','002','/batch/maxtasknum','10','��󲢷���������','0','00000','admin', '20150820090000');

delete from APP_CSKZ where csjz='K_BATCH_SJTJ_MAXWAIT';
insert into APP_CSKZ (csjz,cslx,cstj,jdm,jdz,remark,jzlx,whjg,whgy,whsj ) values('K_BATCH_SJTJ_MAXWAIT','2','002','/batch/sjtj/maxwait','43200','�ύ������ȴ�ʱ��(��)','0','00000','admin', '20150820090000');

delete from APP_CSKZ where csjz='K_BATCH_SJTJ_ITVL';     
insert into APP_CSKZ (csjz,cslx,cstj,jdm,jdz,remark,jzlx,whjg,whgy,whsj ) values ('K_BATCH_SJTJ_ITVL', '2', '002', '/batch/sjtj/interval', '5', '�ύ�����ļ����ʱ��(��)', '0', '100000', 'yd', '20150820090000');

delete from APP_CSKZ where csjz='K_BATCH_HOME';
insert into APP_CSKZ (csjz,cslx,cstj,jdm,jdz,remark,jzlx,whjg,whgy,whsj ) values('K_BATCH_HOME','2','002','/batch/HOME','/agent/gapsdb2/','����ƽ̨HOME·��','0','00000','admin', '20150820090000');

delete from APP_CSKZ where csjz='K_BATCH_WEB_IP';
insert into APP_CSKZ (csjz,cslx,cstj,jdm,jdz,remark,jzlx,whjg,whgy,whsj) values('K_BATCH_WEB_IP','2','002','/batch/web/serverip','127.0.0.1','WEB�����ip','1','00000','admin','20150820090000');

delete from APP_CSKZ where csjz='K_BATCH_WEB_OVERTIME';
insert into APP_CSKZ (csjz,cslx,cstj,jdm,jdz,remark,jzlx,whjg,whgy,whsj) values('K_BATCH_WEB_OVERTIME','2','002','/batch/web/overtime','360','WEB�˷���ʱʱ��(��)','1','00000','admin','20150820090000');

delete from APP_CSKZ where csjz='K_BATCH_WEB_PORT';
insert into APP_CSKZ (csjz,cslx,cstj,jdm,jdz,remark,jzlx,whjg,whgy,whsj) values('K_BATCH_WEB_PORT','2','002','/batch/web/serverport','50005','WEB�����port','1','00000','admin','20150820090000');

delete from APP_CSKZ where csjz='K_BATCH_HOST_TRANAMT';
insert into APP_CSKZ (csjz,cslx,cstj,jdm,jdz,remark,jzlx,whjg,whgy,whsj) values('K_BATCH_HOST_TRANAMT','2','002','/batch/host_tranamt_flag','0','���ķ���ʵ�ʽ���־1-������0-����(Ĭ��)','0','00000','admin','20150820090000');

--add by tuql 20150608--
delete from APP_CSKZ where csjz='K_BATCH_MON_NORM';
insert into APP_CSKZ (csjz,cslx,cstj,jdm,jdz,remark,jzlx,whjg,whgy,whsj) values('K_BATCH_MON_NORM','2','002','/batch/mon/norm','MON_BATCH_NORM','����ҵ������������','0','00000','admin','20150820090000');

delete from APP_CSKZ where csjz='K_BATCH_MON_UNORM';
insert into APP_CSKZ (csjz,cslx,cstj,jdm,jdz,remark,jzlx,whjg,whgy,whsj) values('K_BATCH_MON_UNORM','2','002','/batch/mon/unorm','MON_BATCH_UNORM','����ҵ���쳣������','0','00000','admin','20150820090000');

delete from APP_CSKZ where csjz='K_BATCH_FLPATH';
insert into APP_CSKZ (csjz,cslx,cstj,jdm,jdz,remark,jzlx,whjg,whgy,whsj) values('K_BATCH_FLPATH','2','002','/batch/flpath','/dep3/agent21d/AIX32/file/batch','�����ļ�·��','0','00000','admin','20150820090000');

delete from APP_CSKZ where csjz='K_BATCH_ABNFLOWID';
insert into APP_CSKZ (csjz,cslx,cstj,jdm,jdz,remark,jzlx,whjg,whgy,whsj) values('K_BATCH_ABNFLOWID','2','002','/test/abnflowid','FLOW_xxx','����ҵ����Ϊʧ�������趨','0','00000','admin','20150820090000');

delete from APP_CSKZ where csjz='K_BATCH_ABNFLOWSN';
insert into APP_CSKZ (csjz,cslx,cstj,jdm,jdz,remark,jzlx,whjg,whgy,whsj) values('K_BATCH_ABNFLOWSN','2','002','/test/abnflowsn','2','����������Ϊʧ������ִ�����','0','00000','admin','20150820090000');

delete from APP_CSKZ where csjz='K_BATCH_PRIHIGHPROC';
insert into APP_CSKZ (csjz,cslx,cstj,jdm,jdz,remark,jzlx,whjg,whgy,whsj) values('K_BATCH_PRIHIGHPROC','2','002','/batch/priproc/high','3','��������æʱ�и߼����ȴ�����','0','00000','admin','20150820090000');

delete from APP_CSKZ where csjz='K_BATCH_HOSTFILE';
insert into APP_CSKZ (csjz,cslx,cstj,jdm,jdz,remark,jzlx,whjg,whgy,whsj) values('K_BATCH_HOSTFILE','2','002','/batch/host/fileflg','0','�������������������ļ���־0-����,1-ɾ��','0','00000','admin','20150820090000');

delete from APP_CSKZ where csjz='K_BATCH_BQTIP';
insert into APP_CSKZ (csjz,cslx,cstj,jdm,jdz,remark,jzlx,whjg,whgy,whsj) values('K_BATCH_BQTIP','2','002','/batch/bqtrw/ip','192.168.53.25','��Ƕ������ͨѶIP','0','00000','admin','20150820090000');

delete from APP_CSKZ where csjz='K_BATCH_BQTPORT';
insert into APP_CSKZ (csjz,cslx,cstj,jdm,jdz,remark,jzlx,whjg,whgy,whsj) values('K_BATCH_BQTPORT','2','002','/batch/bqtrw/port','33008','��Ƕ������ͨѶ�˿�','0','00000','admin','20150820090000');

delete from APP_CSKZ where csjz='K_BATCH_BQTTOUT';
insert into APP_CSKZ (csjz,cslx,cstj,jdm,jdz,remark,jzlx,whjg,whgy,whsj) values('K_BATCH_BQTTOUT','2','002','/batch/bqtrw/tout','60','��Ƕ������ͨѶ��ʱʱ��','0','00000','admin','20150820090000');

delete from APP_CSKZ where csjz='K_BATCH_FDSHD_INDEX';
Insert into APP_CSKZ (csjz,cslx,cstj,jdm,jdz,remark,jzlx,whjg,whgy,whsj) values ('K_BATCH_FDSHD_INDEX','0',null,'/batch/index','9|12','����ҵ��������ֶβ�����������','0','00000','admin','20150820090000');

delete from APP_CSKZ where csjz='K_BATCH_GDQLTS';
Insert into APP_CSKZ (csjz,cslx,cstj,jdm,jdz,remark,jzlx,whjg,whgy,whsj) values ('K_BATCH_GDQLTS','0',null,'/batch/qlts','7','ҵ��������鵵Ĭ������','1','00000','admin','20150820090000');

delete from APP_CSKZ where csjz='K_BATCH_ABNOR_AUTO';
Insert into APP_CSKZ (csjz,cslx,cstj,jdm,jdz,remark,jzlx,whjg,whgy,whsj) values ('K_BATCH_ABNOR_AUTO','0','002','/batch/abnorauto','1','���������쳣����0-������ 1-����(ȱʡ)','0','00000','admin','20150820090000');

delete from APP_CSKZ where csjz='K_BATCH_ATASK_DAYS';
Insert into APP_CSKZ (csjz,cslx,cstj,jdm,jdz,remark,jzlx,whjg,whgy,whsj) values ('K_BATCH_ATASK_DAYS','0','002','/batch/autotask/days','-30','�����Զ�����������','0','00000','admin','20150820090000');

delete from APP_CSKZ where csjz='K_BATCH_CHKELEMFLAG';
Insert into APP_CSKZ (csjz,cslx,cstj,jdm,jdz,remark,jzlx,whjg,whgy,whsj) values ('K_BATCH_CHKELEMFLAG','0','002','/batch/checkelemflag','1','��ϸ��������־1-���','0','00000','admin','20150820090000');


commit;

delete from app_xlkz where PKEY='K_BATCH_PCH';
insert into APP_XLKZ (PKEY, CURR_VALUE, PINC, MIN_VALUE, MAX_VALUE, REMARK, WHJG, WHGY, WHSJ )
values ('K_BATCH_PCH', 1, 1, 1, 99999999, '����ҵ�����κ�','00000','admin', '20150820090000' );

delete from app_xlkz where PKEY='K_ZCBINDEX';
INSERT INTO APP_XLKZ(PKEY, CURR_VALUE, PINC, MIN_VALUE, MAX_VALUE, REMARK, WHJG, WHGY, WHSJ)
VALUES('K_ZCBINDEX', 1, 1, 1, 99999999, 'ע���������ʶ����', '00000', 'admin', '20150820090000');

delete from app_xlkz where PKEY='K_BATCH_KHBH';
insert into APP_XLKZ (pkey,curr_value,pinc,min_value,max_value,remark,whjg,whgy,whsj)
values('K_BATCH_KHBH',100000,1,1,99999999,'�����ͻ����','00000','admin','20150820090000');

delete from app_xlkz where PKEY='K_BATCH_XYBH';
insert into APP_XLKZ (pkey,curr_value,pinc,min_value,max_value,remark,whjg,whgy,whsj)
values('K_BATCH_XYBH',100000,1,1,99999999,'�����ͻ�Э����','00000','admin','20150820090000');
commit;
delete from app_dict where ssyy='002';
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY, WHJG, WHGY ) VALUES('K_STEP_DDBZ','�ϵ��־','0','�޶ϵ�','002','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY, WHJG, WHGY ) VALUES('K_STEP_DDBZ','�ϵ��־','1','�ϵ�','002','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY, WHJG, WHGY ) VALUES('K_STEP_DDBZ','�ϵ��־','2','����','002','00000','admin' ); 

INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY, WHJG, WHGY ) VALUES('K_BATCH_MXCGBZ','��ϸ�ɹ���־','0','�ɹ�','002','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY, WHJG, WHGY ) VALUES('K_BATCH_MXCGBZ','��ϸ�ɹ���־','1','���ֳɹ�','002','00000','admin');
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY, WHJG, WHGY ) VALUES('K_BATCH_MXCGBZ','��ϸ�ɹ���־','2','����ʧ��','002','00000','admin'); 

INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_STEP_CFCZBZ','�ظ�������־','0','����','002','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_STEP_CFCZBZ','�ظ�������־','1','������','002','00000','admin' );
                                            
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_STEP_HQSJFS','��ȡ���ݷ�ʽ','0','FTP����ȡ','002','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_STEP_HQSJFS','��ȡ���ݷ�ʽ','1','WEB���������','002','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_STEP_HQSJFS','��ȡ���ݷ�ʽ','2','���׻�ȡ','002','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_STEP_HQSJFS','��ȡ���ݷ�ʽ','3','��������','002','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_STEP_HQSJFS','��ȡ���ݷ�ʽ','4','�ֹ�¼��','002','00000','admin' );
                                            
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_STEP_MXTJBZ','��ϸ�ύ��־','1','�ύ����δ�������ʧ����ϸ','002','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_STEP_MXTJBZ','��ϸ�ύ��־','2','�ύ������δ������ϸ','002','00000','admin' );
                                            
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_STEP_MXHPBZ','��ϸ���̱�־','0','��������������ϸ','002','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_STEP_MXHPBZ','��ϸ���̱�־','1','���ɱ�����������ϸ','002','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_STEP_MXHPBZ','��ϸ���̱�־','2','���ɱ����δ���ɹ���ϸ','002','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_STEP_MXHPBZ','��ϸ���̱�־','3','���ɱ����δ���ʧ����ϸ','002','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_STEP_MXHPBZ','��ϸ���̱�־','4','�ֱ����ɳɹ�ʧ����ϸ','002','00000','admin' );

INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_STEP_XYMZHBZ','��Ӧ��ת����־','0','ת��','002','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_STEP_XYMZHBZ','��Ӧ��ת����־','1','��ת��','002','00000','admin' );
                                            
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_STEP_FSSJFS','�������ݷ�ʽ','0','FTP��������','002','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_STEP_FSSJFS','�������ݷ�ʽ','1','WEB���������','002','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_STEP_FSSJFS','�������ݷ�ʽ','2','����','002','00000','admin' );
                                            
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_STEP_JJMBZ','�ӽ��ܱ�־','0','��Ҫ','002','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_STEP_JJMBZ','�ӽ��ܱ�־','1','����Ҫ','002','00000','admin' );
                                            
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_STEP_WJLXZHBZ','�ļ�����ת����־ ','0','��Ҫ','002','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_STEP_WJLXZHBZ','�ļ�����ת����־ ','1','����Ҫ','002','00000','admin' );
                                            
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_STEP_SHSBBZ','���ʧ�ܱ�־ ','0','������','002','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_STEP_SHSBBZ','���ʧ�ܱ�־ ','1','����','002','00000','admin' );

INSERT INTO app_dict(pkey, keyjs, pval, prompt, ssyy, whjg, whgy, whsj)  VALUES('K_BOTS_CGBZ', '�ɹ���־', '0', '�ɹ�', '002', '00000', 'admin', '20150820090000');
INSERT INTO app_dict(pkey, keyjs, pval, prompt, ssyy, whjg, whgy, whsj)  VALUES('K_BOTS_CGBZ', '�ɹ���־', '1', '���ֳɹ�', '002', '00000', 'admin', '20150820090000');
INSERT INTO app_dict(pkey, keyjs, pval, prompt, ssyy, whjg, whgy, whsj)  VALUES('K_BOTS_CGBZ', '�ɹ���־', '2', '����ʧ��', '002', '00000', 'admin', '20150820090000');
INSERT INTO app_dict(pkey, keyjs, pval, prompt, ssyy, whjg, whgy, whsj)  VALUES('K_BOTS_CGBZ', '�ɹ���־', '9', '��ʼ״̬', '002', '00000', 'admin', '20150820090000');
--INSERT INTO app_dict(pkey, keyjs, pval, prompt, ssyy, whjg, whgy, whsj)  VALUES('K_BOTS_CLZT', '����״̬', '0', 'δ����', '002', '00000', 'admin', '20150820090000');
INSERT INTO app_dict(pkey, keyjs, pval, prompt, ssyy, whjg, whgy, whsj)  VALUES('K_BOTS_CLZT', '����״̬', '1', '�Ѵ���', '002', '00000', 'admin', '20150820090000');
INSERT INTO app_dict(pkey, keyjs, pval, prompt, ssyy, whjg, whgy, whsj)  VALUES('K_BOTS_CLZT', '����״̬', '9', '��ʼ״̬', '002', '00000', 'admin', '20150820090000');
INSERT INTO app_dict(pkey, keyjs, pval, prompt, ssyy, whjg, whgy, whsj)  VALUES('K_BOTS_SHZT', '���״̬', '0', '���ͨ��', '002', '00000', 'admin', '20150820090000');
INSERT INTO app_dict(pkey, keyjs, pval, prompt, ssyy, whjg, whgy, whsj)  VALUES('K_BOTS_SHZT', '���״̬', '1', '���ʧ��', '002', '00000', 'admin', '20150820090000');
INSERT INTO app_dict(pkey, keyjs, pval, prompt, ssyy, whjg, whgy, whsj)  VALUES('K_BOTS_SHZT', '���״̬', '9', '��ʼ״̬', '002', '00000', 'admin', '20150820090000');

INSERT INTO app_dict(pkey, keyjs, pval, prompt, ssyy, whjg, whgy, whsj)  VALUES('K_BOTS_YXJ', '���ȼ�', '0', '�ͼ�', '002', '00000', 'admin', '20150820090000');
INSERT INTO app_dict(pkey, keyjs, pval, prompt, ssyy, whjg, whgy, whsj)  VALUES('K_BOTS_YXJ', '���ȼ�', '1', '�м�', '002', '00000', 'admin', '20150820090000');
INSERT INTO app_dict(pkey, keyjs, pval, prompt, ssyy, whjg, whgy, whsj)  VALUES('K_BOTS_YXJ', '���ȼ�', '2', '�߼�', '002', '00000', 'admin', '20150820090000');
  

delete from app_jyxx where yybs='002';
insert into APP_JYXX (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, QTBZ,WHJG,WHGY) values ('910001', '����ҵ��¼������', '002', '0', '1', '1', '1', '0', null, null, '0','00000','admin' );
insert into APP_JYXX (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, QTBZ,WHJG,WHGY) values ('910002', '����������','002', '0', '1', '1', '1', '0', null, null, '0','00000','admin' );
insert into APP_JYXX (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, QTBZ,WHJG,WHGY) values ('910003', '����ҵ��ȴ�����', '002', '0', '1', '1', '1', '0', null, null, '0','00000','admin' );
insert into APP_JYXX (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, QTBZ,WHJG,WHGY) values ('910004', '����ҵ��ϵ㴥��', '002', '0', '1', '1', '1', '0', null, null, '0','00000','admin' );
insert into APP_JYXX (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, QTBZ,WHJG,WHGY) values ('910005', '����ҵ���ȡ����', '002', '0', '1', '1', '1', '0', null, null, '0','00000','admin' );
insert into APP_JYXX (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, QTBZ,WHJG,WHGY) values ('910006', '����ҵ���������', '002', '0', '1', '1', '1', '0', null, null, '0','00000','admin' );
insert into APP_JYXX (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, QTBZ,WHJG,WHGY) values ('910007', '����ҵ���������', '002', '0', '1', '1', '1', '0', null, null, '0','00000','admin' );
insert into APP_JYXX (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, QTBZ,WHJG,WHGY) values ('910008', '����ҵ�������ύ', '002', '0', '1', '1', '1', '0', null, null, '0','00000','admin' );
insert into APP_JYXX (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, QTBZ,WHJG,WHGY) values ('910009', '����ҵ���������', '002', '0', '1', '1', '1', '0', null, null, '0','00000','admin' );
insert into APP_JYXX (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, QTBZ,WHJG,WHGY) values ('910030', '����ҵ������Ƕ��', '002', '0', '1', '1', '1', '0', null, null, '0','00000','admin' );
insert into APP_JYXX (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, QTBZ,WHJG,WHGY) values ('910031', '����ҵ���������', '002', '0', '1', '1', '1', '0', null, null, '0','00000','admin' );
insert into APP_JYXX (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, QTBZ,WHJG,WHGY) values ('910010', '����ҵ����������״̬��ѯ', '002', '0', '1', '1', '1', '0', null, null, '0','00000','admin' );
insert into APP_JYXX (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, QTBZ,WHJG,WHGY) values ('910011', '����ҵ�����ݻ���', '002', '0', '1', '1', '1', '0', null, null, '0','00000','admin' );
insert into APP_JYXX (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, QTBZ,WHJG,WHGY) values ('910012', '����ҵ������״̬��ѯ', '002', '0', '1', '1', '1', '0', null, null, '0','00000','admin' );
insert into APP_JYXX (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, QTBZ,WHJG,WHGY) values ('910013', '����ҵ������ȡ��','002', '0', '1', '1', '1', '0', null, null, '0','00000','admin' );
insert into APP_JYXX (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, QTBZ,WHJG,WHGY) values ('910014', '����ҵ���������γ���', '002', '0', '1', '1', '1', '0', null, null, '0','00000','admin' );
insert into APP_JYXX (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, QTBZ,WHJG,WHGY) values ('910015', '����ҵ�����������', '002', '0', '1', '1', '1', '0', null, null, '0','00000','admin' );
insert into APP_JYXX (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, QTBZ,WHJG,WHGY) values ('910016', '����ҵ���Զ�����ʧ��/�ȴ�����', '002', '0', '1', '1', '1', '0', null, null, '0','00000','admin' );
insert into APP_JYXX (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, QTBZ,WHJG,WHGY) values ('910020', '����ҵ������ֱ�ӷ���','002', '0', '1', '1', '1', '0', null, null, '0','00000','admin' );
 
insert into APP_JYXX (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, QTBZ,WHJG,WHGY) values ('910021', '�����ͻ�������','002', '0', '1', '1', '1', '0', null, null, '0','00000','admin' );
insert into APP_JYXX (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, QTBZ,WHJG,WHGY) values ('910022', '�����ͻ���������Ϣ�޸�','002', '0', '1', '1', '1', '0', null, null, '0','00000','admin' );
insert into APP_JYXX (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, QTBZ,WHJG,WHGY) values ('910023', '�����ͻ���������Ϣ��ѯ','002', '0', '1', '1', '1', '0', null, null, '0','00000','admin' );
insert into APP_JYXX (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, QTBZ,WHJG,WHGY) values ('910024', '�����ͻ���KEY��ѯ','002', '0', '1', '1', '1', '0', null, null, '0','00000','admin' );

insert into APP_JYXX (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, QTBZ,WHJG,WHGY) values ('910032', '����ҵ�����BREAKDATA', '002', '0', '1', '1', '1', '0', null, null, '0','00000','admin' );

insert into BATCH_AUDITINGPARA (FUNCID, PARASN, PARAVALUE, SNOTE ) values ('FUNC_K_2', 1, 'yhzh', '�跽�ʺ�' );
insert into BATCH_AUDITINGPARA (FUNCID, PARASN, PARAVALUE, SNOTE ) values ('FUNC_K_2', 2, '20', '����' );

insert into BATCH_AUDITINGREG (FUNCID, FUNCNAME, FUNCRUN, FUNCFILE, SNOTE, WHJG, WHGY ) values ('FUNC_K_1', 'BATCH_CHECKALLNUM', 'BATCH_CHECKALLNUM', 'BAT_CHECK.so', '����ҵ��У���ܱ����ܽ��','00000','admin' );
insert into BATCH_AUDITINGREG (FUNCID, FUNCNAME, FUNCRUN, FUNCFILE, SNOTE, WHJG, WHGY ) values ('FUNC_K_2', 'BATCH_CHECKLEN', 'BATCH_CHECKLEN', 'BAT_CHECK.so', '����ҵ������г���','00000','admin' );
insert into BATCH_AUDITINGREG (FUNCID, FUNCNAME, FUNCRUN, FUNCFILE, SNOTE, WHJG, WHGY ) values ('FUNC_K_3', 'BATCH_CHECKSIGN', 'BATCH_CHECKSIGN', 'BAT_CHECK.so', '����ҵ��У��ǩԼ��ϵ','00000','admin' );
commit;
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('hqsj', '��ȡ����', 'ddbz', '�ϵ��־','0' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('hqsj', '��ȡ����', 'ddsj', '�ϵ�ʱ��(��)','0' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('hqsj', '��ȡ����', 'cllcm', '����������','flow_batch_step_hqsj' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('hqsj', '��ȡ����', 'hqsjfs', '��ȡ���ݷ�ʽ','1' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('hqsj', '��ȡ����', 'filename', '�ļ���','' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('hqsj', '��ȡ����', 'filedir', '�ļ�����·��','file/batch/dsf' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('hqsj', '��ȡ����', 'ftpip', 'FTPIP��ַ','' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('hqsj', '��ȡ����', 'ftpuser', 'FTP�û�','' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('hqsj', '��ȡ����', 'ftppwd', 'FTP����','' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('hqsj', '��ȡ����', 'ftpmlj', 'FTPԶ��·��','' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('hqsj', '��ȡ����', 'ftpmode', 'FTP��������ģʽ','' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('hqsj', '��ȡ����', 'ftptype', 'FTP����ģʽ','' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('hqsj', '��ȡ����', 'cdpc', '�ص�����SQL WHERE eg: cgbz=#0#','cgbz=#2#' );

insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('hqsj', '��ȡ����', 'ctwjbs', '�����ļ���ʶ','FILE_' );

insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjrk', '�������', 'cllcm', '����������','flow_batch_step_sjrk' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjrk', '�������', 'ddbz', '�ϵ��־','0' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjrk', '�������', 'ddsj', '�ϵ�ʱ��(��)','0' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjrk', '�������', 'jjmbz', '�ӽ��ܱ�־','1' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjrk', '�������', 'jjmbs', '�ӽ��ܷ����ʶ','subflow_batch_des_proc' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjrk', '�������', 'wjlxzhbz', '�ļ�����ת����־','1' );

insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjsh', '�������', 'cllcm', '����������','flow_batch_step_sjsh' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjsh', '�������', 'ddbz', '�ϵ��־','0' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjsh', '�������', 'ddsj', '�ϵ�ʱ��(��)','0' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjsh', '�������', 'shbs', '������˱�ʶ','' );

insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjtj', '�����ύ', 'cllcm', '����������','flow_batch_step_sjtj' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjtj', '�����ύ', 'ddbz', '�ϵ��־','1' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjtj', '�����ύ', 'gdddsj', '�̶��ϵ�ʱ��(��)','5' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjtj', '�����ύ', 'fdddsj', '�����ϵ�ʱ��(��)','' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjtj', '�����ύ', 'cfczbz', '�ظ�������־','0' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjtj', '�����ύ', 'mxtjbz', '��ϸ�ύ��־','2' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjtj', '�����ύ', 'expwhere', '��ϸ��������eg: AND shzt !=#1# ','' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjtj', '�����ύ', 'ksclsj', 'ҹ��������ʼ����ʱ��','220000' );


insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjth', '�������', 'cllcm', '����������','flow_batch_step_sjth' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjth', '�������', 'cfczbz', '�ظ�������־','0' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjth', '�������', 'ddbz', '�ϵ��־','0' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjth', '�������', 'ddsj', '�ϵ�ʱ��(��)','5' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjth', '�������', 'cftjbz', '�ظ��ύ��־','1' );

insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjhp', '���ݻ���', 'cllcm', '����������','flow_batch_step_sjhp' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjhp', '���ݻ���', 'cfczbz', '�ظ�������־','0' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjhp', '���ݻ���', 'fssjfs', '�������ݷ�ʽ','1' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjhp', '���ݻ���', 'jjmbz', '�ӽ��ܱ�־','1' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjhp', '���ݻ���', 'jjmbs', '�ӽ��ܷ����ʶ','' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjhp', '���ݻ���', 'wjlxzhbz', '�ļ�����ת����־','1' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjhp', '���ݻ���', 'ftpip', 'FTPIP��ַ','' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjhp', '���ݻ���', 'ftpuser', 'FTP�û�','' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjhp', '���ݻ���', 'ftppwd', 'FTP����','' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjhp', '���ݻ���', 'ftpmlj', 'FTPԶ��·��','' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjhp', '���ݻ���', 'mxhpbz', '��ϸ���̱�־','1' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjhp', '���ݻ���', 'filename', '�ɹ������ļ���','' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('sjhp', '���ݻ���', 'filename_f', 'ʧ�ܻ����ļ���','' );

insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('rwqt', '����Ƕ��', 'cllcm', '����������','flow_batch_step_rwqt' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('rwqt', '����Ƕ��', 'bqtcpdm', '��Ƕ�ײ�Ʒ����','xxxx' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('rwqt', '����Ƕ��', 'bqtywbh', '��Ƕ��ҵ����','xxxx' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('rwqt', '����Ƕ��', 'qtwjys', 'Ƕ���ļ�ӳ��','MAP_' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('rwqt', '����Ƕ��', 'qtwjdc', 'Ƕ���ļ�����WHERE eg: yhzh=#123#',' 1=1 ' );
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('rwqt', '����Ƕ��', 'cfczbz', '�ظ�������־','0' );

--add by tuql 20161107 ��Ƕ��������; 0-��ͨ,1-ֻ����ĵȽ���
insert into BATCH_STEPATTRIB (STEPID, STEPNAME, ATTRIBID, ATTRIBNOTE,ATTRIBVALUE) values ('rwqt', '����Ƕ��', 'bqtpcyt', '��Ƕ��������;','0' );

delete from APP_TABLEINFO where TABLECODE='batch_mxmb';
insert into  APP_TABLEINFO (TABLECODE,TABLENAME,TABLETYPE,WHJG,WHGY ) values ('batch_mxmb','����ҵ����ϸģ��','2','00000','admin' );

delete from APP_TABLEREG where TABLENAME='batch_mxmb';

insert into APP_TABLEREG (TABLENAME, FLDSN, FLDID, FLDNAME, FLDTYPE, FLDLEN, DECIMALDIGITS, ISKEY, ISNULL) values ('batch_mxmb', 1, 'pkrq', '��������', 'C', '8', null, '0', '1');
insert into APP_TABLEREG (TABLENAME, FLDSN, FLDID, FLDNAME, FLDTYPE, FLDLEN, DECIMALDIGITS, ISKEY, ISNULL) values ('batch_mxmb', 2, 'ptpch', 'ƽ̨���κ�', 'C', '8', null, '0', '1');
insert into APP_TABLEREG (TABLENAME, FLDSN, FLDID, FLDNAME, FLDTYPE, FLDLEN, DECIMALDIGITS, ISKEY, ISNULL) values ('batch_mxmb', 3, 'lsxh', '��ˮ���', 'I', null, null, '0', '1' );
insert into APP_TABLEREG (TABLENAME, FLDSN, FLDID, FLDNAME, FLDTYPE, FLDLEN, DECIMALDIGITS, ISKEY, ISNULL) values ('batch_mxmb', 4, 'wjxh', '�ļ����', 'I', null, null, '1', '1' );
insert into APP_TABLEREG (TABLENAME, FLDSN, FLDID, FLDNAME, FLDTYPE, FLDLEN, DECIMALDIGITS, ISKEY, ISNULL) values ('batch_mxmb', 5, 'ywbh', 'ҵ����', 'C', '16', null, '1', '0' );
insert into APP_TABLEREG (TABLENAME, FLDSN, FLDID, FLDNAME, FLDTYPE, FLDLEN, DECIMALDIGITS, ISKEY, ISNULL) values ('batch_mxmb', 6, 'dwbh', '��λ���', 'C', '16', null, '1', '0' );
insert into APP_TABLEREG (TABLENAME, FLDSN, FLDID, FLDNAME, FLDTYPE, FLDLEN, DECIMALDIGITS, ISKEY, ISNULL) values ('batch_mxmb', 7, 'jlbs', '��¼��ʶ', 'C', '32', null, '1', '0' );
insert into APP_TABLEREG (TABLENAME, FLDSN, FLDID, FLDNAME, FLDTYPE, FLDLEN, DECIMALDIGITS, ISKEY, ISNULL) values ('batch_mxmb', 8, 'yhh1', '�û���', 'C', '32', null, '1', '0' );
insert into APP_TABLEREG (TABLENAME, FLDSN, FLDID, FLDNAME, FLDTYPE, FLDLEN, DECIMALDIGITS, ISKEY, ISNULL) values ('batch_mxmb', 9, 'yhxm', '�û�����', 'C', '80', null, '1', '0' );
insert into APP_TABLEREG (TABLENAME, FLDSN, FLDID, FLDNAME, FLDTYPE, FLDLEN, DECIMALDIGITS, ISKEY, ISNULL) values ('batch_mxmb', 10, 'zjhm', '֤������', 'C', '32', null, '1', '0' );
insert into APP_TABLEREG (TABLENAME, FLDSN, FLDID, FLDNAME, FLDTYPE, FLDLEN, DECIMALDIGITS, ISKEY, ISNULL) values ('batch_mxmb', 11, 'yhzh', '�û��ʻ�', 'C', '32', null, '1', '0' );
insert into APP_TABLEREG (TABLENAME, FLDSN, FLDID, FLDNAME, FLDTYPE, FLDLEN, DECIMALDIGITS, ISKEY, ISNULL) values ('batch_mxmb', 12, 'jyje', '���׽��', 'D', '15', '2', '1', '0' );
insert into APP_TABLEREG (TABLENAME, FLDSN, FLDID, FLDNAME, FLDTYPE, FLDLEN, DECIMALDIGITS, ISKEY, ISNULL) values ('batch_mxmb', 13, 'sjje', 'ʵ�ʽ��', 'D', '15', '2', '1', '0' );
insert into APP_TABLEREG (TABLENAME, FLDSN, FLDID, FLDNAME, FLDTYPE, FLDLEN, DECIMALDIGITS, ISKEY, ISNULL) values ('batch_mxmb', 14, 'shzt', '���״̬', 'C', '1', null, '1', '0' );
insert into APP_TABLEREG (TABLENAME, FLDSN, FLDID, FLDNAME, FLDTYPE, FLDLEN, DECIMALDIGITS, ISKEY, ISNULL) values ('batch_mxmb', 15, 'clzt', '����״̬', 'C', '1', null, '1', '0' );
insert into APP_TABLEREG (TABLENAME, FLDSN, FLDID, FLDNAME, FLDTYPE, FLDLEN, DECIMALDIGITS, ISKEY, ISNULL) values ('batch_mxmb', 16, 'cgbz', '�ɹ���־', 'C', '1', null, '1', '0' );
insert into APP_TABLEREG (TABLENAME, FLDSN, FLDID, FLDNAME, FLDTYPE, FLDLEN, DECIMALDIGITS, ISKEY, ISNULL) values ('batch_mxmb', 17, 'xym', '��Ӧ��', 'C', '8', null, '1', '0' );
insert into APP_TABLEREG (TABLENAME, FLDSN, FLDID, FLDNAME, FLDTYPE, FLDLEN, DECIMALDIGITS, ISKEY, ISNULL) values ('batch_mxmb', 18, 'xyxx', '��Ӧ��Ϣ', 'C', '60', null, '1', '0' );
insert into APP_TABLEREG (TABLENAME, FLDSN, FLDID, FLDNAME, FLDTYPE, FLDLEN, DECIMALDIGITS, ISKEY, ISNULL) values ('batch_mxmb', 19, 'dsfxym', '��������Ӧ��', 'C', '8', null, '1', '0' );
insert into APP_TABLEREG (TABLENAME, FLDSN, FLDID, FLDNAME, FLDTYPE, FLDLEN, DECIMALDIGITS, ISKEY, ISNULL) values ('batch_mxmb', 20, 'dsfxyxx', '��������Ӧ��Ϣ', 'C', '60', null, '1', '0' );

commit;

CREATE SEQUENCE K_BATCH_PCH
INCREMENT BY 1 
START WITH 1
MAXVALUE 99999999 
MINVALUE 1
CYCLE 
CACHE 1000 
ORDER;

--ALTER SEQUENCE K_BATCH_PCH RESTART WITH 1 INCREMENT by 1 MAXVALUE 99999999;
