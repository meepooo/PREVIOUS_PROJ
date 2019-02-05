package com.jdbc.util;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import org.junit.Test;

public class TestPool {
	@Test
	public void test() {	
		DataSourceDemo dataSource =null;
		Connection conn=null;
		PreparedStatement pst=null;
		ResultSet resultSet = null;
		try {
			dataSource = new DataSourceDemo();
			conn =dataSource.getConnection();
			String sql = "select * from user where id =?";
			pst = conn.prepareStatement(sql);
			pst.setInt(1, 1);
			resultSet = pst.executeQuery();
			while(resultSet.next()) {
				System.out.println(resultSet.getInt(1));
				System.out.println(resultSet.getString(2));
			}					
		} catch (SQLException e) {
			e.printStackTrace();
		} finally {
			//归还连接池
//			dataSource.backConn(conn);
			//释放资源
			JDBCUtil.release(pst, resultSet);
		}
	}
}
