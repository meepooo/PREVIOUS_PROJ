package com.lucky.servlet;

import java.io.IOException;

import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * Servlet implementation class CookieTest
 */
@WebServlet("/CookieTest")
public class CookieTest extends HttpServlet {

	protected void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {

		Cookie cookie = new Cookie("name", "zhangsan");
		cookie.setMaxAge(60*60*24*7);

		Cookie[] cookies = request.getCookies();
		if (cookies != null) {
			for (Cookie c : cookies) {
				System.out.println("getcookie\t" + "name:" + c.getName() + ",value:" + c.getValue());
			}
		}
		

		response.addCookie(cookie);
		System.out.println("add cookie!");
		// ±àÂë
		response.setHeader("Context-Type", "text-html;charset='UTF-8'");
		response.getWriter().write("success");
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse
	 *      response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {

		doGet(request, response);
	}

}
