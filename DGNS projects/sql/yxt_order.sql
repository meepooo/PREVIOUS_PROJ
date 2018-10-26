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
comment on column yxt_order.SOURCE_TYPE       is'渠道类型' ;   
comment on column yxt_order.BRANCH_ID         is'发送方机构 ' ; 
comment on column yxt_order.ORDER_NO          is'订单号  ' ;  
comment on column yxt_order.ZWRQ              is'账务日期 ' ;  
comment on column yxt_order.TRANTIME          is'交易时间 ' ;  
comment on column yxt_order.ZHQZLSH           is'GAPS流水号' ;
comment on column yxt_order.BUSS_SEQ_NO       is'业务流水号 ' ; 
comment on column yxt_order.CONSUMER_SEQ_NO   is'前置流水号  ' ;
comment on column yxt_order.ESB_SEQ_NO        is'ESB流水号 ' ;
comment on column yxt_order.ZJLSH             is'主机流水号 ' ; 
comment on column yxt_order.CLIENT_NO         is'客户号  ' ;  
comment on column yxt_order.CLIENT_TEL        is'客户手机号码 ' ;
comment on column yxt_order.SMS_TEL           is'短信手机号码 ' ;
comment on column yxt_order.PAY_TYPE          is'支付类型' ;   
comment on column yxt_order.PAY_STATE         is'支付状态 ' ;  
comment on column yxt_order.ACCT_NO           is'账号   ' ;  
comment on column yxt_order.SELL_AMT          is'实付金额 ' ;  
comment on column yxt_order.ACT_PAY_AMT       is'应付金额  ' ; 
comment on column yxt_order.FACE_AMT          is'票面金额  ' ; 
comment on column yxt_order.SHOW_CODE         is'排期编号  ' ; 
comment on column yxt_order.SEAT_LIST         is'座位列表  ' ; 
comment on column yxt_order.CINEMA_ID         is'影院ID   ' ;
comment on column yxt_order.CINEMA_NAME       is'影院名称 ' ;  
comment on column yxt_order.HALL_CODE         is'影厅编码 ' ;  
comment on column yxt_order.HALL_NAME         is'影厅名称 ' ;  
comment on column yxt_order.FILM_ID           is'影片ID   ' ;
comment on column yxt_order.FILM_NAME         is'影片名称 ' ;  
comment on column yxt_order.FILM_TYPE         is'影片类型 ' ;  
comment on column yxt_order.IMAGE_URL_ADDRESS is'海报URL地址' ;
comment on column yxt_order.FILM_LANGUAGE     is'影片语言   ' ;
comment on column yxt_order.SHOW_DATE         is'上映日期   ' ;
comment on column yxt_order.SHOW_TIME         is'放映时间   ' ;
comment on column yxt_order.FILM_BILL_NUM     is'影票数量   ' ;
comment on column yxt_order.ORDER_STATUS      is'订单状态   ' ;
comment on column yxt_order.ORDER_STATUS_NAME is'订单状态说明' ; 
comment on column yxt_order.COMMISSION        is'手续费    ' ;
comment on column yxt_order.COUPON_NUM        is'优惠券张数' ;  
comment on column yxt_order.FILM_COIN_NUM     is'影币数量  ' ; 
comment on column yxt_order.AVAIL_COUPON_NUM  is'可用券张数' ;  
comment on column yxt_order.TAKE_BILL_NO      is'取票号    ' ;
comment on column yxt_order.TWO_DIM_CODE      is'二维码信息' ;  
comment on column yxt_order.SUPPLIER_NAME     is'供应商名称' ;  
comment on column yxt_order.SUPPLIER_ID       is'供应商代码' ;  
comment on column yxt_order.GOODS_NAME        is'商品名称  ' ; 
comment on column yxt_order.GOODS_NUM         is'商品数量  ' ; 
comment on column yxt_order.UNIT_PRICE        is'单价     ' ;
comment on column yxt_order.RELATE_GOODS_FLAG is'关联商品标志' ; 
comment on column yxt_order.GROUP_FLAG        is'团购标志   ' ;
comment on column yxt_order.DISCOUNT_MSG      is'优惠说明   ' ;
comment on column yxt_order.up_zhqzlsh        is'更新流水   ' ;
comment on column yxt_order.up_time           is'更新时间   ' ;

