package com.mapreduce.sort;

import java.util.Arrays;

public class StudentMain {
	public static void main(String[] args) {
		Student s1 = new Student();
		Student s2 = new Student();
		Student s3 = new Student();
		
		s1.setStuID(1);
		s1.setStuName("小大");
		s1.setStuAge(18);
		
		s2.setStuID(2);
		s2.setStuName("小红");
		s2.setStuAge(17);
		
		s3.setStuID(3);
		s3.setStuName("小小");
		s3.setStuAge(16);
		
		Object[] objs = {s1,s2,s3};
		
		Arrays.sort(objs);
		
		for(Object obj:objs) {
			System.out.println(obj);
		}
	}
}
