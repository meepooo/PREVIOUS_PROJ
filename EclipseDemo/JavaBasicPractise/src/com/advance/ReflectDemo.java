package com.advance;

import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

public class ReflectDemo {
	public static void main(String[] args) throws NoSuchMethodException, SecurityException, InstantiationException, IllegalAccessException, IllegalArgumentException, InvocationTargetException, NoSuchFieldException {
		//����Ļ���ʹ�÷�ʽ������ʹ��
		StudentTest stu = new StudentTest();
		Class cla = stu.getClass();
		
		//ʹ����������		
		try {
			// step1 ͨ�������ȡ����ʱ����
			Class cla1 = Class.forName("com.advance.StudentTest");
			System.out.println(cla1.getName());
			
			// step2��ù��캯��
			Constructor[] constructor = cla1.getConstructors();
			for(Constructor c:constructor) {
				System.out.println("getConstructors:"+c);
			}
			
			Constructor[] constructor1 = cla1.getDeclaredConstructors();
			for(Constructor c:constructor1) {
				System.out.println("getDeclaredConstructors:"+c);
			}
			// step3ͨ�����캯��ʵ��������
			Constructor constructor2 = cla1.getDeclaredConstructor(java.lang.String.class,int.class,java.lang.String.class);
			constructor2.setAccessible(true);
			// ����ʼ�������
			Object obj = constructor2.newInstance("����",18,"��");
			System.out.println(obj);
			
			// ���ó�Ա
			Field[] fields = cla1.getDeclaredFields();
			for(Field field:fields) {
				System.out.println(field);
			}
			
			Field field = cla1.getDeclaredField("name");
			field.setAccessible(true);
			field.set(obj, "��÷÷");
			System.out.println(obj);
			
			// ���÷���
			Method[] methods = cla1.getMethods();
			for(Method m:methods) {
				System.out.println("����:"+m);
			}
			
			Method method = cla1.getMethod("toString", null);
			System.out.println(method.invoke(obj, null));
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}
}
