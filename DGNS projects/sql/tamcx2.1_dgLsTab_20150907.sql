

--t_tran
delete from t_tran where version='V4.1.dgtab';
insert into t_tran (tran_code,tran_name,tran_type,tran_class,version) values('agentLsyyt','ݸҽͨ���ո���ˮ��ѯ','1','com.hundsun.agent.web.dsf.ctl.AgentLsYytCtl','V4.1.dgtab');

--t_sub_tran
delete from t_sub_tran where version='V4.1.dgtab';
insert into t_sub_tran (tran_code,sub_tran_code,sub_tran_name,repage,sub_tran_desc,version) values('agentLsyyt','def','��ѯ','app/agent/dsf/agenttlsyyt.jsp','Ĭ��','V4.1.dgtab');
insert into t_sub_tran (tran_code,sub_tran_code,sub_tran_name,repage,sub_tran_desc,version) values('agentLsyyt','list','�������','about:blank','�������','V4.1.dgtab');
insert into t_sub_tran (tran_code,sub_tran_code,sub_tran_name,repage,sub_tran_desc,version) values('agentLsyyt','send','ִ�н���','about:blank','ִ�н���','V4.1.dgtab');

--t_menu
delete from t_menu where version='V4.1.dgtab';
insert into t_menu (menu_id,above_menu_id,menu_deep,menu_name,menu_desc,is_run_menu,tran_code,is_enable,version,order_id,menu_type,system_id,bak1) values('dgtable005','dgtable',3,'���ո���ˮ��ѯ','���ո���ˮ��ѯ','1','agentLsyyt','1','V4.1.dgtab','90009500000','0','agent','ywbh=003000110000');
insert into t_menu (menu_id,above_menu_id,menu_deep,menu_name,menu_desc,is_run_menu,tran_code,is_enable,version,report_id,order_id,menu_type,system_id) values('dgtable003','dgtable',3,'ݸҽͨ�ͻ�ҵ����ˮ','ݸҽͨ�ͻ�ҵ����ˮ','1','report','1','V4.1.dgtab','hs_dgyyttable03','90009300000','0','agent');
insert into t_menu (menu_id,above_menu_id,menu_deep,menu_name,menu_desc,is_run_menu,tran_code,is_enable,version,report_id,order_id,menu_type,system_id) values('dgtable004','dgtable',3,'ݸҽͨҵ����ˮ','ݸҽͨҵ����ˮ','1','report','1','V4.1.dgtab','hs_dgyyttable04','90009400000','0','agent');
insert into t_menu (menu_id,above_menu_id,menu_deep,menu_name,menu_desc,is_run_menu,is_enable,version,order_id,menu_type,system_id) values('dgtable','/',2,'ݸҽͨ����','ݸҽͨ����','0','1','V4.1.dgtab','900090000000','0','agent');
insert into t_menu (menu_id,above_menu_id,menu_deep,menu_name,menu_desc,is_run_menu,tran_code,is_enable,version,report_id,order_id,menu_type,system_id) values('dgtable001','dgtable',3,'ݸҽͨҵ��ͬ����ҵ��ͳ�Ʊ�','ݸҽͨҵ��ͬ����ҵ��ͳ�Ʊ�','1','report','1','V4.1.dgtab','hs_dgyyttable01','900091000000','0','agent');
insert into t_menu (menu_id,above_menu_id,menu_deep,menu_name,menu_desc,is_run_menu,tran_code,is_enable,version,report_id,order_id,menu_type,system_id) values('dgtable002','dgtable',3,'ݸҽͨ������ҽԺҵ��ͳ�Ʊ�','ݸҽͨ������ҽԺҵ��ͳ�Ʊ�','1','report','1','V4.1.dgtab','hs_dgyyttable02','90009200000','0','agent');

--t_sendinfo
delete from t_sendinfo where version='V4.1.dgtab';

--t_send_cond
delete from t_send_cond where version='V4.1.dgtab';

--t_send_return
delete from t_send_return where version='V4.1.dgtab';



--t_report
delete from t_report where version='V4.1.dgtab';
insert into t_report (report_id,report_name,report_type,report_path,max_number,version) values('hs_dgyyttable01','ݸҽͨҵ��ͬ����ҵ��ͳ�Ʊ�','1','hs_dgyyttable01.jasper',5000,'V4.1.dgtab');
insert into t_report (report_id,report_name,report_type,report_path,max_number,version) values('hs_dgyyttable03','ݸҽͨ�ͻ�ҵ����ˮ','1','hs_dgyyttable03.jasper',5000,'V4.1.dgtab');
insert into t_report (report_id,report_name,report_type,report_path,max_number,version) values('hs_dgyyttable04','ݸҽͨҵ����ˮ','1','hs_dgyyttable04.jasper',5000,'V4.1.dgtab');
insert into t_report (report_id,report_name,report_type,report_path,max_number,version) values('hs_dgyyttable02','ݸҽͨ������ҽԺҵ����ͳ��','1','hs_dgyyttable02.jasper',5000,'V4.1.dgtab');

--t_report_cond
delete from t_report_cond where version='V4.1.dgtab';
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,cond_value,version,bak1) values('q3','hs_dgyyttable01','����','9','0',3,'APP_QDXX:qdbs:QDSM::true:false','V4.1.dgtab','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,cond_value,version,bak1) values('q4','hs_dgyyttable01','ҵ������','2','0',4,'yyt_ywlx','V4.1.dgtab','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('qa','hs_dgyyttable03','��ʼ����','3','1',1,'V4.1.dgtab','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('qb','hs_dgyyttable03','��������','3','1',2,'V4.1.dgtab','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('qc','hs_dgyyttable03','�ͻ�����','1','0',3,'V4.1.dgtab','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('qd','hs_dgyyttable03','�˺�/����','1','0',4,'V4.1.dgtab','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('q1','hs_dgyyttable01','��ʼ����','3','1',1,'V4.1.dgtab','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('q2','hs_dgyyttable01','��������','3','1',2,'V4.1.dgtab','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('qe','hs_dgyyttable03','�ֻ���','1','0',5,'V4.1.dgtab','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('qa','hs_dgyyttable04','��ʼ����','3','1',1,'V4.1.dgtab','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('qb','hs_dgyyttable04','��������','3','1',2,'V4.1.dgtab','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,cond_value,version,bak1) values('qc','hs_dgyyttable04','֧����ʽ','2','0',3,'zflx','V4.1.dgtab','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,cond_value,version,bak1) values('qd','hs_dgyyttable04','ҵ��״̬','2','0',4,'yyt_state','V4.1.dgtab','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('q1','hs_dgyyttable02','��ʼ����','3','1',1,'V4.1.dgtab','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('q2','hs_dgyyttable02','��������','3','1',2,'V4.1.dgtab','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,cond_value,version,bak1) values('q3','hs_dgyyttable02','����','9','0',3,'yyt_citycode:area_id:area_name:area_level=^3^:true:false','V4.1.dgtab','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('q4','hs_dgyyttable02','ҽԺ','1','0',4,'V4.1.dgtab','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,cond_value,version,bak1) values('q5','hs_dgyyttable02','����','9','0',5,'zjyw_ordersum:unit_id2:unit_name3::true:false','V4.1.dgtab','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,cond_value,version,bak1) values('q6','hs_dgyyttable02','ҵ������','2','0',6,'yyt_ywlx','V4.1.dgtab','1');




--t_tran
delete from t_tran where version='V4.1.dgyxt';

--t_sub_tran
delete from t_sub_tran where version='V4.1.dgyxt';

--t_menu
delete from t_menu where version='V4.1.dgyxt';
insert into t_menu (menu_id,above_menu_id,menu_deep,menu_name,menu_desc,is_run_menu,is_enable,version,order_id,menu_type,system_id) values('dgyxttable','/',2,'Ժ��ͨ����','Ժ��ͨ����','0','1','V4.1.dgyxt','900080000000','0','agent');
insert into t_menu (menu_id,above_menu_id,menu_deep,menu_name,menu_desc,is_run_menu,tran_code,is_enable,version,report_id,order_id,menu_type,system_id) values('dgyxttable001','dgyxttable',3,'Ժ��ͨҵ��ͬ����ҵ��ͳ�Ʊ�','Ժ��ͨҵ��ͬ����ҵ��ͳ�Ʊ�','1','report','1','V4.1.dgyxt','hs_dgyxttable01','900081000000','0','agent');
insert into t_menu (menu_id,above_menu_id,menu_deep,menu_name,menu_desc,is_run_menu,tran_code,is_enable,version,report_id,order_id,menu_type,system_id) values('dgyxttable02','dgyxttable',3,'Ժ��ͨӰԺ�����ҵ��ͳ�Ʊ�','Ժ��ͨӰԺ�����ҵ��ͳ�Ʊ�','1','report','1','V4.1.dgyxt','hs_dgyxttable02','900082000000','0','agent');
insert into t_menu (menu_id,above_menu_id,menu_deep,menu_name,menu_desc,is_run_menu,tran_code,is_enable,version,report_id,order_id,menu_type,system_id) values('dgyxttable03','dgyxttable',3,'Ժ��ͨ�ͻ�ҵ����ˮ','Ժ��ͨ�ͻ�ҵ����ˮ','1','report','1','V4.1.dgyxt','hs_dgyxttable03','900083000000','0','agent');
insert into t_menu (menu_id,above_menu_id,menu_deep,menu_name,menu_desc,is_run_menu,tran_code,is_enable,version,report_id,order_id,menu_type,system_id) values('dgyxttable04','dgyxttable',3,'Ժ��ͨҵ����ˮ','Ժ��ͨҵ����ˮ','1','report','1','V4.1.dgyxt','hs_dgyxttable04','900084000000','0','agent');
insert into t_menu (menu_id,above_menu_id,menu_deep,menu_name,menu_desc,is_run_menu,tran_code,is_enable,version,order_id,menu_type,system_id,bak1) values('dgyxttable05','dgyxttable',3,'���ո���ˮ��ѯ','���ո���ˮ��ѯ','1','agentLsyyt','1','V4.1.dgyxt','900085000000','0','agent','ywbh=003000210000');

--t_sendinfo
delete from t_sendinfo where version='V4.1.dgyxt';

--t_send_cond
delete from t_send_cond where version='V4.1.dgyxt';

--t_send_return
delete from t_send_return where version='V4.1.dgyxt';



--t_report
delete from t_report where version='V4.1.dgyxt';
insert into t_report (report_id,report_name,report_type,report_path,max_number,version) values('hs_dgyxttable01','Ժ��ͨҵ��ͬ����ҵ��ͳ�Ʊ�','1','hs_dgyxttable01.jasper',5000,'V4.1.dgyxt');
insert into t_report (report_id,report_name,report_type,report_path,max_number,version) values('hs_dgyxttable02','Ժ��ͨӰԺ�����ҵ��ͳ�Ʊ�','1','hs_dgyxttable02.jasper',5000,'V4.1.dgyxt');
insert into t_report (report_id,report_name,report_type,report_path,max_number,version) values('hs_dgyxttable03','Ժ��ͨ�ͻ�ҵ����ˮ','1','hs_dgyxttable03.jasper',5000,'V4.1.dgyxt');
insert into t_report (report_id,report_name,report_type,report_path,max_number,version) values('hs_dgyxttable04','Ժ��ͨҵ����ˮ','1','hs_dgyxttable04.jasper',5000,'V4.1.dgyxt');

--t_report_cond
delete from t_report_cond where version='V4.1.dgyxt';
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('qa','hs_dgyxttable01','��ʼ����','3','1',1,'V4.1.dgyxt','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('qb','hs_dgyxttable01','��������','3','1',2,'V4.1.dgyxt','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,cond_value,version,bak1) values('qc','hs_dgyxttable01','����','9','0',3,'APP_QDXX:qdbs:QDSM::true:false','V4.1.dgyxt','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,cond_value,version,bak1) values('qd','hs_dgyxttable01','ҵ������','2','0',4,'yxt_ywlx','V4.1.dgyxt','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('qa','hs_dgyxttable02','��ʼ����','3','0',1,'V4.1.dgyxt','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('qb','hs_dgyxttable02','��������','3','1',2,'V4.1.dgyxt','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('qc','hs_dgyxttable02','����','1','0',3,'V4.1.dgyxt','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('qd','hs_dgyxttable02','ӰԺ','1','0',4,'V4.1.dgyxt','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('qe','hs_dgyxttable02','ӰƬ','1','0',5,'V4.1.dgyxt','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,cond_value,version,bak1) values('qf','hs_dgyxttable02','ҵ������','2','0',6,'yxt_ywlx','V4.1.dgyxt','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('qa','hs_dgyxttable03','��ʼ����','3','1',1,'V4.1.dgyxt','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('qb','hs_dgyxttable03','��������','3','1',2,'V4.1.dgyxt','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('qc','hs_dgyxttable03','�ͻ�����','1','0',3,'V4.1.dgyxt','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('qd','hs_dgyxttable03','�˺�/����','1','0',4,'V4.1.dgyxt','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('qe','hs_dgyxttable03','�ֻ���','1','0',5,'V4.1.dgyxt','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('qa','hs_dgyxttable04','��ʼ����','3','1',1,'V4.1.dgyxt','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,version,bak1) values('qb','hs_dgyxttable04','��������','3','1',2,'V4.1.dgyxt','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,cond_value,version,bak1) values('qc','hs_dgyxttable04','֧����ʽ','2','0',3,'zflx','V4.1.dgyxt','1');
insert into t_report_cond (cond_id,report_id,cond_name,cond_type,is_null,order_id,cond_value,version,bak1) values('qd','hs_dgyxttable04','ҵ��״̬','2','0',4,'yxt_state','V4.1.dgyxt','1');
