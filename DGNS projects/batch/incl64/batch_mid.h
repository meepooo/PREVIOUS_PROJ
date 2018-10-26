/**********************************************************************
版权所有:杭州恒生电子股份有限公司
项目名称:综合应用平台（GAPS）项目
版    本:V2.1.0.1
操作系统:AIX LINUX 
数 据 库:
文 件 名:batch_mid.h
文件描述:批量平台出错信息宏定义头文件
项 目 组:中间业务产品研发组
程 序 员:中间业务产品研发组
发布时间:2011-8-1 10:53:19
**********************************************************************/
/*
修改记录
修改日期:
修改内容:
修改人:
*/
#ifndef __BATCH_MID_H__
#define __BATCH_MID_H__
    #define MID_BATCH_AUDITING_NOFUND         90401
    #define MID_BATCH_AUDITINGREG_NOFUND      90402
    #define MID_BATCH_BDCGBZ_FF               90403
    #define MID_BATCH_BDZT_DD                 90404
    #define MID_BATCH_BDZT_FF                 90405
    #define MID_BATCH_BDZT_SUCC               90406
    #define MID_BATCH_BDZT_WAIT               90407
    #define MID_BATCH_BUSITASKOVER            90408
    #define MID_BATCH_CFCZ                    90409
    #define MID_BATCH_CFCZOVER                90410
    #define MID_BATCH_CZBD_NULL               90419
    #define MID_BATCH_DEL_YWMX                90421
    #define MID_BATCH_DJLSH_NULL              90422
    #define MID_BATCH_DJRQ_NULL               90423
    #define MID_BATCH_EXEC_FLOW               90424
    #define MID_BATCH_EXECSO                  90425
    #define MID_BATCH_EXPORT                  90426
    #define MID_BATCH_FILECOLUMN_LISTFAIL     90427
    #define MID_BATCH_FILE_MAPFAIL            90428
    #define MID_BATCH_FILEMAP_LISTFAIL        90429
    #define MID_BATCH_FILESORT_LISTFAIL       90430
    #define MID_BATCH_FLOWCFG_NOFUND          90431
    #define MID_BATCH_GET_FILESORT            90432
    #define MID_BATCH_GET_STEPCFG             90433
    #define MID_BATCH_GLB_NOFUND              90434
    #define MID_BATCH_HSRK_NOFUND             90435
    #define MID_BATCH_INS_PLRW                90436
    #define MID_BATCH_INS_PLRWBD              90437
    #define MID_BATCH_JYHS_FAIL               90438
    #define MID_BATCH_LOAD_YWMX               90439
    #define MID_BATCH_LPWJM_NULL              90440
    #define MID_BATCH_LRZBS_MXZBS             90441
    #define MID_BATCH_LRZJE_MXZJE             90442
    #define MID_BATCH_LXX_NOFUND              90443
    #define MID_BATCH_PKRQ_NULL               90445
    #define MID_BATCH_PRODUCTTASKOVER         90447
    #define MID_BATCH_PTPCH_NULL              90448
    #define MID_BATCH_SEL_MAPINFO             90449
    #define MID_BATCH_SEL_PLRW                90450
    #define MID_BATCH_SEL_PLRWBD              90451
    #define MID_BATCH_SEL_RUNCTR              90453
    #define MID_BATCH_SEL_SHGZPZ              90454
    #define MID_BATCH_SEL_WBWJDJ              90455
    #define MID_BATCH_SEL_WJLX                90456
    #define MID_BATCH_WJLX_NULL               90457
    #define MID_BATCH_SHPCH                   90458
    #define MID_BATCH_SJRK                    90460
    #define MID_BATCH_SO_CLOSE                90461
    #define MID_BATCH_SO_OPEN                 90462
    #define MID_BATCH_SQLSEL_PLRW_ERR         90463
    #define MID_BATCH_TABLEREG_LISTFAIL       90464
    #define MID_BATCH_TOTALPROC               90465
    #define MID_BATCH_DETAILPROC              90465
    #define MID_BATCH_UPDFLAG_FF              90466
    #define MID_BATCH_UPD_PLRW                90467
    #define MID_BATCH_UPD_PLRWBD              90468
    #define MID_BATCH_UPD_SHZT                90469
    #define MID_BATCH_UPD_WBWJDJ              90470
    #define MID_BATCH_WBWJDJ_CX               90471
    #define MID_BATCH_WBWJDJ_FAIL             90472
    #define MID_BATCH_WBWJDJ_NOFUND           90473
    #define MID_BATCH_WBWJDJ_PRE              90474
    #define MID_BATCH_WBWJDJ_RUNNING          90475
    #define MID_BATCH_WBWJDJ_SUCC             90476
    #define MID_BATCH_WBWJDJ_UNKNOWN          90477
    #define MID_BATCH_WJBS_NULL               90479
    #define MID_BATCH_WJM_NULL                90481
    #define MID_BATCH_WJZBS_MXZBS             90482
    #define MID_BATCH_WJZJE_MXZJE             90483
    #define MID_BATCH_XMLDEL                  90484
    #define MID_BATCH_XMLIMPORT               90485
    #define MID_BATCH_YSBS_NULL               90486
    #define MID_BATCH_YWBH_NULL               90487
    #define MID_BATCH_YWBM_NULL               90488
    #define MID_BATCH_INS_WBWJDJ              90489
    #define MID_BATCH_OPENFILE                90490
    #define MID_BATCH_WRITEFILE               90490
    #define MID_BATCH_SJTJ_GENFILE            90491
    #define MID_BATCH_LPWJ_NULL               90492
    #define MID_BATCH_BREAK_LAUNCHED          90531
    #define MID_BATCH_FILECOLUMN_NOTFOUND     90532
    #define MID_BATCH_WJGS_FF                 90533
    #define MID_BATCH_TABLECOL_NOTFOUND       90534
    #define MID_BATCH_SJTH_ZJE                90535
    #define MID_BATCH_SJTH_ZBS                90536
    #define MID_BATCH_SJHP_UNLOAD             90537
    #define MID_BATCH_RESP_CONV               90538
    #define MID_BATCH_PROC_DETAIL             90539
    #define MID_BATCH_PROC_TOTAL              90540
    #define MID_BATCH_SJHP_PZNULL             90541
    #define MID_BATCH_SJHP_HPBZ               90542
    #define MID_BATCH_CANCELED                90543
    #define MID_BATCH_SJTH_PROC               90550
    #define MID_BATCH_HQSJ_GETFILE            90551
    #define MID_BATCH_QUERY_PQRYERR           90552
    #define MID_BATCH_QUERY_COLERR            90553
    #define MID_BATCH_JYFSERR                 90554
    #define MID_BATCH_TIMEERR                 90555
    #define MID_BATCH_TIME_SETERR             90556
    #define MID_BATCH_LAUNCHED                90557
    #define MID_BATCH_SPLIT_INVAL             90558
    #define MID_BATCH_DE_FLAG                 90560
    #define MID_BATCH_GEN_KHBH                90561
    #define MID_BATCH_GEN_XYBH                90562
    #define MID_BATCH_NULL_CLI_BH             90563
    #define MID_BATCH_NO_CLIINFO              90564
    #define MID_BATCH_UPD_CLIINFO             90565
    #define MID_BATCH_QUYCON                  90566
    #define MID_BATCH_FIELTRANSFER            90567
    #define MID_BATCH_SJRK_SQLNOTNULL         90568
    #define MID_BATCH_DES_FILEERR             90569
    #define MID_BATCH_DES_WRERR               90570
    #define MID_BATCH_RESPNULL                90571
    #define MID_BATCH_SJRK_OVERLEN            90572
    #define MID_BATCH_UPDPLRW_NFND            90573
    #define MID_BATCH_STEPINFO                90574
    #define MID_BATCH_STEP_SUCC               90575
    #define MID_BATCH_PROCING                 90576
    #define MID_BATCH_SJHP_NOTHIS             90577
    #define MID_BATCH_SJHP_FORCE              90578
    #define MID_BATCH_SJTH_NOCONFIG           90579
    #define MID_BATCH_PROCLINE_NOTNULL        90580
    #define MID_BATCH_WJGS_CONV               90581
    #define MID_BATCH_RWQT_CPDMNEQ            90582
    #define MID_BATCH_SH_WBWJDJ               90583
    #define MID_BATCH_DIRRETURN               90584
    #define MID_BATCH_DIRFORCE                90585
    #define MID_BATCH_SJTJ_NIGHT              90585
    #define MID_BATCH_SJTH_UPDZERO            90586
    #define MID_BATCH_SJTH_UPDMULT            90587
    #define MID_BATCH_JYJGNULL                90588
    #define MID_BATCH_SJRK_SUMAMT             90589
    #define MID_BATCH_SJTJ_WAIT               90590
#endif

