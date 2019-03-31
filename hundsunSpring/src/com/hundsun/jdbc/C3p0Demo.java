package com.hundsun.jdbc;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.junit4.SpringJUnit4ClassRunner;

@RunWith(SpringJUnit4ClassRunner.class)
@ContextConfiguration("classpath:applicationContext-c3p0.xml")

public class C3p0Demo {

	@Autowired
	private JdbcTemplate template;
	
	@Test
	public void test() {
		template.update("insert into user values (?,?)", 104, "º«Ã·Ã·");
	}
}
