drop table SYS_ORG;
CREATE TABLE SYS_ORG
(
   ORGID varchar(128),
   ORGNO varchar(20) PRIMARY KEY NOT NULL,
   ORGNAME varchar(256) NOT NULL,
   ORGLEVEL varchar(3) NOT NULL,
   ORGTYPE varchar(8),
   PARENTORGNO varchar(32),
   PASSWORD varchar(32),
   CHECKORGNO varchar(32),
   ADDRESS varchar(256),
   CONTECT varchar(32),
   TELNO varchar(32),
   ORG_STATUS char(1),
   STANDBY1 varchar(32),
   STANDBY2 varchar(32),
   STANDBY3 varchar(64),
   STANDBY4 varchar(128),
   STANDBY5 varchar(256)
) ;
--CREATE UNIQUE INDEX SYS_ORG_IDX1 ON SYS_ORG(ORGNO) ;
