-------------------�ò�����䵥��ִ��,���ݱ����--------------------------------------
--�������ݿ�  db2 connect to $DBALIAS user $DBUSER using $DBPASS
--��������ˮ������������ж��Ƿ���Ҫ����,���ݲ�����ñ���.
--agent_yxt_jfjl (��ˮ��)
--select count(*) from agent_yxt_jfjl
--db2 "export to /home/gapsv4/log/20180530/agent_yxt_jfjl.txt of del select * from agent_yxt_jfjl"
--����agent_jfxq (�ɷ������)
--select count(*) from agent_jfxq where shlxdm='4001000' and shh in (select dwbh from app_dwxx_ext where extfld2='1')

--����app_dwxx
--db2 "export to /home/gapsv4/log/20180530/app_dwxx.txt of del select * from app_dwxx"
--����app_dwcpxy
--db2 "export to /home/gapsv4/log/20180530/app_dwcpxy.txt of del select * from app_dwcpxy"
--����app_dwxx_ext
--db2 "export to /home/gapsv4/log/20180530/app_dwxx_ext.txt of del select * from app_dwxx_ext"

--������±�������,��ɾ�����������,Ȼ���뱸������,ִ���������(����ִ�и����,ִ��ǰ��Ҫ��ղ�����Ϣ,��ֹ�����ظ�)
--table_name�滻Ϊ��Ӧ�ı���
--db2 "import from /home/gapsv4/log/20180530/table_name.txt of del insert into table_name"

--------------------�ò�����䵥��ִ��-------------------------------------------------------

--������Уͨ��Ʒ����(0030025)
INSERT INTO APP_CPXX (CPDM, CPMC, YYBS, ZBJG, ZBGY, KHJL, YWRQLX, QDKZBZ, JGKZCS, SXFBZ, SFQYBZ, QYMS, XYXLJZ, KKFS, JZSX, DZMS, ZJYYH, ZJZYYH, LSBLTS, PDBLTS, JYFS, RZMS, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, CPZT, SXFTKBZ, PZBD, YWB) VALUES ('0030025', '��Уͨ�ɷ�', '003', '00000', '', '', '1', '1', '0', '1', '2', '2', 'K_KHCPQY', '1', '0', '1', '', '', 0, 0, '1', '0', '00000', 'admin', '20180326092850', '', '', '0', null, null, null);
--����agent_yxt_jfjl(��Уͨ�ɷѼ�¼)
update agent_yxt_jfjl set shh=replace(shh,'4001000','0030025') where shh  in (select dwbh from app_dwxx_ext where extfld2='1');
--����agent_jfxq(��Уͨ�ɷ������)
update agent_jfxq set shlxdm=replace(shlxdm,'4001000','0030025'),shdm=replace(shdm,'4001000','0030025') where shdm in (select dwbh from app_dwxx_ext where extfld2='1');
--����app_dwxx(��λ��Ϣ��)
update app_dwxx set  dwbh=replace(dwbh,'4001000','0030025') where  dwbh in (select dwbh from app_dwxx_ext where extfld2='1');
--����app_dwcpxy(��λ��ƷЭ���)
update app_dwcpxy set dwbh=replace(dwbh,'4001000','0030025'),cpdm=replace(cpdm,'4001000','0030025'),ywbh=replace(ywbh,'4001000','0030025') where  dwbh in (select dwbh from app_dwxx_ext where extfld2='1');
--����app_dwxx_ext(��λ��Ϣ��չ��)
update app_dwxx_ext set dwbh=replace(dwbh,'4001000','0030025') where extfld2='1';
