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
comment on table ICPS_JB_APPLYINFO is '授信申请信息表';
comment on column ICPS_JB_APPLYINFO.ptrq is '平台日期';
comment on column ICPS_JB_APPLYINFO.ptlsh is '平台流水号';
comment on column ICPS_JB_APPLYINFO.version is '版本号';
comment on column ICPS_JB_APPLYINFO.appid is '系统标识';
comment on column ICPS_JB_APPLYINFO.function is '交易编码';
comment on column ICPS_JB_APPLYINFO.reqtimezone is '发送方所在时区';
comment on column ICPS_JB_APPLYINFO.reqtime is '报文发起时间';
comment on column ICPS_JB_APPLYINFO.reqmsgid is '请求报文唯一标示';
comment on column ICPS_JB_APPLYINFO.signtype is '签名算法类型';
comment on column ICPS_JB_APPLYINFO.inputcharset is '报文字符编码';
comment on column ICPS_JB_APPLYINFO.reserve is '预留域';
comment on column ICPS_JB_APPLYINFO.applyno is '申请单号';
comment on column ICPS_JB_APPLYINFO.certtype is '证件类型';
comment on column ICPS_JB_APPLYINFO.certno is '证件号码';
comment on column ICPS_JB_APPLYINFO.certvalidenddate is '证件有效期';
comment on column ICPS_JB_APPLYINFO.name is '姓名';
comment on column ICPS_JB_APPLYINFO.customerno   is '客户编号';
comment on column ICPS_JB_APPLYINFO.mobileno     is '手机号';
comment on column ICPS_JB_APPLYINFO.occupation   is '职业';
comment on column ICPS_JB_APPLYINFO.address      is '详细地址';
comment on column ICPS_JB_APPLYINFO.city         is '城市';
comment on column ICPS_JB_APPLYINFO.prov         is '省份';
comment on column ICPS_JB_APPLYINFO.area         is '地区';
comment on column ICPS_JB_APPLYINFO.zmauthflag   is '芝麻授权成功表示';
comment on column ICPS_JB_APPLYINFO.hasjbadmit   is '是否之前就有借呗额度';
comment on column ICPS_JB_APPLYINFO.applystat    is '请求单状态 0-成功 1-失败 2-处理中 3-已发送小微查询 9-初始';
comment on column ICPS_JB_APPLYINFO.reqcode      is '请求响应码';
comment on column ICPS_JB_APPLYINFO.reqmsg       is '请求响应信息';
comment on column ICPS_JB_APPLYINFO.reqdate      is '初审日期';
comment on column ICPS_JB_APPLYINFO.reqtime1     is '初审时间';
comment on column ICPS_JB_APPLYINFO.isadmit      is '是否推荐准入';
comment on column ICPS_JB_APPLYINFO.creditno     is '授信编号';
comment on column ICPS_JB_APPLYINFO.creditamt    is '推荐准入时，推荐的额度';
comment on column ICPS_JB_APPLYINFO.creditrate   is '荐准入时，推荐的利率';
comment on column ICPS_JB_APPLYINFO.refusecode   is '推荐拒绝时，拒绝码';
comment on column ICPS_JB_APPLYINFO.refusemsg    is '推荐拒绝时，拒绝原因';
comment on column ICPS_JB_APPLYINFO.respcode     is '返回响应码';
comment on column ICPS_JB_APPLYINFO.respmsg      is '返回响应信息';
comment on column ICPS_JB_APPLYINFO.retry        is '是否重试';
comment on column ICPS_JB_APPLYINFO.resultstat   is '结果单状态 0-成功 1-失败 2-处理中 9-初始';
comment on column ICPS_JB_APPLYINFO.respdate     is '返回日期';
comment on column ICPS_JB_APPLYINFO.resptime     is '返回时间';

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
comment on table ICPS_JB_BANKINFO is '申请人银行信息';
comment on column ICPS_JB_BANKINFO.ptrq is '平台日期';
comment on column ICPS_JB_BANKINFO.ptlsh  is    '平台流水号';
comment on column ICPS_JB_BANKINFO.reqmsgid is  '请求报文唯一标示'; 
comment on column ICPS_JB_BANKINFO.applyno     is  '请求报文唯一标识';
comment on column ICPS_JB_BANKINFO.isexistcust  is  '是否存量客户';
comment on column ICPS_JB_BANKINFO.isexistdebtcust     is  '是否存量借记卡客户'; 
comment on column ICPS_JB_BANKINFO.balance             is  '卡内余额';
comment on column ICPS_JB_BANKINFO.avgbalancelast3days  is  '近3个月日均余额';
comment on column ICPS_JB_BANKINFO.avgbalancelast6days  is  '近6个月日均余额';
comment on column ICPS_JB_BANKINFO.incomelast3m         is  '近3个月银行流水收入金额数';
comment on column ICPS_JB_BANKINFO.paylast3m            is  '近3个月银行流水支出金额数';
comment on column ICPS_JB_BANKINFO.incomelast6m         is  '近6个月银行流水收入金额数';
comment on column ICPS_JB_BANKINFO.paylast6m            is  '近6个月银行流水支出金额数';
comment on column ICPS_JB_BANKINFO.isexistccust         is  '是否存量信用卡客户';
comment on column ICPS_JB_BANKINFO.currccamt            is  '本行信用卡授信额度';
comment on column ICPS_JB_BANKINFO.currdisburseccamt    is  '本行信用卡当前使用额度';
comment on column ICPS_JB_BANKINFO.isexistfincust       is  '是否存量理财客户';
comment on column ICPS_JB_BANKINFO.finbalance           is  '理财余额';
comment on column ICPS_JB_BANKINFO.avgfinballast6m      is  '近6个月日均理余额';
comment on column ICPS_JB_BANKINFO.isexistinsurancecus  is  '是否存量保险客户';
comment on column ICPS_JB_BANKINFO.isexistloancust      is  '是否存量贷款客户';
comment on column ICPS_JB_BANKINFO.operationloanbal     is  '经营类贷款总余额';
comment on column ICPS_JB_BANKINFO.personalcreditbal    is  '个人信用类贷总余额';
comment on column ICPS_JB_BANKINFO.autoloanbal          is  '车贷余额';
comment on column ICPS_JB_BANKINFO.autoasset            is  '车产价值评估额';
comment on column ICPS_JB_BANKINFO.houseloanbal         is  '房贷余额';
comment on column ICPS_JB_BANKINFO.houseasset           is  '房产价值评估额';
comment on column ICPS_JB_BANKINFO.isstockcust          is  '是否证券客户';
comment on column ICPS_JB_BANKINFO.isthirddepository    is  '是否第三方存管客户';
comment on column ICPS_JB_BANKINFO.ispayrollcust        is  '是否工资代发客户';
comment on column ICPS_JB_BANKINFO.issocialsecuritycus  is  '是否社保代缴客户';
comment on column ICPS_JB_BANKINFO.islifepaymentcust    is  '是否水电煤代缴客户';
comment on column ICPS_JB_BANKINFO.incorporation        is  '工作单位';           
comment on column ICPS_JB_BANKINFO.incorigin            is  '工作单位数据来源';   
comment on column ICPS_JB_BANKINFO.position             is  '职位';
comment on column ICPS_JB_BANKINFO.positionorigin       is  '职位信息来源';
comment on column ICPS_JB_BANKINFO.industry             is  '行业';                     
comment on column ICPS_JB_BANKINFO.industryorigin       is  '行业信息来源';
comment on column ICPS_JB_BANKINFO.workyears            is  '工作年限';   
comment on column ICPS_JB_BANKINFO.workyearsorigin      is  '工作年限信息来源';   
comment on column ICPS_JB_BANKINFO.income               is  '月收入区间';
comment on column ICPS_JB_BANKINFO.incomeorigin         is  '月收入信息来源';  
comment on column ICPS_JB_BANKINFO.marriagestatus       is  '婚姻状态';        
comment on column ICPS_JB_BANKINFO.marriageorigin       is  '婚姻状态信息来源';
comment on column ICPS_JB_BANKINFO.isoperation          is  '是否经营者（工商企业或个体工商企业）';
comment on column ICPS_JB_BANKINFO.operationorigin      is  '是否经营者信息来源';    
comment on column ICPS_JB_BANKINFO.isinnerblackcust     is  '是否击中内部黑名单客户';
comment on column ICPS_JB_BANKINFO.ispolicecertified    is  '是否公安网身份验证成功';
comment on column ICPS_JB_BANKINFO.iscourtexeccust      is  '是否击中被执行人等涉诉信息';
comment on column ICPS_JB_BANKINFO.isqryhousefund       is  '是否有查询公积金信息';
comment on column ICPS_JB_BANKINFO.fundqrydate          is  '公积金查询时间';
comment on column ICPS_JB_BANKINFO.fundmonthamt         is  '公积金查询月缴纳额';  
comment on column ICPS_JB_BANKINFO.fundaccountdate      is  '公积金开户日期';      
comment on column ICPS_JB_BANKINFO.fundmonthslast6m     is  '近6个月累计缴纳月数'; 
comment on column ICPS_JB_BANKINFO.fundamtlast6m        is  '近6个月累计缴纳金额'; 
comment on column ICPS_JB_BANKINFO.fundtotalmonths      is  '总缴纳月数'; 
comment on column ICPS_JB_BANKINFO.fundtotalamt         is  '总缴纳金额'; 
comment on column ICPS_JB_BANKINFO.fundmaxamt           is  '公积金属地缴纳上限'; 
comment on column ICPS_JB_BANKINFO.isqrysocialsec       is  '是否有查询社保信息'; 
comment on column ICPS_JB_BANKINFO.socialqrydate        is  '社保信息查询时间';   
comment on column ICPS_JB_BANKINFO.pensionqrymonthamt   is  '养老保险查询月缴纳额';     
comment on column ICPS_JB_BANKINFO.pensionaccountdate   is  '养老保险开户日期';         
comment on column ICPS_JB_BANKINFO.pensionmonthslast6m  is  '近6个月养老保险累计缴纳月数';  
comment on column ICPS_JB_BANKINFO.pensionamtlast6m     is  '近6个月养老保险累计缴纳金额';  
comment on column ICPS_JB_BANKINFO.pensiontotalmonths   is  '养老保险总缴纳月数';  
comment on column ICPS_JB_BANKINFO.pensiontotalamt      is  '养老保险总缴纳金额';  
comment on column ICPS_JB_BANKINFO.mdcmonthamt          is  '医疗保险查询月缴纳额'; 
comment on column ICPS_JB_BANKINFO.mdcaccountdate       is  '医疗保险开户日期';   
comment on column ICPS_JB_BANKINFO.mdcmonthslast6m      is  '近6个月医疗保险累计缴纳月数';   
comment on column ICPS_JB_BANKINFO.mdcamtlast6m         is  '近6个月医疗保险累计缴纳金额';   
comment on column ICPS_JB_BANKINFO.mdctotalmonths       is  '医疗保险总缴纳月数';  
comment on column ICPS_JB_BANKINFO.mdctotalamt          is  '医疗保险总缴纳金额';  
comment on column ICPS_JB_BANKINFO.isqrydegree          is  '是否有查询学历信息';  
comment on column ICPS_JB_BANKINFO.schoolname           is  '院校名称';  
comment on column ICPS_JB_BANKINFO.degreelevel          is  '学历层次';  
comment on column ICPS_JB_BANKINFO.degreetype           is  '学历类别';  
comment on column ICPS_JB_BANKINFO.entranceyear         is  '入学年份';  
comment on column ICPS_JB_BANKINFO.isqrycommunication   is  '是否有查询运营商信息';
comment on column ICPS_JB_BANKINFO.communication        is  '运营商';  
comment on column ICPS_JB_BANKINFO.onlinedays           is  '在网时长';
comment on column ICPS_JB_BANKINFO.totaltelfare         is  '总话费账单金额';  
comment on column ICPS_JB_BANKINFO.totalcalhours        is  '半年内通话时长';  
comment on column ICPS_JB_BANKINFO.isoutblackcust       is  '是否击中外部查询黑名单';
comment on column ICPS_JB_BANKINFO.bankencryptedfeatur  is  '半年内通话时长';     
comment on column ICPS_JB_BANKINFO.bank_encrypted_meta  is  '是否击中外部查询黑名单';  

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
comment on table ICPS_JB_ZMINFO is '申请人芝麻信息';
comment on column ICPS_JB_ZMINFO.ptrq is '平台日期';
comment on column ICPS_JB_ZMINFO.ptlsh               is '平台流水号';        
comment on column ICPS_JB_ZMINFO.reqmsgid            is '请求报文唯一标示';  
comment on column ICPS_JB_ZMINFO.applyno             is '请求报文唯一标识';  
comment on column ICPS_JB_ZMINFO.creditscore_success is '芝麻信用评分-成功标志'; 
comment on column ICPS_JB_ZMINFO.creditscore_biz_no  is '芝麻信用评分-bizno';    
comment on column ICPS_JB_ZMINFO.creditscore_zmscore is '芝麻信用评分-芝麻分';   
comment on column ICPS_JB_ZMINFO.watchlistii_success is '芝麻行业关注名单-成功标志';  
comment on column ICPS_JB_ZMINFO.watchlistii_biz_no  is '芝麻行业关注名单-bizno';     
comment on column ICPS_JB_ZMINFO.watchlistii_matched is '芝麻行业关注名单-是否关注';  
comment on column ICPS_JB_ZMINFO.ivs_success         is '芝麻欺诈关注清单-成功标志';  
comment on column ICPS_JB_ZMINFO.ivs_hit             is '芝麻欺诈关注清单-是否击中';  
comment on column ICPS_JB_ZMINFO.ivs_biz_no          is '芝麻欺诈关注清单-bizno';  
comment on column ICPS_JB_ZMINFO.company_name        is '所在公司';  
comment on column ICPS_JB_ZMINFO.occupation          is '职业类型';  
comment on column ICPS_JB_ZMINFO.have_car_flag       is '是否有车';  
comment on column ICPS_JB_ZMINFO.have_fang_flag      is '是否有房';  
comment on column ICPS_JB_ZMINFO.auth_fin_last_1mcnt is '最近一个月主动查询金融机构数'; 
comment on column ICPS_JB_ZMINFO.auth_fin_last_3mcnt is '最近三个月主动查询金融机构数'; 
comment on column ICPS_JB_ZMINFO.auth_fin_last_6mcnt is '最近六个月主动查询金融机构数'; 
comment on column ICPS_JB_ZMINFO.ovd_order_cnt_6m    is '最近六个月逾期总笔数';  
comment on column ICPS_JB_ZMINFO.ovd_order_amt_6m    is '最近六个月逾期总金额';  
comment on column ICPS_JB_ZMINFO.mobile_fixed_days   is '手机号稳定天数'; 
comment on column ICPS_JB_ZMINFO.adr_stability_days  is '地址稳定天数';   
comment on column ICPS_JB_ZMINFO.last6mavgassettotal is '最近六个月流动资产日均值';
comment on column ICPS_JB_ZMINFO.tot_pay_amt_6m      is '最近六个月支付总金额';    
comment on column ICPS_JB_ZMINFO.xfdc_index          is '消费档次';
comment on column ICPS_JB_ZMINFO.positive_biz_cnt_1y is '最近一年履约场景数';
comment on column ICPS_JB_ZMINFO.pbocinfo            is '人行征信信息';    


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
comment on table ICPS_JB_EXTINFO is '授信申请扩展表';
comment on column ICPS_JB_EXTINFO.ptrq is '平台日期';
comment on column ICPS_JB_EXTINFO.ptlsh   is '平台流水号';       
comment on column ICPS_JB_EXTINFO.reqmsgid  is '请求报文唯一标示';     
comment on column ICPS_JB_EXTINFO.applyno    is '申请单号';    
comment on column ICPS_JB_EXTINFO.isplatadm  is '平台贷是否准入';    
comment on column ICPS_JB_EXTINFO.platunadmreason is '平台贷不准入原因';
comment on column ICPS_JB_EXTINFO.platcreditamt  is '平台贷授信额度';
comment on column ICPS_JB_EXTINFO.isjbprecreditcust is '是否借呗预授信客户';
comment on column ICPS_JB_EXTINFO.loanrate    is '基础利率';   
comment on column ICPS_JB_EXTINFO.period     is '产品期限';    
comment on column ICPS_JB_EXTINFO.repaytype  is '还款方式';    
comment on column ICPS_JB_EXTINFO.risklevel    is '风险评级';  
comment on column ICPS_JB_EXTINFO.repayabilitylvl is '偿债能力评级';
comment on column ICPS_JB_EXTINFO.changereason    is '提额、降额、提价、降价原因';


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
comment on table ICPS_JB_RESULTINFO is '借呗终审信息表';
comment on column ICPS_JB_RESULTINFO.ptrq is '平台日期';
comment on column ICPS_JB_RESULTINFO.ptlsh is '平台流水号';
comment on column ICPS_JB_RESULTINFO.version is '版本号';
comment on column ICPS_JB_RESULTINFO.appid is '系统标识';
comment on column ICPS_JB_RESULTINFO.function is '交易编码';
comment on column ICPS_JB_RESULTINFO.reqtimezone is '发送方所在时区';
comment on column ICPS_JB_RESULTINFO.reqtime is '报文发起时间';
comment on column ICPS_JB_RESULTINFO.reqmsgid is '请求报文唯一标示';
comment on column ICPS_JB_RESULTINFO.signtype is '签名算法类型';
comment on column ICPS_JB_RESULTINFO.inputcharset is '报文字符编码';
comment on column ICPS_JB_RESULTINFO.reserve is '预留域';
comment on column ICPS_JB_RESULTINFO.applyno is '申请单号';
comment on column ICPS_JB_RESULTINFO.certtype is '证件类型';
comment on column ICPS_JB_RESULTINFO.certno is '证件号码';
comment on column ICPS_JB_RESULTINFO.name is '姓名';
comment on column ICPS_JB_RESULTINFO.platformaccess is '本次审批结果，是否通过';
comment on column ICPS_JB_RESULTINFO.platformrefusereaso is '审批不通过的原因';
comment on column ICPS_JB_RESULTINFO.platformadmit is '如果通过，则输出审批额度';
comment on column ICPS_JB_RESULTINFO.platformrate is '如果通过，则输出审批基础利率';
comment on column ICPS_JB_RESULTINFO.riskrating is '风险评级';
comment on column ICPS_JB_RESULTINFO.solvencyratings is '偿债能力评级';
comment on column ICPS_JB_RESULTINFO.changeresultreason is '额度、定价变更原因';
comment on column ICPS_JB_RESULTINFO.resultcode is '响应码';
comment on column ICPS_JB_RESULTINFO.resultmsg is '响应描述';
comment on column ICPS_JB_RESULTINFO.isadmit is '是否推荐准入';
comment on column ICPS_JB_RESULTINFO.admitmsg is '准入原因';

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
comment on table ICPS_JB_IDCODE2ADDR is '证件号码转地区码表';
comment on column ICPS_JB_IDCODE2ADDR.id6code is '身份证前6位编码';
comment on column ICPS_JB_IDCODE2ADDR.shrtnm  is '地区名';
comment on column ICPS_JB_IDCODE2ADDR.fullnm is '地区全名';
comment on column ICPS_JB_IDCODE2ADDR.upcode is '上级编码';
comment on column ICPS_JB_IDCODE2ADDR.lvl is '层级';

