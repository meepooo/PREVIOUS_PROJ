drop table TBL_SPFYSKJG_JGXM_ZCJYMX;
create table TBL_SPFYSKJG_JGXM_ZCJYMX
(
DETAILID                    varchar(40)               not null,                              
BOOKDATE                    varchar(8)                 not null,
ACCOUNT                     varchar(40)               not null,
TRANDT                      varchar(8)                not null,
TRANSQ                      varchar(20),  
OCCURS                      varchar(2),   
PROTOCOLNO                  varchar(40),  
PROTOCOLVAL                 varchar(20),  
CUSTNO                      varchar(512), 
TRANSTYPE                   varchar(40)               not null,
AMOUNT                      varchar(17)               not null,
AMOUNT2                     varchar(17),  
SMRYTX                      varchar(120), 
TSDATE                      varchar(8),   
MEMO                        varchar(100), 
STATUS                      varchar(2),    
PUSHNO                      DECIMAL(2),     
USERID                      varchar(40),  
ORGID                       varchar(40),  
UPDATEDATE                  varchar(8),   
REMARK1                     varchar(254),  
REMARK2                     varchar(254),  
REMARK3                     varchar(254),  
CONSTRAINT PK_TBL_SPFYSKJG_JGXM_ZCJYMX PRIMARY KEY (DETAILID,BOOKDATE,ACCOUNT,
TRANDT,TRANSTYPE,AMOUNT))IN AGENT_DATA INDEX IN AGENT_INDEX;
COMMENT ON TABLE TBL_SPFYSKJG_JGXM_ZCJYMX IS 'Ԥ�ۼ���˻�֧��������ϸ�ǼǱ�';
COMMENT ON COLUMN TBL_SPFYSKJG_JGXM_ZCJYMX.DETAILID IS '�����˻����׼�¼��ϸΨһ��ʶ��';
COMMENT ON COLUMN TBL_SPFYSKJG_JGXM_ZCJYMX.BOOKDATE IS '�Ǽ�����';
COMMENT ON COLUMN TBL_SPFYSKJG_JGXM_ZCJYMX.ACCOUNT IS '����˺�';
COMMENT ON COLUMN TBL_SPFYSKJG_JGXM_ZCJYMX.TRANDT IS '��������';
COMMENT ON COLUMN TBL_SPFYSKJG_JGXM_ZCJYMX.TRANSQ IS '������ˮ��';
COMMENT ON COLUMN TBL_SPFYSKJG_JGXM_ZCJYMX.OCCURS IS '�ʽ��׷���:D�� C��';
COMMENT ON COLUMN TBL_SPFYSKJG_JGXM_ZCJYMX.PROTOCOLNO IS '��ͬ���';
COMMENT ON COLUMN TBL_SPFYSKJG_JGXM_ZCJYMX.PROTOCOLVAL IS '��ͬ���';
COMMENT ON COLUMN TBL_SPFYSKJG_JGXM_ZCJYMX.CUSTNO IS '���ݱ��';
COMMENT ON COLUMN TBL_SPFYSKJG_JGXM_ZCJYMX.TRANSTYPE IS '��������';
COMMENT ON COLUMN TBL_SPFYSKJG_JGXM_ZCJYMX.AMOUNT IS '��¼���';
COMMENT ON COLUMN TBL_SPFYSKJG_JGXM_ZCJYMX.AMOUNT2 IS '��ˮ���';
COMMENT ON COLUMN TBL_SPFYSKJG_JGXM_ZCJYMX.SMRYTX IS 'ժҪ';
COMMENT ON COLUMN TBL_SPFYSKJG_JGXM_ZCJYMX.TSDATE IS '��������';
COMMENT ON COLUMN TBL_SPFYSKJG_JGXM_ZCJYMX.MEMO IS '���׽������';
COMMENT ON COLUMN TBL_SPFYSKJG_JGXM_ZCJYMX.STATUS IS '����״̬';
COMMENT ON COLUMN TBL_SPFYSKJG_JGXM_ZCJYMX.PUSHNO IS '�������';
COMMENT ON COLUMN TBL_SPFYSKJG_JGXM_ZCJYMX.USERID IS '������id';
COMMENT ON COLUMN TBL_SPFYSKJG_JGXM_ZCJYMX.ORGID IS '��������������';
COMMENT ON COLUMN TBL_SPFYSKJG_JGXM_ZCJYMX.UPDATEDATE IS 'ά������';
COMMENT ON COLUMN TBL_SPFYSKJG_JGXM_ZCJYMX.REMARK1 IS '�����ֶ�1';
COMMENT ON COLUMN TBL_SPFYSKJG_JGXM_ZCJYMX.REMARK2 IS '�����ֶ�2';          
COMMENT ON COLUMN TBL_SPFYSKJG_JGXM_ZCJYMX.REMARK3 IS '�����ֶ�3';        
                         

