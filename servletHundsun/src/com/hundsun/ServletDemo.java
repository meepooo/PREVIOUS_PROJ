package com.hundsun;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.Servlet;
import javax.servlet.ServletConfig;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;

public class ServletDemo implements Servlet{

	@Override
	public void destroy() {
		System.out.println("run destory");
	}

	@Override
	public ServletConfig getServletConfig() {
		System.out.println("run servletconfig");
		return null;
	}

	@Override
	public String getServletInfo() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public void init(ServletConfig arg0) throws ServletException {
		System.out.println("run init");
		
	}

	@Override
	public void service(ServletRequest req, ServletResponse res) throws ServletException, IOException {
		System.out.println("run service");
		PrintWriter writer = res.getWriter();
		String str = "<h1>run service SUCESS</h1>";
		writer.println(str.toCharArray());
		writer.close();
	}

}
