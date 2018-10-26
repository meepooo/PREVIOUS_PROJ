drop table ICPS_JB_APPLYINFO;
drop table ICPS_JB_BANKINFO;
drop table ICPS_JB_ZMINFO
drop table ICPS_JB_EXTINFO;
drop table ICPS_JB_RESULTINFO;
drop table ICPS_JB_IDCODE2ADDR;


/*==============================================================*/
/* Table: ICPS_JB_APPLYINFO                                     */
/*==============================================================*/
create table ICPS_JB_APPLYINFO
(
    ptrq                   VARCHAR(8) not null,
    ptlsh                  VARCHAR(10) not null,
    version                CHAR(8) not null,
    appid                  VARCHAR(32)  not null,
    function               VARCHAR(16)  not null,
    reqtimezone            VARCHAR(32)  not null,
    reqtime                VARCHAR(16)  not null,
    reqmsgid               VARCHAR(64)  not null,
    signtype               VARCHAR(16)  not null,
    inputcharset           VARCHAR(16)  not null,
    reserve                VARCHAR(32),
    applyno                VARCHAR(64)  not null,
    certtype               CHAR(2)  not null,
    certno                 VARCHAR(32)  not null,
    certvalidenddate       VARCHAR(8),
    name                   VARCHAR(32)  not null,
    customerno             VARCHAR(64)  not null,
    mobileno               VARCHAR(32)  not null,
    occupation             CHAR(1),
    address                VARCHAR(256),
    city                   VARCHAR(20),
    prov                   VARCHAR(20),
    area                   VARCHAR(20),
    zmauthflag             CHAR(1),
    hasjbadmit             CHAR(1)   not null,
    applystat              CHAR(1),
    reqcode                CHAR(6),
    reqmsg                 VARCHAR(255),
    reqdate                VARCHAR(8),
    reqtime1               VARCHAR(10),
    isadmit                CHAR(1),
    creditno               VARCHAR(32),
    creditamt              VARCHAR(18),
    creditrate             VARCHAR(8),
    refusecode             VARCHAR(64),
    refusemsg              VARCHAR(1024),
    respcode               CHAR(6),
    respmsg                VARCHAR(255),
    retry                  CHAR(1),
    resultstat             CHAR(1),
    respdate               VARCHAR(8),
    resptime               VARCHAR(10)
);
comment on table ICPS_JB_APPLYINFO is '����������Ϣ��';
comment on column ICPS_JB_APPLYINFO.ptrq is 'ƽ̨����';
comment on column ICPS_JB_APPLYINFO.ptlsh is 'ƽ̨��ˮ��';
comment on column ICPS_JB_APPLYINFO.version is '�汾��';
comment on column ICPS_JB_APPLYINFO.appid is 'ϵͳ��ʶ';
comment on column ICPS_JB_APPLYINFO.function is '���ױ���';
comment on column ICPS_JB_APPLYINFO.reqtimezone is '���ͷ�����ʱ��';
comment on column ICPS_JB_APPLYINFO.reqtime is '���ķ���ʱ��';
comment on column ICPS_JB_APPLYINFO.reqmsgid is '������Ψһ��ʾ';
comment on column ICPS_JB_APPLYINFO.signtype is 'ǩ���㷨����';
comment on column ICPS_JB_APPLYINFO.inputcharset is '�����ַ�����';
comment on column ICPS_JB_APPLYINFO.reserve is 'Ԥ����';
comment on column ICPS_JB_APPLYINFO.applyno is '���뵥��';
comment on column ICPS_JB_APPLYINFO.certtype is '֤������';
comment on column ICPS_JB_APPLYINFO.certno is '֤������';
comment on column ICPS_JB_APPLYINFO.certvalidenddate is '֤����Ч��';
comment on column ICPS_JB_APPLYINFO.name is '����';
comment on column ICPS_JB_APPLYINFO.customerno   is '�ͻ����';
comment on column ICPS_JB_APPLYINFO.mobileno     is '�ֻ���';
comment on column ICPS_JB_APPLYINFO.occupation   is 'ְҵ';
comment on column ICPS_JB_APPLYINFO.address      is '��ϸ��ַ';
comment on column ICPS_JB_APPLYINFO.city         is '����';
comment on column ICPS_JB_APPLYINFO.prov         is 'ʡ��';
comment on column ICPS_JB_APPLYINFO.area         is '����';
comment on column ICPS_JB_APPLYINFO.zmauthflag   is '֥����Ȩ�ɹ���ʾ';
comment on column ICPS_JB_APPLYINFO.hasjbadmit   is '�Ƿ�֮ǰ���н��¶��';
comment on column ICPS_JB_APPLYINFO.applystat    is '����״̬ 0-�ɹ� 1-ʧ�� 2-������ 3-�ѷ���С΢��ѯ 9-��ʼ';
comment on column ICPS_JB_APPLYINFO.reqcode      is '������Ӧ��';
comment on column ICPS_JB_APPLYINFO.reqmsg       is '������Ӧ��Ϣ';
comment on column ICPS_JB_APPLYINFO.reqdate      is '��������';
comment on column ICPS_JB_APPLYINFO.reqtime1     is '����ʱ��';
comment on column ICPS_JB_APPLYINFO.isadmit      is '�Ƿ��Ƽ�׼��';
comment on column ICPS_JB_APPLYINFO.creditno     is '���ű��';
comment on column ICPS_JB_APPLYINFO.creditamt    is '�Ƽ�׼��ʱ���Ƽ��Ķ��';
comment on column ICPS_JB_APPLYINFO.creditrate   is '��׼��ʱ���Ƽ�������';
comment on column ICPS_JB_APPLYINFO.refusecode   is '�Ƽ��ܾ�ʱ���ܾ���';
comment on column ICPS_JB_APPLYINFO.refusemsg    is '�Ƽ��ܾ�ʱ���ܾ�ԭ��';
comment on column ICPS_JB_APPLYINFO.respcode     is '������Ӧ��';
comment on column ICPS_JB_APPLYINFO.respmsg      is '������Ӧ��Ϣ';
comment on column ICPS_JB_APPLYINFO.retry        is '�Ƿ�����';
comment on column ICPS_JB_APPLYINFO.resultstat   is '�����״̬ 0-�ɹ� 1-ʧ�� 2-������ 9-��ʼ';
comment on column ICPS_JB_APPLYINFO.respdate     is '��������';
comment on column ICPS_JB_APPLYINFO.resptime     is '����ʱ��';

/*==============================================================*/
/* Table: ICPS_JB_BANKINFO                                     */
/*==============================================================*/
create table ICPS_JB_BANKINFO
(
    ptrq            VARCHAR(8) not null,
    ptlsh           VARCHAR(10) not null,
    reqmsgid        VARCHAR(64) not null,
    applyno         VARCHAR(64) not null,
    isexistcust     CHAR(1),
    isexistdebtcust         CHAR(1),   
    balance                 VARCHAR(18),
    avgbalancelast3days     VARCHAR(18),
    avgbalancelast6days     VARCHAR(18),
    incomelast3m            VARCHAR(18),       
    paylast3m               VARCHAR(18),          
    incomelast6m            VARCHAR(18),       
    paylast6m               VARCHAR(18),          
    isexistccust            CHAR(1),        
    currccamt               VARCHAR(18),          
    currdisburseccamt       VARCHAR(18),  
    isexistfincust          CHAR(1),      
    finbalance              VARCHAR(18),         
    avgfinballast6m         VARCHAR(18),    
    isexistinsurancecus     CHAR(1), 
    isexistloancust         CHAR(1),     
    operationloanbal        VARCHAR(18),   
    personalcreditbal       VARCHAR(18),  
    autoloanbal             VARCHAR(18),        
    autoasset               VARCHAR(18),          
    houseloanbal            VARCHAR(18),       
    houseasset              VARCHAR(18),         
    isstockcust             CHAR(1),         
    isthirddepository       CHAR(1),   
    ispayrollcust           CHAR(1),       
    issocialsecuritycus     CHAR(1), 
    islifepaymentcust       CHAR(1),   
    incorporation           VARCHAR(120),     
    incorigin               CHAR(1),        
    position                VARCHAR(120),       
    positionorigin          CHAR(1),   
    industry                VARCHAR(120),       
    industryorigin          CHAR(1),   
    workyears               CHAR(3),        
    workyearsorigin         CHAR(1),  
    income                  VARCHAR(18),          
    incomeorigin          CHAR(1),     
    marriagestatus        CHAR(1),   
    marriageorigin        CHAR(1),   
    isoperation           CHAR(1),      
    operationorigin       CHAR(1),  
    isinnerblackcust      CHAR(1), 
    ispolicecertified     CHAR(1),
    iscourtexeccust       CHAR(1),  
    isqryhousefund        CHAR(1),   
    fundqrydate           VARCHAR(8),      
    fundmonthamt          VARCHAR(18),    
    fundaccountdate       VARCHAR(8),  
    fundmonthslast6m      CHAR(3), 
    fundamtlast6m         VARCHAR(18),   
    fundtotalmonths       CHAR(3),  
    fundtotalamt          VARCHAR(18),    
    fundmaxamt            VARCHAR(18),      
    isqrysocialsec        CHAR(1),   
    socialqrydate         VARCHAR(8),    
    pensionqrymonthamt    VARCHAR(18), 
    pensionaccountdate    VARCHAR(8),  
    pensionmonthslast6m   CHAR(3), 
    pensionamtlast6m      VARCHAR(18),   
    pensiontotalmonths    CHAR(3),  
    pensiontotalamt       VARCHAR(18),    
    mdcmonthamt           VARCHAR(18),        
    mdcaccountdate        VARCHAR(8),      
    mdcmonthslast6m       CHAR(3),     
    mdcamtlast6m          VARCHAR(18),       
    mdctotalmonths        CHAR(3),      
    mdctotalamt           VARCHAR(18),        
    isqrydegree           CHAR(1),         
    schoolname            VARCHAR(120),        
    degreelevel           VARCHAR(30),        
    degreetype            VARCHAR(120),        
    entranceyear          VARCHAR(8),        
    isqrycommunication    CHAR(1),  
    communication         CHAR(1),       
    onlinedays            VARCHAR(8),          
    totaltelfare          VARCHAR(18),       
    totalcalhours         VARCHAR(8),       
    isoutblackcust        CHAR(1),      
    bankencryptedfeatur    VARCHAR(4000),
    bank_encrypted_meta    VARCHAR(1024)
);
comment on table ICPS_JB_BANKINFO is '������������Ϣ';
comment on column ICPS_JB_BANKINFO.ptrq is 'ƽ̨����';
comment on column ICPS_JB_BANKINFO.ptlsh  is    'ƽ̨��ˮ��';
comment on column ICPS_JB_BANKINFO.reqmsgid is  '������Ψһ��ʾ'; 
comment on column ICPS_JB_BANKINFO.applyno     is  '������Ψһ��ʶ';
comment on column ICPS_JB_BANKINFO.isexistcust  is  '�Ƿ�����ͻ�';
comment on column ICPS_JB_BANKINFO.isexistdebtcust     is  '�Ƿ������ǿ��ͻ�'; 
comment on column ICPS_JB_BANKINFO.balance             is  '�������';
comment on column ICPS_JB_BANKINFO.avgbalancelast3days  is  '��3�����վ����';
comment on column ICPS_JB_BANKINFO.avgbalancelast6days  is  '��6�����վ����';
comment on column ICPS_JB_BANKINFO.incomelast3m         is  '��3����������ˮ��������';
comment on column ICPS_JB_BANKINFO.paylast3m            is  '��3����������ˮ֧�������';
comment on column ICPS_JB_BANKINFO.incomelast6m         is  '��6����������ˮ��������';
comment on column ICPS_JB_BANKINFO.paylast6m            is  '��6����������ˮ֧�������';
comment on column ICPS_JB_BANKINFO.isexistccust         is  '�Ƿ�������ÿ��ͻ�';
comment on column ICPS_JB_BANKINFO.currccamt            is  '�������ÿ����Ŷ��';
comment on column ICPS_JB_BANKINFO.currdisburseccamt    is  '�������ÿ���ǰʹ�ö��';
comment on column ICPS_JB_BANKINFO.isexistfincust       is  '�Ƿ������ƿͻ�';
comment on column ICPS_JB_BANKINFO.finbalance           is  '������';
comment on column ICPS_JB_BANKINFO.avgfinballast6m      is  '��6�����վ������';
comment on column ICPS_JB_BANKINFO.isexistinsurancecus  is  '�Ƿ�������տͻ�';
comment on column ICPS_JB_BANKINFO.isexistloancust      is  '�Ƿ��������ͻ�';
comment on column ICPS_JB_BANKINFO.operationloanbal     is  '��Ӫ����������';
comment on column ICPS_JB_BANKINFO.personalcreditbal    is  '����������������';
comment on column ICPS_JB_BANKINFO.autoloanbal          is  '�������';
comment on column ICPS_JB_BANKINFO.autoasset            is  '������ֵ������';
comment on column ICPS_JB_BANKINFO.houseloanbal         is  '�������';
comment on column ICPS_JB_BANKINFO.houseasset           is  '������ֵ������';
comment on column ICPS_JB_BANKINFO.isstockcust          is  '�Ƿ�֤ȯ�ͻ�';
comment on column ICPS_JB_BANKINFO.isthirddepository    is  '�Ƿ��������ܿͻ�';
comment on column ICPS_JB_BANKINFO.ispayrollcust        is  '�Ƿ��ʴ����ͻ�';
comment on column ICPS_JB_BANKINFO.issocialsecuritycus  is  '�Ƿ��籣���ɿͻ�';
comment on column ICPS_JB_BANKINFO.islifepaymentcust    is  '�Ƿ�ˮ��ú���ɿͻ�';
comment on column ICPS_JB_BANKINFO.incorporation        is  '������λ';           
comment on column ICPS_JB_BANKINFO.incorigin            is  '������λ������Դ';   
comment on column ICPS_JB_BANKINFO.position             is  'ְλ';
comment on column ICPS_JB_BANKINFO.positionorigin       is  'ְλ��Ϣ��Դ';
comment on column ICPS_JB_BANKINFO.industry             is  '��ҵ';                     
comment on column ICPS_JB_BANKINFO.industryorigin       is  '��ҵ��Ϣ��Դ';
comment on column ICPS_JB_BANKINFO.workyears            is  '��������';   
comment on column ICPS_JB_BANKINFO.workyearsorigin      is  '����������Ϣ��Դ';   
comment on column ICPS_JB_BANKINFO.income               is  '����������';
comment on column ICPS_JB_BANKINFO.incomeorigin         is  '��������Ϣ��Դ';  
comment on column ICPS_JB_BANKINFO.marriagestatus       is  '����״̬';        
comment on column ICPS_JB_BANKINFO.marriageorigin       is  '����״̬��Ϣ��Դ';
comment on column ICPS_JB_BANKINFO.isoperation          is  '�Ƿ�Ӫ�ߣ�������ҵ����幤����ҵ��';
comment on column ICPS_JB_BANKINFO.operationorigin      is  '�Ƿ�Ӫ����Ϣ��Դ';    
comment on column ICPS_JB_BANKINFO.isinnerblackcust     is  '�Ƿ�����ڲ��������ͻ�';
comment on column ICPS_JB_BANKINFO.ispolicecertified    is  '�Ƿ񹫰��������֤�ɹ�';
comment on column ICPS_JB_BANKINFO.iscourtexeccust      is  '�Ƿ���б�ִ���˵�������Ϣ';
comment on column ICPS_JB_BANKINFO.isqryhousefund       is  '�Ƿ��в�ѯ��������Ϣ';
comment on column ICPS_JB_BANKINFO.fundqrydate          is  '�������ѯʱ��';
comment on column ICPS_JB_BANKINFO.fundmonthamt         is  '�������ѯ�½��ɶ�';  
comment on column ICPS_JB_BANKINFO.fundaccountdate      is  '�����𿪻�����';      
comment on column ICPS_JB_BANKINFO.fundmonthslast6m     is  '��6�����ۼƽ�������'; 
comment on column ICPS_JB_BANKINFO.fundamtlast6m        is  '��6�����ۼƽ��ɽ��'; 
comment on column ICPS_JB_BANKINFO.fundtotalmonths      is  '�ܽ�������'; 
comment on column ICPS_JB_BANKINFO.fundtotalamt         is  '�ܽ��ɽ��'; 
comment on column ICPS_JB_BANKINFO.fundmaxamt           is  '���������ؽ�������'; 
comment on column ICPS_JB_BANKINFO.isqrysocialsec       is  '�Ƿ��в�ѯ�籣��Ϣ'; 
comment on column ICPS_JB_BANKINFO.socialqrydate        is  '�籣��Ϣ��ѯʱ��';   
comment on column ICPS_JB_BANKINFO.pensionqrymonthamt   is  '���ϱ��ղ�ѯ�½��ɶ�';     
comment on column ICPS_JB_BANKINFO.pensionaccountdate   is  '���ϱ��տ�������';         
comment on column ICPS_JB_BANKINFO.pensionmonthslast6m  is  '��6�������ϱ����ۼƽ�������';  
comment on column ICPS_JB_BANKINFO.pensionamtlast6m     is  '��6�������ϱ����ۼƽ��ɽ��';  
comment on column ICPS_JB_BANKINFO.pensiontotalmonths   is  '���ϱ����ܽ�������';  
comment on column ICPS_JB_BANKINFO.pensiontotalamt      is  '���ϱ����ܽ��ɽ��';  
comment on column ICPS_JB_BANKINFO.mdcmonthamt          is  'ҽ�Ʊ��ղ�ѯ�½��ɶ�'; 
comment on column ICPS_JB_BANKINFO.mdcaccountdate       is  'ҽ�Ʊ��տ�������';   
comment on column ICPS_JB_BANKINFO.mdcmonthslast6m      is  '��6����ҽ�Ʊ����ۼƽ�������';   
comment on column ICPS_JB_BANKINFO.mdcamtlast6m         is  '��6����ҽ�Ʊ����ۼƽ��ɽ��';   
comment on column ICPS_JB_BANKINFO.mdctotalmonths       is  'ҽ�Ʊ����ܽ�������';  
comment on column ICPS_JB_BANKINFO.mdctotalamt          is  'ҽ�Ʊ����ܽ��ɽ��';  
comment on column ICPS_JB_BANKINFO.isqrydegree          is  '�Ƿ��в�ѯѧ����Ϣ';  
comment on column ICPS_JB_BANKINFO.schoolname           is  'ԺУ����';  
comment on column ICPS_JB_BANKINFO.degreelevel          is  'ѧ�����';  
comment on column ICPS_JB_BANKINFO.degreetype           is  'ѧ�����';  
comment on column ICPS_JB_BANKINFO.entranceyear         is  '��ѧ���';  
comment on column ICPS_JB_BANKINFO.isqrycommunication   is  '�Ƿ��в�ѯ��Ӫ����Ϣ';
comment on column ICPS_JB_BANKINFO.communication        is  '��Ӫ��';  
comment on column ICPS_JB_BANKINFO.onlinedays           is  '����ʱ��';
comment on column ICPS_JB_BANKINFO.totaltelfare         is  '�ܻ����˵����';  
comment on column ICPS_JB_BANKINFO.totalcalhours        is  '������ͨ��ʱ��';  
comment on column ICPS_JB_BANKINFO.isoutblackcust       is  '�Ƿ�����ⲿ��ѯ������';
comment on column ICPS_JB_BANKINFO.bankencryptedfeatur  is  '������ͨ��ʱ��';     
comment on column ICPS_JB_BANKINFO.bank_encrypted_meta  is  '�Ƿ�����ⲿ��ѯ������';  

/*==============================================================*/
/* Table: ICPS_JB_ZMINFO                                     */
/*==============================================================*/
create table ICPS_JB_ZMINFO
(
    ptrq                    VARCHAR(8) not null,
    ptlsh                   VARCHAR(10) not null,
    reqmsgid                VARCHAR(64) not null,
    applyno                 VARCHAR(64) not null,
    creditscore_success    CHAR(1),
    creditscore_biz_no    VARCHAR(64),
    creditscore_zmscore    VARCHAR(8), 
    watchlistii_success    CHAR(1), 
    watchlistii_biz_no    VARCHAR(64), 
    watchlistii_matched    CHAR(1), 
    ivs_success             CHAR(1),
    ivs_hit                 VARCHAR(8),
    ivs_biz_no              VARCHAR(64),
    company_name            VARCHAR(120),
    occupation              VARCHAR(30),
    have_car_flag           CHAR(4),
    have_fang_flag          CHAR(4),
    auth_fin_last_1mcnt    CHAR(3), 
    auth_fin_last_3mcnt    CHAR(3), 
    auth_fin_last_6mcnt    CHAR(3), 
    ovd_order_cnt_6m        CHAR(3),
    ovd_order_amt_6m        VARCHAR(18),
    mobile_fixed_days       CHAR(5),   
    adr_stability_days      CHAR(5),  
    last6mavgassettotal     VARCHAR(18),
    tot_pay_amt_6m          VARCHAR(18),
    xfdc_index              VARCHAR(18),
    positive_biz_cnt_1y    CHAR(5), 
    pbocinfo               INTEGER
);
comment on table ICPS_JB_ZMINFO is '������֥����Ϣ';
comment on column ICPS_JB_ZMINFO.ptrq is 'ƽ̨����';
comment on column ICPS_JB_ZMINFO.ptlsh               is 'ƽ̨��ˮ��';        
comment on column ICPS_JB_ZMINFO.reqmsgid            is '������Ψһ��ʾ';  
comment on column ICPS_JB_ZMINFO.applyno             is '������Ψһ��ʶ';  
comment on column ICPS_JB_ZMINFO.creditscore_success is '֥����������-�ɹ���־'; 
comment on column ICPS_JB_ZMINFO.creditscore_biz_no  is '֥����������-bizno';    
comment on column ICPS_JB_ZMINFO.creditscore_zmscore is '֥����������-֥���';   
comment on column ICPS_JB_ZMINFO.watchlistii_success is '֥����ҵ��ע����-�ɹ���־';  
comment on column ICPS_JB_ZMINFO.watchlistii_biz_no  is '֥����ҵ��ע����-bizno';     
comment on column ICPS_JB_ZMINFO.watchlistii_matched is '֥����ҵ��ע����-�Ƿ��ע';  
comment on column ICPS_JB_ZMINFO.ivs_success         is '֥����թ��ע�嵥-�ɹ���־';  
comment on column ICPS_JB_ZMINFO.ivs_hit             is '֥����թ��ע�嵥-�Ƿ����';  
comment on column ICPS_JB_ZMINFO.ivs_biz_no          is '֥����թ��ע�嵥-bizno';  
comment on column ICPS_JB_ZMINFO.company_name        is '���ڹ�˾';  
comment on column ICPS_JB_ZMINFO.occupation          is 'ְҵ����';  
comment on column ICPS_JB_ZMINFO.have_car_flag       is '�Ƿ��г�';  
comment on column ICPS_JB_ZMINFO.have_fang_flag      is '�Ƿ��з�';  
comment on column ICPS_JB_ZMINFO.auth_fin_last_1mcnt is '���һ����������ѯ���ڻ�����'; 
comment on column ICPS_JB_ZMINFO.auth_fin_last_3mcnt is '���������������ѯ���ڻ�����'; 
comment on column ICPS_JB_ZMINFO.auth_fin_last_6mcnt is '���������������ѯ���ڻ�����'; 
comment on column ICPS_JB_ZMINFO.ovd_order_cnt_6m    is '��������������ܱ���';  
comment on column ICPS_JB_ZMINFO.ovd_order_amt_6m    is '��������������ܽ��';  
comment on column ICPS_JB_ZMINFO.mobile_fixed_days   is '�ֻ����ȶ�����'; 
comment on column ICPS_JB_ZMINFO.adr_stability_days  is '��ַ�ȶ�����';   
comment on column ICPS_JB_ZMINFO.last6mavgassettotal is '��������������ʲ��վ�ֵ';
comment on column ICPS_JB_ZMINFO.tot_pay_amt_6m      is '���������֧���ܽ��';    
comment on column ICPS_JB_ZMINFO.xfdc_index          is '���ѵ���';
comment on column ICPS_JB_ZMINFO.positive_biz_cnt_1y is '���һ����Լ������';
comment on column ICPS_JB_ZMINFO.pbocinfo            is '����������Ϣ';    


/*==============================================================*/
/* Table: ICPS_JB_EXTINFO                                     */
/*==============================================================*/
create table ICPS_JB_EXTINFO
(
    ptrq                VARCHAR(8) not null,
    ptlsh               VARCHAR(10) not null,
    reqmsgid            VARCHAR(64) not null,
    applyno             VARCHAR(64) not null,
    isplatadm           CHAR(1),
    platunadmreason     VARCHAR(1024),
    platcreditamt       VARCHAR(18),
    isjbprecreditcust   CHAR(1), 
    loanrate            VARCHAR(8),
    period              VARCHAR(64),
    repaytype           VARCHAR(64),
    risklevel           VARCHAR(32),
    repayabilitylvl     VARCHAR(32),  
    changereason        VARCHAR(1024)
);
comment on table ICPS_JB_EXTINFO is '����������չ��';
comment on column ICPS_JB_EXTINFO.ptrq is 'ƽ̨����';
comment on column ICPS_JB_EXTINFO.ptlsh   is 'ƽ̨��ˮ��';       
comment on column ICPS_JB_EXTINFO.reqmsgid  is '������Ψһ��ʾ';     
comment on column ICPS_JB_EXTINFO.applyno    is '���뵥��';    
comment on column ICPS_JB_EXTINFO.isplatadm  is 'ƽ̨���Ƿ�׼��';    
comment on column ICPS_JB_EXTINFO.platunadmreason is 'ƽ̨����׼��ԭ��';
comment on column ICPS_JB_EXTINFO.platcreditamt  is 'ƽ̨�����Ŷ��';
comment on column ICPS_JB_EXTINFO.isjbprecreditcust is '�Ƿ����Ԥ���ſͻ�';
comment on column ICPS_JB_EXTINFO.loanrate    is '��������';   
comment on column ICPS_JB_EXTINFO.period     is '��Ʒ����';    
comment on column ICPS_JB_EXTINFO.repaytype  is '���ʽ';    
comment on column ICPS_JB_EXTINFO.risklevel    is '��������';  
comment on column ICPS_JB_EXTINFO.repayabilitylvl is '��ծ��������';
comment on column ICPS_JB_EXTINFO.changereason    is '�������ۡ�����ԭ��';


/*==============================================================*/
/* Table: ICPS_JB_RESULTINFO                                     */
/*==============================================================*/
create table ICPS_JB_RESULTINFO
(
    ptrq                   VARCHAR(8) not null,
    ptlsh                  VARCHAR(10) not null,
    version                CHAR(8) not null,
    appid                  VARCHAR(32)  not null,
    function               VARCHAR(16)  not null,
    reqtimezone            VARCHAR(32)  not null,
    reqtime                VARCHAR(16)  not null,
    reqmsgid               VARCHAR(64)  not null,
    signtype               VARCHAR(16)  not null,
    inputcharset           VARCHAR(16)  not null,
    reserve                VARCHAR(32),
    applyno                VARCHAR(64)  not null,
    certtype               CHAR(2)  not null,
    certno                 VARCHAR(32)  not null,
    name                   VARCHAR(32)   not null,
    platformaccess         CHAR(1)   not null,
    platformrefusereaso    VARCHAR(1024),
    platformadmit          VARCHAR(18),
    platformrate           VARCHAR(8),
    riskrating             VARCHAR(32),
    solvencyratings        VARCHAR(32),
    changeresultreason     VARCHAR(1024),
    resultcode             CHAR(6),
    resultmsg              VARCHAR(255),
    isadmit                CHAR(1),
    admitmsg               VARCHAR(255)
);
comment on table ICPS_JB_RESULTINFO is '����������Ϣ��';
comment on column ICPS_JB_RESULTINFO.ptrq is 'ƽ̨����';
comment on column ICPS_JB_RESULTINFO.ptlsh is 'ƽ̨��ˮ��';
comment on column ICPS_JB_RESULTINFO.version is '�汾��';
comment on column ICPS_JB_RESULTINFO.appid is 'ϵͳ��ʶ';
comment on column ICPS_JB_RESULTINFO.function is '���ױ���';
comment on column ICPS_JB_RESULTINFO.reqtimezone is '���ͷ�����ʱ��';
comment on column ICPS_JB_RESULTINFO.reqtime is '���ķ���ʱ��';
comment on column ICPS_JB_RESULTINFO.reqmsgid is '������Ψһ��ʾ';
comment on column ICPS_JB_RESULTINFO.signtype is 'ǩ���㷨����';
comment on column ICPS_JB_RESULTINFO.inputcharset is '�����ַ�����';
comment on column ICPS_JB_RESULTINFO.reserve is 'Ԥ����';
comment on column ICPS_JB_RESULTINFO.applyno is '���뵥��';
comment on column ICPS_JB_RESULTINFO.certtype is '֤������';
comment on column ICPS_JB_RESULTINFO.certno is '֤������';
comment on column ICPS_JB_RESULTINFO.name is '����';
comment on column ICPS_JB_RESULTINFO.platformaccess is '��������������Ƿ�ͨ��';
comment on column ICPS_JB_RESULTINFO.platformrefusereaso is '������ͨ����ԭ��';
comment on column ICPS_JB_RESULTINFO.platformadmit is '���ͨ����������������';
comment on column ICPS_JB_RESULTINFO.platformrate is '���ͨ���������������������';
comment on column ICPS_JB_RESULTINFO.riskrating is '��������';
comment on column ICPS_JB_RESULTINFO.solvencyratings is '��ծ��������';
comment on column ICPS_JB_RESULTINFO.changeresultreason is '��ȡ����۱��ԭ��';
comment on column ICPS_JB_RESULTINFO.resultcode is '��Ӧ��';
comment on column ICPS_JB_RESULTINFO.resultmsg is '��Ӧ����';
comment on column ICPS_JB_RESULTINFO.isadmit is '�Ƿ��Ƽ�׼��';
comment on column ICPS_JB_RESULTINFO.admitmsg is '׼��ԭ��';

/*==============================================================*/
/* Table: ICPS_JB_IDCODE2ADDR                                    */
/*==============================================================*/
create table ICPS_JB_IDCODE2ADDR
(
	id6code         CHAR(6),
	shrtnm          VARCHAR(60),
	fullnm          VARCHAR(100),
	upcode          CHAR(6),  
	lvl             CHAR(1)     
);
comment on table ICPS_JB_IDCODE2ADDR is '֤������ת�������';
comment on column ICPS_JB_IDCODE2ADDR.id6code is '���֤ǰ6λ����';
comment on column ICPS_JB_IDCODE2ADDR.shrtnm  is '������';
comment on column ICPS_JB_IDCODE2ADDR.fullnm is '����ȫ��';
comment on column ICPS_JB_IDCODE2ADDR.upcode is '�ϼ�����';
comment on column ICPS_JB_IDCODE2ADDR.lvl is '�㼶';

