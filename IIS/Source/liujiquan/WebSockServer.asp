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
<link rel="stylesheet" media="all" href="./css/login.css">
<script src="./js/webserver.js" type="text/javascript"></script>
</head>		
<script type="text/javascript">
var m_Object;
var m_listInfo;
var m_ListIp;

function window_load()
{
	//ATL
	m_Object = new ActiveXObject("WebSocketServerProject.IServer"); 
	//Info
	m_listInfo = new CListBox(document.form_server.listBox);
	//IP
	m_ListIp = new CListBox2(document.getElementById("ul_IP"));
}

function window_unload()
{
	OnStopServer();
}
//FunctionID
var AddMsgID = 0;
var AddIPID = 1;
var DeleteIPID = 2;
function OnStartServer()
{
	// 設置函數
	m_Object.SetJsCallbackFunc(AddString, AddMsgID);
	m_Object.SetJsCallbackFunc(AddIP, AddIPID);
	m_Object.SetJsCallbackFunc(DeleteIP, DeleteIPID);
	var bResult = m_Object.OnInitSocket();
}	
//關閉服務
function OnStopServer()
{
	m_Object.OnStop();

}
//添加信息
function AddString(str)
{
	m_listInfo.addString(str);
}
//添加IP
function AddIP(str)
{
	m_ListIp.add(str);
}

//IP刪除IP
function DeleteIP(str)
{
	m_ListIp.deleteIP(str);
}
</SCRIPT>  
<body  onload="window_load();" id='background' onunload="window_unload();">
<form name="form_server" method="post">
<% '整個區域 Start%>
<div id='container'>

	<div id='ButtonDiv'>
	<table width='100%'>
		<tr>
			<td align='center'><input Type='Button' Value='開&#21855;服務' onClick='OnStartServer()' Name="StartButton"></td>
			<td align='center'><input Type='Button' Value='關閉服務' onClick='OnStopServer()' Name="StopButton"></td>
		</tr>
	</table>
	</div>
	<div id='InfoDiv'>
		<select name="listBox" id = "listBox" multiple="true"  size="25"  style="width:100%" > </select>  
	</div >	
	<div id='ListDiv'>
		<h2>&nbsp;&nbsp;&nbsp;IP列表</h2>
		<ul id='ul_IP' name='ul_IP'>
		</ul>
	</div>
</div>	
<% '整個區域 End%>
</form>
</body>
</html>