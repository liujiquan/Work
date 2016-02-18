<%@ LANGUAGE="VBSCRIPT"%>
<SCRIPT LANGUAGE="VBSCRIPT" RUNAT="SERVER">
'====================
'Filename : WebSockClient.asp
'Title：測試WebSock通訊
'Date :2014-06-04
'Version : 1.00
'Copyright (C) AMANO Corporation 2006 - 2009
'====================
</SCRIPT>
<!doctype html>
<html lang="ja">
<head>
<meta http-equiv="content-type" content="text/html; charset=Shift_JIS">
<meta http-equiv="content-style-type"  content="text/css">
<meta http-equiv="content-script-type" content="text/javascript">
<meta http-equiv="pragma" content="no-cache">
<meta http-equiv="cache-control" content="no-cache">
<title>測試websock2</title>
<meta name="robots" content="none">
<meta name="description" content="Liujiquan Test WebSock">
<meta name="author" content="ABS-ASE:Development Team">
<link rel="stylesheet" media="all" href="./css/login.css">
</head>
<!--#include file="./DbFunction.asp"-->
<%
Dim Username, Userpasword,flag
Dim errorMsg, errorCode
errorCode = 0
errorMsg = ""
Username = ""
Userpasword = ""
If Not IsEmpty(Request.QueryString("flag")) Then
	flag = Request.QueryString("flag")
	Username = Request.QueryString("Username")
	Userpasword = Request.QueryString("Userpassword")
	
	Dim strSql, Conn, RecordSet
	Set Conn = DBConnect()
	strSql = "SELECT * FROM [USER] WHERE NAME = '" & Username  
	strSql = strSql & "' AND PASSWORD = '" & Userpasword
	strSql = strSql & "'"
	Set RecordSet = DBOpen(Conn, strSql)
	
	errorMsg = DBError(Conn)
	if(errorMsg = "") Then
		If Not RecordSet.EOF Then 	'存在數據
			DBDisconnect(Conn)	
			Session.Abandon
			Session("USERNAME") = Username
			Session("PASSWORD") = Userpasword
			Response.Redirect "Main.asp"
		End If
	Else
		errorCode = 1
	End If
	DBDisconnect(Conn)
End if

%>

<script type="text/javascript">
function window_onload()
{
	if( <%= errorCode %> != 0)
	{
		alert("<%= errorMsg %>");
	}
	document.form_login.UserName.value = "<%= Username%>";
	document.form_login.UserPasswod.value = "<%= Userpassword%>";
}

<%' 登&#37636; %>
function Login()
{
	if(document.form_login.UserName.value.length == 0)
	{
		alert("用戸名不能為空");
		document.form_login.UserName.focus();
		return;
	}
	if(document.form_login.UserPasswod.value.length == 0)
	{
		alert("密碼不能為空");
		document.form_login.UserPasswod.focus();
		return;
	}
	document.form_login.action = "login.asp";
	document.form_login.action += "?flag=1";
	document.form_login.action += "&Username=" + document.form_login.UserName.value;
	document.form_login.action += "&Userpassword=" + document.form_login.UserPasswod.value;
	document.form_login.submit();
}
</script>
<body class="loginheader" onload="window_onload();">
<form name="form_login" method="post">
<div id="login_Table">
<img id="passchg" src="images/cx_headerlogo.gif" border="0">
<table id="MainTable" align='center'>
<tr>
	<td class="Items">
	<table id ="SubTable">
		<tr>
		<td class="title">用&#25142;名<br>user</td>
		<td class="iform"><input type="text" name="UserName" autocomplete="off" maxlength="20" size="15"  onfocus="select();"></td>
		<td class="title">密&nbsp;&nbsp;碼<br>password</td>
		<td class="iform"><input type="password" name="UserPasswod" autocomplete="off" maxlength="20" size="15"  onfocus="select();"></td>
		</tr>
	</table>
	</td>
</tr>	
<tr>
<td class="Items">
	<a href="#" onclick="Login(); return false;">
		<img name="loginButton" src="./images/login.gif" border="0" alt="login" title="Login" onmouseover="this.src='./images/login_r.gif';" onmouseout="this.src='./images/login.gif';">
	</a>
</td>
</tr>
</table>
	<A HrEF="http://localhost/liujiquan/Main.asp" >1</a>
	<A HREF  =  "  http://localhost/liujiquan/Main.asp  " >2</a>
	<A HREF  =  "  http://localhost/liujiquan/Main.asp/  " >3</a>
	<A HREF='http://localhost/liujiquan/Main.asp' >4</a>
	<A HREF=http://localhost/liujiquan/Main.asp>5</a>
	<A HREF=Main.asp>1231</a>
</div>										
</form>
</body>
</html>
