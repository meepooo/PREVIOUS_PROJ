package com.Itstar.demo02;
/**
 * 声明一个线程
 * @author Young
 * @version 1.0
 * */
public class MyDamon implements Runnable{

	@Override
	public void run() {
		// TODO Auto-generated method stub
		while(true) {
		System.out.println("我是守护线程，人在塔在，奋战到天亮");
		}
	}

}
