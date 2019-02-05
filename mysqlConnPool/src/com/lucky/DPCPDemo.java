package com.lucky;

import java.io.FileInputStream;
import java.io.InputStream;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Properties;

import javax.sql.DataSource;

import org.apache.commons.dbcp.BasicDataSource;
import org.apache.commons.dbcp.BasicDataSourceFactory;
import org.junit.Test;

public class DPCPDemo {

	@Test
	public void testDPCP() {
		BasicDataSource dataSource = null;
		Connection conn = null;
		PreparedStatement pst = null;
		ResultSet resultSet = null;
		InputStream is = null;
		try {
//			dataSource = new BasicDataSource();

//			dataSource.setDriverClassName("com.mysql.jdbc.Driver");
//			dataSource.setUrl("jdbc:mysql://192.168.2.219/testdb");
//			dataSource.setUsername("test");
//			dataSource.setPassword("Difficult_password1234");

			// 改配置文件
//			Properties properties = new Properties();
//			is = new FileInputStream("jdbc.properties");
//			properties.load(is);
//			
//			dataSource.setDriverClassName(properties.getProperty("driverClass"));
//			dataSource.setUrl(properties.getProperty("url"));
//			dataSource.setUsername(properties.getProperty("name"));
//			dataSource.setPassword(properties.getProperty("password"));

			// 用dpcp配置文件
			BasicDataSourceFactory factory = new BasicDataSourceFactory();
			Properties properties = new Properties();
			is = new FileInputStream("dbcpconfig.properties");
			properties.load(is);
			DataSource source = factory.createDataSource(properties);

			conn = source.getConnection();
			String sql = "select * from user where id =?";
			pst = conn.prepareStatement(sql);
			pst.setInt(1, 2);
			pst.executeQuery();

			resultSet = pst.executeQuery();
			while (resultSet.next()) {
				System.out.println(resultSet.getInt(1));
				System.out.println(resultSet.getString(2));
			}
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			try {
				is.close();
				dataSource.close();
			} catch (Exception e) {
				e.printStackTrace();
			}
		}

	}
}
