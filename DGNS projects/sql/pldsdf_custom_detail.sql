drop table pldsdf_custom_detail;
--==============================================================
-- Table: pldsdf_custom_detail
--==============================================================
create table pldsdf_custom_detail		--�������Ļ�������
(
 	pch				varchar(32) not null,
    wjxh            integer     not null,
    wjmc            varchar(150) not null,
    hth             varchar(20) not null,
    tyxybh          varchar(65),
    xybh            varchar(65),
    xydm            varchar(12),
    yhzh            varchar(32) not null,
    yhzhmc          varchar(150),
    zjhm            varchar(40),
    xyjlzt          char(1),
    lxdh            varchar(15),
    lxdz            varchar(150),
    qysxrq          char(8),
    qydqrq          char(8),
    qyrq            char(8),
    jyrq            char(8),
    qygy            varchar(16),
    jygy            varchar(16),
    qyjg            varchar(16),
    fhxxm           char(7),
    cwzwms          varchar(512),
    extfld1         varchar(80),
    extfld2         varchar(80),
    extfld3         varchar(80),
    extfld4         varchar(80),
    extfld5         varchar(80),
    extfld6         varchar(160),
    constraint PK_pldsdf_custom_detail primary key (pch,wjxh)
)IN AGENT_DATA INDEX IN AGENT_INDEX ;

comment on table pldsdf_custom_detail is
'�����ͻ�ǩԼ��ϸ��';

comment on column pldsdf_custom_detail.wjxh is '�ļ����';

comment on column pldsdf_custom_detail.hth is '��ͬ��';

comment on column pldsdf_custom_detail.tyxybh is 'ͳһЭ����';

comment on column pldsdf_custom_detail.xybh is 'Э����';

comment on column pldsdf_custom_detail.xydm is 'Э�����';

comment on column pldsdf_custom_detail.yhzh is '�����˺�';

comment on column pldsdf_custom_detail.yhzhmc is '�����˺�����';

comment on column pldsdf_custom_detail.zjhm is '֤������';

comment on column pldsdf_custom_detail.xyjlzt is 'Э���¼״̬ 0-���� 1-ɾ��';

comment on column pldsdf_custom_detail.lxdh is '��ϵ�绰';

comment on column pldsdf_custom_detail.lxdz is '��ϵ��ַ';

comment on column pldsdf_custom_detail.qysxrq is 'ǩԼ��Ч����';

comment on column pldsdf_custom_detail.qydqrq is 'ǩԼ��������';

comment on column pldsdf_custom_detail.qyrq is 'ǩԼ����';

comment on column pldsdf_custom_detail.jyrq is '��Լ����';

comment on column pldsdf_custom_detail.qygy is 'ǩԼ��Ա';

comment on column pldsdf_custom_detail.jygy is '��Լ��Ա';

comment on column pldsdf_custom_detail.qyjg is 'ǩԼ����';

comment on column pldsdf_custom_detail.fhxxm is '������Ϣ��';

comment on column pldsdf_custom_detail.cwzwms is '������������';

comment on column pldsdf_custom_detail.EXTFLD1 is '��չ�ֶ�1';

comment on column pldsdf_custom_detail.EXTFLD2 is '��չ�ֶ�2';

comment on column pldsdf_custom_detail.EXTFLD3 is '��չ�ֶ�3';

comment on column pldsdf_custom_detail.EXTFLD4 is '��չ�ֶ�4';

comment on column pldsdf_custom_detail.EXTFLD5 is '��չ�ֶ�5';

comment on column pldsdf_custom_detail.EXTFLD6 is '��չ�ֶ�6';

