--������ʱ��֤ͳһ��ͼ
--ϵͳ���,ҵ��������,ҵ������,ҵ����ˮ��,����״̬
drop view sfck_timeout;
create view sfck_timeout (xtbh,ywbm,ywsqbh,ywrq,ywlsh,qqdzt) as 
    select 'gabdxzp','gab_dxzp_xdxx',ywsqbh,ywrq,ywlsh,qqdzt from gab_dxzp_xdxx where qqdzt in ('23','33')
    ;