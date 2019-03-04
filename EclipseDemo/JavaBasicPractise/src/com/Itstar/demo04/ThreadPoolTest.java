package com.Itstar.demo04;

import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;

public class ThreadPoolTest {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		//1����ʼ���̳߳ء�
		/**
		 *  corePoolSize--�̳߳��к����߳����� 5
	  		maximumPoolsize---����߳��� 10
	  		keepAliveTime--200
	  		TimeUnit--ms
			BlockingQueue--��������-- 5
		 * 
		 * 
		 * */
		ThreadPoolExecutor executor=new ThreadPoolExecutor(5,10,200,
				TimeUnit.MICROSECONDS,new ArrayBlockingQueue<Runnable>(5));
		//2 ģ���̳߳صĹ�������
		for(int i=0;i<15;i++) {
			//2-1 �½�һ���߳�
			MyTask mytask=new MyTask(i);
			//2-2 ���̳߳�������߳�
			executor.execute(mytask);
			System.out.println("�̳߳��е��߳���Ŀ��"+executor.getPoolSize()+
					"�����еȴ����߳���Ŀ��"+executor.getQueue()+
					"��ִ����ɵ�������Ŀ:"+executor.getCompletedTaskCount());
		}
		//3- �ر��̳߳�
		executor.shutdown();

	}

}
