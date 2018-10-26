drop table AGENT_DRLS_TMP;

--drop table AGENT_HIS_DRLS;

--==============================================================
-- Table: AGENT_DRLS_TMP
--==============================================================
create table AGENT_DRLS_TMP
(
   PTRQ                 VARCHAR(8)             not null,
   PTSJ                 VARCHAR(6),
   PTLS                 INTEGER                not null,
   JYXH                 INTEGER                not null default 1,
   YPTLSH               INTEGER,
   JYJG                 VARCHAR(16),
   JYGY                 VARCHAR(16),
   SQJG                 VARCHAR(16),
   SQGY                 VARCHAR(16),
   QDBS                 VARCHAR(3),
   ZDSBBH               VARCHAR(8),
   CPDM                 VARCHAR(16),
   YWBH                 VARCHAR(16),
   YWRQ                 VARCHAR(8),
   YWLSH                INTEGER,
   JYDM                 VARCHAR(8),
   KHMC                 VARCHAR(80),
   KHBH                 VARCHAR(32),
   DQDM                 VARCHAR(8),
   YHLX                 VARCHAR(16),
   YHH1                 VARCHAR(32),
   YHBSH                VARCHAR(32),
   YHMC                 VARCHAR(80),
   JYBZ                 VARCHAR(3),
   XZBZ                 VARCHAR(1),
   JDBZ                 VARCHAR(1),
   ZHLX                 VARCHAR(2),
   YHZH                 VARCHAR(32),
   JYJE                 NUMERIC(16,2),
   JYJE2                NUMERIC(16,2),
   SXF                  NUMERIC(16,2),
   ZNJ                  NUMERIC(16,2),
   PZZL                 VARCHAR(3),
   PZHM                 VARCHAR(32),
   JFBSH                VARCHAR(32),
   CXLSH                INTEGER,
   JYZY                 VARCHAR(40),
   FQFLSH               VARCHAR(32),
   FQFRQ                VARCHAR(8),
   FQFSJ                VARCHAR(6),
   FQFJYDM              VARCHAR(8),
   DSFLSH               VARCHAR(22),
   DSFRQ                VARCHAR(14),
   DSFJYLX              VARCHAR(8),
   DSFJYDM              VARCHAR(8),
   DSFXYM               VARCHAR(8),
   DSFXYXX              VARCHAR(60),
   DSFJYZT              VARCHAR(1),
   ZJLSH                VARCHAR(32),
   ZJRQ                 VARCHAR(14),
   ZJJYDM               VARCHAR(8),
   ZJXYM                VARCHAR(8),
   ZJXYXX               VARCHAR(60),
   ZJJYZT               VARCHAR(1),
   JYXYM                VARCHAR(8),
   JYXYXX               VARCHAR(60),
   JYZT                 VARCHAR(1),
   DSFDZBZ              VARCHAR(1),
   ZJDZBZ               VARCHAR(1),
   EXTFLD1              VARCHAR(40),
   EXTFLD2              VARCHAR(40),
   EXTFLD3              VARCHAR(40),
   EXTFLD4              VARCHAR(40),
   EXTFLD5              VARCHAR(40),
   EXTFLD6              VARCHAR(40),
   constraint P_PK_AGENT_DRLS_TMP primary key (PTRQ, PTLS, JYXH)
) INDEX IN AGENT_INDEX 
PARTITION BY RANGE(PTRQ)
(PART 2015	STARTING '20150101' 	ENDING '20151231' in AGENT_DATA ,
 PART 2016	STARTING '20160101' 	ENDING '20161231' in AGENT_DATA );

INSERT INTO AGENT_DRLS_TMP SELECT * FROM AGENT_DRLS where ptrq <= '20161231';
--INSERT INTO AGENT_DRLS_TMP SELECT * FROM AGENT_DRLS;
