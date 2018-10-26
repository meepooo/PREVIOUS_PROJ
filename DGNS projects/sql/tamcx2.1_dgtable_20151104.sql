
--莞医通订单查询
delete from T_TRAN where TRAN_CODE = 'agentYytOrderQuery';
delete from T_SUB_TRAN where TRAN_CODE = 'agentYytOrderQuery';
delete from T_MENU where TRAN_CODE = 'agentYytOrderQuery';
insert into t_tran (tran_code,tran_name,tran_type,tran_class,version) 
values('agentYytOrderQuery','莞医通订单查询','1','com.hundsun.agent.web.dsf.ctl.AgentYytOrderQueryCtl','V4.1.dgtab');
insert into t_sub_tran (tran_code,sub_tran_code,sub_tran_name,repage,sub_tran_desc,version) 
values('agentYytOrderQuery','def','默认页面','app/agent/dsf/agentYytOrderQuery.jsp','默认页面','V4.1.dgtab');
insert into t_sub_tran (tran_code,sub_tran_code,sub_tran_name,repage,sub_tran_desc,version) 
values('agentYytOrderQuery','list','列表','about:blank','列表','V4.1.dgtab');
insert into t_menu (menu_id,above_menu_id,menu_deep,menu_name,menu_desc,is_run_menu,tran_code,is_enable,version,order_id,menu_type,system_id) 
values('dgyytOrder','dgtable',3,'莞医通订单查询','莞医通订单查询','1','agentYytOrderQuery','1','V4.1.dgtab','90009600000','0','agent'); 


--院线通订单查询
delete from T_TRAN where TRAN_CODE = 'agentYxtOrderQuery';
delete from T_SUB_TRAN where TRAN_CODE = 'agentYxtOrderQuery';
delete from T_MENU where TRAN_CODE = 'agentYxtOrderQuery';
insert into t_tran (tran_code,tran_name,tran_type,tran_class,version) 
values('agentYxtOrderQuery','院线通订单查询','1','com.hundsun.agent.web.dsf.ctl.AgentYxtOrderQueryCtl','V4.1.dgtab');
insert into t_sub_tran (tran_code,sub_tran_code,sub_tran_name,repage,sub_tran_desc,version) 
values('agentYxtOrderQuery','def','默认页面','app/agent/dsf/agentYxtOrderQuery.jsp','默认页面','V4.1.dgtab');
insert into t_sub_tran (tran_code,sub_tran_code,sub_tran_name,repage,sub_tran_desc,version) 
values('agentYxtOrderQuery','list','列表','about:blank','列表','V4.1.dgtab');
insert into t_menu (menu_id,above_menu_id,menu_deep,menu_name,menu_desc,is_run_menu,tran_code,is_enable,version,order_id,menu_type,system_id) 
values('dgyxtOrder','dgyxttable',3,'院线通订单查询','院线通订单查询','1','agentYxtOrderQuery','1','V4.1.dgtab','900086000000','0','agent'); 


--翰银支付订单查询
delete from T_TRAN where TRAN_CODE = 'agentHyzfOrderQuery';
delete from T_SUB_TRAN where TRAN_CODE = 'agentHyzfOrderQuery';
delete from T_MENU where TRAN_CODE = 'agentHyzfOrderQuery';
insert into t_tran (tran_code,tran_name,tran_type,tran_class,version) 
values('agentHyzfOrderQuery','翰银支付订单查询','1','com.hundsun.agent.web.dsf.ctl.AgentHyzfOrderQueryCtl','V4.1.dgtab');
insert into t_sub_tran (tran_code,sub_tran_code,sub_tran_name,repage,sub_tran_desc,version) 
values('agentHyzfOrderQuery','def','默认页面','app/agent/dsf/agentHyzfOrderQuery.jsp','默认页面','V4.1.dgtab');
insert into t_sub_tran (tran_code,sub_tran_code,sub_tran_name,repage,sub_tran_desc,version) 
values('agentHyzfOrderQuery','list','列表','about:blank','列表','V4.1.dgtab');
insert into t_menu (menu_id,above_menu_id,menu_deep,menu_name,menu_desc,is_run_menu,is_enable,version,order_id,menu_type,system_id) 
values('dghyzftable','/',2,'翰银支付报表','翰银支付报表','0','1','V4.1.dgtab','900100000000','0','agent');
insert into t_menu (menu_id,above_menu_id,menu_deep,menu_name,menu_desc,is_run_menu,tran_code,is_enable,version,order_id,menu_type,system_id) 
values('dghyzfOrder','dghyzftable',3,'翰银支付订单查询','翰银支付订单查询','1','agentHyzfOrderQuery','1','V4.1.dgtab','900101000000','0','agent'); 
