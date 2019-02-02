package com.jdbc.demo.dao;

/**
 * 定义操作数据库的方法
 */
public interface UserDao {
	
	//update t_user set name=? where id = ?
	
	/**
	 * 根据id去更新具体的用户名
	 * @param id
	 * @param name
	 */
	void update(int id , String name);
	
	void delete(int id);
	
	/**
	 * 执行添加
	 * @param userName
	 * @param password
	 */
	void insert(String userName , String password);
	

	
	/**
	 * 查询所有
	 */
	void findAll();
	
	
	/**
	 * 登录方法
	 * @param username
	 * @param password
	 */
	void login(String username , String password);
}
