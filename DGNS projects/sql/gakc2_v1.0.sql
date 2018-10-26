drop table TBL_CK_DTCXAJ;
drop table TBL_CK_DTCXZH;
drop table TBL_CK_JJZFQQAJ;
drop table TBL_CK_JJZFQQZH;
drop table TBL_CK_DZQZCXAJ;
drop table TBL_CK_DZQZCXDZZJ;


create table TBL_CK_DTCXAJ (
   DOCNO                VARCHAR(50)            not null,
   CASENO               VARCHAR(100)           not null,
   SBNO                 VARCHAR(32)            not null,
   CASETYPE             VARCHAR(10),
   EXEUNIT              VARCHAR(100),
   APPLYORG             VARCHAR(20),
   TARGETORG            VARCHAR(20),
   REMARK               VARCHAR(200),
   SENDTIME             VARCHAR(20),
   EXENAME              VARCHAR(100),
   POLICECERT           VARCHAR(30),
   POLICETEL            VARCHAR(30),
   EXENAME2             VARCHAR(100),
   POLICECERT2          VARCHAR(30),
   POLICETEL2           VARCHAR(30),
   EXENAME3             VARCHAR(100),
   POLICECERT3          VARCHAR(30),
   POLICETEL3           VARCHAR(30),
   BEIY1                VARCHAR(30),
   BEIY2                VARCHAR(200),
   BEIY3                VARCHAR(200),
   constraint "P_gack_dtcxaj" primary key (DOCNO, CASENO, SBNO)
);

create table TBL_CK_DTCXZH (
   DOCNO                VARCHAR(50)            not null,
   CASENO               VARCHAR(100)           not null,
   UNIQUEID             VARCHAR(40)            not null,
   SBNO                 VARCHAR(32)            not null,
   SEQ                  VARCHAR(40),
   OLDSEQ               VARCHAR(40),
   URGENCY              VARCHAR(40),
   ACCOUNT              VARCHAR(50)            not null,
   ACCTYPE              VARCHAR(30),
   ACCNAME              VARCHAR(100),
   UPTYPE               VARCHAR(10),
   IDTYPE               VARCHAR(20),
   IDNUM                VARCHAR(18),
   INTERVAL             VARCHAR(10),
   STARTDATE            VARCHAR(20),
   ENDDATE              VARCHAR(20),
   NOTIFYDOC            VARCHAR(40),
   DOCNUM               VARCHAR(30),
   BEIY1                VARCHAR(30),
   BEIY2                VARCHAR(100),
   BEIY3                VARCHAR(100),
   constraint "P_gack_dtcxzh" primary key (DOCNO, CASENO, UNIQUEID, 
SBNO)
);

create table TBL_CK_JJZFQQAJ (
   DOCNO                VARCHAR(50)            not null,
   CASENO               VARCHAR(100)           not null,
   SBNO                 VARCHAR(32)            not null,
   CASETYPE             VARCHAR(10),
   EXEUNIT              VARCHAR(100),
   APPLYORG             VARCHAR(20),
   TARGETORG            VARCHAR(20),
   REMARK               VARCHAR(200),
   SENDTIME             VARCHAR(20),
   EXENAME              VARCHAR(100),
   POLICECERT           VARCHAR(30),
   POLICETEL            VARCHAR(30),
   EXENAME2             VARCHAR(100),
   POLICECERT2          VARCHAR(30),
   POLICETEL2           VARCHAR(30),
   EXENAME3             VARCHAR(100),
   POLICECERT3          VARCHAR(30),
   POLICETEL3           VARCHAR(30),
   BEIY1                VARCHAR(30),
   BEIY2                VARCHAR(200),
   BEIY3                VARCHAR(200),
   constraint P_PK_JJZFQQAJ primary key (DOCNO, CASENO, SBNO)
);



create table TBL_CK_JJZFQQZH (
   DOCNO                VARCHAR(50)            not null,
   CASENO               VARCHAR(100)           not null,
   SBNO                 VARCHAR(32)            not null,
   UNIQUEID             VARCHAR(40)            not null,
   UPTYPE               VARCHAR(10),
   NAME                 VARCHAR(100),
   IDTYPE               VARCHAR(20),
   IDNUM                VARCHAR(18),
   OLDSEQ               VARCHAR(50),
   ACCOUNT              VARCHAR(50),
   STOPPAYMENT          VARCHAR(10),
   BEIY1                VARCHAR(10),
   BEIY2                VARCHAR(20),
   BEIY3                VARCHAR(100),
   constraint P_PK_JJZFQQZHZH primary key (DOCNO, CASENO, SBNO, 
UNIQUEID)
);

create table TBL_CK_DZQZCXAJ (
   DOCNO                VARCHAR(50)            not null,
   CASENO               VARCHAR(100)           not null,
   SBNO                 VARCHAR(32)            not null,
   CASETYPE             VARCHAR(10),
   EXEUNIT              VARCHAR(100),
   APPLYORG             VARCHAR(20),
   TARGETORG            VARCHAR(20),
   URGENCY              VARCHAR(2),
   REMARK               VARCHAR(200),
   SENDTIME             VARCHAR(20),
   EXENAME              VARCHAR(100),
   POLICECERT           VARCHAR(30),
   POLICETEL            VARCHAR(30),
   EXENAME2             VARCHAR(100),
   POLICECERT2          VARCHAR(30),
   POLICETEL2           VARCHAR(30),
   EXENAME3             VARCHAR(100),
   POLICECERT3          VARCHAR(30),
   POLICETEL3           VARCHAR(30),
   BEIY1                VARCHAR(30),
   BEIY2                VARCHAR(200),
   BEIY3                VARCHAR(200),
   constraint P_PK_DZQZCXAJ primary key (DOCNO, CASENO, SBNO)
);



create table TBL_CK_DZQZCXDZZJ (
   DOCNO                VARCHAR(50)            not null,
   CASENO               VARCHAR(100)           not null,
   SBNO                 VARCHAR(32)            not null,
   UNIQUEID             VARCHAR(40)            not null,
   FILENAME             VARCHAR(10)            not null,
   FILEHASH             VARCHAR(100)           not null,
   FILESTATUS           VARCHAR(2)             not null,
   SRCFILE              VARCHAR(200),
   STAMPEDFILE          VARCHAR(200),
   BEIY1                VARCHAR(10),
   BEIY2                VARCHAR(20),
   BEIY3                VARCHAR(100),
   constraint P_PK_DZQZCXDZZJ primary key (DOCNO, CASENO, SBNO, 
UNIQUEID)
);


