package com.Itstar.demo03;

/**
 * wait:�ȴ� notify ���� notify:���ѵȴ��� wait
 * 
 * @author Young
 * @version 1.0
 * 
 */
public class WaitNotifyTest01 {
	// ��ʼ��һ���������ʶ���
	public static Object mutex = new Object();

	// ��̬��Ա�ڲ��� �������������ʳ�Ա���� ��Ϊ��һ���߳�
	static class Thread1 implements Runnable {

		@Override
		public void run() {
			// TODO Auto-generated method stub
			synchronized (mutex) {
				// �������ڵȴ�����������ĵ����߳�
				mutex.notify();
				System.out.println(Thread.currentThread().getName() + "������notify����");

			}
			// ִ����ͬ�������֮���ͷ��� �����������̷߳��ʲ��� ����������
			System.out.println(Thread.currentThread().getName() + "�ͷ�����");
		}
	}

	// ��̬��Ա�ڲ��� �������������ʳ�Ա���� ��Ϊ��һ���߳�
	static class Thread2 implements Runnable {

		@Override
		public void run() {
			// TODO Auto-generated method stub
			synchronized (mutex) {

				try {
					mutex.wait();
					System.out.println(Thread.currentThread().getName() + "�ڵȴ�");

				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				// ������
				System.out.println(Thread.currentThread().getName() + "�����ѣ��������");
			}
		}

	}

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		// ����������ͬ���߳� һ�� notify һ�� wait
		// �൱�� Thread1 thread1=new Thread1()��
		Thread th1 = new Thread(new Thread1());
		// Thread2 thread2=new Thread2();
		Thread th2 = new Thread(new Thread2());
		th1.setName("�߳�1--��notify");
		th2.setName("�߳�2--��wait");
		// ��Ȼ�߳�2 �����̣߳����� ��Ϊ wait �߳�������
		th2.start();
		try {
			Thread.sleep(1000);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		th1.start();

	}

}
