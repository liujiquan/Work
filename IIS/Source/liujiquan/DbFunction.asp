<%
'/**************************************************************/
'/* DataSource操作
'/**************************************************************/

const DB_ConnectString = ""
const DB_Timeout = 30
const DB_Dsn = "liujiquan"
const DB_User = "amano_getuser"
const DB_PWD = "amano_getuser"

'---- CursorTypeEnum Values ----
Const adOpenForwardOnly = 0
Const adOpenKeyset = 1
Const adOpenDynamic = 2
Const adOpenStatic = 3
'---- LockTypeEnum Values ----
Const adLockReadOnly = 1
Const adLockPessimistic = 2
Const adLockOptimistic = 3
Const adLockBatchOptimistic = 4
'---- CommandTypeEnum Values ----
Const adCmdUnknown = 0
Const adCmdText = &H0001
Const adCmdTable = &H0002
Const adCmdStoredProc = &H0004

' Database Connect
Function DBConnect()
	Dim Conn
	Set Conn = CreateObject("ADODB.Connection")
	Conn.ConnectionString = DB_ConnectString
	Conn.ConnectionTimeout = DB_Timeout
	
	On Error Resume Next		' 出現錯誤依然執行下面Code
	Conn.Open DB_Dsn ,DB_User, DB_PWD
	On Error Goto 0				' 出現錯誤顯示錯誤信息 並且停止運行
	
	Set DBConnect = Conn
	Set Conn = Nothing
End Function

' Database DisConnect
Function DBDisconnect(conn)
	Set conn = Nothing
End Function

' RecordSet Open
Function DBOpen(Conn, strSQL)

	Set RecordSet = CreateObject("ADODB.Recordset")
	RecordSet.CursorType = adOpenStatic
	RecordSet.LockType = adLockReadOnly
	
	On Error Resume Next
	RecordSet.Open strSQL, Conn, , , adCmdText
	On Error Goto 0
	Set DBOpen = RecordSet
	Set RecordSet = Nothing
End Function

' RecordSet Update
Function DBUpdate(Conn, strSQL)

	Set RecordSet = CreateObject("ADDODB.Recordset")
	RecordSet.CursorType = adOpenDynamic
	RecordSet.LockType = adLockOptimistic
	
	On Error Resume Next
	RecordSet.Open strSQL, Conn, , , adCmdText
	On Error Goto 0
	Set DBUpdate = RecordSet
End Function

' DataBase Error
Function	DBError(Conn)
	Dim error, msg		'
	msg = ""
	For	Each error In Conn.Errors
		If error.Number <> 0 Then
			msg		= msg & error.Description & ";"
		End	If
	Next
	If msg = "" Then
		If Err.Number <> 0 Then
			msg = msg & Err.description
		End If
	End If
	DBError = msg
End	Function
%>