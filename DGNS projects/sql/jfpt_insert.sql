/**
˵��
kztj1��DEFAULT1-�ɷ���Ĭ��������
       DEFAULT2-�̻�Ĭ��������
kztj1��1-���п�
       2-���п�
**/
insert into app_xlkz(pkey,curr_value,pinc,min_value,max_value,remark,whjg,whgy,whsj)/**��ȷ���Ƿ������ã������������������**/
values('K_DWBH','100001','1','100001','999999','��λ���','00000','admin',to_char(current timestamp,'yyyymmddhh24miss'));

insert into app_yyxx(yybs,yymc,yysm,yyfbrq,yybbh,yykfjl,yyzbjl,yyzt)
values('400','jfpt','�ɷ�ƽ̨',to_char(current date,'yyyymmdd'),'0.0.0.1','sunpengjun','sunpengjun','0');

insert into app_cpxx(cpdm,cpmc,yybs,zbjg,ywrqlx,qdkzbz,jgkzcs,sxfbz,sfqybz,qyms,xyxljz,kkfs,jzsx,dzms,lsblts,pdblts,jyfs,rzms,whjg,whgy,whsj,cpzt,sxftkbz)
values('4001000','����ѧ�ӷ�','400','00000','1','1','0','0','0','2','K_DWBH','1','0','1',0,0,'1','1','00000','admin',to_char(current timestamp,'yyyymmddhh24miss'),'0','0');

insert into app_sxffl(flbs,xh,fdbz,nwkbz,sxxkz,sxje,xxje,jslx,jscs,kjbz,kjcs,sm,whjg,whgy,whsj)
values('JFPT_MRFL_S','1','0','0','1',0.00,0.00,'1',0.000000,'0',0.000000,'�ͻ�Ĭ���շѷ���','00000','admin',to_char(current timestamp,'yyyymmddhh24miss'));
insert into app_sxffl(flbs,xh,fdbz,nwkbz,sxxkz,sxje,xxje,jslx,jscs,kjbz,kjcs,sm,whjg,whgy,whsj)
values('JFPT_MRFL_G','1','0','0','1',0.00,0.00,'1',0.000000,'0',0.000000,'�̻�Ĭ���շѷ���','00000','admin',to_char(current timestamp,'yyyymmddhh24miss'));


insert into agent_csys(lb,srcs,sccs,ms)values('MERCHANT','TRADER_CODE','010020160119170814','�м�ҵ����֧�����ص��̻���');
insert into agent_csys(lb,srcs,sccs,ms)values('ZHXX','DSZH','120010190010017087','һ����');
insert into agent_csys(lb,srcs,sccs,ms)values('CARD_TYPE','940062','00','00-ũ���н�ǿ�');
insert into agent_csys(lb,srcs,sccs,ms)values('CARD_TYPE','622328','00','00-ũ���н�ǿ�');
insert into agent_csys(lb,srcs,sccs,ms)values('CARD_TYPE','623038','00','00-ũ���н�ǿ�');
insert into agent_csys(lb,srcs,sccs,ms)values('CARD_TYPE','625288','01','01-ũ���д��ǿ�');
insert into agent_csys(lb,srcs,sccs,ms)values('CARD_TYPE','625888','01','01-ũ���д��ǿ�');
insert into agent_csys(lb,srcs,sccs,ms)values('CARD_TYPE','623198','02','02-�����������н�ǿ�');
insert into agent_csys(lb,srcs,sccs,ms)values('ISREMOTE','4001000','0','�Ƿ��ϵ����� 0:�� 1:��');
insert into agent_csys(lb,srcs,sccs,ms)values('THIRD_REFUND','4001000','0','�Ƿ��ϵ������˿� 0:�� 1:��');
insert into agent_csys(lb,srcs,sccs,ms)values('THIRD_CHECK','4001000','0','�Ƿ��ϵ��������� 0:�� 1:��');
insert into agent_csys(lb,srcs,sccs,ms)values('MERCHANT','CLINET_NO','2000936391','�м�ҵ����֧�����صĿͻ���');
insert into agent_csys(lb,srcs,sccs,ms)values('MERCHANT','FTP_IP','10.8.6.30','֧�����ض����ļ���������ַ');
insert into agent_csys(lb,srcs,sccs,ms)values('MERCHANT','FTP_USER','epayusr','֧�����ض����ļ��������û���');
insert into agent_csys(lb,srcs,sccs,ms)values('MERCHANT','FTP_PWD','123456','֧�����ض����ļ�����������');
insert into agent_csys(lb,srcs,sccs,ms)values('MERCHANT','FTP_PATH','/home/epayusr/file','֧�����ض����ļ�·��');

insert into APP_JYXX values('920004','�ɷ�ƽ̨����Ķ���ϸ','400','0','1','1','1','0','00000','admin','','','','0');
insert into APP_JYXX values('920009','�ɷ�ƽ̨��֧�����ض���ϸ','400','0','1','1','1','0','00000','admin','','','','0');
insert into APP_JYXX values('920305','�ɷ�ƽ̨(ֱ�ӽɷ�)','400','0','0','0','0','0','00000','admin','','','','0');

insert into app_qdxx values('211','�ֽ����','�ֽ����','1','','','0','0','00000','admin','20160520025257','','','0');
insert into app_qdxx values('212','��ݸũ������վ','��ݸũ������վ','1','','','0','0','00000','admin','','','','0');

insert into app_txaqxx values(
'jfpt','�ɷ�ƽ̨','1','400100010000000','1','1','','',60,60,'','','','','','','','','','','','','','','00000','admin',to_char(sysdate,'yyyymmddhh24miss'),'','','0','');
