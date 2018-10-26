/********************************************************************
版权所有:恒生电子股份有限公司（杭州）
项目名称:中间业务平台项目(AGENT2.0)
版    本:V2.0
操作系统:AIX5.3+ORA10G+HSXP
文件名称:batch_head.h
文件描述:批量平台通用头文件
项 目 组:中间业务平台项目组
程 序 员:chensy
发布日期:
*********************************************************************/

#ifndef __BATCH_HEAD_H__
#define __BATCH_HEAD_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "batch_macro.h"
#include "batch_xmlmacro.h"
#include "batch_mid.h"
#include "batch_msg.h"
#include "BATCH_FLOWCFG.h"
#include "BATCH_FILEMAP.h"
#include "BATCH_FILECOLUMN.h"
#include "BATCH_FILESORT.h"
#include "BATCH_AUDITINGFUNC.h"
#include "BATCH_TABLEREG.h"
#include "BATCH_WBWJDJ.h"
#include "BATCH_RUNCTRL.h"
#include "BATCH_MAPINFO.h"
#include "BATCH_MAPRESP.h"
#include "BATCH_PLRW.h"
#include "BATCH_PLRWBD.h"
#include "BATCH_FILETYPE.h"
#include "BATCH_STEPCFG.h"
#include "BATCH_CLI_USER.h"
#include "BATCH_ZJXX.h"
#include "APP_XLKZ.h"
#include "BATCH_LOCKPLRW.h"
#include "BATCH_STEPINFO.h"
#include "BATCH_STEPRWQT.h"
/*#include "BATCH_P2LJ.h"*/
#include "i_list.h"

i_list_t * t_fileTotalSortList;  /* 汇总分类链表 */
i_list_t * t_fileDetailSortList; /* 明细分类链表 */
i_list_t * t_fileColumnList;     /* 文件信息链表 */
i_list_t * t_fileMapList;/* 文件映射链表 */
i_list_t * t_tableRegList;
i_list_iter_t *pfileTotalSortIter;
i_list_iter_t *pfileDetailSortIter;
i_list_iter_t *pfileColumnIter;
i_list_iter_t *pfileMapIter;
i_list_iter_t *ptableRegIter;
i_list_t * t_flowList;
i_list_t * t_step_flowList;
i_list_iter_t *pflowIter;
i_list_t * t_auditingList;
i_list_iter_t *pauditingIter;
BATCH_FILESORT *gSFileTotalSort; /* 文件分类 */
BATCH_FILESORT *gSFileDetailSort; /* 文件分类 */
BATCH_FILECOLUMN *gSFileColumn; /* 文件信息 */
BATCH_FILEMAP *gSFileMap; /* 文件映射 */
BATCH_TABLEREG *gSTableReg; /* 表结构注册 */
BATCH_FLOWCFG *pFlowcfg;
BATCH_AUDITINGFUNC *pAuditingFunc;

typedef struct
{
  int length;
  char data[1024000];
} batchlong;

#endif

