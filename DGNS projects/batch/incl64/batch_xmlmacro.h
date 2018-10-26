/********************************************************************
版权所有:杭州恒生电子股份有限公司
项目名称:综合应用平台（GAPS）项目
版    本:V1.0
操作系统:AIX SCO LINUX SunOS HP-UX
数 据 库:ORACLE10G
文件名称:批量业务平台通用XML元素名称宏定义头文件
文件描述:batch_xmlmacro.h
项 目 组:
程 序 员:
发布日期:
*********************************************************************/
/********************************************************************
修改记录
修改日期:2011-3-09
修改内容:
修改人:
*********************************************************************/

#ifndef __BATCH_XMLMACRO_H__
#define __BATCH_XMLMACRO_H__
     
    /* 外部文件登记表请求节点定义 */
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
    #define XMLNM_BATCH_REQ_DWBH        "/batch/req/dwbh"         /* 批量客户端登记客户编号 */
    #define XMLNM_BATCH_REQ_YPKRQ       "/batch/req/ypkrq"
    #define XMLNM_BATCH_REQ_YPTPCH      "/batch/req/yptpch"

    /* 外部文件登记信息节点定义 */
    #define XMLNM_BATCH_WBWJDJ_DJRQ        "/batch/req/djrq"
    #define XMLNM_BATCH_WBWJDJ_DJLSH       "/batch/req/djlsh"
    #define XMLNM_BATCH_WBWJDJ_LPWJM       "/batch/req/lpwjm"
    
    /*运行控制信息节点定义 */
    #define XMLNM_BATCH_RUNCTRL_CPDM       "/batch/runctrl/cpdm"              /*产品代码*/
    #define XMLNM_BATCH_RUNCTRL_FLOWID     "/batch/runctrl/flowid"            /*流程ID*/
    #define XMLNM_BATCH_RUNCTRL_MAXTASK    "/batch/runctrl/maxtask"           /*最大任务数*/
    #define XMLNM_BATCH_RUNCTRL_MAXTHREAD  "/batch/runctrl/maxthread"         /*最大线程数*/
    #define XMLNM_BATCH_RUNCTRL_ZJYSBS     "/batch/runctrl/zjysbs"              /*映射标识*/
    #define XMLNM_BATCH_RUNCTRL_WWYSBS     "/batch/runctrl/wwysbs"              /*映射标识*/
    #define XMLNM_BATCH_RUNCTRL_SHBZ       "/batch/runctrl/shbz"              /*审核标志*/
    #define XMLNM_BATCH_RUNCTRL_TASKMODE   "/batch/runctrl/taskmode"          /*任务开始方式*/
    #define XMLNM_BATCH_RUNCTRL_TASKPRI   "/batch/runctrl/taskpri"          /*优先级*/
    #define XMLNM_BATCH_RUNCTRL_EXTFLD1    "/batch/runctrl/extfld1"           /*扩展字段1*/

    /*批量步点信息*/
    #define XMLNM_BATCH_STEPINFO_CURSTEP    "/batch/stepinfo/curstep"            /*当前步点*/
    #define XMLNM_BATCH_STEPINFO_CURASSSTEP "/batch/stepinfo/curassstep"         /*当前辅助步点*/
    #define XMLNM_BATCH_STEPINFO_CURSTATUS  "/batch/stepinfo/curstatus"          /*步点状态*/
    #define XMLNM_BATCH_STEPINFO_TASKSTATUS "/batch/stepinfo/taskstatus"         /*任务状态*/
    #define XMLNM_BATCH_STEPINFO_NEXTSTEP   "/batch/stepinfo/nextstep"           /*下一步点*/ 
    
    /* 批量映射信息表节点定义  */
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

    /*批量流程配置节点定义 */
    #define XMLNM_BATCH_FLOWCFG_FLOWID     "/batch/flowcfg/flowid"             /*流程ID*/
    #define XMLNM_BATCH_FLOWCFG_FLOWNAME   "/batch/flowcfg/flowname"           /*流程名称*/
    #define XMLNM_BATCH_FLOWCFG_FLOWSN     "/batch/flowcfg/flowsn"             /*流程序号*/
    #define XMLNM_BATCH_FLOWCFG_STEPID     "/batch/flowcfg/stepid"             /*步点标识*/
    #define XMLNM_BATCH_FLOWCFG_STEPSN     "/batch/flowcfg/stepsn"             /*步点序号*/    
    #define XMLNM_BATCH_FLOWCFG_STEPNAME     "/batch/flowcfg/stepname"         /*步点名称*/ 
    #define XMLNM_BATCH_FLOWCFG_EXTFLD1    "/batch/flowcfg/extfld1"            /*扩展字段1*/
    #define XMLNM_BATCH_FLOWCFG_EXTFLD2    "/batch/flowcfg/extfld2"            /*扩展字段2*/
     

    /*批量任务嵌套步点属性 */
    #define XMLNM_BATCH_STEPCFG_RWQT_CLLCM     "/batch/rwqt/cllcm"             /*处理流程名*/
    #define XMLNM_BATCH_STEPCFG_RWQT_BQTCPDM   "/batch/rwqt/bqtcpdm"           /*被嵌套产品代码*/
    #define XMLNM_BATCH_STEPCFG_RWQT_BQTYWBH   "/batch/rwqt/bqtywbh"           /*被嵌套业务编号*/
    #define XMLNM_BATCH_STEPCFG_RWQT_BQTPCYT   "/batch/rwqt/bqtpcyt"           /*被嵌套批次用途*/
    #define XMLNM_BATCH_STEPCFG_RWQT_QTWJYS    "/batch/rwqt/qtwjys"            /*嵌套文件映射*/
    #define XMLNM_BATCH_STEPCFG_RWQT_QTWJDC    "/batch/rwqt/qtwjdc"            /*嵌套文件导出*/
    
    /* 数据审核配置节点定义 */
    #define XMLNM_BATCH_AUDITING_AUDIID    "/batch/auditing/audiid"             
    #define XMLNM_BATCH_AUDITING_AUDISN    "/batch/auditing/audisn"           
    #define XMLNM_BATCH_AUDITING_FUNCID    "/batch/auditing/funcid"             
    #define XMLNM_BATCH_AUDITING_SHSBBZ    "/batch/auditing/shsbbz"          
    #define XMLNM_BATCH_AUDITING_PARASN    "/batch/auditing/parasn"     
    #define XMLNM_BATCH_AUDITING_PARA      "/batch/auditing/para"    
    
    /* 文件类型信息  */
    #define XMLNM_BATCH_WJLX_FILEID          "/batch/wjlx/fileid"
    #define XMLNM_BATCH_WJLX_FILETYPE        "/batch/wjlx/filetype"
    #define XMLNM_BATCH_WJLX_FILEFMT         "/batch/wjlx/filefmt"
    #define XMLNM_BATCH_WJLX_CODEFMT         "/batch/wjlx/codefmt"
    #define XMLNM_BATCH_WJLX_EXTFLD1         "/batch/wjlx/etxfld1"
        
    /* 全局数据XML节点定义 */
    #define XMLNM_BATCH                  "/batch" 
    #define XMLNM_BATCH_TASK_STATUS      "/batch/taskstatus"               /*任务状态*/
    #define XMLNM_BATCH_STEP_STATUS      "/batch/stepstatus"               /*步点状态*/
    #define XMLNM_BATCH_STEPSN           "/batch/stepsn"                   /*步点序号*/
    #define XMLNM_BATCH_STEPID           "/batch/stepid"                   /*步点标识*/
    #define XMLNM_BATCH_TASKPRI          "/batch/taskpri"
    #define XMLNM_BATCH_PKRQ             "/batch/pkrq"
    #define XMLNM_BATCH_PTPCH            "/batch/ptpch"
    #define XMLNM_BATCH_PLRWKEY          "/batch/plrwkey"
    #define XMLNM_BATCH_SHPCH            "/batch/shpch"
    #define XMLNM_BATCH_ZJPCH            "/batch/zjpch"
    #define XMLNM_BATCH_ZJJYRQ           "/batch/zjjyrq"
    #define XMLNM_BATCH_BDCGBZ           "/batch/bdcgbz"
    #define XMLNM_BATCH_MX_ZJE           "/batch/mxzje"      /*明细实际总金额*/ 
    #define XMLNM_BATCH_MX_ZBS           "/batch/mxzbs"      /*明细实际总笔数*/ 
    #define XMLNM_BATCH_CGZJE            "/batch/cgzje"      /*成功总金额*/ 
    #define XMLNM_BATCH_CGZBS            "/batch/cgzbs"      /*成功总笔数*/ 
    #define XMLNM_BATCH_SBZJE            "/batch/sbzje"      /*失败总金额*/   
    #define XMLNM_BATCH_SBZBS            "/batch/sbzbs"      /*失败总笔数*/ 
    #define XMLNM_BATCH_XKHBS            "/batch/xkhbs"      /*新开户笔数*/ 
    #define XMLNM_BATCH_XKHJE            "/batch/xkhje"      /*新开户金额*/ 
    #define XMLNM_BATCH_PLRW_DQBD        "/batch/dqbd"
    #define XMLNM_BATCH_CPDM             "/batch/cpdm"      /*产品代码*/ 
    #define XMLNM_BATCH_YWBH             "/batch/ywbh"      /*业务编号*/ 
    #define XMLNM_BATCH_MAXTASKNUM       "/batch/maxtasknum" /*最大任务数*/
    #define XMLNM_BATCH_YPKRQ            "/batch/ypkrq"
    #define XMLNM_BATCH_YPTPCH           "/batch/yptpch"


    #define XMLNM_BATCH_HZ_ZJE          "/batch/hqsj/hzzje"      /*来盘文件汇总记录里的总金额*/
    #define XMLNM_BATCH_HZ_ZBS          "/batch/hqsj/hzzbs"      /*来盘文件汇总记录里的总笔数*/
    #define XMLNM_BATCH_HQSJ_HQSJFS     "/batch/hqsj/hqsjfs"  /*获取数据方式*/

    #define XMLNM_BATCH_SJSH_SHBS         "/batch/sjsh/shbs"      /*审核标识*/

    #define XMLNM_BATCH_SJTJ_ZJE          "/batch/sjtj/zje"      /*生成主机提交文件的总金额*/
    #define XMLNM_BATCH_SJTJ_ZBS          "/batch/sjtj/zbs"      /*生成主机提交文件的总笔数*/
    #define XMLNM_BATCH_SJTJ_WJS          "/batch/sjtj/wjs"      /*提交主机文件个数 */
    #define XMLNM_BATCH_SJTJ_WJM          "/batch/sjtj/wjm"      /*上传文件名*/ 
    #define XMLNM_BATCH_SJTJ_WJLJ         "/batch/sjtj/wjlj"     /*提交主机文件路径 */
    #define XMLNM_BATCH_SJTJ_SUBMIITED_WJXH "/batch/sjtj/submiited_wjxh" /*已提交主机文件序号 */
    #define XMLNM_BATCH_SJTJ_GDDDSJ       "/batch/sjtj/gdddsj"   /*提交主机固定中断时间 */
    #define XMLNM_BATCH_SJTJ_FDDDSJ       "/batch/sjtj/fdddsj"   /*提交主机浮动中断时间 */
    #define XMLNM_BATCH_SJTJ_WAIT         "/batch/sjtj/wait"     /*提交主机中断时间 */
    #define XMLNM_BATCH_MAXHOSTWAIT       "/batch/sjtj/maxwait"  /*提交主机最长中断时间 */
    #define XMLNM_BATCH_MXTJBZ            "/batch/sjtj/mxtjbz"   /* 明细提交主机标志 */
    #define XMLNM_BATCH_SJTJ_CPDM         "/batch/sjtj/cpdm"     /*产品代码*/
    #define XMLNM_BATCH_SJTJ_YWBH         "/batch/sjtj/ywbh"     /*业务编号*/
    #define XMLNM_BATCH_SJTJ_STEPID       "/batch/sjtj/stepid"   /*任务步点*/
    #define XMLNM_BATCH_SJTJ_FLOWSN       "/batch/sjtj/flowsn"   /*流程序号*/
    #define XMLNM_BATCH_SJTJ_EXPWHERE     "/batch/sjtj/expwhere" /*导出条件*/

    #define XMLNM_BATCH_SJTH_ZJXH         "/batch/sjth/wjxh"     /*数据提回文件序号*/ 
    
    #define XMLNM_BATCH_SJHP_ZJE          "/batch/sjhp/zje"      /*生成回盘文件的总金额*/
    #define XMLNM_BATCH_SJHP_ZBS          "/batch/sjhp/zbs"      /*生成回盘文件的总笔数*/
    #define XMLNM_BATCH_SJHP_CGZJE        "/batch/sjhp/cgzje"    /*生成回盘文件的成功总金额*/
    #define XMLNM_BATCH_SJHP_CGZBS        "/batch/sjhp/cgzbs"    /*生成回盘文件的成功总笔数*/
    #define XMLNM_BATCH_SJHP_SBZJE        "/batch/sjhp/sbzje"    /*生成回盘文件的失败总金额*/
    #define XMLNM_BATCH_SJHP_SBZBS        "/batch/sjhp/sbzbs"    /*生成回盘文件的失败总笔数*/
    #define XMLNM_BATCH_SJHP_FILEDIR      "/batch/hqsj/filedir"  /*商户回盘文件路径同来盘文件路径*/ 
    #define XMLNM_BATCH_SJHP_REPEAT       "/batch/sjhp/cfczbz"   /*商户回盘重复操作标志*/ 
    #define XMLNM_BATCH_SJHP_CGWJ         "/batch/sjhp/filename"     /*商户回复成功文件*/ 
    #define XMLNM_BATCH_SJHP_SBWJ         "/batch/sjhp/filename_f"   /*商户回复失败文件*/ 
    #define XMLNM_BATCH_SJHP_CVTRESP      "/batch/sjhp/cvtresp"      /* 响应码转换范围 0 全部转换（默认） 1-只转换审核失败明细 */

    #define XMLNM_BATCH_SJCT_ZJE          "/batch/sjct/zje"      /*生成回盘文件的总金额*/
    #define XMLNM_BATCH_SJCT_ZBS          "/batch/sjct/zbs"      /*生成回盘文件的总笔数*/
    #define XMLNM_BATCH_SJCT_CGZJE        "/batch/sjct/cgzje"    /*生成回盘文件的成功总金额*/
    #define XMLNM_BATCH_SJCT_CGZBS        "/batch/sjct/cgzbs"    /*生成回盘文件的成功总笔数*/
    #define XMLNM_BATCH_SJCT_SBZJE        "/batch/sjct/sbzje"    /*生成回盘文件的失败总金额*/
    #define XMLNM_BATCH_SJCT_SBZBS        "/batch/sjct/sbzbs"    /*生成回盘文件的失败总笔数*/
    #define XMLNM_BATCH_SJCT_FILEDIR      "/batch/hqsj/filedir"  /*商户回盘文件路径同来盘文件路径*/ 
    #define XMLNM_BATCH_SJCT_REPEAT       "/batch/sjhp/cfczbz"   /*商户回盘重复操作标志*/ 
    #define XMLNM_BATCH_SJCT_CGWJ         "/batch/sjct/filename"     /*商户回复成功文件*/ 
    #define XMLNM_BATCH_SJCT_SBWJ         "/batch/sjct/filename_f"   /*商户回复失败文件*/ 
    #define XMLNM_BATCH_SJCT_CVTRESP      "/batch/sjct/cvtresp"      /* 响应码转换范围 0 全部转换（默认） 1-只转换审核失败明细 */

    #define XMLNM_BATCH_FORCE_RETURN      "/batch/forceReturn"   /* 强制返回状态 */
    #define XMLNM_BATCH_SJTJ_WJXH      "/batch/sjtj/wjxh"        /* 数据提交文件序号 */

    #define XMLNM_BATCH_FINAL_STEP     "/batch/final_step"       /* 流程尾部步点id */
    #define XMLNM_BATCH_FINAL_FLOWSN   "/batch/final_flowsn"     /* 流程尾部执行sn */
    #define XMLNM_BATCH_FINAL_STEPSN   "/batch/final_stepsn"     /* 流程尾部步点sn */
    #define XMLNM_BATCH_SJHP_EXIST     "/batch/sjhp_exist"       /* 流程数据回盘存在标志 */
    #define XMLNM_BATCH_SJHP_FLOWSN    "/batch/sjhp_flowsn"      /* 流程数据回盘执行sn */
    #define XMLNM_BATCH_SJHP_STEPSN    "/batch/sjhp_stepsn"      /* 流程数据回盘步点sn */    
    #define XMLNM_BATCH_STEP_FAIL      "/batch/steprepeat"       /* 步点最大失败重试次数 */
    #define XMLNM_BATCH_SJTJ_TIME      "/batch/req/sjtj_ksclsj"  /* 数据提交开始处理时间 */
    #define XMLNM_BATCH_SJTJ_DATE      "/batch/req/sjtj_ksclrq"  /* 数据提交开始处理日期 */
    #define XMLNM_BATCH_NIGHT_TIME     "/batch/night_time"       /* 批量夜间批量处理开始时间 */

    /* 客户端领用登记信息节点定义 */
    #define XMLNM_BATCH_REQ_KHBH       "/batch/req/khbh"         /* 批量客户端登记客户编号 */
    #define XMLNM_BATCH_REQ_KHMC       "/batch/req/khmc"         /* 批量客户端登记客户名称 */
    #define XMLNM_BATCH_REQ_XYBH       "/batch/req/xybh"         /* 批量客户端登记协议编号 */
    #define XMLNM_BATCH_REQ_LXR        "/batch/req/lxr"          /* 批量客户端登记联系人 */
    #define XMLNM_BATCH_REQ_DHHM       "/batch/req/dhhm"         /* 批量客户端登记联系人电话 */
    #define XMLNM_BATCH_REQ_SJHM       "/batch/req/sjhm"         /* 批量客户端登记联系人手机 */
    #define XMLNM_BATCH_REQ_EMAIL      "/batch/req/email"        /* 批量客户端登记联系人email */
    #define XMLNM_BATCH_REQ_JYJG       "/batch/req/jyjg"         /* 批量客户端登记交易机构 */
    #define XMLNM_BATCH_REQ_JYGY       "/batch/req/jygy"         /* 批量客户端登记交易柜员 */
    #define XMLNM_BATCH_REQ_DJRQ       "/batch/req/djrq"         /* 批量客户端登记日期 */
    #define XMLNM_BATCH_REQ_KHJL       "/batch/req/khjl"         /* 批量客户端登记客户经理*/
    #define XMLNM_BATCH_REQ_QYZH       "/batch/req/qyzh"         /* 批量客户端登记签约账号*/
    #define XMLNM_BATCH_REQ_QYHM       "/batch/req/qyhm"         /* 批量客户端登记签约户名*/
    
    #define XMLNM_BATCH_RESP_KEY       "/batch/resp/cli_pwd"     /* 批量客户端登记密钥 */
    #define XMLNM_BATCH_RESP_KHBH      "/batch/resp/khbh"        /* 批量客户端登记客户编号 */
    #define XMLNM_BATCH_RESP_XYBH      "/batch/resp/xybh"        /* 批量客户端登记协议编号 */
    #define XMLNM_BATCH_RESP_KHMC      "/batch/resp/khmc"        /* 批量客户端登记客户名称 */
    #define XMLNM_BATCH_RESP_LXR      "/batch/resp/lxr"        /* 批量客户端登记联系人 */
    #define XMLNM_BATCH_RESP_DHHM      "/batch/resp/dhhm"        /* 批量客户端登记联系人电话 */
    #define XMLNM_BATCH_RESP_SJHM      "/batch/resp/sjhm"        /* 批量客户端登记联系人手机号码 */
    #define XMLNM_BATCH_RESP_EMAIL      "/batch/resp/email"        /* 批量客户端登记联系人email */
    #define XMLNM_BATCH_RESP_JYJG      "/batch/resp/jyjg"        /* 批量客户端登记交易机构 */
    #define XMLNM_BATCH_RESP_JYGY      "/batch/resp/jygy"        /* 批量客户端登记交易柜员 */
    #define XMLNM_BATCH_RESP_DJRQ      "/batch/resp/djrq"        /* 批量客户端登记登记日期 */    
    #define XMLNM_BATCH_RESP_DJSJ      "/batch/resp/djsj"        /* 批量客户端登记登记时间 */
    #define XMLNM_BATCH_RESP_PTLS      "/batch/resp/ptls"        /* 批量客户端登记平台流水 */
    #define XMLNM_BATCH_RESP_KHJL      "/batch/resp/khjl"        /* 批量客户端登记客户经理 */
    #define XMLNM_BATCH_RESP_QYHM      "/batch/resp/qyhm"        /* 批量客户端登记签约户名 */
    #define XMLNM_BATCH_RESP_QYZH      "/batch/resp/qyzh"        /* 批量客户端登记签约帐号 */
    #define XMLNM_BATCH_RESP_QYZT      "/batch/resp/qyzt"        /* 批量客户端登记签约状态 */
    #define XMLNM_BATCH_RESP_FSBZ      "/batch/resp/ksbz"        /* 批量客户端登记发送标志 */
    #define XMLNM_BATCH_RESP_KZZD1     "/batch/resp/kzzd1"       /* 批量客户端登记扩展字段1 */
    #define XMLNM_BATCH_RESP_KZZD2     "/batch/resp/kzzd2"       /* 批量客户端登记扩展字段2 */
    #define XMLNM_BATCH_RESP_KZZD3     "/batch/resp/kzzd3"       /* 批量客户端登记扩展字段3 */
    #define XMLNM_BATCH_RESP_KZZD4     "/batch/resp/kzzd4"       /* 批量客户端登记扩展字段4 */
    #define XMLNM_BATCH_RESP_SEND      "/batch/resp/fsbz"        /* 批量客户端key发送标识 */
    #define XMLNM_BATCH_RESP_COUNT     "/batch/resp/count"       /* 查询返回笔数 */
    #define XMLNM_BATCH_RESP_DWBH      "/batch/resp/dwbh"         /* 批量客户端登记客户编号 */
    
    #define XMLNM_BATCH_HOST_AMT_FLAG  "/batch/host_tranamt_flag" /* 核心返回实际交易金额标志 1-不返回 0-返回(默认) */ 

    #define XMLNM_BATCH_FILEPATH       "/batch/filepath"          /*批量文件路径(全路径)*/
    #define XMLNM_BATCH_SJTJ_FILENAME  "/batch/sjtj/filename"     /*文件名称*/
    #define XMLNM_BATCH_ABORNAUTO     "/batch/abnorauto"         /*批量任务异常处理0-不处理 1-处理(缺省)*/

    /* 批量任务步点信息 */
    #define XMLNM_BATCH_STEPINFO_DQBD        "/batchstep/dqbd" /*当前步点*/
    #define XMLNM_BATCH_STEPINFO_FZBD        "/batchstep/fzbd" /*辅助步点*/
    #define XMLNM_BATCH_STEPINFO_BDZT        "/batchstep/bdzt" /*步点状态*/
    #define XMLNM_BATCH_STEPINFO_RWZT        "/batchstep/rwzt" /*任务状态*/
    
    /*批量任务业务监控*/
    #define XMLNM_BATCH_BUSIMON              "/batch/busimon"   /*批量任务监控资源*/
    #define XMLNM_BATCH_MON_NORM             "/batch/mon/norm"  /*批量任务受理监控*/
    #define XMLNM_BATCH_MON_UNORM            "/batch/mon/unorm" /*批量任务异常监控*/
    
    /*批量文件路径*/
    #define XMLNM_BATCH_FLPATH               "/batch/flpath"    /*批量文件路径*/
    #define XMLNM_BATCH_PRIHIGHPROC          "/batch/priproc/high"  /*批量任务繁忙时中高级优先处理数*/
    #define XMLNM_BATCH_HOSTFILE             "/batch/host/fileflg" /*批量任务与主机交互文件标志0-保留,1-删除*/
#endif
