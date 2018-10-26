create table  agent_yxt_jfjl
(
    jgh            varchar(10) not null,
    shh            varchar(20) not null,
    shmc        varchar(60) not null,
    shjth        varchar(20),        
    xxlx        varchar(10),        
    qdlx        varchar(5),    
    pch         varchar(30) not null,        
    ddh            varchar(32) not null,      
    yddh        varchar(32),        
    qdddh        varchar(64),        
    jsddh        varchar(32),        
    kpp            varchar(5),        
    jylx        varchar(6),    
    jyje        decimal(15,2) not null,        
    jybz        varchar(3), 
    jyrq        varchar(8), 
    jysj        varchar(10),
    yjylx        varchar(6),        
    yjsddh        varchar(32),        
    jym            varchar(128),            
    zdh            varchar(10),                
    xsxm        varchar(60),
    xsbj        varchar(20),
    jzsjh        varchar(15),
    hjje        decimal(15,2),    
    tuitionFee    decimal(15,2), 
    bookFee        decimal(15,2), 
    uniformFee    decimal(15,2), 
    schoolBusFee    decimal(15,2), 
    dormitoryFee    decimal(15,2), 
    breakfastFee    decimal(15,2), 
    lunchFee    decimal(15,2), 
    dinnerFee    decimal(15,2), 
    otherFee      decimal(15,2), 
    zkje        decimal(15,2),    
    sjyh        decimal(15,2),        
    qdyh        decimal(15,2),        
    ddsfje        decimal(15,2),        
    wbddh        varchar(40),        
    ydm            varchar(3),                
    fkh            varchar(32),            
    sqm            varchar(64),            
    yhwx_id        varchar(64),        
    zshgz_id    varchar(64),    
    is_shzj        varchar(3),    
    kwzzh        varchar(64),
    constraint p_k_agent_yxt_jfjl primary key(shh,ddh)
);
COMMENT ON TABLE agent_yxt_jfjl IS '银校通缴费记录登记表';
COMMENT ON COLUMN agent_yxt_jfjl.jgh IS '机构号';        
COMMENT ON COLUMN agent_yxt_jfjl.shh IS '商户号';            
COMMENT ON COLUMN agent_yxt_jfjl.shmc IS '商户名称';        
COMMENT ON COLUMN agent_yxt_jfjl.shjth IS '商户集团号';        
COMMENT ON COLUMN agent_yxt_jfjl.xxlx IS '消息类型';        
COMMENT ON COLUMN agent_yxt_jfjl.qdlx IS '渠道类型';
COMMENT ON COLUMN agent_yxt_jfjl.pch IS '批次号';        
COMMENT ON COLUMN agent_yxt_jfjl.ddh IS '订单号';            
COMMENT ON COLUMN agent_yxt_jfjl.yddh IS '原订单号';        
COMMENT ON COLUMN agent_yxt_jfjl.qdddh IS '渠道订单号';        
COMMENT ON COLUMN agent_yxt_jfjl.jsddh IS '检索订单号';        
COMMENT ON COLUMN agent_yxt_jfjl.kpp IS '卡品牌';            
COMMENT ON COLUMN agent_yxt_jfjl.jylx IS '交易类型';        
COMMENT ON COLUMN agent_yxt_jfjl.jyje IS '交易金额';        
COMMENT ON COLUMN agent_yxt_jfjl.jybz IS '交易币种';
COMMENT ON COLUMN agent_yxt_jfjl.jyrq IS '交易日期';        
COMMENT ON COLUMN agent_yxt_jfjl.jysj IS '交易时间';        
COMMENT ON COLUMN agent_yxt_jfjl.yjylx IS '原交易类型';        
COMMENT ON COLUMN agent_yxt_jfjl.yjsddh IS '原检索订单号';        
COMMENT ON COLUMN agent_yxt_jfjl.jym IS '交易码';            
COMMENT ON COLUMN agent_yxt_jfjl.zdh IS '终端号';            
COMMENT ON COLUMN agent_yxt_jfjl.xsxm IS '学生姓名';    
COMMENT ON COLUMN agent_yxt_jfjl.xsbj IS '学生班级';
COMMENT ON COLUMN agent_yxt_jfjl.jzsjh IS '家长手机号码';
COMMENT ON COLUMN agent_yxt_jfjl.hjje IS '合计金额';                
COMMENT ON COLUMN agent_yxt_jfjl.zkje IS '折扣金额';    
COMMENT ON COLUMN agent_yxt_jfjl.sjyh IS '商户优惠';        
COMMENT ON COLUMN agent_yxt_jfjl.qdyh IS '渠道优惠';        
COMMENT ON COLUMN agent_yxt_jfjl.ddsfje IS '订单实付金额';        
COMMENT ON COLUMN agent_yxt_jfjl.wbddh IS '外部订单号';        
COMMENT ON COLUMN agent_yxt_jfjl.ydm IS '应答码';            
COMMENT ON COLUMN agent_yxt_jfjl.fkh IS '发卡行';            
COMMENT ON COLUMN agent_yxt_jfjl.sqm IS '授权码';            
COMMENT ON COLUMN agent_yxt_jfjl.yhwx_id IS '用户微信ID';        
COMMENT ON COLUMN agent_yxt_jfjl.zshgz_id IS '子商户公众ID';    
COMMENT ON COLUMN agent_yxt_jfjl.is_shzj IS '交易是否涉及商户资金';    
COMMENT ON COLUMN agent_yxt_jfjl.kwzzh IS '银行卡号/微信、支付宝账号';        


CREATE TABLE  APP_DWXX_EXT
    (
        DWBH CHARACTER(16) NOT NULL,
        SXFBZ CHARACTER(1),
        SXFGSBZ CHARACTER(1),
        SXFKHFS CHARACTER(1),
        SXFZHLX CHARACTER(1),
        SXFFKZH CHARACTER(32),
        SXFFKZHMC VARCHAR(100),
        SXFJSFS CHARACTER(1),
        SXFJSCS CHARACTER(10),
        SXFJEXX DECIMAL(7,2),
        SXFJESX DECIMAL(7,2),
        KHQYFS CHARACTER(1),
        KKFS CHARACTER(1),
        TZBZ CHARACTER(1),
        TZED DECIMAL(15,2),
        TZDFZH CHARACTER(32),
        YJBZ CHARACTER(1),
        YEYBBL DECIMAL(7,2),
        JCHMBZ CHARACTER(1),
        YQBZ CHARACTER(1),
        YQMY VARCHAR(128),
        FYYWLX1 VARCHAR(3),
        FYRZZH1 VARCHAR(32),
        FYZHLX1 VARCHAR(1),
        FYYWLX2 VARCHAR(3),
        FYRZZH2 VARCHAR(32),
        FYZHLX2 VARCHAR(1),
        FYYWLX3 VARCHAR(3),
        FYRZZH3 VARCHAR(32),
        FYZHLX3 VARCHAR(1),
        FYYWLX4 VARCHAR(3),
        FYRZZH4 VARCHAR(32),
        FYZHLX4 VARCHAR(1),
        FYYWLX5 VARCHAR(3),
        FYRZZH5 VARCHAR(32),
        FYZHLX5 VARCHAR(1),
        EXTFLD1 VARCHAR(80),
        EXTFLD2 VARCHAR(80),
        EXTFLD3 VARCHAR(80),
        EXTFLD4 VARCHAR(80),
        EXTFLD5 VARCHAR(80),
        EXTFLD6 VARCHAR(160),
        CONSTRAINT P_K_APP_DWXX_EXT_1 PRIMARY KEY (DWBH)
    );
COMMENT ON TABLE APP_DWXX_EXT IS '单位信息扩展表';
COMMENT ON COLUMN APP_DWXX_EXT.DWBH  IS   '单位编号';
COMMENT ON COLUMN APP_DWXX_EXT.SXFBZ  IS     '手续费标志 0-收取，1-免收';
COMMENT ON COLUMN APP_DWXX_EXT.SXFGSBZ  IS     '手续费归属标志 0-单位，1-其他，2-个人';
COMMENT ON COLUMN APP_DWXX_EXT.SXFKHFS  IS     '手续费扣划方式 0-自动，1-现金';
COMMENT ON COLUMN APP_DWXX_EXT.SXFZHLX  IS    '手续费付款账号类型';
COMMENT ON COLUMN APP_DWXX_EXT.SXFFKZH  IS     '手续费付款账号';
COMMENT ON COLUMN APP_DWXX_EXT.SXFFKZHMC  IS     '手续费付款账号名称';
COMMENT ON COLUMN APP_DWXX_EXT.SXFJSFS  IS     '手续费计算方式 0-按比例 1-按单笔';
COMMENT ON COLUMN APP_DWXX_EXT.SXFJSCS  IS     '手续费计算参数';
COMMENT ON COLUMN APP_DWXX_EXT.SXFJEXX  IS     '手续费金额下限';
COMMENT ON COLUMN APP_DWXX_EXT.SXFJESX  IS      '手续费金额上限';
COMMENT ON COLUMN APP_DWXX_EXT.KHQYFS  IS     '客户签约方式 0-银行 1-委托单位 2-银行或委托单位';
COMMENT ON COLUMN APP_DWXX_EXT.KKFS  IS    '部分扣款标志';
COMMENT ON COLUMN APP_DWXX_EXT.TZBZ  IS     '透支标志';
COMMENT ON COLUMN APP_DWXX_EXT.TZED  IS     '透支额度';
COMMENT ON COLUMN APP_DWXX_EXT.TZDFZH  IS    '垫付账号';
COMMENT ON COLUMN APP_DWXX_EXT.YJBZ  IS      '预警标志';
COMMENT ON COLUMN APP_DWXX_EXT.YEYBBL  IS     '余额预报比率';
COMMENT ON COLUMN APP_DWXX_EXT.JCHMBZ  IS     '检查户名标志';
COMMENT ON COLUMN APP_DWXX_EXT.YQBZ  IS     '验签标志';
COMMENT ON COLUMN APP_DWXX_EXT.YQMY  IS     '验签密钥';
COMMENT ON COLUMN APP_DWXX_EXT.FYYWLX1  IS    '费用1业务种类';
COMMENT ON COLUMN APP_DWXX_EXT.FYRZZH1  IS     '费用1入账账号';
COMMENT ON COLUMN APP_DWXX_EXT.FYZHLX1  IS     '费用1账号类型';
COMMENT ON COLUMN APP_DWXX_EXT.FYYWLX2  IS     '费用2业务种类';
COMMENT ON COLUMN APP_DWXX_EXT.FYRZZH2  IS     '费用2入账账号';
COMMENT ON COLUMN APP_DWXX_EXT.FYZHLX2  IS    '费用2账号类型';
COMMENT ON COLUMN APP_DWXX_EXT.FYYWLX3  IS     '费用3业务种类';
COMMENT ON COLUMN APP_DWXX_EXT.FYRZZH3  IS     '费用3入账账号';
COMMENT ON COLUMN APP_DWXX_EXT.FYZHLX3  IS     '费用3账号类型';
COMMENT ON COLUMN APP_DWXX_EXT.FYYWLX4  IS     '费用4业务种类';
COMMENT ON COLUMN APP_DWXX_EXT.FYRZZH4  IS     '费用4入账账号';
COMMENT ON COLUMN APP_DWXX_EXT.FYZHLX4  IS     '费用4账号类型';
COMMENT ON COLUMN APP_DWXX_EXT.FYYWLX5  IS     '费用5业务种类';
COMMENT ON COLUMN APP_DWXX_EXT.FYRZZH5  IS    '费用5入账账号';
COMMENT ON COLUMN APP_DWXX_EXT.FYZHLX5  IS     '费用5账号类型';
COMMENT ON COLUMN APP_DWXX_EXT.EXTFLD1  IS     '扩展字段1';
COMMENT ON COLUMN APP_DWXX_EXT.EXTFLD2  IS     '扩展字段2';
COMMENT ON COLUMN APP_DWXX_EXT.EXTFLD3  IS     '扩展字段3';
COMMENT ON COLUMN APP_DWXX_EXT.EXTFLD4  IS     '扩展字段4';
COMMENT ON COLUMN APP_DWXX_EXT.EXTFLD5  IS     '扩展字段5';
COMMENT ON COLUMN APP_DWXX_EXT.EXTFLD6  IS     '扩展字段6';
