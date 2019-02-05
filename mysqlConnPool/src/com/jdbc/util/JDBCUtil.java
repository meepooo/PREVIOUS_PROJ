package com.jdbc.util;
/*
 * @author: Lucky
 * 
 */
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Properties;

public class JDBCUtil {
	static String driverClass = null;
	static String url = null;
	static String name = null;
	static String password= null;
	
	static {
		InputStream is=null;
		try {
			Properties properties = new Properties();
			
			is = new FileInputStream("jdbc.properties");
			//is = JDBCUtil.class.getClassLoader().getResourceAsStream("jdbc.properties");
			properties.load(is);
			driverClass = properties.getProperty("driverClass");
			url = properties.getProperty("url");
			name = properties.getProperty("user");
			password = properties.getProperty("password");
		} catch (Exception e) {
			e.printStackTrace();
		}finally {
			try {
				is.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
	
	public static Connection getConn() {
		Connection conn=null;
		
		try {
			// 1.注册驱动，DriverManager类加载就会注册，不再需要
			//DriverManager.registerDriver(new Driver());
			//forName也可以不写
			//Class.forName("com.mysql.jdbc.Driver");
			// 2.建立连接
			conn = DriverManager.getConnection("jdbc:mysql://192.168.2.219:3306/testdb", "test", "Difficult_password1234");

		} catch (Exception e) {
			e.printStackTrace();
		}		
		return conn;
	}
	
	/*
	 * 释放资源工具类 
	 */
	public static void release(Connection conn, Statement st, ResultSet rs) {
		closeRs(rs);
		closeSt(st);
		closeConn(conn);
	}
	
	public static void release(Statement st, ResultSet rs) {
		closeRs(rs);
		closeSt(st);
	}
	
	private static void closeRs(ResultSet rs) {
		try {
			if(rs != null) {
			rs.close();
			}
		} catch (SQLException e) {
			e.printStackTrace();
		}finally {
			rs=null;
		}
	}
	
	private static void closeSt(Statement st) {
		try {
			if(st != null) {
			st.close();
			}
		} catch (SQLException e) {
			e.printStackTrace();
		}finally {
			st=null;
		}
	}
	
	private static void closeConn(Connection conn) {
		try {
			if(conn != null) {
				conn.close();
			}
		} catch (SQLException e) {
			e.printStackTrace();
		}finally {
			conn=null;
		}
	}
}
