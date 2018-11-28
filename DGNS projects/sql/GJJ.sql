--���������ݱ�����
--��ҵ�������˻���Ϣ��
CREATE
    TABLE TBL_GJJ_DWZH
    (
        DWZH CHARACTER(32) NOT NULL,
        DWMC CHARACTER(100) NOT NULL,
        DWDM CHARACTER(32),
        JCRS INTEGER,
        JCJE DECIMAL(20,2),
        SSZJ CHARACTER(100),
        BZ CHARACTER(100),
        GXRQ CHARACTER(8),
        GXSJ CHARACTER(6),
        STAT CHARACTER(1),
        BY1 CHARACTER(20),
        BY2 CHARACTER(40),
        CONSTRAINT PK_TBL_GJJ_DWZH PRIMARY KEY (DWZH)
    );
COMMENT ON TABLE GAPSUSR.TBL_GJJ_DWZH        IS '��ҵ�������˻�';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_DWZH.DWZH IS '��λ�������˺�';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_DWZH.DWMC IS '��λ����������';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_DWZH.DWDM IS '��λ����';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_DWZH.JCRS IS '�ɴ�����';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_DWZH.JCJE IS '�ɴ���';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_DWZH.SSZJ IS '�������';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_DWZH.BZ   IS '��ע';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_DWZH.GXRQ IS '��������';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_DWZH.GXSJ IS '����ʱ��';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_DWZH.STAT IS '��¼״̬--0��Ч��1��Ч';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_DWZH.BY1  IS '����1';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_DWZH.BY2  IS '����2';
    
--����������˻���Ϣ    
CREATE
    TABLE TBL_GJJ_GDZH
    (
        ZHDM CHARACTER(32) NOT NULL,
        ZHMC CHARACTER(100) NOT NULL,
        ZHLX CHARACTER(1) NOT NULL,
        GXRQ CHARACTER(8),
        GXSJ CHARACTER(6),
        STAT CHARACTER(1) NOT NULL,
        BY1  CHARACTER(20),
        BY2  CHARACTER(40),
        CONSTRAINT PK_TBL_GJJ_GDZH PRIMARY KEY (ZHDM)
    );
COMMENT ON TABLE   GAPSUSR.TBL_GJJ_GDZH      IS  '����������˻���Ϣ��';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_GDZH.ZHDM IS  '����������˺�    ';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_GDZH.ZHMC IS  '����������˻�����';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_GDZH.ZHLX IS  '�˻�����          ';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_GDZH.GXRQ IS  '��������          ';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_GDZH.GXSJ IS  '����ʱ��          ';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_GDZH.STAT IS  '��¼״̬          ';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_GDZH.BY1  IS  '����1             ';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_GDZH.BY2  IS  '����2             ';

--������鼯��ˮ��Ϣ
CREATE
    TABLE TBL_GJJ_GJLS
    (
        PTLS CHARACTER(32) NOT NULL,
        YWLS CHARACTER(32),
        JYRQ CHARACTER(8),
        JYSJ CHARACTER(6),
        JYGY CHARACTER(10),
        SQGY CHARACTER(10),
        DWZH CHARACTER(32),
        DWMC CHARACTER(100),
        GJLX CHARACTER(1),
        WSBJ CHARACTER(1),
        JDBJ CHARACTER(1),
        TKBJ CHARACTER(1),
        KHBJ CHARACTER(2),
        XZBJ CHARACTER(1),
        CBBJ CHARACTER(1),
        FKZH CHARACTER(32),
        FKMC CHARACTER(100),
        FKHH CHARACTER(14),
        FKHM CHARACTER(100),
        SKZH CHARACTER(32),
        SKMC CHARACTER(100),
        SKHH CHARACTER(14),
        SKHM CHARACTER(100),
        JYJE DECIMAL(20,2),
        QRJE DECIMAL(20,2),
        TKJE DECIMAL(20,2),
        JZGY CHARACTER(10),
        GYLS CHARACTER(20),
        ZWRQ CHARACTER(8),
        WHGY CHARACTER(10),
        WHRQ CHARACTER(8),
        WHSJ CHARACTER(6),
        FY CHARACTER(100),
        BZ CHARACTER(100),
        ZYDM CHARACTER(10),
        STAT CHARACTER(1),
        BY1 CHARACTER(20),
        BY2 CHARACTER(40),
        BY3 CHARACTER(60),
        BY4 CHARACTER(100),
        JZZT CHARACTER(1),
        XYDM CHARACTER(12),
        XYXX CHARACTER(150),
        JYJG CHARACTER(12),
        CONSTRAINT PK_TBL_GJJ_GJLS PRIMARY KEY (PTLS)
    );
CREATE INDEX IX_TBL_GJJ_GJLS_PTLS ON GAPSUSR.TBL_GJJ_GJLS(YWLS);
CREATE INDEX IX_TBL_GJJ_GJLS_JYRQ ON GAPSUSR.TBL_GJJ_GJLS(JYRQ,GJLX);
CREATE INDEX IX_TBL_GJJ_GJLS_DWZH ON GAPSUSR.TBL_GJJ_GJLS(DWZH,JYRQ,GJLX);
COMMENT ON TABLE GAPSUSR.TBL_GJJ_GJLS IS '������鼯��ˮ��Ϣ';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_GJLS.PTLS IS 'ƽ̨��ˮ��      ';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_GJLS.YWLS IS 'ҵ����ˮ��      ';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_GJLS.JYRQ IS '��������        ';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_GJLS.JYSJ IS '����ʱ��        ';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_GJLS.JYGY IS '���׹�Ա        ';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_GJLS.SQGY IS '��Ȩ��Ա        ';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_GJLS.DWZH IS '��λ�������˺�  ';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_GJLS.DWMC IS '��λ����������  ';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_GJLS.GJLX IS '�鼯����--0��ɡ�1���ȷ�ϡ�2����˻ء�3����ת����4����ת�����ȷ�ϡ�5����ת���˻㡢6����ת���ػ㡢7����ת������';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_GJLS.WSBJ IS '���б��--0��1��';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_GJLS.JDBJ IS '������--0�衢1��';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_GJLS.TKBJ IS '�˿���--0������1�˿�';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_GJLS.KHBJ IS '���б��--0���ڡ�1����';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_GJLS.XZBJ IS '��ת���--0�ֽ�1ת��';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_GJLS.CBBJ IS '�岹���--0������1�岹';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_GJLS.FKZH IS '�������˺�      ';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_GJLS.FKMC IS '����������      ';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_GJLS.FKHH IS '�����˿������к�';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_GJLS.FKHM IS '�����˿�������  ';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_GJLS.SKZH IS '�տ����˺�      ';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_GJLS.SKMC IS '�տ�������      ';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_GJLS.SKHH IS '�տ��˿������к�';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_GJLS.SKHM IS '�տ��˿�������  ';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_GJLS.JYJE IS '���׽��        ';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_GJLS.QRJE IS '��ȷ�Ͻ��      ';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_GJLS.TKJE IS '���˿���      ';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_GJLS.JZGY IS '���˹�Ա        ';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_GJLS.GYLS IS '��Ա������ˮ��  ';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_GJLS.ZWRQ IS '��������        ';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_GJLS.WHGY IS 'ά����Ա        ';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_GJLS.WHRQ IS 'ά������        ';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_GJLS.WHSJ IS 'ά��ʱ��        ';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_GJLS.FY IS '����            ';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_GJLS.BZ IS '��ע            ';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_GJLS.ZYDM IS 'ժҪ����        ';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_GJLS.STAT IS '��¼״̬--0��ȷ�ϡ�1��ȷ�ϡ�4ɾ����8����ʧ�ܡ�9��ʼ';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_GJLS.BY1 IS '����1           ';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_GJLS.BY2 IS '����2           ';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_GJLS.BY3 IS '����3           ';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_GJLS.BY4 IS '����4           ';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_GJLS.JZZT IS '����״̬--0�ɹ���1ʧ�ܡ�2����֤��9��ʼ';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_GJLS.XYDM IS '������Ӧ��      ';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_GJLS.XYXX IS '������Ӧ��Ϣ    ';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_GJLS.JYJG IS '���׻���        ';    


--������鼯��ˮ������Ϣ
CREATE
    TABLE TBL_GJJ_LSCZ
    (
        CZLS CHARACTER(32) NOT NULL,
        PTLS CHARACTER(32) NOT NULL,
        GLLS CHARACTER(32),
        CZLX CHARACTER(1),
        JYRQ CHARACTER(8),
        JYSJ CHARACTER(6),
        JYGY CHARACTER(10),
        STAT CHARACTER(1),
        BY1 CHARACTER(20),
        BY2 CHARACTER(40),
        BY3 CHARACTER(40),
        JYJG CHARACTER(12),
        CONSTRAINT PK_TBL_GJJ_LSCZ PRIMARY KEY (CZLS)
    );
CREATE INDEX IX_TBL_GJJ_LSCZ_PTLS ON GAPSUSR.TBL_GJJ_LSCZ(PTLS);
CREATE INDEX IX_TBL_GJJ_LSCZ_GLLS ON GAPSUSR.TBL_GJJ_LSCZ(GLLS);
CREATE INDEX IX_TBL_GJJ_LSCZ_JYRQ ON GAPSUSR.TBL_GJJ_LSCZ(JYRQ);
COMMENT ON TABLE GAPSUSR.TBL_GJJ_LSCZ IS '������鼯��ˮ������Ϣ';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_LSCZ.CZLS IS '������ˮ';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_LSCZ.PTLS IS 'ƽ̨��ˮ';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_LSCZ.GLLS IS '������ˮ';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_LSCZ.CZLX IS '��������--0������1ά��';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_LSCZ.JYRQ IS '��������';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_LSCZ.JYSJ IS '����ʱ��';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_LSCZ.JYGY IS '���׹�Ա';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_LSCZ.STAT IS '��¼״̬--0��Ч��1��Ч';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_LSCZ.BY1 IS '����1   ';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_LSCZ.BY2 IS '����2   ';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_LSCZ.BY3 IS '����3   ';
COMMENT ON COLUMN GAPSUSR.TBL_GJJ_LSCZ.JYJG IS '���׻���        ';