
--t_tran
delete from t_tran where version='V4.1.dgyxt';

--t_sub_tran
delete from t_sub_tran where version='V4.1.dgyxt';

--t_menu
delete from t_menu where version='V4.1.dgyxt';
insert into t_menu (menu_id,above_menu_id,menu_deep,menu_name,menu_desc,is_run_menu,is_enable,version,order_id,menu_type,system_id) values('dgyxttable','/',2,'院线通报表','院线通报表','0','1','V4.1.dgyxt','900080000000','0','agent');
insert into t_menu (menu_id,above_menu_id,menu_deep,menu_name,menu_desc,is_run_menu,tran_code,is_enable,version,report_id,order_id,menu_type,system_id) values('dgyxttable001','dgyxttable',3,'院线通业务不同渠道业务统计表','院线通业务不同渠道业务统计表','1','report','1','V4.1.dgyxt','hs_dgyxttable01','900081000000','0','agent');
insert into t_menu (menu_id,above_menu_id,menu_deep,menu_name,menu_desc,is_run_menu,tran_code,is_enable,version,report_id,order_id,menu_type,system_id) values('dgyxttable02','dgyxttable',3,'院线通影院或地区业务统计表','院线通影院或地区业务统计表','1','report','1','V4.1.dgyxt','hs_dgyxttable02','900082000000','0','agent');
insert into t_menu (menu_id,above_menu_id,menu_deep,menu_name,menu_desc,is_run_menu,tran_code,is_enable,version,report_id,order_id,menu_type,system_id) values('dgyxttable03','dgyxttable',3,'院线通客户业务流水','院线通客户业务流水','1','report','1','V4.1.dgyxt','hs_dgyxttable03','900083000000','0','agent');
insert into t_menu (menu_id,above_menu_id,menu_deep,menu_name,menu_desc,is_run_menu,tran_code,is_enable,version,report_id,order_id,menu_type,system_id) values('dgyxttable04','dgyxttable',3,'院线通业务流水','院线通业务流水','1','report','1','V4.1.dgyxt','hs_dgyxttable04','900084000000','0','agent');

--t_sendinfo
delete from t_sendinfo where version='V4.1.dgyxt';

--t_send_cond
delete from t_send_cond where version='V4.1.dgyxt';

--t_send_return
delete from t_send_return where version='V4.1.dgyxt';


--t_report
delete from t_report where version='V4.1.dgyxt';
insert into t_report (report_id,report_name,report_type,report_path,max_number,version) values('hs_dgyxttable01','院线通业务不同渠道业务统计表','1','hs_dgyxttable01.jasper',5000,'V4.1.dgyxt');
insert into t_report (report_id,report_name,report_type,report_path,max_number,version) values('hs_dgyxttable02','院线通影院或地区业务统计表','1','hs_dgyxttable02.jasper',5000,'V4.1.dgyxt');
insert into t_report (report_id,report_name,report_type,report_path,max_number,version) values('hs_dgyxttable03','院线通客户业务流水','1','hs_dgyxttable03.jasper',5000,'V4.1.dgyxt');
insert into t_report (report_id,report_name,report_type,report_path,max_number,version) values('hs_dgyxttable04','院线通业务流水','1','hs_dgyxttable04.jasper',5000,'V4.1.dgyxt');

--t_report_cond
delete from t_report_cond where version='V4.1.dgyxt';
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('qa','hs_dgyxttable01','起始日期','3','1',1,'V4.1.dgyxt','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('qb','hs_dgyxttable01','结束日期','3','1',2,'V4.1.dgyxt','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,cond_value,version,bak1) values('qc','hs_dgyxttable01','渠道','9','0',3,'APP_QDXX:qdbs:QDSM::true:false','V4.1.dgyxt','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,cond_value,version,bak1) values('qd','hs_dgyxttable01','业务类型','2','0',4,'yxt_ywlx','V4.1.dgyxt','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('qa','hs_dgyxttable02','起始日期','3','0',1,'V4.1.dgyxt','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('qb','hs_dgyxttable02','结束日期','3','1',2,'V4.1.dgyxt','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('qc','hs_dgyxttable02','地区','1','0',3,'V4.1.dgyxt','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('qd','hs_dgyxttable02','影院','1','0',4,'V4.1.dgyxt','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('qe','hs_dgyxttable02','影片','1','0',5,'V4.1.dgyxt','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,cond_value,version,bak1) values('qf','hs_dgyxttable02','业务类型','2','0',6,'yxt_ywlx','V4.1.dgyxt','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('qa','hs_dgyxttable03','起始日期','3','1',1,'V4.1.dgyxt','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('qb','hs_dgyxttable03','结束日期','3','1',2,'V4.1.dgyxt','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('qc','hs_dgyxttable03','客户名称','1','0',3,'V4.1.dgyxt','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('qd','hs_dgyxttable03','账号/卡号','1','0',4,'V4.1.dgyxt','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('qe','hs_dgyxttable03','手机号','1','0',5,'V4.1.dgyxt','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('qa','hs_dgyxttable04','起始日期','3','1',1,'V4.1.dgyxt','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('qb','hs_dgyxttable04','结束日期','3','1',2,'V4.1.dgyxt','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,cond_value,version,bak1) values('qc','hs_dgyxttable04','支付方式','2','0',3,'zflx','V4.1.dgyxt','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,cond_value,version,bak1) values('qd','hs_dgyxttable04','业务状态','2','0',4,'yxt_state','V4.1.dgyxt','1');
