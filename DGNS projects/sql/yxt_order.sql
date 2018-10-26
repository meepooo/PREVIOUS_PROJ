drop table yxt_order;
create table yxt_order
(
        SOURCE_TYPE char(10),
        BRANCH_ID char(20),
        ORDER_NO char(52)not null,
        zwrq char(8) not null,
        trantime char(14)not null,
        zhqzlsh integer not null,
        BUSS_SEQ_NO char(52)not null,
        CONSUMER_SEQ_NO char(52)not null,
        ESB_SEQ_NO char(52)not null,
        zjlsh char(32),
        client_no char(20) not null,
        client_tel char(30) not null,
        sms_tel char(30),
        pay_type char(10),
        PAY_STATE char(1),
        acct_no char(50),
        ACCT_NAME varchar(150),
        sell_amt decimal(10,2),
        act_pay_amt decimal(10,2),
        face_amt decimal(10,2),
        show_code char(20),
        seat_list char(50),
        cinema_id char(50),
        cinema_name varchar(150),
        hall_code char(50),
        hall_name varchar(150),
        film_id char(50),
        film_name char(100),
        film_type char(10),
        image_url_address varchar(300),
        film_language char(20),
        show_date char(8),
        show_time char(14),
        film_bill_num integer,
        order_status char(2),
        order_status_name char(10),
        commission decimal(20,2),
        coupon_num integer,
        film_coin_num char(20),
        avail_coupon_num integer,
        take_bill_no char(50),
        two_dim_code varchar(300),
        supplier_name varchar(150),
        supplier_id char(50),
        goods_name char(100),
        goods_num integer,
        unit_price decimal(20,4),
        relate_goods_flag char(10),
        group_flag char(10),
        discount_msg varchar(300),
        up_zhqzlsh integer not null,
        up_time char(14) not null
) IN GAPS_DATA INDEX IN GAPS_INDEX ;
ALTER TABLE yxt_order ADD CONSTRAINT PK_FA_SOILCHECK PRIMARY KEY (order_no);
comment on table  yxt_order  is 'yxt_order' ;
comment on column yxt_order.SOURCE_TYPE       is'��������' ;   
comment on column yxt_order.BRANCH_ID         is'���ͷ����� ' ; 
comment on column yxt_order.ORDER_NO          is'������  ' ;  
comment on column yxt_order.ZWRQ              is'�������� ' ;  
comment on column yxt_order.TRANTIME          is'����ʱ�� ' ;  
comment on column yxt_order.ZHQZLSH           is'GAPS��ˮ��' ;
comment on column yxt_order.BUSS_SEQ_NO       is'ҵ����ˮ�� ' ; 
comment on column yxt_order.CONSUMER_SEQ_NO   is'ǰ����ˮ��  ' ;
comment on column yxt_order.ESB_SEQ_NO        is'ESB��ˮ�� ' ;
comment on column yxt_order.ZJLSH             is'������ˮ�� ' ; 
comment on column yxt_order.CLIENT_NO         is'�ͻ���  ' ;  
comment on column yxt_order.CLIENT_TEL        is'�ͻ��ֻ����� ' ;
comment on column yxt_order.SMS_TEL           is'�����ֻ����� ' ;
comment on column yxt_order.PAY_TYPE          is'֧������' ;   
comment on column yxt_order.PAY_STATE         is'֧��״̬ ' ;  
comment on column yxt_order.ACCT_NO           is'�˺�   ' ;  
comment on column yxt_order.SELL_AMT          is'ʵ����� ' ;  
comment on column yxt_order.ACT_PAY_AMT       is'Ӧ�����  ' ; 
comment on column yxt_order.FACE_AMT          is'Ʊ����  ' ; 
comment on column yxt_order.SHOW_CODE         is'���ڱ��  ' ; 
comment on column yxt_order.SEAT_LIST         is'��λ�б�  ' ; 
comment on column yxt_order.CINEMA_ID         is'ӰԺID   ' ;
comment on column yxt_order.CINEMA_NAME       is'ӰԺ���� ' ;  
comment on column yxt_order.HALL_CODE         is'Ӱ������ ' ;  
comment on column yxt_order.HALL_NAME         is'Ӱ������ ' ;  
comment on column yxt_order.FILM_ID           is'ӰƬID   ' ;
comment on column yxt_order.FILM_NAME         is'ӰƬ���� ' ;  
comment on column yxt_order.FILM_TYPE         is'ӰƬ���� ' ;  
comment on column yxt_order.IMAGE_URL_ADDRESS is'����URL��ַ' ;
comment on column yxt_order.FILM_LANGUAGE     is'ӰƬ����   ' ;
comment on column yxt_order.SHOW_DATE         is'��ӳ����   ' ;
comment on column yxt_order.SHOW_TIME         is'��ӳʱ��   ' ;
comment on column yxt_order.FILM_BILL_NUM     is'ӰƱ����   ' ;
comment on column yxt_order.ORDER_STATUS      is'����״̬   ' ;
comment on column yxt_order.ORDER_STATUS_NAME is'����״̬˵��' ; 
comment on column yxt_order.COMMISSION        is'������    ' ;
comment on column yxt_order.COUPON_NUM        is'�Ż�ȯ����' ;  
comment on column yxt_order.FILM_COIN_NUM     is'Ӱ������  ' ; 
comment on column yxt_order.AVAIL_COUPON_NUM  is'����ȯ����' ;  
comment on column yxt_order.TAKE_BILL_NO      is'ȡƱ��    ' ;
comment on column yxt_order.TWO_DIM_CODE      is'��ά����Ϣ' ;  
comment on column yxt_order.SUPPLIER_NAME     is'��Ӧ������' ;  
comment on column yxt_order.SUPPLIER_ID       is'��Ӧ�̴���' ;  
comment on column yxt_order.GOODS_NAME        is'��Ʒ����  ' ; 
comment on column yxt_order.GOODS_NUM         is'��Ʒ����  ' ; 
comment on column yxt_order.UNIT_PRICE        is'����     ' ;
comment on column yxt_order.RELATE_GOODS_FLAG is'������Ʒ��־' ; 
comment on column yxt_order.GROUP_FLAG        is'�Ź���־   ' ;
comment on column yxt_order.DISCOUNT_MSG      is'�Ż�˵��   ' ;
comment on column yxt_order.up_zhqzlsh        is'������ˮ   ' ;
comment on column yxt_order.up_time           is'����ʱ��   ' ;

