package com.jdbc.util;

import java.io.PrintWriter;
import java.sql.Connection;
import java.sql.SQLException;
import java.sql.SQLFeatureNotSupportedException;
import java.util.ArrayList;
import java.util.List;
import java.util.logging.Logger;

import javax.sql.DataSource;

/*
 * ���ݿ����ӳ�
 * @see javax.sql.DataSource#getConnection(java.lang.String, java.lang.String)
 */
public class DataSourceDemo implements DataSource{
	
	List<Connection> list = new ArrayList<Connection>();
	
	public DataSourceDemo() {
		for(int i=0;i<10;i++) {
			Connection conn = JDBCUtil.getConn();
			list.add(conn);			
		}
	}
	
	// �黹���ӳ�
	public void backConn(Connection conn) {
		list.add(conn);
	}
	
	@Override
	public Connection getConnection() throws SQLException {
		//�鿴�Ƿ�Ϊ��
		if(list.size()==0) {
			for(int i=0;i<3;i++) {
				Connection conn = JDBCUtil.getConn();
				list.add(conn);
			}
		}
		
		//�Ƴ�����
		Connection conn = list.remove(0);
		
		//��װ
		Connection connection = new ConnectionWrap(conn, list);
		
		return connection;
	}

	@Override
	public Connection getConnection(String username, String password) throws SQLException {
		// TODO Auto-generated method stub
		return null;
	}
	
	@Override
	public PrintWriter getLogWriter() throws SQLException {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public void setLogWriter(PrintWriter out) throws SQLException {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void setLoginTimeout(int seconds) throws SQLException {
		// TODO Auto-generated method stub
		
	}

	@Override
	public int getLoginTimeout() throws SQLException {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public Logger getParentLogger() throws SQLFeatureNotSupportedException {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public <T> T unwrap(Class<T> iface) throws SQLException {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public boolean isWrapperFor(Class<?> iface) throws SQLException {
		// TODO Auto-generated method stub
		return false;
	}



}
