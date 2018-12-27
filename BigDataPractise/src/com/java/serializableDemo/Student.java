package com.java.serializableDemo;

import java.io.Serializable;

public class Student implements Serializable {
	private String name;
	private int age;

	Student(String name, int age) {
		this.name = name;
		this.age = age;
	}
}
