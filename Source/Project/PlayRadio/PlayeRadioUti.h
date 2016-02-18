//*-----------------------------------------------------------------------------*/
//* Copyright(C) 2014, liujiquan Company All rights reserved. )
//* FileName :   PlayeRadioUti.h
//* Author   :   liujiquan
//* DateTime :   11/5/2014
//* Version  :   1.0
//* Comment  :   
//*-----------------------------------------------------------------------------*/
#ifndef __PLAYERADIOUTI_H_2459134951B94A1895E650CFD52F4215__
#define __PLAYERADIOUTI_H_2459134951B94A1895E650CFD52F4215__
#pragma once
#include <afx.h>
/************************************************************************/
/* Define                                                                     */
/************************************************************************/
#define DEFAULT_PORT	80
#ifndef u_short
typedef unsigned short  u_short;
#endif
/************************************************************************/
/* Define                                                                     */
/************************************************************************/
#define REQUEST_STATUS_200			200						// HTTP/1.1 200 OK
#define REQUEST_STATUS_OK			REQUEST_STATUS_200		// HTTP/1.1 200 OK
#define REQUEST_STATUS_400			400
#define REQUEST_STATUS_FAILED		REQUEST_STATUS_400

#define REQUEST_CONTENTTYPE_video	100						// video/x-msvideo	

/************************************************************************/
/* struct                                                                     */
/************************************************************************/
typedef struct REQUESTINFO
{
	DWORD	dwStatus;			// : HTTP/1.1 200 OK
	DWORD	Content_Type;		// : Content-Type: video/x-msvideo
	DWORD64	Last_Modified;		// : Sun, 10 Jun 2012 06:36:40 GMT
	DWORD	Accept_Ranges;		// : bytes
	DWORD	ETag;				// : "0c6564d346cd1:0"
	DWORD	Server;				// : Microsoft-IIS/7.5
	DWORD	X_Powered_By;		// : ASP.NET
	DWORD	X_UA_Compatible;	// : IE=5
	DWORD64 Date;				// : Wed, 05 Nov 2014 06:43:01 GMT
	DWORD	Connection;			// : close
	DWORD	Content_Length;		// : 53175428
	DWORD   dwHeaderLen;		// : HEADER len /r/n/r/n End
}REQUESTINFO, *PREQUESTINFO;

/************************************************************************/
/* Function                                                                     */
/************************************************************************/
void randomize_guid(unsigned char *buf);
unsigned char* randomizeGuid();
BOOL AnalyzeUrl(LPCTSTR szUrl, LPSTR pszServerName, LPSTR pszFileName, u_short& nPort);
BOOL AnalyzePacket(LPCTSTR szBuffer, PREQUESTINFO pRequestInfo);

#endif//__PLAYERADIOUTI_H_2459134951B94A1895E650CFD52F4215__

