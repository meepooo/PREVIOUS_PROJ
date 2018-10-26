/********************************************************************
版权所有:杭州恒生电子股份有限公司
项目名称:批量业务平台项目
版    本:V3.2
操作系统:AIX5.3+ORACLE10.2+ANSI.C
文件名称:batch_macro.h
文件描述:批量业务平台宏定义文件
项 目 组:批量业务平台项目组
程 序 员:
发布日期:2009-3-25 10:49:57
修    订:
修改日期:
*********************************************************************/

#if !defined(__BATCH_MACRO__H)
#define __BATCH_MACRO__H

/* xml节点最大长度  */
#define  BATCH_MAX_XML 1024000

/* 分割符分割字符串 */
#define BATCH_DIV        "+"

/* 分割符分割字符串最大长度 */
#define BATCH_MAXLEN_DIV  30

/* 平台流程最大步点数目 */
#define  BATCH_MAX_STEP_NUM   6

/* 批量文件分类最大数目 */
#define  BATCH_MAX_FILESORT_NUM  10

/* 批量文件列信息最大数 */
#define  BATCH_MAX_FILE_COL_NUM     64

/* 文件列最大长度 */ 
#define  BATCH_MAX_FILE_COL_LEN 256 

/* 文件映射列信息最大数 */
#define  BATCH_MAX_FILEMAP_NUM   100

/* 数据审核函数最大数目 */
#define  BATCH_MAX_AUDITING_NUM   10

/* 注册表列信息最大数目 */
#define BATCH_MAX_TABLEREG_NUM   100

/* 文件记录最大长度 */
#define  BATCH_MAX_FILELINE_BYTE 1024 

/* 最长断点时间 12小时 86400秒  */
#define  BATCH_MAX_BREAK_SECONDS  864000   

/* 最步点最大重复次数  */
#define  BATCH_MAX_STEP_REPEAT 5 

/* 自动任务最小轮询间隔  */
#define  BATCH_MIN_BREAK_AUTO  60

/* 响应码映射最大项数 */
#define  BATCH_MAX_RESP 50

/* 成功响应码 */
#define  BATCH_REPSCODE_SUCC  "00000"

/*批量任务业务监控*/
#define  BATCH_MON_NORM  "MON_BATCH_NORM"
#define  BATCH_MON_UNORM  "MON_BATCH_UNORM"

/* 批量全局属性名称定义 */
#define BATCH_ATTRIBUTE_CLLCM     "cllcm"   /* 处理流程名称 */
#define BATCH_ATTRIBUTE_DDBZ      "ddbz"    /* 断点标识 */
#define BATCH_ATTRIBUTE_DDSJ      "ddsj"    /* 断点时间 */

/*  数据获取方式属性定义*/
#define BATCH_ATTRIBUTE_HQSJFS_FTP    "0"   /*FTP获取方式*/
#define BATCH_ATTRIBUTE_HQSJFS_WEB    "1"   /*WEB获取方式*/
#define BATCH_ATTRIBUTE_HQSJFS_PKG    "2"   /*PKG获取方式*/
#define BATCH_ATTRIBUTE_HQSJFS_PCDT   "3"   /*批次重提方式*/
#define BATCH_ATTRIBUTE_HQSJFS_SGLR   "4"   /*手工录入方式*/

/* 重复操作标识属性定义 */
#define BATCH_ATTRIBUTE_CFCZBZ_YES   "0"  /* 步点允许重复操作*/
#define BATCH_ATTRIBUTE_CFCZBZ_NO    "1"  /* 步点不允许重复操作*/

/* 断点属性定义 */
#define BATCH_ATTRIBUTE_DDBZ_NOBREAK    '0'    /* 无断点,继续执行下个步点 */
#define BATCH_ATTRIBUTE_DDBZ_BREAK      '1'    /* 有断点,休眠一段时间后继续进行 */
#define BATCH_ATTRIBUTE_DDBZ_RETURN     '2'    /* 返回不再执行下个步点 */

/* 明细提交标志 */
#define BATCH_MXTJBZ_NONPROC_FAIL  "1"          /* 提交本业务未处理及失败明细 */

/* 明细回盘标志 */
#define BATCH_ATTRIBUTE_MXHPBZ_ALLDATA "0"       /* 生成所有批次全部明细 */
#define BATCH_ATTRIBUTE_MXHPBZ_ALL    "1"        /* 生成本批次处理明细 */
#define BATCH_ATTRIBUTE_MXHPBZ_SUCC   "2"        /* 生成本批次处理成功明细 */
#define BATCH_ATTRIBUTE_MXHPBZ_FAIL   "3"        /* 生成本批次处理失败明细 */
#define BATCH_ATTRIBUTE_MXHPBZ_BOTH   "4"        /* 分别生成本批成功和失败明细*/

/* 发送文件方式定义 */
#define BATCH_ATTRIBUTE_FSSJGS_FTP    "0"   /*FTP获取方式*/
#define BATCH_ATTRIBUTE_FSSJGS_WEB    "1"   /*WEB获取方式*/
#define BATCH_ATTRIBUTE_FSSJGS_PKG    "2"   /*PKG获取方式*/

/* 外部文件登记表批次状态 */
#define WBWJDJ_ZT_PRE     '1'   /* 正在上传 */
#define WBWJDJ_ZT_READY   '2'   /* 就绪 */
#define WBWJDJ_ZT_RUNNING '3'   /* 正在处理 */
#define WBWJDJ_ZT_SUCC    '4'   /* 已返回 */
#define WBWJDJ_ZT_FAIL    '5'   /* 处理失败 */
#define WBWJDJ_ZT_CX      'X'   /* 已撤销 */

/* 外部文件登记表审核状态 */
#define WBWJDJ_SHZT_YES     '0'   /* 审核通过 */
#define WBWJDJ_SHZT_NO      '1'   /* 未审核 */
#define WBWJDJ_SHZT_FAIL    '2'   /* 审核失败 */

/* 批量平台全局步点定义 */
#define BATCH_STEPSN_HQSJ   '0'   /* 获取数据 */
#define BATCH_STEPSN_SJRK   '1'   /* 数据入库 */
#define BATCH_STEPSN_SJSH   '2'   /* 数据审核 */
#define BATCH_STEPSN_SJTJ   '3'   /* 数据提交 */
#define BATCH_STEPSN_SJTH   '4'   /* 数据提回 */
#define BATCH_STEPSN_SJHP   '5'   /* 企业回盘 */
#define BATCH_STEPSN_FINL   '6'   /* 步点终态 */
#define BATCH_STEPSN_RWQT   '7'   /* 任务嵌套 */


#define BATCH_STEPNM_HQSJ   "hqsj"   /* 获取数据 */
#define BATCH_STEPNM_SJRK   "sjrk"   /* 数据入库 */
#define BATCH_STEPNM_SJSH   "sjsh"   /* 数据审核 */
#define BATCH_STEPNM_SJTJ   "sjtj"   /* 数据提交 */
#define BATCH_STEPNM_SJTH   "sjth"   /* 数据提回 */
#define BATCH_STEPNM_SJHP   "sjhp"   /* 企业回盘 */
#define BATCH_STEPNM_RWQT   "rwqt"   /* 任务嵌套 */

/* 步点状态定义 */
#define BATCH_STEP_STATUS_RUNNING   '9'   /* 处理中 */
#define BATCH_STEP_STATUS_STOP      '0'   /* 终止 */
#define BATCH_STEP_STATUS_END       '1'   /* 结束 */
#define BATCH_STEP_STATUS_BREAK     '2'   /* 断点 */
#define BATCH_STEP_STATUS_RETURN    '3'   /* 返回 */
#define BATCH_STEP_STATUS_WAIT      '4'   /* 等待 */
#define BATCH_STEP_STATUS_X         'X'   /* 撤销 */

#define BATCH_STEP_STATUS_S_RUNNING   "9"   /* 处理中 */
#define BATCH_STEP_STATUS_S_STOP      "0"   /* 终止 */
#define BATCH_STEP_STATUS_S_END       "1"   /* 结束 */
#define BATCH_STEP_STATUS_S_BREAK     "2"   /* 断点 */
#define BATCH_STEP_STATUS_S_RETURN    "3"   /* 返回 */
#define BATCH_STEP_STATUS_S_WAIT      "4"   /* 等待 */
#define BATCH_STEP_STATUS_S_X         "X"   /* 撤销 */

/* 辅助步点状态定义 */
#define BATCH_STEP_ASTSTEP_INIT     "00"  /* 待受理，初始 */
#define BATCH_STEP_ASTSTEP_ACTING   "09"  /* 受理中 */
#define BATCH_STEP_ASTSTEP_WRET     "10"  /* 待返回 */
#define BATCH_STEP_ASTSTEP_RETING   "19"  /* 返回中 */
#define BATCH_STEP_ASTSTEP_RETURN   "11"  /* 已返回 */
#define BATCH_STEP_ASTSTEP_END      "99"  /* 已结束 */

/* 任务状态定义 */
#define BATCH_TASK_STATUS_S_RUNNING   "9"   /* 处理中 */
#define BATCH_TASK_STATUS_S_STOP      "0"   /* 失败 */
#define BATCH_TASK_STATUS_S_END       "1"   /* 结束 */
#define BATCH_TASK_STATUS_S_PAUSE     "2"   /* 暂停 */
#define BATCH_TASK_STATUS_S_RETURN    "3"   /* 返回 */
#define BATCH_TASK_STATUS_S_CANCEL    "X"   /* 撤销 */
#define BATCH_TASK_STATUS_S_CORRECT   "C"   /* 冲正 */
#define BATCH_TASK_STATUS_S_TERM      "Z"   /* 强制终止 */
/* 步点成功标志 */
#define BATCH_STEP_S_SUCC      "0"   /* 成功 */
#define BATCH_STEP_S_FAIL      "1"   /* 失败 */
#define BATCH_STEP_S_RETURN    "2"   /* 返回 */
#define BATCH_STEP_S_WAIT      "3"   /* 等待 */

/* 明细成功标志 */
#define BATCH_CGBZ_S_SUCC      "0"   /* 成功 */
#define BATCH_CGBZ_S_BFSUCC    "1"   /* 部分成功 */
#define BATCH_CGBZ_S_FAIL    "2"   /* 处理失败 */

/* 文件格式定义 */
#define BATCH_FILETYPE_TYPE_TXT  '0'   /* 文本文件 */
#define BATCH_FILETYPE_TYPE_PDF  '1'   /* PDF格式 */
#define BATCH_FILETYPE_TYPE_XSL  '2'   /* EXCEL格式 */
#define BATCH_FILETYPE_TYPE_XML  '3'   /* XML文本格式 */

#define BATCH_FILETYPE_FMT_SINGLE  '0'   /* 单分类 */
#define BATCH_FILETYPE_FMT_MULTI   '1'   /* 多分类 */

/* 文件分类定义 */
#define BATCH_FILESORT_TYPE_TOTAL   1   /*  汇总 */
#define BATCH_FILESORT_TYPE_DETAIL  2   /*  明细 */
#define BATCH_FILESORT_TYPE_S_TOTAL   "1"   /*  汇总 */
#define BATCH_FILESORT_TYPE_S_DETAIL  "2"   /*  明细 */

#define BATCH_FILESORT_POSITION_ZDH    '1'   /*  指定行 */
#define BATCH_FILESORT_POSITION_JLBS   '2'   /*  记录标识 */
#define BATCH_FILESORT_POSITION_AHZJL  '3'   /*  汇总记录之后 */

#define BATCH_FILESORT_COLUNM_FIX    '1'   /*  定长 */
#define BATCH_FILESORT_COLUNM_SPLIT  '2'   /*  分割符 */
#define BATCH_FILESORT_COLUNM_SPLIT_TAIL  '3'   /* 去尾分割符 */

/*文件映射定义*/
#define BATCH_FILEMAP_LYLX_FILE     '1'   /* 来盘文件获取 */
#define BATCH_FILEMAP_LYLX_XML      '2'   /* XML获取 */
#define BATCH_FILEMAP_LYLX_WJSEQ    '3'   /* 文件序号 */
#define BATCH_FILEMAP_LYLX_SEQ      '4'   /* 流水序号 */
#define BATCH_FILEMAP_LYLX_CONST    '5'   /* 常量处理 */
#define BATCH_FILEMAP_LYLX_ZHQZLSH  '6'   /* 综合前置流水号 */
 
/*文件列属性定义 */
#define BATCH_FILECOLUMN_LSX_ADD     "0"   /* 明细记录属性-交易金额累加 */
#define BATCH_FILECOLUMN_LSX_SUB     "1"   /* 交易金额累减              */
#define BATCH_FILECOLUMN_LSX_SUM     "2"   /* 字段SUM                   */
#define BATCH_FILECOLUMN_LSX_COUNT   "3"   /* 字段COUNT                 */
#define BATCH_FILECOLUMN_LSX_SETXML  "4"   /* 4-值设置 xml节点   */
#define BATCH_FILECOLUMN_LSX_GETXML  "5"   /* 5-值获取(xml节点或常量)   */
#define BATCH_FILECOLUMN_LSX_ZBS     "6"   /* 汇总记录属性-汇总笔数     */
#define BATCH_FILECOLUMN_LSX_ZJE     "7"   /* 汇总记录属性-汇总金额     */
#define BATCH_FILECOLUMN_LSX_SHPCH   "8"   /* 汇总记录属性-商户批次号   */

#define BATCH_PTPCH_XLJZ "K_BATCH_PCH"     /* 平台批次号序列键值 */

#define BATCH_TOTAL_HEAD   0     /* 汇总记录位置  头 */         
#define BATCH_TOTAL_TAIL   1     /* 汇总记录位置  尾 */         

#define BATCH_KHBH_XLJZ "K_BATCH_KHBH" /* 批量客户端客户编号序列 */
#define BATCH_XYBH_XLJZ "K_BATCH_XYBH" /* 批量客户端协议编号序列 */

/*任务优先级*/
#define BATCH_TASKPRI_LOWER    '0'     /* 低级 */         
#define BATCH_TASKPRI_MIDDLE   '1'     /* 中级 */ 
#define BATCH_TASKPRI_HIGH     '2'     /* 高级 */ 

#endif


