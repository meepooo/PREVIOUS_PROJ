package com.Itstar.demo04;
/**
 * Ϊ�̳߳ص�ʹ����׼��
 * 
 * @author Young
 * @version 1.0
 * 
 * */
public class MyTask implements Runnable {
   //����������
	private int taskNum;
	public MyTask() {
		
		
	}
	public MyTask(int taskNum) {
		
		this.taskNum=taskNum;
	}
	@Override
	public void run() {
		// TODO Auto-generated method stub
		System.out.println("����ִ�е�����"+taskNum);
		try {
			Thread.currentThread().sleep(2000);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		};
		System.out.println("task"+taskNum+"finish!!");
	}
	

}
