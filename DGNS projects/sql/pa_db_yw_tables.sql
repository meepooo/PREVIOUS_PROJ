-------------------------------------------------------------------------------- 
--  ��ռ�����  "TBS_PAYY_DAT_32K"
--
----------------------------------------

-- ����: PABYBH_ORGCFG
-- ����: �������ñ�
-------------------------------------------------------------------------------- 
drop table PABYBH_ORGCFG;
create table PABYBH_ORGCFG
(
    bankOrgNo         VARCHAR(12) not null,            --���˻�����                     
    bankOrgName       VARCHAR(120),                    --���˻���������                 
    coBankNo          VARCHAR(12) not null,            --�����кš�ƽ�����䡿                      
    coBankName        VARCHAR(100) not null,           --����������                     
    custManagerNo    VARCHAR(10) not null,             --ƽ������ͻ�����š�ƽ�����䡿    
    acct1             VARCHAR(32) not null,            --ͷ���˻�
    acct1Name         VARCHAR(60) not null,            --ͷ���˻�����
    acct2             VARCHAR(32) not null,            --�ڲ������˻�
    acct2Name         VARCHAR(60) not null,            --�ڲ������˻����� 
    signStatus        VARCHAR(1) not null,             --ǩ��״̬��0-ǩ����1-ǩ��
    areaCode          VARCHAR(20) not null,            --�������롾ƽ�����䡿
    coOrgNo           VARCHAR(20) not null,            --�����л����š�ƽ�����䡿
    workDate          VARCHAR(8) not null,             --ҵ������
    workSerialNo        VARCHAR(32) not null,          --ҵ����ˮ��
    maintainDate      VARCHAR(8),                      --ά������                       
    maintainTime      VARCHAR(6),                      --ά��ʱ��                       
    extFld1           VARCHAR(64),                     --��չ1
    extFld2           VARCHAR(64),                     --��չ2
    extFld3           VARCHAR(255) ,                    --��չ3
    extFld4           VARCHAR(255)                     --��չ4
);

alter table PABYBH_ORGCFG add constraint PK_PABYBH_ORGCFG primary key (coBankNo);

create unique index K_PABYBH_ORGCFG_1 on PABYBH_ORGCFG 
(
bankOrgNo
);


--������Կ��Ϣ��
drop table PABYBH_SECKEY;
create table PABYBH_SECKEY
(
    coBankNo         VARCHAR(12) not null,               --�����к�  
    encryptIp           VARCHAR(32) not null,            --����ƽ̨��ַ           
    encryptPort        VARCHAR(32) not null,            --����ƽ̨�˿�
    encryptSysId      VARCHAR(32) not null,            --����ƽ̨ϵͳID
    encryptExtId       VARCHAR(32) not null,            --����ƽ̨�ⲿID
    zmk              	   VARCHAR(255),                      --ZMK
    zak               	   VARCHAR(255) not null,             --ZAK
    iepZpk                 VARCHAR(255) not null,           --ZPK ƽ��
    counterZpk          VARCHAR(255) not null,       --ZPK ����
    hostZpk               VARCHAR(255) not null,          --ZPK ������
    extFld1           VARCHAR(64),                       --��չ1
    extFld2           VARCHAR(64),                       --��չ2
    extFld3           VARCHAR(255),                     --��չ3
    extFld4           VARCHAR(255)                       --��չ4
);                                                       

 
-------------------------------------------------------------------------------- 
-- ����: PABYBH_DLCG_APPOINT
-- ����: �������Ԥָ����ϵ�� 
-------------------------------------------------------------------------------- 
drop table PABYBH_SIGN;
create table PABYBH_SIGN
(
    signDate        VARCHAR(8) not null,                    --ָ������  aptDate     
    signTime        VARCHAR(6),                             --ָ��ʱ��  apt_tmie
    coBankNo        VARCHAR(12) not null,                   --�����к�                       
    coBankName      VARCHAR(100),                           --����������           
    acctNo          VARCHAR(32) not null,                   --�����˺� 
    oldAcctNo          VARCHAR(32) not null,                --�������˺�     
    certType        VARCHAR(2) not null,                    --֤������      
    certNo          VARCHAR(32) not null,                   --֤������  
    custType          VARCHAR(2),                           --�ͻ�����      
    custName          VARCHAR(120),                         --�ͻ�����      
    stockCode       VARCHAR(8) not null,                    --ȯ�̴���      
    capitalAcctNo   VARCHAR(30) not null,                   --֤ȯ�ʽ�̨�˺� 
    svrCode       			VARCHAR(6) not null,											--�������
   	curr             VARCHAR(3), 														--����
--   	openfare        VARCHAR(10),                          --����������
--    areaCode        VARCHAR(20),                          --�������� 
--    gradeid         VARCHAR(1),                           --�ͻ����� 
    custManagerId   VARCHAR(20),                            --�ͻ������
    custManagerName  VARCHAR(20),                           --�ͻ���������
    openOrg          VARCHAR(10),                           --��������� 
   	busiType			   VARCHAR(1),														--ҵ������ 
--   	trantype        VARCHAR(2),                           --����ѡ�� 1�¿���ǩԼ  2-�ֻƽ�ǩԼ     
    stat            VARCHAR(1),                             --ǩԼ״̬'9-��У��1-ǩԼ2-��Լ'  
    hostStat        VARCHAR(1),                             --����ǩԼ״̬'9-��У��1-ǩԼ2-��Լ'  
    hostDate        VARCHAR(8),                                --����ǩԼ����
    hostSerialNo    VARCHAR(20),                            --������ˮ   
    chkFlag          VARCHAR(1),                            --���˱�־'0-δ����1-�Ѷ���'      
    updateDate      VARCHAR(8),                             --��������      
    updateTime      VARCHAR(6),                             --����ʱ��      
    transOrg         VARCHAR(10),                           --���׻���      
    transOper        VARCHAR(20),                           --���׹�Ա 
    authOrg         VARCHAR(10),                            --��Ȩ���� 
    authOper           VARCHAR(20),                         --��Ȩ��Ա       
    memo             VARCHAR(40),                           --��ע          
    extFld1          VARCHAR(32),                           --�����ֶ�1   
    extFld2          VARCHAR(32),                           --�����ֶ�2   
    extFld3          VARCHAR(64),                           --�����ֶ�3  
    extFld4          VARCHAR(64),                           --�����ֶ�4 
    extFld5          VARCHAR(64),                           --�����ֶ�5  
    extFld6          VARCHAR(64)                         --�����ֶ�6 
   -- CONSTRAINT PK_PABYBH_SIGN PRIMARY KEY (stockCode, capitalAcctNo, svrCode)
);
alter table PABYBH_SIGN add constraint PK_PABYBH_SIGN primary key (stockCode, capitalAcctNo, svrCode);
-----------------------
--�ͻ���Ϣ�� PABYBH_CUSTINFO
-----------------------
drop table PABYBH_CUSTINFO;
create table PABYBH_CUSTINFO
(
		certType        VARCHAR(2) not null,                   --֤������     
    certNo          VARCHAR(32) not null,                  --֤������      
    custType        VARCHAR(2),                            --�ͻ�����      
    custName        VARCHAR(120),                          --�ͻ����� 
 		post          VARCHAR(6),                              --��������      
    addr          VARCHAR(128),                            --��ϵ��ַ      
    email         VARCHAR(120),                            --�����ʼ���ַ  
    phone         VARCHAR(16),                             --��ϵ�绰      
    mobile        VARCHAR(11),                             --�ƶ��绰      
    fax           VARCHAR(16),                             --����          
    updateDate   VARCHAR(8),                               --��������      
    updateTime   VARCHAR(6),                               --����ʱ��   
    createDate   VARCHAR(8)	,													     --��������
		createTime   VARCHAR(6)	,															 --����ʱ��
		extFld1       VARCHAR(32),                             --�����ֶ�1   
    extFld2       VARCHAR(64),                             --�����ֶ�2   
    extFld3       VARCHAR(64)                            --�����ֶ�3  
		 --CONSTRAINT PK_PABYBH_CUSTINFO PRIMARY KEY (certType, certNo)
);
 alter table PABYBH_CUSTINFO add constraint PK_PABYBH_CUSTINFO primary key (certType, certNo);
-------------------------------------------------------------------------------- 
-- ����: PABYBH_SVRINFO
-- ����:  ҵ����Ϣ
-------------------------------------------------------------------------------- 
drop table PABYBH_SVRINFO;
create table PABYBH_SVRINFO
(
  svrCode      VARCHAR(6) not null,                     --�������	            
  svrName      VARCHAR(100) not null,                   --��������             
--  workDate     VARCHAR(10) not null,                    --��������              
  workTime     VARCHAR(32),                             --ҵ��չʱ���        
  svrStatus    VARCHAR(1) not null,                     --����״̬              
  extFld1      VARCHAR(128),                            --�����ֶ�1             
  extFld2      VARCHAR(128),                            --�����ֶ�2                          
  extFld3      VARCHAR(128)                             --�����ֶ�3
);
 
alter table PABYBH_SVRINFO add constraint PK_PABYBH_SVRINFO primary key (svrCode);
 
-------------------------------------------------------------------------------- 
-- ����: PABYBHTransCTL
-- ����: ���Ľ��׿��Ʊ�
-------------------------------------------------------------------------------- 
drop table PABYBH_PABTRANSCTL;
create table PABYBH_PABTRANSCTL
(
  transCode VARCHAR(10) not null,                       --���״���   
  transName VARCHAR(100) not null,                      --��������   
  svrCode   VARCHAR(6) not null,                        --�������   
  openFlag  VARCHAR(1) not null,                        --���ر�־'0--��1--��'  
  macFlag   VARCHAR(1) not null,                        --MACУ���־'0--��1--��'
  extFld1   VARCHAR(32),                                --�����ֶ�1  
  extFld2   VARCHAR(32),                                --�����ֶ�2  
  extFld3   VARCHAR(32)                                 --�����ֶ�3  
);

alter table PABYBH_PABTRANSCTL add constraint PK_PABYBH_PABTRANSCTL primary key (transCode, svrCode);
 
-------------------------------------------------------------------------------- 
-- ����: PABYBHSerial
-- ����: ������ˮ��
-------------------------------------------------------------------------------- 
drop table PABYBH_SERIAL;
create table PABYBH_SERIAL
(
    transDate           VARCHAR(8) not null,        --ƽ̨����      
    transSerialNo        VARCHAR(20) not null,      --ƽ̨��ˮ��
    oritransDate           VARCHAR(8) ,             --ԭƽ̨����      
    oriTransSerialNo       VARCHAR(20) ,            --ԭƽ̨��ˮ��
    transTime           VARCHAR(8) not null,        --����ʱ��
    workDate            VARCHAR(8),                 --ҵ������
    workSerialNo        VARCHAR(20),                --ҵ����ˮ��
    reqDate             VARCHAR(8) not null,        --��������
    reqSerialNo          VARCHAR(20) not null,      --������ˮ��
    clusterNodeName     VARCHAR(30),                --��Ⱥ�ڵ��������
    clusterNodeIp       VARCHAR(20),                --��Ⱥ�ڵ����IP 
    coBankNo            VARCHAR(12) not null,       --�����к�                       
    coBankName          VARCHAR(100),               --���������� 
    transOrg            VARCHAR(10),                --���׻���      
    transOper           VARCHAR(10),                --���׹�Ա
    authOrg            VARCHAR(10),                 --��Ȩ����      
    authOper           VARCHAR(10),                 --��Ȩ��Ա
    cnlType             VARCHAR(5),                 --�������� 
    termEquiNo          VARCHAR(20),                --�ն��豸���
    transCode           VARCHAR(12),                --���״��� 
    transCode1           VARCHAR(1),                      --���ӽ��״��� 0 ���� 1 ��� 2���������� 3 ���򹤱���
    cuAcounType          VARCHAR(1),                       --�����˱�־ 0-���� 1-����
    transName           VARCHAR(100),               --��������   
    capitalType        VARCHAR(1),                  --�ʽ�����,0 ---ת��1--- ת��    
    svrCode             VARCHAR(10),                --�������   (��ܡ��ƽ��)
    custNo              VARCHAR(20),                --�ͻ���
    custName           VARCHAR(80),                 --�ͻ�����
    custType            VARCHAR(2),                 --�ͻ����� 
    acctNo             VARCHAR(32),                 --�����˺�         
    acctNo2             VARCHAR(32),                --�ʺ�2   �������˻�  
    capitalAcctNo       VARCHAR(32),                --�ʽ��ʺ�    
    transAmt             DECIMAL(16,2),                --���׽��      
    amt2                 DECIMAL(16,2),                --���2         
    amt3                DECIMAL(16,2),                --���3 
    curr                VARCHAR(3),                 --����
    cashFlag            VARCHAR(1),                 --�����ʶ 
    iepSvrCode         VARCHAR(8),                  --��Eͨ������� 
    iepTransCode       VARCHAR(16),                 --��Eͨ���״��� 
    iepBsiDate         VARCHAR(8),                  --��Eͨҵ������
    iepTraDate         VARCHAR(8),                  --��Eͨ�������� 
    iepSerialNo        VARCHAR(32),                 --��Eͨ��ˮ��   ����
    oriIepBsiDate     VARCHAR(8),                   --ԭ��Eͨҵ������
    oriIepSerialNo    VARCHAR(32),                  --ԭ��Eͨ��ˮ��         
    iepRespCode        VARCHAR(12),                 --��Eͨ��Ӧ���� 
    iepRespMsg         VARCHAR(120),                --��Eͨ��Ӧ��Ϣ            
    hostBsiDate        VARCHAR(8),                  --������������  
    hostSerialNo       VARCHAR(32),                 --������ˮ��   
    hostTransCode      VARCHAR(16),                 --�������״���     
    hostRespCode       VARCHAR(12),                 --������Ӧ����  
    hostRespMsg        VARCHAR(120),                --������Ӧ��Ϣ  
    respCode            VARCHAR(10),                --��Ӧ��        
    respMsg             VARCHAR(120),               --��Ӧ��Ϣ     
    iepStat                VARCHAR(1),              --���Ľ���״̬'0�ɹ� 1ʧ�� 6״̬δ֪ 7������ 8������ 9��ʼ'      
    hostStat                VARCHAR(1),             --���Ľ���״̬'0�ɹ� 1ʧ�� 6״̬δ֪ 7������ 8������ 9��ʼ'      
    stat                VARCHAR(1),                 --����״̬'0�ɹ� 1ʧ�� 6״̬δ֪ 7������ 8������ 9��ʼ'   ԭʼ->0-�ɹ���00-�ɹ�����һλ��ʾ���ģ��ڶ�λ��ʾ��3����0--�ɹ�2--ʧ��8--δ���ʹ�����9--��ʼ'          
    oriStat             VARCHAR(1),                       --ƽ̨ͬ������״̬ǰԭ״̬ '0�ɹ� 1ʧ�� 6״̬δ֪ 7������ 8������ 9��ʼ'
    certType            VARCHAR(2),                 --֤������    
    certNo              VARCHAR(32),                --֤������
    chkFlag             VARCHAR(1),                 --���˱�־,0-δ����1-�Ѷ�ƽ2-ƽ����3-���Ķ�4-˫���޼��� 
    memo                  VARCHAR(128),             --��ע
    extFld1             VARCHAR(32),                --�����ֶ�1     
    extFld2             VARCHAR(64),                --�����ֶ�2     
    extFld3             VARCHAR(128)                --�����ֶ�3     
);

alter table PABYBH_SERIAL add constraint PK_PABYBH_SERIAL primary key (transDate, transSerialNo);

create unique index K_PABYBH_SERIAL_1 on PABYBH_SERIAL 
(
iepSerialNo
);
create unique index K_PABYBH_SERIAL_2 on PABYBH_SERIAL 
(
reqDate,reqSerialNo
);
-------------------------------------------------------------------------------- 
-- ����: PABYBH_BBSJ
-- ����: �������� ���ݲ���Ҫ��
-------------------------------------------------------------------------------- 
DROP TABLE PABYBH_BBSJ;
CREATE TABLE PABYBH_BBSJ                                                                               
(                                                                                                     
    transDate       VARCHAR (8)  NOT NULL,      --��������                                            
    transOrg        VARCHAR (10) NOT NULL,      --���׻���                                             
    transOrgNAME    VARCHAR(256) NOT NULL,      --���׻�������      
    DLHJKH          VARCHAR (17),               --����ƽ𿪻�                                         
    DLHJXH          VARCHAR (17),               --����ƽ�����                                         
    DLHJCL          VARCHAR (17),               --����ƽ����                                         
    DLCGKH          VARCHAR (17),               --�����ܿ���                                         
    DLCGXH          VARCHAR (17),               --����������                                         
    DLCGCL          VARCHAR (17),               --�����ܴ���                                         
    DLHJZRBS        INTEGER,               --����ƽ�ת�����                                     
    DLHJZRJE         DECIMAL(16,2) ,               --����ƽ�ת����                                     
    DLHJZCBS        INTEGER,               --����ƽ�ת������                                     
    DLHJZCJE         DECIMAL(16,2),               --����ƽ�ת�����                                     
    DLCGZRBS       INTEGER,               --������ת�����                                     
    DLCGZRJE         DECIMAL(16,2),               --������ת����                                     
    DLCGZCBS       INTEGER,               --������ת������                                     
    DLCGZCJE        DECIMAL(16,2)             --������ת�����                                     
	--CONSTRAINT PK_PABYBH_BBSJ PRIMARY KEY (transDate, transOrg)                                       
);                                                                                                                                            
                                                                 
alter table PABYBH_BBSJ add constraint PK_PABYBH_BBSJ primary key (transDate, transOrg);

 
--create index idx_PABYBH_DLHJ_ZHBG_1 ON PABYBH_BBSJ(CLRQ, acctNo, stat);

-------------------------------------------------------------------------------- 
-- ����: PABYBH_CHECKCTL
-- ����: ���˿��Ʊ�
-------------------------------------------------------------------------------- 
DROP TABLE PABYBH_CHECKCTL;
create table PABYBH_CHECKCTL
(
    chTransDate             VARCHAR(8),                    --���˳�ʼ��������      
    chTransNo               VARCHAR(20),                   --���˳�ʼ������ˮ��    
    checkDate              VARCHAR(8) not null,            --��������   
    coBankNo               VARCHAR(12) not null,           --�����к�
    svrCode                VARCHAR(6) not null,            --������ ҵ������ 
    msgType                VARCHAR(50) not null,           --��������0�ʽ���1�˻��ࣨ������2�˻��ࣨ��Լ&������
    totalCount             INTEGER,                        --�ܱ���
    totalAmt               DECIMAL(16,2),                   --�ܽ��
    backTotalCount         INTEGER,                        --�����ܱ���
    backTotalAmt           DECIMAL(16,2),                   --�����ܽ��
    localTotalCount         INTEGER,                       --ƽ̨�ܱ���
    localTotalAmt           DECIMAL(16,2),                  --ƽ̨�ܽ��
    localBackTotalCount         INTEGER,                   --ƽ̨�����ܱ���
    localBackTotalAmt           DECIMAL(16,2),              --ƽ̨�����ܽ��
    hostTotalCount         INTEGER,                        --�����ܱ���
    hostTotalAmt           DECIMAL(16,2),                   --�����ܽ��
    hostBackTotalCount         INTEGER,                    --���������ܱ���
    hostBackTotalAmt           DECIMAL(16,2),               --���������ܽ��
    netAmt                DECIMAL(16,2),                    --������
    netType               VARCHAR(1),                            --�����  '0���� 1֧��'
    iepChkFile            VARCHAR(100),                    --ƽ�������ļ���
    hostChkFile           VARCHAR(100),                    --���������ļ���
    execTime               VARCHAR(30),                    --ִ��ʱ��'��ʼʱ��|����ʱ��|'
    execStep               VARCHAR(2),                     --ִ�в���'0-��ȡƽ��������Ϣ 1-ƽ�������ļ���� 2-ƽ����ϸ������� 3-�����ύ���� 4-��ȡ���������ļ�,�������ɶ����ļ���� 5-������ϸ�������'
    execStat               VARCHAR(1),                     --ִ��״̬'1-�ɹ� 2-ʧ��9-������'
    chkDetailResult           VARCHAR(1),                --��ϸ���˽��'0 δ���� 1 ����ƽ 2���˲�ƽ 3���˳��� 9 ������'
    chkPabtotalResult           VARCHAR(1),              --���Ķ����˽��'0 δ���� 1 ����ƽ 2���˲�ƽ 3���˳��� 9 ������'
    chkHosttotalResult           VARCHAR(1),             --���Ķ����˽��'0 δ���� 1 ����ƽ 2���˲�ƽ 3���˳��� 9 ������'
    transDate             VARCHAR(8),                      --��������
    transSerialNo         VARCHAR(20),                     --ǰ����ˮ��
    transOrg              VARCHAR(10),                     --���׻���      
    transOper             VARCHAR(10),                     --���׹�Ա
    respCode              VARCHAR(10),                     --��Ӧ��        
    respMsg               VARCHAR(120),                    --��Ӧ��Ϣ
    stat                  VARCHAR(1),                      --����״̬ 0�ɹ� 1ʧ�� 6״̬δ֪ 7������ 8������ 9��ʼ
    extFld1               VARCHAR(32),                     --�����ֶ�1
    extFld2               VARCHAR(64),                     --�����ֶ�2
    extFld3               VARCHAR(128)                   --�����ֶ�3
   -- CONSTRAINT PK_PABYBH_CHECKCTL PRIMARY KEY (checkDate, coBankNo,svrCode,msgType)    
);

alter table PABYBH_CHECKCTL add constraint PK_PABYBH_CHECKCTL primary key (checkDate, coBankNo,svrCode,msgType);
-- ����: PABYBH_DLCG_CHKINFO
-- ����: ƽ�����д�ܶ�����ϸ�� 
-------------------------------------------------------------------------------- 
DROP TABLE PABYBH_DEPCHKINFO;
create table PABYBH_DEPCHKINFO
(
    checkDate           VARCHAR(8) not null,                --��������
    transDate           VARCHAR(8) not null,                --�������� 
    transTime           VARCHAR(6),                         --����ʱ��      
    transferType        VARCHAR(1),                         --�ʽ�����'0--��ת֤1--֤ת��'      
    acctNo              VARCHAR(32),                        --�����˺�      
    stockCode           VARCHAR(8) not null,                --ȯ�̴���      
    capitalAcctNo       VARCHAR(30) not null,               --֤ȯ�ʽ�̨�˺�
    amt                 DECIMAL(16,2),                        --���          
    workSerialNo      VARCHAR(30),                          --��������ˮ��  
    iepSerialNo       VARCHAR(30) not null,                 --��Eͨ��ˮ��   
    coBankNo            VARCHAR(12) not null,               --�����к�
    extFld1             VARCHAR(32),                        --�����ֶ�1     
    extFld2             VARCHAR(64)                       --�����ֶ�2    
   -- CONSTRAINT PK_PABYBH_DEPCHKINFO PRIMARY KEY (checkDate, iepSerialNo)  
);
 alter table PABYBH_DEPCHKINFO add constraint PK_PABYBH_DEPCHKINFO primary key (checkDate, iepSerialNo);
create index IDX_PABYBH_DEPCHKINFO_1 on PABYBH_DEPCHKINFO (checkDate, workSerialNo, coBankNo);


-------------------------------------------------------------------------------- 
-- ����: PABYBH_DLCG_CHKBPINFO
-- ����: ��ܶ��˲�ƽ��ϸ��
-------------------------------------------------------------------------------- 
DROP TABLE PABYBH_DLCG_CHKBPINFO;
create table PABYBH_DLCG_CHKBPINFO
(
    checkDate             VARCHAR(8) not null,                --��������  
    coBankNo              VARCHAR(12) not null,               --�����к�   
    transferType          VARCHAR(1),                         --�ʽ�����'0--������ת֤1--֤ת�������'      
    stockCode             VARCHAR(8),                         --ȯ�̴���       
    capitalAcctNo          VARCHAR(30),                       --֤ȯ�ʽ�̨�˺�        
    workSerialNo          VARCHAR(30),                        --��������ˮ��  
    bankStat              VARCHAR(1),                               --������״̬
    bankAcctNo            VARCHAR(32),                        --ƽ̨�����˺� 
    bankAmt               DECIMAL(16,2),                       --ƽ̨���׽��
    bankTranscode		VARCHAR(8),  								      --ƽ̨���״���
    iepSerialNo           VARCHAR(30),                        --��Eͨ��ˮ��
    iepStat               VARCHAR(1),                               --��Eͨ״̬
    iepAcctNo              VARCHAR(32),                       --��Eͨ�����˺� 
    iepAmt                DECIMAL(16,2),                       --��Eͨ���׽�� 
    iepTranscode					 VARCHAR(8),  								      --��Eͨ���״���  
    hostSerialNo           VARCHAR(30),                       --������ˮ��
    hostStat                VARCHAR(1),                             --����״̬    
    hostAcctNo               VARCHAR(32),                     --���������˺�
    hostAmt                DECIMAL(16,2),                      --�������׽��
    hostTranscode					 VARCHAR(8),  								      --�������״���  
    checkStat                VARCHAR(1),                      --���˽����־,0-δ����1-�Ѷ�ƽ2-ƽ����3-���Ķ�  
    stDesc                  VARCHAR(120),                     --���˽������      
    adjustStat               VARCHAR(1),                           --����״̬ 0-�ɹ� 1-ʧ�� 7-��ʱ 9-��ʼ    
    adjustTransOrg            VARCHAR(10),                    --���˽��׻���      
    adjustTransOper           VARCHAR(10),                    --���˽��׹�Ա
    adjustDate                VARCHAR(8),                     --��������
    adjustSerialno            VARCHAR(32),                    --����ҵ����ˮ��
    adjustHostBsidate        VARCHAR(8),                      --������������  
    adjustHostSerialno       VARCHAR(32),                     --������ˮ��
    adjustRespCode            VARCHAR(10),                    --������Ӧ��
    adjustRespMsg             VARCHAR(120),                   --������Ӧ��Ϣ
    extFld1                   VARCHAR(32),                    --�����ֶ�1     
    extFld2                   VARCHAR(64)                     --�����ֶ�2   
--   CONSTRAINT PK_PABYBH_DLCG_CHKBPINFO PRIMARY KEY (transDate, bankSerialNo)    
);
 
-- alter table PABYBH_DLCG_CHKBPINFO add constraint PK_PABYBH_DLCG_CHKBPINFO primary key (checkDate, );
-------------------------------------------------------------------------------- 
-- ����: PABYBHHostCHKINFO
-- ����:  ����������Ϣ  
-------------------------------------------------------------------------------- 
DROP TABLE PABYBH_HOSCHKINFO;
create table PABYBH_HOSCHKINFO
(
    coBankNo            VARCHAR(10),                            --�����к�
    checkDate             VARCHAR(8),                           --��������
    workSerialNo              VARCHAR(32)  not null,            --ƽ̨ҵ����ˮ��
    hostDate            VARCHAR(8) not null,                    --��������
    hostSerialNo             VARCHAR(32) not null,              --������ˮ��
    hostTransCode       VARCHAR(16),                            --���Ľ��״���  
    acctNo              VARCHAR(32),                            --�˺�
    transAmt             DECIMAL(16,2),                            --���׽��
    transfare           DECIMAL(16,2),                           --������
    cashFlag            VARCHAR(1),                             --��ת��־1-�ֽ� 2-ת��
    stat                VARCHAR(1),                             --����״̬0-���� 7-������ 8-������ 1-ʧ��    
    cdFlag              VARCHAR(1),                             --�����־   
    svrType          VARCHAR(10),                               --ҵ������
    remarkcode          VARCHAR(32),                            --ժҪ��
    remark              VARCHAR(50),                            --ժҪ��Ϣ
    transBranchNo       VARCHAR(10),                            --��������
    transOrg          VARCHAR(10),                              --���׻���
    transOper         VARCHAR(10),                              --���׹�Ա
    joinChkFlag             VARCHAR(1),                         --������˱�־��0-�����룬1-����
    extFld1             VARCHAR(32),                            --�����ֶ�1     
    extFld2             VARCHAR(64),                            --�����ֶ�2     
    extFld3             VARCHAR(64)                           --�����ֶ�3  
   -- CONSTRAINT PK_PABYBH_HOSCHKINFO PRIMARY KEY (hostdate, hostSerialNo)   
);
 alter table PABYBH_HOSCHKINFO add constraint PK_PABYBH_HOSCHKINFO primary key (hostdate, hostSerialNo);
create index IDX_PABYBH_HOSCHKINFO_1 on PABYBH_HOSCHKINFO (coBankNo, checkDate);

create index IDX_PABYBH_HOSCHKINFO_2 on PABYBH_HOSCHKINFO (coBankNo, checkDate, workSerialNo);


COMMIT WORK;

--CONNECT RESET;

--TERMINATE;


