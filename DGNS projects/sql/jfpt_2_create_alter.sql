--�ɷ�ƽ̨����
ALTER TABLE agent_ddxx DROP PRIMARY KEY ;
ALTER TABLE agent_ddxx ADD CONSTRAINT PK_YXT_CINEMAS PRIMARY KEY (ddh,pch,xh);
reorg table agent_ddxx;
