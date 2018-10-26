drop index index_tbl_jzzf_czzh;
drop table TBL_JZZF_CZZH;
CREATE TABLE
    TBL_JZZF_CZZH
    (
        CZBM CHARACTER(12) NOT NULL,
	BGDEPTCODE CHARACTER(12) NOT NULL,
        CZZH CHARACTER(32) NOT NULL,
	CXZT CHAR(1) NOT NULL,
	DSBZ CHAR(1) NOT NULL,
	WHRQ CHAR(8),
        CONSTRAINT Pk_jzzf_czzh PRIMARY KEY (CZZH)
    );

create unique index index_tbl_jzzf_czzh on tbl_jzzf_czzh( CZBM,CZZH );
COMMENT ON TABLE TBL_JZZF_CZZH
IS
    '�����˻���';
COMMENT ON COLUMN TBL_JZZF_CZZH.CZBM
IS
    '��������';
COMMENT ON COLUMN TBL_JZZF_CZZH.BGDEPTCODE
IS
    'Ԥ�㵥λ����';
COMMENT ON COLUMN TBL_JZZF_CZZH.CZZH
IS
    '�����˺�';
COMMENT ON COLUMN TBL_JZZF_CZZH.CXZT
IS
    '��ѯ״̬ 0ʵʱ�ɲ�ѯ 1ʵʱ���ɲ�ѯ';
COMMENT ON COLUMN TBL_JZZF_CZZH.DSBZ
IS
    '��ʱ��־ 0���붨ʱ��ѯ 1�����붨ʱ��ѯ';
COMMENT ON COLUMN TBL_JZZF_CZZH.WHRQ
IS
    'ά������';
