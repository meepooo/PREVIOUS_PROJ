package com.Itstar.demo01;
/**
 * ����2��ͨ��ͬ������ʵ�ֶ��̵߳�ͬ��
 * ����дһ��������Ȼ����synchronized����
 * @author Young
 * @version 1.0
 * */
public class Ticket2 implements Runnable{

	   //Ʊ������
		private int total;
		
		//�����޲εĹ��캯��
		Ticket2(){
			
			
		}
		//����һ�����캯��
		Ticket2(int total){
			
			this.total=total;
			
		}
		//����дһ����Ʊ����
		public synchronized void sellTicket() {
			if(total>0) {
			//��һ��Ʊ
			total--;
			//�����Ʊ����
			String window=Thread.currentThread().getName();
			System.out.println(window+"����һ��Ʊ����ʣ"+total+"��Ʊ");
			}else {
				
				System.out.println("�Բ���Ʊ�����꣡");
			}
			
			
			
		}
		
		@Override
		public void run() {
			// TODO Auto-generated method stub
			
			while(total>0) {
				sellTicket();
				//�߳�sleep 1000ms
				try {
					Thread.sleep(1000);
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
				
			
			
		}
		

}
