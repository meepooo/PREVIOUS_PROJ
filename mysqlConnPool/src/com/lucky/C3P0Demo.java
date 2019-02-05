package com.lucky;

import java.io.InputStream;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

import org.apache.commons.dbcp.BasicDataSource;
import org.junit.Test;

import com.mchange.v2.c3p0.ComboPooledDataSource;

public class C3P0Demo {

	@Test
	public void testC3P0() {
		ComboPooledDataSource dataSource = null;
		Connection conn = null;
		PreparedStatement pst = null;
		ResultSet resultSet = null;
		InputStream is = null;		
		try {
			dataSource = new ComboPooledDataSource();
			
			//快速连接
//			dataSource.setDriverClass("com.mysql.jdbc.Driver");
//			dataSource.setJdbcUrl("jdbc:mysql://192.168.2.219/testdb");
//			dataSource.setUser("test");
//			dataSource.setPassword("Difficult_password1234");
			
			//使用xml配置文件
			// src目录下的c3p0-config.xml
			conn = dataSource.getConnection();
			String sql = "select * from user where id =?";
			pst = conn.prepareStatement(sql);
			pst.setInt(1, 2);
			pst.executeQuery();
	
			resultSet = pst.executeQuery();
			while (resultSet.next()) {
				System.out.println(resultSet.getInt(1));
				System.out.println(resultSet.getString(2));
			}
		}catch(Exception e) {
			e.printStackTrace();
		}
		
	}
}
