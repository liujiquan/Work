<%@ LANGUAGE="VBSCRIPT"%>
<SCRIPT LANGUAGE="VBSCRIPT" RUNAT="SERVER">
'====================
'Filename : WebSockClient.asp
'TitleÅFë™ééWebSockí êu
'Date :2014-06-04
'Version : 1.00
'Copyright (C) AMANO Corporation 2006 - 2009
'====================
</SCRIPT>
<HTML>
<HEAD>
<TITLE>
ë™ééWebSock
</TITLE>
</HEAD>
<BODY>
<%
'	Set Obj = Server.CreateObject("WebSockClient.WebSockClient")
'	obj.OnInit()
%>											
<!--
<OBJECT id="Object1"CLASSID="CLSID:C3ADF044-87E7-4169-BFD3-1530ABB46591"></OBJECT>
-->
<SCRIPT TYPE="TEXT/JAVASCRIPT">
var m_Object ;
function OnInit()
{	
	m_Object = new ActiveXObject("WebSockClient2.WebSockClient2C.1"); 
	try
	{
		m_Object.OnInit();
	}catch(e)
	{
	}
}
function OnConnect()
{
	try
	{
		m_Object.OnConnect();
	}catch(e)
	{
	}
}
</SCRIPT>
<INPUT Type='Button' Value='èâénâª' onClick='OnInit()' Name="InitButton">
<INPUT Type='Button' Value='Connect' onClick='OnConnect()' Name="ConnectButton">
</BODY>
</HTML>
