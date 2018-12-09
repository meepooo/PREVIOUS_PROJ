package com.dgns.pracdemo;

import java.io.FileWriter;
import java.io.IOException;

public class ExceptionDemo {
	public static void main (String[] args) throws Exception{
		if (1==0) {
			function();
			method();
			filewTest();
		}
		checkNum(-1);
		checkNum(101);
	}


public static void function(){
	try{
		System.out.println(2/0);
	}
	catch(Exception e){
		e.printStackTrace();
	}
	finally{
		System.out.println("我要释放function资源");
	}
}

public static void method(){
	try {
		String str = null;
		
		str.length();
	} catch (ArrayIndexOutOfBoundsException  e) {
		e.printStackTrace();
	}catch (NullPointerException e){
		e.printStackTrace();
		System.out.println(e.getMessage());
	}catch (Exception e){
		e.printStackTrace();
	}
	finally{
		System.out.println("我要释放method资源");
	}
}

public static void filewTest(){
	try {
		FileWriter fw = new FileWriter("a.txt");
	} catch (IOException e) {
		e.printStackTrace();
	} finally{
	}
}

public static void checkNum(int num) throws Exception{
	if (num < 0)
		throw new RuntimeException("不能负数");
	if (num > 100)
		throw new MyExceptionDemo("不能大于100");
}
}
