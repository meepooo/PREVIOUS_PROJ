package com.basic;

import java.util.Random;
import java.util.Scanner;

public class RandomDemo {
	public static void main(String[] args) {
		String[] stu = new String[5];
		addStudent(stu);
		Random r = new Random();
		for(int i=0;i<stu.length;i++) {
			int id = r.nextInt(5);
			System.out.println("Ëæ»úÊý:" + id + ",ÐÕÃû:" + stu[id]);
		}
	}

	public static void addStudent(String[] stu) {
		Scanner sc = new Scanner(System.in);

		for (int i = 0; i < stu.length; i++) {
			stu[i] = sc.nextLine();
		}

		sc.close();
	}
}
