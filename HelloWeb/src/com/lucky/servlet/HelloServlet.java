package com.lucky.servlet;

import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.Enumeration;
import java.util.Properties;

import javax.servlet.ServletConfig;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
/*
 * 可以用实现 Servlet接口的方式发现
 */
//public class HelloServlet implements Servlet{
//
//	@Override
//	public void destroy() {
//		System.out.println("destroy run");
//		
//	}
//
//	@Override
//	public ServletConfig getServletConfig() {
//		// TODO Auto-generated method stub
//		return null;
//	}
//
//	@Override
//	public String getServletInfo() {
//		// TODO Auto-generated method stub
//		return null;
//	}
//
//	@Override
//	public void init(ServletConfig arg0) throws ServletException {
//		System.out.println("init run");
//		
//	}
//
//	@Override
//	public void service(ServletRequest arg0, ServletResponse arg1) throws ServletException, IOException {
//		System.out.println("service run");
//		
//	}
//	
//}


/*
 * 用子类的方式实现
 */
public class HelloServlet extends HttpServlet{

	@Override
	protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
		System.out.println("doGetStart");
		//1.得到servlet配置对象
		ServletConfig conf = getServletConfig();
		String servletName = conf.getServletName();
		System.out.println(servletName);
		System.out.println(conf.getInitParameter("address"));
		Enumeration<String> names = conf.getInitParameterNames();
		while(names.hasMoreElements()) {
			System.out.println(names.nextElement());
		}
		
		//2.servletContext上下文
		ServletContext context = getServletContext();
		System.out.println("servletContext:" + context.getInitParameter("name"));
		String path =	context.getRealPath("config.properties");
		System.out.println(path);
		
		//4.或者直接获得流
//		InputStream input = context.getResourceAsStream("config.properties");
		
		//3.Properties
		Properties properties = new Properties();
		InputStream is=new FileInputStream(path);		
		properties.load(is);
		System.out.println("Properties:" + properties.getProperty("name"));
		is.close();
		
		//5.使用classloader获取资源
		//class目录和资源目录的不同
		this.getClass().getClassLoader().getResourceAsStream("../../config.properties");
		
	}

	@Override
	protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
		System.out.println("doPost run");
	}

	@Override
	protected void service(HttpServletRequest arg0, HttpServletResponse arg1) throws ServletException, IOException {
		System.out.println("service run");
		doGet(arg0, arg1);
	}

}
