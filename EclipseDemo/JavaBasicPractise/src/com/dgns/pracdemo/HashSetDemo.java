package com.dgns.pracdemo;

import java.util.HashSet;

public class HashSetDemo {
	public static void main(String[] args) {
		/* 
		 * simple HashSet test
		 * HashCode() 不相同表示不相同的元素
		 * HashCode() 相同，再调用equals方法进行判定
		 * 如果沒有重写equals方法则默认不相等
		 */
		if(1==0)
		{
			HashSet<String> hs = new HashSet<String>();
			String str1 = "I ";
			String str2 = "Love ";
			String str3 = "Beijing!";
			String str4 = "Love ";

			hs.add(str1);
			hs.add(str2);
			hs.add(str3);
			hs.add(str4);

			for (String str : hs) {
				System.out.println(str + str.hashCode());
			}
		}
		/*
		 * 一个稍微复杂一点的例子
		 * 重写了equals方法
		 */
		if(1==0)
		{
			HashSet<Student> hs = new HashSet<Student>();
			
			Student stu1 = new Student(18,"哈哈");
			Student stu2 = new Student(19,"哈哈");
			Student stu3 = new Student(18,"呵呵");
			Student stu4 = new Student(18,"哈哈");
			
			hs.add(stu1);
			hs.add(stu4);
			hs.add(stu3);
			hs.add(stu2);
			
			for ( Student stu : hs){
				System.out.println(stu);
			}
		}
		/*
		 * 尝试优化HashSet的判定相等机制
		 * HashCode返回与对象内部属性,这样HashCode能区分不同的数据对象
		 * HashCode不一致，再按照equals方式判定数据是否相同
		 */
//		if(1==0)
		{
			HashSet<People> hs = new HashSet<People>();
			
			People p1 = new People(18,"张三");
			People p2 = new People(19,"李四");
			People p3 = new People(18,"王五");
			People p4 = new People(18,"张三");
			
			hs.add(p1);
			hs.add(p2);
			hs.add(p3);
			hs.add(p4);
			
			for ( People p : hs){
				System.out.println(p);
			}
		}
	}
}

class Student {
	private int age;
	private String name;

	public Student(int age, String name) {
		this.age = age;
		this.name = name;
	}

	@Override
	public String toString() {
		return name +":"+ age;
	}

	@Override
	public boolean equals(Object obj) {
		Student s = (Student) obj;
		if (this.age != s.age)
			return false;
		else if (!this.name.equals(s.name))
			return false;
		else
			return true;
	}
	
	@Override
	public int hashCode(){
		return 1;
	}
}

class People{
	int age;
	String name;
	
	public People(int age, String name){
		this.age = age;
		this.name = name;
	}
	
	@Override
	public String toString(){
		return name + ":" + age;
	}
	
	@Override
	public int hashCode(){
		//非法输入都存一个hashCode
		if (age==0 || name==null)
			return 0;
		
		final int prime = 31;
		
		return prime+age+name.hashCode();
	}
	
	@Override
	public boolean equals(Object obj){
		if (this==obj)
			return true;
		if (obj==null)
			return false;
		if (getClass()!=obj.getClass())
			return true;
		
		People p = (People) obj;
		
		if(age!=p.age)
			return false;
		
		if(!name.equals(p.name))
			return false;
		
		return true;
	}
}