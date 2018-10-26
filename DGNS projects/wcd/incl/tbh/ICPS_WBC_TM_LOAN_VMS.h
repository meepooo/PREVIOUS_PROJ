/*********************************************************************** 
 ��Ȩ����:�������ӹɷ����޹�˾                                            
 ��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ                                      
 ��    ��:V1.00                                                           
 ����ϵͳ:                                                                
 �� �� ��:db2                                                             
 �� �� ��:ICPS_WBC_TM_LOAN_VMS.h                                          
 �ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�                                     
 �� Ŀ ��:                                                                
 �� �� Ա:[fuwd22392]                                                     
 ����ʱ��:2018-06-12 10:00:00 [Gen]                                       
 ��    ��:                                                                
 �޸�ʱ��:                                                                
 ************************************************************************ 
 ��    ��:ICPS_WBC_TM_LOAN_VMS                                            
 ˵    ��:�����˰�ӹ���                                                                
 ************************************************************************ 
 �޸ļ�¼:                                                                
 �޸�����:                                                                
 �޸�����:                                                                
 �� �� ��:                                                                
 �޸�����:                                                                
 ************************************************************************/
 #ifndef __ICPS_WBC_TM_LOAN_VMS_H__                                       
 #define __ICPS_WBC_TM_LOAN_VMS_H__                                       
 typedef struct TDB_ICPS_WBC_TM_LOAN_VMS                                  
 {
  	char		busi_date[8+1];             
	int			file_order;
	char		id[20+1];
	char		org[12+1];               /* ��˰���ID                                         */
	char		card_no[19+1];            /* ������                                             */
	char		ref_nbr[23+1];            /* ���ʿ���                                           */
	char		bank_group_id[5+1];       /* ���ײο���                                         */
	char		bank_no[10+1];            /* ���ű��                                           */
	char		product_cd[6+1];          /* ���б��                                           */
	double		biz_tax_interest;         /* ��Ʒ��                                             */
	double		vat_int_bal;              /* Ӫҵ˰�µ�Ӧ�ƺ�Ӧ��Ϣ                             */
	double		norevoke_vat_int_bal;     /* 90���ڵ�Ӧ��˰Ϣ���                               */
	double		vat_tax;                  /* ������㷨��Ӧ��˰Ϣ����90����+90���⻹��ǲ��֣�*/
	int			loan_init_term;           /* ������ֵ˰                                         */
	char		last_modified_time[14+1]; /* ����������                                         */
	char		paid_out_date[8+1];       /* �ϴ��޸�ʱ��                                       */
	char		age_cd[1+1];              /* ��������                                           */
	char		batch_date[8+1];          /* ����                                               */
	int			jpa_version;              /* ��������                                           */
	char		is_check_flag[1+1];       /* �ֹ����汾��                                       */
	char		extend_param1[100+1];
	char		extend_param2[250+1];
	char		extend_param3[40+1];
                    
 }ICPS_WBC_TM_LOAN_VMS;
                                                                         
 #define SD_DATA  ICPS_WBC_TM_LOAN_VMS 
 #define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date             ,0),\
	APP_DEFSDMEMBER(T_LONG,    file_order            ,0),\
	APP_DEFSDMEMBER(T_STRING,  id                    ,0),\
	APP_DEFSDMEMBER(T_STRING,  org                   ,0),\
	APP_DEFSDMEMBER(T_STRING,  card_no               ,0),\
	APP_DEFSDMEMBER(T_STRING,  ref_nbr               ,0),\
	APP_DEFSDMEMBER(T_STRING,  bank_group_id         ,0),\
	APP_DEFSDMEMBER(T_STRING,  bank_no               ,0),\
	APP_DEFSDMEMBER(T_STRING,  product_cd            ,0),\
	APP_DEFSDMEMBER(T_DOUBLE,  biz_tax_interest      ,2),\
	APP_DEFSDMEMBER(T_DOUBLE,  vat_int_bal           ,2),\
	APP_DEFSDMEMBER(T_DOUBLE,  norevoke_vat_int_bal  ,2),\
	APP_DEFSDMEMBER(T_DOUBLE,  vat_tax               ,2),\
	APP_DEFSDMEMBER(T_LONG,    loan_init_term        ,0),\
	APP_DEFSDMEMBER(T_STRING,  last_modified_time    ,0),\
	APP_DEFSDMEMBER(T_STRING,  paid_out_date         ,0),\
	APP_DEFSDMEMBER(T_STRING,  age_cd                ,0),\
	APP_DEFSDMEMBER(T_STRING,  batch_date            ,0),\
	APP_DEFSDMEMBER(T_LONG,    jpa_version           ,0),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag         ,0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1         ,0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2         ,0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3         ,0)
	APP_DECLAREFIELDS(SD_ICPS_WBC_TM_LOAN_VMS)
 #undef SD_DATA                                                           
 #undef SD_MEMBERS                                                        
                                                                         
 #endif  /*end of _ICPS_WBC_TM_LOAN_VMS_H__*/                            
