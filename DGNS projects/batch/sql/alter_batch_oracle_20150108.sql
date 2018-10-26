drop table BATCH_ZJXX cascade constraints;
/*==============================================================*/
/* Table: BATCH_ZJXX                                            */
/*==============================================================*/

create table BATCH_ZJXX  
(
   HOSTID            VARCHAR2(30)                       not null,
   FLAG                 INTEGER                    		not null,
   STATUS               VARCHAR2(1)                    	not null,
   BAK1					VARCHAR2(40),
   BAK2					VARCHAR2(40),
   constraint PK_BATCH_ZJXX primary key (HOSTID)
);

comment on table BATCH_ZJXX is
'主机信息表';

comment on column BATCH_ZJXX.HOSTID is
'主机名称';

comment on column BATCH_ZJXX.FLAG is
'主机标记';

comment on column BATCH_ZJXX.STATUS is
'主机状态';

comment on column BATCH_ZJXX.BAK1 is
'备用1';

comment on column BATCH_ZJXX.BAK2 is
'备用2';