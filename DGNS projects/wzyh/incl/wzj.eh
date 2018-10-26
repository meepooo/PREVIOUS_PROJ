/**************************************************************
             ΢����ҵ��ͷ�ļ�
**************************************************************/
#ifndef __WDL_EH__
#define __WDL_EH__

/*΢����������ϸ��*/
typedef struct {
    char          dzrq               [10+1];            /*��������*/
    char          file_name          [128+1];           /*�����ļ���*/
    char          snd_organ          [14+1];            /*�������*/
    char          rev_organ          [14+1];            /*���ջ���*/
    char          business_id        [32+1];            /*������ˮ��*/
    char          transtime          [32+1];            /*����ʱ��*/
    char          business_type      [5+1];             /*ҵ������*/
    char          acct_type          [5+1];             /*�˻�����*/
    char          work_date          [10+1];            /*��������/��������*/
    char          scene_no           [5+1];             /*ҵ�񳡴κ�*/
    double        amount;                               /*���׽��*/
    char          ccy                [5+1];             /*���׻���*/
    double        fee_amount;                           /*����������*/
    char          payer_opbk         [14+1];            /*ת����������*/
    char          payer_acct         [34+1];            /*ת�����˺�*/
    char          payer_name         [140+1];           /*ת��������*/
    char          payee_opbk         [14+1];            /*ת�뷽������*/
    char          payee_acct         [34+1];            /*ת�뷽�˺�*/
    char          payee_name         [140+1];           /*ת�뷽����*/
    char          tran_type          [4+1];             /*��������(01-����ת��02-����ת��)*/
    char          deal_flag          [4+1];             /*������(S:ʧ��,F:�ɹ�)*/
    char          cz_flag            [4+1];             /*������־(0:����δ����,1:���׳���)*/
    char          cz_business_id     [32+1];            /*������ˮ��*/
    char          dz_flag            [4+1];             /*���˱�־(0-��ʼ,1-�Ѷ�ƽ)*/
    char          beiy1              [16+1];            /*��ע1*/
    char          beiy2              [32+1];            /*��ע2*/
    char          beiy3              [32+1];            /*��ע3*/
    char          beiy4              [64+1];            /*��ע4*/
    char          beiy5              [128+1];           /*��ע5*/
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

/*΢�������Ķ���������ϸ��*/
typedef struct {
    char qshh[12+1];                  /* �����к� */
    char qsrq[8+1];                   /* �������� */
    char qslsh[32+1];                 /* ǰ����ˮ */
    char jydm[10+1];                  /* ���״���*/
    char jfyhzh[40+1];                /* �跽�����˺� */
	char jfhm[40+1];				  /* �跽���� */
	char dfyhzh[40+1];                /* ���������˺� */
	char dfhm[40+1];				  /* �������� */
    double jyje;                      /* ���׽�� */
    char hxdate[8+1];                 /* ������������ */
    char hxnum[40+1];                 /* ������ˮ�� */
    char orgno[16+1];                 /* ��������򿪻����� */
    double sxf;                       /* ���������� */
    char sysdt[8+1];                  /* ��¼�������� */
    char systm[6+1];                  /* ��¼����ʱ�� */
    char dzflag[1+1];                 /* �Ƿ��Ѷ��˱�־��0��ʼ��1���Ѷ���  2��������˵���ˮ*/
    char ywlx[8+1];                   /* ҵ������ */
	char busstype[4+1];				  /* ҵ����� */
	char subbusstype[4+1];			  /* ��ҵ����룺0001-��Ʒ�깺 0002-��Ʒ��� 0003-�����ѿۿ�  0004-�����ѻ��� */
    char beiy1[16+1];                 /* �����ֶ� */
    char beiy2[32+1];                 /* �����ֶ� */
    char beiy3[32+1];                 /* �����ֶ� */
    char beiy4[64+1];                 /* �����ֶ� */
    char beiy5[128+1];                /* �����ֶ� */
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


/*΢�������Ķ������ݲ����ϸ��*/
typedef struct {
    char jyrq[10+1];                         /* �������� */
    char business_id[32+1];                  /* ������ˮ�� */
    char accno[34+1];                        /* ���˺� */
    char accname[140+1];                     /* ���˺����� */
    char flag[2+1];                          /* �����ʱ�ʶ0-����1-���� */    
    char qzrq[10+1];                         /* ǰ������ */
    char qzls[20+1];                         /* ǰ����ˮ */
    char hxrq[10+1];                         /* �������� */
    char hxls[32+1];                         /* ������ˮ */
    char hxxym[20+1];                        /* ������Ӧ�� */
    char hxrespmsg[256+1];                   /* ������Ӧ��Ϣ */
    char waiblius[32+1];                     /* �ⲿ��ˮ */
    char errflag[2+1];                        /* 1-���Ķ�,΢����2-������,΢�ڶ� */
    char errmsg[100+1];                      /* �����Ϣ */
    char tzbz[2+1];                          /* ���˱�־(0-��ʼ 1-�ѵ���) */
    char transtime[32+1];                    /* ����ʱ�� */
    char snd_organ[14+1];                    /* ������� */
    char rev_organ[14+1];                    /* ���ջ��� */
    char tran_name[32+1];                    /* �������� */
    char tran_type[4+1];                     /* ��������(01-����ת��02-����ת��) */
    char msg_version[4+1];                   /* �汾�� */
    char pay_product_code[4+1];              /* ҵ������ */
    char acct_type[4+1];                     /* ���п�/������(1-��ǿ�2-����3-���ÿ�) */      
    char payee_name[140+1];                  /* ת�뷽����*/ 
    char payee_acct[34+1];                   /* ת�뷽�˺�*/ 
    char payee_opbk[14+1];                   /* ת�뷽������*/ 
    char payer_name[140+1];                  /* ת��������*/ 
    char payer_acct[34+1];                   /* ת�����˺�*/ 
    char payer_opbk[14+1];                   /* ת����������*/ 
    double  amount;                          /* ���׽��*/ 
    double  coreamount;                      /*���Ľ��׽��*/
    double  fee_amount;                      /* ����������*/ 
    char ccy[5+1];                           /* ���׻���*/  
    char cardChinaInfo[256+1];               /* ���ŵ������Ϣ*/ 
    char cvv[256+1];                         /* cvv(���ÿ�����)*/ 
    char validDate[10+1];                    /* ��Ч��(���ÿ�����)*/ 
    char route[5+1];                         /* ·��*/ 
    char work_date[10+1];                    /* ��������/��������*/ 
    char scene_no[5+1];                      /* ҵ�񳡴κ�*/ 
    char orijyrq[10+1];                      /* ԭ��������*/  
    char oribusiness_id[32+1];               /* ԭ������ˮ��*/ 
    char oritran_type[4+1];                  /* ԭ��������(01-����ת��02-����ת��)*/ 
    double oriamount;                        /* ԭ���׽��*/ 
    char oriccy[5+1];                        /* ԭ���׻���*/  
    char reason[256+1];                      /* ����ԭ��*/  
    char czflag[4+1];                        /* ������־(0-��ʼ1-�ѳ���2-���ܱ�����)*/
	char busstype[4+1];						 /* ҵ����� */
	char subbusstype[4+1];					 /* ��ҵ����룺0001-��Ʒ�깺 0002-��Ʒ��� 0003-�����ѿۿ�  0004-�����ѻ��� */
	char lsbz[2+1];							 /* ��ˮ��־ 1-����ˮ */
    char abstr[512+1];                       /* ժҪ*/  
    char remark[256+1];                      /* ��Ϣ��չ*/  
    char beiy1[16+1];                        /*��ע1*/
    char beiy2[32+1];                        /*��ע2*/
    char beiy3[32+1];                        /*��ע3*/
    char beiy4[64+1];                        /*��ע4*/
    char beiy5[128+1];                       /*��ע5*/ 
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


/*΢����������ˮ��*/
typedef struct {
    char jyrq[10+1];                         /* �������� */
    char business_id[32+1];                  /* ������ˮ�� */
    char flag[2+1];                          /* �����ʱ�ʶ0-����1-���� */    
    char req_date[10+1];                     /* ΢���������� */
    char transtime[32+1];                    /* ����ʱ�� */
    char snd_organ[14+1];                    /* ������� */
    char rev_organ[14+1];                    /* ���ջ��� */
    char tran_name[32+1];                    /* �������� */
    char tran_type[4+1];                     /* ��������(01-����ת��02-����ת��) */
    char msg_version[4+1];                   /* �汾��*/
    char pay_product_code[4+1];              /* ҵ������*/  
	char qdbs[20+1];						 /* ������ʶ */
    char acct_type[4+1];                     /* ���п�/������(1-��ǿ�2-����3-���ÿ�)*/      
    char payee_name[140+1];                  /* ת�뷽����*/ 
    char payee_acct[34+1];                   /* ת�뷽�˺�*/ 
    char payee_opbk[14+1];                   /* ת�뷽������*/ 
    char payer_name[140+1];                  /* ת��������*/ 
    char payer_acct[34+1];                   /* ת�����˺�*/ 
    char payer_opbk[14+1];                   /* ת����������*/ 
    double  amount;                          /* ���׽��*/ 
	double  deal_grammage;					 /* ���׿��� */
    double  fee_amount;                      /* ����������*/ 
    char ccy[5+1];                           /* ���׻���*/  
    char cardChinaInfo[256+1];               /* ���ŵ������Ϣ*/ 
    char cvv[256+1];                         /* cvv(���ÿ�����)*/ 
    char validDate[10+1];                    /* ��Ч��(���ÿ�����)*/ 
    char route[5+1];                         /* ·��*/ 
    char work_date[10+1];                    /* ��������/��������*/ 
    char scene_no[5+1];                      /* ҵ�񳡴κ�*/ 
    char orijyrq[10+1];                      /* ԭ��������*/  
    char oribusiness_id[32+1];               /* ԭ������ˮ��*/ 
    char oritran_type[4+1];                  /* ԭ��������(01-����ת��02-����ת��)*/ 
    double oriamount;                        /* ԭ���׽��*/ 
    char oriccy[5+1];                        /* ԭ���׻���*/  
    char reason[256+1];                      /* ����ԭ��*/  
    char czflag[4+1];                        /* ������־(0-��ʼ1-�ѳ���2-���ܱ�����)*/ 
    char czxym[20+1];                        /* ����������Ӧ��*/  
    char cxrespmsg[256+1];                   /* ����������Ӧ��Ϣ*/  
    char cxwaiblius[32+1];                   /* ���������ⲿ��ˮ*/     
    char qzrq[10+1];                         /* ǰ������ */
    char qzls[20+1];                         /* ǰ����ˮ */
    char hxrq[10+1];                         /* �������� */
    char hxls[32+1];                         /* ������ˮ */
    char hxxym[20+1];                        /* ������Ӧ�� */
    char hxrespmsg[256+1];                   /* ������Ӧ��Ϣ */
    char waiblius[32+1];                     /* �ⲿ��ˮ */
    char hxdzbz[2+1];                        /* ����Ķ��˱�־(0-��ʼ1-��ƽ2-������ƽ̨��3-ƽ̨��������4-����) */
    char pay_tran_status[10+1];              /* ����״̬ */    
    char pay_ret_status_msg[256+1];          /* ԭ����������� */
	char tzzt[2+1];							 /* ����״̬ */
    char abstr[512+1];                       /* ժҪ*/  
    char remark[256+1];                      /* ��Ϣ��չ*/  
    char beiy1[16+1];                        /*��ע1*/
    char beiy2[32+1];                        /*��ע2*/
    char beiy3[32+1];                        /*��ע3*/
    char beiy4[64+1];                        /*��ע4*/
    char beiy5[128+1];                       /*��ע5*/ 
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


/*΢�������˽����*/
typedef struct {
    char qsjg[14+1];                         /* ������� */
    char qsrq[10+1];                         /* �������� */
    char product_buy_num[12+1];              /* ��Ʋ�Ʒ�깺�ܱ���---ֻͳ�ƶ���ƽ�� */    
    double product_buy_amount;               /* �깺�ʽ��ܶ�------ֻͳ�ƶ���ƽ�� */
    char product_back_num[12+1];             /* ��Ʋ�Ʒ����ܱ���---ֻͳ�ƶ���ƽ�� */
    double product_back_amount;              /* ����ʽ��ܶ�---ֻͳ�ƶ���ƽ�� */
    double zc_amount;                        /* �����ܶ� */
    char dz_bz[2+1];                         /* 1-�ɹ� 2---ʧ�� */
    char dzmsg[200+1];                       /* ���˽�� */
    char beiy1[16+1];                        /*��ע1*/
    char beiy2[32+1];                        /*��ע2*/
    char beiy3[32+1];                        /*��ע3*/
    char beiy4[64+1];                        /*��ע4*/
    char beiy5[128+1];                       /*��ע5*/     
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

/*΢���������ϸ��*/
typedef struct {
    char wjrq[10+1];                         /* �ļ����� */
    char file_name[128+1];                   /* ����ļ��� */
    char yw_business[32+1];                  /* ҵ����ˮ�� */
    char business_id[32+1];                  /* ������ˮ�� */
    char oribusiness_id[32+1];               /* ԭ������ˮ�� */
    char jyrq[10+1];                         /* �������� */
    char transtime[32+1];                    /* ����ʱ�� */
    char business_type[5+1];                 /* �������� */
    double amount;                           /* ���׽�� */
    double jy_num;                           /* ���׷ݶ� */
    char cust_name[140+1];                   /* �ͻ����� */
    char cert_type[5+1];                     /* ֤������ */
    char cert_id[32+1];                      /* ֤������ */
    char product_id[32+1];                   /* ��Ʒ���� */
    char product_name[1284+1];               /* ��Ʒ���� */
    char status[5+1];                        /* ����״̬ */
    char beiy1[16+1];                        /*��ע1*/
    char beiy2[32+1];                        /*��ע2*/
    char beiy3[32+1];                        /*��ע3*/
    char beiy4[64+1];                        /*��ע4*/
    char beiy5[128+1];                       /*��ע5*/     
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

/*΢������������ϸ��*/
typedef struct {
    char wjrq[10+1];                         /* �ļ����� */
    char file_name[128+1];                   /* �������ļ��� */
    char tjrq[10+1];                         /* ͳ������ */
    char product_id[32+1];                   /* ��Ʒ���� */
    double product_amount;                   /* ��Ʒ�ܷݶ� */
    double product_net_amount;               /* ��Ʒ��ֵ */
    char beiy1[16+1];                        /*��ע1*/
    char beiy2[32+1];                        /*��ע2*/
    char beiy3[32+1];                        /*��ע3*/
    char beiy4[64+1];                        /*��ע4*/
    char beiy5[128+1];                       /*��ע5*/    
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


#define MAXPAGECOUNT 999 //ÿҳ������

#endif  /* __WDL_EH__ */


/* the end */
