package com.heima.javabase;

/*
 * @author: Lucky
 */
public class ArrayDemo2 {
	public static void main(String[] args) {
		int[] arr1;
		arr1 = new int[3];
		arr1[0] = 4;
		arr1[1] = 5;
		arr1[2] = 6;

		System.out.println(arr1);
		System.out.println(arr1[0]);
		System.out.println(arr1[1]);
		System.out.println(arr1[2]);
		int[] arr2 = arr1;
		System.out.println(arr2);
		System.out.println(arr2[0]);
		System.out.println(arr2[1]);
		System.out.println(arr2[2]);

		System.out.println("arr2共有 " + arr2.length + " 个元素");
		System.out.println(arr2.equals(arr1));
		System.out.println(arr2.getClass());
		System.out.println(arr2.toString());
		System.out.println(arr2.hashCode());

		int[] arr3 = arr2.clone();
		System.out.println(arr3);
		System.out.println(arr3.equals(arr2));
	}
}
