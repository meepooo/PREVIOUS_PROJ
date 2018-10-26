 
delete from T_TRAN where version='V2.1.bots';

delete from T_SUB_TRAN where version='V2.1.bots';

delete from T_SEND_RETURN where version='V2.1.bots';

delete from T_SEND_COND where version='V2.1.bots';

delete from T_SENDINFO where version='V2.1.bots';

delete from T_MENU where version='V2.1.bots';

delete from T_DICT where version='V2.1.bots';

delete from T_SEND_SERVER where id like 'bots%';
 

INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsGapsdown        ', '��GAPS����ļ�                ', '0', 'com.hundsun.agent.web.bots.ctl.GapsDownCtl                                                          ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsWbwjdj          ', '�ⲿ�ļ��Ǽ�                  ', '1', 'com.hundsun.agent.web.bots.ctl.BotsWbwjdjCtl                                                        ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywbd          ', '����ҵ�񵥲������            ', '1', 'com.hundsun.agent.web.bots.ctl.BotsPlywbdCtl                                                        ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsAuditingpara    ', '��˺��������Ǽ�              ', '1', 'com.hundsun.agent.web.bots.ctl.BotsAuditingparaCtl                                                  ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywbdmx        ', '����ҵ�񲽵���ϸ              ', '1', 'com.hundsun.agent.web.bots.ctl.BotsPlywbdmxCtl                                                      ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsAuditingfunc    ', '�����������                  ', '1', 'com.hundsun.agent.web.bots.ctl.BotsAuditingfuncCtl                                                  ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlrwSel         ', '������ѯ                      ', '1', 'com.hundsun.agent.web.bots.ctl.BotsPlywSelCtl                                                       ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywmx          ', '����ҵ����ϸ                  ', '1', 'com.hundsun.agent.web.bots.ctl.BatchPlywmxCtl                                                       ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsEncry           ', '�����ӽ���ע��                ', '1', 'com.hundsun.agent.web.bots.ctl.BotsEncryptregCtl                                                    ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywbh          ', '����ҵ����                  ', '1', 'com.hundsun.agent.web.bots.ctl.BotsPlywbhCtl                                                        ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsFile            ', '�����ļ�����                  ', '1', 'com.hundsun.agent.web.bots.ctl.BotsFileCtl                                                          ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPzdc            ', '�������õ���                  ', '1', 'com.hundsun.agent.web.bots.ctl.BotsPzdcCtl                                                          ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsWbwjdjSH        ', '����ⲿ�ļ�                  ', '1', 'com.hundsun.agent.web.bots.ctl.BotsWbwjdjSHCtl                                                      ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywbdcx        ', '����ҵ��������              ', '1', 'com.hundsun.agent.web.bots.ctl.BotsPlywbdcxCtl                                                      ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsAuditingreg     ', '��˺����Ǽ�                  ', '1', 'com.hundsun.agent.web.bots.ctl.BotsAuditingregCtl                                                   ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsTablereg        ', 'ע���ṹ                    ', '1', 'com.hundsun.agent.web.bots.ctl.BotsTableregCtl                                                      ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsFlowcfg         ', '������������                  ', '1', 'com.hundsun.agent.web.bots.ctl.BotsFlowcfgCtl                                                       ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlrw            ', '��������                      ', '1', 'com.hundsun.agent.web.bots.ctl.BotsPlrwCtl                                                          ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsRunctrl         ', '����ҵ�����п���              ', '1', 'com.hundsun.agent.web.bots.ctl.BotsRunctrlCtl                                                       ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywlx          ', '����ҵ������                  ', '1', 'com.hundsun.agent.web.bots.ctl.BotsPlywlxCtl                                                        ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsKeyctrl         ', '��Կ���ƹ���                  ', '1', 'com.hundsun.agent.web.bots.ctl.BotsKeyctrlCtl                                                       ', 'V2.1.bots ', '                              ', '                              ', '                              ');
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsMapinfo         ', '��Ӱ��                        ', '1', 'com.hundsun.agent.web.bots.ctl.BotsMapinfoCtl                                                       ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywbdcz        ', '����ҵ���������              ', '1', 'com.hundsun.agent.web.bots.ctl.BotsPlywbdczCtl                                                      ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPllpwjcx        ', '���������ļ�¼�볷��          ', '1', 'com.hundsun.agent.web.bots.ctl.BotsWbwjdjcxCtl                                                      ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsZJMapsinfo      ', '����ӳ��                      ', '1', 'com.hundsun.agent.web.bots.ctl.BotsZJMapinfoCtl                                                     ', 'V2.1.bots ', '                              ', '                              ', '                              ');
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsRespmap         ', '��Ӧ��ӳ��                    ', '0', 'com.hundsun.agent.web.bots.ctl.BotsRespmapCtl                                                       ', 'V2.1.bots ', NULL, NULL, NULL);


INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsAuditingreg     ', 'del                 ', 'ɾ��                          ', 'about:blank                                                                                         ', 'ɾ��                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsAuditingreg     ', 'def                 ', '��ѯ                          ', 'app/agent/bots/botsauditingreg.jsp                                                                  ', 'Ĭ��                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsAuditingfunc    ', 'list                ', '������                      ', 'about:blank                                                                                         ', '�������                                          ', 'V2.1.bots ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsAuditingreg     ', 'delpara             ', 'ɾ������                      ', 'about:blank                                                                                         ', 'ɾ��                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsAuditingreg     ', 'uptpara             ', '���²���                      ', 'about:blank                                                                                         ', '����                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsAuditingreg     ', 'addpara             ', '��Ӳ���                      ', 'about:blank                                                                                         ', '���                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsAuditingreg     ', 'listpara            ', '��ò�������                  ', 'about:blank                                                                                         ', '�������                                          ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsAuditingfunc    ', 'addhs               ', '׷�Ӻ���                      ', 'about:blank                                                                                         ', '׷�Ӳ���                                          ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsAuditingfunc    ', 'del                 ', 'ɾ��                          ', 'about:blank                                                                                         ', 'ɾ��                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsAuditingfunc    ', 'upt                 ', '����                          ', 'about:blank                                                                                         ', '����                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsWbwjdjSH        ', 'list                ', '�������                      ', 'about:blank                                                                                         ', '�������                                          ', 'V2.1.bots ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsWbwjdjSH        ', 'upt                 ', 'ִ�����                      ', 'about:blank                                                                                         ', 'ִ�����                                          ', 'V2.1.bots ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsWbwjdjSH        ', 'def                 ', '��ѯ                          ', 'app/agent/bots/botswbwjdjSH.jsp                                                                     ', '��ѯ                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywbd          ', 'down                ', '���ػ����ļ�                  ', 'about:blank                                                                                         ', '���ػ����ļ�                                      ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywbd          ', 'addyw               ', '׷�ӻ�ȡ����                  ', 'about:blank                                                                                         ', '׷�ӻ�ȡ����                                      ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywbd          ', 'selyw               ', '��ѯ��ȡ����ҵ��              ', 'about:blank                                                                                         ', '��ѯ��ȡ����ҵ��                                  ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsTablereg        ', 'addindex            ', '�������                      ', 'about:blank                                                                                         ', '�������                                          ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsWbwjdj          ', 'def                 ', '��ѯ                          ', 'app/agent/bots/botswbwjdj.jsp                                                                       ', 'Ĭ��                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsEncry           ', 'add                 ', '���ά��                      ', 'about:blank                                                                                         ', '���                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsTablereg        ', 'listindex           ', '�������                      ', 'about:blank                                                                                         ', '�������                                          ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsTablereg        ', 'delindex            ', 'ɾ������                      ', 'about:blank                                                                                         ', 'ɾ������                                          ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsTablereg        ', 'create              ', '������                        ', 'about:blank                                                                                         ', '������                                            ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsWbwjdj          ', 'upload              ', '����¼��                      ', 'about:blank                                                                                         ', '����¼��                                          ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywbdcz        ', 'run                 ', '����                          ', 'about:blank                                                                                         ', '����״̬��ѯ                                      ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsMapinfo         ', 'mapdel              ', 'ɾ��ӳ��                      ', 'about:blank                                                                                         ', 'ɾ��                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsMapinfo         ', 'mapupt              ', '����ӳ��                      ', 'about:blank                                                                                         ', '���                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsMapinfo         ', 'maplist             ', '��ѯӳ��                      ', 'about:blank                                                                                         ', '��ѯ����                                          ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsRunctrl         ', 'list                ', '�������                      ', 'about:blank                                                                                         ', '�������                                          ', 'V2.1.bots ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsRunctrl         ', 'def                 ', '��ѯ                          ', 'app/agent/bots/botsrunctrl.jsp                                                                      ', 'Ĭ��                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsRunctrl         ', 'maplist             ', '�����ӳ������                ', 'about:blank                                                                                         ', '�������                                          ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsRunctrl         ', 'mapadd              ', '��Ӹ�����ӳ������            ', 'about:blank                                                                                         ', '��Ӹ�����ӳ������                                ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywmx          ', 'def                 ', '��ѯ                          ', 'app/agent/bots/botsplywmx.jsp                                                                       ', 'Ĭ��                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywmx          ', 'list                ', '�������                      ', 'about:blank                                                                                         ', '�������                                          ', 'V2.1.bots ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywbd          ', 'def                 ', '��ѯ                          ', 'app/agent/bots/botsplywbd.jsp                                                                       ', 'Ĭ��                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywbd          ', 'send                ', '�����㽻��                    ', 'about:blank                                                                                         ', '�����㽻��                                        ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywbd          ', 'list                ', '�������                      ', 'about:blank                                                                                         ', '�������                                          ', 'V2.1.bots ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywbd          ', 'run                 ', '����״̬��ѯ                  ', 'about:blank                                                                                         ', '����״̬��ѯ                                      ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsTablereg        ', 'list                ', '�������                      ', 'about:blank                                                                                         ', '�������                                          ', 'V2.1.bots ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsTablereg        ', 'del                 ', 'ɾ��                          ', 'about:blank                                                                                         ', 'ɾ��                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlrw            ', 'addyw               ', '���ҵ�����                  ', 'about:blank                                                                                         ', '���ҵ�����                                      ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsTablereg        ', 'add                 ', '��Ӹ���                      ', 'about:blank                                                                                         ', '��Ӹ���                                          ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlrw            ', 'selyw               ', '��ѯ���Լ�����ҵ��            ', 'about:blank                                                                                         ', '��ѯ���Լ�����ҵ��                                ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsFile            ', 'def                 ', '��ѯ                          ', 'app/agent/bots/botsfile.jsp                                                                         ', 'Ĭ��                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsFile            ', 'list                ', '����ļ���������              ', 'about:blank                                                                                         ', '�������                                          ', 'V2.1.bots ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsFile            ', 'add                 ', '��Ӹ����ļ�����              ', 'about:blank                                                                                         ', '��Ӹ����ļ�����                                  ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsFile            ', 'del                 ', 'ɾ���ļ�����                  ', 'about:blank                                                                                         ', 'ɾ���ļ�����                                      ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsFlowcfg         ', 'def                 ', '��ѯ                          ', 'app/agent/bots/botsflowcfg.jsp                                                                      ', 'Ĭ��                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsFlowcfg         ', 'add                 ', '���                          ', 'about:blank                                                                                         ', '���                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsFlowcfg         ', 'upt                 ', '����                          ', 'about:blank                                                                                         ', '����                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsWbwjdj          ', 'del                 ', 'ɾ��                          ', 'about:blank                                                                                         ', 'ɾ��                                              ', 'V2.1.bots ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsWbwjdj          ', 'mv                  ', '��Ȩɾ��                      ', 'about:blank                                                                                         ', '��Ȩɾ��                                          ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsTablereg        ', 'set                 ', '���ñ�                        ', 'about:blank                                                                                         ', '���ñ�                                            ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsAuditingfunc    ', 'add                 ', '���                          ', 'about:blank                                                                                         ', '���                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsAuditingfunc    ', 'def                 ', '��ѯ                          ', 'app/agent/bots/botsauditingfunc.jsp                                                                 ', 'Ĭ��                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsAuditingfunc    ', 'dict                ', '��ú���ģ��                  ', 'about:blank                                                                                         ', '��ò���ģ��                                      ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsAuditingfunc    ', 'tree                ', '��������                    ', 'about:blank                                                                                         ', '���������                                        ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsFile            ', 'set                 ', '�ļ�����                      ', 'about:blank                                                                                         ', '�ļ�����                                          ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywbdmx        ', 'def                 ', '��ѯ                          ', 'app/agent/bots/botsplywbdmx.jsp                                                                     ', 'Ĭ��                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywbdmx        ', 'list                ', '�������                      ', 'about:blank                                                                                         ', '�������                                          ', 'V2.1.bots ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsFlowcfg         ', 'set                 ', '����ģ��                      ', 'about:blank                                                                                         ', '����ģ��                                          ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsRunctrl         ', 'set                 ', '����ģ��                      ', 'about:blank                                                                                         ', '����ģ��                                          ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywbdcx        ', 'run                 ', '����                          ', 'about:blank                                                                                         ', '����״̬��ѯ                                      ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywbdcx        ', 'list                ', '�������                      ', 'about:blank                                                                                         ', '�������                                          ', 'V2.1.bots ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywbdcx        ', 'def                 ', '��ѯ                          ', 'app/agent/bots/botsplywbdcx.jsp                                                                     ', 'Ĭ��                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPzdc            ', 'def                 ', 'Ĭ��                          ', 'app/agent/bots/botspzdc.jsp                                                                         ', 'Ĭ��                                              ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPzdc            ', 'down                ', '����                          ', 'app/agent/bots/botspzdc.jsp                                                                         ', '����                                              ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsEncry           ', 'del                 ', 'ɾ��                          ', 'about:blank                                                                                         ', 'ɾ��                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsFlowcfg         ', 'stepupt             ', '��������                      ', 'about:blank                                                                                         ', '����                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsFlowcfg         ', 'stepset             ', 'ʹ��ϵͳ����                  ', 'about:blank                                                                                         ', 'ʹ��ϵͳ����                                      ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsFlowcfg         ', 'steplist            ', '�����������                  ', 'about:blank                                                                                         ', '�������                                          ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsFlowcfg         ', 'stepdel             ', 'ɾ��                          ', 'about:blank                                                                                         ', 'ɾ��                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsFlowcfg         ', 'stepattLst          ', '���ϵͳ����                  ', 'about:blank                                                                                         ', '���ϵͳ����                                      ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsFlowcfg         ', 'stepadd             ', '�������                      ', 'about:blank                                                                                         ', '���                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlrwSel         ', 'def                 ', '��ѯ                          ', 'app/agent/bots/botsplrwsel.jsp                                                                      ', 'Ĭ��                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlrwSel         ', 'list                ', '��ѯ                          ', 'about:blank                                                                                         ', '��ѯ                                              ', 'V2.1.bots ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsFlowcfg         ', 'addbd               ', '׷�Ӳ���                      ', 'about:blank                                                                                         ', '׷�Ӳ���                                          ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsRunctrl         ', 'isIn                ', 'ӳ���ʶ�Ƿ����              ', 'about:blank                                                                                         ', 'ӳ���ʶ�Ƿ����                                  ', 'V2.1.bots ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywbh          ', 'del                 ', 'ɾ��                          ', 'about:blank                                                                                         ', 'ɾ��                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywbh          ', 'list                ', '�������                      ', 'about:blank                                                                                         ', '�������                                          ', 'V2.1.bots ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywbh          ', 'def                 ', '��ѯ                          ', 'app/agent/bots/botsplywbh.jsp                                                                       ', 'Ĭ��                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlrw            ', 'next                ', '�ϵ����                      ', 'about:blank                                                                                         ', '�ϵ����                                          ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlrw            ', 'runStop             ', '����/ֹͣ                     ', 'about:blank                                                                                         ', '����/ֹͣ                                         ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlrw            ', 'load                ', '����ȴ�����                  ', 'about:blank                                                                                         ', '����ȴ�����                                      ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlrw            ', 'upload              ', '�����������                  ', 'about:blank                                                                                         ', '�����������                                      ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsFlowcfg         ', 'tree                ', '���������                    ', 'about:blank                                                                                         ', '���������                                        ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsFlowcfg         ', 'dict                ', '���ģ��                      ', 'about:blank                                                                                         ', '��ò���ģ��                                      ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsRunctrl         ', 'del                 ', 'ɾ��                          ', 'about:blank                                                                                         ', 'ɾ��                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsRunctrl         ', 'add                 ', '��Ӹ���                      ', 'about:blank                                                                                         ', '��Ӹ���                                          ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywbh          ', 'add                 ', '��Ӹ���                      ', 'about:blank                                                                                         ', '��Ӹ���                                          ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsFlowcfg         ', 'list                ', '�������                      ', 'about:blank                                                                                         ', '�������                                          ', 'V2.1.bots ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsTablereg        ', 'def                 ', '��ѯ                          ', 'app/agent/bots/botstablereg.jsp                                                                     ', 'Ĭ��                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('ViewYbLs            ', 'def                 ', 'ҽ����ˮĬ�Ͻ���              ', 'app/bots/sb/viewYbLs.jsp                                                                            ', 'ҽ����ˮĬ�Ͻ���                                  ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('ViewYbLs            ', 'qry                 ', 'ҽ����ˮ��ѯ                  ', 'app/bots/sb/viewYbLs.jsp                                                                            ', 'ҽ����ˮ��ѯ                                      ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('ViewYbLs            ', 'down                ', 'ҽ�������ļ�����              ', 'app/bots/sb/viewYbLs.jsp                                                                            ', 'ҽ�������ļ�����                                  ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('szSB                ', 'test                ', '����״̬�鿴                  ', 'app/bots/sb/szSB.jsp                                                                                ', '����״̬�鿴                                      ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('initSB              ', 'def                 ', '��ʼĬ�Ͻ���                  ', 'app/bots/sb/initSB.jsp                                                                              ', '��ʼĬ�Ͻ���                                      ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('initSB              ', 'new                 ', '��ʼ״̬ˢ��                  ', 'app/bots/sb/initSB.jsp                                                                              ', '��ʼ״̬ˢ��                                      ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('initSB              ', 'upfile              ', '��ʼ�ϴ��ļ�                  ', 'app/bots/sb/initSB.jsp                                                                              ', '��ʼ�ϴ��ļ�                                      ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('initSB              ', 'test                ', '��ʼ״̬�鿴                  ', 'app/bots/sb/initSB.jsp                                                                              ', '��ʼ״̬�鿴                                      ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('updateSB            ', 'def                 ', '����Ĭ�Ͻ���                  ', 'app/bots/sb/updateSB.jsp                                                                            ', '����Ĭ�Ͻ���                                      ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('updateSB            ', 'new                 ', 'ҽ������״̬ˢ��              ', 'app/bots/sb/updateSB.jsp                                                                            ', 'ҽ������״̬ˢ��                                  ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('updateSB            ', 'upfile              ', 'ҽ�����������ϴ�              ', 'app/bots/sb/updateSB.jsp                                                                            ', 'ҽ�����������ϴ�                                  ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('updateSB            ', 'test                ', 'ҽ������״̬�鿴              ', 'app/bots/sb/updateSB.jsp                                                                            ', 'ҽ������״̬�鿴                                  ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('updateSB            ', 'down                ', '�����ļ�                      ', 'app/bots/sb/updateSB.jsp                                                                            ', '�����ļ�                                          ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('szSB                ', 'def                 ', '����Ĭ�Ͻ���                  ', 'app/bots/sb/szSB.jsp                                                                                ', '����Ĭ�Ͻ���                                      ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('szSB                ', 'new                 ', '����״̬ˢ��                  ', 'app/bots/sb/szSB.jsp                                                                                ', '����״̬ˢ��                                      ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('szSB                ', 'upfile              ', '�����ļ��ϴ�                  ', 'app/bots/sb/szSB.jsp                                                                                ', '�����ļ��ϴ�                                      ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('szSB                ', 'down                ', 'ҽ�������ļ�����              ', 'app/bots/sb/szSB.jsp                                                                                ', 'ҽ�������ļ�����                                  ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsTablereg        ', 'listtable           ', '��ѯ����                      ', 'about:blank                                                                                         ', '��ѯ����                                          ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsTablereg        ', 'addtable            ', '��ӱ���                      ', 'about:blank                                                                                         ', '��ӱ���                                          ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsTablereg        ', 'deltable            ', 'ɾ������                      ', 'about:blank                                                                                         ', 'ɾ������                                          ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsWbwjdj          ', 'load                ', '�����������                  ', 'about:blank                                                                                         ', '�����������                                      ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsKeyctrl         ', 'def                 ', '��ѯ                          ', 'app/agent/bots/botskeyctrl.jsp                                                                      ', '��ѯ                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsKeyctrl         ', 'add                 ', '���                          ', 'about:blank                                                                                         ', '���                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsKeyctrl         ', 'down                ', '��Կ����                      ', 'about:blank                                                                                         ', '��Կ����                                          ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsKeyctrl         ', 'yes                 ', '���ͨ��                      ', 'about:blank                                                                                         ', '���ͨ��                                          ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsKeyctrl         ', 'list                ', '�������                      ', 'about:blank                                                                                         ', '�������                                          ', 'V2.1.bots ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsTablereg        ', 'order               ', '������                        ', 'about:blank                                                                                         ', '������                                            ', 'V2.1.bots ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsFlowcfg         ', 'del                 ', 'ɾ��                          ', 'about:blank                                                                                         ', 'ɾ��                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsMapinfo         ', 'def                 ', 'Ĭ��                          ', 'app/agent/bots/botsmapinfo.jsp                                                                      ', 'Ĭ��                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsMapinfo         ', 'list                ', '��ѯ����                      ', 'about:blank                                                                                         ', '��ѯ����                                          ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsMapinfo         ', 'add                 ', '���                          ', 'about:blank                                                                                         ', '���                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsMapinfo         ', 'del                 ', 'ɾ��                          ', 'about:blank                                                                                         ', 'ɾ��                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywbdcz        ', 'def                 ', '��ѯ                          ', 'app/agent/bots/botsplywbdcz.jsp                                                                     ', 'Ĭ��                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywbdcz        ', 'list                ', '�������                      ', 'about:blank                                                                                         ', '�������                                          ', 'V2.1.bots ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywlx          ', 'del                 ', 'ɾ��                          ', 'about:blank                                                                                         ', 'ɾ��                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywlx          ', 'add                 ', '��Ӹ���                      ', 'about:blank                                                                                         ', '��Ӹ���                                          ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywlx          ', 'list                ', '�������                      ', 'about:blank                                                                                         ', '�������                                          ', 'V2.1.bots ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywlx          ', 'def                 ', '��ѯ                          ', 'app/agent/bots/botsplywlx.jsp                                                                       ', 'Ĭ��                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsRunctrl         ', 'mapdel              ', 'ɾ����ӳ��                    ', 'about:blank                                                                                         ', 'ɾ��                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsFile            ', 'delcolumn           ', 'ɾ���ļ���                    ', 'about:blank                                                                                         ', 'ɾ���ļ�����                                      ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsFile            ', 'addcolumn           ', '��Ӹ����ļ���                ', 'about:blank                                                                                         ', '��Ӹ����ļ���                                    ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsFile            ', 'listcolumn          ', '����ļ�������                ', 'about:blank                                                                                         ', '�������                                          ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsFile            ', 'delsort             ', 'ɾ���ļ�����                  ', 'about:blank                                                                                         ', 'ɾ���ļ�����                                      ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsFile            ', 'addsort             ', '��Ӹ����ļ�����              ', 'about:blank                                                                                         ', '��Ӹ����ļ�����                                  ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsFile            ', 'listsort            ', '����ļ���������              ', 'about:blank                                                                                         ', '�������                                          ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywbh          ', 'ljkzsel             ', '��ѯ��������                  ', 'about:blank                                                                                         ', '��ѯ��������                                      ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlywbh          ', 'ljkzupt             ', '������������                  ', 'about:blank                                                                                         ', '������������                                      ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlrw            ', 'def                 ', '��ѯ                          ', 'app/agent/bots/botsplrw.jsp                                                                         ', 'Ĭ��                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlrw            ', 'list                ', '�������                      ', 'about:blank                                                                                         ', '�������                                          ', 'V2.1.bots ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPlrw            ', 'send                ', '����                          ', 'about:blank                                                                                         ', '����                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsFile            ', 'ordercolumn         ', '������                        ', 'about:blank                                                                                         ', '������                                            ', 'V2.1.bots ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsFile            ', 'tree                ', '�ļ��ṹ��                    ', 'about:blank                                                                                         ', '�ļ��ṹ��                                        ', 'V2.1.bots ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsWbwjdj          ', 'list                ', '�������                      ', 'about:blank                                                                                         ', '�������                                          ', 'V2.1.bots ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsAuditingfunc    ', 'cfgupt              ', '���²�����Ϣ                  ', 'about:blank                                                                                         ', '����                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsAuditingfunc    ', 'cfglist             ', '��ò�����Ϣ                  ', 'about:blank                                                                                         ', 'ɾ��                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsEncry           ', 'def                 ', '��ѯ                          ', 'app/agent/bots/botsencryptreg.jsp                                                                   ', 'Ĭ��                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsEncry           ', 'list                ', '�������                      ', 'about:blank                                                                                         ', '�������                                          ', 'V2.1.bots ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsAuditingreg     ', 'list                ', '�������                      ', 'about:blank                                                                                         ', '�������                                          ', 'V2.1.bots ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsAuditingreg     ', 'add                 ', '���                          ', 'about:blank                                                                                         ', '���                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsAuditingreg     ', 'upt                 ', '����                          ', 'about:blank                                                                                         ', '����                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsWbwjdjSH        ', 'down                ', '����                          ', 'about:blank                                                                                         ', '����                                              ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPllpwjcx        ', 'def                 ', 'Ĭ��ҳ��                      ', 'app/agent/bots/botswbwjdjcx.jsp                                                                     ', 'Ĭ��ҳ��                                          ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPllpwjcx        ', 'run                 ', 'ִ��                          ', 'app/agent/bots/botswbwjdjcx.jsp                                                                     ', 'ִ��                                              ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsPllpwjcx        ', 'list                ', '��ѯ                          ', 'app/agent/bots/botswbwjdjcx.jsp                                                                     ', '��ѯ                                              ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsZJMapsinfo      ', 'def                 ', 'Ĭ��ҳ��                      ', 'app/agent/bots/botsZJfilemap.jsp                                                                    ', 'Ĭ��ҳ��                                          ', 'V2.1.bots ', '01                            ', '                              ', '                              ');
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsZJMapsinfo      ', 'list                ', '��ѯ                          ', 'list                                                                                                ', '��ѯ                                              ', 'V2.1.bots ', '01                            ', '                              ', '                              ');
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsZJMapsinfo      ', 'add                 ', '���                          ', 'add                                                                                                 ', '���                                              ', 'V2.1.bots ', '01                            ', '                              ', '                              ');
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsZJMapsinfo      ', 'del                 ', 'ɾ��                          ', 'del                                                                                                 ', 'ɾ��                                              ', 'V2.1.bots ', '01                            ', '                              ', '                              ');
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsZJMapsinfo      ', 'upt                 ', '����                          ', 'upt                                                                                                 ', '����                                              ', 'V2.1.bots ', '01                            ', '                              ', '                              ');
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsZJMapsinfo      ', 'maplist             ', '��ѯӳ����                    ', 'maplist                                                                                             ', '��ѯӳ������Ϣ                                    ', 'V2.1.bots ', '01                            ', '                              ', '                              ');
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsZJMapsinfo      ', 'mapupt              ', '����ӳ����                    ', 'mapupt                                                                                              ', '����ӳ������Ϣ                                    ', 'V2.1.bots ', '01                            ', '                              ', '                              ');
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsZJMapsinfo      ', 'mapdel              ', 'ɾ��ӳ������Ϣ                ', 'mapdel                                                                                              ', 'ɾ��ӳ����                                        ', 'V2.1.bots ', '01                            ', '                              ', '                              ');
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsRespmap         ', 'def                 ', 'Ĭ��                          ', 'app/agent/bots/botsRespMap.jsp                                                                      ', 'Ĭ��                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsRespmap         ', 'add                 ', 'ά��                          ', 'about:blank                                                                                         ', 'ά��                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsRespmap         ', 'del                 ', 'ɾ��                          ', 'about:blank                                                                                         ', 'ɾ��                                              ', 'V2.1.bots ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsTablereg        ', 'rzpz                ', '������������                  ', 'about:blank                                                                                         ', '������������                                      ', 'V2.1.bots ', NULL, NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('botsRespmap         ', 'list                ', '��ѯ                          ', 'about:blank                                                                                         ', '��ѯ                                              ', 'V2.1.bots ', NULL, NULL, NULL);


INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(114, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(114, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(114, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(113, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(113, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(113, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(109, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(109, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(109, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(109, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(110, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(110, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(110, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(110, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(113, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(109, 'detailnum           ', '��¼��                        ', '3 ', '0', NULL, '/batch/resp/        ', '0', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(109, 'ywbh                ', 'ҵ����                      ', '1 ', '0', NULL, NULL, '0', NULL, 'V2.1.bots ', NULL, '1                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(109, 'ptpch               ', 'ƽ̨���κ�                    ', '2 ', '0', NULL, NULL, '0', NULL, 'V2.1.bots ', NULL, '1                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(109, 'status              ', '����״̬                      ', '3 ', '0', NULL, NULL, '0', NULL, 'V2.1.bots ', NULL, '1                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(109, 'memo                ', '��ע                          ', '4 ', '0', NULL, NULL, '0', NULL, 'V2.1.bots ', NULL, '1                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(101, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(114, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(101, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(101, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(100, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(100, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(100, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(100, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(101, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(102, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(102, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(102, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(102, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(108, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(108, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(108, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(108, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(107, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(107, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(107, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(107, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(106, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(106, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(106, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(106, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(105, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(105, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(105, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(105, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(104, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(104, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(104, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(104, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(103, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(103, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(103, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(103, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.bots ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);


INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(103, 'nextflag            ', 'ִ�к��������־              ', '1', '4 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(103, 'djlsh               ', '�Ǽ���ˮ��                    ', '1', '3 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(101, 'dqbd                ', '��ǰ����                      ', '1', '4 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(110, 'ywbh                ', 'ҵ����                      ', '1', '1 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(110, 'pkrq                ', '��������                      ', '1', '2 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(110, 'ptpch               ', 'ƽ̨���κ�                    ', '1', '3 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(109, 'ptpch               ', 'ƽ̨���κ�                    ', '1', '3 ', '1', '                                                                                                    ', '                    ', '                                                                                                    ', 'V2.1.bots ', '                                                                                                    ', '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(109, 'pkrq                ', '��������                      ', '3', '2 ', '1', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(113, 'djlsh               ', '�Ǽ���ˮ��                    ', '7', '3 ', '1', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(114, 'pkrq                ', '��������                      ', '1', '2 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(114, 'ywbh                ', 'ҵ����                      ', '1', '1 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(101, 'ywbh                ', 'ҵ����                      ', '1', '1 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(101, 'pkrq                ', '��������                      ', '1', '2 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(105, 'nextflag            ', 'ִ�к��������־              ', '1', '4 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(105, 'ptpch               ', 'ƽ̨���κ�                    ', '1', '3 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(105, 'pkrq                ', '��������                      ', '1', '2 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(105, 'ywbh                ', 'ҵ����                      ', '1', '1 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(104, 'nextflag            ', 'ִ�к��������־              ', '1', '4 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(104, 'ptpch               ', 'ƽ̨���κ�                    ', '1', '3 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(104, 'pkrq                ', '��������                      ', '1', '2 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(104, 'ywbh                ', 'ҵ����                      ', '1', '1 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(103, 'ywbh                ', 'ҵ����                      ', '1', '1 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(103, 'djrq                ', '�Ǽ�����                      ', '1', '2 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(114, 'ptpch               ', 'ƽ̨���κ�                    ', '1', '3 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(108, 'zjpch               ', '�������κ�                    ', '1', '5 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(107, 'zjpch               ', '�������κ�                    ', '1', '5 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(106, 'zjpch               ', '�������κ�                    ', '1', '5 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(105, 'zjpch               ', '�������κ�                    ', '1', '5 ', '1', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(104, 'zjpch               ', '�������κ�                    ', '1', '5 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(101, 'zjpch               ', '�������κ�                    ', '1', '5 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(109, 'ywbh                ', 'ҵ����                      ', '5', '1 ', '1', NULL, NULL, 'com.hundsun.agent.web.bots.sendUtil.Plywbh910010Send                                                ', 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(100, 'ywbh                ', 'ҵ����                      ', '1', '2 ', '1', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(100, 'lpwjm               ', '�����ļ���                    ', '1', '1 ', '1', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(100, 'zje                 ', '�ܽ��                        ', '1', '5 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(100, 'shpch               ', '�̻����κ�                    ', '1', '3 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(100, 'zbs                 ', '�ܱ���                        ', '1', '4 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(100, 'hpwjm               ', '�����ļ���                    ', '1', '6 ', '1', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(100, 'lrfs                ', '¼�뷽ʽ                      ', '6', '7 ', '1', NULL, NULL, '1                                                                                                   ', 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(113, 'ywbh                ', 'ҵ����                      ', '5', '1 ', '1', '                                                                                                    ', '                    ', 'com.hundsun.agent.web.bots.sendUtil.Plywbh910010Send                                                ', 'V2.1.bots ', '                                                                                                    ', '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(113, 'djrq                ', '��������                      ', '3', '2 ', '1', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(100, 'hqsjfs              ', '��ȡ���ݷ�ʽ                  ', '1', '8 ', '1', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(100, 'localpath           ', '����·��                      ', '1', '9 ', '1', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(100, 'threadno            ', '�߳���                        ', '1', '91', '1', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(100, 'taskmode            ', '����ʼ��ʽ                  ', '1', '92', '1', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(102, 'productma           ', '��Ʒ�����������              ', '1', '5 ', '0', '                                                                                                    ', '                    ', '                                                                                                    ', 'V2.1.bots ', '��Ʒ�����������                                                                                    ', '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(102, 'busimax             ', 'Ӧ�������������              ', '1', '4 ', '0', '                                                                                                    ', '                    ', '                                                                                                    ', 'V2.1.bots ', 'Ӧ�������������                                                                                    ', '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(102, 'djlsh               ', '�Ǽ���ˮ��                    ', '1', '3 ', '1', '                                                                                                    ', '                    ', '                                                                                                    ', 'V2.1.bots ', '�Ǽ���ˮ��                                                                                          ', '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(102, 'djrq                ', '�Ǽ�����                      ', '3', '2 ', '1', '                                                                                                    ', '                    ', '                                                                                                    ', 'V2.1.bots ', '�Ǽ�����                                                                                            ', '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(102, 'ywbh                ', 'ҵ����                      ', '5', '1 ', '1', '                                                                                                    ', '                    ', 'com.hundsun.agent.web.bots.sendUtil.Plywbh910010Send                                                ', 'V2.1.bots ', 'ҵ����                                                                                            ', '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(108, 'nextflag            ', 'ִ�к��������־              ', '1', '4 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(108, 'ptpch               ', 'ƽ̨���κ�                    ', '1', '3 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(108, 'pkrq                ', '��������                      ', '1', '2 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(108, 'ywbh                ', 'ҵ����                      ', '1', '1 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(107, 'nextflag            ', 'ִ�к��������־              ', '1', '4 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(107, 'ptpch               ', 'ƽ̨���κ�                    ', '1', '3 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(107, 'pkrq                ', '��������                      ', '1', '2 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(107, 'ywbh                ', 'ҵ����                      ', '1', '1 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(106, 'nextflag            ', 'ִ�к��������־              ', '1', '4 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(106, 'ptpch               ', 'ƽ̨���κ�                    ', '1', '3 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(106, 'pkrq                ', '��������                      ', '1', '2 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(101, 'ptpch               ', 'ƽ̨���κ�                    ', '1', '3 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(106, 'ywbh                ', 'ҵ����                      ', '1', '1 ', '0', NULL, NULL, NULL, 'V2.1.bots ', NULL, '/batch/req/                   ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(115, 'pkrq                ', '��������                      ', '3', '2 ', '1', '                                                                                                    ', '                    ', '                                                                                                    ', 'V2.1.bots ', '��������                                                                                            ', '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(115, 'ywbh                ', 'ҵ����                      ', '5', '1 ', '1', '                                                                                                    ', '                    ', 'com.hundsun.agent.web.bots.sendUtil.Plywbh910010Send                                                ', 'V2.1.bots ', 'ҵ����                                                                                            ', '/tamc/req/                    ', NULL, NULL, NULL, NULL, NULL);


INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(101, '910004                        ', '����ҵ��ϵ㴦��                                  ', '1', NULL, 'admin               ', '70001               ', '100                 ', 'V2.1.bots ', NULL, 'botsXml                       ', 'botsFile                      ', NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(102, '910002                        ', '����ҵ��������                                  ', '1', NULL, 'admin               ', '70001               ', '100                 ', 'V2.1.bots ', NULL, 'botsXml                       ', 'botsFile                      ', NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(107, '910009                        ', '����ҵ���������                                  ', '1', NULL, 'admin               ', '70001               ', '100                 ', 'V2.1.bots ', NULL, 'botsXml                       ', 'botsFile                      ', NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(106, '910008                        ', '����ҵ�������ύ                                  ', '1', NULL, 'admin               ', '70001               ', '100                 ', 'V2.1.bots ', NULL, 'botsXml                       ', 'botsFile                      ', NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(114, '910015                        ', '����ҵ���������γ���                              ', '1', '                    ', 'admin               ', '00000               ', '100                 ', 'V2.1.bots ', '', 'botsXml                       ', 'botsFile                      ', '                                                                                                                                                      ', '                                                                                                                                                      ', NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(113, '910013                        ', '����ҵ������ȡ��                                  ', '1', NULL, 'admin               ', '70001               ', '100                 ', 'V2.1.bots ', NULL, 'botsXml                       ', 'botsFile                      ', NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(105, '910007                        ', '����ҵ���������                                  ', '1', NULL, 'admin               ', '70001               ', '100                 ', 'V2.1.bots ', NULL, 'botsXml                       ', 'botsFile                      ', NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(104, '910006                        ', '����ҵ���������                                  ', '1', NULL, 'admin               ', '70001               ', '100                 ', 'V2.1.bots ', NULL, 'botsXml                       ', 'botsFile                      ', NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(100, '910001                        ', '����ҵ������¼��                                  ', '1', NULL, 'chensy              ', '70001               ', '100                 ', 'V2.1.bots ', NULL, 'botsXml                       ', 'botsFile                      ', NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(103, '910005                        ', '����ҵ���ȡ����                                  ', '1', NULL, 'admin               ', '70001               ', '100                 ', 'V2.1.bots ', NULL, 'botsXml                       ', 'botsFile                      ', NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(108, '910010                        ', '����ҵ�����ݻ���                                  ', '1', '                    ', 'admin               ', '00000               ', '100                 ', 'V2.1.bots ', '', 'botsXml                       ', 'botsFile                      ', '                                                                                                                                                      ', '                                                                                                                                                      ', NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(110, '910014                        ', '����ҵ���������γ���                              ', '1', '                    ', 'admin               ', '00000               ', '100                 ', 'V2.1.bots ', '', 'botsXml                       ', 'botsFile                      ', '                                                                                                                                                      ', '                                                                                                                                                      ', NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(109, '910012                        ', '����ҵ����������״̬��ѯ                          ', '4', '/batch/resp/        ', 'admin               ', '00000               ', '100                 ', 'V2.1.bots ', '', 'botsXml                       ', 'botsFile                      ', '                                                                                                                                                      ', '                                                                                                                                                      ', NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(115, '910020                        ', '����������                                      ', '0', NULL, 'admin               ', '00000               ', '100                 ', 'V2.1.bots ', NULL, 'botsXml                       ', 'botsFile                      ', NULL, NULL, NULL, NULL, NULL, NULL);


INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_Encry                    ', 'bots_keyM                     ', 4, '�����ӽ���ע��                ', '�����ӽ���ע��                                    ', '1', 'botsEncry           ', '0', 'V2.1.bots ', NULL, '900252710000        ', '0', 'agent     ', '                              ', NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_shgz                     ', 'bots_message                  ', 3, '�������                      ', '�������                                          ', '0', 'botsAuditingreg     ', '1', 'V2.1.bots ', NULL, '900252600000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_Pzdc                     ', 'bots_message                  ', 3, '�������õ���                  ', '�������õ���                                      ', '1', 'botsPzdc            ', '1', 'V2.1.bots ', NULL, '900252800000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_AUDITINGREG              ', 'bots_shgz                     ', 4, '��˺�������                  ', '��˺�������                                      ', '1', 'botsAuditingreg     ', '1', 'V2.1.bots ', NULL, '900252610000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_mapinfo                  ', 'bots_message                  ', 3, '�ļ�ӳ������                  ', '�ļ�ӳ������                                      ', '0', 'botsMapinfo         ', '1', 'V2.1.bots ', NULL, '900252400000        ', '0', 'agent     ', '                              ', NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_plywbdcz                 ', 'bots_fz                       ', 3, '�����������������            ', '�����������������                                ', '1', 'botsPlywbdcz        ', '1', 'V2.1.bots ', NULL, '900254300000        ', '0', 'agent     ', '                              ', NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_zjfilemap                ', 'bots_mapinfo                  ', 4, '����ӳ��                      ', '�����ļ�ӳ��                                      ', '1', 'botsZJMapsinfo      ', '1', 'V2.1.bots ', '                                        ', '900252420000        ', '0', 'agent     ', '                              ', '                                                                                                    ', '                                                                                                    ');
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_WBfilemap                ', 'bots_mapinfo                  ', 4, '�ⲿӳ��                      ', '�ⲿ�ļ�ӳ��                                      ', '1', 'botsMapinfo         ', '1', 'V2.1.bots ', '                                        ', '900252430000        ', '0', 'agent     ', '                              ', '                                                                                                    ', '                                                                                                    ');
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_plywrwqx                 ', 'bots_fz                       ', 3, '��������¼�볷��              ', '���������ļ�¼�볷��                              ', '1', 'botsPllpwjcx        ', '1', 'V2.1.bots ', '                                        ', '900254400000        ', '0', 'agent     ', '                              ', 'send_id=113                                                                                         ', NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_keyctrl                  ', 'bots_keyM                     ', 4, '������Կ����                  ', '������Կ����                                      ', '1', 'botsKeyctrl         ', '0', 'V2.1.bots ', NULL, '900252720000        ', '0', 'agent     ', '                              ', NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_plywbdcx                 ', 'bots_fz                       ', 3, '����������������              ', '����������������                                  ', '1', 'botsPlywbdcx        ', '1', 'V2.1.bots ', NULL, '900254200000        ', '0', 'agent     ', '                              ', NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_downgapsfile             ', 'bots_fz                       ', 3, '�ļ�����                      ', '�ļ�����                                          ', '1', 'botsGapsdown        ', '1', 'V2.1.bots ', NULL, '900254500000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_keyM                     ', 'bots_message                  ', 3, '�ӽ��ܹ���                    ', '�ӽ��ܹ���                                        ', '0', 'botsKeyctrl         ', '0', 'V2.1.bots ', NULL, '900252700000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_plywmx                   ', 'bots_report                   ', 3, '����ҵ����ϸ                  ', '����ҵ����ϸ                                      ', '1', 'botsPlywmx          ', '1', 'V2.1.bots ', NULL, '900255100000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_plywbd                   ', 'bots_run                      ', 3, '�����쳣��������              ', '������������                                      ', '1', 'botsPlywbd          ', '1', 'V2.1.bots ', NULL, '900253300000        ', '0', 'agent     ', '                              ', NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_run                      ', 'bots                          ', 2, '����ҵ������                  ', '����ҵ������                                      ', '0', 'alterUserPass       ', '1', 'V2.1.bots ', NULL, '900253000000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_message                  ', 'bots                          ', 2, '����ҵ������                  ', '����ҵ������                                      ', '0', 'alterUserPass       ', '1', 'V2.1.bots ', NULL, '900252000000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_report                   ', 'bots                          ', 2, '����ҵ�񱨱�                  ', '����ҵ�񱨱�                                      ', '0', 'alterUserPass       ', '1', 'V2.1.bots ', NULL, '900255000000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_wbwjdj                   ', 'bots_run                      ', 3, '�����ļ�����¼��              ', '�����ļ�����¼��                                  ', '1', 'botsWbwjdj          ', '1', 'V2.1.bots ', NULL, '900253100000        ', '0', 'agent     ', '                              ', NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_wbwjsh                   ', 'bots_run                      ', 3, '����ⲿ�ļ�                  ', '����ⲿ�ļ�                                      ', '1', 'botsWbwjdjSH        ', '1', 'V2.1.bots ', NULL, '900253200000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots                          ', '/                             ', 1, '��������                      ', '��������                                          ', '0', 'botsPlywlx          ', '1', 'V2.1.bots ', NULL, '900250000000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_plrw                     ', 'bots_run                      ', 3, '����ҵ����                  ', '����ҵ����                                      ', '1', 'botsPlrw            ', '1', 'V2.1.bots ', NULL, '900253400000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_flowcfg                  ', 'bots_message                  ', 3, '��������                      ', '��������                                          ', '1', 'botsFlowcfg         ', '1', 'V2.1.bots ', NULL, '900252300000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_Plywbdmx                 ', 'bots_report                   ', 3, '����������ϸ                  ', '����ҵ�񲽵���ϸ                                  ', '1', 'botsPlywbdmx        ', '1', 'V2.1.bots ', NULL, '900255400000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_file                     ', 'bots_message                  ', 3, '�ļ�����                      ', '�ļ�����                                          ', '1', 'botsFile            ', '1', 'V2.1.bots ', NULL, '900252100000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_fz                       ', 'bots                          ', 2, '������������                  ', '������������                                      ', '0', 'botsAuditingreg     ', '1', 'V2.1.bots ', NULL, '900254000000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_zjpczt                   ', 'bots_fz                       ', 3, '����״̬��ѯ                  ', '����״̬��ѯ                                      ', '1', 'send                ', '1', 'V2.1.bots ', '                                        ', '900254100000        ', '0', 'agent     ', '                              ', 'send_id=109                                                                                         ', NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_func                     ', 'bots_shgz                     ', 4, '�����������                  ', '�����������                                      ', '1', 'botsAuditingfunc    ', '1', 'V2.1.bots ', NULL, '900252620000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_tablereg                 ', 'bots_message                  ', 3, '��ṹ����                    ', '��ṹ����                                        ', '1', 'botsTablereg        ', '1', 'V2.1.bots ', NULL, '900252200000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_Plywsel                  ', 'bots_report                   ', 3, '���������ѯ                  ', '���������ѯ                                      ', '1', 'botsPlrwSel         ', '1', 'V2.1.bots ', NULL, '900255300000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_runctrl                  ', 'bots_message                  ', 3, '���п�������                  ', '���п�������                                      ', '1', 'botsRunctrl         ', '1', 'V2.1.bots ', NULL, '900252500000        ', '0', 'agent     ', '                              ', NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_plrwfq2                  ', 'bots_run                      ', 3, '����������                  ', '����������(�������ļ�)                          ', '1', 'send                ', '1', 'V2.1.bots ', '                                        ', '900253150000        ', '0', 'agent     ', '                              ', 'send_id=115                                                                                         ', NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('bots_map_xym                  ', 'bots_mapinfo                  ', 4, '��Ӧ��ӳ��                    ', '��Ӧ��ӳ��                                        ', '1', 'botsRespmap         ', '1', 'V2.1.bots ', '                                        ', '900252410000        ', '0', 'agent     ', '                              ', '                                                                                                    ', '                                                                                                    ');


INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step_5              ', '�����ύ�������              ', '0                             ', '���˳ɹ�                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step_5              ', '�����ύ�������              ', '1                             ', '���ݿ����                    ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step_5              ', '�����ύ�������              ', '9                             ', '������                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step_6              ', '���ȡ�ش������              ', '0                             ', '�����ȡ��                    ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step_8              ', '�鵵�������                  ', 'B                             ', '�鵵��                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step_8              ', '�鵵�������                  ', '0                             ', '�鵵����                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step_*              ', '���������������              ', '0                             ', '�����ɹ�                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step_*              ', '���������������              ', '1                             ', '�ѳ���                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step_*              ', '���������������              ', '2                             ', '��������                    ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step_*              ', '���������������              ', '9                             ', '������                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_lrbz                 ', '�Ƿ���Ҫ����¼��              ', '0                             ', '��                            ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_lrbz                 ', '�Ƿ���Ҫ����¼��              ', '1                             ', '��                            ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_hqsjfs               ', '��ȡ���ݷ�ʽ                  ', '0                             ', 'FTP����ȡ                     ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_hqsjfs               ', '��ȡ���ݷ�ʽ                  ', '1                             ', '����ȡ                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_hqsjfs               ', '��ȡ���ݷ�ʽ                  ', '2                             ', '���ױ���                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_jywjfs               ', 'У���ļ���ʽ                  ', '0                             ', '��У��                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_jywjfs               ', 'У���ļ���ʽ                  ', '1                             ', 'У��                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_run_shbz                 ', '��˱�־                      ', '0                             ', '��Ҫ����ⲿ�ļ�              ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_run_shbz                 ', '��˱�־                      ', '1                             ', '����Ҫ����ⲿ�ļ�            ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_rwksfs                   ', '����ʼ��ʽ                  ', '1                             ', '����                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_rwksfs                   ', '����ʼ��ʽ                  ', '2                             ', '�ֶ�                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_flag                ', '������                        ', '0                             ', '���׽���ۼ�                  ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_flag                ', '������                        ', '1                             ', '���׽���ۼ�                  ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_flag                ', '������                        ', '2                             ', '�ֶ�SUM                       ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_flag                ', '������                        ', '3                             ', '�ֶ�COUNT                     ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_flag                ', '������                        ', '4                             ', 'ֵ����                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_flag                ', '������                        ', '5                             ', 'ֵ��ȡ                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_flag                ', '������                        ', '6                             ', '���ܼ�¼����-���ܱ���         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_flag                ', '������                        ', '7                             ', '���ܼ�¼����-���ܽ��         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_lylx                ', '��Դ����                      ', '2                             ', 'xml��ȡ                       ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('batch_plyw_rwzt               ', '��������״̬                  ', 'C                             ', '�ѳ���                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_dbdbz               ', '���㽻�ױ�־                  ', '910005                        ', '��ȡ����                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '21                            ', '[21]NAK(��)                 ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '20                            ', '[20]DC4(�豸����4)            ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '2                             ', '[2]STX(���Ŀ�ʼ)              ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '19                            ', '[19]DC3(�豸����3)            ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '18                            ', '[18]DC2(�豸����2)            ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '17                            ', '[17]DC1(�豸����1)            ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '16                            ', '[16]DLE(�ո�)                 ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step_5              ', '�����ύ�������              ', 'B                             ', '�������˴�����                ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '15                            ', '[15]SI(��λ����)              ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '14                            ', '[14]SO(��λ���)              ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '13                            ', '[13]CR(�س�)                  ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '127                           ', '[127]DEL(ɾ��)                ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '126                           ', '[126]~                        ', 'V2.1.bots ', '1                             ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '125                           ', '[125]}                        ', 'V2.1.bots ', '1                             ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '124                           ', '[124]|                        ', 'V2.1.bots ', '1                             ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '123                           ', '[123]{                        ', 'V2.1.bots ', '1                             ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '122                           ', '[122]z                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '121                           ', '[121]y                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '120                           ', '[120]x                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '12                            ', '[12]FF(��ֽ����)              ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '119                           ', '[119]w                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '118                           ', '[118]v                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '117                           ', '[117]u                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '116                           ', '[116]t                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '115                           ', '[115]s                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '114                           ', '[114]r                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '113                           ', '[113]q                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '112                           ', '[112]p                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '111                           ', '[111]o                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '110                           ', '[110]n                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '11                            ', '[11]VT(��ֱ�Ʊ�)              ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '109                           ', '[109]m                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '108                           ', '[108]l                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '107                           ', '[107]k                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '106                           ', '[106]j                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '105                           ', '[105]i                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '104                           ', '[104]h                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '103                           ', '[103]g                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '102                           ', '[102]f                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '101                           ', '[101]e                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '100                           ', '[100]d                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '10                            ', '[10]LF(����)                  ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '1                             ', '[1]SOH(���⿪ʼ)              ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '0                             ', '[0]NUT                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '49                            ', '[49]1                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '5                             ', '[5]ENQ(ѯ���ַ�)              ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '50                            ', '[50]2                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '51                            ', '[51]3                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '52                            ', '[52]4                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '53                            ', '[53]5                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '54                            ', '[54]6                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_hzfs                ', '���ܷ�ʽ                      ', '1                             ', 'ȫ������                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_hzfs                ', '���ܷ�ʽ                      ', '2                             ', '�ɹ�����                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_hzfs                ', '���ܷ�ʽ                      ', '3                             ', 'ʧ�ܻ���                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_lylx                ', '��Դ����                      ', '3                             ', '�ļ����                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_lylx                ', '��Դ����                      ', '4                             ', '��ˮ���                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_lylx                ', '��Դ����                      ', '5                             ', '����                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_lylx                ', '��Դ����                      ', '6                             ', '�ۺ�ǰ����ˮ��                ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_fldtype                  ', '��������                      ', 'I                             ', '����                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_lylx                ', '��Դ����                      ', '1                             ', '�����ļ���ȡ                  ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_fldtype                  ', '��������                      ', 'D                             ', '����                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_fldtype                  ', '��������                      ', 'C                             ', '�ַ���                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_tjgxbz                   ', '�ύ���±�־                  ', '1                             ', '��������                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('cz_syslx                      ', '����ϵͳ����                  ', '0                             ', '��ϵͳ                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('cz_syslx                      ', '����ϵͳ����                  ', '1                             ', '��ϵͳ                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('cz_syslx                      ', '����ϵͳ����                  ', '2                             ', '�Ե�ϵͳһ��                  ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('cz_syslx                      ', '����ϵͳ����                  ', '3                             ', '�Ե�ϵͳ����                  ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_clfs                     ', '����ʽ                      ', '2                             ', '��ʱ                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_fqfs                     ', '����ʽ                      ', '1                             ', 'web                           ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_fqfs                     ', '����ʽ                      ', '2                             ', '����                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_fqfs                     ', '����ʽ                      ', '3                             ', '�̻�                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_flow_yxsx                ', '��������                      ', '0                             ', '��������                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_flow_yxsx                ', '��������                      ', '1                             ', '��������                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_clfs                     ', '����ʽ                      ', '1                             ', '�ֹ�                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_fileType                 ', '����ҵ���ļ�����              ', '1                             ', '�����ı�                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_fileType                 ', '����ҵ���ļ�����              ', '2                             ', '�ָ����ı�                    ', 'V2.1.bots ', NULL);
INSERT INTO t_dict(dict_kind, dict_name, dict_key, dict_info, version, bak)
  VALUES('bots_fileType                 ', '����ҵ���ļ�����              ', '3                             ', 'ȥβ�ָ����ı�                ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '55                            ', '[55]7                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '56                            ', '[56]8                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '57                            ', '[57]9                         ', 'V2.1.bots ', '1                             ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '58                            ', '[58]:                         ', 'V2.1.bots ', '1                             ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '59                            ', '[59];                         ', 'V2.1.bots ', '1                             ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '6                             ', '[6]ACK(����)                  ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '60                            ', '[60]<                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '61                            ', '[61]=                         ', 'V2.1.bots ', '1                             ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '62                            ', '[62]>                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '63                            ', '[63]?                         ', 'V2.1.bots ', '1                             ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '64                            ', '[64]@                         ', 'V2.1.bots ', '1                             ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '65                            ', '[65]A                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '66                            ', '[66]B                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '67                            ', '[67]C                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '68                            ', '[68]D                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '69                            ', '[69]E                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '7                             ', '[7]BEL(����)                  ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '70                            ', '[70]F                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '71                            ', '[71]G                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '72                            ', '[72]H                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '73                            ', '[73]I                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '74                            ', '[74]J                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '75                            ', '[75]K                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '76                            ', '[76]L                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '77                            ', '[77]M                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '78                            ', '[78]N                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '79                            ', '[79]O                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '8                             ', '[8]BS(��һ��)                 ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '80                            ', '[80]P                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '81                            ', '[81]Q                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '82                            ', '[82]R                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '83                            ', '[83]X                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '84                            ', '[84]T                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '85                            ', '[85]U                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '86                            ', '[86]V                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '87                            ', '[87]W                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '88                            ', '[88]X                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '89                            ', '[89]Y                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '9                             ', '[9]HT(�����б�)               ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '90                            ', '[90]Z                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '91                            ', '[91][                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '92                            ', '[92]\                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '93                            ', '[93]]                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '94                            ', '[94]^                         ', 'V2.1.bots ', '1                             ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '95                            ', '[95]__                        ', 'V2.1.bots ', '1                             ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '96                            ', '[96]��                        ', 'V2.1.bots ', '1                             ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '97                            ', '[97]a                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '98                            ', '[98]b                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '99                            ', '[99]c                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('batch_plyw_rwzt               ', '����״̬                      ', '3                             ', '����                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_auditing_shsbbz          ', '���ʧ�ܱ�־                  ', '0                             ', '�������ʧ��                  ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_auditing_shsbbz          ', '���ʧ�ܱ�־                  ', '1                             ', '�������ʧ����ϸ              ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_NextFlag            ', 'ִ�б�־                      ', '0                             ', 'ִ��                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_NextFlag            ', 'ִ�б�־                      ', '1                             ', '��ִ��                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_wbwj_shbz                ', '��˱�־                      ', '0                             ', '���ͨ��                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_wbwj_shbz                ', '��˱�־                      ', '1                             ', 'δ���                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_lc_bd                    ', '���̲���                      ', 'hqsj                          ', '��ȡ����                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_lc_bd                    ', '���̲���                      ', 'sjtj                          ', '�����ύ                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_lc_bd                    ', '���̲���                      ', 'sjth                          ', '�������                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_lc_bd                    ', '���̲���                      ', 'sjsh                          ', '�������                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_lc_bd                    ', '���̲���                      ', 'sjrk                          ', '�������                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_lc_bd                    ', '���̲���                      ', 'sjhp                          ', '���ݻ���                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_dbdbz               ', '���㽻�ױ�־                  ', '910011                        ', '���ݻ���                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_dbdbz               ', '���㽻�ױ�־                  ', '910006                        ', '�������                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_dbdbz               ', '���㽻�ױ�־                  ', '910007                        ', '�������                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_dbdbz               ', '���㽻�ױ�־                  ', '910009                        ', '�������                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_dbdbz               ', '���㽻�ױ�־                  ', '910008                        ', '�����ύ                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_cxbz                 ', '������־                      ', '1                             ', '������                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_cxbz                 ', '������־                      ', '0                             ', '����                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_jmbz                 ', '�ӽ��ܱ�־                    ', '0                             ', '�������                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_jmbz                 ', '�ӽ��ܱ�־                    ', '1                             ', '��Ҫ����                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_wjlxzhbz             ', '�ļ�����ת����־              ', '0                             ', '����ת��                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_wjlxzhbz             ', '�ļ�����ת����־              ', '1                             ', '��Ҫת��                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_sjlx                 ', '��������                      ', '1                             ', '����                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_sjlx                 ', '��������                      ', '2                             ', '�ļ�                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_sjlx                 ', '��������                      ', '3                             ', '����+�ļ�                     ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_sjlx                 ', '��������                      ', '4                             ', '�ļ�+����                     ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_bwlx                 ', '��������                      ', '1                             ', 'xml                           ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_bwlx                 ', '��������                      ', '2                             ', 'icxp                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_bwlx                 ', '��������                      ', '3                             ', '8583                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_wjtxlx               ', '�ļ�ͨѶ����                  ', '1                             ', 'FTP                           ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_wjtxlx               ', '�ļ�ͨѶ����                  ', '2                             ', '����                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_sqzjpcbz             ', '�Ƿ�������������              ', '0                             ', '��                            ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_sqzjpcbz             ', '�Ƿ�������������              ', '1                             ', '��                            ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_wjfjbz               ', '�ļ��־��־                  ', '0                             ', '���־�                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_wjfjbz               ', '�ļ��־��־                  ', '1                             ', '���ֽڷ�                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_wjfjbz               ', '�ļ��־��־                  ', '2                             ', '��������                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_failflag             ', 'ʧ����ϸ�ύ��־              ', '0                             ', '�ύ�Ǳ����δ���ʧ����ϸ      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_failflag             ', 'ʧ����ϸ�ύ��־              ', '1                             ', '�ύ�����δ���ʧ����ϸ        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_failflag             ', 'ʧ����ϸ�ύ��־              ', '2                             ', '�ύ������δ������ϸ          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_fssjfs               ', '�������ݷ�ʽ                  ', '0                             ', 'FTP��������                   ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_fssjfs               ', '�������ݷ�ʽ                  ', '1                             ', 'WEB���������                 ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_att_fssjfs               ', '�������ݷ�ʽ                  ', '2                             ', '������ʽ                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('batch_plyw_rwzt               ', '����״̬                      ', 'X                             ', '�ѳ���                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('batch_plrw_czbd               ', '��������                      ', 'X                             ', '����                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('batch_plrw_czbd               ', '��������                      ', '5                             ', '���ݻ���                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('batch_plrw_czbd               ', '��������                      ', '4                             ', '�������                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('batch_plrw_czbd               ', '��������                      ', '3                             ', '�����ύ                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('batch_plrw_czbd               ', '��������                      ', '2                             ', '�������                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('batch_plrw_czbd               ', '��������                      ', '1                             ', '�������                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('batch_plrw_czbd               ', '��������                      ', '0                             ', '��ȡ����                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '23                            ', '[23]TB                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '24                            ', '[24]CAN(����)                 ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '25                            ', '[25]EM(ֽ��)                  ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '26                            ', '[26]SUB(����)                 ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '27                            ', '[27]ESC(����)                 ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '28                            ', '[28]FS(���ַָ���)            ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '29                            ', '[29]GS(��ָ���)              ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '3                             ', '[3]ETX(���Ľ���)              ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '30                            ', '[30]RS(��¼�ָ���)            ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '31                            ', '[31]US(��Ԫ�ָ���)            ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '32                            ', '[32](space)                   ', 'V2.1.bots ', '1                             ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '33                            ', '[33]��                        ', 'V2.1.bots ', '1                             ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '34                            ', '[34]��                        ', 'V2.1.bots ', '1                             ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '35                            ', '[35]#                         ', 'V2.1.bots ', '1                             ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '36                            ', '[36]$                         ', 'V2.1.bots ', '1                             ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '37                            ', '[37]%                         ', 'V2.1.bots ', '1                             ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '38                            ', '[38]&                         ', 'V2.1.bots ', '1                             ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '39                            ', '[39]''                         ', 'V2.1.bots ', '1                             ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '4                             ', '[4]EOT                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '40                            ', '[40](                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '41                            ', '[41])                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '42                            ', '[42]*                         ', 'V2.1.bots ', '1                             ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '43                            ', '[43]+                         ', 'V2.1.bots ', '1                             ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '44                            ', '[44],                         ', 'V2.1.bots ', '1                             ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '45                            ', '[45]-                         ', 'V2.1.bots ', '1                             ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '46                            ', '[46].                         ', 'V2.1.bots ', '1                             ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '47                            ', '[47]/                         ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '48                            ', '[48]0                         ', 'V2.1.bots ', '1                             ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step                ', '�����׶�                      ', '1                             ', '�ύ�׶�                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step                ', '�����׶�                      ', '3                             ', '�ļ����׶�                  ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step                ', '�����׶�                      ', '5                             ', '���˽׶�                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step                ', '�����׶�                      ', '6                             ', '���ȡ�ؽ׶�                  ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step                ', '�����׶�                      ', '8                             ', '�鵵�׶�                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step                ', '�����׶�                      ', '*                             ', '���������׶�                  ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step_1              ', '�����ύ�������              ', 'B                             ', '�����ύ������                ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step_1              ', '�����ύ�������              ', '0                             ', '�ύ�ɹ�                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step_1              ', '�����ύ�������              ', '1                             ', 'ǩԼ�ʺŴ�                    ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step_1              ', '�����ύ�������              ', '2                             ', '�鼯�ʺŴ�                    ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step_1              ', '�����ύ�������              ', '3                             ', 'ǩԼ�ʺ�����              ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step_1              ', '�����ύ�������              ', '4                             ', '�鼯�ʺ�����              ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step_1              ', '�����ύ�������              ', '5                             ', 'ԤԼ���ڴ�                    ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step_1              ', '�����ύ�������              ', '6                             ', '6�����ֶδ�                   ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step_1              ', '�����ύ�������              ', '7                             ', '�ļ���С��                    ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_lc_bdsx                  ', '���̲���˳���Ӧ              ', '4                             ', 'sjtj                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_dsfbz                    ', '���ո���־                    ', '1                             ', '����                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_dsfbz                    ', '���ո���־                    ', '2                             ', '����                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_dsfbz                    ', '���ո���־                    ', '3                             ', '����                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('batch_plrw_bdzt               ', '����״̬                      ', '0                             ', 'ʧ����ֹ                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('batch_plrw_bdzt               ', '����״̬                      ', '1                             ', '�ɹ�����                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('batch_plrw_bdzt               ', '����״̬                      ', '2                             ', '�ϵ�                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('batch_plrw_bdzt               ', '����״̬                      ', '3                             ', '����                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('batch_plrw_bdzt               ', '����״̬                      ', '4                             ', '�ȴ�                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('batch_plyw_bdzt               ', '����״̬                      ', '9                             ', '�ڴ�����                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('batch_plyw_rwzt               ', '����״̬                      ', '0                             ', 'ʧ����ֹ                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('batch_plyw_rwzt               ', '����״̬                      ', '1                             ', '�ɹ�����                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('batch_plyw_rwzt               ', '����״̬                      ', '2                             ', '��ͣ                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('batch_plyw_rwzt               ', '����״̬                      ', '9                             ', '�ڴ�����                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('batch_plrw_bdzt               ', '����״̬                      ', '9                             ', '�ڴ�����                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_fmt                 ', '�ļ���ʽ                      ', '01                            ', '����ϸ                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_fmt                 ', '�ļ���ʽ                      ', '02                            ', '���ܣ�����ϸ                  ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_fmt                 ', '�ļ���ʽ                      ', '03                            ', '����ϸ������                  ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_ext                 ', '�ļ�����                      ', '0                             ', 'TXT                           ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_ext                 ', '�ļ�����                      ', '1                             ', 'DBF                           ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_ext                 ', '�ļ�����                      ', '2                             ', 'XLS                           ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_ext                 ', '�ļ�����                      ', '3                             ', 'XLSX                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_fllx                ', '�ļ���������                  ', '1                             ', '����                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_fllx                ', '�ļ���������                  ', '2                             ', '��ϸ                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_wzbz                ', '�����ļ�λ�ñ�־              ', '1                             ', '���У���һ�У�                ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_wzbz                ', '�����ļ�λ�ñ�־              ', '2                             ', '��¼��ʶ                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_wzbz                ', '�����ļ�λ�ñ�־              ', '3                             ', '���ܼ�¼֮��                  ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step_1              ', '�����ύ�������              ', '9                             ', '������                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step_3              ', '�ļ���鴦�����              ', 'B                             ', '�ļ���鴦����                ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step_3              ', '�ļ���鴦�����              ', '0                             ', '�ļ����ɹ�                  ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step_3              ', '�ļ���鴦�����              ', '1                             ', '�ļ�MD5У���                 ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step_3              ', '�ļ���鴦�����              ', '2                             ', '�ܱ�����                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step_3              ', '�ļ���鴦�����              ', '3                             ', '�ܽ���                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_send_step_3              ', '�ļ���鴦�����              ', '9                             ', '������                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_ascii                    ', 'ASCII��                       ', '22                            ', '[22]SYN(��תͬ��)             ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_lc_bdsx                  ', '���̲���˳���Ӧ              ', '5                             ', 'sjth                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_lc_bdsx                  ', '���̲���˳���Ӧ              ', '3                             ', 'sjsh                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_lc_bdsx                  ', '���̲���˳���Ӧ              ', '2                             ', 'sjrk                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_lc_bdsx                  ', '���̲���˳���Ӧ              ', '6                             ', 'sjhp                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_lc_bdsx                  ', '���̲���˳���Ӧ              ', '1                             ', 'hqsj                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_fgfsx               ', '�ָ������                    ', '0                             ', '����β�ָ��                  ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_fgfsx               ', '�ָ������                    ', '1                             ', 'ȥ��β�ָ��                  ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_fgfsx               ', '�ָ������                    ', '2                             ', '����                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_taskmode                 ', '����ʼ��ʽ                  ', '1                             ', '����                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_dqfs                ', '���뷽ʽ                      ', 'L                             ', '�����                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_dqfs                ', '���뷽ʽ                      ', 'R                             ', '�Ҷ���                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_blx                      ', '������                        ', '1                             ', 'ҵ���                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_blx                      ', '������                        ', '2                             ', 'ģ���                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_tjgxbz                   ', '�ύ���±�־                  ', '2                             ', '��������                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_xym_zhbz                 ', '��Ӧ��ת����־                ', '0                             ', 'ת��                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_fmt                 ', '�ļ���ʽ                      ', '04                            ', '���ܣ�����ϸ������            ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_file_wzbz                ', '�����ļ�λ�ñ�־              ', '4                             ', '���һ��                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_taskmode                 ', '����ʼ��ʽ                  ', '2                             ', '�ֶ�                          ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_wbwj_shbz                ', '��˱�־                      ', '2                             ', '���ʧ��                      ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_xym_zhbz                 ', '��Ӧ��ת����־                ', '1                             ', '��ת��                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('batch_plrw_bdzt               ', '����״̬                      ', 'C                             ', '�ѳ���                        ', 'V2.1.bots ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_plywmx_his               ', '���ݱ�ѡ��                    ', '0                             ', '��ǰ��                        ', 'V2.1.bots ', '                              ');
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('bots_plywmx_his               ', '���ݱ�ѡ��                    ', '1                             ', '��ʷ��                        ', 'V2.1.bots ', '                              ');


INSERT INTO T_SEND_SERVER(ID, SERNAME, IP, PORT, TYPEID, CSTIME)
  VALUES('botsFile                      ', '�����ļ�����                                      ', '192.168.53.66       ', 33344, '1', 60);
INSERT INTO T_SEND_SERVER(ID, SERNAME, IP, PORT, TYPEID, CSTIME)
  VALUES('botsXml                       ', '�������ķ���                                      ', '192.168.53.66       ', 13008, '0', 30);
