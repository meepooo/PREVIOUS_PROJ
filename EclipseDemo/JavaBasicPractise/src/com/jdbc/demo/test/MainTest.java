package com.jdbc.demo.test;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.Statement;

import com.jdbc.demo.util.JDBCUtil;

public class MainTest {

	public static void main(String[] args) {
		Connection conn  = null;
		Statement st = null;
		ResultSet rs = null;
		try {
			//1. 注册驱动 
			conn = JDBCUtil.getConn();
			
			//3. 创建statement ， 跟数据库打交道，一定需要这个对象
			st = conn.createStatement();
			
			//4. 执行查询 ， 得到结果集
			String sql = "select * from t_stu";
			rs = st.executeQuery(sql);
			//5. 遍历查询每一条记录
			while(rs.next()){
				int id = rs.getInt("id");
				String name = rs.getString("name");
				int age = rs.getInt("age");
				
				System.out.println("id="+id + "===name="+name+"==age="+age);
					
			}
			
		} catch (Exception e) {
			e.printStackTrace();
		}finally{
			JDBCUtil.release(conn, st, rs);
		}
	}
}
