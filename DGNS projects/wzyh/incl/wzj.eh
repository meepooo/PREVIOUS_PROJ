/**************************************************************
             微动力业务头文件
**************************************************************/
#ifndef __WDL_EH__
#define __WDL_EH__

/*微动力对账明细表*/
typedef struct {
    char          dzrq               [10+1];            /*对账日期*/
    char          file_name          [128+1];           /*对账文件名*/
    char          snd_organ          [14+1];            /*发起机构*/
    char          rev_organ          [14+1];            /*接收机构*/
    char          business_id        [32+1];            /*交易流水号*/
    char          transtime          [32+1];            /*交易时间*/
    char          business_type      [5+1];             /*业务种类*/
    char          acct_type          [5+1];             /*账户类型*/
    char          work_date          [10+1];            /*工作日期/清算日期*/
    char          scene_no           [5+1];             /*业务场次号*/
    double        amount;                               /*交易金额*/
    char          ccy                [5+1];             /*交易货币*/
    double        fee_amount;                           /*交易手续费*/
    char          payer_opbk         [14+1];            /*转出方机构号*/
    char          payer_acct         [34+1];            /*转出方账号*/
    char          payer_name         [140+1];           /*转出方姓名*/
    char          payee_opbk         [14+1];            /*转入方机构号*/
    char          payee_acct         [34+1];            /*转入方账号*/
    char          payee_name         [140+1];           /*转入方姓名*/
    char          tran_type          [4+1];             /*交易类型(01-单笔转入02-单笔转出)*/
    char          deal_flag          [4+1];             /*处理结果(S:失败,F:成功)*/
    char          cz_flag            [4+1];             /*冲正标志(0:交易未冲正,1:交易冲正)*/
    char          cz_business_id     [32+1];            /*冲正流水号*/
    char          dz_flag            [4+1];             /*对账标志(0-初始,1-已对平)*/
    char          beiy1              [16+1];            /*备注1*/
    char          beiy2              [32+1];            /*备注2*/
    char          beiy3              [32+1];            /*备注3*/
    char          beiy4              [64+1];            /*备注4*/
    char          beiy5              [128+1];           /*备注5*/
}SDB_YW_WZYH_DZMX;

#define SD_DATA SDB_YW_WZYH_DZMX
#define	SD_MEMBERS \
	DEFSDMEMBER(T_STRING,dzrq,0),\
	DEFSDMEMBER(T_STRING,file_name,0),\
	DEFSDMEMBER(T_STRING,snd_organ,0),\
	DEFSDMEMBER(T_STRING,rev_organ,0),\
	DEFSDMEMBER(T_STRING,business_id,0),\
	DEFSDMEMBER(T_STRING,transtime,0),\
	DEFSDMEMBER(T_STRING,business_type,0),\
	DEFSDMEMBER(T_STRING,acct_type,0),\
	DEFSDMEMBER(T_STRING,work_date,0),\
	DEFSDMEMBER(T_STRING,scene_no,0),\
	DEFSDMEMBER(T_DOUBLE,amount,2),\
	DEFSDMEMBER(T_STRING,ccy,0),\
	DEFSDMEMBER(T_DOUBLE,fee_amount,2),\
	DEFSDMEMBER(T_STRING,payer_opbk,0),\
	DEFSDMEMBER(T_STRING,payer_acct,0),\
	DEFSDMEMBER(T_STRING,payer_name,0),\
	DEFSDMEMBER(T_STRING,payee_opbk,0),\
	DEFSDMEMBER(T_STRING,payee_acct,0),\
	DEFSDMEMBER(T_STRING,payee_name,0),\
	DEFSDMEMBER(T_STRING,tran_type,0),\
	DEFSDMEMBER(T_STRING,deal_flag,0),\
	DEFSDMEMBER(T_STRING,cz_flag,0),\
	DEFSDMEMBER(T_STRING,cz_business_id,0),\
	DEFSDMEMBER(T_STRING,dz_flag,0),\
	DEFSDMEMBER(T_STRING,beiy1,0),\
	DEFSDMEMBER(T_STRING,beiy2,0),\
	DEFSDMEMBER(T_STRING,beiy3,0),\
	DEFSDMEMBER(T_STRING,beiy4,0),\
	DEFSDMEMBER(T_STRING,beiy5,0)

	DECLAREFIELDS(SD_YW_WZYH_DZMX)
#undef SD_DATA
#undef SD_MEMBERS

/*微动力核心对账数据明细表*/
typedef struct {
    char qshh[12+1];                  /* 清算行号 */
    char qsrq[8+1];                   /* 清算日期 */
    char qslsh[32+1];                 /* 前置流水 */
    char jydm[10+1];                  /* 交易代码*/
    char jfyhzh[40+1];                /* 借方银行账号 */
	char jfhm[40+1];				  /* 借方户名 */
	char dfyhzh[40+1];                /* 货方银行账号 */
	char dfhm[40+1];				  /* 贷方户名 */
    double jyje;                      /* 交易金额 */
    char hxdate[8+1];                 /* 核心账务日期 */
    char hxnum[40+1];                 /* 核心流水号 */
    char orgno[16+1];                 /* 受理网点或开户网点 */
    double sxf;                       /* 本行手续费 */
    char sysdt[8+1];                  /* 记录插入日期 */
    char systm[6+1];                  /* 记录插入时间 */
    char dzflag[1+1];                 /* 是否已对账标志：0初始，1：已对账  2不参与对账的流水*/
    char ywlx[8+1];                   /* 业务类型 */
	char busstype[4+1];				  /* 业务代码 */
	char subbusstype[4+1];			  /* 子业务代码：0001-产品申购 0002-产品赎回 0003-手续费扣款  0004-手续费还款 */
    char beiy1[16+1];                 /* 备用字段 */
    char beiy2[32+1];                 /* 备用字段 */
    char beiy3[32+1];                 /* 备用字段 */
    char beiy4[64+1];                 /* 备用字段 */
    char beiy5[128+1];                /* 备用字段 */
}SDB_YW_WZYH_COREMX;

#define SD_DATA SDB_YW_WZYH_COREMX
#define	SD_MEMBERS \
	DEFSDMEMBER(T_STRING,qshh,0),\
	DEFSDMEMBER(T_STRING,qsrq,0),\
	DEFSDMEMBER(T_STRING,qslsh,0),\
	DEFSDMEMBER(T_STRING,jydm,0),\
	DEFSDMEMBER(T_STRING,jfyhzh,0),\
	DEFSDMEMBER(T_STRING,jfhm,0),\
	DEFSDMEMBER(T_STRING,dfyhzh,0),\
	DEFSDMEMBER(T_STRING,dfhm,0),\
	DEFSDMEMBER(T_DOUBLE,jyje,2),\
	DEFSDMEMBER(T_STRING,hxdate,0),\
	DEFSDMEMBER(T_STRING,hxnum,0),\
	DEFSDMEMBER(T_STRING,orgno,0),\
	DEFSDMEMBER(T_DOUBLE,sxf,2),\
	DEFSDMEMBER(T_STRING,sysdt,0),\
	DEFSDMEMBER(T_STRING,systm,0),\
	DEFSDMEMBER(T_STRING,dzflag,0),\
	DEFSDMEMBER(T_STRING,ywlx,0),\
	DEFSDMEMBER(T_STRING,busstype,0),\
	DEFSDMEMBER(T_STRING,subbusstype,0),\
	DEFSDMEMBER(T_STRING,beiy1,0),\
	DEFSDMEMBER(T_STRING,beiy2,0),\
	DEFSDMEMBER(T_STRING,beiy3,0),\
	DEFSDMEMBER(T_STRING,beiy4,0),\
	DEFSDMEMBER(T_STRING,beiy5,0)
	
	DECLAREFIELDS(SD_YW_WZYH_COREMX)
#undef SD_DATA
#undef SD_MEMBERS


/*微动力核心对账数据差错明细表*/
typedef struct {
    char jyrq[10+1];                         /* 交易日期 */
    char business_id[32+1];                  /* 交易流水号 */
    char accno[34+1];                        /* 主账号 */
    char accname[140+1];                     /* 主账号姓名 */
    char flag[2+1];                          /* 来往帐标识0-往账1-来账 */    
    char qzrq[10+1];                         /* 前置日期 */
    char qzls[20+1];                         /* 前置流水 */
    char hxrq[10+1];                         /* 核心日期 */
    char hxls[32+1];                         /* 核心流水 */
    char hxxym[20+1];                        /* 核心响应码 */
    char hxrespmsg[256+1];                   /* 核心响应信息 */
    char waiblius[32+1];                     /* 外部流水 */
    char errflag[2+1];                        /* 1-核心多,微众少2-核心少,微众多 */
    char errmsg[100+1];                      /* 差错信息 */
    char tzbz[2+1];                          /* 调账标志(0-初始 1-已调账) */
    char transtime[32+1];                    /* 交易时间 */
    char snd_organ[14+1];                    /* 发起机构 */
    char rev_organ[14+1];                    /* 接收机构 */
    char tran_name[32+1];                    /* 报文类型 */
    char tran_type[4+1];                     /* 交易类型(01-单笔转入02-单笔转出) */
    char msg_version[4+1];                   /* 版本号 */
    char pay_product_code[4+1];              /* 业务种类 */
    char acct_type[4+1];                     /* 银行卡/折类型(1-借记卡2-存折3-信用卡) */      
    char payee_name[140+1];                  /* 转入方姓名*/ 
    char payee_acct[34+1];                   /* 转入方账号*/ 
    char payee_opbk[14+1];                   /* 转入方机构号*/ 
    char payer_name[140+1];                  /* 转出方姓名*/ 
    char payer_acct[34+1];                   /* 转出方账号*/ 
    char payer_opbk[14+1];                   /* 转出方机构号*/ 
    double  amount;                          /* 交易金额*/ 
    double  coreamount;                      /*核心交易金额*/
    double  fee_amount;                      /* 交易手续费*/ 
    char ccy[5+1];                           /* 交易货币*/  
    char cardChinaInfo[256+1];               /* 卡磁道相关信息*/ 
    char cvv[256+1];                         /* cvv(信用卡必输)*/ 
    char validDate[10+1];                    /* 有效期(信用卡必输)*/ 
    char route[5+1];                         /* 路由*/ 
    char work_date[10+1];                    /* 工作日期/清算日期*/ 
    char scene_no[5+1];                      /* 业务场次号*/ 
    char orijyrq[10+1];                      /* 原交易日期*/  
    char oribusiness_id[32+1];               /* 原交易流水号*/ 
    char oritran_type[4+1];                  /* 原交易类型(01-单笔转入02-单笔转出)*/ 
    double oriamount;                        /* 原交易金额*/ 
    char oriccy[5+1];                        /* 原交易货币*/  
    char reason[256+1];                      /* 冲正原因*/  
    char czflag[4+1];                        /* 冲正标志(0-初始1-已冲正2-不能被冲正)*/
	char busstype[4+1];						 /* 业务代码 */
	char subbusstype[4+1];					 /* 子业务代码：0001-产品申购 0002-产品赎回 0003-手续费扣款  0004-手续费还款 */
	char lsbz[2+1];							 /* 流水标志 1-无流水 */
    char abstr[512+1];                       /* 摘要*/  
    char remark[256+1];                      /* 消息扩展*/  
    char beiy1[16+1];                        /*备注1*/
    char beiy2[32+1];                        /*备注2*/
    char beiy3[32+1];                        /*备注3*/
    char beiy4[64+1];                        /*备注4*/
    char beiy5[128+1];                       /*备注5*/ 
}SDB_YW_WZYH_ERRMX;

#define SD_DATA SDB_YW_WZYH_ERRMX
#define	SD_MEMBERS \
	DEFSDMEMBER(T_STRING,jyrq,0),\
	DEFSDMEMBER(T_STRING,business_id,0),\
	DEFSDMEMBER(T_STRING,accno,0),\
	DEFSDMEMBER(T_STRING,accname,0),\
	DEFSDMEMBER(T_STRING,flag,0),\
	DEFSDMEMBER(T_STRING,qzrq,0),\
	DEFSDMEMBER(T_STRING,qzls,0),\
	DEFSDMEMBER(T_STRING,hxrq,0),\
	DEFSDMEMBER(T_STRING,hxls,0),\
	DEFSDMEMBER(T_STRING,hxxym,0),\
	DEFSDMEMBER(T_STRING,hxrespmsg,0),\
	DEFSDMEMBER(T_STRING,waiblius,0),\
	DEFSDMEMBER(T_STRING,errflag,0),\
	DEFSDMEMBER(T_STRING,errmsg,0),\
	DEFSDMEMBER(T_STRING,tzbz,0),\
	DEFSDMEMBER(T_STRING,transtime,0),\
	DEFSDMEMBER(T_STRING,snd_organ,0),\
	DEFSDMEMBER(T_STRING,rev_organ,0),\
	DEFSDMEMBER(T_STRING,tran_name,0),\
	DEFSDMEMBER(T_STRING,tran_type,0),\
	DEFSDMEMBER(T_STRING,msg_version,0),\
	DEFSDMEMBER(T_STRING,pay_product_code,0),\
	DEFSDMEMBER(T_STRING,acct_type,0),\
	DEFSDMEMBER(T_STRING,payee_name,0),\
	DEFSDMEMBER(T_STRING,payee_acct,0),\
	DEFSDMEMBER(T_STRING,payee_opbk,0),\
	DEFSDMEMBER(T_STRING,payer_name,0),\
	DEFSDMEMBER(T_STRING,payer_acct,0),\
	DEFSDMEMBER(T_STRING,payer_opbk,0),\
	DEFSDMEMBER(T_DOUBLE,amount,2),\
	DEFSDMEMBER(T_DOUBLE,coreamount,2),\
	DEFSDMEMBER(T_DOUBLE,fee_amount,2),\
	DEFSDMEMBER(T_STRING,ccy,0),\
	DEFSDMEMBER(T_STRING,cardChinaInfo,0),\
	DEFSDMEMBER(T_STRING,cvv,0),\
	DEFSDMEMBER(T_STRING,validDate,0),\
	DEFSDMEMBER(T_STRING,route,0),\
	DEFSDMEMBER(T_STRING,work_date,0),\
	DEFSDMEMBER(T_STRING,scene_no,0),\
	DEFSDMEMBER(T_STRING,orijyrq,0),\
	DEFSDMEMBER(T_STRING,oribusiness_id,0),\
	DEFSDMEMBER(T_STRING,oritran_type,0),\
	DEFSDMEMBER(T_DOUBLE,oriamount,2),\
	DEFSDMEMBER(T_STRING,oriccy,0),\
	DEFSDMEMBER(T_STRING,reason,0),\
	DEFSDMEMBER(T_STRING,czflag,0),\
	DEFSDMEMBER(T_STRING,busstype,0),\
	DEFSDMEMBER(T_STRING,subbusstype,0),\
	DEFSDMEMBER(T_STRING,lsbz,0),\
	DEFSDMEMBER(T_STRING,abstr,0),\
	DEFSDMEMBER(T_STRING,remark,0),\
	DEFSDMEMBER(T_STRING,beiy1,0),\
	DEFSDMEMBER(T_STRING,beiy2,0),\
	DEFSDMEMBER(T_STRING,beiy3,0),\
	DEFSDMEMBER(T_STRING,beiy4,0),\
	DEFSDMEMBER(T_STRING,beiy5,0)
	
	DECLAREFIELDS(SD_YW_WZYH_ERRMX)
#undef SD_DATA
#undef SD_MEMBERS


/*微动力交易流水表*/
typedef struct {
    char jyrq[10+1];                         /* 交易日期 */
    char business_id[32+1];                  /* 交易流水号 */
    char flag[2+1];                          /* 来往帐标识0-往账1-来账 */    
    char req_date[10+1];                     /* 微众请求日期 */
    char transtime[32+1];                    /* 交易时间 */
    char snd_organ[14+1];                    /* 发起机构 */
    char rev_organ[14+1];                    /* 接收机构 */
    char tran_name[32+1];                    /* 报文类型 */
    char tran_type[4+1];                     /* 交易类型(01-单笔转入02-单笔转出) */
    char msg_version[4+1];                   /* 版本号*/
    char pay_product_code[4+1];              /* 业务种类*/  
	char qdbs[20+1];						 /* 渠道标识 */
    char acct_type[4+1];                     /* 银行卡/折类型(1-借记卡2-存折3-信用卡)*/      
    char payee_name[140+1];                  /* 转入方姓名*/ 
    char payee_acct[34+1];                   /* 转入方账号*/ 
    char payee_opbk[14+1];                   /* 转入方机构号*/ 
    char payer_name[140+1];                  /* 转出方姓名*/ 
    char payer_acct[34+1];                   /* 转出方账号*/ 
    char payer_opbk[14+1];                   /* 转出方机构号*/ 
    double  amount;                          /* 交易金额*/ 
	double  deal_grammage;					 /* 交易克数 */
    double  fee_amount;                      /* 交易手续费*/ 
    char ccy[5+1];                           /* 交易货币*/  
    char cardChinaInfo[256+1];               /* 卡磁道相关信息*/ 
    char cvv[256+1];                         /* cvv(信用卡必输)*/ 
    char validDate[10+1];                    /* 有效期(信用卡必输)*/ 
    char route[5+1];                         /* 路由*/ 
    char work_date[10+1];                    /* 工作日期/清算日期*/ 
    char scene_no[5+1];                      /* 业务场次号*/ 
    char orijyrq[10+1];                      /* 原交易日期*/  
    char oribusiness_id[32+1];               /* 原交易流水号*/ 
    char oritran_type[4+1];                  /* 原交易类型(01-单笔转入02-单笔转出)*/ 
    double oriamount;                        /* 原交易金额*/ 
    char oriccy[5+1];                        /* 原交易货币*/  
    char reason[256+1];                      /* 冲正原因*/  
    char czflag[4+1];                        /* 冲正标志(0-初始1-已冲正2-不能被冲正)*/ 
    char czxym[20+1];                        /* 冲正核心响应码*/  
    char cxrespmsg[256+1];                   /* 冲正核心响应信息*/  
    char cxwaiblius[32+1];                   /* 冲正核心外部流水*/     
    char qzrq[10+1];                         /* 前置日期 */
    char qzls[20+1];                         /* 前置流水 */
    char hxrq[10+1];                         /* 核心日期 */
    char hxls[32+1];                         /* 核心流水 */
    char hxxym[20+1];                        /* 核心响应码 */
    char hxrespmsg[256+1];                   /* 核心响应信息 */
    char waiblius[32+1];                     /* 外部流水 */
    char hxdzbz[2+1];                        /* 与核心对账标志(0-初始1-对平2-主机无平台有3-平台无主机有4-金额不符) */
    char pay_tran_status[10+1];              /* 订单状态 */    
    char pay_ret_status_msg[256+1];          /* 原订单结果描述 */
	char tzzt[2+1];							 /* 调账状态 */
    char abstr[512+1];                       /* 摘要*/  
    char remark[256+1];                      /* 消息扩展*/  
    char beiy1[16+1];                        /*备注1*/
    char beiy2[32+1];                        /*备注2*/
    char beiy3[32+1];                        /*备注3*/
    char beiy4[64+1];                        /*备注4*/
    char beiy5[128+1];                       /*备注5*/ 
}SDB_YW_WZYH_YWLS;

#define SD_DATA SDB_YW_WZYH_YWLS
#define	SD_MEMBERS \
	DEFSDMEMBER(T_STRING,jyrq,0),\
	DEFSDMEMBER(T_STRING,business_id,0),\
	DEFSDMEMBER(T_STRING,flag,0),\
	DEFSDMEMBER(T_STRING,req_date,0),\
	DEFSDMEMBER(T_STRING,transtime,0),\
	DEFSDMEMBER(T_STRING,snd_organ,0),\
	DEFSDMEMBER(T_STRING,rev_organ,0),\
	DEFSDMEMBER(T_STRING,tran_name,0),\
	DEFSDMEMBER(T_STRING,tran_type,0),\
	DEFSDMEMBER(T_STRING,msg_version,0),\
	DEFSDMEMBER(T_STRING,pay_product_code,0),\
	DEFSDMEMBER(T_STRING,qdbs,0),\
	DEFSDMEMBER(T_STRING,acct_type,0),\
	DEFSDMEMBER(T_STRING,payee_name,0),\
	DEFSDMEMBER(T_STRING,payee_acct,0),\
	DEFSDMEMBER(T_STRING,payee_opbk,0),\
	DEFSDMEMBER(T_STRING,payer_name,0),\
	DEFSDMEMBER(T_STRING,payer_acct,0),\
	DEFSDMEMBER(T_STRING,payer_opbk,0),\
	DEFSDMEMBER(T_DOUBLE,amount,2),\
	DEFSDMEMBER(T_DOUBLE,deal_grammage,2),\
	DEFSDMEMBER(T_DOUBLE,fee_amount,2),\
	DEFSDMEMBER(T_STRING,ccy,0),\
	DEFSDMEMBER(T_STRING,cardChinaInfo,0),\
	DEFSDMEMBER(T_STRING,cvv,0),\
	DEFSDMEMBER(T_STRING,validDate,0),\
	DEFSDMEMBER(T_STRING,route,0),\
	DEFSDMEMBER(T_STRING,work_date,0),\
	DEFSDMEMBER(T_STRING,scene_no,0),\
	DEFSDMEMBER(T_STRING,orijyrq,0),\
	DEFSDMEMBER(T_STRING,oribusiness_id,0),\
	DEFSDMEMBER(T_STRING,oritran_type,0),\
	DEFSDMEMBER(T_DOUBLE,oriamount,2),\
	DEFSDMEMBER(T_STRING,oriccy,0),\
	DEFSDMEMBER(T_STRING,reason,0),\
	DEFSDMEMBER(T_STRING,czflag,0),\
	DEFSDMEMBER(T_STRING,czxym,0),\
	DEFSDMEMBER(T_STRING,cxrespmsg,0),\
	DEFSDMEMBER(T_STRING,cxwaiblius,0),\
	DEFSDMEMBER(T_STRING,qzrq,0),\
	DEFSDMEMBER(T_STRING,qzls,0),\
	DEFSDMEMBER(T_STRING,hxrq,0),\
	DEFSDMEMBER(T_STRING,hxls,0),\
	DEFSDMEMBER(T_STRING,hxxym,0),\
	DEFSDMEMBER(T_STRING,hxrespmsg,0),\
	DEFSDMEMBER(T_STRING,waiblius,0),\
	DEFSDMEMBER(T_STRING,hxdzbz,0),\
	DEFSDMEMBER(T_STRING,pay_tran_status,0),\
	DEFSDMEMBER(T_STRING,tzzt,0),\
	DEFSDMEMBER(T_STRING,abstr,0),\
	DEFSDMEMBER(T_STRING,remark,0),\
	DEFSDMEMBER(T_STRING,beiy1,0),\
	DEFSDMEMBER(T_STRING,beiy2,0),\
	DEFSDMEMBER(T_STRING,beiy3,0),\
	DEFSDMEMBER(T_STRING,beiy4,0),\
	DEFSDMEMBER(T_STRING,beiy5,0)

	DECLAREFIELDS(SD_YW_WZYH_YWLS)
#undef SD_DATA
#undef SD_MEMBERS


/*微动力对账结果表*/
typedef struct {
    char qsjg[14+1];                         /* 清算机构 */
    char qsrq[10+1];                         /* 交易日期 */
    char product_buy_num[12+1];              /* 理财产品申购总笔数---只统计对账平的 */    
    double product_buy_amount;               /* 申购资金总额------只统计对账平的 */
    char product_back_num[12+1];             /* 理财产品赎回总笔数---只统计对账平的 */
    double product_back_amount;              /* 赎回资金总额---只统计对账平的 */
    double zc_amount;                        /* 轧差总额 */
    char dz_bz[2+1];                         /* 1-成功 2---失败 */
    char dzmsg[200+1];                       /* 对账结果 */
    char beiy1[16+1];                        /*备注1*/
    char beiy2[32+1];                        /*备注2*/
    char beiy3[32+1];                        /*备注3*/
    char beiy4[64+1];                        /*备注4*/
    char beiy5[128+1];                       /*备注5*/     
}SDB_YW_WZYH_DZJG;

#define SD_DATA SDB_YW_WZYH_DZJG
#define	SD_MEMBERS \
	DEFSDMEMBER(T_STRING,qsjg,0),\
	DEFSDMEMBER(T_STRING,qsrq,0),\
	DEFSDMEMBER(T_STRING,product_buy_num,0),\
	DEFSDMEMBER(T_DOUBLE,product_buy_amount,2),\
	DEFSDMEMBER(T_STRING,product_back_num,0),\
	DEFSDMEMBER(T_DOUBLE,product_back_amount,2),\
	DEFSDMEMBER(T_DOUBLE,zc_amount,2),\
	DEFSDMEMBER(T_STRING,dz_bz,0),\
	DEFSDMEMBER(T_STRING,dzmsg,0),\
	DEFSDMEMBER(T_STRING,beiy1,0),\
	DEFSDMEMBER(T_STRING,beiy2,0),\
	DEFSDMEMBER(T_STRING,beiy3,0),\
	DEFSDMEMBER(T_STRING,beiy4,0),\
	DEFSDMEMBER(T_STRING,beiy5,0)
	
	DECLAREFIELDS(SD_YW_WZYH_DZJG)
#undef SD_DATA
#undef SD_MEMBERS

/*微动力理财明细表*/
typedef struct {
    char wjrq[10+1];                         /* 文件日期 */
    char file_name[128+1];                   /* 理财文件名 */
    char yw_business[32+1];                  /* 业务流水号 */
    char business_id[32+1];                  /* 交易流水号 */
    char oribusiness_id[32+1];               /* 原交易流水号 */
    char jyrq[10+1];                         /* 交易日期 */
    char transtime[32+1];                    /* 交易时间 */
    char business_type[5+1];                 /* 交易类型 */
    double amount;                           /* 交易金额 */
    double jy_num;                           /* 交易份额 */
    char cust_name[140+1];                   /* 客户姓名 */
    char cert_type[5+1];                     /* 证件类型 */
    char cert_id[32+1];                      /* 证件号码 */
    char product_id[32+1];                   /* 产品编码 */
    char product_name[1284+1];               /* 产品名称 */
    char status[5+1];                        /* 交易状态 */
    char beiy1[16+1];                        /*备注1*/
    char beiy2[32+1];                        /*备注2*/
    char beiy3[32+1];                        /*备注3*/
    char beiy4[64+1];                        /*备注4*/
    char beiy5[128+1];                       /*备注5*/     
}SDB_YW_WZYH_LCMX;

#define SD_DATA SDB_YW_WZYH_LCMX
#define	SD_MEMBERS \
	DEFSDMEMBER(T_STRING,wjrq,0),\
	DEFSDMEMBER(T_STRING,file_name,0),\
	DEFSDMEMBER(T_STRING,yw_business,0),\
	DEFSDMEMBER(T_STRING,business_id,0),\
	DEFSDMEMBER(T_STRING,oribusiness_id,0),\
	DEFSDMEMBER(T_STRING,jyrq,0),\
	DEFSDMEMBER(T_STRING,transtime,0),\
	DEFSDMEMBER(T_STRING,business_type,0),\
	DEFSDMEMBER(T_DOUBLE,amount,2),\
	DEFSDMEMBER(T_DOUBLE,jy_num,2),\
	DEFSDMEMBER(T_STRING,cust_name,0),\
	DEFSDMEMBER(T_STRING,cert_type,0),\
	DEFSDMEMBER(T_STRING,cert_id,0),\
	DEFSDMEMBER(T_STRING,product_id,0),\
	DEFSDMEMBER(T_STRING,product_name,0),\
	DEFSDMEMBER(T_STRING,status,0),\
	DEFSDMEMBER(T_STRING,beiy1,0),\
	DEFSDMEMBER(T_STRING,beiy2,0),\
	DEFSDMEMBER(T_STRING,beiy3,0),\
	DEFSDMEMBER(T_STRING,beiy4,0),\
	DEFSDMEMBER(T_STRING,beiy5,0)

	DECLAREFIELDS(SD_YW_WZYH_LCMX)
#undef SD_DATA
#undef SD_MEMBERS

/*微动力保有量明细表*/
typedef struct {
    char wjrq[10+1];                         /* 文件日期 */
    char file_name[128+1];                   /* 保有量文件名 */
    char tjrq[10+1];                         /* 统计日期 */
    char product_id[32+1];                   /* 产品代码 */
    double product_amount;                   /* 产品总份额 */
    double product_net_amount;               /* 产品净值 */
    char beiy1[16+1];                        /*备注1*/
    char beiy2[32+1];                        /*备注2*/
    char beiy3[32+1];                        /*备注3*/
    char beiy4[64+1];                        /*备注4*/
    char beiy5[128+1];                       /*备注5*/    
}SDB_YW_WZYH_BYLMX;

#define SD_DATA SDB_YW_WZYH_BYLMX
#define	SD_MEMBERS \
	DEFSDMEMBER(T_STRING,wjrq,0),\
	DEFSDMEMBER(T_STRING,file_name,0),\
	DEFSDMEMBER(T_STRING,tjrq,0),\
	DEFSDMEMBER(T_STRING,product_id,0),\
	DEFSDMEMBER(T_DOUBLE,product_amount,2),\
	DEFSDMEMBER(T_DOUBLE,product_net_amount,2),\
	DEFSDMEMBER(T_STRING,beiy1,0),\
	DEFSDMEMBER(T_STRING,beiy2,0),\
	DEFSDMEMBER(T_STRING,beiy3,0),\
	DEFSDMEMBER(T_STRING,beiy4,0),\
	DEFSDMEMBER(T_STRING,beiy5,0)	
	
	DECLAREFIELDS(SD_YW_WZYH_BYLMX)
#undef SD_DATA
#undef SD_MEMBERS


#define MAXPAGECOUNT 999 //每页最大笔数

#endif  /* __WDL_EH__ */


/* the end */
