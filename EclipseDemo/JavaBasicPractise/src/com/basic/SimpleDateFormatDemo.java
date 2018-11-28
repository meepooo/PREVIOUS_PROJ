package com.basic;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;

public class SimpleDateFormatDemo {
public static void main(String[] args) throws ParseException {
	//���������ʽ��
	SimpleDateFormat sdf = new SimpleDateFormat("yyyy��MM��dd�� hh:mm:ss");
	Date date = new Date();
	String s = sdf.format(date);
	System.out.println(s);
	
	//�������㷽ʽ
	Date d = sdf.parse(s);
	System.out.println(sdf.format(d));
	long lTime = d.getTime() + 1000*60*60*24*10 ;
	d.setTime(lTime);
	System.out.println(sdf.format(d));
}
}
