drop index K_AGT_DRLS_3;

drop index K_AGT_DRLS_2;

drop index K_AGT_DRLS_1;

drop table AGENT_DRLS;

drop index K_AGT_DZBPB_3;

drop index K_AGT_DZBPB_2;

drop index K_AGT_DZBPB_1;

drop table AGENT_DZBPB;

drop index K_AGT_DZLSB_1;

drop table AGENT_DZLSB;

drop index K_AGT_DRLS_6;

drop index K_AGT_DRLS_5;

drop index K_AGT_DRLS_4;

drop table AGENT_HIS_DRLS;

drop table AGENT_RZZT;

drop table AGENT_TJ;

--==============================================================
-- Table: AGENT_DRLS
--==============================================================
create table AGENT_DRLS
(
   PTRQ                 VARCHAR(8)             not null,
   PTSJ                 VARCHAR(6),
   PTLS                 INTEGER                not null,
   JYXH                 INTEGER                not null default 1,
   YPTLSH               INTEGER,
   JYJG                 VARCHAR(16),
   JYGY                 VARCHAR(16),
   SQJG                 VARCHAR(16),
   SQGY                 VARCHAR(16),
   QDBS                 VARCHAR(3),
   ZDSBBH               VARCHAR(8),
   CPDM                 VARCHAR(16),
   YWBH                 VARCHAR(16),
   YWRQ                 VARCHAR(8),
   YWLSH                INTEGER,
   JYDM                 VARCHAR(8),
   KHMC                 VARCHAR(80),
   KHBH                 VARCHAR(32),
   DQDM                 VARCHAR(8),
   YHLX                 VARCHAR(16),
   YHH1                 VARCHAR(32),
   YHBSH                VARCHAR(32),
   YHMC                 VARCHAR(80),
   JYBZ                 VARCHAR(3),
   XZBZ                 VARCHAR(1),
   JDBZ                 VARCHAR(1),
   ZHLX                 VARCHAR(2),
   YHZH                 VARCHAR(32),
   JYJE                 NUMERIC(16,2),
   JYJE2                NUMERIC(16,2),
   SXF                  NUMERIC(16,2),
   ZNJ                  NUMERIC(16,2),
   PZZL                 VARCHAR(3),
   PZHM                 VARCHAR(32),
   JFBSH                VARCHAR(32),
   CXLSH                INTEGER,
   JYZY                 VARCHAR(40),
   FQFLSH               VARCHAR(32),
   FQFRQ                VARCHAR(8),
   FQFSJ                VARCHAR(6),
   FQFJYDM              VARCHAR(8),
   DSFLSH               VARCHAR(22),
   DSFRQ                VARCHAR(14),
   DSFJYLX              VARCHAR(8),
   DSFJYDM              VARCHAR(8),
   DSFXYM               VARCHAR(8),
   DSFXYXX              VARCHAR(60),
   DSFJYZT              VARCHAR(1),
   ZJLSH                VARCHAR(32),
   ZJRQ                 VARCHAR(14),
   ZJJYDM               VARCHAR(8),
   ZJXYM                VARCHAR(8),
   ZJXYXX               VARCHAR(60),
   ZJJYZT               VARCHAR(1),
   JYXYM                VARCHAR(8),
   JYXYXX               VARCHAR(60),
   JYZT                 VARCHAR(1),
   DSFDZBZ              VARCHAR(1),
   ZJDZBZ               VARCHAR(1),
   EXTFLD1              VARCHAR(40),
   EXTFLD2              VARCHAR(40),
   EXTFLD3              VARCHAR(40),
   EXTFLD4              VARCHAR(40),
   EXTFLD5              VARCHAR(40),
   EXTFLD6              VARCHAR(40),
   constraint P_PK_AGENT_DRLS primary key (PTRQ, PTLS, JYXH)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table AGENT_DRLS is
'���ո�Ӧ�õ�����ˮ��';

comment on column AGENT_DRLS.PTRQ is
'ƽ̨���� YYYYMMDD';

comment on column AGENT_DRLS.PTSJ is
'ƽ̨ʱ�� HHMMSS';

comment on column AGENT_DRLS.PTLS is
'ƽ̨��ˮ��';

comment on column AGENT_DRLS.JYXH is
'�������к�';

comment on column AGENT_DRLS.YPTLSH is
'ԭƽ̨��ˮ��(����������ԭ������ƽ̨��ˮ��)';

comment on column AGENT_DRLS.JYJG is
'���׻���';

comment on column AGENT_DRLS.JYGY is
'���׹�Ա';

comment on column AGENT_DRLS.SQJG is
'��Ȩ����';

comment on column AGENT_DRLS.SQGY is
'��Ȩ��Ա';

comment on column AGENT_DRLS.QDBS is
'������ʶ ';

comment on column AGENT_DRLS.ZDSBBH is
'�ն��豸���';

comment on column AGENT_DRLS.CPDM is
'��Ʒ����';

comment on column AGENT_DRLS.YWBH is
'��Ʒ����';

comment on column AGENT_DRLS.YWRQ is
'ҵ������';

comment on column AGENT_DRLS.YWLSH is
'ҵ����ˮ��';

comment on column AGENT_DRLS.JYDM is
'���״���';

comment on column AGENT_DRLS.KHMC is
'�ͻ�����(���ڿͻ�����)';

comment on column AGENT_DRLS.KHBH is
'�ͻ����(���ڿͻ���)';

comment on column AGENT_DRLS.DQDM is
'��������(��������������)';

comment on column AGENT_DRLS.YHLX is
'�û�����  �û��ڵ��������û�����';

comment on column AGENT_DRLS.YHH1 is
'�û���� ���ֻ��� ˮ���';

comment on column AGENT_DRLS.YHBSH is
'�û���ʶ�� �� �û��ڵ������ĺ�ͬ��';

comment on column AGENT_DRLS.YHMC is
'�û�����';

comment on column AGENT_DRLS.JYBZ is
'���ױ��� �������ֵ�KEY=K_JYBZ';

comment on column AGENT_DRLS.XZBZ is
'��ת��־  0�ֽ� 1ת��';

comment on column AGENT_DRLS.JDBZ is
'�����־  �������ֵ�KEY=K_JDBZ';

comment on column AGENT_DRLS.ZHLX is
'�ʻ�����  �������ֵ�KEY=K_ZHLX';

comment on column AGENT_DRLS.YHZH is
'�����ʺ�';

comment on column AGENT_DRLS.JYJE is
'���׽��';

comment on column AGENT_DRLS.JYJE2 is
'���׽��2';

comment on column AGENT_DRLS.SXF is
'������';

comment on column AGENT_DRLS.ZNJ is
'���ɽ�';

comment on column AGENT_DRLS.PZZL is
'ƾ֤����';

comment on column AGENT_DRLS.PZHM is
'ƾ֤����';

comment on column AGENT_DRLS.JFBSH is
'�������ɷѱ�ʶ��';

comment on column AGENT_DRLS.CXLSH is
'��ѯ��ˮ��';

comment on column AGENT_DRLS.JYZY is
'����ժҪ';

comment on column AGENT_DRLS.FQFLSH is
'������ˮ��';

comment on column AGENT_DRLS.FQFRQ is
'��������';

comment on column AGENT_DRLS.FQFSJ is
'����ʱ��';

comment on column AGENT_DRLS.FQFJYDM is
'���𷽽��״���';

comment on column AGENT_DRLS.DSFLSH is
'��������ˮ��';

comment on column AGENT_DRLS.DSFRQ is
'����������';

comment on column AGENT_DRLS.DSFJYLX is
'��������������( �� ���� Ԥ�� �ɷ�)';

comment on column AGENT_DRLS.DSFJYDM is
'���������״���';

comment on column AGENT_DRLS.DSFXYM is
'��������Ӧ��';

comment on column AGENT_DRLS.DSFXYXX is
'��������Ӧ��Ϣ';

comment on column AGENT_DRLS.DSFJYZT is
'����������״̬ �������ֵ�KEY=K_JYZT';

comment on column AGENT_DRLS.ZJLSH is
'������ˮ��';

comment on column AGENT_DRLS.ZJRQ is
'��������';

comment on column AGENT_DRLS.ZJJYDM is
'�������״���';

comment on column AGENT_DRLS.ZJXYM is
'������Ӧ��';

comment on column AGENT_DRLS.ZJXYXX is
'������Ӧ��Ϣ';

comment on column AGENT_DRLS.ZJJYZT is
'��������״̬�������ֵ�KEY=K_JYZT';

comment on column AGENT_DRLS.JYXYM is
'������Ӧ��';

comment on column AGENT_DRLS.JYXYXX is
'������Ӧ��Ϣ';

comment on column AGENT_DRLS.JYZT is
'����״̬�������ֵ�KEY=K_JYZT';

comment on column AGENT_DRLS.DSFDZBZ is
'���ʱ�־  0 δ���� 1 ƽ 2 ƽ̨�� 3 ƽ̨��';

comment on column AGENT_DRLS.ZJDZBZ is
'���ʱ�־  0 δ���� 1 ƽ 2 ƽ̨�� 3 ƽ̨��';

comment on column AGENT_DRLS.EXTFLD1 is
'��չ1';

comment on column AGENT_DRLS.EXTFLD2 is
'��չ2';

comment on column AGENT_DRLS.EXTFLD3 is
'��չ3';

comment on column AGENT_DRLS.EXTFLD4 is
'��չ4';

comment on column AGENT_DRLS.EXTFLD5 is
'��չ5';

comment on column AGENT_DRLS.EXTFLD6 is
'��չ6';

--==============================================================
-- Index: K_AGT_DRLS_1
--==============================================================
create index K_AGT_DRLS_1 on AGENT_DRLS (
   PTRQ                 ASC,
   PTLS                 ASC
);

--==============================================================
-- Index: K_AGT_DRLS_2
--==============================================================
create index K_AGT_DRLS_2 on AGENT_DRLS (
   YWRQ                 ASC,
   YWLSH                ASC
);

--==============================================================
-- Index: K_AGT_DRLS_3
--==============================================================
create index K_AGT_DRLS_3 on AGENT_DRLS (
   PTRQ                 ASC,
   JYJG                 ASC,
   QDBS                 ASC
);

--==============================================================
-- Table: AGENT_DZBPB
--==============================================================
create table AGENT_DZBPB
(
   DZRQ                 VARCHAR(8)             not null,
   PTRQ                 VARCHAR(8),
   PTLS                 INTEGER,
   ZJRQ                 VARCHAR(8),
   ZJLS                 VARCHAR(32),
   JYJG                 VARCHAR(16)            not null,
   JYGY                 VARCHAR(16)            not null,
   JYBZ                 VARCHAR(3),
   YWBH                 VARCHAR(16)            not null,
   XZBZ                 VARCHAR(1),
   JDBZ                 VARCHAR(1),
   JYJE                 NUMERIC(16,2),
   PTJYJE               NUMERIC(16,2),
   JFZH                 VARCHAR(32),
   JFFZH                VARCHAR(10),
   DFZH                 VARCHAR(32),
   DFFZH                VARCHAR(10),
   YWLSH                VARCHAR(16),
   YWRQ                 VARCHAR(8),
   LSLX                 VARCHAR(1),
   DZBZ                 VARCHAR(1),
   TZLSH                VARCHAR(22),
   CLZT                 VARCHAR(1),
   EXTFLD1              VARCHAR(20),
   EXTFLD2              VARCHAR(20),
   EXTFLD3              VARCHAR(20)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table AGENT_DZBPB is
'���ʲ�ƽ��';

comment on column AGENT_DZBPB.PTLS is
'ƽ̨��ˮ��';

comment on column AGENT_DZBPB.ZJRQ is
'��������';

comment on column AGENT_DZBPB.ZJLS is
'������ˮ��';

comment on column AGENT_DZBPB.JYJG is
'���׻���';

comment on column AGENT_DZBPB.JYGY is
'���׹�Ա';

comment on column AGENT_DZBPB.JYBZ is
'���ױ��� �������ֵ� KEY = K_JYBZ';

comment on column AGENT_DZBPB.YWBH is
'ҵ����';

comment on column AGENT_DZBPB.XZBZ is
'��ת��־ 0�ֽ� 1ת��';

comment on column AGENT_DZBPB.JDBZ is
'�����־(D �� C��)';

comment on column AGENT_DZBPB.JYJE is
'���׽��';

comment on column AGENT_DZBPB.PTJYJE is
'ƽ̨���׽��';

comment on column AGENT_DZBPB.JFZH is
'�跽�ʺ�';

comment on column AGENT_DZBPB.JFFZH is
'�跽���ʺ�';

comment on column AGENT_DZBPB.DFZH is
'�����ʺ�';

comment on column AGENT_DZBPB.DFFZH is
'�������ʺ�';

comment on column AGENT_DZBPB.YWLSH is
'ҵ����ˮ��';

comment on column AGENT_DZBPB.YWRQ is
'ҵ������';

comment on column AGENT_DZBPB.LSLX is
'1 �������� 2 ����������';

comment on column AGENT_DZBPB.DZBZ is
'2 ƽ̨�� 3 ƽ̨��';

comment on column AGENT_DZBPB.TZLSH is
'������ˮ��';

comment on column AGENT_DZBPB.CLZT is
'����״̬��0 δ���� 1 �Ѵ��� 8 ������� 9 �����У�';

comment on column AGENT_DZBPB.EXTFLD1 is
'��չ�ֶ�1';

comment on column AGENT_DZBPB.EXTFLD2 is
'��չ�ֶ�2';

comment on column AGENT_DZBPB.EXTFLD3 is
'��չ�ֶ�3';

--==============================================================
-- Index: K_AGT_DZBPB_1
--==============================================================
create index K_AGT_DZBPB_1 on AGENT_DZBPB (
   PTRQ                 ASC,
   PTLS                 ASC
);

--==============================================================
-- Index: K_AGT_DZBPB_2
--==============================================================
create index K_AGT_DZBPB_2 on AGENT_DZBPB (
   ZJRQ                 ASC,
   ZJLS                 ASC
);

--==============================================================
-- Index: K_AGT_DZBPB_3
--==============================================================
create index K_AGT_DZBPB_3 on AGENT_DZBPB (
   YWLSH                ASC,
   YWRQ                 ASC
);

--==============================================================
-- Table: AGENT_DZLSB
--==============================================================
create table AGENT_DZLSB
(
   PTRQ                 VARCHAR(8),
   PTLS                 INTEGER,
   ZJRQ                 VARCHAR(8)             not null,
   ZJLS                 VARCHAR(32)            not null,
   JYJG                 VARCHAR(16)            not null,
   JYGY                 VARCHAR(16)            not null,
   JYBZ                 VARCHAR(3),
   YWBH                 VARCHAR(16)            not null,
   CPDM                 VARCHAR(8),
   XZBZ                 VARCHAR(1),
   JDBZ                 VARCHAR(1),
   JYJE                 NUMERIC(16,2),
   JFZH                 VARCHAR(32),
   JFFZH                VARCHAR(10),
   DFZH                 VARCHAR(32),
   DFFZH                VARCHAR(10),
   EXTFLD1              VARCHAR(20),
   EXTFLD2              VARCHAR(20),
   EXTFLD3              VARCHAR(20),
   JYZT                 VARCHAR(1),
   ZJDZBZ               VARCHAR(1),
   constraint "P_Key_1" primary key (ZJRQ, ZJLS)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table AGENT_DZLSB is
'������ˮ��';

comment on column AGENT_DZLSB.PTRQ is
'ƽ̨����';

comment on column AGENT_DZLSB.PTLS is
'ƽ̨��ˮ��';

comment on column AGENT_DZLSB.ZJRQ is
'��������';

comment on column AGENT_DZLSB.ZJLS is
'������ˮ��';

comment on column AGENT_DZLSB.JYJG is
'���׻���';

comment on column AGENT_DZLSB.JYGY is
'���׹�Ա';

comment on column AGENT_DZLSB.JYBZ is
'���ױ��� �������ֵ� KEY = K_JYBZ';

comment on column AGENT_DZLSB.YWBH is
'ҵ����';

comment on column AGENT_DZLSB.CPDM is
'��Ʒ����';

comment on column AGENT_DZLSB.XZBZ is
'��ת��־ 0�ֽ� 1ת��';

comment on column AGENT_DZLSB.JDBZ is
'�����־(D �� C��)';

comment on column AGENT_DZLSB.JYJE is
'���׽��';

comment on column AGENT_DZLSB.JFZH is
'�跽�ʺ�';

comment on column AGENT_DZLSB.JFFZH is
'�跽���ʺ�';

comment on column AGENT_DZLSB.DFZH is
'�����ʺ�';

comment on column AGENT_DZLSB.DFFZH is
'�������ʺ�';

comment on column AGENT_DZLSB.EXTFLD1 is
'��չ�ֶ�1';

comment on column AGENT_DZLSB.EXTFLD2 is
'��չ�ֶ�2';

comment on column AGENT_DZLSB.EXTFLD3 is
'��չ�ֶ�3';

comment on column AGENT_DZLSB.JYZT is
'����״̬ K_JYZT';

comment on column AGENT_DZLSB.ZJDZBZ is
'���ʱ�־  0 δ���� 1 ƽ 2 ƽ̨�� 3 ƽ̨��';

--==============================================================
-- Index: K_AGT_DZLSB_1
--==============================================================
create index K_AGT_DZLSB_1 on AGENT_DZLSB (
   PTRQ                 ASC,
   PTLS                 ASC
);

--==============================================================
-- Table: AGENT_HIS_DRLS
--==============================================================
create table AGENT_HIS_DRLS
(
   PTRQ                 VARCHAR(8)             not null,
   PTSJ                 VARCHAR(6),
   PTLS                 INTEGER                not null,
   JYXH                 INTEGER                not null default 1,
   YPTLSH               INTEGER,
   JYJG                 VARCHAR(16),
   JYGY                 VARCHAR(16),
   SQJG                 VARCHAR(16),
   SQGY                 VARCHAR(16),
   QDBS                 VARCHAR(3),
   ZDSBBH               VARCHAR(8),
   CPDM                 VARCHAR(16),
   YWBH                 VARCHAR(16),
   YWRQ                 VARCHAR(8),
   YWLSH                INTEGER,
   JYDM                 VARCHAR(8),
   KHMC                 VARCHAR(80),
   KHBH                 VARCHAR(32),
   DQDM                 VARCHAR(8),
   YHLX                 VARCHAR(16),
   YHH1                 VARCHAR(32),
   YHBSH                VARCHAR(32),
   YHMC                 VARCHAR(80),
   JYBZ                 VARCHAR(3),
   XZBZ                 VARCHAR(1),
   JDBZ                 VARCHAR(1),
   ZHLX                 VARCHAR(2),
   YHZH                 VARCHAR(32),
   JYJE                 NUMERIC(16,2),
   JYJE2                NUMERIC(16,2),
   SXF                  NUMERIC(16,2),
   ZNJ                  NUMERIC(16,2),
   PZZL                 VARCHAR(3),
   PZHM                 VARCHAR(32),
   JFBSH                VARCHAR(32),
   CXLSH                INTEGER,
   JYZY                 VARCHAR(40),
   FQFLSH               VARCHAR(22),
   FQFRQ                VARCHAR(8),
   FQFSJ                VARCHAR(6),
   FQFJYDM              VARCHAR(8),
   DSFLSH               VARCHAR(22),
   DSFRQ                VARCHAR(14),
   DSFJYLX              VARCHAR(8),
   DSFJYDM              VARCHAR(8),
   DSFXYM               VARCHAR(8),
   DSFXYXX              VARCHAR(60),
   DSFJYZT              VARCHAR(1),
   ZJLSH                VARCHAR(22),
   ZJRQ                 VARCHAR(14),
   ZJJYDM               VARCHAR(8),
   ZJXYM                VARCHAR(8),
   ZJXYXX               VARCHAR(60),
   ZJJYZT               VARCHAR(1),
   JYXYM                VARCHAR(8),
   JYXYXX               VARCHAR(60),
   JYZT                 VARCHAR(1),
   DSFDZBZ              VARCHAR(1),
   ZJDZBZ               VARCHAR(1),
   EXTFLD1              VARCHAR(40),
   EXTFLD2              VARCHAR(40),
   EXTFLD3              VARCHAR(40),
   EXTFLD4              VARCHAR(40),
   EXTFLD5              VARCHAR(40),
   EXTFLD6              VARCHAR(40),
   constraint P_PK_AGENT_DRLS primary key (PTRQ, PTLS, JYXH)
)IN GAPS_HIS_DATA INDEX IN GAPS_HIS_INDEX ;

comment on table AGENT_HIS_DRLS is
'���ո�Ӧ����ʷ��ˮ��';

comment on column AGENT_HIS_DRLS.PTRQ is
'ƽ̨���� YYYYMMDD';

comment on column AGENT_HIS_DRLS.PTSJ is
'ƽ̨ʱ�� HHMMSS';

comment on column AGENT_HIS_DRLS.PTLS is
'ƽ̨��ˮ��';

comment on column AGENT_HIS_DRLS.JYXH is
'�������к�';

comment on column AGENT_HIS_DRLS.YPTLSH is
'ԭƽ̨��ˮ��(����������ԭ������ƽ̨��ˮ��)';

comment on column AGENT_HIS_DRLS.JYJG is
'���׻���';

comment on column AGENT_HIS_DRLS.JYGY is
'���׹�Ա';

comment on column AGENT_HIS_DRLS.SQJG is
'��Ȩ����';

comment on column AGENT_HIS_DRLS.SQGY is
'��Ȩ��Ա';

comment on column AGENT_HIS_DRLS.QDBS is
'������ʶ ';

comment on column AGENT_HIS_DRLS.ZDSBBH is
'�ն��豸���';

comment on column AGENT_HIS_DRLS.CPDM is
'��Ʒ����';

comment on column AGENT_HIS_DRLS.YWBH is
'��Ʒ����';

comment on column AGENT_HIS_DRLS.YWRQ is
'ҵ������';

comment on column AGENT_HIS_DRLS.YWLSH is
'ҵ����ˮ��';

comment on column AGENT_HIS_DRLS.JYDM is
'���״���';

comment on column AGENT_HIS_DRLS.KHMC is
'�ͻ�����(���ڿͻ�����)';

comment on column AGENT_HIS_DRLS.KHBH is
'�ͻ����(���ڿͻ���)';

comment on column AGENT_HIS_DRLS.DQDM is
'��������(��������������)';

comment on column AGENT_HIS_DRLS.YHLX is
'�û�����  �û��ڵ��������û�����';

comment on column AGENT_HIS_DRLS.YHH1 is
'�û���� ���ֻ��� ˮ���';

comment on column AGENT_HIS_DRLS.YHBSH is
'�û���ʶ�� �� �û��ڵ������ĺ�ͬ��';

comment on column AGENT_HIS_DRLS.YHMC is
'�û�����';

comment on column AGENT_HIS_DRLS.JYBZ is
'���ױ��� �������ֵ�KEY=K_JYBZ';

comment on column AGENT_HIS_DRLS.XZBZ is
'��ת��־  0�ֽ� 1ת��';

comment on column AGENT_HIS_DRLS.JDBZ is
'�����־  �������ֵ�KEY=K_JDBZ';

comment on column AGENT_HIS_DRLS.ZHLX is
'�ʻ�����  �������ֵ�KEY=K_ZHLX';

comment on column AGENT_HIS_DRLS.YHZH is
'�����ʺ�';

comment on column AGENT_HIS_DRLS.JYJE is
'���׽��';

comment on column AGENT_HIS_DRLS.JYJE2 is
'���׽��2';

comment on column AGENT_HIS_DRLS.SXF is
'������';

comment on column AGENT_HIS_DRLS.ZNJ is
'���ɽ�';

comment on column AGENT_HIS_DRLS.PZZL is
'ƾ֤����';

comment on column AGENT_HIS_DRLS.PZHM is
'ƾ֤����';

comment on column AGENT_HIS_DRLS.JFBSH is
'�������ɷѱ�ʶ��';

comment on column AGENT_HIS_DRLS.CXLSH is
'��ѯ��ˮ��';

comment on column AGENT_HIS_DRLS.JYZY is
'����ժҪ';

comment on column AGENT_HIS_DRLS.FQFLSH is
'������ˮ��';

comment on column AGENT_HIS_DRLS.FQFRQ is
'��������';

comment on column AGENT_HIS_DRLS.FQFSJ is
'����ʱ��';

comment on column AGENT_HIS_DRLS.FQFJYDM is
'���𷽽��״���';

comment on column AGENT_HIS_DRLS.DSFLSH is
'��������ˮ��';

comment on column AGENT_HIS_DRLS.DSFRQ is
'����������';

comment on column AGENT_HIS_DRLS.DSFJYLX is
'��������������( �� ���� Ԥ�� �ɷ�)';

comment on column AGENT_HIS_DRLS.DSFJYDM is
'���������״���';

comment on column AGENT_HIS_DRLS.DSFXYM is
'��������Ӧ��';

comment on column AGENT_HIS_DRLS.DSFXYXX is
'��������Ӧ��Ϣ';

comment on column AGENT_HIS_DRLS.DSFJYZT is
'����������״̬ �������ֵ�KEY=K_JYZT';

comment on column AGENT_HIS_DRLS.ZJLSH is
'������ˮ��';

comment on column AGENT_HIS_DRLS.ZJRQ is
'��������';

comment on column AGENT_HIS_DRLS.ZJJYDM is
'�������״���';

comment on column AGENT_HIS_DRLS.ZJXYM is
'������Ӧ��';

comment on column AGENT_HIS_DRLS.ZJXYXX is
'������Ӧ��Ϣ';

comment on column AGENT_HIS_DRLS.ZJJYZT is
'��������״̬�������ֵ�KEY=K_JYZT';

comment on column AGENT_HIS_DRLS.JYXYM is
'������Ӧ��';

comment on column AGENT_HIS_DRLS.JYXYXX is
'������Ӧ��Ϣ';

comment on column AGENT_HIS_DRLS.JYZT is
'����״̬�������ֵ�KEY=K_JYZT';

comment on column AGENT_HIS_DRLS.DSFDZBZ is
'���ʱ�־  0 δ���� 1 ƽ 2 ƽ̨�� 3 ƽ̨��';

comment on column AGENT_HIS_DRLS.ZJDZBZ is
'���ʱ�־  0 δ���� 1 ƽ 2 ƽ̨�� 3 ƽ̨��';

comment on column AGENT_HIS_DRLS.EXTFLD1 is
'��չ1';

comment on column AGENT_HIS_DRLS.EXTFLD2 is
'��չ2';

comment on column AGENT_HIS_DRLS.EXTFLD3 is
'��չ3';

comment on column AGENT_HIS_DRLS.EXTFLD4 is
'��չ4';

comment on column AGENT_HIS_DRLS.EXTFLD5 is
'��չ5';

comment on column AGENT_HIS_DRLS.EXTFLD6 is
'��չ6';

--==============================================================
-- Index: K_AGT_DRLS_4
--==============================================================
create index K_AGT_DRLS_4 on AGENT_HIS_DRLS (
   PTRQ                 ASC,
   PTLS                 ASC
);

--==============================================================
-- Index: K_AGT_DRLS_5
--==============================================================
create index K_AGT_DRLS_5 on AGENT_HIS_DRLS (
   YWRQ                 ASC,
   YWLSH                ASC
);

--==============================================================
-- Index: K_AGT_DRLS_6
--==============================================================
create index K_AGT_DRLS_6 on AGENT_HIS_DRLS (
   PTRQ                 ASC,
   JYJG                 ASC,
   QDBS                 ASC
);

--==============================================================
-- Table: AGENT_RZZT
--==============================================================
create table AGENT_RZZT
(
   YWBH                 VARCHAR(16)            not null,
   PTRQ                 VARCHAR(8)             not null,
   YWRQ                 VARCHAR(8)             not null,
   ZJMXDZZT             VARCHAR(1),
   ZJZZDZZT             VARCHAR(1),
   DSFMXDZZT            VARCHAR(1),
   DSFZZDZZT            VARCHAR(1),
   ZJZJE                NUMERIC(16,2),
   ZJZBS                INTEGER,
   DSFZJE               NUMERIC(16,2),
   DSFZBS               INTEGER,
   GDZT                 VARCHAR(1),
   QLZT                 VARCHAR(1),
   EXTFLD1              VARCHAR(20),
   EXTFLD2              VARCHAR(20),
   constraint "P_Key_1" primary key (YWBH, PTRQ, YWRQ)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on column AGENT_RZZT.ZJMXDZZT is
'0 δ���� 1 ����ƽ 2 ���˲�ƽ 9 ������';

comment on column AGENT_RZZT.ZJZZDZZT is
'0 δ���� 1 ����ƽ 2 ���˲�ƽ 9 ������';

comment on column AGENT_RZZT.DSFMXDZZT is
'0 δ���� 1 ����ƽ 2 ���˲�ƽ 9 ������';

comment on column AGENT_RZZT.DSFZZDZZT is
'0 δ���� 1 ����ƽ 2 ���˲�ƽ 9 ������';

comment on column AGENT_RZZT.EXTFLD1 is
'��չ�ֶ�1';

comment on column AGENT_RZZT.EXTFLD2 is
'��չ�ֶ�2';

--==============================================================
-- Table: AGENT_TJ
--==============================================================
create table AGENT_TJ
(
   PTRQ                 VARCHAR(8)             not null,
   JYJG                 VARCHAR(16)            not null,
   JYGY                 VARCHAR(16)            not null,
   QDBS                 VARCHAR(3)             not null,
   YWBH                 VARCHAR(16)            not null,
   JDBZ                 VARCHAR(1),
   JYJE                 NUMERIC(16,2),
   SXF                  NUMERIC(16,2),
   EXTFLD1              VARCHAR(40),
   EXTFLD2              VARCHAR(40),
   EXTFLD3              VARCHAR(40),
   constraint "P_Key_1" primary key (PTRQ, JYJG, JYGY, QDBS, YWBH)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table AGENT_TJ is
'���ո�Ӧ��ͳ�Ʊ�';

comment on column AGENT_TJ.PTRQ is
'ƽ̨���� YYYYMMDD';

comment on column AGENT_TJ.JYJG is
'���׻���';

comment on column AGENT_TJ.JYGY is
'���׹�Ա';

comment on column AGENT_TJ.QDBS is
'������ʶ ';

comment on column AGENT_TJ.YWBH is
'ҵ����ˮ��';

comment on column AGENT_TJ.JDBZ is
'�����־  �������ֵ�KEY=K_JDBZ';

comment on column AGENT_TJ.JYJE is
'���׽��';

comment on column AGENT_TJ.SXF is
'������';

comment on column AGENT_TJ.EXTFLD1 is
'��չ1';

comment on column AGENT_TJ.EXTFLD2 is
'��չ2';

comment on column AGENT_TJ.EXTFLD3 is
'��չ3';


delete from app_yyxx where yybs='003';
insert into app_yyxx (YYBS, YYMC, YYSM, YYKFKSRQ, YYKFJSRQ, YYFBRQ, YYBBH, YHH, SQH, YYKFJL, YYZBJL, YYZT, EXTFLD)
values ('003', 'agent', 'AGENT���ո�Ӧ��', '20110801', '', '', '2.1.0.0', '', '', 'yd', 'yd', '0', '');


delete from app_jyxx where yybs='003';
insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2,WHJG, WHGY,QTBZ)
values ('920002', '���ո������ж�����', '003', '0', '1', '1', '1', '0', '', '', '00000','admin',  '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920003', '���ո������ж���ϸ', '003', '0', '1', '1', '1', '0', '', '', '00000','admin',  '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920005', '���ո����̻�������','003', '0', '1', '1', '1', '0', '', '', '00000','admin',  '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920006', '���ո����̻�����ϸ',  '003', '0', '1', '1', '1', '0', '', '','00000','admin', '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920008', 'ί�й�ϵ�˶�',  '003', '0', '1', '1', '1', '0', '', '','00000','admin', '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920313', '���˲�ƽ��������',  '003', '0', '1', '1', '1', '1', '', '','00000','admin', '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920314', '���˲�ƽ����������',  '003', '0', '1', '1', '1', '1', '', '','00000','admin', '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920315', '���˲�ƽ��ˮ״̬����',  '003', '0', '1', '1', '1', '1', '', '','00000','admin', '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920011', '���ݹ鵵',  '003', '0', '1', '1', '1', '1', '', '', '00000','admin',  '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920012', '��������', '003', '0', '1', '1', '1', '1', '', '','00000','admin', '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920013', '���ݱ���',  '003', '0', '1', '1', '1', '1', '', '', '00000','admin',  '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920015', '��Ʒ����', '003', '0', '1', '1', '1', '0', '', '','00000','admin', '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920016', 'ҵ�񱨱�',  '003', '0', '1', '1', '1', '1', '', '', '00000','admin',  '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920101', '��ˮ�б��ѯ', '003', '0', '1', '1', '1', '1', '', '', '00000','admin',  '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920102', '��ˮ�б��ѯ',  '003', '0', '1', '1', '1', '1', '', '', '00000','admin',  '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920103', '����ҵ��������ˮ��ѯ',  '003', '0', '1', '1', '1', '0', '', '', '00000','admin',  '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920104', '�̻�ǩ��',  '003', '0', '1', '1', '1', '0', '', '', '00000','admin',  '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2,WHJG, WHGY,QTBZ)
values ('920105', 'ҵ������',  '003', '0', '1', '1', '1', '1', '', '', '00000','admin',  '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920106', '�ͻ�(�˻�)��Ϣ��ѯ', '003', '0', '1', '1', '1', '1', '', '', '00000','admin',  '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920107', '�ͻ���Ϣ��ѯ',  '003', '0', '1', '1', '1', '0', '', '', '00000','admin',  '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920108', 'Ƿ�Ѳ�ѯ',  '003', '0', '0', '1', '1', '0', '', '', '00000','admin',  '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920109', '�������ɷѲ�ѯ',  '003', '0', '0', '1', '1', '0', '', '', '00000','admin',  '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920201', '�ͻ�ǩԼ',  '003', '0', '1', '1', '1', '0', '', '', '00000','admin',  '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920202', '�ͻ���Լ', '003', '0', '1', '1', '1', '0', '', '', '00000','admin',  '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2,WHJG, WHGY,QTBZ)
values ('920203', 'ǩԼ�޸�',  '003', '0', '1', '1', '1', '1', '', '', '00000','admin',  '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920204', 'ǩԼ��ѯ',  '003', '0', '1', '1', '1', '1', '', '', '00000','admin',  '0');

insert into app_jyxx (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ)
values ('920205', '���߽�Լ', '003', '0', '1', '1', '1', '1', '00000', 'admin', '20111222103301', '', '', '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920301', '���д���(��ѯģʽ)', '003', '0', '1', '0', '0', '0', '', '', '00000','admin',  '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920302', '���д���(ֱ�ӽɷ�)',  '003', '0', '0', '0', '0', '0', '', '','00000','admin', '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920303', '���д���(��ѯģʽ)',  '003', '0', '1', '0', '0', '0', '', '','00000','admin', '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920304', '���д���(ֱ�ӽɷ�)',  '003', '0', '0', '0', '0', '0', '', '','00000','admin', '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2,WHJG, WHGY,QTBZ)
values ('920311', '����', '003', '1', '1', '0', '1', '0', '', '', '00000','admin',  '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920312', '����', '003', '1', '1', '0', '1', '0', '', '','00000','admin', '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920401', '��Ʊ��ӡ',  '003', '0', '1', '1', '1', '0', '', '','00000','admin', '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920402', '��Ʊ������ӡ', '003', '0', '1', '1', '1', '0', '', '','00000','admin', '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920403', '��Ʊ��ѯ', '003', '0', '1', '1', '1', '1', '', '','00000','admin', '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2, WHJG, WHGY,QTBZ)
values ('920501', 'ͨ�ô�͸����', '003', '0', '1', '1', '1', '1', '', '','00000','admin', '0');

insert into app_jyxx (JYDM, JYMC,  YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, EXTFLD1, EXTFLD2,WHJG, WHGY,QTBZ)
values ('920007', 'ȡ���������˽��', '003', '0', '1', '1', '1', '0', '', '','00000','admin', '0');

delete from app_cskz where csjz='K_AGENT_DRLSQL';
insert into app_cskz (CSJZ, CSLX, CSTJ, JDM, JDZ, REMARK, JZLX, WHJG, WHGY )
values ('K_AGENT_DRLSQL', '0', '', '/app/cskz', '7', '���ո���ˮ��ǰ��������', '1' , '00000','admin');

delete from app_cskz where csjz='K_AGENT_DRLSGD';
insert into app_cskz (CSJZ, CSLX, CSTJ, JDM, JDZ, REMARK, JZLX, WHJG, WHGY )
values ('K_AGENT_DRLSGD', '0', '', '/app/cskz', '2', '���ո���ˮ�鵵����', '1', '00000','admin');

delete from app_rzpz where ssyy='003';
insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG, WHGY )
values ('003', '1', '1', 'agent_drls', 'agent_his_drls', 'C;ptrq;=;K_AGENT_DRLSGD;;|', '���ո�ҵ����ˮ�鵵 ', ' ', '00000','admin');

insert into app_rzpz (SSYY, CZLX, DXLX, CZDX1, CZDX2, CZTJ, EXTFLD1, EXTFLD2, WHJG, WHGY)
values ('003', '2', '1', 'agent_drls', '', 'C;ptrq;=;K_AGENT_DRLSQL;;|', '���ո�ҵ����ˮ����', ' ',  '00000','admin');
