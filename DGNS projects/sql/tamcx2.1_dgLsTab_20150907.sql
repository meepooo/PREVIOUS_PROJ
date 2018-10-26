

--t_tran
delete from t_tran where version='V4.1.dgtab';
insert into t_tran (tran_code,tran_name,tran_type,tran_class,version) values('agentLsyyt','莞医通代收付流水查询','1','com.hundsun.agent.web.dsf.ctl.AgentLsYytCtl','V4.1.dgtab');

--t_sub_tran
delete from t_sub_tran where version='V4.1.dgtab';
insert into t_sub_tran (tran_code,sub_tran_code,sub_tran_name,repage,sub_tran_desc,version) values('agentLsyyt','def','查询','app/agent/dsf/agenttlsyyt.jsp','默认','V4.1.dgtab');
insert into t_sub_tran (tran_code,sub_tran_code,sub_tran_name,repage,sub_tran_desc,version) values('agentLsyyt','list','获得数据','about:blank','获得数据','V4.1.dgtab');
insert into t_sub_tran (tran_code,sub_tran_code,sub_tran_name,repage,sub_tran_desc,version) values('agentLsyyt','send','执行交易','about:blank','执行交易','V4.1.dgtab');

--t_menu
delete from t_menu where version='V4.1.dgtab';
insert into t_menu (menu_id,above_menu_id,menu_deep,menu_name,menu_desc,is_run_menu,tran_code,is_enable,version,order_id,menu_type,system_id,bak1) values('dgtable005','dgtable',3,'代收付流水查询','代收付流水查询','1','agentLsyyt','1','V4.1.dgtab','90009500000','0','agent','ywbh=003000110000');
insert into t_menu (menu_id,above_menu_id,menu_deep,menu_name,menu_desc,is_run_menu,tran_code,is_enable,version,report_id,order_id,menu_type,system_id) values('dgtable003','dgtable',3,'莞医通客户业务流水','莞医通客户业务流水','1','report','1','V4.1.dgtab','hs_dgyyttable03','90009300000','0','agent');
insert into t_menu (menu_id,above_menu_id,menu_deep,menu_name,menu_desc,is_run_menu,tran_code,is_enable,version,report_id,order_id,menu_type,system_id) values('dgtable004','dgtable',3,'莞医通业务流水','莞医通业务流水','1','report','1','V4.1.dgtab','hs_dgyyttable04','90009400000','0','agent');
insert into t_menu (menu_id,above_menu_id,menu_deep,menu_name,menu_desc,is_run_menu,is_enable,version,order_id,menu_type,system_id) values('dgtable','/',2,'莞医通报表','莞医通报表','0','1','V4.1.dgtab','900090000000','0','agent');
insert into t_menu (menu_id,above_menu_id,menu_deep,menu_name,menu_desc,is_run_menu,tran_code,is_enable,version,report_id,order_id,menu_type,system_id) values('dgtable001','dgtable',3,'莞医通业务不同渠道业务统计表','莞医通业务不同渠道业务统计表','1','report','1','V4.1.dgtab','hs_dgyyttable01','900091000000','0','agent');
insert into t_menu (menu_id,above_menu_id,menu_deep,menu_name,menu_desc,is_run_menu,tran_code,is_enable,version,report_id,order_id,menu_type,system_id) values('dgtable002','dgtable',3,'莞医通地区或医院业务统计表','莞医通地区或医院业务统计表','1','report','1','V4.1.dgtab','hs_dgyyttable02','90009200000','0','agent');

--t_sendinfo
delete from t_sendinfo where version='V4.1.dgtab';

--t_send_cond
delete from t_send_cond where version='V4.1.dgtab';

--t_send_return
delete from t_send_return where version='V4.1.dgtab';



--t_report
delete from t_report where version='V4.1.dgtab';
insert into t_report (report_id,report_name,report_type,report_path,max_number,version) values('hs_dgyyttable01','莞医通业务不同渠道业务统计表','1','hs_dgyyttable01.jasper',5000,'V4.1.dgtab');
insert into t_report (report_id,report_name,report_type,report_path,max_number,version) values('hs_dgyyttable03','莞医通客户业务流水','1','hs_dgyyttable03.jasper',5000,'V4.1.dgtab');
insert into t_report (report_id,report_name,report_type,report_path,max_number,version) values('hs_dgyyttable04','莞医通业务流水','1','hs_dgyyttable04.jasper',5000,'V4.1.dgtab');
insert into t_report (report_id,report_name,report_type,report_path,max_number,version) values('hs_dgyyttable02','莞医通地区或医院业务量统计','1','hs_dgyyttable02.jasper',5000,'V4.1.dgtab');

--t_report_cond
delete from t_report_cond where version='V4.1.dgtab';
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,cond_value,version,bak1) values('q3','hs_dgyyttable01','渠道','9','0',3,'APP_QDXX:qdbs:QDSM::true:false','V4.1.dgtab','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,cond_value,version,bak1) values('q4','hs_dgyyttable01','业务类型','2','0',4,'yyt_ywlx','V4.1.dgtab','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('qa','hs_dgyyttable03','起始日期','3','1',1,'V4.1.dgtab','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('qb','hs_dgyyttable03','结束日期','3','1',2,'V4.1.dgtab','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('qc','hs_dgyyttable03','客户名称','1','0',3,'V4.1.dgtab','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('qd','hs_dgyyttable03','账号/卡号','1','0',4,'V4.1.dgtab','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('q1','hs_dgyyttable01','起始日期','3','1',1,'V4.1.dgtab','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('q2','hs_dgyyttable01','结束日期','3','1',2,'V4.1.dgtab','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('qe','hs_dgyyttable03','手机号','1','0',5,'V4.1.dgtab','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('qa','hs_dgyyttable04','起始日期','3','1',1,'V4.1.dgtab','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('qb','hs_dgyyttable04','结束日期','3','1',2,'V4.1.dgtab','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,cond_value,version,bak1) values('qc','hs_dgyyttable04','支付方式','2','0',3,'zflx','V4.1.dgtab','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,cond_value,version,bak1) values('qd','hs_dgyyttable04','业务状态','2','0',4,'yyt_state','V4.1.dgtab','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('q1','hs_dgyyttable02','起始日期','3','1',1,'V4.1.dgtab','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('q2','hs_dgyyttable02','结束日期','3','1',2,'V4.1.dgtab','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,cond_value,version,bak1) values('q3','hs_dgyyttable02','地区','9','0',3,'yyt_citycode:area_id:area_name:area_level=^3^:true:false','V4.1.dgtab','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('q4','hs_dgyyttable02','医院','1','0',4,'V4.1.dgtab','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,cond_value,version,bak1) values('q5','hs_dgyyttable02','科室','9','0',5,'zjyw_ordersum:unit_id2:unit_name3::true:false','V4.1.dgtab','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,cond_value,version,bak1) values('q6','hs_dgyyttable02','业务类型','2','0',6,'yyt_ywlx','V4.1.dgtab','1');




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
insert into t_menu (menu_id,above_menu_id,menu_deep,menu_name,menu_desc,is_run_menu,tran_code,is_enable,version,order_id,menu_type,system_id,bak1) values('dgyxttable05','dgyxttable',3,'代收付流水查询','代收付流水查询','1','agentLsyyt','1','V4.1.dgyxt','900085000000','0','agent','ywbh=003000210000');

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
