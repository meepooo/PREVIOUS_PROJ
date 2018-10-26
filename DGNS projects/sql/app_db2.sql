drop table APP_CPJGGX;

drop table APP_CPJYFW;

drop table APP_CPJYGYED;

drop table APP_CPJYGYKZ;

drop table APP_CPJYJGED;

drop table APP_CPPZGX;

drop table APP_CPQDGX;

drop index K_APP_CPSXFGX_1;

drop table APP_CPSXFGX;

drop table APP_CPSXFKZ;

drop table APP_CPXX;

drop table APP_CSKZ;

drop table APP_DICT;

drop index K_APP_DRLS_1;

drop table APP_DRLS;

drop table APP_DWCPXY;

drop table APP_DWXX;

drop table APP_GYSQED;

drop table APP_GYXX;

drop index K_APP_DRLS_2;

drop table APP_HIS_DRLS;

drop table APP_JJRDJ;

drop table APP_JYXX;

drop index K_APP_INDEX_1;

drop table APP_KHCPQY;

drop table APP_KHXX;

drop table APP_KZSX;

drop table APP_MJSJ;

drop table APP_MJSX;

drop table APP_PZGLKZ;

drop table APP_PZHMDJ;

drop table APP_PZSLDJ;

drop index K_APP_PZXX_2;

drop index K_APP_PZXX_1;

drop table APP_PZXX;

drop table APP_PZZL;

drop table APP_QDXX;

drop index INDEX_RWJKB_1;

drop table APP_RWJKB;

drop index K_APP_RZPZ_1;

drop table APP_RZPZ;

drop table APP_SXFFL;

drop index K_APP_SXFLS_1;

drop table APP_SXFLS;

drop index K_APP_SXFWHLS_1;

drop table APP_SXFWHLS;

drop table APP_TXAQXX;

drop table APP_XLKZ;

drop table APP_YWRQ;

drop table APP_YYXX;

drop distinct type CPDM;

drop distinct type DWBH;

drop distinct type JYDM;

drop distinct type JYGY;

drop distinct type JYJG;

drop distinct type PTLS;

drop distinct type PTRQ;

drop distinct type QDBS;

drop distinct type WHSJ;

drop distinct type YHH1;

drop distinct type YHZH;

drop distinct type YWBH;

drop distinct type ZHMC;

--==============================================================
-- Domain: CPDM
--==============================================================
create distinct type CPDM as CHAR(16) with comparisons;

--==============================================================
-- Domain: DWBH
--==============================================================
create distinct type DWBH as VARCHAR(16) with comparisons;

--==============================================================
-- Domain: JYDM
--==============================================================
create distinct type JYDM as CHAR(8) with comparisons;

--==============================================================
-- Domain: JYGY
--==============================================================
create distinct type JYGY as VARCHAR(16) with comparisons;

--==============================================================
-- Domain: JYJG
--==============================================================
create distinct type JYJG as VARCHAR(16) with comparisons;

--==============================================================
-- Domain: PTLS
--==============================================================
create distinct type PTLS as CHAR(8) with comparisons;

--==============================================================
-- Domain: PTRQ
--==============================================================
create distinct type PTRQ as CHAR(8) with comparisons;

--==============================================================
-- Domain: QDBS
--==============================================================
create distinct type QDBS as CHAR(3) with comparisons;

--==============================================================
-- Domain: WHSJ
--==============================================================
create distinct type WHSJ as VARCHAR(14) with comparisons;

--==============================================================
-- Domain: YHH1
--==============================================================
create distinct type YHH1 as VARCHAR(32) with comparisons;

--==============================================================
-- Domain: YHZH
--==============================================================
create distinct type YHZH as VARCHAR(32) with comparisons;

--==============================================================
-- Domain: YWBH
--==============================================================
create distinct type YWBH as CHAR(16) with comparisons;

--==============================================================
-- Domain: ZHMC
--==============================================================
create distinct type ZHMC as VARCHAR(80) with comparisons;

--==============================================================
-- Table: APP_CPJGGX
--==============================================================
create table APP_CPJGGX
(
   CPDM                 VARCHAR(16)            not null,
   JGBH                 VARCHAR(16)            not null,
   SJKZBZ               VARCHAR(1),
   QSSJ                 VARCHAR(6),
   JSSJ                 VARCHAR(6),
   WHJG                 VARCHAR(16),
   WHGY                 VARCHAR(16),
   WHSJ                 VARCHAR(14),
   EXTFLD1              VARCHAR(40),
   EXTFLD2              VARCHAR(40),
   ZT                   VARCHAR(1),
   constraint P_K_APP_CPJGGX_1 primary key (CPDM, JGBH)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

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

--==============================================================
-- Table: APP_CPJYFW
--==============================================================
create table APP_CPJYFW
(
   CPDM                 VARCHAR(16)            not null,
   JYDM                 VARCHAR(8)             not null,
   SJKZBZ               VARCHAR(1),
   QSSJ                 VARCHAR(6),
   JSSJ                 VARCHAR(6),
   XEKZBZ               VARCHAR(1),
   ZXXE                 NUMERIC(16,2),
   ZDXE                 NUMERIC(16,2),
   QYKZBZ               VARCHAR(1),
   QXKZ                 VARCHAR(8),
   QYEDKZFS             VARCHAR(1),
   JGEDKZFS             VARCHAR(1),
   WHJG                 VARCHAR(16),
   WHGY                 VARCHAR(16),
   WHSJ                 VARCHAR(14),
   EXTFLD1              VARCHAR(40),
   EXTFLD2              VARCHAR(40),
   QTBZ                 VARCHAR(1),
   constraint P_K_APP_CPJYFW_1 primary key (CPDM, JYDM)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

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
' Ĭ�϶��� 0 ������ ';

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

--==============================================================
-- Table: APP_CPJYGYED
--==============================================================
create table APP_CPJYGYED
(
   CPDM                 VARCHAR(16)            not null,
   JYDM                 VARCHAR(8)             not null,
   JYBZ                 VARCHAR(3)             not null,
   DBEDKZ               VARCHAR(1),
   RLJEDKZ              VARCHAR(1),
   YLJEDKZ              VARCHAR(1),
   GYJB                 VARCHAR(2)             not null,
   DBED                 NUMERIC(16,2),
   YLJED                NUMERIC(16,2),
   RLJED                NUMERIC(16,2),
   CXCL                 VARCHAR(1),
   SQGYGW               VARCHAR(8),
   SQGYJB               VARCHAR(2),
   WHJG                 VARCHAR(16),
   WHGY                 VARCHAR(16),
   WHSJ                 VARCHAR(14),
   EXTFLD1              VARCHAR(40),
   EXTFLD2              VARCHAR(40),
   constraint P_K_APP_CPJYGYED_1 primary key (CPDM, JYDM, JYBZ, GYJB)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

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

--==============================================================
-- Table: APP_CPJYGYKZ
--==============================================================
create table APP_CPJYGYKZ
(
   CPDM                 VARCHAR(16)            not null,
   JYDM                 VARCHAR(8)             not null,
   KZBZ                 VARCHAR(1),
   GYJB                 VARCHAR(2)             not null,
   CXCL                 VARCHAR(1),
   SQGYGW               VARCHAR(8),
   SQGYJB               VARCHAR(2),
   WHJG                 VARCHAR(16),
   WHGY                 VARCHAR(16),
   WHSJ                 VARCHAR(14),
   EXTFLD1              VARCHAR(40),
   EXTFLD2              VARCHAR(40),
   constraint P_K_APP_CPJYGYKZ_1 primary key (CPDM, JYDM)
)IN GAPS_DATA INDEX IN GAPS_INDEX ;

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

--==============================================================
-- Table: APP_CPJYJGED
--==============================================================
create table APP_CPJYJGED
(
   CPDM                 VARCHAR(16)            not null,
   JYDM                 VARCHAR(8)             not null,
   JYBZ                 VARCHAR(3)             not null,
   DBEDKZ               VARCHAR(1),
   RLJEDKZ              VARCHAR(1),
   YLJEDKZ              VARCHAR(1),
   JGJB                 VARCHAR(16)            not null,
   DBED                 NUMERIC(16,2),
   YLJED                NUMERIC(16,2),
   RLJED                NUMERIC(16,2),
   CXCL                 VARCHAR(1),
   SQGYGW               VARCHAR(8),
   SQGYJB               VARCHAR(2),
   WHJG                 VARCHAR(16),
   WHGY                 VARCHAR(16),
   WHSJ                 VARCHAR(14),
   EXTFLD1              VARCHAR(40),
   EXTFLD2              VARCHAR(40),
   constraint P_K_APP_CPJYJGED_1 primary key (CPDM, JYDM, JYBZ, JGJB)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

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

--==============================================================
-- Table: APP_CPPZGX
--==============================================================
create table APP_CPPZGX
(
   CPDM                 VARCHAR(16)            not null,
   PZXH                 INTEGER                not null,
   PZZL                 VARCHAR(3)             not null,
   CPPZSM               VARCHAR(40),
   WHJG                 VARCHAR(16),
   WHGY                 VARCHAR(16),
   WHSJ                 VARCHAR(14),
   EXTFLD1              VARCHAR(40),
   EXTFLD2              VARCHAR(40),
   constraint P_K_APP_CPPZGX_1 primary key (CPDM, PZXH)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

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

--==============================================================
-- Table: APP_CPQDGX
--==============================================================
create table APP_CPQDGX
(
   CPDM                 VARCHAR(16)            not null,
   QDBS                 VARCHAR(3)             not null,
   SJKZBZ               VARCHAR(1),
   QSSJ                 VARCHAR(6),
   JSSJ                 VARCHAR(6),
   XEKZBZ               VARCHAR(1),
   ZXXE                 NUMERIC(16,2),
   ZDXE                 NUMERIC(16,2),
   CZBZ                 VARCHAR(1),
   ZDCZBZ               VARCHAR(1),
   FPBCBZ               VARCHAR(1),
   FPCSFS               VARCHAR(1),
   WHJG                 VARCHAR(16),
   WHGY                 VARCHAR(16),
   WHSJ                 VARCHAR(14),
   EXTFLD1              VARCHAR(40),
   EXTFLD2              VARCHAR(40),
   ZT                   VARCHAR(1),
   constraint P_K_APP_CPQDGX_1 primary key (CPDM, QDBS)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

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

--==============================================================
-- Table: APP_CPSXFGX
--==============================================================
create table APP_CPSXFGX
(
   CPDM                 VARCHAR(16)            not null,
   KZTJ1                VARCHAR(32),
   KZTJ2                VARCHAR(32),
   KZTJ3                VARCHAR(32),
   KZTJ4                VARCHAR(32),
   KZTJ5                VARCHAR(32),
   KZTJ6                VARCHAR(32),
   KZTJ7                VARCHAR(32),
   KZTJ8                VARCHAR(32),
   KZTJ9                VARCHAR(32),
   KZTJ10               VARCHAR(32),
   FLBS                 VARCHAR(32)            not null,
   QYRQ                 VARCHAR(8)             not null,
   SXRQ                 VARCHAR(8)             not null,
   WHJG                 VARCHAR(16),
   WHGY                 VARCHAR(16),
   WHSJ                 VARCHAR(14),
   EXTFLD1              VARCHAR(20),
   EXTFLD2              VARCHAR(40),
   SM                   VARCHAR(40)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

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

--==============================================================
-- Index: K_APP_CPSXFGX_1
--==============================================================
create unique index K_APP_CPSXFGX_1 on APP_CPSXFGX (
   CPDM                 ASC,
   KZTJ1                ASC,
   KZTJ2                ASC,
   KZTJ3                ASC,
   KZTJ4                ASC,
   KZTJ5                ASC,
   FLBS                 ASC,
   QYRQ                 ASC,
   SXRQ                 ASC
);

--==============================================================
-- Table: APP_CPSXFKZ
--==============================================================
create table APP_CPSXFKZ
(
   CPDM                 VARCHAR(16)            not null,
   XH                   VARCHAR(2),
   KZSX                 VARCHAR(32)            not null,
   KZSXM                VARCHAR(40)            not null,
   SXLYLX               VARCHAR(1),
   KZSXLY               VARCHAR(40),
   WHJG                 VARCHAR(16),
   WHGY                 VARCHAR(16),
   WHSJ                 VARCHAR(14),
   EXTFLD1              VARCHAR(40),
   EXTFLD2              VARCHAR(40),
   constraint P_K_APP_CPSXFKZ_1 primary key (CPDM, KZSX)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

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

--==============================================================
-- Table: APP_CPXX
--==============================================================
create table APP_CPXX
(
   CPDM                 VARCHAR(16)            not null,
   CPMC                 VARCHAR(40),
   YYBS                 VARCHAR(8),
   ZBJG                 VARCHAR(16),
   ZBGY                 VARCHAR(16),
   KHJL                 VARCHAR(20),
   YWRQLX               VARCHAR(1),
   QDKZBZ               VARCHAR(1),
   JGKZCS               VARCHAR(1),
   SXFBZ                VARCHAR(1),
   SFQYBZ               VARCHAR(1),
   QYMS                 VARCHAR(1),
   XYXLJZ               VARCHAR(16),
   KKFS                 VARCHAR(1),
   JZSX                 VARCHAR(1),
   DZMS                 VARCHAR(1),
   ZJYYH                VARCHAR(16),
   ZJZYYH               VARCHAR(16),
   LSBLTS               INTEGER,
   PDBLTS               INTEGER,
   JYFS                 VARCHAR(1),
   RZMS                 VARCHAR(1),
   WHJG                 VARCHAR(16),
   WHGY                 VARCHAR(16),
   WHSJ                 VARCHAR(14),
   EXTFLD1              VARCHAR(40),
   EXTFLD2              VARCHAR(40),
   CPZT                 VARCHAR(1),
   constraint P_K_APP_CPXX_1 primary key (CPDM)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

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

--==============================================================
-- Table: APP_CSKZ
--==============================================================
create table APP_CSKZ
(
   CSJZ                 VARCHAR(20)            not null,
   CSLX                 VARCHAR(1),
   CSTJ                 VARCHAR(8),
   JDM                  VARCHAR(80)            not null,
   JDZ                  VARCHAR(40)            not null,
   REMARK               VARCHAR(40),
   JZLX                 VARCHAR(1),
   WHJG                 VARCHAR(16),
   WHGY                 VARCHAR(16),
   WHSJ                 VARCHAR(14),
   constraint P_K_APP_CSKZ_1 primary key (CSJZ)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

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

--==============================================================
-- Table: APP_DICT
--==============================================================
create table APP_DICT
(
   PKEY                 VARCHAR(20)            not null,
   KEYJS                VARCHAR(30)            not null,
   PVAL                 VARCHAR(20)            not null,
   PROMPT               VARCHAR(60)            not null,
   SSYY                 VARCHAR(8)             not null,
   WHJG                 VARCHAR(16),
   WHGY                 VARCHAR(16),
   WHSJ                 VARCHAR(14),
   constraint P_K_APP_DICT_1 primary key (PKEY, PVAL)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table APP_DICT is
'�����ֵ��';

comment on column APP_DICT.KEYJS is
'KEYֵ����';

comment on column APP_DICT.SSYY is
'Ӧ�ñ�ʶ';

--==============================================================
-- Table: APP_DRLS
--==============================================================
create table APP_DRLS
(
   PTRQ                 VARCHAR(8)             not null,
   PTLS                 INTEGER                not null,
   PTSJ                 VARCHAR(6),
   RZBZ                 VARCHAR(1),
   JYLX                 VARCHAR(1),
   YPTLS                INTEGER,
   JYJG                 VARCHAR(16),
   JYGY                 VARCHAR(16),
   QDBS                 VARCHAR(3),
   ZDSBBH               VARCHAR(8),
   YYBS                 VARCHAR(8),
   CPDM                 VARCHAR(16),
   YWBH                 VARCHAR(16),
   JYDM                 VARCHAR(8),
   YHBH                 VARCHAR(32),
   XZBZ                 VARCHAR(1),
   JDBZ                 VARCHAR(1),
   ZHLX                 VARCHAR(2),
   YHZH                 VARCHAR(32),
   DFZH                 VARCHAR(32),
   JYJE                 NUMERIC(16,2),
   SXF                  NUMERIC(16,2),
   PCBH                 INTEGER,
   JYXYM                VARCHAR(8),
   JYXYXX               VARCHAR(60),
   JYZT                 VARCHAR(1),
   EXTFLD1              VARCHAR(40),
   EXTFLD2              VARCHAR(40),
   constraint P_PK_APP_DRLS primary key (PTRQ, PTLS)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

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

--==============================================================
-- Index: K_APP_DRLS_1
--==============================================================
create index K_APP_DRLS_1 on APP_DRLS (
   PTRQ                 ASC,
   PTLS                 ASC,
   YWBH                 ASC
);

--==============================================================
-- Table: APP_DWCPXY
--==============================================================
create table APP_DWCPXY
(
   DWBH                 VARCHAR(16)            not null,
   CPDM                 VARCHAR(16)            not null,
   YWBH                 VARCHAR(16)            not null,
   YWMC                 VARCHAR(40),
   XYBH                 VARCHAR(20),
   YHDM                 VARCHAR(16),
   LJBS                 VARCHAR(8),
   ZHLX                 VARCHAR(2),
   SFBZ                 VARCHAR(1),
   DSZH                 VARCHAR(32),
   DSZHMC               VARCHAR(80),
   DFZH                 VARCHAR(32),
   DFZHMC               VARCHAR(80),
   KHJL                 VARCHAR(20),
   LXR                  VARCHAR(20),
   EMAIL                VARCHAR(32),
   LXDH                 VARCHAR(16),
   HYKSRQ               VARCHAR(8),
   HYJSRQ               VARCHAR(8),
   BLJG                 VARCHAR(16),
   BLGY                 VARCHAR(16),
   BLRQ                 VARCHAR(8),
   ZHZDED               NUMERIC(16,2),
   WHJG                 VARCHAR(16),
   WHGY                 VARCHAR(16),
   WHSJ                 VARCHAR(14),
   EXTFLD1              VARCHAR(40),
   EXTFLD2              VARCHAR(40),
   QYZT                 VARCHAR(1),
   constraint P_K_APP_DWCPXY_2 primary key (YWBH),
   constraint A_K_APP_CPDWXY_1 unique (DWBH, CPDM)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

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

--==============================================================
-- Table: APP_DWXX
--==============================================================
create table APP_DWXX
(
   DWBH                 VARCHAR(16)            not null,
   DWMC                 VARCHAR(80),
   DWZJLX               VARCHAR(2),
   DWZJHM               VARCHAR(32),
   DWLXR                VARCHAR(16),
   DWLXRDH              VARCHAR(16),
   DWDZ                 VARCHAR(60),
   DWEMAIL              VARCHAR(32),
   WHJG                 VARCHAR(16),
   WHGY                 VARCHAR(16),
   WHSJ                 VARCHAR(14),
   EXTFLD1              VARCHAR(40),
   EXTFLD2              VARCHAR(40),
   ZT                   VARCHAR(1),
   constraint P_K_APP_DWXX_1 primary key (DWBH)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

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

--==============================================================
-- Table: APP_GYSQED
--==============================================================
create table APP_GYSQED
(
   CPDM                 VARCHAR(16)            not null,
   JYDM                 VARCHAR(8)             not null,
   GYJB                 VARCHAR(8)             not null,
   GYGW                 VARCHAR(8)             not null,
   JYBZ                 VARCHAR(3)             not null,
   GYDBSQED             NUMERIC(16,2),
   GYRLJSQED            NUMERIC(16,2),
   GYYLJSQED            NUMERIC(16,2),
   JGDBSQED             NUMERIC(16,2),
   JGRLJSQED            NUMERIC(16,2),
   JGYLJSQED            NUMERIC(16,2),
   EXTFLD1              VARCHAR(40),
   EXTFLD2              VARCHAR(40),
   constraint P_K_APP_GYSQED_1 primary key (CPDM, JYDM, GYJB, GYGW, JYBZ)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

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

--==============================================================
-- Table: APP_GYXX
--==============================================================
create table APP_GYXX
(
   GYH                  VARCHAR(16)            not null,
   JGBH                 VARCHAR(16),
   MM                   VARCHAR(32),
   GYJB                 VARCHAR(2),
   GYGW                 VARCHAR(32),
   GYMC                 VARCHAR(16),
   EMAIL                VARCHAR(32),
   FAX                  VARCHAR(16),
   TEL                  VARCHAR(16),
   WHJG                 VARCHAR(16),
   WHGY                 VARCHAR(16),
   WHSJ                 VARCHAR(14),
   EXTFLD1              VARCHAR(40),
   EXTFLD2              VARCHAR(40),
   ZT                   VARCHAR(1),
   constraint P_K_APP_QYXX_1 primary key (GYH)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

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

--==============================================================
-- Table: APP_HIS_DRLS
--==============================================================
create table APP_HIS_DRLS
(
   PTRQ                 VARCHAR(8)             not null,
   PTLS                 INTEGER                not null,
   PTSJ                 VARCHAR(6),
   RZBZ                 VARCHAR(1),
   JYLX                 VARCHAR(1),
   YPTLS                INTEGER,
   JYJG                 VARCHAR(16),
   JYGY                 VARCHAR(16),
   QDBS                 VARCHAR(3),
   ZDSBBH               VARCHAR(8),
   YYBS                 VARCHAR(8),
   CPDM                 VARCHAR(16),
   YWBH                 VARCHAR(16),
   JYDM                 VARCHAR(8),
   YHBH                 VARCHAR(32),
   XZBZ                 VARCHAR(1),
   JDBZ                 VARCHAR(1),
   ZHLX                 VARCHAR(2),
   YHZH                 VARCHAR(32),
   DFZH                 VARCHAR(32),
   JYJE                 NUMERIC(16,2),
   SXF                  NUMERIC(16,2),
   PCBH                 INTEGER,
   JYXYM                VARCHAR(8),
   JYXYXX               VARCHAR(60),
   JYZT                 VARCHAR(1),
   EXTFLD1              VARCHAR(40),
   EXTFLD2              VARCHAR(40),
   constraint P_PK_APP_DRLS primary key (PTRQ, PTLS)
) IN GAPS_HIS_DATA INDEX IN GAPS_HIS_INDEX ;

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

--==============================================================
-- Index: K_APP_DRLS_2
--==============================================================
create index K_APP_DRLS_2 on APP_HIS_DRLS (
   PTRQ                 ASC,
   PTLS                 ASC,
   YWBH                 ASC
);

--==============================================================
-- Table: APP_JJRDJ
--==============================================================
create table APP_JJRDJ
(
   RQ                   VARCHAR(8)             not null,
   JRBZ                 VARCHAR(1)             not null,
   EXTFLD1              VARCHAR(20),
   constraint P_K_APP_JJRDJ_1 primary key (RQ)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table APP_JJRDJ is
'���ý��ձ�־';

comment on column APP_JJRDJ.RQ is
'����';

comment on column APP_JJRDJ.JRBZ is
'�ڼ��ձ�־ 0  �� 1�� ';

comment on column APP_JJRDJ.EXTFLD1 is
'��չ1';

--==============================================================
-- Table: APP_JYXX
--==============================================================
create table APP_JYXX
(
   JYDM                 VARCHAR(8)             not null,
   JYMC                 VARCHAR(40),
   YYBS                 VARCHAR(8),
   JYLX                 VARCHAR(1),
   LSJLBZ               VARCHAR(1),
   RZBZ                 VARCHAR(1),
   BBBZ                 VARCHAR(1),
   CPXG                 VARCHAR(1),
   WHJG                 VARCHAR(16),
   WHGY                 VARCHAR(16),
   WHSJ                 VARCHAR(14),
   EXTFLD1              VARCHAR(40),
   EXTFLD2              VARCHAR(40),
   QTBZ                 VARCHAR(1),
   constraint P_K_APP_JYXX_1 primary key (JYDM)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

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

--==============================================================
-- Table: APP_KHCPQY
--==============================================================
create table APP_KHCPQY
(
   XYBH                 VARCHAR(20)            not null,
   KHBH                 VARCHAR(16),
   CPDM                 VARCHAR(16)            not null,
   YWBH                 VARCHAR(16)            not null,
   ZHLX                 VARCHAR(2),
   KHJG                 VARCHAR(16),
   QYZH                 VARCHAR(32),
   ZHHM                 VARCHAR(80),
   DLZJLX               VARCHAR(3),
   DLZJHM               VARCHAR(32),
   ZJLX                 VARCHAR(3),
   ZJHM                 VARCHAR(32),
   QYLX                 VARCHAR(1),
   KHJL                 VARCHAR(20),
   HYKSRQ               VARCHAR(8),
   HYJSRQ               VARCHAR(8),
   KTQD                 VARCHAR(60),
   BLJG                 VARCHAR(16),
   BLGY                 VARCHAR(16),
   BLRQ                 VARCHAR(8),
   YHH1                 VARCHAR(32),
   YHH2                 VARCHAR(32),
   YHH3                 VARCHAR(32),
   YHMC                 VARCHAR(80),
   YHLX                 VARCHAR(16),
   YHYB                 VARCHAR(6),
   YHDH                 VARCHAR(12),
   YHDZ                 VARCHAR(60),
   JYBZ                 VARCHAR(3),
   KKZDXE               NUMERIC(13,2),
   KKZQ                 VARCHAR(1),
   YDKKRQ               VARCHAR(8),
   KKZT                 VARCHAR(1),
   KKRQ                 VARCHAR(8),
   DXTZBZ               VARCHAR(1),
   ZHZDED               NUMERIC(13,2),
   EXTFLD1              VARCHAR(40),
   EXTFLD2              VARCHAR(40),
   EXTFLD3              VARCHAR(40),
   EXTFLD4              VARCHAR(40),
   EXTFLD5              VARCHAR(40),
   EXTFLD6              VARCHAR(254),
   QYZT                 VARCHAR(1),
   constraint P_K_APP_CPKHQY_1 primary key (XYBH, CPDM)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

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

--==============================================================
-- Index: K_APP_INDEX_1
--==============================================================
create index K_APP_INDEX_1 on APP_KHCPQY (
   CPDM                 ASC,
   QYZH                 ASC,
   YHH1                 ASC,
   QYZT                 ASC
);

--==============================================================
-- Table: APP_KHXX
--==============================================================
create table APP_KHXX
(
   KHBH                 VARCHAR(16)            not null,
   KHXM                 VARCHAR(80),
   YWXM                 VARCHAR(40),
   BM                   VARCHAR(20),
   KHLX                 VARCHAR(1),
   ZJKHBH               VARCHAR(32),
   ZJLX                 VARCHAR(3)             not null,
   ZJHM                 VARCHAR(32)            not null,
   CSNY                 VARCHAR(8),
   SEX                  VARCHAR(1),
   GJ                   VARCHAR(3),
   HK                   VARCHAR(60),
   HYZK                 VARCHAR(1),
   JYCD                 VARCHAR(1),
   ZY                   VARCHAR(3),
   ZW                   VARCHAR(20),
   SRQK                 NUMERIC(16,2),
   GSDZ                 VARCHAR(60),
   GSYB                 VARCHAR(6),
   GSDH                 VARCHAR(16),
   ZZDZ                 VARCHAR(60),
   ZZYB                 VARCHAR(6),
   ZZDH                 VARCHAR(16),
   SJHM                 VARCHAR(16),
   MEMAIL               VARCHAR(32),
   YJDZLX               VARCHAR(1),
   BZ                   VARCHAR(1),
   constraint P_K_APP_KHXX_1 primary key (KHBH),
   constraint A_K_APP_KHXX_2 unique (ZJLX, ZJHM)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

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

--==============================================================
-- Table: APP_KZSX
--==============================================================
create table APP_KZSX
(
   PKEY                 VARCHAR(40)            not null,
   CSMC                 VARCHAR(20)            not null,
   CSSM                 VARCHAR(80)            not null,
   CSZ                  VARCHAR(80),
   EXTFLD               VARCHAR(40),
   WHJG                 VARCHAR(16),
   WHGY                 VARCHAR(16),
   WHSJ                 VARCHAR(14),
   constraint P_K_APP_KZSX_1 primary key (PKEY, CSMC)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

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

--==============================================================
-- Table: APP_MJSJ
--==============================================================
create table APP_MJSJ
(
   MJID                 VARCHAR(16)            not null,
   MJSM                 VARCHAR(40),
   SJXH                 INTEGER                not null,
   QSBZ                 VARCHAR(1),
   REQ1                 VARCHAR(40)            not null,
   REQ2                 VARCHAR(40),
   REQ3                 VARCHAR(40),
   REQ4                 VARCHAR(40),
   REQ5                 VARCHAR(40),
   REQ6                 VARCHAR(40),
   REQ7                 VARCHAR(40),
   REQ8                 VARCHAR(40),
   REQ9                 VARCHAR(40),
   REQ10                VARCHAR(40),
   RESP1                VARCHAR(40)            not null,
   RESP2                VARCHAR(40),
   RESP3                VARCHAR(40),
   RESP4                VARCHAR(40),
   RESP5                VARCHAR(40),
   RESP6                VARCHAR(40),
   RESP7                VARCHAR(40),
   RESP8                VARCHAR(40),
   RESP9                VARCHAR(40),
   RESP10               VARCHAR(40),
   WHJG                 VARCHAR(16),
   WHGY                 VARCHAR(16),
   WHSJ                 VARCHAR(14),
   constraint P_K_APP_MJSJ_1 primary key (MJID, SJXH)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

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

--==============================================================
-- Table: APP_MJSX
--==============================================================
create table APP_MJSX
(
   MJID                 VARCHAR(16)            not null,
   MJSM                 VARCHAR(40)            not null,
   SXLX                 VARCHAR(1)             not null,
   SXXH                 VARCHAR(2)             not null,
   SXMC                 VARCHAR(16)            not null,
   SXNR                 VARCHAR(40)            not null,
   SXSM                 VARCHAR(40),
   WHJG                 VARCHAR(16),
   WHGY                 VARCHAR(16),
   WHSJ                 VARCHAR(14),
   constraint P_K_APP_MJSX_1 primary key (MJID, SXLX, SXXH)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

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

--==============================================================
-- Table: APP_PZGLKZ
--==============================================================
create table APP_PZGLKZ
(
   PTRQ                 VARCHAR(8)             not null,
   PTSJ                 VARCHAR(6),
   PTLS                 INTEGER                not null,
   JYJG                 VARCHAR(16)            not null,
   JYGY                 VARCHAR(16)            not null,
   PZCZDZ               VARCHAR(2),
   CZLX                 VARCHAR(1),
   CZFX                 VARCHAR(1),
   PZLY                 VARCHAR(32),
   PZMD                 VARCHAR(32),
   PZSL                 INTEGER,
   QSHM                 VARCHAR(32),
   JSHM                 VARCHAR(32),
   JYZT                 VARCHAR(1),
   EXTFLD               VARCHAR(40),
   SM                   VARCHAR(40)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

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

--==============================================================
-- Table: APP_PZHMDJ
--==============================================================
create table APP_PZHMDJ
(
   PZZL                 VARCHAR(3)             not null,
   PZHM                 VARCHAR(32)            not null,
   PZWZ                 VARCHAR(34),
   NBJG                 VARCHAR(34),
   PZZT                 VARCHAR(1),
   GXRQ                 VARCHAR(8),
   GXSJ                 VARCHAR(6),
   GXLS                 INTEGER,
   GXJG                 VARCHAR(16),
   GXGY                 VARCHAR(16),
   GXSM                 VARCHAR(40),
   PZNR                 VARCHAR(80),
   EXFLD                VARCHAR(40),
   SM                   VARCHAR(40),
   constraint P_K_APP_PZHMDJ_1 primary key (PZZL, PZHM)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

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

--==============================================================
-- Table: APP_PZSLDJ
--==============================================================
create table APP_PZSLDJ
(
   PZZL                 VARCHAR(3)             not null,
   PZWZ                 VARCHAR(34)            not null,
   NBJG                 VARCHAR(34),
   PZZT                 VARCHAR(1)             not null,
   PZSL                 INTEGER,
   EXFLD                VARCHAR(40),
   SM                   VARCHAR(40),
   constraint P_K_APP_PZSLDJ_1 primary key (PZZL, PZWZ, PZZT)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

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

--==============================================================
-- Table: APP_PZXX
--==============================================================
create table APP_PZXX
(
   PTRQ                 VARCHAR(8)             not null,
   PTLS                 INTEGER                not null,
   PZXH                 INTEGER                not null,
   YWLS                 INTEGER,
   YWRQ                 VARCHAR(8),
   YYBS                 VARCHAR(8),
   CPDM                 VARCHAR(16)            not null,
   YHBH                 VARCHAR(32),
   YHBSH                VARCHAR(32),
   KHMC                 VARCHAR(80),
   YHZH                 VARCHAR(32),
   JYJE                 NUMERIC(16,2),
   JYJE2                NUMERIC(16,2),
   JYJE3                NUMERIC(16,2),
   SXF                  NUMERIC(16,2),
   JFZQ                 VARCHAR(16),
   QSRQ                 VARCHAR(10),
   JSRQ                 VARCHAR(10),
   SJDM                 VARCHAR(10),
   QDBS                 VARCHAR(3),
   PZZL                 VARCHAR(3),
   PZHM                 VARCHAR(32),
   PZSM                 VARCHAR(40),
   DYRQ                 VARCHAR(8),
   DYSJ                 VARCHAR(6),
   DYLS                 INTEGER,
   DYJG                 VARCHAR(16),
   DYGY                 VARCHAR(16),
   DYCS                 INTEGER,
   JLBZ                 VARCHAR(1),
   EXTFLD1              VARCHAR(40),
   EXTFLD2              VARCHAR(40),
   PZNR                 CLOB                   not compact not logged,
   constraint "P_Key_1" primary key (PTRQ, PTLS, PZXH)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

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

--==============================================================
-- Index: K_APP_PZXX_1
--==============================================================
create index K_APP_PZXX_1 on APP_PZXX (
   PTRQ                 ASC,
   PTLS                 ASC
);

--==============================================================
-- Index: K_APP_PZXX_2
--==============================================================
create index K_APP_PZXX_2 on APP_PZXX (
   PTRQ                 ASC,
   PTLS                 ASC,
   CPDM                 ASC,
   YHBH                 ASC,
   YHZH                 ASC
);

--==============================================================
-- Table: APP_PZZL
--==============================================================
create table APP_PZZL
(
   PZZL                 VARCHAR(3)             not null,
   PZMC                 VARCHAR(40)            not null,
   PZSM                 VARCHAR(80),
   PZLB                 VARCHAR(1),
   PZJB                 VARCHAR(1),
   PZLY                 VARCHAR(16),
   PZZGJG               VARCHAR(16)            not null,
   ZJPZZL               VARCHAR(8),
   DSFPZZL              VARCHAR(8),
   PZGS                 VARCHAR(40),
   KZLX                 VARCHAR(1)             not null,
   WHJG                 VARCHAR(16)            not null,
   WHGY                 VARCHAR(16)            not null,
   WHSJ                 VARCHAR(14),
   EXTFLD1              VARCHAR(40),
   EXTFLD2              VARCHAR(40),
   constraint P_K_APP_PZZL_1 primary key (PZZL)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

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

--==============================================================
-- Table: APP_QDXX
--==============================================================
create table APP_QDXX
(
   QDBS                 VARCHAR(3)             not null,
   QDMC                 VARCHAR(40),
   QDSM                 VARCHAR(80),
   SJKZBZ               VARCHAR(1),
   QSSJ                 VARCHAR(8),
   JSSJ                 VARCHAR(8),
   CZBZ                 VARCHAR(1),
   ZDCZBZ               VARCHAR(1),
   WHJG                 VARCHAR(16),
   WHGY                 VARCHAR(16),
   WHSJ                 VARCHAR(14),
   EXTFLD1              VARCHAR(40),
   EXTFLD2              VARCHAR(40),
   QDZT                 VARCHAR(1),
   constraint P_K_APP_QDXX_1 primary key (QDBS)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

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

--==============================================================
-- Table: APP_RWJKB
--==============================================================
create table APP_RWJKB
(
   YYBS                 VARCHAR(8),
   YYMC                 VARCHAR(40),
   CPDM                 VARCHAR(16)            not null,
   CPMC                 VARCHAR(40),
   RWMC                 VARCHAR(50),
   JYDM                 VARCHAR(8),
   JYMC                 VARCHAR(40),
   PTLS                 INTEGER                not null,
   PTRQ                 VARCHAR(8)             not null,
   JYJG                 VARCHAR(16)            not null,
   JYGY                 VARCHAR(16)            not null,
   QDBS                 VARCHAR(3),
   KSSJ                 VARCHAR(19),
   JSSJ                 VARCHAR(19),
   YXSJ                 INTEGER,
   ZXCS                 INTEGER,
   ZXZT                 VARCHAR(1),
   XYM                  VARCHAR(5),
   XYXX                 VARCHAR(60),
   EXTFLD1              VARCHAR(20),
   EXTFLD2              VARCHAR(20),
   constraint "P_Key_1" primary key (PTLS, PTRQ)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

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

--==============================================================
-- Index: INDEX_RWJKB_1
--==============================================================
create index INDEX_RWJKB_1 on APP_RWJKB (
   JYDM                 ASC,
   PTRQ                 ASC
);

--==============================================================
-- Table: APP_RZPZ
--==============================================================
create table APP_RZPZ
(
   SSYY                 VARCHAR(8)             not null,
   CZLX                 VARCHAR(1)             not null,
   DXLX                 VARCHAR(1)             not null,
   CZDX1                VARCHAR(128)           not null,
   CZDX2                VARCHAR(128),
   CZTJ                 VARCHAR(254),
   WHJG                 VARCHAR(16),
   WHGY                 VARCHAR(16),
   WHSJ                 VARCHAR(14),
   EXTFLD1              VARCHAR(20),
   EXTFLD2              VARCHAR(20),
   constraint "P_Key_1" primary key (CZLX, DXLX, CZDX1)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

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

--==============================================================
-- Index: K_APP_RZPZ_1
--==============================================================
create index K_APP_RZPZ_1 on APP_RZPZ (
   SSYY                 ASC,
   CZLX                 ASC,
   DXLX                 ASC
);

--==============================================================
-- Table: APP_SXFFL
--==============================================================
create table APP_SXFFL
(
   FLBS                 VARCHAR(32)            not null,
   XH                   VARCHAR(2)             not null,
   FDBZ                 VARCHAR(1)             not null,
   NWKBZ                VARCHAR(1),
   SXXKZ                VARCHAR(1)             not null,
   SXJE                 NUMERIC(16,2),
   XXJE                 NUMERIC(16,2),
   JSLX                 VARCHAR(1)             not null,
   JSCS                 NUMERIC(16,6)          not null,
   KJBZ                 VARCHAR(1),
   KJCS                 NUMERIC(16,6),
   FDLX                 VARCHAR(1),
   LJBZ                 VARCHAR(1),
   BHBZ                 VARCHAR(1),
   QSS                  VARCHAR(16),
   JSS                  VARCHAR(16),
   SM                   VARCHAR(40),
   WHJG                 VARCHAR(16),
   WHGY                 VARCHAR(16),
   WHSJ                 VARCHAR(14),
   constraint P_K_APP_SXFFL_1 primary key (FLBS, XH)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

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

--==============================================================
-- Table: APP_SXFLS
--==============================================================
create table APP_SXFLS
(
   PTRQ                 VARCHAR(8)             not null,
   PTLS                 VARCHAR(16)            not null,
   FLBS                 VARCHAR(32)            not null,
   YYBS                 VARCHAR(3),
   YWBH                 VARCHAR(16),
   CPDM                 VARCHAR(16)            not null,
   QDBS                 VARCHAR(3),
   JGBS                 VARCHAR(16)            not null,
   KHLX                 VARCHAR(1),
   KHBH                 VARCHAR(32),
   YHH                  VARCHAR(32),
   DWBH                 VARCHAR(16),
   XTNBZ                VARCHAR(1),
   JYLSH                VARCHAR(16),
   JYLX                 VARCHAR(1),
   JYRQ                 VARCHAR(8),
   JYGY                 VARCHAR(16)            not null,
   JYJG                 VARCHAR(16)            not null,
   JYJE                 NUMERIC(16,2),
   JYBS                 INTEGER,
   SXFJE                NUMERIC(16,2)          not null,
   SFZT                 VARCHAR(1),
   JFZH                 VARCHAR(32),
   DFZH                 VARCHAR(32),
   SFRQ                 VARCHAR(8),
   SFJYGY               VARCHAR(16)            not null,
   SFJYJG               VARCHAR(16)            not null,
   SFLS                 VARCHAR(16),
   LSZT                 VARCHAR(1),
   EXTFLD1              VARCHAR(20),
   EXTFLD2              VARCHAR(40),
   SM                   VARCHAR(40),
   constraint "P_Key_1" primary key (PTRQ, PTLS)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

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

--==============================================================
-- Index: K_APP_SXFLS_1
--==============================================================
create index K_APP_SXFLS_1 on APP_SXFLS (
   JYLSH                ASC,
   JYRQ                 ASC
);

--==============================================================
-- Table: APP_SXFWHLS
--==============================================================
create table APP_SXFWHLS
(
   CPDM                 VARCHAR(16),
   FLBS                 VARCHAR(32),
   CZNR                 VARCHAR(254),
   CZBM                 VARCHAR(32),
   WHLX                 VARCHAR(1),
   WHRQ                 VARCHAR(8),
   WHSJ                 VARCHAR(6),
   WHGY                 VARCHAR(16)            not null,
   WHJG                 VARCHAR(16)            not null,
   SQGY                 VARCHAR(16),
   SQJG                 VARCHAR(16),
   EXTFLD1              VARCHAR(20),
   EXTFLD2              VARCHAR(40),
   SM                   VARCHAR(40)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

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

--==============================================================
-- Index: K_APP_SXFWHLS_1
--==============================================================
create index K_APP_SXFWHLS_1 on APP_SXFWHLS (
   CPDM                 ASC,
   FLBS                 ASC,
   CZBM                 ASC,
   WHRQ                 ASC
);

--==============================================================
-- Table: APP_TXAQXX
--==============================================================
create table APP_TXAQXX
(
   LJBS                 VARCHAR(8)             not null,
   LJMC                 VARCHAR(40),
   LJLX                 VARCHAR(1),
   DWBH                 VARCHAR(16),
   QDKZ                 VARCHAR(1),
   TXMS                 VARCHAR(1),
   TXDZ                 VARCHAR(100),
   TXDK                 VARCHAR(6),
   FSCS                 INTEGER,
   JSCS                 INTEGER,
   LJJGH                VARCHAR(16),
   LJGYH                VARCHAR(16),
   LJZDH                VARCHAR(16),
   KEY1                 VARCHAR(128),
   KEY2                 VARCHAR(128),
   KEY3                 VARCHAR(128),
   FTPDZ                VARCHAR(16),
   FTPYH                VARCHAR(16),
   FTPMM                VARCHAR(32),
   FTPGZFS              VARCHAR(1),
   FTPCSFS              VARCHAR(1),
   FTPZDMS              VARCHAR(1),
   FTPDFLJ              VARCHAR(40),
   FTPBDLJ              VARCHAR(40),
   WHJG                 VARCHAR(16),
   WHGY                 VARCHAR(16),
   WHSJ                 VARCHAR(14),
   EXTFLD1              VARCHAR(40),
   EXTFLD2              VARCHAR(254),
   TXZT                 VARCHAR(1),
   QDZT                 VARCHAR(1),
   constraint P_K_APP_TXAQXX_1 primary key (LJBS)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

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

--==============================================================
-- Table: APP_XLKZ
--==============================================================
create table APP_XLKZ
(
   PKEY                 VARCHAR(20)            not null,
   CURR_VALUE           INTEGER                not null,
   PINC                 INTEGER                not null,
   MIN_VALUE            INTEGER                not null,
   MAX_VALUE            INTEGER                not null,
   REMARK               VARCHAR(40),
   WHJG                 VARCHAR(16),
   WHGY                 VARCHAR(16),
   WHSJ                 VARCHAR(14),
   constraint P_K_APP_XLKZ_1 primary key (PKEY)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table APP_XLKZ is
'���п��Ʊ�';

--==============================================================
-- Table: APP_YWRQ
--==============================================================
create table APP_YWRQ
(
   PKEY                 VARCHAR(20)            not null,
   SYYWRQ               VARCHAR(8),
   YWRQ                 VARCHAR(8)             not null,
   XYYWRQ               VARCHAR(8),
   CCH                  VARCHAR(2),
   LSH                  INTEGER,
   EXTFLD               VARCHAR(40),
   SM                   VARCHAR(40),
   constraint P_K_APP_YWRQ_1 primary key (PKEY)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

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

--==============================================================
-- Table: APP_YYXX
--==============================================================
create table APP_YYXX
(
   YYBS                 VARCHAR(8)             not null,
   YYMC                 VARCHAR(40),
   YYSM                 VARCHAR(80),
   YYKFKSRQ             VARCHAR(8),
   YYKFJSRQ             VARCHAR(8),
   YYFBRQ               VARCHAR(8),
   YYBBH                VARCHAR(20),
   YHH                  VARCHAR(40),
   SQH                  VARCHAR(40),
   YYKFJL               VARCHAR(40),
   YYZBJL               VARCHAR(40),
   YYZT                 VARCHAR(1),
   EXTFLD               VARCHAR(40),
   constraint P_K_APP_YYXX_1 primary key (YYBS)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

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

/*�����ֵ�*/
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_APP_GYJB', '��Ա����', '11', '���㾭��', '001', '00000', 'admin', '20110915');
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_APP_GYJB', '��Ա����', '12', '��������', '001', '00000', 'admin', '20110915');
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_APP_GYJB', '��Ա����', '22', '֧������', '001', '00000', 'admin', '20110915');
INSERT INTO APP_DICT(PKEY, KEYJS, PVAL, PROMPT, SSYY, WHJG, WHGY, WHSJ) VALUES('K_APP_GYJB', '��Ա����', '32', '��������', '001', '00000', 'admin', '20110915');

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
insert into app_yyxx (YYBS, YYMC, YYSM, YYKFKSRQ, YYKFJSRQ, YYFBRQ, YYBBH, YHH, SQH, YYKFJL, YYZBJL, YYZT, EXTFLD)
values ('001', 'app', 'App����ҵ�����', '', '', '20111001', '2.1.0.1', '', '', 'YangDong', 'YangDong', '0', '');

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
