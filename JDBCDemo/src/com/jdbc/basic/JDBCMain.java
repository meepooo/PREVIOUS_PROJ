package com.jdbc.basic;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

import com.jdbc.util.JDBCUtil;

public class JDBCMain {
	public static void main(String[] args) {
		Connection conn=null;
		Statement st=null;
		ResultSet rs=null;
		try {
			// 1.注册驱动，DriverManager类加载就会注册，不再需要
			//DriverManager.registerDriver(new Driver());
			//Class.forName("com.mysql.jdbc.Driver");
			// 2.建立连接
			//conn = DriverManager.getConnection("jdbc:mysql://192.168.2.219:3306/testdb", "test", "Difficult_password1234");
			conn = JDBCUtil.getConn();
			// 3.创建statement
			st = conn.createStatement();
			
			// 4.执行sql
			String sql = "select * from test";
			rs = st.executeQuery(sql);
			
			// 5.遍历结果
			while(rs.next()) {
				int id = rs.getInt("a");
				String name = rs.getString("b");
				System.out.println("result:"+ id + "," + name);
			}			
			
		} catch (SQLException e) {
			e.printStackTrace();
		}finally {
			// 6.释放资源
//			try {
//				if(rs != null) {
//				rs.close();
//				st.close();
//				conn.close();
//				}
//			} catch (SQLException e) {
//				e.printStackTrace();
//			}finally {
//				rs=null;
//				st=null;
//				conn=null;
//			}
			JDBCUtil.release(conn, st, rs);
			
		}
	}
}
