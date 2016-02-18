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
<!-- <OBJECT id="m_Object" CLASSID="CLSID:444E4C4D-ABF9-40E5-97DC-A1E10D55F157"></OBJECT> -->
<script type="text/javascript">
//var m_Object = Object;
var m_listInfo;
var m_radiolist;
//FunctionID
var AddMsgID = 0;
var AddIPID = 1;
var DeleteIPID = 2;
var ClearIPID = 3;
function window_load()
{
	//ATL
	m_Object = new ActiveXObject("WebSocketClientProject.IClient"); 
	m_Object.SetJsCallbackFunc(AddString, AddMsgID);
	m_Object.SetJsCallbackFunc(OnAddIP, AddIPID);
	m_Object.SetJsCallbackFunc(OnDeleteIP, DeleteIPID);
	m_Object.SetJsCallbackFunc(OnClear, ClearIPID);
	//Info
	m_listInfo = new CListBox(document.form_Client.listBox);
	//RadioList
	var radioDiv = document.getElementById("radioDiv");
	m_radiolist = new CRadiolist(radioDiv,"radio_g"); 
}

function window_unload()
{
	OnClose();
}

//Connect
function OnConnect()
{
	m_Object.OnConnect();
}

//寫
function OnSendData()
{	
	var value = document.form_Client.SendDataText.value;
	var radioGroup = document.getElementsByName("radio_g");
	var sock, pszIP;
	for( var i = 0; i < radioGroup.length; i++)
	{
		if(radioGroup[i].checked)
		{
			sock = Number(radioGroup[i].id);
			pszIP = radioGroup[i].value;
			m_Object.OnSendData(sock, pszIP, value);
			break;
		}
	}
	
}

//Close
function OnClose()
{
	m_Object.OnDisconnect();
	OnClear();
}
//添加信息
function AddString(str)
{
	m_listInfo.addString(str);
}
//添加IP
function OnAddIP(sock, pszIP)
{
	m_radiolist.add(sock ,pszIP); 
}
//刪除IP
function OnDeleteIP(sock, pszIP)
{
	m_radiolist.delete_(sock ,pszIP); 
}
//清空
function OnClear()
{
	m_radiolist.clear();
}
</SCRIPT>  
<body  onload="window_load();" id='background' onunload='window_unload'>
<form name="form_Client" method="post">
<% '整個區域 Start%>
<div id='container'>
	<div id='InfoDiv_Client' >
		<select  name="listBox" id = "listBox" multiple="true"  size="25" style="width:100%;">
		</select> 
	</div >	
	<div id='ButtonDiv_Client'>
	<table width='100%'>
		<tr><td ><input Type='Button' Value='Connect' onClick='OnConnect()' Name="ConnectBtn"></td> </tr>
		<tr><td ><input Type='Button' Value='Close' onClick='OnClose()' Name="CloseBtn"></td></tr>
	</table>
	</div>
	<div id='ListDiv_Client'>
		<h2>&nbsp;IP列表</h2>
		<div style="width:100%; height:100%;" id='radioDiv'>
		</div>
	</div>
	<div id='SendDataDiv_Client'>
		<input class='input_Text' Type='text' Value=''  Name="SendDataText">
		<input class='input_Button' Type='Button' Value='SendData' onClick='OnSendData()' Name="SendDataBtn" >
		<input class='input_Button' Type='Button' Value='SendData' onClick='OnClear()' Name="SendDataBtn" >
	</div>
</div>	
<% '整個區域 End%>

</form>
</body>
</html>