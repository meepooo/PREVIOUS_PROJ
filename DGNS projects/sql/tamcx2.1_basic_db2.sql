/*
�� Ҷ���� �� 2011-10-13 10:34:22 ����
 �����ɵĽű����ݿ⣺agtdb2
�ܹ���AGTDB2
����TABLE
*/

DROP INDEX I_T_USER;
DROP INDEX T_DATA_TYPE;
DROP INDEX I_T_DICT;
DROP INDEX I_T_IP;
DROP INDEX I_T_LOG;
DROP INDEX I_T_MENU_ID;
DROP INDEX T_MONITOR_2;
DROP INDEX I_MONITOR_1;
DROP INDEX I_T_PKGENERY;
DROP INDEX I_T_REPORT_ID;
DROP INDEX I_T_REPORT_CON;
DROP INDEX I_T_REPORT_Z;
DROP INDEX I_T_ROLE;
DROP INDEX I_T_ROLE_PREV;
DROP INDEX I_T_SEND_ID;
DROP INDEX I_T_SEND_COND_ID;
DROP INDEX I_T_SEND_RETURN_ID;
DROP INDEX I_T_T_SEND_SERVER;
DROP INDEX I_T_SUB_TRAN;
DROP INDEX I_SYS_PARAM;
DROP INDEX I_T_TRAN;
DROP INDEX I_T_USER_DATA;
DROP INDEX I_T_USER_TRAN;
DROP INDEX I_T_USER_ROLE;
DROP INDEX I_T_USER_ORG;
DROP INDEX I_ROLE_WAR;

DROP TABLE T_VERSION;
DROP TABLE T_USER;
DROP TABLE T_USER_WARRANT;
DROP TABLE T_USER_TRAN_ORG;
DROP TABLE T_USER_ROLE;
DROP TABLE T_USER_PURV;
DROP TABLE T_USER_DATA_TYPE;
DROP TABLE T_TRAN;
DROP TABLE T_TRAN_UI_INFO;
DROP TABLE T_TRAN_UI_ATTR;
DROP TABLE T_TRAN_REG;
DROP TABLE T_SYS_PARAM;
DROP TABLE T_SUB_TRAN;
DROP TABLE T_SENDINFO;
DROP TABLE T_SEND_SERVER;
DROP TABLE T_SEND_RETURN;
DROP TABLE T_SEND_LOG;
DROP TABLE T_SEND_COND;
DROP TABLE T_ROLE;
DROP TABLE T_ROLE_PURV;
DROP TABLE T_REPORT;
DROP TABLE T_REPORT_COND;
DROP TABLE T_PKGENETORY;
DROP TABLE T_ORG;
DROP TABLE T_MONITOR_MAIN;
DROP TABLE T_MONITOR_DETAL;
DROP TABLE T_MENU;
DROP TABLE T_LOG;
DROP TABLE T_IP;
DROP TABLE T_EXT_UI_REG;
DROP TABLE T_DICT;
DROP TABLE T_DB_TRAN_REG;
DROP TABLE T_DB_TRAN_LIST;
DROP TABLE T_DATA_TYPE;
DROP TABLE T_APP_REG;
DROP TABLE T_APP_CONST;
DROP TABLE T_SENDIMPT;
DROP TABLE T_TEMP;

CREATE TABLE T_APP_CONST ( 
	APP_ID   	CHARACTER(10) NOT NULL,
	EXT_ID   	CHARACTER(30) NOT NULL,
	EXT_DESC 	CHARACTER(100),
	EXT_VALUE	VARCHAR(1024) NOT NULL,
	BAK1     	CHARACTER(30),
	BAK2     	CHARACTER(60),
	BAK3     	CHARACTER(120),
	CONSTRAINT PK_T_APP_CONST PRIMARY KEY(APP_ID,EXT_ID)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;
CREATE TABLE T_APP_REG
(
  APP_ID   CHARACTER(20) not null,
  APP_NAME CHARACTER(50) not null,
  BAK      CHARACTER(60),
  CONSTRAINT PK_T_APP_REG PRIMARY KEY(APP_ID)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;
CREATE TABLE T_DATA_TYPE ( 
	DATA_TYPE	CHARACTER(20) NOT NULL,
	TYPE_NAME	CHARACTER(30) NOT NULL,
	VERSION  	CHARACTER(10),
	BAK      	CHARACTER(30) 
	) IN GAPS_DATA INDEX IN GAPS_INDEX ;
CREATE TABLE T_DB_TRAN_LIST ( 
	APP_ID     	CHARACTER(10) NOT NULL,
	TRAN_ID    	CHARACTER(30) NOT NULL,
	FIELD_ID   	CHARACTER(30) NOT NULL,
	FIELD_NAME 	CHARACTER(30) NOT NULL,
	STATE      	CHARACTER(1) NOT NULL,
	DATA_TYPE  	CHARACTER(30) NOT NULL,
	UI_TYPE    	CHARACTER(30) NOT NULL,
	ALLOW_BLANK	CHARACTER(1) NOT NULL,
	IS_KEY     	CHARACTER(1) NOT NULL,
	SEARCH_TYPE	CHARACTER(10) NOT NULL,
	SEARCH_EXTS	VARCHAR(255),
	EDITABLE   	CHARACTER(1) NOT NULL,
	MIN_LENGTH 	INTEGER NOT NULL,
	MAX_LENGTH 	INTEGER NOT NULL,
	DEF_VALUE  	VARCHAR(255) NOT NULL,
	ORDER_ID   	INTEGER,
	EXT1       	CHARACTER(30),
	EXT2       	CHARACTER(60),
	EXT3       	CHARACTER(90),
	CONSTRAINT PK_T_DB_TRAN_LIST PRIMARY KEY(APP_ID,TRAN_ID,FIELD_ID)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;
CREATE TABLE T_DB_TRAN_REG ( 
	APP_ID      	CHARACTER(10) NOT NULL,
	TRAN_ID     	CHARACTER(20) NOT NULL,
	TRAN_DESC   	CHARACTER(100),
	WHERE_CTRL  	VARCHAR(255),
	ORDER_CTRL  	CHARACTER(50),
	GROUP_CTRL  	CHARACTER(50),
	TABLE_ID    	CHARACTER(30) NOT NULL,
	TABLE_NAME  	CHARACTER(30),
	DATA_SOURCE 	CHARACTER(10) NOT NULL,
	MAIN_CONTROL	CHARACTER(50) NOT NULL,
	SELECT_ABLE 	CHARACTER(1) NOT NULL,
	INSERT_ABLE 	CHARACTER(1) NOT NULL,
	UPDATE_ABLE 	CHARACTER(1) NOT NULL,
	DELETE_ABLE 	CHARACTER(1) NOT NULL,
	PLUGINS     	VARCHAR(255),
	EXT1        	CHARACTER(30),
	EXT2        	CHARACTER(60),
	EXT3        	CHARACTER(90),
	CONSTRAINT PK_T_DB_TRAN_REG PRIMARY KEY(APP_ID,TRAN_ID)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;
CREATE TABLE T_DICT ( 
	DICT_KIND	CHARACTER(30) NOT NULL,
	DICT_NAME	CHARACTER(30) NOT NULL,
	DICT_KEY 	CHARACTER(30) NOT NULL,
	DICT_INFO	CHARACTER(30) NOT NULL,
	VERSION  	CHARACTER(10),
	BAK      	CHARACTER(30) 
	) IN GAPS_DATA INDEX IN GAPS_INDEX ;
CREATE TABLE T_EXT_UI_REG ( 
	UI_ID      	CHARACTER(30) NOT NULL,
	XTYPE      	CHARACTER(30) NOT NULL,
	UI_NAME    	CHARACTER(50) NOT NULL,
	UI_DESC    	VARCHAR(255) NOT NULL,
	UI_TYPE    	CHARACTER(1) NOT NULL,
	UI_RESOURCE	CHARACTER(100) NOT NULL,
	UI_CLASS   	CHARACTER(50),
	EXT1       	CHARACTER(30),
	EXT2       	CHARACTER(60),
	EXT3       	CHARACTER(90),
	CONSTRAINT PK_T_EXT_UI_REG PRIMARY KEY(UI_ID)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;
CREATE TABLE T_IP ( 
	IP     	CHARACTER(20) NOT NULL,
	IP_DESC	CHARACTER(30),
	BAK    	CHARACTER(30),
	CONSTRAINT PK_T_IP PRIMARY KEY(IP)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;
CREATE TABLE T_LOG ( 
	TRAN_DATE    	CHARACTER(8) NOT NULL,
	SERIAL_NO    	CHARACTER(20) NOT NULL,
	TRAN_TIME    	CHARACTER(6) NOT NULL,
	TRAN_CODE    	CHARACTER(20) NOT NULL,
	TRAN_NAME    	CHARACTER(30) NOT NULL,
	SUB_TRAN_CODE	CHARACTER(20) NOT NULL,
	SUB_TRAN_NAME	CHARACTER(30) NOT NULL,
	ORG_ID       	CHARACTER(10),
	USER_ID      	CHARACTER(15),
	LOG_CONTENT  	CHARACTER(100),
	TRAN_TYPE    	CHARACTER(1),
	BAK1         	CHARACTER(30),
	BAK2         	CHARACTER(30) 
	) IN GAPS_DATA INDEX IN GAPS_INDEX ;
CREATE TABLE T_MENU ( 
	MENU_ID      	CHARACTER(30) NOT NULL,
	ABOVE_MENU_ID	CHARACTER(30) NOT NULL,
	MENU_DEEP    	INTEGER NOT NULL,
	MENU_NAME    	CHARACTER(30) NOT NULL,
	MENU_DESC    	CHARACTER(50) NOT NULL,
	IS_RUN_MENU  	CHARACTER(1) NOT NULL,
	TRAN_CODE    	CHARACTER(20),
	IS_ENABLE    	CHARACTER(1),
	VERSION      	CHARACTER(10),
	REPORT_ID    	CHARACTER(40),
	ORDER_ID     	CHARACTER(20) NOT NULL,
	MENU_TYPE    	CHARACTER(1) NOT NULL,
	SYSTEM_ID    	CHARACTER(10) NOT NULL,
	BAK1         	CHARACTER(30),
	BAK2         	CHARACTER(100),
	BAK3         	CHARACTER(100) 
	) IN GAPS_DATA INDEX IN GAPS_INDEX ;
CREATE TABLE T_MONITOR_DETAL ( 
	ID           	CHARACTER(16) NOT NULL,
	FIELD_EN_NAME	CHARACTER(20) NOT NULL,
	FIELD_CH_NAME	CHARACTER(50) NOT NULL,
	DATA_TYPE    	CHARACTER(20) NOT NULL,
	IS_FORMAT    	CHARACTER(1),
	TABLE_NAME   	CHARACTER(30) NOT NULL,
	VERSION      	CHARACTER(10) 
	) IN GAPS_DATA INDEX IN GAPS_INDEX ;
CREATE TABLE T_MONITOR_MAIN ( 
	TABLE_NAME	CHARACTER(30) NOT NULL,
	TITLE     	CHARACTER(50) NOT NULL,
	CONDITION 	CHARACTER(100),
	VERSION   	CHARACTER(10) 
	) IN GAPS_DATA INDEX IN GAPS_INDEX ;
CREATE TABLE T_ORG ( 
	ORG_ID      	CHARACTER(16) NOT NULL,
	ORG_NAME    	CHARACTER(50) NOT NULL,
	ORG_DESC    	CHARACTER(60),
	ORG_TYPE    	CHARACTER(1),
	ORG_LEVEL   	CHARACTER(1) NOT NULL,
	ABOVE_ORG_ID	CHARACTER(16) NOT NULL,
	INNER_ORG_ID	CHARACTER(27) NOT NULL,
	TEL         	CHARACTER(32),
	EMAIL       	CHARACTER(50),
	ORG_ADRESS  	CHARACTER(120),
	BAK1        	CHARACTER(30),
	BAK2        	CHARACTER(60),
	BAK3        	CHARACTER(120),
	CONSTRAINT PK_T_ORG PRIMARY KEY(ORG_ID)
)
;
COMMENT ON TABLE T_ORG IS '����Ǽ�ϵͳ�ڻ�����Ϣ��ͨ�����ڻ�������μ�ҵ���ϵͳ�������Ϣ��'
;
COMMENT ON COLUMN T_ORG.ORG_ID IS '������'
;
COMMENT ON COLUMN T_ORG.ORG_NAME IS '�������'
;
COMMENT ON COLUMN T_ORG.ORG_DESC IS '��������'
;
COMMENT ON COLUMN T_ORG.ABOVE_ORG_ID IS '�ϼ�������'
;
COMMENT ON COLUMN T_ORG.INNER_ORG_ID IS '���ڹ���̨���а��������в�ѯ��ͳ��
���Բ���   Ϊtamc�ṩ����'
;
COMMENT ON COLUMN T_ORG.ORG_LEVEL IS '0-������������
1��һ������
2����������
3��֧��
4������
5����������'
;
COMMENT ON COLUMN T_ORG.ORG_ADRESS IS '��ϵ��ַ'
;
COMMENT ON COLUMN T_ORG.ORG_TYPE IS '���Բ���   Ϊtamc�ṩ����'
;
COMMENT ON COLUMN T_ORG.TEL IS '��ϵ�绰'
;
COMMENT ON COLUMN T_ORG.EMAIL IS '��������'
;
COMMENT ON COLUMN T_ORG.BAK1 IS '���ֶο���������������Ա'
;
COMMENT ON COLUMN T_ORG.BAK2 IS '����2'
;
COMMENT ON COLUMN T_ORG.BAK3 IS '����3';
CREATE TABLE T_PKGENETORY ( 
	SECEND	INTEGER NOT NULL 
	) IN GAPS_DATA INDEX IN GAPS_INDEX ;
CREATE TABLE T_REPORT_COND ( 
	COND_ID   	CHARACTER(30) NOT NULL,
	REPORT_ID 	CHARACTER(30) NOT NULL,
	COND_NAME 	CHARACTER(50) NOT NULL,
	COND_TYPE 	CHARACTER(1) NOT NULL,
	IS_NULL   	CHARACTER(1) NOT NULL,
	ORDER_ID  	INTEGER NOT NULL,
	COND_VALUE	VARCHAR(300),
	VERSION   	CHARACTER(20),
	NOTE      	CHARACTER(50),
	BAK1      	CHARACTER(30),
	BAK2      	CHARACTER(30),
	BAK3      	CHARACTER(30) 
	) IN GAPS_DATA INDEX IN GAPS_INDEX ;
CREATE TABLE T_REPORT ( 
	REPORT_ID  	CHARACTER(20) NOT NULL,
	REPORT_NAME	CHARACTER(30) NOT NULL,
	REPORT_TYPE	CHARACTER(1) NOT NULL,
	REPORT_PATH	CHARACTER(200) NOT NULL,
	MAX_NUMBER 	INTEGER,
	PROC       	CHARACTER(30),
	VERSION    	CHARACTER(10),
	NOTE       	CHARACTER(100),
	BAK1       	CHARACTER(30),
	BAK2       	CHARACTER(30),
	BAK3       	CHARACTER(30) 
	) IN GAPS_DATA INDEX IN GAPS_INDEX ;
CREATE TABLE T_ROLE_PURV ( 
	ROLE_ID      	CHARACTER(15) NOT NULL,
	MENU_ID      	CHARACTER(30) NOT NULL,
	TRAN_CODE    	CHARACTER(20) NOT NULL,
	SUB_TRAN_CODE	CHARACTER(20) NOT NULL,
	BAK1         	CHARACTER(30) 
	) IN GAPS_DATA INDEX IN GAPS_INDEX ;
CREATE TABLE T_ROLE ( 
	ROLE_ID  	CHARACTER(15) NOT NULL,
	ROLE_NAME	CHARACTER(20) NOT NULL,
	ROLE_DESC	CHARACTER(30),
	BAK1     	CHARACTER(30),
	BAK2     	CHARACTER(30),
	BAK3     	CHARACTER(30) 
	) IN GAPS_DATA INDEX IN GAPS_INDEX ;
CREATE TABLE T_SEND_COND ( 
	ID            	INTEGER NOT NULL,
	SEND_COND_ID  	CHARACTER(20) NOT NULL,
	SEND_COND_NAME	CHARACTER(30) NOT NULL,
	SEND_COND_TYPE	CHARACTER(1) NOT NULL,
	ORDER_ID      	CHARACTER(2) NOT NULL,
	IS_NULL       	CHARACTER(1) NOT NULL,
	SEND_ON       	CHARACTER(100),
	SEND_DIV      	CHARACTER(20),
	COND_INFO     	CHARACTER(100),
	VERSION       	CHARACTER(10),
	NOTE          	CHARACTER(100),
	BAK1          	CHARACTER(30),
	BAK2          	CHARACTER(30),
	BAK3          	CHARACTER(30),
	BAK4          	CHARACTER(30),
	BAK5          	CHARACTER(30),
	BAK6          	CHARACTER(30) 
	) IN GAPS_DATA INDEX IN GAPS_INDEX ;
CREATE TABLE T_SEND_LOG ( 
	JYRQ      	CHARACTER(8),
	JYSJ      	CHARACTER(6),
	JYDM      	CHARACTER(50),
	JYMC      	CHARACTER(60),
	USERID    	CHARACTER(15),
	ORGID     	CHARACTER(10),
	INNERORGID	CHARACTER(27),
	FSINFO    	VARCHAR(1024),
	JSINFO    	VARCHAR(1024),
	RESPCODE  	CHARACTER(20),
	RESPMSG   	CHARACTER(200),
	BAK1      	CHARACTER(200),
	BAK2      	CHARACTER(200),
	BAK3      	CHARACTER(200),
	BAK4      	CHARACTER(100),
	BAK5      	CHARACTER(200) 
	) IN GAPS_DATA INDEX IN GAPS_INDEX ;
CREATE TABLE T_SEND_RETURN ( 
	ID         	INTEGER NOT NULL,
	RETURN_ID  	CHARACTER(20) NOT NULL,
	RETURN_NAME	CHARACTER(30) NOT NULL,
	ORDER_ID   	CHARACTER(2) NOT NULL,
	VALUE_TYPE 	CHARACTER(1),
	FILE_EXT   	CHARACTER(10),
	SUPER_PATH 	CHARACTER(20),
	RET_TYPE   	CHARACTER(1),
	DICT       	CHARACTER(180),
	VERSION    	CHARACTER(10),
	NOTE       	CHARACTER(100),
	BAK1       	CHARACTER(30),
	BAK2       	CHARACTER(30),
	BAK3       	CHARACTER(30),
	BAK4       	CHARACTER(30),
	BAK5       	CHARACTER(30),
	BAK6       	CHARACTER(30) 
	) IN GAPS_DATA INDEX IN GAPS_INDEX ;
CREATE TABLE T_SEND_SERVER ( 
	ID     	CHARACTER(30) NOT NULL,
	SERNAME	CHARACTER(50) NOT NULL,
	IP     	CHARACTER(20) NOT NULL,
	PORT   	INTEGER NOT NULL,
	TYPEID 	CHARACTER(1) NOT NULL,
	CSTIME 	INTEGER NOT NULL 
	) IN GAPS_DATA INDEX IN GAPS_INDEX ;
CREATE TABLE T_SENDINFO ( 
	ID         	INTEGER NOT NULL,
	SEND_ID    	CHARACTER(30) NOT NULL,
	SEND_NAME  	CHARACTER(50) NOT NULL,
	SEND_TYPE  	CHARACTER(1) NOT NULL,
	LSTSUPER   	CHARACTER(20),
	USERID     	CHARACTER(20),
	ORGID      	CHARACTER(20),
	INNERORGID 	CHARACTER(20),
	VERSION    	CHARACTER(10),
	NOTE       	VARCHAR(1024),
	COMMUNICATE	CHARACTER(30),
	DATASVR    	CHARACTER(30),
	BAK1       	CHARACTER(150),
	BAK2       	CHARACTER(150),
	BAK3       	CHARACTER(30),
	BAK4       	CHARACTER(30),
	BAK5       	CHARACTER(30),
	BAK6       	CHARACTER(30) 
	) IN GAPS_DATA INDEX IN GAPS_INDEX ;
CREATE TABLE T_SUB_TRAN ( 
	TRAN_CODE    	CHARACTER(20) NOT NULL,
	SUB_TRAN_CODE	CHARACTER(20) NOT NULL,
	SUB_TRAN_NAME	CHARACTER(30) NOT NULL,
	REPAGE       	CHARACTER(100) NOT NULL,
	SUB_TRAN_DESC	CHARACTER(50),
	VERSION      	CHARACTER(10),
	BAK1         	CHARACTER(30),
	BAK2         	CHARACTER(30),
	BAK3         	CHARACTER(30) 
	) IN GAPS_DATA INDEX IN GAPS_INDEX ;
CREATE TABLE T_SYS_PARAM ( 
	PARAM_ID   	CHARACTER(20) NOT NULL,
	PARAM_NAME 	CHARACTER(30) NOT NULL,
	PARAM_VALUE	CHARACTER(128) NOT NULL,
	PARAM_TYPE 	CHARACTER(1) NOT NULL,
	VERSION    	CHARACTER(10),
	BAK        	CHARACTER(30) 
	) IN GAPS_DATA INDEX IN GAPS_INDEX ;
CREATE TABLE T_TRAN_REG ( 
	APP_ID      	CHARACTER(10) NOT NULL,
	TRAN_ID     	CHARACTER(20) NOT NULL,
	TRAN_NAME   	CHARACTER(50) NOT NULL,
	TRAN_DESC   	CHARACTER(100),
	TRAN_TYPE   	CHARACTER(1) NOT NULL,
	IS_DISABLED 	CHARACTER(1),
	REG_DATE    	CHARACTER(8),
	REG_TIME    	CHARACTER(6),
	TRAN_VERSION	CHARACTER(20),
	BAK1        	CHARACTER(30),
	BAK2        	CHARACTER(60),
	BAK3        	CHARACTER(120),
	CONSTRAINT PK_T_TRAN_REG PRIMARY KEY(APP_ID,TRAN_ID)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;
CREATE TABLE T_TRAN_UI_ATTR ( 
	APP_ID    	CHARACTER(10) NOT NULL,
	TRAN_ID   	CHARACTER(20) NOT NULL,
	NODE_ID   	CHARACTER(30) NOT NULL,
	ATTR_ID   	CHARACTER(30) NOT NULL,
	ATTR_TYPE 	CHARACTER(2),
	ATTR_VALUE	VARCHAR(1024) NOT NULL,
	BAK1      	CHARACTER(30),
	BAK2      	CHARACTER(60),
	BAK3      	CHARACTER(120),
	ORDER_ID  	CHARACTER(3),
	CONSTRAINT PK_T_TRAN_UI_ATTR PRIMARY KEY(APP_ID,TRAN_ID,NODE_ID,ATTR_ID)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;
CREATE TABLE T_TRAN_UI_INFO ( 
	APP_ID    	CHARACTER(10) NOT NULL,
	TRAN_ID   	CHARACTER(20) NOT NULL,
	NODE_ID   	CHARACTER(30) NOT NULL,
	NODE_NAME 	CHARACTER(50) NOT NULL,
	NODE_TYPE 	CHARACTER(2),
	NODE_UI   	CHARACTER(40),
	IS_RUNTIME	CHARACTER(1),
	NODE_VALUE	VARCHAR(255),
	BAK1      	CHARACTER(30),
	BAK2      	CHARACTER(60),
	BAK3      	CHARACTER(120),
	CONSTRAINT PK_T_TRAN_UI_INFO PRIMARY KEY(APP_ID,TRAN_ID,NODE_ID)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;
CREATE TABLE T_TRAN ( 
	TRAN_CODE 	CHARACTER(20) NOT NULL,
	TRAN_NAME 	CHARACTER(30) NOT NULL,
	TRAN_TYPE 	CHARACTER(1) NOT NULL,
	TRAN_CLASS	CHARACTER(100) NOT NULL,
	VERSION   	CHARACTER(10),
	BAK1      	CHARACTER(30),
	BAK2      	CHARACTER(30),
	BAK3      	CHARACTER(30) 
	) IN GAPS_DATA INDEX IN GAPS_INDEX ;
CREATE TABLE T_USER_DATA_TYPE ( 
	USER_ID  	CHARACTER(15) NOT NULL,
	DATA_TYPE	CHARACTER(20) NOT NULL 
	) IN GAPS_DATA INDEX IN GAPS_INDEX ;
CREATE TABLE T_USER_PURV ( 
	USER_ID      	CHARACTER(15) NOT NULL,
	MENU_ID      	CHARACTER(30) NOT NULL,
	TRAN_CODE    	CHARACTER(20) NOT NULL,
	SUB_TRAN_CODE	CHARACTER(20) NOT NULL,
	BAK1         	CHARACTER(80) 
	) IN GAPS_DATA INDEX IN GAPS_INDEX ;
CREATE TABLE T_USER_ROLE ( 
	USER_ID	CHARACTER(15) NOT NULL,
	ROLE_ID	CHARACTER(15) NOT NULL,
	BAK    	CHARACTER(30) 
	) IN GAPS_DATA INDEX IN GAPS_INDEX ;
CREATE TABLE T_USER_TRAN_ORG ( 
	USER_ID	CHARACTER(15) NOT NULL,
	ORG_ID 	CHARACTER(10) NOT NULL 
	) IN GAPS_DATA INDEX IN GAPS_INDEX ;
CREATE TABLE T_USER_WARRANT ( 
	USER_ID	CHARACTER(15),
	ROLE_ID	CHARACTER(15) 
	) IN GAPS_DATA INDEX IN GAPS_INDEX ;
CREATE TABLE T_USER ( 
	USER_ID   	CHARACTER(15) NOT NULL,
	USER_NAME 	CHARACTER(20) NOT NULL,
	ORG_ID    	CHARACTER(10) NOT NULL,
	PASSWD    	CHARACTER(32) NOT NULL,
	OLD_PASSWD	CHARACTER(32),
	STATION   	CHARACTER(6) NOT NULL,
	CREAT_DATE	CHARACTER(8) NOT NULL,
	CREAT_TIME	CHARACTER(6) NOT NULL,
	ALTER_DATE	CHARACTER(8),
	ALTER_TIME	CHARACTER(6),
	DEL_DATE  	CHARACTER(8),
	TEL       	CHARACTER(25),
	EMAIL     	CHARACTER(50),
	STATUS    	CHARACTER(1) NOT NULL,
	SEX       	CHARACTER(1),
	ACADEMIC  	CHARACTER(2),
	CERTI_TYPE	CHARACTER(2),
	CERTI     	CHARACTER(30),
	FAX       	CHARACTER(20),
	ADRESS    	CHARACTER(50),
	POSTCODE  	CHARACTER(30),
	BAK1      	CHARACTER(30),
	BAK2      	CHARACTER(30),
	BAK3      	CHARACTER(30),
	BAK4      	CHARACTER(30),
	BAK5      	CHARACTER(30) 
	)
;
COMMENT ON TABLE T_USER IS '�û���Ϣ��'
;
COMMENT ON COLUMN T_USER.USER_ID IS '����'
;
COMMENT ON COLUMN T_USER.STATION IS 'ȡ���ֵ��:station'
;
COMMENT ON COLUMN T_USER.CREAT_DATE IS 'yyyyMMdd'
;
COMMENT ON COLUMN T_USER.CREAT_TIME IS 'HHmmss'
;
COMMENT ON COLUMN T_USER.ALTER_DATE IS 'yyyyMMdd'
;
COMMENT ON COLUMN T_USER.ALTER_TIME IS 'HHmmss'
;
COMMENT ON COLUMN T_USER.DEL_DATE IS 'yyyyMMdd'
;
COMMENT ON COLUMN T_USER.STATUS IS '0:���� 1:���� 2:�ѵ�¼ 9:ע��';
CREATE TABLE T_VERSION ( 
	APP_ID    	CHARACTER(30) NOT NULL,
	APP_NAME  	CHARACTER(60) NOT NULL,
	VERSION_ID	CHARACTER(20) NOT NULL,
	REGUSER   	CHARACTER(20) NOT NULL,
	REGDATE   	CHARACTER(8) NOT NULL,
	BAK1      	CHARACTER(60),
	BAK2      	CHARACTER(60),
	BAK3      	CHARACTER(60),
	BAK4      	CHARACTER(60),
	BAK5      	CHARACTER(60),
	CONSTRAINT PK_T_VERSION PRIMARY KEY(APP_ID)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;
CREATE TABLE T_SENDIMPT ( 
    APP_ID     	CHARACTER(30) NOT NULL,
    ISEND_CLASS	CHARACTER(254) NOT NULL,
    BAK1       	CHARACTER(200),
    BAK2       	CHARACTER(200),
    BAK3       	CHARACTER(200),
    BAK4       	CHARACTER(200),
    BAK5       	CHARACTER(200),
    CONSTRAINT PK_T_SENDIMPT PRIMARY KEY(APP_ID)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;

CREATE TABLE T_TEMP
(
  XX CHARACTER(20)
) IN GAPS_DATA INDEX IN GAPS_INDEX ;


CREATE UNIQUE INDEX T_DATA_TYPE ON T_DATA_TYPE (DATA_TYPE);
CREATE UNIQUE INDEX I_T_DICT ON T_DICT (DICT_KIND,DICT_KEY);
CREATE UNIQUE INDEX I_T_IP ON T_IP (IP);
CREATE UNIQUE INDEX I_T_LOG ON T_LOG (TRAN_DATE,SERIAL_NO);
CREATE UNIQUE INDEX I_T_MENU_ID ON T_MENU (MENU_ID);
CREATE UNIQUE INDEX T_MONITOR_2 ON T_MONITOR_DETAL (ID);
CREATE UNIQUE INDEX I_MONITOR_1 ON T_MONITOR_MAIN (TABLE_NAME);
CREATE UNIQUE INDEX I_T_PKGENERY ON T_PKGENETORY (SECEND);
CREATE UNIQUE INDEX I_T_REPORT_ID ON T_REPORT (REPORT_ID);
CREATE UNIQUE INDEX I_T_REPORT_CON ON T_REPORT_COND (REPORT_ID,COND_ID);
CREATE UNIQUE INDEX I_T_ROLE ON T_ROLE (ROLE_ID);
CREATE UNIQUE INDEX I_T_ROLE_PREV ON T_ROLE_PURV (ROLE_ID,MENU_ID,TRAN_CODE,SUB_TRAN_CODE);
CREATE UNIQUE INDEX I_T_SEND_ID ON T_SENDINFO (ID);
CREATE UNIQUE INDEX I_T_SEND_COND_ID ON T_SEND_COND (SEND_COND_ID,ID);
CREATE UNIQUE INDEX I_T_SEND_RETURN_ID ON T_SEND_RETURN (RETURN_ID,RET_TYPE,ID);
CREATE UNIQUE INDEX I_T_T_SEND_SERVER ON T_SEND_SERVER (ID);
CREATE UNIQUE INDEX I_T_SUB_TRAN ON T_SUB_TRAN (SUB_TRAN_CODE,TRAN_CODE);
CREATE UNIQUE INDEX I_SYS_PARAM ON T_SYS_PARAM (PARAM_ID);
CREATE UNIQUE INDEX I_T_TRAN ON T_TRAN (TRAN_CODE);
CREATE UNIQUE INDEX I_T_USER ON T_USER (USER_ID DESC);
CREATE UNIQUE INDEX I_T_USER_DATA ON T_USER_DATA_TYPE (USER_ID,DATA_TYPE);
CREATE UNIQUE INDEX I_T_USER_TRAN ON T_USER_PURV (USER_ID,MENU_ID,TRAN_CODE,SUB_TRAN_CODE);
CREATE UNIQUE INDEX I_T_USER_ROLE ON T_USER_ROLE (USER_ID,ROLE_ID);
CREATE UNIQUE INDEX I_T_USER_ORG ON T_USER_TRAN_ORG (USER_ID,ORG_ID);
CREATE UNIQUE INDEX I_ROLE_WAR ON T_USER_WARRANT (USER_ID,ROLE_ID);


insert into T_APP_CONST (APP_ID, EXT_ID, EXT_DESC, EXT_VALUE, BAK1, BAK2, BAK3)
values ('tamcx     ', 'ORDER_T_APP_CONST             ', '��T_APP_CONST����APP_ID,EXT_ID����                                                                  ', 'APP_ID,EXT_ID', null, null, null);
insert into T_APP_CONST (APP_ID, EXT_ID, EXT_DESC, EXT_VALUE, BAK1, BAK2, BAK3)
values ('tamcx     ', 'ORDER_T_APP_REG               ', '��T_APP_REG�����APP_ID����                                                                         ', 'APP_ID', null, null, null);
insert into T_APP_CONST (APP_ID, EXT_ID, EXT_DESC, EXT_VALUE, BAK1, BAK2, BAK3)
values ('tamcx     ', 'ORDER_T_APP_RESOURCE          ', '��T_APP_RESOURCE����ORDER_ID����                                                                    ', 'APP_ID,ORDER_ID', null, null, null);
insert into T_APP_CONST (APP_ID, EXT_ID, EXT_DESC, EXT_VALUE, BAK1, BAK2, BAK3)
values ('tamcx     ', 'ORDER_T_TRAN_REG              ', '��T_TRAN_REG����APP_ID,TRAN_ID����                                                                  ', 'APP_ID,TRAN_ID', null, null, null);
insert into T_APP_CONST (APP_ID, EXT_ID, EXT_DESC, EXT_VALUE, BAK1, BAK2, BAK3)
values ('tamcx     ', 'SELECT_DICT_APP               ', '��ȡT_APP���е�APP_ID��APP_NAME��Ϊ�����ֵ�                                                         ', '${sql:select APP_ID as V, APP_NAME as D from T_APP_REG}', null, null, null);
insert into T_APP_CONST (APP_ID, EXT_ID, EXT_DESC, EXT_VALUE, BAK1, BAK2, BAK3)
values ('tamcx     ', 'SELECT_ORGTREE1               ', '��ȡ��ǰ�����µĻ�������                                                                            ', '${sql:select org_id as node_id,org_name as node_text,(select count(t2.org_id) from t_org t2 where t2.above_org_id=t1.org_id) as node_leaf,org_id as node_value from t_org t1 where t1.org_id=^${context:orgId}^ and t1.org_id<> ^0001^}', null, null, null);
insert into T_APP_CONST (APP_ID, EXT_ID, EXT_DESC, EXT_VALUE, BAK1, BAK2, BAK3)
values ('tamcx     ', 'SELECT_ORGTREE2               ', '��ȡ��ǰ�����µĻ������ݵڶ��㣬����....                                                            ', '${sql:select org_id as node_id,org_name as node_text,(select count(t2.org_id)  from t_org t2 where t2.above_org_id=t1.org_id) as node_leaf, org_id as node_value from t_org t1 where above_org_id=^${params:node}^ and org_id<> ^0001^}', null, null, null);


insert into T_APP_REG (APP_ID, APP_NAME, BAK)
values ('tamcx', 'Tamcx����ƽ̨', null);


insert into T_EXT_UI_REG (UI_ID, XTYPE, UI_NAME, UI_DESC, UI_TYPE, UI_RESOURCE, UI_CLASS, EXT1, EXT2, EXT3)
values ('checkbox                      ', 'checkbox                      ', '��ѡ��                                            ', '���ڵ�ѡ���ݵ�����', '1', 'js/ext2.1/ext-all.js                                                                                ', null, null, null, null);
insert into T_EXT_UI_REG (UI_ID, XTYPE, UI_NAME, UI_DESC, UI_TYPE, UI_RESOURCE, UI_CLASS, EXT1, EXT2, EXT3)
values ('combo                         ', 'combo                         ', '����ѡ���                                        ', '�����������ݵ�����', '1', 'js/ext2.1/ext-all.js                                                                                ', null, null, null, null);
insert into T_EXT_UI_REG (UI_ID, XTYPE, UI_NAME, UI_DESC, UI_TYPE, UI_RESOURCE, UI_CLASS, EXT1, EXT2, EXT3)
values ('datefield                     ', 'datefield                     ', '���������                                        ', '������������', '1', 'js/ext2.1/ext-all.js                                                                                ', null, null, null, null);
insert into T_EXT_UI_REG (UI_ID, XTYPE, UI_NAME, UI_DESC, UI_TYPE, UI_RESOURCE, UI_CLASS, EXT1, EXT2, EXT3)
values ('decimal                       ', 'numberfield                   ', '�����������                                      ', '���ڸ�����������', '1', 'js/ext2.1/ext-all.js                                                                                ', null, null, null, null);
insert into T_EXT_UI_REG (UI_ID, XTYPE, UI_NAME, UI_DESC, UI_TYPE, UI_RESOURCE, UI_CLASS, EXT1, EXT2, EXT3)
values ('fileview                      ', 'fileview                      ', '�������غͲ鿴�ļ�                                ', '�ƶ��ļ�·������������ļ�', '1', 'app/extension/FileView.js                                                                           ', null, null, null, null);
insert into T_EXT_UI_REG (UI_ID, XTYPE, UI_NAME, UI_DESC, UI_TYPE, UI_RESOURCE, UI_CLASS, EXT1, EXT2, EXT3)
values ('hidden                        ', 'hidden                        ', '���������                                        ', '����������ֵ', '1', 'js/ext2.1/ext-all.js                                                                                ', null, null, null, null);
insert into T_EXT_UI_REG (UI_ID, XTYPE, UI_NAME, UI_DESC, UI_TYPE, UI_RESOURCE, UI_CLASS, EXT1, EXT2, EXT3)
values ('integer                       ', 'numberfield                   ', '���������                                        ', '����������������', '1', 'js/ext2.1/ext-all.js                                                                                ', null, null, null, null);
insert into T_EXT_UI_REG (UI_ID, XTYPE, UI_NAME, UI_DESC, UI_TYPE, UI_RESOURCE, UI_CLASS, EXT1, EXT2, EXT3)
values ('money                         ', 'numberfield                   ', '��������                                        ', '������ݿ�', '1', 'js/ext2.1/ext-all.js                                                                                ', null, null, null, null);
insert into T_EXT_UI_REG (UI_ID, XTYPE, UI_NAME, UI_DESC, UI_TYPE, UI_RESOURCE, UI_CLASS, EXT1, EXT2, EXT3)
values ('numberfield                   ', 'numberfield                   ', '��ֵ�����                                        ', '������ֵ��������', '1', 'js/ext2.1/ext-all.js                                                                                ', null, null, null, null);
insert into T_EXT_UI_REG (UI_ID, XTYPE, UI_NAME, UI_DESC, UI_TYPE, UI_RESOURCE, UI_CLASS, EXT1, EXT2, EXT3)
values ('password                      ', 'textfield                     ', '���������                                        ', '���������', '1', 'js/ext2.1/ext-all.js                                                                                ', null, null, null, null);
insert into T_EXT_UI_REG (UI_ID, XTYPE, UI_NAME, UI_DESC, UI_TYPE, UI_RESOURCE, UI_CLASS, EXT1, EXT2, EXT3)
values ('tamcxorg                      ', 'tamcxorgcombo                 ', 'tamcx ����ѡ���                                  ', '����ѡ��tamcx�еĻ�������', '1', 'app/extendsion/ext.ux/ExtUX.js                                                                      ', null, null, null, null);
insert into T_EXT_UI_REG (UI_ID, XTYPE, UI_NAME, UI_DESC, UI_TYPE, UI_RESOURCE, UI_CLASS, EXT1, EXT2, EXT3)
values ('textarea                      ', 'textarea                      ', '�ı�������                                        ', '���ڶ������ı�����', '1', 'js/ext2.1/ext-all.js                                                                                ', null, null, null, null);
insert into T_EXT_UI_REG (UI_ID, XTYPE, UI_NAME, UI_DESC, UI_TYPE, UI_RESOURCE, UI_CLASS, EXT1, EXT2, EXT3)
values ('textfield                     ', 'textfield                     ', '�ı������                                        ', '�����ı����ݵ�����', '1', 'js/ext2.1/ext-all.js                                                                                ', null, null, null, null);
insert into T_EXT_UI_REG (UI_ID, XTYPE, UI_NAME, UI_DESC, UI_TYPE, UI_RESOURCE, UI_CLASS, EXT1, EXT2, EXT3)
values ('timefield                     ', 'timefield                     ', 'ʱ�������                                        ', '����ʱ���ѡ��', '1', 'js/ext2.1/ext-all.js                                                                                ', null, null, null, null);
insert into T_EXT_UI_REG (UI_ID, XTYPE, UI_NAME, UI_DESC, UI_TYPE, UI_RESOURCE, UI_CLASS, EXT1, EXT2, EXT3)
values ('tipsdqcombo                   ', 'tipsdqcombo                   ', '����ѡ��tips��Ҫ�ĵ�������                        ', '����ѡ��tips��Ҫ�ĵ�������', '1', 'app/extension/ext.ux/ExtUX.js                                                                       ', null, null, null, null);
insert into T_EXT_UI_REG (UI_ID, XTYPE, UI_NAME, UI_DESC, UI_TYPE, UI_RESOURCE, UI_CLASS, EXT1, EXT2, EXT3)
values ('tipsjgcombo                   ', 'tipsjgcombo                   ', '����ѡ��tips����Ҫ�Ļ�������                      ', '����ѡ��tips����Ҫ�Ļ�������', '1', 'app/extendsion/ext.ux/ExtUX.js                                                                      ', null, null, null, null);
insert into T_EXT_UI_REG (UI_ID, XTYPE, UI_NAME, UI_DESC, UI_TYPE, UI_RESOURCE, UI_CLASS, EXT1, EXT2, EXT3)
values ('treecombo                     ', 'treecombo                     ', '���νṹ������                                    ', '�ṩ����֧�ֵ����νṹ������', '1', 'app/extension/ext.ux/ExtUx.js                                                                       ', null, null, null, null);
insert into T_EXT_UI_REG (UI_ID, XTYPE, UI_NAME, UI_DESC, UI_TYPE, UI_RESOURCE, UI_CLASS, EXT1, EXT2, EXT3)
values ('uxcombo                       ', 'uxcombo                       ', '����ѡ���(ʹ�����ݽӿ�)                          ', '�����������ݵ�����', '1', 'app/extension/ext.ux/ExtUX.js                                                                       ', null, null, null, null);
insert into T_EXT_UI_REG (UI_ID, XTYPE, UI_NAME, UI_DESC, UI_TYPE, UI_RESOURCE, UI_CLASS, EXT1, EXT2, EXT3)
values ('ux-radiogroup                 ', 'ux-radiogroup                 ', '��ѡ��                                            ', 'Բ�ε�ѡ��', '1', 'script/ext-2.0.2/app/Ext.ux.Radio.js                                                                ', '                                                  ', '                              ', '                                                            ', '                                                                                          ');



insert into T_IP (IP, IP_DESC, BAK)
values ('127.0.0.1           ', '����                          ', null);


insert into T_ORG (ORG_ID, ORG_NAME, ORG_DESC, ORG_TYPE, ORG_LEVEL, ABOVE_ORG_ID, INNER_ORG_ID, TEL, EMAIL, ORG_ADRESS, BAK1, BAK2, BAK3)
values ('00000           ', '��������                                          ', '�������                                                    ', null, '0', '/               ', '100                        ', null, null, null, null, null, null);


insert into T_SEND_SERVER (ID, SERNAME, IP, PORT, TYPEID, CSTIME)
values ('0088                          ', '����ģ��GAPS                                      ', '127.0.0.1           ', 8081, '0', 60);


insert into T_SYS_PARAM (PARAM_ID, PARAM_NAME, PARAM_VALUE, PARAM_TYPE, VERSION, BAK)
values ('web_file_path       ', '�ļ�����·��                  ', 'app/infoDown/                                                                                                                   ', '0', 'V2.1.tamcx          ', null);


insert into T_USER (USER_ID, USER_NAME, ORG_ID, PASSWD, OLD_PASSWD, STATION, CREAT_DATE, CREAT_TIME, ALTER_DATE, ALTER_TIME, DEL_DATE, TEL, EMAIL, STATUS, SEX, ACADEMIC, CERTI_TYPE, CERTI, FAX, ADRESS, POSTCODE, BAK1, BAK2, BAK3, BAK4, BAK5)
values ('admin          ', '��������Ա          ', '00000     ', 'FF5E61835C355E755EEF9321        ', 'A43B59E342F86CEE5EEF9321        ', '0     ', '20071201', '101010', null, null, null, null, null, '2', null, null, null, null, null, null, null, null, null, null, null, null);


insert into T_VERSION (APP_ID, APP_NAME, VERSION_ID, REGUSER, REGDATE, BAK1, BAK2, BAK3, BAK4, BAK5)
values ('test                          ', 'test                                                        ', '2.1                 ', 'lecky               ', '20110831', null, null, null, null, null);
insert into T_VERSION (APP_ID, APP_NAME, VERSION_ID, REGUSER, REGDATE, BAK1, BAK2, BAK3, BAK4, BAK5)
values ('tamcx                         ', 'TAMCX���                                                   ', 'V2.1.tamcx          ', 'jeffreyLu           ', '20110311', null, null, null, null, null);
insert into T_VERSION (APP_ID, APP_NAME, VERSION_ID, REGUSER, REGDATE, BAK1, BAK2, BAK3, BAK4, BAK5)
values ('bots                          ', '��������                                                    ', 'V2.1.bots           ', 'jeffreyLu           ', '20110313', null, null, null, null, null);
insert into T_VERSION(APP_ID, APP_NAME, VERSION_ID, REGUSER, REGDATE, BAK1, BAK2, BAK3, BAK4, BAK5)
  VALUES('dsf                           ', '���ո�ҵ��                                                  ', 'V2.1.dsf            ', 'jeffreyLu           ', '20110715', NULL, NULL, NULL, NULL, NULL);
insert into T_VERSION (APP_ID, APP_NAME, VERSION_ID, REGUSER, REGDATE, BAK1, BAK2, BAK3, BAK4, BAK5)
values ('btoo                          ', '��ת��                                                      ', 'V2.1.btoo           ', 'jeffreyLu           ', '20110313', null, null, null, null, null);
insert into T_VERSION (APP_ID, APP_NAME, VERSION_ID, REGUSER, REGDATE, BAK1, BAK2, BAK3, BAK4, BAK5)
values ('gaps                          ', 'GAPSͨѶ                                                    ', 'V2.1.gaps           ', 'jeffreyLu           ', '20110312', null, null, null, null, null);
insert into T_VERSION (APP_ID, APP_NAME, VERSION_ID, REGUSER, REGDATE, BAK1, BAK2, BAK3, BAK4, BAK5)
values ('app                           ', '����ҵ��                                                    ', 'V2.1.app            ', 'jeffreyLu           ', '20110411', null, null, null, null, null);
insert into T_VERSION (APP_ID, APP_NAME, VERSION_ID, REGUSER, REGDATE, BAK1, BAK2, BAK3, BAK4, BAK5)
values ('tx                            ', 'Tamcx Extension                                             ', 'V2.1.tx             ', 'jeffreyLu           ', '20110411', null, null, null, null, null);


insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('color_type                    ', '��                            ', '0                             ', '#009933                       ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('color_type                    ', '��                            ', '1                             ', '#FF0000                       ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('color_type                    ', '��                            ', '2                             ', '#3333CC                       ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('color_type                    ', '��                            ', '3                             ', '#FF9900                       ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('color_type                    ', '��                            ', '4                             ', '#993399                       ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('color_type                    ', '��                            ', '5                             ', '#FF6699                       ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('send_type                     ', '������������                  ', '0                             ', 'Ĭ��ͨѶ                      ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('send_type                     ', '������������                  ', '1                             ', '��ʾ��Ϣ                      ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('send_type                     ', '������������                  ', '2                             ', '�ļ�����                      ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('send_type                     ', '������������                  ', '3                             ', '�ļ�չʾ��ӡ                  ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('send_type                     ', '������������                  ', '4                             ', '������Ϣ                      ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('send_returnType               ', '���׽������                  ', '0                             ', '��Ϣ                          ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('send_returnType               ', '���׽������                  ', '4                             ', '��ӡ                          ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('send_returnType               ', '���׽������                  ', '1                             ', '���                          ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('send_returnType               ', '���׽������                  ', '2                             ', '�ļ�                          ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('send_returnType               ', '���׽������                  ', '3                             ', '�ֵ�                          ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('send_cond_type                ', '������������                  ', '1                             ', '�ı���                        ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('send_cond_type                ', '������������                  ', '2                             ', 'ѡ���                        ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('send_cond_type                ', '������������                  ', '3                             ', '����                          ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('send_cond_type                ', '������������                  ', '4                             ', '�����б�                      ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('send_cond_type                ', '������������                  ', '5                             ', '��������                      ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('send_cond_type                ', '������������                  ', '6                             ', '�����ı���                    ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('send_cond_type                ', '������������                  ', '7                             ', '�����ı���                    ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('send_cond_type                ', '������������                  ', '8                             ', '�����ı���                    ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('send_cond_type                ', '������������                  ', '9                             ', '���ݿ�ѡ���                  ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('gaps_send_retType             ', 'GAPSͨѶ�����������          ', '0                             ', '��ȷʱ����                    ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('gaps_send_retType             ', 'GAPSͨѶ�����������          ', '1                             ', '����ʱ����                    ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tamcx_log                     ', '��־����                      ', '0                             ', 'debug                         ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tamcx_log                     ', '��־����                      ', '1                             ', 'fatal                         ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tamcx_log                     ', '��־����                      ', '2                             ', 'info                          ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tamcx_log                     ', '��־����                      ', '3                             ', 'error                         ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('user_academic                 ', 'ѧ��                          ', '3                             ', '����                          ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_report_text_align          ', '���뷽ʽ                      ', '1                             ', '�����                        ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('user_academic                 ', 'ѧ��                          ', '4                             ', '��ר                          ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('send_cond_type                ', '������������                  ', '0                             ', '��ѡ��                        ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('report_data_type              ', '������������                  ', '8                             ', 'ģ����String                  ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('report_data_type              ', '������������                  ', '1                             ', 'String                        ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('report_data_type              ', '������������                  ', '3                             ', 'Double                        ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('report_data_type              ', '������������                  ', '4                             ', 'Float                         ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('report_data_type              ', '������������                  ', '5                             ', 'Integer                       ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('report_data_type              ', '������������                  ', '6                             ', 'Long                          ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('report_data_type              ', '������������                  ', '7                             ', 'Short                         ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('report_data_type              ', '������������                  ', '2                             ', 'BigDecimal                    ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('system_id                     ', 'ϵͳ��ʶ                      ', 'tamcx                         ', 'tamcxϵͳ                     ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('cond_type                     ', '������������                  ', '1                             ', '�ı���                        ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('cond_type                     ', '������������                  ', '2                             ', 'ѡ���                        ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('cond_type                     ', '������������                  ', '3                             ', '����                          ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('cond_type                     ', '������������                  ', '4                             ', '�����б�                      ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('cond_type                     ', '������������                  ', '5                             ', '��������                      ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK) 
values ('cond_type','������������','7','�����ı���','V2.1.tamcx','');
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('cond_type','������������','8','�����ı���','V2.1.tamcx','');
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('cond_type','������������','9','���ݿ�ѡ���','V2.1.tamcx','');
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tranType                      ', '��������                      ', '0                             ', 'ϵͳ����                      ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tranType                      ', '��������                      ', '1                             ', 'ҵ����                      ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('user_status                   ', '�û�״̬                      ', '0                             ', '����                          ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('user_status                   ', '�û�״̬                      ', '1                             ', '����                          ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('user_status                   ', '�û�״̬                      ', '2                             ', '�ѵ�¼                        ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('user_status                   ', '�û�״̬                      ', '9                             ', 'ע��                          ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('user_station                  ', '�û���λ                      ', '0                             ', 'ϵͳ����Ա                    ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('user_station                  ', '�û���λ                      ', '1                             ', '�ؿչ���Ա                    ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('user_station                  ', '�û���λ                      ', '2                             ', '��������                      ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('user_station                  ', '�û���λ                      ', '3                             ', '��ͨ��Ա                      ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('send_returnType               ', '���׽������                  ', '5                             ', '��ѯ����                      ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('user_sex                      ', '�û��Ա�                      ', '0                             ', '��                            ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('user_sex                      ', '�û��Ա�                      ', '1                             ', 'Ů                            ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('user_academic                 ', 'ѧ��                          ', '1                             ', 'Сѧ                          ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('user_academic                 ', 'ѧ��                          ', '2                             ', '��ѧ                          ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('report_type                   ', '����������                  ', '1                             ', 'EXCEL                         ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('report_type                   ', '����������                  ', '2                             ', 'PDF                           ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('sysParamType                  ', 'ϵͳ��������                  ', '0                             ', 'ϵͳ����                      ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('sysParamType                  ', 'ϵͳ��������                  ', '1                             ', 'ҵ��ϵͳ����                  ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('cond_type                     ', '������������                  ', '6                             ', '�����ı���                    ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('lzccb_xmlx                    ', '��Ŀ����                      ', '%%                            ', 'ȫ��                          ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('lzccb_xmlx                    ', '��Ŀ����                      ', '01%                           ', '����                          ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('lzccb_xmlx                    ', '��Ŀ����                      ', '02%                           ', '����                          ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('lzccb_ybfp                    ', 'ҽ����Ʊ                      ', 'lhjy_0202                     ', '����                          ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('lzccb_ybfp                    ', 'ҽ����Ʊ                      ', 'lhjy_03                       ', '����                          ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('send_look_return              ', '��ʾ����                      ', '1                             ', '����                          ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('user_academic                 ', 'ѧ��                          ', '5                             ', '��ר                          ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('user_academic                 ', 'ѧ��                          ', '6                             ', '����                          ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('user_academic                 ', 'ѧ��                          ', '7                             ', '�о���                        ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('user_academic                 ', 'ѧ��                          ', '8                             ', '��ʿ                          ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('certi_type                    ', '֤������                      ', '1                             ', '���֤                        ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('certi_type                    ', '֤������                      ', '2                             ', '����֤                        ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('certi_type                    ', '֤������                      ', '3                             ', '��ʻ֤                        ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('data_type                     ', '��������                      ', '0                             ', 'String                        ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('data_type                     ', '��������                      ', '1                             ', 'Integer                       ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('data_type                     ', '��������                      ', '2                             ', 'Date                          ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('data_type                     ', '��������                      ', '3                             ', 'Double                        ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('data_type                     ', '��������                      ', '4                             ', 'Float                         ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('is_format                     ', '�Ƿ��ʽ��                    ', '0                             ', '��                            ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('is_format                     ', '�Ƿ��ʽ��                    ', '1                             ', '��                            ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('is_null                       ', '�Ƿ��ʽ��                    ', '0                             ', '��                            ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('is_null                       ', '�Ƿ��ʽ��                    ', '1                             ', '��                            ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('org_type                      ', '��������                      ', '0                             ', '���׻���                      ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('org_type                      ', '��������                      ', '1                             ', '�ǽ��׻���                    ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('send_look_return              ', '��ʾ����                      ', '0                             ', '����                          ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX�����������                ', 'timefield                     ', 'ʱ��ѡ���                    ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX�����������                ', 'tipsdqcombo                   ', 'TIPS����ѡ���                ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX�����������                ', 'tipsjgcombo                   ', 'TIPS����ѡ���                ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX�����������                ', 'treecombo                     ', '����ѡ���                    ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX�����������                ', 'treepanel                     ', '�������                      ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX�����������                ', 'window                        ', '����                          ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_xml_node_type              ', 'XML �ڵ�����                  ', '0                             ', '��ͨ�ڵ�                      ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_xml_node_type              ', 'XML �ڵ�����                  ', '1                             ', 'ѭ���ڵ�                      ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_xml_node_type              ', 'XML �ڵ�����                  ', '2                             ', '���ݽڵ�                      ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_yes_no_type                ', 'TX boolean����                ', '0                             ', '��                            ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_yes_no_type                ', 'TX boolean����                ', '1                             ', '��                            ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_comm_type                  ', 'TXͨѶ�������                ', '5                             ', '������                      ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_report_fill_type           ', '�������                      ', '1                             ', '�����                        ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_report_fill_type           ', '�������                      ', '2                             ', '�Կո����                    ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_report_fill_type           ', '�������                      ', '3                             ', '��0���                       ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_report_sum_type            ', '�ϼ�����                      ', '1                             ', '�Ǻϼ���                      ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_report_sum_type            ', '�ϼ�����                      ', '2                             ', 'С����                        ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_report_sum_type            ', '�ϼ�����                      ', '3                             ', '�ϼ���                        ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('t_ui_type                     ', 'TX�����������                ', 'box                           ', 'Box���                       ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('t_ui_type                     ', 'TX�����������                ', 'button                        ', '��ť                          ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('t_ui_type                     ', 'TX�����������                ', 'checkbox                      ', '��ѡ��                        ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_res_type                   ', 'TX��Դ����                    ', 'folder-delete                 ', 'SQL��ѯ����                   ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_res_type                   ', 'TX��Դ����                    ', 'sql-delete                    ', 'SQL��ѯɾ��                   ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_res_type                   ', 'TX��Դ����                    ', 'sql-select                    ', 'SQL��ѯ����                   ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_res_type                   ', 'TX��Դ����                    ', 'sql-update                    ', 'SQL��ѯ����                   ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX�����������                ', 'tabpanel                      ', 'TAB���                       ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('t_search_type                 ', '���ֶβ�ѯ����                ', 'between                       ', '�����ѯ                      ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('t_search_type                 ', '���ֶβ�ѯ����                ', 'equal                         ', '��ȷ��ѯ                      ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('t_search_type                 ', '���ֶβ�ѯ����                ', 'ext                           ', '��չ��ѯ                      ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('t_search_type                 ', '���ֶβ�ѯ����                ', 'gt                            ', '���ڲ�ѯ                      ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('t_search_type                 ', '���ֶβ�ѯ����                ', 'lg                            ', 'С�ڲ�ѯ                      ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('t_search_type                 ', '���ֶβ�ѯ����                ', 'like                          ', 'ģ����ѯ                      ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('t_search_type                 ', '���ֶβ�ѯ����                ', 'none                          ', '����Ϊ��ѯ����                ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('t_search_type                 ', '���ֶβ�ѯ����                ', 'notequal                      ', '���Ȳ�ѯ                      ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tranType                      ', '��������                      ', '2                             ', '���ý���                      ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_boolean_type               ', 'boolean ����                  ', '0                             ', '��                            ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_boolean_type               ', 'boolean ����                  ', '1                             ', '��                            ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_charset                    ', '�ַ�����                      ', 'GB18030                       ', 'GB18030�ַ�����               ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_charset                    ', '�ַ�����                      ', 'GB2312                        ', 'GB2312�ַ�����                ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_charset                    ', '�ַ�����                      ', 'GBK                           ', 'GBK�ַ�����                   ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_charset                    ', '�ַ�����                      ', 'ISO-8599-1                    ', 'ISO-8599-1�ַ�����            ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_charset                    ', '�ַ�����                      ', 'UTF-16                        ', 'UTF-16�ַ�����                ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_charset                    ', '�ַ�����                      ', 'UTF-16BE                      ', 'UTF-16BE�ַ�����              ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_charset                    ', '�ַ�����                      ', 'UTF-16LE                      ', 'UTF-16LE�ַ�����              ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_charset                    ', '�ַ�����                      ', 'UTF-8                         ', 'UTF-8�ַ�����                 ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_comm_request_node_type     ', 'TXͨѶ����ڵ�����            ', '0                             ', 'Ԫ���ݽڵ�                    ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_comm_request_node_type     ', 'TXͨѶ����ڵ�����            ', '1                             ', '�ؼ�ֵ�ڵ�                    ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_comm_request_node_type     ', 'TXͨѶ����ڵ�����            ', '2                             ', 'ҳ����ڵ�                    ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_comm_request_node_type     ', 'TXͨѶ����ڵ�����            ', '3                             ', 'ҳ�渨���ڵ�                  ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_comm_request_node_type     ', 'TXͨѶ����ڵ�����            ', '4                             ', 'gapsͨѶ����ڵ�              ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_comm_request_node_type     ', 'TXͨѶ����ڵ�����            ', '5                             ', 'gapsͨѶ��Ӧ�ڵ�              ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_comm_type                  ', 'TXͨѶ�������                ', '0                             ', 'GAPSͨѶ���                  ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_comm_type                  ', 'TXͨѶ�������                ', '1                             ', '���ݿ�ͨѶ                    ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_comm_type                  ', 'TXͨѶ�������                ', '2                             ', '���ý���                      ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_comm_type                  ', 'TXͨѶ�������                ', '3                             ', '���Ͻ���                      ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_comm_type                  ', 'TXͨѶ�������                ', '4                             ', '�����ӽ���                    ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_com_type                   ', 'TX�������                    ', '0                             ', 'EXT-UI                        ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ext_ui_type                ', '�������                      ', '0                             ', '��ʾ�����                    ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ext_ui_type                ', '�������                      ', '1                             ', '���������                    ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_search_type                ', '���ֶβ�ѯ����                ', 'between                       ', '�����ѯ                      ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_search_type                ', '���ֶβ�ѯ����                ', 'equal                         ', '��ȷ��ѯ                      ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_search_type                ', '���ֶβ�ѯ����                ', 'ext                           ', '��չ��ѯ                      ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_search_type                ', '���ֶβ�ѯ����                ', 'gt                            ', '���ڲ�ѯ                      ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_search_type                ', '���ֶβ�ѯ����                ', 'lg                            ', 'С�ڲ�ѯ                      ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_search_type                ', '���ֶβ�ѯ����                ', 'like                          ', 'ģ����ѯ                      ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_search_type                ', '���ֶβ�ѯ����                ', 'none                          ', '����Ϊ��ѯ����                ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_search_type                ', '���ֶβ�ѯ����                ', 'notequal                      ', '���Ȳ�ѯ                      ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX�����������                ', 'box                           ', 'Box���                       ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX�����������                ', 'button                        ', '��ť                          ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX�����������                ', 'checkbox                      ', '��ѡ��                        ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX�����������                ', 'colorpalette                  ', '��ɫѡ���                    ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX�����������                ', 'combo                         ', '������                        ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX�����������                ', 'component                     ', '���                          ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX�����������                ', 'container                     ', '����                          ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX�����������                ', 'datefield                     ', '����ѡ���                    ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX�����������                ', 'dbpanel                       ', '���ݿ����                    ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX�����������                ', 'field                         ', '���ֶ�                      ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX�����������                ', 'fieldset                      ', '���ֶ���                    ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX�����������                ', 'fileview                      ', '�ļ��鿴���                  ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX�����������                ', 'form                          ', '��                          ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX�����������                ', 'gapscommpanel                 ', 'gapsͨѶ���                  ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX�����������                ', 'grid                          ', '������                      ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX�����������                ', 'hidden                        ', '�������ֶ�                  ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX�����������                ', 'htmleditor                    ', 'HTML�༭��                    ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_report_text_align          ', '���뷽ʽ                      ', '2                             ', '�Ҷ���                        ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_report_text_align          ', '���뷽ʽ                      ', '3                             ', '���ж���                      ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_report_type                ', '��������                      ', 'fix                           ', '��������                      ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_report_type                ', '��������                      ', 'ireport                       ', 'ireport����                   ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_report_type                ', '��������                      ', 'pdf                           ', 'pdf����                       ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_report_type                ', '��������                      ', 'sep                           ', '���߷ָ��                  ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_report_type                ', '��������                      ', 'sql                           ', 'sql����                       ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_report_type                ', '��������                      ', 'xls                           ', '��xls����                   ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_report_type                ', '��������                      ', 'xls_tpl                       ', 'xlsģ�屨��                   ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_res_type                   ', 'TX��Դ����                    ', 'file-copy                     ', '�ļ�����                      ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_res_type                   ', 'TX��Դ����                    ', 'file-delete                   ', '�ļ�ɾ��                      ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_res_type                   ', 'TX��Դ����                    ', 'folder-copy                   ', 'Ŀ¼����                      ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX�����������                ', 'numberfield                   ', '��ֵ�����                    ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX�����������                ', 'panel                         ', '���                          ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX�����������                ', 'password                      ', '���������                    ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX�����������                ', 'radio                         ', '��ѡ��                        ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX�����������                ', 'tamcxorgcombo                 ', 'TAMCX����ѡ���               ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX�����������                ', 'textarea                      ', '�ı���                        ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX�����������                ', 'textfield                     ', '�ı���                        ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('t_ui_type                     ', 'TX�����������                ', 'colorpalette                  ', '��ɫѡ���                    ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('t_ui_type                     ', 'TX�����������                ', 'combo                         ', '������                        ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('t_ui_type                     ', 'TX�����������                ', 'component                     ', '���                          ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('t_ui_type                     ', 'TX�����������                ', 'container                     ', '����                          ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('t_ui_type                     ', 'TX�����������                ', 'datefield                     ', '����ѡ���                    ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('t_ui_type                     ', 'TX�����������                ', 'dbpanel                       ', '���ݿ����                    ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('t_ui_type                     ', 'TX�����������                ', 'field                         ', '���ֶ�                      ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('t_ui_type                     ', 'TX�����������                ', 'fieldset                      ', '���ֶ���                    ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('t_ui_type                     ', 'TX�����������                ', 'fileview                      ', '�ļ��鿴���                  ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('t_ui_type                     ', 'TX�����������                ', 'form                          ', '��                          ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('t_ui_type                     ', 'TX�����������                ', 'grid                          ', '������                      ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('t_ui_type                     ', 'TX�����������                ', 'hidden                        ', '�������ֶ�                  ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('t_ui_type                     ', 'TX�����������                ', 'htmleditor                    ', 'HTML�༭��                    ', 'V2.1.tamcx          ', null);


insert into T_MENU (MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
values ('menux                         ', 'super_menage                  ', 3, '�˵�����            ', '�˵�����                                          ', '1', 'menux               ', '1', 'V2.1.tamcx          ', null, '900002000000        ', '0', 'agent     ', null, null, null);
insert into T_MENU (MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
values ('tx_db                         ', 'TX_CONFIG                     ', 3, '��ɾ�Ĳ�����        ', '��ɾ�Ĳ�����                                      ', '1', 'tx_db_operator      ', '1', 'V2.1.tamcx          ', null, '908060000000        ', '0', 'agent     ', null, null, null);
insert into T_MENU (MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
values ('ipreg                         ', 'sysinit                       ', 3, 'IP�Ǽǹ���          ', 'IP�Ǽǹ���                                        ', '1', 'ipreg               ', '1', 'V2.1.tamcx          ', null, '900026100000        ', '0', 'agent     ', null, null, null);
insert into t_menu (menu_id,above_menu_id,menu_deep,menu_name,menu_desc,is_run_menu,tran_code,is_enable,version,report_id,order_id,menu_type,system_id,bak1,bak2,bak3) 
values('TX_PZJYEXPORT','TX_CONFIG',3,'���ý��׵���','���ý��׵���','1','pzjyexport','1','','','908080000000','0','agent','','','');
insert into T_MENU (MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
values ('change_pwd                    ', 'sysinit                       ', 3, '�޸�����            ', '�޸�����                                          ', '1', 'changePwd           ', '1', 'V2.1.tamcx          ', null, '900027100000        ', '0', 'agent     ', null, null, null);
insert into T_MENU (MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
values ('usermacheck                   ', 'sysinit                       ', 3, '�û����            ', '�û����                                          ', '1', 'usermacheck         ', '1', 'V2.1.tamcx          ', null, '900025100000        ', '0', 'agent     ', null, null, null);
insert into T_MENU (MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
values ('statusmonitor                 ', 'sysinit                       ', 3, '����״̬            ', '�鿴����״̬                                      ', '1', 'statusmonitor       ', '1', 'V2.1.tamcx          ', null, '900028100000        ', '0', 'agent     ', null, null, null);
insert into T_MENU (MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
values ('appversionmanage              ', 'TX_CONFIG                     ', 3, 'Ӧ�ð汾����        ', 'Ӧ�ð汾����                                      ', '1', 'appversionmanage    ', '1', 'V2.1.tamcx          ', null, '908050000000        ', '0', 'agent     ', null, null, null);
insert into T_MENU (MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
values ('TX_APP_PAGE_GEN               ', 'TX_CONFIG                     ', 3, 'Ӧ�ý�������        ', 'Ӧ�ý�������                                      ', '1', 'tx_app_page_gen     ', '1', 'V2.1.tx             ', null, '908070000000        ', '0', 'tamcx     ', null, null, null);
insert into T_MENU (MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
values ('TX_CONFIG                     ', 'super_menage                  ', 2, '��������            ', '��������                                          ', '0', 'alterUserPass       ', '1', 'V2.1.tx             ', null, '908000000000        ', '0', 'tamcx     ', null, null, null);
insert into T_MENU (MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
values ('reportPz                      ', 'super_menage                  ', 2, '��������            ', '��������                                          ', '1', 'reportPz            ', '1', 'V2.1.tamcx          ', 'reportPz                                ', '900004000000        ', '0', 'tamcx     ', null, null, null);
insert into T_MENU (MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
values ('sysini                        ', 'super_menage                  ', 2, 'ϵͳ����ά��        ', 'ϵͳ����ά��                                      ', '1', 'system_param        ', '1', 'V2.1.tamcx          ', null, '900009000000        ', '0', 'tamcx     ', null, null, null);
insert into T_MENU (MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
values ('dict_menage                   ', 'super_menage                  ', 2, '�ֵ�ά��            ', '�ֵ����ά��                                      ', '1', 'dictManage          ', '1', 'V2.1.tamcx          ', null, '900003000000        ', '0', 'tamcx     ', null, null, null);
insert into T_MENU (MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
values ('super_menage                  ', '/                             ', 1, '��������            ', '������Ϊ������Աר�ã�����ҵ�񿪷š�              ', '0', null, '1', 'V2.1.tamcx          ', null, '900000000000        ', '0', 'tamcx     ', null, null, null);
insert into T_MENU (MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
values ('refresh_param                 ', 'super_menage                  ', 2, 'ˢ��ϵͳ����        ', 'ˢ��ϵͳ����                                      ', '1', 'refresh_param       ', '1', 'V2.1.tamcx          ', null, '900009000000        ', '0', 'tamcx     ', null, null, null);
insert into T_MENU (MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
values ('sys_menage                    ', '/                             ', 1, 'ϵͳ����            ', 'ϵͳ����                                          ', '0', 'sys_Menage          ', '1', 'V2.1.tamcx          ', null, '900020000000        ', '0', 'tamcx     ', null, null, null);
insert into T_MENU (MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
values ('sysinit                       ', 'sys_menage                    ', 2, 'ϵͳ��������        ', 'ϵͳ��������                                      ', '0', 'botsPlywlx          ', '1', 'V2.1.tamcx          ', null, '900021000000        ', '0', 'tamcx     ', null, null, null);
insert into T_MENU (MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
values ('tran_conf                     ', 'super_menage                  ', 2, '��������            ', '���ý��������Ϣ                                  ', '1', 'TranSubtran         ', '1', 'V2.1.tamcx          ', null, '900001000000        ', '0', 'tamcx     ', null, null, null);
insert into T_MENU (MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
values ('gaps_new                      ', 'super_menage                  ', 3, 'GAPSͨѶ����        ', 'GAPSͨѶ����                                      ', '1', 'gapsconfig          ', '1', 'V2.1.tamcx          ', null, '900004100000        ', '0', 'agent     ', null, null, null);
insert into T_MENU (MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
values ('org_manage                    ', 'sysinit                       ', 3, '��������            ', '��������                                          ', '1', 'org_manage          ', '1', 'V2.1.tamcx          ', null, '900022100000        ', '0', 'agent     ', null, null, null);
insert into T_MENU (MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
values ('role_manage                   ', 'sysinit                       ', 3, '��ɫ����            ', '��ɫ����                                          ', '1', 'role_manage         ', '1', 'V2.1.tamcx          ', null, '900023100000        ', '0', 'tamcx     ', null, null, null);
insert into T_MENU (MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
values ('user_manage                   ', 'sysinit                       ', 3, '�û�����            ', '�û�����                                          ', '1', 'user_manage         ', '1', 'V2.1.tamcx          ', null, '900024100000        ', '0', 'tamcx     ', null, null, null);
insert into T_MENU (MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
values ('dzgl                          ', 'xtgljdz                       ', 4, '���˹���            ', '���˹���                                          ', '1', 'dzgl                ', '1', 'V2.1.tamcx          ', null, '900400000101        ', '0', 'agent     ', null, null, null);
insert into T_MENU (MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
values ('xtjk                          ', 'xtgljdz                       ', 4, 'ϵͳ���            ', 'ϵͳ���                                          ', '1', 'xtjk                ', '1', 'V2.1.tamcx          ', null, '900400000102        ', '0', 'agent     ', null, null, null);
insert into T_MENU (MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
values ('prod_upgrade                  ', 'super_menage                  ', 2, '��Ʒ����            ', '��Ʒ����                                          ', '1', 'cpsj_manage         ', '1', 'V2.1.tamcx          ', null, '900009030000        ', '0', 'agent     ', null, null, null);


insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_table            ', 'edt                 ', 'edt                           ', 'app/extension/tableEdt.jsp                                                                          ', 'edt                                               ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('user_menage         ', 'upt                 ', '����                          ', 'success.jsp                                                                                         ', '�����û���Ϣ                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('reportPz            ', 'def                 ', 'Ĭ�ϱ�������ҳ��              ', 'systemx/sysx_report.jsp                                                                             ', 'Ĭ�ϱ�������ҳ��                                  ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('cpsj_manage         ', 'import              ', '�������ݵ���                  ', 'system/cpsjmanage.jsp                                                                               ', '����ϵͳ���ݵ���                                  ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('TranSubtran         ', 'addSubtran          ', '�����ӽ���                    ', 'systemx/sysx_transubtran.jsp                                                                        ', '�����ӽ���                                        ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('TranSubtran         ', 'delSubtran          ', 'ɾ���ӽ���                    ', 'systemx/sysx_transubtran.jsp                                                                        ', 'ɾ���ӽ���                                        ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('changePwd           ', 'def                 ', 'Ĭ��                          ', 'systemx/sysx_change_pwd.jsp                                                                         ', 'Ĭ��                                              ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('gapsconfig          ', 'serverupt           ', 'ִ�з������                  ', 'systemx/sysx_gapsconfig.jsp                                                                         ', 'ִ�з�����                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('TranSubtran         ', 'add                 ', '���ӽ��׽���                  ', 'systemx/sysx_transubtran.jsp                                                                        ', '���ӽ��׽���                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('TranSubtran         ', 'def                 ', '�����б�                      ', 'systemx/sysx_transubtran.jsp                                                                        ', '��ѯ����ʾ�����б�                                ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('TranSubtran         ', 'edt                 ', '�޸Ľ��׽���                  ', 'systemx/sysx_transubtran.jsp                                                                        ', '��ѯ����ʾ���޸ĵĽ�����Ϣ                        ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('gapsconfig          ', 'serveredt           ', '�޸ķ���ҳ��                  ', 'systemx/sysx_gapsconfig.jsp                                                                         ', '�޸ķ���ҳ��                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('logon               ', 'ent                 ', '�û���¼                      ', 'main/logonNew.jsp                                                                                   ', '�û���¼,У���û���Ϣ                             ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('logon               ', 'def                 ', '��¼Ĭ��ҳ��                  ', 'main/logonNew.jsp                                                                                   ', '��¼Ĭ��ҳ��                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('logon               ', 'out                 ', '�û�ǩ��                      ', 'main/logonNew.jsp                                                                                   ', '�û�ǩ��                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('menu_conf           ', 'upt                 ', '�޸Ĳ˵�������Ϣ              ', 'success.jsp                                                                                         ', '�޸Ĳ˵���������                                  ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('org_menage          ', 'batch               ', '������������                  ', 'success.jsp                                                                                         ', '������������                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('user_menage         ', 'batch               ', '�������û�                    ', 'success.jsp                                                                                         ', '�������û�                                        ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('gapsdown            ', 'def                 ', 'Ĭ��ҳ��                      ', 'app/send/toGapsFile.jsp                                                                             ', 'Ĭ��ҳ��                                          ', 'V2.1.gaps           ', '01                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('gapsdown            ', 'down                ', '�����ļ�                      ', 'app/send/toGapsFile.jsp                                                                             ', '����                                              ', 'V2.1.gaps           ', '01                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('dict_menage         ', 'edt                 ', '�޸�                          ', 'system/dictEdt.jsp                                                                                  ', '�޸Ľ���                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('dict_menage         ', 'upt                 ', '�޸ĸ���                      ', 'system/dictMenage.jsp                                                                               ', '�޸ĸ���                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('dict_menage         ', 'add                 ', '����                          ', 'system/dictEdt.jsp                                                                                  ', '���ӽ���                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('dict_menage         ', 'ins                 ', '���Ӹ���                      ', 'system/dictMenage.jsp                                                                               ', '���Ӹ���                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('dict_menage         ', 'del                 ', 'ɾ��                          ', 'system/dictMenage.jsp                                                                               ', 'ɾ��                                              ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('cpsj_manage         ', 'export              ', '�������ݵ���                  ', 'system/cpsjmanage.jsp                                                                               ', '����ϵͳ���ݵ���                                  ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('reportPz            ', 'add                 ', '��ӱ�����Ϣ                  ', 'systemx/sysx_report.jsp                                                                             ', '��ӱ�����Ϣ                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('sendPz              ', 'serveredt           ', '�޸ķ���ҳ��                  ', 'app/gaps/sendServerPzEdt.jsp                                                                        ', '�޸ķ���ҳ��                                      ', 'V2.1.gaps           ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('sendPz              ', 'serverins           ', 'ִ�з�������                  ', 'app/gaps/sendServerPzLst.jsp                                                                        ', 'ִ�з������                                      ', 'V2.1.gaps           ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('sendPz              ', 'serveradd           ', '���ӷ���                      ', 'app/gaps/sendServerPzEdt.jsp                                                                        ', '���ӷ���ҳ��                                      ', 'V2.1.gaps           ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('sendPz              ', 'serverdef           ', 'Ĭ�Ϸ���                      ', 'app/gaps/sendServerPzLst.jsp                                                                        ', 'Ĭ�Ϸ���                                          ', 'V2.1.gaps           ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('userMenageCheck     ', 'check               ', '����û�                      ', 'system/userMenageCheck.jsp                                                                          ', '����û�                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('send                ', 'def                 ', '��ʼ����                      ', 'app/gaps/send.jsp                                                                                   ', '��ʼ����                                          ', 'V2.1.gaps           ', '01                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('sendPz              ', 'def                 ', 'ͨѶ��ѯ                      ', 'app/gaps/sendPzLst.jsp                                                                              ', 'ͨѶ                                              ', 'V2.1.gaps           ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('send                ', 'send                ', 'ִ�н���                      ', 'app/gaps/sendreturn.jsp                                                                             ', 'ִ�н���                                          ', 'V2.1.gaps           ', '01                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('sendPz              ', 'add                 ', '���ͨѶҳ��                  ', 'app/gaps/sendPzEdt.jsp                                                                              ', '���ҳ��ͨѶ                                      ', 'V2.1.gaps           ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('sendPz              ', 'edt                 ', '����ͨѶҳ��                  ', 'app/gaps/sendPzEdt.jsp                                                                              ', '����ͨѶҳ��                                      ', 'V2.1.gaps           ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('sendPz              ', 'ins                 ', 'ִ��ͨѶ���                  ', 'app/gaps/sendPzLst.jsp                                                                              ', 'ִ��ͨѶ���                                      ', 'V2.1.gaps           ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('sendPz              ', 'del                 ', 'ɾ��ͨѶ                      ', 'app/gaps/sendPzLst.jsp                                                                              ', 'ɾ��ͨѶ                                          ', 'V2.1.gaps           ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('sendPz              ', 'conddef             ', 'Ĭ��ͨѶ����                  ', 'app/gaps/sendCondPzLst.jsp                                                                          ', 'ͨѶ����                                          ', 'V2.1.gaps           ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('sendPz              ', 'condadd             ', '���ͨѶ����ҳ��              ', 'app/gaps/sendCondPzEdt.jsp                                                                          ', '�������ҳ��                                      ', 'V2.1.gaps           ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('reportPz            ', 'del                 ', 'ɾ��������Ϣ                  ', 'systemx/sysx_report.jsp                                                                             ', 'ɾ��������Ϣ                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('cpsj_manage         ', 'def                 ', '��Ʒ��������                  ', 'system/cpsjmanage.jsp                                                                               ', '��Ʒ��������                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('reportCondPz        ', 'add                 ', '��ת��ӱ�������ҳ��          ', 'system/reportCondPzEdt.jsp                                                                          ', '��ת��ӱ�������ҳ��                              ', 'V2.1.tamcx          ', '02                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('reportCondPz        ', 'ins                 ', '��ӱ���������Ϣ              ', 'system/reportCondPzLst.jsp                                                                          ', '��ӱ���������Ϣ                                  ', 'V2.1.tamcx          ', '02                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('reportCondPz        ', 'edt                 ', '��ת��������ά��ҳ            ', 'system/reportCondPzEdt.jsp                                                                          ', '��ת��������ά��ҳ                                ', 'V2.1.tamcx          ', '02                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('reportCondPz        ', 'upt                 ', '������������                  ', 'system/reportCondPzLst.jsp                                                                          ', '������������                                      ', 'V2.1.tamcx          ', '02                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('reportCondPz        ', 'del                 ', 'ɾ����������                  ', 'system/reportCondPzLst.jsp                                                                          ', 'ɾ����������                                      ', 'V2.1.tamcx          ', '02                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('alterUserPass       ', 'def                 ', '�޸��������                  ', 'system/alterUserPass.jsp                                                                            ', '�޸��������                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('userMenageCheck     ', 'def                 ', '��ѯ�û�                      ', 'system/userMenageCheck.jsp                                                                          ', '��ѯδͨ������û�                                ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('user_menage         ', 'del                 ', 'ɾ��                          ', 'success.jsp                                                                                         ', 'ɾ���û���Ϣ                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('sendPz              ', 'returndef           ', 'Ĭ��ͨѶ���                  ', 'app/gaps/sendreturnPzLst.jsp                                                                        ', 'Ĭ��ͨѶ���                                      ', 'V2.1.gaps           ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('sendPz              ', 'returnadd           ', '����ͨѶ���ҳ��              ', 'app/gaps/sendreturnPzEdt.jsp                                                                        ', '����ͨѶ���ҳ��                                  ', 'V2.1.gaps           ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('send                ', 'infLst              ', '������Ϣ                      ', 'app/gaps/sendinfoLst.jsp                                                                            ', '������Ϣ                                          ', 'V2.1.gaps           ', '02                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('send                ', 'info                ', '��Ϣ��ʾ                      ', 'app/gaps/sendinfo.jsp                                                                               ', '������Ϣ                                          ', 'V2.1.gaps           ', '02                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('send                ', 'print               ', '��ʾ��ӡ�ļ�                  ', 'app/gaps/sendreturn.jsp                                                                             ', '��ʾ��ӡ�ļ�                                      ', 'V2.1.gaps           ', '02                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('send                ', 'down                ', '�����ļ�                      ', 'about:blank                                                                                         ', '�����ļ�                                          ', 'V2.1.gaps           ', '02                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('send                ', 'fileToPrint         ', '�ļ���ʾ��ӡ                  ', 'break                                                                                               ', '�ļ���ʾ��ӡ                                      ', 'V2.1.gaps           ', '02                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('sendPz              ', 'returnins           ', 'ִ��ͨѶ�������              ', 'app/gaps/sendreturnPzLst.jsp                                                                        ', 'ִ��ͨѶ������                                  ', 'V2.1.gaps           ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('sendPz              ', 'returnedt           ', '�޸�ͨѶ���ҳ��              ', 'app/gaps/sendreturnPzEdt.jsp                                                                        ', '�޸�ͨѶ���ҳ��                                  ', 'V2.1.gaps           ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('sendPz              ', 'returnupt           ', 'ִ��ͨѶ�������              ', 'app/gaps/sendreturnPzLst.jsp                                                                        ', 'ִ�и���ͨѶ���                                  ', 'V2.1.gaps           ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('sendPz              ', 'returndel           ', 'ɾ��ͨѶ���                  ', 'app/gaps/sendreturnPzLst.jsp                                                                        ', 'ɾ��ͨѶ���                                      ', 'V2.1.gaps           ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('report              ', 'lend                ', '������                      ', 'success.jsp                                                                                         ', '������                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('report              ', 'look                ', '��������ҳ��ѯ              ', 'success.jsp                                                                                         ', '��������ҳ��ѯ                                  ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('report              ', 'def                 ', '�����ѯ                      ', 'systemx/report.jsp', '�����ѯ                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('org_menage          ', 'ins                 ', '����                          ', 'success.jsp                                                                                         ', '���뽻������                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('org_menage          ', 'upt                 ', '����                          ', 'success.jsp                                                                                         ', '���»�����Ϣ                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('user_menage         ', 'ins                 ', '����                          ', 'success.jsp                                                                                         ', '�����û���Ϣ                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('send                ', 'dateReport          ', '���ݱ���                      ', 'app/gaps/sendreturn.jsp                                                                             ', '���ݱ���                                          ', 'V2.1.gaps           ', '02                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('botsGapsdown        ', 'down                ', '�����ļ�                      ', 'app/agent/bots/toGapsFile.jsp                                                                       ', '����                                              ', 'V2.1.gaps           ', '01                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('botsGapsdown        ', 'def                 ', 'Ĭ��ҳ��                      ', 'app/agent/bots/toGapsFile.jsp                                                                       ', 'Ĭ��ҳ��                                          ', 'V2.1.gaps           ', '01                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('sendPz              ', 'condins             ', 'ִ��ͨѶ�������              ', 'app/gaps/sendCondPzLst.jsp                                                                          ', 'ִ���������                                      ', 'V2.1.gaps           ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('sendPz              ', 'condedt             ', '����ͨѶ����ҳ��              ', 'app/gaps/sendCondPzEdt.jsp                                                                          ', '��������ҳ��                                      ', 'V2.1.gaps           ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('sendPz              ', 'condupt             ', 'ִ��ͨѶ��������              ', 'app/gaps/sendCondPzLst.jsp                                                                          ', 'ִ�и�������                                      ', 'V2.1.gaps           ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('sendPz              ', 'conddel             ', 'ɾ��ͨѶ����                  ', 'app/gaps/sendCondPzLst.jsp                                                                          ', 'ɾ������                                          ', 'V2.1.gaps           ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('mvSend              ', 'print               ', '��ʾ��ӡ�ļ�                  ', 'app/gaps/sendreturn.jsp                                                                             ', '��ʾ��ӡ�ļ�                                      ', 'V2.1.gaps           ', '02                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('mvSend              ', 'down                ', '�����ļ�                      ', 'about:blank                                                                                         ', '�����ļ�                                          ', 'V2.1.gaps           ', '02                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('mvSend              ', 'def                 ', '��ʼ����                      ', 'app/gaps/mvSend.jsp                                                                                 ', '��ʼ����                                          ', 'V2.1.gaps           ', '01                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('mvSend              ', 'infLst              ', '������Ϣ                      ', 'app/gaps/sendinfoLst.jsp                                                                            ', '������Ϣ                                          ', 'V2.1.gaps           ', '02                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('mvSend              ', 'info                ', '��Ϣ��ʾ                      ', 'app/gaps/sendinfo.jsp                                                                               ', '��Ϣ��ʾ                                          ', 'V2.1.gaps           ', '02                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('mvSend              ', 'fileToprint         ', '�ļ���ʾ��ӡ                  ', 'app/gaps/sendreturn.jsp                                                                             ', '�ļ���ʾ��ӡ                                      ', 'V2.1.gaps           ', '02                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('mvSend              ', 'send                ', 'ִ�н���                      ', 'app/gaps/sendreturn.jsp                                                                             ', 'ִ�н���                                          ', 'V2.1.gaps           ', '01                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('mvSend              ', 'mv                  ', '��Ȩ                          ', 'about:blank                                                                                         ', '��Ȩ                                              ', 'V2.1.gaps           ', '01                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('mvSend              ', 'mvExe               ', 'ִ����֤                      ', 'about:blank                                                                                         ', 'ִ����֤                                          ', 'V2.1.gaps           ', '02                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('TranSubtran         ', 'list                ', '���ײ�ѯ                      ', 'systemx/sysx_transubtran.jsp                                                                        ', '�������ò�ѯ                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('refresh_param       ', 'refresh             ', 'ϵͳ����ˢ��                  ', 'success.jsp                                                                                         ', 'ϵͳ����ˢ��                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('reportPz            ', 'ins                 ', 'ִ����ӱ�����Ϣ              ', 'systemx/sysx_report.jsp                                                                             ', 'ִ����ӱ�����Ϣ                                  ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('TranSubtran         ', 'upt                 ', '���½���                      ', 'systemx/sysx_transubtran.jsp                                                                        ', '���½���������Ϣ                                  ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('TranSubtran         ', 'uptSubtran          ', '�����ӽ���                    ', 'systemx/sysx_transubtran.jsp                                                                        ', '�����ӽ���                                        ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('TranSubtran         ', 'listSubtran         ', '�ӽ����б�                    ', 'systemx/sysx_transubtran.jsp                                                                        ', '��ѯ����ʾ�ӽ����б�                              ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('gapsconfig          ', 'serverdel           ', 'ɾ������                      ', 'systemx/sysx_gapsconfig.jsp                                                                         ', 'ɾ��������                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('statusmonitor       ', 'show                ', '�鿴                          ', 'systemx/sysx_status_monitor.jsp                                                                     ', '�鿴                                              ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('dict_menage         ', 'def                 ', '�ֵ��б�                      ', 'system/dictMenage.jsp                                                                               ', '��ʾ�ֵ��б�                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('expsql              ', 'def                 ', 'Ĭ��                          ', 'systemx/sysx_exp_sql.jsp                                                                            ', 'Ĭ��                                              ', 'V2.1.tamcx          ', '01                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('expsql              ', 'exc                 ', '����                          ', 'systemx/sysx_exp_sql.jsp                                                                            ', '����                                              ', 'V2.1.tamcx          ', '01                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('reportCondPz        ', 'def                 ', '����������ѯ                  ', 'system/reportCondPzLst.jsp                                                                          ', '����������ѯ                                      ', 'V2.1.tamcx          ', '02                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('user_menage         ', 'qry                 ', '��ѯ                          ', 'system/userMenage.jsp                                                                               ', '�û���ѯ                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('reportPz            ', 'edt                 ', '������Ϣ�޸�ҳ��              ', 'systemx/sysx_report.jsp                                                                             ', '������Ϣ�޸�ҳ��                                  ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('reportPz            ', 'upt                 ', '���±�����Ϣ                  ', 'systemx/sysx_report.jsp                                                                             ', '���±�����Ϣ                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('sendPz              ', 'serverdel           ', 'ɾ������                      ', 'app/gaps/sendServerPzLst.jsp                                                                        ', 'ɾ��������                                      ', 'V2.1.gaps           ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('sendPz              ', 'serverupt           ', 'ִ�з������                  ', 'app/gaps/sendServerPzLst.jsp                                                                        ', 'ִ�з�����                                      ', 'V2.1.gaps           ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('menux               ', 'del                 ', 'ɾ���˵�����                  ', 'systemx/sys_menu.jsp                                                                                ', 'ɾ���˵�������Ϣ                                  ', 'V2.1.tamcx          ', '01                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('menux               ', 'upt                 ', '�޸Ĳ˵�������Ϣ              ', 'systemx/sys_menu.jsp                                                                                ', '�޸Ĳ˵���������                                  ', 'V2.1.tamcx          ', '01                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('HundsunExtension    ', 'add                 ', '�������                      ', 'blank.html                                                                                          ', '�������                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_db_operator      ', 'add                 ', '���                          ', 'systemx/extension/dbInfoReg.jsp                                                                     ', '���                                              ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_report_cfg       ', 'add                 ', '������Ϣ                      ', 'app/extension/reportInfoReg.jsp                                                                     ', '������Ϣ                                          ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_table            ', 'add                 ', 'add                           ', 'app/extension/tableEdt.jsp                                                                          ', 'add                                               ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_xml_operator     ', 'add                 ', '��������                      ', 'app/extension/xmlInfoReg.jsp                                                                        ', '��������                                          ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_report_ctl       ', 'createfile          ', '���������ļ�                  ', 'blank.html                                                                                          ', '���������ļ�                                      ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('HundsunExtension    ', 'def                 ', 'Ĭ�Ͻ���                      ', 'blank.html                                                                                          ', 'Ĭ�Ͻ���                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('HundsunExtension    ', 'file                ', '�ļ�����                      ', 'blank.html                                                                                          ', '�ļ�����                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_page_dispatcher  ', 'fileView            ', '�ļ�����                      ', 'blank.html                                                                                          ', '�ļ�����                                          ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_di_test          ', 'get                 ', '��ȡ��Դ                      ', 'systemx/extension/TestDI.jsp                                                                        ', '��ȡ��Դ                                          ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_page_dispatcher  ', 'getOrgTree          ', '��ȡ������                    ', 'blank.html                                                                                          ', '��ȡ������                                        ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('HundsunExtension    ', 'getPageData         ', '��ȡ�����ʼ����              ', 'blank.html                                                                                          ', '��ȡ�����ʼ����                                  ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_xml_operator     ', 'getPkgInfo          ', '��ȡ������Ϣ                  ', 'app/extension/xmlInfoReg.jsp                                                                        ', '��ȡ������Ϣ                                      ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_db_operator      ', 'getRegTreeInfos     ', '��ȡע����Ϣ                  ', 'systemx/extension/dbInfoReg.jsp                                                                     ', '��ȡע����Ϣ                                      ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_report_cfg       ', 'getReportInfo       ', '��ȡ����������Ϣ              ', 'blank.html                                                                                          ', '��ȡ����������Ϣ                                  ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_page_dispatcher  ', 'getResource         ', '��ȡ��Դ                      ', 'blank.html                                                                                          ', '��ȡ��Դ                                          ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_db_operator      ', 'getTableColumns     ', '��ȡ���ݱ����                ', 'systemx/extension/dbInfoReg.jsp                                                                     ', '��ȡ���ݱ����                                    ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_db_operator      ', 'getTableNames       ', '��ȡ���ݿ��еı�              ', 'systemx/extension/dbInfoReg.jsp                                                                     ', '��ȡ���ݿ��еı�                                  ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_table            ', 'ins                 ', 'ins                           ', 'app/extension/tableLst.jsp                                                                          ', 'ins                                               ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_main_config      ', 'load                ', '�������ݼ���                  ', 'tx/configTree.html                                                                                  ', '�������ݼ���                                      ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_report_ctl       ', 'loaddata            ', '��������                      ', 'blank.html                                                                                          ', '��������                                          ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('HundsunExtension    ', 'lst                 ', '��ȡ������                    ', 'blank.html                                                                                          ', '��ȡ������                                        ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_db_operator      ', 'lst                 ', '���ݻ�ȡ                      ', 'systemx/extension/dbInfoReg.jsp                                                                     ', '���ݻ�ȡ                                          ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('HundsunExtension    ', 'send2gaps           ', '����JDOM��GAPS                ', 'blank.html                                                                                          ', '����JDOM��GAPS                                    ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_main_config      ', 'tpl                 ', 'ģ�巽ʽ����                  ', 'tx/configTree.html                                                                                  ', 'ģ�巽ʽ����                                      ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('HundsunExtension    ', 'upt                 ', '��������                      ', 'blank.html                                                                                          ', '��������                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_db_operator      ', 'upt                 ', '�޸�                          ', 'systemx/extension/dbInfoReg.jsp                                                                     ', '�޸�                                              ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_table            ', 'upt                 ', 'upt                           ', 'app/extension/tableLst.jsp                                                                          ', 'upt                                               ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('HundsunExtension    ', 'warrant             ', '��Ȩ                          ', 'blank.html                                                                                          ', '��Ȩ                                              ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_app_page_gen     ', 'def                 ', 'Ĭ�Ͻ���                      ', 'systemx/extension/appPageGenerator.jsp                                                              ', 'Ĭ�Ͻ���                                          ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_db_operator      ', 'def                 ', 'Ĭ�Ͻ���                      ', 'systemx/extension/dbInfoReg.jsp                                                                     ', 'Ĭ�Ͻ���                                          ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_di_test          ', 'def                 ', 'Ĭ�Ͻ���                      ', 'systemx/extension/TestDI.jsp                                                                        ', 'Ĭ�Ͻ���                                          ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_ext_doc          ', 'def                 ', 'EXT�����ĵ���ҳ               ', 'js/ext2.1/docs/link.html                                                                            ', 'EXT�����ĵ���ҳ                                   ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_main_config      ', 'def                 ', 'Ĭ�Ͻ���                      ', 'tx/configTree.html                                                                                  ', 'Ĭ�Ͻ���                                          ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_page_dispatcher  ', 'def                 ', 'ҳ����ת                      ', 'success.jsp                                                                                         ', 'ҳ����ת                                          ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_report_cfg       ', 'def                 ', 'Ĭ�Ͻ���                      ', 'app/extension/reportInfoReg.jsp                                                                     ', '��ȡҳ��                                          ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_report_ctl       ', 'def                 ', 'ҳ����ת                      ', 'blank.html                                                                                          ', 'ҳ����ת                                          ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_table            ', 'def                 ', 'def                           ', 'app/extension/tableLst.jsp                                                                          ', 'def                                               ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_xml_operator     ', 'def                 ', 'Ĭ�Ͻ���                      ', 'app/extension/xmlInfoReg.jsp                                                                        ', 'Ĭ�Ͻ���                                          ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('appversionmanage    ', 'def                 ', 'Ĭ��                          ', 'systemx/sysx_app_version.jsp                                                                        ', 'Ӧ�ð汾����Ĭ��ҳ                                ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('appversionmanage    ', 'list                ', '��ѯ                          ', 'systemx/sysx_app_version.jsp                                                                        ', '��ѯ                                              ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('appversionmanage    ', 'add                 ', '���                          ', 'systemx/sysx_app_version.jsp                                                                        ', '���                                              ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('appversionmanage    ', 'upt                 ', '����                          ', 'systemx/sysx_app_version.jsp                                                                        ', '����                                              ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('appversionmanage    ', 'del                 ', 'ɾ��                          ', 'systemx/sysx_app_version.jsp                                                                        ', 'ɾ��                                              ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('role_manage         ', 'def                 ', '��ѯ                          ', 'systemx/sysx_role_manage_new.jsp                                                                    ', '��ѯ                                              ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('role_manage         ', 'disAssign           ', 'ȡ����Ȩ                      ', 'systemx/sysx_role_manage_new.jsp                                                                    ', 'ȡ����Ȩ                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('role_manage         ', 'ins                 ', '��������                      ', 'systemx/sysx_role_manage_new.jsp                                                                    ', '��ɫ����                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('role_manage         ', 'list                ', '��ѯ                          ', 'systemx/sysx_role_manage_new.jsp                                                                    ', '��ѯ��ɫ��Ϣ                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('role_manage         ', 'lstprv              ', '�г�Ȩ��                      ', 'systemx/sysx_role_manage_new.jsp                                                                    ', '�г�Ȩ��                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('role_manage         ', 'doAssign            ', '�����ɫȨ��                  ', 'systemx/sysx_role_manage_new.jsp                                                                    ', '�����ɫȨ��                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('role_manage         ', 'upt                 ', '�޸ĸ���                      ', 'systemx/sysx_role_manage_new.jsp                                                                    ', '�޸ĸ��½�ɫ��Ϣ                                  ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('role_manage         ', 'add                 ', '��������                      ', 'systemx/sysx_role_manage_new.jsp                                                                    ', '���ӽ�ɫ����                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('role_manage         ', 'del                 ', 'ɾ��                          ', 'systemx/sysx_role_manage_new.jsp                                                                    ', 'ɾ����ɫ��Ϣ                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('HundsunExtension    ', 'sendGaps            ', '����GapsͨѶ����              ', 'blank.html                                                                                          ', '����GapsͨѶ����                                  ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('user_manage         ', 'assignUpt           ', '�������                      ', 'systemx/sysx_user_manage.jsp                                                                        ', '����Ȩ�޸���                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values('user_manage         ', 'warrantUpt          ', '��Ȩ����                      ', 'systemx/sysx_user_manage.jsp                                                                        ', '��Ȩ����                                          ', 'V2.1.tamcx', NULL, NULL, NULL);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('role_manage         ', 'toauth              ', '��ȡ����Ȩ                    ', 'systemx/sysx_role_manage_new.jsp                                                                    ', '��ȡ����Ȩ                                        ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('role_manage         ', 'authed              ', '��ȡ����Ȩ                    ', 'systgemx/sysx_role_manage_new.jsp                                                                   ', '��ȡ����Ȩ                                        ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('user_menage         ', 'def                 ', 'Ĭ��                          ', 'system/userMenage.jsp                                                                               ', 'Ĭ��                                              ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('statusmonitor       ', 'def                 ', 'Ĭ��                          ', 'systemx/sysx_status_monitor.jsp                                                                     ', 'Ĭ��                                              ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('HundsunExtension    ', 'del                 ', 'ɾ������                      ', 'blank.html                                                                                          ', 'ɾ������                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_db_operator      ', 'del                 ', 'ɾ��                          ', 'systemx/extension/dbInfoReg.jsp                                                                     ', 'ɾ��                                              ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_table            ', 'del                 ', 'del                           ', 'app/extension/tableLst.jsp                                                                          ', 'del                                               ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_report_ctl       ', 'downfile            ', '�����ļ�                      ', 'blank.html                                                                                          ', '�����ļ�                                          ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('dictManage          ', 'del                 ', 'ɾ��                          ', 'systemx/sysx_dict_manage.jsp                                                                        ', 'ɾ��                                              ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('dictManage          ', 'def                 ', '��ѯ                          ', 'systemx/sysx_dict_manage.jsp                                                                        ', 'Ĭ��                                              ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('dictManage          ', 'list                ', '�������                      ', 'systemx/sysx_dict_manage.jsp                                                                        ', '�������                                          ', 'V2.1.tamcx          ', '02                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('dictManage          ', 'add                 ', '��Ӹ���                      ', 'systemx/sysx_dict_manage.jsp                                                                        ', '��Ӹ���                                          ', 'V2.1.tamcx          ', '01                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('gapsconfig          ', 'serveradd           ', '���ӷ���                      ', 'systemx/sysx_gapsconfig.jsp                                                                         ', '���ӷ���ҳ��                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('gapsconfig          ', 'serverdef           ', 'Ĭ�Ϸ���                      ', 'systemx/sysx_gapsconfig.jsp                                                                         ', 'Ĭ�Ϸ���                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('gapsconfig          ', 'def                 ', 'ͨѶ��ѯ                      ', 'systemx/sysx_gapsconfig.jsp                                                                         ', 'ͨѶ                                              ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('gapsconfig          ', 'add                 ', '���ͨѶҳ��                  ', 'systemx/sysx_gapsconfig.jsp                                                                         ', '���ҳ��ͨѶ                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('gapsconfig          ', 'list                ', '��ѯͨѶ���                  ', 'systemx/sysx_gapsconfig.jsp                                                                         ', '��ѯͨѶ���                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('role_manage         ', 'assign              ', '��ɫ��Ȩ                      ', 'systemx/sysx_role_manage_new.jsp                                                                    ', '��ɫ��Ȩ                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('TranSubtran         ', 'del                 ', 'ɾ������                      ', 'systemx/sysx_transubtran.jsp                                                                        ', 'ɾ��������Ϣ                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('gapsconfig          ', 'del                 ', 'ɾ��ͨѶ                      ', 'systemx/sysx_gapsconfig.jsp                                                                         ', 'ɾ��ͨѶ                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('gapsconfig          ', 'conddef             ', 'Ĭ��ͨѶ����                  ', 'systemx/sysx_gapsconfig.jsp                                                                         ', 'ͨѶ����                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('gapsconfig          ', 'condadd             ', '���ͨѶ����ҳ��              ', 'systemx/sysx_gapsconfig.jsp                                                                         ', '�������ҳ��                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('gapsconfig          ', 'returndef           ', 'Ĭ��ͨѶ���                  ', 'systemx/sysx_gapsconfig.jsp                                                                         ', 'Ĭ��ͨѶ���                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('gapsconfig          ', 'returnadd           ', '����ͨѶ���ҳ��              ', 'systemx/sysx_gapsconfig.jsp                                                                         ', '����ͨѶ���ҳ��                                  ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('gapsconfig          ', 'returnedt           ', '�޸�ͨѶ���ҳ��              ', 'systemx/sysx_gapsconfig.jsp                                                                         ', '�޸�ͨѶ���ҳ��                                  ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('gapsconfig          ', 'returnupt           ', 'ִ��ͨѶ�������              ', 'systemx/sysx_gapsconfig.jsp                                                                         ', 'ִ�и���ͨѶ���                                  ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('gapsconfig          ', 'returndel           ', 'ɾ��ͨѶ���                  ', 'systemx/sysx_gapsconfig.jsp                                                                         ', 'ɾ��ͨѶ���                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('gapsconfig          ', 'condupt             ', 'ִ��ͨѶ��������              ', 'systemx/sysx_gapsconfig.jsp                                                                         ', 'ִ�и�������                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('gapsconfig          ', 'conddel             ', 'ɾ��ͨѶ����                  ', 'systemx/sysx_gapsconfig.jsp                                                                         ', 'ɾ������                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('org_manage          ', 'del                 ', 'ɾ������������Ϣ              ', 'systemx/sysx_org_manage.jsp                                                                         ', 'ɾ������������Ϣ                                  ', 'V2.1.tamcx          ', '01                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('org_manage          ', 'upt                 ', '�޸����û�����Ϣ              ', 'systemx/sysx_org_manage.jsp                                                                         ', '�޸Ļ�����������                                  ', 'V2.1.tamcx          ', '01                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('org_manage          ', 'list                ', '��ѯ                          ', 'systemx/sysx_org_manage.jsp                                                                         ', '��ѯ                                              ', 'V2.1.tamcx          ', '01                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('org_manage          ', 'get                 ', '��û�����ϸ��Ϣ              ', 'systemx/sysx_org_manage.jsp                                                                         ', '��û�����ϸ��Ϣ                                  ', 'V2.1.tamcx          ', '01                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('org_manage          ', 'add                 ', '���                          ', 'systemx/sysx_org_manage.jsp                                                                         ', '���                                              ', 'V2.1.tamcx          ', '01                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('user_manage         ', 'resetPass           ', '��������                      ', 'systemx/sysx_user_manage.jsp                                                                        ', '��������                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('user_manage         ', 'qry                 ', '��ѯ                          ', 'systemx/sysx_user_manage.jsp                                                                        ', '�û���ѯ                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('user_manage         ', 'del                 ', 'ɾ��                          ', 'systemx/sysx_user_manage.jsp                                                                        ', 'ɾ���û���Ϣ                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('user_manage         ', 'roleAss             ', '��ɫ����                      ', 'systemx/sysx_user_manage.jsp                                                                        ', '��ɫ����                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('user_manage         ', 'roleAssUpt          ', '��ɫ�������                  ', 'systemx/sysx_user_manage.jsp                                                                        ', '��ɫ�������                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('user_manage         ', 'tranAss             ', '���׷���                      ', 'systemx/sysx_user_manage.jsp                                                                        ', '����Ȩ�޷���                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('reportPz            ', 'lst                 ', '��ѯ                          ', 'systemx/sysx_report.jsp                                                                             ', '��ѯ                                              ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('sendPz              ', 'upt                 ', 'ִ��ͨѶ����                  ', 'app/gaps/sendPzNew.jsp                                                                              ', 'ִ�и���ͨѶ                                      ', 'V2.1.gaps           ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('org_manage          ', 'def                 ', 'Ĭ��                          ', 'systemx/sysx_org_manage.jsp                                                                         ', 'Ĭ��                                              ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('user_manage         ', 'tranAssUpt          ', '���׷������                  ', 'systemx/sysx_user_manage.jsp                                                                        ', '����Ȩ�޷������                                  ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('user_manage         ', 'dataAss             ', '���ݷ���                      ', 'systemx/sysx_user_manage.jsp                                                                        ', '����Ȩ�޷���                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('user_manage         ', 'dataAssUpt          ', '���ݷ������                  ', 'systemx/sysx_user_manage.jsp                                                                        ', '����Ȩ�޷������                                  ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('user_manage         ', 'add                 ', '����ҳ��                      ', 'systemx/sysx_user_manage.jsp                                                                        ', '�����û���Ϣҳ��                                  ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('user_manage         ', 'def                 ', 'Ĭ��                          ', 'systemx/sysx_user_manage.jsp                                                                        ', 'Ĭ��                                              ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('user_manage         ', 'upt                 ', '����                          ', 'systemx/sysx_user_manage.jsp                                                                        ', '�����û���Ϣ                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('user_manage         ', 'warrant             ', '��Ȩ                          ', 'systemx/sysx_user_manage.jsp                                                                        ', '��Ȩ                                              ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('user_manage         ', 'list                ', '��ѯ�û�                      ', 'systemx/sysx_user_manage.jsp                                                                        ', '��ѯ�û���ʾ������                                ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('user_manage         ', 'lstprv              ', '�г�Ȩ��                      ', 'systemx/sysx_user_manage.jsp                                                                        ', '�г�Ȩ��                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('refresh_param       ', 'def                 ', 'ϵͳ����ˢ��                  ', 'system/refreshParam.jsp                                                                             ', 'ϵͳ����ˢ��                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('system_param        ', 'def                 ', 'Ĭ��                          ', 'systemx/sysx_parammanage.jsp                                                                        ', 'ϵͳ����ά��                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('system_param        ', 'list                ', 'Ĭ��                          ', 'systemx/sysx_parammanage.jsp                                                                        ', 'ϵͳ����ά��                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('system_param        ', 'add                 ', 'Ĭ��                          ', 'systemx/sysx_parammanage.jsp                                                                        ', 'ϵͳ����ά��                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('system_param        ', 'upt                 ', 'Ĭ��                          ', 'systemx/sysx_parammanage.jsp                                                                        ', 'ϵͳ����ά��                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('menux               ', 'list                ', '��ѯ                          ', 'systemx/sys_menu.jsp                                                                                ', '��ѯ                                              ', 'V2.1.tamcx          ', '01                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('menux               ', 'get                 ', '��ò˵���ϸ                  ', 'systemx/sys_menu.jsp                                                                                ', '��õ����˵���Ϣ                                  ', 'V2.1.tamcx          ', '01                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('menux               ', 'add                 ', '���                          ', 'systemx/sys_menu.jsp                                                                                ', '���                                              ', 'V2.1.tamcx          ', '01                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('menux               ', 'def                 ', '��ʾ�˵���                    ', 'systemx/sys_menu.jsp                                                                                ', '��ѯ�˵���Ϣ,�����β˵���ʾ                       ', 'V2.1.tamcx          ', '01                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('usermacheck         ', 'def                 ', 'Ĭ��                          ', 'systemx/sysx_userma_check.jsp                                                                       ', 'Ĭ��                                              ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('usermacheck         ', 'list                ', '��ѯ                          ', 'about:blank                                                                                         ', '��ѯ                                              ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('usermacheck         ', 'chk                 ', '���                          ', 'about:blank                                                                                         ', '���                                              ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('usermacheck         ', 'del                 ', 'ɾ��                          ', 'about:blank                                                                                         ', 'ɾ������ͨ����˵��û�                            ', 'V2.1.zhhr           ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('ipreg               ', 'def                 ', 'Ĭ��                          ', 'systemx/sysx_ip_reg.jsp                                                                             ', 'Ĭ��                                              ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('ipreg               ', 'list                ', '��ѯ                          ', 'systemx/sysx_ip_reg.jsp                                                                             ', '��ѯ                                              ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('ipreg               ', 'add                 ', '����                          ', 'systemx/sysx_ip_reg.jsp                                                                             ', '����                                              ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('ipreg               ', 'upt                 ', '�޸�                          ', 'systemx/sysx_ip_reg.jsp                                                                             ', '�޸�                                              ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('ipreg               ', 'del                 ', 'ɾ��                          ', 'systemx/sysx_ip_reg.jsp                                                                             ', 'ɾ��                                              ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('changePwd           ', 'change              ', '�޸�����                      ', 'systemx/sysx_change_pwd.jsp                                                                         ', '�޸�����                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('reportPz            ', 'listPara            ', '��ѯ��������                  ', 'systemx/sysx_report.jsp                                                                             ', '��ѯ��������                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('reportPz            ', 'uptPara             ', '�޸ı�������                  ', 'systemx/sysx_report.jsp                                                                             ', '�޸ı�������                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('reportPz            ', 'delPara             ', 'ɾ����������                  ', 'systemx/sysx_report.jsp                                                                             ', 'ɾ����������                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('reportPz            ', 'addPara             ', '���ӱ�������                  ', 'systemx/sysx_report.jsp                                                                             ', '���ӱ�������                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('pzjyexport          ', 'def                 ', 'Ĭ��                          ', 'systemx/extension/pzjyexport.jsp                                                                    ', 'Ĭ��                                              ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('pzjyexport          ', 'export              ', '����                          ', 'systemx/extension/pzjyexport.jsp                                                                    ', '����                                              ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('pzjyexport          ', 'down                ', '����                          ', 'systemx/extension/pzjyexport.jsp                                                                    ', '����                                              ', 'V2.1.tx             ', null, null, null);


insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('tx_page_dispatcher  ', 'TXҳ����ת����                ', '0', 'com.hundsun.tamcx.app.extension.ctl.DispatcherCtl                                                   ', 'V2.1.tx             ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('tx_report_cfg       ', 'TX������                    ', '1', 'com.hundsun.tamcx.app.extension.ctl.ReportPzCtl                                                     ', 'V2.1.tx             ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('tx_report_ctl       ', 'TX�򵥱�������                ', '2', 'com.hundsun.tamcx.app.extension.system.ReportProcessCtl                                             ', 'V2.1.tx             ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('tx_table            ', 'TX���ݿ�����                ', '0', 'com.hundsun.tamcx.app.extension.ctl.TableCtl                                                        ', 'V2.1.tx             ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('tx_xml_operator     ', 'xml��������                   ', '0', 'com.hundsun.tamcx.app.extension.ctl.GapsCommCtl                                                     ', 'V2.1.tx             ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('sendPz              ', '�������ù���                  ', '0', ' com.hundsun.agent.gaps.MessageSendCtl                                                              ', 'V2.1.gaps           ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('send                ', '����                          ', '0', ' com.hundsun.agent.gaps.SystemSendCtl                                                               ', 'V2.1.gaps           ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('gapsdown            ', '��GAPS����ļ�                ', '0', ' com.hundsun.agent.send.GapsDownCtl                                                                 ', 'V2.1.gaps           ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('cpsj_manage         ', '��Ʒ��������                  ', '0', 'com.hundsun.tamcx.system.cpsj.CpsjManageCtl                                                         ', 'V2.1.tamcx          ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('TranSubtran         ', '��������                      ', '0', 'com.hundsun.tamcx.systemx.ctl.TranSubtranCtl                                                        ', 'V2.1.tamcx          ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('menu_conf           ', '�˵�����                      ', '0', 'com.hundsun.tamcx.systemx.ctl.MenuConfCtl                                                           ', 'V2.1.tamcx          ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('refresh_param       ', 'ˢ��ϵͳ����                  ', '0', 'com.hundsun.tamcx.systemx.ctl.RefreshParamCtl                                                       ', 'V2.1.tamcx          ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('logon               ', '�û���¼                      ', '0', 'com.hundsun.tamcx.system.ctl.LogonCtl                                                               ', 'V2.1.tamcx          ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('user_menage         ', '�û�����                      ', '0', 'com.hundsun.tamcx.system.ctl.UserMenageCtl                                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('dict_menage         ', '�����ֵ����                  ', '0', 'com.hundsun.tamcx.system.ctl.DictMenageCtl                                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('system_param        ', 'ϵͳ��������                  ', '0', 'com.hundsun.tamcx.systemx.ctl.SystemParamCtl                                                        ', 'V2.1.tamcx          ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('tamcx_upgrade       ', '��Ʒ����                      ', '0', 'com.hundsun.tamcx.system.ctl.TamcxUpgradeCtl                                                        ', 'V2.1.tamcx          ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('reportPz            ', '��������                      ', '0', 'com.hundsun.tamcx.systemx.ctl.ReportPzCtl                                                           ', 'V2.1.tamcx          ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('reportCondPz        ', '������������                  ', '0', 'com.hundsun.tamcx.system.report.ReportCondPzCtl                                                     ', 'V2.1.tamcx          ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('ipMenage            ', '��¼IP����                    ', '0', 'com.hundsun.tamcx.system.ctl.IpMenageCtl                                                            ', 'V2.1.tamcx          ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('expsql              ', '����SQL                       ', '0', 'com.hundsun.tamcx.systemx.util.ExpSql                                                               ', 'V2.1.tamcx          ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('mvSend              ', 'GAPSͨѶ[��Ȩ]                ', '0', ' com.hundsun.agent.gaps.MvSystemSendCtl                                                             ', 'V2.1.gaps           ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('test2               ', 'test2                         ', '2', 'com.hundsun.tamcx.systemx.extension.ctl.HundsunExtension                                            ', 'V2.1.tx             ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('usermacheck         ', '�û����                      ', '0', 'com.hundsun.tamcx.systemx.ctl.UserMaCheckCtl                                                        ', 'V2.1.tamcx          ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('dictManage          ', 'ϵͳ�����ֵ����              ', '1', 'com.hundsun.tamcx.systemx.ctl.DictManageCtl                                                         ', 'V2.1.tamcx          ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('gapsconfig          ', 'GAPSͨѶ����                  ', '0', 'com.hundsun.tamcx.systemx.ctl.GapsConfigCtl                                                         ', 'V2.1.tamcx          ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('org_manage          ', '��������                      ', '0', 'com.hundsun.tamcx.systemx.ctl.OrgManageCtl                                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('role_manage         ', '��ɫ����                      ', '0', 'com.hundsun.tamcx.systemx.ctl.RoleManageCtl                                                         ', 'V2.1.tamcx          ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('user_manage         ', '�û�����                      ', '0', 'com.hundsun.tamcx.systemx.ctl.UserManageCtl                                                         ', 'V2.1.tamcx          ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('ipreg               ', 'IP�Ǽǹ���                    ', '0', 'com.hundsun.tamcx.systemx.ctl.IpRegCtl                                                              ', 'V2.1.tamcx          ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('statusmonitor       ', '����״̬                      ', '0', 'com.hundsun.tamcx.systemx.ctl.StatusMonitorCtl                                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('appversionmanage    ', 'Ӧ�ð汾����                  ', '0', 'com.hundsun.tamcx.systemx.ctl.AppVersionManageCtl                                                   ', 'V2.1.tamcx          ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('report              ', '�����ѯ                      ', '1', 'com.hundsun.tamcx.systemx.report.ReportCtl                                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('changePwd           ', '�޸�����                      ', '0', 'com.hundsun.tamcx.systemx.ctl.ChangePasswordCtl                                                     ', 'V2.1.tamcx          ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('alterUserPass       ', '�޸��û�����                  ', '0', 'com.hundsun.tamcx.system.ctl.AlterUserPassCtl                                                       ', 'V2.1.tamcx          ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('menux               ', '�˵�����                      ', '0', 'com.hundsun.tamcx.systemx.ctl.MenuConfCtl                                                           ', 'V2.1.tamcx          ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('HundsunExtension    ', 'TXͨ������                    ', '0', 'com.hundsun.tamcx.systemx.extension.ctl.HundsunExtension                                            ', 'V2.1.tx             ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('tx_app_page_gen     ', 'Ӧ�ý�������                  ', '0', 'com.hundsun.tamcx.systemx.extension.di.DIControl                                                    ', 'V2.1.tx             ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('tx_composite_cfg    ', 'TX�������                    ', '0', 'com.hundsun.tamcx.app.extension.ctl.CompositeCtl                                                    ', 'V2.1.tx             ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('tx_db_operator      ', 'TX���ݿ��ά��                ', '0', 'com.hundsun.tamcx.systemx.extension.ctl.DbOperatorCtl                                               ', 'V2.1.tx             ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('tx_di_test          ', '���ݽӿڲ���                  ', '0', 'com.hundsun.tamcx.systemx.extension.di.DIControl                                                    ', 'V2.1.tx             ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('tx_ext_doc          ', 'EXT �����ĵ�                  ', '0', 'com.hundsun.tamcx.app.extension.di.DIControl                                                        ', 'V2.1.tx             ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('tx_main_config      ', 'TX������ý���                ', '0', 'com.hundsun.tamcx.app.extension.ctl.ConfigCtl                                                       ', 'V2.1.tx             ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('pzjyexport          ', '���ý��׵���                  ', '1', 'com.hundsun.tamcx.systemx.extension.ctl.PzjyExportCtl                                               ', 'V2.1.tx             ', null, null, null);
