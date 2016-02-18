//*-----------------------------------------------------------------------------*/
//* Copyright(C) 2014, liujiquan Company All rights reserved. )
//* FileName :   MailUtil.h
//* Author   :   liujiquan
//* DateTime :   11/17/2014
//* Version  :   1.0
//* Comment  :   邮件的辅助
//*-----------------------------------------------------------------------------*/
#ifndef __MAILUTIL_H_2459134951B94A1895E650CFD52F4215__
#define __MAILUTIL_H_2459134951B94A1895E650CFD52F4215__
#pragma once
#include <vector>
#include <set>
using namespace std;
#include "Gfxsock.h"
#include "Base64.h"
#include <gfxlog.h>
#include <afxtempl.h>
#include "URLEncode.h"
/************************************************************************/
/* Define                                                               */
/************************************************************************/
#define	INIFILE				".\\Setting.ini"
#define DISPLAYNAMELEN		MAX_PATH
#define EMAILADDRESSLEN		128	
#define SERVERLEN			64	
#define NAMEPWDLEN			64
#define	SEC_ACCOUNT_SIZE	"Account"
#define KET_ACCOUNT_SIZE	"AccountSize"
#define SEC_ACCOUNT			"Account%d"

#define SEC_RECVUSER_SIZE	"RecvUserSize"
#define KEY_RECVUSER_SIZE	"RecvUserSize"
#define SEC_RECVUSER		"RecvUser"
#define KEY_RECVUSER		"RecvUser%d"

#define DISPLAYNAME			"DisplayName"
#define EMAILADDRESS		"E-mail Address"
#define SENDSERVER			"SendServer"
#define RECVSERVER			"RecvServer"
#define SENDPORT			"SendPort"
#define RECVPORT			"RecvPort"
#define USERNAME			"UserName"
#define PWD					"Pwd"

#define VIEW_WID			350*2 
#define VIEW_HEI			280*2

#define SPLITCHAR			','

#define MAIL_SEPARATE_TEXT	"MAIL_SEPARATE_TEXT"
#define MAIL_SEPARATE_FILE	"MAIL_SEPARATE_FILE"
#define X_Priority			1
#define X_MSMail_Priority	"High"
#define X_Mailer			"Microsoft Outlook Express 6.00.2900.5931"
#define X_MimeOLE			"Produced By Microsoft MimeOLE V6.00.2900.6157"
#define X_INFO				"This is a multi-part message in MIME format."

#define MAIL_BEGIN "\
From: \"%s\" <%s>\r\n\
To: \"%s\" <%s>\r\n\
Cc: \"%s\" <%s>\r\n\
Bcc: \"%s\" <%s>\r\n\
Subject: %s\r\n\
Date: %s\r\n\
MIME-Version: 1.0\r\n\
Content-Type: multipart/mixed;\r\n\
	boundary=\"%s\"\r\n\
X-Priority: %d\r\n\
X-MSMail-Priority: %s\r\n\
X-Mailer: %s\r\n\
X-MimeOLE: %s\r\n\
\r\n\
%s\r\n\
\r\n\
--%s\r\n\
Content-Type: multipart/alternative;\r\n\
boundary=\"%s\"\r\n\
\r\n\
\r\n"
#define UTF8_HEADER			"=?utf-8?B?%s?="
#define MAIL_FROMTO			"From: \"%s\" <%s>\r\nTo: %s\r\n"
#define MAIL_CC				"Cc: %s\r\n"
#define MAIL_BCC			"Bcc: %s\r\n"
#define MAIL_INFO			"\
Subject: =?utf-8?B?%s?=\r\n\
Date: %s\r\n\
MIME-Version: 1.0\r\n\
X-Priority: %d\r\n\
X-MSMail-Priority: %s\r\n\
X-Mailer: %s\r\n\
X-MimeOLE: %s\r\n\r\n%s\r\n"
#define MAIL_TEXTboundary	"\
Content-Type: multipart/alternative;\r\n\
	boundary=\"%s\"\r\n"

#define ISO_8859_1			"iso-8859-1"		// ascii
#define UTF_8				"utf-8"				// utf8
#define MAIL_TEXTBegin		"--%s\r\nContent-Type: text/plain;\r\n\
	charset=\"%s\"\r\n\
Content-Transfer-Encoding: quoted-printable\r\n\r\n"
#define MAIL_TEXTBegin_HTML	"--%s\r\nContent-Type: text/html;\r\n\
	charset=\"%s\"\r\n\
Content-Transfer-Encoding: quoted-printable\r\n\r\n"
#define MAIL_TEXTOneEnd		"\r\n"
#define MAIL_TEXTEnd		"\r\n--%s--\r\n\r\n"

#define MAIL_TEXT_HTML_HEADER	"\
<HTML><HEAD>\r\n\
<META content=\"text/html; charset=utf-8\" http-equiv=Content-Type>\r\n\
<META name=GENERATOR content=\"MSHTML 9.00.8112.16421\"></HEAD>\r\n\
<BODY>\r\n\
<TABLE border=0 cellSpacing=0 cellPadding=0 width=680 align=center>\r\n\
<TBODY style=\"LINE-HEIGHT: 0px; DISPLAY: inline; FLOAT: left; HEIGHT: 0px; CLEAR: both; OVERFLOW: hidden\">\r\n"
#define MAIL_TEXT_HTML_TAIL	"</TBODY></TABLE></BODY></HTML>"

#define MAIL_OnlineText_Video	"\
<video width=\"320\" height=\"240\" controls=\"controls\" autoplay=\"autoplay\">\r\n\
	<source src=\"%s\" type=\"video/ogg\" />\r\n\
	<source src=\"%s\" type=\"video/mp4\" />\r\n\
	<source src=\"%s\" type=\"video/webm\" />\r\n\
	<object data=\"%s\" width=\"320\" height=\"240\">\r\n\
		<embed width=\"320\" height=\"240\" src=\"%s\"/>\r\n\
	</object>\r\n\
</video>\r\n"
#define MAIL_OnlineText_Audio	"\
<audio controls=\"controls\" height=\"100\" width=\"100\">\r\n\
	<source src=\"%s\" type=\"audio/mp3\" />\r\n\
	<source src=\"%s\" type=\"audio/ogg\" />\r\n\
	<embed height=\"100\" width=\"100\" src=\"%s\" />\r\n\
</audio>\r\n"
#define MAIL_OnlineText_jpeg	"<IMG src=\"%s\" type=\"image\">\r\n"

#define MAIL_HrefText	"<a href=\"%s\">%s</a>"

#define MAIL_FILEboundary	"\
Content-Type: multipart/mixed;\r\n\
	boundary=\"%s\"\r\n"

#define ContentType_Text		"text/plain"
#define ContentType_jpeg		"image/jpeg"
#define ContentType_gif			"image/gif"
#define ContentType_audio		"audio/basic"
#define ContentTYpe_video		"video/mpeg"
#define ContentType_stream		"application/octet-stream"

#define MAIL_FILEBegin	"--%s\r\n\
Content-Type: %s;\r\n\
	name=\"=?utf-8?B?%s?=\"\r\n\
Content-Transfer-Encoding: base64\r\n\
Content-Disposition: attachment;\r\n\
	filename=\"=?utf-8?B?%s?=\"\r\n\r\n"
#define MAIL_FILEOneEnd "\r\n"
#define MAIL_FILEAllENd "\r\n--%s--\r\n"

#define BASE64LEN	76
#define DATASIZE	57		// 76/4*3=57

#define LOGFILENAME		"SimpleEmail"

#define HREF_LEFT			"[href:]"		// href
#define HREF_RIGHT			"[:href]"		
#define IMG_LEFT			"[img:]"		// img
#define IMG_RIGHT			"[:img]"
#define AUDIO_LEFT			"[audio:]"		// audio
#define AUDIO_RIGHT			"[:audio]"
#define VEDIO_LEFT			"[vedio:]"		// vedio
#define VEDIO_RIGHT			"[:vedio]"
/************************************************************************/
/* Struct                                                               */
/************************************************************************/
// Account info
typedef struct tag_Account
{
	TCHAR	szDisplayName[DISPLAYNAMELEN];		// DisplayName
	TCHAR	szE_mailAddress[EMAILADDRESSLEN];	// E-mail Address
	TCHAR	szSendServer[SERVERLEN];			// SendServer
	TCHAR	szRecvServer[SERVERLEN];			// RecvServer
	SHORT	nSendPort;							// SendPort
	SHORT	nRecvPort;							// RecvPort
	TCHAR	szUserName[NAMEPWDLEN];				// UserName
	TCHAR	szPwd[NAMEPWDLEN];					// Pwd
}Account, *PAccount;
// Send File[file type]
enum FILETYPE
{
	text_plain = 0,					// text/plain
	image_jpeg = 1,					// image/jpeg
	image_gif = 2,					// image/gif
	audio = 3,						// audio/basic
	video = 4,						// video/mpeg
	application_octet_stream = 5,	// application/octet-stream
};

// Send Text[File type]
enum TEXTTYPE	
{
	TEXT_TEXT = 0,	// text
	TEXT_HREF = 1,	// href
	TEXT_IMG = 2,	// img 
	TEXT_AUDIO = 3, // audio
	TEXT_VEDIO = 4,	// vedio
};

// Send Text[Text Info]
struct TEXTINFO
{
	TEXTTYPE		nFlag;
	CString			strText;
};

/************************************************************************/
/* Function                                                             */
/************************************************************************/
int	 GetAccountSize();															// Setting.ini
BOOL SetAccountSize(int nSize = 0);												// Setting.ini
BOOL GetAccountFromIniFile(Account* PAccount, int id);							// Setting.ini
BOOL SetAccountFromIniFile(Account* pAccount, int id);							// Setting.ini
int	 GetRecivecUserSize();														// Setting.ini
int  SetRecivecUserSize(int nSize = 0);											// Setting.ini
BOOL GetRecivecUser();															// Setting.ini
BOOL SetRecivecUser();															// Setting.ini
	
SOCKET PrepareSendEmail(Account* pAccount);										// Connect Server
BOOL MailAuthLogin(SOCKET sock, Account* PAccount);								// auth login
BOOL MailFromTo(SOCKET sock, CString strFrom, CString strTo, CString strCC, CString strBCC);	// Send From TO Info
BOOL MailBegin(SOCKET sock, Account*pAccount,CString strTo, CString strCC, CString strBcc, CString strSubject, BOOL bSendText, BOOL bSendFile);		//  mail begin
BOOL MailText(SOCKET sock, CString strText);									// Send Text1
BOOL MailTextArr(SOCKET sock, CArray<TEXTINFO, TEXTINFO>& textArr);				// Send text2
BOOL MailFile(SOCKET sock, CStringArray& fileArr);								// Send File
BOOL MailEnd(SOCKET sock);														// 邮件发送结束
BOOL Compare(LPCTSTR pszBuffer, LPCTSTR pszSource);								// compare 220
CString GetCurrentTimeStr();													// time
void SetStatusInfo(LPCTSTR pszBuffer);											// statusBar info
void SetStatusInfo(CString strBuffer);											// statusBar info
void SplitString(CString strSource, CStringArray& strArr, CHAR splitChar);		// splitString
CString GetMIMEUtf8Text(CString strSource);										// 刘继全=E5=88=98=E7=BB=A7=E5=85=A8
CString GetMIMEUtf8Header(CString strSource);									// 刘继全-》5YiY57un5YWo		Subject: =?utf-8?B?5YiY57un5YWo?=
FILETYPE GetFileExt(CString strFilePath, CString& strFileName);					// Ext FIleName 
CString GetFileExtStr(CString strFilePath, CString& strFileName);				// Ext FIleName 
CString HtmlEnCodeString(CString &strEnCode, BOOL bEditFlg = FALSE);			// HtmlEnCodeString
CString ReplaceAll(CString strData, const CString &strReplace, const CString &strSearch);

#endif//__MAILUTIL_H_2459134951B94A1895E650CFD52F4215__
