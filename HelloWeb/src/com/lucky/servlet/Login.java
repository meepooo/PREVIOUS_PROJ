package com.lucky.servlet;

import java.io.IOException;
import java.util.Enumeration;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;

import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * Servlet implementation class Login
 */
@WebServlet("/Login")
public class Login extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public Login() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
//		System.out.println("get data:"+request.getRequestURI());
//		System.out.println("get username:"+request.getParameter("form-username"));
//		System.out.println("get password:"+request.getParameter("form-password"));
		
		//批量取头信息
		Enumeration<String> names = request.getHeaderNames();
		while(names.hasMoreElements()) {
			String name = names.nextElement();
			String value = request.getHeader(name);
					
			System.out.println("name:"+name+",value:"+value);
		}
		
		//批量取报文体
		Map<String, String[]> map = request.getParameterMap();
		Set<String> set = map.keySet();
		Iterator<String> iterator = set.iterator();
		while(iterator.hasNext()) {
			String key = iterator.next();
			String value = map.get(key)[0];
			
			//转换编码
			//从默认的ISO-8859-1转换为UTF-8
			key = new String(key.getBytes("ISO-8859-1"), "UTF-8");
			value = new String(value.getBytes("ISO-8859-1"), "UTF-8");
			
			System.out.println("key:"+key+",value:"+value);
		}
		
		//返回FOUND
		response.setStatus(302);
		response.setHeader("Location", "success.html");
		
		//1. 成功的次数累加
		
//		//获取以前存的值 ， 然后在旧的值基础上  + 1 
//		Object obj = getServletContext().getAttribute("count") ; 
//		
//		//默认就是0次
//		int totalCount = 0 ;
//		if(obj != null){
//			totalCount = (int) obj;
//		}
//		
//		System.out.println("已知登录成功的次数是："+totalCount);
//		
//		//给这个count赋新的值
//		getServletContext().setAttribute("count", totalCount+1);
		
		ServletContext context = getServletContext();
		Object obj = context.getAttribute("count");
		int count=0;
		if(obj!=null) {
			count = (int)obj;
		}
		System.out.println("已知登录成功的次数是："+count);
		context.setAttribute("count", count+1);
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		doGet(request, response);
	}

}
