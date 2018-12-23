package com.advance;

import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

public class ReflectDemo {
	public static void main(String[] args) throws NoSuchMethodException, SecurityException, InstantiationException, IllegalAccessException, IllegalArgumentException, InvocationTargetException, NoSuchFieldException {
		//反射的基本使用方式，但不使用
		StudentTest stu = new StudentTest();
		Class cla = stu.getClass();
		
		//使用下面这种		
		try {
			// step1 通过反射获取运行时对象
			Class cla1 = Class.forName("com.advance.StudentTest");
			System.out.println(cla1.getName());
			
			// step2获得构造函数
			Constructor[] constructor = cla1.getConstructors();
			for(Constructor c:constructor) {
				System.out.println("getConstructors:"+c);
			}
			
			Constructor[] constructor1 = cla1.getDeclaredConstructors();
			for(Constructor c:constructor1) {
				System.out.println("getDeclaredConstructors:"+c);
			}
			// step3通过构造函数实例化对象
			Constructor constructor2 = cla1.getDeclaredConstructor(java.lang.String.class,int.class,java.lang.String.class);
			constructor2.setAccessible(true);
			// 对象始祖类调用
			Object obj = constructor2.newInstance("李雷",18,"男");
			System.out.println(obj);
			
			// 调用成员
			Field[] fields = cla1.getDeclaredFields();
			for(Field field:fields) {
				System.out.println(field);
			}
			
			Field field = cla1.getDeclaredField("name");
			field.setAccessible(true);
			field.set(obj, "韩梅梅");
			System.out.println(obj);
			
			// 调用方法
			Method[] methods = cla1.getMethods();
			for(Method m:methods) {
				System.out.println("方法:"+m);
			}
			
			Method method = cla1.getMethod("toString", null);
			System.out.println(method.invoke(obj, null));
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}
}
