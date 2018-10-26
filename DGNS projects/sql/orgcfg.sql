drop table PABYBH_ORGCFG;
create table PABYBH_ORGCFG
(                
    coBankNo          VARCHAR(12) not null,            --�����кš�ƽ�����䡿                      
    coBankName        VARCHAR(100) ,           --����������                     
    custManagerNo    VARCHAR(10) not null,             --ƽ������ͻ�����š�ƽ�����䡿    
    acct1             VARCHAR(32),            --ͷ���˻�
    acct1Name         VARCHAR(60),            --ͷ���˻�����
    acct2             VARCHAR(32),            --�ڲ������˻�
    acct2Name         VARCHAR(60),            --�ڲ������˻����� 
    signStatus        VARCHAR(1) not null,             --ǩ��״̬��0-ǩ����1-ǩ��
    areaCode          VARCHAR(20),            --�������롾ƽ�����䡿
    coOrgNo           VARCHAR(20),            --�����л����š�ƽ�����䡿
    workDate          VARCHAR(8) not null,             --ҵ������
    workSerialNo        VARCHAR(32) ,          --ҵ����ˮ��
    maintainDate      VARCHAR(8),                      --ά������                       
    maintainTime      VARCHAR(6),                      --ά��ʱ��                       
    extFld1           VARCHAR(64),                     --��չ1
    extFld2           VARCHAR(64),                     --��չ2
    extFld3           VARCHAR(255) ,                    --��չ3
    extFld4           VARCHAR(255)                     --��չ4
);

alter table PABYBH_ORGCFG add constraint PK_PABYBH_ORGCFG primary key (coBankNo);