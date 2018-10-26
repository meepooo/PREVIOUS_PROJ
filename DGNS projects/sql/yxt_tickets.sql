create table yxt_tickets
(
        zwrq char(8) not null,
        order_no char(52) not null,
        film_ticket_id char(50) not null,
        seat_id char(50)not null,
        seat_col char(3) not null,
        seat_row char(3)not null,
        section_id char(8)not null
) IN GAPS_DATA INDEX IN GAPS_INDEX ;
