
--ݸҽͨ������ѯ
delete from T_TRAN where TRAN_CODE = 'agentYytOrderQuery';
delete from T_SUB_TRAN where TRAN_CODE = 'agentYytOrderQuery';
delete from T_MENU where TRAN_CODE = 'agentYytOrderQuery';
insert into t_tran (tran_code,tran_name,tran_type,tran_class,version) 
values('agentYytOrderQuery','ݸҽͨ������ѯ','1','com.hundsun.agent.web.dsf.ctl.AgentYytOrderQueryCtl','V4.1.dgtab');
insert into t_sub_tran (tran_code,sub_tran_code,sub_tran_name,repage,sub_tran_desc,version) 
values('agentYytOrderQuery','def','Ĭ��ҳ��','app/agent/dsf/agentYytOrderQuery.jsp','Ĭ��ҳ��','V4.1.dgtab');
insert into t_sub_tran (tran_code,sub_tran_code,sub_tran_name,repage,sub_tran_desc,version) 
values('agentYytOrderQuery','list','�б�','about:blank','�б�','V4.1.dgtab');
insert into t_menu (menu_id,above_menu_id,menu_deep,menu_name,menu_desc,is_run_menu,tran_code,is_enable,version,order_id,menu_type,system_id) 
values('dgyytOrder','dgtable',3,'ݸҽͨ������ѯ','ݸҽͨ������ѯ','1','agentYytOrderQuery','1','V4.1.dgtab','90009600000','0','agent'); 


--Ժ��ͨ������ѯ
delete from T_TRAN where TRAN_CODE = 'agentYxtOrderQuery';
delete from T_SUB_TRAN where TRAN_CODE = 'agentYxtOrderQuery';
delete from T_MENU where TRAN_CODE = 'agentYxtOrderQuery';
insert into t_tran (tran_code,tran_name,tran_type,tran_class,version) 
values('agentYxtOrderQuery','Ժ��ͨ������ѯ','1','com.hundsun.agent.web.dsf.ctl.AgentYxtOrderQueryCtl','V4.1.dgtab');
insert into t_sub_tran (tran_code,sub_tran_code,sub_tran_name,repage,sub_tran_desc,version) 
values('agentYxtOrderQuery','def','Ĭ��ҳ��','app/agent/dsf/agentYxtOrderQuery.jsp','Ĭ��ҳ��','V4.1.dgtab');
insert into t_sub_tran (tran_code,sub_tran_code,sub_tran_name,repage,sub_tran_desc,version) 
values('agentYxtOrderQuery','list','�б�','about:blank','�б�','V4.1.dgtab');
insert into t_menu (menu_id,above_menu_id,menu_deep,menu_name,menu_desc,is_run_menu,tran_code,is_enable,version,order_id,menu_type,system_id) 
values('dgyxtOrder','dgyxttable',3,'Ժ��ͨ������ѯ','Ժ��ͨ������ѯ','1','agentYxtOrderQuery','1','V4.1.dgtab','900086000000','0','agent'); 


--����֧��������ѯ
delete from T_TRAN where TRAN_CODE = 'agentHyzfOrderQuery';
delete from T_SUB_TRAN where TRAN_CODE = 'agentHyzfOrderQuery';
delete from T_MENU where TRAN_CODE = 'agentHyzfOrderQuery';
insert into t_tran (tran_code,tran_name,tran_type,tran_class,version) 
values('agentHyzfOrderQuery','����֧��������ѯ','1','com.hundsun.agent.web.dsf.ctl.AgentHyzfOrderQueryCtl','V4.1.dgtab');
insert into t_sub_tran (tran_code,sub_tran_code,sub_tran_name,repage,sub_tran_desc,version) 
values('agentHyzfOrderQuery','def','Ĭ��ҳ��','app/agent/dsf/agentHyzfOrderQuery.jsp','Ĭ��ҳ��','V4.1.dgtab');
insert into t_sub_tran (tran_code,sub_tran_code,sub_tran_name,repage,sub_tran_desc,version) 
values('agentHyzfOrderQuery','list','�б�','about:blank','�б�','V4.1.dgtab');
insert into t_menu (menu_id,above_menu_id,menu_deep,menu_name,menu_desc,is_run_menu,is_enable,version,order_id,menu_type,system_id) 
values('dghyzftable','/',2,'����֧������','����֧������','0','1','V4.1.dgtab','900100000000','0','agent');
insert into t_menu (menu_id,above_menu_id,menu_deep,menu_name,menu_desc,is_run_menu,tran_code,is_enable,version,order_id,menu_type,system_id) 
values('dghyzfOrder','dghyzftable',3,'����֧��������ѯ','����֧��������ѯ','1','agentHyzfOrderQuery','1','V4.1.dgtab','900101000000','0','agent'); 
