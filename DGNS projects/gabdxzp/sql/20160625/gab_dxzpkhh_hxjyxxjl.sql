drop table gab_dxzpkhh_hxjyxxjl;
create table gab_dxzpkhh_hxjyxxjl  (
   khhywsqbh          varchar(40)                     not null,
   ywsqbh             varchar(40)                     not null,
   jybm               char(6)                         not null,
   jylx               char(1)                         not null,
   fsjgbh             varchar(12),
   tjhxwjm            varchar(200),
   hxfhjgwjm1         varchar(200),
   oldhxfhjgwjm1         varchar(200),
   hxfhjgwjm2         varchar(200),
   oldhxfhjgwjm2         varchar(200),
   hxfhjgwjm3         varchar(200),
   oldhxfhjgwjm3         varchar(200),
   by1                varchar(30),
   by2                varchar(254),
   by3                varchar(254),
   constraint pkgab_dxzpkhh_hxjyxxjl primary key (khhywsqbh, jybm,jylx)
);
/*==============================================================*/
/* Table: gab_dxzpkhh_hxjyxxjl                                  */
/*==============================================================*/
comment on table gab_dxzpkhh_hxjyxxjl is
'��¼����թƭ���Ľ�����Ϣ';

comment on column gab_dxzpkhh_hxjyxxjl.ywsqbh is
'������������ˮ�ţ����ڱ�ʶ�������';

comment on column gab_dxzpkhh_hxjyxxjl.jybm is
'���ױ���';

comment on column gab_dxzpkhh_hxjyxxjl.jylx is
'�������� 0-��ͨ����,1-��̬��ѯ��N�ν���,N����1';

comment on column gab_dxzpkhh_hxjyxxjl.fsjgbh is
'���ͻ������';

comment on column gab_dxzpkhh_hxjyxxjl.tjhxwjm is
'�ύ�����ļ���';

comment on column gab_dxzpkhh_hxjyxxjl.hxfhjgwjm1 is
'���ķ��ؽ���ļ���1';

comment on column gab_dxzpkhh_hxjyxxjl.oldhxfhjgwjm1 is
'�Ϻ��ķ��ؽ���ļ���1';

comment on column gab_dxzpkhh_hxjyxxjl.hxfhjgwjm2 is
'���ķ��ؽ���ļ���2';

comment on column gab_dxzpkhh_hxjyxxjl.oldhxfhjgwjm2 is
'�Ϻ��ķ��ؽ���ļ���2';

comment on column gab_dxzpkhh_hxjyxxjl.hxfhjgwjm3 is
'���ķ��ؽ���ļ���3';

comment on column gab_dxzpkhh_hxjyxxjl.oldhxfhjgwjm3 is
'�Ϻ��ķ��ؽ���ļ���3';

comment on column gab_dxzpkhh_hxjyxxjl.by1 is
'����1';

comment on column gab_dxzpkhh_hxjyxxjl.by2 is
'����2';

comment on column gab_dxzpkhh_hxjyxxjl.by3 is
'����3';
