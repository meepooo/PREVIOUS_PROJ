drop table ywty_acctycls;
create table ywty_acctycls
(
CPDM    varchar(16)  ,
YWBH    varchar(16)  ,
PTRQ    varchar(8)   ,
PTLS    varchar(52)   ,
PTSJ    varchar(6)   ,
YPTLS   varchar(52)  ,
TLSQ    varchar(32)  ,
CZSQ    varchar(32)  ,
JYJG    varchar(16)  ,
JYGY    varchar(16)  ,
QDBS    varchar(3)   ,
ZDSBBH  varchar(8)   ,
YYBS    varchar(8)   ,
JYDM    varchar(8)   ,
DWBH    varchar(32)  ,
WKDT    varchar (8)  ,
WKTM    varchar (6)  ,
OPDT    varchar (8)  ,
SRTM    varchar (6)  ,
JDBZ    varchar(1)   ,
ZHLX    varchar(2)   ,
YHZH    varchar(32)  ,
DFZH    varchar(32)  ,
JYJE    decimal(16,2),
SXF     decimal(16,2),
JYZT    varchar(1)   ,
REMARK1 VARCHAR(80)  ,
REMARK2 VARCHAR(80)  ,
REMARK3 VARCHAR(80)  ,
REMARK4 VARCHAR(80)  ,
REMARK5 VARCHAR(80)  
);

comment on table  ywty_acctycls  is 'ywty_acctycls' ;
comment on column ywty_acctycls.CPDM    is'��Ʒ����' ;         
comment on column ywty_acctycls.YWBH    is'ҵ����' ;         
comment on column ywty_acctycls.PTRQ    is'ƽ̨���� YYYYMMDD' ;
comment on column ywty_acctycls.PTLS    is'ƽ̨��ˮ��' ;       
comment on column ywty_acctycls.PTSJ    is'ƽ̨ʱ�� HHMMSS' ;  
comment on column ywty_acctycls.YPTLS   is'ԭƽ̨��ˮ��' ;     
comment on column ywty_acctycls.TLSQ    is'������ˮ��' ;       
comment on column ywty_acctycls.CZSQ    is'���ĳ�����ˮ��' ;   
comment on column ywty_acctycls.JYJG    is'���׻���' ;         
comment on column ywty_acctycls.JYGY    is'���׹�Ա' ;         
comment on column ywty_acctycls.QDBS    is'������ʶ' ;         
comment on column ywty_acctycls.ZDSBBH  is'�ն��豸���' ;     
comment on column ywty_acctycls.YYBS    is'Ӧ�ñ�ʶ' ;         
comment on column ywty_acctycls.JYDM    is'���״���' ;         
comment on column ywty_acctycls.DWBH    is'�û�������ֻ���' ; 
comment on column ywty_acctycls.WKDT    is'�Ǽ�����' ;         
comment on column ywty_acctycls.WKTM    is'�Ǽ�ʱ��' ;         
comment on column ywty_acctycls.OPDT    is'ʵ��ִ������' ;     
comment on column ywty_acctycls.SRTM    is'ʵ��ִ��ʱ��' ;     
comment on column ywty_acctycls.JDBZ    is'�����־�������ֵ�KEY=K_JDBZ C ��  D ��' ;
comment on column ywty_acctycls.ZHLX    is'�ʻ����ͼ������ֵ�KEY=K_ZHLX
01 �Թ�����
02 ��˽����
03 �Թ�����
04 ��˽����
05 ��֤��
06 ����
07 �ڲ���
08 ������' ;
comment on column ywty_acctycls.YHZH    is'�����ʺ�' ;
comment on column ywty_acctycls.DFZH    is'�Է��ʺ�' ;
comment on column ywty_acctycls.JYJE    is'���׽��' ;
comment on column ywty_acctycls.SXF     is'������' ;  
comment on column ywty_acctycls.JYZT    is'0 �Ǽ�
1 ����ɹ�
2 ����ʧ��' ;
comment on column ywty_acctycls.REMARK1 is'��չ1' ;
comment on column ywty_acctycls.REMARK2 is'��չ2' ;
comment on column ywty_acctycls.REMARK3 is'��չ3' ;
comment on column ywty_acctycls.REMARK4 is'��չ4' ;
comment on column ywty_acctycls.REMARK5 is'��չ4' ;
