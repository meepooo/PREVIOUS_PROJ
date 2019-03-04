package com.Itstar.demo01;
/**
 * 方法1：通过同步代码块实现多线程的同步
 * @author Young
 * @version 1.0
 * */
public class Ticket1 implements Runnable{

	   //票的总数
		private int total;
		//新建一个锁对象
		Object mutex=new Object();
		//建立无参的构造函数
		Ticket1(){
			
			
		}
		//建立一个构造函数
		Ticket1(int total){
			
			this.total=total;
			
		}
		@Override
		public void run() {
			// TODO Auto-generated method stub
			
			while(total>0) {
				//同步代码块
				synchronized(mutex) {
				//卖一张票
				total--;
				//获得售票窗口
				String window=Thread.currentThread().getName();
				System.out.println(window+"卖了一张票，还剩"+total+"张票");
				}//
				//模拟收钱找钱的过程--并没有在同步代码块里面
				//因为同步代码块是一个高开销的操作，所以尽量减少同步的内容。
				try {
					Thread.sleep(1000);
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				
			}
			
			
		}
		

}
