package com.hundsun.jdbc;

import org.junit.Test;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.jdbc.datasource.DriverManagerDataSource;

public class JdbcDemo1 {

	@Test
	public void demo() {
		DriverManagerDataSource dataSource = new DriverManagerDataSource();
		dataSource.setDriverClassName("com.mysql.jdbc.Driver");
		dataSource.setUrl("jdbc:mysql://139.9.2.241:3306/testdb");
		dataSource.setUsername("test");
		dataSource.setPassword("Difficult_password1234");
		
		JdbcTemplate template = new JdbcTemplate(dataSource);
		template.update("insert into user values(?,?)", 101,"ะกร๗");
		
	}
}
