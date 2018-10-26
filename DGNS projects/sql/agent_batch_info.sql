drop table agent_batch_info;
--==============================================================
-- Table: AGENT_BATCH_INFO
--==============================================================
create table AGENT_BATCH_INFO
(
   BATCH_NO             CHAR(32)            not null,
   CPDM                 CHAR(16)            not null,
   DWBH                 CHAR(16)            not null,
   FILE_NAME            VARCHAR(256)        not null,
   ORI_FILE_NAME        VARCHAR(256),
   UP_DATE              CHAR(8),
   UP_SEQ_NO            INTEGER,
   UP_TIME              CHAR(6),
   UP_UNIT              CHAR(16),
   UP_TELLER            CHAR(16),
   UP_CHANNEL           CHAR(3),
   UPLOAD_TYPE          CHAR(2),
   DC_FLAG              CHAR(1),
   PLAT_DATE            CHAR(8),
   SEQ_NO               INTEGER,
   PLAT_TIME            CHAR(6),
   TX_UNIT              CHAR(16),
   TELLER_NO            CHAR(16),
   CHANNEL_NO           CHAR(3),
   EXEC_DATE            CHAR(8),
   WITHDRAW_DATE        CHAR(8),
   WITHDRAW_SEQ         INTEGER,
   WITHDRAW_TIME        CHAR(6),
   WITHDRAW_UNIT        CHAR(16),
   WITHDRAW_TELLER      CHAR(16),
   WITHDRAW_CHANN       CHAR(3),
   BRIEF_CODE           CHAR(6),
   MD5_CODE             CHAR(40),
   STAT                 CHAR(1),
   RESP_CODE            CHAR(7),
   RESP_MSG             VARCHAR(60),
   RET_FILE_NAME        VARCHAR(256),
   TOT_CNT              INTEGER,
   TOT_AMT              DECIMAL(16,2),
   TOT_SUCC_CNT         INTEGER,
   TOT_SUCC_AMT         DECIMAL(16,2),
   TOT_BUSI_AMT         DECIMAL(16,2),
   TOT_AMT1             DECIMAL(16,2),
   TOT_AMT2             DECIMAL(16,2),
   TOT_AMT3             DECIMAL(16,2),
   TOT_AMT4             DECIMAL(16,2),
   TOT_AMT5             DECIMAL(16,2),
   FULL_CNT             INTEGER,
   FULL_AMT             DECIMAL(16,2),
   PART_CNT             INTEGER,
   PART_AMT             DECIMAL(16,2),
   FEE_CNT              INTEGER,
   FEE                  DECIMAL(16,2),
   REAL_FEE_CNT         INTEGER,
   REAL_FEE             DECIMAL(16,2),
   OPEN_SUCC_CNT        INTEGER,
   OPEN_SUCC_AMT        DECIMAL(16,2),
   OPEN_FAIL_CNT        INTEGER,
   OPEN_FAIL_AMT        DECIMAL(16,2),
   ACCT_DATE            CHAR(8),
   EXTFLD1              VARCHAR(80),
   EXTFLD2              VARCHAR(80),
   EXTFLD3              VARCHAR(80),
   EXTFLD4              VARCHAR(80),
   EXTFLD5              VARCHAR(80),
   EXTFLD6              VARCHAR(160),
   constraint P_K_AGENT_BATCH_INFO_1 primary key (BATCH_NO)
);

CREATE UNIQUE INDEX AGENT_BATCH_INFO_IDX1 ON AGENT_BATCH_INFO(CPDM,DWBH,FILE_NAME);
CREATE INDEX AGENT_BATCH_INFO_IDX2 ON AGENT_BATCH_INFO(UP_DATE,UP_UNIT);
CREATE INDEX AGENT_BATCH_INFO_IDX3 ON AGENT_BATCH_INFO(PLAT_DATE,TX_UNIT);
CREATE INDEX AGENT_BATCH_INFO_IDX4 ON AGENT_BATCH_INFO(EXEC_DATE,STAT);

comment on table AGENT_BATCH_INFO is
'�������ո�������Ϣ�Ǽǲ�';

comment on column AGENT_BATCH_INFO.BATCH_NO is
'���κ�';

comment on column AGENT_BATCH_INFO.CPDM is
'��Ʒ����';

comment on column AGENT_BATCH_INFO.DWBH is
'��λ���';

comment on column AGENT_BATCH_INFO.FILE_NAME is
'�ļ���';

comment on column AGENT_BATCH_INFO.ORI_FILE_NAME is
'ԭ�ϴ��ļ���';

comment on column AGENT_BATCH_INFO.UP_DATE is
'�ϴ�����';

comment on column AGENT_BATCH_INFO.UP_SEQ_NO is
'�ϴ���ˮ��';

comment on column AGENT_BATCH_INFO.UP_TIME is
'�ϴ�ʱ��';

comment on column AGENT_BATCH_INFO.UP_UNIT is
'�ϴ�����';

comment on column AGENT_BATCH_INFO.UP_TELLER is
'�ϴ���Ա';

comment on column AGENT_BATCH_INFO.UP_CHANNEL is
'�ϴ�������ʶ';

comment on column AGENT_BATCH_INFO.UPLOAD_TYPE is
'�ϴ���ʽ 01-�ɷ�ƽ̨ 02-����ϵͳ 03-���´��� ';

comment on column AGENT_BATCH_INFO.DC_FLAG is
'�ո���־ 1-�� 2-��';

comment on column AGENT_BATCH_INFO.PLAT_DATE is
'������������';

comment on column AGENT_BATCH_INFO.SEQ_NO is
'����������ˮ��';

comment on column AGENT_BATCH_INFO.PLAT_TIME is
'��������ʱ��';

comment on column AGENT_BATCH_INFO.TX_UNIT is
'�����������';

comment on column AGENT_BATCH_INFO.TELLER_NO is
'���������Ա';

comment on column AGENT_BATCH_INFO.CHANNEL_NO is
'��������������ʶ';

comment on column AGENT_BATCH_INFO.EXEC_DATE is
'������������';

comment on column AGENT_BATCH_INFO.WITHDRAW_DATE is
'��������';

comment on column AGENT_BATCH_INFO.WITHDRAW_SEQ is
'������ˮ��';

comment on column AGENT_BATCH_INFO.WITHDRAW_TIME is
'����ʱ��';

comment on column AGENT_BATCH_INFO.WITHDRAW_UNIT is
'��������';

comment on column AGENT_BATCH_INFO.WITHDRAW_TELLER is
'������Ա';

comment on column AGENT_BATCH_INFO.WITHDRAW_CHANN is
'����������ʶ';

comment on column AGENT_BATCH_INFO.BRIEF_CODE is
'ժҪ����';

comment on column AGENT_BATCH_INFO.MD5_CODE is
'�ļ�md5��';

comment on column AGENT_BATCH_INFO.STAT is
'����״̬ 1-����ɹ� 2-����ʧ�� 3-���̳ɹ� 4-�ѳ��� 8-���������� 9-������';

comment on column AGENT_BATCH_INFO.RESP_CODE is
'������';

comment on column AGENT_BATCH_INFO.RESP_MSG is
'������Ϣ';

comment on column AGENT_BATCH_INFO.RET_FILE_NAME is
'�����ļ���';

comment on column AGENT_BATCH_INFO.TOT_CNT is
'�ܱ���';

comment on column AGENT_BATCH_INFO.TOT_AMT is
'�ܽ��';

comment on column AGENT_BATCH_INFO.TOT_SUCC_CNT is
'�ɹ��ܱ���';

comment on column AGENT_BATCH_INFO.TOT_SUCC_AMT is
'�ɹ��ܽ��';

comment on column AGENT_BATCH_INFO.TOT_BUSI_AMT is
'�ɹ���ҵ����';

comment on column AGENT_BATCH_INFO.TOT_AMT1 is
'�ɹ��ܷ���1';

comment on column AGENT_BATCH_INFO.TOT_AMT2 is
'�ɹ��ܷ���2';

comment on column AGENT_BATCH_INFO.TOT_AMT3 is
'�ɹ��ܷ���3';

comment on column AGENT_BATCH_INFO.TOT_AMT4 is
'�ɹ��ܷ���4';

comment on column AGENT_BATCH_INFO.TOT_AMT5 is
'�ɹ��ܷ���5';

comment on column AGENT_BATCH_INFO.FULL_CNT is
'���֧���ܻ���';

comment on column AGENT_BATCH_INFO.FULL_AMT is
'���֧���ܽ��';

comment on column AGENT_BATCH_INFO.PART_CNT is
'����֧���ܻ���';

comment on column AGENT_BATCH_INFO.PART_AMT is
'����֧���ܽ��';

comment on column AGENT_BATCH_INFO.FEE_CNT is
'Ӧ���������ܱ���';

comment on column AGENT_BATCH_INFO.FEE is
'Ӧ���������ܽ��';

comment on column AGENT_BATCH_INFO.REAL_FEE_CNT is
'ʵ���������ܱ���';

comment on column AGENT_BATCH_INFO.REAL_FEE is
'ʵ���������ܽ��';

comment on column AGENT_BATCH_INFO.OPEN_SUCC_CNT is
'�����ɹ��ܻ���';

comment on column AGENT_BATCH_INFO.OPEN_SUCC_AMT is
'�����ɹ��ܽ��';

comment on column AGENT_BATCH_INFO.OPEN_FAIL_CNT is
'����ʧ���ܻ���';

comment on column AGENT_BATCH_INFO.OPEN_FAIL_AMT is
'����ʧ���ܽ��';

comment on column AGENT_BATCH_INFO.ACCT_DATE is
'������������(��������)';

comment on column AGENT_BATCH_INFO.EXTFLD1 is
'��չ�ֶ�1';

comment on column AGENT_BATCH_INFO.EXTFLD2 is
'��չ�ֶ�2';

comment on column AGENT_BATCH_INFO.EXTFLD3 is
'��չ�ֶ�3';

comment on column AGENT_BATCH_INFO.EXTFLD4 is
'��չ�ֶ�4';

comment on column AGENT_BATCH_INFO.EXTFLD5 is
'��չ�ֶ�5';

comment on column AGENT_BATCH_INFO.EXTFLD6 is
'��չ�ֶ�6';

