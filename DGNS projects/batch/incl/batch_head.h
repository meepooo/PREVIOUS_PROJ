/********************************************************************
��Ȩ����:�������ӹɷ����޹�˾�����ݣ�
��Ŀ����:�м�ҵ��ƽ̨��Ŀ(AGENT2.0)
��    ��:V2.0
����ϵͳ:AIX5.3+ORA10G+HSXP
�ļ�����:batch_head.h
�ļ�����:����ƽ̨ͨ��ͷ�ļ�
�� Ŀ ��:�м�ҵ��ƽ̨��Ŀ��
�� �� Ա:chensy
��������:
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

i_list_t * t_fileTotalSortList;  /* ���ܷ������� */
i_list_t * t_fileDetailSortList; /* ��ϸ�������� */
i_list_t * t_fileColumnList;     /* �ļ���Ϣ���� */
i_list_t * t_fileMapList;/* �ļ�ӳ������ */
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
BATCH_FILESORT *gSFileTotalSort; /* �ļ����� */
BATCH_FILESORT *gSFileDetailSort; /* �ļ����� */
BATCH_FILECOLUMN *gSFileColumn; /* �ļ���Ϣ */
BATCH_FILEMAP *gSFileMap; /* �ļ�ӳ�� */
BATCH_TABLEREG *gSTableReg; /* ��ṹע�� */
BATCH_FLOWCFG *pFlowcfg;
BATCH_AUDITINGFUNC *pAuditingFunc;

typedef struct
{
  int length;
  char data[1024000];
} batchlong;

#endif

