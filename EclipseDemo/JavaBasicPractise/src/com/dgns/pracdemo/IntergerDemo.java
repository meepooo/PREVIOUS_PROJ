package com.dgns.pracdemo;

public class IntergerDemo {
public static void main(String[] args) {
		Integer i = new Integer("10");
		System.out.println(i);
		
		System.out.println(i.intValue());
		
		System.out.println(i.parseInt("100"));
		
		int b = Integer.parseInt("200");
		System.out.println(b);
		
		String s = i.toString();
		System.out.println(s);
		
		System.out.println(Integer.toString(40));
		
		String str = "ab324b";
		System.out.println(str.matches("[a-zA-Z_0-9][a-z].[0-9][0-9][a-z]"));
	}
}
