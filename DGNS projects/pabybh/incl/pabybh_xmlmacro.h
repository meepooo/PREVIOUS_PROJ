/********************************************************************
��Ȩ����:���ݺ������ӹɷ����޹�˾
��Ŀ����:�ۺ�Ӧ��ƽ̨��GAPS����Ŀ
��    ��:V1.0
����ϵͳ:AIX SCO LINUX SunOS HP-UX
�� �� ��:
�ļ�����:ͨ��XMLԪ�����ƺ궨��ͷ�ļ�
�ļ�����:pabybh_xmlmacro.h
�� Ŀ ��:
�� �� Ա:
��������:
��    ��:
�޸�����:
*********************************************************************/
/*
�޸ļ�¼
�޸�����:
�޸�����:
�޸���:
*/


#ifndef __PABYBH_XMLMACRO_H__
#define __PABYBH_XMLMACRO_H__

#define XMLNM_APP_JYXX_LSJLBZ           "/app/jyxx/lsjlbz"               /*��ˮ��¼��־ 0 ��¼ 1 ����¼*/

/*һ��XML�ڵ�   BEGIN-----*/
#define XMLNM_PABYBH_REQ_TRANSDATE             "/pabybh/req/transdate"            /*ƽ̨����*/
#define XMLNM_PABYBH_REQ_TRANSSERIALNO         "/pabybh/req/transserialno"        /*ƽ̨��ˮ��*/
#define XMLNM_PABYBH_REQ_ORITRANSDATE          "/pabybh/req/oritransdate"         /*ԭ��������*/
#define XMLNM_PABYBH_REQ_ORITRANSSERIALNO      "/pabybh/req/oritransserialno"     /*ԭ�ۺ�ǰ����ˮ��*/
#define XMLNM_PABYBH_REQ_TRANSTIME             "/pabybh/req/transtime"            /*����ʱ��*/
#define XMLNM_PABYBH_REQ_WORKDATE              "/pabybh/req/workdate"             /*ҵ������*/
#define XMLNM_PABYBH_REQ_WORKSERIALNO          "/pabybh/req/workserialno"         /*ҵ����ˮ��*/
#define XMLNM_PABYBH_REQ_REQDATE               "/pabybh/req/reqdate"              /*��������*/
#define XMLNM_PABYBH_REQ_REQSERIALNO           "/pabybh/req/reqserialno"          /*������ˮ��*/
#define XMLNM_PABYBH_REQ_CLUSTERNODENAME       "/pabybh/req/clusternodename"      /*��Ⱥ�ڵ��������*/
#define XMLNM_PABYBH_REQ_CLUSTERNODEIP         "/pabybh/req/clusternodeip"        /*��Ⱥ�ڵ����IP*/
#define XMLNM_PABYBH_REQ_COBANKNO              "/pabybh/req/cobankno"             /*�����к�*/
#define XMLNM_PABYBH_REQ_COBANKNAME            "/pabybh/req/cobankname"           /*����������*/
#define XMLNM_PABYBH_REQ_TRANSORG              "/pabybh/req/transorg"             /*���׻���*/
#define XMLNM_PABYBH_REQ_TRANSOPER             "/pabybh/req/transoper"            /*���׹�Ա*/
#define XMLNM_PABYBH_REQ_AUTHORG               "/pabybh/req/authorg"              /*��Ȩ����*/
#define XMLNM_PABYBH_REQ_AUTHOPER              "/pabybh/req/authoper"             /*��Ȩ��Ա*/
#define XMLNM_PABYBH_REQ_CNLTYPE               "/pabybh/req/cnltype"              /*��������*/
#define XMLNM_PABYBH_REQ_TERMEQUINO            "/pabybh/req/termequino"           /*�ն��豸���*/
#define XMLNM_PABYBH_REQ_TRANSCODE             "/pabybh/req/transcode"            /*���״���*/
#define XMLNM_PABYBH_REQ_TRANSCODE1            "/pabybh/req/transcode1"           /*���ӽ��״���0����1���2����������3���򹤱���*/
#define XMLNM_PABYBH_REQ_TRANSNAME             "/pabybh/req/transname"            /*��������*/
#define XMLNM_PABYBH_REQ_CUACOUNTYPE           "/pabybh/req/cuacountype"            /*�����ʱ�־*/
#define XMLNM_PABYBH_REQ_CAPITALTYPE           "/pabybh/req/capitaltype"          /*�ʽ�����,0---ת��1---ת��*/
#define XMLNM_PABYBH_REQ_SVRCODE               "/pabybh/req/svrcode"              /*�������(��ܡ��ƽ��)*/
#define XMLNM_PABYBH_REQ_CUSTNO                "/pabybh/req/custno"               /*�ͻ���*/
#define XMLNM_PABYBH_REQ_CUSTNAME              "/pabybh/req/custname"             /*�ͻ�����*/
#define XMLNM_PABYBH_REQ_CUSTTYPE              "/pabybh/req/custtype"             /*�ͻ�����00-����01-����*/
#define XMLNM_PABYBH_REQ_ACCTNO                "/pabybh/req/acctno"               /*�����˺�*/
#define XMLNM_PABYBH_REQ_ORIACCTNO             "/pabybh/req/oriacctno"               /*�����˺�*/
#define XMLNM_PABYBH_REQ_ACCTNO2               "/pabybh/req/acctno2"              /*�ʺ�2�������˻�*/
#define XMLNM_PABYBH_REQ_STOCKCODE             "/pabybh/req/stockcode"            /*ȯ�̴���*/
#define XMLNM_PABYBH_REQ_CAPITALACCTNO         "/pabybh/req/capitalacctno"        /*�ʽ��ʺ�*/
#define XMLNM_PABYBH_REQ_TRANSAMT              "/pabybh/req/transamt"             /*���׽��*/
#define XMLNM_PABYBH_REQ_ORITRANSAMT           "/pabybh/req/oritransamt"             /*���׽��*/
#define XMLNM_PABYBH_REQ_AMT2                  "/pabybh/req/amt2"                 /*���2*/
#define XMLNM_PABYBH_REQ_AMT3                  "/pabybh/req/amt3"                 /*���3*/
#define XMLNM_PABYBH_REQ_CURR                  "/pabybh/req/curr"                 /*����*/
#define XMLNM_PABYBH_REQ_CASHFLAG              "/pabybh/req/cashflag"             /*�����ʶ*/
#define XMLNM_PABYBH_REQ_IEPSVRCODE            "/pabybh/req/iepsvrcode"           /*��Eͨ�������*/
#define XMLNM_PABYBH_REQ_IEPTRANSCODE          "/pabybh/req/ieptranscode"         /*��Eͨ���״���*/
#define XMLNM_PABYBH_REQ_IEPBSIDATE            "/pabybh/req/iepbsidate"           /*��Eͨҵ������*/
#define XMLNM_PABYBH_REQ_IEPTRADATE            "/pabybh/req/ieptradate"           /*��Eͨ��������*/
#define XMLNM_PABYBH_REQ_IEPSERIALNO           "/pabybh/req/iepserialno"          /*��Eͨ��ˮ��*/
#define XMLNM_PABYBH_REQ_ORIIEPBSIDATE         "/pabybh/req/oriiepbsidate"        /*ԭ��Eͨҵ������*/
#define XMLNM_PABYBH_REQ_ORIIEPSERIALNO        "/pabybh/req/oriiepserialno"       /*ԭ��Eͨ��ˮ��*/
#define XMLNM_PABYBH_REQ_IEPRESPCODE           "/pabybh/req/ieprespcode"          /*��Eͨ��Ӧ����*/
#define XMLNM_PABYBH_REQ_IEPRESPMSG            "/pabybh/req/ieprespmsg"           /*��Eͨ��Ӧ��Ϣ*/
#define XMLNM_PABYBH_REQ_HOSTBSIDATE           "/pabybh/req/hostbsidate"          /*������������*/
#define XMLNM_PABYBH_REQ_HOSTSERIALNO          "/pabybh/req/hostserialno"         /*������ˮ��*/
#define XMLNM_PABYBH_REQ_HOSTTRANSCODE         "/pabybh/req/hosttranscode"        /*�������״���*/
#define XMLNM_PABYBH_REQ_HOSTRESPCODE          "/pabybh/req/hostrespcode"         /*������Ӧ����*/
#define XMLNM_PABYBH_REQ_HOSTRESPMSG           "/pabybh/req/hostrespmsg"          /*������Ӧ��Ϣ*/
#define XMLNM_PABYBH_REQ_RESPCODE              "/pabybh/req/respcode"             /*��Ӧ��*/
#define XMLNM_PABYBH_REQ_RESPMSG               "/pabybh/req/respmsg"              /*��Ӧ��Ϣ*/
#define XMLNM_PABYBH_REQ_IEPSTAT               "/pabybh/req/iepstat"              /*����״̬'0�ɹ�1ʧ��6״̬δ֪7������8������9��ʼ'*/
#define XMLNM_PABYBH_REQ_HOSTSTAT              "/pabybh/req/hoststat"             /*����״̬'0�ɹ�1ʧ��6״̬δ֪7������8������9��ʼ'*/
#define XMLNM_PABYBH_REQ_STAT                  "/pabybh/req/stat"                 /*����״̬'0�ɹ�1ʧ��6״̬δ֪7������8������9��ʼ'*/
#define XMLNM_PABYBH_REQ_ORISTAT               "/pabybh/req/oristat"              /*ƽ̨ͬ������ǰԭ����״̬'0�ɹ�1ʧ��6״̬δ֪7������8������9��ʼ Xԭ��ˮ������'*/
#define XMLNM_PABYBH_REQ_CERTTYPE              "/pabybh/req/certtype"             /*֤������*/
#define XMLNM_PABYBH_REQ_CERTNO                "/pabybh/req/certno"               /*֤������*/
#define XMLNM_PABYBH_REQ_PHONE                 "/pabybh/req/phone"                /*��ϵ��ʽ*/
#define XMLNM_PABYBH_REQ_AGENTNAME             "/pabybh/req/agentname"            /*�����˿ͻ�����*/
#define XMLNM_PABYBH_REQ_AGENTCERTY            "/pabybh/req/agentcerty"           /*������֤������*/
#define XMLNM_PABYBH_REQ_AGENTCERNO            "/pabybh/req/agentcerno"           /*������֤������*/
#define XMLNM_PABYBH_REQ_AGENTPHONE            "/pabybh/req/agentphone"           /*��������ϵ��ʽ*/
#define XMLNM_PABYBH_REQ_CHKFLAG               "/pabybh/req/chkflag"              /*���˱�־,0-δ����1-�Ѷ�ƽ2-ƽ����3-���Ķ�4-˫���޼���*/
#define XMLNM_PABYBH_REQ_MEMO                  "/pabybh/req/memo"                 /*��ע*/
#define XMLNM_PABYBH_REQ_EXTFLD1               "/pabybh/req/extfld1"              /*�����ֶ�1*/
#define XMLNM_PABYBH_REQ_EXTFLD2               "/pabybh/req/extfld2"              /*�����ֶ�2*/
#define XMLNM_PABYBH_REQ_EXTFLD3               "/pabybh/req/extfld3"              /*�����ֶ�3*/
#define XMLNM_PABYBH_REQ_EXTFLD4               "/pabybh/req/extfld4"              /*�����ֶ�4*/

#define XMLNM_PABYBH_REQ_OPERASTEP             "/pabybh/req/operastep"            /*������־0-���¶��� 1-��������*/
#define XMLNM_PABYBH_REQ_CHECKDATE             "/pabybh/req/checkdate"            /*��������*/
#define XMLNM_PABYBH_REQ_FILENAME              "/pabybh/req/filename"             /*�ļ�����*/
#define XMLNM_PABYBH_REQ_SIGNSTATUS            "/pabybh/req/signstatus"           /*ǩ��������־*/
#define XMLNM_PABYBH_REQ_CURRSTEP              "/pabybh/req/currstep"             /*��ǰ����*/
#define XMLNM_PABYBH_REQ_CURRSTAT              "/pabybh/req/currstat"             /*��ǰ����״̬*/

#define XMLNM_PABYBH_RESP_OPENORG              "/pabybh/resp/openorg"             /*�������� ����������*/


#define XMLNM_PABYBH_RESP_IEPBSIDATE            "/pabybh/resp/iepbsidate"           /*��Eͨ��������*/
#define XMLNM_PABYBH_RESP_IEPSERIALNO           "/pabybh/resp/iepserialno"          /*��Eͨ��ˮ��*/
#define XMLNM_PABYBH_RESP_IEPRESPCODE           "/pabybh/resp/ieprespcode"          /*��Eͨ��Ӧ����*/
#define XMLNM_PABYBH_RESP_IEPRESPMSG            "/pabybh/resp/ieprespmsg"           /*��Eͨ��Ӧ��Ϣ*/
#define XMLNM_PABYBH_RESP_HOSTBSIDATE           "/pabybh/resp/hostbsidate"          /*������������*/
#define XMLNM_PABYBH_RESP_HOSTSERIALNO          "/pabybh/resp/hostserialno"         /*������ˮ��*/
#define XMLNM_PABYBH_RESP_HOSTTRANSCODE         "/pabybh/resp/hosttranscode"        /*�������״���*/
#define XMLNM_PABYBH_RESP_HOSTRESPCODE          "/pabybh/resp/hostrespcode"         /*������Ӧ����*/
#define XMLNM_PABYBH_RESP_HOSTRESPMSG           "/pabybh/resp/hostrespmsg"          /*������Ӧ��Ϣ*/
#define XMLNM_PABYBH_RESP_RESPCODE              "/pabybh/resp/respcode"             /*��Ӧ��*/
#define XMLNM_PABYBH_RESP_RESPMSG               "/pabybh/resp/respmsg"              /*��Ӧ��Ϣ*/
/*END------------*/


/*�����������Ϣ   BEGIN---*/               
#define XMLNM_PABYBH_ORGCFG_COBANKNO       "/pabybh/orgcfg/cobankno"       /*�����кš�ƽ�����䡿*/          
#define XMLNM_PABYBH_ORGCFG_COBANKNAME     "/pabybh/orgcfg/cobankname"     /*����������*/                    
#define XMLNM_PABYBH_ORGCFG_CUSTMANAGERNO  "/pabybh/orgcfg/custmanagerno"  /*ƽ������ͻ�����š�ƽ�����䡿*/
#define XMLNM_PABYBH_ORGCFG_ACCT1          "/pabybh/orgcfg/acct1"          /*ͷ���˻�*/                      
#define XMLNM_PABYBH_ORGCFG_ACCT1NAME      "/pabybh/orgcfg/acct1name"      /*ͷ���˻�����*/                  
#define XMLNM_PABYBH_ORGCFG_ACCT2          "/pabybh/orgcfg/acct2"          /*�ڲ������˻�*/                  
#define XMLNM_PABYBH_ORGCFG_ACCT2NAME      "/pabybh/orgcfg/acct2name"      /*�ڲ������˻�����*/              
#define XMLNM_PABYBH_ORGCFG_SIGNSTATUS     "/pabybh/orgcfg/signstatus"     /*ǩ��״̬��0-ǩ����1-ǩ��*/      
#define XMLNM_PABYBH_ORGCFG_AREACODE       "/pabybh/orgcfg/areacode"       /*�������롾ƽ�����䡿*/          
#define XMLNM_PABYBH_ORGCFG_COORGNO        "/pabybh/orgcfg/coorgno"        /*�����л����š�ƽ�����䡿*/      
#define XMLNM_PABYBH_ORGCFG_WORKDATE       "/pabybh/orgcfg/workdate"       /*ҵ������*/                      
#define XMLNM_PABYBH_ORGCFG_WORKSERIALNO   "/pabybh/orgcfg/workserialno"   /*ҵ����ˮ��*/                    
#define XMLNM_PABYBH_ORGCFG_MAINTAINDATE   "/pabybh/orgcfg/maintaindate"   /*ά������*/                      
#define XMLNM_PABYBH_ORGCFG_MAINTAINTIME   "/pabybh/orgcfg/maintaintime"   /*ά��ʱ��*/                      
#define XMLNM_PABYBH_ORGCFG_EXTFLD1        "/pabybh/orgcfg/extfld1"        /*��չ1*/                         
#define XMLNM_PABYBH_ORGCFG_EXTFLD2        "/pabybh/orgcfg/extfld2"        /*��չ2*/                         
#define XMLNM_PABYBH_ORGCFG_EXTFLD3        "/pabybh/orgcfg/extfld3"        /*��չ3*/                         
#define XMLNM_PABYBH_ORGCFG_EXTFLD4        "/pabybh/orgcfg/extfld4"        /*��չ4*/                         
/*END---------*/

/*��Կ��Ϣ    BEGIN----*/
#define XMLNM_PABYBH_SECKEY_COBANKNO       "/pabybh/seckey/cobankno"       /*�����к�*/
#define XMLNM_PABYBH_SECKEY_ENCRYPTIP      "/pabybh/seckey/encryptip"      /*����ƽ̨��ַ*/
#define XMLNM_PABYBH_SECKEY_ENCRYPTPORT    "/pabybh/seckey/encryptport"    /*����ƽ̨�˿�*/
#define XMLNM_PABYBH_SECKEY_ENCRYPTSYSID   "/pabybh/seckey/encryptsysid"   /*����ƽ̨ϵͳID*/
#define XMLNM_PABYBH_SECKEY_ENCRYPTEXTID   "/pabybh/seckey/encryptextid"   /*����ƽ̨�ⲿID*/
#define XMLNM_PABYBH_SECKEY_ZMK            "/pabybh/seckey/zmk"            /*ZMK*/
#define XMLNM_PABYBH_SECKEY_ZAK            "/pabybh/seckey/zak"            /*ZAK*/
#define XMLNM_PABYBH_SECKEY_IEPZPK         "/pabybh/seckey/iepzpk"         /*ZPKƽ��*/
#define XMLNM_PABYBH_SECKEY_COUNTERZPK     "/pabybh/seckey/counterzpk"     /*ZPK����*/
#define XMLNM_PABYBH_SECKEY_HOSTZPK        "/pabybh/seckey/hostzpk"        /*ZPK������*/
#define XMLNM_PABYBH_SECKEY_EXTFLD1        "/pabybh/seckey/extfld1"        /*��չ1*/
#define XMLNM_PABYBH_SECKEY_EXTFLD2        "/pabybh/seckey/extfld2"        /*��չ2*/
#define XMLNM_PABYBH_SECKEY_EXTFLD3        "/pabybh/seckey/extfld3"        /*��չ3*/
#define XMLNM_PABYBH_SECKEY_EXTFLD4        "/pabybh/seckey/extfld4"        /*��չ4*/
/*END----------*/

/*ǩԼ��Ϣ    BEGIN------*/
#define XMLNM_PABYBH_SIGN_SIGNDATE          "/pabybh/sign/signdate"             /*ָ������aptDate*/
#define XMLNM_PABYBH_SIGN_SIGNTMIE          "/pabybh/sign/signtmie"             /*ָ��ʱ��apt_tmie*/
#define XMLNM_PABYBH_SIGN_COBANKNO          "/pabybh/sign/cobankno"             /*�����к�*/
#define XMLNM_PABYBH_SIGN_COBANKNAME        "/pabybh/sign/cobankname"           /*����������*/
#define XMLNM_PABYBH_SIGN_ACCTNO            "/pabybh/sign/acctno"               /*�����˺�*/
#define XMLNM_PABYBH_SIGN_OLDACCTNO         "/pabybh/sign/oldacctno"            /*�������˺�*/
#define XMLNM_PABYBH_SIGN_CERTTYPE          "/pabybh/sign/certtype"             /*֤������*/
#define XMLNM_PABYBH_SIGN_CERTNO            "/pabybh/sign/certno"               /*֤������*/
#define XMLNM_PABYBH_SIGN_CUSTTYPE          "/pabybh/sign/custtype"             /*�ͻ�����*/
#define XMLNM_PABYBH_SIGN_CUSTNAME          "/pabybh/sign/custname"             /*�ͻ�����*/
#define XMLNM_PABYBH_SIGN_STOCKCODE         "/pabybh/sign/stockcode"            /*ȯ�̴���*/
#define XMLNM_PABYBH_SIGN_CAPITALACCTNO     "/pabybh/sign/capitalacctno"        /*֤ȯ�ʽ�̨�˺�*/
#define XMLNM_PABYBH_SIGN_CURR              "/pabybh/sign/curr"                 /*����*/
#define XMLNM_PABYBH_SIGN_CUSTMANAGERID     "/pabybh/sign/custmanagerid"        /*�ͻ������*/
#define XMLNM_PABYBH_SIGN_CUSTMANAGERNAME   "/pabybh/sign/custmanagername"      /*�ͻ���������*/
#define XMLNM_PABYBH_SIGN_OPENORG           "/pabybh/sign/openorg"              /*���������*/
#define XMLNM_PABYBH_SIGN_BUSITYPE          "/pabybh/sign/busitype"             /*ҵ������*/
#define XMLNM_PABYBH_SIGN_STAT              "/pabybh/sign/stat"                 /*ǩԼ״̬'9-��У��1-ǩԼ2-��Լ'*/
#define XMLNM_PABYBH_SIGN_HOSTSTAT          "/pabybh/sign/hoststat"             /*����ǩԼ״̬'9-��У��1-ǩԼ2-��Լ'*/
#define XMLNM_PABYBH_SIGN_HOSTDATE          "/pabybh/sign/hostdate"             /*����ǩԼ����*/
#define XMLNM_PABYBH_SIGN_HOSTSERIALNO      "/pabybh/sign/hostserialno"         /*������ˮ*/
#define XMLNM_PABYBH_SIGN_CHKFLAG           "/pabybh/sign/chkflag"              /*���˱�־'0-δ����1-�Ѷ���'*/
#define XMLNM_PABYBH_SIGN_UPDATEDATE        "/pabybh/sign/updatedate"           /*��������*/
#define XMLNM_PABYBH_SIGN_UPDATETIME        "/pabybh/sign/updatetime"           /*����ʱ��*/
#define XMLNM_PABYBH_SIGN_TRANSORG          "/pabybh/sign/transorg"             /*���׻���*/
#define XMLNM_PABYBH_SIGN_TRANSOPER         "/pabybh/sign/transoper"            /*���׹�Ա*/
#define XMLNM_PABYBH_SIGN_AUTHORG           "/pabybh/sign/authorg"              /*��Ȩ����*/
#define XMLNM_PABYBH_SIGN_AUTHOPER          "/pabybh/sign/authoper"             /*��Ȩ��Ա*/
#define XMLNM_PABYBH_SIGN_MEMO              "/pabybh/sign/memo"                 /*��ע*/
#define XMLNM_PABYBH_SIGN_EXTFLD1           "/pabybh/sign/extfld1"              /*�����ֶ�1*/
#define XMLNM_PABYBH_SIGN_EXTFLD2           "/pabybh/sign/extfld2"              /*�����ֶ�2*/
#define XMLNM_PABYBH_SIGN_EXTFLD3           "/pabybh/sign/extfld3"              /*�����ֶ�3*/
#define XMLNM_PABYBH_SIGN_EXTFLD4           "/pabybh/sign/extfld4"              /*�����ֶ�4*/
#define XMLNM_PABYBH_SIGN_EXTFLD5           "/pabybh/sign/extfld5"              /*�����ֶ�5*/
#define XMLNM_PABYBH_SIGN_EXTFLD6           "/pabybh/sign/extfld6"              /*�����ֶ�6*/
/*END--------------*/


/*�ͻ���Ϣ��     BEGIN-----*/
#define XMLNM_PABYBH_CUSTINFO_CERTTYPE      "/pabybh/custinfo/certType"       /*֤������*/
#define XMLNM_PABYBH_CUSTINFO_CERTNO        "/pabybh/custinfo/certNo"         /*֤������*/
#define XMLNM_PABYBH_CUSTINFO_CUSTTYPE      "/pabybh/custinfo/custType"       /*�ͻ�����*/
#define XMLNM_PABYBH_CUSTINFO_CUSTNAME      "/pabybh/custinfo/custName"       /*�ͻ�����*/
#define XMLNM_PABYBH_CUSTINFO_POST          "/pabybh/custinfo/post"           /*��������*/
#define XMLNM_PABYBH_CUSTINFO_ADDR          "/pabybh/custinfo/addr"           /*��ϵ��ַ*/
#define XMLNM_PABYBH_CUSTINFO_EMAIL         "/pabybh/custinfo/email"          /*�����ʼ���ַ*/
#define XMLNM_PABYBH_CUSTINFO_PHONE         "/pabybh/custinfo/phone"          /*��ϵ�绰*/
#define XMLNM_PABYBH_CUSTINFO_MOBILE        "/pabybh/custinfo/mobile"         /*�ƶ��绰*/
#define XMLNM_PABYBH_CUSTINFO_FAX           "/pabybh/custinfo/fax"            /*����*/
#define XMLNM_PABYBH_CUSTINFO_UPDATEDATE    "/pabybh/custinfo/updateDate"     /*��������*/
#define XMLNM_PABYBH_CUSTINFO_UPDATETIME    "/pabybh/custinfo/updateTime"     /*����ʱ��*/
#define XMLNM_PABYBH_CUSTINFO_CREATEDATE    "/pabybh/custinfo/createDate"     /*��������*/
#define XMLNM_PABYBH_CUSTINFO_CREATETIME    "/pabybh/custinfo/createTime"     /*����ʱ��*/
#define XMLNM_PABYBH_CUSTINFO_EXTFLD1       "/pabybh/custinfo/extfld1"        /*�����ֶ�1*/
#define XMLNM_PABYBH_CUSTINFO_EXTFLD2       "/pabybh/custinfo/extfld2"        /*�����ֶ�2*/
#define XMLNM_PABYBH_CUSTINFO_EXTFLD3       "/pabybh/custinfo/extfld3"        /*�����ֶ�3*/
/*END--------------*/

/*������Ϣ      BEGIN-----*/
#define XMLNM_PABYBH_SVFINFO_SVRCODE       "/pabybh/svrinfo/svrcode"         /*�������	*/
#define XMLNM_PABYBH_SVFINFO_SVRNAME       "/pabybh/svrinfo/svrname"         /*��������*/
#define XMLNM_PABYBH_SVFINFO_WORKTIME      "/pabybh/svrinfo/worktime"        /*ҵ��չʱ���*/
#define XMLNM_PABYBH_SVFINFO_SVRSTATUS     "/pabybh/svrinfo/svrstatus"       /*����״̬*/
#define XMLNM_PABYBH_SVFINFO_EXTFLD1       "/pabybh/svrinfo/extfld1"         /*�����ֶ�1*/
#define XMLNM_PABYBH_SVFINFO_EXTFLD2       "/pabybh/svrinfo/extfld2"         /*�����ֶ�2*/
#define XMLNM_PABYBH_SVFINFO_EXTFLD3       "/pabybh/svrinfo/extfld3"         /*�����ֶ�3*/
/*END-------------*/                                                         

/*���Ľ��׿�����Ϣ    BEGIN------*/
#define XMLNM_PABYBH_PABTRANSCTL_TRANSCODE     "/pabybh/pabtransctl/transcode"     /*���״���*/
#define XMLNM_PABYBH_PABTRANSCTL_TRANSNAME     "/pabybh/pabtransctl/transname"     /*��������*/
#define XMLNM_PABYBH_PABTRANSCTL_SVRCODE       "/pabybh/pabtransctl/svrcode"       /*�������*/
#define XMLNM_PABYBH_PABTRANSCTL_OPENFLAG      "/pabybh/pabtransctl/openflag"      /*���ر�־'0--��1--��'*/
#define XMLNM_PABYBH_PABTRANSCTL_MACFLAG       "/pabybh/pabtransctl/macflag"       /*MACУ���־'0--��1--��'*/
#define XMLNM_PABYBH_PABTRANSCTL_EXTFLD1       "/pabybh/pabtransctl/extfld1"       /*�����ֶ�1*/
#define XMLNM_PABYBH_PABTRANSCTL_EXTFLD2       "/pabybh/pabtransctl/extfld2"       /*�����ֶ�2*/
#define XMLNM_PABYBH_PABTRANSCTL_EXTFLD3       "/pabybh/pabtransctl/extfld3"       /*�����ֶ�3*/
/*END------------*/

/*������ˮ��     BEGIN--------*/
#define XMLNM_PABYBH_SERIAL_TRANSDATE             "/pabybh/serial/transdate"            /*ƽ̨����*/
#define XMLNM_PABYBH_SERIAL_TRANSSERIALNO         "/pabybh/serial/transserialno"        /*ƽ̨��ˮ��*/
#define XMLNM_PABYBH_SERIAL_ORITRANSDATE          "/pabybh/serial/oritransdate"         /*ԭƽ̨����*/
#define XMLNM_PABYBH_SERIAL_ORITRANSSERIALNO      "/pabybh/serial/oritransserialno"     /*ԭƽ̨��ˮ��*/
#define XMLNM_PABYBH_SERIAL_TRANSTIME             "/pabybh/serial/transtime"            /*����ʱ��*/
#define XMLNM_PABYBH_SERIAL_WORKDATE              "/pabybh/serial/workdate"             /*ҵ������*/
#define XMLNM_PABYBH_SERIAL_WORKSERIALNO          "/pabybh/serial/workserialno"         /*ҵ����ˮ��*/
#define XMLNM_PABYBH_SERIAL_REQDATE               "/pabybh/serial/reqdate"              /*��������*/
#define XMLNM_PABYBH_SERIAL_REQSERIALNO           "/pabybh/serial/reqserialno"          /*������ˮ��*/
#define XMLNM_PABYBH_SERIAL_CLUSTERNODENAME       "/pabybh/serial/clusternodename"      /*��Ⱥ�ڵ��������*/
#define XMLNM_PABYBH_SERIAL_CLUSTERNODEIP         "/pabybh/serial/clusternodeip"        /*��Ⱥ�ڵ����IP*/
#define XMLNM_PABYBH_SERIAL_COBANKNO              "/pabybh/serial/cobankno"             /*�����к�*/
#define XMLNM_PABYBH_SERIAL_TRANSORG              "/pabybh/serial/transorg"             /*���׻���*/
#define XMLNM_PABYBH_SERIAL_TRANSOPER             "/pabybh/serial/transoper"            /*���׹�Ա*/
#define XMLNM_PABYBH_SERIAL_AUTHORG               "/pabybh/serial/authorg"              /*��Ȩ����*/
#define XMLNM_PABYBH_SERIAL_AUTHOPER              "/pabybh/serial/authoper"             /*��Ȩ��Ա*/
#define XMLNM_PABYBH_SERIAL_CNLTYPE               "/pabybh/serial/cnltype"              /*��������*/
#define XMLNM_PABYBH_SERIAL_TERMEQUINO            "/pabybh/serial/termequino"           /*�ն��豸���*/
#define XMLNM_PABYBH_SERIAL_TRANSCODE             "/pabybh/serial/transcode"            /*���״���*/
#define XMLNM_PABYBH_SERIAL_TRANSCODE1            "/pabybh/serial/transcode1"           /*���ӽ��״���0����1���2����������3���򹤱���*/
#define XMLNM_PABYBH_SERIAL_TRANSNAME             "/pabybh/serial/transname"            /*��������*/
#define XMLNM_PABYBH_SERIAL_CUACOUNTYPE           "/pabybh/serial/cuacountype"            /*�����ʱ�־*/
#define XMLNM_PABYBH_SERIAL_CAPITALTYPE           "/pabybh/serial/capitaltype"          /*�ʽ�����,0---ת��1---ת��*/
#define XMLNM_PABYBH_SERIAL_SVRCODE               "/pabybh/serial/svrcode"              /*�������(��ܡ��ƽ��)*/
#define XMLNM_PABYBH_SERIAL_CUSTNAME              "/pabybh/serial/custname"             /*�ͻ�����*/
#define XMLNM_PABYBH_SERIAL_CUSTTYPE              "/pabybh/serial/custtype"             /*�ͻ�����00-����01-����*/
#define XMLNM_PABYBH_SERIAL_ACCTNO                "/pabybh/serial/acctno"               /*�����˺�*/
#define XMLNM_PABYBH_SERIAL_ORIACCTNO             "/pabybh/serial/oriacctno"               /*�����˺�*/
#define XMLNM_PABYBH_SERIAL_ACCTNO2               "/pabybh/serial/acctno2"              /*�ʺ�2�������˻�*/
#define XMLNM_PABYBH_SERIAL_STOCKCODE             "/pabybh/serial/stockcode"          /*ȯ�̴���*/
#define XMLNM_PABYBH_SERIAL_CAPITALACCTNO         "/pabybh/serial/capitalacctno"        /*�ʽ��ʺ�*/
#define XMLNM_PABYBH_SERIAL_TRANSAMT              "/pabybh/serial/transamt"             /*���׽��*/
#define XMLNM_PABYBH_SERIAL_ORITRANSAMT           "/pabybh/serial/oritransamt"             /*���׽��*/
#define XMLNM_PABYBH_SERIAL_AMT2                  "/pabybh/serial/amt2"                 /*���2*/
#define XMLNM_PABYBH_SERIAL_AMT3                  "/pabybh/serial/amt3"                 /*���3*/
#define XMLNM_PABYBH_SERIAL_CURR                  "/pabybh/serial/curr"                 /*����*/
#define XMLNM_PABYBH_SERIAL_CASHFLAG              "/pabybh/serial/cashflag"             /*�����ʶ*/
#define XMLNM_PABYBH_SERIAL_IEPSVRCODE            "/pabybh/serial/iepsvrcode"           /*��Eͨ�������*/
#define XMLNM_PABYBH_SERIAL_IEPTRANSCODE          "/pabybh/serial/ieptranscode"         /*��Eͨ���״���*/
#define XMLNM_PABYBH_SERIAL_IEPBSIDATE            "/pabybh/serial/iepbsidate"           /*��Eͨҵ������*/
#define XMLNM_PABYBH_SERIAL_IEPTRADATE            "/pabybh/serial/ieptradate"           /*��Eͨ��������*/
#define XMLNM_PABYBH_SERIAL_IEPSERIALNO           "/pabybh/serial/iepserialno"          /*��Eͨ��ˮ��*/
#define XMLNM_PABYBH_SERIAL_ORIIEPBSIDATE         "/pabybh/serial/oriiepbsidate"        /*ԭ��Eͨҵ������*/
#define XMLNM_PABYBH_SERIAL_ORIIEPSERIALNO        "/pabybh/serial/oriiepserialno"       /*ԭ��Eͨ��ˮ��*/
#define XMLNM_PABYBH_SERIAL_IEPRESPCODE           "/pabybh/serial/ieprespcode"          /*��Eͨ��Ӧ����*/
#define XMLNM_PABYBH_SERIAL_IEPRESPMSG            "/pabybh/serial/ieprespmsg"           /*��Eͨ��Ӧ��Ϣ*/
#define XMLNM_PABYBH_SERIAL_HOSTBSIDATE           "/pabybh/serial/hostbsidate"          /*������������*/
#define XMLNM_PABYBH_SERIAL_HOSTSERIALNO          "/pabybh/serial/hostserialno"         /*������ˮ��*/
#define XMLNM_PABYBH_SERIAL_HOSTTRANSCODE         "/pabybh/serial/hosttranscode"        /*�������״���*/
#define XMLNM_PABYBH_SERIAL_HOSTRESPCODE          "/pabybh/serial/hostrespcode"         /*������Ӧ����*/
#define XMLNM_PABYBH_SERIAL_HOSTRESPMSG           "/pabybh/serial/hostrespmsg"          /*������Ӧ��Ϣ*/
#define XMLNM_PABYBH_SERIAL_RESPCODE              "/pabybh/serial/respcode"             /*��Ӧ��*/
#define XMLNM_PABYBH_SERIAL_RESPMSG               "/pabybh/serial/respmsg"              /*��Ӧ��Ϣ*/
#define XMLNM_PABYBH_SERIAL_IEPSTAT               "/pabybh/serial/iepstat"              /*���Ľ���״̬'0�ɹ�1ʧ��6״̬δ֪7������8������9��ʼ'*/
#define XMLNM_PABYBH_SERIAL_HOSTSTAT              "/pabybh/serial/hoststat"             /*���Ľ���״̬'0�ɹ�1ʧ��6״̬δ֪7������8������9��ʼ'*/
#define XMLNM_PABYBH_SERIAL_STAT                  "/pabybh/serial/stat"                 /*����״̬'0�ɹ�1ʧ��6״̬δ֪7������8������9��ʼ'*/
#define XMLNM_PABYBH_SERIAL_ORISTAT               "/pabybh/serial/oristat"              /*ƽ̨ͬ������ǰԭ����״̬'0�ɹ�1ʧ��6״̬δ֪7������8������9��ʼ'*/
#define XMLNM_PABYBH_SERIAL_CERTTYPE              "/pabybh/serial/certtype"             /*֤������*/
#define XMLNM_PABYBH_SERIAL_CERTNO                "/pabybh/serial/certno"               /*֤������*/
#define XMLNM_PABYBH_SERIAL_PHONE                 "/pabybh/serial/phone"                /*��ϵ��ʽ*/
#define XMLNM_PABYBH_SERIAL_AGENTNAME             "/pabybh/serial/agentname"            /*�����˿ͻ�����*/
#define XMLNM_PABYBH_SERIAL_AGENTCERTY            "/pabybh/serial/agentcerty"           /*������֤������*/
#define XMLNM_PABYBH_SERIAL_AGENTCERNO            "/pabybh/serial/agentcerno"           /*������֤������*/
#define XMLNM_PABYBH_SERIAL_AGENTPHONE            "/pabybh/serial/agentphone"           /*��������ϵ��ʽ*/
#define XMLNM_PABYBH_SERIAL_CHKFLAG               "/pabybh/serial/chkflag"              /*���˱�־,0-δ����1-�Ѷ�ƽ2-ƽ����3-���Ķ�4-˫���޼���*/
#define XMLNM_PABYBH_SERIAL_MEMO                  "/pabybh/serial/memo"                 /*��ע*/
#define XMLNM_PABYBH_SERIAL_EXTFLD1               "/pabybh/serial/extfld1"              /*�����ֶ�1*/
#define XMLNM_PABYBH_SERIAL_EXTFLD2               "/pabybh/serial/extfld2"              /*�����ֶ�2*/
#define XMLNM_PABYBH_SERIAL_EXTFLD3               "/pabybh/serial/extfld3"              /*�����ֶ�3*/
#define XMLNM_PABYBH_SERIAL_EXTFLD4               "/pabybh/serial/extfld4"              /*�����ֶ�4*/
/*END--------------*/

/*����״̬��Ϣ      BEGIN------*/
#define XMLNM_PABYBH_CHECKCTL_CHTRANSDATE                "/pabybh/checkctl/chtransdate"                /*���˷�������*/
#define XMLNM_PABYBH_CHECKCTL_CHTRANSNO                  "/pabybh/checkctl/chtransno"                  /*���˷�����ˮ��*/
#define XMLNM_PABYBH_CHECKCTL_CHECKDATE                  "/pabybh/checkctl/checkdate"                  /*��������*/
#define XMLNM_PABYBH_CHECKCTL_COBANKNO                   "/pabybh/checkctl/cobankno"                   /*�����к�*/
#define XMLNM_PABYBH_CHECKCTL_SVRCODE                    "/pabybh/checkctl/svrcode"                    /*������ҵ������*/
#define XMLNM_PABYBH_CHECKCTL_MSGTYPE                    "/pabybh/checkctl/msgtype"                    /*��������0�ʽ���1�˻��ࣨ������2�˻��ࣨ��Լ&������*/
#define XMLNM_PABYBH_CHECKCTL_TOTALCOUNT                 "/pabybh/checkctl/totalcount"                 /*�ܱ���*/
#define XMLNM_PABYBH_CHECKCTL_TOTALAMT                   "/pabybh/checkctl/totalamt"                   /*�ܽ��*/
#define XMLNM_PABYBH_CHECKCTL_INTOTCNT                 "/pabybh/checkctl/intotcnt"                 /*ת���ܱ���*/
#define XMLNM_PABYBH_CHECKCTL_INTOTAMT                   "/pabybh/checkctl/intotamt"                   /*ת���ܽ��*/
#define XMLNM_PABYBH_CHECKCTL_OUTTOTCNT                 "/pabybh/checkctl/outtotcnt"                 /*ת���ܱ���*/
#define XMLNM_PABYBH_CHECKCTL_OUTTOTAMT                   "/pabybh/checkctl/outtotamt"                   /*ת���ܽ��*/
#define XMLNM_PABYBH_CHECKCTL_BACKTOTALCOUNT             "/pabybh/checkctl/backtotalcount"             /*�����ܱ���*/
#define XMLNM_PABYBH_CHECKCTL_BACKTOTALAMT               "/pabybh/checkctl/backtotalamt"               /*�����ܽ��*/
#define XMLNM_PABYBH_CHECKCTL_LOCALTOTALCOUNT            "/pabybh/checkctl/localtotalcount"            /*ƽ̨�ܱ���*/
#define XMLNM_PABYBH_CHECKCTL_LOCALTOTALAMT              "/pabybh/checkctl/localtotalamt"              /*ƽ̨�ܽ��*/
#define XMLNM_PABYBH_CHECKCTL_LOCALBACKTOTALCOUNT        "/pabybh/checkctl/localbacktotalcount"        /*ƽ̨�����ܱ���*/
#define XMLNM_PABYBH_CHECKCTL_LOCALBACKTOTALAMT          "/pabybh/checkctl/localbacktotalamt"          /*ƽ̨�����ܽ��*/
#define XMLNM_PABYBH_CHECKCTL_HOSTTOTALCOUNT             "/pabybh/checkctl/hosttotalcount"             /*�����ܱ���*/
#define XMLNM_PABYBH_CHECKCTL_HOSTTOTALAMT               "/pabybh/checkctl/hosttotalamt"               /*�����ܽ��*/
#define XMLNM_PABYBH_CHECKCTL_HOSTBACKTOTALCOUNT         "/pabybh/checkctl/hostbacktotalcount"         /*���ĳ����ܱ���*/
#define XMLNM_PABYBH_CHECKCTL_HOSTBACKTOTALAMT           "/pabybh/checkctl/hostbacktotalamt"           /*���ĳ����ܽ��*/
#define XMLNM_PABYBH_CHECKCTL_NETAMT                     "/pabybh/checkctl/netamt"                     /*������*/
#define XMLNM_PABYBH_CHECKCTL_NETTYPE                    "/pabybh/checkctl/nettype"                    /*�����'0����1֧��'*/
#define XMLNM_PABYBH_CHECKCTL_IEPCHKFILE                 "/pabybh/checkctl/iepchkfile"                 /*ƽ�������ļ���*/
#define XMLNM_PABYBH_CHECKCTL_HOSTCHKFILE                "/pabybh/checkctl/hostchkfile"                /*���������ļ���*/
#define XMLNM_PABYBH_CHECKCTL_EXECTIME                   "/pabybh/checkctl/exectime"                   /*ִ��ʱ��'��ʼʱ��|����ʱ��|'*/
#define XMLNM_PABYBH_CHECKCTL_EXECSTEP                   "/pabybh/checkctl/execstep"                   /*ִ�в���'0-��ȡƽ��������Ϣ1-ƽ�������ļ����2-ƽ����ϸ�������3-�����ύ����4-��ȡ���������ļ�,�������ɶ����ļ����5-������ϸ�������'*/
#define XMLNM_PABYBH_CHECKCTL_EXECSTAT                   "/pabybh/checkctl/execstat"                   /*ִ��״̬'1-�ɹ�2-ʧ��9-������'*/
#define XMLNM_PABYBH_CHECKCTL_CHKDETAILRESULT            "/pabybh/checkctl/chkdetailresult"            /*��ϸ���˽��'0δ����1����ƽ2���˲�ƽ3���˳���9������'*/
#define XMLNM_PABYBH_CHECKCTL_CHKPABTOTALRESULT          "/pabybh/checkctl/chkpabtotalresult"          /*���Ķ����˽��'0δ����1����ƽ2���˲�ƽ3���˳���9������'*/
#define XMLNM_PABYBH_CHECKCTL_CHKHOSTTOTALRESULT         "/pabybh/checkctl/chkhosttotalresult"         /*���Ķ����˽��'0δ����1����ƽ2���˲�ƽ3���˳���9������'*/
#define XMLNM_PABYBH_CHECKCTL_TRANSDATE                  "/pabybh/checkctl/transdate"                  /*��������*/
#define XMLNM_PABYBH_CHECKCTL_TRANSSERIALNO              "/pabybh/checkctl/transserialno"              /*ǰ����ˮ��*/
#define XMLNM_PABYBH_CHECKCTL_SETTLEDATE                 "/pabybh/checkctl/settledate"                 /*��������*/
#define XMLNM_PABYBH_CHECKCTL_SETTLESERNO                "/pabybh/checkctl/settleserno"                /*������ˮ��*/
#define XMLNM_PABYBH_CHECKCTL_HOSTDATE                   "/pabybh/checkctl/hostdate"                   /*��������*/
#define XMLNM_PABYBH_CHECKCTL_HOSTSERIALNO               "/pabybh/checkctl/hostserialno"               /*������ˮ��*/
#define XMLNM_PABYBH_CHECKCTL_TRANSORG                   "/pabybh/checkctl/transorg"                   /*���׻���*/
#define XMLNM_PABYBH_CHECKCTL_TRANSOPER                  "/pabybh/checkctl/transoper"                  /*���׹�Ա*/
#define XMLNM_PABYBH_CHECKCTL_RESPCODE                   "/pabybh/checkctl/respcode"                   /*��Ӧ��*/
#define XMLNM_PABYBH_CHECKCTL_RESPMSG                    "/pabybh/checkctl/respmsg"                    /*��Ӧ��Ϣ*/
#define XMLNM_PABYBH_CHECKCTL_STAT                       "/pabybh/checkctl/stat"                       /*����״̬0�ɹ�1ʧ��6״̬δ֪7������8������9��ʼ*/
#define XMLNM_PABYBH_CHECKCTL_EXTFLD1                    "/pabybh/checkctl/extfld1"                    /*�����ֶ�1*/
#define XMLNM_PABYBH_CHECKCTL_EXTFLD2                    "/pabybh/checkctl/extfld2"                    /*�����ֶ�2*/
#define XMLNM_PABYBH_CHECKCTL_EXTFLD3                    "/pabybh/checkctl/extfld3"                    /*�����ֶ�3*/
/*END-------------*/

/*����ʽ������ϸ    BEGIN-------*/
#define XMLNM_PABYBH_DEPCHKINFO_CHECKDATE         "/pabybh/depchkinfo/checkdate"          /*��������*/
#define XMLNM_PABYBH_DEPCHKINFO_TRANSDATE         "/pabybh/depchkinfo/transdate"          /*��������*/
#define XMLNM_PABYBH_DEPCHKINFO_TRANSTIME         "/pabybh/depchkinfo/transtime"          /*����ʱ��*/
#define XMLNM_PABYBH_DEPCHKINFO_TRANSFERTYPE      "/pabybh/depchkinfo/transfertype"       /*�ʽ�����'0--��ת֤1--֤ת��'*/
#define XMLNM_PABYBH_DEPCHKINFO_ACCTNO            "/pabybh/depchkinfo/acctno"             /*�����˺�*/
#define XMLNM_PABYBH_DEPCHKINFO_STOCKCODE         "/pabybh/depchkinfo/stockcode"          /*ȯ�̴���*/
#define XMLNM_PABYBH_DEPCHKINFO_CAPITALACCTNO     "/pabybh/depchkinfo/capitalacctno"      /*֤ȯ�ʽ�̨�˺�*/
#define XMLNM_PABYBH_DEPCHKINFO_AMT               "/pabybh/depchkinfo/amt"                /*���*/
#define XMLNM_PABYBH_DEPCHKINFO_WORKSERIALNO      "/pabybh/depchkinfo/workserialno"       /*��������ˮ��*/
#define XMLNM_PABYBH_DEPCHKINFO_IEPSERIALNO       "/pabybh/depchkinfo/iepserialno"        /*��Eͨ��ˮ��*/
#define XMLNM_PABYBH_DEPCHKINFO_COBANKNO          "/pabybh/depchkinfo/cobankno"           /*�����к�*/
#define XMLNM_PABYBH_DEPCHKINFO_EXTFLD1           "/pabybh/depchkinfo/extfld1"            /*�����ֶ�1*/
#define XMLNM_PABYBH_DEPCHKINFO_EXTFLD2           "/pabybh/depchkinfo/extfld2"            /*�����ֶ�2*/
/*END----------*/

/*�ʽ���˲�ƽ��ϸ    BEGIN-------*/
#define XMLNM_PABYBH_NOTBAL_CHECKDATE           "/pabybh/notbal/checkdate"               /*��������*/
#define XMLNM_PABYBH_NOTBAL_COBANKNO            "/pabybh/notbal/cobankno"                /*�����к�*/
#define XMLNM_PABYBH_NOTBAL_TRANSFERTYPE        "/pabybh/notbal/transfertype"            /*�ʽ�����'0--������ת֤1--֤ת�������'*/
#define XMLNM_PABYBH_NOTBAL_STOCKCODE           "/pabybh/notbal/stockcode"               /*ȯ�̴���*/
#define XMLNM_PABYBH_NOTBAL_CAPITALACCTNO       "/pabybh/notbal/capitalacctno"           /*֤ȯ�ʽ�̨�˺�*/
#define XMLNM_PABYBH_NOTBAL_WORKSERIALNO        "/pabybh/notbal/workserialno"            /*��������ˮ��*/
#define XMLNM_PABYBH_NOTBAL_BANKSTAT            "/pabybh/notbal/bankstat"                /*������״̬*/
#define XMLNM_PABYBH_NOTBAL_BANKACCTNO          "/pabybh/notbal/bankacctno"              /*ƽ̨�����˺�*/
#define XMLNM_PABYBH_NOTBAL_BANKAMT             "/pabybh/notbal/bankamt"                 /*ƽ̨���׽��*/
#define XMLNM_PABYBH_NOTBAL_BANKTRANSCODE				"/pabybh/notbal/banktranscode"           /*ƽ̨���״���*/
#define XMLNM_PABYBH_NOTBAL_IEPSERIALNO         "/pabybh/notbal/iepserialno"             /*��Eͨ��ˮ��*/
#define XMLNM_PABYBH_NOTBAL_IEPSTAT             "/pabybh/notbal/iepstat"                 /*��Eͨ״̬*/
#define XMLNM_PABYBH_NOTBAL_IEPACCTNO           "/pabybh/notbal/iepacctno"               /*��Eͨ�����˺�*/
#define XMLNM_PABYBH_NOTBAL_IEPAMT              "/pabybh/notbal/iepamt"                  /*��Eͨ���׽��*/
#define XMLNM_PABYBH_NOTBAL_IEPTRANSCODE				"/pabybh/notbal/ieptranscode"            /*��Eͨ���״���*/
#define XMLNM_PABYBH_NOTBAL_HOSTSERIALNO        "/pabybh/notbal/hostserialno"            /*������ˮ��*/
#define XMLNM_PABYBH_NOTBAL_HOSTSTAT            "/pabybh/notbal/hoststat"                /*����״̬*/
#define XMLNM_PABYBH_NOTBAL_HOSTACCTNO          "/pabybh/notbal/hostacctno"              /*���������˺�*/
#define XMLNM_PABYBH_NOTBAL_HOSTAMT             "/pabybh/notbal/hostamt"                 /*�������׽��*/
#define XMLNM_PABYBH_NOTBAL_HOSTTRANSCODE				"/pabybh/notbal/hosttranscode"           /*�������״���*/
#define XMLNM_PABYBH_NOTBAL_CHECKSTAT           "/pabybh/notbal/checkstat"               /*���˽����־,0-δ����1-�Ѷ�ƽ2-ƽ����3-���Ķ�*/
#define XMLNM_PABYBH_NOTBAL_ADJUSTSTAT          "/pabybh/notbal/adjuststat"              /*����״̬0-�ɹ�1-ʧ��7-��ʱ9-��ʼ*/
#define XMLNM_PABYBH_NOTBAL_ADJUSTTRANSORG      "/pabybh/notbal/adjusttransorg"          /*���˽��׻���*/
#define XMLNM_PABYBH_NOTBAL_ADJUSTTRANSOPER     "/pabybh/notbal/adjusttransoper"         /*���˽��׹�Ա*/
#define XMLNM_PABYBH_NOTBAL_ADJUSTDATE          "/pabybh/notbal/adjustdate"              /*��������*/
#define XMLNM_PABYBH_NOTBAL_ADJUSTSERIALNO      "/pabybh/notbal/adjustserialno"          /*����ҵ����ˮ��*/
#define XMLNM_PABYBH_NOTBAL_ADJUSTHOSTBSIDATE   "/pabybh/notbal/adjusthostbsidate"       /*������������*/
#define XMLNM_PABYBH_NOTBAL_ADJUSTHOSTSERIALNO  "/pabybh/notbal/adjusthostserialno"      /*������ˮ��*/
#define XMLNM_PABYBH_NOTBAL_ADJUSTRESPCODE      "/pabybh/notbal/adjustrespcode"          /*������Ӧ��*/
#define XMLNM_PABYBH_NOTBAL_ADJUSTRESPMSG       "/pabybh/notbal/adjustrespmsg"           /*������Ӧ��Ϣ*/
#define XMLNM_PABYBH_NOTBAL_EXTFLD1             "/pabybh/notbal/extfld1"                 /*�����ֶ�1*/
#define XMLNM_PABYBH_NOTBAL_EXTFLD2             "/pabybh/notbal/extfld2"                 /*�����ֶ�2*/
/*END----------*/

/*����������ϸ    BEGIN-------*/
#define XMLNM_PABYBH_HOSCHKINFO_COBANKNO             "/pabybh/hoschkinfo/cobankno"                /*�����к�*/                            
#define XMLNM_PABYBH_HOSCHKINFO_CHECKDATE            "/pabybh/hoschkinfo/checkdate"               /*��������*/                            
#define XMLNM_PABYBH_HOSCHKINFO_WORKSERIALNO         "/pabybh/hoschkinfo/workserialno"            /*ƽ̨ҵ����ˮ��*/                      
#define XMLNM_PABYBH_HOSCHKINFO_HOSTDATE             "/pabybh/hoschkinfo/hostdate"                /*��������*/                            
#define XMLNM_PABYBH_HOSCHKINFO_HOSTSERIALNO         "/pabybh/hoschkinfo/hostserialno"            /*������ˮ��*/                          
#define XMLNM_PABYBH_HOSCHKINFO_HOSTTRANSCODE        "/pabybh/hoschkinfo/hosttranscode"           /*���Ľ��״���*/                        
#define XMLNM_PABYBH_HOSCHKINFO_ACCTNO               "/pabybh/hoschkinfo/acctno"                  /*�˺�*/                                
#define XMLNM_PABYBH_HOSCHKINFO_TRANSAMT             "/pabybh/hoschkinfo/transamt"                /*���׽��*/                            
#define XMLNM_PABYBH_HOSCHKINFO_TRANSFARE            "/pabybh/hoschkinfo/transfare"               /*������*/                              
#define XMLNM_PABYBH_HOSCHKINFO_CASHFLAG             "/pabybh/hoschkinfo/cashflag"                /*��ת��־1-�ֽ�2-ת��*/                
#define XMLNM_PABYBH_HOSCHKINFO_STAT                 "/pabybh/hoschkinfo/stat"                    /*��Ч��־0-����1-������2-������9-ʧ��*/
#define XMLNM_PABYBH_HOSCHKINFO_CDFLAG               "/pabybh/hoschkinfo/cdflag"                  /*�����־*/                            
#define XMLNM_PABYBH_HOSCHKINFO_SVRTYPE              "/pabybh/hoschkinfo/svrtype"                 /*ҵ������*/                            
#define XMLNM_PABYBH_HOSCHKINFO_REMARKCODE           "/pabybh/hoschkinfo/remarkcode"              /*ժҪ��*/                              
#define XMLNM_PABYBH_HOSCHKINFO_REMARK               "/pabybh/hoschkinfo/remark"                  /*ժҪ��Ϣ*/                            
#define XMLNM_PABYBH_HOSCHKINFO_TRANSBRANCHNO        "/pabybh/hoschkinfo/transbranchno"           /*��������*/                            
#define XMLNM_PABYBH_HOSCHKINFO_TRANSORG             "/pabybh/hoschkinfo/transorg"                /*���׻���*/                            
#define XMLNM_PABYBH_HOSCHKINFO_TRANSOPER            "/pabybh/hoschkinfo/transoper"               /*���׹�Ա*/                            
#define XMLNM_PABYBH_HOSCHKINFO_JOINCHKFLAG          "/pabybh/hoschkinfo/joinchkflag"             /*������˱�־��0-�����룬1-����*/      
#define XMLNM_PABYBH_HOSCHKINFO_EXTFLD1              "/pabybh/hoschkinfo/extfld1"                 /*�����ֶ�1*/                           
#define XMLNM_PABYBH_HOSCHKINFO_EXTFLD2              "/pabybh/hoschkinfo/extfld2"                 /*�����ֶ�2*/                           
#define XMLNM_PABYBH_HOSCHKINFO_EXTFLD3              "/pabybh/hoschkinfo/extfld3"                 /*�����ֶ�3*/                           
/*END----------*/

/*������Ϣ    */
#define XMLNM_APP_JYXX_JYDM          "/app/jyxx/jydm"              /*���״���*/
#define XMLNM_APP_JYXX_JYMC          "/app/jyxx/jymc"              /*��������*/
#define XMLNM_APP_JYXX_JYLX          "/app/jyxx/jylx"              /*�������� 0������ 1������ 9����*/
#define XMLNM_APP_JYXX_LSJLBZ        "/app/jyxx/lsjlbz"            /*��ˮ��¼��־ 0��¼ 1����¼*/
#define XMLNM_APP_JYXX_RZBZ          "/app/jyxx/rzbz"              /*���˱�־ 0���� 1������*/
#define XMLNM_APP_JYXX_BBBZ          "/app/jyxx/bbbz"              /*�����־ 0���� 1�Ǳ���*/
#define XMLNM_APP_JYXX_WHJG          "/app/jyxx/whjg"              /*ά������*/
#define XMLNM_APP_JYXX_WHGY          "/app/jyxx/whgy"              /*ά����Ա*/
#define XMLNM_APP_JYXX_WHSJ          "/app/jyxx/whsj"              /*ά��ʱ��*/
#define XMLNM_APP_JYXX_JYXE          "/app/jyxx/jyxe"              /*�����޶�*/
#define XMLNM_APP_JYXX_XEFS          "/app/jyxx/xefs"              /*�޶ʽ*/
#define XMLNM_APP_JYXX_EXTFLD1       "/app/jyxx/extfld1"           /*��չ�ֶ�1*/
#define XMLNM_APP_JYXX_EXTFLD2       "/app/jyxx/extfld2"           /*��չ�ֶ�2*/
#define XMLNM_APP_JYXX_QTBZ          "/app/jyxx/qtbz"              /*��ͣ��־ 0���� 1�ر�*/
/*END-----------*/

/*��������   */
#define XMLNM_PABYBH_PARACTL_FILESPLIT     "/pabybh/paractl/filesplit"    /*�ļ��ָ���*/
#define XMLNM_PABYBH_PARACTL_FILELINEFLAG  "/pabybh/paractl/filelineflag" /*�ļ���β�б�־*/   

#define XMLNM_PABYBH_PARACTL_SETTLEFUND    "/pabybh/paractl/settlefund"   /*���������ʽ�  0������ 1����*/
#define XMLNM_PABYBH_PARACTL_HOSTSIGN      "/pabybh/paractl/hostsign"     /*����ǩԼ�Ǽ� 0��ǩԼ 1ǩԼ�Ǽ�*/
#define XMLNM_PABYBH_PARACTL_HOSTCHE       "/pabybh/paractl/hostche"      /*������������ 0������ 1����*/
#define XMLNM_PABYBH_PARACTL_GETHOSTFILE   "/pabybh/paractl/gethostfile"  /*������ȡ���������ļ� 0������ 1����*/

#define XMLNM_PABYBH_PARACTL_FILEPATH      "/pabybh/paractl/filepath"     /*ƽ�����ٺ��ļ�Ŀ¼*/
#define XMLNM_PABYBH_PARACTL_PABCOMM       "/pabybh/paractl/pabcomm"      /*����ͨѶ��ʽ��1ͨ��GXP 2ֱ������*/

                                                                     
#define XMLNM_PABYBH_PARACTL_PABCHEFP      "/pabybh/paractl/pabchefp"    /*���Ķ����ļ�·��*/
#define XMLNM_PABYBH_PARACTL_HOSTCHEFP      "/pabybh/paractl/hostchefp"   /*���Ķ����ļ�·��*/

#define XMLNM_PABYBH_PARACTL_PABPARAFP   "/pabybh/paractl/pabparafp"  /*���Ĳ����ļ�·��*/
#define XMLNM_PABYBH_PARACTL_LOCPARAFP    "/pabybh/paractl/locparafp"  /*���ز����ļ�·��*/





/*���Ķ���    */
/*ƽ��������  /iep/req  /iep/resp*/

/*���ı���  */

/*����ƽ������  /pabfe/req   /pabfe/resp*/

#endif
