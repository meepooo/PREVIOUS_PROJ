--单位信息表  app_dwxx  单位信息配置包括账号等信息
	INSERT INTO APP_DWXX  VALUES ('4001001000001', '东莞实验中学', '1', '02200059', '弓长张', '186186186186', '东莞市', 'dongguan@163.com', '00000', 'admin', '20170807091802', null, null, '0');
--单位产品协议表  app_dwcpxy 
	INSERT INTO APP_DWCPXY  VALUES ('4001001000001', '4001001', '4001001000001', '校园卡圈存', '4001001000001', 'drc', 'jfpt', '99', '1', '120120190010000010', '天天发工资公司', '', '', null, null, null, null, null, null, '', '', null, 0.00, '00000', 'admin', '20170807093121', '88888', null, '0', null, null, null, '天天发工资公司&#x2014;线上缴费', '000010126220010072', null, null, '03', '1', null, null, null);
--是否上第三方标志
	INSERT INTO AGENT_CSYS  VALUES ('THIRD_CHECK', '4001001', '1', '是否上第三方对账 0:否 1:是', null, null, null, null, null);
--缴费项目参数配置
	INSERT INTO AGENT_JFXM  VALUES ('4001001', '10001', '校园卡充值', '1', '1', '20170721142901', 'admin', '000000', '20170721143000', 'admin', '000000', null, null, null, null, null);
--通讯参数信息表设置  测试环境对应的gapsIP和端口 gxpIP和端口  注意学校ftp服务器的目录需要配置
	INSERT INTO APP_TXAQXX  VALUES ('000001', '东莞实验中学校园卡圈存', '3', '4001001000001', '1', '1', '10.8.208.171', '50021', null, null, null, null, null, 'gapsv4', 'gapsv4', null, '10.106.0.118', 'ftp_nsh', '123456789', '1', '2', '', '/file/xykdz', '/home/gapsv4/file/xykqc', '00000', 'admin', '20170808045548', '8894', '10.8.208.178', '0', null);
--缴费项目代码
  INSERT INTO AGENT_JFXM  VALUES ('4001001', '10001', '校园卡充值', '1', '1', '20170721142901', 'admin', '000000', '20170721143000', 'admin', '000000', null, null, null, null, null);
--渠道信息表
	INSERT INTO APP_QDXX  VALUES ('80', '第三方系统', '第三方渠道', '1', '', '', '0', '0', '00000', 'admin', '20170901090752', '', '', '0');
--产品信息表
	INSERT INTO APP_CPXX  VALUES ('4001001', '校园卡充值费', '003', '00000', null, null, '1', '1', '0', '1', '2', '3', 'K_KHCPQY', '1', '0', '1', null, null, 0, 0, '1', '1', '00000', 'admin', '20170718095638', null, null, '0', null, null, null);

