package com.heima.classa;

public class SubStrDemo {
	public static void main(String[] args) {
		String str1 = "hello,11\"DF,Dd\"f,dfdER,ERER1,12\"222,2222";
//		String substr = str1.substring(5);
//		substr = str1.substring(1, 3);
//		System.out.println(substr);

//		(str1.charAt(0) + "").toUpperCase();
//		str1.substring(1).toLowerCase();
//
//		System.out.println( str1.substring(0,1).toUpperCase() + str1.substring(1).toLowerCase() );
//		
//		System.out.println( (str1.charAt(0) + "").toUpperCase() + str1.substring(1).toLowerCase() );
//		
//		int[] a = new int[3];
//		a[0] = 1;
//		a[1] = 2;
//		a[2] = 3;
		
//		String[] str = new String[3];
//		str[0] = "hello";
//		str[1] = "world";
//		str[2] = "ÄãºÃ";
		
//		String[] str = str1.split("11");
		String[] str = str1.split("\"");
		System.out.println(str.length);
		System.out.println(str[0]);
		System.out.println(str[1]);
		System.out.println(str[2]);
	}
}
