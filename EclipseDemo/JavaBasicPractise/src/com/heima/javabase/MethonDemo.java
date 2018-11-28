package com.heima.javabase;

public class MethonDemo {

	public static int sum(int a, int b) {
		return a+b;
	}
	
	public static void print(int[] a) {
		for(int i=0;i<a.length;i++)
		{
			System.out.println("a["+i+"]: "+a[i]);
		}
	}
	
	public static void main(String[] args) {
		int a=1;
		int b=2;
		int c=3;
		
		System.out.println(sum(1,2));

		System.out.println(a);
		System.out.println(b);
		System.out.println(c);
		
		int[] arr= {1,2,3,4,5,8888,222};
		print(arr);
	}
}
