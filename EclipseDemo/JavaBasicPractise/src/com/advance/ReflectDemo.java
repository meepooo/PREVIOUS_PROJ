package com.advance;

import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;

public class ReflectDemo {
	public static void main(String[] args) throws NoSuchMethodException, SecurityException, InstantiationException, IllegalAccessException, IllegalArgumentException, InvocationTargetException {
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
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}
}
