--删表语句
DROP TABLE AGENT_JFPT_DZDW;
--建表语句
CREATE TABLE    AGENT_JFPT_DZDW
(
 RWBH VARCHAR(5) NOT NULL,
 DWXH VARCHAR(5) NOT NULL,
 DWBH VARCHAR(16) NOT NULL,
 DWMC VARCHAR(80),
 QYZT VARCHAR(2) NOT NULL,
 SHZT VARCHAR(2) NOT NULL,
 CONSTRAINT P_PK_AGENT_JFPT_DZDW PRIMARY KEY (DWBH)
); 
COMMENT ON TABLE AGENT_JFPT_DZDW    IS    '缴费平台对账单位表';
COMMENT ON COLUMN AGENT_JFPT_DZDW.RWBH    IS    '任务编号';
COMMENT ON COLUMN AGENT_JFPT_DZDW.DWXH    IS    '单位序号';
COMMENT ON COLUMN AGENT_JFPT_DZDW.DWBH    IS    '单位编号';
COMMENT ON COLUMN AGENT_JFPT_DZDW.DWMC    IS    '单位名称';
COMMENT ON COLUMN AGENT_JFPT_DZDW.QYZT    IS    '签约状态: 0-正常 1-无效';
COMMENT ON COLUMN AGENT_JFPT_DZDW.SHZT    IS    '审核状态: 1-审核通过 2-审核拒绝 9-未审核';
--插表语句
insert into agent_jfpt_dzdw
select round((rownum-1)/200,0)+1,mod((rownum-1),200)+1, dwbh,dwmc,qyzt,shzt from
(
 select   rownumber () over ()  as rownum, a.dwbh,a.dwmc,b.qyzt ,b.shzt from app_dwxx a ,app_dwcpxy b 
 where a.dwbh like '400%' and a.dwbh not like '4001001%' and a.dwbh=b.dwbh and a.zt='0' 
);

