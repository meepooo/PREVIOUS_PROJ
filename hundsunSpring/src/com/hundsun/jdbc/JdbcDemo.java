package com.hundsun.jdbc;

import org.junit.Test;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.jdbc.datasource.DriverManagerDataSource;

public class JdbcDemo {
	
	@Test
	// jdbc模板的使用类似于Dbutils.
	public void demo1(){
		// 创建连接池:
		DriverManagerDataSource dataSource = new DriverManagerDataSource();
		dataSource.setDriverClassName("com.mysql.jdbc.Driver");
		dataSource.setUrl("jdbc:mysql://139.9.2.241:3306/testdb");
		dataSource.setUsername("test");
		dataSource.setPassword("Difficult_password1234");
		// 创建jdbc模板
		JdbcTemplate jdbcTemplate = new JdbcTemplate();
		jdbcTemplate.setDataSource(dataSource);
		jdbcTemplate.update("insert into user values (?,?)", 10000d, "赵冠希");
		
	}
	
}
