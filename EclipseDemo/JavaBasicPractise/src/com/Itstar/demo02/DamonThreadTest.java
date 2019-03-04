package com.Itstar.demo02;
/**
 * 守护线程演示
 * @author Young
 * @version 1.0
 * 
 * */
public class DamonThreadTest {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		//1、用户线程声明 runnable对象
		MyUser myUser=new MyUser();
		//调用Thread类以runnable对象为参数的构造函数
		Thread userThread=new Thread(myUser);
		
		//2、守护线程
		MyDamon myDamon=new MyDamon();
		Thread damonThread=new Thread(myDamon);
		damonThread.setDaemon(true);
		//3 开启用户线程和守护线程
		
		userThread.start();
		damonThread.start();

	}

}
