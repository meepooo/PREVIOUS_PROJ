package com.annotation;

import java.lang.reflect.Method;

public class TestMain {

	public static void main(String[] args) {
		@SuppressWarnings({ "unused", "deprecation" })
		TestDemo testDemo = new TestDemo();
		
		try {
			Class<?> anno = Class.forName("com.annotation.TestDemo");
			Method[] methods = anno.getMethods();
			
			for(Method e:methods) {
				if (e.isAnnotationPresent(AnnotationDemo.class)) {
					AnnotationDemo annotation = e.getAnnotation(AnnotationDemo.class);
					String value = annotation.value();
					System.out.println(value);
				}
			}
			
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		}
	}

}
