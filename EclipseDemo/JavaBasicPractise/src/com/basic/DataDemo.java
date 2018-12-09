package com.basic;

import java.util.Date;

public class DataDemo {
	public static void main(String[] args) {
		Date d = new Date();
		System.out.println(d);
		System.out.println(d.getTime());
		d.setTime(1000 * 60 * 60 * 24 * 2);
		System.out.println(d);
		System.out.println(d.getTime());
		System.out.println();
	}
}
