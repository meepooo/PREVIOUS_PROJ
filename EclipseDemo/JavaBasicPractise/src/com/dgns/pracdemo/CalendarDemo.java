package com.dgns.pracdemo;

import java.util.Calendar;

public class CalendarDemo {
public static void main(String[] args) {
	Calendar c = Calendar.getInstance();
	
	System.out.println(c);
	System.out.println(c.getTime());
	System.out.println(c.get(Calendar.YEAR) +"��"+ c.get(Calendar.MONTH) +"��"+ c.get(Calendar.DAY_OF_MONTH) + "��");
	
	c.add(Calendar.MONTH,3);
	System.out.println(c.get(Calendar.YEAR) +"��"+ c.get(Calendar.MONTH) +"��"+ c.get(Calendar.DAY_OF_MONTH) + "��");
	System.out.println(c.getTimeZone());
}
}
