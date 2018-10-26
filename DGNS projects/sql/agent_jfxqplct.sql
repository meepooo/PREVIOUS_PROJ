drop table agent_jfxqplct;

--==============================================================
-- Table: agent_jfxqplct
--==============================================================
create table agent_jfxqplct
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
   constraint P_AGENT_jfxqplct primary key (pch, xh)
);

comment on table agent_jfxqplct is
'�ɷ��������������';

comment on column agent_jfxqplct.pch is
'���κ�';

comment on column agent_jfxqplct.xh is
'���';

comment on column agent_jfxqplct.xm is
'����';

comment on column agent_jfxqplct.jfnd is
'�ɷ���� YYYY';

comment on column agent_jfxqplct.jfyf is
'�ɷ��·� MM';

comment on column agent_jfxqplct.shlxdm is
'�̻����ʹ���';

comment on column agent_jfxqplct.shlxmc is
'�̻���������';

comment on column agent_jfxqplct.jfxmdm is
'�ɷ���Ŀ����';

comment on column agent_jfxqplct.jfxmmc is
'�ɷ���Ŀ����';

comment on column agent_jfxqplct.shdm is
'�̻�����';

comment on column agent_jfxqplct.shmc is
'�̻�����';

comment on column agent_jfxqplct.qsyxrq is
'��ʼ��Ч���� YYYYMMDD';

comment on column agent_jfxqplct.zzyxrq is
'��ֹ��Ч���� YYYYMMDD';

comment on column agent_jfxqplct.jfbh is
'�ɷѱ��';

comment on column agent_jfxqplct.qfje is
'Ƿ�ѽ��';

comment on column agent_jfxqplct.znj is
'������';

comment on column agent_jfxqplct.tkje is
'�˿���';

comment on column agent_jfxqplct.bz1 is
'��ע1';

comment on column agent_jfxqplct.bz2 is
'��ע2';

comment on column agent_jfxqplct.khh is
'�ͻ���';

comment on column agent_jfxqplct.whsj is
'ά��ʱ�� YYYYMMDDHHMMSS';

comment on column agent_jfxqplct.why is
'ά��Ա';

comment on column agent_jfxqplct.whjg is
'ά������';

comment on column agent_jfxqplct.yxbz is
'��Ч��־ 1-��Ч 2-��Ч';

comment on column agent_jfxqplct.zt is
'״̬ 90-��ʼ 10-Ԥ�� 20-���� 21-�ѽ� 30-�˿��� 31-���˿�';

comment on column agent_jfxqplct.jfrq is
'�ɷ����� YYYYMMDD';

comment on column agent_jfxqplct.jfls is
'�ɷ���ˮ';

comment on column agent_jfxqplct.tkrq is
'�˿����� YYYYMMDD';

comment on column agent_jfxqplct.tkls is
'�˿���ˮ';

comment on column agent_jfxqplct.qszt is
'����״̬ 1-δ���� 2-������';

comment on column agent_jfxqplct.qsrq is
'�������� YYYYMMDD';

comment on column agent_jfxqplct.kzzd1 is
'��չ�ֶ�1';

comment on column agent_jfxqplct.kzzd2 is
'��չ�ֶ�2';

comment on column agent_jfxqplct.kzzd3 is
'��չ�ֶ�3';

comment on column agent_jfxqplct.kzzd4 is
'��չ�ֶ�4';

comment on column agent_jfxqplct.kzzd5 is
'��չ�ֶ�5';
