/*********************************************************************** 
版权所有:恒生电子股份有限公司                                            
项目名称:综合技术平台(Turandot)项目                                      
版    本:V1.00                                                           
操作系统:                                                                
数 据 库:db2                                                             
文 件 名:ICPS_WBC_TM_GL_BAL.h                                          
文件描述:结构定义数据库开发嵌C头文件                                     
项 目 组:                                                                
程 序 员:[fuwd22392]                                                     
发布时间:2018-06-12 10:00:00 [Gen]                                       
修    订:                                                                
修改时间:                                                                
************************************************************************ 
表    名:ICPS_WBC_TM_GL_BAL                                            
说    明:总账会计科目表                                                                
************************************************************************ 
修改记录:                                                                
修改日期:                                                                
修改内容:                                                                
修 改 人:                                                                
修改内容:                                                                
************************************************************************/
#ifndef __ICPS_WBC_TM_GL_BAL_H__     
#define __ICPS_WBC_TM_GL_BAL_H__     
typedef struct TDB_ICPS_WBC_TM_GL_BAL
{                                      
    char            busi_date[8+1];              
    int             file_order;                      
    char            org[12+1];                   /*机构号        */
    char            subject[40+1];               /*科目          */
    char            branch_id[9+1];              /*分支行号      */
    double          db_bal;                      /*借方余额      */
    double          cr_bal;                      /*贷方余额      */
    double          db_amt;                      /*借方发生额    */
    int             db_count;                    /*借方笔数      */    
    double          cr_amt;                      /*贷方发生额    */
    int             cr_count;                    /*贷方笔数      */    
    double          last_db_bal;                 /*昨日借方余额  */
    double          last_cr_bal;                 /*昨日贷方余额  */
    double          last_mth_db_bal;             /*上月末借方余额*/
    double          last_mth_cr_bal;             /*上月末贷方余额*/
    double          last_qtr_db_bal;             /*上季末借方余额*/
    double          last_qtr_cr_bal;             /*上季末贷方余额*/
    double          last_yr_db_bal;              /*上年末借方余额*/
    double          last_yr_cr_bal;              /*上年末贷方余额*/
    int             jpa_version;                 /*乐观锁版本号  */    
    char            product_cd[6+1];             /*产品编号      */
    char            bal_id[20+1];                 /*顺序号 fuwd22392 Modify   */    
    char            bank_no[10+1];               /*银行代码      */
    char            bank_group_id[5+1];          /*银团代码      */
    char            is_check_flag[1+1];          /*              */
    char            extend_param1[100+1];        /*              */
    char            extend_param2[250+1];        /*              */
    char            extend_param3[40+1];         /*              */
    
}ICPS_WBC_TM_GL_BAL;

#define SD_DATA  ICPS_WBC_TM_GL_BAL
#define SD_MEMBERS \ 
   APP_DEFSDMEMBER(T_STRING,  busi_date        ,0),\
   APP_DEFSDMEMBER(T_LONG,    file_order       ,0),\
   APP_DEFSDMEMBER(T_STRING,  org              ,0),\
   APP_DEFSDMEMBER(T_STRING,  subject          ,0),\
   APP_DEFSDMEMBER(T_STRING,  branch_id        ,0),\
   APP_DEFSDMEMBER(T_DOUBLE,  db_bal           ,2),\
   APP_DEFSDMEMBER(T_DOUBLE,  cr_bal           ,2),\
   APP_DEFSDMEMBER(T_DOUBLE,  db_amt           ,2),\
   APP_DEFSDMEMBER(T_LONG,    db_count         ,0),\
   APP_DEFSDMEMBER(T_DOUBLE,  cr_amt           ,2),\
   APP_DEFSDMEMBER(T_LONG,    cr_count         ,0),\
   APP_DEFSDMEMBER(T_DOUBLE,  last_db_bal      ,2),\
   APP_DEFSDMEMBER(T_DOUBLE,  last_cr_bal      ,2),\
   APP_DEFSDMEMBER(T_DOUBLE,  last_mth_db_bal  ,2),\
   APP_DEFSDMEMBER(T_DOUBLE,  last_mth_cr_bal  ,2),\
   APP_DEFSDMEMBER(T_DOUBLE,  last_qtr_db_bal  ,2),\
   APP_DEFSDMEMBER(T_DOUBLE,  last_qtr_cr_bal  ,2),\
   APP_DEFSDMEMBER(T_DOUBLE,  last_yr_db_bal   ,2),\
   APP_DEFSDMEMBER(T_DOUBLE,  last_yr_cr_bal   ,2),\
   APP_DEFSDMEMBER(T_LONG,    jpa_version      ,0),\
   APP_DEFSDMEMBER(T_STRING,  product_cd       ,0),\
   APP_DEFSDMEMBER(T_STRING,  bal_id           ,0),\
   APP_DEFSDMEMBER(T_STRING,  bank_no          ,0),\
   APP_DEFSDMEMBER(T_STRING,  bank_group_id    ,0),\
   APP_DEFSDMEMBER(T_STRING,  is_check_flag    ,0),\
   APP_DEFSDMEMBER(T_STRING,  extend_param1    ,0),\
   APP_DEFSDMEMBER(T_STRING,  extend_param2    ,0),\
   APP_DEFSDMEMBER(T_STRING,  extend_param3    ,0)
   APP_DECLAREFIELDS(SD_ICPS_WBC_TM_GL_BAL) 
   #undef SD_DATA                               
   #undef SD_MEMBERS                            
                                             
   #endif  /*end of __ICPS_WBC_TM_GL_BAL_H__*/
