package com.hundsun.service;

import com.hundsun.dao.DaoDemoImpl;

public class ServiceDemoImpl implements ServiceDemo {

	private DaoDemoImpl dao;
	
	//setter方法
	public void setDao(DaoDemoImpl dao) {
		this.dao = dao;
	}
	
	@Override
	public void register() {
		
		//方法一：
//		DaoDemoImpl daoDemoImpl = new DaoDemoImpl();
//		daoDemoImpl.addUser();

		//方法二：
		dao.addUser();
		
		System.out.println("register success");
	}

	public DaoDemoImpl getDao() {
		return dao;
	}

	@Override
	public void login() {
		// TODO Auto-generated method stub

	}

	@Override
	public void logout() {
		// TODO Auto-generated method stub

	}

}
