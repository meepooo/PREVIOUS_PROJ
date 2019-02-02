package com.jdbc.dao.impl;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

import com.jdbc.dao.UserDao;
import com.jdbc.util.JDBCUtil;

public class UserDaoImpl implements UserDao{

	@Override
	public void findAll() {
		Connection conn =null;
		Statement st = null;
		ResultSet rs = null;
		
		conn = JDBCUtil.getConn();
		try {
			// createstatement用法
			st = conn.createStatement();
		
			String sql = "select * from user";
			rs = st.executeQuery(sql);
			while(rs.next()) {
				System.out.println("out:"+ rs.getInt("id") + "," + rs.getString("name"));
			}
			
			// prepareStatement用法
			String psql = "select * from t_user where name = ?";
			PreparedStatement pst = conn.prepareStatement(psql);
			pst.setString(1, "zhangsan");
			ResultSet rst = pst.executeQuery();
			while(rst.next()) {
				System.out.println("pre out:"+ rst.getString("name") + "," + rst.getString("password"));
			}
		} catch (SQLException e) {
			e.printStackTrace();
		}finally {
			JDBCUtil.release(conn, st, rs);
		}
	}

	@Override
	public boolean login(String user, String password) {
		Connection conn =null;
		Statement st = null;
		ResultSet rs = null;
		
		conn = JDBCUtil.getConn();
		try {
			st = conn.createStatement();
		
			String sql = "select * from t_user where name = " + "'" + user + "'";
			rs = st.executeQuery(sql);
			while(rs.next()) {
				String ps = rs.getString("password");
				
				if(ps.equals(password)) {
					System.out.println("密码验证通过");
					return true;
				}
			}
		} catch (SQLException e) {
			e.printStackTrace();
		}finally {
			JDBCUtil.release(conn, st, rs);
		}
		return false;
	}
	
}
