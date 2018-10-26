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
    workDate            VARCHAR(8) not null,        --ҵ������
    workSerialNo        VARCHAR(20) not null,       --ҵ����ˮ��
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
    stockCode             VARCHAR(8),                         --ȯ�̴��� 
    capitalType        VARCHAR(1),                  --�ʽ�����,0 ---ת��1--- ת��    
    svrCode             VARCHAR(10),                --�������   (��ܡ��ƽ��)
    custNo              VARCHAR(20),                --�ͻ���
    custName           VARCHAR(80),                 --�ͻ�����
    custType            VARCHAR(2),                 --�ͻ����� 
    acctNo             VARCHAR(32),                 --�����˺�         
    oriAcctNo             VARCHAR(32),                 --�����˺�
    acctNo2             VARCHAR(32),                --�ʺ�2   �������˻�  
    capitalAcctNo       VARCHAR(32),                --�ʽ��ʺ�    
    transAmt             DECIMAL(16,2),                --���׽��      
    oriTransAmt             DECIMAL(16,2),                --���׽��
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
