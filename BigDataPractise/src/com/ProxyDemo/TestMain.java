package com.ProxyDemo;

import java.lang.reflect.InvocationHandler;
import java.lang.reflect.Method;
import java.lang.reflect.Proxy;

public class TestMain {

	public static void main(String[] args) {
		// ������������
		MyBusiness obj = new MyBusinessImpl();
		
		// �����������
		MyBusiness proxy = (MyBusiness) Proxy.newProxyInstance(TestMain.class.getClassLoader(), 
				obj.getClass().getInterfaces(), 
				new InvocationHandler() {

					@Override
					public Object invoke(Object proxy, Method method, Object[] args) throws Throwable {
						if ( method.getName().equals("method1")) {
							// ִ�д���
							System.out.println("��������method1");
						}
						else {
							//��������
							return method.invoke(obj, args);
						}
						return null;
					}
		});
		
		proxy.method1();
		proxy.method2();
	}

}
