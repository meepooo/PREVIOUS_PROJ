package com.advance;

import org.junit.Test;


public class StudentTest {
	private String name;
	private int age;
	private String sex;
	
	
	public StudentTest(){
		
	}
	
	public StudentTest(String name, int age, String sex){
		this.name = name;
		this.age = age;
		this.sex = sex;
	}
	
	public String getName() {
		return name;
	}
	
	public int getAge() {
		return age;
	}
	
	@Override
	public String toString() {
		return name+age+sex;
		
	}
	
	@Test
	public void hello() {
		System.out.println("hello");
	}
}
