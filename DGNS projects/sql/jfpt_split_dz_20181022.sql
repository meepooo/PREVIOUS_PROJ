--ɾ�����
DROP TABLE AGENT_JFPT_DZDW;
--�������
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
COMMENT ON TABLE AGENT_JFPT_DZDW    IS    '�ɷ�ƽ̨���˵�λ��';
COMMENT ON COLUMN AGENT_JFPT_DZDW.RWBH    IS    '������';
COMMENT ON COLUMN AGENT_JFPT_DZDW.DWXH    IS    '��λ���';
COMMENT ON COLUMN AGENT_JFPT_DZDW.DWBH    IS    '��λ���';
COMMENT ON COLUMN AGENT_JFPT_DZDW.DWMC    IS    '��λ����';
COMMENT ON COLUMN AGENT_JFPT_DZDW.QYZT    IS    'ǩԼ״̬: 0-���� 1-��Ч';
COMMENT ON COLUMN AGENT_JFPT_DZDW.SHZT    IS    '���״̬: 1-���ͨ�� 2-��˾ܾ� 9-δ���';
--������
insert into agent_jfpt_dzdw
select round((rownum-1)/200,0)+1,mod((rownum-1),200)+1, dwbh,dwmc,qyzt,shzt from
(
 select   rownumber () over ()  as rownum, a.dwbh,a.dwmc,b.qyzt ,b.shzt from app_dwxx a ,app_dwcpxy b 
 where a.dwbh like '400%' and a.dwbh not like '4001001%' and a.dwbh=b.dwbh and a.zt='0' 
);

