drop table ICPS_SERIAL;

drop table ICPS_BUSI_INF;

drop table ICPS_DAILY_STATUS;

drop table ICPS_FILE_INFO;



/*==============================================================*/
/* Table: ICPS_SERIAL                                           */
/*==============================================================*/
create table ICPS_SERIAL 
(
   plt_date             CHAR(8)              not null,
   plt_time             CHAR(6)              not null,
   plt_serial           VARCHAR(16)          not null,
   busi_date            VARCHAR(8)           not null,
   busi_no              VARCHAR(16)          not null,
   channel              VARCHAR(16),
   local_id             VARCHAR(32),
   trans_code           VARCHAR(8),
   send_recv_flag       CHAR(1),
   apply_no             VARCHAR(64),
   version              VARCHAR(8),
   send_time_zone       VARCHAR(32),
   send_dttm            VARCHAR(16),
   msg_id               VARCHAR(64),
   third_id             VARCHAR(32),
   third_trans_code     VARCHAR(64),
   third_respcode       VARCHAR(16),
   third_respmsg        VARCHAR(255),
   third_trans_status   VARCHAR(1),
   retry                CHAR(1),
   send_host_serial     VARCHAR(64),
   send_host_date       CHAR(8),
   host_serial          VARCHAR(64),
   host_date            CHAR(8),
   host_trans_code      VARCHAR(16),
   host_respcode        VARCHAR(16),
   host_respmsg         VARCHAR(250),
   host_status          VARCHAR(2),
   in_channel_date      VARCHAR(64),
   in_channel_serial    VARCHAR(8),
   respcode             VARCHAR(8),
   respmsg              VARCHAR(250),
   trans_status         VARCHAR(1),
   branch               VARCHAR(16),
   teller               VARCHAR(16),
   grant_branch         VARCHAR(16),
   grant_teller         VARCHAR(16),
   extend_param1        VARCHAR(10),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   extend_param4        VARCHAR(60),
   extend_param5        VARCHAR(250),
   constraint PK_ICPS_SERIAL primary key (plt_date, plt_serial)
);

comment on table ICPS_SERIAL is
'������ˮ��';

comment on column ICPS_SERIAL.plt_date is
'ƽ̨����YYYYMMDD';

comment on column ICPS_SERIAL.plt_time is
'ƽ̨ʱ��HHMMSS';

comment on column ICPS_SERIAL.plt_serial is
'ƽ̨��ˮ��';

comment on column ICPS_SERIAL.busi_date is
'ҵ������';

comment on column ICPS_SERIAL.busi_no is
'ҵ���� jiebei-���� jintiao-���� wbank-΢����';

comment on column ICPS_SERIAL.channel is
'�������� 311-���� 312-�������� 313-΢����';

comment on column ICPS_SERIAL.local_id is
'���л�����ʶ';

comment on column ICPS_SERIAL.trans_code is
'ƽ̨���״���';

comment on column ICPS_SERIAL.send_recv_flag is
'�����˱�־ 0-���� 1-����';

comment on column ICPS_SERIAL.apply_no is
'���뵥��';

comment on column ICPS_SERIAL.version is
'�汾�� �ӿڰ汾';

comment on column ICPS_SERIAL.send_time_zone is
'���ͷ�����ʱ�� UTC+8';

comment on column ICPS_SERIAL.send_dttm is
'���ķ���ʱ�� YYYYMMDDHHMMSS';

comment on column ICPS_SERIAL.msg_id is
'�����ı�ʾ��';

comment on column ICPS_SERIAL.third_id is
'������������ʶ';

comment on column ICPS_SERIAL.third_trans_code is
'���������״���';

comment on column ICPS_SERIAL.third_respcode is
'��������Ӧ��';

comment on column ICPS_SERIAL.third_respmsg is
'��������Ӧ��Ϣ';

comment on column ICPS_SERIAL.third_trans_status is
'����������״̬';

comment on column ICPS_SERIAL.retry is
'�Ƿ���Ҫ���Ա�� Y-��Ҫ N-����Ҫ';

comment on column ICPS_SERIAL.send_host_serial is
'����������ˮ��';

comment on column ICPS_SERIAL.send_host_date is
'������������';

comment on column ICPS_SERIAL.host_serial is
'������ˮ��';

comment on column ICPS_SERIAL.host_date is
'��������';

comment on column ICPS_SERIAL.host_trans_code is
'�������״���';

comment on column ICPS_SERIAL.host_respcode is
'������Ӧ��';

comment on column ICPS_SERIAL.host_respmsg is
'������Ӧ��Ϣ';

comment on column ICPS_SERIAL.host_status is
'��������״̬';

comment on column ICPS_SERIAL.in_channel_date is
'������������';

comment on column ICPS_SERIAL.in_channel_serial is
'����������ˮ��';

comment on column ICPS_SERIAL.respcode is
'������Ӧ��';

comment on column ICPS_SERIAL.respmsg is
'������Ӧ��Ϣ';

comment on column ICPS_SERIAL.trans_status is
'����״̬';

comment on column ICPS_SERIAL.branch is
'���׻���';

comment on column ICPS_SERIAL.teller is
'���׹�Ա';

comment on column ICPS_SERIAL.grant_branch is
'��Ȩ����';

comment on column ICPS_SERIAL.grant_teller is
'��Ȩ��Ա';

comment on column ICPS_SERIAL.extend_param1 is
'��չ1';

comment on column ICPS_SERIAL.extend_param2 is
'��չ2';

comment on column ICPS_SERIAL.extend_param3 is
'��չ3';

comment on column ICPS_SERIAL.extend_param4 is
'��չ4';

comment on column ICPS_SERIAL.extend_param5 is
'��չ5';


/*==============================================================*/
/* Table: ICPS_BUSI_INF                                         */
/*==============================================================*/
create table ICPS_BUSI_INF 
(
   busi_no              VARCHAR(16)         not null,
   busi_nm              VARCHAR(64),
   local_id             VARCHAR(16),
   time_zone            VARCHAR(32),
   sign_type            VARCHAR(16),
   message_charset      VARCHAR(16),
   version              VARCHAR(8)          not null,
   clear_acct_id        VARCHAR(64),
   clear_acct_nm        VARCHAR(128),
   position_acct_id     VARCHAR(64),
   position_acct_nm     VARCHAR(128),
   fee_out_acct_id      VARCHAR(64),
   fee_out_acct_nm      VARCHAR(128),
   fee_in_acct_id       VARCHAR(64),
   fee_in_acct_nm       VARCHAR(128),
   provisions_acct_id   VARCHAR(64),
   provisions_acct_nm   VARCHAR(128),
   open_flag            CHAR(1),
   extend_param1        VARCHAR(100),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_BUSI_INF primary key (busi_no)
);

comment on table ICPS_BUSI_INF is
'ҵ����Ϣ��';

comment on column ICPS_BUSI_INF.busi_no is
'ҵ���� jiebei-���� jintiao-���� wbank-΢����';

comment on column ICPS_BUSI_INF.busi_nm is
'ҵ������';

comment on column ICPS_BUSI_INF.local_id is
'����������';

comment on column ICPS_BUSI_INF.time_zone is
'������ʱ��';

comment on column ICPS_BUSI_INF.sign_type is
'ǩ���㷨���� RSA';

comment on column ICPS_BUSI_INF.message_charset is
'�����ַ�����';

comment on column ICPS_BUSI_INF.version is
'�汾��';

comment on column ICPS_BUSI_INF.clear_acct_id is
'�ڲ������˺�';

comment on column ICPS_BUSI_INF.clear_acct_nm is
'�ڲ������˺�����';

comment on column ICPS_BUSI_INF.position_acct_id is
'�ڲ�ͷ���˺�';

comment on column ICPS_BUSI_INF.position_acct_nm is
'�ڲ�ͷ���˺�����';

comment on column ICPS_BUSI_INF.fee_out_acct_id is
'������֧���˺�';

comment on column ICPS_BUSI_INF.fee_out_acct_nm is
'������֧���˺�����';

comment on column ICPS_BUSI_INF.fee_in_acct_id is
'�����������˺�';

comment on column ICPS_BUSI_INF.fee_in_acct_nm is
'�����������˺�����';

comment on column ICPS_BUSI_INF.provisions_acct_id is
'�������������˺�';

comment on column ICPS_BUSI_INF.provisions_acct_nm is
'�������������˺�����';

comment on column ICPS_BUSI_INF.open_flag is
'��ͨ��ʶ 0-δ��ͨ 1-��ͨ';

comment on column ICPS_BUSI_INF.extend_param1 is
'��չ1';

comment on column ICPS_BUSI_INF.extend_param2 is
'��չ2';

comment on column ICPS_BUSI_INF.extend_param3 is
'��չ3';


/*==============================================================*/
/* Table: ICPS_DAILY_STATUS                                     */
/*==============================================================*/
create table ICPS_DAILY_STATUS 
(
   busi_date            CHAR(8)              not null,
   busi_no              VARCHAR(16)          not null,
   file_step            CHAR(2),
   third_total_check_status CHAR(1),
   third_detail_check_status CHAR(1),
   host_total_check_status CHAR(1),
   host_detail_check_status CHAR(1),
   third_pre_total_check_status CHAR(1),
   third_pre_detail_check_status CHAR(1),
   host_pre_total_check_status CHAR(1),
   host_pre_detail_check_status CHAR(1),
   plt_date             CHAR(8),
   plt_serial           VARCHAR(16),
   send_host_date       CHAR(8),
   host_serial          VARCHAR(64),
   host_date            CHAR(8),
   respcode             VARCHAR(8),
   respmsg              VARCHAR(250),
   trans_status         VARCHAR(1),
   branch               VARCHAR(16),
   teller               VARCHAR(16),
   extend_param1        VARCHAR(10),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_DAILY_STATUS primary key (busi_date, busi_no)
);

comment on table ICPS_DAILY_STATUS is
'����״̬��';

comment on column ICPS_DAILY_STATUS.busi_date is
'ҵ������';

comment on column ICPS_DAILY_STATUS.busi_no is
'ҵ���� jiebei-���� jintiao-���� wbank-΢����';

comment on column ICPS_DAILY_STATUS.file_step is
'�ļ����� 00-��ȡ�� 01-��ȡ�ɹ� 02-���ֻ�ȡ�ɹ� 03-��ȡʧ�� 04-����� 05-���ɹ� 06-�������ɹ� 07-���ʧ�� 99-��ʼ';

comment on column ICPS_DAILY_STATUS.third_total_check_status is
'������������״̬ 0 δ���� 1 ����ƽ 2 ���˲�ƽ 3���˳��� 4����ƽ��β�� 9 ������';

comment on column ICPS_DAILY_STATUS.third_detail_check_status is
'��������ϸ����״̬  0 δ���� 1 ����ƽ 2 ���˲�ƽ 3���˳��� 4����ƽ��β�� 9 ������';

comment on column ICPS_DAILY_STATUS.host_total_check_status is
'���Ķ�����״̬ 0 δ���� 1 ����ƽ 2 ���˲�ƽ 3���˳��� 4����ƽ��β�� 9 ������';

comment on column ICPS_DAILY_STATUS.host_detail_check_status is
'������ϸ����״̬ 0 δ���� 1 ����ƽ 2 ���˲�ƽ 3���˳��� 4����ƽ��β�� 9 ������';

comment on column ICPS_DAILY_STATUS.third_pre_total_check_status is
'������Ԥ������״̬ 0 δ���� 1 ����ƽ 2 ���˲�ƽ 3���˳��� 4����ƽ��β�� 9 ������';

comment on column ICPS_DAILY_STATUS.third_pre_detail_check_status is
'������Ԥ��ϸ����״̬ 0 δ���� 1 ����ƽ 2 ���˲�ƽ 3���˳��� 4����ƽ��β�� 9 ������';

comment on column ICPS_DAILY_STATUS.host_pre_total_check_status is
'����Ԥ������״̬ 0 δ���� 1 ����ƽ 2 ���˲�ƽ 3���˳��� 4����ƽ��β�� 9 ������';

comment on column ICPS_DAILY_STATUS.host_pre_detail_check_status is
'����Ԥ��ϸ����״̬ 0 δ���� 1 ����ƽ 2 ���˲�ƽ 3���˳��� 4����ƽ��β�� 9 ������';

comment on column ICPS_DAILY_STATUS.plt_date is
'ƽ̨����YYYYMMDD';

comment on column ICPS_DAILY_STATUS.plt_serial is
'ƽ̨��ˮ��';

comment on column ICPS_DAILY_STATUS.send_host_date is
'������������';

comment on column ICPS_DAILY_STATUS.host_serial is
'������ˮ��';

comment on column ICPS_DAILY_STATUS.host_date is
'��������';

comment on column ICPS_DAILY_STATUS.respcode is
'������Ӧ��';

comment on column ICPS_DAILY_STATUS.respmsg is
'������Ӧ��Ϣ';

comment on column ICPS_DAILY_STATUS.trans_status is
'����״̬';

comment on column ICPS_DAILY_STATUS.branch is
'���׻���';

comment on column ICPS_DAILY_STATUS.teller is
'���׹�Ա';

comment on column ICPS_DAILY_STATUS.extend_param1 is
'��չ1';

comment on column ICPS_DAILY_STATUS.extend_param2 is
'��չ2';

comment on column ICPS_DAILY_STATUS.extend_param3 is
'��չ3';


/*==============================================================*/
/* Table: ICPS_FILE_INFO                                        */
/*==============================================================*/
create table ICPS_FILE_INFO 
(
   busi_date            VARCHAR(8)          not null,
   busi_no              VARCHAR(16)         not null,
   file_type            VARCHAR(60)         not null,
   md5_code             VARCHAR(64),
   file_status          CHAR(1),
   plt_date             CHAR(8),
   plt_serial           VARCHAR(16),
   extend_param1        VARCHAR(10),
   extend_param2        VARCHAR(250),
   extend_param3        VARCHAR(40),
   constraint PK_ICPS_FILE_INFO primary key (busi_date, busi_no, file_type)
);

comment on table ICPS_FILE_INFO is
'�ļ���Ϣ�����';

comment on column ICPS_FILE_INFO.busi_date is
'ҵ������';

comment on column ICPS_FILE_INFO.busi_no is
'ҵ���� jiebei-���� jintiao-���� wbank-΢����';

comment on column ICPS_FILE_INFO.file_type is
'�ļ�����';

comment on column ICPS_FILE_INFO.md5_code is
'MD5ֵ 16�����ַ���';

comment on column ICPS_FILE_INFO.file_status is
'�ļ�״̬';

comment on column ICPS_FILE_INFO.plt_date is
'ƽ̨����YYYYMMDD';

comment on column ICPS_FILE_INFO.plt_serial is
'ƽ̨��ˮ��';

comment on column ICPS_FILE_INFO.extend_param1 is
'��չ1';

comment on column ICPS_FILE_INFO.extend_param2 is
'��չ2';

comment on column ICPS_FILE_INFO.extend_param3 is
'��չ3';