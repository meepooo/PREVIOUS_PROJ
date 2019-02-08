<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Insert title here</title>
<script type="text/javascript" src="js/jquery-1.11.3.min.js"></script>
<script type="text/javascript">
	function load(){
		$("#name").load("/jQueryDemo/ServletDemo", function(responseText, statusTXT, xhr){
			//alert("result:"+responseText);
			$("#name").val(responseText);
		});
	}
</script>
</head>
<body>
	<input type="text" name="name" id="name" onblur="checkName()">
	<input type="password" name="passowrd" id="password">
	<input type="button" name="" value="submit" onclick="load()">
	<h1><a href="" onclick="load()">点击AjaxDemo访问servlet</a></h1>
</body>
</html>