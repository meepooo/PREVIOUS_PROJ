drop table zmxy_qzpfxx;
drop table zmxy_qzpfxx_verify_code;
drop table zmxy_qzpfxx_risk_code;
drop table zmxy_zmpfxx;
drop table zmxy_hygzmdxx;
drop table zmxy_hygzmdxx_details;
drop table zmxy_hygzmdxx_details_extend_info;
drop table zmxy_xtcsb;
drop table zmxy_sjfkhz;
drop table zmxy_sjfkmx;

--==============================================================
-- Table:  zmxy_qzpfxx 
--==============================================================
create table  zmxy_qzpfxx 
(
    transaction_id           VARCHAR(32)               not null,
    product_code             VARCHAR(32),
    cert_type                VARCHAR(32),
    cert_no                  VARCHAR(20),
    name                     VARCHAR(64),
    mobile                   VARCHAR(15),
    email                    VARCHAR(32),
    bank_card                VARCHAR(20),
    address                  VARCHAR(256),
    ip                       VARCHAR(40),
    mac                      VARCHAR(20),
    wifimac                  VARCHAR(20),
    imei                     VARCHAR(16),
    biz_no                   VARCHAR(40),
    score                    CHAR(3),
    hit_risk                 CHAR(5),
    whrq                     CHAR(8),
    cgbz                     CHAR(1),
   constraint  pk_zmxy_qzpfxx  primary key ( transaction_id )
)IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table zmxy_qzpfxx is
'��թ������Ϣ��';

comment on column zmxy_qzpfxx.transaction_id is
'ҵ��ƾ֤��ˮ��';

comment on column zmxy_qzpfxx.product_code is
'��Ʒ����';

comment on column zmxy_qzpfxx.cert_type is
'֤������';

comment on column zmxy_qzpfxx.cert_no is
'֤������';

comment on column zmxy_qzpfxx.name is
'����';

comment on column zmxy_qzpfxx.mobile is
'�ֻ�����';

comment on column zmxy_qzpfxx.email is
'����';

comment on column zmxy_qzpfxx.bank_card is
'���п�����';

comment on column zmxy_qzpfxx.address is
'��ַ��Ϣ';

comment on column zmxy_qzpfxx.ip is
'IP��ַ';

comment on column zmxy_qzpfxx.mac is
'MAC��ַ';

comment on column zmxy_qzpfxx.wifimac is
'WIFIMAC��ַ';

comment on column zmxy_qzpfxx.imei is
'�����ƶ��豸��־';

comment on column zmxy_qzpfxx.biz_no is
'ҵ���';

comment on column zmxy_qzpfxx.score is
'����';

comment on column zmxy_qzpfxx.hit_risk is
'���б�־';

comment on column zmxy_qzpfxx.whrq is
'����ά������';

comment on column zmxy_qzpfxx.cgbz is
'�ɹ���־��Y-�ɹ���N-ʧ��';


--==============================================================
-- Table:  zmxy_qzpfxx_verify_code 
--==============================================================
create table  zmxy_qzpfxx_verify_code 
(
    transaction_id           VARCHAR(32)               not null,
    verify_code             VARCHAR(20)                not null,
   constraint  pk_zmxy_qzpfxx_verify_code  primary key ( transaction_id, verify_code )
)IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table zmxy_qzpfxx_verify_code is
'��թ������Ϣƥ����Ϣ��';

comment on column zmxy_qzpfxx_verify_code.transaction_id is
'ҵ��ƾ֤��ˮ��';

comment on column zmxy_qzpfxx_verify_code.verify_code is
'ƥ����Ϣ��֤��';


--==============================================================
-- Table:  zmxy_qzpfxx_risk_code 
--==============================================================
create table  zmxy_qzpfxx_risk_code 
(
    transaction_id           VARCHAR(32)               not null,
    risk_code                VARCHAR(20)               not null,
   constraint  pk_zmxy_qzpfxx_risk_code  primary key ( transaction_id, risk_code )
)IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table zmxy_qzpfxx_risk_code is
'��թ������Ϣ������Ϣ��';

comment on column zmxy_qzpfxx_risk_code.transaction_id is
'ҵ��ƾ֤��ˮ��';

comment on column zmxy_qzpfxx_risk_code.risk_code is
'������Ϣ��֤��';


--==============================================================
-- Table:  zmxy_zmpfxx 
--==============================================================
create table  zmxy_zmpfxx 
(
    transaction_id           VARCHAR(32)               not null,
    product_code             VARCHAR(32)               not null,
    open_id                  VARCHAR(32)               not null,
    biz_no                   VARCHAR(40),               
    zm_score                 CHAR(3),
    whrq                     CHAR(8),
    cgbz                     CHAR(1),
   constraint  pk_zmxy_zmpfxx  primary key ( transaction_id )
)IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table zmxy_zmpfxx is
'֥������������Ϣ��';

comment on column zmxy_zmpfxx.transaction_id is
'ҵ��ƾ֤��ˮ��';

comment on column zmxy_zmpfxx.product_code is
'��Ʒ����';

comment on column zmxy_zmpfxx.open_id is
'֥���Ա��ݱ�ʶ';

comment on column zmxy_zmpfxx.biz_no is
'ҵ���';

comment on column zmxy_zmpfxx.zm_score is
'����';

comment on column zmxy_zmpfxx.whrq is
'����ά������';

comment on column zmxy_zmpfxx.cgbz is
'�ɹ���־��Y-�ɹ���N-ʧ��';


--==============================================================
-- Table:  zmxy_hygzmdxx 
--==============================================================
create table  zmxy_hygzmdxx 
(
    transaction_id           VARCHAR(32)               not null,
    product_code             VARCHAR(32)               not null,
    open_id                  VARCHAR(32)               not null,
    biz_no                   VARCHAR(40),
    is_matched               CHAR(5),
    whrq                     CHAR(8),
    cgbz                     CHAR(1),
   constraint  pk_zmxy_hygzmdxx  primary key ( transaction_id )
)IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table zmxy_hygzmdxx is
'��ҵ��ע������Ϣ��';

comment on column zmxy_hygzmdxx.transaction_id is
'ҵ��ƾ֤��ˮ��';

comment on column zmxy_hygzmdxx.product_code is
'��Ʒ����';

comment on column zmxy_hygzmdxx.open_id is
'֥���Ա��ݱ�ʶ';

comment on column zmxy_hygzmdxx.biz_no is
'ҵ���';

comment on column zmxy_hygzmdxx.is_matched is
'���б�־';

comment on column zmxy_hygzmdxx.whrq is
'����ά������';

comment on column zmxy_hygzmdxx.cgbz is
'�ɹ���־��Y-�ɹ���N-ʧ��';

--==============================================================
-- Table:  zmxy_hygzmdxx_details 
--==============================================================
create table  zmxy_hygzmdxx_details 
(
    transaction_id       VARCHAR(32)               not null,
    biz_code             VARCHAR(16),
    level                VARCHAR(16),
    type                 VARCHAR(16),
    code                 VARCHAR(16)               not null,
    refresh_time         VARCHAR(20),
    settlement           CHAR(5),
    status               VARCHAR(16),
    statement            VARCHAR(256),
   constraint  pk_zmxy_hygzmdxx_details  primary key ( transaction_id,code )
)IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table zmxy_hygzmdxx_details is
'��ҵ��ע������Ϣϸ���б�';

comment on column zmxy_hygzmdxx_details.transaction_id is
'ҵ��ƾ֤��ˮ��';

comment on column zmxy_hygzmdxx_details.biz_code is
'������Ϣ��ҵ����';

comment on column zmxy_hygzmdxx_details.level is
'���յȼ�';

comment on column zmxy_hygzmdxx_details.type is
'��ҵ������������';

comment on column zmxy_hygzmdxx_details.code is
'���ձ���';

comment on column zmxy_hygzmdxx_details.refresh_time is
'����ˢ��ʱ��';

comment on column zmxy_hygzmdxx_details.settlement is
'����״̬';

comment on column zmxy_hygzmdxx_details.status is
'���鴦������״̬';

comment on column zmxy_hygzmdxx_details.statement is
'��������';



--==============================================================
-- Table:  zmxy_hygzmdxx_details_extend_info 
--==============================================================
create table  zmxy_hygzmdxx_details_extend_info 
(
    transaction_id       VARCHAR(32)               not null,
    code                 VARCHAR(16)               not null,
    key                  VARCHAR(32)               not null,
    value                VARCHAR(256),
    description          VARCHAR(256),
   constraint  pk_zmxy_hygzmdxx_details_extend_info  primary key ( transaction_id,code,key )
)IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table zmxy_hygzmdxx_details_extend_info is
'��ҵ��ע������Ϣϸ����չ��Ϣ�б�';

comment on column zmxy_hygzmdxx_details_extend_info.transaction_id is
'ҵ��ƾ֤��ˮ��';

comment on column zmxy_hygzmdxx_details_extend_info.code is
'���ձ���';

comment on column zmxy_hygzmdxx_details_extend_info.key is
'������Ϣ�ֶε�Ӣ�ı���';

comment on column zmxy_hygzmdxx_details_extend_info.value is
'������Ϣ�ֶε���Ϣ����';

comment on column zmxy_hygzmdxx_details_extend_info.description is
'������Ϣ�ֶε���������';


--==============================================================
-- Table:  zmxy_xtcsb 
--==============================================================
create table  zmxy_xtcsb 
(
    app_id       VARCHAR(32)               not null,
    charset      VARCHAR(16),
    version      VARCHAR(8),               
    platform     VARCHAR(32),
    type_id      VARCHAR(32),
    columns      VARCHAR(200),
    primary_key_columns  VARCHAR(200),
    update_day   CHAR(2),
    by1          VARCHAR(32),
   constraint  pk_zmxy_xtcsb  primary key ( app_id )
)IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table zmxy_xtcsb is
'֥������ϵͳ������';

comment on column zmxy_xtcsb.app_id is
'�̻�ID';

comment on column zmxy_xtcsb.charset is
'�����ַ���';

comment on column zmxy_xtcsb.version is
'�ӿڰ汾';

comment on column zmxy_xtcsb.platform is
'��Դƽ̨';

comment on column zmxy_xtcsb.type_id is
'���ݷ�����typeid';

comment on column zmxy_xtcsb.columns is
'���ݷ����ĵ������ݵ�������,��Ӣ�Ķ��ŷָ�';

comment on column zmxy_xtcsb.primary_key_columns is
'���ݷ�������ϸ��������,��Ӣ�Ķ��ŷָ�';

comment on column zmxy_xtcsb.update_day is
'֥��ָ����գ�06-ÿ��6�Ÿ���';

comment on column zmxy_xtcsb.by1 is
'�����ֶ�1';


--==============================================================
-- Table:  zmxy_sjfkhz 
--==============================================================
create table  zmxy_sjfkhz 
(
    zwrq       VARCHAR(8)               not null,
    zhqzlsh    VARCHAR(8)               not null,
    records      VARCHAR(10),
    file_description      VARCHAR(256),               
   constraint  pk_zmxy_sjfkhz  primary key ( zwrq,zhqzlsh )
)IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table zmxy_sjfkhz is
'֥���������ݷ������ܱ�';

comment on column zmxy_sjfkhz.zwrq is
'��������';

comment on column zmxy_sjfkhz.zhqzlsh is
'�ۺ�ǰ����ˮ��';

comment on column zmxy_sjfkhz.records is
'�ļ���ϸ��¼��';

comment on column zmxy_sjfkhz.file_description is
'�ļ�����';


--==============================================================
-- Table:  zmxy_sjfkmx 
--==============================================================
create table  zmxy_sjfkmx 
(
    zwrq                       VARCHAR(8)               not null,
    zhqzlsh                    VARCHAR(8)               not null,
    credentials_type           VARCHAR(2),
    credentials_no             VARCHAR(32),
    user_name                  VARCHAR(256),
    order_no                   VARCHAR(64),
    biz_type                   VARCHAR(2), 
    pay_month                  VARCHAR(16),
    gmt_ovd_date               VARCHAR(20),
    order_status               VARCHAR(3),
    create_amt                 VARCHAR(32),
    overdue_days               VARCHAR(10),
    overdue_amt                VARCHAR(32),
    gmt_pay                    VARCHAR(20),
    memo                       VARCHAR(256),
   constraint  pk_zmxy_sjfkmx  primary key ( zwrq,zhqzlsh )
)IN GAPS_DATA INDEX IN GAPS_INDEX ;

comment on table zmxy_sjfkmx is
'֥���������ݷ�����ϸ��';

comment on column zmxy_sjfkmx.zwrq is
'��������';

comment on column zmxy_sjfkmx.zhqzlsh is
'�ۺ�ǰ����ˮ��';

comment on column zmxy_sjfkmx.credentials_type is
'֤������';

comment on column zmxy_sjfkmx.credentials_no is
'֤������';

comment on column zmxy_sjfkmx.user_name is
'�û�����';

comment on column zmxy_sjfkmx.order_no is
'ҵ���';

comment on column zmxy_sjfkmx.biz_type is
'ҵ������';

comment on column zmxy_sjfkmx.pay_month is
'�����·�';

comment on column zmxy_sjfkmx.gmt_ovd_date is
'���׶�����';

comment on column zmxy_sjfkmx.order_status is
'ҵ��״̬';

comment on column zmxy_sjfkmx.create_amt is
'���Ŷ��/�ſ���';

comment on column zmxy_sjfkmx.overdue_days is
'��ǰ��������';

comment on column zmxy_sjfkmx.overdue_amt is
'��ǰ�����ܶ�';

comment on column zmxy_sjfkmx.gmt_pay is
'��������';

comment on column zmxy_sjfkmx.memo is
'��ע';






insert into zmxy_xtcsb (app_id,charset,version,platform,type_id,columns,primary_key_columns,update_day,by1) values ('300001971','GBK','1.0','zmop','typeid','��ϸ������','������','06','');
insert into app_cpxx(cpdm,cpmc,yybs,zbjg,ywrqlx,qdkzbz,jgkzcs,sxfbz,sfqybz,qyms,xyxljz,kkfs,jzsx,dzms,lsblts,pdblts,jyfs,rzms,whjg,whgy,whsj,cpzt,sxftkbz)
values('0030021','֥������ϵͳ','003','00000','1','1','0','1','0','1','K_DWBH','1','0','2',0,0,'5','0','00000','admin',to_char(current timestamp,'yyyymmddhh24miss'),'0','0');
insert into app_dwxx values('003002110000','֥������ϵͳǰ��','','','','','','','00000','admin',to_char(current timestamp,'yyyymmddhh24miss'),'','','0');
insert into app_dwcpxy values('003002110000','0030021','003002110000','֥������ϵͳǰ��','','','','','','','','','','','','','','','','','','',0.00,'00000','admin',to_char(current timestamp,'yyyymmddhh24miss'),'','','0','','','','','','','','','1','','','');
insert into app_txaqxx (ljbs,ljmc,ljlx,dwbh,qdkz,txms,txdz,txdk,whjg,whgy,whsj,txzt)values ('zmxy','֥������','3','003002110000','1','1','10.8.208.140','50043','00000','admin','20180227081818','0');



