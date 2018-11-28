alter table app_dwcpxy
    add fwrx varchar(32)
    add jfbhxsmc varchar(100)
    add khh varchar(32)
    add nbhzhmc varchar(100)
    add nbhzh varchar(32)
    add sxfnbhzhmc varchar(100)
    add sxfnbhzh varchar(32)
    add scfs varchar(2)
    add shzt varchar(1)
    add shsj varchar(14)
    add shgy varchar(16)
    add shjg varchar(32);
comment on column app_dwcpxy.fwrx is'��������';
comment on column app_dwcpxy.jfbhxsmc is'�ɷѱ����ʾ����';
comment on column app_dwcpxy.khh is'�ͻ���';
comment on column app_dwcpxy.nbhzhmc is'�ڲ����˺�����';
comment on column app_dwcpxy.nbhzh is'�ڲ����˺�';
comment on column app_dwcpxy.sxfnbhzhmc is'�������ڲ����˺�����';
comment on column app_dwcpxy.sxfnbhzh is'�������ڲ����˺�';
comment on column app_dwcpxy.scfs is'�ϴ���ʽ 01-�ɷ�ƽ̨ 02-����ϵͳ 03-���´���';
comment on column app_dwcpxy.shzt is'���״̬ 9-δ��� 1-���ͨ�� 2-��˾ܾ�';
comment on column app_dwcpxy.shsj is'���ʱ��';
comment on column app_dwcpxy.shgy is'��˹�Ա';
comment on column app_dwcpxy.shjg is'��˻���';
reorg table app_dwcpxy;

alter table APP_CPXX add sxftkbz varchar(1);
comment on column APP_CPXX.sxftkbz is'�������˿��־ 0-�� 1-����';
reorg table APP_CPXX;

ALTER TABLE YWTY_BUSI_DZ ALTER COLUMN dzcpno SET DATA TYPE varchar(9);
reorg table YWTY_BUSI_DZ;

--==============================================================
-- DBMS name:      IBM DB2 UDB 9.0 Common Server
-- Created on:     2017-01-03 11:30:24
--==============================================================


drop table YWTY_ZFWG_DZ;

drop table agent_csys;

drop table agent_ddxx;

drop table agent_ggxx;

drop index agent_jfhz_index_2;

drop index agent_jfhz_index_1;

drop table agent_jfhz;

drop table agent_jfxm;

drop table agent_jfxq;

drop table agent_khjfbh;

drop index agent_qsls_Index_1;

drop table agent_qsls;

--==============================================================
-- Table: YWTY_ZFWG_DZ
--==============================================================
create table YWTY_ZFWG_DZ
(
   JYSX                 VARCHAR(4) NOT NULL,
   QSRQ                 VARCHAR(8) NOT NULL,
   TRAN_TIME            VARCHAR(14) NOT NULL,
   ORDER_NO             VARCHAR(32) NOT NULL,
   Merchant_SEQ         VARCHAR(32) NOT NULL,
   Merchant_Id          VARCHAR(19) NOT NULL,
   TRAN_AMT             DECIMAL(20,2) NOT NULL,
   SXF_AMT              DECIMAL(20,2) NOT NULL,
   QSJE_AMT             DECIMAL(20,2) NOT NULL,
   RESPCODE             VARCHAR(8) NOT NULL,
   REMARK1              VARCHAR(32) NOT NULL,
   REMARK2              VARCHAR(32) ,
   DZ_FLAG              VARCHAR(1) ,
   constraint P_YWTY_ZFWG_DZ primary key (QSRQ, Merchant_SEQ)
)IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table YWTY_ZFWG_DZ is
'֧�����ض������ݱ�';

comment on column YWTY_ZFWG_DZ.JYSX is
'������д';

comment on column YWTY_ZFWG_DZ.QSRQ is
'��������';

comment on column YWTY_ZFWG_DZ.TRAN_TIME is
'���׷���ʱ��';

comment on column YWTY_ZFWG_DZ.ORDER_NO is
'������';

comment on column YWTY_ZFWG_DZ."Merchant_SEQ" is
'������ͳһ֧��ƽ̨��ˮ��';

comment on column YWTY_ZFWG_DZ."Merchant_Id" is
'�̻���';

comment on column YWTY_ZFWG_DZ.TRAN_AMT is
'���׽��';

comment on column YWTY_ZFWG_DZ.SXF_AMT is
'������';

comment on column YWTY_ZFWG_DZ.QSJE_AMT is
'��������';

comment on column YWTY_ZFWG_DZ.RESPCODE is
'��Ӧ��';

comment on column YWTY_ZFWG_DZ.REMARK1 is
'�̻�����1';

comment on column YWTY_ZFWG_DZ.REMARK2 is
'�̻�����2';

comment on column YWTY_ZFWG_DZ.DZ_FLAG is
'���˱�ʶ:1-������� 0-���������';

--==============================================================
-- Table: agent_csys
--==============================================================
create table agent_csys
(
   lb                   VARCHAR(32)            not null,
   srcs                 VARCHAR(128)           not null,
   sccs                 VARCHAR(128),
   ms                   VARCHAR(256),
   kzzd1                VARCHAR(10),
   kzzd2                VARCHAR(20),
   kzzd3                VARCHAR(50),
   kzzd4                VARCHAR(100),
   kzzd5                VARCHAR(200),
   constraint P_AGENT_CSYS primary key (lb, srcs)
)IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table agent_csys is
'����ӳ���';

comment on column agent_csys.lb is
'���';

comment on column agent_csys.srcs is
'�������';

comment on column agent_csys.sccs is
'�������';

comment on column agent_csys.ms is
'����';

comment on column agent_csys.kzzd1 is
'��չ�ֶ�1';

comment on column agent_csys.kzzd2 is
'��չ�ֶ�2';

comment on column agent_csys.kzzd3 is
'��չ�ֶ�3';

comment on column agent_csys.kzzd4 is
'��չ�ֶ�4';

comment on column agent_csys.kzzd5 is
'��չ�ֶ�5';

--==============================================================
-- Table: agent_ddxx
--==============================================================
create table agent_ddxx
(
   ddh                  VARCHAR(32)            not null,
   jfbs                 INTEGER,
   jfje                 DECIMAL(17,2),
   yjsxf                DECIMAL(17,2),
   cgbs                 INTEGER,
   cgje                 DECIMAL(17,2),
   sssxf                DECIMAL(17,2),
   zt                   VARCHAR(1),
   fkhhh                VARCHAR(32),
   fkrmc                VARCHAR(200),
   fkrzh                VARCHAR(32),
   skhhh                VARCHAR(32),
   skrmc                VARCHAR(200),
   skrzh                VARCHAR(32),
   pch                  VARCHAR(32)            not null,
   xh                   INTEGER                not null,
   whsj                 VARCHAR(14),
   why                  VARCHAR(16),
   whjg                 VARCHAR(16),
   kzzd1                VARCHAR(10),
   kzzd2                VARCHAR(20),
   kzzd3                VARCHAR(50),
   kzzd4                VARCHAR(100),
   kzzd5                VARCHAR(200),
   constraint P_AGENT_DDXX primary key (ddh)
)IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table agent_ddxx is
'������Ϣ��';

comment on column agent_ddxx.ddh is
'������';

comment on column agent_ddxx.jfbs is
'�ɷѱ���';

comment on column agent_ddxx.jfje is
'�ɷѽ��';

comment on column agent_ddxx.yjsxf is
'Ӧ��������';

comment on column agent_ddxx.cgbs is
'�ɹ�����';

comment on column agent_ddxx.cgje is
'�ɹ����';

comment on column agent_ddxx.sssxf is
'ʵ��������';

comment on column agent_ddxx.zt is
'״̬ 1-Ԥ�� 2-���� 3-�ѽ�';

comment on column agent_ddxx.fkhhh is
'�������к�';

comment on column agent_ddxx.fkrmc is
'����������';

comment on column agent_ddxx.fkrzh is
'�������˺�';

comment on column agent_ddxx.skhhh is
'�տ����к�';

comment on column agent_ddxx.skrmc is
'�տ�������';

comment on column agent_ddxx.skrzh is
'�տ����˺�';

comment on column agent_ddxx.pch is
'���κ�';

comment on column agent_ddxx.xh is
'ƽ̨��ˮ';

comment on column agent_ddxx.whsj is
'ά��ʱ�� YYYYMMDDHHMMSS';

comment on column agent_ddxx.why is
'ά��Ա';

comment on column agent_ddxx.whjg is
'ά������';

comment on column agent_ddxx.kzzd1 is
'��չ�ֶ�1';

comment on column agent_ddxx.kzzd2 is
'��չ�ֶ�2';

comment on column agent_ddxx.kzzd3 is
'��չ�ֶ�3';

comment on column agent_ddxx.kzzd4 is
'��չ�ֶ�4';

comment on column agent_ddxx.kzzd5 is
'��չ�ֶ�5';

--==============================================================
-- Table: agent_ggxx
--==============================================================
create table agent_ggxx
(
   bt                   VARCHAR(256)           not null,
   ggxx                 VARCHAR(2048)          not null,
   yxbz                 VARCHAR(1)             not null,
   whsj                 VARCHAR(14),
   why                  VARCHAR(16),
   whjg                 VARCHAR(16),
   kzzd1                VARCHAR(10),
   kzzd2                VARCHAR(20),
   kzzd3                VARCHAR(50),
   kzzd4                VARCHAR(100),
   kzzd5                VARCHAR(200),
   constraint P_AGENT_GGXX primary key (bt)
)IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table agent_ggxx is
'������Ϣ��';

comment on column agent_ggxx.bt is
'����';

comment on column agent_ggxx.ggxx is
'������Ϣ';

comment on column agent_ggxx.yxbz is
'��Ч��־ 1-��Ч 2-��Ч';

comment on column agent_ggxx.whsj is
'ά��ʱ�� YYYYMMDDHHMMSS';

comment on column agent_ggxx.why is
'ά��Ա';

comment on column agent_ggxx.whjg is
'ά������';

comment on column agent_ggxx.kzzd1 is
'��չ�ֶ�1';

comment on column agent_ggxx.kzzd2 is
'��չ�ֶ�2';

comment on column agent_ggxx.kzzd3 is
'��չ�ֶ�3';

comment on column agent_ggxx.kzzd4 is
'��չ�ֶ�4';

comment on column agent_ggxx.kzzd5 is
'��չ�ֶ�5';

--==============================================================
-- Table: agent_jfhz
--==============================================================
create table agent_jfhz
(
   pch                  VARCHAR(32)            not null,
   wjm                  VARCHAR(256)           not null,
   ptrq                 VARCHAR(8)             not null,
   ptls                 VARCHAR(16)            not null,
   ptsj                 VARCHAR(6),
   zbs                  INTEGER,
   zje                  DECIMAL(17,2),
   zznj                 DECIMAL(17,2),
   drzt                 VARCHAR(1)             not null,
   sbyy                 VARCHAR(200),
   jfnd                 VARCHAR(4),
   jfyf                 VARCHAR(2),
   shlxdm               VARCHAR(16),
   jfxmdm               VARCHAR(32),
   shdm                 VARCHAR(16),
   qsyxrq               VARCHAR(8),
   zzyxrq               VARCHAR(8),
   whsj                 VARCHAR(14),
   why                  VARCHAR(16),
   whjg                 VARCHAR(16),
   khh                  VARCHAR(16),
   scfs                 VARCHAR(2),
   pljfzbs              INTEGER,
   pljfzje              NUMERIC(17,2),
   kzzd1                VARCHAR(10),
   kzzd2                VARCHAR(20),
   kzzd3                VARCHAR(50),
   kzzd4                VARCHAR(100),
   kzzd5                VARCHAR(200),
   constraint P_AGENT_JFHZ primary key (pch)
)IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table agent_jfhz is
'�ɷѻ��ܱ�';

comment on column agent_jfhz.pch is
'���κ�';

comment on column agent_jfhz.wjm is
'�ļ���';

comment on column agent_jfhz.ptrq is
'ƽ̨���� YYYYMMDD';

comment on column agent_jfhz.ptls is
'ƽ̨��ˮ';

comment on column agent_jfhz.ptsj is
'ƽ̨ʱ�� HHMMSS';

comment on column agent_jfhz.zbs is
'�ܱ���';

comment on column agent_jfhz.zje is
'�ܽ��';

comment on column agent_jfhz.zznj is
'�����ɽ�';

comment on column agent_jfhz.drzt is
'����״̬ 9-������ 1-����ɹ� 2-����ʧ��';

comment on column agent_jfhz.sbyy is
'ʧ��ԭ��';

comment on column agent_jfhz.jfnd is
'�ɷ���� YYYY';

comment on column agent_jfhz.jfyf is
'�ɷ��·� MM';

comment on column agent_jfhz.shlxdm is
'�̻����ʹ���';

comment on column agent_jfhz.jfxmdm is
'�ɷ���Ŀ����';

comment on column agent_jfhz.shdm is
'�̻�����';

comment on column agent_jfhz.qsyxrq is
'��ʼ��Ч���� YYYYMMDD';

comment on column agent_jfhz.zzyxrq is
'��ֹ��Ч���� YYYYMMDD';

comment on column agent_jfhz.whsj is
'ά��ʱ�� YYYYMMDDHHMMSS';

comment on column agent_jfhz.why is
'ά��Ա';

comment on column agent_jfhz.whjg is
'ά������';

comment on column agent_jfhz.khh is
'�ͻ���';

comment on column agent_jfhz.scfs is
'�ϴ���ʽ 01-�ɷ�ƽ̨ 02-����ϵͳ 03-���´���';

comment on column agent_jfhz.pljfzbs is
'�����ɷ��ܱ���';

comment on column agent_jfhz.pljfzje is
'�����ɷ��ܽ��';

comment on column agent_jfhz.kzzd1 is
'��չ�ֶ�1';

comment on column agent_jfhz.kzzd2 is
'��չ�ֶ�2';

comment on column agent_jfhz.kzzd3 is
'��չ�ֶ�3';

comment on column agent_jfhz.kzzd4 is
'��չ�ֶ�2';

comment on column agent_jfhz.kzzd5 is
'��չ�ֶ�2';

--==============================================================
-- Index: agent_jfhz_index_1
--==============================================================
create unique index agent_jfhz_index_1 on agent_jfhz (
   wjm                  ASC
);

--==============================================================
-- Index: agent_jfhz_index_2
--==============================================================
create unique index agent_jfhz_index_2 on agent_jfhz (
   ptrq                 ASC,
   ptls                 ASC
);

--==============================================================
-- Table: agent_jfxm
--==============================================================
create table agent_jfxm
(
   shlxdm               VARCHAR(16)            not null,
   jfxmdm               VARCHAR(32)            not null,
   jfxmmc               VARCHAR(100)           not null,
   shbz                 VARCHAR(1)             not null,
   yxbz                 VARCHAR(1)             not null,
   whsj                 VARCHAR(14),
   why                  VARCHAR(16),
   whjg                 VARCHAR(16),
   shsj                 VARCHAR(14),
   shy                  VARCHAR(16),
   shjg                 VARCHAR(16),
   kzzd1                VARCHAR(10),
   kzzd2                VARCHAR(20),
   kzzd3                VARCHAR(50),
   kzzd4                VARCHAR(100),
   kzzd5                VARCHAR(200),
   constraint P_AGENT_JFXM primary key (shlxdm, jfxmdm)
)IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table agent_jfxm is
'�ɷ���Ŀ��';

comment on column agent_jfxm.shlxdm is
'�̻����ʹ���';

comment on column agent_jfxm.jfxmdm is
'�ɷ���Ŀ����';

comment on column agent_jfxm.jfxmmc is
'�ɷ���Ŀ����';

comment on column agent_jfxm.shbz is
'��˱�־ 9-δ��� 1-���ͨ�� 2-��˾ܾ�';

comment on column agent_jfxm.yxbz is
'��Ч��־ 1-��Ч 2-��Ч';

comment on column agent_jfxm.whsj is
'ά��ʱ�� YYYYMMDDHHMMSS';

comment on column agent_jfxm.why is
'ά��Ա';

comment on column agent_jfxm.whjg is
'ά������';

comment on column agent_jfxm.shsj is
'���ʱ��';

comment on column agent_jfxm.shy is
'���Ա';

comment on column agent_jfxm.shjg is
'��˻���';

comment on column agent_jfxm.kzzd1 is
'��չ�ֶ�1';

comment on column agent_jfxm.kzzd2 is
'��չ�ֶ�2';

comment on column agent_jfxm.kzzd3 is
'��չ�ֶ�3';

comment on column agent_jfxm.kzzd4 is
'��չ�ֶ�4';

comment on column agent_jfxm.kzzd5 is
'��չ�ֶ�5';

--==============================================================
-- Table: agent_jfxq
--==============================================================
create table agent_jfxq
(
   pch                  VARCHAR(32)            not null,
   xh                   INTEGER                not null,
   xm                   VARCHAR(100),
   jfnd                 VARCHAR(4),
   jfyf                 VARCHAR(2),
   shlxdm               VARCHAR(16),
   jfxmdm               VARCHAR(32),
   shdm                 VARCHAR(16),
   qsyxrq               VARCHAR(8),
   zzyxrq               VARCHAR(8),
   jfbh                 VARCHAR(32),
   qfje                 DECIMAL(17,2),
   znj                  DECIMAL(17,2),
   tkje                 DECIMAL(17,2),
   khzh                 VARCHAR(32),
   kxrq                 VARCHAR(8),
   sjh                  VARCHAR(16),
   zjhm                 VARCHAR(32),
   glfy1                DECIMAL(17,2),
   glfy2                DECIMAL(17,2),
   bz1                  VARCHAR(512),
   bz2                  VARCHAR(1024),
   khh                  VARCHAR(16),
   whsj                 VARCHAR(14),
   why                  VARCHAR(16),
   whjg                 VARCHAR(16),
   yxbz                 VARCHAR(1)             not null,
   zt                   VARCHAR(2)             not null,
   jfrq                 VARCHAR(8),
   jfls                 VARCHAR(16),
   tkrq                 VARCHAR(8),
   tkls                 VARCHAR(16),
   tkyy                 VARCHAR(100),
   qszt                 VARCHAR(1)             not null,
   qsrq                 VARCHAR(8),
   zflx                 VARCHAR(1),
   kzzd1                VARCHAR(10),
   kzzd2                VARCHAR(20),
   kzzd3                VARCHAR(50),
   kzzd4                VARCHAR(100),
   kzzd5                VARCHAR(200),
   constraint P_AGENT_JFXQ primary key (pch, xh)
)IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table agent_jfxq is
'�ɷ������';

comment on column agent_jfxq.pch is
'���κ�';

comment on column agent_jfxq.xh is
'���';

comment on column agent_jfxq.xm is
'����';

comment on column agent_jfxq.jfnd is
'�ɷ���� YYYY';

comment on column agent_jfxq.jfyf is
'�ɷ��·� MM';

comment on column agent_jfxq.shlxdm is
'�̻����ʹ���';

comment on column agent_jfxq.jfxmdm is
'�ɷ���Ŀ����';

comment on column agent_jfxq.shdm is
'�̻�����';

comment on column agent_jfxq.qsyxrq is
'��ʼ��Ч���� YYYYMMDD';

comment on column agent_jfxq.zzyxrq is
'��ֹ��Ч���� YYYYMMDD';

comment on column agent_jfxq.jfbh is
'�ɷѱ��';

comment on column agent_jfxq.qfje is
'Ƿ�ѽ��';

comment on column agent_jfxq.znj is
'������';

comment on column agent_jfxq.tkje is
'�˿���';

comment on column agent_jfxq.khzh is
'�ͻ��˺�';

comment on column agent_jfxq.kxrq is
'��������';

comment on column agent_jfxq.sjh is
'�ֻ���';

comment on column agent_jfxq.zjhm is
'֤������';

comment on column agent_jfxq.glfy1 is
'��������1';

comment on column agent_jfxq.glfy2 is
'��������2';

comment on column agent_jfxq.bz1 is
'��ע1';

comment on column agent_jfxq.bz2 is
'��ע2';

comment on column agent_jfxq.khh is
'�ͻ���';

comment on column agent_jfxq.whsj is
'ά��ʱ�� YYYYMMDDHHMMSS';

comment on column agent_jfxq.why is
'ά��Ա';

comment on column agent_jfxq.whjg is
'ά������';

comment on column agent_jfxq.yxbz is
'��Ч��־ 1-��Ч 2-��Ч';

comment on column agent_jfxq.zt is
'״̬ 90-��ʼ 10-Ԥ�� 20-���� 21-�ѽ� 30-�˿��� 31-���˿�';

comment on column agent_jfxq.jfrq is
'�ɷ����� YYYYMMDD';

comment on column agent_jfxq.jfls is
'�ɷ���ˮ';

comment on column agent_jfxq.tkrq is
'�˿����� YYYYMMDD';

comment on column agent_jfxq.tkls is
'�˿���ˮ';

comment on column agent_jfxq.tkyy is
'�˿�ԭ��';

comment on column agent_jfxq.qszt is
'����״̬ 1-δ���� 2-������';

comment on column agent_jfxq.qsrq is
'�������� YYYYMMDD';

comment on column agent_jfxq.zflx is
'֧������ 1-����֧�� 2-����֧�� 3-����֧��';

comment on column agent_jfxq.kzzd1 is
'��չ�ֶ�1';

comment on column agent_jfxq.kzzd2 is
'��չ�ֶ�2';

comment on column agent_jfxq.kzzd3 is
'��չ�ֶ�3';

comment on column agent_jfxq.kzzd4 is
'��չ�ֶ�4';

comment on column agent_jfxq.kzzd5 is
'��չ�ֶ�5';

--==============================================================
-- Table: agent_khjfbh
--==============================================================
create table agent_khjfbh
(
   khh                  VARCHAR(16)            not null,
   shlxdm               VARCHAR(16)            not null,
   shdm                 VARCHAR(16)            not null,
   jfbh                 VARCHAR(32)            not null,
   yhm                  VARCHAR(200),
   bz                   VARCHAR(256),
   yxbz                 VARCHAR(1),
   whsj                 VARCHAR(14),
   why                  VARCHAR(16),
   whjg                 VARCHAR(16),
   kzzd1                VARCHAR(10),
   kzzd2                VARCHAR(20),
   kzzd3                VARCHAR(50),
   kzzd4                VARCHAR(100),
   kzzd5                VARCHAR(200),
   constraint P_AGENT_KHJFBH primary key (khh, shlxdm, shdm, jfbh)
)IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table agent_khjfbh is
'�ͻ��ɷѱ�ű�';

comment on column agent_khjfbh.khh is
'�ͻ���';

comment on column agent_khjfbh.shlxdm is
'�̻����ʹ���';

comment on column agent_khjfbh.shdm is
'�̻�����';

comment on column agent_khjfbh.jfbh is
'�ɷѱ��';

comment on column agent_khjfbh.yhm is
'�û���';

comment on column agent_khjfbh.bz is
'��ע';

comment on column agent_khjfbh.yxbz is
'��Ч��־ 1-��Ч 2-��Ч';

comment on column agent_khjfbh.whsj is
'ά��ʱ�� YYYYMMDDHHMMSS';

comment on column agent_khjfbh.why is
'ά��Ա';

comment on column agent_khjfbh.whjg is
'ά������';

comment on column agent_khjfbh.kzzd1 is
'��չ�ֶ�1';

comment on column agent_khjfbh.kzzd2 is
'��չ�ֶ�2';

comment on column agent_khjfbh.kzzd3 is
'��չ�ֶ�3';

comment on column agent_khjfbh.kzzd4 is
'��չ�ֶ�4';

comment on column agent_khjfbh.kzzd5 is
'��չ�ֶ�5';

--==============================================================
-- Table: agent_qsls
--==============================================================
create table agent_qsls
(
   qsrq                 VARCHAR(8)             not null,
   qssj                 VARCHAR(6),
   qsls                 VARCHAR(16)            not null,
   qsbs                 INTEGER,
   qsje                 DECIMAL(17,2),
   qslx                 VARCHAR(1)             not null,
   qsfx                 VARCHAR(1)             not null,
   qszt                 VARCHAR(1),
   sbyy                 VARCHAR(200),
   shlxdm               VARCHAR(16),
   shdm                 VARCHAR(16),
   fkhhh                VARCHAR(32),
   fkrmc                VARCHAR(200),
   fkrzh                VARCHAR(32),
   skhhh                VARCHAR(32),
   skrmc                VARCHAR(200),
   skrzh                VARCHAR(32),
   ywbh                 VARCHAR(16)            not null,
   dzrq                 VARCHAR(8)             not null,
   kzzd1                VARCHAR(10),
   kzzd2                VARCHAR(20),
   kzzd3                VARCHAR(50),
   kzzd4                VARCHAR(100),
   kzzd5                VARCHAR(200),
   constraint P_AGENT_QSLS primary key (qsrq, qsls)
)IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table agent_qsls is
'������ˮ��';

comment on column agent_qsls.qsrq is
'�������� YYYYMMDD';

comment on column agent_qsls.qssj is
'����ʱ�� HHMMSS';

comment on column agent_qsls.qsls is
'������ˮ';

comment on column agent_qsls.qsbs is
'�������';

comment on column agent_qsls.qsje is
'������';

comment on column agent_qsls.qslx is
'�������� 1-�ʽ����� 2-����������';

comment on column agent_qsls.qsfx is
'���㷽�� 1-����������(�����ɷ�) 2-����������(ֱ�ӽɷ�)  3-������ͻ����� ';

comment on column agent_qsls.qszt is
'����״̬ 9-��ʼ 1-�ɹ� 2-ʧ�� 3-��ʱ';

comment on column agent_qsls.sbyy is
'ʧ��ԭ��';

comment on column agent_qsls.shlxdm is
'�̻����ʹ���';

comment on column agent_qsls.shdm is
'�̻�����';

comment on column agent_qsls.fkhhh is
'�������к�';

comment on column agent_qsls.fkrmc is
'����������';

comment on column agent_qsls.fkrzh is
'�������˺�';

comment on column agent_qsls.skhhh is
'�տ����к�';

comment on column agent_qsls.skrmc is
'�տ�������';

comment on column agent_qsls.skrzh is
'�տ����˺�';

comment on column agent_qsls.ywbh is
'ҵ����';

comment on column agent_qsls.dzrq is
'�������� YYYYMMDD';

comment on column agent_qsls.kzzd1 is
'��չ�ֶ�1';

comment on column agent_qsls.kzzd2 is
'��չ�ֶ�2';

comment on column agent_qsls.kzzd3 is
'��չ�ֶ�3';

comment on column agent_qsls.kzzd4 is
'��չ�ֶ�4';

comment on column agent_qsls.kzzd5 is
'��չ�ֶ�5';

--==============================================================
-- Index: agent_qsls_Index_1
--==============================================================
create index agent_qsls_Index_1 on agent_qsls (
   ywbh                 ASC,
   dzrq                 ASC
);
