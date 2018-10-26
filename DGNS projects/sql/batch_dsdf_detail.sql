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
'�������ո�ҵ���';

comment on column BATCH_DSDF_DETAIL.PKRQ is '��������';
comment on column BATCH_DSDF_DETAIL.PTPCH is 'ƽ̨���κ�';
comment on column BATCH_DSDF_DETAIL.LSXH is '��ˮ���';
comment on column BATCH_DSDF_DETAIL.WJXH is '�ļ����';
comment on column BATCH_DSDF_DETAIL.JDBZ is '�����־';
comment on column BATCH_DSDF_DETAIL.ZYDM is 'ժҪ����';
comment on column BATCH_DSDF_DETAIL.YWBH is 'ҵ����';
comment on column BATCH_DSDF_DETAIL.DWBH is '��λ���';
comment on column BATCH_DSDF_DETAIL.JLBS is '��¼��ʶ';
comment on column BATCH_DSDF_DETAIL.YHH1 is '�û���';
comment on column BATCH_DSDF_DETAIL.YHXM is '�û�����';
comment on column BATCH_DSDF_DETAIL.ZJHM is '֤������';
comment on column BATCH_DSDF_DETAIL.YHZH is '�û��ʻ�';
comment on column BATCH_DSDF_DETAIL.FKRZH is '�������˺�';
comment on column BATCH_DSDF_DETAIL.FKRXM is '����������';
comment on column BATCH_DSDF_DETAIL.FKHHH is '�������к�';
comment on column BATCH_DSDF_DETAIL.FKHHM is '����������';
comment on column BATCH_DSDF_DETAIL.SKRZH is '�տ����˺�';
comment on column BATCH_DSDF_DETAIL.SKRXM is '�տ�������';
comment on column BATCH_DSDF_DETAIL.SKHHH is '�տ����к�';
comment on column BATCH_DSDF_DETAIL.SKHHM is '�տ�������';
comment on column BATCH_DSDF_DETAIL.JYJE is '���׽��';
comment on column BATCH_DSDF_DETAIL.SJJE is 'ʵ�ʽ��';
comment on column BATCH_DSDF_DETAIL.PTLSH is 'ƽ̨��ˮ��';
comment on column BATCH_DSDF_DETAIL.YWLSH is 'ҵ����ˮ��';
comment on column BATCH_DSDF_DETAIL.JYLSH is '������ˮ��';
comment on column BATCH_DSDF_DETAIL.PTDM is 'ƽ̨����';
comment on column BATCH_DSDF_DETAIL.BFKKBZ is '���ֿۿ��־';
comment on column BATCH_DSDF_DETAIL.BZ is '����';
comment on column BATCH_DSDF_DETAIL.ZWRQ is '��������';
comment on column BATCH_DSDF_DETAIL.GYLSH is '��Ա��ˮ��';
comment on column BATCH_DSDF_DETAIL.CZLSH is '������ˮ��';
comment on column BATCH_DSDF_DETAIL.CZRQ is '��������';
comment on column BATCH_DSDF_DETAIL.DJXTRQ is '�Ǽ�ϵͳ����';
comment on column BATCH_DSDF_DETAIL.DJXTSJ is '�Ǽ�ϵͳʱ��';
comment on column BATCH_DSDF_DETAIL.ZHGXRQ is '����������';
comment on column BATCH_DSDF_DETAIL.ZHGXSJ is '������ʱ��';
comment on column BATCH_DSDF_DETAIL.BYZD1 is '�����ֶ�1';
comment on column BATCH_DSDF_DETAIL.BYZD2 is '�����ֶ�2';
comment on column BATCH_DSDF_DETAIL.BYZD3 is '�����ֶ�3';
comment on column BATCH_DSDF_DETAIL.BYZD4 is '�����ֶ�4';
comment on column BATCH_DSDF_DETAIL.JLZT is '��¼״̬';
comment on column BATCH_DSDF_DETAIL.ZJYXQ is '֤����Ч��';
comment on column BATCH_DSDF_DETAIL.ZJLX is '֤������';
comment on column BATCH_DSDF_DETAIL.XB is '�Ա�';
comment on column BATCH_DSDF_DETAIL.CSRQ is '��������';
comment on column BATCH_DSDF_DETAIL.FZJG is '��֤����';
comment on column BATCH_DSDF_DETAIL.DZ is '��ַ';
comment on column BATCH_DSDF_DETAIL.YZBM is '��������';
comment on column BATCH_DSDF_DETAIL.DHHM is '�绰����';
comment on column BATCH_DSDF_DETAIL.ZY is 'ְҵ';
comment on column BATCH_DSDF_DETAIL.GZDW is '������λ';
comment on column BATCH_DSDF_DETAIL.SSJMSF is '˰�վ������ 1-��Ϊ�й�˰�վ��� 2-��Ϊ���й�˰�վ��� 3-�����й�˰�վ��������������ң�������˰�վ���';
comment on column BATCH_DSDF_DETAIL.KXRQ is '��������';
comment on column BATCH_DSDF_DETAIL.YWJE is 'ҵ����';
comment on column BATCH_DSDF_DETAIL.SJYWJE is 'ʵ��ҵ����';
comment on column BATCH_DSDF_DETAIL.FYJE1 is '����1';
comment on column BATCH_DSDF_DETAIL.SJFYJE1 is 'ʵ�ʷ���1';
comment on column BATCH_DSDF_DETAIL.FYJE2 is '����2';
comment on column BATCH_DSDF_DETAIL.SJFYJE2 is 'ʵ�ʷ���2';
comment on column BATCH_DSDF_DETAIL.FYJE3 is '����3';
comment on column BATCH_DSDF_DETAIL.SJFYJE3 is 'ʵ�ʷ���3';
comment on column BATCH_DSDF_DETAIL.FYJE4 is '����4';
comment on column BATCH_DSDF_DETAIL.SJFYJE4 is 'ʵ�ʷ���4';
comment on column BATCH_DSDF_DETAIL.FYJE5 is '����5';
comment on column BATCH_DSDF_DETAIL.SJFYJE5 is 'ʵ�ʷ���5';
comment on column BATCH_DSDF_DETAIL.SXFJE is '�����ѽ��';
comment on column BATCH_DSDF_DETAIL.SJSXFJE is 'ʵ�������ѽ��';
comment on column BATCH_DSDF_DETAIL.SHZT is '���״̬';
comment on column BATCH_DSDF_DETAIL.CLZT is '����״̬';
comment on column BATCH_DSDF_DETAIL.CGBZ is '�ɹ���־';
comment on column BATCH_DSDF_DETAIL.XYM is '��Ӧ��';
comment on column BATCH_DSDF_DETAIL.XYXX is '��Ӧ��Ϣ';
comment on column BATCH_DSDF_DETAIL.ZJRQ is '��������';
comment on column BATCH_DSDF_DETAIL.ZJSJ is '����ʱ��';
comment on column BATCH_DSDF_DETAIL.ZJLSH is '������ˮ��';
comment on column BATCH_DSDF_DETAIL.ZJXYM is '������Ӧ��';
comment on column BATCH_DSDF_DETAIL.ZJXYXX is '������Ӧ��Ϣ';
comment on column BATCH_DSDF_DETAIL.DSFRQ is '����������';
comment on column BATCH_DSDF_DETAIL.DSFSJ is '������ʱ��';
comment on column BATCH_DSDF_DETAIL.DSFLSH is '��������ˮ��';
comment on column BATCH_DSDF_DETAIL.DSFXYM is '��������Ӧ��';
comment on column BATCH_DSDF_DETAIL.DSFXYXX is '��������Ӧ��Ϣ';
comment on column BATCH_DSDF_DETAIL.WBRQ is '�ⲿ����';
comment on column BATCH_DSDF_DETAIL.WBPCH is '�ⲿ���κ�';
comment on column BATCH_DSDF_DETAIL.WBXH is '�ⲿ���';
comment on column BATCH_DSDF_DETAIL.ZJPCH is '�������κ�';
comment on column BATCH_DSDF_DETAIL.KZZD1 is '��չ�ֶ�1';
comment on column BATCH_DSDF_DETAIL.KZZD2 is '��չ�ֶ�2';
comment on column BATCH_DSDF_DETAIL.KZZD3 is '��չ�ֶ�3';
comment on column BATCH_DSDF_DETAIL.KZZD4 is '��չ�ֶ�4';
comment on column BATCH_DSDF_DETAIL.KZZD5 is '��չ�ֶ�5';
comment on column BATCH_DSDF_DETAIL.KZZD6 is '��չ�ֶ�6';
comment on column BATCH_DSDF_DETAIL.KZZD7 is '��չ�ֶ�7';
comment on column BATCH_DSDF_DETAIL.KZZD8 is '��չ�ֶ�8';
comment on column BATCH_DSDF_DETAIL.KZZD9 is '��չ�ֶ�9';
comment on column BATCH_DSDF_DETAIL.KZZD10 is '��չ�ֶ�10';

