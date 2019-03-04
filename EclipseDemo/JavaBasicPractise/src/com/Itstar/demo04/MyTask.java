package com.Itstar.demo04;
/**
 * 为线程池的使用做准备
 * 
 * @author Young
 * @version 1.0
 * 
 * */
public class MyTask implements Runnable {
   //工作任务数
	private int taskNum;
	public MyTask() {
		
		
	}
	public MyTask(int taskNum) {
		
		this.taskNum=taskNum;
	}
	@Override
	public void run() {
		// TODO Auto-generated method stub
		System.out.println("正在执行的任务"+taskNum);
		try {
			Thread.currentThread().sleep(2000);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		};
		System.out.println("task"+taskNum+"finish!!");
	}
	

}
