<%@page contentType="text/html;charset=GBK" isELIgnored="false"%>
<html>
<head><title>��ʵ���û���¼ʵ����struts��Spring����</title></head>
<body>
<font size='22'> $<br> </font>
<form name="form1" action="/myLogin/loginActionSupportdo" method="post">
�û�����<input type="text" name="username" value="${user.username}"/><br>
���룺<input type="password" name="password" value="${user.password}"/><br>
<input type="submit" name="method" value="�ύ"/>
</form>
</body>
</html>