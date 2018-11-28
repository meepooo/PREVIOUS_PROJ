package com.heima.javabase;

import java.util.Random;
import java.util.Scanner;

/*
 * 随机数示例
 * @author: 程琪
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
		System.out.println("\n开始:");
		while (true) {
			Scanner sc = new Scanner(System.in);
			System.out.println("猜一猜:");
			int guessNum = sc.nextInt();
			
			if (guessNum == number)
			{
				System.out.println("恭喜猜对！");
				sc.close();
				break;
			}
		}
	}
}
