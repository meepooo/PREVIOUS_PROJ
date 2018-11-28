<%@page contentType="text/html;charset=GBK" isELIgnored="false"%>
<html>
<head><title>；实现用户登录实例，struts和Spring整合</title></head>
<body>
<font size='22'> $<br> </font>
<form name="form1" action="/myLogin/loginActionSupportdo" method="post">
用户名：<input type="text" name="username" value="${user.username}"/><br>
密码：<input type="password" name="password" value="${user.password}"/><br>
<input type="submit" name="method" value="提交"/>
</form>
</body>
</html>