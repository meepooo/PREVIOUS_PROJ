package com.Itstar.demo01;
/**
 * 
 * ģ��һ����Ʊ�Ĺ���--ͨ��ͬ�������ʵ��ͬ����
 * @author Young
 * @version 1.0
 * 
 * 
 * */
public class SaleTickets {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		//1 ��ʼ��Ʊ��--runnable ����
		Ticket1 tk=new Ticket1(100);
		//2 �½� thread��
		Thread thread=new Thread(tk);
		thread.setName("����1");
		Thread thread2=new Thread(tk);
		thread2.setName("����2");
		//3 ��ʼ��Ʊ-- �����߳� 
		thread.start();
		thread2.start();
		
		

	}

}
