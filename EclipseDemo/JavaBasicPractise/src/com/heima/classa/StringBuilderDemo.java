package com.heima.classa;

public class StringBuilderDemo {
	public static void main(String[] args) {
		StringBuilder str = new StringBuilder();

		str.append("hello").append("world").append("ÄãºÃ").append("ÊÀ½çaaaaaaaaaaaaa");
		System.out.println(str);
		System.out.println(str.capacity());
		System.out.println(str.length());
		str.reverse();
		String st = str.toString();
		System.out.println(st);
		
		int[] a= {1,2,3};
//		str = null;
		str.delete(0,str.capacity());
		str.append(a[0]).append(a[1]).append(a[2]);
		System.out.println(str);
	}
}
