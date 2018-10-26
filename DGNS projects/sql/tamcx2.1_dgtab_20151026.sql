
--t_tran
--delete from t_tran where version='V4.1.hytab';
--insert into t_tran (tran_code,tran_name,tran_type,tran_class,version) values('agentLshyf','翰银支付代收付流水查询','1','com.hundsun.agent.web.dsf.ctl.AgentLsYytCtl','V4.1.hytab');

--t_sub_tran
--delete from t_sub_tran where version='V4.1.hytab';
--insert into t_sub_tran (tran_code,sub_tran_code,sub_tran_name,repage,sub_tran_desc,version) values('agentLshyf','send','执行交易','about:blank','执行交易','V4.1.hytab');
--insert into t_sub_tran (tran_code,sub_tran_code,sub_tran_name,repage,sub_tran_desc,version) values('agentLshyf','def','查询','app/agent/dsf/agenttlsyyt.jsp','默认','V4.1.hytab');
--insert into t_sub_tran (tran_code,sub_tran_code,sub_tran_name,repage,sub_tran_desc,version) values('agentLshyf','list','获得数据','about:blank','获得数据','V4.1.hytab');

--t_menu
delete from t_menu where version='V4.1.hytab';
insert into t_menu (menu_id,above_menu_id,menu_deep,menu_name,menu_desc,is_run_menu,tran_code,is_enable,version,order_id,menu_type,system_id,bak1) values('hytable005','hytable',3,'代收付流水查询','代收付流水查询','1','agentLs','1','V4.1.hytab','90009500000','0','agent','ywbh=003000110000');
insert into t_menu (menu_id,above_menu_id,menu_deep,menu_name,menu_desc,is_run_menu,is_enable,version,order_id,menu_type,system_id) values('hytable','/',2,'翰银支付报表','翰银支付报表','0','1','V4.1.hytab','900100000000','0','agent');
