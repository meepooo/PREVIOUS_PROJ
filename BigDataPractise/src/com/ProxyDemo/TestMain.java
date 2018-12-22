package com.ProxyDemo;

import java.lang.reflect.InvocationHandler;
import java.lang.reflect.Method;
import java.lang.reflect.Proxy;

public class TestMain {

	public static void main(String[] args) {
		// 创建真正对象
		MyBusiness obj = new MyBusinessImpl();
		
		// 创建代理对象
		MyBusiness proxy = (MyBusiness) Proxy.newProxyInstance(TestMain.class.getClassLoader(), 
				obj.getClass().getInterfaces(), 
				new InvocationHandler() {

					@Override
					public Object invoke(Object proxy, Method method, Object[] args) throws Throwable {
						if ( method.getName().equals("method1")) {
							// 执行代理
							System.out.println("代理对象的method1");
						}
						else {
							//其他方法
							return method.invoke(obj, args);
						}
						return null;
					}
		});
		
		proxy.method1();
		proxy.method2();
	}

}
