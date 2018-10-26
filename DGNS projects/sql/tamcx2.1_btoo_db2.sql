delete from T_TRAN where version='V2.1.btoo';

delete from T_SUB_TRAN where version='V2.1.btoo';

delete from T_SEND_RETURN where version='V2.1.btoo';

delete from T_SEND_COND where version='V2.1.btoo';

delete from T_SENDINFO where version='V2.1.btoo';

delete from T_MENU where version='V2.1.btoo';

delete from T_DICT where version='V2.1.btoo';

delete from T_SEND_SERVER where id like 'btoo%';



INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('btooYwlx            ', '批转联[业务类型]              ', '1', 'com.hundsun.agent.web.btoo.ctl.BtooYwlxCtl                                                          ', 'V2.1.btoo ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('btooYwbh            ', '批转联[业务编号]              ', '1', 'com.hundsun.agent.web.btoo.ctl.BtooYwbhCtl                                                          ', 'V2.1.btoo ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('btooStepcfg         ', '批转联[步点服务配置]          ', '1', 'com.hundsun.agent.web.btoo.ctl.BtooStepcfgCtl                                                       ', 'V2.1.btoo ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('btooZtsel           ', '批转联状态查询                ', '1', 'com.hundsun.agent.web.btoo.ctl.BtooZtselCtl                                                         ', 'V2.1.btoo ', NULL, NULL, NULL);


INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('btooZtsel           ', 'list                ', '获得数据                      ', 'about:blank                                                                                         ', '获得数据                                          ', 'V2.1.btoo ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('btooZtsel           ', 'next                ', '执行任务                      ', 'about:blank                                                                                         ', '执行任务                                          ', 'V2.1.btoo ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('btooYwlx            ', 'upt                 ', '更新更新                      ', 'about:blank                                                                                         ', '添加更新                                          ', 'V2.1.btoo ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('btooYwlx            ', 'del                 ', '删除                          ', 'about:blank                                                                                         ', '删除                                              ', 'V2.1.btoo ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('btooYwlx            ', 'add                 ', '添加更新                      ', 'about:blank                                                                                         ', '添加更新                                          ', 'V2.1.btoo ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('btooYwlx            ', 'list                ', '获得数据                      ', 'about:blank                                                                                         ', '获得数据                                          ', 'V2.1.btoo ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('btooYwlx            ', 'def                 ', '查询                          ', 'app/agent/btoo/btooywlx.jsp                                                                         ', '默认                                              ', 'V2.1.btoo ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('btooYwbh            ', 'def                 ', '查询                          ', 'app/agent/btoo/btooywbh.jsp                                                                         ', '默认                                              ', 'V2.1.btoo ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('btooYwbh            ', 'list                ', '获得数据                      ', 'about:blank                                                                                         ', '获得数据                                          ', 'V2.1.btoo ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('btooYwbh            ', 'add                 ', '添加更新                      ', 'about:blank                                                                                         ', '添加更新                                          ', 'V2.1.btoo ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('btooYwbh            ', 'del                 ', '删除                          ', 'about:blank                                                                                         ', '删除                                              ', 'V2.1.btoo ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('btooYwbh            ', 'upt                 ', '更新更新                      ', 'about:blank                                                                                         ', '添加更新                                          ', 'V2.1.btoo ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('btooStepcfg         ', 'def                 ', '查询                          ', 'app/agent/btoo/btoostepcfg.jsp                                                                      ', '默认                                              ', 'V2.1.btoo ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('btooStepcfg         ', 'list                ', '获得数据                      ', 'about:blank                                                                                         ', '获得数据                                          ', 'V2.1.btoo ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('btooStepcfg         ', 'add                 ', '添加更新                      ', 'about:blank                                                                                         ', '添加更新                                          ', 'V2.1.btoo ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('btooStepcfg         ', 'del                 ', '删除                          ', 'about:blank                                                                                         ', '删除                                              ', 'V2.1.btoo ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('btooStepcfg         ', 'upt                 ', '更新更新                      ', 'about:blank                                                                                         ', '添加更新                                          ', 'V2.1.btoo ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('btooZtsel           ', 'def                 ', '默认                          ', 'app/agent/btoo/btooztsel.jsp                                                                        ', '默认                                              ', 'V2.1.btoo ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('btooYwbh            ', 'ywxxByYwbh          ', '获取业务信息                  ', 'about:blank                                                                                         ', '获取业务信息                                      ', 'V2.1.btoo ', NULL, NULL, NULL);


INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(302, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.btoo ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(302, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.btoo ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(302, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.btoo ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(302, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.btoo ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(301, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.btoo ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(301, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.btoo ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(301, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.btoo ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(301, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.btoo ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(303, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.btoo ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(303, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.btoo ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(303, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.btoo ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(303, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.btoo ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);


INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(301, 'qtywbh              ', '批转联业务编号                ', '5', '1 ', '1', NULL, NULL, 'com.hundsun.agent.web.btoo.sendUtil.BtooywbhSend                                                    ', 'V2.1.btoo ', '批转联业务编号                                                                                      ', '/btoo/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(301, 'qtbz                ', '启停标志                      ', '0', '2 ', '1', NULL, NULL, 'agent_send_qtbz                                                                                     ', 'V2.1.btoo ', '启停标志                                                                                            ', '/btoo/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(302, 'ywbh                ', '业务编号                      ', '5', '1 ', '1', NULL, NULL, 'com.hundsun.agent.web.btoo.sendUtil.BtooywbhSend                                                    ', 'V2.1.btoo ', '业务编号                                                                                            ', '/btoo/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(302, 'kkrq                ', '扣款日期                      ', '3', '2 ', '0', NULL, NULL, NULL, 'V2.1.btoo ', '扣款日期                                                                                            ', '/btoo/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(303, 'ywbh                ', '业务编号                      ', '5', '1 ', '1', NULL, NULL, 'com.hundsun.agent.web.btoo.sendUtil.BtooywbhSend                                                    ', 'V2.1.btoo ', '业务编号                                                                                            ', '/btoo/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(303, 'czbz                ', '操作标志                      ', '0', '4 ', '1', NULL, NULL, 'btoo_czbz                                                                                           ', 'V2.1.btoo ', '操作标志                                                                                            ', '/btoo/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(303, 'ptrq                ', '扣款日期                      ', '3', '2 ', '1', NULL, NULL, NULL, 'V2.1.btoo ', '扣款日期                                                                                            ', '/btoo/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(303, 'ptlsh               ', '扣款流水号                    ', '1', '3 ', '1', NULL, NULL, NULL, 'V2.1.btoo ', '扣款流水号                                                                                          ', '/btoo/req/                    ', NULL, NULL, NULL, NULL, NULL);


INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(303, '920903                        ', '批转联任务中断/继续/终止                          ', '1', NULL, 'admin               ', '00000               ', '100                 ', 'V2.1.btoo ', NULL, 'btooXml                       ', 'btooFile                      ', NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(301, '920901                        ', '批转联业务启停                                    ', '1', '                    ', 'yd                  ', '00000               ', '100                 ', 'V2.1.btoo ', '', 'btooXml                       ', 'btooFile                      ', '                                                                                                                                                      ', '                                                                                                                                                      ', NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(302, '920902                        ', '批转联任务发起                                    ', '1', NULL, 'admin               ', '00000               ', '100                 ', 'V2.1.btoo ', NULL, 'btooXml                       ', 'btooFile                      ', NULL, NULL, NULL, NULL, NULL, NULL);


INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('btoo                          ', '/                             ', 1, '批转联管理                    ', '批转联管理                                        ', '0', 'sendPz              ', '1', 'V2.1.btoo ', NULL, '900310000000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('btoo_yw                       ', 'btoo                          ', 2, '业务配置                      ', '业务配置                                          ', '0', 'sendPz              ', '1', 'V2.1.btoo ', NULL, '900311000000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('btoo_ywlx                     ', 'btoo_yw                       ', 3, '业务类型配置                  ', '业务类型配置                                      ', '1', 'btooYwlx            ', '0', 'V2.1.btoo ', NULL, '900311100000        ', '0', 'agent     ', '                              ', NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('btoo_ywbh                     ', 'btoo_yw                       ', 3, '业务编号配置                  ', '业务编号配置                                      ', '1', 'btooYwbh            ', '1', 'V2.1.btoo ', NULL, '900311300000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('btoo_stepcfg                  ', 'btoo_yw                       ', 3, '步点服务配置                  ', '步点服务配置                                      ', '1', 'btooStepcfg         ', '1', 'V2.1.btoo ', NULL, '900311200000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('btoo_ywgl                     ', 'btoo                          ', 2, '业务管理                      ', '业务管理                                          ', '0', 'sendPz              ', '1', 'V2.1.btoo ', NULL, '900312000000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('btoo_ywqt                     ', 'btoo_ywgl                     ', 3, '业务启停                      ', '业务启停                                          ', '1', 'send                ', '0', 'V2.1.btoo ', '                                        ', '900312100000        ', '0', 'agent     ', '                              ', 'send_id=301                                                                                         ', NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('btoo_pzlztsel                 ', 'btoo_ywgl                     ', 3, '状态查询                      ', '状态查询                                          ', '1', 'btooZtsel           ', '1', 'V2.1.btoo ', NULL, '900312200000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('btoo_pzlrwfq                  ', 'btoo_ywgl                     ', 3, '任务发起                      ', '任务发起                                          ', '1', 'send                ', '1', 'V2.1.btoo ', NULL, '900312300000        ', '0', 'agent     ', NULL, 'send_id=302                                                                                         ', NULL);


INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('btoo_ywzt                     ', '业务状态                      ', '0                             ', '有效                          ', 'V2.1.btoo ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('btoo_ywzt                     ', '业务状态                      ', '1                             ', '无效                          ', 'V2.1.btoo ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('btoo_czbz                     ', '操作标志                      ', '1                             ', '终止                          ', 'V2.1.btoo ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('btoo_czbz                     ', '操作标志                      ', '2                             ', '暂停                          ', 'V2.1.btoo ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('btoo_czbz                     ', '操作标志                      ', '3                             ', '继续                          ', 'V2.1.btoo ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('btoo_kkzq                     ', '扣款周期                      ', '0                             ', '无周期（每次都扣款）          ', 'V2.1.btoo ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('btoo_kkzq                     ', '扣款周期                      ', '3                             ', '月                            ', 'V2.1.btoo ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('btoo_kkzq                     ', '扣款周期                      ', '4                             ', '年                            ', 'V2.1.btoo ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('btoo_clfs                     ', '处理方式                      ', '1                             ', '手工                          ', 'V2.1.btoo ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('btoo_clfs                     ', '处理方式                      ', '2                             ', '定时                          ', 'V2.1.btoo ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('btoo_stepType                 ', '步点类型                      ', '0                             ', '默认                          ', 'V2.1.btoo ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('btoo_stepType                 ', '步点类型                      ', '1                             ', '自定义                        ', 'V2.1.btoo ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('btoo_svrType                  ', '服务类型                      ', '0                             ', '流程                          ', 'V2.1.btoo ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('btoo_svrType                  ', '服务类型                      ', '1                             ', '交易                          ', 'V2.1.btoo ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('btoo_qdbd                     ', '操作步点                      ', '0                             ', '数据预处理                    ', 'V2.1.btoo ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('btoo_qdbd                     ', '操作步点                      ', '1                             ', '数据处理                      ', 'V2.1.btoo ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('btoo_qdbd                     ', '操作步点                      ', '2                             ', '数据后处理                    ', 'V2.1.btoo ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('btoo_ywyxbz                   ', '业务运行标志                  ', '0                             ', '结束                          ', 'V2.1.btoo ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('btoo_ywyxbz                   ', '业务运行标志                  ', '1                             ', '终止                          ', 'V2.1.btoo ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('btoo_ywyxbz                   ', '业务运行标志                  ', '2                             ', '暂停                          ', 'V2.1.btoo ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('btoo_ywyxbz                   ', '业务运行标志                  ', '9                             ', '在处理中                      ', 'V2.1.btoo ', NULL);


INSERT INTO T_SEND_SERVER(ID, SERNAME, IP, PORT, TYPEID, CSTIME)
  VALUES('btooXml                       ', 'btoo报文服务                                      ', '192.168.53.66       ', 13009, '0', 30);
INSERT INTO T_SEND_SERVER(ID, SERNAME, IP, PORT, TYPEID, CSTIME)
  VALUES('btooFile                      ', 'btoo文件服务                                      ', '192.168.53.66       ', 33345, '1', 60);
