package com.Itstar.demo01;
/**
 * ����1��ͨ��ͬ�������ʵ�ֶ��̵߳�ͬ��
 * @author Young
 * @version 1.0
 * */
public class Ticket1 implements Runnable{

	   //Ʊ������
		private int total;
		//�½�һ��������
		Object mutex=new Object();
		//�����޲εĹ��캯��
		Ticket1(){
			
			
		}
		//����һ�����캯��
		Ticket1(int total){
			
			this.total=total;
			
		}
		@Override
		public void run() {
			// TODO Auto-generated method stub
			
			while(total>0) {
				//ͬ�������
				synchronized(mutex) {
				//��һ��Ʊ
				total--;
				//�����Ʊ����
				String window=Thread.currentThread().getName();
				System.out.println(window+"����һ��Ʊ����ʣ"+total+"��Ʊ");
				}//
				//ģ����Ǯ��Ǯ�Ĺ���--��û����ͬ�����������
				//��Ϊͬ���������һ���߿����Ĳ��������Ծ�������ͬ�������ݡ�
				try {
					Thread.sleep(1000);
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				
			}
			
			
		}
		

}
