--t_tran
delete from t_tran where version='V4.1.dgyxt';
delete from t_tran where version='V4.1.dgtab';
insert into t_tran (tran_code,tran_name,tran_type,tran_class,version) values('agentYxtRgcz','院线通人工冲正','1','com.hundsun.agent.web.dsf.ctl.AgentYxtRgczCtl','V4.1.dgtab');
insert into t_tran (tran_code,tran_name,tran_type,tran_class,version) values('agentYytRgcz','莞医通人工冲正','1','com.hundsun.agent.web.dsf.ctl.AgentYytRgczCtl','V4.1.dgtab');
insert into t_tran (tran_code,tran_name,tran_type,tran_class,version) values('agentLsyyt','莞医通代收付流水查询','1','com.hundsun.agent.web.dsf.ctl.AgentLsYytCtl','V4.1.dgtab');

--t_sub_tran
delete from t_sub_tran where version='V4.1.dgyxt';
delete from t_sub_tran where version='V4.1.dgtab';
insert into t_sub_tran (tran_code,sub_tran_code,sub_tran_name,repage,sub_tran_desc,version) values('agentYytRgcz','send','核心冲正','about:blank','核心冲正','V4.1.dgtab');
insert into t_sub_tran (tran_code,sub_tran_code,sub_tran_name,repage,sub_tran_desc,version) values('agentLsyyt','send','执行交易','about:blank','执行交易','V4.1.dgtab');
insert into t_sub_tran (tran_code,sub_tran_code,sub_tran_name,repage,sub_tran_desc,version) values('agentLsyyt','def','查询','app/agent/dsf/agenttlsyyt.jsp','默认','V4.1.dgtab');
insert into t_sub_tran (tran_code,sub_tran_code,sub_tran_name,repage,sub_tran_desc,version) values('agentLsyyt','list','获得数据','about:blank','获得数据','V4.1.dgtab');
insert into t_sub_tran (tran_code,sub_tran_code,sub_tran_name,repage,sub_tran_desc,version) values('agentYytRgcz','def','默认','app/agent/dsf/agent_yyt_rgcz.jsp','默认','V4.1.dgtab');
insert into t_sub_tran (tran_code,sub_tran_code,sub_tran_name,repage,sub_tran_desc,version) values('agentYytRgcz','list','查看','about:blank','查看','V4.1.dgtab');
insert into t_sub_tran (tran_code,sub_tran_code,sub_tran_name,repage,sub_tran_desc,version) values('agentYxtRgcz','def','默认','app/agent/dsf/agent_yxt_rgcz.jsp','默认','V4.1.dgtab');
insert into t_sub_tran (tran_code,sub_tran_code,sub_tran_name,repage,sub_tran_desc,version) values('agentYxtRgcz','list','查看','about:blank','查看','V4.1.dgtab');
insert into t_sub_tran (tran_code,sub_tran_code,sub_tran_name,repage,sub_tran_desc,version) values('agentYxtRgcz','send','核心冲正','about:blank','核心冲正','V4.1.dgtab');

--t_menu
delete from t_menu where version='V4.1.dgyxt';
delete from t_menu where version='V4.1.dgtab';
insert into t_menu (menu_id,above_menu_id,menu_deep,menu_name,menu_desc,is_run_menu,tran_code,is_enable,version,order_id,menu_type,system_id,bak1) values('dgtable005','dgtable',3,'代收付流水查询','代收付流水查询','1','agentLsyyt','1','V4.1.dgtab','90009500000','0','agent','ywbh=003000110000');
insert into t_menu (menu_id,above_menu_id,menu_deep,menu_name,menu_desc,is_run_menu,tran_code,is_enable,version,report_id,order_id,menu_type,system_id) values('dgtable003','dgtable',3,'莞医通客户业务流水','莞医通客户业务流水','1','report','1','V4.1.dgtab','hs_dgyyttable03','90009300000','0','agent');
insert into t_menu (menu_id,above_menu_id,menu_deep,menu_name,menu_desc,is_run_menu,tran_code,is_enable,version,report_id,order_id,menu_type,system_id) values('dgtable004','dgtable',3,'莞医通业务流水','莞医通业务流水','1','report','1','V4.1.dgtab','hs_dgyyttable04','90009400000','0','agent');
insert into t_menu (menu_id,above_menu_id,menu_deep,menu_name,menu_desc,is_run_menu,is_enable,version,order_id,menu_type,system_id) values('dgtable','/',2,'莞医通报表','莞医通报表','0','1','V4.1.dgtab','900090000000','0','agent');
insert into t_menu (menu_id,above_menu_id,menu_deep,menu_name,menu_desc,is_run_menu,tran_code,is_enable,version,report_id,order_id,menu_type,system_id) values('dgtable001','dgtable',3,'莞医通业务不同渠道业务统计表','莞医通业务不同渠道业务统计表','1','report','1','V4.1.dgtab','hs_dgyyttable01','900091000000','0','agent');
insert into t_menu (menu_id,above_menu_id,menu_deep,menu_name,menu_desc,is_run_menu,tran_code,is_enable,version,report_id,order_id,menu_type,system_id) values('dgtable002','dgtable',3,'莞医通地区或医院业务统计表','莞医通地区或医院业务统计表','1','report','1','V4.1.dgtab','hs_dgyyttable02','90009200000','0','agent');
insert into t_menu (menu_id,above_menu_id,menu_deep,menu_name,menu_desc,is_run_menu,is_enable,version,order_id,menu_type,system_id) values('dgyxttable','/',2,'院线通报表','院线通报表','0','1','V4.1.dgtab','900080000000','0','agent');
insert into t_menu (menu_id,above_menu_id,menu_deep,menu_name,menu_desc,is_run_menu,tran_code,is_enable,version,report_id,order_id,menu_type,system_id) values('dgyxttable001','dgyxttable',3,'院线通业务不同渠道业务统计表','院线通业务不同渠道业务统计表','1','report','1','V4.1.dgtab','hs_dgyxttable01','900081000000','0','agent');
insert into t_menu (menu_id,above_menu_id,menu_deep,menu_name,menu_desc,is_run_menu,tran_code,is_enable,version,report_id,order_id,menu_type,system_id) values('dgyxttable02','dgyxttable',3,'院线通地区业务统计表','院线通地区业务统计表','1','report','1','V4.1.dgtab','hs_dgyxttable02','900082000000','0','agent');
insert into t_menu (menu_id,above_menu_id,menu_deep,menu_name,menu_desc,is_run_menu,tran_code,is_enable,version,report_id,order_id,menu_type,system_id) values('dgyxttable03','dgyxttable',3,'院线通客户交易流水','院线通客户交易流水','1','report','1','V4.1.dgtab','hs_dgyxttable03','900083000000','0','agent');
insert into t_menu (menu_id,above_menu_id,menu_deep,menu_name,menu_desc,is_run_menu,tran_code,is_enable,version,report_id,order_id,menu_type,system_id) values('dgyxttable04','dgyxttable',3,'院线通业务流水','院线通业务流
水','1','report','1','V4.1.dgtab','hs_dgyxttable04','900084000000','0','agent');
insert into t_menu (menu_id,above_menu_id,menu_deep,menu_name,menu_desc,is_run_menu,tran_code,is_enable,version,order_id,menu_type,system_id,bak1) values('dgyxttable05','dgyxttable',3,'代收付流水查询','代收付流水查
询','1','agentLsyyt','1','V4.1.dgtab','900085000000','0','agent','ywbh=003000210000');
insert into t_menu (menu_id,above_menu_id,menu_deep,menu_name,menu_desc,is_run_menu,tran_code,is_enable,version,order_id,menu_type,system_id) values('dgyytrgcz','dgtable',3,'莞医通人工冲正','莞医通人工冲正','1','agentYytRgcz','1','V4.1.dgtab','900090000000','0','agent');
insert into t_menu (menu_id,above_menu_id,menu_deep,menu_name,menu_desc,is_run_menu,tran_code,is_enable,version,order_id,menu_type,system_id) values('dgtabyxtrgcz','dgyxttable',3,'院线通人工冲正','院线通人工冲正','1','agentYxtRgcz','1','V4.1.dgtab','900080000000','0','agent');

--t_sendinfo
delete from t_sendinfo where version='V4.1.dgyxt';
delete from t_sendinfo where version='V4.1.dgtab';
insert into t_sendinfo (id,send_id,send_name,send_type,userid,orgid,innerorgid,version,communicate,datasvr) values(311,'931100','莞银人工冲正','1','admin','00000','100','V4.1.dgtab','agentXml','agentFile');

--t_send_cond
delete from t_send_cond where version='V4.1.dgyxt';
delete from t_send_cond where version='V4.1.dgtab';
insert into t_send_cond (id,send_cond_id,send_cond_name,send_cond_type,order_id,is_null,version) values(311,'yjylsh','原交易流水号','1','1','1','V4.1.dgtab');
insert into t_send_cond (id,send_cond_id,send_cond_name,send_cond_type,order_id,is_null,version) values(311,'jyrq','交易日期','1','2','1','V4.1.dgtab');
insert into t_send_cond (id,send_cond_id,send_cond_name,send_cond_type,order_id,is_null,version) values(311,'ywbh','业务编号','1','3','1','V4.1.dgtab');
insert into t_send_cond (id,send_cond_id,send_cond_name,send_cond_type,order_id,is_null,version) values(311,'jydm','交易代码','1','4','1','V4.1.dgtab');
insert into t_send_cond (id,send_cond_id,send_cond_name,send_cond_type,order_id,is_null,version) values(311,'qdbs','办理渠道','1','5','1','V4.1.dgtab');
insert into t_send_cond (id,send_cond_id,send_cond_name,send_cond_type,order_id,is_null,version) values(311,'order_no','订单号','1','6','1','V4.1.dgtab');
insert into t_send_cond (id,send_cond_id,send_cond_name,send_cond_type,order_id,is_null,version) values(311,'ywlx','业务类型','1','7','1','V4.1.dgtab');
insert into t_send_cond (id,send_cond_id,send_cond_name,send_cond_type,order_id,is_null,version) values(311,'acct_no','支付账号','1','8','1','V4.1.dgtab');

--t_send_return
delete from t_send_return where version='V4.1.dgyxt';
delete from t_send_return where version='V4.1.dgtab';
insert into t_send_return (id,return_id,return_name,order_id,value_type,ret_type,version,bak1) values(311,'ptrq','平台日期','1','0','0','V4.1.dgtab','0');
insert into t_send_return (id,return_id,return_name,order_id,value_type,ret_type,version,bak1) values(311,'ptlsh','平台流水','2','0','0','V4.1.dgtab','0');
insert into t_send_return (id,return_id,return_name,order_id,value_type,ret_type,version,bak1) values(311,'retcode','响应码','3','0','0','V4.1.dgtab','0');
insert into t_send_return (id,return_id,return_name,order_id,value_type,ret_type,version,bak1) values(311,'retmsg','响应信息','4','0','0','V4.1.dgtab','0');

--t_report
delete from t_report where version='V4.1.dgyxt';
delete from t_report where version='V4.1.dgtab';
insert into t_report (report_id,report_name,report_type,report_path,max_number,version) values('hs_dgyyttable01','莞医通业务不同渠道业务统计表','1','hs_dgyyttable01.jasper',5000,'V4.1.dgtab');
insert into t_report (report_id,report_name,report_type,report_path,max_number,version) values('hs_dgyyttable03','莞医通客户业务流水','1','hs_dgyyttable03.jasper',5000,'V4.1.dgtab');
insert into t_report (report_id,report_name,report_type,report_path,max_number,version) values('hs_dgyyttable04','莞医通业务流水','1','hs_dgyyttable04.jasper',5000,'V4.1.dgtab');
insert into t_report (report_id,report_name,report_type,report_path,max_number,version) values('hs_dgyyttable02','莞医通地区或医院业务量统计','1','hs_dgyyttable02.jasper',5000,'V4.1.dgtab');
insert into t_report (report_id,report_name,report_type,report_path,max_number,version) values('hs_dgyxttable01','院线通业
务不同渠道业务统计表','1','hs_dgyxttable01.jasper',5000,'V4.1.dgtab');
insert into t_report (report_id,report_name,report_type,report_path,max_number,version) values('hs_dgyxttable02','院线通影
院或地区业务统计表','1','hs_dgyxttable02.jasper',5000,'V4.1.dgtab');
insert into t_report (report_id,report_name,report_type,report_path,max_number,version) values('hs_dgyxttable03','院线通客
户业务流水','1','hs_dgyxttable03.jasper',5000,'V4.1.dgtab');
insert into t_report (report_id,report_name,report_type,report_path,max_number,version) values('hs_dgyxttable04','院线通业
务流水','1','hs_dgyxttable04.jasper',5000,'V4.1.dgtab');

--t_report_cond
delete from t_report_cond where version='V4.1.dgyxt';
delete from t_report_cond where version='V4.1.dgtab';
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,cond_value,version,bak1) values('qd','hs_dgyxttable01','业务类型','2','0',4,'ywlx','V4.1.dgtab','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('qe','hs_dgyxttable03','手机号','1','0',5,'V4.1.dgtab','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('qa','hs_dgyxttable04','起始日期','3','1',1,'V4.1.dgtab','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('qb','hs_dgyxttable04','结束日期','3','1',2,'V4.1.dgtab','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,cond_value,version,bak1) values('qc','hs_dgyxttable04','支付方式','2','0',3,'zflx','V4.1.dgtab','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,cond_value,version,bak1) values('qd','hs_dgyxttable04','业务状态','2','0',4,'yxt_state','V4.1.dgtab','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,cond_value,version,bak1) values('qf','hs_dgyxttable03','渠道','9','0',6,'APP_QDXX:qdbs:QDSM::true:false','V4.1.dgtab','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,cond_value,version,bak1) values('q3','hs_dgyyttable01','渠道','9','0',3,'APP_QDXX:qdbs:QDMC::true:false','V4.1.dgtab','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,cond_value,version,bak1) values('q4','hs_dgyyttable01','业务类型','2','0',4,'ywlx','V4.1.dgtab','1');
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
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,cond_value,version,bak1) values('q6','hs_dgyyttable02','业务类型','2','0',6,'ywlx','V4.1.dgtab','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('qa','hs_dgyxttable01','起始日期','3','1',1,'V4.1.dgtab','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('qb','hs_dgyxttable01','结束日期','3','1',2,'V4.1.dgtab','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,cond_value,version,bak1) values('qc','hs_dgyxttable01','渠道','9','0',3,'APP_QDXX:qdbs:QDMC::true:false','V4.1.dgtab','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('qa','hs_dgyxttable02','起始日期','3','1',1,'V4.1.dgtab','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('qb','hs_dgyxttable02','结束日期','3','1',2,'V4.1.dgtab','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,cond_value,version,bak1) values('qc','hs_dgyxttable02','省份','9','0',3,'YWTY_CITYPROVS:PROVSID:PROVSNAME::true:false','V4.1.dgtab','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,cond_value,version,bak1) values('qd','hs_dgyxttable02','渠道','9','0',4,'APP_QDXX:qdbs:QDMC::true:false','V4.1.dgtab','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,cond_value,version,bak1) values('qe','hs_dgyxttable02','支付方式','2','0',5,'zflx','V4.1.dgtab','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,cond_value,version,bak1) values('qf','hs_dgyxttable02','业务类型','2','0',6,'ywlx','V4.1.dgtab','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('qa','hs_dgyxttable03','起始日期','3','1',1,'V4.1.dgtab','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('qb','hs_dgyxttable03','结束日期','3','1',2,'V4.1.dgtab','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('qc','hs_dgyxttable03','客户名称','1','0',3,'V4.1.dgtab','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('qd','hs_dgyxttable03','账号/卡号','1','0',4,'V4.1.dgtab','1');
