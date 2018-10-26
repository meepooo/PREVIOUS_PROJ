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
'�¾��˺Ŷ��ձ�';

comment on column AGENT_XJZHDZ.JZZH is
'�����˺�';

comment on column AGENT_XJZHDZ.XZZH is
'�����ʺ�';

comment on column AGENT_XJZHDZ.JYBT is
'��һ��ͨ';

comment on column AGENT_XJZHDZ.XYBT is
'��һ��ͨ';

comment on column AGENT_XJZHDZ.STAT is
'״̬';
