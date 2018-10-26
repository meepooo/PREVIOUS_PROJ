-------------------该部分语句单独执行,备份表语句--------------------------------------
--连接数据库  db2 connect to $DBALIAS user $DBUSER using $DBPASS
--这两张流水表根据数量级判断是否需要备份,数据不大最好备份.
--agent_yxt_jfjl (流水表)
--select count(*) from agent_yxt_jfjl
--db2 "export to /home/gapsv4/log/20180530/agent_yxt_jfjl.txt of del select * from agent_yxt_jfjl"
--备份agent_jfxq (缴费详请表)
--select count(*) from agent_jfxq where shlxdm='4001000' and shh in (select dwbh from app_dwxx_ext where extfld2='1')

--备份app_dwxx
--db2 "export to /home/gapsv4/log/20180530/app_dwxx.txt of del select * from app_dwxx"
--备份app_dwcpxy
--db2 "export to /home/gapsv4/log/20180530/app_dwcpxy.txt of del select * from app_dwcpxy"
--备份app_dwxx_ext
--db2 "export to /home/gapsv4/log/20180530/app_dwxx_ext.txt of del select * from app_dwxx_ext"

--如果更新表发生错误,先删除错误的数据,然后导入备份数据,执行以下语句(谨慎执行该语句,执行前需要清空部分信息,防止数据重复)
--table_name替换为对应的表名
--db2 "import from /home/gapsv4/log/20180530/table_name.txt of del insert into table_name"

--------------------该部分语句单独执行-------------------------------------------------------

--新增银校通产品代码(0030025)
INSERT INTO APP_CPXX (CPDM, CPMC, YYBS, ZBJG, ZBGY, KHJL, YWRQLX, QDKZBZ, JGKZCS, SXFBZ, SFQYBZ, QYMS, XYXLJZ, KKFS, JZSX, DZMS, ZJYYH, ZJZYYH, LSBLTS, PDBLTS, JYFS, RZMS, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, CPZT, SXFTKBZ, PZBD, YWB) VALUES ('0030025', '银校通缴费', '003', '00000', '', '', '1', '1', '0', '1', '2', '2', 'K_KHCPQY', '1', '0', '1', '', '', 0, 0, '1', '0', '00000', 'admin', '20180326092850', '', '', '0', null, null, null);
--更新agent_yxt_jfjl(银校通缴费记录)
update agent_yxt_jfjl set shh=replace(shh,'4001000','0030025') where shh  in (select dwbh from app_dwxx_ext where extfld2='1');
--更新agent_jfxq(银校通缴费详情表)
update agent_jfxq set shlxdm=replace(shlxdm,'4001000','0030025'),shdm=replace(shdm,'4001000','0030025') where shdm in (select dwbh from app_dwxx_ext where extfld2='1');
--更新app_dwxx(单位信息表)
update app_dwxx set  dwbh=replace(dwbh,'4001000','0030025') where  dwbh in (select dwbh from app_dwxx_ext where extfld2='1');
--更新app_dwcpxy(单位产品协议表)
update app_dwcpxy set dwbh=replace(dwbh,'4001000','0030025'),cpdm=replace(cpdm,'4001000','0030025'),ywbh=replace(ywbh,'4001000','0030025') where  dwbh in (select dwbh from app_dwxx_ext where extfld2='1');
--更新app_dwxx_ext(单位信息扩展表)
update app_dwxx_ext set dwbh=replace(dwbh,'4001000','0030025') where extfld2='1';
