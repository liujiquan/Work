//*-----------------------------------------------------------------------------*/
//* Copyright(C) 2014, liujiquan Company All rights reserved. )
//* FileName :   Gfxsock.h
//* Author   :   liujiquan
//* DateTime :   11/24/2014
//* Version  :   1.0
//* Comment  :   SocketµÄÒ»Ð©²Ù×÷
//*-----------------------------------------------------------------------------*/
#ifndef __GFXSOCK_H_DFAB4662_8771_4C0B_9DBB_6E00E60648D5__
#define __GFXSOCK_H_DFAB4662_8771_4C0B_9DBB_6E00E60648D5__
#if _MSC_VER >= 0x0400
#pragma once
#endif
#include <stdio.h>
#include <WinSock2.h>
#include <ws2tcpip.h>
#pragma comment(lib,"ws2_32.lib")

/*
MS VC++ 10.0	_MSC_VER = 1600 640
MS VC++ 9.0		_MSC_VER = 1500
MS VC++ 8.0		_MSC_VER = 1400
MS VC++ 7.1		_MSC_VER = 1310
MS VC++ 7.0		_MSC_VER = 1300	514
MS VC++ 6.0		_MSC_VER = 1200 4B0
MS VC++ 5.0		_MSC_VER = 1100 44C
*/

//////////////////////////////////////////////////////////////////////////
//Normal Function
static BOOL boolWSAInitialize = FALSE;	// boolWSAInitialize
BOOL WSAInitialize();					// WSAInitialize
void WSAUninitialize();					// WSAUninitialize
int GetSendBuf(SOCKET s);				// GetSendBuf
int GetRecvBuf(SOCKET s);				// GetRecvBuf
int BlockSocket(SOCKET s);				// BlockSocket
int UnBlockSocket(SOCKET s);			// UnBlockSocket
BOOL SetSendTimeo(SOCKET s, int time);	// SetSendTimeo
BOOL SetRecvTimeo(SOCKET s, int time);	// SetRecvTimeo
int GetRecvDataSize(SOCKET s);			// GetRecvDataSize

//////////////////////////////////////////////////////////////////////////
//Connect
#define CONNECT_TIMEO			10
#define CONMB					0		// block mode
#define CONMNB					1		// unblock mode
int Connect(SOCKET s, SOCKADDR* addr, UINT nMode = CONMB);

//////////////////////////////////////////////////////////////////////////
//Send
#define SEND_TIMEO				10		// Send TIMEO
#define SEND_OK					0		// OK				Send OK
#define SEND_LOSS				1		// LOSS				Send lost Data
#define SEND_FAIL				2		// FAIL				Send Failed
#define SEND_Retransmission		3		// Retransmission	Send Repeat 
#define SEND_RepeatMAX			4		// RepeatMAX		Send Repeat Count
int SendData_(SOCKET s, LPTSTR pBuffer, int Len, UINT& retransmissionsCount, int& SendSize);	// SendData
int SendData(SOCKET s, LPTSTR pBuffer, int nLen, int& nSendCount, UINT retransmissionsCount);
//////////////////////////////////////////////////////////////////////////
//Recv
#define RECV_TIMEO				10		// Send TIMEO
#define RECV_RepeatMAX			4		// RepeatMAX		Recv Repeat Count
#define RECV_OK					0		// OK				Recv OK
#define RECV_FAIL				1		// FAIL				Recv Failed
#define RECV_Retransmission		2		// Retransmission	Recv Repeat 
#define RECVBLOCK				0
#define RECVUNBLOCK				1
// 2015.03.03 Ver10.9.0.2 [Menu/Send Mail Failed] Start
#define REPEATMAX				5
// 2015.03.03 Ver10.9.0.2 [Menu/Send Mail Failed] End
int RecvData_(SOCKET s, LPTSTR pBuffer, int nLen, int& nRecvCount);								// RecvData
int RecvData(SOCKET s, LPTSTR pBuffer, int nLen, int& nRecvCount, UINT retransmissionsCount);
// 2015.03.03 Ver10.9.0.2 [Menu/Send Mail Failed] Start
//int receive(SOCKET s, LPSTR pszBuffer, int nLen, int nFlag = RECVUNBLOCK);
int receive(SOCKET s, LPSTR pszBuffer, int nLen, int nFlag = RECVUNBLOCK, int nRepeat = 0);
// 2015.03.03 Ver10.9.0.2 [Menu/Send Mail Failed] End
//////////////////////////////////////////////////////////////////////////
//Sock Operation Function
BOOL InitSockInfo(u_short nPort, LPCTSTR pszIP, SOCKET& sock, SOCKADDR& addr);	//Init sockInfo
BOOL InitSockInfo_(u_short nPort, LPCTSTR pszServer, SOCKET& sock, SOCKADDR& addr);	//Init sockInfo
BOOL InitSockInfo2(u_short nPort, LPCTSTR pszIP, SOCKET& sock, SOCKADDR& addr);	//Init sockInfo
void ReleaseSock(SOCKET sock);													//Release sock	

//////////////////////////////////////////////////////////////////////////
//Other Function
LPTSTR GetHostIP();						// GetHostIP
LPTSTR GetIP(LPCTSTR szHostName);
//////////////////////////////////////////////////////////////////////////
//Data Struct
#define		SDF_PREPARE			0		//Send SocketData Prepear	
#define		SDF_START			1		//Send SocketData Start
#define		SDF_NORMAL			2		//Send SocketData Normal
#define		SDF_END				3		//Send SocketData End
#define		SDSIZE		1024*10 
typedef struct _SOCKETDATA
{
	UINT flag;			// flag
	long max_len;		// max_len
	long length;		// len
	TCHAR data[SDSIZE];	// data
}SOCKETDATA, *PSOCKETDATA;

//////////////////////////////////////////////////////////////////////////
//select

#endif//__GFXSOCK_H_DFAB4662_8771_4C0B_9DBB_6E00E60648D5__
