package com.basic;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;

public class SimpleDateFormatDemo {
public static void main(String[] args) throws ParseException {
	//日期输出格式化
	SimpleDateFormat sdf = new SimpleDateFormat("yyyy年MM月dd日 hh:mm:ss");
	Date date = new Date();
	String s = sdf.format(date);
	System.out.println(s);
	
	//日期运算方式
	Date d = sdf.parse(s);
	System.out.println(sdf.format(d));
	long lTime = d.getTime() + 1000*60*60*24*10 ;
	d.setTime(lTime);
	System.out.println(sdf.format(d));
}
}
