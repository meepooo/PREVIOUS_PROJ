package com.dgns.pracdemo;

import java.util.Calendar;

public class CalendarDemo {
public static void main(String[] args) {
	Calendar c = Calendar.getInstance();
	
	System.out.println(c);
	System.out.println(c.getTime());
	System.out.println(c.get(Calendar.YEAR) +"年"+ c.get(Calendar.MONTH) +"月"+ c.get(Calendar.DAY_OF_MONTH) + "日");
	
	c.add(Calendar.MONTH,3);
	System.out.println(c.get(Calendar.YEAR) +"年"+ c.get(Calendar.MONTH) +"月"+ c.get(Calendar.DAY_OF_MONTH) + "日");
	System.out.println(c.getTimeZone());
}
}
