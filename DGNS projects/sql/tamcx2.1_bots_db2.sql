 
delete from T_TRAN where version='V2.1.bots';

delete from T_SUB_TRAN where version='V2.1.bots';

delete from T_SEND_RETURN where version='V2.1.bots';

delete from T_SEND_COND where version='V2.1.bots';

delete from T_SENDINFO where version='V2.1.bots';

delete from T_MENU where version='V2.1.bots';

delete from T_DICT where version='V2.1.bots';

delete from T_SEND_SERVER where id like 'bots%';
 

INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsGapsdown        ', '从GAPS获得文件                ', '0', 'com.hundsun.agent.web.bots.ctl.GapsDownCtl                                                          ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsWbwjdj          ', '外部文件登记                  ', '1', 'com.hundsun.agent.web.bots.ctl.BotsWbwjdjCtl                                                        ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywbd          ', '批量业务单步点操作            ', '1', 'com.hundsun.agent.web.bots.ctl.BotsPlywbdCtl                                                        ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsAuditingpara    ', '审核函数参数登记              ', '1', 'com.hundsun.agent.web.bots.ctl.BotsAuditingparaCtl                                                  ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywbdmx        ', '批量业务步点明细              ', '1', 'com.hundsun.agent.web.bots.ctl.BotsPlywbdmxCtl                                                      ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsAuditingfunc    ', '批量审核配置                  ', '1', 'com.hundsun.agent.web.bots.ctl.BotsAuditingfuncCtl                                                  ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlrwSel         ', '批量查询                      ', '1', 'com.hundsun.agent.web.bots.ctl.BotsPlywSelCtl                                                       ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywmx          ', '批量业务明细                  ', '1', 'com.hundsun.agent.web.bots.ctl.BatchPlywmxCtl                                                       ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsEncry           ', '批量加解密注册                ', '1', 'com.hundsun.agent.web.bots.ctl.BotsEncryptregCtl                                                    ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywbh          ', '批量业务编号                  ', '1', 'com.hundsun.agent.web.bots.ctl.BotsPlywbhCtl                                                        ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsFile            ', '批量文件配置                  ', '1', 'com.hundsun.agent.web.bots.ctl.BotsFileCtl                                                          ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPzdc            ', '批量配置导出                  ', '1', 'com.hundsun.agent.web.bots.ctl.BotsPzdcCtl                                                          ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsWbwjdjSH        ', '审核外部文件                  ', '1', 'com.hundsun.agent.web.bots.ctl.BotsWbwjdjSHCtl                                                      ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywbdcx        ', '批量业务撤消操作              ', '1', 'com.hundsun.agent.web.bots.ctl.BotsPlywbdcxCtl                                                      ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsAuditingreg     ', '审核函数登记                  ', '1', 'com.hundsun.agent.web.bots.ctl.BotsAuditingregCtl                                                   ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsTablereg        ', '注册表结构                    ', '1', 'com.hundsun.agent.web.bots.ctl.BotsTableregCtl                                                      ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsFlowcfg         ', '批量流程配置                  ', '1', 'com.hundsun.agent.web.bots.ctl.BotsFlowcfgCtl                                                       ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlrw            ', '批量任务                      ', '1', 'com.hundsun.agent.web.bots.ctl.BotsPlrwCtl                                                          ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsRunctrl         ', '批量业务运行控制              ', '1', 'com.hundsun.agent.web.bots.ctl.BotsRunctrlCtl                                                       ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywlx          ', '批量业务类型                  ', '1', 'com.hundsun.agent.web.bots.ctl.BotsPlywlxCtl                                                        ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsKeyctrl         ', '密钥控制管理                  ', '1', 'com.hundsun.agent.web.bots.ctl.BotsKeyctrlCtl                                                       ', 'V2.1.bots ', '                              ', '                              ', '                              ');
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsMapinfo         ', '表影射                        ', '1', 'com.hundsun.agent.web.bots.ctl.BotsMapinfoCtl                                                       ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywbdcz        ', '批量业务冲正操作              ', '1', 'com.hundsun.agent.web.bots.ctl.BotsPlywbdczCtl                                                      ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPllpwjcx        ', '批量来盘文件录入撤销          ', '1', 'com.hundsun.agent.web.bots.ctl.BotsWbwjdjcxCtl                                                      ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsZJMapsinfo      ', '主机映射                      ', '1', 'com.hundsun.agent.web.bots.ctl.BotsZJMapinfoCtl                                                     ', 'V2.1.bots ', '                              ', '                              ', '                              ');
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsRespmap         ', '响应码映射                    ', '0', 'com.hundsun.agent.web.bots.ctl.BotsRespmapCtl                                                       ', 'V2.1.bots ', NULL, NULL, NULL);


INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsAuditingreg     ', 'del                 ', '删除                          ', 'about:blank                                                                                         ', '删除                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsAuditingreg     ', 'def                 ', '查询                          ', 'app/agent/bots/botsauditingreg.jsp                                                                  ', '默认                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsAuditingfunc    ', 'list                ', '获得审核                      ', 'about:blank                                                                                         ', '获得数据                                          ', 'V2.1.bots ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsAuditingreg     ', 'delpara             ', '删除参数                      ', 'about:blank                                                                                         ', '删除                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsAuditingreg     ', 'uptpara             ', '更新参数                      ', 'about:blank                                                                                         ', '更新                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsAuditingreg     ', 'addpara             ', '添加参数                      ', 'about:blank                                                                                         ', '添加                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsAuditingreg     ', 'listpara            ', '获得参数数据                  ', 'about:blank                                                                                         ', '获得数据                                          ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsAuditingfunc    ', 'addhs               ', '追加函数                      ', 'about:blank                                                                                         ', '追加步点                                          ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsAuditingfunc    ', 'del                 ', '删除                          ', 'about:blank                                                                                         ', '删除                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsAuditingfunc    ', 'upt                 ', '更新                          ', 'about:blank                                                                                         ', '更新                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsWbwjdjSH        ', 'list                ', '获得数据                      ', 'about:blank                                                                                         ', '获得数据                                          ', 'V2.1.bots ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsWbwjdjSH        ', 'upt                 ', '执行审核                      ', 'about:blank                                                                                         ', '执行审核                                          ', 'V2.1.bots ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsWbwjdjSH        ', 'def                 ', '查询                          ', 'app/agent/bots/botswbwjdjSH.jsp                                                                     ', '查询                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywbd          ', 'down                ', '下载回盘文件                  ', 'about:blank                                                                                         ', '下载回盘文件                                      ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywbd          ', 'addyw               ', '追加获取数据                  ', 'about:blank                                                                                         ', '追加获取数据                                      ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywbd          ', 'selyw               ', '查询获取数据业务              ', 'about:blank                                                                                         ', '查询获取数据业务                                  ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsTablereg        ', 'addindex            ', '添加索引                      ', 'about:blank                                                                                         ', '添加索引                                          ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsWbwjdj          ', 'def                 ', '查询                          ', 'app/agent/bots/botswbwjdj.jsp                                                                       ', '默认                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsEncry           ', 'add                 ', '添加维护                      ', 'about:blank                                                                                         ', '添加                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsTablereg        ', 'listindex           ', '获得索引                      ', 'about:blank                                                                                         ', '获得索引                                          ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsTablereg        ', 'delindex            ', '删除索引                      ', 'about:blank                                                                                         ', '删除索引                                          ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsTablereg        ', 'create              ', '创建表                        ', 'about:blank                                                                                         ', '创建表                                            ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsWbwjdj          ', 'upload              ', '申请录入                      ', 'about:blank                                                                                         ', '申请录入                                          ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywbdcz        ', 'run                 ', '冲正                          ', 'about:blank                                                                                         ', '批次状态查询                                      ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsMapinfo         ', 'mapdel              ', '删除映射                      ', 'about:blank                                                                                         ', '删除                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsMapinfo         ', 'mapupt              ', '更新映射                      ', 'about:blank                                                                                         ', '添加                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsMapinfo         ', 'maplist             ', '查询映射                      ', 'about:blank                                                                                         ', '查询数据                                          ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsRunctrl         ', 'list                ', '获得数据                      ', 'about:blank                                                                                         ', '获得数据                                          ', 'V2.1.bots ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsRunctrl         ', 'def                 ', '查询                          ', 'app/agent/bots/botsrunctrl.jsp                                                                      ', '默认                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsRunctrl         ', 'maplist             ', '获得列映射数据                ', 'about:blank                                                                                         ', '获得数据                                          ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsRunctrl         ', 'mapadd              ', '添加更新列映射数据            ', 'about:blank                                                                                         ', '添加更新列映射数据                                ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywmx          ', 'def                 ', '查询                          ', 'app/agent/bots/botsplywmx.jsp                                                                       ', '默认                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywmx          ', 'list                ', '获得数据                      ', 'about:blank                                                                                         ', '获得数据                                          ', 'V2.1.bots ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywbd          ', 'def                 ', '查询                          ', 'app/agent/bots/botsplywbd.jsp                                                                       ', '默认                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywbd          ', 'send                ', '单步点交易                    ', 'about:blank                                                                                         ', '单步点交易                                        ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywbd          ', 'list                ', '获得数据                      ', 'about:blank                                                                                         ', '获得数据                                          ', 'V2.1.bots ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywbd          ', 'run                 ', '批次状态查询                  ', 'about:blank                                                                                         ', '批次状态查询                                      ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsTablereg        ', 'list                ', '获得数据                      ', 'about:blank                                                                                         ', '获得数据                                          ', 'V2.1.bots ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsTablereg        ', 'del                 ', '删除                          ', 'about:blank                                                                                         ', '删除                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlrw            ', 'addyw               ', '添加业务监听                  ', 'about:blank                                                                                         ', '添加业务监听                                      ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsTablereg        ', 'add                 ', '添加更新                      ', 'about:blank                                                                                         ', '添加更新                                          ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlrw            ', 'selyw               ', '查询可以监听的业务            ', 'about:blank                                                                                         ', '查询可以监听的业务                                ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsFile            ', 'def                 ', '查询                          ', 'app/agent/bots/botsfile.jsp                                                                         ', '默认                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsFile            ', 'list                ', '获得文件类型数据              ', 'about:blank                                                                                         ', '获得数据                                          ', 'V2.1.bots ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsFile            ', 'add                 ', '添加更新文件类型              ', 'about:blank                                                                                         ', '添加更新文件类型                                  ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsFile            ', 'del                 ', '删除文件类型                  ', 'about:blank                                                                                         ', '删除文件类型                                      ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsFlowcfg         ', 'def                 ', '查询                          ', 'app/agent/bots/botsflowcfg.jsp                                                                      ', '默认                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsFlowcfg         ', 'add                 ', '添加                          ', 'about:blank                                                                                         ', '添加                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsFlowcfg         ', 'upt                 ', '更新                          ', 'about:blank                                                                                         ', '更新                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsWbwjdj          ', 'del                 ', '删除                          ', 'about:blank                                                                                         ', '删除                                              ', 'V2.1.bots ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsWbwjdj          ', 'mv                  ', '授权删除                      ', 'about:blank                                                                                         ', '授权删除                                          ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsTablereg        ', 'set                 ', '套用表                        ', 'about:blank                                                                                         ', '套用表                                            ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsAuditingfunc    ', 'add                 ', '添加                          ', 'about:blank                                                                                         ', '添加                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsAuditingfunc    ', 'def                 ', '查询                          ', 'app/agent/bots/botsauditingfunc.jsp                                                                 ', '默认                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsAuditingfunc    ', 'dict                ', '获得函数模型                  ', 'about:blank                                                                                         ', '获得步点模型                                      ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsAuditingfunc    ', 'tree                ', '获得审核树                    ', 'about:blank                                                                                         ', '获得流程树                                        ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsFile            ', 'set                 ', '文件套用                      ', 'about:blank                                                                                         ', '文件套用                                          ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywbdmx        ', 'def                 ', '查询                          ', 'app/agent/bots/botsplywbdmx.jsp                                                                     ', '默认                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywbdmx        ', 'list                ', '获得数据                      ', 'about:blank                                                                                         ', '获得数据                                          ', 'V2.1.bots ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsFlowcfg         ', 'set                 ', '套用模板                      ', 'about:blank                                                                                         ', '套用模板                                          ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsRunctrl         ', 'set                 ', '套用模板                      ', 'about:blank                                                                                         ', '套用模板                                          ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywbdcx        ', 'run                 ', '撤消                          ', 'about:blank                                                                                         ', '批次状态查询                                      ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywbdcx        ', 'list                ', '获得数据                      ', 'about:blank                                                                                         ', '获得数据                                          ', 'V2.1.bots ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywbdcx        ', 'def                 ', '查询                          ', 'app/agent/bots/botsplywbdcx.jsp                                                                     ', '默认                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPzdc            ', 'def                 ', '默认                          ', 'app/agent/bots/botspzdc.jsp                                                                         ', '默认                                              ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPzdc            ', 'down                ', '导出                          ', 'app/agent/bots/botspzdc.jsp                                                                         ', '导出                                              ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsEncry           ', 'del                 ', '删除                          ', 'about:blank                                                                                         ', '删除                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsFlowcfg         ', 'stepupt             ', '更新属性                      ', 'about:blank                                                                                         ', '更新                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsFlowcfg         ', 'stepset             ', '使用系统属性                  ', 'about:blank                                                                                         ', '使用系统属性                                      ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsFlowcfg         ', 'steplist            ', '获得数据属性                  ', 'about:blank                                                                                         ', '获得数据                                          ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsFlowcfg         ', 'stepdel             ', '删除                          ', 'about:blank                                                                                         ', '删除                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsFlowcfg         ', 'stepattLst          ', '获得系统属性                  ', 'about:blank                                                                                         ', '获得系统属性                                      ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsFlowcfg         ', 'stepadd             ', '添加属性                      ', 'about:blank                                                                                         ', '添加                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlrwSel         ', 'def                 ', '查询                          ', 'app/agent/bots/botsplrwsel.jsp                                                                      ', '默认                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlrwSel         ', 'list                ', '查询                          ', 'about:blank                                                                                         ', '查询                                              ', 'V2.1.bots ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsFlowcfg         ', 'addbd               ', '追加步点                      ', 'about:blank                                                                                         ', '追加步点                                          ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsRunctrl         ', 'isIn                ', '映射标识是否存在              ', 'about:blank                                                                                         ', '映射标识是否存在                                  ', 'V2.1.bots ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywbh          ', 'del                 ', '删除                          ', 'about:blank                                                                                         ', '删除                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywbh          ', 'list                ', '获得数据                      ', 'about:blank                                                                                         ', '获得数据                                          ', 'V2.1.bots ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywbh          ', 'def                 ', '查询                          ', 'app/agent/bots/botsplywbh.jsp                                                                       ', '默认                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlrw            ', 'next                ', '断点继续                      ', 'about:blank                                                                                         ', '断点继续                                          ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlrw            ', 'runStop             ', '运行/停止                     ', 'about:blank                                                                                         ', '运行/停止                                         ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlrw            ', 'load                ', '步点等待参数                  ', 'about:blank                                                                                         ', '步点等待参数                                      ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlrw            ', 'upload              ', '步点参数交易                  ', 'about:blank                                                                                         ', '步点参数交易                                      ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsFlowcfg         ', 'tree                ', '获得流程树                    ', 'about:blank                                                                                         ', '获得流程树                                        ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsFlowcfg         ', 'dict                ', '获得模型                      ', 'about:blank                                                                                         ', '获得步点模型                                      ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsRunctrl         ', 'del                 ', '删除                          ', 'about:blank                                                                                         ', '删除                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsRunctrl         ', 'add                 ', '添加更新                      ', 'about:blank                                                                                         ', '添加更新                                          ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywbh          ', 'add                 ', '添加更新                      ', 'about:blank                                                                                         ', '添加更新                                          ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsFlowcfg         ', 'list                ', '获得数据                      ', 'about:blank                                                                                         ', '获得数据                                          ', 'V2.1.bots ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsTablereg        ', 'def                 ', '查询                          ', 'app/agent/bots/botstablereg.jsp                                                                     ', '默认                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('ViewYbLs            ', 'def                 ', '医保流水默认界面              ', 'app/bots/sb/viewYbLs.jsp                                                                            ', '医保流水默认界面                                  ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('ViewYbLs            ', 'qry                 ', '医保流水查询                  ', 'app/bots/sb/viewYbLs.jsp                                                                            ', '医保流水查询                                      ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('ViewYbLs            ', 'down                ', '医保错误文件下载              ', 'app/bots/sb/viewYbLs.jsp                                                                            ', '医保错误文件下载                                  ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('szSB                ', 'test                ', '上账状态查看                  ', 'app/bots/sb/szSB.jsp                                                                                ', '上账状态查看                                      ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('initSB              ', 'def                 ', '初始默认界面                  ', 'app/bots/sb/initSB.jsp                                                                              ', '初始默认界面                                      ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('initSB              ', 'new                 ', '初始状态刷新                  ', 'app/bots/sb/initSB.jsp                                                                              ', '初始状态刷新                                      ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('initSB              ', 'upfile              ', '初始上传文件                  ', 'app/bots/sb/initSB.jsp                                                                              ', '初始上传文件                                      ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('initSB              ', 'test                ', '初始状态查看                  ', 'app/bots/sb/initSB.jsp                                                                              ', '初始状态查看                                      ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('updateSB            ', 'def                 ', '更新默认界面                  ', 'app/bots/sb/updateSB.jsp                                                                            ', '更新默认界面                                      ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('updateSB            ', 'new                 ', '医保更新状态刷新              ', 'app/bots/sb/updateSB.jsp                                                                            ', '医保更新状态刷新                                  ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('updateSB            ', 'upfile              ', '医保更新数据上传              ', 'app/bots/sb/updateSB.jsp                                                                            ', '医保更新数据上传                                  ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('updateSB            ', 'test                ', '医保更新状态查看              ', 'app/bots/sb/updateSB.jsp                                                                            ', '医保更新状态查看                                  ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('updateSB            ', 'down                ', '下载文件                      ', 'app/bots/sb/updateSB.jsp                                                                            ', '下载文件                                          ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('szSB                ', 'def                 ', '上账默认界面                  ', 'app/bots/sb/szSB.jsp                                                                                ', '上账默认界面                                      ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('szSB                ', 'new                 ', '上账状态刷新                  ', 'app/bots/sb/szSB.jsp                                                                                ', '上账状态刷新                                      ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('szSB                ', 'upfile              ', '上账文件上传                  ', 'app/bots/sb/szSB.jsp                                                                                ', '上账文件上传                                      ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('szSB                ', 'down                ', '医保错误文件下载              ', 'app/bots/sb/szSB.jsp                                                                                ', '医保错误文件下载                                  ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsTablereg        ', 'listtable           ', '查询表名                      ', 'about:blank                                                                                         ', '查询表名                                          ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsTablereg        ', 'addtable            ', '添加表名                      ', 'about:blank                                                                                         ', '添加表名                                          ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsTablereg        ', 'deltable            ', '删除表名                      ', 'about:blank                                                                                         ', '删除表名                                          ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsWbwjdj          ', 'load                ', '获得运行属性                  ', 'about:blank                                                                                         ', '获得运行属性                                      ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsKeyctrl         ', 'def                 ', '查询                          ', 'app/agent/bots/botskeyctrl.jsp                                                                      ', '查询                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsKeyctrl         ', 'add                 ', '添加                          ', 'about:blank                                                                                         ', '添加                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsKeyctrl         ', 'down                ', '密钥导出                      ', 'about:blank                                                                                         ', '密钥导出                                          ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsKeyctrl         ', 'yes                 ', '审核通过                      ', 'about:blank                                                                                         ', '审核通过                                          ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsKeyctrl         ', 'list                ', '获得数据                      ', 'about:blank                                                                                         ', '获得数据                                          ', 'V2.1.bots ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsTablereg        ', 'order               ', '列排序                        ', 'about:blank                                                                                         ', '列排序                                            ', 'V2.1.bots ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsFlowcfg         ', 'del                 ', '删除                          ', 'about:blank                                                                                         ', '删除                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsMapinfo         ', 'def                 ', '默认                          ', 'app/agent/bots/botsmapinfo.jsp                                                                      ', '默认                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsMapinfo         ', 'list                ', '查询数据                      ', 'about:blank                                                                                         ', '查询数据                                          ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsMapinfo         ', 'add                 ', '添加                          ', 'about:blank                                                                                         ', '添加                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsMapinfo         ', 'del                 ', '删除                          ', 'about:blank                                                                                         ', '删除                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywbdcz        ', 'def                 ', '查询                          ', 'app/agent/bots/botsplywbdcz.jsp                                                                     ', '默认                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywbdcz        ', 'list                ', '获得数据                      ', 'about:blank                                                                                         ', '获得数据                                          ', 'V2.1.bots ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywlx          ', 'del                 ', '删除                          ', 'about:blank                                                                                         ', '删除                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywlx          ', 'add                 ', '添加更新                      ', 'about:blank                                                                                         ', '添加更新                                          ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywlx          ', 'list                ', '获得数据                      ', 'about:blank                                                                                         ', '获得数据                                          ', 'V2.1.bots ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywlx          ', 'def                 ', '查询                          ', 'app/agent/bots/botsplywlx.jsp                                                                       ', '默认                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsRunctrl         ', 'mapdel              ', '删除列映射                    ', 'about:blank                                                                                         ', '删除                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsFile            ', 'delcolumn           ', '删除文件列                    ', 'about:blank                                                                                         ', '删除文件类型                                      ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsFile            ', 'addcolumn           ', '添加更新文件列                ', 'about:blank                                                                                         ', '添加更新文件列                                    ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsFile            ', 'listcolumn          ', '获得文件列数据                ', 'about:blank                                                                                         ', '获得数据                                          ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsFile            ', 'delsort             ', '删除文件分类                  ', 'about:blank                                                                                         ', '删除文件类型                                      ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsFile            ', 'addsort             ', '添加更新文件分类              ', 'about:blank                                                                                         ', '添加更新文件分类                                  ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsFile            ', 'listsort            ', '获得文件分类数据              ', 'about:blank                                                                                         ', '获得数据                                          ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywbh          ', 'ljkzsel             ', '查询联机控制                  ', 'about:blank                                                                                         ', '查询联机控制                                      ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywbh          ', 'ljkzupt             ', '更新联机控制                  ', 'about:blank                                                                                         ', '更新联机控制                                      ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlrw            ', 'def                 ', '查询                          ', 'app/agent/bots/botsplrw.jsp                                                                         ', '默认                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlrw            ', 'list                ', '获得数据                      ', 'about:blank                                                                                         ', '获得数据                                          ', 'V2.1.bots ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlrw            ', 'send                ', '交易                          ', 'about:blank                                                                                         ', '交易                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsFile            ', 'ordercolumn         ', '列排序                        ', 'about:blank                                                                                         ', '列排序                                            ', 'V2.1.bots ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsFile            ', 'tree                ', '文件结构树                    ', 'about:blank                                                                                         ', '文件结构树                                        ', 'V2.1.bots ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsWbwjdj          ', 'list                ', '获得数据                      ', 'about:blank                                                                                         ', '获得数据                                          ', 'V2.1.bots ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsAuditingfunc    ', 'cfgupt              ', '更新参数信息                  ', 'about:blank                                                                                         ', '更新                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsAuditingfunc    ', 'cfglist             ', '获得参数信息                  ', 'about:blank                                                                                         ', '删除                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsEncry           ', 'def                 ', '查询                          ', 'app/agent/bots/botsencryptreg.jsp                                                                   ', '默认                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsEncry           ', 'list                ', '获得数据                      ', 'about:blank                                                                                         ', '获得数据                                          ', 'V2.1.bots ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsAuditingreg     ', 'list                ', '获得数据                      ', 'about:blank                                                                                         ', '获得数据                                          ', 'V2.1.bots ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsAuditingreg     ', 'add                 ', '添加                          ', 'about:blank                                                                                         ', '添加                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsAuditingreg     ', 'upt                 ', '更新                          ', 'about:blank                                                                                         ', '更新                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsWbwjdjSH        ', 'down                ', '下载                          ', 'about:blank                                                                                         ', '下载                                              ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPllpwjcx        ', 'def                 ', '默认页面                      ', 'app/agent/bots/botswbwjdjcx.jsp                                                                     ', '默认页面                                          ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPllpwjcx        ', 'run                 ', '执行                          ', 'app/agent/bots/botswbwjdjcx.jsp                                                                     ', '执行                                              ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPllpwjcx        ', 'list                ', '查询                          ', 'app/agent/bots/botswbwjdjcx.jsp                                                                     ', '查询                                              ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsZJMapsinfo      ', 'def                 ', '默认页面                      ', 'app/agent/bots/botsZJfilemap.jsp                                                                    ', '默认页面                                          ', 'V2.1.bots ', '01                            ', '                              ', '                              ');
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsZJMapsinfo      ', 'list                ', '查询                          ', 'list                                                                                                ', '查询                                              ', 'V2.1.bots ', '01                            ', '                              ', '                              ');
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsZJMapsinfo      ', 'add                 ', '添加                          ', 'add                                                                                                 ', '添加                                              ', 'V2.1.bots ', '01                            ', '                              ', '                              ');
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsZJMapsinfo      ', 'del                 ', '删除                          ', 'del                                                                                                 ', '删除                                              ', 'V2.1.bots ', '01                            ', '                              ', '                              ');
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsZJMapsinfo      ', 'upt                 ', '更新                          ', 'upt                                                                                                 ', '更新                                              ', 'V2.1.bots ', '01                            ', '                              ', '                              ');
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsZJMapsinfo      ', 'maplist             ', '查询映射列                    ', 'maplist                                                                                             ', '查询映射列信息                                    ', 'V2.1.bots ', '01                            ', '                              ', '                              ');
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsZJMapsinfo      ', 'mapupt              ', '更新映射列                    ', 'mapupt                                                                                              ', '更新映射列信息                                    ', 'V2.1.bots ', '01                            ', '                              ', '                              ');
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsZJMapsinfo      ', 'mapdel              ', '删除映射列信息                ', 'mapdel                                                                                              ', '删除映射列                                        ', 'V2.1.bots ', '01                            ', '                              ', '                              ');
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsRespmap         ', 'def                 ', '默认                          ', 'app/agent/bots/botsRespMap.jsp                                                                      ', '默认                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsRespmap         ', 'add                 ', '维护                          ', 'about:blank                                                                                         ', '维护                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsRespmap         ', 'del                 ', '删除                          ', 'about:blank                                                                                         ', '删除                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsTablereg        ', 'rzpz                ', '日终任务配置                  ', 'about:blank                                                                                         ', '日终任务配置                                      ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsRespmap         ', 'list                ', '查询                          ', 'about:blank                                                                                         ', '查询                                              ', 'V2.1.bots ', NULL, NULL, NULL);


INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(114, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(114, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(114, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(113, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(113, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(113, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(109, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(109, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(109, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(109, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(110, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(110, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(110, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(110, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(113, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(109, 'detailnum           ', '记录数                        ', '3 ', '0', NULL, '/batch/resp/        ', '0', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(109, 'ywbh                ', '业务编号                      ', '1 ', '0', NULL, NULL, '0', NULL, 'V2.1.bots ', NULL, '1                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(109, 'ptpch               ', '平台批次号                    ', '2 ', '0', NULL, NULL, '0', NULL, 'V2.1.bots ', NULL, '1                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(109, 'status              ', '批次状态                      ', '3 ', '0', NULL, NULL, '0', NULL, 'V2.1.bots ', NULL, '1                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(109, 'memo                ', '备注                          ', '4 ', '0', NULL, NULL, '0', NULL, 'V2.1.bots ', NULL, '1                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(101, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(114, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(101, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(101, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(100, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(100, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(100, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(100, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(101, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(102, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(102, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(102, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(102, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(108, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(108, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(108, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(108, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(107, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(107, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(107, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(107, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(106, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(106, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(106, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(106, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(105, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(105, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(105, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(105, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(104, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(104, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(104, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(104, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(103, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(103, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(103, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(103, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);


INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(103, 'nextflag            ', '执行后续步点标志              ', '1', '4 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(103, 'djlsh               ', '登记流水号                    ', '1', '3 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(101, 'dqbd                ', '当前步点                      ', '1', '4 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(110, 'ywbh                ', '业务编号                      ', '1', '1 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(110, 'pkrq                ', '批扣日期                      ', '1', '2 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(110, 'ptpch               ', '平台批次号                    ', '1', '3 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(109, 'ptpch               ', '平台批次号                    ', '1', '3 ', '1', '                                                                                                    ', '                    ', '                                                                                                    ', 'V2.1.bots ', '                                                                                                    ', '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(109, 'pkrq                ', '批扣日期                      ', '3', '2 ', '1', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(113, 'djlsh               ', '登记流水号                    ', '7', '3 ', '1', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(114, 'pkrq                ', '批扣日期                      ', '1', '2 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(114, 'ywbh                ', '业务编号                      ', '1', '1 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(101, 'ywbh                ', '业务编号                      ', '1', '1 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(101, 'pkrq                ', '批扣日期                      ', '1', '2 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(105, 'nextflag            ', '执行后续步点标志              ', '1', '4 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(105, 'ptpch               ', '平台批次号                    ', '1', '3 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(105, 'pkrq                ', '批扣日期                      ', '1', '2 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(105, 'ywbh                ', '业务编号                      ', '1', '1 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(104, 'nextflag            ', '执行后续步点标志              ', '1', '4 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(104, 'ptpch               ', '平台批次号                    ', '1', '3 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(104, 'pkrq                ', '批扣日期                      ', '1', '2 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(104, 'ywbh                ', '业务编号                      ', '1', '1 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(103, 'ywbh                ', '业务编号                      ', '1', '1 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(103, 'djrq                ', '登记日期                      ', '1', '2 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(114, 'ptpch               ', '平台批次号                    ', '1', '3 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(108, 'zjpch               ', '主机批次号                    ', '1', '5 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(107, 'zjpch               ', '主机批次号                    ', '1', '5 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(106, 'zjpch               ', '主机批次号                    ', '1', '5 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(105, 'zjpch               ', '主机批次号                    ', '1', '5 ', '1', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(104, 'zjpch               ', '主机批次号                    ', '1', '5 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(101, 'zjpch               ', '主机批次号                    ', '1', '5 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(109, 'ywbh                ', '业务编号                      ', '5', '1 ', '1', NULL, NULL, 'com.hundsun.agent.web.bots.sendUtil.Plywbh910010Send                                                ', 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(100, 'ywbh                ', '业务编号                      ', '1', '2 ', '1', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(100, 'lpwjm               ', '来盘文件名                    ', '1', '1 ', '1', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(100, 'zje                 ', '总金额                        ', '1', '5 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(100, 'shpch               ', '商户批次号                    ', '1', '3 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(100, 'zbs                 ', '总笔数                        ', '1', '4 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(100, 'hpwjm               ', '回盘文件名                    ', '1', '6 ', '1', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(100, 'lrfs                ', '录入方式                      ', '6', '7 ', '1', NULL, NULL, '1                                                                                                   ', 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(113, 'ywbh                ', '业务编号                      ', '5', '1 ', '1', '                                                                                                    ', '                    ', 'com.hundsun.agent.web.bots.sendUtil.Plywbh910010Send                                                ', 'V2.1.bots ', '                                                                                                    ', '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(113, 'djrq                ', '批扣日期                      ', '3', '2 ', '1', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(100, 'hqsjfs              ', '获取数据方式                  ', '1', '8 ', '1', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(100, 'localpath           ', '本地路径                      ', '1', '9 ', '1', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(100, 'threadno            ', '线程数                        ', '1', '91', '1', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(100, 'taskmode            ', '任务开始方式                  ', '1', '92', '1', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(102, 'productma           ', '产品任务最大总数              ', '1', '5 ', '0', '                                                                                                    ', '                    ', '                                                                                                    ', 'V2.1.bots ', '产品任务最大总数                                                                                    ', '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(102, 'busimax             ', '应用任务最大总数              ', '1', '4 ', '0', '                                                                                                    ', '                    ', '                                                                                                    ', 'V2.1.bots ', '应用任务最大总数                                                                                    ', '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(102, 'djlsh               ', '登记流水号                    ', '1', '3 ', '1', '                                                                                                    ', '                    ', '                                                                                                    ', 'V2.1.bots ', '登记流水号                                                                                          ', '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(102, 'djrq                ', '登记日期                      ', '3', '2 ', '1', '                                                                                                    ', '                    ', '                                                                                                    ', 'V2.1.bots ', '登记日期                                                                                            ', '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(102, 'ywbh                ', '业务编号                      ', '5', '1 ', '1', '                                                                                                    ', '                    ', 'com.hundsun.agent.web.bots.sendUtil.Plywbh910010Send                                                ', 'V2.1.bots ', '业务编号                                                                                            ', '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(108, 'nextflag            ', '执行后续步点标志              ', '1', '4 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(108, 'ptpch               ', '平台批次号                    ', '1', '3 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(108, 'pkrq                ', '批扣日期                      ', '1', '2 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(108, 'ywbh                ', '业务编号                      ', '1', '1 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(107, 'nextflag            ', '执行后续步点标志              ', '1', '4 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(107, 'ptpch               ', '平台批次号                    ', '1', '3 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(107, 'pkrq                ', '批扣日期                      ', '1', '2 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(107, 'ywbh                ', '业务编号                      ', '1', '1 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(106, 'nextflag            ', '执行后续步点标志              ', '1', '4 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(106, 'ptpch               ', '平台批次号                    ', '1', '3 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(106, 'pkrq                ', '批扣日期                      ', '1', '2 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(101, 'ptpch               ', '平台批次号                    ', '1', '3 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(106, 'ywbh                ', '业务编号                      ', '1', '1 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(115, 'pkrq                ', '批扣日期                      ', '3', '2 ', '1', '                                                                                                    ', '                    ', '                                                                                                    ', 'V2.1.bots ', '批扣日期                                                                                            ', '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(115, 'ywbh                ', '业务编号                      ', '5', '1 ', '1', '                                                                                                    ', '                    ', 'com.hundsun.agent.web.bots.sendUtil.Plywbh910010Send                                                ', 'V2.1.bots ', '业务编号                                                                                            ', '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);


INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(101, '910004                        ', '批量业务断点处理                                  ', '1', NULL, 'admin               ', '70001               ', '100                 ', 'V2.1.bots ', NULL, 'botsXml                       ', 'botsFile                      ', NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(102, '910002                        ', '批量业务任务发起                                  ', '1', NULL, 'admin               ', '70001               ', '100                 ', 'V2.1.bots ', NULL, 'botsXml                       ', 'botsFile                      ', NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(107, '910009                        ', '批量业务数据提回                                  ', '1', NULL, 'admin               ', '70001               ', '100                 ', 'V2.1.bots ', NULL, 'botsXml                       ', 'botsFile                      ', NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(106, '910008                        ', '批量业务数据提交                                  ', '1', NULL, 'admin               ', '70001               ', '100                 ', 'V2.1.bots ', NULL, 'botsXml                       ', 'botsFile                      ', NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(114, '910015                        ', '批量业务主机批次冲正                              ', '1', '                    ', 'admin               ', '00000               ', '100                 ', 'V2.1.bots ', '', 'botsXml                       ', 'botsFile                      ', '                                                                                                                                                      ', '                                                                                                                                                      ', NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(113, '910013                        ', '批量业务任务取消                                  ', '1', NULL, 'admin               ', '70001               ', '100                 ', 'V2.1.bots ', NULL, 'botsXml                       ', 'botsFile                      ', NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(105, '910007                        ', '批量业务数据审核                                  ', '1', NULL, 'admin               ', '70001               ', '100                 ', 'V2.1.bots ', NULL, 'botsXml                       ', 'botsFile                      ', NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(104, '910006                        ', '批量业务数据入库                                  ', '1', NULL, 'admin               ', '70001               ', '100                 ', 'V2.1.bots ', NULL, 'botsXml                       ', 'botsFile                      ', NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(100, '910001                        ', '批量业务申请录入                                  ', '1', NULL, 'chensy              ', '70001               ', '100                 ', 'V2.1.bots ', NULL, 'botsXml                       ', 'botsFile                      ', NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(103, '910005                        ', '批量业务获取数据                                  ', '1', NULL, 'admin               ', '70001               ', '100                 ', 'V2.1.bots ', NULL, 'botsXml                       ', 'botsFile                      ', NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(108, '910010                        ', '批量业务数据回盘                                  ', '1', '                    ', 'admin               ', '00000               ', '100                 ', 'V2.1.bots ', '', 'botsXml                       ', 'botsFile                      ', '                                                                                                                                                      ', '                                                                                                                                                      ', NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(110, '910014                        ', '批量业务主机批次撤销                              ', '1', '                    ', 'admin               ', '00000               ', '100                 ', 'V2.1.bots ', '', 'botsXml                       ', 'botsFile                      ', '                                                                                                                                                      ', '                                                                                                                                                      ', NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(109, '910012                        ', '批量业务主机批次状态查询                          ', '4', '/batch/resp/        ', 'admin               ', '00000               ', '100                 ', 'V2.1.bots ', '', 'botsXml                       ', 'botsFile                      ', '                                                                                                                                                      ', '                                                                                                                                                      ', NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(115, '910020                        ', '批量任务发起                                      ', '0', NULL, 'admin               ', '00000               ', '100                 ', 'V2.1.bots ', NULL, 'botsXml                       ', 'botsFile                      ', NULL, NULL, NULL, NULL, NULL, NULL);


INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_Encry                    ', 'bots_keyM                     ', 4, '批量加解密注册                ', '批量加解密注册                                    ', '1', 'botsEncry           ', '0', 'V2.1.bots ', NULL, '900252710000        ', '0', 'agent     ', '                              ', NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_shgz                     ', 'bots_message                  ', 3, '审核配置                      ', '审核配置                                          ', '0', 'botsAuditingreg     ', '1', 'V2.1.bots ', NULL, '900252600000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_Pzdc                     ', 'bots_message                  ', 3, '批量配置导出                  ', '批量配置导出                                      ', '1', 'botsPzdc            ', '1', 'V2.1.bots ', NULL, '900252800000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_AUDITINGREG              ', 'bots_shgz                     ', 4, '审核函数配置                  ', '审核函数配置                                      ', '1', 'botsAuditingreg     ', '1', 'V2.1.bots ', NULL, '900252610000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_mapinfo                  ', 'bots_message                  ', 3, '文件映射配置                  ', '文件映射配置                                      ', '0', 'botsMapinfo         ', '1', 'V2.1.bots ', NULL, '900252400000        ', '0', 'agent     ', '                              ', NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_plywbdcz                 ', 'bots_fz                       ', 3, '批量任务第三方冲正            ', '批量任务第三方冲正                                ', '1', 'botsPlywbdcz        ', '1', 'V2.1.bots ', NULL, '900254300000        ', '0', 'agent     ', '                              ', NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_zjfilemap                ', 'bots_mapinfo                  ', 4, '主机映射                      ', '主机文件映射                                      ', '1', 'botsZJMapsinfo      ', '1', 'V2.1.bots ', '                                        ', '900252420000        ', '0', 'agent     ', '                              ', '                                                                                                    ', '                                                                                                    ');
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_WBfilemap                ', 'bots_mapinfo                  ', 4, '外部映射                      ', '外部文件映射                                      ', '1', 'botsMapinfo         ', '1', 'V2.1.bots ', '                                        ', '900252430000        ', '0', 'agent     ', '                              ', '                                                                                                    ', '                                                                                                    ');
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_plywrwqx                 ', 'bots_fz                       ', 3, '批量来盘录入撤销              ', '批量来盘文件录入撤销                              ', '1', 'botsPllpwjcx        ', '1', 'V2.1.bots ', '                                        ', '900254400000        ', '0', 'agent     ', '                              ', 'send_id=113                                                                                         ', NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_keyctrl                  ', 'bots_keyM                     ', 4, '批量密钥控制                  ', '批量密钥控制                                      ', '1', 'botsKeyctrl         ', '0', 'V2.1.bots ', NULL, '900252720000        ', '0', 'agent     ', '                              ', NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_plywbdcx                 ', 'bots_fz                       ', 3, '批量任务主机冲正              ', '批量任务主机冲正                                  ', '1', 'botsPlywbdcx        ', '1', 'V2.1.bots ', NULL, '900254200000        ', '0', 'agent     ', '                              ', NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_downgapsfile             ', 'bots_fz                       ', 3, '文件下载                      ', '文件下载                                          ', '1', 'botsGapsdown        ', '1', 'V2.1.bots ', NULL, '900254500000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_keyM                     ', 'bots_message                  ', 3, '加解密管理                    ', '加解密管理                                        ', '0', 'botsKeyctrl         ', '0', 'V2.1.bots ', NULL, '900252700000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_plywmx                   ', 'bots_report                   ', 3, '批量业务明细                  ', '批量业务明细                                      ', '1', 'botsPlywmx          ', '1', 'V2.1.bots ', NULL, '900255100000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_plywbd                   ', 'bots_run                      ', 3, '批量异常单步处理              ', '批量单步处理                                      ', '1', 'botsPlywbd          ', '1', 'V2.1.bots ', NULL, '900253300000        ', '0', 'agent     ', '                              ', NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_run                      ', 'bots                          ', 2, '批量业务运行                  ', '批量业务运行                                      ', '0', 'alterUserPass       ', '1', 'V2.1.bots ', NULL, '900253000000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_message                  ', 'bots                          ', 2, '批量业务配置                  ', '批量业务配置                                      ', '0', 'alterUserPass       ', '1', 'V2.1.bots ', NULL, '900252000000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_report                   ', 'bots                          ', 2, '批量业务报表                  ', '批量业务报表                                      ', '0', 'alterUserPass       ', '1', 'V2.1.bots ', NULL, '900255000000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_wbwjdj                   ', 'bots_run                      ', 3, '来盘文件申请录入              ', '来盘文件申请录入                                  ', '1', 'botsWbwjdj          ', '1', 'V2.1.bots ', NULL, '900253100000        ', '0', 'agent     ', '                              ', NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_wbwjsh                   ', 'bots_run                      ', 3, '审核外部文件                  ', '审核外部文件                                      ', '1', 'botsWbwjdjSH        ', '1', 'V2.1.bots ', NULL, '900253200000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots                          ', '/                             ', 1, '批量管理                      ', '批量管理                                          ', '0', 'botsPlywlx          ', '1', 'V2.1.bots ', NULL, '900250000000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_plrw                     ', 'bots_run                      ', 3, '批量业务处理                  ', '批量业务处理                                      ', '1', 'botsPlrw            ', '1', 'V2.1.bots ', NULL, '900253400000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_flowcfg                  ', 'bots_message                  ', 3, '流程配置                      ', '流程配置                                          ', '1', 'botsFlowcfg         ', '1', 'V2.1.bots ', NULL, '900252300000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_Plywbdmx                 ', 'bots_report                   ', 3, '批量步点明细                  ', '批量业务步点明细                                  ', '1', 'botsPlywbdmx        ', '1', 'V2.1.bots ', NULL, '900255400000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_file                     ', 'bots_message                  ', 3, '文件配置                      ', '文件配置                                          ', '1', 'botsFile            ', '1', 'V2.1.bots ', NULL, '900252100000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_fz                       ', 'bots                          ', 2, '批量辅助管理                  ', '批量辅助管理                                      ', '0', 'botsAuditingreg     ', '1', 'V2.1.bots ', NULL, '900254000000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_zjpczt                   ', 'bots_fz                       ', 3, '批次状态查询                  ', '批次状态查询                                      ', '1', 'send                ', '1', 'V2.1.bots ', '                                        ', '900254100000        ', '0', 'agent     ', '                              ', 'send_id=109                                                                                         ', NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_func                     ', 'bots_shgz                     ', 4, '审核流程配置                  ', '审核流程配置                                      ', '1', 'botsAuditingfunc    ', '1', 'V2.1.bots ', NULL, '900252620000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_tablereg                 ', 'bots_message                  ', 3, '表结构配置                    ', '表结构配置                                        ', '1', 'botsTablereg        ', '1', 'V2.1.bots ', NULL, '900252200000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_Plywsel                  ', 'bots_report                   ', 3, '批量任务查询                  ', '批量任务查询                                      ', '1', 'botsPlrwSel         ', '1', 'V2.1.bots ', NULL, '900255300000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_runctrl                  ', 'bots_message                  ', 3, '运行控制配置                  ', '运行控制配置                                      ', '1', 'botsRunctrl         ', '1', 'V2.1.bots ', NULL, '900252500000        ', '0', 'agent     ', '                              ', NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_plrwfq2                  ', 'bots_run                      ', 3, '批量任务发起                  ', '批量任务发起(非来盘文件)                          ', '1', 'send                ', '1', 'V2.1.bots ', '                                        ', '900253150000        ', '0', 'agent     ', '                              ', 'send_id=115                                                                                         ', NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_map_xym                  ', 'bots_mapinfo                  ', 4, '响应码映射                    ', '响应码映射                                        ', '1', 'botsRespmap         ', '1', 'V2.1.bots ', '                                        ', '900252410000        ', '0', 'agent     ', '                              ', '                                                                                                    ', '                                                                                                    ');


INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step_5              ', '批量提交处理情况              ', '0                             ', '入账成功                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step_5              ', '批量提交处理情况              ', '1                             ', '数据库错误                    ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step_5              ', '批量提交处理情况              ', '9                             ', '其他错                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step_6              ', '结果取回处理情况              ', '0                             ', '结果已取回                    ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step_8              ', '归档处理情况                  ', 'B                             ', '归档中                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step_8              ', '归档处理情况                  ', '0                             ', '归档结束                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step_*              ', '批量撤销处理情况              ', '0                             ', '撤销成功                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step_*              ', '批量撤销处理情况              ', '1                             ', '已撤销                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step_*              ', '批量撤销处理情况              ', '2                             ', '不允许撤销                    ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step_*              ', '批量撤销处理情况              ', '9                             ', '其他错                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_lrbz                 ', '是否需要申请录入              ', '0                             ', '是                            ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_lrbz                 ', '是否需要申请录入              ', '1                             ', '否                            ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_hqsjfs               ', '获取数据方式                  ', '0                             ', 'FTP主动取                     ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_hqsjfs               ', '获取数据方式                  ', '1                             ', '本地取                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_hqsjfs               ', '获取数据方式                  ', '2                             ', '交易报文                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_jywjfs               ', '校验文件方式                  ', '0                             ', '不校验                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_jywjfs               ', '校验文件方式                  ', '1                             ', '校验                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_run_shbz                 ', '审核标志                      ', '0                             ', '需要审核外部文件              ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_run_shbz                 ', '审核标志                      ', '1                             ', '不需要审核外部文件            ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_rwksfs                   ', '任务开始方式                  ', '1                             ', '立即                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_rwksfs                   ', '任务开始方式                  ', '2                             ', '手动                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_flag                ', '列属性                        ', '0                             ', '交易金额累加                  ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_flag                ', '列属性                        ', '1                             ', '交易金额累减                  ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_flag                ', '列属性                        ', '2                             ', '字段SUM                       ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_flag                ', '列属性                        ', '3                             ', '字段COUNT                     ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_flag                ', '列属性                        ', '4                             ', '值设置                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_flag                ', '列属性                        ', '5                             ', '值获取                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_flag                ', '列属性                        ', '6                             ', '汇总记录属性-汇总笔数         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_flag                ', '列属性                        ', '7                             ', '汇总记录属性-汇总金额         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_lylx                ', '来源类型                      ', '2                             ', 'xml获取                       ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('batch_plyw_rwzt               ', '批量任务状态                  ', 'C                             ', '已冲正                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_dbdbz               ', '步点交易标志                  ', '910005                        ', '获取数据                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '21                            ', '[21]NAK(否定)                 ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '20                            ', '[20]DC4(设备控制4)            ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '2                             ', '[2]STX(正文开始)              ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '19                            ', '[19]DC3(设备控制3)            ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '18                            ', '[18]DC2(设备控制2)            ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '17                            ', '[17]DC1(设备控制1)            ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '16                            ', '[16]DLE(空格)                 ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step_5              ', '批量提交处理情况              ', 'B                             ', '批量入账处理中                ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '15                            ', '[15]SI(移位输入)              ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '14                            ', '[14]SO(移位输出)              ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '13                            ', '[13]CR(回车)                  ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '127                           ', '[127]DEL(删除)                ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '126                           ', '[126]~                        ', 'V2.1.bots ', '1                             ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '125                           ', '[125]}                        ', 'V2.1.bots ', '1                             ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '124                           ', '[124]|                        ', 'V2.1.bots ', '1                             ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '123                           ', '[123]{                        ', 'V2.1.bots ', '1                             ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '122                           ', '[122]z                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '121                           ', '[121]y                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '120                           ', '[120]x                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '12                            ', '[12]FF(走纸控制)              ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '119                           ', '[119]w                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '118                           ', '[118]v                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '117                           ', '[117]u                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '116                           ', '[116]t                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '115                           ', '[115]s                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '114                           ', '[114]r                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '113                           ', '[113]q                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '112                           ', '[112]p                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '111                           ', '[111]o                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '110                           ', '[110]n                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '11                            ', '[11]VT(垂直制表)              ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '109                           ', '[109]m                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '108                           ', '[108]l                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '107                           ', '[107]k                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '106                           ', '[106]j                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '105                           ', '[105]i                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '104                           ', '[104]h                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '103                           ', '[103]g                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '102                           ', '[102]f                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '101                           ', '[101]e                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '100                           ', '[100]d                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '10                            ', '[10]LF(换行)                  ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '1                             ', '[1]SOH(标题开始)              ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '0                             ', '[0]NUT                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '49                            ', '[49]1                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '5                             ', '[5]ENQ(询问字符)              ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '50                            ', '[50]2                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '51                            ', '[51]3                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '52                            ', '[52]4                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '53                            ', '[53]5                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '54                            ', '[54]6                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_hzfs                ', '汇总方式                      ', '1                             ', '全部汇总                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_hzfs                ', '汇总方式                      ', '2                             ', '成功汇总                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_hzfs                ', '汇总方式                      ', '3                             ', '失败汇总                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_lylx                ', '来源类型                      ', '3                             ', '文件序号                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_lylx                ', '来源类型                      ', '4                             ', '流水序号                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_lylx                ', '来源类型                      ', '5                             ', '常量                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_lylx                ', '来源类型                      ', '6                             ', '综合前置流水号                ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_fldtype                  ', '付点类型                      ', 'I                             ', '整型                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_lylx                ', '来源类型                      ', '1                             ', '来盘文件获取                  ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_fldtype                  ', '付点类型                      ', 'D                             ', '浮点                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_fldtype                  ', '付点类型                      ', 'C                             ', '字符串                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_tjgxbz                   ', '提交更新标志                  ', '1                             ', '更新内容                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('cz_syslx                      ', '财政系统类型                  ', '0                             ', '老系统                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('cz_syslx                      ', '财政系统类型                  ', '1                             ', '新系统                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('cz_syslx                      ', '财政系统类型                  ', '2                             ', '试点系统一次                  ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('cz_syslx                      ', '财政系统类型                  ', '3                             ', '试点系统二次                  ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_clfs                     ', '处理方式                      ', '2                             ', '定时                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_fqfs                     ', '发起方式                      ', '1                             ', 'web                           ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_fqfs                     ', '发起方式                      ', '2                             ', '柜面                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_fqfs                     ', '发起方式                      ', '3                             ', '商户                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_flow_yxsx                ', '属性类型                      ', '0                             ', '运行属性                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_flow_yxsx                ', '属性类型                      ', '1                             ', '开发属性                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_clfs                     ', '处理方式                      ', '1                             ', '手工                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_fileType                 ', '代理业务文件类型              ', '1                             ', '定长文本                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_fileType                 ', '代理业务文件类型              ', '2                             ', '分隔符文本                    ', 'V2.1.bots ', NULL);
INSERT INTO t_dict(dict_kind, dict_name, dict_key, dict_info, version, bak)
  VALUES('bots_fileType                 ', '代理业务文件类型              ', '3                             ', '去尾分隔符文本                ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '55                            ', '[55]7                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '56                            ', '[56]8                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '57                            ', '[57]9                         ', 'V2.1.bots ', '1                             ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '58                            ', '[58]:                         ', 'V2.1.bots ', '1                             ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '59                            ', '[59];                         ', 'V2.1.bots ', '1                             ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '6                             ', '[6]ACK(承认)                  ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '60                            ', '[60]<                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '61                            ', '[61]=                         ', 'V2.1.bots ', '1                             ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '62                            ', '[62]>                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '63                            ', '[63]?                         ', 'V2.1.bots ', '1                             ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '64                            ', '[64]@                         ', 'V2.1.bots ', '1                             ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '65                            ', '[65]A                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '66                            ', '[66]B                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '67                            ', '[67]C                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '68                            ', '[68]D                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '69                            ', '[69]E                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '7                             ', '[7]BEL(报警)                  ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '70                            ', '[70]F                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '71                            ', '[71]G                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '72                            ', '[72]H                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '73                            ', '[73]I                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '74                            ', '[74]J                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '75                            ', '[75]K                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '76                            ', '[76]L                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '77                            ', '[77]M                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '78                            ', '[78]N                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '79                            ', '[79]O                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '8                             ', '[8]BS(退一格)                 ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '80                            ', '[80]P                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '81                            ', '[81]Q                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '82                            ', '[82]R                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '83                            ', '[83]X                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '84                            ', '[84]T                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '85                            ', '[85]U                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '86                            ', '[86]V                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '87                            ', '[87]W                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '88                            ', '[88]X                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '89                            ', '[89]Y                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '9                             ', '[9]HT(横向列表)               ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '90                            ', '[90]Z                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '91                            ', '[91][                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '92                            ', '[92]\                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '93                            ', '[93]]                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '94                            ', '[94]^                         ', 'V2.1.bots ', '1                             ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '95                            ', '[95]__                        ', 'V2.1.bots ', '1                             ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '96                            ', '[96]、                        ', 'V2.1.bots ', '1                             ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '97                            ', '[97]a                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '98                            ', '[98]b                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '99                            ', '[99]c                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('batch_plyw_rwzt               ', '任务状态                      ', '3                             ', '返回                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_auditing_shsbbz          ', '审核失败标志                  ', '0                             ', '返回审核失败                  ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_auditing_shsbbz          ', '审核失败标志                  ', '1                             ', '跳过审核失败明细              ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_NextFlag            ', '执行标志                      ', '0                             ', '执行                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_NextFlag            ', '执行标志                      ', '1                             ', '不执行                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_wbwj_shbz                ', '审核标志                      ', '0                             ', '审核通过                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_wbwj_shbz                ', '审核标志                      ', '1                             ', '未审核                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_lc_bd                    ', '流程步点                      ', 'hqsj                          ', '获取数据                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_lc_bd                    ', '流程步点                      ', 'sjtj                          ', '数据提交                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_lc_bd                    ', '流程步点                      ', 'sjth                          ', '数据提回                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_lc_bd                    ', '流程步点                      ', 'sjsh                          ', '数据审核                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_lc_bd                    ', '流程步点                      ', 'sjrk                          ', '数据入库                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_lc_bd                    ', '流程步点                      ', 'sjhp                          ', '数据回盘                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_dbdbz               ', '步点交易标志                  ', '910011                        ', '数据回盘                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_dbdbz               ', '步点交易标志                  ', '910006                        ', '数据入库                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_dbdbz               ', '步点交易标志                  ', '910007                        ', '数据审核                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_dbdbz               ', '步点交易标志                  ', '910009                        ', '数据提回                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_dbdbz               ', '步点交易标志                  ', '910008                        ', '数据提交                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_cxbz                 ', '撤消标志                      ', '1                             ', '不允许                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_cxbz                 ', '撤消标志                      ', '0                             ', '允许                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_jmbz                 ', '加解密标志                    ', '0                             ', '无需解密                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_jmbz                 ', '加解密标志                    ', '1                             ', '需要解密                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_wjlxzhbz             ', '文件类型转换标志              ', '0                             ', '无需转换                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_wjlxzhbz             ', '文件类型转换标志              ', '1                             ', '需要转换                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_sjlx                 ', '数据类型                      ', '1                             ', '报文                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_sjlx                 ', '数据类型                      ', '2                             ', '文件                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_sjlx                 ', '数据类型                      ', '3                             ', '报文+文件                     ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_sjlx                 ', '数据类型                      ', '4                             ', '文件+报文                     ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_bwlx                 ', '报文类型                      ', '1                             ', 'xml                           ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_bwlx                 ', '报文类型                      ', '2                             ', 'icxp                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_bwlx                 ', '报文类型                      ', '3                             ', '8583                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_wjtxlx               ', '文件通讯类型                  ', '1                             ', 'FTP                           ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_wjtxlx               ', '文件通讯类型                  ', '2                             ', '其他                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_sqzjpcbz             ', '是否申请主机批次              ', '0                             ', '是                            ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_sqzjpcbz             ', '是否申请主机批次              ', '1                             ', '否                            ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_wjfjbz               ', '文件分卷标志                  ', '0                             ', '不分卷                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_wjfjbz               ', '文件分卷标志                  ', '1                             ', '按字节分                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_wjfjbz               ', '文件分卷标志                  ', '2                             ', '按笔数分                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_failflag             ', '失败明细提交标志              ', '0                             ', '提交非本批次处理失败明细      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_failflag             ', '失败明细提交标志              ', '1                             ', '提交本批次处理失败明细        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_failflag             ', '失败明细提交标志              ', '2                             ', '提交本批次未处理明细          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_fssjfs               ', '发送数据方式                  ', '0                             ', 'FTP主动发送                   ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_fssjfs               ', '发送数据方式                  ', '1                             ', 'WEB服务端数据                 ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_fssjfs               ', '发送数据方式                  ', '2                             ', '其他方式                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('batch_plyw_rwzt               ', '任务状态                      ', 'X                             ', '已撤消                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('batch_plrw_czbd               ', '操作步点                      ', 'X                             ', '撤销                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('batch_plrw_czbd               ', '操作步点                      ', '5                             ', '数据回盘                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('batch_plrw_czbd               ', '操作步点                      ', '4                             ', '数据提回                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('batch_plrw_czbd               ', '操作步点                      ', '3                             ', '数据提交                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('batch_plrw_czbd               ', '操作步点                      ', '2                             ', '数据审核                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('batch_plrw_czbd               ', '操作步点                      ', '1                             ', '数据入库                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('batch_plrw_czbd               ', '操作步点                      ', '0                             ', '获取数据                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '23                            ', '[23]TB                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '24                            ', '[24]CAN(作废)                 ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '25                            ', '[25]EM(纸尽)                  ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '26                            ', '[26]SUB(换置)                 ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '27                            ', '[27]ESC(换码)                 ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '28                            ', '[28]FS(文字分隔符)            ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '29                            ', '[29]GS(组分隔符)              ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '3                             ', '[3]ETX(正文结束)              ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '30                            ', '[30]RS(记录分隔符)            ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '31                            ', '[31]US(单元分隔符)            ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '32                            ', '[32](space)                   ', 'V2.1.bots ', '1                             ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '33                            ', '[33]！                        ', 'V2.1.bots ', '1                             ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '34                            ', '[34]”                        ', 'V2.1.bots ', '1                             ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '35                            ', '[35]#                         ', 'V2.1.bots ', '1                             ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '36                            ', '[36]$                         ', 'V2.1.bots ', '1                             ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '37                            ', '[37]%                         ', 'V2.1.bots ', '1                             ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '38                            ', '[38]&                         ', 'V2.1.bots ', '1                             ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '39                            ', '[39]''                         ', 'V2.1.bots ', '1                             ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '4                             ', '[4]EOT                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '40                            ', '[40](                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '41                            ', '[41])                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '42                            ', '[42]*                         ', 'V2.1.bots ', '1                             ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '43                            ', '[43]+                         ', 'V2.1.bots ', '1                             ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '44                            ', '[44],                         ', 'V2.1.bots ', '1                             ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '45                            ', '[45]-                         ', 'V2.1.bots ', '1                             ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '46                            ', '[46].                         ', 'V2.1.bots ', '1                             ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '47                            ', '[47]/                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '48                            ', '[48]0                         ', 'V2.1.bots ', '1                             ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step                ', '批量阶段                      ', '1                             ', '提交阶段                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step                ', '批量阶段                      ', '3                             ', '文件检查阶段                  ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step                ', '批量阶段                      ', '5                             ', '入账阶段                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step                ', '批量阶段                      ', '6                             ', '结果取回阶段                  ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step                ', '批量阶段                      ', '8                             ', '归档阶段                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step                ', '批量阶段                      ', '*                             ', '批量撤销阶段                  ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step_1              ', '批量提交处理情况              ', 'B                             ', '批量提交处理中                ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step_1              ', '批量提交处理情况              ', '0                             ', '提交成功                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step_1              ', '批量提交处理情况              ', '1                             ', '签约帐号错                    ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step_1              ', '批量提交处理情况              ', '2                             ', '归集帐号错                    ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step_1              ', '批量提交处理情况              ', '3                             ', '签约帐号余额不足              ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step_1              ', '批量提交处理情况              ', '4                             ', '归集帐号余额不足              ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step_1              ', '批量提交处理情况              ', '5                             ', '预约日期错                    ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step_1              ', '批量提交处理情况              ', '6                             ', '6报文字段错                   ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step_1              ', '批量提交处理情况              ', '7                             ', '文件大小错                    ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_lc_bdsx                  ', '流程步点顺序对应              ', '4                             ', 'sjtj                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_dsfbz                    ', '代收付标志                    ', '1                             ', '代收                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_dsfbz                    ', '代收付标志                    ', '2                             ', '代付                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_dsfbz                    ', '代收付标志                    ', '3                             ', '其他                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('batch_plrw_bdzt               ', '步点状态                      ', '0                             ', '失败中止                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('batch_plrw_bdzt               ', '步点状态                      ', '1                             ', '成功结束                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('batch_plrw_bdzt               ', '步点状态                      ', '2                             ', '断点                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('batch_plrw_bdzt               ', '步点状态                      ', '3                             ', '返回                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('batch_plrw_bdzt               ', '步点状态                      ', '4                             ', '等待                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('batch_plyw_bdzt               ', '步点状态                      ', '9                             ', '在处理中                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('batch_plyw_rwzt               ', '任务状态                      ', '0                             ', '失败中止                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('batch_plyw_rwzt               ', '任务状态                      ', '1                             ', '成功结束                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('batch_plyw_rwzt               ', '任务状态                      ', '2                             ', '暂停                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('batch_plyw_rwzt               ', '任务状态                      ', '9                             ', '在处理中                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('batch_plrw_bdzt               ', '步点状态                      ', '9                             ', '在处理中                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_fmt                 ', '文件格式                      ', '01                            ', '单明细                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_fmt                 ', '文件格式                      ', '02                            ', '汇总＋单明细                  ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_fmt                 ', '文件格式                      ', '03                            ', '单明细＋汇总                  ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_ext                 ', '文件类型                      ', '0                             ', 'TXT                           ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_ext                 ', '文件类型                      ', '1                             ', 'DBF                           ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_ext                 ', '文件类型                      ', '2                             ', 'XLS                           ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_ext                 ', '文件类型                      ', '3                             ', 'XLSX                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_fllx                ', '文件分类类型                  ', '1                             ', '汇总                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_fllx                ', '文件分类类型                  ', '2                             ', '明细                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_wzbz                ', '批量文件位置标志              ', '1                             ', '首列（第一行）                ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_wzbz                ', '批量文件位置标志              ', '2                             ', '记录标识                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_wzbz                ', '批量文件位置标志              ', '3                             ', '汇总记录之后                  ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step_1              ', '批量提交处理情况              ', '9                             ', '其他错                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step_3              ', '文件检查处理情况              ', 'B                             ', '文件检查处理中                ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step_3              ', '文件检查处理情况              ', '0                             ', '文件检查成功                  ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step_3              ', '文件检查处理情况              ', '1                             ', '文件MD5校验错                 ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step_3              ', '文件检查处理情况              ', '2                             ', '总笔数错                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step_3              ', '文件检查处理情况              ', '3                             ', '总金额错                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step_3              ', '文件检查处理情况              ', '9                             ', '其他错                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII码                       ', '22                            ', '[22]SYN(空转同步)             ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_lc_bdsx                  ', '流程步点顺序对应              ', '5                             ', 'sjth                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_lc_bdsx                  ', '流程步点顺序对应              ', '3                             ', 'sjsh                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_lc_bdsx                  ', '流程步点顺序对应              ', '2                             ', 'sjrk                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_lc_bdsx                  ', '流程步点顺序对应              ', '6                             ', 'sjhp                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_lc_bdsx                  ', '流程步点顺序对应              ', '1                             ', 'hqsj                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_fgfsx               ', '分割符属性                    ', '0                             ', '保留尾分割符                  ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_fgfsx               ', '分割符属性                    ', '1                             ', '去掉尾分割符                  ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_fgfsx               ', '分割符属性                    ', '2                             ', '其他                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_taskmode                 ', '任务开始方式                  ', '1                             ', '立即                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_dqfs                ', '对齐方式                      ', 'L                             ', '左对齐                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_dqfs                ', '对齐方式                      ', 'R                             ', '右对齐                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_blx                      ', '表类型                        ', '1                             ', '业务表                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_blx                      ', '表类型                        ', '2                             ', '模板表                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_tjgxbz                   ', '提交更新标志                  ', '2                             ', '更新条件                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_xym_zhbz                 ', '响应吗转换标志                ', '0                             ', '转换                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_fmt                 ', '文件格式                      ', '04                            ', '汇总＋单明细＋汇总            ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_wzbz                ', '批量文件位置标志              ', '4                             ', '最后一行                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_taskmode                 ', '任务开始方式                  ', '2                             ', '手动                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_wbwj_shbz                ', '审核标志                      ', '2                             ', '审核失败                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_xym_zhbz                 ', '响应吗转换标志                ', '1                             ', '不转换                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('batch_plrw_bdzt               ', '步点状态                      ', 'C                             ', '已冲正                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_plywmx_his               ', '数据表选择                    ', '0                             ', '当前表                        ', 'V2.1.bots ', '                              ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_plywmx_his               ', '数据表选择                    ', '1                             ', '历史表                        ', 'V2.1.bots ', '                              ');


INSERT INTO T_SEND_SERVER(ID, SERNAME, IP, PORT, TYPEID, CSTIME)
  VALUES('botsFile                      ', '批量文件服务                                      ', '192.168.53.66       ', 33344, '1', 60);
INSERT INTO T_SEND_SERVER(ID, SERNAME, IP, PORT, TYPEID, CSTIME)
  VALUES('botsXml                       ', '批量报文服务                                      ', '192.168.53.66       ', 13008, '0', 30);
