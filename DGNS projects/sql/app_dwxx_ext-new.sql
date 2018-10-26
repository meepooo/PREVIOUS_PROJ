drop table app_dwxx_ext;
--==============================================================
-- Table: APP_DWXX_EXT
--==============================================================
create table APP_DWXX_EXT
(
   DWBH                 CHAR(16)            not null,
   SXFBZ                CHAR(1),
   SXFGSBZ              CHAR(1),
   SXFKHFS              CHAR(1),
   SXFZHLX              CHAR(1),
   SXFFKZH              CHAR(32),
   SXFFKZHMC            VARCHAR(100),
   SXFJSFS              CHAR(1),
   SXFJSCS              CHAR(10),
   SXFJEXX              NUMERIC(7,2),
   SXFJESX              NUMERIC(7,2),
   KHQYFS               CHAR(1),
   KKFS                 CHAR(1),
   TZBZ                 CHAR(1),
   TZED                 NUMERIC(15,2),
   TZDFZH               CHAR(32),
   YJBZ                 CHAR(1),
   YEYBBL               NUMERIC(7,2),
   JCHMBZ               CHAR(1),
   YQBZ                 CHAR(1),
   YQMY                 VARCHAR(128),
   FYYWLX1              VARCHAR(3),
   FYRZZH1              VARCHAR(32),
   FYZHLX1              VARCHAR(1),
   FYYWLX2              VARCHAR(3),
   FYRZZH2              VARCHAR(32),
   FYZHLX2              VARCHAR(1),
   FYYWLX3              VARCHAR(3),
   FYRZZH3              VARCHAR(32),
   FYZHLX3              VARCHAR(1),
   FYYWLX4              VARCHAR(3),
   FYRZZH4              VARCHAR(32),
   FYZHLX4              VARCHAR(1),
   FYYWLX5              VARCHAR(3),
   FYRZZH5              VARCHAR(32),
   FYZHLX5              VARCHAR(1),
   EXTFLD1              VARCHAR(80),
   EXTFLD2              VARCHAR(80),
   EXTFLD3              VARCHAR(80),
   EXTFLD4              VARCHAR(80),
   EXTFLD5              VARCHAR(80),
   EXTFLD6              VARCHAR(160),
   QYLX                 CHAR(1),
   DFFS                 CHAR(1),
   QSBZ                 CHAR(1),
   BYFLAG1              CHAR(2),
   BYFLAG2              CHAR(3),
   BYFLAG3              CHAR(4),
   BYZD1                CHAR(10),
   BYZD2                CHAR(20),
   BYZD3                CHAR(30),
   BYZD4                CHAR(50),
   BYZD5                CHAR(80),
   BYZD6                CHAR(100),
   constraint P_K_APP_DWXX_EXT_1 primary key (DWBH)
);

comment on table APP_DWXX_EXT is
'��λ��Ϣ��չ��';

comment on column APP_DWXX_EXT.DWBH is
'��λ���';

comment on column APP_DWXX_EXT.SXFBZ is
'�����ѱ�־ 0-��ȡ��1-����';

comment on column APP_DWXX_EXT.SXFGSBZ is
'�����ѹ�����־ 0-��λ��1-������2-����';

comment on column APP_DWXX_EXT.SXFKHFS is
'�����ѿۻ���ʽ 0-�Զ���1-�ֽ�';

comment on column APP_DWXX_EXT.SXFZHLX is
'�����Ѹ����˺�����';

comment on column APP_DWXX_EXT.SXFFKZH is
'�����Ѹ����˺�';

comment on column APP_DWXX_EXT.SXFFKZHMC is
'�����Ѹ����˺�����';

comment on column APP_DWXX_EXT.SXFJSFS is
'�����Ѽ��㷽ʽ 0-������ 1-������';

comment on column APP_DWXX_EXT.SXFJSCS is
'�����Ѽ������';

comment on column APP_DWXX_EXT.SXFJEXX is
'�����ѽ������';

comment on column APP_DWXX_EXT.SXFJESX is
'�����ѽ������';

comment on column APP_DWXX_EXT.KHQYFS is
'�ͻ�ǩԼ��ʽ 0-���� 1-ί�е�λ 2-���л�ί�е�λ';

comment on column APP_DWXX_EXT.KKFS is
'���ֿۿ��־';

comment on column APP_DWXX_EXT.TZBZ is
'͸֧��־';

comment on column APP_DWXX_EXT.TZED is
'͸֧���';

comment on column APP_DWXX_EXT.TZDFZH is
'�渶�˺�';

comment on column APP_DWXX_EXT.YJBZ is
'Ԥ����־';

comment on column APP_DWXX_EXT.YEYBBL is
'���Ԥ������';

comment on column APP_DWXX_EXT.JCHMBZ is
'��黧����־';

comment on column APP_DWXX_EXT.YQBZ is
'��ǩ��־';

comment on column APP_DWXX_EXT.YQMY is
'��ǩ��Կ';

comment on column APP_DWXX_EXT.FYYWLX1 is
'����1ҵ������';

comment on column APP_DWXX_EXT.FYRZZH1 is
'����1�����˺�';

comment on column APP_DWXX_EXT.FYZHLX1 is
'����1�˺�����';

comment on column APP_DWXX_EXT.FYYWLX2 is
'����2ҵ������';

comment on column APP_DWXX_EXT.FYRZZH2 is
'����2�����˺�';

comment on column APP_DWXX_EXT.FYZHLX2 is
'����2�˺�����';

comment on column APP_DWXX_EXT.FYYWLX3 is
'����3ҵ������';

comment on column APP_DWXX_EXT.FYRZZH3 is
'����3�����˺�';

comment on column APP_DWXX_EXT.FYZHLX3 is
'����3�˺�����';

comment on column APP_DWXX_EXT.FYYWLX4 is
'����4ҵ������';

comment on column APP_DWXX_EXT.FYRZZH4 is
'����4�����˺�';

comment on column APP_DWXX_EXT.FYZHLX4 is
'����4�˺�����';

comment on column APP_DWXX_EXT.FYYWLX5 is
'����5ҵ������';

comment on column APP_DWXX_EXT.FYRZZH5 is
'����5�����˺�';

comment on column APP_DWXX_EXT.FYZHLX5 is
'����5�˺�����';

comment on column APP_DWXX_EXT.EXTFLD1 is
'��չ�ֶ�1';

comment on column APP_DWXX_EXT.EXTFLD2 is
'��չ�ֶ�2';

comment on column APP_DWXX_EXT.EXTFLD3 is
'��չ�ֶ�3';

comment on column APP_DWXX_EXT.EXTFLD4 is
'��չ�ֶ�4';

comment on column APP_DWXX_EXT.EXTFLD5 is
'��չ�ֶ�5';

comment on column APP_DWXX_EXT.EXTFLD6 is
'��չ�ֶ�6';

comment on column APP_DWXX_EXT.QYLX is
'��ҵ����';

comment on column APP_DWXX_EXT.DFFS is
'������ʽ';

comment on column APP_DWXX_EXT.QSBZ is
'���㷽ʽ';
