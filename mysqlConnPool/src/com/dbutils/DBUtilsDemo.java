package com.dbutils;

import java.util.List;

import org.apache.commons.dbutils.QueryRunner;
import org.apache.commons.dbutils.handlers.BeanHandler;
import org.apache.commons.dbutils.handlers.BeanListHandler;
import org.junit.Test;

import com.mchange.v2.c3p0.ComboPooledDataSource;

public class DBUtilsDemo {

	public static class User {
		private int id;
		private String name;

		public int getId() {
			return id;
		}

		public void setId(int id) {
			this.id = id;
		}

		public String getName() {
			return name;
		}

		public void setName(String name) {
			this.name = name;
		}

		@Override
		public String toString() {
			return "" + id + ":" + name;
		}

	}

	@Test
	public void dbutilsDemo() {

		// 简化CRUD代码
		try {
			ComboPooledDataSource dataSource = new ComboPooledDataSource();
			QueryRunner queryRunner = new QueryRunner(dataSource);
			// 能直接插入，修改，删除
			// queryRunner.update("insert into user values(?,?)", 4, "zhaoliu");
			// queryRunner.update("delete from user where id = ?", 4);

			// 查询
			String sql = "select * from user where id =?";

//			queryRunner.query(sql, new ResultSetHandler<User>(){
//
//				@Override
//				public User handle(ResultSet rs) throws SQLException {
//					User user = new User();
//					while(rs.next()) {
//						user.id = rs.getInt(1);
//						user.name = rs.getString(2);
//						System.out.println(user.id);
//						System.out.println(user.name);
//					}
//					
//					return user;
//				}
//				
//			}, 3);
			// 另外一种写法
//			User account = queryRunner.query("select * from user where id = ?", 
//					new BeanHandler<User>(User.class), 1);
//			System.out.println(account.toString());

			User user = queryRunner.query(sql, new BeanHandler<User>(User.class), 3);
			System.out.println(user.toString());

			// 多条记录查询
			List<User> list = queryRunner.query("select * from user ", new BeanListHandler<User>(User.class));

			for (User account : list) {
				System.out.println(account.toString());
			}

		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}
