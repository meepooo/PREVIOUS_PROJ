package com.jdbc.test;

import org.junit.Test;

import com.jdbc.dao.UserDao;
import com.jdbc.dao.impl.UserDaoImpl;

public class UserDaoTest {

	@Test
	public void testFindAdd() {
		
		UserDao dao = new UserDaoImpl();
		if(!dao.login("zhangsan", "123456")) {
			System.out.println("√‹¬Î¥Ì");
			return ;
		}
		dao.findAll();
	}
}
