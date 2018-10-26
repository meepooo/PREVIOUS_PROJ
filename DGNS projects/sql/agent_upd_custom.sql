drop table agent_upd_custom;
--==============================================================
-- Table: AGENT_UPD_CUSTOM
--==============================================================
create table AGENT_UPD_CUSTOM
(
   BATCH_NO             VARCHAR(32)            not null,
   CPDM                 VARCHAR(16)            not null,
   DWBH                 VARCHAR(16)            not null,
   FILE_NAME            VARCHAR(256)           not null,
   PLAT_DATE            INTEGER,
   SEQ_NO               VARCHAR(16),
   PLAT_TIME            CHAR(6),
   TX_UNIT              VARCHAR(16),
   TELLER_NO            VARCHAR(16),
   CHANNEL_NO           CHAR(3),
   UPLOAD_TYPE          CHAR(2),
   STAT                 CHAR(1),
   RESP_CODE            CHAR(7),
   RESP_MSG             VARCHAR(60),
   RET_FILE_NAME        VARCHAR(256),
   EXTFLD1              VARCHAR(80),
   EXTFLD2              VARCHAR(80),
   EXTFLD3              VARCHAR(80),
   EXTFLD4              VARCHAR(80),
   EXTFLD5              VARCHAR(80),
   EXTFLD6              VARCHAR(160),
   constraint P_K_AGENT_UPD_CUSTOM_1 primary key (BATCH_NO)
);

CREATE INDEX AGENT_UPD_CUSTOM_IDX1 ON AGENT_UPD_CUSTOM(CPDM,DWBH,FILE_NAME,STAT);
CREATE INDEX AGENT_UPD_CUSTOM_IDX2 ON AGENT_UPD_CUSTOM(PLAT_DATE,STAT);

comment on table AGENT_UPD_CUSTOM is
'�����ͻ�Э����Ϣ�Ǽǲ�';

comment on column AGENT_UPD_CUSTOM.BATCH_NO is
'���κ�';

comment on column AGENT_UPD_CUSTOM.CPDM is
'��Ʒ����';

comment on column AGENT_UPD_CUSTOM.DWBH is
'��λ���';

comment on column AGENT_UPD_CUSTOM.FILE_NAME is
'�ļ���';

comment on column AGENT_UPD_CUSTOM.PLAT_DATE is
'ƽ̨����';

comment on column AGENT_UPD_CUSTOM.SEQ_NO is
'ƽ̨��ˮ��';

comment on column AGENT_UPD_CUSTOM.PLAT_TIME is
'ƽ̨ʱ��';

comment on column AGENT_UPD_CUSTOM.TX_UNIT is
'���׻���';

comment on column AGENT_UPD_CUSTOM.TELLER_NO is
'���׹�Ա';

comment on column AGENT_UPD_CUSTOM.CHANNEL_NO is
'������ʶ';

comment on column AGENT_UPD_CUSTOM.UPLOAD_TYPE is
'�ϴ���ʽ 01-�ɷ�ƽ̨ 02-����ϵͳ 03-���´��� ';

comment on column AGENT_UPD_CUSTOM.STAT is
'����״̬ 1-����ɹ� 2-����ʧ�� 3-���̳ɹ� 4-�ύ���� 5-����ļ� 9-������';

comment on column AGENT_UPD_CUSTOM.RESP_CODE is
'������';

comment on column AGENT_UPD_CUSTOM.RESP_MSG is
'������Ϣ';

comment on column AGENT_UPD_CUSTOM.RET_FILE_NAME is
'�����ļ���';

comment on column AGENT_UPD_CUSTOM.EXTFLD1 is
'��չ�ֶ�1';

comment on column AGENT_UPD_CUSTOM.EXTFLD2 is
'��չ�ֶ�2';

comment on column AGENT_UPD_CUSTOM.EXTFLD3 is
'��չ�ֶ�3';

comment on column AGENT_UPD_CUSTOM.EXTFLD4 is
'��չ�ֶ�4';

comment on column AGENT_UPD_CUSTOM.EXTFLD5 is
'��չ�ֶ�5';

comment on column AGENT_UPD_CUSTOM.EXTFLD6 is
'��չ�ֶ�6';

