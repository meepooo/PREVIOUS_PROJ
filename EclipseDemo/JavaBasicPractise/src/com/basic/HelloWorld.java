package com.basic;

import java.util.ArrayList;

public class HelloWorld {
	public static void main(String[] args) {
		System.out.println("HelloWorld");
		
		ArrayList<Double> arr=new ArrayList<Double>();
		arr.add(1.0);
		arr.add(2.0);
		arr.add(3.0);
		System.out.println(arr.get(0)+","+arr.get(1)+","+arr.get(2));
		arr.remove(1);
		System.out.println(arr.get(0)+","+arr.get(1)+",");
		
		String str = "hello world";
		char[] buf;
		buf = str.toCharArray();
		System.out.println(buf);
		
//		String str2;
//		str2 = buf.toString();
//		System.out.println(str2);
		
		String str1 = String.valueOf(buf);
		System.out.println(str1);
		
	}
}
