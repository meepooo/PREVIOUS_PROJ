package com.Itstar.demo02;
/**
 * �ػ��߳���ʾ
 * @author Young
 * @version 1.0
 * 
 * */
public class DamonThreadTest {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		//1���û��߳����� runnable����
		MyUser myUser=new MyUser();
		//����Thread����runnable����Ϊ�����Ĺ��캯��
		Thread userThread=new Thread(myUser);
		
		//2���ػ��߳�
		MyDamon myDamon=new MyDamon();
		Thread damonThread=new Thread(myDamon);
		damonThread.setDaemon(true);
		//3 �����û��̺߳��ػ��߳�
		
		userThread.start();
		damonThread.start();

	}

}
