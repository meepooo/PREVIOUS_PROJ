package com.hundsun.jdbc;

import org.junit.Test;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.jdbc.datasource.DriverManagerDataSource;

public class JdbcDemo {
	
	@Test
	// jdbcģ���ʹ��������Dbutils.
	public void demo1(){
		// �������ӳ�:
		DriverManagerDataSource dataSource = new DriverManagerDataSource();
		dataSource.setDriverClassName("com.mysql.jdbc.Driver");
		dataSource.setUrl("jdbc:mysql://139.9.2.241:3306/testdb");
		dataSource.setUsername("test");
		dataSource.setPassword("Difficult_password1234");
		// ����jdbcģ��
		JdbcTemplate jdbcTemplate = new JdbcTemplate();
		jdbcTemplate.setDataSource(dataSource);
		jdbcTemplate.update("insert into user values (?,?)", 10000d, "�Թ�ϣ");
		
	}
	
}
