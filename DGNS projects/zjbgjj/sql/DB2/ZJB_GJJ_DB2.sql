drop table yw_gjj_trans;

/*==============================================================*/
/* Table: yw_gjj_trans                                        */
/*==============================================================*/
create table yw_gjj_trans 
(
   sendseqno          VARCHAR(32)          not null,
   txunitno           VARCHAR(15)          not null,
   sendnode           VARCHAR(6),
   senddate           VARCHAR(8)              not null,
   sendtime           VARCHAR(6),
   transcode          VARCHAR(7)           not null,
   receivenode        VARCHAR(6),
   bdcdate            VARCHAR(8),
   bdctime            VARCHAR(6),
   bdcseqno           VARCHAR(32),
   custno             VARCHAR(32),
   operno             VARCHAR(21),
   beginrec           INTEGER,
   maxrec             INTEGER,
   clrq               VARCHAR(8),
   clsj               VARCHAR(6),
   jbjg               VARCHAR(16),
   jbgy               VARCHAR(16),
   ywlsh              VARCHAR(32),
   hoststatus         VARCHAR(1),
   hostseqno          VARCHAR(32),
   hostmsg            VARCHAR(160),
   hostrespcode       VARCHAR(20),
   zjrq               VARCHAR(8),
   zjsj               VARCHAR(6),
   tjhxcs             INTEGER,
   caphostseqno       VARCHAR(32),
   inthostseqno       VARCHAR(32),
   penhostseqno       VARCHAR(32),
   finehostseqno      VARCHAR(32),
   summary            VARCHAR(60),
   batch              VARCHAR(20),
   transdate          VARCHAR(8)           not null,
   transtime          VARCHAR(8),
   qzlsh              VARCHAR(10)          not null,
   qqdzt              VARCHAR(2),
   respcode           VARCHAR(8),
   respmsg            VARCHAR(100),
   zwrq               VARCHAR(8),
   systime            VARCHAR(6),
   remark             VARCHAR(32),
   remark1            VARCHAR(64),
   remark2            VARCHAR(128),
   remark3            VARCHAR(254),
   remark4            VARCHAR(254),
   constraint PK_TRANS primary key (sendseqno, txunitno)
);

comment on table yw_gjj_trans is
'ס��������������ˮ��';

comment on column yw_gjj_trans.sendseqno is
'���ͷ���ˮ��';

comment on column yw_gjj_trans.txunitno is
'���׻�����';

comment on column yw_gjj_trans.sendnode is
'���Ĵ���';

comment on column yw_gjj_trans.senddate is
'���ͷ�����';

comment on column yw_gjj_trans.transcode is
'������';

comment on column yw_gjj_trans.bdcdate is
'�ɼ�ϵͳ����';

comment on column yw_gjj_trans.bdctime is
'����Ӧ��ϵͳʱ��';

comment on column yw_gjj_trans.bdcseqno is
'�ɼ�ϵͳ��ˮ��';

comment on column yw_gjj_trans.custno is
'���пͻ����';

comment on column yw_gjj_trans.operno is
'���Ͳ���Ա';

comment on column yw_gjj_trans.beginrec is
'��ʼ��¼��';

comment on column yw_gjj_trans.maxrec is
'һ�β�ѯ����¼��';

comment on column yw_gjj_trans.clrq is
'��������';

comment on column yw_gjj_trans.clsj is
'����ʱ��';

comment on column yw_gjj_trans.jbjg is
'�������';

comment on column yw_gjj_trans.jbgy is
'�����Ա';

comment on column yw_gjj_trans.ywlsh is
'ҵ����ˮ��';

comment on column yw_gjj_trans.hoststatus is
'������������״̬0-�ɹ� 1-ʧ�� 3-��ʱ 9-��ʼ';

comment on column yw_gjj_trans.hostseqno is
'����������ˮ��';

comment on column yw_gjj_trans.hostmsg is
'����������Ӧ��Ϣ';

comment on column yw_gjj_trans.hostrespcode is
'����������Ӧ��';

comment on column yw_gjj_trans.zjrq is
'��������';

comment on column yw_gjj_trans.zjsj is
'����ʱ��';

comment on column yw_gjj_trans.tjhxcs is
'�ύ���Ĵ���';

comment on column yw_gjj_trans.caphostseqno is
'��������������ˮ��';

comment on column yw_gjj_trans.inthostseqno is
'��Ϣ����������ˮ��';

comment on column yw_gjj_trans.penhostseqno is
'���Ϣ����������ˮ��';

comment on column yw_gjj_trans.finehostseqno is
'����ΥԼ��������ˮ��';

comment on column yw_gjj_trans.summary is
'ժҪ';

comment on column yw_gjj_trans.batch is
'�����������';

comment on column yw_gjj_trans.transdate is
'��������';

comment on column yw_gjj_trans.transtime is
'����ʱ��';

comment on column yw_gjj_trans.qzlsh is
'ǰ����ˮ��';

comment on column yw_gjj_trans.qqdzt is
'11-���ʧ��,20-����ش�����,21-�ύʧ��,23-�ύ��ʱ,30-���ύ�����,31-���ʧ��,33-��س�ʱ,40-�Ѵ��������,41-����ʧ��,43-������ʱ,99-�ѷ���';

comment on column yw_gjj_trans.zwrq is
'ǰ������';

comment on column yw_gjj_trans.systime is
'ǰ��ʱ��';

comment on column yw_gjj_trans.remark is
'��ע';

comment on column yw_gjj_trans.remark1 is
'����1';

comment on column yw_gjj_trans.remark2 is
'��ע2';

comment on column yw_gjj_trans.remark3 is
'����3';

comment on column yw_gjj_trans.remark4 is
'����4';













drop table yw_gjj_dbsfk;

/*==============================================================*/
/* Table: yw_gjj_dbsfk                                        */
/*==============================================================*/
create table yw_gjj_dbsfk 
(
   sendseqno          VARCHAR(32)          not null,
   txunitno           VARCHAR(15)          not null,
   sfkbz              VARCHAR(1),
   currno             VARCHAR(3),
   curriden           VARCHAR(1),
   settletype         VARCHAR(1),
   bustype            VARCHAR(6),
   deacctno           VARCHAR(32),
   deacctname         VARCHAR(60),
   deacctclass        VARCHAR(1),
   debankname         VARCHAR(60),
   dechgno            VARCHAR(12),
   debankclass        VARCHAR(1),
   conagrno           VARCHAR(32),
   capamt             NUMERIC(16,2),
   deintacctno        VARCHAR(32),
   deintacctname      VARCHAR(60),
   deintacctclass     VARCHAR(1),
   deintcracct        VARCHAR(32),
   intamt             NUMERIC(16,2),
   cracctno           VARCHAR(32),
   cracctname         VARCHAR(60),
   cracctclass        VARCHAR(1),
   crbankclass        VARCHAR(1),
   crbankname         VARCHAR(60),
   crchgno            VARCHAR(12),
   amt                NUMERIC(16,2),
   refacctno          VARCHAR(32),
   refseqno1          VARCHAR(32),
   refseqno2          VARCHAR(32),
   zwrq               VARCHAR(8),
   systime            VARCHAR(6),
   remark             VARCHAR(32),
   remark1            VARCHAR(64),
   remark2            VARCHAR(128),
   remark3            VARCHAR(254),
   remark4            VARCHAR(254),
   constraint PK_DBSFK primary key (sendseqno, txunitno)
);

comment on table yw_gjj_dbsfk is
'ס���������𵥱��ո����';

comment on column yw_gjj_dbsfk.sendseqno is
'���ͷ���ˮ��';

comment on column yw_gjj_dbsfk.txunitno is
'���׻�����';

comment on column yw_gjj_dbsfk.sfkbz is
'�ո����־0-�տ1-����';

comment on column yw_gjj_dbsfk.currno is
'����';

comment on column yw_gjj_dbsfk.curriden is
'�������';

comment on column yw_gjj_dbsfk.settletype is
'����ģʽ';

comment on column yw_gjj_dbsfk.bustype is
'ҵ������';

comment on column yw_gjj_dbsfk.deacctno is
'�����˺�';

comment on column yw_gjj_dbsfk.deacctname is
'��������';

comment on column yw_gjj_dbsfk.deacctclass is
'�����˻����';

comment on column yw_gjj_dbsfk.debankname is
'��������';

comment on column yw_gjj_dbsfk.dechgno is
'�������к�';

comment on column yw_gjj_dbsfk.debankclass is
'�����˻��б�';

comment on column yw_gjj_dbsfk.conagrno is
'�෽Э���';

comment on column yw_gjj_dbsfk.capamt is
'��������';

comment on column yw_gjj_dbsfk.deintacctno is
'��Ϣ���˺�';

comment on column yw_gjj_dbsfk.deintacctname is
'��Ϣ������';

comment on column yw_gjj_dbsfk.deintacctclass is
'��Ϣ�����';

comment on column yw_gjj_dbsfk.deintcracct is
'��Ϣ�շ��˺�';

comment on column yw_gjj_dbsfk.intamt is
'��Ϣ������';

comment on column yw_gjj_dbsfk.cracctno is
'�շ��˺�';

comment on column yw_gjj_dbsfk.cracctname is
'�շ�����';

comment on column yw_gjj_dbsfk.cracctclass is
'�շ��˻����';

comment on column yw_gjj_dbsfk.crbankclass is
'�շ��˻��б�';

comment on column yw_gjj_dbsfk.crbankname is
'�շ�����';

comment on column yw_gjj_dbsfk.crchgno is
'�շ����к�';

comment on column yw_gjj_dbsfk.amt is
'���';

comment on column yw_gjj_dbsfk.refacctno is
'ҵ����ϸ�˺�';

comment on column yw_gjj_dbsfk.refseqno1 is
'ҵ����ϸ��ˮ��1';

comment on column yw_gjj_dbsfk.refseqno2 is
'ҵ����ϸ��ˮ��2';

comment on column yw_gjj_dbsfk.zwrq is
'ǰ������';

comment on column yw_gjj_dbsfk.systime is
'ǰ��ʱ��';

comment on column yw_gjj_dbsfk.remark is
'��ע';

comment on column yw_gjj_dbsfk.remark1 is
'����1';

comment on column yw_gjj_dbsfk.remark2 is
'��ע2';

comment on column yw_gjj_dbsfk.remark3 is
'����3';

comment on column yw_gjj_dbsfk.remark4 is
'����4';














drop table yw_gjj_drbatch;

/*==============================================================*/
/* Table: yw_gjj_drbatch                                      */
/*==============================================================*/
create table yw_gjj_drbatch 
(
   sendseqno          VARCHAR(32)          not null,
   txunitno           VARCHAR(15)          not null,
   sfkbz              VARCHAR(1),
   batchno            VARCHAR(20)          not null,
   fileno             VARCHAR(8)           not null,
   currno             VARCHAR(3),
   curriden           VARCHAR(1),
   filetype           VARCHAR(1),
   bustype            VARCHAR(6),
   batchprjno         VARCHAR(32),
   acctno             VARCHAR(32),
   acctname           VARCHAR(60),
   acctclass          VARCHAR(1),
   batchcapamt        NUMERIC(16,2),
   deintacctno        VARCHAR(32),
   deintacctname      VARCHAR(60),
   deintacctclass     VARCHAR(1),
   deintcracct        VARCHAR(32),
   batchintamt        NUMERIC(16,2),
   bankacctno         VARCHAR(32),
   batchtotalnum      INTEGER,
   batchtotalamt      NUMERIC(16,2),
   batchsuccnum       INTEGER,
   batchsuccamt       NUMERIC(16,2),
   batchfailnum       INTEGER,
   batchfailamt       NUMERIC(16,2),
   zipfilename        VARCHAR(128),
   unzipfilename      VARCHAR(128),
   trantype           VARCHAR(1),
   dealtype           VARCHAR(1),
   dealstep           VARCHAR(1),
   dealstatus         VARCHAR(5),
   dealinf            VARCHAR(160),
   batchpch           VARCHAR(64),
   querystatus        VARCHAR(1),
   zwrq               VARCHAR(8),
   systime            VARCHAR(6),
   remark             VARCHAR(32),
   remark1            VARCHAR(64),
   remark2            VARCHAR(128),
   remark3            VARCHAR(254),
   remark4            VARCHAR(254),
   constraint PK_DRBATCH primary key (sendseqno, txunitno)
);

comment on table yw_gjj_drbatch is
'ס���������������ո�������';

comment on column yw_gjj_drbatch.sendseqno is
'���ͷ���ˮ��';

comment on column yw_gjj_drbatch.txunitno is
'���׻�����';

comment on column yw_gjj_drbatch.sfkbz is
'�ո����־0-�տ�,1-����,2-�ۿ�';

comment on column yw_gjj_drbatch.batchno is
'���κ�';

comment on column yw_gjj_drbatch.fileno is
'�ļ����';

comment on column yw_gjj_drbatch.currno is
'����';

comment on column yw_gjj_drbatch.curriden is
'�������';

comment on column yw_gjj_drbatch.filetype is
'�ļ�����';

comment on column yw_gjj_drbatch.bustype is
'ҵ������';

comment on column yw_gjj_drbatch.batchprjno is
'������Ŀ���';

comment on column yw_gjj_drbatch.acctno is
'�˺�';

comment on column yw_gjj_drbatch.acctname is
'����';

comment on column yw_gjj_drbatch.acctclass is
'�˻����';

comment on column yw_gjj_drbatch.batchcapamt is
'�������';

comment on column yw_gjj_drbatch.deintacctno is
'������Ϣ���˺�';

comment on column yw_gjj_drbatch.deintacctname is
'������Ϣ������';

comment on column yw_gjj_drbatch.deintacctclass is
'������Ϣ�����';

comment on column yw_gjj_drbatch.deintcracct is
'��Ϣ�շ��˺�';

comment on column yw_gjj_drbatch.batchintamt is
'������Ϣ���';

comment on column yw_gjj_drbatch.bankacctno is
'�����ڲ����ɻ�';

comment on column yw_gjj_drbatch.batchtotalnum is
'�ܱ���';

comment on column yw_gjj_drbatch.batchtotalamt is
'�ܽ��';

comment on column yw_gjj_drbatch.batchsuccnum is
'�ɹ�����';

comment on column yw_gjj_drbatch.batchsuccamt is
'�ɹ����';

comment on column yw_gjj_drbatch.batchfailnum is
'ʧ�ܱ���';

comment on column yw_gjj_drbatch.batchfailamt is
'ʧ�ܽ��';

comment on column yw_gjj_drbatch.zipfilename is
'�����ļ���';

comment on column yw_gjj_drbatch.unzipfilename is
'�����ļ���';

comment on column yw_gjj_drbatch.trantype is
'������� a�����ڴ��� b�����ڴ��� c�����д��� d: ���д��� e: ��ϴ��� f: ��ϴ��� g: ����';

comment on column yw_gjj_drbatch.dealtype is
'��������1:�ļ� 2:��� 3:��֧��';

comment on column yw_gjj_drbatch.dealstep is
'������0-��̬��1-���ף�2-�����У�3-�������';

comment on column yw_gjj_drbatch.dealstatus is
'0-��̬��1-�ɹ���2-ʧ��';

comment on column yw_gjj_drbatch.dealinf is
'����������';

comment on column yw_gjj_drbatch.batchpch is
'���Ĵ������κ�';

comment on column yw_gjj_drbatch.querystatus is
'�����ѯ״̬0-δ��ѯ��1-�Ѳ�ѯ��2-��ѯʧ��';

comment on column yw_gjj_drbatch.zwrq is
'ǰ������';

comment on column yw_gjj_drbatch.systime is
'ǰ��ʱ��';

comment on column yw_gjj_drbatch.remark is
'��ע';

comment on column yw_gjj_drbatch.remark1 is
'��ע1';

comment on column yw_gjj_drbatch.remark2 is
'��ע2';

comment on column yw_gjj_drbatch.remark3 is
'��ע3';

comment on column yw_gjj_drbatch.remark4 is
'��ע4';




















drop table yw_gjj_drbatchmx;

/*==============================================================*/
/* Table: yw_gjj_drbatchmx                                    */
/*==============================================================*/
create table yw_gjj_drbatchmx 
(
   sendseqno          VARCHAR(32)          not null,
   txunitno           VARCHAR(15)          not null,
   seqno              VARCHAR(20)          not null,
   batchno            VARCHAR(20)          not null,
   fileno             VARCHAR(5)           not null,
   amt                NUMERIC(16,2),
   acctno             VARCHAR(32),
   acctname           VARCHAR(60),
   chgno              VARCHAR(12),
   openchgno          VARCHAR(12),
   drbal              NUMERIC(16,2),
   crbal              NUMERIC(16,2),
   address            VARCHAR(80),
   conagrno           VARCHAR(32),
   amttype            VARCHAR(1),
   summary            VARCHAR(60),
   mxacctno           VARCHAR(32),
   mxserialno1        VARCHAR(32),
   mxserialno2        VARCHAR(32),
   capamt             NUMERIC(16,2),
   intamt             NUMERIC(16,2),
   dealstatus         VARCHAR(1),
   hostseq            VARCHAR(32),
   hostdate           VARCHAR(8),
   caphostseqno       VARCHAR(32),
   inthostseqno       VARCHAR(32),
   dealcode           VARCHAR(5),
   dealmsg            VARCHAR(160),
   hzno               VARCHAR(32),
   bankex             VARCHAR(254),
   zwrq               VARCHAR(8),
   systime            VARCHAR(6),
   remark             VARCHAR(32),
   remark1            VARCHAR(128),
   remark2            VARCHAR(64),
   remark3            VARCHAR(254),
   remark4            VARCHAR(254),
   constraint PK_DRBATCHMX primary key (sendseqno, txunitno, seqno)
);

comment on table yw_gjj_drbatchmx is
'ס���������������ո�����ϸ��';

comment on column yw_gjj_drbatchmx.sendseqno is
'���ͷ���ˮ��';

comment on column yw_gjj_drbatchmx.txunitno is
'���׻�����';

comment on column yw_gjj_drbatchmx.seqno is
'���';

comment on column yw_gjj_drbatchmx.batchno is
'���κ�';

comment on column yw_gjj_drbatchmx.fileno is
'�ļ����';

comment on column yw_gjj_drbatchmx.amt is
'���';

comment on column yw_gjj_drbatchmx.acctno is
'�˺�';

comment on column yw_gjj_drbatchmx.acctname is
'����';

comment on column yw_gjj_drbatchmx.chgno is
'�˻����к�';

comment on column yw_gjj_drbatchmx.openchgno is
'���������к�';

comment on column yw_gjj_drbatchmx.drbal is
'�������';

comment on column yw_gjj_drbatchmx.crbal is
'�շ����';

comment on column yw_gjj_drbatchmx.address is
'��ַ';

comment on column yw_gjj_drbatchmx.conagrno is
'�෽Э���';

comment on column yw_gjj_drbatchmx.amttype is
'����־';

comment on column yw_gjj_drbatchmx.summary is
'ժҪ';

comment on column yw_gjj_drbatchmx.mxacctno is
'ҵ����ϸ�˺�';

comment on column yw_gjj_drbatchmx.mxserialno1 is
'ҵ����ϸ��ˮ��1';

comment on column yw_gjj_drbatchmx.mxserialno2 is
'ҵ����ϸ��ˮ��2';

comment on column yw_gjj_drbatchmx.capamt is
'��������';

comment on column yw_gjj_drbatchmx.intamt is
'��Ϣ������';

comment on column yw_gjj_drbatchmx.dealstatus is
'������0-��̬��1-�ɹ���2ʧ�ܣ�3��ʱ';

comment on column yw_gjj_drbatchmx.hostseq is
'������ˮ';

comment on column yw_gjj_drbatchmx.hostdate is
'��������';

comment on column yw_gjj_drbatchmx.caphostseqno is
'����������ˮ��';

comment on column yw_gjj_drbatchmx.inthostseqno is
'��Ϣ������ˮ��';

comment on column yw_gjj_drbatchmx.dealcode is
'��������00000-�ɹ���99999��ʱ������ʧ��';

comment on column yw_gjj_drbatchmx.dealmsg is
'��������Ϣ';

comment on column yw_gjj_drbatchmx.hzno is
'��ִ���';

comment on column yw_gjj_drbatchmx.bankex is
'������չ';

comment on column yw_gjj_drbatchmx.zwrq is
'ǰ������';

comment on column yw_gjj_drbatchmx.systime is
'ǰ��ʱ��';

comment on column yw_gjj_drbatchmx.remark is
'����';

comment on column yw_gjj_drbatchmx.remark1 is
'����1';

comment on column yw_gjj_drbatchmx.remark2 is
'����2';

comment on column yw_gjj_drbatchmx.remark3 is
'����3';

comment on column yw_gjj_drbatchmx.remark4 is
'����4';




















drop table yw_gjj_custqy;

/*==============================================================*/
/* Table: yw_gjj_custqy                                       */
/*==============================================================*/
create table yw_gjj_custqy 
(
   receivenode        VARCHAR(6)           not null,
   acctno             VARCHAR(32)          not null,
   custno             VARCHAR(32),
   acctname           VARCHAR(60),
   opbrhno            VARCHAR(20),
   opbrhname          VARCHAR(80),
   acctnature         VARCHAR(1),
   accttype           VARCHAR(1),
   acctkind           VARCHAR(1),
   acctstatus         VARCHAR(1),
   trantype           VARCHAR(1),
   bankacctno         VARCHAR(32),
   bkrefloancapno     VARCHAR(32),
   dkbjacctno         VARCHAR(32),
   dklxacctno         VARCHAR(32),
   qystatus           VARCHAR(1),
   qydate             VARCHAR(8),
   sendflag           VARCHAR(1),
   remark             VARCHAR(32),
   remark1            VARCHAR(64),
   remark2            VARCHAR(128),
   remark3            VARCHAR(254),
   remark4            VARCHAR(254),
   constraint PK_CUSTQY primary key (receivenode, acctno)
);

comment on table yw_gjj_custqy is
'ס���������������˻�ǩԼ��';

comment on column yw_gjj_custqy.receivenode is
'���������Ľڵ��';

comment on column yw_gjj_custqy.acctno is
'�˺�';

comment on column yw_gjj_custqy.custno is
'�ͻ����';

comment on column yw_gjj_custqy.acctname is
'�˻�����';

comment on column yw_gjj_custqy.opbrhno is
'����������';

comment on column yw_gjj_custqy.opbrhname is
'����������';

comment on column yw_gjj_custqy.acctnature is
'1-����2-����3-һ��ͨ';

comment on column yw_gjj_custqy.accttype is
'1-�鼯��2-���㻧3-��ֵ���滧4-�����ר��5-������Ϣר��6-���Ϣר��7-����ΥԼ��ר��';

comment on column yw_gjj_custqy.acctkind is
'2-�Թ�1-��˽';

comment on column yw_gjj_custqy.acctstatus is
'0-ע�� 1-����';

comment on column yw_gjj_custqy.trantype is
'1-ͬ��2-ʵʱ�����У�3-��ʵʱ�����У�';

comment on column yw_gjj_custqy.bankacctno is
'���пۿ��ʽ��ڲ����ɻ�';

comment on column yw_gjj_custqy.bkrefloancapno is
'����ί�д�����˺�';

comment on column yw_gjj_custqy.dkbjacctno is
'���д�����ڲ����ɻ�';

comment on column yw_gjj_custqy.dklxacctno is
'���д�����Ϣ�ڲ����ɻ�';

comment on column yw_gjj_custqy.qystatus is
'0-ǩԼ��1-��Լ';

comment on column yw_gjj_custqy.qydate is
'ǩԼ����';

comment on column yw_gjj_custqy.sendflag is
'0-δ���ͣ�1-������';

comment on column yw_gjj_custqy.remark is
'��ע';

comment on column yw_gjj_custqy.remark1 is
'��ע1';

comment on column yw_gjj_custqy.remark2 is
'��ע2';

comment on column yw_gjj_custqy.remark3 is
'��ע3';

comment on column yw_gjj_custqy.remark4 is
'��ע4';




















drop table yw_gjj_accserial;

/*==============================================================*/
/* Table: yw_gjj_accserial                                    */
/*==============================================================*/
create table yw_gjj_accserial 
(
   sendseqno          VARCHAR(32)          not null,
   sendnode           VARCHAR(6)           not null,
   acctno             VARCHAR(32)          not null,
   seqno              VARCHAR(20)          not null,
   hostseq            VARCHAR(32)          not null,
   jydm               VARCHAR(6),
   rivalacctno        VARCHAR(32),
   rivalacctname      VARCHAR(60),
   amt                NUMERIC(16,2),
   trandate           VARCHAR(8),
   trantime           VARCHAR(6),
   availbal           NUMERIC(16,2),
   openbrhno          VARCHAR(20),
   beiz               VARCHAR(254),
   currno             VARCHAR(3),
   curriden           VARCHAR(1),
   bal                NUMERIC(16,2),
   overamt            NUMERIC(16,2),
   dcmttp             VARCHAR(4),
   dcmtno             VARCHAR(16),
   bankno             VARCHAR(32),
   desctx             VARCHAR(60),
   transtatus         VARCHAR(1),
   penno              VARCHAR(30),
   copno              VARCHAR(30),
   zwrq               VARCHAR(8),
   systime            VARCHAR(6),
   remark             VARCHAR(32),
   remark1            VARCHAR(64),
   remark2            VARCHAR(128),
   remark3            VARCHAR(254),
   remark4            VARCHAR(254),
   constraint PK_ACCSERIAL primary key (sendseqno, sendnode, acctno, seqno, hostseq)
);

comment on table yw_gjj_accserial is
'ס�����������˻��䶯֪ͨ��ϸ��';

comment on column yw_gjj_accserial.acctno is
'�˺�';

comment on column yw_gjj_accserial.seqno is
'���';

comment on column yw_gjj_accserial.hostseq is
'����������ˮ��';

comment on column yw_gjj_accserial.jydm is
'���״���';

comment on column yw_gjj_accserial.rivalacctno is
'���׶����˺�';

comment on column yw_gjj_accserial.rivalacctname is
'���׶��ֻ���';

comment on column yw_gjj_accserial.amt is
'���';

comment on column yw_gjj_accserial.trandate is
'��������';

comment on column yw_gjj_accserial.trantime is
'����ʱ��';

comment on column yw_gjj_accserial.availbal is
'�������';

comment on column yw_gjj_accserial.openbrhno is
'����������';

comment on column yw_gjj_accserial.beiz is
'˵��';

comment on column yw_gjj_accserial.currno is
'����156';

comment on column yw_gjj_accserial.curriden is
'�����־1���� 2����';

comment on column yw_gjj_accserial.bal is
'�˻����';

comment on column yw_gjj_accserial.overamt is
'��͸֧���';

comment on column yw_gjj_accserial.dcmttp is
'ƾ֤����';

comment on column yw_gjj_accserial.dcmtno is
'ƾ֤����';

comment on column yw_gjj_accserial.bankno is
'���׶����к�';

comment on column yw_gjj_accserial.desctx is
'ժҪ';

comment on column yw_gjj_accserial.transtatus is
'Y������
N��δ����';

comment on column yw_gjj_accserial.penno is
'����/֪ͨ/һ��ͨ�˻�ʹ�ã����ڱ�ʶ�˺��²�ͬ���';

comment on column yw_gjj_accserial.copno is
'����/֪ͨ/һ��ͨʹ�ã���ʶ�˺��²�ͬ���';

comment on column yw_gjj_accserial.zwrq is
'ǰ������';

comment on column yw_gjj_accserial.systime is
'ǰ��ʱ��';

comment on column yw_gjj_accserial.remark is
'��ע';

comment on column yw_gjj_accserial.remark1 is
'��ע1';

comment on column yw_gjj_accserial.remark2 is
'��ע2';

comment on column yw_gjj_accserial.remark3 is
'��ע3';

comment on column yw_gjj_accserial.remark4 is
'��ע4';




















drop table yw_gjj_sendserial;

/*==============================================================*/
/* Table: yw_gjj_sendserial                                   */
/*==============================================================*/
create table yw_gjj_sendserial 
(
   sendseqno          VARCHAR(32)          not null,
   sendnode           VARCHAR(6)           not null,
   senddate           VARCHAR(8)              not null,
   sendtime           VARCHAR(6),
   transcode          VARCHAR(7),
   receivenode        VARCHAR(6),
   receivedate        VARCHAR(8),
   receivetime        VARCHAR(6),
   receiveseqno       VARCHAR(32),
   jbjg               VARCHAR(16),
   jbgy               VARCHAR(16),
   txstatus           VARCHAR(1),
   qzlsh              VARCHAR(10)          not null,
   qqdzt              VARCHAR(2),
   respcode           VARCHAR(8),
   respmsg            VARCHAR(254),
   zwrq               VARCHAR(8),
   systime            VARCHAR(6),
   remark             VARCHAR(32),
   remark1            VARCHAR(64),
   remark2            VARCHAR(128),
   remark3            VARCHAR(254),
   remark4            VARCHAR(254),
   constraint PK_SENDSERIAL primary key (sendseqno, sendnode)
);

comment on table yw_gjj_sendserial is
'ס����������������ˮ��';

comment on column yw_gjj_sendserial.sendseqno is
'���ͷ���ˮ��-������ˮ��';

comment on column yw_gjj_sendserial.sendnode is
'���ͷ��ڵ��-�μ����д����';

comment on column yw_gjj_sendserial.senddate is
'���ͷ�����';

comment on column yw_gjj_sendserial.sendtime is
'���ͷ�ʱ��';

comment on column yw_gjj_sendserial.transcode is
'������';

comment on column yw_gjj_sendserial.receivenode is
'���շ��ڵ��-�μ����������Ĵ����';

comment on column yw_gjj_sendserial.receivedate is
'���շ�����';

comment on column yw_gjj_sendserial.receivetime is
'���շ�ʱ��';

comment on column yw_gjj_sendserial.receiveseqno is
'���շ���ˮ��-����Ӧ��ϵͳ������ˮ��';

comment on column yw_gjj_sendserial.jbjg is
'�������';

comment on column yw_gjj_sendserial.jbgy is
'�����Ա';

comment on column yw_gjj_sendserial.txstatus is
'0���ɹ� 1��ʧ�� 9����ʼ
';

comment on column yw_gjj_sendserial.qzlsh is
'ǰ����ˮ��';

comment on column yw_gjj_sendserial.qqdzt is
'20-��ʼ,41-����ʧ��,43-������ʱ,99-�ѷ���';

comment on column yw_gjj_sendserial.zwrq is
'ǰ������';

comment on column yw_gjj_sendserial.systime is
'ǰ��ʱ��';

comment on column yw_gjj_sendserial.remark is
'��ע';

comment on column yw_gjj_sendserial.remark1 is
'����1';

comment on column yw_gjj_sendserial.remark2 is
'��ע2';

comment on column yw_gjj_sendserial.remark3 is
'����3';

comment on column yw_gjj_sendserial.remark4 is
'����4';






















drop table yw_gjj_sign;

/*==============================================================*/
/* Table: yw_gjj_sign                                         */
/*==============================================================*/
create table yw_gjj_sign 
(
   sendnode           VARCHAR(6)           not null,
   receivenode        VARCHAR(6)           not null,
   zwrq               VARCHAR(8),
   receivedate        VARCHAR(8),
   bdcdate            VARCHAR(8),
   dotime             VARCHAR(8),
   keyfilename        VARCHAR(128),
   handkey            VARCHAR(1024),
   bankno             VARCHAR(12),
   status             VARCHAR(1),
   remark             VARCHAR(32),
   remark1            VARCHAR(64),
   remark2            VARCHAR(128),
   remark3            VARCHAR(254),
   remark4            VARCHAR(254),
   constraint PK_SIGN primary key (sendnode, receivenode)
);

comment on table yw_gjj_sign is
'ס����������ǩ��ǩ�˱�';

comment on column yw_gjj_sign.sendnode is
'���ͷ��ڵ�';

comment on column yw_gjj_sign.receivenode is
'���շ��ڵ�';

comment on column yw_gjj_sign.zwrq is
'ǰ����������';

comment on column yw_gjj_sign.receivedate is
'���շ�����';

comment on column yw_gjj_sign.bdcdate is
'�ɼ�ϵͳ����';

comment on column yw_gjj_sign.dotime is
'ǩ��ǩ��ʱ��';

comment on column yw_gjj_sign.keyfilename is
'֤���ļ���';

comment on column yw_gjj_sign.handkey is
'�Ự��Կ����';

comment on column yw_gjj_sign.bankno is
'�����к�';

comment on column yw_gjj_sign.status is
'ǩ��ǩ��״̬';

comment on column yw_gjj_sign.remark is
'��ע';

comment on column yw_gjj_sign.remark1 is
'��ע1';

comment on column yw_gjj_sign.remark2 is
'��ע2';

comment on column yw_gjj_sign.remark3 is
'��ע3';

comment on column yw_gjj_sign.remark4 is
'��ע4';





















drop table yw_gjj_cskz;

/*==============================================================*/
/* Table: yw_gjj_cskz                                         */
/*==============================================================*/
create table yw_gjj_cskz 
(
   csjz               VARCHAR(20)          not null,
   cslx               VARCHAR(1),
   cstj               VARCHAR(8),
   jdm                VARCHAR(80)          not null,
   jdz                VARCHAR(40)          not null,
   remark             VARCHAR(40),
   jzlx               VARCHAR(1),
   whjg               VARCHAR(16),
   whgy               VARCHAR(16),
   whsj               VARCHAR(14),
   constraint PK_CSKZ primary key (csjz)
);

comment on table yw_gjj_cskz is
'ס�����������ʼ������';

comment on column yw_gjj_cskz.csjz is
'������ֵ';

comment on column yw_gjj_cskz.cslx is
'��������';

comment on column yw_gjj_cskz.cstj is
'�������� �������Ϊ����������������ʶ���ΪӦ������Ӧ�ñ�ʶ';

comment on column yw_gjj_cskz.jdm is
'�ڵ���';

comment on column yw_gjj_cskz.jdz is
'�ڵ�ֵ';

comment on column yw_gjj_cskz.remark is
'˵��';

comment on column yw_gjj_cskz.jzlx is
'�������� 0�Զ� 1���Զ�';







drop table yw_gjj_crcapint;

/*==============================================================*/
/* Table: yw_gjj_crcapint                                     */
/*==============================================================*/
create table yw_gjj_crcapint 
(
   sendseqno          VARCHAR(32)          not null,
   txunitno           VARCHAR(15)          not null,
   batchno            VARCHAR(20)          not null,
   fileno             VARCHAR(8)           not null,
   oribatchno         VARCHAR(20)          not null,
   batchtotalnum      INTEGER,
   batchtotalamt      NUMERIC(16,2),
   beiz               VARCHAR(254),
   bkamt              NUMERIC(16,2),
   refamt             NUMERIC(16,2),
   refcapamt          NUMERIC(16,2),
   refintamt          NUMERIC(16,2),
   repenamt           NUMERIC(16,2),
   refineamt          NUMERIC(16,2),
   bankacctno         VARCHAR(32),
   bkrefloancapno     VARCHAR(32),
   bkloancapinacctno  VARCHAR(32),
   bkloanintinacctno  VARCHAR(32),
   loancapcracctno    VARCHAR(32),
   loancapcracctname  VARCHAR(60),
   loancapcracctclass VARCHAR(1),
   loancapcracctbkname VARCHAR(60),
   loancapamt         NUMERIC(16,2),
   loanintcracctno    VARCHAR(32),
   loanintcracctname  VARCHAR(60),
   loanintcracctclass VARCHAR(1),
   loanintcracctbkname VARCHAR(60),
   loanintamt         NUMERIC(16,2),
   loanpencracctno    VARCHAR(32),
   loanpencracctname  VARCHAR(60),
   loanpencracctclass VARCHAR(1),
   loanpencratbkname  VARCHAR(60),
   loanpenamt         NUMERIC(16,2),
   loanfinecracctno   VARCHAR(32),
   loanfinecracctname VARCHAR(60),
   loanfinecracctclass VARCHAR(1),
   loanfinecratbkname VARCHAR(60),
   loanfineamt        NUMERIC(16,2),
   batchsuccnum       INTEGER,
   batchsuccamt       NUMERIC(16,2),
   batchfailnum       INTEGER,
   batchfailamt       NUMERIC(16,2),
   zipfilename        VARCHAR(128),
   unzipfilename      VARCHAR(128),
   trantype           VARCHAR(1),
   dealtype           VARCHAR(1),
   dealstep           VARCHAR(1),
   dealstatus         VARCHAR(5),
   dealinf            VARCHAR(160),
   batchpch           VARCHAR(64),
   querystatus        VARCHAR(1),
   zwrq               VARCHAR(8),
   systime            VARCHAR(6),
   remark             VARCHAR(32),
   remark1            VARCHAR(64),
   remark2            VARCHAR(128),
   remark3            VARCHAR(254),
   remark4            VARCHAR(254),
   constraint PK_CRCAPINT primary key (sendseqno, txunitno)
);

comment on table yw_gjj_crcapint is
'ס������������Ϣ�ֽ�����';

comment on column yw_gjj_crcapint.sendseqno is
'���ͷ���ˮ��';

comment on column yw_gjj_crcapint.txunitno is
'���׻�����';

comment on column yw_gjj_crcapint.batchno is
'���κ�';

comment on column yw_gjj_crcapint.fileno is
'�ļ����';

comment on column yw_gjj_crcapint.oribatchno is
'ԭ����ۿ����κ�';

comment on column yw_gjj_crcapint.batchtotalnum is
'�����ν����ܱ���';

comment on column yw_gjj_crcapint.batchtotalamt is
'�����ν����ܽ��';

comment on column yw_gjj_crcapint.beiz is
'˵��';

comment on column yw_gjj_crcapint.bkamt is
'�����пۿ�����';

comment on column yw_gjj_crcapint.refamt is
'����Ҫ���пۿ�򹫻��𻹴����';

comment on column yw_gjj_crcapint.refcapamt is
'�ǿۿ�𻹿��';

comment on column yw_gjj_crcapint.refintamt is
'�ǿۿ���Ϣ�����';

comment on column yw_gjj_crcapint.repenamt is
'�ǿۿϢ�����';

comment on column yw_gjj_crcapint.refineamt is
'�ǿۿ�ΥԼ�𻹿��';

comment on column yw_gjj_crcapint.bankacctno is
'����ۿ���ʹ�õ��տ������տ��ڲ����ɻ�';

comment on column yw_gjj_crcapint.bkrefloancapno is
'����ί�д�����˺�';

comment on column yw_gjj_crcapint.bkloancapinacctno is
'����ʹ�õĴ������ɻ�';

comment on column yw_gjj_crcapint.bkloanintinacctno is
'����ʹ�õĴ�����Ϣ���ɻ�';

comment on column yw_gjj_crcapint.loancapcracctno is
'���������ķ��ô�����˺�';

comment on column yw_gjj_crcapint.loancapcracctname is
'������˺Ż���';

comment on column yw_gjj_crcapint.loancapcracctclass is
'1����˽
2���Թ�';

comment on column yw_gjj_crcapint.loancapcracctbkname is
'������շ��˻�����';

comment on column yw_gjj_crcapint.loancapamt is
'���пۿ���������';

comment on column yw_gjj_crcapint.loanintcracctno is
'���������ķ��ô�����Ϣ�˺�';

comment on column yw_gjj_crcapint.loanintcracctname is
'������Ϣ�շ�����';

comment on column yw_gjj_crcapint.loanintcracctclass is
'1����˽
2���Թ�';

comment on column yw_gjj_crcapint.loanintcracctbkname is
'������Ϣ�շ��˻�����';

comment on column yw_gjj_crcapint.loanintamt is
'���пۿ������Ϣ������';

comment on column yw_gjj_crcapint.loanpencracctno is
'���������ķ��ô��Ϣ�˺�';

comment on column yw_gjj_crcapint.loanpencracctname is
'���Ϣ�շ�����';

comment on column yw_gjj_crcapint.loanpencracctclass is
'1����˽ 2���Թ�';

comment on column yw_gjj_crcapint.loanpencratbkname is
'���Ϣ�շ��˻�����';

comment on column yw_gjj_crcapint.loanpenamt is
'���пۿ���Ϣ������';

comment on column yw_gjj_crcapint.loanfinecracctno is
'���������ķ��ô���ΥԼ���˺�';

comment on column yw_gjj_crcapint.loanfinecracctname is
'����ΥԼ���շ��˻�����';

comment on column yw_gjj_crcapint.loanfinecracctclass is
'1����˽2���Թ�';

comment on column yw_gjj_crcapint.loanfinecratbkname is
'����ΥԼ���շ��˻�����';

comment on column yw_gjj_crcapint.loanfineamt is
'���пۿ����ΥԼ�����ʱ��д';

comment on column yw_gjj_crcapint.batchsuccnum is
'�ɹ�����';

comment on column yw_gjj_crcapint.batchsuccamt is
'�ɹ����';

comment on column yw_gjj_crcapint.batchfailnum is
'ʧ�ܱ���';

comment on column yw_gjj_crcapint.batchfailamt is
'ʧ�ܽ��';

comment on column yw_gjj_crcapint.zipfilename is
'�����ļ���';

comment on column yw_gjj_crcapint.unzipfilename is
'�����ļ���';

comment on column yw_gjj_crcapint.trantype is
'������� a�����ڴ��� b�����ڴ��� c�����д��� d: ���д��� e: ��ϴ��� f: ��ϴ��� g: ����';

comment on column yw_gjj_crcapint.dealtype is
'��������1:�ļ� 2:��� 3:��֧��';

comment on column yw_gjj_crcapint.dealstep is
'������0-��̬��1-���ף�2-�����У�3-�������';

comment on column yw_gjj_crcapint.dealstatus is
'0-��̬��1-�ɹ���2-ʧ��';

comment on column yw_gjj_crcapint.dealinf is
'����������';

comment on column yw_gjj_crcapint.batchpch is
'���Ĵ������κ�';

comment on column yw_gjj_crcapint.querystatus is
'�����ѯ״̬0-δ��ѯ��1-�Ѳ�ѯ��2-��ѯʧ��';

comment on column yw_gjj_crcapint.zwrq is
'ǰ������';

comment on column yw_gjj_crcapint.systime is
'ǰ��ʱ��';

comment on column yw_gjj_crcapint.remark is
'��ע';

comment on column yw_gjj_crcapint.remark1 is
'��ע1';

comment on column yw_gjj_crcapint.remark2 is
'��ע2';

comment on column yw_gjj_crcapint.remark3 is
'��ע3';

comment on column yw_gjj_crcapint.remark4 is
'��ע4';














drop table yw_gjj_crcapintmx;

/*==============================================================*/
/* Table: yw_gjj_crcapintmx                                   */
/*==============================================================*/
create table yw_gjj_crcapintmx 
(
   sendseqno          VARCHAR(32)          not null,
   txunitno           VARCHAR(15)          not null,
   seqno              VARCHAR(20)          not null,
   batchno            VARCHAR(20)          not null,
   fileno             VARCHAR(5)           not null,
   mxacctno           VARCHAR(32),
   mxserialno         VARCHAR(32),
   idNUMERIC           VARCHAR(18),
   contractno         VARCHAR(32),
   name               VARCHAR(60),
   amt                NUMERIC(16,2),
   capamt             NUMERIC(16,2),
   intamt             NUMERIC(16,2),
   penamt             NUMERIC(16,2),
   fineamt            NUMERIC(16,2),
   bkamt              NUMERIC(16,2),
   refcapamt          NUMERIC(16,2),
   refintamt          NUMERIC(16,2),
   refineamt          NUMERIC(16,2),
   repenamt           NUMERIC(16,2),
   summary            VARCHAR(60),
   dealstatus         VARCHAR(1),
   hostseq            VARCHAR(32),
   hostdate           VARCHAR(8),
   caphostseqno       VARCHAR(32),
   inthostseqno       VARCHAR(32),
   dealcode           VARCHAR(5),
   dealmsg            VARCHAR(160),
   hzno               VARCHAR(32),
   bankex             VARCHAR(254),
   zwrq               VARCHAR(8),
   systime            VARCHAR(6),
   remark             VARCHAR(32),
   remark1            VARCHAR(128),
   remark2            VARCHAR(64),
   remark3            VARCHAR(254),
   remark4            VARCHAR(254),
   constraint PK_CRCAPINTMX primary key (sendseqno, txunitno, seqno)
);

comment on table yw_gjj_crcapintmx is
'ס������������Ϣ�ֽ���ϸ��';

comment on column yw_gjj_crcapintmx.sendseqno is
'���ͷ���ˮ��';

comment on column yw_gjj_crcapintmx.txunitno is
'���׻�����';

comment on column yw_gjj_crcapintmx.seqno is
'���';

comment on column yw_gjj_crcapintmx.batchno is
'���κ�';

comment on column yw_gjj_crcapintmx.fileno is
'�ļ����';

comment on column yw_gjj_crcapintmx.mxacctno is
'ҵ����ϸ�˺�';

comment on column yw_gjj_crcapintmx.mxserialno is
'ҵ����ϸ��ˮ��';

comment on column yw_gjj_crcapintmx.idNUMERIC is
'���֤��';

comment on column yw_gjj_crcapintmx.contractno is
'��ͬ���';

comment on column yw_gjj_crcapintmx.name is
'����';

comment on column yw_gjj_crcapintmx.amt is
'������';

comment on column yw_gjj_crcapintmx.capamt is
'���������';

comment on column yw_gjj_crcapintmx.intamt is
'������Ϣ������';

comment on column yw_gjj_crcapintmx.penamt is
'���Ϣ������';

comment on column yw_gjj_crcapintmx.fineamt is
'����ΥԼ������';

comment on column yw_gjj_crcapintmx.bkamt is
'�ǿۿ�����';

comment on column yw_gjj_crcapintmx.refcapamt is
'�ǿۿ���������';

comment on column yw_gjj_crcapintmx.refintamt is
'�ǿۿ������Ϣ������';

comment on column yw_gjj_crcapintmx.refineamt is
'�ǿۿ����ΥԼ������';

comment on column yw_gjj_crcapintmx.repenamt is
'�ǿۿ���Ϣ������';

comment on column yw_gjj_crcapintmx.summary is
'ժҪ';

comment on column yw_gjj_crcapintmx.dealstatus is
'������0-��̬��1-�ɹ���2ʧ�ܣ�3��ʱ';

comment on column yw_gjj_crcapintmx.hostseq is
'������ˮ';

comment on column yw_gjj_crcapintmx.hostdate is
'��������';

comment on column yw_gjj_crcapintmx.caphostseqno is
'����������ˮ��';

comment on column yw_gjj_crcapintmx.inthostseqno is
'��Ϣ������ˮ��';

comment on column yw_gjj_crcapintmx.dealcode is
'��������00000-�ɹ���99999��ʱ������ʧ��';

comment on column yw_gjj_crcapintmx.dealmsg is
'��������Ϣ';

comment on column yw_gjj_crcapintmx.hzno is
'��ִ���';

comment on column yw_gjj_crcapintmx.bankex is
'������չ';

comment on column yw_gjj_crcapintmx.zwrq is
'ǰ������';

comment on column yw_gjj_crcapintmx.systime is
'ǰ��ʱ��';

comment on column yw_gjj_crcapintmx.remark is
'����';

comment on column yw_gjj_crcapintmx.remark1 is
'����1';

comment on column yw_gjj_crcapintmx.remark2 is
'����2';

comment on column yw_gjj_crcapintmx.remark3 is
'����3';

comment on column yw_gjj_crcapintmx.remark4 is
'����4';
















drop table yw_gjj_fixedbusiness;

/*==============================================================*/
/* Table: yw_gjj_fixedbusiness                                */
/*==============================================================*/
create table yw_gjj_fixedbusiness 
(
   sendseqno          VARCHAR(32)          not null,
   txunitno           VARCHAR(15)          not null,
   jylx               VARCHAR(1),
   currno             VARCHAR(3),
   curriden           VARCHAR(1),
   activedacctno      VARCHAR(32),
   activedacctname    VARCHAR(60),
   activedacctopenbank VARCHAR(60),
   fixedacctno        VARCHAR(32),
   fixedacctname      VARCHAR(60),
   fixedacctopenbank  VARCHAR(60),
   depositperiod      VARCHAR(1),
   interestrate       NUMERIC(8,5),
   amt                NUMERIC(16,2),
   extenddeposittype  VARCHAR(1),
   partexdeacctno     VARCHAR(32),
   beiz               VARCHAR(254),
   bookno             VARCHAR(50),
   booklistno         VARCHAR(50),
   depositbegindate   VARCHAR(8),
   depositenddate     VARCHAR(8),
   depostiamt         NUMERIC(16,2),
   drawamt            NUMERIC(16,2),
   zwrq               VARCHAR(8),
   systime            VARCHAR(6),
   remark             VARCHAR(32),
   remark1            VARCHAR(64),
   remark2            VARCHAR(128),
   remark3            VARCHAR(254),
   remark4            VARCHAR(254),
   constraint PK_FIXEDBUSINESS primary key (sendseqno, txunitno)
);

comment on table yw_gjj_fixedbusiness is
'ס������������ҵ��';

comment on column yw_gjj_fixedbusiness.sendseqno is
'���ͷ���ˮ��';

comment on column yw_gjj_fixedbusiness.txunitno is
'���׻�����';

comment on column yw_gjj_fixedbusiness.jylx is
'�������� 0-����ת���� 1-����֧ȡ 2-����ת�淽ʽ�趨';

comment on column yw_gjj_fixedbusiness.currno is
'����';

comment on column yw_gjj_fixedbusiness.curriden is
'�������';

comment on column yw_gjj_fixedbusiness.activedacctno is
'�����˺�';

comment on column yw_gjj_fixedbusiness.activedacctname is
'���ڻ���';

comment on column yw_gjj_fixedbusiness.activedacctopenbank is
'�����˻�����������';

comment on column yw_gjj_fixedbusiness.fixedacctno is
'�����˺�';

comment on column yw_gjj_fixedbusiness.fixedacctname is
'���ڻ���';

comment on column yw_gjj_fixedbusiness.fixedacctopenbank is
'�����˻�����������';

comment on column yw_gjj_fixedbusiness.depositperiod is
'���� 0�������� 1������ 2��һ�� 3������ 4������ 5������ 
';

comment on column yw_gjj_fixedbusiness.interestrate is
'���й�������';

comment on column yw_gjj_fixedbusiness.amt is
'���׽��';

comment on column yw_gjj_fixedbusiness.extenddeposittype is
'ת�淽ʽ
0������+��Ϣ�Զ�ת�� 
1�����Զ�ת�� 
2�������Զ�ת�� 
';

comment on column yw_gjj_fixedbusiness.partexdeacctno is
'��������';

comment on column yw_gjj_fixedbusiness.beiz is
'��Ϣ���˺�';

comment on column yw_gjj_fixedbusiness.bookno is
'��� �ʺ�Ϊһ��ͨʱ,����';

comment on column yw_gjj_fixedbusiness.booklistno is
'�ʺ� �ʺ�Ϊһ��ͨʱ,����';

comment on column yw_gjj_fixedbusiness.depositbegindate is
'��������';

comment on column yw_gjj_fixedbusiness.depositenddate is
'��������';

comment on column yw_gjj_fixedbusiness.depostiamt is
'ʵ�ʽ��';

comment on column yw_gjj_fixedbusiness.drawamt is
'֧ȡ���';

comment on column yw_gjj_fixedbusiness.zwrq is
'ǰ������';

comment on column yw_gjj_fixedbusiness.systime is
'ǰ��ʱ��';

comment on column yw_gjj_fixedbusiness.remark is
'����';

comment on column yw_gjj_fixedbusiness.remark1 is
'����1';

comment on column yw_gjj_fixedbusiness.remark2 is
'����2';

comment on column yw_gjj_fixedbusiness.remark3 is
'����3';

comment on column yw_gjj_fixedbusiness.remark4 is
'����4';










drop table yw_gjj_noticebusiness;

/*==============================================================*/
/* Table: yw_gjj_noticebusiness                               */
/*==============================================================*/
create table yw_gjj_noticebusiness 
(
   sendseqno          VARCHAR(32)          not null,
   txunitno           VARCHAR(15)          not null,
   jylx               VARCHAR(1),
   currno             VARCHAR(3),
   curriden           VARCHAR(1),
   fixedacctno        VARCHAR(32),
   fixedacctname      VARCHAR(60),
   fixedacctopenbank  VARCHAR(60),
   noticesetserialno  VARCHAR(20),
   bookno             VARCHAR(50),
   booklistno         VARCHAR(50),
   noticeflag         VARCHAR(1),
   noticedrawsetdate  VARCHAR(8),
   noticedrawdate     VARCHAR(8),
   drawamt            NUMERIC(16,2),
   balance            NUMERIC(16,2),
   noticedepositamt   NUMERIC(16,2),
   activedacctno      VARCHAR(32),
   activedacctname    VARCHAR(60),
   activedacctopenbank VARCHAR(60),
   depositperiod      VARCHAR(1),
   acctno             VARCHAR(32),
   drawtype           VARCHAR(1),
   acctname           VARCHAR(60),
   noticedrawamt      NUMERIC(16,2),
   depositbegindate   VARCHAR(8),
   zwrq               VARCHAR(8),
   systime            VARCHAR(6),
   remark             VARCHAR(32),
   remark1            VARCHAR(64),
   remark2            VARCHAR(128),
   remark3            VARCHAR(254),
   remark4            VARCHAR(254),
   constraint PK_NOTICEBUSINESS primary key (sendseqno, txunitno)
);

comment on table yw_gjj_noticebusiness is
'ס����������֪ͨ�����ҵ��';

comment on column yw_gjj_noticebusiness.sendseqno is
'���ͷ���ˮ��';

comment on column yw_gjj_noticebusiness.txunitno is
'���׻�����';

comment on column yw_gjj_noticebusiness.jylx is
'�������� 0-����ת֪ͨ��� 1-֪ͨ���֧ȡ 2-֪ͨ���֧ȡ�趨 3-֪ͨ���֧ȡ֪ͨȡ��';

comment on column yw_gjj_noticebusiness.currno is
'����';

comment on column yw_gjj_noticebusiness.curriden is
'�������';

comment on column yw_gjj_noticebusiness.fixedacctno is
'֪ͨ����˺�';

comment on column yw_gjj_noticebusiness.fixedacctname is
'֪ͨ�˻�����';

comment on column yw_gjj_noticebusiness.fixedacctopenbank is
'֪ͨ�˻�����������';

comment on column yw_gjj_noticebusiness.noticesetserialno is
'֪ͨ�趨���';

comment on column yw_gjj_noticebusiness.bookno is
'��� �ʺ�Ϊһ��ͨʱ,����';

comment on column yw_gjj_noticebusiness.booklistno is
'�ʺ� �ʺ�Ϊһ��ͨʱ,����';

comment on column yw_gjj_noticebusiness.noticeflag is
'֪ͨ��־0������ 1��֪ͨ�ѹ���';

comment on column yw_gjj_noticebusiness.noticedrawsetdate is
'֪ͨ�趨����';

comment on column yw_gjj_noticebusiness.noticedrawdate is
'֪֧ͨȡ����';

comment on column yw_gjj_noticebusiness.drawamt is
'֧ȡ���';

comment on column yw_gjj_noticebusiness.balance is
'�浥���';

comment on column yw_gjj_noticebusiness.noticedepositamt is
'֪ͨ�����';

comment on column yw_gjj_noticebusiness.activedacctno is
'�����˺�';

comment on column yw_gjj_noticebusiness.activedacctname is
'���ڻ���';

comment on column yw_gjj_noticebusiness.activedacctopenbank is
'�����˻�����������';

comment on column yw_gjj_noticebusiness.depositperiod is
'���� 6-1�� 7-7�� 

';

comment on column yw_gjj_noticebusiness.acctno is
'����˺�';

comment on column yw_gjj_noticebusiness.drawtype is
'֧ȡ��ʽ 0����֧ȡ֪֧ͨȡ 1��ֱ��֧ȡ';

comment on column yw_gjj_noticebusiness.acctname is
'����˻�����';

comment on column yw_gjj_noticebusiness.noticedrawamt is
'֪֧ͨȡ���';

comment on column yw_gjj_noticebusiness.depositbegindate is
'��������';

comment on column yw_gjj_noticebusiness.zwrq is
'ǰ������';

comment on column yw_gjj_noticebusiness.systime is
'ǰ��ʱ��';

comment on column yw_gjj_noticebusiness.remark is
'����';

comment on column yw_gjj_noticebusiness.remark1 is
'����1';

comment on column yw_gjj_noticebusiness.remark2 is
'����2';

comment on column yw_gjj_noticebusiness.remark3 is
'����3';

comment on column yw_gjj_noticebusiness.remark4 is
'����4';
