package com.thread;

public class ThreadTest {
	public static void main(String[] args) {
		ThreadDemo demo = new ThreadDemo();
		
		Thread thread1 = new Thread(demo);
		Thread thread2 = new Thread(demo);
		
//		Thread t1 = new Thread("thread1");
//		Thread t2 = new Thread("thread2");
//		
//		t1.start();
//		t2.start();
		
		thread1.start();
		thread2.start();
		
		System.out.println("======end========");
	}
}
