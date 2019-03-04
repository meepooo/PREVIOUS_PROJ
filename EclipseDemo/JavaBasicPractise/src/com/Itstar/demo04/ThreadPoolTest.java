package com.Itstar.demo04;

import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;

public class ThreadPoolTest {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		//1、初始化线程池。
		/**
		 *  corePoolSize--线程池中核心线程数。 5
	  		maximumPoolsize---最大线程数 10
	  		keepAliveTime--200
	  		TimeUnit--ms
			BlockingQueue--阻塞队列-- 5
		 * 
		 * 
		 * */
		ThreadPoolExecutor executor=new ThreadPoolExecutor(5,10,200,
				TimeUnit.MICROSECONDS,new ArrayBlockingQueue<Runnable>(5));
		//2 模拟线程池的工作机制
		for(int i=0;i<15;i++) {
			//2-1 新建一个线程
			MyTask mytask=new MyTask(i);
			//2-2 往线程池中添加线程
			executor.execute(mytask);
			System.out.println("线程池中的线程数目："+executor.getPoolSize()+
					"对列中等待的线程数目："+executor.getQueue()+
					"已执行完成的任务数目:"+executor.getCompletedTaskCount());
		}
		//3- 关闭线程池
		executor.shutdown();

	}

}
