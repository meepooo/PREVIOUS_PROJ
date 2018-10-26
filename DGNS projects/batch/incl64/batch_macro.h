/********************************************************************
��Ȩ����:���ݺ������ӹɷ����޹�˾
��Ŀ����:����ҵ��ƽ̨��Ŀ
��    ��:V3.2
����ϵͳ:AIX5.3+ORACLE10.2+ANSI.C
�ļ�����:batch_macro.h
�ļ�����:����ҵ��ƽ̨�궨���ļ�
�� Ŀ ��:����ҵ��ƽ̨��Ŀ��
�� �� Ա:
��������:2009-3-25 10:49:57
��    ��:
�޸�����:
*********************************************************************/

#if !defined(__BATCH_MACRO__H)
#define __BATCH_MACRO__H

/* xml�ڵ���󳤶�  */
#define  BATCH_MAX_XML 1024000

/* �ָ���ָ��ַ��� */
#define BATCH_DIV        "+"

/* �ָ���ָ��ַ�����󳤶� */
#define BATCH_MAXLEN_DIV  30

/* ƽ̨������󲽵���Ŀ */
#define  BATCH_MAX_STEP_NUM   6

/* �����ļ����������Ŀ */
#define  BATCH_MAX_FILESORT_NUM  10

/* �����ļ�����Ϣ����� */
#define  BATCH_MAX_FILE_COL_NUM     64

/* �ļ�����󳤶� */ 
#define  BATCH_MAX_FILE_COL_LEN 256 

/* �ļ�ӳ������Ϣ����� */
#define  BATCH_MAX_FILEMAP_NUM   100

/* ������˺��������Ŀ */
#define  BATCH_MAX_AUDITING_NUM   10

/* ע�������Ϣ�����Ŀ */
#define BATCH_MAX_TABLEREG_NUM   100

/* �ļ���¼��󳤶� */
#define  BATCH_MAX_FILELINE_BYTE 1024 

/* ��ϵ�ʱ�� 12Сʱ 86400��  */
#define  BATCH_MAX_BREAK_SECONDS  864000   

/* �������ظ�����  */
#define  BATCH_MAX_STEP_REPEAT 5 

/* �Զ�������С��ѯ���  */
#define  BATCH_MIN_BREAK_AUTO  60

/* ��Ӧ��ӳ��������� */
#define  BATCH_MAX_RESP 50

/* �ɹ���Ӧ�� */
#define  BATCH_REPSCODE_SUCC  "00000"

/*��������ҵ����*/
#define  BATCH_MON_NORM  "MON_BATCH_NORM"
#define  BATCH_MON_UNORM  "MON_BATCH_UNORM"

/* ����ȫ���������ƶ��� */
#define BATCH_ATTRIBUTE_CLLCM     "cllcm"   /* ������������ */
#define BATCH_ATTRIBUTE_DDBZ      "ddbz"    /* �ϵ��ʶ */
#define BATCH_ATTRIBUTE_DDSJ      "ddsj"    /* �ϵ�ʱ�� */

/*  ���ݻ�ȡ��ʽ���Զ���*/
#define BATCH_ATTRIBUTE_HQSJFS_FTP    "0"   /*FTP��ȡ��ʽ*/
#define BATCH_ATTRIBUTE_HQSJFS_WEB    "1"   /*WEB��ȡ��ʽ*/
#define BATCH_ATTRIBUTE_HQSJFS_PKG    "2"   /*PKG��ȡ��ʽ*/
#define BATCH_ATTRIBUTE_HQSJFS_PCDT   "3"   /*�������᷽ʽ*/
#define BATCH_ATTRIBUTE_HQSJFS_SGLR   "4"   /*�ֹ�¼�뷽ʽ*/

/* �ظ�������ʶ���Զ��� */
#define BATCH_ATTRIBUTE_CFCZBZ_YES   "0"  /* ���������ظ�����*/
#define BATCH_ATTRIBUTE_CFCZBZ_NO    "1"  /* ���㲻�����ظ�����*/

/* �ϵ����Զ��� */
#define BATCH_ATTRIBUTE_DDBZ_NOBREAK    '0'    /* �޶ϵ�,����ִ���¸����� */
#define BATCH_ATTRIBUTE_DDBZ_BREAK      '1'    /* �жϵ�,����һ��ʱ���������� */
#define BATCH_ATTRIBUTE_DDBZ_RETURN     '2'    /* ���ز���ִ���¸����� */

/* ��ϸ�ύ��־ */
#define BATCH_MXTJBZ_NONPROC_FAIL  "1"          /* �ύ��ҵ��δ����ʧ����ϸ */

/* ��ϸ���̱�־ */
#define BATCH_ATTRIBUTE_MXHPBZ_ALLDATA "0"       /* ������������ȫ����ϸ */
#define BATCH_ATTRIBUTE_MXHPBZ_ALL    "1"        /* ���ɱ����δ�����ϸ */
#define BATCH_ATTRIBUTE_MXHPBZ_SUCC   "2"        /* ���ɱ����δ���ɹ���ϸ */
#define BATCH_ATTRIBUTE_MXHPBZ_FAIL   "3"        /* ���ɱ����δ���ʧ����ϸ */
#define BATCH_ATTRIBUTE_MXHPBZ_BOTH   "4"        /* �ֱ����ɱ����ɹ���ʧ����ϸ*/

/* �����ļ���ʽ���� */
#define BATCH_ATTRIBUTE_FSSJGS_FTP    "0"   /*FTP��ȡ��ʽ*/
#define BATCH_ATTRIBUTE_FSSJGS_WEB    "1"   /*WEB��ȡ��ʽ*/
#define BATCH_ATTRIBUTE_FSSJGS_PKG    "2"   /*PKG��ȡ��ʽ*/

/* �ⲿ�ļ��ǼǱ�����״̬ */
#define WBWJDJ_ZT_PRE     '1'   /* �����ϴ� */
#define WBWJDJ_ZT_READY   '2'   /* ���� */
#define WBWJDJ_ZT_RUNNING '3'   /* ���ڴ��� */
#define WBWJDJ_ZT_SUCC    '4'   /* �ѷ��� */
#define WBWJDJ_ZT_FAIL    '5'   /* ����ʧ�� */
#define WBWJDJ_ZT_CX      'X'   /* �ѳ��� */

/* �ⲿ�ļ��ǼǱ����״̬ */
#define WBWJDJ_SHZT_YES     '0'   /* ���ͨ�� */
#define WBWJDJ_SHZT_NO      '1'   /* δ��� */
#define WBWJDJ_SHZT_FAIL    '2'   /* ���ʧ�� */

/* ����ƽ̨ȫ�ֲ��㶨�� */
#define BATCH_STEPSN_HQSJ   '0'   /* ��ȡ���� */
#define BATCH_STEPSN_SJRK   '1'   /* ������� */
#define BATCH_STEPSN_SJSH   '2'   /* ������� */
#define BATCH_STEPSN_SJTJ   '3'   /* �����ύ */
#define BATCH_STEPSN_SJTH   '4'   /* ������� */
#define BATCH_STEPSN_SJHP   '5'   /* ��ҵ���� */
#define BATCH_STEPSN_FINL   '6'   /* ������̬ */
#define BATCH_STEPSN_RWQT   '7'   /* ����Ƕ�� */


#define BATCH_STEPNM_HQSJ   "hqsj"   /* ��ȡ���� */
#define BATCH_STEPNM_SJRK   "sjrk"   /* ������� */
#define BATCH_STEPNM_SJSH   "sjsh"   /* ������� */
#define BATCH_STEPNM_SJTJ   "sjtj"   /* �����ύ */
#define BATCH_STEPNM_SJTH   "sjth"   /* ������� */
#define BATCH_STEPNM_SJHP   "sjhp"   /* ��ҵ���� */
#define BATCH_STEPNM_RWQT   "rwqt"   /* ����Ƕ�� */

/* ����״̬���� */
#define BATCH_STEP_STATUS_RUNNING   '9'   /* ������ */
#define BATCH_STEP_STATUS_STOP      '0'   /* ��ֹ */
#define BATCH_STEP_STATUS_END       '1'   /* ���� */
#define BATCH_STEP_STATUS_BREAK     '2'   /* �ϵ� */
#define BATCH_STEP_STATUS_RETURN    '3'   /* ���� */
#define BATCH_STEP_STATUS_WAIT      '4'   /* �ȴ� */
#define BATCH_STEP_STATUS_X         'X'   /* ���� */

#define BATCH_STEP_STATUS_S_RUNNING   "9"   /* ������ */
#define BATCH_STEP_STATUS_S_STOP      "0"   /* ��ֹ */
#define BATCH_STEP_STATUS_S_END       "1"   /* ���� */
#define BATCH_STEP_STATUS_S_BREAK     "2"   /* �ϵ� */
#define BATCH_STEP_STATUS_S_RETURN    "3"   /* ���� */
#define BATCH_STEP_STATUS_S_WAIT      "4"   /* �ȴ� */
#define BATCH_STEP_STATUS_S_X         "X"   /* ���� */

/* ��������״̬���� */
#define BATCH_STEP_ASTSTEP_INIT     "00"  /* ��������ʼ */
#define BATCH_STEP_ASTSTEP_ACTING   "09"  /* ������ */
#define BATCH_STEP_ASTSTEP_WRET     "10"  /* ������ */
#define BATCH_STEP_ASTSTEP_RETING   "19"  /* ������ */
#define BATCH_STEP_ASTSTEP_RETURN   "11"  /* �ѷ��� */
#define BATCH_STEP_ASTSTEP_END      "99"  /* �ѽ��� */

/* ����״̬���� */
#define BATCH_TASK_STATUS_S_RUNNING   "9"   /* ������ */
#define BATCH_TASK_STATUS_S_STOP      "0"   /* ʧ�� */
#define BATCH_TASK_STATUS_S_END       "1"   /* ���� */
#define BATCH_TASK_STATUS_S_PAUSE     "2"   /* ��ͣ */
#define BATCH_TASK_STATUS_S_RETURN    "3"   /* ���� */
#define BATCH_TASK_STATUS_S_CANCEL    "X"   /* ���� */
#define BATCH_TASK_STATUS_S_CORRECT   "C"   /* ���� */
#define BATCH_TASK_STATUS_S_TERM      "Z"   /* ǿ����ֹ */
/* ����ɹ���־ */
#define BATCH_STEP_S_SUCC      "0"   /* �ɹ� */
#define BATCH_STEP_S_FAIL      "1"   /* ʧ�� */
#define BATCH_STEP_S_RETURN    "2"   /* ���� */
#define BATCH_STEP_S_WAIT      "3"   /* �ȴ� */

/* ��ϸ�ɹ���־ */
#define BATCH_CGBZ_S_SUCC      "0"   /* �ɹ� */
#define BATCH_CGBZ_S_BFSUCC    "1"   /* ���ֳɹ� */
#define BATCH_CGBZ_S_FAIL    "2"   /* ����ʧ�� */

/* �ļ���ʽ���� */
#define BATCH_FILETYPE_TYPE_TXT  '0'   /* �ı��ļ� */
#define BATCH_FILETYPE_TYPE_PDF  '1'   /* PDF��ʽ */
#define BATCH_FILETYPE_TYPE_XSL  '2'   /* EXCEL��ʽ */
#define BATCH_FILETYPE_TYPE_XML  '3'   /* XML�ı���ʽ */

#define BATCH_FILETYPE_FMT_SINGLE  '0'   /* ������ */
#define BATCH_FILETYPE_FMT_MULTI   '1'   /* ����� */

/* �ļ����ඨ�� */
#define BATCH_FILESORT_TYPE_TOTAL   1   /*  ���� */
#define BATCH_FILESORT_TYPE_DETAIL  2   /*  ��ϸ */
#define BATCH_FILESORT_TYPE_S_TOTAL   "1"   /*  ���� */
#define BATCH_FILESORT_TYPE_S_DETAIL  "2"   /*  ��ϸ */

#define BATCH_FILESORT_POSITION_ZDH    '1'   /*  ָ���� */
#define BATCH_FILESORT_POSITION_JLBS   '2'   /*  ��¼��ʶ */
#define BATCH_FILESORT_POSITION_AHZJL  '3'   /*  ���ܼ�¼֮�� */

#define BATCH_FILESORT_COLUNM_FIX    '1'   /*  ���� */
#define BATCH_FILESORT_COLUNM_SPLIT  '2'   /*  �ָ�� */
#define BATCH_FILESORT_COLUNM_SPLIT_TAIL  '3'   /* ȥβ�ָ�� */

/*�ļ�ӳ�䶨��*/
#define BATCH_FILEMAP_LYLX_FILE     '1'   /* �����ļ���ȡ */
#define BATCH_FILEMAP_LYLX_XML      '2'   /* XML��ȡ */
#define BATCH_FILEMAP_LYLX_WJSEQ    '3'   /* �ļ���� */
#define BATCH_FILEMAP_LYLX_SEQ      '4'   /* ��ˮ��� */
#define BATCH_FILEMAP_LYLX_CONST    '5'   /* �������� */
#define BATCH_FILEMAP_LYLX_ZHQZLSH  '6'   /* �ۺ�ǰ����ˮ�� */
 
/*�ļ������Զ��� */
#define BATCH_FILECOLUMN_LSX_ADD     "0"   /* ��ϸ��¼����-���׽���ۼ� */
#define BATCH_FILECOLUMN_LSX_SUB     "1"   /* ���׽���ۼ�              */
#define BATCH_FILECOLUMN_LSX_SUM     "2"   /* �ֶ�SUM                   */
#define BATCH_FILECOLUMN_LSX_COUNT   "3"   /* �ֶ�COUNT                 */
#define BATCH_FILECOLUMN_LSX_SETXML  "4"   /* 4-ֵ���� xml�ڵ�   */
#define BATCH_FILECOLUMN_LSX_GETXML  "5"   /* 5-ֵ��ȡ(xml�ڵ����)   */
#define BATCH_FILECOLUMN_LSX_ZBS     "6"   /* ���ܼ�¼����-���ܱ���     */
#define BATCH_FILECOLUMN_LSX_ZJE     "7"   /* ���ܼ�¼����-���ܽ��     */
#define BATCH_FILECOLUMN_LSX_SHPCH   "8"   /* ���ܼ�¼����-�̻����κ�   */

#define BATCH_PTPCH_XLJZ "K_BATCH_PCH"     /* ƽ̨���κ����м�ֵ */

#define BATCH_TOTAL_HEAD   0     /* ���ܼ�¼λ��  ͷ */         
#define BATCH_TOTAL_TAIL   1     /* ���ܼ�¼λ��  β */         

#define BATCH_KHBH_XLJZ "K_BATCH_KHBH" /* �����ͻ��˿ͻ�������� */
#define BATCH_XYBH_XLJZ "K_BATCH_XYBH" /* �����ͻ���Э�������� */

/*�������ȼ�*/
#define BATCH_TASKPRI_LOWER    '0'     /* �ͼ� */         
#define BATCH_TASKPRI_MIDDLE   '1'     /* �м� */ 
#define BATCH_TASKPRI_HIGH     '2'     /* �߼� */ 

#endif


