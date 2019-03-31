package com.user.register;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.jdbc.dao.impl.UserDaoImpl;

@WebServlet("/login.html")
public class UserRegister extends HttpServlet{

	@Override
	protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
		System.out.println("helloworld");
		String user = req.getParameter("user");
		String pass = req.getParameter("password");
		System.out.println("get:" + user + "," + pass);
		
		UserDaoImpl userDaoImpl = new UserDaoImpl();
		
		boolean login = userDaoImpl.login(user, pass);
		
		PrintWriter out = resp.getWriter();
		String html=null;
		if(login==true) {		
			html = "<h1>login1 success</h1>";
		}
		else{
			html = "<h1>login1 fail</h1>";
		}
		out.println(html);
		out.close();
	}

	@Override
	protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
		doGet(req, resp);
	}

}
