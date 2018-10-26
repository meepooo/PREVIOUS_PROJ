drop table BATCH_ZJXX;
--==============================================================
-- Table: BATCH_ZJXX                                            
--==============================================================
create table BATCH_ZJXX  
(
   HOSTID           VARCHAR(30)                       not null,
   FLAG             INTEGER,
   STATUS           VARCHAR(1),
   BAK1             VARCHAR(40),
   BAK2             VARCHAR(40),
primary key (HOSTID) constraint PK_BATCH_ZJXX
);