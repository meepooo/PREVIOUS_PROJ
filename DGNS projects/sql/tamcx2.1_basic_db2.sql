/*
由 叶德铭 于 2011-10-13 10:34:22 上午
 日生成的脚本数据库：agtdb2
架构：AGTDB2
对象：TABLE
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
COMMENT ON TABLE T_ORG IS '管理登记系统内机构信息和通过行内机构代理参加业务的系统外机构信息。'
;
COMMENT ON COLUMN T_ORG.ORG_ID IS '机构号'
;
COMMENT ON COLUMN T_ORG.ORG_NAME IS '机构简称'
;
COMMENT ON COLUMN T_ORG.ORG_DESC IS '机构名称'
;
COMMENT ON COLUMN T_ORG.ABOVE_ORG_ID IS '上级机构号'
;
COMMENT ON COLUMN T_ORG.INNER_ORG_ID IS '便于管理台进行按机构进行查询、统计
可以不填   为tamc提供冗余'
;
COMMENT ON COLUMN T_ORG.ORG_LEVEL IS '0-总行清算中心
1－一级分行
2－二级分行
3－支行
4－分理处
5－村镇银行'
;
COMMENT ON COLUMN T_ORG.ORG_ADRESS IS '联系地址'
;
COMMENT ON COLUMN T_ORG.ORG_TYPE IS '可以不填   为tamc提供冗余'
;
COMMENT ON COLUMN T_ORG.TEL IS '联系电话'
;
COMMENT ON COLUMN T_ORG.EMAIL IS '电子邮箱'
;
COMMENT ON COLUMN T_ORG.BAK1 IS '该字段可以用来存放虚拟柜员'
;
COMMENT ON COLUMN T_ORG.BAK2 IS '备用2'
;
COMMENT ON COLUMN T_ORG.BAK3 IS '备用3';
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
COMMENT ON TABLE T_USER IS '用户信息表'
;
COMMENT ON COLUMN T_USER.USER_ID IS '主键'
;
COMMENT ON COLUMN T_USER.STATION IS '取自字典表:station'
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
COMMENT ON COLUMN T_USER.STATUS IS '0:创建 1:正常 2:已登录 9:注销';
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
values ('tamcx     ', 'ORDER_T_APP_CONST             ', '对T_APP_CONST按照APP_ID,EXT_ID排序                                                                  ', 'APP_ID,EXT_ID', null, null, null);
insert into T_APP_CONST (APP_ID, EXT_ID, EXT_DESC, EXT_VALUE, BAK1, BAK2, BAK3)
values ('tamcx     ', 'ORDER_T_APP_REG               ', '对T_APP_REG表进行APP_ID排序                                                                         ', 'APP_ID', null, null, null);
insert into T_APP_CONST (APP_ID, EXT_ID, EXT_DESC, EXT_VALUE, BAK1, BAK2, BAK3)
values ('tamcx     ', 'ORDER_T_APP_RESOURCE          ', '对T_APP_RESOURCE按照ORDER_ID排序                                                                    ', 'APP_ID,ORDER_ID', null, null, null);
insert into T_APP_CONST (APP_ID, EXT_ID, EXT_DESC, EXT_VALUE, BAK1, BAK2, BAK3)
values ('tamcx     ', 'ORDER_T_TRAN_REG              ', '对T_TRAN_REG按照APP_ID,TRAN_ID排序                                                                  ', 'APP_ID,TRAN_ID', null, null, null);
insert into T_APP_CONST (APP_ID, EXT_ID, EXT_DESC, EXT_VALUE, BAK1, BAK2, BAK3)
values ('tamcx     ', 'SELECT_DICT_APP               ', '获取T_APP表中的APP_ID和APP_NAME作为数据字典                                                         ', '${sql:select APP_ID as V, APP_NAME as D from T_APP_REG}', null, null, null);
insert into T_APP_CONST (APP_ID, EXT_ID, EXT_DESC, EXT_VALUE, BAK1, BAK2, BAK3)
values ('tamcx     ', 'SELECT_ORGTREE1               ', '获取当前机构下的机构数据                                                                            ', '${sql:select org_id as node_id,org_name as node_text,(select count(t2.org_id) from t_org t2 where t2.above_org_id=t1.org_id) as node_leaf,org_id as node_value from t_org t1 where t1.org_id=^${context:orgId}^ and t1.org_id<> ^0001^}', null, null, null);
insert into T_APP_CONST (APP_ID, EXT_ID, EXT_DESC, EXT_VALUE, BAK1, BAK2, BAK3)
values ('tamcx     ', 'SELECT_ORGTREE2               ', '获取当前机构下的机构数据第二层，三层....                                                            ', '${sql:select org_id as node_id,org_name as node_text,(select count(t2.org_id)  from t_org t2 where t2.above_org_id=t1.org_id) as node_leaf, org_id as node_value from t_org t1 where above_org_id=^${params:node}^ and org_id<> ^0001^}', null, null, null);


insert into T_APP_REG (APP_ID, APP_NAME, BAK)
values ('tamcx', 'Tamcx管理平台', null);


insert into T_EXT_UI_REG (UI_ID, XTYPE, UI_NAME, UI_DESC, UI_TYPE, UI_RESOURCE, UI_CLASS, EXT1, EXT2, EXT3)
values ('checkbox                      ', 'checkbox                      ', '单选框                                            ', '用于单选数据的输入', '1', 'js/ext2.1/ext-all.js                                                                                ', null, null, null, null);
insert into T_EXT_UI_REG (UI_ID, XTYPE, UI_NAME, UI_DESC, UI_TYPE, UI_RESOURCE, UI_CLASS, EXT1, EXT2, EXT3)
values ('combo                         ', 'combo                         ', '下拉选择框                                        ', '用于下拉数据的数据', '1', 'js/ext2.1/ext-all.js                                                                                ', null, null, null, null);
insert into T_EXT_UI_REG (UI_ID, XTYPE, UI_NAME, UI_DESC, UI_TYPE, UI_RESOURCE, UI_CLASS, EXT1, EXT2, EXT3)
values ('datefield                     ', 'datefield                     ', '日期输入框                                        ', '用于日期输入', '1', 'js/ext2.1/ext-all.js                                                                                ', null, null, null, null);
insert into T_EXT_UI_REG (UI_ID, XTYPE, UI_NAME, UI_DESC, UI_TYPE, UI_RESOURCE, UI_CLASS, EXT1, EXT2, EXT3)
values ('decimal                       ', 'numberfield                   ', '浮点数输入框                                      ', '用于浮点数的输入', '1', 'js/ext2.1/ext-all.js                                                                                ', null, null, null, null);
insert into T_EXT_UI_REG (UI_ID, XTYPE, UI_NAME, UI_DESC, UI_TYPE, UI_RESOURCE, UI_CLASS, EXT1, EXT2, EXT3)
values ('fileview                      ', 'fileview                      ', '可以下载和查看文件                                ', '制定文件路径后可以下载文件', '1', 'app/extension/FileView.js                                                                           ', null, null, null, null);
insert into T_EXT_UI_REG (UI_ID, XTYPE, UI_NAME, UI_DESC, UI_TYPE, UI_RESOURCE, UI_CLASS, EXT1, EXT2, EXT3)
values ('hidden                        ', 'hidden                        ', '隐藏输入框                                        ', '用于隐含传值', '1', 'js/ext2.1/ext-all.js                                                                                ', null, null, null, null);
insert into T_EXT_UI_REG (UI_ID, XTYPE, UI_NAME, UI_DESC, UI_TYPE, UI_RESOURCE, UI_CLASS, EXT1, EXT2, EXT3)
values ('integer                       ', 'numberfield                   ', '整数输入框                                        ', '用于整型数据输入', '1', 'js/ext2.1/ext-all.js                                                                                ', null, null, null, null);
insert into T_EXT_UI_REG (UI_ID, XTYPE, UI_NAME, UI_DESC, UI_TYPE, UI_RESOURCE, UI_CLASS, EXT1, EXT2, EXT3)
values ('money                         ', 'numberfield                   ', '金额输入框                                        ', '金额数据库', '1', 'js/ext2.1/ext-all.js                                                                                ', null, null, null, null);
insert into T_EXT_UI_REG (UI_ID, XTYPE, UI_NAME, UI_DESC, UI_TYPE, UI_RESOURCE, UI_CLASS, EXT1, EXT2, EXT3)
values ('numberfield                   ', 'numberfield                   ', '数值输入框                                        ', '用于数值数据输入', '1', 'js/ext2.1/ext-all.js                                                                                ', null, null, null, null);
insert into T_EXT_UI_REG (UI_ID, XTYPE, UI_NAME, UI_DESC, UI_TYPE, UI_RESOURCE, UI_CLASS, EXT1, EXT2, EXT3)
values ('password                      ', 'textfield                     ', '密码输入框                                        ', '密码输入框', '1', 'js/ext2.1/ext-all.js                                                                                ', null, null, null, null);
insert into T_EXT_UI_REG (UI_ID, XTYPE, UI_NAME, UI_DESC, UI_TYPE, UI_RESOURCE, UI_CLASS, EXT1, EXT2, EXT3)
values ('tamcxorg                      ', 'tamcxorgcombo                 ', 'tamcx 机构选择框                                  ', '用于选择tamcx中的机构数据', '1', 'app/extendsion/ext.ux/ExtUX.js                                                                      ', null, null, null, null);
insert into T_EXT_UI_REG (UI_ID, XTYPE, UI_NAME, UI_DESC, UI_TYPE, UI_RESOURCE, UI_CLASS, EXT1, EXT2, EXT3)
values ('textarea                      ', 'textarea                      ', '文本输入区                                        ', '用于多数据文本输入', '1', 'js/ext2.1/ext-all.js                                                                                ', null, null, null, null);
insert into T_EXT_UI_REG (UI_ID, XTYPE, UI_NAME, UI_DESC, UI_TYPE, UI_RESOURCE, UI_CLASS, EXT1, EXT2, EXT3)
values ('textfield                     ', 'textfield                     ', '文本输入框                                        ', '用于文本数据的输入', '1', 'js/ext2.1/ext-all.js                                                                                ', null, null, null, null);
insert into T_EXT_UI_REG (UI_ID, XTYPE, UI_NAME, UI_DESC, UI_TYPE, UI_RESOURCE, UI_CLASS, EXT1, EXT2, EXT3)
values ('timefield                     ', 'timefield                     ', '时间输入框                                        ', '用于时间的选择', '1', 'js/ext2.1/ext-all.js                                                                                ', null, null, null, null);
insert into T_EXT_UI_REG (UI_ID, XTYPE, UI_NAME, UI_DESC, UI_TYPE, UI_RESOURCE, UI_CLASS, EXT1, EXT2, EXT3)
values ('tipsdqcombo                   ', 'tipsdqcombo                   ', '用于选择tips需要的地区代号                        ', '用于选择tips需要的地区代号', '1', 'app/extension/ext.ux/ExtUX.js                                                                       ', null, null, null, null);
insert into T_EXT_UI_REG (UI_ID, XTYPE, UI_NAME, UI_DESC, UI_TYPE, UI_RESOURCE, UI_CLASS, EXT1, EXT2, EXT3)
values ('tipsjgcombo                   ', 'tipsjgcombo                   ', '用于选择tips中需要的机构代码                      ', '用于选择tips中需要的机构代码', '1', 'app/extendsion/ext.ux/ExtUX.js                                                                      ', null, null, null, null);
insert into T_EXT_UI_REG (UI_ID, XTYPE, UI_NAME, UI_DESC, UI_TYPE, UI_RESOURCE, UI_CLASS, EXT1, EXT2, EXT3)
values ('treecombo                     ', 'treecombo                     ', '树形结构下拉框                                    ', '提供数据支持的树形结构下拉框', '1', 'app/extension/ext.ux/ExtUx.js                                                                       ', null, null, null, null);
insert into T_EXT_UI_REG (UI_ID, XTYPE, UI_NAME, UI_DESC, UI_TYPE, UI_RESOURCE, UI_CLASS, EXT1, EXT2, EXT3)
values ('uxcombo                       ', 'uxcombo                       ', '下拉选择框(使用数据接口)                          ', '用于下列数据的输入', '1', 'app/extension/ext.ux/ExtUX.js                                                                       ', null, null, null, null);
insert into T_EXT_UI_REG (UI_ID, XTYPE, UI_NAME, UI_DESC, UI_TYPE, UI_RESOURCE, UI_CLASS, EXT1, EXT2, EXT3)
values ('ux-radiogroup                 ', 'ux-radiogroup                 ', '单选框                                            ', '圆形单选框', '1', 'script/ext-2.0.2/app/Ext.ux.Radio.js                                                                ', '                                                  ', '                              ', '                                                            ', '                                                                                          ');



insert into T_IP (IP, IP_DESC, BAK)
values ('127.0.0.1           ', '本网                          ', null);


insert into T_ORG (ORG_ID, ORG_NAME, ORG_DESC, ORG_TYPE, ORG_LEVEL, ABOVE_ORG_ID, INNER_ORG_ID, TEL, EMAIL, ORG_ADRESS, BAK1, BAK2, BAK3)
values ('00000           ', '顶级机构                                          ', '虚拟机构                                                    ', null, '0', '/               ', '100                        ', null, null, null, null, null, null);


insert into T_SEND_SERVER (ID, SERNAME, IP, PORT, TYPEID, CSTIME)
values ('0088                          ', '本机模拟GAPS                                      ', '127.0.0.1           ', 8081, '0', 60);


insert into T_SYS_PARAM (PARAM_ID, PARAM_NAME, PARAM_VALUE, PARAM_TYPE, VERSION, BAK)
values ('web_file_path       ', '文件备份路径                  ', 'app/infoDown/                                                                                                                   ', '0', 'V2.1.tamcx          ', null);


insert into T_USER (USER_ID, USER_NAME, ORG_ID, PASSWD, OLD_PASSWD, STATION, CREAT_DATE, CREAT_TIME, ALTER_DATE, ALTER_TIME, DEL_DATE, TEL, EMAIL, STATUS, SEX, ACADEMIC, CERTI_TYPE, CERTI, FAX, ADRESS, POSTCODE, BAK1, BAK2, BAK3, BAK4, BAK5)
values ('admin          ', '超级管理员          ', '00000     ', 'FF5E61835C355E755EEF9321        ', 'A43B59E342F86CEE5EEF9321        ', '0     ', '20071201', '101010', null, null, null, null, null, '2', null, null, null, null, null, null, null, null, null, null, null, null);


insert into T_VERSION (APP_ID, APP_NAME, VERSION_ID, REGUSER, REGDATE, BAK1, BAK2, BAK3, BAK4, BAK5)
values ('test                          ', 'test                                                        ', '2.1                 ', 'lecky               ', '20110831', null, null, null, null, null);
insert into T_VERSION (APP_ID, APP_NAME, VERSION_ID, REGUSER, REGDATE, BAK1, BAK2, BAK3, BAK4, BAK5)
values ('tamcx                         ', 'TAMCX框架                                                   ', 'V2.1.tamcx          ', 'jeffreyLu           ', '20110311', null, null, null, null, null);
insert into T_VERSION (APP_ID, APP_NAME, VERSION_ID, REGUSER, REGDATE, BAK1, BAK2, BAK3, BAK4, BAK5)
values ('bots                          ', '批量处理                                                    ', 'V2.1.bots           ', 'jeffreyLu           ', '20110313', null, null, null, null, null);
insert into T_VERSION(APP_ID, APP_NAME, VERSION_ID, REGUSER, REGDATE, BAK1, BAK2, BAK3, BAK4, BAK5)
  VALUES('dsf                           ', '代收付业务                                                  ', 'V2.1.dsf            ', 'jeffreyLu           ', '20110715', NULL, NULL, NULL, NULL, NULL);
insert into T_VERSION (APP_ID, APP_NAME, VERSION_ID, REGUSER, REGDATE, BAK1, BAK2, BAK3, BAK4, BAK5)
values ('btoo                          ', '批转联                                                      ', 'V2.1.btoo           ', 'jeffreyLu           ', '20110313', null, null, null, null, null);
insert into T_VERSION (APP_ID, APP_NAME, VERSION_ID, REGUSER, REGDATE, BAK1, BAK2, BAK3, BAK4, BAK5)
values ('gaps                          ', 'GAPS通讯                                                    ', 'V2.1.gaps           ', 'jeffreyLu           ', '20110312', null, null, null, null, null);
insert into T_VERSION (APP_ID, APP_NAME, VERSION_ID, REGUSER, REGDATE, BAK1, BAK2, BAK3, BAK4, BAK5)
values ('app                           ', '公共业务                                                    ', 'V2.1.app            ', 'jeffreyLu           ', '20110411', null, null, null, null, null);
insert into T_VERSION (APP_ID, APP_NAME, VERSION_ID, REGUSER, REGDATE, BAK1, BAK2, BAK3, BAK4, BAK5)
values ('tx                            ', 'Tamcx Extension                                             ', 'V2.1.tx             ', 'jeffreyLu           ', '20110411', null, null, null, null, null);


insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('color_type                    ', '绿                            ', '0                             ', '#009933                       ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('color_type                    ', '红                            ', '1                             ', '#FF0000                       ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('color_type                    ', '蓝                            ', '2                             ', '#3333CC                       ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('color_type                    ', '橙                            ', '3                             ', '#FF9900                       ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('color_type                    ', '紫                            ', '4                             ', '#993399                       ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('color_type                    ', '粉                            ', '5                             ', '#FF6699                       ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('send_type                     ', '交易配置类型                  ', '0                             ', '默认通讯                      ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('send_type                     ', '交易配置类型                  ', '1                             ', '显示信息                      ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('send_type                     ', '交易配置类型                  ', '2                             ', '文件下载                      ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('send_type                     ', '交易配置类型                  ', '3                             ', '文件展示打印                  ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('send_type                     ', '交易配置类型                  ', '4                             ', '集合信息                      ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('send_returnType               ', '交易结果类型                  ', '0                             ', '信息                          ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('send_returnType               ', '交易结果类型                  ', '4                             ', '打印                          ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('send_returnType               ', '交易结果类型                  ', '1                             ', '金额                          ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('send_returnType               ', '交易结果类型                  ', '2                             ', '文件                          ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('send_returnType               ', '交易结果类型                  ', '3                             ', '字典                          ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('send_cond_type                ', '交易条件类型                  ', '1                             ', '文本框                        ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('send_cond_type                ', '交易条件类型                  ', '2                             ', '选择框                        ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('send_cond_type                ', '交易条件类型                  ', '3                             ', '日期                          ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('send_cond_type                ', '交易条件类型                  ', '4                             ', '机构列表                      ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('send_cond_type                ', '交易条件类型                  ', '5                             ', '万能类型                      ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('send_cond_type                ', '交易条件类型                  ', '6                             ', '隐藏文本框                    ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('send_cond_type                ', '交易条件类型                  ', '7                             ', '数字文本框                    ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('send_cond_type                ', '交易条件类型                  ', '8                             ', '多行文本框                    ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('send_cond_type                ', '交易条件类型                  ', '9                             ', '数据库选择框                  ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('gaps_send_retType             ', 'GAPS通讯结果返回类型          ', '0                             ', '正确时返回                    ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('gaps_send_retType             ', 'GAPS通讯结果返回类型          ', '1                             ', '错误时返回                    ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tamcx_log                     ', '日志类型                      ', '0                             ', 'debug                         ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tamcx_log                     ', '日志类型                      ', '1                             ', 'fatal                         ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tamcx_log                     ', '日志类型                      ', '2                             ', 'info                          ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tamcx_log                     ', '日志类型                      ', '3                             ', 'error                         ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('user_academic                 ', '学历                          ', '3                             ', '高中                          ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_report_text_align          ', '对齐方式                      ', '1                             ', '左对齐                        ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('user_academic                 ', '学历                          ', '4                             ', '中专                          ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('send_cond_type                ', '交易条件类型                  ', '0                             ', '单选框                        ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('report_data_type              ', '报表数据类型                  ', '8                             ', '模糊查String                  ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('report_data_type              ', '报表数据类型                  ', '1                             ', 'String                        ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('report_data_type              ', '报表数据类型                  ', '3                             ', 'Double                        ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('report_data_type              ', '报表数据类型                  ', '4                             ', 'Float                         ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('report_data_type              ', '报表数据类型                  ', '5                             ', 'Integer                       ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('report_data_type              ', '报表数据类型                  ', '6                             ', 'Long                          ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('report_data_type              ', '报表数据类型                  ', '7                             ', 'Short                         ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('report_data_type              ', '报表数据类型                  ', '2                             ', 'BigDecimal                    ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('system_id                     ', '系统标识                      ', 'tamcx                         ', 'tamcx系统                     ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('cond_type                     ', '报表条件类型                  ', '1                             ', '文本框                        ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('cond_type                     ', '报表条件类型                  ', '2                             ', '选择框                        ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('cond_type                     ', '报表条件类型                  ', '3                             ', '日期                          ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('cond_type                     ', '报表条件类型                  ', '4                             ', '机构列表                      ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('cond_type                     ', '报表条件类型                  ', '5                             ', '万能类型                      ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK) 
values ('cond_type','报表条件类型','7','数字文本框','V2.1.tamcx','');
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('cond_type','报表条件类型','8','多行文本框','V2.1.tamcx','');
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('cond_type','报表条件类型','9','数据库选择框','V2.1.tamcx','');
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tranType                      ', '交易类型                      ', '0                             ', '系统交易                      ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tranType                      ', '交易类型                      ', '1                             ', '业务交易                      ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('user_status                   ', '用户状态                      ', '0                             ', '创建                          ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('user_status                   ', '用户状态                      ', '1                             ', '正常                          ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('user_status                   ', '用户状态                      ', '2                             ', '已登录                        ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('user_status                   ', '用户状态                      ', '9                             ', '注销                          ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('user_station                  ', '用户岗位                      ', '0                             ', '系统管理员                    ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('user_station                  ', '用户岗位                      ', '1                             ', '重空管理员                    ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('user_station                  ', '用户岗位                      ', '2                             ', '网点主管                      ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('user_station                  ', '用户岗位                      ', '3                             ', '普通柜员                      ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('send_returnType               ', '交易结果类型                  ', '5                             ', '查询报表                      ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('user_sex                      ', '用户性别                      ', '0                             ', '男                            ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('user_sex                      ', '用户性别                      ', '1                             ', '女                            ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('user_academic                 ', '学历                          ', '1                             ', '小学                          ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('user_academic                 ', '学历                          ', '2                             ', '中学                          ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('report_type                   ', '报表导出类型                  ', '1                             ', 'EXCEL                         ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('report_type                   ', '报表导出类型                  ', '2                             ', 'PDF                           ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('sysParamType                  ', '系统参数类型                  ', '0                             ', '系统参数                      ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('sysParamType                  ', '系统参数类型                  ', '1                             ', '业务系统参数                  ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('cond_type                     ', '报表条件类型                  ', '6                             ', '隐藏文本框                    ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('lzccb_xmlx                    ', '项目类型                      ', '%%                            ', '全部                          ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('lzccb_xmlx                    ', '项目类型                      ', '01%                           ', '代收                          ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('lzccb_xmlx                    ', '项目类型                      ', '02%                           ', '代付                          ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('lzccb_ybfp                    ', '医保发票                      ', 'lhjy_0202                     ', '正常                          ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('lzccb_ybfp                    ', '医保发票                      ', 'lhjy_03                       ', '作废                          ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('send_look_return              ', '显示类型                      ', '1                             ', '集合                          ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('user_academic                 ', '学历                          ', '5                             ', '大专                          ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('user_academic                 ', '学历                          ', '6                             ', '本科                          ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('user_academic                 ', '学历                          ', '7                             ', '研究生                        ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('user_academic                 ', '学历                          ', '8                             ', '博士                          ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('certi_type                    ', '证件类型                      ', '1                             ', '身份证                        ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('certi_type                    ', '证件类型                      ', '2                             ', '军官证                        ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('certi_type                    ', '证件类型                      ', '3                             ', '驾驶证                        ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('data_type                     ', '数据类型                      ', '0                             ', 'String                        ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('data_type                     ', '数据类型                      ', '1                             ', 'Integer                       ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('data_type                     ', '数据类型                      ', '2                             ', 'Date                          ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('data_type                     ', '数据类型                      ', '3                             ', 'Double                        ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('data_type                     ', '数据类型                      ', '4                             ', 'Float                         ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('is_format                     ', '是否格式化                    ', '0                             ', '是                            ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('is_format                     ', '是否格式化                    ', '1                             ', '否                            ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('is_null                       ', '是否格式化                    ', '0                             ', '是                            ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('is_null                       ', '是否格式化                    ', '1                             ', '否                            ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('org_type                      ', '机构类型                      ', '0                             ', '交易机构                      ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('org_type                      ', '机构类型                      ', '1                             ', '非交易机构                    ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('send_look_return              ', '显示类型                      ', '0                             ', '单显                          ', 'V2.1.gaps           ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX界面组件类型                ', 'timefield                     ', '时间选择框                    ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX界面组件类型                ', 'tipsdqcombo                   ', 'TIPS地区选择框                ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX界面组件类型                ', 'tipsjgcombo                   ', 'TIPS机构选择框                ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX界面组件类型                ', 'treecombo                     ', '树形选择框                    ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX界面组件类型                ', 'treepanel                     ', '树形面板                      ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX界面组件类型                ', 'window                        ', '窗口                          ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_xml_node_type              ', 'XML 节点类型                  ', '0                             ', '普通节点                      ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_xml_node_type              ', 'XML 节点类型                  ', '1                             ', '循环节点                      ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_xml_node_type              ', 'XML 节点类型                  ', '2                             ', '内容节点                      ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_yes_no_type                ', 'TX boolean类型                ', '0                             ', '是                            ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_yes_no_type                ', 'TX boolean类型                ', '1                             ', '否                            ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_comm_type                  ', 'TX通讯组件类型                ', '5                             ', '报表交易                      ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_report_fill_type           ', '填充类型                      ', '1                             ', '不填充                        ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_report_fill_type           ', '填充类型                      ', '2                             ', '以空格填充                    ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_report_fill_type           ', '填充类型                      ', '3                             ', '以0填充                       ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_report_sum_type            ', '合计类型                      ', '1                             ', '非合计项                      ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_report_sum_type            ', '合计类型                      ', '2                             ', '小记项                        ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_report_sum_type            ', '合计类型                      ', '3                             ', '合计项                        ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('t_ui_type                     ', 'TX界面组件类型                ', 'box                           ', 'Box组件                       ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('t_ui_type                     ', 'TX界面组件类型                ', 'button                        ', '按钮                          ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('t_ui_type                     ', 'TX界面组件类型                ', 'checkbox                      ', '复选框                        ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_res_type                   ', 'TX资源类型                    ', 'folder-delete                 ', 'SQL查询导出                   ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_res_type                   ', 'TX资源类型                    ', 'sql-delete                    ', 'SQL查询删除                   ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_res_type                   ', 'TX资源类型                    ', 'sql-select                    ', 'SQL查询导出                   ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_res_type                   ', 'TX资源类型                    ', 'sql-update                    ', 'SQL查询更新                   ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX界面组件类型                ', 'tabpanel                      ', 'TAB面板                       ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('t_search_type                 ', '表字段查询类型                ', 'between                       ', '区间查询                      ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('t_search_type                 ', '表字段查询类型                ', 'equal                         ', '精确查询                      ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('t_search_type                 ', '表字段查询类型                ', 'ext                           ', '扩展查询                      ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('t_search_type                 ', '表字段查询类型                ', 'gt                            ', '大于查询                      ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('t_search_type                 ', '表字段查询类型                ', 'lg                            ', '小于查询                      ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('t_search_type                 ', '表字段查询类型                ', 'like                          ', '模糊查询                      ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('t_search_type                 ', '表字段查询类型                ', 'none                          ', '不作为查询条件                ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('t_search_type                 ', '表字段查询类型                ', 'notequal                      ', '不等查询                      ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tranType                      ', '交易类型                      ', '2                             ', '配置交易                      ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_boolean_type               ', 'boolean 类型                  ', '0                             ', '真                            ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_boolean_type               ', 'boolean 类型                  ', '1                             ', '假                            ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_charset                    ', '字符编码                      ', 'GB18030                       ', 'GB18030字符编码               ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_charset                    ', '字符编码                      ', 'GB2312                        ', 'GB2312字符编码                ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_charset                    ', '字符编码                      ', 'GBK                           ', 'GBK字符编码                   ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_charset                    ', '字符编码                      ', 'ISO-8599-1                    ', 'ISO-8599-1字符编码            ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_charset                    ', '字符编码                      ', 'UTF-16                        ', 'UTF-16字符编码                ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_charset                    ', '字符编码                      ', 'UTF-16BE                      ', 'UTF-16BE字符编码              ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_charset                    ', '字符编码                      ', 'UTF-16LE                      ', 'UTF-16LE字符编码              ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_charset                    ', '字符编码                      ', 'UTF-8                         ', 'UTF-8字符编码                 ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_comm_request_node_type     ', 'TX通讯请求节点类型            ', '0                             ', '元数据节点                    ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_comm_request_node_type     ', 'TX通讯请求节点类型            ', '1                             ', '关键值节点                    ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_comm_request_node_type     ', 'TX通讯请求节点类型            ', '2                             ', '页面根节点                    ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_comm_request_node_type     ', 'TX通讯请求节点类型            ', '3                             ', '页面辅助节点                  ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_comm_request_node_type     ', 'TX通讯请求节点类型            ', '4                             ', 'gaps通讯请求节点              ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_comm_request_node_type     ', 'TX通讯请求节点类型            ', '5                             ', 'gaps通讯响应节点              ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_comm_type                  ', 'TX通讯组件类型                ', '0                             ', 'GAPS通讯组件                  ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_comm_type                  ', 'TX通讯组件类型                ', '1                             ', '数据库通讯                    ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_comm_type                  ', 'TX通讯组件类型                ', '2                             ', '配置交易                      ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_comm_type                  ', 'TX通讯组件类型                ', '3                             ', '集合交易                      ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_comm_type                  ', 'TX通讯组件类型                ', '4                             ', '集合子交易                    ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_com_type                   ', 'TX组件类型                    ', '0                             ', 'EXT-UI                        ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ext_ui_type                ', '组件类型                      ', '0                             ', '显示型组件                    ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ext_ui_type                ', '组件类型                      ', '1                             ', '输入型组件                    ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_search_type                ', '表字段查询类型                ', 'between                       ', '区间查询                      ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_search_type                ', '表字段查询类型                ', 'equal                         ', '精确查询                      ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_search_type                ', '表字段查询类型                ', 'ext                           ', '扩展查询                      ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_search_type                ', '表字段查询类型                ', 'gt                            ', '大于查询                      ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_search_type                ', '表字段查询类型                ', 'lg                            ', '小于查询                      ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_search_type                ', '表字段查询类型                ', 'like                          ', '模糊查询                      ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_search_type                ', '表字段查询类型                ', 'none                          ', '不作为查询条件                ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_search_type                ', '表字段查询类型                ', 'notequal                      ', '不等查询                      ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX界面组件类型                ', 'box                           ', 'Box组件                       ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX界面组件类型                ', 'button                        ', '按钮                          ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX界面组件类型                ', 'checkbox                      ', '复选框                        ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX界面组件类型                ', 'colorpalette                  ', '颜色选择框                    ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX界面组件类型                ', 'combo                         ', '下拉框                        ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX界面组件类型                ', 'component                     ', '组件                          ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX界面组件类型                ', 'container                     ', '容器                          ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX界面组件类型                ', 'datefield                     ', '日期选择框                    ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX界面组件类型                ', 'dbpanel                       ', '数据库面板                    ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX界面组件类型                ', 'field                         ', '表单字段                      ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX界面组件类型                ', 'fieldset                      ', '表单字段组                    ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX界面组件类型                ', 'fileview                      ', '文件查看组件                  ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX界面组件类型                ', 'form                          ', '表单                          ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX界面组件类型                ', 'gapscommpanel                 ', 'gaps通讯面板                  ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX界面组件类型                ', 'grid                          ', '表格面板                      ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX界面组件类型                ', 'hidden                        ', '表单隐藏字段                  ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX界面组件类型                ', 'htmleditor                    ', 'HTML编辑器                    ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_report_text_align          ', '对齐方式                      ', '2                             ', '右对齐                        ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_report_text_align          ', '对齐方式                      ', '3                             ', '居中对齐                      ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_report_type                ', '报表类型                      ', 'fix                           ', '定长报表                      ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_report_type                ', '报表类型                      ', 'ireport                       ', 'ireport报表                   ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_report_type                ', '报表类型                      ', 'pdf                           ', 'pdf报表                       ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_report_type                ', '报表类型                      ', 'sep                           ', '竖线分割报表                  ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_report_type                ', '报表类型                      ', 'sql                           ', 'sql报表                       ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_report_type                ', '报表类型                      ', 'xls                           ', '简单xls报表                   ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_report_type                ', '报表类型                      ', 'xls_tpl                       ', 'xls模板报表                   ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_res_type                   ', 'TX资源类型                    ', 'file-copy                     ', '文件复制                      ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_res_type                   ', 'TX资源类型                    ', 'file-delete                   ', '文件删除                      ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_res_type                   ', 'TX资源类型                    ', 'folder-copy                   ', '目录复制                      ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX界面组件类型                ', 'numberfield                   ', '数值输入框                    ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX界面组件类型                ', 'panel                         ', '面板                          ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX界面组件类型                ', 'password                      ', '密码输入框                    ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX界面组件类型                ', 'radio                         ', '单选框                        ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX界面组件类型                ', 'tamcxorgcombo                 ', 'TAMCX机构选择框               ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX界面组件类型                ', 'textarea                      ', '文本区                        ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('tx_ui_type                    ', 'TX界面组件类型                ', 'textfield                     ', '文本框                        ', 'V2.1.tx             ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('t_ui_type                     ', 'TX界面组件类型                ', 'colorpalette                  ', '颜色选择框                    ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('t_ui_type                     ', 'TX界面组件类型                ', 'combo                         ', '下拉框                        ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('t_ui_type                     ', 'TX界面组件类型                ', 'component                     ', '组件                          ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('t_ui_type                     ', 'TX界面组件类型                ', 'container                     ', '容器                          ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('t_ui_type                     ', 'TX界面组件类型                ', 'datefield                     ', '日期选择框                    ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('t_ui_type                     ', 'TX界面组件类型                ', 'dbpanel                       ', '数据库面板                    ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('t_ui_type                     ', 'TX界面组件类型                ', 'field                         ', '表单字段                      ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('t_ui_type                     ', 'TX界面组件类型                ', 'fieldset                      ', '表单字段组                    ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('t_ui_type                     ', 'TX界面组件类型                ', 'fileview                      ', '文件查看组件                  ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('t_ui_type                     ', 'TX界面组件类型                ', 'form                          ', '表单                          ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('t_ui_type                     ', 'TX界面组件类型                ', 'grid                          ', '表格面板                      ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('t_ui_type                     ', 'TX界面组件类型                ', 'hidden                        ', '表单隐藏字段                  ', 'V2.1.tamcx          ', null);
insert into T_DICT (DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
values ('t_ui_type                     ', 'TX界面组件类型                ', 'htmleditor                    ', 'HTML编辑器                    ', 'V2.1.tamcx          ', null);


insert into T_MENU (MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
values ('menux                         ', 'super_menage                  ', 3, '菜单配置            ', '菜单配置                                          ', '1', 'menux               ', '1', 'V2.1.tamcx          ', null, '900002000000        ', '0', 'agent     ', null, null, null);
insert into T_MENU (MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
values ('tx_db                         ', 'TX_CONFIG                     ', 3, '增删改查配置        ', '增删改查配置                                      ', '1', 'tx_db_operator      ', '1', 'V2.1.tamcx          ', null, '908060000000        ', '0', 'agent     ', null, null, null);
insert into T_MENU (MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
values ('ipreg                         ', 'sysinit                       ', 3, 'IP登记管理          ', 'IP登记管理                                        ', '1', 'ipreg               ', '1', 'V2.1.tamcx          ', null, '900026100000        ', '0', 'agent     ', null, null, null);
insert into t_menu (menu_id,above_menu_id,menu_deep,menu_name,menu_desc,is_run_menu,tran_code,is_enable,version,report_id,order_id,menu_type,system_id,bak1,bak2,bak3) 
values('TX_PZJYEXPORT','TX_CONFIG',3,'配置交易导出','配置交易导出','1','pzjyexport','1','','','908080000000','0','agent','','','');
insert into T_MENU (MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
values ('change_pwd                    ', 'sysinit                       ', 3, '修改密码            ', '修改密码                                          ', '1', 'changePwd           ', '1', 'V2.1.tamcx          ', null, '900027100000        ', '0', 'agent     ', null, null, null);
insert into T_MENU (MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
values ('usermacheck                   ', 'sysinit                       ', 3, '用户审核            ', '用户审核                                          ', '1', 'usermacheck         ', '1', 'V2.1.tamcx          ', null, '900025100000        ', '0', 'agent     ', null, null, null);
insert into T_MENU (MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
values ('statusmonitor                 ', 'sysinit                       ', 3, '进程状态            ', '查看进程状态                                      ', '1', 'statusmonitor       ', '1', 'V2.1.tamcx          ', null, '900028100000        ', '0', 'agent     ', null, null, null);
insert into T_MENU (MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
values ('appversionmanage              ', 'TX_CONFIG                     ', 3, '应用版本配置        ', '应用版本配置                                      ', '1', 'appversionmanage    ', '1', 'V2.1.tamcx          ', null, '908050000000        ', '0', 'agent     ', null, null, null);
insert into T_MENU (MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
values ('TX_APP_PAGE_GEN               ', 'TX_CONFIG                     ', 3, '应用界面生成        ', '应用界面生成                                      ', '1', 'tx_app_page_gen     ', '1', 'V2.1.tx             ', null, '908070000000        ', '0', 'tamcx     ', null, null, null);
insert into T_MENU (MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
values ('TX_CONFIG                     ', 'super_menage                  ', 2, '开发配置            ', '开发配置                                          ', '0', 'alterUserPass       ', '1', 'V2.1.tx             ', null, '908000000000        ', '0', 'tamcx     ', null, null, null);
insert into T_MENU (MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
values ('reportPz                      ', 'super_menage                  ', 2, '报表配置            ', '报表配置                                          ', '1', 'reportPz            ', '1', 'V2.1.tamcx          ', 'reportPz                                ', '900004000000        ', '0', 'tamcx     ', null, null, null);
insert into T_MENU (MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
values ('sysini                        ', 'super_menage                  ', 2, '系统参数维护        ', '系统参数维护                                      ', '1', 'system_param        ', '1', 'V2.1.tamcx          ', null, '900009000000        ', '0', 'tamcx     ', null, null, null);
insert into T_MENU (MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
values ('dict_menage                   ', 'super_menage                  ', 2, '字典维护            ', '字典管理维护                                      ', '1', 'dictManage          ', '1', 'V2.1.tamcx          ', null, '900003000000        ', '0', 'tamcx     ', null, null, null);
insert into T_MENU (MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
values ('super_menage                  ', '/                             ', 1, '超级管理            ', '可设置为开发人员专用，不对业务开放。              ', '0', null, '1', 'V2.1.tamcx          ', null, '900000000000        ', '0', 'tamcx     ', null, null, null);
insert into T_MENU (MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
values ('refresh_param                 ', 'super_menage                  ', 2, '刷新系统参数        ', '刷新系统参数                                      ', '1', 'refresh_param       ', '1', 'V2.1.tamcx          ', null, '900009000000        ', '0', 'tamcx     ', null, null, null);
insert into T_MENU (MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
values ('sys_menage                    ', '/                             ', 1, '系统管理            ', '系统管理                                          ', '0', 'sys_Menage          ', '1', 'V2.1.tamcx          ', null, '900020000000        ', '0', 'tamcx     ', null, null, null);
insert into T_MENU (MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
values ('sysinit                       ', 'sys_menage                    ', 2, '系统参数管理        ', '系统参数管理                                      ', '0', 'botsPlywlx          ', '1', 'V2.1.tamcx          ', null, '900021000000        ', '0', 'tamcx     ', null, null, null);
insert into T_MENU (MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
values ('tran_conf                     ', 'super_menage                  ', 2, '交易配置            ', '配置交易相关信息                                  ', '1', 'TranSubtran         ', '1', 'V2.1.tamcx          ', null, '900001000000        ', '0', 'tamcx     ', null, null, null);
insert into T_MENU (MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
values ('gaps_new                      ', 'super_menage                  ', 3, 'GAPS通讯配置        ', 'GAPS通讯配置                                      ', '1', 'gapsconfig          ', '1', 'V2.1.tamcx          ', null, '900004100000        ', '0', 'agent     ', null, null, null);
insert into T_MENU (MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
values ('org_manage                    ', 'sysinit                       ', 3, '机构管理            ', '机构管理                                          ', '1', 'org_manage          ', '1', 'V2.1.tamcx          ', null, '900022100000        ', '0', 'agent     ', null, null, null);
insert into T_MENU (MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
values ('role_manage                   ', 'sysinit                       ', 3, '角色管理            ', '角色管理                                          ', '1', 'role_manage         ', '1', 'V2.1.tamcx          ', null, '900023100000        ', '0', 'tamcx     ', null, null, null);
insert into T_MENU (MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
values ('user_manage                   ', 'sysinit                       ', 3, '用户管理            ', '用户管理                                          ', '1', 'user_manage         ', '1', 'V2.1.tamcx          ', null, '900024100000        ', '0', 'tamcx     ', null, null, null);
insert into T_MENU (MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
values ('dzgl                          ', 'xtgljdz                       ', 4, '对账管理            ', '对账管理                                          ', '1', 'dzgl                ', '1', 'V2.1.tamcx          ', null, '900400000101        ', '0', 'agent     ', null, null, null);
insert into T_MENU (MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
values ('xtjk                          ', 'xtgljdz                       ', 4, '系统监控            ', '系统监控                                          ', '1', 'xtjk                ', '1', 'V2.1.tamcx          ', null, '900400000102        ', '0', 'agent     ', null, null, null);
insert into T_MENU (MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
values ('prod_upgrade                  ', 'super_menage                  ', 2, '产品升级            ', '产品升级                                          ', '1', 'cpsj_manage         ', '1', 'V2.1.tamcx          ', null, '900009030000        ', '0', 'agent     ', null, null, null);


insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_table            ', 'edt                 ', 'edt                           ', 'app/extension/tableEdt.jsp                                                                          ', 'edt                                               ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('user_menage         ', 'upt                 ', '更新                          ', 'success.jsp                                                                                         ', '更新用户信息                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('reportPz            ', 'def                 ', '默认报表配置页面              ', 'systemx/sysx_report.jsp                                                                             ', '默认报表配置页面                                  ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('cpsj_manage         ', 'import              ', '升级数据导入                  ', 'system/cpsjmanage.jsp                                                                               ', '升级系统数据导入                                  ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('TranSubtran         ', 'addSubtran          ', '增加子交易                    ', 'systemx/sysx_transubtran.jsp                                                                        ', '增加子交易                                        ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('TranSubtran         ', 'delSubtran          ', '删除子交易                    ', 'systemx/sysx_transubtran.jsp                                                                        ', '删除子交易                                        ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('changePwd           ', 'def                 ', '默认                          ', 'systemx/sysx_change_pwd.jsp                                                                         ', '默认                                              ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('gapsconfig          ', 'serverupt           ', '执行服务更新                  ', 'systemx/sysx_gapsconfig.jsp                                                                         ', '执行服务结果                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('TranSubtran         ', 'add                 ', '增加交易界面                  ', 'systemx/sysx_transubtran.jsp                                                                        ', '增加交易界面                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('TranSubtran         ', 'def                 ', '交易列表                      ', 'systemx/sysx_transubtran.jsp                                                                        ', '查询并显示交易列表                                ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('TranSubtran         ', 'edt                 ', '修改交易界面                  ', 'systemx/sysx_transubtran.jsp                                                                        ', '查询并显示需修改的交易信息                        ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('gapsconfig          ', 'serveredt           ', '修改服务页面                  ', 'systemx/sysx_gapsconfig.jsp                                                                         ', '修改服务页面                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('logon               ', 'ent                 ', '用户登录                      ', 'main/logonNew.jsp                                                                                   ', '用户登录,校验用户信息                             ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('logon               ', 'def                 ', '登录默认页面                  ', 'main/logonNew.jsp                                                                                   ', '登录默认页面                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('logon               ', 'out                 ', '用户签退                      ', 'main/logonNew.jsp                                                                                   ', '用户签退                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('menu_conf           ', 'upt                 ', '修改菜单配置信息              ', 'success.jsp                                                                                         ', '修改菜单配置数据                                  ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('org_menage          ', 'batch               ', '批量机构插入                  ', 'success.jsp                                                                                         ', '批量机构插入                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('user_menage         ', 'batch               ', '批量开用户                    ', 'success.jsp                                                                                         ', '批量开用户                                        ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('gapsdown            ', 'def                 ', '默认页面                      ', 'app/send/toGapsFile.jsp                                                                             ', '默认页面                                          ', 'V2.1.gaps           ', '01                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('gapsdown            ', 'down                ', '下载文件                      ', 'app/send/toGapsFile.jsp                                                                             ', '下载                                              ', 'V2.1.gaps           ', '01                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('dict_menage         ', 'edt                 ', '修改                          ', 'system/dictEdt.jsp                                                                                  ', '修改界面                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('dict_menage         ', 'upt                 ', '修改更新                      ', 'system/dictMenage.jsp                                                                               ', '修改更新                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('dict_menage         ', 'add                 ', '增加                          ', 'system/dictEdt.jsp                                                                                  ', '增加界面                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('dict_menage         ', 'ins                 ', '增加更新                      ', 'system/dictMenage.jsp                                                                               ', '增加更新                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('dict_menage         ', 'del                 ', '删除                          ', 'system/dictMenage.jsp                                                                               ', '删除                                              ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('cpsj_manage         ', 'export              ', '升级数据导出                  ', 'system/cpsjmanage.jsp                                                                               ', '升级系统数据导出                                  ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('reportPz            ', 'add                 ', '添加报表信息                  ', 'systemx/sysx_report.jsp                                                                             ', '添加报表信息                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('sendPz              ', 'serveredt           ', '修改服务页面                  ', 'app/gaps/sendServerPzEdt.jsp                                                                        ', '修改服务页面                                      ', 'V2.1.gaps           ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('sendPz              ', 'serverins           ', '执行服务增加                  ', 'app/gaps/sendServerPzLst.jsp                                                                        ', '执行服务添加                                      ', 'V2.1.gaps           ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('sendPz              ', 'serveradd           ', '增加服务                      ', 'app/gaps/sendServerPzEdt.jsp                                                                        ', '增加服务页面                                      ', 'V2.1.gaps           ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('sendPz              ', 'serverdef           ', '默认服务                      ', 'app/gaps/sendServerPzLst.jsp                                                                        ', '默认服务                                          ', 'V2.1.gaps           ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('userMenageCheck     ', 'check               ', '审核用户                      ', 'system/userMenageCheck.jsp                                                                          ', '审核用户                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('send                ', 'def                 ', '起始交易                      ', 'app/gaps/send.jsp                                                                                   ', '起始交易                                          ', 'V2.1.gaps           ', '01                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('sendPz              ', 'def                 ', '通讯查询                      ', 'app/gaps/sendPzLst.jsp                                                                              ', '通讯                                              ', 'V2.1.gaps           ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('send                ', 'send                ', '执行交易                      ', 'app/gaps/sendreturn.jsp                                                                             ', '执行交易                                          ', 'V2.1.gaps           ', '01                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('sendPz              ', 'add                 ', '添加通讯页面                  ', 'app/gaps/sendPzEdt.jsp                                                                              ', '添加页面通讯                                      ', 'V2.1.gaps           ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('sendPz              ', 'edt                 ', '更新通讯页面                  ', 'app/gaps/sendPzEdt.jsp                                                                              ', '更新通讯页面                                      ', 'V2.1.gaps           ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('sendPz              ', 'ins                 ', '执行通讯添加                  ', 'app/gaps/sendPzLst.jsp                                                                              ', '执行通讯添加                                      ', 'V2.1.gaps           ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('sendPz              ', 'del                 ', '删除通讯                      ', 'app/gaps/sendPzLst.jsp                                                                              ', '删除通讯                                          ', 'V2.1.gaps           ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('sendPz              ', 'conddef             ', '默认通讯条件                  ', 'app/gaps/sendCondPzLst.jsp                                                                          ', '通讯条件                                          ', 'V2.1.gaps           ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('sendPz              ', 'condadd             ', '添加通讯条件页面              ', 'app/gaps/sendCondPzEdt.jsp                                                                          ', '添加条件页面                                      ', 'V2.1.gaps           ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('reportPz            ', 'del                 ', '删除报表信息                  ', 'systemx/sysx_report.jsp                                                                             ', '删除报表信息                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('cpsj_manage         ', 'def                 ', '产品升级管理                  ', 'system/cpsjmanage.jsp                                                                               ', '产品升级管理                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('reportCondPz        ', 'add                 ', '跳转添加报表条件页面          ', 'system/reportCondPzEdt.jsp                                                                          ', '跳转添加报表条件页面                              ', 'V2.1.tamcx          ', '02                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('reportCondPz        ', 'ins                 ', '添加报表条件信息              ', 'system/reportCondPzLst.jsp                                                                          ', '添加报表条件信息                                  ', 'V2.1.tamcx          ', '02                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('reportCondPz        ', 'edt                 ', '跳转报表条件维护页            ', 'system/reportCondPzEdt.jsp                                                                          ', '跳转报表条件维护页                                ', 'V2.1.tamcx          ', '02                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('reportCondPz        ', 'upt                 ', '报表条件更新                  ', 'system/reportCondPzLst.jsp                                                                          ', '报表条件更新                                      ', 'V2.1.tamcx          ', '02                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('reportCondPz        ', 'del                 ', '删除报表条件                  ', 'system/reportCondPzLst.jsp                                                                          ', '删除报表条件                                      ', 'V2.1.tamcx          ', '02                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('alterUserPass       ', 'def                 ', '修改密码界面                  ', 'system/alterUserPass.jsp                                                                            ', '修改密码界面                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('userMenageCheck     ', 'def                 ', '查询用户                      ', 'system/userMenageCheck.jsp                                                                          ', '查询未通过审核用户                                ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('user_menage         ', 'del                 ', '删除                          ', 'success.jsp                                                                                         ', '删除用户信息                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('sendPz              ', 'returndef           ', '默认通讯结果                  ', 'app/gaps/sendreturnPzLst.jsp                                                                        ', '默认通讯结果                                      ', 'V2.1.gaps           ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('sendPz              ', 'returnadd           ', '增加通讯结果页面              ', 'app/gaps/sendreturnPzEdt.jsp                                                                        ', '增加通讯结果页面                                  ', 'V2.1.gaps           ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('send                ', 'infLst              ', '集合信息                      ', 'app/gaps/sendinfoLst.jsp                                                                            ', '集合信息                                          ', 'V2.1.gaps           ', '02                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('send                ', 'info                ', '信息显示                      ', 'app/gaps/sendinfo.jsp                                                                               ', '交易信息                                          ', 'V2.1.gaps           ', '02                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('send                ', 'print               ', '显示打印文件                  ', 'app/gaps/sendreturn.jsp                                                                             ', '显示打印文件                                      ', 'V2.1.gaps           ', '02                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('send                ', 'down                ', '下载文件                      ', 'about:blank                                                                                         ', '下载文件                                          ', 'V2.1.gaps           ', '02                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('send                ', 'fileToPrint         ', '文件显示打印                  ', 'break                                                                                               ', '文件显示打印                                      ', 'V2.1.gaps           ', '02                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('sendPz              ', 'returnins           ', '执行通讯结果增加              ', 'app/gaps/sendreturnPzLst.jsp                                                                        ', '执行通讯结果添加                                  ', 'V2.1.gaps           ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('sendPz              ', 'returnedt           ', '修改通讯结果页面              ', 'app/gaps/sendreturnPzEdt.jsp                                                                        ', '修改通讯结果页面                                  ', 'V2.1.gaps           ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('sendPz              ', 'returnupt           ', '执行通讯结果更新              ', 'app/gaps/sendreturnPzLst.jsp                                                                        ', '执行更新通讯结果                                  ', 'V2.1.gaps           ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('sendPz              ', 'returndel           ', '删除通讯结果                  ', 'app/gaps/sendreturnPzLst.jsp                                                                        ', '删除通讯结果                                      ', 'V2.1.gaps           ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('report              ', 'lend                ', '报表导出                      ', 'success.jsp                                                                                         ', '报表导出                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('report              ', 'look                ', '报表导出分页查询              ', 'success.jsp                                                                                         ', '报表导出分页查询                                  ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('report              ', 'def                 ', '报表查询                      ', 'systemx/report.jsp', '报表查询                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('org_menage          ', 'ins                 ', '插入                          ', 'success.jsp                                                                                         ', '插入交易配置                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('org_menage          ', 'upt                 ', '更新                          ', 'success.jsp                                                                                         ', '更新机构信息                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('user_menage         ', 'ins                 ', '插入                          ', 'success.jsp                                                                                         ', '插入用户信息                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('send                ', 'dateReport          ', '数据报表                      ', 'app/gaps/sendreturn.jsp                                                                             ', '数据报表                                          ', 'V2.1.gaps           ', '02                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('botsGapsdown        ', 'down                ', '下载文件                      ', 'app/agent/bots/toGapsFile.jsp                                                                       ', '下载                                              ', 'V2.1.gaps           ', '01                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('botsGapsdown        ', 'def                 ', '默认页面                      ', 'app/agent/bots/toGapsFile.jsp                                                                       ', '默认页面                                          ', 'V2.1.gaps           ', '01                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('sendPz              ', 'condins             ', '执行通讯条件添加              ', 'app/gaps/sendCondPzLst.jsp                                                                          ', '执行条件添加                                      ', 'V2.1.gaps           ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('sendPz              ', 'condedt             ', '更新通讯条件页面              ', 'app/gaps/sendCondPzEdt.jsp                                                                          ', '更新条件页面                                      ', 'V2.1.gaps           ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('sendPz              ', 'condupt             ', '执行通讯条件更新              ', 'app/gaps/sendCondPzLst.jsp                                                                          ', '执行更新条件                                      ', 'V2.1.gaps           ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('sendPz              ', 'conddel             ', '删除通讯条件                  ', 'app/gaps/sendCondPzLst.jsp                                                                          ', '删除条件                                          ', 'V2.1.gaps           ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('mvSend              ', 'print               ', '显示打印文件                  ', 'app/gaps/sendreturn.jsp                                                                             ', '显示打印文件                                      ', 'V2.1.gaps           ', '02                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('mvSend              ', 'down                ', '下载文件                      ', 'about:blank                                                                                         ', '下载文件                                          ', 'V2.1.gaps           ', '02                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('mvSend              ', 'def                 ', '起始交易                      ', 'app/gaps/mvSend.jsp                                                                                 ', '起始交易                                          ', 'V2.1.gaps           ', '01                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('mvSend              ', 'infLst              ', '集合信息                      ', 'app/gaps/sendinfoLst.jsp                                                                            ', '集合信息                                          ', 'V2.1.gaps           ', '02                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('mvSend              ', 'info                ', '信息显示                      ', 'app/gaps/sendinfo.jsp                                                                               ', '信息显示                                          ', 'V2.1.gaps           ', '02                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('mvSend              ', 'fileToprint         ', '文件显示打印                  ', 'app/gaps/sendreturn.jsp                                                                             ', '文件显示打印                                      ', 'V2.1.gaps           ', '02                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('mvSend              ', 'send                ', '执行交易                      ', 'app/gaps/sendreturn.jsp                                                                             ', '执行交易                                          ', 'V2.1.gaps           ', '01                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('mvSend              ', 'mv                  ', '授权                          ', 'about:blank                                                                                         ', '授权                                              ', 'V2.1.gaps           ', '01                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('mvSend              ', 'mvExe               ', '执行验证                      ', 'about:blank                                                                                         ', '执行验证                                          ', 'V2.1.gaps           ', '02                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('TranSubtran         ', 'list                ', '交易查询                      ', 'systemx/sysx_transubtran.jsp                                                                        ', '交易配置查询                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('refresh_param       ', 'refresh             ', '系统参数刷新                  ', 'success.jsp                                                                                         ', '系统参数刷新                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('reportPz            ', 'ins                 ', '执行添加报表信息              ', 'systemx/sysx_report.jsp                                                                             ', '执行添加报表信息                                  ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('TranSubtran         ', 'upt                 ', '更新交易                      ', 'systemx/sysx_transubtran.jsp                                                                        ', '更新交易配置信息                                  ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('TranSubtran         ', 'uptSubtran          ', '更新子交易                    ', 'systemx/sysx_transubtran.jsp                                                                        ', '更新子交易                                        ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('TranSubtran         ', 'listSubtran         ', '子交易列表                    ', 'systemx/sysx_transubtran.jsp                                                                        ', '查询并显示子交易列表                              ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('gapsconfig          ', 'serverdel           ', '删除服务                      ', 'systemx/sysx_gapsconfig.jsp                                                                         ', '删除服务结果                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('statusmonitor       ', 'show                ', '查看                          ', 'systemx/sysx_status_monitor.jsp                                                                     ', '查看                                              ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('dict_menage         ', 'def                 ', '字典列表                      ', 'system/dictMenage.jsp                                                                               ', '显示字典列表                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('expsql              ', 'def                 ', '默认                          ', 'systemx/sysx_exp_sql.jsp                                                                            ', '默认                                              ', 'V2.1.tamcx          ', '01                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('expsql              ', 'exc                 ', '下载                          ', 'systemx/sysx_exp_sql.jsp                                                                            ', '下载                                              ', 'V2.1.tamcx          ', '01                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('reportCondPz        ', 'def                 ', '报表条件查询                  ', 'system/reportCondPzLst.jsp                                                                          ', '报表条件查询                                      ', 'V2.1.tamcx          ', '02                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('user_menage         ', 'qry                 ', '查询                          ', 'system/userMenage.jsp                                                                               ', '用户查询                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('reportPz            ', 'edt                 ', '报表信息修改页面              ', 'systemx/sysx_report.jsp                                                                             ', '报表信息修改页面                                  ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('reportPz            ', 'upt                 ', '更新报表信息                  ', 'systemx/sysx_report.jsp                                                                             ', '更新报表信息                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('sendPz              ', 'serverdel           ', '删除服务                      ', 'app/gaps/sendServerPzLst.jsp                                                                        ', '删除服务结果                                      ', 'V2.1.gaps           ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('sendPz              ', 'serverupt           ', '执行服务更新                  ', 'app/gaps/sendServerPzLst.jsp                                                                        ', '执行服务结果                                      ', 'V2.1.gaps           ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('menux               ', 'del                 ', '删除菜单配置                  ', 'systemx/sys_menu.jsp                                                                                ', '删除菜单配置信息                                  ', 'V2.1.tamcx          ', '01                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('menux               ', 'upt                 ', '修改菜单配置信息              ', 'systemx/sys_menu.jsp                                                                                ', '修改菜单配置数据                                  ', 'V2.1.tamcx          ', '01                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('HundsunExtension    ', 'add                 ', '添加数据                      ', 'blank.html                                                                                          ', '添加数据                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_db_operator      ', 'add                 ', '添加                          ', 'systemx/extension/dbInfoReg.jsp                                                                     ', '添加                                              ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_report_cfg       ', 'add                 ', '保存信息                      ', 'app/extension/reportInfoReg.jsp                                                                     ', '保存信息                                          ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_table            ', 'add                 ', 'add                           ', 'app/extension/tableEdt.jsp                                                                          ', 'add                                               ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_xml_operator     ', 'add                 ', '新增数据                      ', 'app/extension/xmlInfoReg.jsp                                                                        ', '新增数据                                          ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_report_ctl       ', 'createfile          ', '创建报表文件                  ', 'blank.html                                                                                          ', '创建报表文件                                      ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('HundsunExtension    ', 'def                 ', '默认交易                      ', 'blank.html                                                                                          ', '默认交易                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('HundsunExtension    ', 'file                ', '文件操作                      ', 'blank.html                                                                                          ', '文件操作                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_page_dispatcher  ', 'fileView            ', '文件下载                      ', 'blank.html                                                                                          ', '文件下载                                          ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_di_test          ', 'get                 ', '获取资源                      ', 'systemx/extension/TestDI.jsp                                                                        ', '获取资源                                          ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_page_dispatcher  ', 'getOrgTree          ', '获取机构树                    ', 'blank.html                                                                                          ', '获取机构树                                        ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('HundsunExtension    ', 'getPageData         ', '获取界面初始数据              ', 'blank.html                                                                                          ', '获取界面初始数据                                  ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_xml_operator     ', 'getPkgInfo          ', '获取报文信息                  ', 'app/extension/xmlInfoReg.jsp                                                                        ', '获取报文信息                                      ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_db_operator      ', 'getRegTreeInfos     ', '获取注册信息                  ', 'systemx/extension/dbInfoReg.jsp                                                                     ', '获取注册信息                                      ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_report_cfg       ', 'getReportInfo       ', '获取报表配置信息              ', 'blank.html                                                                                          ', '获取报表配置信息                                  ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_page_dispatcher  ', 'getResource         ', '获取资源                      ', 'blank.html                                                                                          ', '获取资源                                          ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_db_operator      ', 'getTableColumns     ', '获取数据表的列                ', 'systemx/extension/dbInfoReg.jsp                                                                     ', '获取数据表的列                                    ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_db_operator      ', 'getTableNames       ', '获取数据库中的表              ', 'systemx/extension/dbInfoReg.jsp                                                                     ', '获取数据库中的表                                  ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_table            ', 'ins                 ', 'ins                           ', 'app/extension/tableLst.jsp                                                                          ', 'ins                                               ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_main_config      ', 'load                ', '树形数据加载                  ', 'tx/configTree.html                                                                                  ', '树形数据加载                                      ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_report_ctl       ', 'loaddata            ', '加载数据                      ', 'blank.html                                                                                          ', '加载数据                                          ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('HundsunExtension    ', 'lst                 ', '获取表数据                    ', 'blank.html                                                                                          ', '获取表数据                                        ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_db_operator      ', 'lst                 ', '数据获取                      ', 'systemx/extension/dbInfoReg.jsp                                                                     ', '数据获取                                          ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('HundsunExtension    ', 'send2gaps           ', '发送JDOM到GAPS                ', 'blank.html                                                                                          ', '发送JDOM到GAPS                                    ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_main_config      ', 'tpl                 ', '模板方式增加                  ', 'tx/configTree.html                                                                                  ', '模板方式增加                                      ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('HundsunExtension    ', 'upt                 ', '更新数据                      ', 'blank.html                                                                                          ', '更新数据                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_db_operator      ', 'upt                 ', '修改                          ', 'systemx/extension/dbInfoReg.jsp                                                                     ', '修改                                              ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_table            ', 'upt                 ', 'upt                           ', 'app/extension/tableLst.jsp                                                                          ', 'upt                                               ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('HundsunExtension    ', 'warrant             ', '授权                          ', 'blank.html                                                                                          ', '授权                                              ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_app_page_gen     ', 'def                 ', '默认交易                      ', 'systemx/extension/appPageGenerator.jsp                                                              ', '默认交易                                          ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_db_operator      ', 'def                 ', '默认界面                      ', 'systemx/extension/dbInfoReg.jsp                                                                     ', '默认界面                                          ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_di_test          ', 'def                 ', '默认交易                      ', 'systemx/extension/TestDI.jsp                                                                        ', '默认交易                                          ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_ext_doc          ', 'def                 ', 'EXT帮助文档首页               ', 'js/ext2.1/docs/link.html                                                                            ', 'EXT帮助文档首页                                   ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_main_config      ', 'def                 ', '默认界面                      ', 'tx/configTree.html                                                                                  ', '默认界面                                          ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_page_dispatcher  ', 'def                 ', '页面跳转                      ', 'success.jsp                                                                                         ', '页面跳转                                          ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_report_cfg       ', 'def                 ', '默认交易                      ', 'app/extension/reportInfoReg.jsp                                                                     ', '获取页面                                          ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_report_ctl       ', 'def                 ', '页面跳转                      ', 'blank.html                                                                                          ', '页面跳转                                          ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_table            ', 'def                 ', 'def                           ', 'app/extension/tableLst.jsp                                                                          ', 'def                                               ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_xml_operator     ', 'def                 ', '默认交易                      ', 'app/extension/xmlInfoReg.jsp                                                                        ', '默认交易                                          ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('appversionmanage    ', 'def                 ', '默认                          ', 'systemx/sysx_app_version.jsp                                                                        ', '应用版本配置默认页                                ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('appversionmanage    ', 'list                ', '查询                          ', 'systemx/sysx_app_version.jsp                                                                        ', '查询                                              ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('appversionmanage    ', 'add                 ', '添加                          ', 'systemx/sysx_app_version.jsp                                                                        ', '添加                                              ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('appversionmanage    ', 'upt                 ', '更新                          ', 'systemx/sysx_app_version.jsp                                                                        ', '更新                                              ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('appversionmanage    ', 'del                 ', '删除                          ', 'systemx/sysx_app_version.jsp                                                                        ', '删除                                              ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('role_manage         ', 'def                 ', '查询                          ', 'systemx/sysx_role_manage_new.jsp                                                                    ', '查询                                              ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('role_manage         ', 'disAssign           ', '取消授权                      ', 'systemx/sysx_role_manage_new.jsp                                                                    ', '取消授权                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('role_manage         ', 'ins                 ', '插入新增                      ', 'systemx/sysx_role_manage_new.jsp                                                                    ', '角色新增                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('role_manage         ', 'list                ', '查询                          ', 'systemx/sysx_role_manage_new.jsp                                                                    ', '查询角色信息                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('role_manage         ', 'lstprv              ', '列出权限                      ', 'systemx/sysx_role_manage_new.jsp                                                                    ', '列出权限                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('role_manage         ', 'doAssign            ', '分配角色权限                  ', 'systemx/sysx_role_manage_new.jsp                                                                    ', '分配角色权限                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('role_manage         ', 'upt                 ', '修改更新                      ', 'systemx/sysx_role_manage_new.jsp                                                                    ', '修改更新角色信息                                  ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('role_manage         ', 'add                 ', '新增界面                      ', 'systemx/sysx_role_manage_new.jsp                                                                    ', '增加角色界面                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('role_manage         ', 'del                 ', '删除                          ', 'systemx/sysx_role_manage_new.jsp                                                                    ', '删除角色信息                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('HundsunExtension    ', 'sendGaps            ', '发送Gaps通讯交易              ', 'blank.html                                                                                          ', '发送Gaps通讯交易                                  ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('user_manage         ', 'assignUpt           ', '分配更新                      ', 'systemx/sysx_user_manage.jsp                                                                        ', '分配权限更新                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values('user_manage         ', 'warrantUpt          ', '授权更新                      ', 'systemx/sysx_user_manage.jsp                                                                        ', '授权更新                                          ', 'V2.1.tamcx', NULL, NULL, NULL);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('role_manage         ', 'toauth              ', '获取待授权                    ', 'systemx/sysx_role_manage_new.jsp                                                                    ', '获取待授权                                        ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('role_manage         ', 'authed              ', '获取已授权                    ', 'systgemx/sysx_role_manage_new.jsp                                                                   ', '获取已授权                                        ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('user_menage         ', 'def                 ', '默认                          ', 'system/userMenage.jsp                                                                               ', '默认                                              ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('statusmonitor       ', 'def                 ', '默认                          ', 'systemx/sysx_status_monitor.jsp                                                                     ', '默认                                              ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('HundsunExtension    ', 'del                 ', '删除数据                      ', 'blank.html                                                                                          ', '删除数据                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_db_operator      ', 'del                 ', '删除                          ', 'systemx/extension/dbInfoReg.jsp                                                                     ', '删除                                              ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_table            ', 'del                 ', 'del                           ', 'app/extension/tableLst.jsp                                                                          ', 'del                                               ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('tx_report_ctl       ', 'downfile            ', '下载文件                      ', 'blank.html                                                                                          ', '下载文件                                          ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('dictManage          ', 'del                 ', '删除                          ', 'systemx/sysx_dict_manage.jsp                                                                        ', '删除                                              ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('dictManage          ', 'def                 ', '查询                          ', 'systemx/sysx_dict_manage.jsp                                                                        ', '默认                                              ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('dictManage          ', 'list                ', '获得数据                      ', 'systemx/sysx_dict_manage.jsp                                                                        ', '获得数据                                          ', 'V2.1.tamcx          ', '02                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('dictManage          ', 'add                 ', '添加更新                      ', 'systemx/sysx_dict_manage.jsp                                                                        ', '添加更新                                          ', 'V2.1.tamcx          ', '01                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('gapsconfig          ', 'serveradd           ', '增加服务                      ', 'systemx/sysx_gapsconfig.jsp                                                                         ', '增加服务页面                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('gapsconfig          ', 'serverdef           ', '默认服务                      ', 'systemx/sysx_gapsconfig.jsp                                                                         ', '默认服务                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('gapsconfig          ', 'def                 ', '通讯查询                      ', 'systemx/sysx_gapsconfig.jsp                                                                         ', '通讯                                              ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('gapsconfig          ', 'add                 ', '添加通讯页面                  ', 'systemx/sysx_gapsconfig.jsp                                                                         ', '添加页面通讯                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('gapsconfig          ', 'list                ', '查询通讯结果                  ', 'systemx/sysx_gapsconfig.jsp                                                                         ', '查询通讯结果                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('role_manage         ', 'assign              ', '角色授权                      ', 'systemx/sysx_role_manage_new.jsp                                                                    ', '角色授权                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('TranSubtran         ', 'del                 ', '删除交易                      ', 'systemx/sysx_transubtran.jsp                                                                        ', '删除交易信息                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('gapsconfig          ', 'del                 ', '删除通讯                      ', 'systemx/sysx_gapsconfig.jsp                                                                         ', '删除通讯                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('gapsconfig          ', 'conddef             ', '默认通讯条件                  ', 'systemx/sysx_gapsconfig.jsp                                                                         ', '通讯条件                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('gapsconfig          ', 'condadd             ', '添加通讯条件页面              ', 'systemx/sysx_gapsconfig.jsp                                                                         ', '添加条件页面                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('gapsconfig          ', 'returndef           ', '默认通讯结果                  ', 'systemx/sysx_gapsconfig.jsp                                                                         ', '默认通讯结果                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('gapsconfig          ', 'returnadd           ', '增加通讯结果页面              ', 'systemx/sysx_gapsconfig.jsp                                                                         ', '增加通讯结果页面                                  ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('gapsconfig          ', 'returnedt           ', '修改通讯结果页面              ', 'systemx/sysx_gapsconfig.jsp                                                                         ', '修改通讯结果页面                                  ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('gapsconfig          ', 'returnupt           ', '执行通讯结果更新              ', 'systemx/sysx_gapsconfig.jsp                                                                         ', '执行更新通讯结果                                  ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('gapsconfig          ', 'returndel           ', '删除通讯结果                  ', 'systemx/sysx_gapsconfig.jsp                                                                         ', '删除通讯结果                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('gapsconfig          ', 'condupt             ', '执行通讯条件更新              ', 'systemx/sysx_gapsconfig.jsp                                                                         ', '执行更新条件                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('gapsconfig          ', 'conddel             ', '删除通讯条件                  ', 'systemx/sysx_gapsconfig.jsp                                                                         ', '删除条件                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('org_manage          ', 'del                 ', '删除机构配置信息              ', 'systemx/sysx_org_manage.jsp                                                                         ', '删除机构配置信息                                  ', 'V2.1.tamcx          ', '01                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('org_manage          ', 'upt                 ', '修改配置机构信息              ', 'systemx/sysx_org_manage.jsp                                                                         ', '修改机构配置数据                                  ', 'V2.1.tamcx          ', '01                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('org_manage          ', 'list                ', '查询                          ', 'systemx/sysx_org_manage.jsp                                                                         ', '查询                                              ', 'V2.1.tamcx          ', '01                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('org_manage          ', 'get                 ', '获得机构详细信息              ', 'systemx/sysx_org_manage.jsp                                                                         ', '获得机构详细信息                                  ', 'V2.1.tamcx          ', '01                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('org_manage          ', 'add                 ', '添加                          ', 'systemx/sysx_org_manage.jsp                                                                         ', '添加                                              ', 'V2.1.tamcx          ', '01                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('user_manage         ', 'resetPass           ', '重置密码                      ', 'systemx/sysx_user_manage.jsp                                                                        ', '重置密码                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('user_manage         ', 'qry                 ', '查询                          ', 'systemx/sysx_user_manage.jsp                                                                        ', '用户查询                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('user_manage         ', 'del                 ', '删除                          ', 'systemx/sysx_user_manage.jsp                                                                        ', '删除用户信息                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('user_manage         ', 'roleAss             ', '角色分配                      ', 'systemx/sysx_user_manage.jsp                                                                        ', '角色分配                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('user_manage         ', 'roleAssUpt          ', '角色分配更新                  ', 'systemx/sysx_user_manage.jsp                                                                        ', '角色分配更新                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('user_manage         ', 'tranAss             ', '交易分配                      ', 'systemx/sysx_user_manage.jsp                                                                        ', '交易权限分配                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('reportPz            ', 'lst                 ', '查询                          ', 'systemx/sysx_report.jsp                                                                             ', '查询                                              ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('sendPz              ', 'upt                 ', '执行通讯更新                  ', 'app/gaps/sendPzNew.jsp                                                                              ', '执行更新通讯                                      ', 'V2.1.gaps           ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('org_manage          ', 'def                 ', '默认                          ', 'systemx/sysx_org_manage.jsp                                                                         ', '默认                                              ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('user_manage         ', 'tranAssUpt          ', '交易分配更新                  ', 'systemx/sysx_user_manage.jsp                                                                        ', '交易权限分配更新                                  ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('user_manage         ', 'dataAss             ', '数据分配                      ', 'systemx/sysx_user_manage.jsp                                                                        ', '数据权限分配                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('user_manage         ', 'dataAssUpt          ', '数据分配更新                  ', 'systemx/sysx_user_manage.jsp                                                                        ', '数据权限分配更新                                  ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('user_manage         ', 'add                 ', '增加页面                      ', 'systemx/sysx_user_manage.jsp                                                                        ', '增加用户信息页面                                  ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('user_manage         ', 'def                 ', '默认                          ', 'systemx/sysx_user_manage.jsp                                                                        ', '默认                                              ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('user_manage         ', 'upt                 ', '更新                          ', 'systemx/sysx_user_manage.jsp                                                                        ', '更新用户信息                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('user_manage         ', 'warrant             ', '授权                          ', 'systemx/sysx_user_manage.jsp                                                                        ', '授权                                              ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('user_manage         ', 'list                ', '查询用户                      ', 'systemx/sysx_user_manage.jsp                                                                        ', '查询用户显示到界面                                ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('user_manage         ', 'lstprv              ', '列出权限                      ', 'systemx/sysx_user_manage.jsp                                                                        ', '列出权限                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('refresh_param       ', 'def                 ', '系统参数刷新                  ', 'system/refreshParam.jsp                                                                             ', '系统参数刷新                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('system_param        ', 'def                 ', '默认                          ', 'systemx/sysx_parammanage.jsp                                                                        ', '系统参数维护                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('system_param        ', 'list                ', '默认                          ', 'systemx/sysx_parammanage.jsp                                                                        ', '系统参数维护                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('system_param        ', 'add                 ', '默认                          ', 'systemx/sysx_parammanage.jsp                                                                        ', '系统参数维护                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('system_param        ', 'upt                 ', '默认                          ', 'systemx/sysx_parammanage.jsp                                                                        ', '系统参数维护                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('menux               ', 'list                ', '查询                          ', 'systemx/sys_menu.jsp                                                                                ', '查询                                              ', 'V2.1.tamcx          ', '01                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('menux               ', 'get                 ', '获得菜单详细                  ', 'systemx/sys_menu.jsp                                                                                ', '获得单个菜单信息                                  ', 'V2.1.tamcx          ', '01                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('menux               ', 'add                 ', '添加                          ', 'systemx/sys_menu.jsp                                                                                ', '添加                                              ', 'V2.1.tamcx          ', '01                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('menux               ', 'def                 ', '显示菜单树                    ', 'systemx/sys_menu.jsp                                                                                ', '查询菜单信息,以树形菜单显示                       ', 'V2.1.tamcx          ', '01                            ', null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('usermacheck         ', 'def                 ', '默认                          ', 'systemx/sysx_userma_check.jsp                                                                       ', '默认                                              ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('usermacheck         ', 'list                ', '查询                          ', 'about:blank                                                                                         ', '查询                                              ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('usermacheck         ', 'chk                 ', '审核                          ', 'about:blank                                                                                         ', '审核                                              ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('usermacheck         ', 'del                 ', '删除                          ', 'about:blank                                                                                         ', '删除不能通过审核的用户                            ', 'V2.1.zhhr           ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('ipreg               ', 'def                 ', '默认                          ', 'systemx/sysx_ip_reg.jsp                                                                             ', '默认                                              ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('ipreg               ', 'list                ', '查询                          ', 'systemx/sysx_ip_reg.jsp                                                                             ', '查询                                              ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('ipreg               ', 'add                 ', '增加                          ', 'systemx/sysx_ip_reg.jsp                                                                             ', '增加                                              ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('ipreg               ', 'upt                 ', '修改                          ', 'systemx/sysx_ip_reg.jsp                                                                             ', '修改                                              ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('ipreg               ', 'del                 ', '删除                          ', 'systemx/sysx_ip_reg.jsp                                                                             ', '删除                                              ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('changePwd           ', 'change              ', '修改密码                      ', 'systemx/sysx_change_pwd.jsp                                                                         ', '修改密码                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('reportPz            ', 'listPara            ', '查询报表条件                  ', 'systemx/sysx_report.jsp                                                                             ', '查询报表条件                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('reportPz            ', 'uptPara             ', '修改报表条件                  ', 'systemx/sysx_report.jsp                                                                             ', '修改报表条件                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('reportPz            ', 'delPara             ', '删除报表条件                  ', 'systemx/sysx_report.jsp                                                                             ', '删除报表条件                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('reportPz            ', 'addPara             ', '增加报表条件                  ', 'systemx/sysx_report.jsp                                                                             ', '增加报表条件                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('pzjyexport          ', 'def                 ', '默认                          ', 'systemx/extension/pzjyexport.jsp                                                                    ', '默认                                              ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('pzjyexport          ', 'export              ', '导出                          ', 'systemx/extension/pzjyexport.jsp                                                                    ', '导出                                              ', 'V2.1.tx             ', null, null, null);
insert into T_SUB_TRAN (TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
values ('pzjyexport          ', 'down                ', '下载                          ', 'systemx/extension/pzjyexport.jsp                                                                    ', '下载                                              ', 'V2.1.tx             ', null, null, null);


insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('tx_page_dispatcher  ', 'TX页面跳转主控                ', '0', 'com.hundsun.tamcx.app.extension.ctl.DispatcherCtl                                                   ', 'V2.1.tx             ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('tx_report_cfg       ', 'TX表报配置                    ', '1', 'com.hundsun.tamcx.app.extension.ctl.ReportPzCtl                                                     ', 'V2.1.tx             ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('tx_report_ctl       ', 'TX简单报表主控                ', '2', 'com.hundsun.tamcx.app.extension.system.ReportProcessCtl                                             ', 'V2.1.tx             ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('tx_table            ', 'TX数据库表管理                ', '0', 'com.hundsun.tamcx.app.extension.ctl.TableCtl                                                        ', 'V2.1.tx             ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('tx_xml_operator     ', 'xml交易配置                   ', '0', 'com.hundsun.tamcx.app.extension.ctl.GapsCommCtl                                                     ', 'V2.1.tx             ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('sendPz              ', '交易配置管理                  ', '0', ' com.hundsun.agent.gaps.MessageSendCtl                                                              ', 'V2.1.gaps           ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('send                ', '交易                          ', '0', ' com.hundsun.agent.gaps.SystemSendCtl                                                               ', 'V2.1.gaps           ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('gapsdown            ', '从GAPS获得文件                ', '0', ' com.hundsun.agent.send.GapsDownCtl                                                                 ', 'V2.1.gaps           ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('cpsj_manage         ', '产品升级管理                  ', '0', 'com.hundsun.tamcx.system.cpsj.CpsjManageCtl                                                         ', 'V2.1.tamcx          ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('TranSubtran         ', '交易配置                      ', '0', 'com.hundsun.tamcx.systemx.ctl.TranSubtranCtl                                                        ', 'V2.1.tamcx          ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('menu_conf           ', '菜单配置                      ', '0', 'com.hundsun.tamcx.systemx.ctl.MenuConfCtl                                                           ', 'V2.1.tamcx          ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('refresh_param       ', '刷新系统参数                  ', '0', 'com.hundsun.tamcx.systemx.ctl.RefreshParamCtl                                                       ', 'V2.1.tamcx          ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('logon               ', '用户登录                      ', '0', 'com.hundsun.tamcx.system.ctl.LogonCtl                                                               ', 'V2.1.tamcx          ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('user_menage         ', '用户管理                      ', '0', 'com.hundsun.tamcx.system.ctl.UserMenageCtl                                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('dict_menage         ', '数据字典管理                  ', '0', 'com.hundsun.tamcx.system.ctl.DictMenageCtl                                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('system_param        ', '系统参数管理                  ', '0', 'com.hundsun.tamcx.systemx.ctl.SystemParamCtl                                                        ', 'V2.1.tamcx          ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('tamcx_upgrade       ', '产品升级                      ', '0', 'com.hundsun.tamcx.system.ctl.TamcxUpgradeCtl                                                        ', 'V2.1.tamcx          ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('reportPz            ', '报表配置                      ', '0', 'com.hundsun.tamcx.systemx.ctl.ReportPzCtl                                                           ', 'V2.1.tamcx          ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('reportCondPz        ', '报表条件配置                  ', '0', 'com.hundsun.tamcx.system.report.ReportCondPzCtl                                                     ', 'V2.1.tamcx          ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('ipMenage            ', '登录IP管理                    ', '0', 'com.hundsun.tamcx.system.ctl.IpMenageCtl                                                            ', 'V2.1.tamcx          ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('expsql              ', '导出SQL                       ', '0', 'com.hundsun.tamcx.systemx.util.ExpSql                                                               ', 'V2.1.tamcx          ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('mvSend              ', 'GAPS通讯[授权]                ', '0', ' com.hundsun.agent.gaps.MvSystemSendCtl                                                             ', 'V2.1.gaps           ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('test2               ', 'test2                         ', '2', 'com.hundsun.tamcx.systemx.extension.ctl.HundsunExtension                                            ', 'V2.1.tx             ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('usermacheck         ', '用户审核                      ', '0', 'com.hundsun.tamcx.systemx.ctl.UserMaCheckCtl                                                        ', 'V2.1.tamcx          ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('dictManage          ', '系统数据字典管理              ', '1', 'com.hundsun.tamcx.systemx.ctl.DictManageCtl                                                         ', 'V2.1.tamcx          ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('gapsconfig          ', 'GAPS通讯配置                  ', '0', 'com.hundsun.tamcx.systemx.ctl.GapsConfigCtl                                                         ', 'V2.1.tamcx          ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('org_manage          ', '机构管理                      ', '0', 'com.hundsun.tamcx.systemx.ctl.OrgManageCtl                                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('role_manage         ', '角色管理                      ', '0', 'com.hundsun.tamcx.systemx.ctl.RoleManageCtl                                                         ', 'V2.1.tamcx          ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('user_manage         ', '用户管理                      ', '0', 'com.hundsun.tamcx.systemx.ctl.UserManageCtl                                                         ', 'V2.1.tamcx          ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('ipreg               ', 'IP登记管理                    ', '0', 'com.hundsun.tamcx.systemx.ctl.IpRegCtl                                                              ', 'V2.1.tamcx          ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('statusmonitor       ', '进程状态                      ', '0', 'com.hundsun.tamcx.systemx.ctl.StatusMonitorCtl                                                      ', 'V2.1.tamcx          ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('appversionmanage    ', '应用版本配置                  ', '0', 'com.hundsun.tamcx.systemx.ctl.AppVersionManageCtl                                                   ', 'V2.1.tamcx          ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('report              ', '报表查询                      ', '1', 'com.hundsun.tamcx.systemx.report.ReportCtl                                                          ', 'V2.1.tamcx          ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('changePwd           ', '修改密码                      ', '0', 'com.hundsun.tamcx.systemx.ctl.ChangePasswordCtl                                                     ', 'V2.1.tamcx          ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('alterUserPass       ', '修改用户密码                  ', '0', 'com.hundsun.tamcx.system.ctl.AlterUserPassCtl                                                       ', 'V2.1.tamcx          ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('menux               ', '菜单配置                      ', '0', 'com.hundsun.tamcx.systemx.ctl.MenuConfCtl                                                           ', 'V2.1.tamcx          ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('HundsunExtension    ', 'TX通用主控                    ', '0', 'com.hundsun.tamcx.systemx.extension.ctl.HundsunExtension                                            ', 'V2.1.tx             ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('tx_app_page_gen     ', '应用界面生成                  ', '0', 'com.hundsun.tamcx.systemx.extension.di.DIControl                                                    ', 'V2.1.tx             ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('tx_composite_cfg    ', 'TX组件配置                    ', '0', 'com.hundsun.tamcx.app.extension.ctl.CompositeCtl                                                    ', 'V2.1.tx             ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('tx_db_operator      ', 'TX数据库表维护                ', '0', 'com.hundsun.tamcx.systemx.extension.ctl.DbOperatorCtl                                               ', 'V2.1.tx             ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('tx_di_test          ', '数据接口测试                  ', '0', 'com.hundsun.tamcx.systemx.extension.di.DIControl                                                    ', 'V2.1.tx             ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('tx_ext_doc          ', 'EXT 帮助文档                  ', '0', 'com.hundsun.tamcx.app.extension.di.DIControl                                                        ', 'V2.1.tx             ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('tx_main_config      ', 'TX组件配置交易                ', '0', 'com.hundsun.tamcx.app.extension.ctl.ConfigCtl                                                       ', 'V2.1.tx             ', null, null, null);
insert into T_TRAN (TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
values ('pzjyexport          ', '配置交易导出                  ', '1', 'com.hundsun.tamcx.systemx.extension.ctl.PzjyExportCtl                                               ', 'V2.1.tx             ', null, null, null);
