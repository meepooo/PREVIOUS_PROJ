/********************************************************************
��Ȩ����:���ݺ������ӹɷ����޹�˾
��Ŀ����:�ۺ�Ӧ��ƽ̨��GAPS����Ŀ
��    ��:V1.0
����ϵͳ:AIX SCO LINUX SunOS HP-UX
�� �� ��:ORACLE10G
�ļ�����:����ҵ��ƽ̨ͨ��XMLԪ�����ƺ궨��ͷ�ļ�
�ļ�����:batch_xmlmacro.h
�� Ŀ ��:
�� �� Ա:
��������:
*********************************************************************/
/********************************************************************
�޸ļ�¼
�޸�����:2011-3-09
�޸�����:
�޸���:
*********************************************************************/

#ifndef __BATCH_XMLMACRO_H__
#define __BATCH_XMLMACRO_H__
     
    /* �ⲿ�ļ��ǼǱ�����ڵ㶨�� */
    #define XMLNM_BATCH_REQ_YWBH        "/batch/req/ywbh"
    #define XMLNM_BATCH_REQ_DJJG        "/batch/req/jyjg"
    #define XMLNM_BATCH_REQ_DJGY        "/batch/req/jygy"
    #define XMLNM_BATCH_REQ_JYDM        "/batch/req/jydm"
    #define XMLNM_BATCH_REQ_SHPCH       "/batch/req/shpch"
    #define XMLNM_BATCH_REQ_PKRQ        "/batch/req/pkrq"
    #define XMLNM_BATCH_REQ_PTPCH       "/batch/req/ptpch"
    #define XMLNM_BATCH_REQ_LPWJM       "/batch/req/lpwjm"
    #define XMLNM_BATCH_REQ_HPWJM       "/batch/req/hpwjm"
    #define XMLNM_BATCH_REQ_ZBS         "/batch/req/zbs"
    #define XMLNM_BATCH_REQ_ZJE         "/batch/req/zje"
    #define XMLNM_BATCH_REQ_LRFS        "/batch/req/lrfs"
    #define XMLNM_BATCH_REQ_HQSJFS      "/batch/req/hqsjfs"
    #define XMLNM_BATCH_REQ_LOCALPATH   "/batch/req/localpath"
    #define XMLNM_BATCH_REQ_THREADNO    "/batch/req/threadno"
    #define XMLNM_BATCH_REQ_TASKMODE    "/batch/req/taskmode"
    #define XMLNM_BATCH_REQ_TASKPRI     "/batch/req/taskpri"
    #define XMLNM_BATCH_REQ_NEXTSTEP    "/batch/req/nextstep"
    #define XMLNM_BATCH_REQ_PCZT        "/batch/req/pczt"
    #define XMLNM_BATCH_REQ_SHZT        "/batch/req/shzt"
    #define XMLNM_BATCH_REQ_NOTE        "/batch/req/note"
    #define XMLNM_BATCH_REQ_EXTFLD1     "/batch/req/extfld1"
    #define XMLNM_BATCH_REQ_EXTFLD2     "/batch/req/extfld2"
    #define XMLNM_BATCH_REQ_EXTFLD3     "/batch/req/extfld3"
    #define XMLNM_BATCH_REQ_EXTFLD4     "/batch/req/extfld4"
    #define XMLNM_BATCH_REQ_DQBD        "/batch/req/dqbd"
    #define XMLNM_BATCH_REQ_BDZT        "/batch/req/bdzt"
    #define XMLNM_BATCH_REQ_FZBD        "/batch/req/fzbd"
    #define XMLNM_BATCH_REQ_RWZT        "/batch/req/rwzt"
    #define XMLNM_BATCH_REQ_QTPKRQ      "/batch/req/qtpkrq"
    #define XMLNM_BATCH_REQ_QTPTPCH     "/batch/req/qtptpch"
    #define XMLNM_BATCH_REQ_QTBZ        "/batch/req/qtbz"
    #define XMLNM_BATCH_REQ_DWBH        "/batch/req/dwbh"         /* �����ͻ��˵Ǽǿͻ���� */
    #define XMLNM_BATCH_REQ_YPKRQ       "/batch/req/ypkrq"
    #define XMLNM_BATCH_REQ_YPTPCH      "/batch/req/yptpch"

    /* �ⲿ�ļ��Ǽ���Ϣ�ڵ㶨�� */
    #define XMLNM_BATCH_WBWJDJ_DJRQ        "/batch/req/djrq"
    #define XMLNM_BATCH_WBWJDJ_DJLSH       "/batch/req/djlsh"
    #define XMLNM_BATCH_WBWJDJ_LPWJM       "/batch/req/lpwjm"
    
    /*���п�����Ϣ�ڵ㶨�� */
    #define XMLNM_BATCH_RUNCTRL_CPDM       "/batch/runctrl/cpdm"              /*��Ʒ����*/
    #define XMLNM_BATCH_RUNCTRL_FLOWID     "/batch/runctrl/flowid"            /*����ID*/
    #define XMLNM_BATCH_RUNCTRL_MAXTASK    "/batch/runctrl/maxtask"           /*���������*/
    #define XMLNM_BATCH_RUNCTRL_MAXTHREAD  "/batch/runctrl/maxthread"         /*����߳���*/
    #define XMLNM_BATCH_RUNCTRL_ZJYSBS     "/batch/runctrl/zjysbs"              /*ӳ���ʶ*/
    #define XMLNM_BATCH_RUNCTRL_WWYSBS     "/batch/runctrl/wwysbs"              /*ӳ���ʶ*/
    #define XMLNM_BATCH_RUNCTRL_SHBZ       "/batch/runctrl/shbz"              /*��˱�־*/
    #define XMLNM_BATCH_RUNCTRL_TASKMODE   "/batch/runctrl/taskmode"          /*����ʼ��ʽ*/
    #define XMLNM_BATCH_RUNCTRL_TASKPRI   "/batch/runctrl/taskpri"          /*���ȼ�*/
    #define XMLNM_BATCH_RUNCTRL_EXTFLD1    "/batch/runctrl/extfld1"           /*��չ�ֶ�1*/

    /*����������Ϣ*/
    #define XMLNM_BATCH_STEPINFO_CURSTEP    "/batch/stepinfo/curstep"            /*��ǰ����*/
    #define XMLNM_BATCH_STEPINFO_CURASSSTEP "/batch/stepinfo/curassstep"         /*��ǰ��������*/
    #define XMLNM_BATCH_STEPINFO_CURSTATUS  "/batch/stepinfo/curstatus"          /*����״̬*/
    #define XMLNM_BATCH_STEPINFO_TASKSTATUS "/batch/stepinfo/taskstatus"         /*����״̬*/
    #define XMLNM_BATCH_STEPINFO_NEXTSTEP   "/batch/stepinfo/nextstep"           /*��һ����*/ 
    
    /* ����ӳ����Ϣ��ڵ㶨��  */
    #define XMLNM_BATCH_ZJMAPINFO_MAPID      "/batch/zjmapinfo/mapid"
    #define XMLNM_BATCH_ZJMAPINFO_YWBM       "/batch/zjmapinfo/ywbm"
    #define XMLNM_BATCH_ZJMAPINFO_TJWJBS     "/batch/zjmapinfo/tjwjbs"
    #define XMLNM_BATCH_ZJMAPINFO_THWJBS     "/batch/zjmapinfo/thwjbs"
    #define XMLNM_BATCH_ZJMAPINFO_JLSXZ      "/batch/zjmapinfo/jlsxz"
    #define XMLNM_BATCH_ZJMAPINFO_ZHBZ       "/batch/zjmapinfo/zhbz"
    #define XMLNM_BATCH_ZJMAPINFO_ZHBS       "/batch/zjmapinfo/zhbs"

    #define XMLNM_BATCH_WWMAPINFO_MAPID      "/batch/wwmapinfo/mapid"
    #define XMLNM_BATCH_WWMAPINFO_YWBM       "/batch/wwmapinfo/ywbm"
    #define XMLNM_BATCH_WWMAPINFO_LPWJBS     "/batch/wwmapinfo/lpwjbs"
    #define XMLNM_BATCH_WWMAPINFO_HPWJBS     "/batch/wwmapinfo/hpwjbs"
    #define XMLNM_BATCH_WWMAPINFO_ZHBZ       "/batch/wwmapinfo/zhbz"
    #define XMLNM_BATCH_WWMAPINFO_ZHBS       "/batch/wwmapinfo/zhbs"

    #define XMLNM_BATCH_QTMAPINFO_MAPID      "/batch/qtmapinfo/mapid"
    #define XMLNM_BATCH_QTMAPINFO_YWBM       "/batch/qtmapinfo/ywbm"
    #define XMLNM_BATCH_QTMAPINFO_TJWJBS     "/batch/qtmapinfo/tjwjbs"
    #define XMLNM_BATCH_QTMAPINFO_THWJBS     "/batch/qtmapinfo/thwjbs"
    #define XMLNM_BATCH_QTMAPINFO_JLSXZ      "/batch/qtmapinfo/jlsxz"
    #define XMLNM_BATCH_QTMAPINFO_ZHBZ       "/batch/qtmapinfo/zhbz"
    #define XMLNM_BATCH_QTMAPINFO_ZHBS       "/batch/qtmapinfo/zhbs"

    /*�����������ýڵ㶨�� */
    #define XMLNM_BATCH_FLOWCFG_FLOWID     "/batch/flowcfg/flowid"             /*����ID*/
    #define XMLNM_BATCH_FLOWCFG_FLOWNAME   "/batch/flowcfg/flowname"           /*��������*/
    #define XMLNM_BATCH_FLOWCFG_FLOWSN     "/batch/flowcfg/flowsn"             /*�������*/
    #define XMLNM_BATCH_FLOWCFG_STEPID     "/batch/flowcfg/stepid"             /*�����ʶ*/
    #define XMLNM_BATCH_FLOWCFG_STEPSN     "/batch/flowcfg/stepsn"             /*�������*/    
    #define XMLNM_BATCH_FLOWCFG_STEPNAME     "/batch/flowcfg/stepname"         /*��������*/ 
    #define XMLNM_BATCH_FLOWCFG_EXTFLD1    "/batch/flowcfg/extfld1"            /*��չ�ֶ�1*/
    #define XMLNM_BATCH_FLOWCFG_EXTFLD2    "/batch/flowcfg/extfld2"            /*��չ�ֶ�2*/
     

    /*��������Ƕ�ײ������� */
    #define XMLNM_BATCH_STEPCFG_RWQT_CLLCM     "/batch/rwqt/cllcm"             /*����������*/
    #define XMLNM_BATCH_STEPCFG_RWQT_BQTCPDM   "/batch/rwqt/bqtcpdm"           /*��Ƕ�ײ�Ʒ����*/
    #define XMLNM_BATCH_STEPCFG_RWQT_BQTYWBH   "/batch/rwqt/bqtywbh"           /*��Ƕ��ҵ����*/
    #define XMLNM_BATCH_STEPCFG_RWQT_BQTPCYT   "/batch/rwqt/bqtpcyt"           /*��Ƕ��������;*/
    #define XMLNM_BATCH_STEPCFG_RWQT_QTWJYS    "/batch/rwqt/qtwjys"            /*Ƕ���ļ�ӳ��*/
    #define XMLNM_BATCH_STEPCFG_RWQT_QTWJDC    "/batch/rwqt/qtwjdc"            /*Ƕ���ļ�����*/
    
    /* ����������ýڵ㶨�� */
    #define XMLNM_BATCH_AUDITING_AUDIID    "/batch/auditing/audiid"             
    #define XMLNM_BATCH_AUDITING_AUDISN    "/batch/auditing/audisn"           
    #define XMLNM_BATCH_AUDITING_FUNCID    "/batch/auditing/funcid"             
    #define XMLNM_BATCH_AUDITING_SHSBBZ    "/batch/auditing/shsbbz"          
    #define XMLNM_BATCH_AUDITING_PARASN    "/batch/auditing/parasn"     
    #define XMLNM_BATCH_AUDITING_PARA      "/batch/auditing/para"    
    
    /* �ļ�������Ϣ  */
    #define XMLNM_BATCH_WJLX_FILEID          "/batch/wjlx/fileid"
    #define XMLNM_BATCH_WJLX_FILETYPE        "/batch/wjlx/filetype"
    #define XMLNM_BATCH_WJLX_FILEFMT         "/batch/wjlx/filefmt"
    #define XMLNM_BATCH_WJLX_CODEFMT         "/batch/wjlx/codefmt"
    #define XMLNM_BATCH_WJLX_EXTFLD1         "/batch/wjlx/etxfld1"
        
    /* ȫ������XML�ڵ㶨�� */
    #define XMLNM_BATCH                  "/batch" 
    #define XMLNM_BATCH_TASK_STATUS      "/batch/taskstatus"               /*����״̬*/
    #define XMLNM_BATCH_STEP_STATUS      "/batch/stepstatus"               /*����״̬*/
    #define XMLNM_BATCH_STEPSN           "/batch/stepsn"                   /*�������*/
    #define XMLNM_BATCH_STEPID           "/batch/stepid"                   /*�����ʶ*/
    #define XMLNM_BATCH_TASKPRI          "/batch/taskpri"
    #define XMLNM_BATCH_PKRQ             "/batch/pkrq"
    #define XMLNM_BATCH_PTPCH            "/batch/ptpch"
    #define XMLNM_BATCH_PLRWKEY          "/batch/plrwkey"
    #define XMLNM_BATCH_SHPCH            "/batch/shpch"
    #define XMLNM_BATCH_ZJPCH            "/batch/zjpch"
    #define XMLNM_BATCH_ZJJYRQ           "/batch/zjjyrq"
    #define XMLNM_BATCH_BDCGBZ           "/batch/bdcgbz"
    #define XMLNM_BATCH_MX_ZJE           "/batch/mxzje"      /*��ϸʵ���ܽ��*/ 
    #define XMLNM_BATCH_MX_ZBS           "/batch/mxzbs"      /*��ϸʵ���ܱ���*/ 
    #define XMLNM_BATCH_CGZJE            "/batch/cgzje"      /*�ɹ��ܽ��*/ 
    #define XMLNM_BATCH_CGZBS            "/batch/cgzbs"      /*�ɹ��ܱ���*/ 
    #define XMLNM_BATCH_SBZJE            "/batch/sbzje"      /*ʧ���ܽ��*/   
    #define XMLNM_BATCH_SBZBS            "/batch/sbzbs"      /*ʧ���ܱ���*/ 
    #define XMLNM_BATCH_XKHBS            "/batch/xkhbs"      /*�¿�������*/ 
    #define XMLNM_BATCH_XKHJE            "/batch/xkhje"      /*�¿������*/ 
    #define XMLNM_BATCH_PLRW_DQBD        "/batch/dqbd"
    #define XMLNM_BATCH_CPDM             "/batch/cpdm"      /*��Ʒ����*/ 
    #define XMLNM_BATCH_YWBH             "/batch/ywbh"      /*ҵ����*/ 
    #define XMLNM_BATCH_MAXTASKNUM       "/batch/maxtasknum" /*���������*/
    #define XMLNM_BATCH_YPKRQ            "/batch/ypkrq"
    #define XMLNM_BATCH_YPTPCH           "/batch/yptpch"


    #define XMLNM_BATCH_HZ_ZJE          "/batch/hqsj/hzzje"      /*�����ļ����ܼ�¼����ܽ��*/
    #define XMLNM_BATCH_HZ_ZBS          "/batch/hqsj/hzzbs"      /*�����ļ����ܼ�¼����ܱ���*/
    #define XMLNM_BATCH_HQSJ_HQSJFS     "/batch/hqsj/hqsjfs"  /*��ȡ���ݷ�ʽ*/

    #define XMLNM_BATCH_SJSH_SHBS         "/batch/sjsh/shbs"      /*��˱�ʶ*/

    #define XMLNM_BATCH_SJTJ_ZJE          "/batch/sjtj/zje"      /*���������ύ�ļ����ܽ��*/
    #define XMLNM_BATCH_SJTJ_ZBS          "/batch/sjtj/zbs"      /*���������ύ�ļ����ܱ���*/
    #define XMLNM_BATCH_SJTJ_WJS          "/batch/sjtj/wjs"      /*�ύ�����ļ����� */
    #define XMLNM_BATCH_SJTJ_WJM          "/batch/sjtj/wjm"      /*�ϴ��ļ���*/ 
    #define XMLNM_BATCH_SJTJ_WJLJ         "/batch/sjtj/wjlj"     /*�ύ�����ļ�·�� */
    #define XMLNM_BATCH_SJTJ_SUBMIITED_WJXH "/batch/sjtj/submiited_wjxh" /*���ύ�����ļ���� */
    #define XMLNM_BATCH_SJTJ_GDDDSJ       "/batch/sjtj/gdddsj"   /*�ύ�����̶��ж�ʱ�� */
    #define XMLNM_BATCH_SJTJ_FDDDSJ       "/batch/sjtj/fdddsj"   /*�ύ���������ж�ʱ�� */
    #define XMLNM_BATCH_SJTJ_WAIT         "/batch/sjtj/wait"     /*�ύ�����ж�ʱ�� */
    #define XMLNM_BATCH_MAXHOSTWAIT       "/batch/sjtj/maxwait"  /*�ύ������ж�ʱ�� */
    #define XMLNM_BATCH_MXTJBZ            "/batch/sjtj/mxtjbz"   /* ��ϸ�ύ������־ */
    #define XMLNM_BATCH_SJTJ_CPDM         "/batch/sjtj/cpdm"     /*��Ʒ����*/
    #define XMLNM_BATCH_SJTJ_YWBH         "/batch/sjtj/ywbh"     /*ҵ����*/
    #define XMLNM_BATCH_SJTJ_STEPID       "/batch/sjtj/stepid"   /*���񲽵�*/
    #define XMLNM_BATCH_SJTJ_FLOWSN       "/batch/sjtj/flowsn"   /*�������*/
    #define XMLNM_BATCH_SJTJ_EXPWHERE     "/batch/sjtj/expwhere" /*��������*/

    #define XMLNM_BATCH_SJTH_ZJXH         "/batch/sjth/wjxh"     /*��������ļ����*/ 
    
    #define XMLNM_BATCH_SJHP_ZJE          "/batch/sjhp/zje"      /*���ɻ����ļ����ܽ��*/
    #define XMLNM_BATCH_SJHP_ZBS          "/batch/sjhp/zbs"      /*���ɻ����ļ����ܱ���*/
    #define XMLNM_BATCH_SJHP_CGZJE        "/batch/sjhp/cgzje"    /*���ɻ����ļ��ĳɹ��ܽ��*/
    #define XMLNM_BATCH_SJHP_CGZBS        "/batch/sjhp/cgzbs"    /*���ɻ����ļ��ĳɹ��ܱ���*/
    #define XMLNM_BATCH_SJHP_SBZJE        "/batch/sjhp/sbzje"    /*���ɻ����ļ���ʧ���ܽ��*/
    #define XMLNM_BATCH_SJHP_SBZBS        "/batch/sjhp/sbzbs"    /*���ɻ����ļ���ʧ���ܱ���*/
    #define XMLNM_BATCH_SJHP_FILEDIR      "/batch/hqsj/filedir"  /*�̻������ļ�·��ͬ�����ļ�·��*/ 
    #define XMLNM_BATCH_SJHP_REPEAT       "/batch/sjhp/cfczbz"   /*�̻������ظ�������־*/ 
    #define XMLNM_BATCH_SJHP_CGWJ         "/batch/sjhp/filename"     /*�̻��ظ��ɹ��ļ�*/ 
    #define XMLNM_BATCH_SJHP_SBWJ         "/batch/sjhp/filename_f"   /*�̻��ظ�ʧ���ļ�*/ 
    #define XMLNM_BATCH_SJHP_CVTRESP      "/batch/sjhp/cvtresp"      /* ��Ӧ��ת����Χ 0 ȫ��ת����Ĭ�ϣ� 1-ֻת�����ʧ����ϸ */

    #define XMLNM_BATCH_SJCT_ZJE          "/batch/sjct/zje"      /*���ɻ����ļ����ܽ��*/
    #define XMLNM_BATCH_SJCT_ZBS          "/batch/sjct/zbs"      /*���ɻ����ļ����ܱ���*/
    #define XMLNM_BATCH_SJCT_CGZJE        "/batch/sjct/cgzje"    /*���ɻ����ļ��ĳɹ��ܽ��*/
    #define XMLNM_BATCH_SJCT_CGZBS        "/batch/sjct/cgzbs"    /*���ɻ����ļ��ĳɹ��ܱ���*/
    #define XMLNM_BATCH_SJCT_SBZJE        "/batch/sjct/sbzje"    /*���ɻ����ļ���ʧ���ܽ��*/
    #define XMLNM_BATCH_SJCT_SBZBS        "/batch/sjct/sbzbs"    /*���ɻ����ļ���ʧ���ܱ���*/
    #define XMLNM_BATCH_SJCT_FILEDIR      "/batch/hqsj/filedir"  /*�̻������ļ�·��ͬ�����ļ�·��*/ 
    #define XMLNM_BATCH_SJCT_REPEAT       "/batch/sjhp/cfczbz"   /*�̻������ظ�������־*/ 
    #define XMLNM_BATCH_SJCT_CGWJ         "/batch/sjct/filename"     /*�̻��ظ��ɹ��ļ�*/ 
    #define XMLNM_BATCH_SJCT_SBWJ         "/batch/sjct/filename_f"   /*�̻��ظ�ʧ���ļ�*/ 
    #define XMLNM_BATCH_SJCT_CVTRESP      "/batch/sjct/cvtresp"      /* ��Ӧ��ת����Χ 0 ȫ��ת����Ĭ�ϣ� 1-ֻת�����ʧ����ϸ */

    #define XMLNM_BATCH_FORCE_RETURN      "/batch/forceReturn"   /* ǿ�Ʒ���״̬ */
    #define XMLNM_BATCH_SJTJ_WJXH      "/batch/sjtj/wjxh"        /* �����ύ�ļ���� */

    #define XMLNM_BATCH_FINAL_STEP     "/batch/final_step"       /* ����β������id */
    #define XMLNM_BATCH_FINAL_FLOWSN   "/batch/final_flowsn"     /* ����β��ִ��sn */
    #define XMLNM_BATCH_FINAL_STEPSN   "/batch/final_stepsn"     /* ����β������sn */
    #define XMLNM_BATCH_SJHP_EXIST     "/batch/sjhp_exist"       /* �������ݻ��̴��ڱ�־ */
    #define XMLNM_BATCH_SJHP_FLOWSN    "/batch/sjhp_flowsn"      /* �������ݻ���ִ��sn */
    #define XMLNM_BATCH_SJHP_STEPSN    "/batch/sjhp_stepsn"      /* �������ݻ��̲���sn */    
    #define XMLNM_BATCH_STEP_FAIL      "/batch/steprepeat"       /* �������ʧ�����Դ��� */
    #define XMLNM_BATCH_SJTJ_TIME      "/batch/req/sjtj_ksclsj"  /* �����ύ��ʼ����ʱ�� */
    #define XMLNM_BATCH_SJTJ_DATE      "/batch/req/sjtj_ksclrq"  /* �����ύ��ʼ�������� */
    #define XMLNM_BATCH_NIGHT_TIME     "/batch/night_time"       /* ����ҹ����������ʼʱ�� */

    /* �ͻ������õǼ���Ϣ�ڵ㶨�� */
    #define XMLNM_BATCH_REQ_KHBH       "/batch/req/khbh"         /* �����ͻ��˵Ǽǿͻ���� */
    #define XMLNM_BATCH_REQ_KHMC       "/batch/req/khmc"         /* �����ͻ��˵Ǽǿͻ����� */
    #define XMLNM_BATCH_REQ_XYBH       "/batch/req/xybh"         /* �����ͻ��˵Ǽ�Э���� */
    #define XMLNM_BATCH_REQ_LXR        "/batch/req/lxr"          /* �����ͻ��˵Ǽ���ϵ�� */
    #define XMLNM_BATCH_REQ_DHHM       "/batch/req/dhhm"         /* �����ͻ��˵Ǽ���ϵ�˵绰 */
    #define XMLNM_BATCH_REQ_SJHM       "/batch/req/sjhm"         /* �����ͻ��˵Ǽ���ϵ���ֻ� */
    #define XMLNM_BATCH_REQ_EMAIL      "/batch/req/email"        /* �����ͻ��˵Ǽ���ϵ��email */
    #define XMLNM_BATCH_REQ_JYJG       "/batch/req/jyjg"         /* �����ͻ��˵Ǽǽ��׻��� */
    #define XMLNM_BATCH_REQ_JYGY       "/batch/req/jygy"         /* �����ͻ��˵Ǽǽ��׹�Ա */
    #define XMLNM_BATCH_REQ_DJRQ       "/batch/req/djrq"         /* �����ͻ��˵Ǽ����� */
    #define XMLNM_BATCH_REQ_KHJL       "/batch/req/khjl"         /* �����ͻ��˵Ǽǿͻ�����*/
    #define XMLNM_BATCH_REQ_QYZH       "/batch/req/qyzh"         /* �����ͻ��˵Ǽ�ǩԼ�˺�*/
    #define XMLNM_BATCH_REQ_QYHM       "/batch/req/qyhm"         /* �����ͻ��˵Ǽ�ǩԼ����*/
    
    #define XMLNM_BATCH_RESP_KEY       "/batch/resp/cli_pwd"     /* �����ͻ��˵Ǽ���Կ */
    #define XMLNM_BATCH_RESP_KHBH      "/batch/resp/khbh"        /* �����ͻ��˵Ǽǿͻ���� */
    #define XMLNM_BATCH_RESP_XYBH      "/batch/resp/xybh"        /* �����ͻ��˵Ǽ�Э���� */
    #define XMLNM_BATCH_RESP_KHMC      "/batch/resp/khmc"        /* �����ͻ��˵Ǽǿͻ����� */
    #define XMLNM_BATCH_RESP_LXR      "/batch/resp/lxr"        /* �����ͻ��˵Ǽ���ϵ�� */
    #define XMLNM_BATCH_RESP_DHHM      "/batch/resp/dhhm"        /* �����ͻ��˵Ǽ���ϵ�˵绰 */
    #define XMLNM_BATCH_RESP_SJHM      "/batch/resp/sjhm"        /* �����ͻ��˵Ǽ���ϵ���ֻ����� */
    #define XMLNM_BATCH_RESP_EMAIL      "/batch/resp/email"        /* �����ͻ��˵Ǽ���ϵ��email */
    #define XMLNM_BATCH_RESP_JYJG      "/batch/resp/jyjg"        /* �����ͻ��˵Ǽǽ��׻��� */
    #define XMLNM_BATCH_RESP_JYGY      "/batch/resp/jygy"        /* �����ͻ��˵Ǽǽ��׹�Ա */
    #define XMLNM_BATCH_RESP_DJRQ      "/batch/resp/djrq"        /* �����ͻ��˵ǼǵǼ����� */    
    #define XMLNM_BATCH_RESP_DJSJ      "/batch/resp/djsj"        /* �����ͻ��˵ǼǵǼ�ʱ�� */
    #define XMLNM_BATCH_RESP_PTLS      "/batch/resp/ptls"        /* �����ͻ��˵Ǽ�ƽ̨��ˮ */
    #define XMLNM_BATCH_RESP_KHJL      "/batch/resp/khjl"        /* �����ͻ��˵Ǽǿͻ����� */
    #define XMLNM_BATCH_RESP_QYHM      "/batch/resp/qyhm"        /* �����ͻ��˵Ǽ�ǩԼ���� */
    #define XMLNM_BATCH_RESP_QYZH      "/batch/resp/qyzh"        /* �����ͻ��˵Ǽ�ǩԼ�ʺ� */
    #define XMLNM_BATCH_RESP_QYZT      "/batch/resp/qyzt"        /* �����ͻ��˵Ǽ�ǩԼ״̬ */
    #define XMLNM_BATCH_RESP_FSBZ      "/batch/resp/ksbz"        /* �����ͻ��˵ǼǷ��ͱ�־ */
    #define XMLNM_BATCH_RESP_KZZD1     "/batch/resp/kzzd1"       /* �����ͻ��˵Ǽ���չ�ֶ�1 */
    #define XMLNM_BATCH_RESP_KZZD2     "/batch/resp/kzzd2"       /* �����ͻ��˵Ǽ���չ�ֶ�2 */
    #define XMLNM_BATCH_RESP_KZZD3     "/batch/resp/kzzd3"       /* �����ͻ��˵Ǽ���չ�ֶ�3 */
    #define XMLNM_BATCH_RESP_KZZD4     "/batch/resp/kzzd4"       /* �����ͻ��˵Ǽ���չ�ֶ�4 */
    #define XMLNM_BATCH_RESP_SEND      "/batch/resp/fsbz"        /* �����ͻ���key���ͱ�ʶ */
    #define XMLNM_BATCH_RESP_COUNT     "/batch/resp/count"       /* ��ѯ���ر��� */
    #define XMLNM_BATCH_RESP_DWBH      "/batch/resp/dwbh"         /* �����ͻ��˵Ǽǿͻ���� */
    
    #define XMLNM_BATCH_HOST_AMT_FLAG  "/batch/host_tranamt_flag" /* ���ķ���ʵ�ʽ��׽���־ 1-������ 0-����(Ĭ��) */ 

    #define XMLNM_BATCH_FILEPATH       "/batch/filepath"          /*�����ļ�·��(ȫ·��)*/
    #define XMLNM_BATCH_SJTJ_FILENAME  "/batch/sjtj/filename"     /*�ļ�����*/
    #define XMLNM_BATCH_ABORNAUTO     "/batch/abnorauto"         /*���������쳣����0-������ 1-����(ȱʡ)*/

    /* �������񲽵���Ϣ */
    #define XMLNM_BATCH_STEPINFO_DQBD        "/batchstep/dqbd" /*��ǰ����*/
    #define XMLNM_BATCH_STEPINFO_FZBD        "/batchstep/fzbd" /*��������*/
    #define XMLNM_BATCH_STEPINFO_BDZT        "/batchstep/bdzt" /*����״̬*/
    #define XMLNM_BATCH_STEPINFO_RWZT        "/batchstep/rwzt" /*����״̬*/
    
    /*��������ҵ����*/
    #define XMLNM_BATCH_BUSIMON              "/batch/busimon"   /*������������Դ*/
    #define XMLNM_BATCH_MON_NORM             "/batch/mon/norm"  /*��������������*/
    #define XMLNM_BATCH_MON_UNORM            "/batch/mon/unorm" /*���������쳣���*/
    
    /*�����ļ�·��*/
    #define XMLNM_BATCH_FLPATH               "/batch/flpath"    /*�����ļ�·��*/
    #define XMLNM_BATCH_PRIHIGHPROC          "/batch/priproc/high"  /*��������æʱ�и߼����ȴ�����*/
    #define XMLNM_BATCH_HOSTFILE             "/batch/host/fileflg" /*�������������������ļ���־0-����,1-ɾ��*/
#endif
