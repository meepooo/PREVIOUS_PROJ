package com.wraperdemo;

/*
 * ��װ��
 */
public class WaitressWrap implements Waiter {

	Waiter waiter = null;

	public WaitressWrap(Waitress waiter) {
		this.waiter=waiter;
	}

	@Override
	public void service() {
		System.out.println("service��װ��");
		waiter.service();
	}

}
