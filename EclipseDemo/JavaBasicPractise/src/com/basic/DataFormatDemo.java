package com.basic;

import java.text.DateFormat;
import java.text.ParseException;
import java.util.Date;

public class DataFormatDemo {
	public static void main(String[] args) throws ParseException {
		DateFormat d = DateFormat.getInstance();
		Date date = new Date();
		System.out.println(d.format(date));
		System.out.println(d.parse("18-12-5 обнГ9:10"));
		System.out.println(d.getCalendar().getTime());
	}
}
