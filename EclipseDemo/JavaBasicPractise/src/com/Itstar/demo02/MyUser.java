package com.Itstar.demo02;
/**
 * �û��߳�
 * @author Young
 * @version 1.0
 * 
 * */
public class MyUser implements Runnable {

	@Override
	public void run() {
		// TODO Auto-generated method stub
		for(int i=1;i<=10;i++) {
		System.out.println("�����û��̣߳����ڼ�����"+i);
		}
	}
	

}
