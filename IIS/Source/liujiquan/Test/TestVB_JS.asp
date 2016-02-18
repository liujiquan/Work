<%@ LANGUAGE="VBSCRIPT"%>
<SCRIPT LANGUAGE="VBSCRIPT" RUNAT="SERVER">
'====================
'Filename : WebSockClient.asp
'TitleF‘ªWebSock’Êu
'Date :2014-06-04
'Version : 1.00
'Copyright (C) AMANO Corporation 2006 - 2009
'====================
</SCRIPT>
<HTML>
<HEAD>
<TITLE>
‘ªWebSock
</TITLE>
</HEAD>
<BODY>
<%
	Set Obj = Server.CreateObject("WebSocketClientProject.IClient")
%>											
<!--
<OBJECT id="Object1"CLASSID="CLSID:C3ADF044-87E7-4169-BFD3-1530ABB46591"></OBJECT>
-->
<SCRIPT TYPE="TEXT/JAVASCRIPT">
var m_Object ;
function OnInit()
{	
	m_Object = new ActiveXObject("WebSocketClientProject.IClient"); 

}

</SCRIPT>
<INPUT Type='Button' Value='‰n‰»' onClick='OnInit()' Name="InitButton">
</BODY>
</HTML>
