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
COMMENT ON TABLE agent_yxt_jfjl IS '��Уͨ�ɷѼ�¼�ǼǱ�';
COMMENT ON COLUMN agent_yxt_jfjl.jgh IS '������';        
COMMENT ON COLUMN agent_yxt_jfjl.shh IS '�̻���';            
COMMENT ON COLUMN agent_yxt_jfjl.shmc IS '�̻�����';        
COMMENT ON COLUMN agent_yxt_jfjl.shjth IS '�̻����ź�';        
COMMENT ON COLUMN agent_yxt_jfjl.xxlx IS '��Ϣ����';        
COMMENT ON COLUMN agent_yxt_jfjl.qdlx IS '��������';
COMMENT ON COLUMN agent_yxt_jfjl.pch IS '���κ�';        
COMMENT ON COLUMN agent_yxt_jfjl.ddh IS '������';            
COMMENT ON COLUMN agent_yxt_jfjl.yddh IS 'ԭ������';        
COMMENT ON COLUMN agent_yxt_jfjl.qdddh IS '����������';        
COMMENT ON COLUMN agent_yxt_jfjl.jsddh IS '����������';        
COMMENT ON COLUMN agent_yxt_jfjl.kpp IS '��Ʒ��';            
COMMENT ON COLUMN agent_yxt_jfjl.jylx IS '��������';        
COMMENT ON COLUMN agent_yxt_jfjl.jyje IS '���׽��';        
COMMENT ON COLUMN agent_yxt_jfjl.jybz IS '���ױ���';
COMMENT ON COLUMN agent_yxt_jfjl.jyrq IS '��������';        
COMMENT ON COLUMN agent_yxt_jfjl.jysj IS '����ʱ��';        
COMMENT ON COLUMN agent_yxt_jfjl.yjylx IS 'ԭ��������';        
COMMENT ON COLUMN agent_yxt_jfjl.yjsddh IS 'ԭ����������';        
COMMENT ON COLUMN agent_yxt_jfjl.jym IS '������';            
COMMENT ON COLUMN agent_yxt_jfjl.zdh IS '�ն˺�';            
COMMENT ON COLUMN agent_yxt_jfjl.xsxm IS 'ѧ������';    
COMMENT ON COLUMN agent_yxt_jfjl.xsbj IS 'ѧ���༶';
COMMENT ON COLUMN agent_yxt_jfjl.jzsjh IS '�ҳ��ֻ�����';
COMMENT ON COLUMN agent_yxt_jfjl.hjje IS '�ϼƽ��';                
COMMENT ON COLUMN agent_yxt_jfjl.zkje IS '�ۿ۽��';    
COMMENT ON COLUMN agent_yxt_jfjl.sjyh IS '�̻��Ż�';        
COMMENT ON COLUMN agent_yxt_jfjl.qdyh IS '�����Ż�';        
COMMENT ON COLUMN agent_yxt_jfjl.ddsfje IS '����ʵ�����';        
COMMENT ON COLUMN agent_yxt_jfjl.wbddh IS '�ⲿ������';        
COMMENT ON COLUMN agent_yxt_jfjl.ydm IS 'Ӧ����';            
COMMENT ON COLUMN agent_yxt_jfjl.fkh IS '������';            
COMMENT ON COLUMN agent_yxt_jfjl.sqm IS '��Ȩ��';            
COMMENT ON COLUMN agent_yxt_jfjl.yhwx_id IS '�û�΢��ID';        
COMMENT ON COLUMN agent_yxt_jfjl.zshgz_id IS '���̻�����ID';    
COMMENT ON COLUMN agent_yxt_jfjl.is_shzj IS '�����Ƿ��漰�̻��ʽ�';    
COMMENT ON COLUMN agent_yxt_jfjl.kwzzh IS '���п���/΢�š�֧�����˺�';        


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
COMMENT ON TABLE APP_DWXX_EXT IS '��λ��Ϣ��չ��';
COMMENT ON COLUMN APP_DWXX_EXT.DWBH  IS   '��λ���';
COMMENT ON COLUMN APP_DWXX_EXT.SXFBZ  IS     '�����ѱ�־ 0-��ȡ��1-����';
COMMENT ON COLUMN APP_DWXX_EXT.SXFGSBZ  IS     '�����ѹ�����־ 0-��λ��1-������2-����';
COMMENT ON COLUMN APP_DWXX_EXT.SXFKHFS  IS     '�����ѿۻ���ʽ 0-�Զ���1-�ֽ�';
COMMENT ON COLUMN APP_DWXX_EXT.SXFZHLX  IS    '�����Ѹ����˺�����';
COMMENT ON COLUMN APP_DWXX_EXT.SXFFKZH  IS     '�����Ѹ����˺�';
COMMENT ON COLUMN APP_DWXX_EXT.SXFFKZHMC  IS     '�����Ѹ����˺�����';
COMMENT ON COLUMN APP_DWXX_EXT.SXFJSFS  IS     '�����Ѽ��㷽ʽ 0-������ 1-������';
COMMENT ON COLUMN APP_DWXX_EXT.SXFJSCS  IS     '�����Ѽ������';
COMMENT ON COLUMN APP_DWXX_EXT.SXFJEXX  IS     '�����ѽ������';
COMMENT ON COLUMN APP_DWXX_EXT.SXFJESX  IS      '�����ѽ������';
COMMENT ON COLUMN APP_DWXX_EXT.KHQYFS  IS     '�ͻ�ǩԼ��ʽ 0-���� 1-ί�е�λ 2-���л�ί�е�λ';
COMMENT ON COLUMN APP_DWXX_EXT.KKFS  IS    '���ֿۿ��־';
COMMENT ON COLUMN APP_DWXX_EXT.TZBZ  IS     '͸֧��־';
COMMENT ON COLUMN APP_DWXX_EXT.TZED  IS     '͸֧���';
COMMENT ON COLUMN APP_DWXX_EXT.TZDFZH  IS    '�渶�˺�';
COMMENT ON COLUMN APP_DWXX_EXT.YJBZ  IS      'Ԥ����־';
COMMENT ON COLUMN APP_DWXX_EXT.YEYBBL  IS     '���Ԥ������';
COMMENT ON COLUMN APP_DWXX_EXT.JCHMBZ  IS     '��黧����־';
COMMENT ON COLUMN APP_DWXX_EXT.YQBZ  IS     '��ǩ��־';
COMMENT ON COLUMN APP_DWXX_EXT.YQMY  IS     '��ǩ��Կ';
COMMENT ON COLUMN APP_DWXX_EXT.FYYWLX1  IS    '����1ҵ������';
COMMENT ON COLUMN APP_DWXX_EXT.FYRZZH1  IS     '����1�����˺�';
COMMENT ON COLUMN APP_DWXX_EXT.FYZHLX1  IS     '����1�˺�����';
COMMENT ON COLUMN APP_DWXX_EXT.FYYWLX2  IS     '����2ҵ������';
COMMENT ON COLUMN APP_DWXX_EXT.FYRZZH2  IS     '����2�����˺�';
COMMENT ON COLUMN APP_DWXX_EXT.FYZHLX2  IS    '����2�˺�����';
COMMENT ON COLUMN APP_DWXX_EXT.FYYWLX3  IS     '����3ҵ������';
COMMENT ON COLUMN APP_DWXX_EXT.FYRZZH3  IS     '����3�����˺�';
COMMENT ON COLUMN APP_DWXX_EXT.FYZHLX3  IS     '����3�˺�����';
COMMENT ON COLUMN APP_DWXX_EXT.FYYWLX4  IS     '����4ҵ������';
COMMENT ON COLUMN APP_DWXX_EXT.FYRZZH4  IS     '����4�����˺�';
COMMENT ON COLUMN APP_DWXX_EXT.FYZHLX4  IS     '����4�˺�����';
COMMENT ON COLUMN APP_DWXX_EXT.FYYWLX5  IS     '����5ҵ������';
COMMENT ON COLUMN APP_DWXX_EXT.FYRZZH5  IS    '����5�����˺�';
COMMENT ON COLUMN APP_DWXX_EXT.FYZHLX5  IS     '����5�˺�����';
COMMENT ON COLUMN APP_DWXX_EXT.EXTFLD1  IS     '��չ�ֶ�1';
COMMENT ON COLUMN APP_DWXX_EXT.EXTFLD2  IS     '��չ�ֶ�2';
COMMENT ON COLUMN APP_DWXX_EXT.EXTFLD3  IS     '��չ�ֶ�3';
COMMENT ON COLUMN APP_DWXX_EXT.EXTFLD4  IS     '��չ�ֶ�4';
COMMENT ON COLUMN APP_DWXX_EXT.EXTFLD5  IS     '��չ�ֶ�5';
COMMENT ON COLUMN APP_DWXX_EXT.EXTFLD6  IS     '��չ�ֶ�6';
