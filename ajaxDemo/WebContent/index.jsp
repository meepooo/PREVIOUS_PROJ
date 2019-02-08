<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Insert title here</title>
<script>
	function  ajaxFunction(){
	   var xmlHttp;
	   try{ // Firefox, Opera 8.0+, Safari
	        xmlHttp=new XMLHttpRequest();
	    }
	    catch (e){
		   try{// Internet Explorer
		         xmlHttp=new ActiveXObject("Msxml2.XMLHTTP");
		      }
		    catch (e){
		      try{
		         xmlHttp=new ActiveXObject("Microsoft.XMLHTTP");
		      }
		      catch (e){}
		      }
	    }

		return xmlHttp;
	 }
	
	function get(){
		//1. 创建xmlhttprequest 对象
		var request = ajaxFunction();
		
		var name = document.getElementById("name").value;
		
		//2. 发送请求
		request.open("GET" ,"/ajaxDemo/ServletDemo?name="+name ,true );
		
		//3. 获取响应数据 注册监听的意思。  一会准备的状态发生了改变，那么就执行 = 号右边的方法
		request.onreadystatechange = function(){
			
			//前半段表示 已经能够正常处理。  再判断状态码是否是200
			if(request.readyState == 4 && request.status == 200){
				//弹出响应的信息
				alert(request.responseText);
			}
		}
		
		request.send();
	}
	
	function checkName(){
		//1. 创建xmlhttprequest 对象
		var request = ajaxFunction();
		
		var name = document.getElementById("name").value;
		alter("name");
		//2. 发送请求
		request.open("GET" ,"/ajaxDemo/ServletDemo?name="+name ,true );
		
		//3. 获取响应数据 注册监听的意思。  一会准备的状态发生了改变，那么就执行 = 号右边的方法
		request.onreadystatechange = function(){
			
			//前半段表示 已经能够正常处理。  再判断状态码是否是200
			if(request.readyState == 4 && request.status == 200){
				//弹出响应的信息
				alert(request.responseText);
			}
		}
		
		request.send();
	}
</script>
</head>
<body>
	<input type="text" name="name" id="name" onblur="checkName()">
	<input type="password" name="passowrd" id="password">
	<input type="button" name="" value="submit">
	<h1><a href="" onclick="get()">点击AjaxDemo访问servlet</a></h1>
</body>
</html>