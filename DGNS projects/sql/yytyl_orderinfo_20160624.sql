    --建诊中医疗支付订单表
drop INDEX yytyl_orderinfo_I_KEY1;
DROP TABLE YYTYL_ORDERINFO;
CREATE TABLE YYTYL_ORDERINFO
(
KHH VARCHAR(32) not null,                            
ZWRQ VARCHAR(8),
TRAN_TIME VARCHAR(14),
ZFLX VARCHAR(1),
QDBS VARCHAR(10),
YWLX VARCHAR(10),
ACCT_NO VARCHAR(32),
TRAN_AMT decimal(20,2),
PAY_AMT decimal(20,2),
REFUND_AMT decimal(20,2),
DISCOUNT_MSG VARCHAR(150),
ZHQZLSH	VARCHAR(8) not null,
BUSS_SEQ_NO	VARCHAR(52),  
CONSUMER_SEQ_NO	VARCHAR(52),
ESB_SEQ_NO	VARCHAR(52), 
ZJRQ	VARCHAR(8), 
ZJSJ	VARCHAR(14), 
ZJLSH	VARCHAR(52), 
REFUND_SEQ_NO VARCHAR(52), 
ORDER_DATE	VARCHAR(8), 
ORDER_TIME	VARCHAR(14), 
UID VARCHAR(30),
HOSP_NAME VARCHAR(150) ,
DEP_ID VARCHAR(30) ,
DEP_NAME VARCHAR(150) ,
DOCTOR_ID VARCHAR(30) ,
DOCTOR_NAME VARCHAR(150) ,
DOCTOR_ZCNAME VARCHAR(150) ,
PHONE  VARCHAR(30) ,
ID_NO VARCHAR(30) ,
ID_TYPE VARCHAR(2) ,
NAME VARCHAR(150) ,
SEX VARCHAR(30) ,
BIRTH VARCHAR(10) ,
SOCIAL_CARD VARCHAR(30) ,
CLINIC_NO VARCHAR(30) ,
ORDER_NO VARCHAR(64) not null,
ORDER_TYPE VARCHAR(1) not null,
TO_DATE VARCHAR(10) not null,
TO_TIME VARCHAR(40) ,
BEGIN_TIME VARCHAR(10) ,
END_TIME VARCHAR(10) ,
STATE VARCHAR(10) ,
MSG VARCHAR(150) ,
QSZT VARCHAR(10) ,
ORDER_TYPE_MSG VARCHAR(50) ,
PAY_FLAG VARCHAR(10) ,
PS_FLAG VARCHAR(20) ,
SUR_CHARGE_FLAG VARCHAR(20) ,
REMARK1 VARCHAR(40) ,
REMARK2 VARCHAR(40) 
);

CREATE INDEX yytyl_orderinfo_I_KEY1 ON YYTYL_ORDERINFO(KHH,ORDER_NO,TO_DATE);
COMMENT ON TABLE  YYTYL_ORDERINFO  IS '诊中医疗订单表';
COMMENT ON COLUMN yytyl_orderinfo.KHH IS'客户号';
COMMENT ON COLUMN yytyl_orderinfo.ZWRQ IS'交易日期';
COMMENT ON COLUMN yytyl_orderinfo.TRAN_TIME IS'交易时间';
COMMENT ON COLUMN yytyl_orderinfo.ZFLX IS'支付类型';
COMMENT ON COLUMN yytyl_orderinfo.QDBS IS'交易渠道';
COMMENT ON COLUMN yytyl_orderinfo.YWLX IS'业务类型';
COMMENT ON COLUMN yytyl_orderinfo.ACCT_NO IS'账号';
COMMENT ON COLUMN yytyl_orderinfo.TRAN_AMT IS'交易金额';
COMMENT ON COLUMN yytyl_orderinfo.PAY_AMT IS'实付金额';
COMMENT ON COLUMN yytyl_orderinfo.REFUND_AMT IS'退款金额';
COMMENT ON COLUMN yytyl_orderinfo.DISCOUNT_MSG IS'优惠说明';
COMMENT ON COLUMN yytyl_orderinfo.ZHQZLSH IS'GAPS流水号';
COMMENT ON COLUMN yytyl_orderinfo.BUSS_SEQ_NO IS'业务流水号';
COMMENT ON COLUMN yytyl_orderinfo.CONSUMER_SEQ_NO IS'前置流水号';
COMMENT ON COLUMN yytyl_orderinfo.ESB_SEQ_NO IS'ESB流水号';
COMMENT ON COLUMN yytyl_orderinfo.ZJLSH IS'主机流水号';
COMMENT ON COLUMN yytyl_orderinfo.REFUND_SEQ_NO IS'退款流水号';
COMMENT ON COLUMN yytyl_orderinfo.UID IS'医院ID ';
COMMENT ON COLUMN yytyl_orderinfo.HOSP_NAME IS'医院名称';
COMMENT ON COLUMN yytyl_orderinfo.DEP_ID IS'科室ID';
COMMENT ON COLUMN yytyl_orderinfo.DEP_NAME IS'科室名称';
COMMENT ON COLUMN yytyl_orderinfo.DOCTOR_ID IS'医生ID';
COMMENT ON COLUMN yytyl_orderinfo.DOCTOR_NAME IS'医生名称';
COMMENT ON COLUMN yytyl_orderinfo.DOCTOR_ZCNAME IS'医生职称';
COMMENT ON COLUMN yytyl_orderinfo.PHONE  IS'手机号码';
COMMENT ON COLUMN yytyl_orderinfo.ID_NO IS'证件号码';
COMMENT ON COLUMN yytyl_orderinfo.ID_TYPE IS'证件类型';
COMMENT ON COLUMN yytyl_orderinfo.NAME IS'姓名';
COMMENT ON COLUMN yytyl_orderinfo.SEX IS'性别';
COMMENT ON COLUMN yytyl_orderinfo.BIRTH IS'出生日期';
COMMENT ON COLUMN yytyl_orderinfo.SOCIAL_CARD IS'社保卡号';
COMMENT ON COLUMN yytyl_orderinfo.CLINIC_NO IS'就诊卡号/门诊编号';
COMMENT ON COLUMN yytyl_orderinfo.ORDER_NO IS'订单编号';
COMMENT ON COLUMN yytyl_orderinfo.ORDER_TYPE IS'订单类型 0-支付 1-退款';
COMMENT ON COLUMN yytyl_orderinfo.TO_DATE IS'就诊日期';
COMMENT ON COLUMN yytyl_orderinfo.TO_TIME IS'就诊时段';
COMMENT ON COLUMN yytyl_orderinfo.BEGIN_TIME IS'就诊开始时间';
COMMENT ON COLUMN yytyl_orderinfo.END_TIME IS'就诊结束时间';
COMMENT ON COLUMN yytyl_orderinfo.STATE IS'状态';
COMMENT ON COLUMN yytyl_orderinfo.MSG IS'状态说明';
COMMENT ON COLUMN yytyl_orderinfo.QSZT IS'清算状态';
COMMENT ON COLUMN yytyl_orderinfo.ORDER_TYPE_MSG IS'订单类型说明';
COMMENT ON COLUMN yytyl_orderinfo.PAY_FLAG IS'支付标识';
COMMENT ON COLUMN yytyl_orderinfo.PS_FLAG IS'皮试标志';
COMMENT ON COLUMN yytyl_orderinfo.SUR_CHARGE_FLAG IS'附加费标志';
COMMENT ON COLUMN yytyl_orderinfo.REMARK1 IS'备注1';
COMMENT ON COLUMN yytyl_orderinfo.REMARK2 IS'备注2';
