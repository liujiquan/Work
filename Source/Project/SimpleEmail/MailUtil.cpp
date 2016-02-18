//*-----------------------------------------------------------------------------*/
//* Copyright(C) 2014, liujiquan Company All rights reserved. )
//* FileName :   MailUtil.cpp
//* Author   :   liujiquan
//* DateTime :   11/17/2014
//* Version  :   1.0
//* Comment  :   邮件的辅助
//*-----------------------------------------------------------------------------*/
#include "StdAfx.h"
#include "MailUtil.h"
#include "MainFrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/************************************************************************/
/* Global member                                                        */
/************************************************************************/
int				g_AccountSize = 0;		// account size
vector<Account>	g_AccountVector;		// account
int				g_UserSize = 0;			// recvUser Size
set<CString>	g_userSet;				// recvUser

// -----------------------------------------------------------//
// Function :   int		GetAccountSize
// Return   :   
// Comment  :   
// -----------------------------------------------------------//
int	GetAccountSize()
{
	return GetPrivateProfileInt(SEC_ACCOUNT_SIZE, KET_ACCOUNT_SIZE, 0, INIFILE);
}

BOOL SetAccountSize(int nSize)
{
	TCHAR szBuffer[MAX_PATH] = {0};
	sprintf(szBuffer, "%d", nSize);

	return WritePrivateProfileString(SEC_ACCOUNT_SIZE, KET_ACCOUNT_SIZE, szBuffer, INIFILE) == 0;
}

// -----------------------------------------------------------//
// Function :   GetAccountFromIniFile
// Param    :   Account* PAccount
//              int id
// Return   :   BOOL
// Comment  :   
// -----------------------------------------------------------//
BOOL GetAccountFromIniFile(Account* PAccount, int id)
{
	if(PAccount == NULL || id < 0)		return FALSE;

	TCHAR SecName[MAX_PATH] = {0};
	TCHAR szBuffer2[MAX_PATH] = {0};
	sprintf(SecName, SEC_ACCOUNT, id);
	DWORD dwRet = GetPrivateProfileSection(SecName, szBuffer2, MAX_PATH, INIFILE);
	if(dwRet == 0)						return FALSE;	
	memset(PAccount, 0x00, sizeof(Account));
	// displayname
	memset(szBuffer2, 0x00, MAX_PATH);
	if(GetPrivateProfileString(SecName, DISPLAYNAME, NULL, szBuffer2, MAX_PATH, INIFILE) == 0)	return FALSE;
	memcpy(PAccount->szDisplayName, szBuffer2, strlen(szBuffer2) > DISPLAYNAMELEN ? DISPLAYNAMELEN : strlen(szBuffer2));
	// emailaddress
	memset(szBuffer2, 0x00, MAX_PATH);
	if(GetPrivateProfileString(SecName, EMAILADDRESS, NULL, szBuffer2, MAX_PATH, INIFILE) == 0)	return FALSE;
	memcpy(PAccount->szE_mailAddress, szBuffer2, strlen(szBuffer2) > EMAILADDRESSLEN ? EMAILADDRESSLEN : strlen(szBuffer2));
	// sendserver
	memset(szBuffer2, 0x00, MAX_PATH);
	if(GetPrivateProfileString(SecName, SENDSERVER, NULL, szBuffer2, MAX_PATH, INIFILE) == 0)	return FALSE;
	memcpy(PAccount->szSendServer, szBuffer2, strlen(szBuffer2) > SERVERLEN ? SERVERLEN : strlen(szBuffer2));
	// recvserver
	memset(szBuffer2, 0x00, MAX_PATH);
	if(GetPrivateProfileString(SecName, RECVSERVER, NULL, szBuffer2, MAX_PATH, INIFILE) == 0)	return FALSE;
	memcpy(PAccount->szRecvServer, szBuffer2, strlen(szBuffer2) > SERVERLEN ? SERVERLEN : strlen(szBuffer2));
	// sendport
	if(GetPrivateProfileInt(SecName, SENDPORT, 0, INIFILE) == 0)	return FALSE;
	PAccount->nSendPort = GetPrivateProfileInt(SecName, SENDPORT, 0, INIFILE);
	// recvport
	if(GetPrivateProfileInt(SecName, RECVPORT, 0, INIFILE) == 0)	return FALSE;
	PAccount->nRecvPort = GetPrivateProfileInt(SecName, RECVPORT, 0, INIFILE);
	// username
	memset(szBuffer2, 0x00, MAX_PATH);
	if(GetPrivateProfileString(SecName, USERNAME, NULL, szBuffer2, MAX_PATH, INIFILE) == 0)	return FALSE;
	memcpy(PAccount->szUserName, szBuffer2, strlen(szBuffer2) > NAMEPWDLEN ? NAMEPWDLEN : strlen(szBuffer2));
	// pwd
	memset(szBuffer2, 0x00, MAX_PATH);
	if(GetPrivateProfileString(SecName, PWD, NULL, szBuffer2, MAX_PATH, INIFILE) == 0)	return FALSE;
	memcpy(PAccount->szPwd, szBuffer2, strlen(szBuffer2) > NAMEPWDLEN ? NAMEPWDLEN : strlen(szBuffer2));

	return TRUE;
}


// -----------------------------------------------------------//
// Function :   SetAccountFromIniFile
// Param    :   Account* pAccount
//              int id
// Return   :   BOOL
// Comment  :   
// -----------------------------------------------------------//
BOOL SetAccountFromIniFile(Account* pAccount, int id)
{
	if(pAccount == NULL || id < 0)		return FALSE;
	
	TCHAR SecName[MAX_PATH] = {0};
	TCHAR szBuffer2[MAX_PATH] = {0};
	sprintf(SecName, SEC_ACCOUNT, id);
	// displayname
	if(WritePrivateProfileString(SecName, DISPLAYNAME, pAccount->szDisplayName, INIFILE) == 0)		return FALSE;
	// emailaddress
	if(WritePrivateProfileString(SecName, EMAILADDRESS, pAccount->szE_mailAddress, INIFILE) == 0)	return FALSE;
	// sendserver
	if(WritePrivateProfileString(SecName, SENDSERVER, pAccount->szSendServer, INIFILE) == 0)		return FALSE;
	// recvserver
	if(WritePrivateProfileString(SecName, RECVSERVER, pAccount->szRecvServer, INIFILE) == 0)		return FALSE;
	// sendport
	memset(szBuffer2, 0x00, MAX_PATH);
	sprintf(szBuffer2, "%d", pAccount->nSendPort);
	if(WritePrivateProfileString(SecName, SENDPORT, szBuffer2, INIFILE) == 0)						return FALSE;
	// recvport
	memset(szBuffer2, 0x00, MAX_PATH);
	sprintf(szBuffer2, "%d", pAccount->nRecvPort);
	if(WritePrivateProfileString(SecName, RECVPORT, szBuffer2, INIFILE) == 0)						return FALSE;
	// username
	if(WritePrivateProfileString(SecName, USERNAME, pAccount->szUserName, INIFILE) == 0)			return FALSE;
	// pwd
	if(WritePrivateProfileString(SecName, PWD, pAccount->szPwd, INIFILE) == 0)						return FALSE;
	
	return TRUE;
}

// -----------------------------------------------------------//
// Function :   GetRecivecUserSize
// Return   :   
// Comment  :   
// -----------------------------------------------------------//
int	 GetRecivecUserSize()
{
	return GetPrivateProfileInt(SEC_RECVUSER_SIZE, KEY_RECVUSER_SIZE, 0, INIFILE);
}

// -----------------------------------------------------------//
// Function :   SetRecivecUserSize
// Param    :   int nSize = 0
// Return   :   int 
// Comment  :   
// -----------------------------------------------------------//
int  SetRecivecUserSize(int nSize)
{
	TCHAR szBuffer[MAX_PATH] = {0};
	sprintf(szBuffer, "%d", nSize);
	
	return WritePrivateProfileString(SEC_RECVUSER_SIZE, KEY_RECVUSER_SIZE, szBuffer, INIFILE) == 0;
}


// -----------------------------------------------------------//
// Function :   GetRecivecUser
// Return   :   BOOL
// Comment  :   
// -----------------------------------------------------------//
BOOL GetRecivecUser()
{
	int nSize = GetRecivecUserSize();
	if(nSize == 0)			return TRUE;

	TCHAR szBuffer[MAX_PATH] = {0};
	TCHAR szSecName[MAX_PATH] = {0};

	for(int i = 0; i < nSize; i++)
	{
		sprintf(szSecName, KEY_RECVUSER, i);
		if(GetPrivateProfileString(SEC_RECVUSER, szSecName, NULL, szBuffer, MAX_PATH, INIFILE) != 0)
		{
			g_userSet.insert(CString(szBuffer));
		}
	}
	
	return TRUE;
}

// -----------------------------------------------------------//
// Function :   SetRecivecUser
// Return   :   BOOL
// Comment  :   
// -----------------------------------------------------------//
BOOL SetRecivecUser()
{
	TCHAR szBuffer[MAX_PATH] = {0};
	TCHAR szKeyName[MAX_PATH] = {0};
	
	SetRecivecUserSize(g_userSet.size());	// size
	int index = 0;
	for(set<CString>::iterator it = g_userSet.begin(); it != g_userSet.end(); it++)
	{
		sprintf(szKeyName, KEY_RECVUSER, index);
		CString strValue = *it;
		WritePrivateProfileString(SEC_RECVUSER, szKeyName, strValue.GetBuffer(0), INIFILE);

		index++;
	}	

	return TRUE;
}

// -----------------------------------------------------------//
// Function :   PrepareSendEmail
// Param    :   Account* pAccount
// Return   :   SOCKET
// Comment  :   
// -----------------------------------------------------------//
SOCKET PrepareSendEmail(Account* pAccount)
{
	if(pAccount == NULL)		return	INVALID_SOCKET;

	SOCKET sock = socket(AF_INET,SOCK_STREAM,IPPROTO_IP); 
	if(sock == INVALID_SOCKET)	return  INVALID_SOCKET;
	struct hostent *pHost = gethostbyname(pAccount->szSendServer);
	if(pHost == NULL)			return	INVALID_SOCKET;

	struct sockaddr_in ServerAddr;
	ServerAddr.sin_family= AF_INET; 
	memcpy(&ServerAddr.sin_addr.S_un.S_addr, pHost->h_addr_list[0], pHost->h_length);
	ServerAddr.sin_port = htons(pAccount->nSendPort);
	
//	int nRet = connect(sock, (sockaddr*)&ServerAddr, sizeof(sockaddr));
	int nRet = Connect(sock, (sockaddr*)&ServerAddr, CONMNB);
	if(nRet == -1)		
	{
		ReleaseSock(sock);
		SetStatusInfo("connect server failed.");
		return INVALID_SOCKET;
	}
	TCHAR szRecvBuffer[MAX_PATH] = {0};
	nRet = receive(sock, szRecvBuffer, MAX_PATH);
	if(nRet == -1 || !Compare(szRecvBuffer, "220"))	
	{
		ReleaseSock(sock);
		SetStatusInfo("the configuration server cannot send a emial. please modify the account info.");
		return INVALID_SOCKET;
	}
	SetStatusInfo(szRecvBuffer);
	GfxPutLog3(LOGFILENAME, "%s", szRecvBuffer);
//	TRACE1("%s\n", szRecvBuffer);

	return sock;
}

// -----------------------------------------------------------//
// Function :   MailAuthLogin
// Param    :   SOCKET sock
//              Account* PAccount
// Return   :   BOOL
// Comment  :   
// -----------------------------------------------------------//
BOOL MailAuthLogin(SOCKET sock, Account* PAccount)
{
	if(PAccount == NULL)		return	FALSE;
	if(sock == INVALID_SOCKET)	return	FALSE;

	DWORD dwRet = 0;
	int nAuthLogin = 0;
	TCHAR szBuffer[MAX_PATH] = {0};
	TCHAR szRecvBuffer[MAX_PATH] = {0};
	
	// HELO
	sprintf(szBuffer, "HELO %s\r\n", PAccount->szSendServer);
	dwRet = send(sock, szBuffer, strlen(szBuffer), 0);
	if(receive(sock, szRecvBuffer, MAX_PATH, RECVBLOCK) == -1)		
	{
		SetStatusInfo(szBuffer);
		return FALSE;
	}
	SetStatusInfo(szRecvBuffer);
	GfxPutLog3(LOGFILENAME, "%s", szRecvBuffer);
//	TRACE1("%s\n", szRecvBuffer);
	// auth login
	memset(szRecvBuffer, 0, MAX_PATH);
	dwRet = send(sock, "auth login\r\n", strlen("auth login\r\n"), 0);
	nAuthLogin = receive(sock, szRecvBuffer, MAX_PATH, RECVBLOCK);
	GfxPutLog3(LOGFILENAME, "%s", szRecvBuffer);
//	TRACE1("%s\n", szRecvBuffer);
	if(Compare(szRecvBuffer, "334"))
	{
		
		CString strUserName = GetEncryptBase64(CString(PAccount->szUserName));
		CString strPwd = GetEncryptBase64(CString(PAccount->szPwd));
		strUserName += "\r\n";
		strPwd += "\r\n";
		// username
		dwRet = send(sock, strUserName.GetBuffer(0), strUserName.GetLength(), 0);
		memset(szRecvBuffer, 0, MAX_PATH);
		if(receive(sock, szRecvBuffer, MAX_PATH, RECVBLOCK) == -1)		
		{
			SetStatusInfo("auth login username failed. please modify the account info.");
			return FALSE;
		}
		SetStatusInfo(szRecvBuffer);
		GfxPutLog3(LOGFILENAME, "%s", szRecvBuffer);
//		TRACE1("%s\n", szRecvBuffer);
		// pwd	
		dwRet = send(sock, strPwd.GetBuffer(0), strPwd.GetLength(), 0);
		memset(szRecvBuffer, 0, MAX_PATH);
		if(receive(sock, szRecvBuffer, MAX_PATH, RECVBLOCK) == -1)	
		{
			SetStatusInfo("auth login password failed. please modify the account info.");
			return FALSE;
		}
		SetStatusInfo(szRecvBuffer);
		GfxPutLog3(LOGFILENAME, "%s", szRecvBuffer);
//		TRACE1("%s\n", szRecvBuffer);
	}

	return TRUE;
}

// -----------------------------------------------------------//
// Function :   MailFromTo
// Param    :   SOCKET sock
//              CString strFrom
//              CString strTo
//              CString strCC
//              CString strBCC
// Return   :   BOOL
// Comment  :   
// -----------------------------------------------------------//
BOOL MailFromTo(SOCKET sock, CString strFrom, CString strTo, CString strCC, CString strBCC)
{
	if(sock == INVALID_SOCKET)
	{
		SetStatusInfo("socket communication failed.");
		return FALSE;
	}
	if(strFrom.IsEmpty())		
	{
		SetStatusInfo("The user sending mail is empty. please modify the account info.");
		return FALSE;
	}
	if(strTo.IsEmpty())		
	{
		SetStatusInfo("The user recieving mail is empty. please input [To] text.");
		return FALSE;
	}

	DWORD dwRet = 0;
	CString strBuffer;
	TCHAR szRecvBuffer[MAX_PATH] = {0};
	CStringArray toArr;
	
	SplitString(strTo, toArr, SPLITCHAR);
	SplitString(strCC, toArr, SPLITCHAR);
	SplitString(strBCC, toArr, SPLITCHAR);
	// MAIL FROM
	strBuffer.Format("MAIL FROM: <%s>\r\n", strFrom);
	dwRet = send(sock, strBuffer, strBuffer.GetLength(), 0);
	if(receive(sock, szRecvBuffer, MAX_PATH, RECVBLOCK) == -1)		
	{
		SetStatusInfo(strBuffer);
		return FALSE;
	}
	SetStatusInfo(szRecvBuffer);
	GfxPutLog3(LOGFILENAME, "%s", szRecvBuffer);
//	TRACE1("%s\n", szRecvBuffer);
	// RCPT TO
	for(int i = 0; i < toArr.GetSize(); i++)
	{
		strBuffer.Format("RCPT TO: <%s>\r\n", toArr.GetAt(i));
		dwRet = send(sock, strBuffer, strBuffer.GetLength(), 0);
		memset(szRecvBuffer, 0, MAX_PATH);
		if(receive(sock, szRecvBuffer, MAX_PATH, RECVBLOCK) == -1)	
		{
			SetStatusInfo(strBuffer);
			return FALSE;
		}
		SetStatusInfo(szRecvBuffer);
		GfxPutLog3(LOGFILENAME, "%s", szRecvBuffer);
//		TRACE1("%s\n", szRecvBuffer);
	}
	
	// DATA
	strBuffer.Format("DATA\r\n", strFrom);
	dwRet = send(sock, strBuffer, strBuffer.GetLength(), 0);
	memset(szRecvBuffer, 0, MAX_PATH);
	if(receive(sock, szRecvBuffer, MAX_PATH, RECVBLOCK) == -1)		return FALSE;
	SetStatusInfo(szRecvBuffer);
	GfxPutLog3(LOGFILENAME, "%s", szRecvBuffer);
//	TRACE1("%s\n", szRecvBuffer);

	return TRUE;
}


// -----------------------------------------------------------//
// Function :   MailBegin
// Param    :   SOCKET sock
//              Account*pAccount
//              CString strTo
//              CString strCC
//              CString strBcc
//              CString strSubject
//              BOOL bSendText
//              BOOL bSendFile
// Return   :   BOOL
// Comment  :   
// -----------------------------------------------------------//
BOOL MailBegin(SOCKET sock, Account*pAccount,CString strTo, CString strCC, CString strBcc, CString strSubject, BOOL bSendText, BOOL bSendFile)
{
	if(sock == INVALID_SOCKET)
	{
		SetStatusInfo("socket communication failed.");
		return FALSE;
	}
	if(strTo.IsEmpty())		
	{
		SetStatusInfo("The user sending mail is empty. please input [To] text.");
		return FALSE;
	}
	if(pAccount == NULL)		
	{
		SetStatusInfo("account info is error. please modify account info.");
		return FALSE;
	}

	DWORD dwRet = 0;
	CString strBuffer;
	CString strTemp;
	
	// From To
	strTemp.Format(MAIL_FROMTO, pAccount->szDisplayName, pAccount->szE_mailAddress, strTo);
	strBuffer += strTemp;
	// CC
	if(!strCC.IsEmpty())
	{
		strTemp.Format(MAIL_CC, strCC);
		strBuffer += strTemp;
	}
	// BCC
	if(!strBcc.IsEmpty())
	{
		strTemp.Format(MAIL_BCC, strBcc);
		strBuffer += strTemp;
	}
	// SendFile	
	if(bSendFile)
	{
		strTemp.Format(MAIL_FILEboundary, MAIL_SEPARATE_FILE);			// File boundary
		strBuffer += strTemp;
	}
	else
	{
		strTemp.Format(MAIL_TEXTboundary, MAIL_SEPARATE_TEXT);			// text boundary
		strBuffer += strTemp;
	}
	// Info
	strTemp.Format(MAIL_INFO, 
				GetMIMEUtf8Header(strSubject),		// utf8
				GetCurrentTimeStr(),
				X_Priority,
				X_MSMail_Priority,
				X_Mailer,
				X_MimeOLE,
				X_INFO);
	strBuffer += strTemp;
	// SendText	
	if(bSendFile)
	{
		strTemp.Format("--%s\r\n", MAIL_SEPARATE_FILE);
		strBuffer += strTemp;

		strTemp.Format(MAIL_TEXTboundary, MAIL_SEPARATE_TEXT);
		strBuffer += strTemp;
	}	
	
	dwRet = send(sock, strBuffer, strBuffer.GetLength(), 0);
	GfxPutLog3(LOGFILENAME, "%s", strBuffer);
//	TRACE1("%s\n", strBuffer);
	return TRUE;
}

// -----------------------------------------------------------//
// Function :   MailText
// Param    :   SOCKET sock
//              CString strText
// Return   :   BOOL
// Comment  :   
// -----------------------------------------------------------//
BOOL MailText(SOCKET sock, CString strText)
{
	if(sock == INVALID_SOCKET)
	{
		SetStatusInfo("socket communication failed.");
		return FALSE;
	}
	
	DWORD dwRet = 0;
	CString strBuffer;
	CString strTemp;
		
	// Begin	// UTF-8
	strTemp.Format(MAIL_TEXTBegin, MAIL_SEPARATE_TEXT, UTF_8);
	strBuffer += strTemp;
	// NomalText
	strBuffer += GetMIMEUtf8Text(strText);
	strBuffer += strText;
	strTemp.Format(MAIL_TEXTEnd, MAIL_SEPARATE_TEXT);
	strBuffer += strTemp;
	// Send
	dwRet = send(sock, strBuffer, strBuffer.GetLength(), 0);
	GfxPutLog3(LOGFILENAME, "%s", strBuffer);
//	TRACE1("%s", strBuffer);

	return TRUE;
}

// -----------------------------------------------------------//
// Function :   MailTextArr
// Param    :   SOCKET sock
//              CArray<TEXTINFO
//              TEXTINFO>& textArr
// Return   :   BOOL
// Comment  :   
// -----------------------------------------------------------//
BOOL MailTextArr(SOCKET sock, CArray<TEXTINFO, TEXTINFO>& textArr)
{
	if(sock == INVALID_SOCKET)
	{
		SetStatusInfo("socket communication failed.");
		return FALSE;
	}
	
	DWORD dwRet = 0;
	CString strBuffer;
	CString strTemp;
	TEXTINFO textInfo;
	
	// Begin	
	strTemp.Format(MAIL_TEXTBegin_HTML, MAIL_SEPARATE_TEXT, UTF_8);
	// HTML Header
	strTemp += MAIL_TEXT_HTML_HEADER;
	strBuffer += strTemp;
//	TRACE1("%s", strTemp);
	for(int i = 0; i < textArr.GetSize(); i++)
	{
		strTemp = "";
		textInfo = textArr.GetAt(i);
		textInfo.strText = HtmlEnCodeString(textInfo.strText);
		if(textInfo.nFlag == TEXT_TEXT)
		{
			// NomalText
			strTemp = GetMIMEUtf8Text(textInfo.strText);
		}
		else if(textInfo.nFlag == TEXT_HREF)		// href
		{
			strTemp.Format(MAIL_HrefText, GetMIMEUtf8Text(textInfo.strText), GetMIMEUtf8Text(textInfo.strText));
		}
		else if(textInfo.nFlag == TEXT_IMG)			// img
		{
			strTemp.Format(MAIL_OnlineText_jpeg, GetMIMEUtf8Text(textInfo.strText));
		}
		else if(textInfo.nFlag == TEXT_AUDIO)		// audio
		{
			strTemp.Format(MAIL_OnlineText_Audio,	GetMIMEUtf8Text(textInfo.strText),
													GetMIMEUtf8Text(textInfo.strText),
													GetMIMEUtf8Text(textInfo.strText));
		}
		else if(textInfo.nFlag == TEXT_VEDIO)		// vedio
		{
			strTemp.Format(MAIL_OnlineText_Video,	GetMIMEUtf8Text(textInfo.strText),
													GetMIMEUtf8Text(textInfo.strText),
													GetMIMEUtf8Text(textInfo.strText),
													GetMIMEUtf8Text(textInfo.strText),
													GetMIMEUtf8Text(textInfo.strText));
		}
//		TRACE1("%s", strTemp);
		strBuffer += strTemp;
	}
	// HTML Tail
	strTemp = MAIL_TEXT_HTML_TAIL;
//	TRACE1("%s", strTemp);
	strBuffer += strTemp;
	// end
	strTemp.Format(MAIL_TEXTEnd, MAIL_SEPARATE_TEXT);
//	TRACE1("%s", strTemp);
	strBuffer += strTemp;
	// Send
	dwRet = send(sock, strBuffer, strBuffer.GetLength(), 0);
	GfxPutLog3(LOGFILENAME, "%s", strBuffer);
	
	return TRUE;
}

// -----------------------------------------------------------//
// Function :   MailFile
// Param    :   SOCKET sock
//              CStringArray& fileArr
// Return   :   BOOL
// Comment  :   
// -----------------------------------------------------------//
BOOL MailFile(SOCKET sock, CStringArray& fileArr)
{
	if(sock == INVALID_SOCKET)
	{
		SetStatusInfo("socket communication failed.");
		return FALSE;
	}
	if(fileArr.GetSize() == 0)		return	FALSE;

	DWORD dwRet = 0;
	CString strBuffer;
	CString strTemp;
	
	for(int i = 0; i < fileArr.GetSize(); i++)
	{
		CString strFilePath = fileArr.GetAt(i);
		CString strFileName;												// fileName
		CString strFileType = GetFileExtStr(strFilePath, strFileName);		// filetype
		// Begin
		strTemp.Format(MAIL_FILEBegin, MAIL_SEPARATE_FILE, strFileType, GetMIMEUtf8Header(strFileName), GetMIMEUtf8Header(strFileName));
		dwRet = send(sock, strTemp, strTemp.GetLength(), 0);
		GfxPutLog3(LOGFILENAME, "%s", strTemp);
//		TRACE1("%s", strTemp);
		// Text	
		FILE *pFile = fopen(strFilePath.GetBuffer(0), "rb");
		if(pFile)
		{
			TCHAR szData[DATASIZE] = {0};
			TCHAR szBase64Data[BASE64LEN+2+1] = {0};
			int nRead = 0;
			int nBase64Size = 0;
			nRead = fread(szData, 1, DATASIZE, pFile);
			while(nRead > 0)
			{
				memset(szBase64Data, 0x00, BASE64LEN);
				EncryptBase64(szBase64Data, szData, nRead);
				nBase64Size = nRead*4/3;
				szBase64Data[nBase64Size]	= '\r';
				szBase64Data[nBase64Size+1]	= '\n';
				szBase64Data[nBase64Size+2]	= '\0';
				dwRet = send(sock, szBase64Data, nBase64Size + 2 , 0);
//				GfxPutLog3(LOGFILENAME, "%s", szBase64Data);
////				TRACE1("%s", szBase64Data);
				memset(szData, 0x00, DATASIZE);
				nRead = fread(szData, 1, DATASIZE, pFile);
				DWORD dwError = GetLastError();
			}
			fclose(pFile);
		}
		// OneEnd
		strTemp.Format(MAIL_FILEOneEnd, MAIL_SEPARATE_FILE);
		dwRet = send(sock, strTemp, strTemp.GetLength(), 0);
		GfxPutLog3(LOGFILENAME, "%s", strTemp);
//		TRACE1("%s", strTemp);
	}
	// End
	strTemp.Format(MAIL_FILEAllENd, MAIL_SEPARATE_FILE);
	dwRet = send(sock, strTemp, strTemp.GetLength(), 0);
	GfxPutLog3(LOGFILENAME, "%s", strTemp);
//	TRACE1("%s", strTemp);

	return TRUE;
}

// -----------------------------------------------------------//
// Function :   MailEnd
// Param    :   SOCKET sock
// Return   :   BOOL
// Comment  :   邮件发送结束
// -----------------------------------------------------------//
BOOL MailEnd(SOCKET sock)
{
	if(sock == INVALID_SOCKET)
	{
		SetStatusInfo("socket communication failed.");
		return FALSE;
	}
	
	DWORD dwRet = 0;
	TCHAR szRecvBuffer[MAX_PATH] = {0};
	
	// .\r\n
	dwRet = send(sock, ".\r\n", strlen(".\r\n"), 0);
	if(receive(sock, szRecvBuffer, MAX_PATH, RECVBLOCK) == -1)		
	{
		SetStatusInfo("send .\r\n failed.");
		return FALSE;
	}
	SetStatusInfo(szRecvBuffer);
	GfxPutLog3(LOGFILENAME, "%s", szRecvBuffer);
//	TRACE1("%s\n", szRecvBuffer);
	// QUIT
	dwRet = send(sock, "QUIT\r\n", strlen("QUIT\r\n"), 0);
	if(receive(sock, szRecvBuffer, MAX_PATH, RECVBLOCK) == -1)	
	{
		SetStatusInfo("QUIT failed.");
		return FALSE;
	}
	SetStatusInfo(szRecvBuffer);
	GfxPutLog3(LOGFILENAME, "%s", szRecvBuffer);
//	TRACE1("%s\n", szRecvBuffer);

	return TRUE;
}

// -----------------------------------------------------------//
// Function :   Compare
// Param    :   LPCTSTR pszBuffer
//              LPCTSTR pszSource
// Return   :   BOOL
// Comment  :   Compare
// -----------------------------------------------------------//
BOOL Compare(LPCTSTR pszBuffer, LPCTSTR pszSource)
{
	int nLen = strlen(pszSource);
	int nLen2 = strlen(pszBuffer);
	if(nLen2 == 0 || nLen == 0)		return FALSE;
	if(nLen2 < nLen)				return FALSE;

	while(nLen-- != 0)
	{
		if(pszSource[nLen] != pszBuffer[nLen])	return FALSE;
	}

	return TRUE;
}

// -----------------------------------------------------------//
// Function :   GetCurrentTimeStr
// Return   :   CString
// Comment  :   
// -----------------------------------------------------------//
CString GetCurrentTimeStr()
{
	CString strTemp;

	CTime tm = CTime::GetCurrentTime();
	strTemp.Format("%04d/%02d/%02d %02d:%02d:%02d",	tm.GetYear(), tm.GetMonth(), tm.GetDay(), tm.GetHour(), tm.GetMinute(), tm.GetSecond());

	return strTemp;
}

// -----------------------------------------------------------//
// Function :   SetStatusInfo
// Param    :   LPCTSTR pszBuffer
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void SetStatusInfo(LPCTSTR pszBuffer)
{
	CMainFrame* pMainFrame = ((CMainFrame*)AfxGetMainWnd());
	if(pMainFrame)
		pMainFrame->m_wndStatusBar.SetInfo(pszBuffer);
}

// -----------------------------------------------------------//
// Function :   SetStatusInfo
// Param    :   CString strBuffer
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void SetStatusInfo(CString strBuffer)
{
	SetStatusInfo(strBuffer.GetBuffer(0));
}

// -----------------------------------------------------------//
// Function :   SplitString
// Param    :   CString strSource
//              CStringArray& strArr
//              CHAR splitChar
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void SplitString(CString strSource, CStringArray& strArr, CHAR splitChar)
{
	TCHAR szBuffer[MAX_PATH] = {0};
	if(strSource.IsEmpty())			return;
	char* pSource = strSource.GetBuffer(0);
	char* pTemp = strchr(pSource, splitChar);
	
	while(pTemp)
	{
		memset(szBuffer, 0x00, MAX_PATH);
		memcpy(szBuffer, pSource, pTemp - pSource);
		CString str(szBuffer);
		strArr.Add(str);
		
		pSource = pTemp + 1;
		pTemp = strchr(pSource, splitChar);
	}

	strArr.Add(CString(pSource));
}

// -----------------------------------------------------------//
// Function :   GetMIMEUtf8Text
// Param    :   CString strSource
// Return   :   CString
// Comment  :   ???=E5=88=98=E7=BB=A7=E5=85=A8
// -----------------------------------------------------------//
CString GetMIMEUtf8Text(CString strSource)
{
	if(strSource.IsEmpty())			return "";

	return Encode(strSource, TRUE, ENCODE_MIME);
}

// -----------------------------------------------------------//
// Function :   GetMIMEUtf8Header
// Param    :   CString strSource
// Return   :   CString
// Comment  :   ???-?5YiY57un5YWo		Subject: =?utf-8?B?5YiY57un5YWo?=
// -----------------------------------------------------------//
CString GetMIMEUtf8Header(CString strSource)
{
	if(strSource.IsEmpty())			return "";
	
	CString strTemp;
	strTemp = UTF8TOASCII(strSource.GetBuffer(0));		// ASCII -?UTF-8
	strTemp = GetEncryptBase64(strTemp);				// BASE64

	return strTemp;
}

// -----------------------------------------------------------//
// Function :   GetFileExt
// Param    :   CString strFilePath
//              CString& strFileName
// Return   :   FILETYPE
// Comment  :   
// -----------------------------------------------------------//
FILETYPE GetFileExt(CString strFilePath, CString& strFileName)
{
	if(strFilePath.IsEmpty())		return application_octet_stream;
	
	CString extName;
	int index = strFilePath.ReverseFind('\\');
	if(index == -1)	
	{
		index = strFilePath.ReverseFind('/');
	}
	if(index == -1)					return application_octet_stream;
	
	strFileName = strFilePath.Right(strFilePath.GetLength() - index - 1);
	if(strFileName.IsEmpty())		return application_octet_stream;

	index = strFileName.ReverseFind('.');
	if(index == -1)					return application_octet_stream;

	extName = strFileName.Right(strFileName.GetLength() - index);
	if(extName.IsEmpty())			return application_octet_stream;

	extName.MakeUpper();		// MakeUpper
	if(extName == ".TXT")			return text_plain;
	else if(extName == ".JPG")		return image_jpeg;
	else if(extName == ".GIF")		return image_gif;
	else if(extName == ".WAV" || extName == ".MP3" || extName == ".AIF" || extName == ".RM" )	
	{
		return audio;
	}
	else if(extName == ".MPEG" || extName == ".MPG"  || extName == ".MKV"   || 
			extName == ".DAT"  || extName == ".AVI"  || extName == ".MOV"   || 
			extName == ".ASF"  || extName == ".WMV"  || extName == ".NAVI"  || 
			extName == ".3GP"  || extName == ".REAL" || extName == ".VIDEO" || 
			extName == ".RMVB" )
	{
		return video;
	}

	return application_octet_stream;
}

// -----------------------------------------------------------//
// Function :   GetFileExtStr
// Param    :   CString strFilePath
//              CString& strFileName
// Return   :   CString 
// Comment  :   
// -----------------------------------------------------------//
CString  GetFileExtStr(CString strFilePath, CString& strFileName)
{
	FILETYPE type = GetFileExt(strFilePath, strFileName);
	switch(type)
	{
	case text_plain:				return "text/plain";
		break;
	case image_jpeg:				return "image/jpeg";
		break;
	case image_gif:					return "image/gif";
		break;
	case audio:						return "audio/basic";
		break;
	case video:						return "video/mpeg";
		break;
	case application_octet_stream:	return "application/octet-stream";
		break;
	}

	return "application/octet-stream";
}

// -----------------------------------------------------------//
// Function :   HtmlEnCodeString
// Param    :   CString &strEnCode
//              BOOL bEditFlg /*= FALSE*/
// Return   :   CString
// Comment  :   
// -----------------------------------------------------------//
CString HtmlEnCodeString(CString &strEnCode, BOOL bEditFlg /*= FALSE*/)
{
	CString strTemp = strEnCode;
	strTemp = ReplaceAll(strTemp, _T("&amp;"), _T("&"));
	strTemp = ReplaceAll(strTemp, _T("&lt;"), _T("<"));
	strTemp = ReplaceAll(strTemp, _T("&gt;"), _T(">"));
	strTemp = ReplaceAll(strTemp, _T("&quot;"), _T("\""));
	strTemp = ReplaceAll(strTemp, _T("&#39;"), _T("\'"));
	if (bEditFlg == FALSE)
	{
		strTemp = ReplaceAll(strTemp, _T("&nbsp;"), _T(" "));
	}
	
	return strTemp;
}

// -----------------------------------------------------------//
// Function :   ReplaceAll
// Param    :   CString strData
//              const CString &strReplace
//              const CString &strSearch
// Return   :   CString
// Comment  :   
// -----------------------------------------------------------//
CString ReplaceAll(CString strData, const CString &strReplace, const CString &strSearch)
{
	CString strTemp = strData;
	CString strChangeData;
	int nIndex = 0;
	int nPos = 0;
	strChangeData.Empty();
	
	while ((nPos = strTemp.Find(strSearch)) != -1)
	{
		CString strHead, strTail;
		strHead = strTemp.Left(nPos);
		strTail = strTemp.Right(strTemp.GetLength() - nPos - strSearch.GetLength());
		strChangeData += (strHead + strReplace);
		strTemp = strTail;
	}
	strChangeData += strTemp;
	return strChangeData;
}