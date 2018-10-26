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
COMMENT ON TABLE TBL_SPFYSKJG_DSRW IS '预售监管定时任务登记表';
COMMENT ON COLUMN TBL_SPFYSKJG_DSRW.BOOKDATE IS '登记日期';
COMMENT ON COLUMN TBL_SPFYSKJG_DSRW.RECORDID IS '流水号';
COMMENT ON COLUMN TBL_SPFYSKJG_DSRW.SYSTEMID IS '子系统编码';
COMMENT ON COLUMN TBL_SPFYSKJG_DSRW.SYSTEMNAME IS '系统名称';
COMMENT ON COLUMN TBL_SPFYSKJG_DSRW.TASKNAME IS '定时任务名称';
COMMENT ON COLUMN TBL_SPFYSKJG_DSRW.TASKTYPE IS '任务类型';
COMMENT ON COLUMN TBL_SPFYSKJG_DSRW.TASKDESCRIBE IS '任务描述';
COMMENT ON COLUMN TBL_SPFYSKJG_DSRW.BEGINTIME IS '交易开始时间';
COMMENT ON COLUMN TBL_SPFYSKJG_DSRW.ENDTIME IS '交易结束时间';
COMMENT ON COLUMN TBL_SPFYSKJG_DSRW.STATUS IS '状态';
COMMENT ON COLUMN TBL_SPFYSKJG_DSRW.MEMO IS '交易描述';
COMMENT ON COLUMN TBL_SPFYSKJG_DSRW.MEGSTATUS IS '是否已短信通知';
COMMENT ON COLUMN TBL_SPFYSKJG_DSRW.REMARK1 IS '备用字段1';
COMMENT ON COLUMN TBL_SPFYSKJG_DSRW.REMARK2 IS '备用字段2';
COMMENT ON COLUMN TBL_SPFYSKJG_DSRW.REMARK3 IS '备用字段3';
