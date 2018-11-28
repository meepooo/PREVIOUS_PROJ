package com.heima.javabase;

public class ArrayDemo4 {
	public static void main(String[] args) {
		int[][] a = { { 10, 100, 1000 }, { 2, 4, 6 } };

		for (int i = 0; i < a.length; i++)
			for (int j = 0; j < a[i].length; j++)
				System.out.println(a[i][j]);
	}
}
