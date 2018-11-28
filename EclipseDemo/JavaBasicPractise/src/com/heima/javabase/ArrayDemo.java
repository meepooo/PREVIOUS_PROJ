package com.heima.javabase;

public class ArrayDemo {
	public static void main(String[] args) {
		int[] arr = new int[3];
		
		System.out.println(arr);
		System.out.println(arr[0]);
		System.out.println(arr[1]);
		System.out.println(arr[2]);
		
		arr[0] = 1;
		arr[1] = 2;
		arr[2] = 3;
		System.out.println(arr);
		System.out.println(arr[0]);
		System.out.println(arr[1]);
		System.out.println(arr[2]);
		
		int[] arr1= {1,2,3};
		System.out.println(arr1);
		System.out.println(arr1[0]);
		System.out.println(arr1[1]);
		System.out.println(arr1[2]);
	}
}
