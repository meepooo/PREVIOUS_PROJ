drop table tbl_jzzf_gwkhkhz;
create table tbl_jzzf_gwkhkhz
(
        czbm varchar(12) not null,
        trandate varchar(10),
        finano varchar(25),
        bankid varchar(20),
        bgdeptcode varchar(12),
        totalserialnum varchar(20)not null,
        billno varchar(20)not null,
        totalamt decimal(20,2),
        count INTEGER,
        state varchar(1),
        sendflag varchar(1),
constraint P_YWTY_ZFWG_DZ primary key (CZBM,TOTALSERIALNUM)
)--IN GAPS_DATA INDEX IN GAPS_INDEX
 ;

create index index_tbl_jzzf_gwkhkhz_1 on tbl_jzzf_gwkhkhz( CZBM,BILLNO );
comment on table  tbl_jzzf_gwkhkhz  is '���⼯��֧��������ܱ�' ;
comment on column tbl_jzzf_gwkhkhz.CZBM is '�����ִ���' ;
comment on column tbl_jzzf_gwkhkhz.TRANDATE is '��������' ;
comment on column tbl_jzzf_gwkhkhz.FINANO is '������ˮ��' ;
comment on column tbl_jzzf_gwkhkhz.BANKID is '���б�ʶ��' ;
comment on column tbl_jzzf_gwkhkhz.BGDEPTCODE is 'Ԥ�㵥λ����' ;
comment on column tbl_jzzf_gwkhkhz.TOTALSERIALNUM is '���ܱ��' ;
comment on column tbl_jzzf_gwkhkhz.BILLNO is '��Ȩ֧��ƾ֤��' ;
comment on column tbl_jzzf_gwkhkhz.TOTALAMT is '��Ȩ֧�����ܽ��' ;
comment on column tbl_jzzf_gwkhkhz.COUNT is '���׼�¼����' ;
comment on column tbl_jzzf_gwkhkhz.STATE is '
0:��ʼ
1:�ѻ���
2:���˻�
3:����ʧ��
4:�˻�ʧ��
5:���ĺ󻹿�' ;
comment on column tbl_jzzf_gwkhkhz.SENDFLAG is '������ʶ 0��δ���� 1���ѷ���' ;
