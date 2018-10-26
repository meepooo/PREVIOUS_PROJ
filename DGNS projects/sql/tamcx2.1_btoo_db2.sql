delete from T_TRAN where version='V2.1.btoo';

delete from T_SUB_TRAN where version='V2.1.btoo';

delete from T_SEND_RETURN where version='V2.1.btoo';

delete from T_SEND_COND where version='V2.1.btoo';

delete from T_SENDINFO where version='V2.1.btoo';

delete from T_MENU where version='V2.1.btoo';

delete from T_DICT where version='V2.1.btoo';

delete from T_SEND_SERVER where id like 'btoo%';



INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('btooYwlx            ', '��ת��[ҵ������]              ', '1', 'com.hundsun.agent.web.btoo.ctl.BtooYwlxCtl                                                          ', 'V2.1.btoo ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('btooYwbh            ', '��ת��[ҵ����]              ', '1', 'com.hundsun.agent.web.btoo.ctl.BtooYwbhCtl                                                          ', 'V2.1.btoo ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('btooStepcfg         ', '��ת��[�����������]          ', '1', 'com.hundsun.agent.web.btoo.ctl.BtooStepcfgCtl                                                       ', 'V2.1.btoo ', NULL, NULL, NULL);
INSERT INTO T_TRAN(TRAN_CODE, TRAN_NAME, TRAN_TYPE, TRAN_CLASS, VERSION, BAK1, BAK2, BAK3)
  VALUES('btooZtsel           ', '��ת��״̬��ѯ                ', '1', 'com.hundsun.agent.web.btoo.ctl.BtooZtselCtl                                                         ', 'V2.1.btoo ', NULL, NULL, NULL);


INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('btooZtsel           ', 'list                ', '�������                      ', 'about:blank                                                                                         ', '�������                                          ', 'V2.1.btoo ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('btooZtsel           ', 'next                ', 'ִ������                      ', 'about:blank                                                                                         ', 'ִ������                                          ', 'V2.1.btoo ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('btooYwlx            ', 'upt                 ', '���¸���                      ', 'about:blank                                                                                         ', '��Ӹ���                                          ', 'V2.1.btoo ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('btooYwlx            ', 'del                 ', 'ɾ��                          ', 'about:blank                                                                                         ', 'ɾ��                                              ', 'V2.1.btoo ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('btooYwlx            ', 'add                 ', '��Ӹ���                      ', 'about:blank                                                                                         ', '��Ӹ���                                          ', 'V2.1.btoo ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('btooYwlx            ', 'list                ', '�������                      ', 'about:blank                                                                                         ', '�������                                          ', 'V2.1.btoo ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('btooYwlx            ', 'def                 ', '��ѯ                          ', 'app/agent/btoo/btooywlx.jsp                                                                         ', 'Ĭ��                                              ', 'V2.1.btoo ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('btooYwbh            ', 'def                 ', '��ѯ                          ', 'app/agent/btoo/btooywbh.jsp                                                                         ', 'Ĭ��                                              ', 'V2.1.btoo ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('btooYwbh            ', 'list                ', '�������                      ', 'about:blank                                                                                         ', '�������                                          ', 'V2.1.btoo ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('btooYwbh            ', 'add                 ', '��Ӹ���                      ', 'about:blank                                                                                         ', '��Ӹ���                                          ', 'V2.1.btoo ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('btooYwbh            ', 'del                 ', 'ɾ��                          ', 'about:blank                                                                                         ', 'ɾ��                                              ', 'V2.1.btoo ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('btooYwbh            ', 'upt                 ', '���¸���                      ', 'about:blank                                                                                         ', '��Ӹ���                                          ', 'V2.1.btoo ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('btooStepcfg         ', 'def                 ', '��ѯ                          ', 'app/agent/btoo/btoostepcfg.jsp                                                                      ', 'Ĭ��                                              ', 'V2.1.btoo ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('btooStepcfg         ', 'list                ', '�������                      ', 'about:blank                                                                                         ', '�������                                          ', 'V2.1.btoo ', '02                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('btooStepcfg         ', 'add                 ', '��Ӹ���                      ', 'about:blank                                                                                         ', '��Ӹ���                                          ', 'V2.1.btoo ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('btooStepcfg         ', 'del                 ', 'ɾ��                          ', 'about:blank                                                                                         ', 'ɾ��                                              ', 'V2.1.btoo ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('btooStepcfg         ', 'upt                 ', '���¸���                      ', 'about:blank                                                                                         ', '��Ӹ���                                          ', 'V2.1.btoo ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('btooZtsel           ', 'def                 ', 'Ĭ��                          ', 'app/agent/btoo/btooztsel.jsp                                                                        ', 'Ĭ��                                              ', 'V2.1.btoo ', '01                            ', NULL, NULL);
INSERT INTO T_SUB_TRAN(TRAN_CODE, SUB_TRAN_CODE, SUB_TRAN_NAME, REPAGE, SUB_TRAN_DESC, VERSION, BAK1, BAK2, BAK3)
  VALUES('btooYwbh            ', 'ywxxByYwbh          ', '��ȡҵ����Ϣ                  ', 'about:blank                                                                                         ', '��ȡҵ����Ϣ                                      ', 'V2.1.btoo ', NULL, NULL, NULL);


INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(302, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.btoo ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(302, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.btoo ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(302, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.btoo ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(302, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.btoo ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(301, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.btoo ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(301, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.btoo ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(301, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.btoo ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(301, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.btoo ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(303, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.btoo ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(303, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '0', NULL, 'V2.1.btoo ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(303, 'zhqzlsh             ', 'ƽ̨��ˮ��                    ', '1 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.btoo ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_RETURN(ID, RETURN_ID, RETURN_NAME, ORDER_ID, VALUE_TYPE, FILE_EXT, SUPER_PATH, RET_TYPE, DICT, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(303, 'zwrq                ', 'ƽ̨��������                  ', '2 ', '0', NULL, '/pub/               ', '1', NULL, 'V2.1.btoo ', NULL, '0                             ', NULL, NULL, NULL, NULL, NULL);


INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(301, 'qtywbh              ', '��ת��ҵ����                ', '5', '1 ', '1', NULL, NULL, 'com.hundsun.agent.web.btoo.sendUtil.BtooywbhSend                                                    ', 'V2.1.btoo ', '��ת��ҵ����                                                                                      ', '/btoo/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(301, 'qtbz                ', '��ͣ��־                      ', '0', '2 ', '1', NULL, NULL, 'agent_send_qtbz                                                                                     ', 'V2.1.btoo ', '��ͣ��־                                                                                            ', '/btoo/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(302, 'ywbh                ', 'ҵ����                      ', '5', '1 ', '1', NULL, NULL, 'com.hundsun.agent.web.btoo.sendUtil.BtooywbhSend                                                    ', 'V2.1.btoo ', 'ҵ����                                                                                            ', '/btoo/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(302, 'kkrq                ', '�ۿ�����                      ', '3', '2 ', '0', NULL, NULL, NULL, 'V2.1.btoo ', '�ۿ�����                                                                                            ', '/btoo/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(303, 'ywbh                ', 'ҵ����                      ', '5', '1 ', '1', NULL, NULL, 'com.hundsun.agent.web.btoo.sendUtil.BtooywbhSend                                                    ', 'V2.1.btoo ', 'ҵ����                                                                                            ', '/btoo/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(303, 'czbz                ', '������־                      ', '0', '4 ', '1', NULL, NULL, 'btoo_czbz                                                                                           ', 'V2.1.btoo ', '������־                                                                                            ', '/btoo/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(303, 'ptrq                ', '�ۿ�����                      ', '3', '2 ', '1', NULL, NULL, NULL, 'V2.1.btoo ', '�ۿ�����                                                                                            ', '/btoo/req/                    ', NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SEND_COND(ID, SEND_COND_ID, SEND_COND_NAME, SEND_COND_TYPE, ORDER_ID, IS_NULL, SEND_ON, SEND_DIV, COND_INFO, VERSION, NOTE, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(303, 'ptlsh               ', '�ۿ���ˮ��                    ', '1', '3 ', '1', NULL, NULL, NULL, 'V2.1.btoo ', '�ۿ���ˮ��                                                                                          ', '/btoo/req/                    ', NULL, NULL, NULL, NULL, NULL);


INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(303, '920903                        ', '��ת�������ж�/����/��ֹ                          ', '1', NULL, 'admin               ', '00000               ', '100                 ', 'V2.1.btoo ', NULL, 'btooXml                       ', 'btooFile                      ', NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(301, '920901                        ', '��ת��ҵ����ͣ                                    ', '1', '                    ', 'yd                  ', '00000               ', '100                 ', 'V2.1.btoo ', '', 'btooXml                       ', 'btooFile                      ', '                                                                                                                                                      ', '                                                                                                                                                      ', NULL, NULL, NULL, NULL);
INSERT INTO T_SENDINFO(ID, SEND_ID, SEND_NAME, SEND_TYPE, LSTSUPER, USERID, ORGID, INNERORGID, VERSION, NOTE, COMMUNICATE, DATASVR, BAK1, BAK2, BAK3, BAK4, BAK5, BAK6)
  VALUES(302, '920902                        ', '��ת��������                                    ', '1', NULL, 'admin               ', '00000               ', '100                 ', 'V2.1.btoo ', NULL, 'btooXml                       ', 'btooFile                      ', NULL, NULL, NULL, NULL, NULL, NULL);


INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('btoo                          ', '/                             ', 1, '��ת������                    ', '��ת������                                        ', '0', 'sendPz              ', '1', 'V2.1.btoo ', NULL, '900310000000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('btoo_yw                       ', 'btoo                          ', 2, 'ҵ������                      ', 'ҵ������                                          ', '0', 'sendPz              ', '1', 'V2.1.btoo ', NULL, '900311000000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('btoo_ywlx                     ', 'btoo_yw                       ', 3, 'ҵ����������                  ', 'ҵ����������                                      ', '1', 'btooYwlx            ', '0', 'V2.1.btoo ', NULL, '900311100000        ', '0', 'agent     ', '                              ', NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('btoo_ywbh                     ', 'btoo_yw                       ', 3, 'ҵ��������                  ', 'ҵ��������                                      ', '1', 'btooYwbh            ', '1', 'V2.1.btoo ', NULL, '900311300000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('btoo_stepcfg                  ', 'btoo_yw                       ', 3, '�����������                  ', '�����������                                      ', '1', 'btooStepcfg         ', '1', 'V2.1.btoo ', NULL, '900311200000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('btoo_ywgl                     ', 'btoo                          ', 2, 'ҵ�����                      ', 'ҵ�����                                          ', '0', 'sendPz              ', '1', 'V2.1.btoo ', NULL, '900312000000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('btoo_ywqt                     ', 'btoo_ywgl                     ', 3, 'ҵ����ͣ                      ', 'ҵ����ͣ                                          ', '1', 'send                ', '0', 'V2.1.btoo ', '                                        ', '900312100000        ', '0', 'agent     ', '                              ', 'send_id=301                                                                                         ', NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('btoo_pzlztsel                 ', 'btoo_ywgl                     ', 3, '״̬��ѯ                      ', '״̬��ѯ                                          ', '1', 'btooZtsel           ', '1', 'V2.1.btoo ', NULL, '900312200000        ', '0', 'agent     ', NULL, NULL, NULL);
INSERT INTO T_MENU(MENU_ID, ABOVE_MENU_ID, MENU_DEEP, MENU_NAME, MENU_DESC, IS_RUN_MENU, TRAN_CODE, IS_ENABLE, VERSION, REPORT_ID, ORDER_ID, MENU_TYPE, SYSTEM_ID, BAK1, BAK2, BAK3)
  VALUES('btoo_pzlrwfq                  ', 'btoo_ywgl                     ', 3, '������                      ', '������                                          ', '1', 'send                ', '1', 'V2.1.btoo ', NULL, '900312300000        ', '0', 'agent     ', NULL, 'send_id=302                                                                                         ', NULL);


INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('btoo_ywzt                     ', 'ҵ��״̬                      ', '0                             ', '��Ч                          ', 'V2.1.btoo ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('btoo_ywzt                     ', 'ҵ��״̬                      ', '1                             ', '��Ч                          ', 'V2.1.btoo ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('btoo_czbz                     ', '������־                      ', '1                             ', '��ֹ                          ', 'V2.1.btoo ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('btoo_czbz                     ', '������־                      ', '2                             ', '��ͣ                          ', 'V2.1.btoo ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('btoo_czbz                     ', '������־                      ', '3                             ', '����                          ', 'V2.1.btoo ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('btoo_kkzq                     ', '�ۿ�����                      ', '0                             ', '�����ڣ�ÿ�ζ��ۿ          ', 'V2.1.btoo ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('btoo_kkzq                     ', '�ۿ�����                      ', '3                             ', '��                            ', 'V2.1.btoo ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('btoo_kkzq                     ', '�ۿ�����                      ', '4                             ', '��                            ', 'V2.1.btoo ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('btoo_clfs                     ', '����ʽ                      ', '1                             ', '�ֹ�                          ', 'V2.1.btoo ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('btoo_clfs                     ', '����ʽ                      ', '2                             ', '��ʱ                          ', 'V2.1.btoo ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('btoo_stepType                 ', '��������                      ', '0                             ', 'Ĭ��                          ', 'V2.1.btoo ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('btoo_stepType                 ', '��������                      ', '1                             ', '�Զ���                        ', 'V2.1.btoo ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('btoo_svrType                  ', '��������                      ', '0                             ', '����                          ', 'V2.1.btoo ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('btoo_svrType                  ', '��������                      ', '1                             ', '����                          ', 'V2.1.btoo ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('btoo_qdbd                     ', '��������                      ', '0                             ', '����Ԥ����                    ', 'V2.1.btoo ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('btoo_qdbd                     ', '��������                      ', '1                             ', '���ݴ���                      ', 'V2.1.btoo ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('btoo_qdbd                     ', '��������                      ', '2                             ', '���ݺ���                    ', 'V2.1.btoo ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('btoo_ywyxbz                   ', 'ҵ�����б�־                  ', '0                             ', '����                          ', 'V2.1.btoo ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('btoo_ywyxbz                   ', 'ҵ�����б�־                  ', '1                             ', '��ֹ                          ', 'V2.1.btoo ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('btoo_ywyxbz                   ', 'ҵ�����б�־                  ', '2                             ', '��ͣ                          ', 'V2.1.btoo ', NULL);
INSERT INTO T_DICT(DICT_KIND, DICT_NAME, DICT_KEY, DICT_INFO, VERSION, BAK)
  VALUES('btoo_ywyxbz                   ', 'ҵ�����б�־                  ', '9                             ', '�ڴ�����                      ', 'V2.1.btoo ', NULL);


INSERT INTO T_SEND_SERVER(ID, SERNAME, IP, PORT, TYPEID, CSTIME)
  VALUES('btooXml                       ', 'btoo���ķ���                                      ', '192.168.53.66       ', 13009, '0', 30);
INSERT INTO T_SEND_SERVER(ID, SERNAME, IP, PORT, TYPEID, CSTIME)
  VALUES('btooFile                      ', 'btoo�ļ�����                                      ', '192.168.53.66       ', 33345, '1', 60);
