package com.heima.classa;

import java.util.Random;

public class RandomDemo {
	public static void main(String[] args) {
//		Scanner sc = new Scanner(System.in);
//		String s =new String();
//		int a = sc.nextInt();
//		s = sc.nextLine();
//		System.out.println(s);
//		s = sc.nextLine();
//		System.out.println(s);
		String s = "hellow";
		String s1 = "helloworld1111111111111";
		int[] a = new int[5];
		char[] ch = new char[16];

		ch = "hello1111".toCharArray();
		ch = s.toCharArray();
		int len=s.length();
		String s2 = "helloworld1111111111111";
		boolean b = s1.equals(s2);

		Random r = new Random();
		System.out.println(b);
		System.out.println(ch);
		System.out.println(len);
	}
}
