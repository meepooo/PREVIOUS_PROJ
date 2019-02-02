package com.jdbc.test;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

import org.junit.Test;

import com.jdbc.util.JDBCUtil;

public class TestDemo {
	
	@Test
	public void queryTbl() throws SQLException {
		
		Connection conn = JDBCUtil.getConn();
		Statement st = conn.createStatement();
		String sql="select * from test";
		ResultSet rs = st.executeQuery(sql);
		while(rs.next()) {
			System.out.println(rs.getInt("a")+rs.getString("b"));
		}
		JDBCUtil.release(conn, st, rs);
	}
}
