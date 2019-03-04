package com.thread;

import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class ThreadDemo implements Runnable{

	
	@Override
	public void run() {
		System.out.println("run thread");
		
		ReentrantLock lock = new ReentrantLock();
		
		lock.lock();
		lock.unlock();
		
		try {
			Thread.sleep(2);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
