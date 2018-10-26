drop table ywty_drls cascade constraints
/


/*==============================================================*/
/* Table: ywty_drls                                             */
/*==============================================================*/


create table ywty_drls  (
   zwrq                 char(8)                          not null,
   zhqzlsh              integer                          not null,
   zxlsh                char(16),
   dsfzwrq              char(8),
   dsflsh               char(18),
   jygzh                char(12),
   zhqzlsh2             integer,
   sqm                  char(6),
   sqczy                char(8),
   sjjgbh               char(16),
   jgbh                 char(16)                         not null,
   nbjgbs               char(24),
   wtjgbh               char(16),
   wtnbjgbs             char(24),
   czyh                 char(8)                          not null,
   jdbh                 char(16),
   jyqd                 char(12),
   jyrq                 char(8)                          not null,
   jysj                 char(6)                          not null,
   jydm                 char(50),
   jymc                 char(50),
   ywdm                 char(10),
   xmdh                 char(10),
   khmc                 char(80),
   jyzh                 char(32),
   zhzl                 char(2),
   jyzh2                char(32),
   zhzl2                char(2),
   zhjg2                char(32),
   khh                  char(20),
   yhh                  char(32),
   bzh                  char(2),
   jyje                 number(16,2),
   sxf                  number(16,2),
   gbf                  number(16,2),
   znj                  number(16,2),
   jyzt                 char(1)                          not null,
   xym                  char(8),
   xyxx                 char(60),
   jyfs                 char(1),
   jdbz                 char(1),
   gdbz                 char(1),
   jyzl                 char(1),
   jzbz                 char(1),
   qsbz                 char(1),
   kzbz                 char(8),
   wbzwbs               char(20),
   trans_time           integer,
   byzd                 char(128),
   constraint pk_ywty_drls primary key (zwrq, zhqzlsh)
)
/

