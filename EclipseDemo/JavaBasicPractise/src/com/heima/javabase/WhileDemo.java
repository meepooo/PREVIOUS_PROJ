package com.heima.javabase;

public class WhileDemo {
	public static void main(String[] args) {

		String[] str= {"hello", "World", "!!!"};
		int i=0;
		while(i<3) {
			System.out.println(str[i++]);
		}
	}
}
