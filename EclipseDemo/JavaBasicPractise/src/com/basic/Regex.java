package com.basic;

import java.util.Scanner;

/*
 * ��֤QQ�źϷ���
 */
public class Regex {
	public static void main(String[] args) {
//		System.out.println("������QQ���룺");
//		String Qq = new Scanner(System.in).nextLine();
//		checkQQ(Qq);
		
		System.out.println("������E-mail��");
		String Email = new Scanner(System.in).nextLine();
		checkEmail(Email);
		
//		System.out.println("�������ֻ��ţ�");
//		String phone = new Scanner(System.in).nextLine();
//		checkPhone(phone);
	}

	public static void checkQQ(String str) {
		String regex = "[1-9]\\d{5,11}";
		if (str.matches(regex))
			System.out.println("QQ����:��"+str+"���Ϸ�");
		else
			System.out.println("QQ����:��"+str+"�����Ϸ�");
	}
	
	public static void checkEmail(String str) {
		String regex = "([1-9a-zA-Z_-])+@([1-9a-zA-Z.])+[.](\\w{2,3})";
		if (str.matches(regex))
			System.out.println("Email:��"+str+"���Ϸ�");
		else
			System.out.println("Email:��"+str+"�����Ϸ�");
	}
	
	public static void checkPhone(String str) {
		String regex = "1[3-9]\\d{9}";
		if (str.matches(regex))
			System.out.println("�ֻ���:��"+str+"���Ϸ�");
		else
			System.out.println("�ֻ���:��"+str+"�����Ϸ�");
	}
}
