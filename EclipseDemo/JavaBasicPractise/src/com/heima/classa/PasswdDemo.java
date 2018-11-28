package com.heima.classa;

import java.util.Scanner;

public class PasswdDemo {
	public static void main(String[] args) {
		//设定密码
		String passwd = "wangqs";
		
		//循环输入密码，并判断密码是否正确
		for (int i = 0; i < 3; i++) {
			
			//输入密码
			Scanner sc = new Scanner(System.in);
			
			//判断密码是否正确
			if (passwd.equals(sc.nextLine())) {
				System.out.println("输入正确");
				break;
			}

			//打印错误信息
			System.out.println("输入错误，还剩 " + (3 - i - 1) + " 次机会！");
			
			if (i == 2) {
				System.out.println("三次全部输入错误，退出！");
			}
		}

		//程序结束
		System.out.println("程序结束!");
	}
}
