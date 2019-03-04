package com.Itstar.demo01;
/**
 * 
 * 模仿一下售票的过程--通过同步代码块实现同步。
 * @author Young
 * @version 1.0
 * 
 * 
 * */
public class SaleTickets2 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		//1 初始化票额--runnable 对象
		Ticket2 tk=new Ticket2(100);
		//2 新建 thread类
		Thread thread=new Thread(tk);
		thread.setName("窗口1");
		Thread thread2=new Thread(tk);
		thread2.setName("窗口2");
		//3 开始买票-- 开启线程 
		thread.start();
		thread2.start();
		
		

	}

}
