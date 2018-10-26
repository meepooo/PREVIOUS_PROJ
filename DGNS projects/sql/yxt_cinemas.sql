create table yxt_cinemas
(
	cinemaId char(20) not null primary key,
	cinemaName char(128),
	spCode char(10), 
	cityid char(6) not null,
	countyCode char(6),
	countyName char(40),
	longitude char(11),
	latitude char(11),
	address varchar(128),
	imgurl   varchar(300)
)IN GAPS_DATA INDEX IN GAPS_INDEX ;
