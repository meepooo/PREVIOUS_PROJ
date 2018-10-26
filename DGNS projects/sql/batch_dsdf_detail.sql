drop table batch_dsdf_detail;
--==============================================================
-- Table: BATCH_DSDF_DETAIL
--==============================================================
create table BATCH_DSDF_DETAIL
(
   PKRQ                 CHAR(8) NOT NULL,    
   PTPCH                CHAR(8) NOT NULL,    
   LSXH                 INTEGER NOT NULL,
   WJXH                 INTEGER NOT NULL,
   JDBZ                 CHAR(1),   
   ZYDM                 CHAR(16),   
   YWBH                 CHAR(16),   
   DWBH                 CHAR(16),   
   JLBS                 CHAR(32),   
   YHH1                 CHAR(32),   
   YHXM                 CHAR(200),   
   ZJHM                 CHAR(32),   
   YHZH                 CHAR(32),   
   FKRZH                CHAR(32),   
   FKRXM                CHAR(200),   
   FKHHH                CHAR(12),   
   FKHHM                CHAR(200),   
   SKRZH                CHAR(32),   
   SKRXM                CHAR(200),   
   SKHHH                CHAR(12),   
   SKHHM                CHAR(200),   
   JYJE                 DECIMAL(15,2),   
   SJJE                 DECIMAL(15,2),   
   PTLSH                CHAR(32) NOT NULL,    
   YWLSH                CHAR(32) NOT NULL,    
   JYLSH                CHAR(32) NOT NULL,    
   PTDM                 CHAR(32),   
   BFKKBZ               CHAR(1),   
   BZ                   CHAR(8),   
   GYLSH                CHAR(32),   
   ZWRQ                 CHAR(8),   
   CZLSH                CHAR(32),   
   CZRQ                 CHAR(8),   
   DJXTRQ               CHAR(8),   
   DJXTSJ               CHAR(6),   
   ZHGXRQ               CHAR(8),   
   ZHGXSJ               CHAR(6),   
   BYZD1                CHAR(40),   
   BYZD2                CHAR(40),   
   BYZD3                DECIMAL(15,2),   
   BYZD4                INTEGER,
   JLZT                 CHAR(8),   
   ZJYXQ                CHAR(8),   
   ZJLX                 CHAR(3),   
   XB                   CHAR(1),   
   CSRQ                 CHAR(8),   
   FZJG                 CHAR(60),   
   DZ                   CHAR(120),   
   YZBM                 CHAR(7),   
   DHHM                 CHAR(15),   
   ZY                   CHAR(40),   
   GZDW                 CHAR(120),   
   SSJMSF               CHAR(3),   
   KXRQ                 CHAR(8),   
   YWJE                 DECIMAL(15,2),   
   SJYWJE               DECIMAL(15,2),   
   FYJE1                DECIMAL(15,2),   
   SJFYJE1              DECIMAL(15,2),   
   FYJE2                DECIMAL(15,2),   
   SJFYJE2              DECIMAL(15,2),   
   FYJE3                DECIMAL(15,2),   
   SJFYJE3              DECIMAL(15,2),   
   FYJE4                DECIMAL(15,2),   
   SJFYJE4              DECIMAL(15,2),   
   FYJE5                DECIMAL(15,2),   
   SJFYJE5              DECIMAL(15,2),   
   SXFJE                DECIMAL(15,2),   
   SJSXFJE              DECIMAL(15,2),   
   SHZT                 CHAR(1),   
   CLZT                 CHAR(1),   
   CGBZ                 CHAR(1),   
   XYM                  CHAR(8),   
   XYXX                 CHAR(60),   
   ZJRQ                 CHAR(8),   
   ZJSJ                 CHAR(6),   
   ZJLSH                CHAR(32),   
   ZJXYM                CHAR(8),   
   ZJXYXX               CHAR(60),   
   DSFRQ                CHAR(8),   
   DSFSJ                CHAR(6),   
   DSFLSH               CHAR(32),   
   DSFXYM               CHAR(8),   
   DSFXYXX              CHAR(60),   
   WBRQ                 CHAR(8),   
   WBPCH                CHAR(32) NOT NULL,    
   WBXH                 INTEGER NOT NULL,
   ZJPCH                CHAR(32) NOT NULL,    
   KZZD1                VARCHAR(10),   
   KZZD2                VARCHAR(20),   
   KZZD3                VARCHAR(50),   
   KZZD4                VARCHAR(100),   
   KZZD5                VARCHAR(200),   
   KZZD6                VARCHAR(256),   
   KZZD7                VARCHAR(512),   
   KZZD8                VARCHAR(1024),   
   KZZD9                INTEGER,
   KZZD10               DECIMAL(20,2),
   constraint PK_BATCH_DSDF_DETAIL_1 primary key (PKRQ,PTPCH,LSXH,WJXH)
);

CREATE INDEX BATCH_DSDF_DETAIL_IDX1 ON BATCH_DSDF_DETAIL(ZJPCH,WBXH);
CREATE INDEX BATCH_DSDF_DETAIL_IDX2 ON BATCH_DSDF_DETAIL(WBPCH,WBXH);
CREATE INDEX BATCH_DSDF_DETAIL_IDX3 ON BATCH_DSDF_DETAIL(PKRQ,YWBH);
CREATE INDEX BATCH_DSDF_DETAIL_IDX4 ON BATCH_DSDF_DETAIL(PKRQ,PTPCH,SHZT,CLZT);

comment on table BATCH_DSDF_DETAIL is
'批量代收付业务表';

comment on column BATCH_DSDF_DETAIL.PKRQ is '批扣日期';
comment on column BATCH_DSDF_DETAIL.PTPCH is '平台批次号';
comment on column BATCH_DSDF_DETAIL.LSXH is '流水序号';
comment on column BATCH_DSDF_DETAIL.WJXH is '文件序号';
comment on column BATCH_DSDF_DETAIL.JDBZ is '借贷标志';
comment on column BATCH_DSDF_DETAIL.ZYDM is '摘要代码';
comment on column BATCH_DSDF_DETAIL.YWBH is '业务编号';
comment on column BATCH_DSDF_DETAIL.DWBH is '单位编号';
comment on column BATCH_DSDF_DETAIL.JLBS is '记录标识';
comment on column BATCH_DSDF_DETAIL.YHH1 is '用户号';
comment on column BATCH_DSDF_DETAIL.YHXM is '用户姓名';
comment on column BATCH_DSDF_DETAIL.ZJHM is '证件号码';
comment on column BATCH_DSDF_DETAIL.YHZH is '用户帐户';
comment on column BATCH_DSDF_DETAIL.FKRZH is '付款人账号';
comment on column BATCH_DSDF_DETAIL.FKRXM is '付款人姓名';
comment on column BATCH_DSDF_DETAIL.FKHHH is '付款行行号';
comment on column BATCH_DSDF_DETAIL.FKHHM is '付款行行名';
comment on column BATCH_DSDF_DETAIL.SKRZH is '收款人账号';
comment on column BATCH_DSDF_DETAIL.SKRXM is '收款人姓名';
comment on column BATCH_DSDF_DETAIL.SKHHH is '收款行行号';
comment on column BATCH_DSDF_DETAIL.SKHHM is '收款行行名';
comment on column BATCH_DSDF_DETAIL.JYJE is '交易金额';
comment on column BATCH_DSDF_DETAIL.SJJE is '实际金额';
comment on column BATCH_DSDF_DETAIL.PTLSH is '平台流水号';
comment on column BATCH_DSDF_DETAIL.YWLSH is '业务流水号';
comment on column BATCH_DSDF_DETAIL.JYLSH is '交易流水号';
comment on column BATCH_DSDF_DETAIL.PTDM is '平台代码';
comment on column BATCH_DSDF_DETAIL.BFKKBZ is '部分扣款标志';
comment on column BATCH_DSDF_DETAIL.BZ is '币种';
comment on column BATCH_DSDF_DETAIL.ZWRQ is '账务日期';
comment on column BATCH_DSDF_DETAIL.GYLSH is '柜员流水号';
comment on column BATCH_DSDF_DETAIL.CZLSH is '冲正流水号';
comment on column BATCH_DSDF_DETAIL.CZRQ is '冲正日期';
comment on column BATCH_DSDF_DETAIL.DJXTRQ is '登记系统日期';
comment on column BATCH_DSDF_DETAIL.DJXTSJ is '登记系统时间';
comment on column BATCH_DSDF_DETAIL.ZHGXRQ is '最后更新日期';
comment on column BATCH_DSDF_DETAIL.ZHGXSJ is '最后更新时间';
comment on column BATCH_DSDF_DETAIL.BYZD1 is '备用字段1';
comment on column BATCH_DSDF_DETAIL.BYZD2 is '备用字段2';
comment on column BATCH_DSDF_DETAIL.BYZD3 is '备用字段3';
comment on column BATCH_DSDF_DETAIL.BYZD4 is '备用字段4';
comment on column BATCH_DSDF_DETAIL.JLZT is '记录状态';
comment on column BATCH_DSDF_DETAIL.ZJYXQ is '证件有效期';
comment on column BATCH_DSDF_DETAIL.ZJLX is '证件类型';
comment on column BATCH_DSDF_DETAIL.XB is '性别';
comment on column BATCH_DSDF_DETAIL.CSRQ is '出生日期';
comment on column BATCH_DSDF_DETAIL.FZJG is '发证机关';
comment on column BATCH_DSDF_DETAIL.DZ is '地址';
comment on column BATCH_DSDF_DETAIL.YZBM is '邮政编码';
comment on column BATCH_DSDF_DETAIL.DHHM is '电话号码';
comment on column BATCH_DSDF_DETAIL.ZY is '职业';
comment on column BATCH_DSDF_DETAIL.GZDW is '工作单位';
comment on column BATCH_DSDF_DETAIL.SSJMSF is '税收居民身份 1-仅为中国税收居民 2-仅为非中国税收居民 3-既是中国税收居民又是其他国家（地区）税收居民';
comment on column BATCH_DSDF_DETAIL.KXRQ is '款项日期';
comment on column BATCH_DSDF_DETAIL.YWJE is '业务金额';
comment on column BATCH_DSDF_DETAIL.SJYWJE is '实际业务金额';
comment on column BATCH_DSDF_DETAIL.FYJE1 is '费用1';
comment on column BATCH_DSDF_DETAIL.SJFYJE1 is '实际费用1';
comment on column BATCH_DSDF_DETAIL.FYJE2 is '费用2';
comment on column BATCH_DSDF_DETAIL.SJFYJE2 is '实际费用2';
comment on column BATCH_DSDF_DETAIL.FYJE3 is '费用3';
comment on column BATCH_DSDF_DETAIL.SJFYJE3 is '实际费用3';
comment on column BATCH_DSDF_DETAIL.FYJE4 is '费用4';
comment on column BATCH_DSDF_DETAIL.SJFYJE4 is '实际费用4';
comment on column BATCH_DSDF_DETAIL.FYJE5 is '费用5';
comment on column BATCH_DSDF_DETAIL.SJFYJE5 is '实际费用5';
comment on column BATCH_DSDF_DETAIL.SXFJE is '手续费金额';
comment on column BATCH_DSDF_DETAIL.SJSXFJE is '实际手续费金额';
comment on column BATCH_DSDF_DETAIL.SHZT is '审核状态';
comment on column BATCH_DSDF_DETAIL.CLZT is '处理状态';
comment on column BATCH_DSDF_DETAIL.CGBZ is '成功标志';
comment on column BATCH_DSDF_DETAIL.XYM is '响应码';
comment on column BATCH_DSDF_DETAIL.XYXX is '响应信息';
comment on column BATCH_DSDF_DETAIL.ZJRQ is '主机日期';
comment on column BATCH_DSDF_DETAIL.ZJSJ is '主机时间';
comment on column BATCH_DSDF_DETAIL.ZJLSH is '主机流水号';
comment on column BATCH_DSDF_DETAIL.ZJXYM is '主机响应吗';
comment on column BATCH_DSDF_DETAIL.ZJXYXX is '主机响应信息';
comment on column BATCH_DSDF_DETAIL.DSFRQ is '第三方日期';
comment on column BATCH_DSDF_DETAIL.DSFSJ is '第三方时间';
comment on column BATCH_DSDF_DETAIL.DSFLSH is '第三方流水号';
comment on column BATCH_DSDF_DETAIL.DSFXYM is '第三方响应码';
comment on column BATCH_DSDF_DETAIL.DSFXYXX is '第三方响应信息';
comment on column BATCH_DSDF_DETAIL.WBRQ is '外部日期';
comment on column BATCH_DSDF_DETAIL.WBPCH is '外部批次号';
comment on column BATCH_DSDF_DETAIL.WBXH is '外部序号';
comment on column BATCH_DSDF_DETAIL.ZJPCH is '主机批次号';
comment on column BATCH_DSDF_DETAIL.KZZD1 is '扩展字段1';
comment on column BATCH_DSDF_DETAIL.KZZD2 is '扩展字段2';
comment on column BATCH_DSDF_DETAIL.KZZD3 is '扩展字段3';
comment on column BATCH_DSDF_DETAIL.KZZD4 is '扩展字段4';
comment on column BATCH_DSDF_DETAIL.KZZD5 is '扩展字段5';
comment on column BATCH_DSDF_DETAIL.KZZD6 is '扩展字段6';
comment on column BATCH_DSDF_DETAIL.KZZD7 is '扩展字段7';
comment on column BATCH_DSDF_DETAIL.KZZD8 is '扩展字段8';
comment on column BATCH_DSDF_DETAIL.KZZD9 is '扩展字段9';
comment on column BATCH_DSDF_DETAIL.KZZD10 is '扩展字段10';

