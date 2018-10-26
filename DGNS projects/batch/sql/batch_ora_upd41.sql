--���ȱ������¸�������

drop table BATCH_FILETYPE cascade constraints;

drop table BATCH_FLOWCFG cascade constraints;

drop table BATCH_STEPCFG cascade constraints;

drop table BATCH_RUNCTRL cascade constraints;

drop index K_BAT_PLRW_1;
drop index K_BAT_PLRW_3;
drop index K_BAT_PLRW_4;
drop table BATCH_PLRW cascade constraints;

drop index K_BAT_PLRW_2;
drop table BATCH_HIS_PLRW cascade constraints;

drop index K_BAT_PLRWBD_1;
drop table BATCH_PLRWBD cascade constraints;

drop index K_BAT_WBWJDJ_1;
drop index K_BAT_WBWJDJ_3;
drop index K_BAT_WBWJDJ_4;
drop table BATCH_WBWJDJ cascade constraints;

drop index K_BAT_WBWJDJ_2;

drop table BATCH_HIS_WBWJDJ cascade constraints;

--==============================================================--
-- Table: BATCH_FILETYPE                                        --
--==============================================================--
create table BATCH_FILETYPE  (
   FILEID               VARCHAR2(32)                    not null,
   FILEIDNOTE           VARCHAR2(40),
   FILETYPE             VARCHAR2(1),
   FILEFMT              VARCHAR2(2),
   CODEFMT              VARCHAR2(1)                     default '0',
   EXTFLD1              VARCHAR2(32),
   WHJG                 VARCHAR2(16),
   WHGY                 VARCHAR2(16),
   WHSJ                 VARCHAR2(14),
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

--==============================================================--
-- Table: BATCH_FLOWCFG                                         --
--==============================================================--
create table BATCH_FLOWCFG  (
   FLOWID               VARCHAR2(32)                    not null,
   FLOWNAME             VARCHAR2(40),
   FLOWSN               INTEGER                         not null,
   STEPID               VARCHAR2(32),
   STEPSN               INTEGER,
   STEPNAME             VARCHAR2(32),
   EXTFLD1              VARCHAR2(40),
   EXTFLD2              VARCHAR2(40),
   WHJG                 VARCHAR2(16),
   WHGY                 VARCHAR2(16),
   WHSJ                 VARCHAR2(14),
   constraint PK_BATCH_FLOWCFG primary key (FLOWID, FLOWSN)
);

--==============================================================--
-- Table: BATCH_STEPCFG                                         --
--==============================================================--
create table BATCH_STEPCFG  (
   FLOWID               VARCHAR2(32)                    not null,
   FLOWSN               INTEGER               default 1 not null ,
   STEPID               VARCHAR2(32)                    not null,
   ATTRIBNOTE           VARCHAR2(40),
   ATTRIBID             VARCHAR2(16)                    not null,
   ATTRIBTYPE           VARCHAR2(1),
   ATTRIBVALUE          VARCHAR2(60),
   constraint PK_BATCH_STEPCFG primary key (FLOWID, FLOWSN, STEPID, ATTRIBID)
);

comment on column BATCH_STEPCFG.FLOWSN is
'����ִ�����';

comment on column BATCH_STEPCFG.ATTRIBTYPE is
'0 �������� 1��������';

comment on column BATCH_STEPCFG.FLOWSN is
'����ִ�����';

--==============================================================--
-- Table: BATCH_RUNCTRL                                         --
--==============================================================--
create table BATCH_RUNCTRL  (
   CPDM                 VARCHAR2(16)                    not null,
   FLOWID               VARCHAR2(32),
   MAXTASK              VARCHAR2(5),
   MAXTHREAD            VARCHAR2(5),
   ZJYSBS               VARCHAR2(32),
   WWYSBS               VARCHAR2(32),
   SHBZ                 VARCHAR2(1),
   TASKMODE             VARCHAR2(1),
   TASKPRI              VARCHAR2(3)                     default '0',
   PZBD                 VARCHAR2(2),
   EXTFLD1              VARCHAR2(60),
   WHJG                 VARCHAR2(16),
   WHGY                 VARCHAR2(16),
   WHSJ                 VARCHAR2(14),
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

--==============================================================--
-- Table: BATCH_PLRW                                            --
--==============================================================--
create table BATCH_PLRW  (
   PKRQ                 VARCHAR2(8)                     not null,
   PTPCH                VARCHAR2(8)                     not null,
   TASKPRI              VARCHAR2(3),
   SHPCH                VARCHAR2(32),
   ZJPCH                VARCHAR2(32),
   YWBH                 VARCHAR2(16)                    not null,
   DWBH                 VARCHAR2(16),
   TJRQ                 VARCHAR2(8),
   TJSJ                 VARCHAR2(6),
   CLRQ                 VARCHAR2(8),
   CLSJ                 VARCHAR2(6),
   ZJE                  NUMBER(16,2),
   ZBS                  INTEGER,
   SJZJE                NUMBER(16,2),
   SJZBS                INTEGER,
   CGZJE                NUMBER(16,2),
   CGZBS                INTEGER,
   SBZJE                NUMBER(16,2),
   SBZBS                INTEGER,
   SXFJE                NUMBER(16,2),
   XKHBS                INTEGER,
   XKHJE                NUMBER(16,2),
   LPWJM                VARCHAR2(60),
   SCZJWJM              VARCHAR2(60),
   ZJHFWJM              VARCHAR2(60),
   SHCGWJM              VARCHAR2(60),
   SHSBWJM              VARCHAR2(60),
   DQBD                 VARCHAR2(2),
   FZBD                 VARCHAR2(2)                 default '00',
   BDZT                 VARCHAR2(1),
   RWZT                 VARCHAR2(1),
   XYDM                 VARCHAR2(8),
   XYXX                 VARCHAR2(60),
   BQTPKRQ              VARCHAR2(8),
   BQTPTPCH             VARCHAR2(8),
   QTBZ                 VARCHAR2(1)                 default '0',
   QTPKRQ               VARCHAR2(8),
   QTPTPCH              VARCHAR2(8),
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
����������Ϊ7������Ƕ��ʱ����Ч����������ʹ��00
00-������  09-������ 10-������  19-������ 11-�ѷ��� 99-������̬';

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

--==============================================================--
-- Index: K_BAT_PLRW_1                                          --
--==============================================================--
create index K_BAT_PLRW_1 on BATCH_PLRW (
   YWBH ASC,
   PKRQ ASC,
   PTPCH ASC
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

--==============================================================--
-- Table: BATCH_HIS_PLRW                                        --
--==============================================================--
create table BATCH_HIS_PLRW  (
   PKRQ                 VARCHAR2(8)                     not null,
   PTPCH                VARCHAR2(8)                     not null,
   TASKPRI              VARCHAR2(3),
   SHPCH                VARCHAR2(32),
   ZJPCH                VARCHAR2(32),
   YWBH                 VARCHAR2(16)                    not null,
   DWBH                 VARCHAR2(16),
   TJRQ                 VARCHAR2(8),
   TJSJ                 VARCHAR2(6),
   CLRQ                 VARCHAR2(8),
   CLSJ                 VARCHAR2(6),
   ZJE                  NUMBER(16,2),
   ZBS                  INTEGER,
   SJZJE                NUMBER(16,2),
   SJZBS                INTEGER,
   CGZJE                NUMBER(16,2),
   CGZBS                INTEGER,
   SBZJE                NUMBER(16,2),
   SBZBS                INTEGER,
   SXFJE                NUMBER(16,2),
   XKHBS                INTEGER,
   XKHJE                NUMBER(16,2),
   LPWJM                VARCHAR2(60),
   SCZJWJM              VARCHAR2(60),
   ZJHFWJM              VARCHAR2(60),
   SHCGWJM              VARCHAR2(60),
   SHSBWJM              VARCHAR2(60),
   DQBD                 VARCHAR2(2),
   FZBD                 VARCHAR2(2)                 default '00',
   BDZT                 VARCHAR2(1),
   RWZT                 VARCHAR2(1),
   XYDM                 VARCHAR2(8),
   XYXX                 VARCHAR2(60),
   BQTPKRQ              VARCHAR2(8),
   BQTPTPCH             VARCHAR2(8),
   QTBZ                 VARCHAR2(1)                 default '0',
   QTPKRQ               VARCHAR2(8),
   QTPTPCH              VARCHAR2(8),
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

comment on column BATCH_HIS_PLRW.FZBD is
'��������
����������Ϊ7������Ƕ��ʱ����Ч����������ʹ��00���������������99-������̬
00-������  09-������ 10-������  19-������ 11-�ѷ��� ';

comment on column BATCH_HIS_PLRW.BDZT is
' 0��ֹ 1���� 2�ϵ� 3���� 4�ȴ� 9�ڴ�����  X ���� C����';

comment on column BATCH_HIS_PLRW.RWZT is
' 0��ֹ 1���� 2�ϵ� 3���� 4�ȴ� 9�ڴ�����  X ���� C����';

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

--==============================================================--
-- Index: K_BAT_PLRW_2                                          --
--==============================================================--
create index K_BAT_PLRW_2 on BATCH_HIS_PLRW (
   YWBH ASC,
   PKRQ ASC,
   PTPCH ASC
);

--==============================================================--
-- Table: BATCH_PLRWBD                                          --
--==============================================================--
create table BATCH_PLRWBD  (
   PKRQ                 VARCHAR2(8)                     not null,
   PTPCH                VARCHAR2(8)                     not null,
   FLOWSN               INTEGER               default 1 not null ,
   CZBD                 VARCHAR2(2)                     not null,
   FZBD                 VARCHAR2(2),
   BDZT                 VARCHAR2(1),
   CLJG                 VARCHAR2(16)                    not null,
   CLGY                 VARCHAR2(16)                    not null,
   CLKSRQ               VARCHAR2(8),
   CLKSSJ               VARCHAR2(6),
   CLJSRQ               VARCHAR2(8),
   CLJSSJ               VARCHAR2(6),
   CLCS                 INTEGER,
   XYDM                 VARCHAR2(8),
   XYXX                 VARCHAR2(60),
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

--==============================================================--
-- Table: BATCH_WBWJDJ                                          --
--==============================================================--
create table BATCH_WBWJDJ  (
   DJRQ                 VARCHAR2(8)                     not null,
   DJLSH                INTEGER                         not null,
   DJSJ                 VARCHAR2(6),
   YWBH                 VARCHAR2(16)                    not null,
   DJJG                 VARCHAR2(16)                    not null,
   DJGY                 VARCHAR2(16)                    not null,
   SHJG                 VARCHAR2(16),
   SHGY                 VARCHAR2(16),
   SHPCH                VARCHAR2(32),
   PKRQ                 VARCHAR2(8),
   PTPCH                VARCHAR2(8),
   LPWJLJ               VARCHAR2(254),
   LPWJM                VARCHAR2(60),
   ZBS                  VARCHAR2(8),
   ZJE                  NUMBER(16,2),
   THREADNO             INTEGER,
   TASKMODE             VARCHAR2(1),
   PCZT                 VARCHAR2(1),
   SHZT                 VARCHAR2(1),
   NOTE                 VARCHAR2(128),
   BREAKDATA            BLOB,
   EXTFLD1              VARCHAR2(40),
   EXTFLD2              VARCHAR2(40),
   EXTFLD3              VARCHAR2(40),
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
--==============================================================--
-- Index: K_BAT_WBWJDJ_1                                        --
--==============================================================--
create index K_BAT_WBWJDJ_1 on BATCH_WBWJDJ (
   SHPCH ASC
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
--==============================================================--
-- Table: BATCH_HIS_WBWJDJ                                      --
--==============================================================--
create table BATCH_HIS_WBWJDJ  (
   DJRQ                 VARCHAR2(8)                     not null,
   DJLSH                INTEGER                         not null,
   DJSJ                 VARCHAR2(6),
   YWBH                 VARCHAR2(16)                    not null,
   DJJG                 VARCHAR2(16)                    not null,
   DJGY                 VARCHAR2(16)                    not null,
   SHJG                 VARCHAR2(16),
   SHGY                 VARCHAR2(16),
   SHPCH                VARCHAR2(32),
   PKRQ                 VARCHAR2(8),
   PTPCH                VARCHAR2(8),
   LPWJLJ               VARCHAR2(254),   
   LPWJM                VARCHAR2(60),
   ZBS                  VARCHAR2(8),
   ZJE                  NUMBER(16,2),
   THREADNO             INTEGER,
   TASKMODE             VARCHAR2(1),
   PCZT                 VARCHAR2(1),
   SHZT                 VARCHAR2(1),
   NOTE                 VARCHAR2(128),
   BREAKDATA            BLOB,
   EXTFLD1              VARCHAR2(40),
   EXTFLD2              VARCHAR2(40),
   EXTFLD3              VARCHAR2(40),
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

--==============================================================--
-- Index: K_BAT_WBWJDJ_2                                        --
--==============================================================--
create index K_BAT_WBWJDJ_2 on BATCH_HIS_WBWJDJ (
   DJRQ ASC,
   SHPCH ASC
);

--@BATCH_FILETYPE.sql
--@BATCH_FLOWCFG.sql
--UPDATE BATCH_FLOWCFG SET STEPSN=FLOWSN,STEPNAME=STEPID WHERE 1=1;
--commit;
--@BATCH_RUNCTRL.sql
--@BATCH_PLRW.sql
--@BATCH_HIS_PLRW.sql
--@BATCH_PLRWBD.sql
--@BATCH_WBWJDJ.sql
--@BATCH_HIS_WBWJDJ.sql
