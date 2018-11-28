package com.basic;

public class ObjectDemo {
	public static void main(String[] args) {
		Student s = new Student("ÀîÀ×", 18);

		System.out.println(s);
		System.out.println(s.toString());
	}
}

class Student extends Object {
	String name;
	int age;

	@Override
	public String toString() {
		return name + ":" + age;
	}

	Student(String name, int age) {
		this.name = name;
		this.age = age;
	}
}