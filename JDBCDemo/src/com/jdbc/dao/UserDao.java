package com.jdbc.dao;

public interface UserDao {
	void findAll();
	boolean login(String user, String password);
}
