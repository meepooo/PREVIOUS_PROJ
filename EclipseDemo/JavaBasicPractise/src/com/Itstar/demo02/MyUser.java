package com.Itstar.demo02;
/**
 * 用户线程
 * @author Young
 * @version 1.0
 * 
 * */
public class MyUser implements Runnable {

	@Override
	public void run() {
		// TODO Auto-generated method stub
		for(int i=1;i<=10;i++) {
		System.out.println("我是用户线程，正在计数："+i);
		}
	}
	

}
