
delete from T_TRAN where version='V2.1.app';

delete from T_SUB_TRAN where version='V2.1.app';

delete from T_SEND_RETURN where version='V2.1.app';

delete from T_SEND_COND where version='V2.1.app';

delete from T_SENDINFO where version='V2.1.app';

delete from T_MENU where version='V2.1.app';

delete from T_DICT where version='V2.1.app';

delete from T_SEND_SERVER where id like 'app%';



INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appKhcpqy           ', '客户产品签约                  ', '1', 'com.hundsun.agent.web.app.ctl.AppKhcpqyCtl                                                          ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appDwcpxy           ', '单位产品协议                  ', '1', 'com.hundsun.agent.web.app.ctl.AppDwcpxyCtl                                                          ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appSxfl             ', '手续费率                      ', '1', 'com.hundsun.agent.web.sxfl.ctl.AgentSxflCtl                                                         ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpSxfgx          ', '产品手续费关系                ', '1', 'com.hundsun.agent.web.sxfl.ctl.AgentSxfgxCtl                                                        ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpqd             ', '中间业务[产品渠道]            ', '1', 'com.hundsun.agent.web.app.ctl.AppCpqdCtl                                                            ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCptx             ', '中间业务[产品通讯]            ', '1', 'com.hundsun.agent.web.app.ctl.AppCptxCtl                                                            ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpdc             ', '产品导出                      ', '1', 'com.hundsun.agent.web.app.ctl.AppCpdcCtl                                                            ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appSjdr             ', '数据导入                      ', '1', 'com.hundsun.agent.web.app.ctl.AppSjdrCtl                                                            ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appXlkz             ', '中间业务[序列]管理            ', '1', 'com.hundsun.agent.web.app.ctl.AppXlkzCtl                                                            ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appJyxx             ', '中间业务[交易]信息管理        ', '1', 'com.hundsun.agent.web.app.ctl.AppJyxxCtl                                                            ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appDict             ', '中间业务系统数据字典          ', '1', 'com.hundsun.agent.web.app.ctl.AppDictCtl                                                            ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCskz             ', '中间业务[参数]配置            ', '1', 'com.hundsun.agent.web.app.ctl.AppCskzCtl                                                            ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appKzxx             ', '扩展信息                      ', '1', 'com.hundsun.agent.web.app.ctl.AppKzxxCtl                                                            ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpjy             ', '产品交易服务                  ', '1', 'com.hundsun.agent.web.app.ctl.AppCpjyCtl                                                            ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appSxfkz            ', '手续费控制                    ', '1', 'com.hundsun.agent.web.sxfl.ctl.AgentSxfkzCtl                                                        ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCppz             ', '产品凭证                      ', '1', 'com.hundsun.agent.web.app.ctl.AppCppzCtl                                                            ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appRwjk             ', '任务监控查询                  ', '1', 'com.hundsun.agent.web.app.ctl.AppRwjkCtl                                                            ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appTxxx             ', '通讯信息维护                  ', '1', 'com.hundsun.agent.web.app.ctl.AppTxxxCtl                                                            ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpxx             ', '中间业务[产品]信息维护        ', '1', 'com.hundsun.agent.web.app.ctl.AppCpxxCtl                                                            ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appLs               ', '平台流水查询                  ', '1', 'com.hundsun.agent.web.app.ctl.AppLsCtl                                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appOrg              ', '机构操作                      ', '0', 'com.hundsun.agent.web.app.ctl.AppOrgCtl                                                             ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appMj               ', '枚举配置                      ', '1', 'com.hundsun.agent.web.app.ctl.AppMjCtl                                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appKhxx             ', '客户信息                      ', '1', 'com.hundsun.agent.web.app.ctl.AppKhxxCtl                                                            ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appYyxx             ', '中间业务[应用信息]维护        ', '1', 'com.hundsun.agent.web.app.ctl.AppYyxxCtl                                                            ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appQdxx             ', '中间业务[渠道]信息维护        ', '1', 'com.hundsun.agent.web.app.ctl.AppQdxxCtl                                                            ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appDwxx             ', '中间业务系统[单位]信息维护    ', '1', 'com.hundsun.agent.web.app.ctl.AppDwxxCtl                                                            ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appPzzl             ', '中间业务[凭证]信息管理        ', '1', 'com.hundsun.agent.web.app.ctl.AppPzzlCtl                                                            ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appYydc             ', '应用导出                      ', '1', 'com.hundsun.agent.web.app.ctl.AppYydcCtl                                                            ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpjg             ', '中间业务[产品机构]            ', '1', 'com.hundsun.agent.web.app.ctl.AppCpjgCtl                                                            ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpdzxd           ', '产品定制向导                  ', '1', 'com.hundsun.agent.web.app.ctl.AppCpdzxdCtl                                                          ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appZwrq             ', '帐务日期                      ', '1', 'com.hundsun.agent.web.app.ctl.AppZwrqCtl                                                            ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appGyjyqxkz         ', '产品柜员交易权限控制          ', '1', 'com.hundsun.agent.web.app.ctl.AppGyjyqxkzCtl                                                        ', 'V2.1.app  ', '                              ', '                              ', '                              ');
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appRzpz             ', '日终配置                      ', '1', 'com.hundsun.agent.web.app.ctl.AppRzpzCtl                                                            ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appJgedkz           ', '产品机构额度控制              ', '1', 'com.hundsun.agent.web.app.ctl.AppJgedkzCtl                                                          ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appGyedkz           ', '产品柜员额度控制              ', '1', 'com.hundsun.agent.web.app.ctl.AppGyedkzCtl                                                          ', 'V2.1.app  ', NULL, NULL, NULL);


INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpxx             ', 'list                ', '获得数据                      ', 'app/agent/app/appcpxx.jsp                                                                           ', '获得数据                                          ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appDwxx             ', 'add                 ', '添加                          ', 'app/agent/app/appdwxx.jsp                                                                           ', '添加                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appDwxx             ', 'del                 ', '删除                          ', 'app/agent/app/appdwxx.jsp                                                                           ', '删除                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appPzzl             ', 'def                 ', '查询                          ', 'app/agent/app/apppzzl.jsp                                                                           ', '默认                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appPzzl             ', 'add                 ', '添加                          ', 'app/agent/app/apppzzl.jsp                                                                           ', '添加                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appPzzl             ', 'list                ', '获得数据                      ', 'app/agent/app/apppzzl.jsp                                                                           ', '获得数据                                          ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpxx             ', 'del                 ', '删除                          ', 'app/agent/app/appcpxx.jsp                                                                           ', '删除                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCskz             ', 'add                 ', '添加                          ', 'app/agent/app/appcskz.jsp                                                                           ', '添加                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appKzxx             ', 'def                 ', '查询                          ', 'app/agent/app/appkzxx.jsp                                                                           ', '默认                                              ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appKzxx             ', 'list                ', '获得数据                      ', 'app/agent/app/appkzxx.jsp                                                                           ', '获得数据                                          ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appKzxx             ', 'add                 ', '添加                          ', 'app/agent/app/appkzxx.jsp                                                                           ', '添加                                              ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appKzxx             ', 'upt                 ', '更新                          ', 'app/agent/app/appkzxx.jsp                                                                           ', '更新                                              ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpjg             ', 'del                 ', '删除                          ', 'app/agent/app/appcpjg.jsp                                                                           ', '删除                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpSxfgx          ', 'upt                 ', '修改记录                      ', 'app/agent/sxfl/agent_cpsxfgx.jsp                                                                    ', '修改记录                                          ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appSxfkz            ', 'def                 ', '默认界面                      ', 'app/agent/sxfl/agent_cpsxfkz.jsp                                                                    ', '获取默认界面                                      ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appSxfkz            ', 'add                 ', '新增记录                      ', 'app/agent/sxfl/agent_cpsxfkz.jsp                                                                    ', '新增记录                                          ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appSxfkz            ', 'del                 ', '删除记录                      ', 'app/agent/sxfl/agent_cpsxfkz.jsp                                                                    ', '删除记录                                          ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appSxfkz            ', 'upt                 ', '更新记录                      ', 'app/agent/sxfl/agent_cpsxfkz.jsp                                                                    ', '更新记录                                          ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appSxfl             ', 'def                 ', '获取默认界面                  ', 'app/agent/sxfl/agent_sxfl.jsp                                                                       ', '获取默认界面                                      ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appKhcpqy           ', 'def                 ', '查询                          ', 'app/agent/app/appkhcpqy.jsp                                                                         ', '默认                                              ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appKhcpqy           ', 'list                ', '获得数据                      ', 'app/agent/app/appkhcpqy.jsp                                                                         ', '获得数据                                          ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appKhcpqy           ', 'add                 ', '添加                          ', 'app/agent/app/appkhcpqy.jsp                                                                         ', '添加                                              ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appKhcpqy           ', 'upt                 ', '更新                          ', 'app/agent/app/appkhcpqy.jsp                                                                         ', '更新                                              ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appKhcpqy           ', 'del                 ', '删除                          ', 'app/agent/app/appkhcpqy.jsp                                                                         ', '删除                                              ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appPzzl             ', 'upt                 ', '更新                          ', 'app/agent/app/apppzzl.jsp                                                                           ', '更新                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appPzzl             ', 'del                 ', '删除                          ', 'app/agent/app/apppzzl.jsp                                                                           ', '删除                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appYyxx             ', 'add                 ', '添加                          ', 'app/agent/app/appyyxx.jsp                                                                           ', '添加                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appYyxx             ', 'list                ', '获得数据                      ', 'app/agent/app/appyyxx.jsp                                                                           ', '获得数据                                          ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appYyxx             ', 'upt                 ', '更新                          ', 'app/agent/app/appyyxx.jsp                                                                           ', '更新                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appYyxx             ', 'del                 ', '删除                          ', 'app/agent/app/appyyxx.jsp                                                                           ', '删除                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appQdxx             ', 'def                 ', '查询                          ', 'app/agent/app/appqdxx.jsp                                                                           ', '默认                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appZwrq             ', 'def                 ', '查询                          ', 'app/agent/app/appzwrq.jsp                                                                           ', '默认                                              ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appKhxx             ', 'def                 ', '查询                          ', 'app/agent/app/appkhxx.jsp                                                                           ', '默认                                              ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appZwrq             ', 'upt                 ', '更新                          ', 'app/agent/app/appzwrq.jsp                                                                           ', '更新                                              ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appZwrq             ', 'list                ', '获得数据                      ', 'app/agent/app/appzwrq.jsp                                                                           ', '获得数据                                          ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appKhxx             ', 'list                ', '获得数据                      ', 'app/agent/app/appkhxx.jsp                                                                           ', '获得数据                                          ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appKhxx             ', 'add                 ', '添加更新                      ', 'app/agent/app/appkhxx.jsp                                                                           ', '添加更新                                          ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appKhxx             ', 'del                 ', '删除                          ', 'app/agent/app/appkhxx.jsp                                                                           ', '删除                                              ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appRwjk             ', 'def                 ', '查询                          ', 'app/agent/app/apprwjk.jsp                                                                           ', '默认                                              ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appRwjk             ', 'list                ', '获得数据                      ', 'app/agent/app/apprwjk.jsp                                                                           ', '获得数据                                          ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appDict             ', 'def                 ', '查询                          ', 'app/agent/app/appdict.jsp                                                                           ', '默认                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appDict             ', 'list                ', '获得数据                      ', 'app/agent/app/appdict.jsp                                                                           ', '获得数据                                          ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appDict             ', 'add                 ', '添加更新                      ', 'app/agent/app/appdict.jsp                                                                           ', '添加更新                                          ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCskz             ', 'def                 ', '查询                          ', 'app/agent/app/appcskz.jsp                                                                           ', '默认                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCskz             ', 'list                ', '获得数据                      ', 'app/agent/app/appcskz.jsp                                                                           ', '获得数据                                          ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCskz             ', 'upt                 ', '更新数据                      ', 'app/agent/app/appcskz.jsp                                                                           ', '更新数据                                          ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCskz             ', 'del                 ', '删除数据                      ', 'app/agent/app/appcskz.jsp                                                                           ', '删除数据                                          ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appQdxx             ', 'add                 ', '添加                          ', 'app/agent/app/appqdxx.jsp                                                                           ', '添加                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appQdxx             ', 'list                ', '获得数据                      ', 'app/agent/app/appqdxx.jsp                                                                           ', '获得数据                                          ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appQdxx             ', 'upt                 ', '更新                          ', 'app/agent/app/appqdxx.jsp                                                                           ', '更新                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appQdxx             ', 'del                 ', '删除                          ', 'app/agent/app/appqdxx.jsp                                                                           ', '删除                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appDwxx             ', 'def                 ', '查询                          ', 'app/agent/app/appdwxx.jsp                                                                           ', '默认                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appDwxx             ', 'list                ', '获得数据                      ', 'app/agent/app/appdwxx.jsp                                                                           ', '获得数据                                          ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appDwxx             ', 'upt                 ', '更新                          ', 'app/agent/app/appdwxx.jsp                                                                           ', '更新                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appMj               ', 'list                ', '获得树结构                    ', 'app/agent/app/appmj.jsp                                                                             ', '获得树结构                                        ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appMj               ', 'load                ', '获得单个属性                  ', 'app/agent/app/appmj.jsp                                                                             ', '获得单个属性                                      ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appMj               ', 'listsx              ', '获得枚举属性                  ', 'app/agent/app/appmj.jsp                                                                             ', '获得枚举属性                                      ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appMj               ', 'uptsj               ', '更新枚举数据                  ', 'app/agent/app/appmj.jsp                                                                             ', '更新枚举数据                                      ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appMj               ', 'delsj               ', '获得树结构                    ', 'app/agent/app/appmj.jsp                                                                             ', '获得树结构                                        ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appMj               ', 'addsj               ', '获得树结构                    ', 'app/agent/app/appmj.jsp                                                                             ', '获得树结构                                        ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appMj               ', 'listsj              ', '获得树结构                    ', 'app/agent/app/appmj.jsp                                                                             ', '获得树结构                                        ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appMj               ', 'add                 ', '获得树结构                    ', 'app/agent/app/appmj.jsp                                                                             ', '获得树结构                                        ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appMj               ', 'del                 ', '获得树结构                    ', 'app/agent/app/appmj.jsp                                                                             ', '获得树结构                                        ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpxx             ', 'get                 ', '获得套用信息                  ', 'app/agent/app/appcpxx.jsp                                                                           ', '获得套用信息                                      ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appOrg              ', 'def                 ', '默认                          ', 'app/agent/app/apppzzl.jsp                                                                           ', '默认                                              ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpxx             ', 'copy                ', '套用产品                      ', 'app/agent/app/appcpxx.jsp                                                                           ', '套用产品                                          ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpjg             ', 'upt                 ', '更新                          ', 'app/agent/app/appcpjg.jsp                                                                           ', '更新                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpjg             ', 'add                 ', '添加                          ', 'app/agent/app/appcpjg.jsp                                                                           ', '添加                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpjg             ', 'list                ', '获得数据                      ', 'app/agent/app/appcpjg.jsp                                                                           ', '获得数据                                          ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpjg             ', 'def                 ', '查询                          ', 'app/agent/app/appcpjg.jsp                                                                           ', '默认                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCptx             ', 'del                 ', '删除                          ', 'app/agent/app/appcptx.jsp                                                                           ', '删除                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCptx             ', 'upt                 ', '更新                          ', 'app/agent/app/appcptx.jsp                                                                           ', '更新                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCptx             ', 'add                 ', '添加                          ', 'app/agent/app/appcptx.jsp                                                                           ', '添加                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCptx             ', 'list                ', '获得数据                      ', 'app/agent/app/appcptx.jsp                                                                           ', '获得数据                                          ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCptx             ', 'def                 ', '查询                          ', 'app/agent/app/appcptx.jsp                                                                           ', '默认                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpqd             ', 'del                 ', '删除                          ', 'app/agent/app/appcpqd.jsp                                                                           ', '删除                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpqd             ', 'upt                 ', '更新                          ', 'app/agent/app/appcpqd.jsp                                                                           ', '更新                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpqd             ', 'add                 ', '添加                          ', 'app/agent/app/appcpqd.jsp                                                                           ', '添加                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpqd             ', 'list                ', '获得数据                      ', 'app/agent/app/appcpqd.jsp                                                                           ', '获得数据                                          ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpqd             ', 'def                 ', '查询                          ', 'app/agent/app/appcpqd.jsp                                                                           ', '默认                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpdc             ', 'def                 ', '默认                          ', 'app/agent/app/appcpdc.jsp                                                                           ', '默认                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpdc             ', 'down                ', '导出                          ', 'app/agent/app/appcpdc.jsp                                                                           ', '导出                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appSjdr             ', 'def                 ', '默认                          ', 'app/agent/app/appsjdr.jsp                                                                           ', '默认                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appSjdr             ', 'up                  ', '导入                          ', 'app/agent/app/appsjdr.jsp                                                                           ', '导入                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appYyxx             ', 'def                 ', '查询                          ', 'app/agent/app/appyyxx.jsp                                                                           ', '默认                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpxx             ', 'add                 ', '添加更新                      ', 'app/agent/app/appcpxx.jsp                                                                           ', '添加更新                                          ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appXlkz             ', 'def                 ', '查询                          ', 'app/agent/app/appxlkz.jsp                                                                           ', '默认                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appXlkz             ', 'list                ', '获得数据                      ', 'app/agent/app/appxlkz.jsp                                                                           ', '获得数据                                          ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appXlkz             ', 'add                 ', '添加                          ', 'app/agent/app/appxlkz.jsp                                                                           ', '添加                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appXlkz             ', 'upt                 ', '更新                          ', 'app/agent/app/appxlkz.jsp                                                                           ', '更新                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appXlkz             ', 'del                 ', '删除                          ', 'app/agent/app/appxlkz.jsp                                                                           ', '删除                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appYydc             ', 'def                 ', '默认                          ', 'app/agent/app/appyydc.jsp                                                                           ', '默认                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appYydc             ', 'down                ', '导出                          ', 'app/agent/app/appyydc.jsp                                                                           ', '导出                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appJyxx             ', 'list                ', '获得数据                      ', 'app/agent/app/appjyxx.jsp                                                                           ', '获得数据                                          ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpjg             ', 'org                 ', '获得机构树                    ', 'app/agent/app/appcpjg.jsp                                                                           ', '获得机构树                                        ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpdzxd           ', 'def                 ', '默认                          ', 'app/agent/app/appcpdzxd.jsp                                                                         ', '默认                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpdzxd           ', 'ok                  ', '模板套用                      ', 'app/agent/app/appcpdzxd.jsp                                                                         ', '模板套用                                          ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appJyxx             ', 'def                 ', '查询                          ', 'app/agent/app/appjyxx.jsp                                                                           ', '默认                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appJyxx             ', 'add                 ', '添加更新                      ', 'app/agent/app/appjyxx.jsp                                                                           ', '添加更新                                          ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appJyxx             ', 'del                 ', '删除                          ', 'app/agent/app/appjyxx.jsp                                                                           ', '删除                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpSxfgx          ', 'def                 ', '默认交易                      ', 'app/agent/sxfl/agent_cpsxfgx.jsp                                                                    ', '获取界面                                          ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpSxfgx          ', 'add                 ', '新增记录                      ', 'app/agent/sxfl/agent_cpsxfgx.jsp                                                                    ', '新增记录                                          ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpSxfgx          ', 'del                 ', '删除记录                      ', 'app/agent/sxfl/agent_cpsxfgx.jsp                                                                    ', '删除记录                                          ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appDict             ', 'del                 ', '删除                          ', 'app/agent/app/appdict.jsp                                                                           ', '删除                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appDwcpxy           ', 'del                 ', '删除                          ', 'app/agent/app/appdwcpxy.jsp                                                                         ', '删除                                              ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appDwcpxy           ', 'upt                 ', '更新                          ', 'app/agent/app/appdwcpxy.jsp                                                                         ', '更新                                              ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appDwcpxy           ', 'add                 ', '添加                          ', 'app/agent/app/appdwcpxy.jsp                                                                         ', '添加                                              ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appDwcpxy           ', 'list                ', '获得数据                      ', 'app/agent/app/appdwcpxy.jsp                                                                         ', '获得数据                                          ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appDwcpxy           ', 'def                 ', '查询                          ', 'app/agent/app/appdwcpxy.jsp                                                                         ', '默认                                              ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appTxxx             ', 'del                 ', '删除                          ', 'app/agent/app/apptxxx.jsp                                                                           ', '删除                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appTxxx             ', 'def                 ', '查询                          ', 'app/agent/app/apptxxx.jsp                                                                           ', '默认                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appTxxx             ', 'list                ', '获得数据                      ', 'app/agent/app/apptxxx.jsp                                                                           ', '获得数据                                          ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appTxxx             ', 'add                 ', '添加                          ', 'app/agent/app/apptxxx.jsp                                                                           ', '添加                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appTxxx             ', 'upt                 ', '更新                          ', 'app/agent/app/apptxxx.jsp                                                                           ', '更新                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCppz             ', 'def                 ', '查询                          ', 'app/agent/app/appcppz.jsp                                                                           ', '查询                                              ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpjy             ', 'list                ', '获得数据                      ', 'app/agent/app/appcpjy.jsp                                                                           ', '获得数据                                          ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpjy             ', 'add                 ', '添加                          ', 'app/agent/app/appcpjy.jsp                                                                           ', '添加                                              ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpjy             ', 'del                 ', '删除                          ', 'app/agent/app/appcpjy.jsp                                                                           ', '删除                                              ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appSxfl             ', 'add                 ', '新增记录                      ', 'app/agent/sxfl/agent_sxfl.jsp                                                                       ', '新增记录                                          ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appSxfl             ', 'del                 ', '删除记录                      ', 'app/agent/sxfl/agent_sxfl.jsp                                                                       ', '删除记录                                          ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appSxfl             ', 'upt                 ', '更新记录                      ', 'app/agent/sxfl/agent_sxfl.jsp                                                                       ', '更新记录                                          ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpSxfgx          ', 'lst                 ', '显示数据                      ', 'app/agent/sxfl/agent_cpsxfgx.jsp                                                                    ', '显示数据                                          ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appSxfkz            ', 'lst                 ', '显示数据                      ', 'app/agent/sxfl/agent_cpsxfkz.jsp                                                                    ', '显示数据                                          ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appSxfl             ', 'lst                 ', '显示数据                      ', 'app/agent/sxfl/agent_sxfl.jsp                                                                       ', '显示数据                                          ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCppz             ', 'add                 ', '添加                          ', 'app/agent/app/appcppz.jsp                                                                           ', '添加                                              ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCppz             ', 'del                 ', '删除                          ', 'app/agent/app/appcppz.jsp                                                                           ', '删除                                              ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpjy             ', 'def                 ', '查询                          ', 'app/agent/app/appcpjy.jsp                                                                           ', '查询                                              ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCppz             ', 'list                ', '获得数据                      ', 'app/agent/app/appcppz.jsp                                                                           ', '获得数据                                          ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appYydc             ', 'ywdown              ', '业务应用导出                  ', 'app/agent/app/appyydc.jsp                                                                           ', '业务应用导出                                      ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appKzxx             ', 'del                 ', '删除                          ', 'app/agent/app/appkzxx.jsp                                                                           ', '删除                                              ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appLs               ', 'def                 ', '默认                          ', 'app/agent/app/appls.jsp                                                                             ', '默认                                              ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appLs               ', 'list                ', '查询                          ', 'app/agent/app/appls.jsp                                                                             ', '查询                                              ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appMj               ', 'def                 ', '查询                          ', 'app/agent/app/appmj.jsp                                                                             ', '查询                                              ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpxx             ', 'def                 ', '查询                          ', 'app/agent/app/appcpxx.jsp                                                                           ', '默认                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpjg             ', 'listone             ', '查询详细信息                  ', 'app/agent/app/appcpjg.jsp                                                                           ', '查询详细信息                                      ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('AppCpjygydbedkz     ', 'def                 ', '默认页面                      ', 'app/agent/app/appcpjygydbedkz.jsp                                                                   ', '默认页面                                          ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('AppCpjygydbedkz     ', 'add                 ', '添加                          ', 'app/agent/app/appcpjygydbedkz.jsp                                                                   ', '添加                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('AppCpjygydbedkz     ', 'del                 ', '删除                          ', 'app/agent/app/appcpjygydbedkz.jsp                                                                   ', '删除                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('AppCpjygydbedkz     ', 'list                ', '查询                          ', 'app/agent/app/appcpjygydbedkz.jsp                                                                   ', '查询                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appGyjyqxkz         ', 'def                 ', '默认页面                      ', 'app/agent/app/appgyjyqxkz.jsp                                                                       ', '默认页面                                          ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appGyjyqxkz         ', 'add                 ', '添加                          ', 'app/agent/app/appgyjyqxkz.jsp                                                                       ', '添加                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appGyjyqxkz         ', 'list                ', '查询                          ', 'app/agent/app/appgyjyqxkz.jsp                                                                       ', '查询                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appGyjyqxkz         ', 'del                 ', '删除                          ', 'app/agent/app/appgyjyqxkz.jsp                                                                       ', '删除                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appRzpz             ', 'def                 ', '默认页面                      ', 'app/agent/app/apprzpz.jsp                                                                           ', '默认页面                                          ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appRzpz             ', 'add                 ', '添加                          ', 'app/agent/app/apprzpz.jsp                                                                           ', '添加                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appRzpz             ', 'del                 ', '删除                          ', 'app/agent/app/apprzpz.jsp                                                                           ', '删除                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appRzpz             ', 'list                ', '查询                          ', 'app/agent/app/apprzpz.jsp                                                                           ', '查询                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appJgedkz           ', 'def                 ', '默认页面                      ', 'app/agent/app/appjgedkz.jsp                                                                         ', '默认页面                                          ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appJgedkz           ', 'list                ', '查询                          ', 'app/agent/app/appjgedkz.jsp                                                                         ', '查询                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appJgedkz           ', 'add                 ', '添加                          ', 'app/agent/app/appjgedkz.jsp                                                                         ', '添加                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appJgedkz           ', 'del                 ', '删除                          ', 'app/agent/app/appjgedkz.jsp                                                                         ', '删除                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appJgedkz           ', 'getJgkzfs           ', '获得机构额度控制方式          ', 'app/agent/app/appjgedkz.jsp                                                                         ', '获得机构额度控制方式                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appGyedkz           ', 'def                 ', '默认                          ', 'app/agent/app/appgyedkz.jsp                                                                         ', '默认                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appGyedkz           ', 'del                 ', '删除                          ', 'app/agent/app/appgyedkz.jsp                                                                         ', '删除                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appGyedkz           ', 'add                 ', '添加                          ', 'app/agent/app/appgyedkz.jsp                                                                         ', '添加                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appGyedkz           ', 'list                ', '查询                          ', 'app/agent/app/appgyedkz.jsp                                                                         ', '查询                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appGyedkz           ', 'getGykzfs           ', '获得柜员交易额度控制方式      ', 'app/agent/app/appgyedkz.jsp                                                                         ', '获得柜员交易额度控制方式                          ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appGyjyqxkz         ', 'getGygwjbkz         ', '获取柜员岗位控制标志          ', 'about:blank                                                                                         ', '获取柜员岗位控制标志                              ', 'V2.1.app  ', NULL, NULL, NULL);


INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(24, 'dateReport          ', '重要单证出库单                ', '3 ', '6', NULL, NULL, '1', 'com.hundsun.agent.web.app.sendUtil.PzXtwCkReport                                                                                                                                    ', 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(23, 'dateReport          ', '重要单证入库单                ', '3 ', '6', NULL, NULL, '1', 'com.hundsun.agent.web.app.sendUtil.PzXtwRkReport                                                                                                                                    ', 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(28, 'dataReport          ', '重要单证销毁清单              ', '3 ', '6', NULL, NULL, '1', 'com.hundsun.agent.web.app.sendUtil.PzTzReport                                                                                                                                       ', 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(25, 'dataReport          ', '网点划拨单                    ', '3 ', '6', NULL, NULL, '1', 'com.hundsun.agent.web.app.sendUtil.PzHuabReport                                                                                                                                     ', 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(26, 'dataReport          ', '网点回拨单                    ', '3 ', '6', NULL, NULL, '1', 'com.hundsun.agent.web.app.sendUtil.PzHbReport                                                                                                                                       ', 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(29, 'dataReport          ', '重要单证撤销单                ', '3 ', '6', NULL, NULL, '1', 'com.hundsun.agent.web.app.sendUtil.PzCkCxReport                                                                                                                                     ', 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(30, 'dataReport          ', '重要单证撤销单                ', '3 ', '6', NULL, NULL, '1', 'com.hundsun.agent.web.app.sendUtil.PzRkCxReport                                                                                                                                     ', 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(30, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(30, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(30, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(30, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(11, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(11, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(7, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(7, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(6, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(6, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(6, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(3, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(3, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(2, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(2, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(2, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(20, 'qldbh               ', '请领单编号                    ', '3 ', '0', NULL, '/tamc/resp/         ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(1, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(20, 'qldbh               ', '请领单编号                    ', '3 ', '0', NULL, '/tamc/resp/         ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(1, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(22, 'pzmd                ', '凭证目的                      ', '8 ', '0', NULL, NULL, '0', NULL, 'V2.1.app  ', NULL, '1                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(22, 'pzly                ', '凭证来源                      ', '7 ', '0', NULL, NULL, '0', NULL, 'V2.1.app  ', NULL, '1                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(22, 'pzsl                ', '凭证数量                      ', '6 ', '0', NULL, NULL, '0', NULL, 'V2.1.app  ', NULL, '1                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(22, 'pzzl                ', '凭证种类                      ', '5 ', '0', NULL, NULL, '0', NULL, 'V2.1.app  ', NULL, '1                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(22, 'qldzt               ', '请领单状态                    ', '4 ', '0', NULL, NULL, '0', NULL, 'V2.1.app  ', NULL, '1                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(22, 'qlsj                ', '请领时间                      ', '2 ', '0', NULL, NULL, '0', NULL, 'V2.1.app  ', NULL, '1                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(22, 'qlrq                ', '请领日期                      ', '1 ', '0', NULL, NULL, '0', NULL, 'V2.1.app  ', NULL, '1                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(22, 'qldbh               ', '请领单编号                    ', '3 ', '0', NULL, NULL, '0', NULL, 'V2.1.app  ', NULL, '1                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(1, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(22, 'icount              ', '记录条数                      ', '9 ', '0', NULL, '/tamc/resp/         ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(1, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(12, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(4, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(11, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(id, return_id, return_name, order_id, value_type, file_ext, super_path, ret_type, dict, version, note, bak1, bak2, bak3, bak4, bak5, bak6)
  VALUES(11, 'cch                 ', '场次号                        ', '4 ', '0', '          ', '/tamc/resp/         ', '0', '                                                                                                                                                                                    ', 'V2.1.app  ', '                                                                                                    ', '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(id, return_id, return_name, order_id, value_type, file_ext, super_path, ret_type, dict, version, note, bak1, bak2, bak3, bak4, bak5, bak6)
  VALUES(11, 'jqrq                ', '机器日期                      ', '6 ', '0', '          ', '/tamc/resp/         ', '0', '                                                                                                                                                                                    ', 'V2.1.app  ', '                                                                                                    ', '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(id, return_id, return_name, order_id, value_type, file_ext, super_path, ret_type, dict, version, note, bak1, bak2, bak3, bak4, bak5, bak6)
  VALUES(11, 'lsh                 ', '业务流水号                    ', '5 ', '0', '          ', '/tamc/resp/         ', '0', '                                                                                                                                                                                    ', 'V2.1.app  ', '                                                                                                    ', '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(id, return_id, return_name, order_id, value_type, file_ext, super_path, ret_type, dict, version, note, bak1, bak2, bak3, bak4, bak5, bak6)
  VALUES(11, 'ywrq                ', '业务日期                      ', '3 ', '0', '          ', '/tamc/resp/         ', '0', '                                                                                                                                                                                    ', 'V2.1.app  ', '                                                                                                    ', '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(27, 'wjmc                ', '文件                          ', '3 ', '4', NULL, '/tamc/resp/         ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(27, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(27, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(27, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(27, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(6, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(3, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(21, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(11, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(7, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(7, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(21, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(3, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(2, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(12, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(12, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(12, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(5, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(28, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(28, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(28, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(28, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(4, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(8, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(8, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(8, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(20, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(20, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(20, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(22, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(23, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(23, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(23, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(23, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(24, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(24, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(24, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(24, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(25, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(25, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(25, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(25, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(26, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(26, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(26, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(26, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(4, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(4, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(5, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(5, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(5, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(8, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(20, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(21, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(29, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(21, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(22, 'zwrq                ', '平台帐务日期                  ', '11', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(22, 'zhqzlsh             ', '平台流水号                    ', '10', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(22, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(29, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(29, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(29, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(305, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', '          ', '/pub/               ', '1', '                                                                                                                                                                                    ', 'V2.1.app  ', '                                                                                                    ', '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(305, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', '          ', '/pub/               ', '0', '                                                                                                                                                                                    ', 'V2.1.app  ', '                                                                                                    ', '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(305, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', '          ', '/pub/               ', '1', '                                                                                                                                                                                    ', 'V2.1.app  ', '                                                                                                    ', '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(305, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', '          ', '/pub/               ', '0', '                                                                                                                                                                                    ', 'V2.1.app  ', '                                                                                                    ', '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(306, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', '          ', '/pub/               ', '1', '                                                                                                                                                                                    ', 'V2.1.app  ', '                                                                                                    ', '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(306, 'zhqzlsh             ', '平台流水号                    ', '1 ', '0', '          ', '/pub/               ', '0', '                                                                                                                                                                                    ', 'V2.1.app  ', '                                                                                                    ', '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(306, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', '          ', '/pub/               ', '1', '                                                                                                                                                                                    ', 'V2.1.app  ', '                                                                                                    ', '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(306, 'zwrq                ', '平台帐务日期                  ', '2 ', '0', '          ', '/pub/               ', '0', '                                                                                                                                                                                    ', 'V2.1.app  ', '                                                                                                    ', '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(304, 'wjnr                ', '文件内容                      ', '1 ', '0', '          ', '                    ', '0', '                                                                                                                                                                                    ', 'V2.1.app  ', '                                                                                                    ', '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(304, 'wjmc                ', '文件名称                      ', '2 ', '2', '          ', '                    ', '0', '                                                                                                                                                                                    ', 'V2.1.app  ', '                                                                                                    ', '0                             ', NULL, NULL, NULL, NULL, NULL);


INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(22, 'qsrq                ', '起始日期                      ', '3', '2 ', '1', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(29, 'jshm                ', '结束号码                      ', '1', '4 ', '0', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(29, 'tzlx                ', '调整类型                      ', '6', '5 ', '1', NULL, NULL, '2                                                                                                   ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(29, 'qshm                ', '起始号码                      ', '1', '3 ', '0', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(29, 'pzsl                ', '凭证数量                      ', '7', '2 ', '1', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(29, 'pzzl                ', '凭证种类                      ', '5', '1 ', '1', NULL, NULL, 'com.hundsun.agent.web.app.sendUtil.Pzrk_PzzlSend                                                    ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(1, 'qtbz                ', '启停标志                      ', '0', '3 ', '1', NULL, NULL, 'agent_send_qtbz                                                                                     ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(2, 'qtqdbs              ', '待启停渠道标识                ', '9', '1 ', '1', NULL, NULL, 'app_qdxx:qdbs:qdmc:qdbs<>''200'':true:false                                                           ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(3, 'qtyybs              ', '待启停应用标识                ', '9', '1 ', '1', NULL, NULL, 'app_yyxx:yybs:yymc::true:false                                                                      ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(7, 'czdx                ', '操作对象                      ', '1', '1 ', '1', NULL, NULL, NULL, 'V2.1.app  ', '恢复库表名                                                                                          ', '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(7, 'bfwj                ', '备份文件名                    ', '1', '2 ', '1', NULL, NULL, NULL, 'V2.1.app  ', '全路径文件名                                                                                        ', '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(11, 'rqlx                ', '查询类型                      ', '2', '1 ', '1', NULL, NULL, 'agent_send_rqcxlx                                                                                   ', 'V2.1.app  ', '日期类型                                                                                            ', '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(24, 'jshm                ', '结束号码                      ', '1', '8 ', '0', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(24, 'qshm                ', '起始号码                      ', '1', '7 ', '0', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(24, 'pzsl                ', '凭证数量                      ', '7', '6 ', '1', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(24, 'pzmd                ', '凭证目的                      ', '4', '3 ', '1', NULL, NULL, 'org:all                                                                                             ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(24, 'czlx                ', '操作类型                      ', '2', '2 ', '1', 'onChange:Topzmd(this.value)                                                                         ', NULL, 'send_czlx                                                                                           ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(25, 'jshm                ', '结束号码                      ', '1', '6 ', '0', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(25, 'qshm                ', '起始号码                      ', '1', '5 ', '0', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(25, 'pzsl                ', '凭证数量                      ', '7', '4 ', '1', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(26, 'pzsl                ', '凭证数量                      ', '7', '4 ', '1', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(26, 'qshm                ', '起始号码                      ', '1', '5 ', '0', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(26, 'jshm                ', '结束号码                      ', '1', '6 ', '0', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(26, 'dfgy                ', '对方柜员                      ', '1', '1 ', '1', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(23, 'pzzl                ', '凭证种类                      ', '5', '4 ', '1', NULL, NULL, 'com.hundsun.agent.web.app.sendUtil.Pzrk_PzzlSend                                                    ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(24, 'pzzl                ', '凭证种类                      ', '5', '5 ', '1', NULL, NULL, 'com.hundsun.agent.web.app.sendUtil.Pzrk_PzzlSend                                                    ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(25, 'pzzl                ', '凭证种类                      ', '5', '3 ', '1', NULL, NULL, 'com.hundsun.agent.web.app.sendUtil.Pzrk_PzzlSend                                                    ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(26, 'pzzl                ', '凭证种类                      ', '5', '3 ', '1', NULL, NULL, 'com.hundsun.agent.web.app.sendUtil.Pzrk_PzzlSend                                                    ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(20, 'qlsl                ', '请领数量                      ', '7', '2 ', '1', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(24, 'qldbh               ', '请领单编号                    ', '1', '1 ', '0', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(25, 'dfgy                ', '对方柜员                      ', '1', '1 ', '1', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(27, 'pzzl                ', '凭证种类                      ', '5', '1 ', '0', NULL, NULL, 'com.hundsun.agent.web.app.sendUtil.Pzrk_PzzlSend                                                    ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(27, 'pzzt                ', '凭证状态                      ', '2', '2 ', '0', NULL, NULL, 'agent_send_pzzt                                                                                     ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(27, 'jgfs                ', '结果方式                      ', '2', '3 ', '1', NULL, NULL, 'agent_jgfs                                                                                          ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(28, 'pzzl                ', '凭证种类                      ', '5', '1 ', '1', NULL, NULL, 'com.hundsun.agent.web.app.sendUtil.Pzrk_PzzlSend                                                    ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(28, 'pzsl                ', '凭证数量                      ', '7', '2 ', '1', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(20, 'zysm                ', '摘要说明                      ', '8', '4 ', '0', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(22, 'qldzt               ', '请领单状态                    ', '2', '4 ', '0', NULL, NULL, 'agent_send_qldzt                                                                                    ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(27, 'qshm                ', '起始号码                      ', '1', '6 ', '0', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(27, 'jshm                ', '结束号码                      ', '1', '7 ', '0', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(28, 'ypzzt               ', '原凭证状态                    ', '0', '6 ', '1', NULL, NULL, 'app_pz_tzlx                                                                                         ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(22, 'pzzl                ', '凭证种类                      ', '9', '1 ', '0', NULL, NULL, 'app_pzzl:pzzl:pzmc::true:false                                                                      ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(23, 'czlx                ', '操作类型                      ', '2', '1 ', '1', 'onChange:Topzly(this.value)                                                                         ', NULL, 'send_czlx                                                                                           ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(11, 'cpdm                ', '产品代码                      ', '9', '2 ', '0', NULL, NULL, 'app_cpxx:cpdm:cpmc::true:false                                                                      ', 'V2.1.app  ', '查询类型为 2：产品业务日期  时必输                                                                  ', '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(20, 'pzzl                ', '凭证种类                      ', '5', '1 ', '1', NULL, NULL, 'com.hundsun.agent.web.app.sendUtil.PzzlSend                                                         ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(12, 'rq                  ', '日期                          ', '3', '1 ', '1', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(12, 'jrbz                ', '节假日标志                    ', '2', '2 ', '1', NULL, NULL, 'is_null                                                                                             ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(8, 'yybs                ', '应用标识                      ', '6', '1 ', '1', NULL, NULL, '001                                                                                                 ', 'V2.1.app  ', '                                                                                                    ', '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(8, 'rqrq                ', '日切日期                      ', '3', '2 ', '0', NULL, NULL, NULL, 'V2.1.app  ', '日切后日期                                                                                          ', '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(20, 'dfjg                ', '对方机构                      ', '4', '3 ', '1', NULL, NULL, 'org:all                                                                                             ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(21, 'qldbh               ', '请领单编号                    ', '1', '1 ', '1', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(23, 'pzly                ', '凭证来源                      ', '4', '2 ', '1', NULL, NULL, 'org:all                                                                                             ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(23, 'pzsl                ', '凭证数量                      ', '7', '5 ', '1', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(23, 'qshm                ', '起始号码                      ', '1', '6 ', '0', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(23, 'jshm                ', '结束号码                      ', '1', '7 ', '0', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(27, 'pzgy                ', '凭证柜员                      ', '1', '4 ', '0', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(27, 'pzjg                ', '凭证机构                      ', '1', '5 ', '0', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(28, 'qshm                ', '起始号码                      ', '1', '3 ', '0', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(1, 'qtyybs              ', '应用标识                      ', '5', '1 ', '1', NULL, NULL, 'com.hundsun.agent.web.app.sendUtil.Yybs_JydmSend                                                    ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(28, 'tzlx                ', '调整类型                      ', '0', '5 ', '1', NULL, NULL, 'app_pz_tzlx                                                                                         ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(1, 'qtjydm              ', '交易代码                      ', '2', '2 ', '1', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(2, 'qtbz                ', '启停标志                      ', '0', '2 ', '1', NULL, NULL, 'agent_send_qtbz                                                                                     ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(6, 'bfrq                ', '备份日期                      ', '3', '2 ', '1', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(3, 'qtbz                ', '启停标志                      ', '0', '2 ', '1', NULL, NULL, 'agent_send_qtbz                                                                                     ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(6, 'bfyybs              ', '备份应用标识                  ', '9', '1 ', '1', NULL, NULL, 'app_yyxx:yybs:yymc::true:false                                                                      ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(4, 'gdrq                ', '归档日期                      ', '3', '2 ', '1', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(22, 'jsrq                ', '结束日期                      ', '3', '3 ', '1', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(20, 'pkey                ', 'pkey                          ', '6', '7 ', '0', NULL, NULL, 'K_CPZT                                                                                              ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(30, 'pzzl                ', '凭证种类                      ', '5', '1 ', '1', NULL, NULL, 'com.hundsun.agent.web.app.sendUtil.Pzrk_PzzlSend                                                    ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(30, 'pzsl                ', '凭证数量                      ', '7', '3 ', '1', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(30, 'qshm                ', '起始号码                      ', '1', '4 ', '0', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(30, 'pzly                ', '凭证来源                      ', '4', '2 ', '1', NULL, NULL, 'org:all                                                                                             ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(30, 'jshm                ', '结束号码                      ', '1', '5 ', '0', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(28, 'jshm                ', '结束号码                      ', '1', '4 ', '0', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(4, 'gdyybs              ', '待归档应用标识                ', '9', '1 ', '1', NULL, NULL, 'app_yyxx:yybs:yymc::true:false                                                                      ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(5, 'qlyybs              ', '清理应用标识                  ', '9', '1 ', '1', NULL, NULL, 'app_yyxx:yybs:yymc::true:false                                                                      ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(5, 'qlrq                ', '清理日期                      ', '3', '2 ', '1', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(305, 'qtyybs              ', '应用标识                      ', '5', '1 ', '1', '                                                                                                    ', '                    ', 'com.hundsun.agent.web.app.sendUtil.Yybs_CpdmSend                                                    ', 'V2.1.app  ', '                                                                                                    ', '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(29, 'pzmd                ', '凭证目的                      ', '4', '6 ', '0', '                                                                                                    ', '                    ', '                                                                                                    ', 'V2.1.app  ', '                                                                                                    ', '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(305, 'qtjydm              ', '交易代码                      ', '2', '3 ', '1', '                                                                                                    ', '                    ', '                                                                                                    ', 'V2.1.app  ', '                                                                                                    ', '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(304, 'shell               ', 'shell命令                     ', '1', '1 ', '1', '                                                                                                    ', '                    ', '                                                                                                    ', 'V2.1.app  ', '                                                                                                    ', '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(305, 'qtcpdm              ', '产品代码                      ', '5', '2 ', '1', '                                                                                                    ', '                    ', 'com.hundsun.agent.web.app.sendUtil.Cpbs_JydmSend                                                    ', 'V2.1.app  ', '                                                                                                    ', '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(305, 'qtbz                ', '启停标志                      ', '0', '4 ', '1', '                                                                                                    ', '                    ', 'agent_send_qtbz                                                                                     ', 'V2.1.app  ', '                                                                                                    ', '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(306, 'qtyybs              ', '应用标识                      ', '5', '1 ', '1', '                                                                                                    ', '                    ', 'com.hundsun.agent.web.app.sendUtil.Yybs_Cpdm_Send                                                   ', 'V2.1.app  ', '                                                                                                    ', '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(306, 'qtcpdm              ', '产品代码                      ', '5', '2 ', '1', '                                                                                                    ', '                    ', 'com.hundsun.agent.web.app.sendUtil.Cpdm_YwbhSend                                                    ', 'V2.1.app  ', '                                                                                                    ', '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(306, 'qtbz                ', '启停标志                      ', '0', '4 ', '1', '                                                                                                    ', '                    ', 'agent_send_qtbz                                                                                     ', 'V2.1.app  ', '                                                                                                    ', '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(306, 'qtywbh              ', '业务编号                      ', '2', '3 ', '1', '                                                                                                    ', '                    ', '                                                                                                    ', 'V2.1.app  ', '                                                                                                    ', '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(308, 'tbbz                ', '同步标志                      ', '2', '1 ', '1', '                                                                                                    ', '                    ', 'app_tbbz                                                                                            ', 'V2.1.app  ', '同步标志                                                                                            ', '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);


INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(308, '900014                        ', '机构柜员信息同步                                  ', '1', '                    ', 'admin               ', '00000               ', '100                 ', 'V2.1.app  ', '与后台同步机构信息，柜员信息', 'appXml                        ', 'appFile                       ', '                                                                                                                                                      ', '                                                                                                                                                      ', NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(117, '900027                        ', '凭证查询                                          ', '4', '/tamc/resp/         ', 'admin               ', '00000               ', '100                 ', 'V2.1.app  ', '用于凭证查询，普通柜员只能查询自己名下的凭证，机构可以查询自己名下所有柜员的凭证状态，上级机构可以查询下机构的，主管机构可以查询全行该类凭证信息。                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              ', 'appXml                        ', 'appFile                       ', NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(23, '900023                        ', '凭证入库                                          ', '1', NULL, 'admin               ', '70001               ', '100                 ', 'V2.1.app  ', '分为系统内入库及系统外入库.系统外入库由凭证主管机构操作,将第三方提供的凭证进行入库.系统内入库,如果为凭证主管机构操作,则表示将凭证经办网点归还的凭证进行入库,如果为经办网点操作,则表示将凭证主管机构的给的凭证进行入库操作.系统内入库操作需要同之前的出库交易流水进行关联,根据凭证种类的控制类型,控制数量或号码.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 ', 'appXml                        ', 'appFile                       ', 'com.hundsun.agent.web.app.sendUtil.PzrkSubmitSend                                                                                                     ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(305, '900010                        ', '产品交易服务启停                                  ', '1', '                    ', 'admin               ', '00000               ', '100                 ', 'V2.1.app  ', '', 'appXml                        ', 'appFile                       ', '                                                                                                                                                      ', '                                                                                                                                                      ', NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(306, '900013                        ', '产品业务服务启停                                 ', '1', '                    ', 'admin               ', '00000               ', '100                 ', 'V2.1.app  ', '', 'appXml                        ', 'appFile                       ', '                                                                                                                                                      ', '                                                                                                                                                      ', NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(20, '900020                        ', '凭证请领                                          ', '1', NULL, 'admin               ', '00000               ', '100                 ', 'V2.1.app  ', '经办网点根据业务开展需要，向凭证主管机构或上级机构提请请领交易，告知需要某类凭证多少张？(非必须交易)。                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          ', 'appXml                        ', 'appFile                       ', 'com.hundsun.agent.web.app.sendUtil.PzqlSubmitSend                                                                                                     ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(21, '900021                        ', '凭证请领撤消                                      ', '1', NULL, 'admin               ', '0001                ', '100                 ', 'V2.1.app  ', '经办网点根据业务需要撤消凭证请领交易                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            ', 'appXml                        ', 'appFile                       ', NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(4, '900004                        ', '数据归档                                          ', '1', NULL, 'admin               ', '70001               ', '100                 ', 'V2.1.app  ', NULL, 'appXml                        ', 'appFile                       ', NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(5, '900005                        ', '数据清理                                          ', '1', NULL, 'admin               ', '0001                ', '100                 ', 'V2.1.app  ', NULL, 'appXml                        ', 'appFile                       ', NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(24, '900024                        ', '凭证出库                                          ', '1', NULL, 'admin               ', '70001               ', '100                 ', 'V2.1.app  ', '分为系统内出库及系统外出库.系统外出库由凭证主管机构操作,将凭证归还给第三方.系统内出库,如果为凭证主管机构操作,则表示将凭证出库，后续交由经办网点归进行入库,如果为经办网点操作,则表示将凭证出库后归还给主管机构.如果存在请领编号，则需要同请领相关联，数量上要少于等于请领数量。                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  ', 'appXml                        ', 'appFile                       ', 'com.hundsun.agent.web.app.sendUtil.PzckSubmitSend                                                                                                     ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(25, '900025                        ', '凭证划拨                                          ', '1', NULL, 'admin               ', '70001               ', '100                 ', 'V2.1.app  ', '凭证划拨用于处理同一机构内网点主管将重要空白凭证分配给普通柜员的交易。该交易必须由网点主管发起。网点主管选择需划拨的单证实物的凭证种类，输入需划拨数量，起始号码,结束号码，输入对方柜员号，对方柜员确认实物数量后输入柜员密码即可划拨。                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         ', 'appXml                        ', 'appFile                       ', 'com.hundsun.agent.web.app.sendUtil.PzslSubmitSend                                                                                                     ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(2, '900003                        ', '渠道服务启停                                      ', '1', NULL, 'admin               ', '0010001             ', '100                 ', 'V2.1.app  ', NULL, 'appXml                        ', 'appFile                       ', NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(8, '900008                        ', '日切处理                                          ', '1', NULL, 'admin               ', '70001               ', '100                 ', 'V2.1.app  ', NULL, 'appXml                        ', 'appFile                       ', NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(3, '900002                        ', '应用服务启停                                      ', '1', NULL, 'admin               ', '0010001             ', '100                 ', 'V2.1.app  ', NULL, 'appXml                        ', 'appFile                       ', NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(6, '900006                        ', '数据备份                                          ', '1', NULL, 'admin               ', '0001                ', '100                 ', 'V2.1.app  ', NULL, 'appXml                        ', 'appFile                       ', NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(7, '900007                        ', '数据恢复                                          ', '1', NULL, 'admin               ', '0001                ', '100                 ', 'V2.1.app  ', NULL, 'appXml                        ', 'appFile                       ', NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(30, '900030                        ', '凭证入库撤销                                      ', '1', NULL, 'admin               ', '70001               ', '100                 ', 'V2.1.app  ', '只限系统内入库操作，系统外入库撤销通过系统外出库来实现。                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        ', 'appXml                        ', 'appFile                       ', NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(26, '900026                        ', '凭证回划                                          ', '1', NULL, 'admin               ', '70001               ', '100                 ', 'V2.1.app  ', '凭证回划用于处理同一机构内网点主管将在普通柜员名下的重要空白凭证划回的交易。该交易必须由网点主管发起，根据需回划单证实物的凭证种类、调拨数量、凭证起至号，输入拨出方柜员号，拨出方柜员确认实物数量后输入密码即可。                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              ', 'appXml                        ', 'appFile                       ', 'com.hundsun.agent.web.app.sendUtil.PzslSubmitSend                                                                                                     ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(27, '900027                        ', '凭证查询                                          ', '4', '/tamc/resp/         ', 'admin               ', '0001                ', '100                 ', 'V2.1.app  ', '用于凭证查询，普通柜员只能查询自己名下的凭证，机构可以查询自己名下所有柜员的凭证状态，上级机构可以查询下机构的，主管机构可以查询全行该类凭证信息。                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              ', 'appXml                        ', 'appFile                       ', NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(11, '900011                        ', '日期查询                                          ', '1', NULL, 'admin               ', '0001                ', '100                 ', 'V2.1.app  ', NULL, 'appXml                        ', 'appFile                       ', 'com.hundsun.agent.web.app.sendUtil.RqcxSubmitSend                                                                                                     ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(12, '900012                        ', '节假日设置                                        ', '1', NULL, 'admin               ', '0001                ', '100                 ', 'V2.1.app  ', NULL, 'appXml                        ', 'appFile                       ', NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(28, '900028                        ', '凭证调整                                          ', '1', NULL, 'admin               ', '70001               ', '100                 ', 'V2.1.app  ', '在重空凭证损坏或进行账务冲正时，柜员手工进行重要空白凭证状态处理，该交易需网点主管授权。                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        ', 'appXml                        ', 'appFile                       ', 'com.hundsun.agent.web.app.sendUtil.PzslSubmitSend                                                                                                     ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(29, '900029                        ', '凭证出库撤销                                      ', '1', NULL, 'admin               ', '70001               ', '100                 ', 'V2.1.app  ', '发生出库错误时，可以撤销出库。撤销只限系统内出库，并且对方机构未入库的情况。                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    ', 'appXml                        ', 'appFile                       ', NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(1, '900001                        ', '交易服务启停                                      ', '1', NULL, 'admin               ', '0001                ', '100                 ', 'V2.1.app  ', NULL, 'appXml                        ', 'appFile                       ', NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(22, '900022                        ', '凭证请领查询                                      ', '4', '/tamc/resp/         ', 'admin               ', '0001                ', '100                 ', 'V2.1.app  ', '查询凭证请领单,查询机构既查询作为请领发起方，又作为请领接受方的请求单信息，可以返回多条数据信息。                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               ', 'appXml                        ', 'appFile                       ', NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(304, '900040                        ', 'shell命令运行                                     ', '1', '                    ', 'admin               ', '00000               ', '100                 ', 'V2.1.app  ', '', 'appXml                        ', 'appFile                       ', '                                                                                                                                                      ', '                                                                                                                                                      ', NULL, NULL, NULL, NULL);


INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_khxx                      ', 'app_yyxxgl                    ', 4, '客户信息维护                  ', '客户信息维护                                      ', '1', 'appKhxx             ', '1', 'V2.1.app  ', NULL, '900122250000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_sxffl                     ', 'app_yyxxgl                    ', 4, '手续费费率维护                ', '手续费费率维护                                    ', '1', 'appSxfl             ', '1', 'V2.1.app  ', NULL, '900122260000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_4_sjgd                    ', 'app_3_rzcz                    ', 5, '数据归档                      ', '数据归档                                          ', '1', 'send                ', '1', 'V2.1.app  ', NULL, '900122521000        ', '0', 'agent     ', NULL, 'send_id=4                                                                                           ', NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_cppz                      ', 'app_cpmessage                 ', 4, '产品凭证关系维护              ', '产品凭证关系维护                                  ', '1', 'appCppz             ', '0', 'V2.1.app  ', NULL, '900122480000        ', '0', 'agent     ', '                              ', NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_pzgl                      ', 'app_cpgl                      ', 3, '凭证管理                      ', '凭证管理                                          ', '0', 'alterUserPass       ', '1', 'V2.1.app  ', NULL, '900122300000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('appcpjy                       ', 'app_cpmessage                 ', 4, '产品交易服务维护              ', '产品交易服务维护                                  ', '1', 'appCpjy             ', '1', 'V2.1.app  ', NULL, '900122490000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_appqdxx                   ', 'app_yyxxgl                    ', 4, '渠道信息维护                  ', '渠道信息维护                                      ', '1', 'appQdxx             ', '1', 'V2.1.app  ', NULL, '900122220000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_4_sjql                    ', 'app_3_rzcz                    ', 5, '数据清理                      ', '数据清理                                          ', '1', 'send                ', '1', 'V2.1.app  ', NULL, '900122522000        ', '0', 'agent     ', NULL, 'send_id=5                                                                                           ', NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_pzck                      ', 'app_pzgl                      ', 4, '凭证出库                      ', '凭证出库                                          ', '1', 'send                ', '1', 'V2.1.app  ', NULL, '900122350000        ', '0', 'agent     ', NULL, 'send_id=24                                                                                          ', NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_pzhb                      ', 'app_pzgl                      ', 4, '凭证划拨                      ', '凭证划拨                                          ', '1', 'send                ', '1', 'V2.1.app  ', NULL, '900122360000        ', '0', 'agent     ', NULL, 'send_id=25                                                                                          ', NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_pzhh                      ', 'app_pzgl                      ', 4, '凭证回划                      ', '凭证回划                                          ', '1', 'send                ', '1', 'V2.1.app  ', NULL, '900122370000        ', '0', 'agent     ', NULL, 'send_id=26                                                                                          ', NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_pzcx                      ', 'app_pzgl                      ', 4, '凭证查询                      ', '凭证查询                                          ', '1', 'send                ', '1', 'V2.1.app  ', NULL, '900122380000        ', '0', 'agent     ', NULL, 'send_id=27                                                                                          ', NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_pztz                      ', 'app_pzgl                      ', 4, '凭证调整                      ', '凭证调整                                          ', '1', 'send                ', '1', 'V2.1.app  ', NULL, '900122390000        ', '0', 'agent     ', NULL, 'send_id=28                                                                                          ', NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_rc_fw_yyqt                ', 'app_rcgl_qtcz                 ', 5, '应用服务启停                  ', '应用服务启停                                      ', '1', 'send                ', '1', 'V2.1.app  ', NULL, '900122513000        ', '0', 'agent     ', NULL, 'send_id=3                                                                                           ', NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_appdict                   ', 'app_jbcsgl                    ', 4, '业务字典维护                  ', '业务字典维护                                      ', '1', 'appDict             ', '1', 'V2.1.app  ', NULL, '900122110000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_cspz                      ', 'app_jbcsgl                    ', 4, '参数配置维护                  ', '参数配置维护                                      ', '1', 'appCskz             ', '1', 'V2.1.app  ', NULL, '900122120000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_cpdc                      ', 'app_drdc                      ', 4, '产品应用导出                  ', '产品应用导出                                      ', '1', 'appCpdc             ', '1', 'V2.1.app  ', NULL, '900122620000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_yydcagent                 ', 'app_drdc                      ', 4, '应用信息导出                  ', '应用信息导出                                      ', '1', 'appYydc             ', '1', 'V2.1.app  ', NULL, '900122610000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_pzqlcx                    ', 'app_pzgl                      ', 4, '凭证请领撤消                  ', '凭证请领撤消                                      ', '1', 'send                ', '1', 'V2.1.app  ', NULL, '900122330000        ', '0', 'agent     ', NULL, 'send_id=21                                                                                          ', NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_rcgl_qtcz                 ', 'app_rcgl                      ', 4, '服务启停                      ', '服务启停                                          ', '0', 'botsKeyctrl         ', '1', 'V2.1.app  ', NULL, '900122510000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_rc_fw_jyqt                ', 'app_rcgl_qtcz                 ', 5, '交易服务启停                  ', '交易服务启停                                      ', '1', 'send                ', '1', 'V2.1.app  ', NULL, '900122511000        ', '0', 'agent     ', NULL, 'send_id=1                                                                                           ', NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_rc_fw_qdqt                ', 'app_rcgl_qtcz                 ', 5, '渠道服务启停                  ', '渠道服务启停                                      ', '1', 'send                ', '1', 'V2.1.app  ', NULL, '900122512000        ', '0', 'agent     ', NULL, 'send_id=2                                                                                           ', NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_sj_bf                     ', 'app_3_rzcz                    ', 5, '数据备份                      ', '数据备份                                          ', '1', 'send                ', '1', 'V2.1.app  ', NULL, '900122523000        ', '0', 'agent     ', NULL, 'send_id=6                                                                                           ', NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_cpgl                      ', '/                             ', 2, '公共业务管理                  ', '公共业务管理                                      ', '0', 'sendPz              ', '1', 'V2.1.app  ', NULL, '900122000000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_yyxxgl                    ', 'app_cpgl                      ', 3, '应用信息管理                  ', '应用信息管理                                      ', '0', 'sendPz              ', '1', 'V2.1.app  ', NULL, '900122200000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_APPDWXX                   ', 'app_yyxxgl                    ', 4, '单位信息维护                  ', '单位信息维护                                      ', '1', 'appDwxx             ', '1', 'V2.1.app  ', NULL, '900122230000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_apppzzl                   ', 'app_yyxxgl                    ', 4, '凭证类型维护                  ', '凭证信息管理                                      ', '1', 'appPzzl             ', '1', 'V2.1.app  ', NULL, '900122240000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_rc_sj_hf                  ', 'app_3_rzcz                    ', 5, '数据恢复                      ', '数据恢复                                          ', '1', 'send                ', '1', 'V2.1.app  ', NULL, '900122524000        ', '0', 'agent     ', NULL, 'send_id=7                                                                                           ', NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_rc_rq                     ', 'app_rcgl                      ', 4, '日期操作                      ', '日期操作                                          ', '0', 'botsKeyctrl         ', '1', 'V2.1.app  ', NULL, '900122530000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_jbcsgl                    ', 'app_cpgl                      ', 3, '基本参数管理                  ', '基本参数管理                                      ', '0', 'sendPz              ', '1', 'V2.1.app  ', NULL, '900122100000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_rc_rqcl                   ', 'app_rc_rq                     ', 5, '日切处理                      ', '日切处理                                          ', '1', 'send                ', '1', 'V2.1.app  ', NULL, '900122531000        ', '0', 'agent     ', NULL, 'send_id=8                                                                                           ', NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_dwcpxy                    ', 'app_cpmessage                 ', 4, '单位产品协议维护              ', '单位产品协议                                      ', '1', 'appDwcpxy           ', '1', 'V2.1.app  ', NULL, '900122470000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_rc_rqcx                   ', 'app_rc_rq                     ', 5, '日期查询                      ', '日期查询                                          ', '1', 'send                ', '1', 'V2.1.app  ', NULL, '900122532000        ', '0', 'agent     ', NULL, 'send_id=11                                                                                          ', NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_rc_jjrsz                  ', 'app_rc_rq                     ', 5, '节假日设置                    ', '节假日设置                                        ', '1', 'send                ', '1', 'V2.1.app  ', NULL, '900122533000        ', '0', 'agent     ', NULL, 'send_id=12                                                                                          ', NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_cpsxfgx                   ', 'app_cpmessage                 ', 4, '产品手续费关系维护            ', '产品手续费关系维护                                ', '1', 'appCpSxfgx          ', '1', 'V2.1.app  ', NULL, '900122451000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_pzql                      ', 'app_pzgl                      ', 4, '凭证请领                      ', '凭证请领                                          ', '1', 'send                ', '1', 'V2.1.app  ', NULL, '900122310000        ', '0', 'agent     ', NULL, 'send_id=20                                                                                          ', NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_pzrk                      ', 'app_pzgl                      ', 4, '凭证入库                      ', '凭证入库                                          ', '1', 'send                ', '1', 'V2.1.app  ', NULL, '900122340000        ', '0', 'agent     ', NULL, 'send_id=23                                                                                          ', NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_rc_fw_cpjyqt              ', 'app_rcgl_qtcz                 ', 5, '产品交易服务启停              ', '产品交易服务启停                                  ', '1', 'send                ', '1', 'V2.1.app  ', '                                        ', '900122514000        ', '0', 'agent     ', '                              ', 'send_id=305                                                                                         ', NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_rc_fw_cpqt                ', 'app_rcgl_qtcz                 ', 5, '产品业务服务启停              ', '产品业务服务启停                                  ', '1', 'send                ', '1', 'V2.1.app  ', '                                        ', '900122515000        ', '0', 'agent     ', '                              ', 'send_id=306                                                                                         ', NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_cpkhqy                    ', 'app_cpmessage                 ', 4, '产品客户签约查询              ', '产品客户签约查询                                  ', '1', 'appKhcpqy           ', '1', 'V2.1.app  ', NULL, '900122460000        ', '0', 'agent     ', '                              ', NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_cpjg                      ', 'app_cpmessage                 ', 4, '产品机构关系维护              ', '产品机构维护                                      ', '1', 'appCpjg             ', '1', 'V2.1.app  ', NULL, '900122420000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_cpxx                      ', 'app_cpmessage                 ', 4, '产品基本信息维护              ', '产品信息维护                                      ', '1', 'appCpxx             ', '1', 'V2.1.app  ', NULL, '900122410000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_3_rzcz                    ', 'app_rcgl                      ', 4, '数据查询                      ', '数据操作                                          ', '0', 'appTxxx             ', '1', 'V2.1.app  ', NULL, '900122520000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_sjdr                      ', 'app_drdc                      ', 4, '配置信息导入                  ', '配置信息导入                                      ', '1', 'appSjdr             ', '1', 'V2.1.app  ', NULL, '900122680000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_jygl                      ', 'app_yyxxgl                    ', 4, '交易服务控制维护              ', '交易服务控制维护                                  ', '1', 'appJyxx             ', '1', 'V2.1.app  ', NULL, '900122280000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_applxkz                   ', 'app_jbcsgl                    ', 4, '序列配置维护                  ', '序列维护                                          ', '1', 'appXlkz             ', '1', 'V2.1.app  ', NULL, '900122130000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_appcpqd                   ', 'app_cpmessage                 ', 4, '产品渠道关系维护              ', '产品渠道维护                                      ', '1', 'appCpqd             ', '1', 'V2.1.app  ', NULL, '900122430000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_appcptx                   ', 'app_cpmessage                 ', 4, '产品通讯参数维护              ', '产品通讯参数管理                                  ', '1', 'appCptx             ', '0', 'V2.1.app  ', NULL, '900122440000        ', '0', 'agent     ', '                              ', NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_appcpsxf                  ', 'app_cpmessage                 ', 4, '产品手续费控制维护            ', '产品手续费控制维护                                ', '1', 'appSxfkz            ', '1', 'V2.1.app  ', NULL, '900122450000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_appyyxxx                  ', 'app_yyxxgl                    ', 4, '应用信息查询                  ', '应用信息查询                                      ', '1', 'appYyxx             ', '1', 'V2.1.app  ', NULL, '900122210000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_cpmessage                 ', 'app_cpgl                      ', 3, '产品配置                      ', '产品信息维护                                      ', '0', 'appCpxx             ', '1', 'V2.1.app  ', NULL, '900122400000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_drdc                      ', 'app_cpgl                      ', 3, '导入导出                      ', '导入导出                                          ', '0', 'sendPz              ', '1', 'V2.1.app  ', NULL, '900122600000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_sendpzqlcx                ', 'app_pzgl                      ', 4, '凭证请领查询                  ', '凭证请领查询                                      ', '1', 'send                ', '1', 'V2.1.app  ', NULL, '900122320000        ', '0', 'agent     ', NULL, 'send_id=22                                                                                          ', NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('appls                         ', 'app_3_rzcz                    ', 5, '平台流水                      ', '平台流水                                          ', '1', 'appLs               ', '1', 'V2.1.app  ', NULL, '900122525000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_dcmjwh                    ', 'app_jbcsgl                    ', 4, '多重枚举维护                  ', '多重枚举维护                                      ', '1', 'appMj               ', '1', 'V2.1.app  ', NULL, '900122140000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_rwjk                      ', 'app_3_rzcz                    ', 5, '任务监控                      ', '任务监控                                          ', '1', 'appRwjk             ', '1', 'V2.1.app  ', NULL, '900122526000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_pz_pzrkcx                 ', 'app_pzgl                      ', 4, '凭证入库撤消                  ', '凭证入库撤消                                      ', '1', 'send                ', '1', 'V2.1.app  ', NULL, '900122396000        ', '0', 'agent     ', NULL, 'send_id=30                                                                                          ', NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_rcgl                      ', 'app_cpgl                      ', 3, '日常管理                      ', '日常管理                                          ', '0', 'botsPlywlx          ', '1', 'V2.1.app  ', NULL, '900122500000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_apptxxx                   ', 'app_yyxxgl                    ', 4, '通讯参数维护                  ', '通讯参数维护                                      ', '1', 'appTxxx             ', '1', 'V2.1.app  ', NULL, '900122270000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('appPzckcx                     ', 'app_pzgl                      ', 4, '凭证出库撤销                  ', '凭证出库撤销                                      ', '1', 'send                ', '1', 'V2.1.app  ', NULL, '900122395000        ', '0', 'agent     ', NULL, 'send_id=29                                                                                          ', NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_cpgyjyqxkz                ', 'app_cpmessage                 ', 4, '产品柜员级别控制              ', '产品柜员级别控制                                  ', '1', 'appGyjyqxkz         ', '1', 'V2.1.app  ', NULL, '900122500000        ', '0', 'agent     ', '                              ', NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_cpjgljedkz                ', 'app_cpmessage                 ', 4, '产品机构累计额度控制          ', '产品机构累计额度控制                              ', '1', 'appJgljedkz         ', '0', 'V2.1.app  ', NULL, '900122520000        ', '0', 'agent     ', '                              ', NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_rzcz_rzpz                 ', 'app_3_rzcz                    ', 5, '日终任务配置                  ', '日终任务配置                                      ', '1', 'appRzpz             ', '1', 'V2.1.app  ', NULL, '900122527000        ', '0', 'agent     ', '                              ', NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_cpjgedkz                  ', 'app_cpmessage                 ', 4, '产品机构额度控制              ', '产品机构额度控制                                  ', '1', 'appJgedkz           ', '1', 'V2.1.app  ', NULL, '900122540000        ', '0', 'agent     ', '                              ', NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_shell                     ', 'app_rcgl                      ', 4, 'shell命令运行                 ', 'shell命令运行                                     ', '1', 'send                ', '1', 'V2.1.app  ', '                                        ', '900122540000        ', '0', 'agent     ', '                              ', 'send_id=304                                                                                         ', NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_cpgyedkz                  ', 'app_cpmessage                 ', 4, '产品柜员额度控制              ', '产品柜员额度控制                                  ', '1', 'appGyedkz           ', '1', 'V2.1.app  ', NULL, '900122550000        ', '0', 'agent     ', '                              ', NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_rcgl_qtcz_xxtb            ', 'app_rcgl_qtcz                 ', 5, '机构柜员信息同步              ', '机构柜员信息同步                                  ', '1', 'send                ', '1', 'V2.1.app  ', '                                        ', '900122516000        ', '0', 'agent     ', '                              ', 'send_id=308                                                                                         ', NULL);


INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_qdqt                    ', '签到签退状态                  ', '1                             ', '签退                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_qdqt                    ', '签到签退状态                  ', '2                             ', '签到                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_send_gdlx               ', '归档类型                      ', '1                             ', '系统归档                      ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_send_gdlx               ', '归档类型                      ', '2                             ', '业务（产品）归档              ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_qdkzcs                  ', '渠道控制参数                  ', '0                             ', '无关                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_qdkzcs                  ', '渠道控制参数                  ', '1                             ', '有关                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_qykzcs                  ', '签约控制参数                  ', '0                             ', '校验                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_qykzcs                  ', '签约控制参数                  ', '1                             ', '不校验                        ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_sxfkzcs                 ', '手续费控制参数                ', '0                             ', '收取                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_sxfkzcs                 ', '手续费控制参数                ', '1                             ', '免收                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_dzms                    ', '对帐模式                      ', '1                             ', '银行为主                      ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_dzms                    ', '对帐模式                      ', '2                             ', '第三方为主                    ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_sfqybz                  ', '三方签约标志                  ', '0                             ', '是                            ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_sfqybz                  ', '三方签约标志                  ', '1                             ', '否                            ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_dsfbz                   ', '代收付标志                    ', '1                             ', '代收                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_dsfbz                   ', '代收付标志                    ', '2                             ', '代付                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_dsfbz                   ', '代收付标志                    ', '3                             ', '其它                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_jylx                    ', '交易类型                      ', '0                             ', '正交易                        ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_jylx                    ', '交易类型                      ', '1                             ', '反交易                        ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_jylx                    ', '交易类型                      ', '9                             ', '其它                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_rzbz                    ', '入帐标志                      ', '0                             ', '入帐                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_rzbz                    ', '入帐标志                      ', '1                             ', '非入帐                        ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_bbbz                    ', '报表标志                      ', '0                             ', '报表                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_bbbz                    ', '报表标志                      ', '1                             ', '非报表                        ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_lsjlbz                  ', '流水记录标志                  ', '0                             ', '记录                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('app_cpxg                      ', '产品相关                      ', '0                             ', '相关                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('app_cpxg                      ', '产品相关                      ', '1                             ', '不相关                        ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_sxf_fdlx                ', '浮动类型                      ', '1                             ', '交易笔数浮动                  ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_sxf_fdlx                ', '浮动类型                      ', '2                             ', '交易金额浮动                  ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_send_qtbz               ', '启停标志                      ', '0                             ', '启动                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_send_qtbz               ', '启停标志                      ', '1                             ', '停止                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_ywbh_kkfs               ', '扣款方式                      ', '0                             ', '全额扣款                      ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_ywbh_kkfs               ', '扣款方式                      ', '1                             ', '允许部分扣款                  ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_ywbh_dzzt               ', '对帐状态                      ', '7                             ', '与第三方对明细帐              ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_sxf_nwkbz               ', '内外扣标志                    ', '1                             ', '内扣                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_sxf_nwkbz               ', '内外扣标志                    ', '0                             ', '外扣                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_send_qldzt              ', '请领单状态                    ', '0                             ', '未处理                        ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_send_qldzt              ', '请领单状态                    ', '1                             ', '已处理                        ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_send_qldzt              ', '请领单状态                    ', '9                             ', '取消                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_ywbh_dzzt               ', '对帐状态                      ', '1                             ', '主机对总账                    ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_ywbh_dzzt               ', '对帐状态                      ', '2                             ', '与主机对明细帐                ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_ywbh_dzzt               ', '对帐状态                      ', '6                             ', '第三方对总账                  ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_ywbh_gdzt               ', '归档状态                      ', '2                             ', '已清理                        ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_sxf_jslx                ', '计算参数类型                  ', '2                             ', '百分比                        ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_sxf_bhbz                ', '包含上限标志                  ', '1                             ', '包含上限                      ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_sxf_bhbz                ', '包含上限标志                  ', '2                             ', '包含下限                      ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_send_rqcxlx             ', '日期查询类型                  ', '1                             ', '系统帐务日期                  ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_send_rqcxlx             ', '日期查询类型                  ', '2                             ', '产品业务日期                  ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_send_rqcxlx             ', '日期查询类型                  ', '3                             ', '机器日期                      ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_ywbh_jzsx               ', '记账顺序                      ', '0                             ', '先上主机                      ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_ywbh_jzsx               ', '记账顺序                      ', '1                             ', '先上第三方                    ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_ywbh_qyms               ', '签约模式                      ', '1                             ', '产品代码＋银行帐号            ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_ywbh_qyms               ', '签约模式                      ', '2                             ', '产品代码＋客户号              ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_ywbh_qyms               ', '签约模式                      ', '3                             ', '产品代码＋银行帐号＋客户号    ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_ywbh_gdzt               ', '归档状态                      ', '1                             ', '已归档                        ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('app_pz_tzlx                   ', '调整类型                      ', '0                             ', '正常                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('app_pz_tzlx                   ', '调整类型                      ', '1                             ', '已使用                        ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('app_pz_tzlx                   ', '调整类型                      ', '2                             ', '作废                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('app_pz_tzlx                   ', '调整类型                      ', '4                             ', '丢失                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('app_pz_tzlx                   ', '调整类型                      ', '5                             ', '销毁                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('app_bill_pzzt                 ', '凭证状态                      ', '9                             ', '取消                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('app_bill_pzzt                 ', '凭证状态                      ', '1                             ', '完成                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('app_bill_pzzt                 ', '凭证状态                      ', '0                             ', '请求                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_dict_is                 ', '有效标志                      ', '0                             ', '有效                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_dict_is                 ', '有效标志                      ', '1                             ', '无效                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_jzlx                    ', '加载类型                      ', '0                             ', '自动                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_jzlx                    ', '加载类型                      ', '1                             ', '非自动                        ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_qdbz                    ', '渠道标志                      ', '0                             ', '开启                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_qdbz                    ', '渠道标志                      ', '1                             ', '关闭                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_czbz                    ', '冲正标志                      ', '0                             ', '允许                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_czbz                    ', '冲正标志                      ', '1                             ', '不允许                        ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_kzlx                    ', '控制类型                      ', '0                             ', '不控制                        ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_dwzt                    ', '单位状态                      ', '0                             ', '正常                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_clfs                    ', '处理方式                      ', '1                             ', '非实时                        ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_flxz                    ', '费率性质                      ', '0                             ', '固定                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_flxz                    ', '费率性质                      ', '1                             ', '浮动                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('send_czlx                     ', '通讯-操作类型                 ', '0                             ', '系统内                        ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('send_czlx                     ', '通讯-操作类型                 ', '1                             ', '系统外                        ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_ljlx                    ', '联机类型                      ', '1                             ', '行内主机                      ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_ljlx                    ', '联机类型                      ', '2                             ', '行内其它系统                  ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_ljlx                    ', '联机类型                      ', '3                             ', '外联单位                      ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_ljlx                    ', '联机类型                      ', '9                             ', '其它                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_txzt                    ', '通讯状态                      ', '0                             ', '正常                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_txzt                    ', '通讯状态                      ', '9                             ', '无效                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_kzbz                    ', '控制标志                      ', '0                             ', '控制                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_kzbz                    ', '控制标志                      ', '1                             ', '不控制                        ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_zwrqlx                  ', '帐务日期类型                  ', '1                             ', '公共                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_zwrqlx                  ', '帐务日期类型                  ', '2                             ', '私有                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_dwzt                    ', '单位状态                      ', 'X                             ', '删除                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_kzlx                    ', '控制类型                      ', '1                             ', '控制数量                      ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_kzlx                    ', '控制类型                      ', '2                             ', '控制号码                      ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_pzjb                    ', '凭证级别                      ', '0                             ', '一般                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_pzjb                    ', '凭证级别                      ', '1                             ', '重要                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_fpbcbz                  ', '发票保存标志                  ', '0                             ', '保存                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_fpbcbz                  ', '发票保存标志                  ', '1                             ', '不保存                        ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_fpcsfs                  ', '发票传输方式                  ', '0                             ', '报文                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_fpcsfs                  ', '发票传输方式                  ', '1                             ', '文件                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_sqfs                    ', '收取方式                      ', '0                             ', '免收                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_sqfs                    ', '收取方式                      ', '1                             ', '收                            ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_qhbz                    ', '前后标志                      ', '0                             ', '前收费                        ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_qhbz                    ', '前后标志                      ', '1                             ', '后收费                        ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_kkfs                    ', '扣款方式                      ', '0                             ', '内扣                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_kkfs                    ', '扣款方式                      ', '1                             ', '外扣                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_clfs                    ', '处理方式                      ', '0                             ', '实时                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('user_data_type                ', '数据权限字典                  ', '002                           ', '联机业务                      ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('user_data_type                ', '数据权限字典                  ', '800                           ', '批量业务                      ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_yxbz                    ', '有效标志                      ', '9                             ', '未授权                        ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_yxbz                    ', '有效标志                      ', '1                             ', '关闭                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_yxbz                    ', '有效标志                      ', '0                             ', '正常                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_dzlx                    ', '对账类型                      ', '1                             ', '隔日对账                      ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_send_qllx               ', '清理类型                      ', '1                             ', '系统清理                      ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_dzlx                    ', '对账类型                      ', '0                             ', '当日对账                      ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_send_qllx               ', '清理类型                      ', '2                             ', '业务（产品）清理              ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_send_rqlx               ', '日切类型                      ', '1                             ', '系统日切                      ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_send_rqlx               ', '日切类型                      ', '2                             ', '业务（产品）日切              ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_send_fileType           ', '文件标志                      ', '0                             ', '无文件                        ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_send_fileType           ', '文件标志                      ', '1                             ', '有文件                        ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('send_zjdz_errType             ', '错帐类型                      ', '1                             ', '调整为成功                    ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('send_zjdz_errType             ', '错帐类型                      ', '2                             ', '调整为失败                    ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_xzbz                    ', '现转标志                      ', '0                             ', '现金                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_xzbz                    ', '现转标志                      ', '1                             ', '转帐                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_sxf_jslx                ', '计算参数类型                  ', '1                             ', '金额                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_send_pzzt               ', '凭证状态                      ', '0                             ', '正常                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_send_pzzt               ', '凭证状态                      ', '1                             ', '已使用                        ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_send_pzzt               ', '凭证状态                      ', '2                             ', '已作废                        ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_send_pzzt               ', '凭证状态                      ', '3                             ', '在途                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_lsjlbz                  ', '流水记录标志                  ', '1                             ', '非记录                        ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_khcpqy_ljlx             ', '联机类型                      ', '0                             ', '联机                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_khcpqy_ljlx             ', '联机类型                      ', '1                             ', '批量                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_khcpqy_tzbz             ', '短信通知标志                  ', '0                             ', '通知                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_khcpqy_tzbz             ', '短信通知标志                  ', '1                             ', '不通知                        ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('sxf_ljbz                      ', '累进标志                      ', '0                             ', '不累进                        ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('sxf_ljbz                      ', '累进标志                      ', '1                             ', '根据各段费用累加              ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_jgfs                    ', '结果方式                      ', '1                             ', '报文                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_jgfs                    ', '结果方式                      ', '2                             ', '文件                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_qyzt                     ', '签约状态                      ', '0                             ', '正常                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_qyzt                     ', '签约状态                      ', '1                             ', '撤消                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_yy_table                ', '应用表导出                    ', '9                             ', '机构信息表                    ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_yy_table                ', '应用表导出                    ', '8                             ', '交易信息表                    ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_yy_table                ', '应用表导出                    ', '7                             ', '通讯安全信息表                ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_yy_table                ', '应用表导出                    ', '6                             ', '应用信息表                    ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_yy_table                ', '应用表导出                    ', '5                             ', '序列控制表                    ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_yy_table                ', '应用表导出                    ', '4                             ', '渠道信息表                    ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_yy_table                ', '应用表导出                    ', '3                             ', '凭证信息表                    ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_yy_table                ', '应用表导出                    ', '0                             ', '参数信息表                    ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_yy_table                ', '应用表导出                    ', '1                             ', '数据字典表                    ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_hyzk                    ', '婚姻状况                      ', '0                             ', '未婚                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_hyzk                    ', '婚姻状况                      ', '1                             ', '已婚                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_hyzk                    ', '婚姻状况                      ', '2                             ', '离婚                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_hyzk                    ', '婚姻状况                      ', '9                             ', '未知                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_yjdzlx                  ', '邮寄地址类型                  ', '1                             ', '公司地址                      ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_yjdzlx                  ', '邮寄地址类型                  ', '2                             ', '住宅地址                      ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_khxx_bz                 ', '客户信息标志                  ', '0                             ', '正常                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_khxx_bz                 ', '客户信息标志                  ', '1                             ', '无效                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_khxx_bz                 ', '客户信息标志                  ', 'X                             ', '删除                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_zxzt                    ', '执行状态                      ', '0                             ', '执行成功                      ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_zxzt                    ', '执行状态                      ', '1                             ', '执行失败                      ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('[object]                      ', '对象                          ', '2                             ', '22                            ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_qdkz                    ', '签到控制                      ', '0                             ', '控制                          ', 'V2.1.app  ', '                              ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_qdkz                    ', '签到控制                      ', '1                             ', '不控制                        ', 'V2.1.app  ', '                              ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_ftpgzfs                 ', 'FTP工作方式                   ', '1                             ', '主动模式                      ', 'V2.1.app  ', '                              ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_ftpgzfs                 ', 'FTP工作方式                   ', '2                             ', '被动模式                      ', 'V2.1.app  ', '                              ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_ftpzbdms                ', 'FTP主动被动模式               ', '0                             ', '主动PORT                      ', 'V2.1.app  ', '                              ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_ftpzbdms                ', 'FTP主动被动模式               ', '1                             ', '被动PASV                      ', 'V2.1.app  ', '                              ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_qdzt                    ', '签到状态                      ', '1                             ', '签退                          ', 'V2.1.app  ', '                              ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_qdzt                    ', '签到状态                      ', '2                             ', '签到                          ', 'V2.1.app  ', '                              ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_qyms                    ', '签约模式                      ', '1                             ', '产品代码＋银行帐号            ', 'V2.1.app  ', '                              ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_qyms                    ', '签约模式                      ', '2                             ', '产品代码＋用户号              ', 'V2.1.app  ', '                              ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_qyms                    ', '签约模式                      ', '3                             ', '产品代码＋银行帐号＋用户号    ', 'V2.1.app  ', '                              ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_rzms                    ', '日志模式                      ', '0                             ', '调试                          ', 'V2.1.app  ', '                              ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_rzms                    ', '日志模式                      ', '1                             ', '生产                          ', 'V2.1.app  ', '                              ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('app_tbbz                      ', '同步标志                      ', '1                             ', '机构信息                      ', 'V2.1.app  ', '                              ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('app_tbbz                      ', '同步标志                      ', '2                             ', '柜员信息                      ', 'V2.1.app  ', '                              ');


INSERT INTO T_SEND_SERVER(ID, SERNAME, IP, PORT, TYPEID, CSTIME)
  VALUES('appXml                        ', 'APP报文服务                                       ', '192.168.53.66       ', 13002, '0', 30);
INSERT INTO T_SEND_SERVER(ID, SERNAME, IP, PORT, TYPEID, CSTIME)
  VALUES('appFile                       ', 'APP文件服务                                       ', '192.168.53.66       ', 33344, '1', 60);
