--==============================================================
-- Database name:  GAPS4.1_ƽ̨����
-- DBMS name:      ORACLE DATABASE
-- Created on:     2014-11-2 10:32:30
-- Modify on :     2014-11-15 10:56  
--==============================================================
drop table APP_CPJGGX cascade constraints;

drop table APP_CPJYFW cascade constraints;

drop table APP_CPJYGYED cascade constraints;

drop table APP_CPJYGYKZ cascade constraints;

drop table APP_CPJYJGED cascade constraints;

drop table APP_CPPZGX cascade constraints;

drop table APP_CPQDGX cascade constraints;

drop index K_APP_CPSXFGX_1;

drop table APP_CPSXFGX cascade constraints;

drop table APP_CPSXFKZ cascade constraints;

drop table APP_CPXX cascade constraints;

drop table APP_CSKZ cascade constraints;

drop table APP_DICT cascade constraints;

drop index K_APP_DRLS_1;

drop table APP_DRLS cascade constraints;

drop table APP_DWCPXY cascade constraints;

drop table APP_DWXX cascade constraints;

drop table APP_GYSQED cascade constraints;

drop table APP_GYXX cascade constraints;

drop index K_APP_DRLS_2;

drop table APP_HIS_DRLS cascade constraints;

drop table APP_JJRDJ cascade constraints;

drop table APP_JYXX cascade constraints;

drop index K_APP_INDEX_1;

drop table APP_KHCPQY cascade constraints;

drop table APP_KHXX cascade constraints;

drop table APP_KZSX cascade constraints;

drop table APP_MJSJ cascade constraints;

drop table APP_MJSX cascade constraints;

drop table APP_PZGLKZ cascade constraints;

drop table APP_PZHMDJ cascade constraints;

drop table APP_PZSLDJ cascade constraints;

drop index K_APP_PZXX_2;

drop index K_APP_PZXX_1;

drop table APP_PZXX cascade constraints;

drop table APP_PZZL cascade constraints;

drop table APP_QDXX cascade constraints;

drop index INDEX_RWJKB_1;

drop table APP_RWJKB cascade constraints;

drop index K_APP_RZPZ_1;

drop table APP_RZPZ cascade constraints;

drop table APP_SXFFL cascade constraints;

drop index K_APP_SXFLS_1;

drop table APP_SXFLS cascade constraints;

drop index K_APP_SXFWHLS_1;

drop table APP_SXFWHLS cascade constraints;

drop table APP_TXAQXX cascade constraints;

drop table APP_XLKZ cascade constraints;

drop table APP_YWRQ cascade constraints;

drop table APP_YYXX cascade constraints;

/*==============================================================*/
/* Table: APP_CPJGGX                                            */
/*==============================================================*/
create table APP_CPJGGX  
(
   CPDM                 VARCHAR2(16)                    not null,
   JGBH                 VARCHAR2(16)                    not null,
   SJKZBZ               VARCHAR2(1),
   QSSJ                 VARCHAR2(6),
   JSSJ                 VARCHAR2(6),
   WHJG                 VARCHAR2(16),
   WHGY                 VARCHAR2(16),
   WHSJ                 VARCHAR2(14),
   EXTFLD1              VARCHAR2(40),
   EXTFLD2              VARCHAR2(40),
   ZT                   VARCHAR2(1),
   constraint PK_APP_CPJGGX primary key (CPDM, JGBH)
);

comment on table APP_CPJGGX is
'��Ʒ������ϵ��
�����Ʒ��׼�����';

comment on column APP_CPJGGX.CPDM is
'��Ʒ����';

comment on column APP_CPJGGX.JGBH is
'�������';

comment on column APP_CPJGGX.SJKZBZ is
'ʱ����Ʊ�־  0���� 1������';

comment on column APP_CPJGGX.QSSJ is
'��ʼʱ��';

comment on column APP_CPJGGX.JSSJ is
'����ʱ��';

comment on column APP_CPJGGX.EXTFLD1 is
'��չ����1';

comment on column APP_CPJGGX.EXTFLD2 is
'��չ����1';

comment on column APP_CPJGGX.ZT is
'״̬ 0���� 1������';

/*==============================================================*/
/* Table: APP_CPJYFW                                            */
/*==============================================================*/
create table APP_CPJYFW  
(
   CPDM                 VARCHAR2(16)                    not null,
   JYDM                 VARCHAR2(8)                     not null,
   SJKZBZ               VARCHAR2(1),
   QSSJ                 VARCHAR2(6),
   JSSJ                 VARCHAR2(6),
   XEKZBZ               VARCHAR2(1),
   ZXXE                 NUMBER(16,2),
   ZDXE                 NUMBER(16,2),
   QYKZBZ               VARCHAR2(1),
   QXKZ                 VARCHAR2(8),
   QYEDKZFS             VARCHAR2(1),
   JGEDKZFS             VARCHAR2(1),
   WHJG                 VARCHAR2(16),
   WHGY                 VARCHAR2(16),
   WHSJ                 VARCHAR2(14),
   EXTFLD1              VARCHAR2(40),
   EXTFLD2              VARCHAR2(40),
   QTBZ                 VARCHAR2(1),
   constraint PK_APP_CPJYFW primary key (CPDM, JYDM)
);

comment on table APP_CPJYFW is
'��Ʒ���׷����ϵ��';

comment on column APP_CPJYFW.CPDM is
'��Ʒ����';

comment on column APP_CPJYFW.JYDM is
'���״���';

comment on column APP_CPJYFW.SJKZBZ is
'ʱ����Ʊ�־  0���� 1������';

comment on column APP_CPJYFW.QSSJ is
'��ʼʱ�� hhmmss';

comment on column APP_CPJYFW.JSSJ is
'����ʱ�� hhmmss';

comment on column APP_CPJYFW.XEKZBZ is
'�޶���Ʊ�־ 0���� 1������';

comment on column APP_CPJYFW.ZXXE is
'��С�޶�';

comment on column APP_CPJYFW.ZDXE is
'����޶�';

comment on column APP_CPJYFW.QYKZBZ is
'ǩԼ��ϵ����  0У�� 1��У��';

comment on column APP_CPJYFW.QXKZ is
'��һλ ��Ա��λ�������    0 ������ 1����
�ڶ�λ ��Ա���ʶ�ȿ���    0 ������ 1����
����λ ��Ա���ۼƶ�ȿ���  0 ������ 1����
����λ ��Ա���ۼƶ�ȿ���  0 ������ 1����
����λ �������ʶ�ȿ���    0������ 1 ����
����λ �������ۼƶ�ȿ���  0������ 1 ����
����λ �������ۼƶ�ȿ���  0������ 1 ����
Ĭ�϶��� 0 ������
';

comment on column APP_CPJYFW.QYEDKZFS is
'��Ա��ȿ��Ʒ�ʽ    0������ 1 ���Ƽ��� 9�������л���';

comment on column APP_CPJYFW.JGEDKZFS is
'������ȿ��Ʒ�ʽ    0������ 1 ���Ƽ��� 9�������л���';

comment on column APP_CPJYFW.EXTFLD1 is
'��չ����1';

comment on column APP_CPJYFW.EXTFLD2 is
'��չ����1';

comment on column APP_CPJYFW.QTBZ is
'��ͣ��־ 0���� 1�ر�';

/*==============================================================*/
/* Table: APP_CPJYGYED                                          */
/*==============================================================*/
create table APP_CPJYGYED  
(
   CPDM                 VARCHAR2(16)                    not null,
   JYDM                 VARCHAR2(8)                     not null,
   JYBZ                 VARCHAR2(3)                     not null,
   DBEDKZ               VARCHAR2(1),
   RLJEDKZ              VARCHAR2(1),
   YLJEDKZ              VARCHAR2(1),
   GYJB                 VARCHAR2(2)                     not null,
   DBED                 NUMBER(16,2),
   YLJED                NUMBER(16,2),
   RLJED                NUMBER(16,2),
   CXCL                 VARCHAR2(1),
   SQGYGW               VARCHAR2(8),
   SQGYJB               VARCHAR2(2),
   WHJG                 VARCHAR2(16),
   WHGY                 VARCHAR2(16),
   WHSJ                 VARCHAR2(14),
   EXTFLD1              VARCHAR2(40),
   EXTFLD2              VARCHAR2(40),
   constraint PK_APP_CPJYGYED primary key (CPDM, JYDM, JYBZ, GYJB)
);

comment on table APP_CPJYGYED is
'��Ʒ��Ա���׶�ȿ��Ʊ�';

comment on column APP_CPJYGYED.CPDM is
'��Ʒ����';

comment on column APP_CPJYGYED.JYDM is
'���״���';

comment on column APP_CPJYGYED.DBEDKZ is
'0 ������ 1���Ƽ��� 9�������й�Ա';

comment on column APP_CPJYGYED.RLJEDKZ is
'0 ������ 1���Ƽ��� 9�������й�Ա';

comment on column APP_CPJYGYED.YLJEDKZ is
'0 ������ 1���Ƽ��� 9�������й�Ա';

comment on column APP_CPJYGYED.GYJB is
'�����ֵ�K_APP_GYJB';

comment on column APP_CPJYGYED.CXCL is
'0 ���׾ܾ� 1 �����Ȩ��Ա���� 2 �����Ȩ��Ա��λ 3 �����Ȩ��Ա����͸�λ';

comment on column APP_CPJYGYED.EXTFLD1 is
'��չ����1';

comment on column APP_CPJYGYED.EXTFLD2 is
'��չ����1';

/*==============================================================*/
/* Table: APP_CPJYGYKZ                                          */
/*==============================================================*/
create table APP_CPJYGYKZ  
(
   CPDM                 VARCHAR2(16)                    not null,
   JYDM                 VARCHAR2(8)                     not null,
   KZBZ                 VARCHAR2(1),
   GYJB                 VARCHAR2(2)                     not null,
   CXCL                 VARCHAR2(1),
   SQGYGW               VARCHAR2(8),
   SQGYJB               VARCHAR2(2),
   WHJG                 VARCHAR2(16),
   WHGY                 VARCHAR2(16),
   WHSJ                 VARCHAR2(14),
   EXTFLD1              VARCHAR2(40),
   EXTFLD2              VARCHAR2(40),
   constraint PK_APP_CPJYGYKZ primary key (CPDM, JYDM)
);

comment on table APP_CPJYGYKZ is
'��Ʒ��Ա���׸�λ������Ʊ�';

comment on column APP_CPJYGYKZ.CPDM is
'��Ʒ����';

comment on column APP_CPJYGYKZ.JYDM is
'���״���';

comment on column APP_CPJYGYKZ.KZBZ is
'0 ������ 1����';

comment on column APP_CPJYGYKZ.GYJB is
'�����ֵ� K_APP_GYJB';

comment on column APP_CPJYGYKZ.CXCL is
'0 ���׾ܾ� 1 �����Ȩ��Ա���� 2 �����Ȩ��Ա��λ 3 �����Ȩ��Ա����͸�λ';

comment on column APP_CPJYGYKZ.SQGYGW is
'�����ֵ�K_APP_GYGW';

comment on column APP_CPJYGYKZ.SQGYJB is
'�����ֵ�K_APP_GYJB';

comment on column APP_CPJYGYKZ.EXTFLD1 is
'��չ����1';

comment on column APP_CPJYGYKZ.EXTFLD2 is
'��չ����1';

/*==============================================================*/
/* Table: APP_CPJYJGED                                          */
/*==============================================================*/
create table APP_CPJYJGED  
(
   CPDM                 VARCHAR2(16)                    not null,
   JYDM                 VARCHAR2(8)                     not null,
   JYBZ                 VARCHAR2(3)                     not null,
   DBEDKZ               VARCHAR2(1),
   RLJEDKZ              VARCHAR2(1),
   YLJEDKZ              VARCHAR2(1),
   JGJB                 VARCHAR2(16)                    not null,
   DBED                 NUMBER(16,2),
   YLJED                NUMBER(16,2),
   RLJED                NUMBER(16,2),
   CXCL                 VARCHAR2(1),
   SQGYGW               VARCHAR2(8),
   SQGYJB               VARCHAR2(2),
   WHJG                 VARCHAR2(16),
   WHGY                 VARCHAR2(16),
   WHSJ                 VARCHAR2(14),
   EXTFLD1              VARCHAR2(40),
   EXTFLD2              VARCHAR2(40),
   constraint PK_APP_CPJYJGED primary key (CPDM, JYDM, JYBZ, JGJB)
);

comment on table APP_CPJYJGED is
'��Ʒ�������׶�ȿ��Ʊ�';

comment on column APP_CPJYJGED.CPDM is
'��Ʒ����';

comment on column APP_CPJYJGED.JYDM is
'���״���';

comment on column APP_CPJYJGED.DBEDKZ is
'0 ������ 1���Ƽ��� 9�������л���';

comment on column APP_CPJYJGED.RLJEDKZ is
'0 ������ 1���Ƽ��� 9�������л���';

comment on column APP_CPJYJGED.YLJEDKZ is
'0 ������ 1���Ƽ��� 9�������л���';

comment on column APP_CPJYJGED.CXCL is
'0 ���׾ܾ� 1 �����Ȩ��Ա���� 2 �����Ȩ��Ա��λ 3 �����Ȩ��Ա����͸�λ';

comment on column APP_CPJYJGED.EXTFLD1 is
'��չ����1';

comment on column APP_CPJYJGED.EXTFLD2 is
'��չ����1';

/*==============================================================*/
/* Table: APP_CPPZGX                                            */
/*==============================================================*/
create table APP_CPPZGX  
(
   CPDM                 VARCHAR2(16)                    not null,
   PZXH                 INTEGER                         not null,
   PZZL                 VARCHAR2(3)                     not null,
   CPPZSM               VARCHAR2(40),
   WHJG                 VARCHAR2(16),
   WHGY                 VARCHAR2(16),
   WHSJ                 VARCHAR2(14),
   EXTFLD1              VARCHAR2(40),
   EXTFLD2              VARCHAR2(40),
   constraint PK_APP_CPPZGX primary key (CPDM, PZXH)
);

comment on table APP_CPPZGX is
'��Ʒƾ֤��ϵ��';

comment on column APP_CPPZGX.CPDM is
'��Ʒ����';

comment on column APP_CPPZGX.PZXH is
'ƾ֤���';

comment on column APP_CPPZGX.PZZL is
'ƾ֤����';

comment on column APP_CPPZGX.CPPZSM is
'��Ʒƾ֤˵��';

comment on column APP_CPPZGX.EXTFLD1 is
'��չ�ֶ�';

comment on column APP_CPPZGX.EXTFLD2 is
'��չ�ֶ�2';

/*==============================================================*/
/* Table: APP_CPQDGX                                            */
/*==============================================================*/
create table APP_CPQDGX  
(
   CPDM                 VARCHAR2(16)                    not null,
   QDBS                 VARCHAR2(3)                     not null,
   SJKZBZ               VARCHAR2(1),
   QSSJ                 VARCHAR2(6),
   JSSJ                 VARCHAR2(6),
   XEKZBZ               VARCHAR2(1),
   ZXXE                 NUMBER(16,2),
   ZDXE                 NUMBER(16,2),
   CZBZ                 VARCHAR2(1),
   ZDCZBZ               VARCHAR2(1),
   FPBCBZ               VARCHAR2(1),
   FPCSFS               VARCHAR2(1),
   WHJG                 VARCHAR2(16),
   WHGY                 VARCHAR2(16),
   WHSJ                 VARCHAR2(14),
   EXTFLD1              VARCHAR2(40),
   EXTFLD2              VARCHAR2(40),
   ZT                   VARCHAR2(1),
   constraint PK_APP_CPQDGX primary key (CPDM, QDBS)
);

comment on table APP_CPQDGX is
'��Ʒ������ϵ��';

comment on column APP_CPQDGX.CPDM is
'��Ʒ����';

comment on column APP_CPQDGX.QDBS is
'������ʶ';

comment on column APP_CPQDGX.SJKZBZ is
'ʱ����Ʊ�־  0���� 1������';

comment on column APP_CPQDGX.QSSJ is
'��ʼʱ��';

comment on column APP_CPQDGX.JSSJ is
'����ʱ��';

comment on column APP_CPQDGX.XEKZBZ is
'�޶���Ʊ�־ 0���� 1������';

comment on column APP_CPQDGX.ZXXE is
'��С�޶�';

comment on column APP_CPQDGX.ZDXE is
'����޶�';

comment on column APP_CPQDGX.CZBZ is
'�Ƿ��������  0���� 1������';

comment on column APP_CPQDGX.ZDCZBZ is
'                0��������  
                1���첽����
                2��ͬ������
                3���ط�';

comment on column APP_CPQDGX.FPBCBZ is
'��Ʊ�����־ 0���� 1������';

comment on column APP_CPQDGX.FPCSFS is
'��Ʊ���䷽ʽ 0���� 1�ļ�';

comment on column APP_CPQDGX.EXTFLD1 is
'��չ����1';

comment on column APP_CPQDGX.EXTFLD2 is
'��չ����2';

comment on column APP_CPQDGX.ZT is
'״̬ 0���� 1������';

/*==============================================================*/
/* Table: APP_CPSXFGX                                           */
/*==============================================================*/
create table APP_CPSXFGX  
(
   CPDM                 VARCHAR2(16)                    not null,
   KZTJ1                VARCHAR2(32),
   KZTJ2                VARCHAR2(32),
   KZTJ3                VARCHAR2(32),
   KZTJ4                VARCHAR2(32),
   KZTJ5                VARCHAR2(32),
   KZTJ6                VARCHAR2(32),
   KZTJ7                VARCHAR2(32),
   KZTJ8                VARCHAR2(32),
   KZTJ9                VARCHAR2(32),
   KZTJ10               VARCHAR2(32),
   FLBS                 VARCHAR2(32)                    not null,
   QYRQ                 VARCHAR2(8)                     not null,
   SXRQ                 VARCHAR2(8)                     not null,
   WHJG                 VARCHAR2(16),
   WHGY                 VARCHAR2(16),
   WHSJ                 VARCHAR2(14),
   EXTFLD1              VARCHAR2(20),
   EXTFLD2              VARCHAR2(40),
   SM                   VARCHAR2(40)
);

comment on table APP_CPSXFGX is
'���ݲ�Ʒ�����ѿ������ԣ�������Ʒ�������ѵĹ�ϵ';

comment on column APP_CPSXFGX.CPDM is
'��Ʒ����';

comment on column APP_CPSXFGX.KZTJ1 is
'�Ӳ�Ʒ�����ѿ��Ʊ��л�ȡ�Ŀ�������';

comment on column APP_CPSXFGX.KZTJ2 is
'�Ӳ�Ʒ�����ѿ��Ʊ��л�ȡ�Ŀ�������';

comment on column APP_CPSXFGX.KZTJ3 is
'�Ӳ�Ʒ�����ѿ��Ʊ��л�ȡ�Ŀ�������';

comment on column APP_CPSXFGX.KZTJ4 is
'�Ӳ�Ʒ�����ѿ��Ʊ��л�ȡ�Ŀ�������';

comment on column APP_CPSXFGX.KZTJ5 is
'�Ӳ�Ʒ�����ѿ��Ʊ��л�ȡ�Ŀ�������';

comment on column APP_CPSXFGX.KZTJ6 is
'�Ӳ�Ʒ�����ѿ��Ʊ��л�ȡ�Ŀ�������';

comment on column APP_CPSXFGX.KZTJ7 is
'�Ӳ�Ʒ�����ѿ��Ʊ��л�ȡ�Ŀ�������';

comment on column APP_CPSXFGX.KZTJ8 is
'�Ӳ�Ʒ�����ѿ��Ʊ��л�ȡ�Ŀ�������';

comment on column APP_CPSXFGX.KZTJ9 is
'�Ӳ�Ʒ�����ѿ��Ʊ��л�ȡ�Ŀ�������';

comment on column APP_CPSXFGX.KZTJ10 is
'�Ӳ�Ʒ�����ѿ��Ʊ��л�ȡ�Ŀ�������';

comment on column APP_CPSXFGX.FLBS is
'���ʱ�ʶ';

comment on column APP_CPSXFGX.QYRQ is
'������������';

comment on column APP_CPSXFGX.SXRQ is
'����ʧЧ����';

/*==============================================================*/
/* Index: K_APP_CPSXFGX_1                                       */
/*==============================================================*/
create unique index K_APP_CPSXFGX_1 on APP_CPSXFGX (
   CPDM ASC,
   KZTJ1 ASC,
   KZTJ2 ASC,
   KZTJ3 ASC,
   KZTJ4 ASC,
   KZTJ5 ASC,
   FLBS ASC,
   QYRQ ASC,
   SXRQ ASC
);

/*==============================================================*/
/* Table: APP_CPSXFKZ                                           */
/*==============================================================*/
create table APP_CPSXFKZ  
(
   CPDM                 VARCHAR2(16)                    not null,
   XH                   VARCHAR2(2),
   KZSX                 VARCHAR2(32)                    not null,
   KZSXM                VARCHAR2(40)                    not null,
   SXLYLX               VARCHAR2(1),
   KZSXLY               VARCHAR2(40),
   WHJG                 VARCHAR2(16),
   WHGY                 VARCHAR2(16),
   WHSJ                 VARCHAR2(14),
   EXTFLD1              VARCHAR2(40),
   EXTFLD2              VARCHAR2(40),
   constraint PK_APP_CPSXFKZ primary key (CPDM, KZSX)
);

comment on table APP_CPSXFKZ is
'�����ѿ��Ʊ�';

comment on column APP_CPSXFKZ.CPDM is
'��Ʒ����';

comment on column APP_CPSXFKZ.XH is
'��Ʒ�ж����������ʱ���������Զ�����������У���1��ʼ�����ϵ�������λ�ö�Ӧ';

comment on column APP_CPSXFKZ.KZSX is
'�磺/app/sxf/khlx';

comment on column APP_CPSXFKZ.KZSXM is
'�������Ե�����˵��';

comment on column APP_CPSXFKZ.SXLYLX is
'��������ֵ����Դ��1 ���ݿ� 2 �����ֵ䣬����ά�������ѹ�ϵʱѡ��������Ե�������Դ';

comment on column APP_CPSXFKZ.KZSXLY is
'�����Դ����Ϊ �����ֵ䣬����ֵ��ֵ;�����Դ�����ݿ⣬��ſ������ֶ����м䶺�Ÿ���,�� T_ORG,org_id  ��ʾ�����������Ի�����Ļ�����';

comment on column APP_CPSXFKZ.EXTFLD1 is
'˵�� ';

comment on column APP_CPSXFKZ.EXTFLD2 is
'˵�� ';

/*==============================================================*/
/* Table: APP_CPXX                                              */
/*==============================================================*/
create table APP_CPXX  
(
   CPDM                 VARCHAR2(16)                    not null,
   CPMC                 VARCHAR2(40),
   YYBS                 VARCHAR2(8),
   ZBJG                 VARCHAR2(16),
   ZBGY                 VARCHAR2(16),
   KHJL                 VARCHAR2(20),
   YWRQLX               VARCHAR2(1),
   QDKZBZ               VARCHAR2(1),
   JGKZCS               VARCHAR2(1),
   SXFBZ                VARCHAR2(1),
   SFQYBZ               VARCHAR2(1),
   QYMS                 VARCHAR2(1),
   XYXLJZ               VARCHAR2(16),
   KKFS                 VARCHAR2(1),
   JZSX                 VARCHAR2(1),
   DZMS                 VARCHAR2(1),
   ZJYYH                VARCHAR2(16),
   ZJZYYH               VARCHAR2(16),
   LSBLTS               INTEGER,
   PDBLTS               INTEGER,
   JYFS                 VARCHAR2(1),
   RZMS                 VARCHAR2(1),
   WHJG                 VARCHAR2(16),
   WHGY                 VARCHAR2(16),
   WHSJ                 VARCHAR2(14),
   EXTFLD1              VARCHAR2(40),
   EXTFLD2              VARCHAR2(40),
   CPZT                 VARCHAR2(1),
   constraint PK_APP_CPXX primary key (CPDM)
);

comment on table APP_CPXX is
'ά����Ʒ��ͨ������';

comment on column APP_CPXX.CPDM is
'��Ʒ����';

comment on column APP_CPXX.CPMC is
'��Ʒ����';

comment on column APP_CPXX.ZBJG is
'�������';

comment on column APP_CPXX.ZBGY is
'�����Ա';

comment on column APP_CPXX.KHJL is
'�ͻ�����';

comment on column APP_CPXX.YWRQLX is
'ҵ���������� 1���� 2˽�� Ĭ�� 1';

comment on column APP_CPXX.QDKZBZ is
'�������Ʊ�־ 0���� 1������ Ĭ��1';

comment on column APP_CPXX.JGKZCS is
'�������Ʋ��� �������ֵ� KEY=K_JGKZCS Ĭ��0 ������';

comment on column APP_CPXX.SXFBZ is
'��������ȡ��־ 0��ȡ 1���� Ĭ��1';

comment on column APP_CPXX.SFQYBZ is
'0����ҪǩԼ��1 ������ǩԼ��2����ǩԼ��3 ͬʱǩԼ  Ĭ��0 ';

comment on column APP_CPXX.QYMS is
'1  ��Ʒ���룫�����ʺ� 2 ��Ʒ���룫�û��� 3 ��Ʒ���룫�����ʺţ��û���  Ĭ��2';

comment on column APP_CPXX.XYXLJZ is
'Э�����м�ֵ Ĭ�� K_KHCPQY';

comment on column APP_CPXX.KKFS is
'1ȫ��ۿ2 ���ֿۿ� Ĭ��1';

comment on column APP_CPXX.JZSX is
'����˳��0�����������ϵ�������Ĭ�ϣ�
                    1���ϵ�������������';

comment on column APP_CPXX.DZMS is
'����ģʽ 1����Ϊ�� 2������Ϊ��';

comment on column APP_CPXX.LSBLTS is
'��ˮ��������';

comment on column APP_CPXX.PDBLTS is
'ƾ����������';

comment on column APP_CPXX.JYFS is
'���׷�ʽ �������ֵ� KEY=K_JYFS';

comment on column APP_CPXX.RZMS is
'0����  1 ���� Ĭ�� 1';

comment on column APP_CPXX.EXTFLD1 is
'��չ����1';

comment on column APP_CPXX.EXTFLD2 is
'��չ����2';

comment on column APP_CPXX.CPZT is
'��Ʒ״̬ �������ֵ� KEY=K_CPZT';

/*==============================================================*/
/* Table: APP_CSKZ                                              */
/*==============================================================*/
create table APP_CSKZ  
(
   CSJZ                 VARCHAR2(20)                    not null,
   CSLX                 VARCHAR2(1),
   CSTJ                 VARCHAR2(8),
   JDM                  VARCHAR2(80)                    not null,
   JDZ                  VARCHAR2(40)                    not null,
   REMARK               VARCHAR2(40),
   JZLX                 VARCHAR2(1),
   WHJG                 VARCHAR2(16),
   WHGY                 VARCHAR2(16),
   WHSJ                 VARCHAR2(14),
   constraint PK_APP_CSKZ primary key (CSJZ)
);

comment on table APP_CSKZ is
'�������Ʊ�';

comment on column APP_CSKZ.CSJZ is
'������ֵ';

comment on column APP_CSKZ.CSLX is
'�������� �������ֵ� KEY=K_CSLX';

comment on column APP_CSKZ.CSTJ is
'�������� �������Ϊ����������������ʶ���ΪӦ������Ӧ�ñ�ʶ';

comment on column APP_CSKZ.JDM is
'�ڵ���';

comment on column APP_CSKZ.JDZ is
'�ڵ�ֵ';

comment on column APP_CSKZ.REMARK is
'˵��';

comment on column APP_CSKZ.JZLX is
'�������� 0�Զ� 1���Զ�';

/*==============================================================*/
/* Table: APP_DICT                                              */
/*==============================================================*/
create table APP_DICT  
(
   PKEY                 VARCHAR2(20)                    not null,
   KEYJS                VARCHAR2(30)                    not null,
   PVAL                 VARCHAR2(20)                    not null,
   PROMPT               VARCHAR2(60)                    not null,
   SSYY                 VARCHAR2(8)                     not null,
   WHJG                 VARCHAR2(16),
   WHGY                 VARCHAR2(16),
   WHSJ                 VARCHAR2(14),
   constraint PK_APP_DICT primary key (PKEY, PVAL)
);

comment on table APP_DICT is
'�����ֵ��';

comment on column APP_DICT.KEYJS is
'KEYֵ����';

comment on column APP_DICT.SSYY is
'Ӧ�ñ�ʶ';

/*==============================================================*/
/* Table: APP_DRLS                                              */
/*==============================================================*/
create table APP_DRLS  
(
   PTRQ                 VARCHAR2(8)                     not null,
   PTLS                 INTEGER                         not null,
   PTSJ                 VARCHAR2(6),
   RZBZ                 VARCHAR2(1),
   JYLX                 VARCHAR2(1),
   YPTLS                INTEGER,
   JYJG                 VARCHAR2(16),
   JYGY                 VARCHAR2(16),
   QDBS                 VARCHAR2(3),
   ZDSBBH               VARCHAR2(8),
   YYBS                 VARCHAR2(8),
   CPDM                 VARCHAR2(16),
   YWBH                 VARCHAR2(16),
   JYDM                 VARCHAR2(8),
   YHBH                 VARCHAR2(32),
   XZBZ                 VARCHAR2(1),
   JDBZ                 VARCHAR2(1),
   ZHLX                 VARCHAR2(2),
   YHZH                 VARCHAR2(32),
   DFZH                 VARCHAR2(32),
   JYJE                 NUMBER(16,2),
   SXF                  NUMBER(16,2),
   PCBH                 INTEGER,
   JYXYM                VARCHAR2(8),
   JYXYXX               VARCHAR2(60),
   JYZT                 VARCHAR2(1),
   EXTFLD1              VARCHAR2(40),
   EXTFLD2              VARCHAR2(40),
   constraint PK_APP_DRLS primary key (PTRQ, PTLS)
);

comment on table APP_DRLS is
'ƽ̨������ˮ��';

comment on column APP_DRLS.PTRQ is
'ƽ̨���� YYYYMMDD';

comment on column APP_DRLS.PTLS is
'ƽ̨��ˮ��';

comment on column APP_DRLS.PTSJ is
'ƽ̨ʱ�� HHMMSS';

comment on column APP_DRLS.RZBZ is
'���ʱ�־ 0���� 1������';

comment on column APP_DRLS.JYLX is
'�������� 0������ 1������ 9����';

comment on column APP_DRLS.YPTLS is
'ԭƽ̨��ˮ��';

comment on column APP_DRLS.JYJG is
'���׻���';

comment on column APP_DRLS.JYGY is
'���׹�Ա';

comment on column APP_DRLS.QDBS is
'������ʶ ';

comment on column APP_DRLS.ZDSBBH is
'�ն��豸���';

comment on column APP_DRLS.YYBS is
'Ӧ�ñ�ʶ ';

comment on column APP_DRLS.CPDM is
'��Ʒ����';

comment on column APP_DRLS.YWBH is
'ҵ����';

comment on column APP_DRLS.JYDM is
'���״���';

comment on column APP_DRLS.YHBH is
'�û���� ���ֻ���';

comment on column APP_DRLS.XZBZ is
'��ת��־  0�ֽ� 1ת��';

comment on column APP_DRLS.JDBZ is
'�����־  �������ֵ�KEY=K_JDBZ';

comment on column APP_DRLS.ZHLX is
'�ʻ�����  �������ֵ�KEY=K_ZHLX';

comment on column APP_DRLS.YHZH is
'�����ʺ�';

comment on column APP_DRLS.DFZH is
'�Է��ʺ�';

comment on column APP_DRLS.JYJE is
'���׽��';

comment on column APP_DRLS.SXF is
'������';

comment on column APP_DRLS.PCBH is
'���α��';

comment on column APP_DRLS.JYXYM is
'������Ӧ��';

comment on column APP_DRLS.JYXYXX is
'������Ӧ��Ϣ';

comment on column APP_DRLS.JYZT is
'����״̬�������ֵ�KEY=K_JYZT';

comment on column APP_DRLS.EXTFLD1 is
'��չ1';

comment on column APP_DRLS.EXTFLD2 is
'��չ2';

/*==============================================================*/
/* Index: K_APP_DRLS_1                                          */
/*==============================================================*/
create index K_APP_DRLS_1 on APP_DRLS (
   PTRQ ASC,
   PTLS ASC,
   YWBH ASC
);

/*==============================================================*/
/* Table: APP_DWCPXY                                            */
/*==============================================================*/
create table APP_DWCPXY  
(
   DWBH                 VARCHAR2(16)                    not null,
   CPDM                 VARCHAR2(16)                    not null,
   YWBH                 VARCHAR2(16)                    not null,
   YWMC                 VARCHAR2(40),
   XYBH                 VARCHAR2(20),
   YHDM                 VARCHAR2(16),
   LJBS                 VARCHAR2(8),
   ZHLX                 VARCHAR2(2),
   SFBZ                 VARCHAR2(1),
   DSZH                 VARCHAR2(32),
   DSZHMC               VARCHAR2(80),
   DFZH                 VARCHAR2(32),
   DFZHMC               VARCHAR2(80),
   KHJL                 VARCHAR2(20),
   LXR                  VARCHAR2(20),
   EMAIL                VARCHAR2(32),
   LXDH                 VARCHAR2(16),
   HYKSRQ               VARCHAR2(8),
   HYJSRQ               VARCHAR2(8),
   BLJG                 VARCHAR2(16),
   BLGY                 VARCHAR2(16),
   BLRQ                 VARCHAR2(8),
   ZHZDED               NUMBER(16,2),
   WHJG                 VARCHAR2(16),
   WHGY                 VARCHAR2(16),
   WHSJ                 VARCHAR2(14),
   EXTFLD1              VARCHAR2(40),
   EXTFLD2              VARCHAR2(40),
   QYZT                 VARCHAR2(1),
   constraint PK_APP_DWCPXY primary key (YWBH),
   constraint AK_K_APP_CPDWXY_1_APP_DWCP unique (DWBH, CPDM)
);

comment on table APP_DWCPXY is
'��λ��ƷЭ���';

comment on column APP_DWCPXY.DWBH is
'��λ���';

comment on column APP_DWCPXY.CPDM is
'��Ʒ����';

comment on column APP_DWCPXY.YWBH is
'ҵ���� ���ո�ҵ�������ҵ���ţ�����ͨ������';

comment on column APP_DWCPXY.XYBH is
'��ͬ���';

comment on column APP_DWCPXY.YHDM is
'�����ڵ������ı���';

comment on column APP_DWCPXY.ZHLX is
'�˻����� �������ֵ� KEY=K_ZHLX';

comment on column APP_DWCPXY.SFBZ is
'1 �� 2 �� 3 ���� 
�������ֵ� K_SFBZ';

comment on column APP_DWCPXY.DSZH is
'ǩԼ�˻�';

comment on column APP_DWCPXY.DSZHMC is
'�˻�����';

comment on column APP_DWCPXY.DFZH is
'ǩԼ�˻�';

comment on column APP_DWCPXY.DFZHMC is
'�˻�����';

comment on column APP_DWCPXY.KHJL is
'�ͻ�����';

comment on column APP_DWCPXY.HYKSRQ is
'��Լ��ʼ����';

comment on column APP_DWCPXY.HYJSRQ is
'��Լ��������';

comment on column APP_DWCPXY.BLJG is
'�������';

comment on column APP_DWCPXY.BLGY is
'�����Ա';

comment on column APP_DWCPXY.BLRQ is
'��������';

comment on column APP_DWCPXY.ZHZDED is
'�˻���Ͷ��';

comment on column APP_DWCPXY.EXTFLD1 is
'��չ����1';

comment on column APP_DWCPXY.EXTFLD2 is
'��չ����2';

comment on column APP_DWCPXY.QYZT is
'ǩԼ״̬ 0���� 1����';

/*==============================================================*/
/* Table: APP_DWXX                                              */
/*==============================================================*/
create table APP_DWXX  
(
   DWBH                 VARCHAR2(16)                    not null,
   DWMC                 VARCHAR2(80),
   DWZJLX               VARCHAR2(2),
   DWZJHM               VARCHAR2(32),
   DWLXR                VARCHAR2(16),
   DWLXRDH              VARCHAR2(16),
   DWDZ                 VARCHAR2(60),
   DWEMAIL              VARCHAR2(32),
   WHJG                 VARCHAR2(16),
   WHGY                 VARCHAR2(16),
   WHSJ                 VARCHAR2(14),
   EXTFLD1              VARCHAR2(40),
   EXTFLD2              VARCHAR2(40),
   ZT                   VARCHAR2(1),
   constraint PK_APP_DWXX primary key (DWBH)
);

comment on table APP_DWXX is
'��λ��Ϣ��';

comment on column APP_DWXX.DWMC is
'��λ����';

comment on column APP_DWXX.DWZJLX is
'��λ֤������ �������ֵ� KEY=K_DWZJLX';

comment on column APP_DWXX.DWZJHM is
'��λ֤������';

comment on column APP_DWXX.DWLXR is
'��λ��ϵ������';

comment on column APP_DWXX.DWLXRDH is
'��λ��ϵ�˵绰';

comment on column APP_DWXX.DWDZ is
'��λ��ϵ��ַ';

comment on column APP_DWXX.DWEMAIL is
'��λ��ϵemail';

comment on column APP_DWXX.EXTFLD1 is
'��չ����1';

comment on column APP_DWXX.EXTFLD2 is
'��չ����2';

comment on column APP_DWXX.ZT is
'״̬ 0 ���� Xɾ��';

/*==============================================================*/
/* Table: APP_GYSQED                                            */
/*==============================================================*/
create table APP_GYSQED  
(
   CPDM                 VARCHAR2(16)                    not null,
   JYDM                 VARCHAR2(8)                     not null,
   GYJB                 VARCHAR2(8)                     not null,
   GYGW                 VARCHAR2(8)                     not null,
   JYBZ                 VARCHAR2(3)                     not null,
   GYDBSQED             NUMBER(16,2),
   GYRLJSQED            NUMBER(16,2),
   GYYLJSQED            NUMBER(16,2),
   JGDBSQED             NUMBER(16,2),
   JGRLJSQED            NUMBER(16,2),
   JGYLJSQED            NUMBER(16,2),
   EXTFLD1              VARCHAR2(40),
   EXTFLD2              VARCHAR2(40),
   constraint PK_APP_GYSQED primary key (CPDM, JYDM, GYJB, GYGW, JYBZ)
);

comment on table APP_GYSQED is
'��Ա��Ʒ��Ȩ��ȱ�';

comment on column APP_GYSQED.CPDM is
'��Ʒ����';

comment on column APP_GYSQED.JYDM is
'���״���';

comment on column APP_GYSQED.GYJB is
'��Ա����';

comment on column APP_GYSQED.GYGW is
'��Ա��λ';

comment on column APP_GYSQED.JYBZ is
'���ױ���';

comment on column APP_GYSQED.GYDBSQED is
'��Ա���ʶ��';

comment on column APP_GYSQED.GYRLJSQED is
'��Ա���ۼƶ��';

comment on column APP_GYSQED.GYYLJSQED is
'��Ա���ۼƶ��';

comment on column APP_GYSQED.JGDBSQED is
'�������ʶ��';

comment on column APP_GYSQED.JGRLJSQED is
'�������ۼƶ��';

comment on column APP_GYSQED.JGYLJSQED is
'�����ۼƶ��';

comment on column APP_GYSQED.EXTFLD1 is
'��չ����1';

comment on column APP_GYSQED.EXTFLD2 is
'��չ����2';

/*==============================================================*/
/* Table: APP_GYXX                                              */
/*==============================================================*/
create table APP_GYXX  
(
   GYH                  VARCHAR2(16)                    not null,
   JGBH                 VARCHAR2(16),
   MM                   VARCHAR2(32),
   GYJB                 VARCHAR2(2),
   GYGW                 VARCHAR2(32),
   GYMC                 VARCHAR2(16),
   EMAIL                VARCHAR2(32),
   FAX                  VARCHAR2(16),
   TEL                  VARCHAR2(16),
   WHJG                 VARCHAR2(16),
   WHGY                 VARCHAR2(16),
   WHSJ                 VARCHAR2(14),
   EXTFLD1              VARCHAR2(40),
   EXTFLD2              VARCHAR2(40),
   ZT                   VARCHAR2(1),
   constraint PK_APP_GYXX primary key (GYH)
);

comment on table APP_GYXX is
'��Ա��Ϣ��';

comment on column APP_GYXX.GYH is
'��Ա��';

comment on column APP_GYXX.JGBH is
'�������';

comment on column APP_GYXX.MM is
'��Ա����';

comment on column APP_GYXX.GYJB is
'��Ա����';

comment on column APP_GYXX.GYGW is
'��Ա��λ';

comment on column APP_GYXX.GYMC is
'��Ա����';

comment on column APP_GYXX.EMAIL is
'email��ַ';

comment on column APP_GYXX.FAX is
'����';

comment on column APP_GYXX.TEL is
'�绰';

comment on column APP_GYXX.EXTFLD1 is
'��չ����1';

comment on column APP_GYXX.EXTFLD2 is
'��չ����2';

comment on column APP_GYXX.ZT is
'״̬';

/*==============================================================*/
/* Table: APP_HIS_DRLS                                          */
/*==============================================================*/
create table APP_HIS_DRLS  
(
   PTRQ                 VARCHAR2(8)                     not null,
   PTLS                 INTEGER                         not null,
   PTSJ                 VARCHAR2(6),
   RZBZ                 VARCHAR2(1),
   JYLX                 VARCHAR2(1),
   YPTLS                INTEGER,
   JYJG                 VARCHAR2(16),
   JYGY                 VARCHAR2(16),
   QDBS                 VARCHAR2(3),
   ZDSBBH               VARCHAR2(8),
   YYBS                 VARCHAR2(8),
   CPDM                 VARCHAR2(16),
   YWBH                 VARCHAR2(16),
   JYDM                 VARCHAR2(8),
   YHBH                 VARCHAR2(32),
   XZBZ                 VARCHAR2(1),
   JDBZ                 VARCHAR2(1),
   ZHLX                 VARCHAR2(2),
   YHZH                 VARCHAR2(32),
   DFZH                 VARCHAR2(32),
   JYJE                 NUMBER(16,2),
   SXF                  NUMBER(16,2),
   PCBH                 INTEGER,
   JYXYM                VARCHAR2(8),
   JYXYXX               VARCHAR2(60),
   JYZT                 VARCHAR2(1),
   EXTFLD1              VARCHAR2(40),
   EXTFLD2              VARCHAR2(40),
   constraint PK_APP_HIS_DRLS primary key (PTRQ, PTLS)
);

comment on table APP_HIS_DRLS is
'ƽ̨������ˮ����ʷ��';

comment on column APP_HIS_DRLS.PTRQ is
'ƽ̨���� YYYYMMDD';

comment on column APP_HIS_DRLS.PTLS is
'ƽ̨��ˮ��';

comment on column APP_HIS_DRLS.PTSJ is
'ƽ̨ʱ�� HHMMSS';

comment on column APP_HIS_DRLS.RZBZ is
'���ʱ�־ 0���� 1������';

comment on column APP_HIS_DRLS.JYLX is
'�������� 0������ 1������ 9����';

comment on column APP_HIS_DRLS.YPTLS is
'ԭƽ̨��ˮ��';

comment on column APP_HIS_DRLS.JYJG is
'���׻���';

comment on column APP_HIS_DRLS.JYGY is
'���׹�Ա';

comment on column APP_HIS_DRLS.QDBS is
'������ʶ ';

comment on column APP_HIS_DRLS.ZDSBBH is
'�ն��豸���';

comment on column APP_HIS_DRLS.YYBS is
'Ӧ�ñ�ʶ ';

comment on column APP_HIS_DRLS.CPDM is
'��Ʒ����';

comment on column APP_HIS_DRLS.YWBH is
'ҵ����';

comment on column APP_HIS_DRLS.JYDM is
'���״���';

comment on column APP_HIS_DRLS.YHBH is
'�û���� ���ֻ��� ˮ���';

comment on column APP_HIS_DRLS.XZBZ is
'��ת��־  0�ֽ� 1ת��';

comment on column APP_HIS_DRLS.JDBZ is
'�����־  �������ֵ�KEY=K_JDBZ';

comment on column APP_HIS_DRLS.ZHLX is
'�ʻ�����  �������ֵ�KEY=K_ZHLX';

comment on column APP_HIS_DRLS.YHZH is
'�����ʺ�';

comment on column APP_HIS_DRLS.DFZH is
'�Է��ʺ�';

comment on column APP_HIS_DRLS.JYJE is
'���׽��';

comment on column APP_HIS_DRLS.SXF is
'������';

comment on column APP_HIS_DRLS.PCBH is
'���α��';

comment on column APP_HIS_DRLS.JYXYM is
'������Ӧ��';

comment on column APP_HIS_DRLS.JYXYXX is
'������Ӧ��Ϣ';

comment on column APP_HIS_DRLS.JYZT is
'����״̬�������ֵ�KEY=K_JYZT';

comment on column APP_HIS_DRLS.EXTFLD1 is
'��չ1';

comment on column APP_HIS_DRLS.EXTFLD2 is
'��չ2';

/*==============================================================*/
/* Index: K_APP_DRLS_2                                          */
/*==============================================================*/
create index K_APP_DRLS_2 on APP_HIS_DRLS (
   PTRQ ASC,
   PTLS ASC,
   YWBH ASC
);

/*==============================================================*/
/* Table: APP_JJRDJ                                             */
/*==============================================================*/
create table APP_JJRDJ  
(
   RQ                   VARCHAR2(8)                     not null,
   JRBZ                 VARCHAR2(1)                     not null,
   EXTFLD1              VARCHAR2(20),
   constraint PK_APP_JJRDJ primary key (RQ)
);

comment on table APP_JJRDJ is
'���ý��ձ�־';

comment on column APP_JJRDJ.RQ is
'����';

comment on column APP_JJRDJ.JRBZ is
'�ڼ��ձ�־ 0  �� 1�� ';

comment on column APP_JJRDJ.EXTFLD1 is
'��չ1';

/*==============================================================*/
/* Table: APP_JYXX                                              */
/*==============================================================*/
create table APP_JYXX  
(
   JYDM                 VARCHAR2(8)                     not null,
   JYMC                 VARCHAR2(40),
   YYBS                 VARCHAR2(8),
   JYLX                 VARCHAR2(1),
   LSJLBZ               VARCHAR2(1),
   RZBZ                 VARCHAR2(1),
   BBBZ                 VARCHAR2(1),
   CPXG                 VARCHAR2(1),
   WHJG                 VARCHAR2(16),
   WHGY                 VARCHAR2(16),
   WHSJ                 VARCHAR2(14),
   EXTFLD1              VARCHAR2(40),
   EXTFLD2              VARCHAR2(40),
   QTBZ                 VARCHAR2(1),
   constraint PK_APP_JYXX primary key (JYDM)
);

comment on table APP_JYXX is
'������Ϣ���Ʊ�';

comment on column APP_JYXX.JYDM is
'���״���';

comment on column APP_JYXX.JYMC is
'��������';

comment on column APP_JYXX.YYBS is
'Ӧ�ñ�ʶ Ӧ�ñ�ʶ ��app_yyxx��';

comment on column APP_JYXX.JYLX is
'�������� 0������ 1������ 9����';

comment on column APP_JYXX.LSJLBZ is
'��ˮ��¼��־ 0��¼ 1����¼';

comment on column APP_JYXX.RZBZ is
'���ʱ�־ 0���� 1������';

comment on column APP_JYXX.BBBZ is
'�����־ 0���� 1�Ǳ���';

comment on column APP_JYXX.CPXG is
'��Ʒ��� 0��� 1�����(�������Ʒ�޹�ʱ�����׵Ļ���������������ʱ�䣬�޶�ȶ���������)';

comment on column APP_JYXX.EXTFLD1 is
'��չ����1';

comment on column APP_JYXX.EXTFLD2 is
'��չ����2';

comment on column APP_JYXX.QTBZ is
'��ͣ��־ 0���� 1�ر�';

/*==============================================================*/
/* Table: APP_KHCPQY                                            */
/*==============================================================*/
create table APP_KHCPQY  
(
   XYBH                 VARCHAR2(20)                    not null,
   KHBH                 VARCHAR2(16),
   CPDM                 VARCHAR2(16)                    not null,
   YWBH                 VARCHAR2(16)                    not null,
   ZHLX                 VARCHAR2(2),
   KHJG                 VARCHAR2(16),
   QYZH                 VARCHAR2(32),
   ZHHM                 VARCHAR2(80),
   DLZJLX               VARCHAR2(3),
   DLZJHM               VARCHAR2(32),
   ZJLX                 VARCHAR2(3),
   ZJHM                 VARCHAR2(32),
   QYLX                 VARCHAR2(1),
   KHJL                 VARCHAR2(20),
   HYKSRQ               VARCHAR2(8),
   HYJSRQ               VARCHAR2(8),
   KTQD                 VARCHAR2(60),
   BLJG                 VARCHAR2(16),
   BLGY                 VARCHAR2(16),
   BLRQ                 VARCHAR2(8),
   YHH1                 VARCHAR2(32),
   YHH2                 VARCHAR2(32),
   YHH3                 VARCHAR2(32),
   YHMC                 VARCHAR2(80),
   YHLX                 VARCHAR2(16),
   YHYB                 VARCHAR2(6),
   YHDH                 VARCHAR2(12),
   YHDZ                 VARCHAR2(60),
   JYBZ                 VARCHAR2(3),
   KKZDXE               NUMBER(13,2),
   KKZQ                 VARCHAR2(1),
   YDKKRQ               VARCHAR2(8),
   KKZT                 VARCHAR2(1),
   KKRQ                 VARCHAR2(8),
   DXTZBZ               VARCHAR2(1),
   ZHZDED               NUMBER(13,2),
   EXTFLD1              VARCHAR2(40),
   EXTFLD2              VARCHAR2(40),
   EXTFLD3              VARCHAR2(40),
   EXTFLD4              VARCHAR2(40),
   EXTFLD5              VARCHAR2(40),
   EXTFLD6              VARCHAR2(254),
   QYZT                 VARCHAR2(1),
   constraint PK_APP_KHCPQY primary key (XYBH, CPDM)
);

comment on table APP_KHCPQY is
'�ͻ���ƷǩԼ��';

comment on column APP_KHCPQY.XYBH is
'Э���� ���������ɣ���Ʒ��Ϣ�������ã�';

comment on column APP_KHCPQY.CPDM is
'��Ʒ����';

comment on column APP_KHCPQY.YWBH is
'ҵ���� ';

comment on column APP_KHCPQY.ZHLX is
'�˻����� ';

comment on column APP_KHCPQY.KHJG is
'ǩԼ�˻���������';

comment on column APP_KHCPQY.QYZH is
'ǩԼ�˻�';

comment on column APP_KHCPQY.ZHHM is
'�˻�����';

comment on column APP_KHCPQY.DLZJLX is
'������֤������ �������ֵ� KEY=K_ZJLX';

comment on column APP_KHCPQY.DLZJHM is
'������֤������';

comment on column APP_KHCPQY.ZJLX is
'֤������ �������ֵ� KEY=K_ZJLX';

comment on column APP_KHCPQY.ZJHM is
'֤������';

comment on column APP_KHCPQY.QYLX is
'ǩԼ���� 0���� 1���� 9����';

comment on column APP_KHCPQY.KHJL is
'�ͻ�����';

comment on column APP_KHCPQY.HYKSRQ is
'��Լ��ʼ����';

comment on column APP_KHCPQY.HYJSRQ is
'��Լ��������';

comment on column APP_KHCPQY.KTQD is
'��ͨ����  ������ʶͨ�� | ��ָ��� ALL��ʾȫ��ͨ';

comment on column APP_KHCPQY.BLJG is
'�������';

comment on column APP_KHCPQY.BLGY is
'�����Ա';

comment on column APP_KHCPQY.BLRQ is
'��������';

comment on column APP_KHCPQY.YHH1 is
'�û���1';

comment on column APP_KHCPQY.YHH2 is
'�û���2';

comment on column APP_KHCPQY.YHH3 is
'�û���3';

comment on column APP_KHCPQY.YHMC is
'�û�����(�������û�����)';

comment on column APP_KHCPQY.YHLX is
'�û�����(�������û�����)';

comment on column APP_KHCPQY.YHYB is
'�û��ʱ�(�������û��ʱ�)';

comment on column APP_KHCPQY.YHDH is
'�û��绰(�������û��绰)';

comment on column APP_KHCPQY.YHDZ is
'�û���ַ(�������û���ַ)';

comment on column APP_KHCPQY.JYBZ is
'���ױ���';

comment on column APP_KHCPQY.KKZDXE is
'�ۿ�����޶�';

comment on column APP_KHCPQY.KKZQ is
'�ۿ�����  --0-û���ڣ�1-�գ�2-�ܣ�3-�£�4-��';

comment on column APP_KHCPQY.YDKKRQ is
'Լ���ۿ�����';

comment on column APP_KHCPQY.KKZT is
'���һ�οۿ�״̬ 0 �C �ɹ�  1 �C ���ֳɹ�  2-ʧ�� 
';

comment on column APP_KHCPQY.KKRQ is
'���һ�οۿ�����';

comment on column APP_KHCPQY.DXTZBZ is
'����֪ͨ��־ 0֪ͨ 1��֪ͨ';

comment on column APP_KHCPQY.ZHZDED is
'�˻���Ͷ��';

comment on column APP_KHCPQY.EXTFLD1 is
'��չ����1';

comment on column APP_KHCPQY.EXTFLD2 is
'��չ����2';

comment on column APP_KHCPQY.EXTFLD3 is
'��չ����3';

comment on column APP_KHCPQY.EXTFLD4 is
'��չ����4';

comment on column APP_KHCPQY.EXTFLD5 is
'��չ����5';

comment on column APP_KHCPQY.EXTFLD6 is
'��չ����6';

comment on column APP_KHCPQY.QYZT is
'ǩԼ״̬ 0���� 1����';

/*==============================================================*/
/* Index: K_APP_INDEX_1                                         */
/*==============================================================*/
create index K_APP_INDEX_1 on APP_KHCPQY (
   CPDM ASC,
   QYZH ASC,
   YHH1 ASC,
   QYZT ASC
);

/*==============================================================*/
/* Table: APP_KHXX                                              */
/*==============================================================*/
create table APP_KHXX  
(
   KHBH                 VARCHAR2(16)                    not null,
   KHXM                 VARCHAR2(80),
   YWXM                 VARCHAR2(40),
   BM                   VARCHAR2(20),
   KHLX                 VARCHAR2(1),
   ZJKHBH               VARCHAR2(32),
   ZJLX                 VARCHAR2(3)                     not null,
   ZJHM                 VARCHAR2(32)                    not null,
   CSNY                 VARCHAR2(8),
   SEX                  VARCHAR2(1),
   GJ                   VARCHAR2(3),
   HK                   VARCHAR2(60),
   HYZK                 VARCHAR2(1),
   JYCD                 VARCHAR2(1),
   ZY                   VARCHAR2(3),
   ZW                   VARCHAR2(20),
   SRQK                 NUMBER(16,2),
   GSDZ                 VARCHAR2(60),
   GSYB                 VARCHAR2(6),
   GSDH                 VARCHAR2(16),
   ZZDZ                 VARCHAR2(60),
   ZZYB                 VARCHAR2(6),
   ZZDH                 VARCHAR2(16),
   SJHM                 VARCHAR2(16),
   MEMAIL               VARCHAR2(32),
   YJDZLX               VARCHAR2(1),
   BZ                   VARCHAR2(1),
   constraint PK_APP_KHXX primary key (KHBH),
   constraint AK_K_APP_KHXX_2_APP_KHXX unique (ZJLX, ZJHM)
);

comment on table APP_KHXX is
'�ͻ���Ϣ��';

comment on column APP_KHXX.KHBH is
'�ͻ���� ������ K_KHBH ����';

comment on column APP_KHXX.KHXM is
'�ͻ�����';

comment on column APP_KHXX.YWXM is
'Ӣ������';

comment on column APP_KHXX.BM is
'����';

comment on column APP_KHXX.KHLX is
'�ͻ����� �������ֵ�KEY=K_KHLX';

comment on column APP_KHXX.ZJKHBH is
'�����ͻ����';

comment on column APP_KHXX.ZJLX is
'֤������ �������ֵ�KEY=K_ZJLX';

comment on column APP_KHXX.ZJHM is
'֤������';

comment on column APP_KHXX.CSNY is
'��������';

comment on column APP_KHXX.SEX is
'�Ա� �������ֵ�KEY=K_SEX';

comment on column APP_KHXX.GJ is
'����';

comment on column APP_KHXX.HK is
'����';

comment on column APP_KHXX.HYZK is
'����״�� 0δ�� 1�ѻ� 2��� 9δ֪';

comment on column APP_KHXX.JYCD is
'�����̶� �������ֵ�KEY=K_JYCD';

comment on column APP_KHXX.ZY is
'ְҵ  ���ݹ��ұ�׼';

comment on column APP_KHXX.ZW is
'ְ��';

comment on column APP_KHXX.SRQK is
'���������';

comment on column APP_KHXX.GSDZ is
'��˾��ַ';

comment on column APP_KHXX.GSYB is
'��˾�ʱ�';

comment on column APP_KHXX.GSDH is
'��˾�绰';

comment on column APP_KHXX.ZZDZ is
'סլ��ַ';

comment on column APP_KHXX.ZZYB is
'סլ�ʱ�';

comment on column APP_KHXX.ZZDH is
'סլ�绰';

comment on column APP_KHXX.SJHM is
'�ֻ�����';

comment on column APP_KHXX.MEMAIL is
'��������';

comment on column APP_KHXX.YJDZLX is
'�ʼĵ�ַ���� 1��˾��ַ2סլ��ַ';

comment on column APP_KHXX.BZ is
'��־ 0���� 1��Ч Xɾ��';

/*==============================================================*/
/* Table: APP_KZSX                                              */
/*==============================================================*/
create table APP_KZSX  
(
   PKEY                 VARCHAR2(40)                    not null,
   CSMC                 VARCHAR2(20)                    not null,
   CSSM                 VARCHAR2(80)                    not null,
   CSZ                  VARCHAR2(80),
   EXTFLD               VARCHAR2(40),
   WHJG                 VARCHAR2(16),
   WHGY                 VARCHAR2(16),
   WHSJ                 VARCHAR2(14),
   constraint PK_APP_KZSX primary key (PKEY, CSMC)
);

comment on table APP_KZSX is
'��չ���Ա�';

comment on column APP_KZSX.PKEY is
'��ֵ �����Ҫ��������ı�ı��� + ��¼��Ψһ�ؼ�ֵ�����ڶ���ֶ�ͨ��"|"�ָ�
�� CPXX_001';

comment on column APP_KZSX.CSMC is
'��ʾ�������ֶ���Ӣ����ĸ��ʾ�������ڱ��ֶ�����';

comment on column APP_KZSX.CSSM is
'����˵��';

comment on column APP_KZSX.CSZ is
'������ֵ';

comment on column APP_KZSX.EXTFLD is
'��չ���� ��Ź�������';

/*==============================================================*/
/* Table: APP_MJSJ                                              */
/*==============================================================*/
create table APP_MJSJ  
(
   MJID                 VARCHAR2(16)                    not null,
   MJSM                 VARCHAR2(40),
   SJXH                 INTEGER                         not null,
   QSBZ                 VARCHAR2(1),
   REQ1                 VARCHAR2(40)                    not null,
   REQ2                 VARCHAR2(40),
   REQ3                 VARCHAR2(40),
   REQ4                 VARCHAR2(40),
   REQ5                 VARCHAR2(40),
   REQ6                 VARCHAR2(40),
   REQ7                 VARCHAR2(40),
   REQ8                 VARCHAR2(40),
   REQ9                 VARCHAR2(40),
   REQ10                VARCHAR2(40),
   RESP1                VARCHAR2(40)                    not null,
   RESP2                VARCHAR2(40),
   RESP3                VARCHAR2(40),
   RESP4                VARCHAR2(40),
   RESP5                VARCHAR2(40),
   RESP6                VARCHAR2(40),
   RESP7                VARCHAR2(40),
   RESP8                VARCHAR2(40),
   RESP9                VARCHAR2(40),
   RESP10               VARCHAR2(40),
   WHJG                 VARCHAR2(16),
   WHGY                 VARCHAR2(16),
   WHSJ                 VARCHAR2(14),
   constraint PK_APP_MJSJ primary key (MJID, SJXH)
);

comment on table APP_MJSJ is
'ö�����ݱ�';

comment on column APP_MJSJ.MJID is
'ö��ID';

comment on column APP_MJSJ.MJSM is
'ö��˵��';

comment on column APP_MJSJ.SJXH is
'�������';

comment on column APP_MJSJ.QSBZ is
'ȱʡ��ʶ  0�� 1��';

/*==============================================================*/
/* Table: APP_MJSX                                              */
/*==============================================================*/
create table APP_MJSX  
(
   MJID                 VARCHAR2(16)                    not null,
   MJSM                 VARCHAR2(40)                    not null,
   SXLX                 VARCHAR2(1)                     not null,
   SXXH                 VARCHAR2(2)                     not null,
   SXMC                 VARCHAR2(16)                    not null,
   SXNR                 VARCHAR2(40)                    not null,
   SXSM                 VARCHAR2(40),
   WHJG                 VARCHAR2(16),
   WHGY                 VARCHAR2(16),
   WHSJ                 VARCHAR2(14),
   constraint PK_APP_MJSX primary key (MJID, SXLX, SXXH)
);

comment on table APP_MJSX is
'ö�����Կ��Ʊ�';

comment on column APP_MJSX.MJID is
'ö��ID';

comment on column APP_MJSX.MJSM is
'ö��˵��';

comment on column APP_MJSX.SXLX is
'�������� 1���� 2���';

comment on column APP_MJSX.SXXH is
'���Ը����������ͣ���1��ʼ�����ܴ���10�����ϵ���λ�����Ӧ';

comment on column APP_MJSX.SXMC is
'��������';

comment on column APP_MJSX.SXNR is
'�������Ϊ��������ʾ���ݵ���Դ���������Ϊ��������ݵ�Ŀ��';

comment on column APP_MJSX.SXSM is
'���Ե�����˵��';

/*==============================================================*/
/* Table: APP_PZGLKZ                                            */
/*==============================================================*/
create table APP_PZGLKZ  
(
   PTRQ                 VARCHAR2(8)                     not null,
   PTSJ                 VARCHAR2(6),
   PTLS                 INTEGER                         not null,
   JYJG                 VARCHAR2(16)                    not null,
   JYGY                 VARCHAR2(16)                    not null,
   PZCZDZ               VARCHAR2(2),
   CZLX                 VARCHAR2(1),
   CZFX                 VARCHAR2(1),
   PZLY                 VARCHAR2(32),
   PZMD                 VARCHAR2(32),
   PZSL                 INTEGER,
   QSHM                 VARCHAR2(32),
   JSHM                 VARCHAR2(32),
   JYZT                 VARCHAR2(1),
   EXTFLD               VARCHAR2(40),
   SM                   VARCHAR2(40)
);

comment on table APP_PZGLKZ is
'ƾ֤������Ʊ�';

comment on column APP_PZGLKZ.PTRQ is
'ƽ̨����';

comment on column APP_PZGLKZ.PTSJ is
'ƽ̨ʱ��';

comment on column APP_PZGLKZ.PTLS is
'ƽ̨��ˮ��';

comment on column APP_PZGLKZ.JYJG is
'���׻���';

comment on column APP_PZGLKZ.JYGY is
'���׹�Ա';

comment on column APP_PZGLKZ.PZCZDZ is
'ƾ֤��������  �������ֵ� KEY=K_PZCZDZ';

comment on column APP_PZGLKZ.CZLX is
'�������� 0 ϵͳ�� 1ϵͳ��';

comment on column APP_PZGLKZ.CZFX is
'�������� 0 ���ϼ� 1���¼� 2���� 3����';

comment on column APP_PZGLKZ.PZLY is
'ƾ֤��Դ ��ʽ������|��Ա �����Ϊ�������������ԱΪ��';

comment on column APP_PZGLKZ.PZMD is
'ƾ֤Ŀ�� ��ʽ������|��Ա �����Ϊ�������������ԱΪ��';

comment on column APP_PZGLKZ.PZSL is
'ƾ֤����';

comment on column APP_PZGLKZ.QSHM is
'��ʼ����';

comment on column APP_PZGLKZ.JSHM is
'��������';

comment on column APP_PZGLKZ.JYZT is
'����״̬ 0 ���� 1��� 9ȡ��';

comment on column APP_PZGLKZ.EXTFLD is
'��չ�ֶ�';

comment on column APP_PZGLKZ.SM is
'˵��';

/*==============================================================*/
/* Table: APP_PZHMDJ                                            */
/*==============================================================*/
create table APP_PZHMDJ  
(
   PZZL                 VARCHAR2(3)                     not null,
   PZHM                 VARCHAR2(32)                    not null,
   PZWZ                 VARCHAR2(34),
   NBJG                 VARCHAR2(34),
   PZZT                 VARCHAR2(1),
   GXRQ                 VARCHAR2(8),
   GXSJ                 VARCHAR2(6),
   GXLS                 INTEGER,
   GXJG                 VARCHAR2(16),
   GXGY                 VARCHAR2(16),
   GXSM                 VARCHAR2(40),
   PZNR                 VARCHAR2(80),
   EXFLD                VARCHAR2(40),
   SM                   VARCHAR2(40),
   constraint PK_APP_PZHMDJ primary key (PZZL, PZHM)
);

comment on table APP_PZHMDJ is
'ƾ֤����ǼǱ�';

comment on column APP_PZHMDJ.PZZL is
'ƾ֤����';

comment on column APP_PZHMDJ.PZHM is
'ƾ֤����';

comment on column APP_PZHMDJ.PZWZ is
'ƾ֤λ�� ��ʽ������|��Ա';

comment on column APP_PZHMDJ.NBJG is
'�ڲ�����';

comment on column APP_PZHMDJ.PZZT is
'ƾ֤״̬ 0���� 1��ʹ�� 2������ 3��;';

comment on column APP_PZHMDJ.GXRQ is
'��������';

comment on column APP_PZHMDJ.GXSJ is
'����ʱ��';

comment on column APP_PZHMDJ.GXLS is
'������ˮ';

comment on column APP_PZHMDJ.GXJG is
'���»���';

comment on column APP_PZHMDJ.GXGY is
'���¹�Ա';

comment on column APP_PZHMDJ.GXSM is
'����˵��';

comment on column APP_PZHMDJ.PZNR is
'ƾ֤����';

comment on column APP_PZHMDJ.EXFLD is
'��չ�ֶ�';

comment on column APP_PZHMDJ.SM is
'˵��';

/*==============================================================*/
/* Table: APP_PZSLDJ                                            */
/*==============================================================*/
create table APP_PZSLDJ  
(
   PZZL                 VARCHAR2(3)                     not null,
   PZWZ                 VARCHAR2(34)                    not null,
   NBJG                 VARCHAR2(34),
   PZZT                 VARCHAR2(1)                     not null,
   PZSL                 INTEGER,
   EXFLD                VARCHAR2(40),
   SM                   VARCHAR2(40),
   constraint PK_APP_PZSLDJ primary key (PZZL, PZWZ, PZZT)
);

comment on table APP_PZSLDJ is
'ƾ֤�����ǼǱ�';

comment on column APP_PZSLDJ.PZZL is
'ƾ֤����';

comment on column APP_PZSLDJ.PZWZ is
'ƾ֤λ�� ��ʽ������|��Ա';

comment on column APP_PZSLDJ.NBJG is
'�ڲ�����';

comment on column APP_PZSLDJ.PZZT is
'ƾ֤״̬ 0���� 1��ʹ�� 2������ 3��;';

comment on column APP_PZSLDJ.PZSL is
'ƾ֤����';

comment on column APP_PZSLDJ.EXFLD is
'��չ�ֶ�';

comment on column APP_PZSLDJ.SM is
'˵��';

/*==============================================================*/
/* Table: APP_PZXX                                              */
/*==============================================================*/
create table APP_PZXX  
(
   PTRQ                 VARCHAR2(8)                     not null,
   PTLS                 INTEGER                         not null,
   PZXH                 INTEGER                         not null,
   YWLS                 INTEGER,
   YWRQ                 VARCHAR2(8),
   YYBS                 VARCHAR2(8),
   CPDM                 VARCHAR2(16)                    not null,
   YHBH                 VARCHAR2(32),
   YHBSH                VARCHAR2(32),
   KHMC                 VARCHAR2(80),
   YHZH                 VARCHAR2(32),
   JYJE                 NUMBER(16,2),
   JYJE2                NUMBER(16,2),
   JYJE3                NUMBER(16,2),
   SXF                  NUMBER(16,2),
   JFZQ                 VARCHAR2(16),
   QSRQ                 VARCHAR2(10),
   JSRQ                 VARCHAR2(10),
   SJDM                 VARCHAR2(10),
   QDBS                 VARCHAR2(3),
   PZZL                 VARCHAR2(3),
   PZHM                 VARCHAR2(32),
   PZSM                 VARCHAR2(40),
   DYRQ                 VARCHAR2(8),
   DYSJ                 VARCHAR2(6),
   DYLS                 INTEGER,
   DYJG                 VARCHAR2(16),
   DYGY                 VARCHAR2(16),
   DYCS                 INTEGER,
   JLBZ                 VARCHAR2(1),
   EXTFLD1              VARCHAR2(40),
   EXTFLD2              VARCHAR2(40),
   PZNR                 LONG RAW,
   constraint PK_APP_PZXX primary key (PTRQ, PTLS, PZXH)
);

comment on table APP_PZXX is
'ƾ֤������Ϣ��';

comment on column APP_PZXX.PTRQ is
'ƽ̨���� ����ƾ֤�Ľ���ƽ̨����YYYYMMDD';

comment on column APP_PZXX.PTLS is
'ƽ̨��ˮ��';

comment on column APP_PZXX.PZXH is
'ƾ֤���';

comment on column APP_PZXX.YWLS is
'ҵ����ˮ';

comment on column APP_PZXX.YWRQ is
'ҵ������';

comment on column APP_PZXX.YYBS is
'Ӧ�ñ�ʶ';

comment on column APP_PZXX.CPDM is
'��Ʒ����';

comment on column APP_PZXX.YHBH is
'�û����';

comment on column APP_PZXX.YHBSH is
'�ͻ���ʶ��';

comment on column APP_PZXX.KHMC is
'�ͻ�����';

comment on column APP_PZXX.YHZH is
'�����ʺ�';

comment on column APP_PZXX.JYJE is
'���׽��';

comment on column APP_PZXX.JYJE2 is
'���׽��2';

comment on column APP_PZXX.JYJE3 is
'���׽��3';

comment on column APP_PZXX.SXF is
'������';

comment on column APP_PZXX.JFZQ is
'�ɷ�����';

comment on column APP_PZXX.QSRQ is
'��ʼ����';

comment on column APP_PZXX.JSRQ is
'��������';

comment on column APP_PZXX.SJDM is
'˰�ִ���';

comment on column APP_PZXX.QDBS is
'��������';

comment on column APP_PZXX.PZZL is
'ƾ֤����';

comment on column APP_PZXX.PZHM is
'ƾ֤����';

comment on column APP_PZXX.PZSM is
'ƾ֤˵��';

comment on column APP_PZXX.DYRQ is
'��ӡ����';

comment on column APP_PZXX.DYSJ is
'��ӡʱ��';

comment on column APP_PZXX.DYLS is
'��ӡ��ˮ��';

comment on column APP_PZXX.DYJG is
'��ӡ����';

comment on column APP_PZXX.DYGY is
'��ӡ��Ա';

comment on column APP_PZXX.DYCS is
'��ӡ����';

comment on column APP_PZXX.JLBZ is
'��¼��־ 0���� 1����';

comment on column APP_PZXX.EXTFLD1 is
'��չ�ֶ�1';

comment on column APP_PZXX.EXTFLD2 is
'��չ�ֶ�2';

comment on column APP_PZXX.PZNR is
'ƾ֤����';

/*==============================================================*/
/* Index: K_APP_PZXX_1                                          */
/*==============================================================*/
create index K_APP_PZXX_1 on APP_PZXX (
   PTRQ ASC,
   PTLS ASC
);

/*==============================================================*/
/* Index: K_APP_PZXX_2                                          */
/*==============================================================*/
create index K_APP_PZXX_2 on APP_PZXX (
   PTRQ ASC,
   PTLS ASC,
   CPDM ASC,
   YHBH ASC,
   YHZH ASC
);

/*==============================================================*/
/* Table: APP_PZZL                                              */
/*==============================================================*/
create table APP_PZZL  
(
   PZZL                 VARCHAR2(3)                     not null,
   PZMC                 VARCHAR2(40)                    not null,
   PZSM                 VARCHAR2(80),
   PZLB                 VARCHAR2(1),
   PZJB                 VARCHAR2(1),
   PZLY                 VARCHAR2(16),
   PZZGJG               VARCHAR2(16)                    not null,
   ZJPZZL               VARCHAR2(8),
   DSFPZZL              VARCHAR2(8),
   PZGS                 VARCHAR2(40),
   KZLX                 VARCHAR2(1)                     not null,
   WHJG                 VARCHAR2(16),
   WHGY                 VARCHAR2(16),
   WHSJ                 VARCHAR2(14),
   EXTFLD1              VARCHAR2(40),
   EXTFLD2              VARCHAR2(40),
   constraint PK_APP_PZZL primary key (PZZL)
);

comment on table APP_PZZL is
'ƾ֤�����';

comment on column APP_PZZL.PZZL is
'�ֹ�������� ���������� KEY=K_PZBH';

comment on column APP_PZZL.PZMC is
'ƾ֤����';

comment on column APP_PZZL.PZSM is
'ƾ֤˵��';

comment on column APP_PZZL.PZLB is
'ƾ֤��� �������ֵ� KEY=K_PZLB';

comment on column APP_PZZL.PZJB is
'ƾ֤���� 0һ�� 1��Ҫ';

comment on column APP_PZZL.PZLY is
'ƾ֤��Դ �ɴ�ŵ�������λ����';

comment on column APP_PZZL.PZZGJG is
'ƾ֤���ܻ���';

comment on column APP_PZZL.ZJPZZL is
'����ƾ֤����';

comment on column APP_PZZL.DSFPZZL is
'������ƾ֤����';

comment on column APP_PZZL.PZGS is
'ƾ֤��ʽ';

comment on column APP_PZZL.KZLX is
'�������� 0������ 1�������� 2���ƺ���';

comment on column APP_PZZL.EXTFLD1 is
'��չ����1';

comment on column APP_PZZL.EXTFLD2 is
'��չ����2';

/*==============================================================*/
/* Table: APP_QDXX                                              */
/*==============================================================*/
create table APP_QDXX  
(
   QDBS                 VARCHAR2(3)                     not null,
   QDMC                 VARCHAR2(40),
   QDSM                 VARCHAR2(80),
   SJKZBZ               VARCHAR2(1),
   QSSJ                 VARCHAR2(8),
   JSSJ                 VARCHAR2(8),
   CZBZ                 VARCHAR2(1),
   ZDCZBZ               VARCHAR2(1),
   WHJG                 VARCHAR2(16),
   WHGY                 VARCHAR2(16),
   WHSJ                 VARCHAR2(14),
   EXTFLD1              VARCHAR2(40),
   EXTFLD2              VARCHAR2(40),
   QDZT                 VARCHAR2(1),
   constraint PK_APP_QDXX primary key (QDBS)
);

comment on table APP_QDXX is
'������Ϣ��';

comment on column APP_QDXX.QDBS is
'������ʶ �������ֵ� KEY=K_QDBS ';

comment on column APP_QDXX.QDMC is
'��������';

comment on column APP_QDXX.QDSM is
'����˵��';

comment on column APP_QDXX.SJKZBZ is
'ʱ����Ʊ�־ 0 ���� 1������';

comment on column APP_QDXX.QSSJ is
'��ʼʱ�� ';

comment on column APP_QDXX.JSSJ is
'����ʱ��';

comment on column APP_QDXX.CZBZ is
'�Ƿ��������  0���� 1������';

comment on column APP_QDXX.ZDCZBZ is
'ϵͳ�쳣�Ƿ��Զ�����  0�� 1��';

comment on column APP_QDXX.EXTFLD1 is
'��չ�ֶ�1';

comment on column APP_QDXX.EXTFLD2 is
'��չ�ֶ�2';

comment on column APP_QDXX.QDZT is
'����״̬ 0���� 1�ر�';

/*==============================================================*/
/* Table: APP_RWJKB                                             */
/*==============================================================*/
create table APP_RWJKB  
(
   YYBS                 VARCHAR2(8),
   YYMC                 VARCHAR2(40),
   CPDM                 VARCHAR2(16)                    not null,
   CPMC                 VARCHAR2(40),
   RWMC                 VARCHAR2(50),
   JYDM                 VARCHAR2(8),
   JYMC                 VARCHAR2(40),
   PTLS                 INTEGER                         not null,
   PTRQ                 VARCHAR2(8)                     not null,
   JYJG                 VARCHAR2(16),
   JYGY                 VARCHAR2(16),
   QDBS                 VARCHAR2(3),
   KSSJ                 VARCHAR2(19),
   JSSJ                 VARCHAR2(19),
   YXSJ                 INTEGER,
   ZXCS                 INTEGER,
   ZXZT                 VARCHAR2(1),
   XYM                  VARCHAR2(5),
   XYXX                 VARCHAR2(60),
   EXTFLD1              VARCHAR2(20),
   EXTFLD2              VARCHAR2(20),
   constraint PK_APP_RWJKB primary key (PTLS, PTRQ)
);

comment on column APP_RWJKB.YYBS is
'Ӧ�ñ�ʶ';

comment on column APP_RWJKB.YYMC is
'Ӧ������';

comment on column APP_RWJKB.CPDM is
'��Ʒ����';

comment on column APP_RWJKB.CPMC is
'��Ʒ����';

comment on column APP_RWJKB.RWMC is
'��������';

comment on column APP_RWJKB.JYDM is
'���״���';

comment on column APP_RWJKB.JYMC is
'��������';

comment on column APP_RWJKB.PTLS is
'ƽ̨��ˮ';

comment on column APP_RWJKB.PTRQ is
'ƽ̨����';

comment on column APP_RWJKB.JYJG is
'���ѻ���';

comment on column APP_RWJKB.JYGY is
'���ѹ�Ա';

comment on column APP_RWJKB.QDBS is
'������ʶ';

comment on column APP_RWJKB.KSSJ is
'��ʼʱ���';

comment on column APP_RWJKB.JSSJ is
'����ʱ���';

comment on column APP_RWJKB.YXSJ is
'���к�����';

comment on column APP_RWJKB.ZXCS is
'���д���';

comment on column APP_RWJKB.ZXZT is
'ִ��״̬0:ִ�гɹ�1:ִ��ʧ��9:ִ����';

comment on column APP_RWJKB.XYM is
'��Ӧ����';

comment on column APP_RWJKB.XYXX is
'��Ӧ��Ϣ';

comment on column APP_RWJKB.EXTFLD1 is
'��չ1';

comment on column APP_RWJKB.EXTFLD2 is
'��չ2';

/*==============================================================*/
/* Index: INDEX_RWJKB_1                                         */
/*==============================================================*/
create index INDEX_RWJKB_1 on APP_RWJKB (
   JYDM ASC,
   PTRQ ASC
);

/*==============================================================*/
/* Table: APP_RZPZ                                              */
/*==============================================================*/
create table APP_RZPZ  
(
   SSYY                 VARCHAR2(8)                     not null,
   CZLX                 VARCHAR2(1)                     not null,
   DXLX                 VARCHAR2(1)                     not null,
   CZDX1                VARCHAR2(128)                   not null,
   CZDX2                VARCHAR2(128),
   CZTJ                 VARCHAR2(254),
   WHJG                 VARCHAR2(16),
   WHGY                 VARCHAR2(16),
   WHSJ                 VARCHAR2(14),
   EXTFLD1              VARCHAR2(20),
   EXTFLD2              VARCHAR2(20),
   constraint PK_APP_RZPZ primary key (CZLX, DXLX, CZDX1)
);

comment on table APP_RZPZ is
'��������ʱ��Ҫƽ̨ͳһ�鵵������Ŀ���ļ���';

comment on column APP_RZPZ.SSYY is
'Ӧ�ñ�ʶ';

comment on column APP_RZPZ.CZLX is
'1 �鵵 2 ���� 3 ���� ';

comment on column APP_RZPZ.DXLX is
'1 ���ݿ� 2 �ļ�';

comment on column APP_RZPZ.CZDX1 is
'�鵵ʱ���Դ��Դ�ļ�·��';

comment on column APP_RZPZ.CZDX2 is
'�鵵ʱ���Ŀ���Ŀ���ļ�·��';

comment on column APP_RZPZ.CZTJ is
'���ݿ��� sql����';

comment on column APP_RZPZ.EXTFLD1 is
'��չ1';

comment on column APP_RZPZ.EXTFLD2 is
'��չ2';

/*==============================================================*/
/* Index: K_APP_RZPZ_1                                          */
/*==============================================================*/
create index K_APP_RZPZ_1 on APP_RZPZ (
   SSYY ASC,
   CZLX ASC,
   DXLX ASC
);

/*==============================================================*/
/* Table: APP_SXFFL                                             */
/*==============================================================*/
create table APP_SXFFL  
(
   FLBS                 VARCHAR2(32)                    not null,
   XH                   VARCHAR2(2)                     not null,
   FDBZ                 VARCHAR2(1)                     not null,
   NWKBZ                VARCHAR2(1),
   SXXKZ                VARCHAR2(1)                     not null,
   SXJE                 NUMBER(16,2),
   XXJE                 NUMBER(16,2),
   JSLX                 VARCHAR2(1)                     not null,
   JSCS                 NUMBER(16,6)                    not null,
   KJBZ                 VARCHAR2(1),
   KJCS                 NUMBER(16,6),
   FDLX                 VARCHAR2(1),
   LJBZ                 VARCHAR2(1),
   BHBZ                 VARCHAR2(1),
   QSS                  VARCHAR2(16),
   JSS                  VARCHAR2(16),
   SM                   VARCHAR2(40),
   WHJG                 VARCHAR2(16),
   WHGY                 VARCHAR2(16),
   WHSJ                 VARCHAR2(14),
   constraint PK_APP_SXFFL primary key (FLBS, XH)
);

comment on table APP_SXFFL is
'�����ѷ��ʱ�';

comment on column APP_SXFFL.FLBS is
'�ֹ�����';

comment on column APP_SXFFL.XH is
'��������ʱ������ʷֶε����';

comment on column APP_SXFFL.FDBZ is
'0 �������� 1 ���� ';

comment on column APP_SXFFL.NWKBZ is
'0���  1 �ڿ�  Ĭ�� 0';

comment on column APP_SXFFL.SXXKZ is
'0 ����  1 ������ ';

comment on column APP_SXFFL.JSLX is
'����������� 1 ���  2�ٷֱ�   ���Ϊ1 ����ʾ�����Ѽ�����Խ��ױ����ģ�����ǰٷֱȣ���ʾ�����Ѽ�����Խ��׽�';

comment on column APP_SXFFL.JSCS is
'������� ��������Ϊ1 ������ ����1 ��ʾ1Ԫ������Ϊ2������ٷֱ� ������1 ����ʾ1��';

comment on column APP_SXFFL.KJBZ is
'0���Ż� 1 ���� 2 ���ۼ� Ĭ��0';

comment on column APP_SXFFL.FDLX is
'�������� 1 ���ױ������� 2 ���׽���';

comment on column APP_SXFFL.LJBZ is
'0 ���۽�  1 �۽� Ĭ��0';

comment on column APP_SXFFL.BHBZ is
'��������������ޱ�־  1 �������� 0��������';

comment on column APP_SXFFL.SM is
'˵��';

/*==============================================================*/
/* Table: APP_SXFLS                                             */
/*==============================================================*/
create table APP_SXFLS  
(
   PTRQ                 VARCHAR2(8)                     not null,
   PTLS                 VARCHAR2(16)                    not null,
   FLBS                 VARCHAR2(32)                    not null,
   YYBS                 VARCHAR2(3),
   YWBH                 VARCHAR2(16),
   CPDM                 VARCHAR2(16)                    not null,
   QDBS                 VARCHAR2(3),
   JGBS                 VARCHAR2(16)                    not null,
   KHLX                 VARCHAR2(1),
   KHBH                 VARCHAR2(32),
   YHH                  VARCHAR2(32),
   DWBH                 VARCHAR2(16),
   XTNBZ                VARCHAR2(1),
   JYLSH                VARCHAR2(16),
   JYLX                 VARCHAR2(1),
   JYRQ                 VARCHAR2(8),
   JYGY                 VARCHAR2(16)                    not null,
   JYJG                 VARCHAR2(16)                    not null,
   JYJE                 NUMBER(16,2),
   JYBS                 INTEGER,
   SXFJE                NUMBER(16,2)                    not null,
   SFZT                 VARCHAR2(1),
   JFZH                 VARCHAR2(32),
   DFZH                 VARCHAR2(32),
   SFRQ                 VARCHAR2(8),
   SFJYGY               VARCHAR2(16)                    not null,
   SFJYJG               VARCHAR2(16)                    not null,
   SFLS                 VARCHAR2(16),
   LSZT                 VARCHAR2(1),
   EXTFLD1              VARCHAR2(20),
   EXTFLD2              VARCHAR2(40),
   SM                   VARCHAR2(40),
   constraint PK_APP_SXFLS primary key (PTRQ, PTLS)
);

comment on table APP_SXFLS is
'��������ˮ��';

comment on column APP_SXFLS.PTRQ is
'ƽ̨����';

comment on column APP_SXFLS.PTLS is
'ƽ̨��ˮ��';

comment on column APP_SXFLS.FLBS is
'���ʱ�ʶ';

comment on column APP_SXFLS.KHBH is
'�ͻ������б��';

comment on column APP_SXFLS.YHH is
'�û��ڵ������ͻ���';

comment on column APP_SXFLS.XTNBZ is
'1 ϵͳ��  0 ϵͳ��';

comment on column APP_SXFLS.JYLSH is
'��ȡ�����ѵ�ԭ������ˮ��';

comment on column APP_SXFLS.JYLX is
'�������� 0 ���� 1����';

comment on column APP_SXFLS.JYJE is
'���׽��';

comment on column APP_SXFLS.SXFJE is
'���ý��';

comment on column APP_SXFLS.SFZT is
'��ȡ״̬ 0 δ��ȡ 1����ȡ';

comment on column APP_SXFLS.JFZH is
'�跽�ʻ�';

comment on column APP_SXFLS.DFZH is
'�����ʻ�';

comment on column APP_SXFLS.SFRQ is
'�շ�����';

comment on column APP_SXFLS.LSZT is
'��ˮ״̬ 0 ���� 1ȡ��';

comment on column APP_SXFLS.SM is
'˵��';

/*==============================================================*/
/* Index: K_APP_SXFLS_1                                         */
/*==============================================================*/
create index K_APP_SXFLS_1 on APP_SXFLS (
   JYLSH ASC,
   JYRQ ASC
);

/*==============================================================*/
/* Table: APP_SXFWHLS                                           */
/*==============================================================*/
create table APP_SXFWHLS  
(
   CPDM                 VARCHAR2(16),
   FLBS                 VARCHAR2(32),
   CZNR                 VARCHAR2(254),
   CZBM                 VARCHAR2(32),
   WHLX                 VARCHAR2(1),
   WHRQ                 VARCHAR2(8),
   WHSJ                 VARCHAR2(6),
   WHGY                 VARCHAR2(16)                    not null,
   WHJG                 VARCHAR2(16)                    not null,
   SQGY                 VARCHAR2(16),
   SQJG                 VARCHAR2(16),
   EXTFLD1              VARCHAR2(20),
   EXTFLD2              VARCHAR2(40),
   SM                   VARCHAR2(40)
);

comment on table APP_SXFWHLS is
'������ά����ˮ����¼ά���������ʣ���Ʒ�����ѿ��ƣ���Ʒ�����ѹ�ϵ��ά����Ϣ';

comment on column APP_SXFWHLS.CPDM is
'��Ʒ����';

comment on column APP_SXFWHLS.FLBS is
'���ʱ�ʶ';

comment on column APP_SXFWHLS.CZNR is
'����SQL';

comment on column APP_SXFWHLS.CZBM is
'���������ݿ����';

comment on column APP_SXFWHLS.WHLX is
'1 ���ӣ� 2 �޸ģ� 3 ɾ��';

/*==============================================================*/
/* Index: K_APP_SXFWHLS_1                                       */
/*==============================================================*/
create index K_APP_SXFWHLS_1 on APP_SXFWHLS (
   CPDM ASC,
   FLBS ASC,
   CZBM ASC,
   WHRQ ASC
);

/*==============================================================*/
/* Table: APP_TXAQXX                                            */
/*==============================================================*/
create table APP_TXAQXX  
(
   LJBS                 VARCHAR2(8)                     not null,
   LJMC                 VARCHAR2(40),
   LJLX                 VARCHAR2(1),
   DWBH                 VARCHAR2(16),
   QDKZ                 VARCHAR2(1),
   TXMS                 VARCHAR2(1),
   TXDZ                 VARCHAR2(16),
   TXDK                 VARCHAR2(6),
   FSCS                 INTEGER,
   JSCS                 INTEGER,
   LJJGH                VARCHAR2(16),
   LJGYH                VARCHAR2(16),
   LJZDH                VARCHAR2(16),
   KEY1                 VARCHAR2(128),
   KEY2                 VARCHAR2(128),
   KEY3                 VARCHAR2(128),
   FTPDZ                VARCHAR2(16),
   FTPYH                VARCHAR2(16),
   FTPMM                VARCHAR2(32),
   FTPGZFS              VARCHAR2(1),
   FTPCSFS              VARCHAR2(1),
   FTPZDMS              VARCHAR2(1),
   FTPDFLJ              VARCHAR2(40),
   FTPBDLJ              VARCHAR2(40),
   WHJG                 VARCHAR2(16),
   WHGY                 VARCHAR2(16),
   WHSJ                 VARCHAR2(14),
   EXTFLD1              VARCHAR2(40),
   EXTFLD2              VARCHAR2(254),
   TXZT                 VARCHAR2(1),
   QDZT                 VARCHAR2(1),
   constraint PK_APP_TXAQXX primary key (LJBS)
);

comment on table APP_TXAQXX is
'ͨѶ��ȫ��Ϣ��';

comment on column APP_TXAQXX.LJBS is
'������ʶ L_';

comment on column APP_TXAQXX.LJMC is
'��������';

comment on column APP_TXAQXX.LJLX is
'�������� 1�������� 2��������ϵͳ 3������λ 9����';

comment on column APP_TXAQXX.DWBH is
'��λ��� ���������';

comment on column APP_TXAQXX.QDKZ is
'�Ƿ����ǩ��״̬��Ĭ��1��
0 ���� 1������';

comment on column APP_TXAQXX.TXMS is
'ͨѶģʽ�������ֵ� KEY=K_TXMS';

comment on column APP_TXAQXX.TXDZ is
'ͨѶ��ַ';

comment on column APP_TXAQXX.TXDK is
'ͨѶ�˿�';

comment on column APP_TXAQXX.FSCS is
'���ͳ�ʱ';

comment on column APP_TXAQXX.JSCS is
'���ճ�ʱ';

comment on column APP_TXAQXX.LJJGH is
'����������';

comment on column APP_TXAQXX.LJGYH is
'������Ա��';

comment on column APP_TXAQXX.LJZDH is
'�����ն˺�';

comment on column APP_TXAQXX.KEY1 is
'��Կ1';

comment on column APP_TXAQXX.KEY2 is
'��Կ2';

comment on column APP_TXAQXX.KEY3 is
'��Կ3';

comment on column APP_TXAQXX.FTPDZ is
'ftp��ַ��Ĭ��ͬͨѶ��ַ';

comment on column APP_TXAQXX.FTPYH is
'ftp�û�����';

comment on column APP_TXAQXX.FTPMM is
'ftp�û�����';

comment on column APP_TXAQXX.FTPGZFS is
'(1 ����ģʽ 2 ����ģʽii)';

comment on column APP_TXAQXX.FTPCSFS is
'ftp���䷽ʽ(1 bin 2 ascii)';

comment on column APP_TXAQXX.FTPZDMS is
'0-����PORT 1-����PASV';

comment on column APP_TXAQXX.FTPDFLJ is
'�Է��ļ����·��';

comment on column APP_TXAQXX.FTPBDLJ is
'�����ļ����·��';

comment on column APP_TXAQXX.EXTFLD1 is
'��չ�ֶ�1';

comment on column APP_TXAQXX.EXTFLD2 is
'��չ�ֶ�2';

comment on column APP_TXAQXX.TXZT is
'ͨѶ״̬ 0���� 9��Ч';

comment on column APP_TXAQXX.QDZT is
'ǩ��״̬  1ǩ�� 2ǩ�� ';

/*==============================================================*/
/* Table: APP_XLKZ                                              */
/*==============================================================*/
create table APP_XLKZ  
(
   PKEY                 VARCHAR2(20)                    not null,
   CURR_VALUE           INTEGER                         not null,
   PINC                 INTEGER                         not null,
   MIN_VALUE            INTEGER                         not null,
   MAX_VALUE            INTEGER                         not null,
   REMARK               VARCHAR2(40),
   WHJG                 VARCHAR2(16),
   WHGY                 VARCHAR2(16),
   WHSJ                 VARCHAR2(14),
   constraint PK_APP_XLKZ primary key (PKEY)
);

comment on table APP_XLKZ is
'���п��Ʊ�';

/*==============================================================*/
/* Table: APP_YWRQ                                              */
/*==============================================================*/
create table APP_YWRQ  
(
   PKEY                 VARCHAR2(20)                    not null,
   SYYWRQ               VARCHAR2(8),
   YWRQ                 VARCHAR2(8)                     not null,
   XYYWRQ               VARCHAR2(8),
   CCH                  VARCHAR2(2),
   LSH                  INTEGER,
   EXTFLD               VARCHAR2(40),
   SM                   VARCHAR2(40),
   constraint PK_APP_YWRQ primary key (PKEY)
);

comment on table APP_YWRQ is
'ҵ�����ڱ�';

comment on column APP_YWRQ.PKEY is
'��ֵ  ��Ʒ����';

comment on column APP_YWRQ.SYYWRQ is
'��һҵ������';

comment on column APP_YWRQ.YWRQ is
'��Ʒҵ������';

comment on column APP_YWRQ.XYYWRQ is
'��һҵ������';

comment on column APP_YWRQ.CCH is
'���κ�';

comment on column APP_YWRQ.LSH is
'��ˮ��';

comment on column APP_YWRQ.EXTFLD is
'��չ����';

comment on column APP_YWRQ.SM is
'˵��';

/*==============================================================*/
/* Table: APP_YYXX                                              */
/*==============================================================*/
create table APP_YYXX  
(
   YYBS                 VARCHAR2(8)                     not null,
   YYMC                 VARCHAR2(40),
   YYSM                 VARCHAR2(80),
   YYKFKSRQ             VARCHAR2(8),
   YYKFJSRQ             VARCHAR2(8),
   YYFBRQ               VARCHAR2(8),
   YYBBH                VARCHAR2(20),
   YHH                  VARCHAR2(40),
   SQH                  VARCHAR2(40),
   YYKFJL               VARCHAR2(40),
   YYZBJL               VARCHAR2(40),
   YYZT                 VARCHAR2(1),
   EXTFLD               VARCHAR2(40),
   constraint PK_APP_YYXX primary key (YYBS)
);

comment on table APP_YYXX is
'Ӧ����Ϣ��';

comment on column APP_YYXX.YYBS is
'Ӧ�ñ�ʶ ';

comment on column APP_YYXX.YYMC is
'Ӧ������';

comment on column APP_YYXX.YYSM is
'Ӧ��˵��';

comment on column APP_YYXX.YYKFKSRQ is
'Ӧ�ÿ�����ʼ����';

comment on column APP_YYXX.YYKFJSRQ is
'Ӧ�ÿ�����������';

comment on column APP_YYXX.YYFBRQ is
'Ӧ�÷�������';

comment on column APP_YYXX.YYBBH is
'Ӧ�ð汾��';

comment on column APP_YYXX.YHH is
'�û���';

comment on column APP_YYXX.SQH is
'��Ȩ��';

comment on column APP_YYXX.YYKFJL is
'Ӧ�ÿ�������';

comment on column APP_YYXX.YYZBJL is
'Ӧ���ʱ�����';

comment on column APP_YYXX.YYZT is
'0���� 1�ر�';

comment on column APP_YYXX.EXTFLD is
'��չ�ֶ�';

/* ���� */
insert into app_cskz (CSJZ, CSLX, CSTJ, JDM, JDZ, REMARK, JZLX, WHJG, WHGY )
values ('K_APP_PTLSGD', '0', '', '/app/ptlsgd', '2', 'ƽ̨������ˮ�鵵����', '1', '00000','admin');

insert into app_cskz (CSJZ, CSLX, CSTJ, JDM, JDZ, REMARK, JZLX, WHJG, WHGY )
values ('K_APP_PTLSQL', '0', '', '/app/ptlsql', '7', 'ƽ̨������ˮ����������', '1', '00000','admin' );

insert into app_cskz (CSJZ, CSLX, CSTJ, JDM, JDZ, REMARK, JZLX, WHJG, WHGY )
values ('K_APP_QYCXXZ', '0', '', '/app/custom/qycxxz', '100', 'ǩԼ��ѯ��������¼��', '0', '00000','admin' );

insert into app_cskz (CSJZ, CSLX, CSTJ, JDM, JDZ, REMARK, JZLX, WHJG, WHGY )
values ('K_APP_ZXLSH', '0', '', '/app/zxlsh', '1', '��С��ˮ��', '0', '00000','admin' );

insert into app_cskz (CSJZ, CSLX, CSTJ, JDM, JDZ, REMARK, JZLX, WHJG, WHGY )
values ('K_APP_LSH_RETURN', '0', '', '/app/lshreturn', '0', '��ˮ�Ź����ñ�־ 0-����', '0', '00000','admin' );

/* ������Ϣ  */
insert into app_xlkz (PKEY, CURR_VALUE, PINC, MIN_VALUE, MAX_VALUE, REMARK, WHJG, WHGY ) 
values ('K_KHBH', 10000000, 1, 1, 99999999, '�ͻ����', '00000','admin' );

insert into app_xlkz (PKEY, CURR_VALUE, PINC, MIN_VALUE, MAX_VALUE, REMARK, WHJG, WHGY ) 
values ('K_KHCPQY', 10000000, 1, 1, 99999999, '�ͻ���ƷǩԼ����', '00000','admin' );

insert into app_xlkz (PKEY, CURR_VALUE, PINC, MIN_VALUE, MAX_VALUE, REMARK, WHJG, WHGY )
values ('K_DWBH', 1, 1, 1, 999999, '��λ���', '00000','admin' );

/*�����ֵ�*/
insert into app_dict (pkey,keyjs,pval,prompt,ssyy,WHJG,WHGY) values('K_APP_GYJB','��Ա����','11','���㾭��','001','00000','admin');
insert into app_dict (pkey,keyjs,pval,prompt,ssyy,WHJG,WHGY) values('K_APP_GYJB','��Ա����','12','��������','001','00000','admin');
insert into app_dict (pkey,keyjs,pval,prompt,ssyy,WHJG,WHGY) values('K_APP_GYJB','��Ա����','22','������������','001','00000','admin');
insert into app_dict (pkey,keyjs,pval,prompt,ssyy,WHJG,WHGY) values('K_APP_GYJB','��Ա����','32','һ����������','001','00000','admin');

INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JDBZ','�����־','D','��','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JDBZ','�����־','C','��','001','00000','admin' );
                                           
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_SEX','�Ա��־','0','δ֪���Ա�','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_SEX','�Ա��־','1','����','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_SEX','�Ա��־','2','Ů��','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_SEX','�Ա��־','9','δ˵���Ա�','001','00000','admin' );
                                                                                      
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYZT','����״̬','0','�ɹ�','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYZT','����״̬','1','ʧ��','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYZT','����״̬','6','״̬δ֪','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYZT','����״̬','7','���ױ�����','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYZT','����״̬','8','���ױ�����','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYZT','����״̬','9','��ʼ','001','00000','admin' );
                                            
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_YXBZ','��Ч��־','1','����','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_YXBZ','��Ч��־','2','�ر�','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_YXBZ','��Ч��־','9','δ��Ȩ','001','00000','admin' );
                                            
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JGKZCS','�������Ʋ���','0','������','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JGKZCS','�������Ʋ���','1','һ����������','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JGKZCS','�������Ʋ���','2','������������','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JGKZCS','�������Ʋ���','3','������������','001','00000','admin' );
                                            
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYFS','���׷�ʽ','1','����','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYFS','���׷�ʽ','2','����','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYFS','���׷�ʽ','3','�ռ�����','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYFS','���׷�ʽ','4','ҹ������','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYFS','���׷�ʽ','5','����������','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYFS','���׷�ʽ','6','�������ռ�����','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYFS','���׷�ʽ','7','������ҹ������','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYFS','���׷�ʽ','8','��������ת��','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYFS','���׷�ʽ','9','����','001','00000','admin' );
                                            
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_CPZT','��Ʒ״̬','0','����','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_CPZT','��Ʒ״̬','1','��ͣ','001','00000','admin' );
                                            
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_CSLX','��������','0','ϵͳ����','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_CSLX','��������','1','��������','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_CSLX','��������','2','Ӧ�ò���','001','00000','admin' );
                                            
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_DWZJLX','��λ֤������','1','Ӫҵִ��','001','00000','admin' );
                                            
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_TXMS','ͨѶģʽ','1','TCP/IP','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_TXMS','ͨѶģʽ','2','CICSCLI','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_TXMS','ͨѶģʽ','3','TUXEDOCLI','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_TXMS','ͨѶģʽ','4','IBM MQ','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_TXMS','ͨѶģʽ','9','����','001','00000','admin' );
                                            
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_ZHLX','�ʻ�����','01','�Թ�����','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_ZHLX','�ʻ�����','02','��˽����','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_ZHLX','�ʻ�����','03','�Թ�����','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_ZHLX','�ʻ�����','04','��˽����','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_ZHLX','�ʻ�����','05','��֤��','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_ZHLX','�ʻ�����','06','����','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_ZHLX','�ʻ�����','07','�ڲ���','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_ZHLX','�ʻ�����','08','������','001','00000','admin' );
                                            
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_ZJLX','֤������','0','���֤','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_ZJLX','֤������','1','���ڲ�','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_ZJLX','֤������','2','����','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_ZJLX','֤������','3','����֤','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_ZJLX','֤������','4','ʿ��֤','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_ZJLX','֤������','5','�۰ľ��������ڵ�ͨ��֤','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_ZJLX','֤������','6','̨��ͬ�������ڵ�ͨ��֤','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_ZJLX','֤������','7','��ʱ���֤','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_ZJLX','֤������','8','����˾���֤','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_ZJLX','֤������','9','����֤','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_ZJLX','֤������','X','����','001','00000','admin' );
                                            
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_PZLB','ƾ֤���','0','�Թ���','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_PZLB','ƾ֤���','1','��˽��','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_PZLB','ƾ֤���','2','�м�ҵ����','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_PZLB','ƾ֤���','3','����','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_PZLB','ƾ֤���','4','�м۵�֤��','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_PZLB','ƾ֤���','9','����','001','00000','admin' );
                                            
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_PZCZDZ','ƾ֤��������','01','����','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_PZCZDZ','ƾ֤��������','02','���','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_PZCZDZ','ƾ֤��������','03','����','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_PZCZDZ','ƾ֤��������','04','����','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_PZCZDZ','ƾ֤��������','05','�ػ�','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_PZCZDZ','ƾ֤��������','06','����','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_PZCZDZ','ƾ֤��������','07','ʹ��','001','00000','admin' );
                                            
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYBZ','���ױ���','CNY','�����','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYBZ','���ױ���','HKD','�۱�','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYBZ','���ױ���','USD','��Ԫ','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYBZ','���ױ���','EUR','ŷԪ','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYBZ','���ױ���','JPY','��Ԫ','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYBZ','���ױ���','MOP','����Ԫ','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYBZ','���ױ���','CHF','��ʿ����','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYBZ','���ױ���','GBP','Ӣ��','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYBZ','���ױ���','RUR','����˹¬��','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYBZ','���ױ���','CAD','���ô�Ԫ','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYBZ','���ױ���','DKK','�������','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYBZ','���ױ���','AUD','�Ĵ�����Ԫ','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYBZ','���ױ���','SEK','������','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYBZ','���ױ���','KRW','��Ԫ','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYBZ','���ױ���','SGD','��Ԫ','001','00000','admin' );
                                            
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_KHLX','�ͻ�����','1','��ͨ�û�','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_KHLX','�ͻ�����','2','�������','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_KHLX','�ͻ�����','3','�𿨹��','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_KHLX','�ͻ�����','4','��ʯ�����','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_KHLX','�ͻ�����','9','����','001','00000','admin' );
                                            
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYCD','�����̶�','1','��ä','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYCD','�����̶�','2','Сѧ','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYCD','�����̶�','3','����','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYCD','�����̶�','4','����','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYCD','�����̶�','5','��ר','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYCD','�����̶�','6','��','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYCD','�����̶�','7','˶ʿ�о���','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYCD','�����̶�','8','��ʿ�о���','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_JYCD','�����̶�','9','δ֪������','001','00000','admin' );

INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_SFBZ','�ո���־','1','��','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_SFBZ','�ո���־','2','��','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_SFBZ','�ո���־','3','����','001','00000','admin' );

INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_QYBZ','ǩԼ��־','0','����ҪǩԼ','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_QYBZ','ǩԼ��־','1','������ǩԼ','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_QYBZ','ǩԼ��־','2','����ǩԼ','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_QYBZ','ǩԼ��־','3','���ĵ�����ͬʱǩԼ','001','00000','admin' );
                                           
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_KKFS','�ۿʽ','1','ȫ��ۿ�','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_KKFS','�ۿʽ','2','�����ֿۿ�','001','00000','admin' );

INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_RZMS','��־ģʽ','0','����ģʽ','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_RZMS','��־ģʽ','1','����ģʽ','001','00000','admin' );

INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_QYMS','ǩԼģʽ','1','��Ʒ���룫�����ʺ�','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_QYMS','ǩԼģʽ','2','��Ʒ���룫�û���','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_QYMS','ǩԼģʽ','3','��Ʒ���룫�����ʺţ��û���','001','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_QYMS','ǩԼģʽ','4','ҵ���ţ��û���','001','00000','admin' );

INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_APP_CZLX', '��������', '1', '�鵵', '001', '00000', 'admin', '20110908');
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_APP_CZLX', '��������', '2', '����', '001', '00000', 'admin', '20110908');
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_APP_CZLX', '��������', '3', '����', '001', '00000', 'admin', '20110908');
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_APP_DXLX', '��������', '1', '���ݿ�', '001', '00000', 'admin', '20110908');
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_BATCH_MXCGBZ', '��ϸ�ɹ���־', '0', '�ɹ�', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_BATCH_MXCGBZ', '��ϸ�ɹ���־', '1', '���ֳɹ�', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_BATCH_MXCGBZ', '��ϸ�ɹ���־', '2', '����ʧ��', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_APP_DXLX', '��������', '2', '�ļ�', '001', '00000', 'admin', '20110908');
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_HQSJFS', '��ȡ���ݷ�ʽ', '0', 'FTP����ȡ', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_HQSJFS', '��ȡ���ݷ�ʽ', '1', 'WEB���������', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_HQSJFS', '��ȡ���ݷ�ʽ', '2', '����', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_MXTJBZ', '��ϸ�ύ��־', '0', '�ύ����δ�������ʧ����ϸ', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_MXTJBZ', '��ϸ�ύ��־', '1', '�ύ������δ�������ʧ����ϸ', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_MXTJBZ', '��ϸ�ύ��־', '2', '�ύ������δ������ϸ', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_MXHPBZ', '��ϸ���̱�־', '0', '��������������ϸ', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_MXHPBZ', '��ϸ���̱�־', '1', '���ɱ�����������ϸ', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_MXHPBZ', '��ϸ���̱�־', '2', '���ɱ����δ���ɹ���ϸ', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_MXHPBZ', '��ϸ���̱�־', '3', '���ɱ����δ���ʧ����ϸ', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_MXHPBZ', '��ϸ���̱�־', '4', '�ֱ����ɳɹ�ʧ����ϸ', '002', '00000', 'admin', NULL);

INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_FSSJFS', '�������ݷ�ʽ', '0', 'FTP��������', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_FSSJFS', '�������ݷ�ʽ', '1', 'WEB���������', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_FSSJFS', '�������ݷ�ʽ', '2', '����', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_APP_CXCL', '���޴���', '0', '���׾ܾ�', '001', '00000', 'admin', '20110906');
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_APP_CXCL', '���޴���', '1', '�����Ȩ��Ա����', '001', '00000', 'admin', '20110906');
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_APP_CXCL', '���޴���', '2', '�����Ȩ��Ա��λ', '001', '00000', 'admin', '20110906');
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_APP_CXCL', '���޴���', '3', '�����Ȩ��Ա����͸�λ', '001', '00000', 'admin', '20110906');
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_APP_EDKZFS', '��ȿ��Ʒ�ʽ', '1', '������', '001', '00000', 'admin', '20110915');
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_APP_EDKZFS', '��ȿ��Ʒ�ʽ', '0', '���Ƽ���', '001', '00000', 'admin', '20110915');
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_APP_EDKZFS', '��ȿ��Ʒ�ʽ', '9', '��������', '001', '00000', 'admin', '20110915');

INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_KZBL', '���Ʊ���', '0', '00', '001', '00000', 'admin', '20110830');
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_JZSX', '����˳��', '0', '��������', '001', '00000', 'admin', '20110917');
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_JZSX', '����˳��', '1', '���ϵ�����', '001', '00000', 'admin', '20110917');
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_JJMBZ', '�ӽ��ܱ�־', '0', '����', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_JJMBZ', '�ӽ��ܱ�־', '1', '������', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_WJLXZHBZ', '�ļ�����ת����־ ', '0', 'ת��', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_WJLXZHBZ', '�ļ�����ת����־ ', '1', '��ת��', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_CFCZBZ', '�ظ�������־', '0', '����', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_CFCZBZ', '�ظ�������־', '1', '������', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_SHSBBZ', '���ʧ�ܱ�־ ', '0', '����', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_SHSBBZ', '���ʧ�ܱ�־ ', '1', 'ʧ���˳�', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_XYMZHBZ', '��Ӧ��ת����־', '0', 'ת��', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_XYMZHBZ', '��Ӧ��ת����־', '1', '��ת��', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_DDBZ', '�ϵ��־', '0', '�޶ϵ�', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_DDBZ', '�ϵ��־', '1', '�ϵ�', '002', '00000', 'admin', NULL);
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_STEP_DDBZ', '�ϵ��־', '2', '����', '002', '00000', 'admin', NULL);

INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_DZLSLX','������ˮ����','1','�������˲�ƽ','003','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_DZLSLX','������ˮ����','2','���������˲�ƽ','003','00000','admin' );

INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_DZCLZT','���˴���״̬','0','δ����','003','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_DZCLZT','���˴���״̬','1','����ɹ�','003','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_DZCLZT','���˴���״̬','8','�������','003','00000','admin' );
INSERT INTO APP_DICT(PKEY,KEYJS,PVAL,PROMPT,SSYY,WHJG,WHGY) VALUES('K_DZCLZT','���˴���״̬','9','������','003','00000','admin' );

/* Ӧ����Ϣ */
insert into app_yyxx (YYBS, YYMC, YYSM, YYKFKSRQ, YYKFJSRQ, YYFBRQ, YYBBH, YHH, SQH, YYKFJL, YYZBJL, YYZT, EXTFLD) values ('001', 'app', '������������', '', '', '20130220', '2.1.3.0', '', '', 'YangDong', 'YangDong', '0', '');

/* ������Ϣ */
insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900001', '���׷�����ͣ', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900002', 'Ӧ����ͣ', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900003', '������ͣ', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900004', '���ݹ鵵', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900005', '��������', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900006', '���ݱ���', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900007', '���ݻָ�', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900008', 'ƽ̨����', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900010', '��Ʒ���׷�����ͣ', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900011', '���ڲ�ѯ', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900012', '�ڼ�������', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900013', '��Ʒҵ����ͣ', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900014', '������Ա��Ϣͬ��', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900015', '�����Ѽ���', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900016', '��������ˮ�Ǽ�', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900017', '�����ѻ�������', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900018', 'ƾ֤У��', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900019', 'ƾ֤ʹ��', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900020', 'ƾ֤����', '001', '0', '0', '1', '1', '1', '00000', 'admin', '', ' ', ' ', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900021', 'ƾ֤���쳷��', '001', '0', '0', '1', '1', '1', '00000', 'admin', '', ' ', ' ', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900022', 'ƾ֤�����ѯ', '001', '0', '0', '1', '1', '1', '00000', 'admin', '', ' ', ' ', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900023', 'ƾ֤���', '001', '0', '0', '1', '1', '1', '00000', 'admin', '', ' ', ' ', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900024', 'ƾ֤����', '001', '0', '0', '1', '1', '1', '00000', 'admin', '', ' ', ' ', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900025', 'ƾ֤����', '001', '0', '0', '1', '1', '1', '00000', 'admin', '', ' ', ' ', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900026', 'ƾ֤�ػ�', '001', '0', '0', '1', '1', '1', '00000', 'admin', '', ' ', ' ', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900027', 'ƾ֤��ѯ', '001', '0', '0', '1', '1', '1', '00000', 'admin', '', ' ', ' ', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900028', 'ƾ֤����', '001', '0', '0', '1', '1', '1', '00000', 'admin', '', ' ', ' ', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900029', 'ƾ֤���⳷��', '001', '0', '0', '1', '1', '1', '00000', 'admin', '', ' ', ' ', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900030', 'ƾ֤��⳷��', '001', '0', '0', '1', '1', '1', '00000', 'admin', '', ' ', ' ', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900031', '����ǩԼ��ϵ', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900032', '�Ǽ�ǩԼ��ϵ', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900033', '��ѯǩԼ��ϵ', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900034', '����ǩԼ��ϵ', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900040', 'shell��������', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900041', '������λǩԼ', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900042', '�޸ĵ�λǩԼ', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('900043', '��ѯ��λǩԼ', '001', '0', '1', '1', '1', '1', '00000', 'admin', '', '', '', '0');

/*������Ϣ */
insert into app_qdxx (QDBS, QDMC, QDSM, SJKZBZ, QSSJ, JSSJ, CZBZ, ZDCZBZ, EXTFLD1, EXTFLD2,  QDZT,WHJG,WHGY)
values ('200', 'tamc', 'TAMC����̨����', '1', '', '', '0', '0', '', '', '0', '00000','admin' );

insert into app_qdxx (QDBS, QDMC, QDSM, SJKZBZ, QSSJ, JSSJ, CZBZ, ZDCZBZ, EXTFLD1, EXTFLD2,  QDZT,WHJG,WHGY)
values ('201', 'cxs', '�����������', '1', '', '', '0', '0', '', '', '0', '00000','admin' );

insert into app_qdxx (QDBS, QDMC, QDSM, SJKZBZ, QSSJ, JSSJ, CZBZ, ZDCZBZ, EXTFLD1, EXTFLD2,  QDZT,WHJG,WHGY)
values ('202', 'netbk', '������������', '1', '', '', '0', '0', '', '', '0', '00000','admin' );

insert into app_qdxx (QDBS, QDMC, QDSM, SJKZBZ, QSSJ, JSSJ, CZBZ, ZDCZBZ, EXTFLD1, EXTFLD2,  QDZT,WHJG,WHGY)
values ('203', 'telbk', '�绰��������', '1', '', '', '0', '0', '', '', '0', '00000','admin' );

insert into app_qdxx (QDBS, QDMC, QDSM, SJKZBZ, QSSJ, JSSJ, CZBZ, ZDCZBZ, EXTFLD1, EXTFLD2,  QDZT,WHJG,WHGY)
values ('204', 'mbbk', '�ֻ���������', '1', '', '', '0', '0', '', '', '0', '00000','admin' );

insert into app_qdxx (QDBS, QDMC, QDSM, SJKZBZ, QSSJ, JSSJ, CZBZ, ZDCZBZ, EXTFLD1, EXTFLD2,  QDZT,WHJG,WHGY)
values ('205', 'atm', 'ATM����', '1', '', '', '0', '0', '', '', '0', '00000','admin' );

insert into app_qdxx (QDBS, QDMC, QDSM, SJKZBZ, QSSJ, JSSJ, CZBZ, ZDCZBZ, EXTFLD1, EXTFLD2,  QDZT,WHJG,WHGY)
values ('206', 'pos', 'POS����', '1', '', '', '0', '0', '', '', '0', '00000','admin' );

insert into app_qdxx (QDBS, QDMC, QDSM, SJKZBZ, QSSJ, JSSJ, CZBZ, ZDCZBZ, EXTFLD1, EXTFLD2,  QDZT,WHJG,WHGY)
values ('299', 'systask', 'systask�Զ�����', '1', '', '', '0', '0', '', '', '0', '00000','admin' );

/* ������������ */
insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_cpjggx', '', '', '��Ʒ������ϵ', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_dwcpxy', '', '', '��λ��ƷЭ��', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_dwxx', '', '', '��λ��Ϣ', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_jjrdj', '', '', '�ڼ��յǼ�', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_jyxx', '', '', '������Ϣ', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_kzsx', '', '', '��չ����', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_khcpqy', '', '', '�ͻ���ƷǩԼ', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_khxx', '', '', '������Ϣ', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_pzhmdj', '', '', 'ƾ֤����Ǽ�', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_pzsldj', '', '', 'ƾ֤�����Ǽ�', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_pzzl', '', '', 'ƾ֤����', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_qdxx', '', '', '������Ϣ', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_rzpz', '', '', '��������', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_sxffl', '', '', '�����ѷ���', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'APP_CPJYJGED', '', '', '��Ʒ���׻�����ȿ���', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'APP_CPJYGYED', '', '', '��Ʒ���׹�Ա��ȿ���', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'APP_CPJYGYKZ', '', '', '��Ʒ���׹�ԱȨ�޿���', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_txaqxx', '', '', 'ͨѶ��ȫ��Ϣ', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_xlkz', '', '', '���п���', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_yyxx', '', '', 'Ӧ����Ϣ', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_cpjyfw', '', '', '��Ʒ���׷���', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_cppzgx', '', '', '��Ʒƾ֤��ϵ', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_cpqdgx', '', '', '��Ʒ������ϵ', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_cpsxfgx', '', '', '��Ʒ�����ѹ�ϵ', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_cpsxfkz', '', '', '��Ʒ�����ѿ���', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_cpxx', '', '', '��Ʒ��Ϣ', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_cskz', '', '', '��������', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '3', '1', 'app_dict', '', '', '�����ֵ�', '', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '1', '1', 'app_drls', 'app_his_drls', 'C;ptrq;=;K_APP_PTLSGD;;|', 'ƽ̨������ˮ�鵵 ', ' ', '00000','admin' );

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG,WHGY)
values ('001', '2', '1', 'app_drls', '', 'C;ptrq;=;K_APP_PTLSQL;;|', 'ƽ̨��ˮ��ǰ������', ' ', '00000','admin' );
