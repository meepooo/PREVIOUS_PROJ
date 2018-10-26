drop table batch_dsdf_detail_his;
--==============================================================
-- Table: BATCH_DSDF_DETAIL_HIS
--==============================================================
create table BATCH_DSDF_DETAIL_HIS
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
   constraint PK_BATCH_DSDF_DETAIL_HIS_1 primary key (PKRQ,PTPCH,LSXH,WJXH)
) partition by range(pkrq) (
  partition P000000 starting '00000000' ending '00000000');

CREATE INDEX BATCH_DSDF_DETAIL_HIS_IDX1 ON BATCH_DSDF_DETAIL_HIS(ZJPCH,WBXH);
CREATE INDEX BATCH_DSDF_DETAIL_HIS_IDX2 ON BATCH_DSDF_DETAIL_HIS(WBPCH,WBXH);
CREATE INDEX BATCH_DSDF_DETAIL_HIS_IDX3 ON BATCH_DSDF_DETAIL_HIS(PKRQ,YWBH);

comment on table BATCH_DSDF_DETAIL_HIS is
'�������ո�ҵ���';

comment on column BATCH_DSDF_DETAIL_HIS.PKRQ is '��������';
comment on column BATCH_DSDF_DETAIL_HIS.PTPCH is 'ƽ̨���κ�';
comment on column BATCH_DSDF_DETAIL_HIS.LSXH is '��ˮ���';
comment on column BATCH_DSDF_DETAIL_HIS.WJXH is '�ļ����';
comment on column BATCH_DSDF_DETAIL_HIS.JDBZ is '�����־';
comment on column BATCH_DSDF_DETAIL_HIS.ZYDM is 'ժҪ����';
comment on column BATCH_DSDF_DETAIL_HIS.YWBH is 'ҵ����';
comment on column BATCH_DSDF_DETAIL_HIS.DWBH is '��λ���';
comment on column BATCH_DSDF_DETAIL_HIS.JLBS is '��¼��ʶ';
comment on column BATCH_DSDF_DETAIL_HIS.YHH1 is '�û���';
comment on column BATCH_DSDF_DETAIL_HIS.YHXM is '�û�����';
comment on column BATCH_DSDF_DETAIL_HIS.ZJHM is '֤������';
comment on column BATCH_DSDF_DETAIL_HIS.YHZH is '�û��ʻ�';
comment on column BATCH_DSDF_DETAIL_HIS.FKRZH is '�������˺�';
comment on column BATCH_DSDF_DETAIL_HIS.FKRXM is '����������';
comment on column BATCH_DSDF_DETAIL_HIS.FKHHH is '�������к�';
comment on column BATCH_DSDF_DETAIL_HIS.FKHHM is '����������';
comment on column BATCH_DSDF_DETAIL_HIS.SKRZH is '�տ����˺�';
comment on column BATCH_DSDF_DETAIL_HIS.SKRXM is '�տ�������';
comment on column BATCH_DSDF_DETAIL_HIS.SKHHH is '�տ����к�';
comment on column BATCH_DSDF_DETAIL_HIS.SKHHM is '�տ�������';
comment on column BATCH_DSDF_DETAIL_HIS.JYJE is '���׽��';
comment on column BATCH_DSDF_DETAIL_HIS.SJJE is 'ʵ�ʽ��';
comment on column BATCH_DSDF_DETAIL_HIS.PTLSH is 'ƽ̨��ˮ��';
comment on column BATCH_DSDF_DETAIL_HIS.YWLSH is 'ҵ����ˮ��';
comment on column BATCH_DSDF_DETAIL_HIS.JYLSH is '������ˮ��';
comment on column BATCH_DSDF_DETAIL_HIS.PTDM is 'ƽ̨����';
comment on column BATCH_DSDF_DETAIL_HIS.BFKKBZ is '���ֿۿ��־';
comment on column BATCH_DSDF_DETAIL_HIS.BZ is '����';
comment on column BATCH_DSDF_DETAIL_HIS.ZWRQ is '��������';
comment on column BATCH_DSDF_DETAIL_HIS.GYLSH is '��Ա��ˮ��';
comment on column BATCH_DSDF_DETAIL_HIS.CZLSH is '������ˮ��';
comment on column BATCH_DSDF_DETAIL_HIS.CZRQ is '��������';
comment on column BATCH_DSDF_DETAIL_HIS.DJXTRQ is '�Ǽ�ϵͳ����';
comment on column BATCH_DSDF_DETAIL_HIS.DJXTSJ is '�Ǽ�ϵͳʱ��';
comment on column BATCH_DSDF_DETAIL_HIS.ZHGXRQ is '����������';
comment on column BATCH_DSDF_DETAIL_HIS.ZHGXSJ is '������ʱ��';
comment on column BATCH_DSDF_DETAIL_HIS.BYZD1 is '�����ֶ�1';
comment on column BATCH_DSDF_DETAIL_HIS.BYZD2 is '�����ֶ�2';
comment on column BATCH_DSDF_DETAIL_HIS.BYZD3 is '�����ֶ�3';
comment on column BATCH_DSDF_DETAIL_HIS.BYZD4 is '�����ֶ�4';
comment on column BATCH_DSDF_DETAIL_HIS.JLZT is '��¼״̬';
comment on column BATCH_DSDF_DETAIL_HIS.ZJYXQ is '֤����Ч��';
comment on column BATCH_DSDF_DETAIL_HIS.ZJLX is '֤������';
comment on column BATCH_DSDF_DETAIL_HIS.XB is '�Ա�';
comment on column BATCH_DSDF_DETAIL_HIS.CSRQ is '��������';
comment on column BATCH_DSDF_DETAIL_HIS.FZJG is '��֤����';
comment on column BATCH_DSDF_DETAIL_HIS.DZ is '��ַ';
comment on column BATCH_DSDF_DETAIL_HIS.YZBM is '��������';
comment on column BATCH_DSDF_DETAIL_HIS.DHHM is '�绰����';
comment on column BATCH_DSDF_DETAIL.ZY is 'ְҵ';
comment on column BATCH_DSDF_DETAIL.GZDW is '������λ';
comment on column BATCH_DSDF_DETAIL.SSJMSF is '˰�վ������';
comment on column BATCH_DSDF_DETAIL_HIS.KXRQ is '��������';
comment on column BATCH_DSDF_DETAIL_HIS.YWJE is 'ҵ����';
comment on column BATCH_DSDF_DETAIL_HIS.SJYWJE is 'ʵ��ҵ����';
comment on column BATCH_DSDF_DETAIL_HIS.FYJE1 is '����1';
comment on column BATCH_DSDF_DETAIL_HIS.SJFYJE1 is 'ʵ�ʷ���1';
comment on column BATCH_DSDF_DETAIL_HIS.FYJE2 is '����2';
comment on column BATCH_DSDF_DETAIL_HIS.SJFYJE2 is 'ʵ�ʷ���2';
comment on column BATCH_DSDF_DETAIL_HIS.FYJE3 is '����3';
comment on column BATCH_DSDF_DETAIL_HIS.SJFYJE3 is 'ʵ�ʷ���3';
comment on column BATCH_DSDF_DETAIL_HIS.FYJE4 is '����4';
comment on column BATCH_DSDF_DETAIL_HIS.SJFYJE4 is 'ʵ�ʷ���4';
comment on column BATCH_DSDF_DETAIL_HIS.FYJE5 is '����5';
comment on column BATCH_DSDF_DETAIL_HIS.SJFYJE5 is 'ʵ�ʷ���5';
comment on column BATCH_DSDF_DETAIL_HIS.SXFJE is '�����ѽ��';
comment on column BATCH_DSDF_DETAIL_HIS.SJSXFJE is 'ʵ�������ѽ��';
comment on column BATCH_DSDF_DETAIL_HIS.SHZT is '���״̬';
comment on column BATCH_DSDF_DETAIL_HIS.CLZT is '����״̬';
comment on column BATCH_DSDF_DETAIL_HIS.CGBZ is '�ɹ���־';
comment on column BATCH_DSDF_DETAIL_HIS.XYM is '��Ӧ��';
comment on column BATCH_DSDF_DETAIL_HIS.XYXX is '��Ӧ��Ϣ';
comment on column BATCH_DSDF_DETAIL_HIS.ZJRQ is '��������';
comment on column BATCH_DSDF_DETAIL_HIS.ZJSJ is '����ʱ��';
comment on column BATCH_DSDF_DETAIL_HIS.ZJLSH is '������ˮ��';
comment on column BATCH_DSDF_DETAIL_HIS.ZJXYM is '������Ӧ��';
comment on column BATCH_DSDF_DETAIL_HIS.ZJXYXX is '������Ӧ��Ϣ';
comment on column BATCH_DSDF_DETAIL_HIS.DSFRQ is '����������';
comment on column BATCH_DSDF_DETAIL_HIS.DSFSJ is '������ʱ��';
comment on column BATCH_DSDF_DETAIL_HIS.DSFLSH is '��������ˮ��';
comment on column BATCH_DSDF_DETAIL_HIS.DSFXYM is '��������Ӧ��';
comment on column BATCH_DSDF_DETAIL_HIS.DSFXYXX is '��������Ӧ��Ϣ';
comment on column BATCH_DSDF_DETAIL_HIS.WBRQ is '�ⲿ����';
comment on column BATCH_DSDF_DETAIL_HIS.WBPCH is '�ⲿ���κ�';
comment on column BATCH_DSDF_DETAIL_HIS.WBXH is '�ⲿ���';
comment on column BATCH_DSDF_DETAIL_HIS.ZJPCH is '�������κ�';
comment on column BATCH_DSDF_DETAIL_HIS.KZZD1 is '��չ�ֶ�1';
comment on column BATCH_DSDF_DETAIL_HIS.KZZD2 is '��չ�ֶ�2';
comment on column BATCH_DSDF_DETAIL_HIS.KZZD3 is '��չ�ֶ�3';
comment on column BATCH_DSDF_DETAIL_HIS.KZZD4 is '��չ�ֶ�4';
comment on column BATCH_DSDF_DETAIL_HIS.KZZD5 is '��չ�ֶ�5';
comment on column BATCH_DSDF_DETAIL_HIS.KZZD6 is '��չ�ֶ�6';
comment on column BATCH_DSDF_DETAIL_HIS.KZZD7 is '��չ�ֶ�7';
comment on column BATCH_DSDF_DETAIL_HIS.KZZD8 is '��չ�ֶ�8';
comment on column BATCH_DSDF_DETAIL_HIS.KZZD9 is '��չ�ֶ�9';
comment on column BATCH_DSDF_DETAIL_HIS.KZZD10 is '��չ�ֶ�10';

