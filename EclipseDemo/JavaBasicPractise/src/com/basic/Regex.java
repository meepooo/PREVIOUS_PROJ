package com.basic;

import java.util.Scanner;

/*
 * 验证QQ号合法性
 */
public class Regex {
	public static void main(String[] args) {
//		System.out.println("请输入QQ号码：");
//		String Qq = new Scanner(System.in).nextLine();
//		checkQQ(Qq);
		
		System.out.println("请输入E-mail：");
		String Email = new Scanner(System.in).nextLine();
		checkEmail(Email);
		
//		System.out.println("请输入手机号：");
//		String phone = new Scanner(System.in).nextLine();
//		checkPhone(phone);
	}

	public static void checkQQ(String str) {
		String regex = "[1-9]\\d{5,11}";
		if (str.matches(regex))
			System.out.println("QQ号码:【"+str+"】合法");
		else
			System.out.println("QQ号码:【"+str+"】不合法");
	}
	
	public static void checkEmail(String str) {
		String regex = "([1-9a-zA-Z_-])+@([1-9a-zA-Z.])+[.](\\w{2,3})";
		if (str.matches(regex))
			System.out.println("Email:【"+str+"】合法");
		else
			System.out.println("Email:【"+str+"】不合法");
	}
	
	public static void checkPhone(String str) {
		String regex = "1[3-9]\\d{9}";
		if (str.matches(regex))
			System.out.println("手机号:【"+str+"】合法");
		else
			System.out.println("手机号:【"+str+"】不合法");
	}
}
