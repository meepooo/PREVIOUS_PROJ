
delete from T_TRAN where version='V2.1.app';

delete from T_SUB_TRAN where version='V2.1.app';

delete from T_SEND_RETURN where version='V2.1.app';

delete from T_SEND_COND where version='V2.1.app';

delete from T_SENDINFO where version='V2.1.app';

delete from T_MENU where version='V2.1.app';

delete from T_DICT where version='V2.1.app';

delete from T_SEND_SERVER where id like 'app%';



INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appKhcpqy           ', '�ͻ���ƷǩԼ                  ', '1', 'com.hundsun.agent.web.app.ctl.AppKhcpqyCtl                                                          ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appDwcpxy           ', '��λ��ƷЭ��                  ', '1', 'com.hundsun.agent.web.app.ctl.AppDwcpxyCtl                                                          ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appSxfl             ', '��������                      ', '1', 'com.hundsun.agent.web.sxfl.ctl.AgentSxflCtl                                                         ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpSxfgx          ', '��Ʒ�����ѹ�ϵ                ', '1', 'com.hundsun.agent.web.sxfl.ctl.AgentSxfgxCtl                                                        ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpqd             ', '�м�ҵ��[��Ʒ����]            ', '1', 'com.hundsun.agent.web.app.ctl.AppCpqdCtl                                                            ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCptx             ', '�м�ҵ��[��ƷͨѶ]            ', '1', 'com.hundsun.agent.web.app.ctl.AppCptxCtl                                                            ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpdc             ', '��Ʒ����                      ', '1', 'com.hundsun.agent.web.app.ctl.AppCpdcCtl                                                            ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appSjdr             ', '���ݵ���                      ', '1', 'com.hundsun.agent.web.app.ctl.AppSjdrCtl                                                            ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appXlkz             ', '�м�ҵ��[����]����            ', '1', 'com.hundsun.agent.web.app.ctl.AppXlkzCtl                                                            ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appJyxx             ', '�м�ҵ��[����]��Ϣ����        ', '1', 'com.hundsun.agent.web.app.ctl.AppJyxxCtl                                                            ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appDict             ', '�м�ҵ��ϵͳ�����ֵ�          ', '1', 'com.hundsun.agent.web.app.ctl.AppDictCtl                                                            ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCskz             ', '�м�ҵ��[����]����            ', '1', 'com.hundsun.agent.web.app.ctl.AppCskzCtl                                                            ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appKzxx             ', '��չ��Ϣ                      ', '1', 'com.hundsun.agent.web.app.ctl.AppKzxxCtl                                                            ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpjy             ', '��Ʒ���׷���                  ', '1', 'com.hundsun.agent.web.app.ctl.AppCpjyCtl                                                            ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appSxfkz            ', '�����ѿ���                    ', '1', 'com.hundsun.agent.web.sxfl.ctl.AgentSxfkzCtl                                                        ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCppz             ', '��Ʒƾ֤                      ', '1', 'com.hundsun.agent.web.app.ctl.AppCppzCtl                                                            ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appRwjk             ', '�����ز�ѯ                  ', '1', 'com.hundsun.agent.web.app.ctl.AppRwjkCtl                                                            ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appTxxx             ', 'ͨѶ��Ϣά��                  ', '1', 'com.hundsun.agent.web.app.ctl.AppTxxxCtl                                                            ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpxx             ', '�м�ҵ��[��Ʒ]��Ϣά��        ', '1', 'com.hundsun.agent.web.app.ctl.AppCpxxCtl                                                            ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appLs               ', 'ƽ̨��ˮ��ѯ                  ', '1', 'com.hundsun.agent.web.app.ctl.AppLsCtl                                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appOrg              ', '��������                      ', '0', 'com.hundsun.agent.web.app.ctl.AppOrgCtl                                                             ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appMj               ', 'ö������                      ', '1', 'com.hundsun.agent.web.app.ctl.AppMjCtl                                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appKhxx             ', '�ͻ���Ϣ                      ', '1', 'com.hundsun.agent.web.app.ctl.AppKhxxCtl                                                            ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appYyxx             ', '�м�ҵ��[Ӧ����Ϣ]ά��        ', '1', 'com.hundsun.agent.web.app.ctl.AppYyxxCtl                                                            ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appQdxx             ', '�м�ҵ��[����]��Ϣά��        ', '1', 'com.hundsun.agent.web.app.ctl.AppQdxxCtl                                                            ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appDwxx             ', '�м�ҵ��ϵͳ[��λ]��Ϣά��    ', '1', 'com.hundsun.agent.web.app.ctl.AppDwxxCtl                                                            ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appPzzl             ', '�м�ҵ��[ƾ֤]��Ϣ����        ', '1', 'com.hundsun.agent.web.app.ctl.AppPzzlCtl                                                            ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appYydc             ', 'Ӧ�õ���                      ', '1', 'com.hundsun.agent.web.app.ctl.AppYydcCtl                                                            ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpjg             ', '�м�ҵ��[��Ʒ����]            ', '1', 'com.hundsun.agent.web.app.ctl.AppCpjgCtl                                                            ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpdzxd           ', '��Ʒ������                  ', '1', 'com.hundsun.agent.web.app.ctl.AppCpdzxdCtl                                                          ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appZwrq             ', '��������                      ', '1', 'com.hundsun.agent.web.app.ctl.AppZwrqCtl                                                            ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appGyjyqxkz         ', '��Ʒ��Ա����Ȩ�޿���          ', '1', 'com.hundsun.agent.web.app.ctl.AppGyjyqxkzCtl                                                        ', 'V2.1.app  ', '                              ', '                              ', '                              ');
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appRzpz             ', '��������                      ', '1', 'com.hundsun.agent.web.app.ctl.AppRzpzCtl                                                            ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appJgedkz           ', '��Ʒ������ȿ���              ', '1', 'com.hundsun.agent.web.app.ctl.AppJgedkzCtl                                                          ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('appGyedkz           ', '��Ʒ��Ա��ȿ���              ', '1', 'com.hundsun.agent.web.app.ctl.AppGyedkzCtl                                                          ', 'V2.1.app  ', NULL, NULL, NULL);


INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpxx             ', 'list                ', '�������                      ', 'app/agent/app/appcpxx.jsp                                                                           ', '�������                                          ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appDwxx             ', 'add                 ', '���                          ', 'app/agent/app/appdwxx.jsp                                                                           ', '���                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appDwxx             ', 'del                 ', 'ɾ��                          ', 'app/agent/app/appdwxx.jsp                                                                           ', 'ɾ��                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appPzzl             ', 'def                 ', '��ѯ                          ', 'app/agent/app/apppzzl.jsp                                                                           ', 'Ĭ��                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appPzzl             ', 'add                 ', '���                          ', 'app/agent/app/apppzzl.jsp                                                                           ', '���                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appPzzl             ', 'list                ', '�������                      ', 'app/agent/app/apppzzl.jsp                                                                           ', '�������                                          ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpxx             ', 'del                 ', 'ɾ��                          ', 'app/agent/app/appcpxx.jsp                                                                           ', 'ɾ��                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCskz             ', 'add                 ', '���                          ', 'app/agent/app/appcskz.jsp                                                                           ', '���                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appKzxx             ', 'def                 ', '��ѯ                          ', 'app/agent/app/appkzxx.jsp                                                                           ', 'Ĭ��                                              ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appKzxx             ', 'list                ', '�������                      ', 'app/agent/app/appkzxx.jsp                                                                           ', '�������                                          ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appKzxx             ', 'add                 ', '���                          ', 'app/agent/app/appkzxx.jsp                                                                           ', '���                                              ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appKzxx             ', 'upt                 ', '����                          ', 'app/agent/app/appkzxx.jsp                                                                           ', '����                                              ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpjg             ', 'del                 ', 'ɾ��                          ', 'app/agent/app/appcpjg.jsp                                                                           ', 'ɾ��                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpSxfgx          ', 'upt                 ', '�޸ļ�¼                      ', 'app/agent/sxfl/agent_cpsxfgx.jsp                                                                    ', '�޸ļ�¼                                          ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appSxfkz            ', 'def                 ', 'Ĭ�Ͻ���                      ', 'app/agent/sxfl/agent_cpsxfkz.jsp                                                                    ', '��ȡĬ�Ͻ���                                      ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appSxfkz            ', 'add                 ', '������¼                      ', 'app/agent/sxfl/agent_cpsxfkz.jsp                                                                    ', '������¼                                          ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appSxfkz            ', 'del                 ', 'ɾ����¼                      ', 'app/agent/sxfl/agent_cpsxfkz.jsp                                                                    ', 'ɾ����¼                                          ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appSxfkz            ', 'upt                 ', '���¼�¼                      ', 'app/agent/sxfl/agent_cpsxfkz.jsp                                                                    ', '���¼�¼                                          ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appSxfl             ', 'def                 ', '��ȡĬ�Ͻ���                  ', 'app/agent/sxfl/agent_sxfl.jsp                                                                       ', '��ȡĬ�Ͻ���                                      ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appKhcpqy           ', 'def                 ', '��ѯ                          ', 'app/agent/app/appkhcpqy.jsp                                                                         ', 'Ĭ��                                              ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appKhcpqy           ', 'list                ', '�������                      ', 'app/agent/app/appkhcpqy.jsp                                                                         ', '�������                                          ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appKhcpqy           ', 'add                 ', '���                          ', 'app/agent/app/appkhcpqy.jsp                                                                         ', '���                                              ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appKhcpqy           ', 'upt                 ', '����                          ', 'app/agent/app/appkhcpqy.jsp                                                                         ', '����                                              ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appKhcpqy           ', 'del                 ', 'ɾ��                          ', 'app/agent/app/appkhcpqy.jsp                                                                         ', 'ɾ��                                              ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appPzzl             ', 'upt                 ', '����                          ', 'app/agent/app/apppzzl.jsp                                                                           ', '����                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appPzzl             ', 'del                 ', 'ɾ��                          ', 'app/agent/app/apppzzl.jsp                                                                           ', 'ɾ��                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appYyxx             ', 'add                 ', '���                          ', 'app/agent/app/appyyxx.jsp                                                                           ', '���                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appYyxx             ', 'list                ', '�������                      ', 'app/agent/app/appyyxx.jsp                                                                           ', '�������                                          ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appYyxx             ', 'upt                 ', '����                          ', 'app/agent/app/appyyxx.jsp                                                                           ', '����                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appYyxx             ', 'del                 ', 'ɾ��                          ', 'app/agent/app/appyyxx.jsp                                                                           ', 'ɾ��                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appQdxx             ', 'def                 ', '��ѯ                          ', 'app/agent/app/appqdxx.jsp                                                                           ', 'Ĭ��                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appZwrq             ', 'def                 ', '��ѯ                          ', 'app/agent/app/appzwrq.jsp                                                                           ', 'Ĭ��                                              ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appKhxx             ', 'def                 ', '��ѯ                          ', 'app/agent/app/appkhxx.jsp                                                                           ', 'Ĭ��                                              ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appZwrq             ', 'upt                 ', '����                          ', 'app/agent/app/appzwrq.jsp                                                                           ', '����                                              ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appZwrq             ', 'list                ', '�������                      ', 'app/agent/app/appzwrq.jsp                                                                           ', '�������                                          ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appKhxx             ', 'list                ', '�������                      ', 'app/agent/app/appkhxx.jsp                                                                           ', '�������                                          ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appKhxx             ', 'add                 ', '��Ӹ���                      ', 'app/agent/app/appkhxx.jsp                                                                           ', '��Ӹ���                                          ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appKhxx             ', 'del                 ', 'ɾ��                          ', 'app/agent/app/appkhxx.jsp                                                                           ', 'ɾ��                                              ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appRwjk             ', 'def                 ', '��ѯ                          ', 'app/agent/app/apprwjk.jsp                                                                           ', 'Ĭ��                                              ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appRwjk             ', 'list                ', '�������                      ', 'app/agent/app/apprwjk.jsp                                                                           ', '�������                                          ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appDict             ', 'def                 ', '��ѯ                          ', 'app/agent/app/appdict.jsp                                                                           ', 'Ĭ��                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appDict             ', 'list                ', '�������                      ', 'app/agent/app/appdict.jsp                                                                           ', '�������                                          ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appDict             ', 'add                 ', '��Ӹ���                      ', 'app/agent/app/appdict.jsp                                                                           ', '��Ӹ���                                          ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCskz             ', 'def                 ', '��ѯ                          ', 'app/agent/app/appcskz.jsp                                                                           ', 'Ĭ��                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCskz             ', 'list                ', '�������                      ', 'app/agent/app/appcskz.jsp                                                                           ', '�������                                          ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCskz             ', 'upt                 ', '��������                      ', 'app/agent/app/appcskz.jsp                                                                           ', '��������                                          ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCskz             ', 'del                 ', 'ɾ������                      ', 'app/agent/app/appcskz.jsp                                                                           ', 'ɾ������                                          ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appQdxx             ', 'add                 ', '���                          ', 'app/agent/app/appqdxx.jsp                                                                           ', '���                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appQdxx             ', 'list                ', '�������                      ', 'app/agent/app/appqdxx.jsp                                                                           ', '�������                                          ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appQdxx             ', 'upt                 ', '����                          ', 'app/agent/app/appqdxx.jsp                                                                           ', '����                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appQdxx             ', 'del                 ', 'ɾ��                          ', 'app/agent/app/appqdxx.jsp                                                                           ', 'ɾ��                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appDwxx             ', 'def                 ', '��ѯ                          ', 'app/agent/app/appdwxx.jsp                                                                           ', 'Ĭ��                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appDwxx             ', 'list                ', '�������                      ', 'app/agent/app/appdwxx.jsp                                                                           ', '�������                                          ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appDwxx             ', 'upt                 ', '����                          ', 'app/agent/app/appdwxx.jsp                                                                           ', '����                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appMj               ', 'list                ', '������ṹ                    ', 'app/agent/app/appmj.jsp                                                                             ', '������ṹ                                        ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appMj               ', 'load                ', '��õ�������                  ', 'app/agent/app/appmj.jsp                                                                             ', '��õ�������                                      ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appMj               ', 'listsx              ', '���ö������                  ', 'app/agent/app/appmj.jsp                                                                             ', '���ö������                                      ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appMj               ', 'uptsj               ', '����ö������                  ', 'app/agent/app/appmj.jsp                                                                             ', '����ö������                                      ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appMj               ', 'delsj               ', '������ṹ                    ', 'app/agent/app/appmj.jsp                                                                             ', '������ṹ                                        ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appMj               ', 'addsj               ', '������ṹ                    ', 'app/agent/app/appmj.jsp                                                                             ', '������ṹ                                        ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appMj               ', 'listsj              ', '������ṹ                    ', 'app/agent/app/appmj.jsp                                                                             ', '������ṹ                                        ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appMj               ', 'add                 ', '������ṹ                    ', 'app/agent/app/appmj.jsp                                                                             ', '������ṹ                                        ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appMj               ', 'del                 ', '������ṹ                    ', 'app/agent/app/appmj.jsp                                                                             ', '������ṹ                                        ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpxx             ', 'get                 ', '���������Ϣ                  ', 'app/agent/app/appcpxx.jsp                                                                           ', '���������Ϣ                                      ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appOrg              ', 'def                 ', 'Ĭ��                          ', 'app/agent/app/apppzzl.jsp                                                                           ', 'Ĭ��                                              ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpxx             ', 'copy                ', '���ò�Ʒ                      ', 'app/agent/app/appcpxx.jsp                                                                           ', '���ò�Ʒ                                          ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpjg             ', 'upt                 ', '����                          ', 'app/agent/app/appcpjg.jsp                                                                           ', '����                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpjg             ', 'add                 ', '���                          ', 'app/agent/app/appcpjg.jsp                                                                           ', '���                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpjg             ', 'list                ', '�������                      ', 'app/agent/app/appcpjg.jsp                                                                           ', '�������                                          ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpjg             ', 'def                 ', '��ѯ                          ', 'app/agent/app/appcpjg.jsp                                                                           ', 'Ĭ��                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCptx             ', 'del                 ', 'ɾ��                          ', 'app/agent/app/appcptx.jsp                                                                           ', 'ɾ��                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCptx             ', 'upt                 ', '����                          ', 'app/agent/app/appcptx.jsp                                                                           ', '����                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCptx             ', 'add                 ', '���                          ', 'app/agent/app/appcptx.jsp                                                                           ', '���                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCptx             ', 'list                ', '�������                      ', 'app/agent/app/appcptx.jsp                                                                           ', '�������                                          ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCptx             ', 'def                 ', '��ѯ                          ', 'app/agent/app/appcptx.jsp                                                                           ', 'Ĭ��                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpqd             ', 'del                 ', 'ɾ��                          ', 'app/agent/app/appcpqd.jsp                                                                           ', 'ɾ��                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpqd             ', 'upt                 ', '����                          ', 'app/agent/app/appcpqd.jsp                                                                           ', '����                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpqd             ', 'add                 ', '���                          ', 'app/agent/app/appcpqd.jsp                                                                           ', '���                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpqd             ', 'list                ', '�������                      ', 'app/agent/app/appcpqd.jsp                                                                           ', '�������                                          ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpqd             ', 'def                 ', '��ѯ                          ', 'app/agent/app/appcpqd.jsp                                                                           ', 'Ĭ��                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpdc             ', 'def                 ', 'Ĭ��                          ', 'app/agent/app/appcpdc.jsp                                                                           ', 'Ĭ��                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpdc             ', 'down                ', '����                          ', 'app/agent/app/appcpdc.jsp                                                                           ', '����                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appSjdr             ', 'def                 ', 'Ĭ��                          ', 'app/agent/app/appsjdr.jsp                                                                           ', 'Ĭ��                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appSjdr             ', 'up                  ', '����                          ', 'app/agent/app/appsjdr.jsp                                                                           ', '����                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appYyxx             ', 'def                 ', '��ѯ                          ', 'app/agent/app/appyyxx.jsp                                                                           ', 'Ĭ��                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpxx             ', 'add                 ', '��Ӹ���                      ', 'app/agent/app/appcpxx.jsp                                                                           ', '��Ӹ���                                          ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appXlkz             ', 'def                 ', '��ѯ                          ', 'app/agent/app/appxlkz.jsp                                                                           ', 'Ĭ��                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appXlkz             ', 'list                ', '�������                      ', 'app/agent/app/appxlkz.jsp                                                                           ', '�������                                          ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appXlkz             ', 'add                 ', '���                          ', 'app/agent/app/appxlkz.jsp                                                                           ', '���                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appXlkz             ', 'upt                 ', '����                          ', 'app/agent/app/appxlkz.jsp                                                                           ', '����                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appXlkz             ', 'del                 ', 'ɾ��                          ', 'app/agent/app/appxlkz.jsp                                                                           ', 'ɾ��                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appYydc             ', 'def                 ', 'Ĭ��                          ', 'app/agent/app/appyydc.jsp                                                                           ', 'Ĭ��                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appYydc             ', 'down                ', '����                          ', 'app/agent/app/appyydc.jsp                                                                           ', '����                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appJyxx             ', 'list                ', '�������                      ', 'app/agent/app/appjyxx.jsp                                                                           ', '�������                                          ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpjg             ', 'org                 ', '��û�����                    ', 'app/agent/app/appcpjg.jsp                                                                           ', '��û�����                                        ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpdzxd           ', 'def                 ', 'Ĭ��                          ', 'app/agent/app/appcpdzxd.jsp                                                                         ', 'Ĭ��                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpdzxd           ', 'ok                  ', 'ģ������                      ', 'app/agent/app/appcpdzxd.jsp                                                                         ', 'ģ������                                          ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appJyxx             ', 'def                 ', '��ѯ                          ', 'app/agent/app/appjyxx.jsp                                                                           ', 'Ĭ��                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appJyxx             ', 'add                 ', '��Ӹ���                      ', 'app/agent/app/appjyxx.jsp                                                                           ', '��Ӹ���                                          ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appJyxx             ', 'del                 ', 'ɾ��                          ', 'app/agent/app/appjyxx.jsp                                                                           ', 'ɾ��                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpSxfgx          ', 'def                 ', 'Ĭ�Ͻ���                      ', 'app/agent/sxfl/agent_cpsxfgx.jsp                                                                    ', '��ȡ����                                          ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpSxfgx          ', 'add                 ', '������¼                      ', 'app/agent/sxfl/agent_cpsxfgx.jsp                                                                    ', '������¼                                          ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpSxfgx          ', 'del                 ', 'ɾ����¼                      ', 'app/agent/sxfl/agent_cpsxfgx.jsp                                                                    ', 'ɾ����¼                                          ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appDict             ', 'del                 ', 'ɾ��                          ', 'app/agent/app/appdict.jsp                                                                           ', 'ɾ��                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appDwcpxy           ', 'del                 ', 'ɾ��                          ', 'app/agent/app/appdwcpxy.jsp                                                                         ', 'ɾ��                                              ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appDwcpxy           ', 'upt                 ', '����                          ', 'app/agent/app/appdwcpxy.jsp                                                                         ', '����                                              ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appDwcpxy           ', 'add                 ', '���                          ', 'app/agent/app/appdwcpxy.jsp                                                                         ', '���                                              ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appDwcpxy           ', 'list                ', '�������                      ', 'app/agent/app/appdwcpxy.jsp                                                                         ', '�������                                          ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appDwcpxy           ', 'def                 ', '��ѯ                          ', 'app/agent/app/appdwcpxy.jsp                                                                         ', 'Ĭ��                                              ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appTxxx             ', 'del                 ', 'ɾ��                          ', 'app/agent/app/apptxxx.jsp                                                                           ', 'ɾ��                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appTxxx             ', 'def                 ', '��ѯ                          ', 'app/agent/app/apptxxx.jsp                                                                           ', 'Ĭ��                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appTxxx             ', 'list                ', '�������                      ', 'app/agent/app/apptxxx.jsp                                                                           ', '�������                                          ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appTxxx             ', 'add                 ', '���                          ', 'app/agent/app/apptxxx.jsp                                                                           ', '���                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appTxxx             ', 'upt                 ', '����                          ', 'app/agent/app/apptxxx.jsp                                                                           ', '����                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCppz             ', 'def                 ', '��ѯ                          ', 'app/agent/app/appcppz.jsp                                                                           ', '��ѯ                                              ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpjy             ', 'list                ', '�������                      ', 'app/agent/app/appcpjy.jsp                                                                           ', '�������                                          ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpjy             ', 'add                 ', '���                          ', 'app/agent/app/appcpjy.jsp                                                                           ', '���                                              ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpjy             ', 'del                 ', 'ɾ��                          ', 'app/agent/app/appcpjy.jsp                                                                           ', 'ɾ��                                              ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appSxfl             ', 'add                 ', '������¼                      ', 'app/agent/sxfl/agent_sxfl.jsp                                                                       ', '������¼                                          ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appSxfl             ', 'del                 ', 'ɾ����¼                      ', 'app/agent/sxfl/agent_sxfl.jsp                                                                       ', 'ɾ����¼                                          ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appSxfl             ', 'upt                 ', '���¼�¼                      ', 'app/agent/sxfl/agent_sxfl.jsp                                                                       ', '���¼�¼                                          ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpSxfgx          ', 'lst                 ', '��ʾ����                      ', 'app/agent/sxfl/agent_cpsxfgx.jsp                                                                    ', '��ʾ����                                          ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appSxfkz            ', 'lst                 ', '��ʾ����                      ', 'app/agent/sxfl/agent_cpsxfkz.jsp                                                                    ', '��ʾ����                                          ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appSxfl             ', 'lst                 ', '��ʾ����                      ', 'app/agent/sxfl/agent_sxfl.jsp                                                                       ', '��ʾ����                                          ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCppz             ', 'add                 ', '���                          ', 'app/agent/app/appcppz.jsp                                                                           ', '���                                              ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCppz             ', 'del                 ', 'ɾ��                          ', 'app/agent/app/appcppz.jsp                                                                           ', 'ɾ��                                              ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpjy             ', 'def                 ', '��ѯ                          ', 'app/agent/app/appcpjy.jsp                                                                           ', '��ѯ                                              ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCppz             ', 'list                ', '�������                      ', 'app/agent/app/appcppz.jsp                                                                           ', '�������                                          ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appYydc             ', 'ywdown              ', 'ҵ��Ӧ�õ���                  ', 'app/agent/app/appyydc.jsp                                                                           ', 'ҵ��Ӧ�õ���                                      ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appKzxx             ', 'del                 ', 'ɾ��                          ', 'app/agent/app/appkzxx.jsp                                                                           ', 'ɾ��                                              ', 'V2.1.app  ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appLs               ', 'def                 ', 'Ĭ��                          ', 'app/agent/app/appls.jsp                                                                             ', 'Ĭ��                                              ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appLs               ', 'list                ', '��ѯ                          ', 'app/agent/app/appls.jsp                                                                             ', '��ѯ                                              ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appMj               ', 'def                 ', '��ѯ                          ', 'app/agent/app/appmj.jsp                                                                             ', '��ѯ                                              ', 'V2.1.app  ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpxx             ', 'def                 ', '��ѯ                          ', 'app/agent/app/appcpxx.jsp                                                                           ', 'Ĭ��                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appCpjg             ', 'listone             ', '��ѯ��ϸ��Ϣ                  ', 'app/agent/app/appcpjg.jsp                                                                           ', '��ѯ��ϸ��Ϣ                                      ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('AppCpjygydbedkz     ', 'def                 ', 'Ĭ��ҳ��                      ', 'app/agent/app/appcpjygydbedkz.jsp                                                                   ', 'Ĭ��ҳ��                                          ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('AppCpjygydbedkz     ', 'add                 ', '���                          ', 'app/agent/app/appcpjygydbedkz.jsp                                                                   ', '���                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('AppCpjygydbedkz     ', 'del                 ', 'ɾ��                          ', 'app/agent/app/appcpjygydbedkz.jsp                                                                   ', 'ɾ��                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('AppCpjygydbedkz     ', 'list                ', '��ѯ                          ', 'app/agent/app/appcpjygydbedkz.jsp                                                                   ', '��ѯ                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appGyjyqxkz         ', 'def                 ', 'Ĭ��ҳ��                      ', 'app/agent/app/appgyjyqxkz.jsp                                                                       ', 'Ĭ��ҳ��                                          ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appGyjyqxkz         ', 'add                 ', '���                          ', 'app/agent/app/appgyjyqxkz.jsp                                                                       ', '���                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appGyjyqxkz         ', 'list                ', '��ѯ                          ', 'app/agent/app/appgyjyqxkz.jsp                                                                       ', '��ѯ                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appGyjyqxkz         ', 'del                 ', 'ɾ��                          ', 'app/agent/app/appgyjyqxkz.jsp                                                                       ', 'ɾ��                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appRzpz             ', 'def                 ', 'Ĭ��ҳ��                      ', 'app/agent/app/apprzpz.jsp                                                                           ', 'Ĭ��ҳ��                                          ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appRzpz             ', 'add                 ', '���                          ', 'app/agent/app/apprzpz.jsp                                                                           ', '���                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appRzpz             ', 'del                 ', 'ɾ��                          ', 'app/agent/app/apprzpz.jsp                                                                           ', 'ɾ��                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appRzpz             ', 'list                ', '��ѯ                          ', 'app/agent/app/apprzpz.jsp                                                                           ', '��ѯ                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appJgedkz           ', 'def                 ', 'Ĭ��ҳ��                      ', 'app/agent/app/appjgedkz.jsp                                                                         ', 'Ĭ��ҳ��                                          ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appJgedkz           ', 'list                ', '��ѯ                          ', 'app/agent/app/appjgedkz.jsp                                                                         ', '��ѯ                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appJgedkz           ', 'add                 ', '���                          ', 'app/agent/app/appjgedkz.jsp                                                                         ', '���                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appJgedkz           ', 'del                 ', 'ɾ��                          ', 'app/agent/app/appjgedkz.jsp                                                                         ', 'ɾ��                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appJgedkz           ', 'getJgkzfs           ', '��û�����ȿ��Ʒ�ʽ          ', 'app/agent/app/appjgedkz.jsp                                                                         ', '��û�����ȿ��Ʒ�ʽ                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appGyedkz           ', 'def                 ', 'Ĭ��                          ', 'app/agent/app/appgyedkz.jsp                                                                         ', 'Ĭ��                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appGyedkz           ', 'del                 ', 'ɾ��                          ', 'app/agent/app/appgyedkz.jsp                                                                         ', 'ɾ��                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appGyedkz           ', 'add                 ', '���                          ', 'app/agent/app/appgyedkz.jsp                                                                         ', '���                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appGyedkz           ', 'list                ', '��ѯ                          ', 'app/agent/app/appgyedkz.jsp                                                                         ', '��ѯ                                              ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appGyedkz           ', 'getGykzfs           ', '��ù�Ա���׶�ȿ��Ʒ�ʽ      ', 'app/agent/app/appgyedkz.jsp                                                                         ', '��ù�Ա���׶�ȿ��Ʒ�ʽ                          ', 'V2.1.app  ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('appGyjyqxkz         ', 'getGygwjbkz         ', '��ȡ��Ա��λ���Ʊ�־          ', 'about:blank                                                                                         ', '��ȡ��Ա��λ���Ʊ�־                              ', 'V2.1.app  ', NULL, NULL, NULL);


INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(24, 'dateReport          ', '��Ҫ��֤���ⵥ                ', '3 ', '6', NULL, NULL, '1', 'com.hundsun.agent.web.app.sendUtil.PzXtwCkReport                                                                                                                                    ', 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(23, 'dateReport          ', '��Ҫ��֤��ⵥ                ', '3 ', '6', NULL, NULL, '1', 'com.hundsun.agent.web.app.sendUtil.PzXtwRkReport                                                                                                                                    ', 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(28, 'dataReport          ', '��Ҫ��֤�����嵥              ', '3 ', '6', NULL, NULL, '1', 'com.hundsun.agent.web.app.sendUtil.PzTzReport                                                                                                                                       ', 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(25, 'dataReport          ', '���㻮����                    ', '3 ', '6', NULL, NULL, '1', 'com.hundsun.agent.web.app.sendUtil.PzHuabReport                                                                                                                                     ', 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(26, 'dataReport          ', '����ز���                    ', '3 ', '6', NULL, NULL, '1', 'com.hundsun.agent.web.app.sendUtil.PzHbReport                                                                                                                                       ', 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(29, 'dataReport          ', '��Ҫ��֤������                ', '3 ', '6', NULL, NULL, '1', 'com.hundsun.agent.web.app.sendUtil.PzCkCxReport                                                                                                                                     ', 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(30, 'dataReport          ', '��Ҫ��֤������                ', '3 ', '6', NULL, NULL, '1', 'com.hundsun.agent.web.app.sendUtil.PzRkCxReport                                                                                                                                     ', 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(30, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(30, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(30, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(30, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(11, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(11, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(7, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(7, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(6, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(6, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(6, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(3, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(3, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(2, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(2, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(2, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(20, 'qldbh               ', '���쵥���                    ', '3 ', '0', NULL, '/tamc/resp/         ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(1, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(20, 'qldbh               ', '���쵥���                    ', '3 ', '0', NULL, '/tamc/resp/         ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(1, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(22, 'pzmd                ', 'ƾ֤Ŀ��                      ', '8 ', '0', NULL, NULL, '0', NULL, 'V2.1.app  ', NULL, '1                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(22, 'pzly                ', 'ƾ֤��Դ                      ', '7 ', '0', NULL, NULL, '0', NULL, 'V2.1.app  ', NULL, '1                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(22, 'pzsl                ', 'ƾ֤����                      ', '6 ', '0', NULL, NULL, '0', NULL, 'V2.1.app  ', NULL, '1                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(22, 'pzzl                ', 'ƾ֤����                      ', '5 ', '0', NULL, NULL, '0', NULL, 'V2.1.app  ', NULL, '1                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(22, 'qldzt               ', '���쵥״̬                    ', '4 ', '0', NULL, NULL, '0', NULL, 'V2.1.app  ', NULL, '1                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(22, 'qlsj                ', '����ʱ��                      ', '2 ', '0', NULL, NULL, '0', NULL, 'V2.1.app  ', NULL, '1                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(22, 'qlrq                ', '��������                      ', '1 ', '0', NULL, NULL, '0', NULL, 'V2.1.app  ', NULL, '1                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(22, 'qldbh               ', '���쵥���                    ', '3 ', '0', NULL, NULL, '0', NULL, 'V2.1.app  ', NULL, '1                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(1, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(22, 'icount              ', '��¼����                      ', '9 ', '0', NULL, '/tamc/resp/         ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(1, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(12, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(4, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(11, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(id, return_id, return_name, order_id, value_type, file_ext, super_path, ret_type, dict, version, note, bak1, bak2, bak3, bak4, bak5, bak6)
  VALUES(11, 'cch                 ', '���κ�                        ', '4 ', '0', '          ', '/tamc/resp/         ', '0', '                                                                                                                                                                                    ', 'V2.1.app  ', '                                                                                                    ', '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(id, return_id, return_name, order_id, value_type, file_ext, super_path, ret_type, dict, version, note, bak1, bak2, bak3, bak4, bak5, bak6)
  VALUES(11, 'jqrq                ', '��������                      ', '6 ', '0', '          ', '/tamc/resp/         ', '0', '                                                                                                                                                                                    ', 'V2.1.app  ', '                                                                                                    ', '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(id, return_id, return_name, order_id, value_type, file_ext, super_path, ret_type, dict, version, note, bak1, bak2, bak3, bak4, bak5, bak6)
  VALUES(11, 'lsh                 ', 'ҵ����ˮ��                    ', '5 ', '0', '          ', '/tamc/resp/         ', '0', '                                                                                                                                                                                    ', 'V2.1.app  ', '                                                                                                    ', '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(id, return_id, return_name, order_id, value_type, file_ext, super_path, ret_type, dict, version, note, bak1, bak2, bak3, bak4, bak5, bak6)
  VALUES(11, 'ywrq                ', 'ҵ������                      ', '3 ', '0', '          ', '/tamc/resp/         ', '0', '                                                                                                                                                                                    ', 'V2.1.app  ', '                                                                                                    ', '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(27, 'wjmc                ', '�ļ�                          ', '3 ', '4', NULL, '/tamc/resp/         ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(27, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(27, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(27, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(27, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(6, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(3, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(21, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(11, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(7, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(7, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(21, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(3, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(2, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(12, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(12, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(12, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(5, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(28, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(28, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(28, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(28, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(4, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(8, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(8, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(8, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(20, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(20, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(20, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(22, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(23, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(23, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(23, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(23, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(24, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(24, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(24, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(24, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(25, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(25, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(25, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(25, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(26, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(26, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(26, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(26, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(4, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(4, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(5, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(5, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(5, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(8, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(20, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(21, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(29, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(21, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(22, 'zwrq                ', 'ƽ̨��������                  ', '11', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(22, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '10', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(22, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(29, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(29, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(29, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.app  ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(305, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', '          ', '/pub/               ', '1', '                                                                                                                                                                                    ', 'V2.1.app  ', '                                                                                                    ', '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(305, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', '          ', '/pub/               ', '0', '                                                                                                                                                                                    ', 'V2.1.app  ', '                                                                                                    ', '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(305, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', '          ', '/pub/               ', '1', '                                                                                                                                                                                    ', 'V2.1.app  ', '                                                                                                    ', '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(305, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', '          ', '/pub/               ', '0', '                                                                                                                                                                                    ', 'V2.1.app  ', '                                                                                                    ', '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(306, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', '          ', '/pub/               ', '1', '                                                                                                                                                                                    ', 'V2.1.app  ', '                                                                                                    ', '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(306, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', '          ', '/pub/               ', '0', '                                                                                                                                                                                    ', 'V2.1.app  ', '                                                                                                    ', '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(306, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', '          ', '/pub/               ', '1', '                                                                                                                                                                                    ', 'V2.1.app  ', '                                                                                                    ', '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(306, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', '          ', '/pub/               ', '0', '                                                                                                                                                                                    ', 'V2.1.app  ', '                                                                                                    ', '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(304, 'wjnr                ', '�ļ�����                      ', '1 ', '0', '          ', '                    ', '0', '                                                                                                                                                                                    ', 'V2.1.app  ', '                                                                                                    ', '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(304, 'wjmc                ', '�ļ�����                      ', '2 ', '2', '          ', '                    ', '0', '                                                                                                                                                                                    ', 'V2.1.app  ', '                                                                                                    ', '0                             ', NULL, NULL, NULL, NULL, NULL);


INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(22, 'qsrq                ', '��ʼ����                      ', '3', '2 ', '1', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(29, 'jshm                ', '��������                      ', '1', '4 ', '0', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(29, 'tzlx                ', '��������                      ', '6', '5 ', '1', NULL, NULL, '2                                                                                                   ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(29, 'qshm                ', '��ʼ����                      ', '1', '3 ', '0', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(29, 'pzsl                ', 'ƾ֤����                      ', '7', '2 ', '1', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(29, 'pzzl                ', 'ƾ֤����                      ', '5', '1 ', '1', NULL, NULL, 'com.hundsun.agent.web.app.sendUtil.Pzrk_PzzlSend                                                    ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(1, 'qtbz                ', '��ͣ��־                      ', '0', '3 ', '1', NULL, NULL, 'agent_send_qtbz                                                                                     ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(2, 'qtqdbs              ', '����ͣ������ʶ                ', '9', '1 ', '1', NULL, NULL, 'app_qdxx:qdbs:qdmc:qdbs<>''200'':true:false                                                           ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(3, 'qtyybs              ', '����ͣӦ�ñ�ʶ                ', '9', '1 ', '1', NULL, NULL, 'app_yyxx:yybs:yymc::true:false                                                                      ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(7, 'czdx                ', '��������                      ', '1', '1 ', '1', NULL, NULL, NULL, 'V2.1.app  ', '�ָ������                                                                                          ', '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(7, 'bfwj                ', '�����ļ���                    ', '1', '2 ', '1', NULL, NULL, NULL, 'V2.1.app  ', 'ȫ·���ļ���                                                                                        ', '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(11, 'rqlx                ', '��ѯ����                      ', '2', '1 ', '1', NULL, NULL, 'agent_send_rqcxlx                                                                                   ', 'V2.1.app  ', '��������                                                                                            ', '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(24, 'jshm                ', '��������                      ', '1', '8 ', '0', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(24, 'qshm                ', '��ʼ����                      ', '1', '7 ', '0', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(24, 'pzsl                ', 'ƾ֤����                      ', '7', '6 ', '1', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(24, 'pzmd                ', 'ƾ֤Ŀ��                      ', '4', '3 ', '1', NULL, NULL, 'org:all                                                                                             ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(24, 'czlx                ', '��������                      ', '2', '2 ', '1', 'onChange:Topzmd(this.value)                                                                         ', NULL, 'send_czlx                                                                                           ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(25, 'jshm                ', '��������                      ', '1', '6 ', '0', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(25, 'qshm                ', '��ʼ����                      ', '1', '5 ', '0', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(25, 'pzsl                ', 'ƾ֤����                      ', '7', '4 ', '1', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(26, 'pzsl                ', 'ƾ֤����                      ', '7', '4 ', '1', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(26, 'qshm                ', '��ʼ����                      ', '1', '5 ', '0', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(26, 'jshm                ', '��������                      ', '1', '6 ', '0', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(26, 'dfgy                ', '�Է���Ա                      ', '1', '1 ', '1', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(23, 'pzzl                ', 'ƾ֤����                      ', '5', '4 ', '1', NULL, NULL, 'com.hundsun.agent.web.app.sendUtil.Pzrk_PzzlSend                                                    ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(24, 'pzzl                ', 'ƾ֤����                      ', '5', '5 ', '1', NULL, NULL, 'com.hundsun.agent.web.app.sendUtil.Pzrk_PzzlSend                                                    ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(25, 'pzzl                ', 'ƾ֤����                      ', '5', '3 ', '1', NULL, NULL, 'com.hundsun.agent.web.app.sendUtil.Pzrk_PzzlSend                                                    ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(26, 'pzzl                ', 'ƾ֤����                      ', '5', '3 ', '1', NULL, NULL, 'com.hundsun.agent.web.app.sendUtil.Pzrk_PzzlSend                                                    ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(20, 'qlsl                ', '��������                      ', '7', '2 ', '1', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(24, 'qldbh               ', '���쵥���                    ', '1', '1 ', '0', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(25, 'dfgy                ', '�Է���Ա                      ', '1', '1 ', '1', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(27, 'pzzl                ', 'ƾ֤����                      ', '5', '1 ', '0', NULL, NULL, 'com.hundsun.agent.web.app.sendUtil.Pzrk_PzzlSend                                                    ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(27, 'pzzt                ', 'ƾ֤״̬                      ', '2', '2 ', '0', NULL, NULL, 'agent_send_pzzt                                                                                     ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(27, 'jgfs                ', '�����ʽ                      ', '2', '3 ', '1', NULL, NULL, 'agent_jgfs                                                                                          ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(28, 'pzzl                ', 'ƾ֤����                      ', '5', '1 ', '1', NULL, NULL, 'com.hundsun.agent.web.app.sendUtil.Pzrk_PzzlSend                                                    ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(28, 'pzsl                ', 'ƾ֤����                      ', '7', '2 ', '1', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(20, 'zysm                ', 'ժҪ˵��                      ', '8', '4 ', '0', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(22, 'qldzt               ', '���쵥״̬                    ', '2', '4 ', '0', NULL, NULL, 'agent_send_qldzt                                                                                    ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(27, 'qshm                ', '��ʼ����                      ', '1', '6 ', '0', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(27, 'jshm                ', '��������                      ', '1', '7 ', '0', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(28, 'ypzzt               ', 'ԭƾ֤״̬                    ', '0', '6 ', '1', NULL, NULL, 'app_pz_tzlx                                                                                         ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(22, 'pzzl                ', 'ƾ֤����                      ', '9', '1 ', '0', NULL, NULL, 'app_pzzl:pzzl:pzmc::true:false                                                                      ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(23, 'czlx                ', '��������                      ', '2', '1 ', '1', 'onChange:Topzly(this.value)                                                                         ', NULL, 'send_czlx                                                                                           ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(11, 'cpdm                ', '��Ʒ����                      ', '9', '2 ', '0', NULL, NULL, 'app_cpxx:cpdm:cpmc::true:false                                                                      ', 'V2.1.app  ', '��ѯ����Ϊ 2����Ʒҵ������  ʱ����                                                                  ', '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(20, 'pzzl                ', 'ƾ֤����                      ', '5', '1 ', '1', NULL, NULL, 'com.hundsun.agent.web.app.sendUtil.PzzlSend                                                         ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(12, 'rq                  ', '����                          ', '3', '1 ', '1', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(12, 'jrbz                ', '�ڼ��ձ�־                    ', '2', '2 ', '1', NULL, NULL, 'is_null                                                                                             ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(8, 'yybs                ', 'Ӧ�ñ�ʶ                      ', '6', '1 ', '1', NULL, NULL, '001                                                                                                 ', 'V2.1.app  ', '                                                                                                    ', '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(8, 'rqrq                ', '��������                      ', '3', '2 ', '0', NULL, NULL, NULL, 'V2.1.app  ', '���к�����                                                                                          ', '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(20, 'dfjg                ', '�Է�����                      ', '4', '3 ', '1', NULL, NULL, 'org:all                                                                                             ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(21, 'qldbh               ', '���쵥���                    ', '1', '1 ', '1', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(23, 'pzly                ', 'ƾ֤��Դ                      ', '4', '2 ', '1', NULL, NULL, 'org:all                                                                                             ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(23, 'pzsl                ', 'ƾ֤����                      ', '7', '5 ', '1', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(23, 'qshm                ', '��ʼ����                      ', '1', '6 ', '0', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(23, 'jshm                ', '��������                      ', '1', '7 ', '0', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(27, 'pzgy                ', 'ƾ֤��Ա                      ', '1', '4 ', '0', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(27, 'pzjg                ', 'ƾ֤����                      ', '1', '5 ', '0', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(28, 'qshm                ', '��ʼ����                      ', '1', '3 ', '0', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(1, 'qtyybs              ', 'Ӧ�ñ�ʶ                      ', '5', '1 ', '1', NULL, NULL, 'com.hundsun.agent.web.app.sendUtil.Yybs_JydmSend                                                    ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(28, 'tzlx                ', '��������                      ', '0', '5 ', '1', NULL, NULL, 'app_pz_tzlx                                                                                         ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(1, 'qtjydm              ', '���״���                      ', '2', '2 ', '1', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(2, 'qtbz                ', '��ͣ��־                      ', '0', '2 ', '1', NULL, NULL, 'agent_send_qtbz                                                                                     ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(6, 'bfrq                ', '��������                      ', '3', '2 ', '1', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(3, 'qtbz                ', '��ͣ��־                      ', '0', '2 ', '1', NULL, NULL, 'agent_send_qtbz                                                                                     ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(6, 'bfyybs              ', '����Ӧ�ñ�ʶ                  ', '9', '1 ', '1', NULL, NULL, 'app_yyxx:yybs:yymc::true:false                                                                      ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(4, 'gdrq                ', '�鵵����                      ', '3', '2 ', '1', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(22, 'jsrq                ', '��������                      ', '3', '3 ', '1', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(20, 'pkey                ', 'pkey                          ', '6', '7 ', '0', NULL, NULL, 'K_CPZT                                                                                              ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(30, 'pzzl                ', 'ƾ֤����                      ', '5', '1 ', '1', NULL, NULL, 'com.hundsun.agent.web.app.sendUtil.Pzrk_PzzlSend                                                    ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(30, 'pzsl                ', 'ƾ֤����                      ', '7', '3 ', '1', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(30, 'qshm                ', '��ʼ����                      ', '1', '4 ', '0', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(30, 'pzly                ', 'ƾ֤��Դ                      ', '4', '2 ', '1', NULL, NULL, 'org:all                                                                                             ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(30, 'jshm                ', '��������                      ', '1', '5 ', '0', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(28, 'jshm                ', '��������                      ', '1', '4 ', '0', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(4, 'gdyybs              ', '���鵵Ӧ�ñ�ʶ                ', '9', '1 ', '1', NULL, NULL, 'app_yyxx:yybs:yymc::true:false                                                                      ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(5, 'qlyybs              ', '����Ӧ�ñ�ʶ                  ', '9', '1 ', '1', NULL, NULL, 'app_yyxx:yybs:yymc::true:false                                                                      ', 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(5, 'qlrq                ', '��������                      ', '3', '2 ', '1', NULL, NULL, NULL, 'V2.1.app  ', NULL, '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(305, 'qtyybs              ', 'Ӧ�ñ�ʶ                      ', '5', '1 ', '1', '                                                                                                    ', '                    ', 'com.hundsun.agent.web.app.sendUtil.Yybs_CpdmSend                                                    ', 'V2.1.app  ', '                                                                                                    ', '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(29, 'pzmd                ', 'ƾ֤Ŀ��                      ', '4', '6 ', '0', '                                                                                                    ', '                    ', '                                                                                                    ', 'V2.1.app  ', '                                                                                                    ', '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(305, 'qtjydm              ', '���״���                      ', '2', '3 ', '1', '                                                                                                    ', '                    ', '                                                                                                    ', 'V2.1.app  ', '                                                                                                    ', '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(304, 'shell               ', 'shell����                     ', '1', '1 ', '1', '                                                                                                    ', '                    ', '                                                                                                    ', 'V2.1.app  ', '                                                                                                    ', '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(305, 'qtcpdm              ', '��Ʒ����                      ', '5', '2 ', '1', '                                                                                                    ', '                    ', 'com.hundsun.agent.web.app.sendUtil.Cpbs_JydmSend                                                    ', 'V2.1.app  ', '                                                                                                    ', '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(305, 'qtbz                ', '��ͣ��־                      ', '0', '4 ', '1', '                                                                                                    ', '                    ', 'agent_send_qtbz                                                                                     ', 'V2.1.app  ', '                                                                                                    ', '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(306, 'qtyybs              ', 'Ӧ�ñ�ʶ                      ', '5', '1 ', '1', '                                                                                                    ', '                    ', 'com.hundsun.agent.web.app.sendUtil.Yybs_Cpdm_Send                                                   ', 'V2.1.app  ', '                                                                                                    ', '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(306, 'qtcpdm              ', '��Ʒ����                      ', '5', '2 ', '1', '                                                                                                    ', '                    ', 'com.hundsun.agent.web.app.sendUtil.Cpdm_YwbhSend                                                    ', 'V2.1.app  ', '                                                                                                    ', '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(306, 'qtbz                ', '��ͣ��־                      ', '0', '4 ', '1', '                                                                                                    ', '                    ', 'agent_send_qtbz                                                                                     ', 'V2.1.app  ', '                                                                                                    ', '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(306, 'qtywbh              ', 'ҵ����                      ', '2', '3 ', '1', '                                                                                                    ', '                    ', '                                                                                                    ', 'V2.1.app  ', '                                                                                                    ', '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(308, 'tbbz                ', 'ͬ����־                      ', '2', '1 ', '1', '                                                                                                    ', '                    ', 'app_tbbz                                                                                            ', 'V2.1.app  ', 'ͬ����־                                                                                            ', '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);


INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(308, '900014                        ', '������Ա��Ϣͬ��                                  ', '1', '                    ', 'admin               ', '00000               ', '100                 ', 'V2.1.app  ', '���̨ͬ��������Ϣ����Ա��Ϣ', 'appXml                        ', 'appFile                       ', '                                                                                                                                                      ', '                                                                                                                                                      ', NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(117, '900027                        ', 'ƾ֤��ѯ                                          ', '4', '/tamc/resp/         ', 'admin               ', '00000               ', '100                 ', 'V2.1.app  ', '����ƾ֤��ѯ����ͨ��Աֻ�ܲ�ѯ�Լ����µ�ƾ֤���������Բ�ѯ�Լ��������й�Ա��ƾ֤״̬���ϼ��������Բ�ѯ�»����ģ����ܻ������Բ�ѯȫ�и���ƾ֤��Ϣ��                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              ', 'appXml                        ', 'appFile                       ', NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(23, '900023                        ', 'ƾ֤���                                          ', '1', NULL, 'admin               ', '70001               ', '100                 ', 'V2.1.app  ', '��Ϊϵͳ����⼰ϵͳ�����.ϵͳ�������ƾ֤���ܻ�������,���������ṩ��ƾ֤�������.ϵͳ�����,���Ϊƾ֤���ܻ�������,���ʾ��ƾ֤��������黹��ƾ֤�������,���Ϊ�����������,���ʾ��ƾ֤���ܻ����ĸ���ƾ֤����������.ϵͳ����������Ҫ֮ͬǰ�ĳ��⽻����ˮ���й���,����ƾ֤����Ŀ�������,�������������.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 ', 'appXml                        ', 'appFile                       ', 'com.hundsun.agent.web.app.sendUtil.PzrkSubmitSend                                                                                                     ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(305, '900010                        ', '��Ʒ���׷�����ͣ                                  ', '1', '                    ', 'admin               ', '00000               ', '100                 ', 'V2.1.app  ', '', 'appXml                        ', 'appFile                       ', '                                                                                                                                                      ', '                                                                                                                                                      ', NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(306, '900013                        ', '��Ʒҵ�������ͣ                                 ', '1', '                    ', 'admin               ', '00000               ', '100                 ', 'V2.1.app  ', '', 'appXml                        ', 'appFile                       ', '                                                                                                                                                      ', '                                                                                                                                                      ', NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(20, '900020                        ', 'ƾ֤����                                          ', '1', NULL, 'admin               ', '00000               ', '100                 ', 'V2.1.app  ', '�����������ҵ��չ��Ҫ����ƾ֤���ܻ������ϼ������������콻�ף���֪��Ҫĳ��ƾ֤�����ţ�(�Ǳ��뽻��)��                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          ', 'appXml                        ', 'appFile                       ', 'com.hundsun.agent.web.app.sendUtil.PzqlSubmitSend                                                                                                     ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(21, '900021                        ', 'ƾ֤���쳷��                                      ', '1', NULL, 'admin               ', '0001                ', '100                 ', 'V2.1.app  ', '�����������ҵ����Ҫ����ƾ֤���콻��                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            ', 'appXml                        ', 'appFile                       ', NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(4, '900004                        ', '���ݹ鵵                                          ', '1', NULL, 'admin               ', '70001               ', '100                 ', 'V2.1.app  ', NULL, 'appXml                        ', 'appFile                       ', NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(5, '900005                        ', '��������                                          ', '1', NULL, 'admin               ', '0001                ', '100                 ', 'V2.1.app  ', NULL, 'appXml                        ', 'appFile                       ', NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(24, '900024                        ', 'ƾ֤����                                          ', '1', NULL, 'admin               ', '70001               ', '100                 ', 'V2.1.app  ', '��Ϊϵͳ�ڳ��⼰ϵͳ�����.ϵͳ�������ƾ֤���ܻ�������,��ƾ֤�黹��������.ϵͳ�ڳ���,���Ϊƾ֤���ܻ�������,���ʾ��ƾ֤���⣬�������ɾ��������������,���Ϊ�����������,���ʾ��ƾ֤�����黹�����ܻ���.������������ţ�����Ҫͬ�����������������Ҫ���ڵ�������������                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  ', 'appXml                        ', 'appFile                       ', 'com.hundsun.agent.web.app.sendUtil.PzckSubmitSend                                                                                                     ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(25, '900025                        ', 'ƾ֤����                                          ', '1', NULL, 'admin               ', '70001               ', '100                 ', 'V2.1.app  ', 'ƾ֤�������ڴ���ͬһ�������������ܽ���Ҫ�հ�ƾ֤�������ͨ��Ա�Ľ��ס��ý��ױ������������ܷ�����������ѡ���軮���ĵ�֤ʵ���ƾ֤���࣬�����軮����������ʼ����,�������룬����Է���Ա�ţ��Է���Աȷ��ʵ�������������Ա���뼴�ɻ�����                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         ', 'appXml                        ', 'appFile                       ', 'com.hundsun.agent.web.app.sendUtil.PzslSubmitSend                                                                                                     ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(2, '900003                        ', '����������ͣ                                      ', '1', NULL, 'admin               ', '0010001             ', '100                 ', 'V2.1.app  ', NULL, 'appXml                        ', 'appFile                       ', NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(8, '900008                        ', '���д���                                          ', '1', NULL, 'admin               ', '70001               ', '100                 ', 'V2.1.app  ', NULL, 'appXml                        ', 'appFile                       ', NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(3, '900002                        ', 'Ӧ�÷�����ͣ                                      ', '1', NULL, 'admin               ', '0010001             ', '100                 ', 'V2.1.app  ', NULL, 'appXml                        ', 'appFile                       ', NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(6, '900006                        ', '���ݱ���                                          ', '1', NULL, 'admin               ', '0001                ', '100                 ', 'V2.1.app  ', NULL, 'appXml                        ', 'appFile                       ', NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(7, '900007                        ', '���ݻָ�                                          ', '1', NULL, 'admin               ', '0001                ', '100                 ', 'V2.1.app  ', NULL, 'appXml                        ', 'appFile                       ', NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(30, '900030                        ', 'ƾ֤��⳷��                                      ', '1', NULL, 'admin               ', '70001               ', '100                 ', 'V2.1.app  ', 'ֻ��ϵͳ����������ϵͳ����⳷��ͨ��ϵͳ�������ʵ�֡�                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        ', 'appXml                        ', 'appFile                       ', NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(26, '900026                        ', 'ƾ֤�ػ�                                          ', '1', NULL, 'admin               ', '70001               ', '100                 ', 'V2.1.app  ', 'ƾ֤�ػ����ڴ���ͬһ�������������ܽ�����ͨ��Ա���µ���Ҫ�հ�ƾ֤���صĽ��ס��ý��ױ������������ܷ��𣬸�����ػ���֤ʵ���ƾ֤���ࡢ����������ƾ֤�����ţ����벦������Ա�ţ���������Աȷ��ʵ���������������뼴�ɡ�                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              ', 'appXml                        ', 'appFile                       ', 'com.hundsun.agent.web.app.sendUtil.PzslSubmitSend                                                                                                     ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(27, '900027                        ', 'ƾ֤��ѯ                                          ', '4', '/tamc/resp/         ', 'admin               ', '0001                ', '100                 ', 'V2.1.app  ', '����ƾ֤��ѯ����ͨ��Աֻ�ܲ�ѯ�Լ����µ�ƾ֤���������Բ�ѯ�Լ��������й�Ա��ƾ֤״̬���ϼ��������Բ�ѯ�»����ģ����ܻ������Բ�ѯȫ�и���ƾ֤��Ϣ��                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              ', 'appXml                        ', 'appFile                       ', NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(11, '900011                        ', '���ڲ�ѯ                                          ', '1', NULL, 'admin               ', '0001                ', '100                 ', 'V2.1.app  ', NULL, 'appXml                        ', 'appFile                       ', 'com.hundsun.agent.web.app.sendUtil.RqcxSubmitSend                                                                                                     ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(12, '900012                        ', '�ڼ�������                                        ', '1', NULL, 'admin               ', '0001                ', '100                 ', 'V2.1.app  ', NULL, 'appXml                        ', 'appFile                       ', NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(28, '900028                        ', 'ƾ֤����                                          ', '1', NULL, 'admin               ', '70001               ', '100                 ', 'V2.1.app  ', '���ؿ�ƾ֤�𻵻�����������ʱ����Ա�ֹ�������Ҫ�հ�ƾ֤״̬�����ý���������������Ȩ��                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        ', 'appXml                        ', 'appFile                       ', 'com.hundsun.agent.web.app.sendUtil.PzslSubmitSend                                                                                                     ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(29, '900029                        ', 'ƾ֤���⳷��                                      ', '1', NULL, 'admin               ', '70001               ', '100                 ', 'V2.1.app  ', '�����������ʱ�����Գ������⡣����ֻ��ϵͳ�ڳ��⣬���ҶԷ�����δ���������                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    ', 'appXml                        ', 'appFile                       ', NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(1, '900001                        ', '���׷�����ͣ                                      ', '1', NULL, 'admin               ', '0001                ', '100                 ', 'V2.1.app  ', NULL, 'appXml                        ', 'appFile                       ', NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(22, '900022                        ', 'ƾ֤�����ѯ                                      ', '4', '/tamc/resp/         ', 'admin               ', '0001                ', '100                 ', 'V2.1.app  ', '��ѯƾ֤���쵥,��ѯ�����Ȳ�ѯ��Ϊ���췢�𷽣�����Ϊ������ܷ���������Ϣ�����Է��ض���������Ϣ��                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               ', 'appXml                        ', 'appFile                       ', NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(304, '900040                        ', 'shell��������                                     ', '1', '                    ', 'admin               ', '00000               ', '100                 ', 'V2.1.app  ', '', 'appXml                        ', 'appFile                       ', '                                                                                                                                                      ', '                                                                                                                                                      ', NULL, NULL, NULL, NULL);


INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_khxx                      ', 'app_yyxxgl                    ', 4, '�ͻ���Ϣά��                  ', '�ͻ���Ϣά��                                      ', '1', 'appKhxx             ', '1', 'V2.1.app  ', NULL, '900122250000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_sxffl                     ', 'app_yyxxgl                    ', 4, '�����ѷ���ά��                ', '�����ѷ���ά��                                    ', '1', 'appSxfl             ', '1', 'V2.1.app  ', NULL, '900122260000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_4_sjgd                    ', 'app_3_rzcz                    ', 5, '���ݹ鵵                      ', '���ݹ鵵                                          ', '1', 'send                ', '1', 'V2.1.app  ', NULL, '900122521000        ', '0', 'agent     ', NULL, 'send_id=4                                                                                           ', NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_cppz                      ', 'app_cpmessage                 ', 4, '��Ʒƾ֤��ϵά��              ', '��Ʒƾ֤��ϵά��                                  ', '1', 'appCppz             ', '0', 'V2.1.app  ', NULL, '900122480000        ', '0', 'agent     ', '                              ', NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_pzgl                      ', 'app_cpgl                      ', 3, 'ƾ֤����                      ', 'ƾ֤����                                          ', '0', 'alterUserPass       ', '1', 'V2.1.app  ', NULL, '900122300000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('appcpjy                       ', 'app_cpmessage                 ', 4, '��Ʒ���׷���ά��              ', '��Ʒ���׷���ά��                                  ', '1', 'appCpjy             ', '1', 'V2.1.app  ', NULL, '900122490000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_appqdxx                   ', 'app_yyxxgl                    ', 4, '������Ϣά��                  ', '������Ϣά��                                      ', '1', 'appQdxx             ', '1', 'V2.1.app  ', NULL, '900122220000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_4_sjql                    ', 'app_3_rzcz                    ', 5, '��������                      ', '��������                                          ', '1', 'send                ', '1', 'V2.1.app  ', NULL, '900122522000        ', '0', 'agent     ', NULL, 'send_id=5                                                                                           ', NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_pzck                      ', 'app_pzgl                      ', 4, 'ƾ֤����                      ', 'ƾ֤����                                          ', '1', 'send                ', '1', 'V2.1.app  ', NULL, '900122350000        ', '0', 'agent     ', NULL, 'send_id=24                                                                                          ', NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_pzhb                      ', 'app_pzgl                      ', 4, 'ƾ֤����                      ', 'ƾ֤����                                          ', '1', 'send                ', '1', 'V2.1.app  ', NULL, '900122360000        ', '0', 'agent     ', NULL, 'send_id=25                                                                                          ', NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_pzhh                      ', 'app_pzgl                      ', 4, 'ƾ֤�ػ�                      ', 'ƾ֤�ػ�                                          ', '1', 'send                ', '1', 'V2.1.app  ', NULL, '900122370000        ', '0', 'agent     ', NULL, 'send_id=26                                                                                          ', NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_pzcx                      ', 'app_pzgl                      ', 4, 'ƾ֤��ѯ                      ', 'ƾ֤��ѯ                                          ', '1', 'send                ', '1', 'V2.1.app  ', NULL, '900122380000        ', '0', 'agent     ', NULL, 'send_id=27                                                                                          ', NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_pztz                      ', 'app_pzgl                      ', 4, 'ƾ֤����                      ', 'ƾ֤����                                          ', '1', 'send                ', '1', 'V2.1.app  ', NULL, '900122390000        ', '0', 'agent     ', NULL, 'send_id=28                                                                                          ', NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_rc_fw_yyqt                ', 'app_rcgl_qtcz                 ', 5, 'Ӧ�÷�����ͣ                  ', 'Ӧ�÷�����ͣ                                      ', '1', 'send                ', '1', 'V2.1.app  ', NULL, '900122513000        ', '0', 'agent     ', NULL, 'send_id=3                                                                                           ', NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_appdict                   ', 'app_jbcsgl                    ', 4, 'ҵ���ֵ�ά��                  ', 'ҵ���ֵ�ά��                                      ', '1', 'appDict             ', '1', 'V2.1.app  ', NULL, '900122110000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_cspz                      ', 'app_jbcsgl                    ', 4, '��������ά��                  ', '��������ά��                                      ', '1', 'appCskz             ', '1', 'V2.1.app  ', NULL, '900122120000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_cpdc                      ', 'app_drdc                      ', 4, '��ƷӦ�õ���                  ', '��ƷӦ�õ���                                      ', '1', 'appCpdc             ', '1', 'V2.1.app  ', NULL, '900122620000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_yydcagent                 ', 'app_drdc                      ', 4, 'Ӧ����Ϣ����                  ', 'Ӧ����Ϣ����                                      ', '1', 'appYydc             ', '1', 'V2.1.app  ', NULL, '900122610000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_pzqlcx                    ', 'app_pzgl                      ', 4, 'ƾ֤���쳷��                  ', 'ƾ֤���쳷��                                      ', '1', 'send                ', '1', 'V2.1.app  ', NULL, '900122330000        ', '0', 'agent     ', NULL, 'send_id=21                                                                                          ', NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_rcgl_qtcz                 ', 'app_rcgl                      ', 4, '������ͣ                      ', '������ͣ                                          ', '0', 'botsKeyctrl         ', '1', 'V2.1.app  ', NULL, '900122510000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_rc_fw_jyqt                ', 'app_rcgl_qtcz                 ', 5, '���׷�����ͣ                  ', '���׷�����ͣ                                      ', '1', 'send                ', '1', 'V2.1.app  ', NULL, '900122511000        ', '0', 'agent     ', NULL, 'send_id=1                                                                                           ', NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_rc_fw_qdqt                ', 'app_rcgl_qtcz                 ', 5, '����������ͣ                  ', '����������ͣ                                      ', '1', 'send                ', '1', 'V2.1.app  ', NULL, '900122512000        ', '0', 'agent     ', NULL, 'send_id=2                                                                                           ', NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_sj_bf                     ', 'app_3_rzcz                    ', 5, '���ݱ���                      ', '���ݱ���                                          ', '1', 'send                ', '1', 'V2.1.app  ', NULL, '900122523000        ', '0', 'agent     ', NULL, 'send_id=6                                                                                           ', NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_cpgl                      ', '/                             ', 2, '����ҵ�����                  ', '����ҵ�����                                      ', '0', 'sendPz              ', '1', 'V2.1.app  ', NULL, '900122000000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_yyxxgl                    ', 'app_cpgl                      ', 3, 'Ӧ����Ϣ����                  ', 'Ӧ����Ϣ����                                      ', '0', 'sendPz              ', '1', 'V2.1.app  ', NULL, '900122200000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_APPDWXX                   ', 'app_yyxxgl                    ', 4, '��λ��Ϣά��                  ', '��λ��Ϣά��                                      ', '1', 'appDwxx             ', '1', 'V2.1.app  ', NULL, '900122230000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_apppzzl                   ', 'app_yyxxgl                    ', 4, 'ƾ֤����ά��                  ', 'ƾ֤��Ϣ����                                      ', '1', 'appPzzl             ', '1', 'V2.1.app  ', NULL, '900122240000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_rc_sj_hf                  ', 'app_3_rzcz                    ', 5, '���ݻָ�                      ', '���ݻָ�                                          ', '1', 'send                ', '1', 'V2.1.app  ', NULL, '900122524000        ', '0', 'agent     ', NULL, 'send_id=7                                                                                           ', NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_rc_rq                     ', 'app_rcgl                      ', 4, '���ڲ���                      ', '���ڲ���                                          ', '0', 'botsKeyctrl         ', '1', 'V2.1.app  ', NULL, '900122530000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_jbcsgl                    ', 'app_cpgl                      ', 3, '������������                  ', '������������                                      ', '0', 'sendPz              ', '1', 'V2.1.app  ', NULL, '900122100000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_rc_rqcl                   ', 'app_rc_rq                     ', 5, '���д���                      ', '���д���                                          ', '1', 'send                ', '1', 'V2.1.app  ', NULL, '900122531000        ', '0', 'agent     ', NULL, 'send_id=8                                                                                           ', NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_dwcpxy                    ', 'app_cpmessage                 ', 4, '��λ��ƷЭ��ά��              ', '��λ��ƷЭ��                                      ', '1', 'appDwcpxy           ', '1', 'V2.1.app  ', NULL, '900122470000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_rc_rqcx                   ', 'app_rc_rq                     ', 5, '���ڲ�ѯ                      ', '���ڲ�ѯ                                          ', '1', 'send                ', '1', 'V2.1.app  ', NULL, '900122532000        ', '0', 'agent     ', NULL, 'send_id=11                                                                                          ', NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_rc_jjrsz                  ', 'app_rc_rq                     ', 5, '�ڼ�������                    ', '�ڼ�������                                        ', '1', 'send                ', '1', 'V2.1.app  ', NULL, '900122533000        ', '0', 'agent     ', NULL, 'send_id=12                                                                                          ', NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_cpsxfgx                   ', 'app_cpmessage                 ', 4, '��Ʒ�����ѹ�ϵά��            ', '��Ʒ�����ѹ�ϵά��                                ', '1', 'appCpSxfgx          ', '1', 'V2.1.app  ', NULL, '900122451000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_pzql                      ', 'app_pzgl                      ', 4, 'ƾ֤����                      ', 'ƾ֤����                                          ', '1', 'send                ', '1', 'V2.1.app  ', NULL, '900122310000        ', '0', 'agent     ', NULL, 'send_id=20                                                                                          ', NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_pzrk                      ', 'app_pzgl                      ', 4, 'ƾ֤���                      ', 'ƾ֤���                                          ', '1', 'send                ', '1', 'V2.1.app  ', NULL, '900122340000        ', '0', 'agent     ', NULL, 'send_id=23                                                                                          ', NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_rc_fw_cpjyqt              ', 'app_rcgl_qtcz                 ', 5, '��Ʒ���׷�����ͣ              ', '��Ʒ���׷�����ͣ                                  ', '1', 'send                ', '1', 'V2.1.app  ', '                                        ', '900122514000        ', '0', 'agent     ', '                              ', 'send_id=305                                                                                         ', NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_rc_fw_cpqt                ', 'app_rcgl_qtcz                 ', 5, '��Ʒҵ�������ͣ              ', '��Ʒҵ�������ͣ                                  ', '1', 'send                ', '1', 'V2.1.app  ', '                                        ', '900122515000        ', '0', 'agent     ', '                              ', 'send_id=306                                                                                         ', NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_cpkhqy                    ', 'app_cpmessage                 ', 4, '��Ʒ�ͻ�ǩԼ��ѯ              ', '��Ʒ�ͻ�ǩԼ��ѯ                                  ', '1', 'appKhcpqy           ', '1', 'V2.1.app  ', NULL, '900122460000        ', '0', 'agent     ', '                              ', NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_cpjg                      ', 'app_cpmessage                 ', 4, '��Ʒ������ϵά��              ', '��Ʒ����ά��                                      ', '1', 'appCpjg             ', '1', 'V2.1.app  ', NULL, '900122420000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_cpxx                      ', 'app_cpmessage                 ', 4, '��Ʒ������Ϣά��              ', '��Ʒ��Ϣά��                                      ', '1', 'appCpxx             ', '1', 'V2.1.app  ', NULL, '900122410000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_3_rzcz                    ', 'app_rcgl                      ', 4, '���ݲ�ѯ                      ', '���ݲ���                                          ', '0', 'appTxxx             ', '1', 'V2.1.app  ', NULL, '900122520000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_sjdr                      ', 'app_drdc                      ', 4, '������Ϣ����                  ', '������Ϣ����                                      ', '1', 'appSjdr             ', '1', 'V2.1.app  ', NULL, '900122680000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_jygl                      ', 'app_yyxxgl                    ', 4, '���׷������ά��              ', '���׷������ά��                                  ', '1', 'appJyxx             ', '1', 'V2.1.app  ', NULL, '900122280000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_applxkz                   ', 'app_jbcsgl                    ', 4, '��������ά��                  ', '����ά��                                          ', '1', 'appXlkz             ', '1', 'V2.1.app  ', NULL, '900122130000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_appcpqd                   ', 'app_cpmessage                 ', 4, '��Ʒ������ϵά��              ', '��Ʒ����ά��                                      ', '1', 'appCpqd             ', '1', 'V2.1.app  ', NULL, '900122430000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_appcptx                   ', 'app_cpmessage                 ', 4, '��ƷͨѶ����ά��              ', '��ƷͨѶ��������                                  ', '1', 'appCptx             ', '0', 'V2.1.app  ', NULL, '900122440000        ', '0', 'agent     ', '                              ', NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_appcpsxf                  ', 'app_cpmessage                 ', 4, '��Ʒ�����ѿ���ά��            ', '��Ʒ�����ѿ���ά��                                ', '1', 'appSxfkz            ', '1', 'V2.1.app  ', NULL, '900122450000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_appyyxxx                  ', 'app_yyxxgl                    ', 4, 'Ӧ����Ϣ��ѯ                  ', 'Ӧ����Ϣ��ѯ                                      ', '1', 'appYyxx             ', '1', 'V2.1.app  ', NULL, '900122210000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_cpmessage                 ', 'app_cpgl                      ', 3, '��Ʒ����                      ', '��Ʒ��Ϣά��                                      ', '0', 'appCpxx             ', '1', 'V2.1.app  ', NULL, '900122400000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_drdc                      ', 'app_cpgl                      ', 3, '���뵼��                      ', '���뵼��                                          ', '0', 'sendPz              ', '1', 'V2.1.app  ', NULL, '900122600000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_sendpzqlcx                ', 'app_pzgl                      ', 4, 'ƾ֤�����ѯ                  ', 'ƾ֤�����ѯ                                      ', '1', 'send                ', '1', 'V2.1.app  ', NULL, '900122320000        ', '0', 'agent     ', NULL, 'send_id=22                                                                                          ', NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('appls                         ', 'app_3_rzcz                    ', 5, 'ƽ̨��ˮ                      ', 'ƽ̨��ˮ                                          ', '1', 'appLs               ', '1', 'V2.1.app  ', NULL, '900122525000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_dcmjwh                    ', 'app_jbcsgl                    ', 4, '����ö��ά��                  ', '����ö��ά��                                      ', '1', 'appMj               ', '1', 'V2.1.app  ', NULL, '900122140000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_rwjk                      ', 'app_3_rzcz                    ', 5, '������                      ', '������                                          ', '1', 'appRwjk             ', '1', 'V2.1.app  ', NULL, '900122526000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_pz_pzrkcx                 ', 'app_pzgl                      ', 4, 'ƾ֤��⳷��                  ', 'ƾ֤��⳷��                                      ', '1', 'send                ', '1', 'V2.1.app  ', NULL, '900122396000        ', '0', 'agent     ', NULL, 'send_id=30                                                                                          ', NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_rcgl                      ', 'app_cpgl                      ', 3, '�ճ�����                      ', '�ճ�����                                          ', '0', 'botsPlywlx          ', '1', 'V2.1.app  ', NULL, '900122500000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_apptxxx                   ', 'app_yyxxgl                    ', 4, 'ͨѶ����ά��                  ', 'ͨѶ����ά��                                      ', '1', 'appTxxx             ', '1', 'V2.1.app  ', NULL, '900122270000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('appPzckcx                     ', 'app_pzgl                      ', 4, 'ƾ֤���⳷��                  ', 'ƾ֤���⳷��                                      ', '1', 'send                ', '1', 'V2.1.app  ', NULL, '900122395000        ', '0', 'agent     ', NULL, 'send_id=29                                                                                          ', NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_cpgyjyqxkz                ', 'app_cpmessage                 ', 4, '��Ʒ��Ա�������              ', '��Ʒ��Ա�������                                  ', '1', 'appGyjyqxkz         ', '1', 'V2.1.app  ', NULL, '900122500000        ', '0', 'agent     ', '                              ', NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_cpjgljedkz                ', 'app_cpmessage                 ', 4, '��Ʒ�����ۼƶ�ȿ���          ', '��Ʒ�����ۼƶ�ȿ���                              ', '1', 'appJgljedkz         ', '0', 'V2.1.app  ', NULL, '900122520000        ', '0', 'agent     ', '                              ', NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_rzcz_rzpz                 ', 'app_3_rzcz                    ', 5, '������������                  ', '������������                                      ', '1', 'appRzpz             ', '1', 'V2.1.app  ', NULL, '900122527000        ', '0', 'agent     ', '                              ', NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_cpjgedkz                  ', 'app_cpmessage                 ', 4, '��Ʒ������ȿ���              ', '��Ʒ������ȿ���                                  ', '1', 'appJgedkz           ', '1', 'V2.1.app  ', NULL, '900122540000        ', '0', 'agent     ', '                              ', NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_shell                     ', 'app_rcgl                      ', 4, 'shell��������                 ', 'shell��������                                     ', '1', 'send                ', '1', 'V2.1.app  ', '                                        ', '900122540000        ', '0', 'agent     ', '                              ', 'send_id=304                                                                                         ', NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_cpgyedkz                  ', 'app_cpmessage                 ', 4, '��Ʒ��Ա��ȿ���              ', '��Ʒ��Ա��ȿ���                                  ', '1', 'appGyedkz           ', '1', 'V2.1.app  ', NULL, '900122550000        ', '0', 'agent     ', '                              ', NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('app_rcgl_qtcz_xxtb            ', 'app_rcgl_qtcz                 ', 5, '������Ա��Ϣͬ��              ', '������Ա��Ϣͬ��                                  ', '1', 'send                ', '1', 'V2.1.app  ', '                                        ', '900122516000        ', '0', 'agent     ', '                              ', 'send_id=308                                                                                         ', NULL);


INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_qdqt                    ', 'ǩ��ǩ��״̬                  ', '1                             ', 'ǩ��                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_qdqt                    ', 'ǩ��ǩ��״̬                  ', '2                             ', 'ǩ��                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_send_gdlx               ', '�鵵����                      ', '1                             ', 'ϵͳ�鵵                      ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_send_gdlx               ', '�鵵����                      ', '2                             ', 'ҵ�񣨲�Ʒ���鵵              ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_qdkzcs                  ', '�������Ʋ���                  ', '0                             ', '�޹�                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_qdkzcs                  ', '�������Ʋ���                  ', '1                             ', '�й�                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_qykzcs                  ', 'ǩԼ���Ʋ���                  ', '0                             ', 'У��                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_qykzcs                  ', 'ǩԼ���Ʋ���                  ', '1                             ', '��У��                        ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_sxfkzcs                 ', '�����ѿ��Ʋ���                ', '0                             ', '��ȡ                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_sxfkzcs                 ', '�����ѿ��Ʋ���                ', '1                             ', '����                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_dzms                    ', '����ģʽ                      ', '1                             ', '����Ϊ��                      ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_dzms                    ', '����ģʽ                      ', '2                             ', '������Ϊ��                    ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_sfqybz                  ', '����ǩԼ��־                  ', '0                             ', '��                            ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_sfqybz                  ', '����ǩԼ��־                  ', '1                             ', '��                            ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_dsfbz                   ', '���ո���־                    ', '1                             ', '����                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_dsfbz                   ', '���ո���־                    ', '2                             ', '����                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_dsfbz                   ', '���ո���־                    ', '3                             ', '����                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_jylx                    ', '��������                      ', '0                             ', '������                        ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_jylx                    ', '��������                      ', '1                             ', '������                        ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_jylx                    ', '��������                      ', '9                             ', '����                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_rzbz                    ', '���ʱ�־                      ', '0                             ', '����                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_rzbz                    ', '���ʱ�־                      ', '1                             ', '������                        ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_bbbz                    ', '�����־                      ', '0                             ', '����                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_bbbz                    ', '�����־                      ', '1                             ', '�Ǳ���                        ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_lsjlbz                  ', '��ˮ��¼��־                  ', '0                             ', '��¼                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('app_cpxg                      ', '��Ʒ���                      ', '0                             ', '���                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('app_cpxg                      ', '��Ʒ���                      ', '1                             ', '�����                        ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_sxf_fdlx                ', '��������                      ', '1                             ', '���ױ�������                  ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_sxf_fdlx                ', '��������                      ', '2                             ', '���׽���                  ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_send_qtbz               ', '��ͣ��־                      ', '0                             ', '����                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_send_qtbz               ', '��ͣ��־                      ', '1                             ', 'ֹͣ                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_ywbh_kkfs               ', '�ۿʽ                      ', '0                             ', 'ȫ��ۿ�                      ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_ywbh_kkfs               ', '�ۿʽ                      ', '1                             ', '�����ֿۿ�                  ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_ywbh_dzzt               ', '����״̬                      ', '7                             ', '�����������ϸ��              ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_sxf_nwkbz               ', '����۱�־                    ', '1                             ', '�ڿ�                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_sxf_nwkbz               ', '����۱�־                    ', '0                             ', '���                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_send_qldzt              ', '���쵥״̬                    ', '0                             ', 'δ����                        ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_send_qldzt              ', '���쵥״̬                    ', '1                             ', '�Ѵ���                        ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_send_qldzt              ', '���쵥״̬                    ', '9                             ', 'ȡ��                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_ywbh_dzzt               ', '����״̬                      ', '1                             ', '����������                    ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_ywbh_dzzt               ', '����״̬                      ', '2                             ', '����������ϸ��                ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_ywbh_dzzt               ', '����״̬                      ', '6                             ', '������������                  ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_ywbh_gdzt               ', '�鵵״̬                      ', '2                             ', '������                        ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_sxf_jslx                ', '�����������                  ', '2                             ', '�ٷֱ�                        ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_sxf_bhbz                ', '�������ޱ�־                  ', '1                             ', '��������                      ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_sxf_bhbz                ', '�������ޱ�־                  ', '2                             ', '��������                      ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_send_rqcxlx             ', '���ڲ�ѯ����                  ', '1                             ', 'ϵͳ��������                  ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_send_rqcxlx             ', '���ڲ�ѯ����                  ', '2                             ', '��Ʒҵ������                  ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_send_rqcxlx             ', '���ڲ�ѯ����                  ', '3                             ', '��������                      ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_ywbh_jzsx               ', '����˳��                      ', '0                             ', '��������                      ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_ywbh_jzsx               ', '����˳��                      ', '1                             ', '���ϵ�����                    ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_ywbh_qyms               ', 'ǩԼģʽ                      ', '1                             ', '��Ʒ���룫�����ʺ�            ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_ywbh_qyms               ', 'ǩԼģʽ                      ', '2                             ', '��Ʒ���룫�ͻ���              ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_ywbh_qyms               ', 'ǩԼģʽ                      ', '3                             ', '��Ʒ���룫�����ʺţ��ͻ���    ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_ywbh_gdzt               ', '�鵵״̬                      ', '1                             ', '�ѹ鵵                        ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('app_pz_tzlx                   ', '��������                      ', '0                             ', '����                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('app_pz_tzlx                   ', '��������                      ', '1                             ', '��ʹ��                        ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('app_pz_tzlx                   ', '��������                      ', '2                             ', '����                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('app_pz_tzlx                   ', '��������                      ', '4                             ', '��ʧ                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('app_pz_tzlx                   ', '��������                      ', '5                             ', '����                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('app_bill_pzzt                 ', 'ƾ֤״̬                      ', '9                             ', 'ȡ��                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('app_bill_pzzt                 ', 'ƾ֤״̬                      ', '1                             ', '���                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('app_bill_pzzt                 ', 'ƾ֤״̬                      ', '0                             ', '����                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_dict_is                 ', '��Ч��־                      ', '0                             ', '��Ч                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_dict_is                 ', '��Ч��־                      ', '1                             ', '��Ч                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_jzlx                    ', '��������                      ', '0                             ', '�Զ�                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_jzlx                    ', '��������                      ', '1                             ', '���Զ�                        ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_qdbz                    ', '������־                      ', '0                             ', '����                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_qdbz                    ', '������־                      ', '1                             ', '�ر�                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_czbz                    ', '������־                      ', '0                             ', '����                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_czbz                    ', '������־                      ', '1                             ', '������                        ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_kzlx                    ', '��������                      ', '0                             ', '������                        ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_dwzt                    ', '��λ״̬                      ', '0                             ', '����                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_clfs                    ', '����ʽ                      ', '1                             ', '��ʵʱ                        ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_flxz                    ', '��������                      ', '0                             ', '�̶�                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_flxz                    ', '��������                      ', '1                             ', '����                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('send_czlx                     ', 'ͨѶ-��������                 ', '0                             ', 'ϵͳ��                        ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('send_czlx                     ', 'ͨѶ-��������                 ', '1                             ', 'ϵͳ��                        ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_ljlx                    ', '��������                      ', '1                             ', '��������                      ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_ljlx                    ', '��������                      ', '2                             ', '��������ϵͳ                  ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_ljlx                    ', '��������                      ', '3                             ', '������λ                      ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_ljlx                    ', '��������                      ', '9                             ', '����                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_txzt                    ', 'ͨѶ״̬                      ', '0                             ', '����                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_txzt                    ', 'ͨѶ״̬                      ', '9                             ', '��Ч                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_kzbz                    ', '���Ʊ�־                      ', '0                             ', '����                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_kzbz                    ', '���Ʊ�־                      ', '1                             ', '������                        ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_zwrqlx                  ', '������������                  ', '1                             ', '����                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_zwrqlx                  ', '������������                  ', '2                             ', '˽��                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_dwzt                    ', '��λ״̬                      ', 'X                             ', 'ɾ��                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_kzlx                    ', '��������                      ', '1                             ', '��������                      ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_kzlx                    ', '��������                      ', '2                             ', '���ƺ���                      ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_pzjb                    ', 'ƾ֤����                      ', '0                             ', 'һ��                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_pzjb                    ', 'ƾ֤����                      ', '1                             ', '��Ҫ                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_fpbcbz                  ', '��Ʊ�����־                  ', '0                             ', '����                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_fpbcbz                  ', '��Ʊ�����־                  ', '1                             ', '������                        ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_fpcsfs                  ', '��Ʊ���䷽ʽ                  ', '0                             ', '����                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_fpcsfs                  ', '��Ʊ���䷽ʽ                  ', '1                             ', '�ļ�                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_sqfs                    ', '��ȡ��ʽ                      ', '0                             ', '����                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_sqfs                    ', '��ȡ��ʽ                      ', '1                             ', '��                            ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_qhbz                    ', 'ǰ���־                      ', '0                             ', 'ǰ�շ�                        ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_qhbz                    ', 'ǰ���־                      ', '1                             ', '���շ�                        ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_kkfs                    ', '�ۿʽ                      ', '0                             ', '�ڿ�                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_kkfs                    ', '�ۿʽ                      ', '1                             ', '���                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_clfs                    ', '����ʽ                      ', '0                             ', 'ʵʱ                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('user_data_type                ', '����Ȩ���ֵ�                  ', '002                           ', '����ҵ��                      ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('user_data_type                ', '����Ȩ���ֵ�                  ', '800                           ', '����ҵ��                      ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_yxbz                    ', '��Ч��־                      ', '9                             ', 'δ��Ȩ                        ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_yxbz                    ', '��Ч��־                      ', '1                             ', '�ر�                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_yxbz                    ', '��Ч��־                      ', '0                             ', '����                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_dzlx                    ', '��������                      ', '1                             ', '���ն���                      ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_send_qllx               ', '��������                      ', '1                             ', 'ϵͳ����                      ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_dzlx                    ', '��������                      ', '0                             ', '���ն���                      ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_send_qllx               ', '��������                      ', '2                             ', 'ҵ�񣨲�Ʒ������              ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_send_rqlx               ', '��������                      ', '1                             ', 'ϵͳ����                      ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_send_rqlx               ', '��������                      ', '2                             ', 'ҵ�񣨲�Ʒ������              ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_send_fileType           ', '�ļ���־                      ', '0                             ', '���ļ�                        ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_send_fileType           ', '�ļ���־                      ', '1                             ', '���ļ�                        ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('send_zjdz_errType             ', '��������                      ', '1                             ', '����Ϊ�ɹ�                    ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('send_zjdz_errType             ', '��������                      ', '2                             ', '����Ϊʧ��                    ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_xzbz                    ', '��ת��־                      ', '0                             ', '�ֽ�                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_xzbz                    ', '��ת��־                      ', '1                             ', 'ת��                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_sxf_jslx                ', '�����������                  ', '1                             ', '���                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_send_pzzt               ', 'ƾ֤״̬                      ', '0                             ', '����                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_send_pzzt               ', 'ƾ֤״̬                      ', '1                             ', '��ʹ��                        ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_send_pzzt               ', 'ƾ֤״̬                      ', '2                             ', '������                        ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_send_pzzt               ', 'ƾ֤״̬                      ', '3                             ', '��;                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_lsjlbz                  ', '��ˮ��¼��־                  ', '1                             ', '�Ǽ�¼                        ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_khcpqy_ljlx             ', '��������                      ', '0                             ', '����                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_khcpqy_ljlx             ', '��������                      ', '1                             ', '����                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_khcpqy_tzbz             ', '����֪ͨ��־                  ', '0                             ', '֪ͨ                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_khcpqy_tzbz             ', '����֪ͨ��־                  ', '1                             ', '��֪ͨ                        ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('sxf_ljbz                      ', '�۽���־                      ', '0                             ', '���۽�                        ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('sxf_ljbz                      ', '�۽���־                      ', '1                             ', '���ݸ��η����ۼ�              ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_jgfs                    ', '�����ʽ                      ', '1                             ', '����                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_jgfs                    ', '�����ʽ                      ', '2                             ', '�ļ�                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_qyzt                     ', 'ǩԼ״̬                      ', '0                             ', '����                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_qyzt                     ', 'ǩԼ״̬                      ', '1                             ', '����                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_yy_table                ', 'Ӧ�ñ���                    ', '9                             ', '������Ϣ��                    ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_yy_table                ', 'Ӧ�ñ���                    ', '8                             ', '������Ϣ��                    ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_yy_table                ', 'Ӧ�ñ���                    ', '7                             ', 'ͨѶ��ȫ��Ϣ��                ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_yy_table                ', 'Ӧ�ñ���                    ', '6                             ', 'Ӧ����Ϣ��                    ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_yy_table                ', 'Ӧ�ñ���                    ', '5                             ', '���п��Ʊ�                    ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_yy_table                ', 'Ӧ�ñ���                    ', '4                             ', '������Ϣ��                    ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_yy_table                ', 'Ӧ�ñ���                    ', '3                             ', 'ƾ֤��Ϣ��                    ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_yy_table                ', 'Ӧ�ñ���                    ', '0                             ', '������Ϣ��                    ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_yy_table                ', 'Ӧ�ñ���                    ', '1                             ', '�����ֵ��                    ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_hyzk                    ', '����״��                      ', '0                             ', 'δ��                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_hyzk                    ', '����״��                      ', '1                             ', '�ѻ�                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_hyzk                    ', '����״��                      ', '2                             ', '���                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_hyzk                    ', '����״��                      ', '9                             ', 'δ֪                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_yjdzlx                  ', '�ʼĵ�ַ����                  ', '1                             ', '��˾��ַ                      ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_yjdzlx                  ', '�ʼĵ�ַ����                  ', '2                             ', 'סլ��ַ                      ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_khxx_bz                 ', '�ͻ���Ϣ��־                  ', '0                             ', '����                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_khxx_bz                 ', '�ͻ���Ϣ��־                  ', '1                             ', '��Ч                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_khxx_bz                 ', '�ͻ���Ϣ��־                  ', 'X                             ', 'ɾ��                          ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_zxzt                    ', 'ִ��״̬                      ', '0                             ', 'ִ�гɹ�                      ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_zxzt                    ', 'ִ��״̬                      ', '1                             ', 'ִ��ʧ��                      ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('[object]                      ', '����                          ', '2                             ', '22                            ', 'V2.1.app  ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_qdkz                    ', 'ǩ������                      ', '0                             ', '����                          ', 'V2.1.app  ', '                              ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_qdkz                    ', 'ǩ������                      ', '1                             ', '������                        ', 'V2.1.app  ', '                              ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_ftpgzfs                 ', 'FTP������ʽ                   ', '1                             ', '����ģʽ                      ', 'V2.1.app  ', '                              ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_ftpgzfs                 ', 'FTP������ʽ                   ', '2                             ', '����ģʽ                      ', 'V2.1.app  ', '                              ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_ftpzbdms                ', 'FTP��������ģʽ               ', '0                             ', '����PORT                      ', 'V2.1.app  ', '                              ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_ftpzbdms                ', 'FTP��������ģʽ               ', '1                             ', '����PASV                      ', 'V2.1.app  ', '                              ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_qdzt                    ', 'ǩ��״̬                      ', '1                             ', 'ǩ��                          ', 'V2.1.app  ', '                              ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_qdzt                    ', 'ǩ��״̬                      ', '2                             ', 'ǩ��                          ', 'V2.1.app  ', '                              ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_qyms                    ', 'ǩԼģʽ                      ', '1                             ', '��Ʒ���룫�����ʺ�            ', 'V2.1.app  ', '                              ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_qyms                    ', 'ǩԼģʽ                      ', '2                             ', '��Ʒ���룫�û���              ', 'V2.1.app  ', '                              ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_qyms                    ', 'ǩԼģʽ                      ', '3                             ', '��Ʒ���룫�����ʺţ��û���    ', 'V2.1.app  ', '                              ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_rzms                    ', '��־ģʽ                      ', '0                             ', '����                          ', 'V2.1.app  ', '                              ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('agent_rzms                    ', '��־ģʽ                      ', '1                             ', '����                          ', 'V2.1.app  ', '                              ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('app_tbbz                      ', 'ͬ����־                      ', '1                             ', '������Ϣ                      ', 'V2.1.app  ', '                              ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('app_tbbz                      ', 'ͬ����־                      ', '2                             ', '��Ա��Ϣ                      ', 'V2.1.app  ', '                              ');


INSERT INTO T_SEND_SERVER(ID, SERNAME, IP, PORT, TYPEID, CSTIME)
  VALUES('appXml                        ', 'APP���ķ���                                       ', '192.168.53.66       ', 13002, '0', 30);
INSERT INTO T_SEND_SERVER(ID, SERNAME, IP, PORT, TYPEID, CSTIME)
  VALUES('appFile                       ', 'APP�ļ�����                                       ', '192.168.53.66       ', 33344, '1', 60);
