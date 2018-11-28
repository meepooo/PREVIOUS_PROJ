package com.basic;

public class ExtentsClassDemo {
	public static void main(String[] args) {
		Dad1 d = new Dad1("father");
		Son1 s = new Son1("son");

		System.out.println(d.getName());
		System.out.println(s.getName());
	}
}

class Dad1 {
	private String name = null;
	public int age = 0;

	public String getName() {
		return name;
	}

	Dad1(String s) {
		name = s;
	}

	Dad1() {
		name = null;
	}
}

class Son1 extends Dad1 {

	@Override
	public String getName() {
		return super.getName();
	}

	Son1(String s) {
		super(s);
	}
}