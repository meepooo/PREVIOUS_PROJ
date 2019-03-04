package com.Itstar.demo01;

import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

/**
 * 方法3：通过ReentrantLock实现多线程的同步
 * 
 * @author Young
 * @version 1.0
 * */
public class Ticket3 implements Runnable{

	   //票的总数
		private int total;
		//定义一个 ReentrantLock对象--多态
		private Lock lock=new ReentrantLock();
		
		//建立无参的构造函数
		Ticket3(){
			
			
		}
		//建立一个构造函数
		Ticket3(int total){
			
			this.total=total;
			
		}
	
		
		@Override
		public void run() {
			// TODO Auto-generated method stub
			
			while(total>0) {
				//上锁
				lock.lock();
				try {
				total--;
				//获得售票窗口
				String window=Thread.currentThread().getName();
				System.out.println(window+"卖了一张票，还剩"+total+"张票");
				}finally {
				//释放锁
				lock.unlock();
				}
				try {
					Thread.sleep(1000);
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
				
			
			
		}
		

}
