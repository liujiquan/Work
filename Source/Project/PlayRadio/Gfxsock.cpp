#include "Gfxsock.h"
//#include "GfxLog.h"
#ifdef _DEBUG
#undef THIS_FILE
#define static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
// Normal Function
//----------------------------------------------------------------------------//
// Function:	WSAInitialize
// Param   :	
// meaning :	WSAInitialize
//-----------------------------------------------------------
BOOL WSAInitialize()					
{	
	if(boolWSAInitialize == FALSE)
	{
		WSADATA wsadata;
		if(WSAStartup(MAKEWORD(2,2),&wsadata) !=0)
		{
			return FALSE;
		}
		boolWSAInitialize = TRUE;
	}
	return TRUE;
}
   
//-----------------------------------------------------------//
// Function:    WSAUninitialize()
// Param                
// Return  :    void
// meaning :	WSAUninitialize
//-----------------------------------------------------------//
void WSAUninitialize()
{
	if(boolWSAInitialize)
	{
		WSACleanup();
		boolWSAInitialize = FALSE;
	}
}

//-----------------------------------------------------------//
// Function:    GetSendBuf()
// Param        SOCKET        s
// Return  :    int
// meaning :	GetSendBuf
//-----------------------------------------------------------//
int GetSendBuf(SOCKET s)
{
	int nSize = 0;
	int len = sizeof(nSize);
	int nRet = getsockopt(s, SOL_SOCKET, SO_SNDBUF, (char*)&nSize, &len);
	if(nRet == 0)
	{
		return nSize;
	}
	return 0;
}

//-----------------------------------------------------------//
// Function:    GetRecvBuf()
// Param        SOCKET        s
// Return  :    int
// meaning :    GetRecvBuf
//-----------------------------------------------------------//
int GetRecvBuf(SOCKET s)
{
	int nSize = 0;
	int len = sizeof(nSize);
	int nRet = getsockopt(s, SOL_SOCKET, SO_RCVBUF, (char*)&nSize, &len);
	if(nRet == 0)
	{
		return nSize;
	}
	return 0;
}

//-----------------------------------------------------------//
// Function:    BlockSocket()
// Param        SOCKET        s
// Return  :    int
// meaning :    BlockSocket
//-----------------------------------------------------------//
int BlockSocket(SOCKET s)
{
	u_long l = 0L;
	return ioctlsocket(s, FIONBIO, &l);
}

//-----------------------------------------------------------//
// Function:    UnBlockSocket()
// Param        SOCKET        s
// Return  :    int
// meaning :    UnBlockSocket
//-----------------------------------------------------------//
int UnBlockSocket(SOCKET s)
{
	u_long l = 1L;
	return ioctlsocket(s, FIONBIO, &l);
}

//-----------------------------------------------------------//
// Function:    SetSendTimeo()
// Param        SOCKET        s
//              int        time
// Return  :    BOOL
// meaning :    SetSendTimeo
//-----------------------------------------------------------//
BOOL SetSendTimeo(SOCKET s, int time)
{
	int nRet = setsockopt(s, SOL_SOCKET, SO_SNDTIMEO,(char*)&time, sizeof(int));
	return nRet == 0 ? TRUE : FALSE;
}

//-----------------------------------------------------------//
// Function:    SetRecvTimeo()
// Param        SOCKET        s
//              int        time
// Return  :    BOOL
// meaning :    SetRecvTimeo
//-----------------------------------------------------------//
BOOL SetRecvTimeo(SOCKET s, int time)
{	
	int nRet = setsockopt(s, SOL_SOCKET, SO_RCVTIMEO,(char*)&time, sizeof(int));
	return nRet == 0 ? TRUE : FALSE;
}

//-----------------------------------------------------------//
// Function:    GetRecvDataSize
// Param        SOCKET        s
// Return  :    int
// meaning :    GetRecvDataSize
//-----------------------------------------------------------//
int GetRecvDataSize(SOCKET s)
{
	u_long ul = 0;
	if(ioctlsocket(s, FIONREAD, &ul) == 0)
	{
		return ul;
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////
//Connect
//-----------------------------------------------------------//
// Function:    connect
// Param        SOCKET        s
//              SOCKADDR      &addr
//              UINT          nMode
// Return  :    int 
// meaning :    connect server
//-----------------------------------------------------------//
int Connect(SOCKET s, SOCKADDR* addr, UINT nMode /*= CONMB*/ )
{
	if(nMode == CONMB)
	{	
		BlockSocket(s);
		return connect(s, addr, sizeof(SOCKADDR));
	}
	else if(nMode == CONMNB)
	{
		UnBlockSocket(s);
		int nRet1, nRet;
		nRet1 = connect(s, addr, sizeof(SOCKADDR));	
		if(nRet1 == SOCKET_ERROR)
		{
			DWORD dwRet = WSAGetLastError();
			if(dwRet == WSAEWOULDBLOCK)
			{
				TIMEVAL timeo;
				timeo.tv_sec = 0;
				timeo.tv_usec = CONNECT_TIMEO;
				fd_set fd;
				FD_ZERO(&fd);
				FD_SET(s, &fd);
				nRet1 =  select(s+1, NULL, &fd, NULL, &timeo);
				if(nRet1 == 1)
				{
					nRet = 0;
				}
				else if(nRet1 == 0 || nRet1 == SOCKET_ERROR)
				{
					nRet = SOCKET_ERROR;
				}
				FD_CLR(s, &fd);
			}
		}
		BlockSocket(s);
		return nRet;
	}

	return -1;
}


//////////////////////////////////////////////////////////////////////////
//Send
//-----------------------------------------------------------//
// Function:    SendData_
// Param        SOCKET        s
//              LPTSTR        pBuffer
//              int			  Len
//              UINT&         retransmissionsCount
//              int&          SendSize
// Return  :    int
// meaning :	SendData_ 
//-----------------------------------------------------------//
int SendData_(SOCKET s, LPTSTR pBuffer, int Len, UINT& retransmissionsCount, int& SendSize)
{
	retransmissionsCount = 0;		// Repeat Send Number
	int nSendRet = 0;				// Send 返回
	LPTSTR pBufferTemp = pBuffer;	// Data
	int nSendCount = Len;			// Len
	int nRetSendCount = 0;			// Success Send Size
	SendSize = 0;
	while(TRUE)
	{
		nSendRet = SendData(s, pBufferTemp, nSendCount, nRetSendCount, retransmissionsCount);
		if(nSendRet == SEND_OK)
		{
			SendSize += nRetSendCount;
			break;
		}
		else if(nSendRet == SEND_FAIL)
		{
			retransmissionsCount++;
		}
		else if(nSendRet == SEND_LOSS)
		{
			pBuffer = pBuffer + nRetSendCount;
			nSendCount = nSendCount - nRetSendCount;

			SendSize += nRetSendCount;
			retransmissionsCount++;
		}
		else if(nSendRet == SEND_Retransmission)
		{
			break;
		}
	}
//	GfxPutLog3("Client","%d/%d", SendSize, Len);
	return nSendRet;
}
      
//-----------------------------------------------------------//
// Function:    SendData
// Param        SOCKET        s
//              LPTSTR        pBuffer
//              int           nLen
//              int&          nSendCount
//              UINT          retransmissionsCount
// Return  :    int
// meaning :    發送data
//-----------------------------------------------------------//
int SendData(SOCKET s, LPTSTR pBuffer, int nLen, int& nSendCount, UINT retransmissionsCount)
{
	if(retransmissionsCount == SEND_RepeatMAX)		//Send Retransmission
	{
		return SEND_Retransmission;
	}
	nSendCount = send(s, pBuffer, nLen, 0);
	if(nSendCount == nLen)							//Send Success
	{
		return SEND_OK;
	}
	else if(nSendCount == -1)						//Send Failed
	{
		nSendCount = 0; 
		return SEND_FAIL;
	}
	else if(nSendCount >= 0 && nSendCount < nLen)	//Send Loss
	{
		return SEND_LOSS;
	}

	return -1;
}

//////////////////////////////////////////////////////////////////////////
//Recv
//-----------------------------------------------------------//
// Function:    RecvData_
// Param        SOCKET        sock
//              LPTSTR        Recv Data
//              int           Recv Len
//              int&          Success Recv Size
// Return  :    int
// meaning :	RecvData_
//-----------------------------------------------------------//
int RecvData_(SOCKET s, LPTSTR pBuffer, int nLen, int& nRecvCount)
{
	int retransmissionsCount = 0;
	int nRet = RECV_FAIL;
	while(TRUE)
	{	
		nRet = RecvData(s, pBuffer, nLen, nRecvCount, retransmissionsCount);
		if(nRet == RECV_Retransmission)
		{
			break;
		}
		else if(nRet == RECV_FAIL)
		{
			retransmissionsCount++;
		}
		else if(nRet == RECV_OK)
		{
			break;
		}
	}
	return nRet;
}

//-----------------------------------------------------------//
// Function:    RecvData
// Param        SOCKET        s
//              LPTSTR        pBuffer
//              int           nLen
//              int&          nRecvCount
//              UINT          retransmissionsCount
// Return  :    int
// meaning :    RecvData
//-----------------------------------------------------------//
int RecvData(SOCKET s, LPTSTR pBuffer, int nLen, int& nRecvCount, UINT retransmissionsCount)
{
	if(retransmissionsCount == RECV_RepeatMAX)		//Send Retransmission
	{
		return RECV_Retransmission;
	}
	nRecvCount = recv(s, pBuffer, nLen, 0);
	if(nRecvCount == -1 || nRecvCount==0 )		// Recv Failed
	{
		nRecvCount = 0; 
		return RECV_FAIL;
	}
	else										// Recv Success
	{
		return RECV_OK;							
	}
}

//////////////////////////////////////////////////////////////////////////
//Sock Operation Function
//-----------------------------------------------------------//
// Function:    InitSockInfo
// Param        u_short          nPort
//              LPCTSTR          pszIP
//              SOCKET&          sock
//              SOCKADDR&        addr
// Return  :    BOOL
// meaning :    InitSockInfo
//-----------------------------------------------------------//
BOOL InitSockInfo(u_short nPort, LPCTSTR pszIP, SOCKET& sock, SOCKADDR& addr)
{
	if(sock == INVALID_SOCKET)
	{
		sock = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
	}
	if(sock == INVALID_SOCKET)
	{
		return FALSE;
	}
	memset(&addr, 0x00, sizeof(addr));
	SOCKADDR_IN* pAddr_in = (SOCKADDR_IN*)&addr;
	pAddr_in->sin_family = AF_INET;
	pAddr_in->sin_port = htons(nPort);
	pAddr_in->sin_addr.S_un.S_addr = inet_addr(pszIP);

	return TRUE;
}

BOOL InitSockInfo_(u_short nPort, LPCTSTR pszServer, SOCKET& sock, SOCKADDR& addr)
{
	if(pszServer == NULL)		return FALSE;
	if(sock == INVALID_SOCKET)
	{
		sock = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
	}
	if(sock == INVALID_SOCKET)	return FALSE;

	

	memset(&addr, 0x00, sizeof(addr));
	SOCKADDR_IN* pAddr_in = (SOCKADDR_IN*)&addr;
	pAddr_in->sin_family = AF_INET;
	pAddr_in->sin_port = htons(nPort);
	if(!isalpha(pszServer[0]))
	{
		pAddr_in->sin_addr.S_un.S_addr = inet_addr(pszServer);
	}
	else
	{
		
	}
	
	
	return TRUE;
}

//-----------------------------------------------------------//
// Function:    InitSockInfo2
// Param        u_short          nPort
//              LPCTSTR          pszIP
//              SOCKET&          sock
//              SOCKADDR&        addr
// Return  :    BOOL
// meaning :    InitSockInfo2
//-----------------------------------------------------------//
BOOL InitSockInfo2(u_short nPort, LPCTSTR pszIP, SOCKET& sock, SOCKADDR& addr)
{	
#ifdef _WIN64
	if(pszIP == NULL)
	{
		pszIP = GetHostIP();
	}
	ADDRINFO hints,*res;
	memset(&hints, 0x00, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_NUMERICHOST;

	TCHAR szPort[16] = {0};
#if _MSC_VER <= 1310
	sprintf(szPort, "%d", nPort);		
#else
	sprintf_s(szPort, "%d", nPort);
#endif
	int nRet = getaddrinfo(pszIP, szPort, &hints, &res);
	if(nRet != 0)	
	{	
		return FALSE;
	}
	if(sock == INVALID_SOCKET)
	{
		sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	}
	if(sock == INVALID_SOCKET)	
	{	
		return FALSE;
	}

	memset(&addr, 0x00, sizeof(addr));
	memcpy(&addr, res->ai_addr, res->ai_addrlen);
#endif
	return TRUE;
}

//-----------------------------------------------------------//
// Function:    ReleaseSock
// Param        SOCKET        sock
// Return  :    void
// meaning :    釋放sock資源
//-----------------------------------------------------------//
void ReleaseSock(SOCKET sock)
{
	if(sock != INVALID_SOCKET)
	{
		shutdown(sock, SD_BOTH);
		closesocket(sock);
		sock = INVALID_SOCKET;
	}
}

//////////////////////////////////////////////////////////////////////////
//Other Function
//-----------------------------------------------------------//
// Function:    GetHostIP
// Param                
// Return  :    LPTSTR
// meaning :    GetHostIP
//-----------------------------------------------------------//
LPTSTR GetHostIP()
{
	TCHAR szHostName[MAX_PATH] = {0};
	gethostname(szHostName,MAX_PATH);
	struct hostent* pHost = gethostbyname(szHostName);
	if(pHost)
	{
		TCHAR* szIP = (TCHAR*)malloc(pHost->h_length);
		memcpy(szIP, pHost->h_addr_list[0], pHost->h_length);
		TCHAR *pIP = inet_ntoa(*(in_addr*)(szIP));
		free(szIP);
		szIP = NULL;

		return pIP;
	}
	return NULL;
}

// -----------------------------------------------------------//
// Function :   GetIP
// Param    :   LPCTSTR szHostName
// Return   :   LPTSTR
// Comment  :   
// -----------------------------------------------------------//
LPTSTR GetIP(LPCTSTR szHostName)
{
	struct hostent* pHost = gethostbyname(szHostName);
	if(pHost)
	{
		TCHAR* szIP = (TCHAR*)malloc(pHost->h_length);
		memcpy(szIP, pHost->h_addr_list[0], pHost->h_length);
		TCHAR *pIP = inet_ntoa(*(in_addr*)(szIP));
		free(szIP);
		szIP = NULL;
		
		return pIP;
	}
	return NULL;
}

//////////////////////////////////////////////////////////////////////////
//select
