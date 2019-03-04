package com.Itstar.demo01;
/**
 * 方法2：通过同步方法实现多线程的同步
 * 单独写一个方法，然后用synchronized修饰
 * @author Young
 * @version 1.0
 * */
public class Ticket2 implements Runnable{

	   //票的总数
		private int total;
		
		//建立无参的构造函数
		Ticket2(){
			
			
		}
		//建立一个构造函数
		Ticket2(int total){
			
			this.total=total;
			
		}
		//单独写一个卖票方法
		public synchronized void sellTicket() {
			if(total>0) {
			//卖一张票
			total--;
			//获得售票窗口
			String window=Thread.currentThread().getName();
			System.out.println(window+"卖了一张票，还剩"+total+"张票");
			}else {
				
				System.out.println("对不起，票已卖完！");
			}
			
			
			
		}
		
		@Override
		public void run() {
			// TODO Auto-generated method stub
			
			while(total>0) {
				sellTicket();
				//线程sleep 1000ms
				try {
					Thread.sleep(1000);
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
				
			
			
		}
		

}
