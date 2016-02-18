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
<title>LoginMenu</title>
<meta name="robots" content="none">
<meta name="description" content="Liujiquan Test WebSock">
<meta name="author" content="ABS-ASE:Development Team">
<link rel="stylesheet" media="all" href="./css/login.css">
</head>
<%
Dim strFileName, strUrlArray(100)
strFileName = "/data/MainMenu.txt"
Dim fileObj, fileTextObj
Set fileObj = Server.CreateObject("Scripting.FileSystemObject")
'--FileName取得
strFileName = Server.MapPath("./") & strFileName		'&#34395;擬目&#37636;+strFileName
if "False" = fileObj.FileExists(strFileName) Then
	Response.Redirect("login.asp")
End if
' 讀取配置文件
Set fileTextObj = fileObj.OpenTextFile(strFileName, 1)
Dim dLoopCnt
dLoopCnt = 0
Do Until fileTextObj.AtEndOfStream 
	Dim param
	param = fileTextObj.ReadLine
	strUrlArray(dLoopCnt) = param
	dLoopCnt = dLoopCnt + 1
Loop	
%>
<script type="text/javascript">
function window_onload()
{

}
function mouseOut()
{
	document.all[0].style.backgroundColor="silver";

}

function Action(strUrl)
{
	window.parent.frames["FRAME2"].location = strUrl;
	window.parent.frames["FRAME1"].location.reload();
}
</script>
<body text="#333333" link="#003399" vlink="#003399" alink="#ffffff" onload="window_onload();">
<form name="form_loginMenu" method="post">
<%  Dim i ,strTemp %>
<%  For i = 0 to  dLoopCnt-1 %>
<%  
		Dim paramArr	
		paramArr = Split(strUrlArray(i) , ",")
		If UBound(paramArr) < 1 Then
			break
		End If
		strTemp =  "<DIV ID = '" & i 
		strTemp =  strTemp & "'><img SRC='./images/l_ymd.gif' ALT='"
		strTemp =  strTemp & paramArr(0)
		strTemp =  strTemp & "'><a HREF='javascript:void(0);'  TARGET='_self' rel='"
		strTemp =  strTemp &	paramArr(0)
		strTemp =  strTemp &	"?"
		strTemp =  strTemp &	paramArr(1)
		strTemp =  strTemp &	"' title='"
		strTemp =  strTemp & paramArr(1)
		strTemp =  strTemp & "' onclick='Action(this.rel);' onmouseout='mouseOut();'>"
		strTemp =  strTemp & paramArr(1)
		strTemp =  strTemp & "<BR></A></DIV>"
		Response.write(strTemp & Chr(13))
%>
<%  Next %>
</form>
</body>
</html>
