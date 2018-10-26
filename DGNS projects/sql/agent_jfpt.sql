drop table agent_csys;

drop index agent_ddxx_Index_1;

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
);

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
   ptrq                 VARCHAR(8)             not null,
   ptls                 VARCHAR(16)            not null,
   jfbs                 INTEGER,
   jfje                 DECIMAL(17,2),
   yjsxf                DECIMAL(17,2),
   cgbs                 INTEGER,
   cgje                 DECIMAL(17,2),
   sssxf                DECIMAL(17,2),
   zt                   VARCHAR(1),
   zfqd                 VARCHAR(3),
   zffs                 VARCHAR(1),
   bz                   VARCHAR(16),
   fkhhh                VARCHAR(32),
   fkrmc                VARCHAR(200),
   fkrzh                VARCHAR(32),
   skhhh                VARCHAR(32),
   skrmc                VARCHAR(200),
   skrzh                VARCHAR(32),
   scczy                VARCHAR(16),
   scrq                 VARCHAR(8),
   scsj                 VARCHAR(6),
   jfczy                VARCHAR(16),
   jfrq                 VARCHAR(8),
   jfsj                 VARCHAR(6),
   kzzd1                VARCHAR(10),
   kzzd2                VARCHAR(20),
   kzzd3                VARCHAR(50),
   kzzd4                VARCHAR(100),
   kzzd5                VARCHAR(200),
   constraint P_AGENT_DDXX primary key (ddh)
);

comment on table agent_ddxx is
'������Ϣ��';

comment on column agent_ddxx.ddh is
'������';

comment on column agent_ddxx.ptrq is
'ƽ̨���� YYYYMMDD';

comment on column agent_ddxx.ptls is
'ƽ̨��ˮ';

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

comment on column agent_ddxx.zfqd is
'֧������';

comment on column agent_ddxx.zffs is
'֧����ʽ 1-���� 2-���� 3-�ֽ�';

comment on column agent_ddxx.bz is
'����';

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

comment on column agent_ddxx.scczy is
'���ɲ���Ա';

comment on column agent_ddxx.scrq is
'�������� YYYYMMDD';

comment on column agent_ddxx.scsj is
'����ʱ�� HHMMSS';

comment on column agent_ddxx.jfczy is
'�ɷѲ���Ա';

comment on column agent_ddxx.jfrq is
'�ɷ����� YYYYMMDD';

comment on column agent_ddxx.jfsj is
'�ɷ�ʱ�� HHMMSS';

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
-- Index: agent_ddxx_Index_1
--==============================================================
create unique index agent_ddxx_Index_1 on agent_ddxx (
   ptrq                 ASC,
   ptls                 ASC
);

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
);

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
   shlxmc               VARCHAR(100),
   jfxmdm               VARCHAR(32),
   jfxmmc               VARCHAR(100),
   shdm                 VARCHAR(16),
   shmc                 VARCHAR(200),
   qsyxrq               VARCHAR(8),
   zzyxrq               VARCHAR(8),
   whsj                 VARCHAR(14),
   why                  VARCHAR(16),
   whjg                 VARCHAR(16),
   khh                  VARCHAR(16),
   kzzd1                VARCHAR(10),
   kzzd2                VARCHAR(20),
   kzzd3                VARCHAR(50),
   kzzd4                VARCHAR(100),
   kzzd5                VARCHAR(200),
   constraint P_AGENT_JFHZ primary key (pch)
);

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

comment on column agent_jfhz.shlxmc is
'�̻���������';

comment on column agent_jfhz.jfxmdm is
'�ɷ���Ŀ����';

comment on column agent_jfhz.jfxmmc is
'�ɷ���Ŀ����';

comment on column agent_jfhz.shdm is
'�̻�����';

comment on column agent_jfhz.shmc is
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
   shlxmc               VARCHAR(100)           not null,
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
);

comment on table agent_jfxm is
'�ɷ���Ŀ��';

comment on column agent_jfxm.shlxdm is
'�̻����ʹ���';

comment on column agent_jfxm.shlxmc is
'�̻���������';

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
   shlxmc               VARCHAR(100),
   jfxmdm               VARCHAR(32),
   jfxmmc               VARCHAR(100),
   shdm                 VARCHAR(16),
   shmc                 VARCHAR(200),
   qsyxrq               VARCHAR(8),
   zzyxrq               VARCHAR(8),
   jfbh                 VARCHAR(32),
   qfje                 DECIMAL(17,2),
   znj                  DECIMAL(17,2),
   tkje                 DECIMAL(17,2),
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
   qszt                 VARCHAR(1)             not null,
   qsrq                 VARCHAR(8),
   kzzd1                VARCHAR(10),
   kzzd2                VARCHAR(20),
   kzzd3                VARCHAR(50),
   kzzd4                VARCHAR(100),
   kzzd5                VARCHAR(200),
   constraint P_AGENT_JFXQ primary key (pch, xh)
);

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

comment on column agent_jfxq.shlxmc is
'�̻���������';

comment on column agent_jfxq.jfxmdm is
'�ɷ���Ŀ����';

comment on column agent_jfxq.jfxmmc is
'�ɷ���Ŀ����';

comment on column agent_jfxq.shdm is
'�̻�����';

comment on column agent_jfxq.shmc is
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

comment on column agent_jfxq.qszt is
'����״̬ 1-δ���� 2-������';

comment on column agent_jfxq.qsrq is
'�������� YYYYMMDD';

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
   shlxmc               VARCHAR(100),
   shdm                 VARCHAR(16)            not null,
   shmc                 VARCHAR(200),
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
);

comment on table agent_khjfbh is
'�ͻ��ɷѱ�ű�';

comment on column agent_khjfbh.khh is
'�ͻ���';

comment on column agent_khjfbh.shlxdm is
'�̻����ʹ���';

comment on column agent_khjfbh.shlxmc is
'�̻���������';

comment on column agent_khjfbh.shdm is
'�̻�����';

comment on column agent_khjfbh.shmc is
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
   shlxmc               VARCHAR(100),
   shdm                 VARCHAR(16),
   shmc                 VARCHAR(200),
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
);

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
'���㷽�� 1-���������� 2-������ͻ�����';

comment on column agent_qsls.qszt is
'����״̬ 9-��ʼ 1-�ɹ� 2-ʧ�� 3-��ʱ';

comment on column agent_qsls.sbyy is
'ʧ��ԭ��';

comment on column agent_qsls.shlxdm is
'�̻����ʹ���';

comment on column agent_qsls.shlxmc is
'�̻���������';

comment on column agent_qsls.shdm is
'�̻�����';

comment on column agent_qsls.shmc is
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

