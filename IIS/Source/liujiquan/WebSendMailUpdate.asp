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
<title>Main</title>
<meta name="robots" content="none">
<meta name="description" content="Liujiquan Test WebSock">
<meta name="author" content="ABS-ASE:Development Team">
<link rel="stylesheet" media="all" href="./css/SendMail.css">
<%
Dim strServer, nPort, strFrom, strTo, strUserName, strPwd
Dim sendText,sendFile, strTitle
Dim strBcc, strCc
sendText = Request.Form("sendtext")
strServer = Request.Form("server")
nPort = CInt(Request.Form("port"))
strFrom = Request.Form("from")
strTo = Request.Form("to")
strUserName = Request.Form("username")
strPwd = Request.Form("password")
strTitle = Request.Form("title")
sendFile = Request.QueryString("fileString")
strCc = Request.Form("cc")
strBcc = Request.Form("bcc")

Dim SendMailObj, nResult
nResult = 1
Set SendMailObj = CreateObject("AtlMail.CxMail")
If Not IsEmpty(SendMailObj) Then
	IF Not IsEmpty(sendFile) Then 
		Call SendMailObj.AddFile(sendFile)
	End  If
	'壓力測試
	For i = 1 To  1
		nResult = SendMailObj.SendMail(strServer, nPort, strFrom, strTo, strCc, strBcc, strUserName, strPwd, strTitle, sendText)
	Next
End if

Response.Redirect "WebSendMail.asp?nResult=" & nResult
%>

</html>