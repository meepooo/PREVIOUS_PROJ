package com.hundsun;

import java.io.IOException;
import java.io.PrintWriter;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Enumeration;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@SuppressWarnings("serial")
public class ServletLogin extends HttpServlet {

	@Override
	protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
		System.out.println("run doGet");
		req.setCharacterEncoding("UTF-8");
		resp.setHeader("Content-Type", "text/html; charset=UTF-8 ");
		
		PrintWriter writer = resp.getWriter();

		// 1.��ȡname��password
		Enumeration<String> names = req.getParameterNames();
		User user = new User();
		String eleName = null;
		String parameter = null;

		// get name
		eleName = names.nextElement();
		parameter = req.getParameter(eleName);
		System.out.println("name:" + eleName + ",value:" + parameter);
		user.setName(parameter);

		// get password
		eleName = names.nextElement();
		parameter = req.getParameter(eleName);
		System.out.println("name:" + eleName + ",value:" + parameter);
		user.setPassword(parameter);

		// init
		Connection conn = null;
		PreparedStatement pst = null;
		ResultSet rs = null;
		String resStr = null;

		// 2.���ݿ�У��
		try {
			// register���°汾mysql��Ϊcom.mysql.cj.jdbc.Driver
			DriverManager.registerDriver(new com.mysql.cj.jdbc.Driver());

			// connect
			conn = DriverManager.getConnection("jdbc:mysql://114.115.149.137:3306/testdb", "test",
					"Difficult_password1234");

			String sql = "select * from user where name = ? ";

			// prestatement
			pst = conn.prepareStatement(sql);
			pst.setString(1, user.getName());
			rs = pst.executeQuery();
			
			// ȡ����У��
			while (rs.next()) {
				System.out.println("rs.password:" + rs.getString("password") + ",user.password:" + user.getPassword());
				if (rs.getString("password").equals(user.getPassword())) {
					System.out.println("��¼�ɹ�");
					resStr = "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />"
							+ "<h1>login success</h1>\n"
							+ "<h1><a href=\"download/1.jpg\">��Ů</a></h1><br>"
							+ "<h1><a href=\"download/2.jpg\">����</a></h1><br>";
				}
			}

			if (resStr == null) {
				System.out.println("��¼ʧ��");
				resStr = "<h1>login fail</h1>";
			}
			
//			rs = pst.executeQuery();
//			while (rs.next()) {
//				int id = rs.getInt(1);
//				String name = rs.getString("name");
//				int age = rs.getInt("age");
//				System.out.println("id:" + id + ",name:" + name + ",age:" + age);
//			}

		} catch (SQLException e) {
			e.printStackTrace();
		} finally {
			try {
				rs.close();
				pst.close();
				conn.close();
			} catch (SQLException e) {
				System.out.println(e);
			}
		}

		// 3.����
		writer.println(resStr.toCharArray());
		writer.close();
	}

	@Override
	protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
		doGet(req, resp);
	}

}
