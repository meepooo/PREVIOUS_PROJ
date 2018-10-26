drop table TBL_SPFYSKJG_DSRW;    
create table TBL_SPFYSKJG_DSRW
(
 BOOKDATE                      varchar(8)             not null,
 RECORDID                      varchar(30)            not null,
 SYSTEMID                      varchar(30), 
 SYSTEMNAME                    varchar(40), 
 TASKNAME                      varchar(100),
 TASKTYPE                      varchar(2),  
 TASKDESCRIBE                  varchar(100),
 BEGINTIME                     date,         
 ENDTIME                       date,         
 STATUS                        varchar(2),  
 MEMO                          varchar(100),
 MEGSTATUS                     varchar(2),  
 REMARK1                       varchar(254),
 REMARK2                       varchar(254),
 REMARK3                       varchar(254),
 CONSTRAINT PK_TBL_SPFYSKJG_DSRW PRIMARY KEY (BOOKDATE,RECORDID))IN AGENT_DATA INDEX IN AGENT_INDEX;
COMMENT ON TABLE TBL_SPFYSKJG_DSRW IS 'Ԥ�ۼ�ܶ�ʱ����ǼǱ�';
COMMENT ON COLUMN TBL_SPFYSKJG_DSRW.BOOKDATE IS '�Ǽ�����';
COMMENT ON COLUMN TBL_SPFYSKJG_DSRW.RECORDID IS '��ˮ��';
COMMENT ON COLUMN TBL_SPFYSKJG_DSRW.SYSTEMID IS '��ϵͳ����';
COMMENT ON COLUMN TBL_SPFYSKJG_DSRW.SYSTEMNAME IS 'ϵͳ����';
COMMENT ON COLUMN TBL_SPFYSKJG_DSRW.TASKNAME IS '��ʱ��������';
COMMENT ON COLUMN TBL_SPFYSKJG_DSRW.TASKTYPE IS '��������';
COMMENT ON COLUMN TBL_SPFYSKJG_DSRW.TASKDESCRIBE IS '��������';
COMMENT ON COLUMN TBL_SPFYSKJG_DSRW.BEGINTIME IS '���׿�ʼʱ��';
COMMENT ON COLUMN TBL_SPFYSKJG_DSRW.ENDTIME IS '���׽���ʱ��';
COMMENT ON COLUMN TBL_SPFYSKJG_DSRW.STATUS IS '״̬';
COMMENT ON COLUMN TBL_SPFYSKJG_DSRW.MEMO IS '��������';
COMMENT ON COLUMN TBL_SPFYSKJG_DSRW.MEGSTATUS IS '�Ƿ��Ѷ���֪ͨ';
COMMENT ON COLUMN TBL_SPFYSKJG_DSRW.REMARK1 IS '�����ֶ�1';
COMMENT ON COLUMN TBL_SPFYSKJG_DSRW.REMARK2 IS '�����ֶ�2';
COMMENT ON COLUMN TBL_SPFYSKJG_DSRW.REMARK3 IS '�����ֶ�3';
