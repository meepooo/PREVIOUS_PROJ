drop table AGENT_XJZHDZ;

create table AGENT_XJZHDZ
(
  JZZH		CHAR(18) NOT NULL,
  XZZH		CHAR(18) NOT NULL,
  JYBT		CHAR(15),
  XYBT		CHAR(15),
  STAT		CHAR(1),
  constraint PK_AGENT_XJZHDZ_1 primary key (JZZH)
)IN AGENT_DATA INDEX IN AGENT_INDEX ;

--==============================================================
-- Index: K_AGT_DRLS_1
--==============================================================
CREATE INDEX
    AGENT_XJZHDZ_IDX2
ON
	AGENT_XJZHDZ
	(
	    JYBT    ASC
	)
	ALLOW REVERSE SCANS;

comment on table AGENT_XJZHDZ is
'新旧账号对照表';

comment on column AGENT_XJZHDZ.JZZH is
'旧子账号';

comment on column AGENT_XJZHDZ.XZZH is
'新子帐号';

comment on column AGENT_XJZHDZ.JYBT is
'旧一本通';

comment on column AGENT_XJZHDZ.XYBT is
'新一本通';

comment on column AGENT_XJZHDZ.STAT is
'状态';
