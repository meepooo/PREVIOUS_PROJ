
--t_tran
--delete from t_tran where version='V4.1.hytab';
--insert into t_tran (tran_code,tran_name,tran_type,tran_class,version) values('agentLshyf','����֧�����ո���ˮ��ѯ','1','com.hundsun.agent.web.dsf.ctl.AgentLsYytCtl','V4.1.hytab');

--t_sub_tran
--delete from t_sub_tran where version='V4.1.hytab';
--insert into t_sub_tran (tran_code,sub_tran_code,sub_tran_name,repage,sub_tran_desc,version) values('agentLshyf','send','ִ�н���','about:blank','ִ�н���','V4.1.hytab');
--insert into t_sub_tran (tran_code,sub_tran_code,sub_tran_name,repage,sub_tran_desc,version) values('agentLshyf','def','��ѯ','app/agent/dsf/agenttlsyyt.jsp','Ĭ��','V4.1.hytab');
--insert into t_sub_tran (tran_code,sub_tran_code,sub_tran_name,repage,sub_tran_desc,version) values('agentLshyf','list','�������','about:blank','�������','V4.1.hytab');

--t_menu
delete from t_menu where version='V4.1.hytab';
insert into t_menu (menu_id,above_menu_id,menu_deep,menu_name,menu_desc,is_run_menu,tran_code,is_enable,version,order_id,menu_type,system_id,bak1) values('hytable005','hytable',3,'���ո���ˮ��ѯ','���ո���ˮ��ѯ','1','agentLs','1','V4.1.hytab','90009500000','0','agent','ywbh=003000110000');
insert into t_menu (menu_id,above_menu_id,menu_deep,menu_name,menu_desc,is_run_menu,is_enable,version,order_id,menu_type,system_id) values('hytable','/',2,'����֧������','����֧������','0','1','V4.1.hytab','900100000000','0','agent');
