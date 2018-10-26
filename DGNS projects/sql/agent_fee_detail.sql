drop table agent_fee_detail;
--==============================================================
-- Table: AGENT_FEE_DETAIL
--==============================================================
create table AGENT_FEE_DETAIL
(
   PKRQ                 CHAR(8)             not null,
   PTPCH                CHAR(8)             not null,
   CPDM                 CHAR(16),
   YWBH                 CHAR(16)            not null,
   BATCH_NO             CHAR(32)            not null,
   PAY_MONTH            CHAR(8),
   FILE_NAME            VARCHAR(128),
   TOT_SUCC_CNT         INTEGER,
   TOT_SUCC_AMT         DECIMAL(16,2),
   TOT_BUSI_AMT         DECIMAL(16,2),
   TOT_AMT1             DECIMAL(16,2),
   TOT_AMT2             DECIMAL(16,2),
   TOT_AMT3             DECIMAL(16,2),
   TOT_AMT4             DECIMAL(16,2),
   TOT_AMT5             DECIMAL(16,2),
   FEE_FLAG             CHAR(1),
   FEE_OWN_FLAG         CHAR(1),
   FEE_PAY_FLAG         CHAR(1),
   PAY_ACT_NO           CHAR(32),
   PAY_ACT_NAME         VARCHAR(100),
   PAYEE_ACT_NO         CHAR(32),
   PAYEE_ACT_NAME       VARCHAR(100),
   FEE                  DECIMAL(16,2),
   REAL_FEE             DECIMAL(16,2),
   ACCT_DATE            CHAR(8),
   ACCT_TIME            CHAR(6),
   ACCT_SEQ_NO          INTEGER,
   TX_UNIT              VARCHAR(16),
   TELLER_NO            VARCHAR(16),
   CHANNEL_NO           VARCHAR(3),
   STAT                 VARCHAR(1),
   CLEAR_STAT           VARCHAR(1),
   RESP_CODE            VARCHAR(7),
   RESP_MSG             VARCHAR(60),
   SEND_NUM             INTEGER,
   EXTFLD1              VARCHAR(80),
   EXTFLD2              VARCHAR(80),
   EXTFLD3              VARCHAR(80),
   EXTFLD4              VARCHAR(80),
   EXTFLD5              VARCHAR(80),
   EXTFLD6              VARCHAR(160),
   constraint P_K_AGENT_FEE_DETAIL_1 primary key (BATCH_NO)
);

CREATE UNIQUE INDEX AGENT_FEE_DETAIL_IDX1 ON AGENT_FEE_DETAIL(PKRQ,PTPCH);
CREATE INDEX AGENT_FEE_DETAIL_IDX2 ON AGENT_FEE_DETAIL(PKRQ,CPDM,STAT);
CREATE INDEX AGENT_FEE_DETAIL_IDX3 ON AGENT_FEE_DETAIL(PAY_MONTH,CPDM,YWBH);

comment on table AGENT_FEE_DETAIL is
'�������ո������ѿ۷���ϸ�Ǽǲ�';

comment on column AGENT_FEE_DETAIL.PKRQ is '��������';

comment on column AGENT_FEE_DETAIL.PTPCH is 'ƽ̨���κ�';

comment on column AGENT_FEE_DETAIL.CPDM is '��Ʒ����';

comment on column AGENT_FEE_DETAIL.YWBH is 'ҵ����';

comment on column AGENT_FEE_DETAIL.BATCH_NO is '�̻����κ�';

comment on column AGENT_FEE_DETAIL.PAY_MONTH is '��������(��������)';

comment on column AGENT_FEE_DETAIL.FILE_NAME is '�����ļ���';

comment on column AGENT_FEE_DETAIL.TOT_SUCC_CNT is '�ɹ��ܱ���';

comment on column AGENT_FEE_DETAIL.TOT_SUCC_AMT is '�ɹ��ܽ��';

comment on column AGENT_FEE_DETAIL.TOT_BUSI_AMT is '�ɹ���ҵ����';

comment on column AGENT_FEE_DETAIL.TOT_AMT1 is '�ɹ��ܷ���1';

comment on column AGENT_FEE_DETAIL.TOT_AMT2 is '�ɹ��ܷ���2';

comment on column AGENT_FEE_DETAIL.TOT_AMT3 is '�ɹ��ܷ���3';

comment on column AGENT_FEE_DETAIL.TOT_AMT4 is '�ɹ��ܷ���4';

comment on column AGENT_FEE_DETAIL.TOT_AMT5 is '�ɹ��ܷ���5';

comment on column AGENT_FEE_DETAIL.FEE_FLAG is '�����ѱ�־ 0-��ȡ,1-����';

comment on column AGENT_FEE_DETAIL.FEE_OWN_FLAG is '�����ѹ�����־ 0-��λ,1-����,2-����';

comment on column AGENT_FEE_DETAIL.FEE_PAY_FLAG is '�����ѿۻ���ʽ 0-�Զ� 1-�ֹ�';

comment on column AGENT_FEE_DETAIL.PAY_ACT_NO is '�����Ѹ����˺�';

comment on column AGENT_FEE_DETAIL.PAY_ACT_NAME is '�����Ѹ����˺�����';

comment on column AGENT_FEE_DETAIL.PAYEE_ACT_NO is '�������տ��˺�';

comment on column AGENT_FEE_DETAIL.PAYEE_ACT_NAME is '�������տ��˺�����';

comment on column AGENT_FEE_DETAIL.FEE is '�����ѽ��';

comment on column AGENT_FEE_DETAIL.REAL_FEE is 'ʵ�������ѽ��';

comment on column AGENT_FEE_DETAIL.ACCT_DATE is '��������';

comment on column AGENT_FEE_DETAIL.ACCT_TIME is '����ʱ��';

comment on column AGENT_FEE_DETAIL.ACCT_SEQ_NO is '������ˮ��';

comment on column AGENT_FEE_DETAIL.TX_UNIT is '���׻���';

comment on column AGENT_FEE_DETAIL.TELLER_NO is '���׹�Ա';

comment on column AGENT_FEE_DETAIL.CHANNEL_NO is '������ʶ';

comment on column AGENT_FEE_DETAIL.STAT is '״̬ 0-������,1-���˳ɹ�,2-����ʧ��,9-���˴�����';

comment on column AGENT_FEE_DETAIL.CLEAR_STAT is '����״̬ 0-������,1-����ɹ�,2-����ʧ��';

comment on column AGENT_FEE_DETAIL.RESP_CODE is '������';

comment on column AGENT_FEE_DETAIL.RESP_MSG is '������Ϣ';

comment on column AGENT_FEE_DETAIL.SEND_NUM is '���ʹ���';

comment on column AGENT_FEE_DETAIL.EXTFLD1 is '��չ�ֶ�1';

comment on column AGENT_FEE_DETAIL.EXTFLD2 is '��չ�ֶ�2';

comment on column AGENT_FEE_DETAIL.EXTFLD3 is '��չ�ֶ�3';

comment on column AGENT_FEE_DETAIL.EXTFLD4 is '��չ�ֶ�4';

comment on column AGENT_FEE_DETAIL.EXTFLD5 is '��չ�ֶ�5';

comment on column AGENT_FEE_DETAIL.EXTFLD6 is '��չ�ֶ�6';

