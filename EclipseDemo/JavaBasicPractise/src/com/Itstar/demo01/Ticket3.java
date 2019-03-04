package com.Itstar.demo01;

import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

/**
 * ����3��ͨ��ReentrantLockʵ�ֶ��̵߳�ͬ��
 * 
 * @author Young
 * @version 1.0
 * */
public class Ticket3 implements Runnable{

	   //Ʊ������
		private int total;
		//����һ�� ReentrantLock����--��̬
		private Lock lock=new ReentrantLock();
		
		//�����޲εĹ��캯��
		Ticket3(){
			
			
		}
		//����һ�����캯��
		Ticket3(int total){
			
			this.total=total;
			
		}
	
		
		@Override
		public void run() {
			// TODO Auto-generated method stub
			
			while(total>0) {
				//����
				lock.lock();
				try {
				total--;
				//�����Ʊ����
				String window=Thread.currentThread().getName();
				System.out.println(window+"����һ��Ʊ����ʣ"+total+"��Ʊ");
				}finally {
				//�ͷ���
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
