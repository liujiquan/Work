<%@ language="vbscript" %>
<script language="vbscript" runat="server">
'====================
'Filename : Xaw1300.asp
'Title : エラーデータ一覧
'Date : 2014-05-30
'Version : 7.20
'Copyright(C) AMANO Business Solutions Corporation. All Rights Reserved.
'====================
</script>
<%
Dim a, b ,obj
a=Request.TotalBytes
b=Request.BinaryRead(a)
set obj =server.createobject("Basp21")
name=obj.Form(b,"yourname")
f1=obj.FormFileName(b,"file1")
f2=obj.FormFileName(b,"file2")
fsize1=obj.FormFileSize(b,"file1")
fsize2=obj.FormFileSize(b,"file2")
newf1=Mid(f1,InstrRev(f1,"\")+1)
newf2=Mid(f2,InstrRev(f2,"\")+1)
l1=obj.FormSaveAs(b,"file1","d:\temp\log\" & newf1)
l2=obj.FormSaveAs(b,"file2","d:\temp\log\" & newf2)
%>
<HTML><HEAD><TITLE>File Upload Test</TITLE>
<BODY>
<H1>Testing</H1>
<BR>
Dear <%= name %>; Your file has been uploaded<BR>
file1= <%= newf1 %><BR>
file2= <%= newf2 %><BR>
len1= <%= l1 %><BR>
len2= <%= l2 %><BR>
</BODY></HTML>
