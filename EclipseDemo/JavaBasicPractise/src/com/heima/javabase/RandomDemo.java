package com.heima.javabase;

import java.util.Random;
import java.util.Scanner;

/*
 * �����ʾ��
 * @author: ����
 */

public class RandomDemo {
	public static void main(String[] args) {
		Random r = new Random();
		int number = 0;
		System.out.println("hello world");
		for (int i = 0; i < 10; i++) {
			number = r.nextInt(10);
			System.out.print(number + " ");
		}

		number = r.nextInt(10);

		//number =5;
		System.out.println("\n��ʼ:");
		while (true) {
			Scanner sc = new Scanner(System.in);
			System.out.println("��һ��:");
			int guessNum = sc.nextInt();
			
			if (guessNum == number)
			{
				System.out.println("��ϲ�¶ԣ�");
				sc.close();
				break;
			}
		}
	}
}
