package com.heima.javabase;

public class ArrayTest {
	public static void reverse(int[] a) {
		int[] b = a.clone();
		for (int i = 0; i < a.length; i++) {
			a[i] = b[a.length - i - 1];

		}
	}

	public static void main(String[] args) {
		int[] a = { 1, 23, 0 };
		reverse(a);
		for (int i = 0; i < a.length; i++)
			System.out.println(a[i]);
	}
}
