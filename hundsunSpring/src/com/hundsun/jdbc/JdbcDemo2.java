package com.hundsun.jdbc;

import javax.annotation.Resource;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.junit4.SpringJUnit4ClassRunner;

@RunWith(SpringJUnit4ClassRunner.class)
@ContextConfiguration("classpath:applicationContext.xml")
public class JdbcDemo2 {

	@Resource(name="template")
	private JdbcTemplate template;
	
	@Test
	public void test() {
		template.update("insert into user values(?,?)", 102,"Ð¡»¨");
	}
}
