//*-----------------------------------------------------------------------------*/
//* Copyright(C) 2014, liujiquan Company All rights reserved. )
//* FileName :   _SectionUtil.cpp
//* Author   :   liujiquan
//* DateTime :   9/23/2014
//* Version  :   1.0
//* Comment  :   
//*-----------------------------------------------------------------------------*/
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "StdAfx.h"
#include "_sectionutil.h"
#include <stdio.h>

/************************************************************************/
/* Gbloabl Member                                                       */
/************************************************************************/
char*		g_szBuffer = NULL;					// Buffer
char		g_szFileName[MAX_PATH];				// FileName
DWORD		g_dwFileSize = 0;					// FileSize
SEC_FLAG	g_flag = SEC_INSERT;				// SEC flag
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] Start
DWORD g_PEVerson = X32_PE;
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] End

// -----------------------------------------------------------//
// Function :   OpenFile
// Return   :   BOOL
// Comment  :   Open File
// -----------------------------------------------------------//
BOOL OpenFile()
{
	if(g_szBuffer != NULL)	{	return FALSE;}
	// Select File
	OPENFILENAME ofn;
	memset(&ofn, 0x00, sizeof(ofn));
	
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = g_szFileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFilter = "Exe File(*.exe)\0*.exe\0All File(*.*)\0*.*\0\0";
	ofn.lpstrTitle = "Open File";
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	
	if(GetOpenFileName(&ofn) == FALSE)	{	return FALSE;}
	
	// Open File
	HANDLE handle = CreateFile(g_szFileName, 
		GENERIC_READ,
		FILE_SHARE_READ, 
		NULL, 
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL, 
		NULL);
	if(handle == NULL)
	{
		return FALSE;
	}
	
	DWORD  dwFileSizeHi;
	g_dwFileSize = GetFileSize(handle, &dwFileSizeHi);
	if(g_dwFileSize == 0)	
	{
		CloseHandle(handle);
		return FALSE;
	}
	// Read File
	g_szBuffer = (TCHAR*)malloc(g_dwFileSize);
	if(g_szBuffer == NULL)
	{
		CloseHandle(handle);
		return FALSE;
	}
	
	DWORD dwReadSize;
	if(ReadFile(handle, g_szBuffer, g_dwFileSize, &dwReadSize, NULL) == FALSE)
	{
		CloseHandle(handle);
		Release();
		return FALSE;
	}
	
	CloseHandle(handle);
	handle = NULL;
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] Start
	GetPEVersion();
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] End	

	return TRUE;
}

// -----------------------------------------------------------//
// Function :   CreateNewFile
// Return   :   BOOL
// Comment  :   
// -----------------------------------------------------------//
BOOL CreateNewFile()
{
	CString newFileName(g_szFileName);
	int index = newFileName.ReverseFind('\\');
	if(index == -1)
	{
		index = newFileName.ReverseFind('/');
	}
	if(index != -1)
	{
		switch(g_flag)
		{
		case SEC_INSERT:
			newFileName = newFileName.Left(index+1) + SECTION_HEADER + "INSERT_" + newFileName.Right(newFileName.GetLength()-index-1);
			break;
		case SEC_DELETE:
			newFileName = newFileName.Left(index+1) + SECTION_HEADER + "DELETE_" + newFileName.Right(newFileName.GetLength()-index-1);
			break;
		case SEC_RM_DOS_NT:
			newFileName = newFileName.Left(index+1) + SECTION_HEADER + "RM_" + newFileName.Right(newFileName.GetLength()-index-1);
			break;
		case SEC_EXTEND:
			newFileName = newFileName.Left(index+1) + SECTION_HEADER + "EXTEND_" + newFileName.Right(newFileName.GetLength()-index-1);
			break;
		case SEC_NULL:
		default:
			newFileName = newFileName.Left(index+1) + SECTION_HEADER  + newFileName.Right(newFileName.GetLength()-index-1);
			break;
		}
		
		FILE* pFile;
		pFile = fopen(newFileName.GetBuffer(0), "wb");
		if(pFile)
		{
			fwrite(g_szBuffer, 1, g_dwFileSize, pFile);
			fclose(pFile);
		}
		
		return TRUE; 
	}
	
	return FALSE;
}

// -----------------------------------------------------------//
// Function :   Release
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void Release()
{
	if(g_szBuffer)
	{
		free(g_szBuffer);
		g_szBuffer = NULL;
	}
}

// -----------------------------------------------------------//
// Function :   RemoveInfoBetweenDosHeaderAndNTHeader
// Return   :   BOOL
// Comment  :   Remove Info Between DosHeader and NtHeader
// -----------------------------------------------------------//
BOOL RemoveInfoBetweenDosHeaderAndNTHeader()
{
	if(g_szBuffer == NULL)	return FALSE;
	
	IMAGE_DOS_HEADER dosHeader;
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] Start
//	IMAGE_NT_HEADERS ntHeader;
	IMAGE_NT_HEADERS32 ntHeader;
	IMAGE_NT_HEADERS64 ntHeader64;
	DWORD dwNTHeaderSize;

	if(g_PEVerson == X64_PE)
	{
		dwNTHeaderSize = sizeof(IMAGE_NT_HEADERS64);
	}
	else
	{
		dwNTHeaderSize = sizeof(IMAGE_NT_HEADERS32);
	}
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] End
	
	memcpy(&dosHeader, g_szBuffer, sizeof(dosHeader));
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] Start
	if(g_PEVerson == X64_PE)
	{
		memcpy(&ntHeader64, g_szBuffer+dosHeader.e_lfanew, dwNTHeaderSize);
	}
	else
	{
		memcpy(&ntHeader, g_szBuffer+dosHeader.e_lfanew, sizeof(ntHeader));
	}
	
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] End	
	DWORD dwDosHeaderSize = sizeof(IMAGE_DOS_HEADER);
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] Start
//	DWORD dwNTHeaderSize = sizeof(IMAGE_NT_HEADERS);
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] End
	DWORD dwSectionHeaderSize = sizeof(IMAGE_SECTION_HEADER);
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] Start
//	DWORD dwSectionNum = ntHeader.FileHeader.NumberOfSections;
	DWORD dwSectionNum;
	if(g_PEVerson == X64_PE)
	{
		dwSectionNum = ntHeader64.FileHeader.NumberOfSections;
	}
	else
	{
		dwSectionNum = ntHeader.FileHeader.NumberOfSections;
	}
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] End
	DWORD dwRemainSize = dosHeader.e_lfanew - dwDosHeaderSize;
	if(dwRemainSize <= 0)
	{
		MessageBox(0, "No Size Between Dos and NtHeader", 0, 0);
		return FALSE;
	}
	//3:Copy IMAGE_SECTION_HEADER
	DWORD dwSectionOldIndex = dosHeader.e_lfanew+dwNTHeaderSize;
	DWORD dwSectionNewIndex = dwSectionOldIndex - dwRemainSize;
	DWORD dwSectionSize = dwSectionHeaderSize * dwSectionNum;
	
	char* oldBuffer = (char* )malloc(dwSectionSize);
	memcpy(oldBuffer, g_szBuffer+dwSectionOldIndex, dwSectionSize);
	memset(g_szBuffer+dwSectionOldIndex, 0x00, dwSectionSize);
	memcpy(g_szBuffer+dwSectionNewIndex, oldBuffer, dwSectionSize);
	free(oldBuffer);
	oldBuffer = NULL;
	//2:Copy IMAGE_NT_HEADERS
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] Start
	if(g_PEVerson == X64_PE)
	{
		memcpy(g_szBuffer+dwDosHeaderSize, &ntHeader64, dwNTHeaderSize);
	}
	else
	{
		memcpy(g_szBuffer+dwDosHeaderSize, &ntHeader, dwNTHeaderSize);
	}	
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] End
	//1:Mdoify IMAGE_DOS_HEADER
	dosHeader.e_lfanew = dwDosHeaderSize;
	memcpy(g_szBuffer, &dosHeader, dwDosHeaderSize);
	
	g_flag = SEC_RM_DOS_NT;

	return TRUE;
}

// -----------------------------------------------------------//
// Function :   ExtendedPESize
// Param    :   DWORD dwExtendSize
// Return   :   BOOL
// Comment  :   
// -----------------------------------------------------------//
BOOL ExtendedPESize(DWORD dwExtendSize)
{
	if(g_szBuffer == NULL || dwExtendSize <= 0)	return FALSE;
	
	IMAGE_DOS_HEADER dosHeader;
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] Start
//	IMAGE_NT_HEADERS ntHeader;
	IMAGE_NT_HEADERS32 ntHeader;
	IMAGE_NT_HEADERS64 ntHeader64;
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] End
	
	memcpy(&dosHeader, g_szBuffer, sizeof(dosHeader));
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] Start
	if(g_PEVerson == X64_PE)
	{
		memcpy(&ntHeader64, g_szBuffer+dosHeader.e_lfanew, sizeof(ntHeader64));
	}
	else
	{
		memcpy(&ntHeader, g_szBuffer+dosHeader.e_lfanew, sizeof(ntHeader));
	}
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] End
	
	
	//1: Check Extended Size multiple of SectionAlignment
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] Start
//	DWORD dwSectionAlignment = ntHeader.OptionalHeader.SectionAlignment;
	DWORD dwSectionAlignment;
	if(g_PEVerson == X64_PE)
	{
		dwSectionAlignment = ntHeader64.OptionalHeader.SectionAlignment;
	}
	else
	{
		dwSectionAlignment = ntHeader.OptionalHeader.SectionAlignment;
	}
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] End
	
	if(dwExtendSize % dwSectionAlignment != 0)
	{
		MessageBox(0, "Extended Size Must  be a multiple of SectionAlignment.", 0, 0);
		return FALSE;
	}
	
	//3: Extended PE Size
	char* szTemp = (char* )malloc(g_dwFileSize);
	memcpy(szTemp, g_szBuffer, g_dwFileSize);
	free(g_szBuffer);
	g_szBuffer = NULL;
	g_szBuffer = (char* )malloc(g_dwFileSize+dwExtendSize);
	memset(g_szBuffer, 0x00, g_dwFileSize+dwExtendSize);
	memcpy(g_szBuffer, szTemp, g_dwFileSize);
	free(szTemp);
	szTemp = NULL;
	
	g_dwFileSize += dwExtendSize;
	
	g_flag = SEC_EXTEND;

	return TRUE;
}

// -----------------------------------------------------------//
// Function :   InserSection
// Param    :   DWORD dwSectionSize
//              char* sectionName
//              char* sectionData
//              int datasize
// Return   :   BOOL
// Comment  :   
// -----------------------------------------------------------//
BOOL InserSection(DWORD dwSectionSize, char* sectionName, char* sectionData, DWORD datasize)
{
	if(g_szBuffer == NULL)			return FALSE;
	if(datasize > dwSectionSize)	return FALSE;

	//1: ExtendedPESize
	if(ExtendedPESize(dwSectionSize) == FALSE)
	{
		return FALSE;
	}
	
	IMAGE_DOS_HEADER dosHeader;
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] Start
//	IMAGE_NT_HEADERS ntHeader;
	IMAGE_NT_HEADERS32 ntHeader;
	IMAGE_NT_HEADERS64 ntHeader64;
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] End
	IMAGE_SECTION_HEADER sectionHeader,newSectionHeader;
	
	memcpy(&dosHeader, g_szBuffer, sizeof(dosHeader));
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] Start
	if(g_PEVerson == X64_PE)
	{
		memcpy(&ntHeader64, g_szBuffer+dosHeader.e_lfanew, sizeof(ntHeader64));
	}
	else
	{
		memcpy(&ntHeader, g_szBuffer+dosHeader.e_lfanew, sizeof(ntHeader));
	}
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] End
	
	DWORD dwDosHeaderSize = sizeof(IMAGE_DOS_HEADER);
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] Start
//	DWORD dwNTHeaderSize = sizeof(IMAGE_NT_HEADERS);
	DWORD dwNTHeaderSize;
	if(g_PEVerson == X64_PE)
	{
		dwNTHeaderSize = sizeof(IMAGE_NT_HEADERS64);
	}
	else
	{
		dwNTHeaderSize = sizeof(IMAGE_NT_HEADERS32);
	}
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] End
	DWORD dwSectionHeaderSize = sizeof(IMAGE_SECTION_HEADER);
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] Start
//	DWORD dwSectionNum = ntHeader.FileHeader.NumberOfSections;
//	DWORD dwInserAddress = dosHeader.e_lfanew + dwNTHeaderSize + dwSectionHeaderSize * dwSectionNum;
//	memcpy(&sectionHeader, g_szBuffer+dosHeader.e_lfanew+sizeof(ntHeader) + (dwSectionNum-1)*sizeof(IMAGE_SECTION_HEADER), sizeof(sectionHeader));
//	DWORD dwSectionAlignment = ntHeader.OptionalHeader.SectionAlignment;
//	DWORD dwFileAlignment = ntHeader.OptionalHeader.FileAlignment;
	DWORD dwSectionNum = 0;
	DWORD dwSectionAlignment;
	DWORD dwFileAlignment;
	if(g_PEVerson == X64_PE)
	{
		dwSectionNum = ntHeader64.FileHeader.NumberOfSections;
		dwSectionAlignment = ntHeader64.OptionalHeader.SectionAlignment;
		dwFileAlignment = ntHeader64.OptionalHeader.FileAlignment;
	}
	else
	{
		dwSectionNum = ntHeader.FileHeader.NumberOfSections;
		dwSectionAlignment = ntHeader.OptionalHeader.SectionAlignment;
		dwFileAlignment = ntHeader.OptionalHeader.FileAlignment;	
	}
	memcpy(&sectionHeader, g_szBuffer+dosHeader.e_lfanew+dwNTHeaderSize + (dwSectionNum-1)*sizeof(IMAGE_SECTION_HEADER), sizeof(sectionHeader));
	DWORD dwInserAddress = dosHeader.e_lfanew + dwNTHeaderSize + dwSectionHeaderSize * dwSectionNum;
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] End
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] Start
	if(JudgeMemoryNotUsed(g_szBuffer+dwInserAddress, sizeof(IMAGE_SECTION_HEADER)) == FALSE)
	{
		//RemoveInfoBetweenDosHeaderAndNTHeader
		if(RemoveInfoBetweenDosHeaderAndNTHeader() == FALSE)	return FALSE;
		MessageBox(0, "RemoveInfoBetweenDosHeaderAndNTHeader", 0, 0);
		//
		memcpy(&dosHeader, g_szBuffer, sizeof(dosHeader));
		//  2014.09.24 Ver1.00[X64/X32 PE] Start
		if(g_PEVerson == X64_PE)
		{
			memcpy(&ntHeader64, g_szBuffer+dosHeader.e_lfanew, sizeof(ntHeader64));
			dwSectionNum = ntHeader64.FileHeader.NumberOfSections;
		}
		else
		{
			memcpy(&ntHeader, g_szBuffer+dosHeader.e_lfanew, sizeof(ntHeader));
			dwSectionNum = ntHeader.FileHeader.NumberOfSections;
		}
		//  2014.09.24 Ver1.00[X64/X32 PE] End
		memcpy(&sectionHeader, g_szBuffer+dosHeader.e_lfanew+dwNTHeaderSize + (dwSectionNum-1)*sizeof(IMAGE_SECTION_HEADER), sizeof(sectionHeader));
		dwInserAddress = dosHeader.e_lfanew+dwNTHeaderSize+sizeof(IMAGE_SECTION_HEADER)*dwSectionNum;
		
		if(JudgeMemoryNotUsed(g_szBuffer+dwInserAddress, sizeof(IMAGE_SECTION_HEADER)) == FALSE)
		{
			return FALSE;
		}
	}	
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] End
	//1:Check VirtualSize 
	if(dwSectionSize - datasize > dwSectionAlignment)
	{
		return FALSE;
	}

	//2: Set Section Count / SizeofImage
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] Start
	if(g_PEVerson == X64_PE)
	{
		ntHeader64.FileHeader.NumberOfSections += 1;					// Section Num Modify
		ntHeader64.OptionalHeader.SizeOfImage += dwSectionSize;			// SizeofImage Modify
		memcpy(g_szBuffer+dosHeader.e_lfanew, &ntHeader64, dwNTHeaderSize);
	}
	else
	{
		ntHeader.FileHeader.NumberOfSections += 1;					// Section Num Modify
		ntHeader.OptionalHeader.SizeOfImage += dwSectionSize;		// SizeofImage Modify
		memcpy(g_szBuffer+dosHeader.e_lfanew, &ntHeader, dwNTHeaderSize);	
	}
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] End
	//3: New Section Header
	memset(&newSectionHeader, 0x00, dwSectionHeaderSize);
	memcpy(&newSectionHeader, &sectionHeader, dwSectionHeaderSize);
	memset(&newSectionHeader.Name, 0x00, IMAGE_SIZEOF_SHORT_NAME);
	memcpy(newSectionHeader.Name, sectionName, strlen(sectionName)>IMAGE_SIZEOF_SHORT_NAME?IMAGE_SIZEOF_SHORT_NAME:strlen(sectionName));
	newSectionHeader.Misc.VirtualSize = datasize;
	newSectionHeader.PointerToRawData = sectionHeader.PointerToRawData + sectionHeader.SizeOfRawData;
	newSectionHeader.SizeOfRawData = dwSectionSize;
	DWORD dwVirtualAddress = PEAlign(sectionHeader.VirtualAddress+sectionHeader.Misc.VirtualSize, dwSectionAlignment);
	newSectionHeader.VirtualAddress = dwVirtualAddress; 
	newSectionHeader.Characteristics = IMAGE_SCN_CNT_INITIALIZED_DATA|IMAGE_SCN_MEM_READ|IMAGE_SCN_MEM_WRITE;
	//4: Insert New Section Header
	memcpy(g_szBuffer+dwInserAddress, &newSectionHeader, dwSectionHeaderSize);
	
	//4: Insert new Section Data
	memcpy(g_szBuffer+g_dwFileSize-dwSectionSize, sectionData, datasize);
	
	g_flag = SEC_INSERT;

	return TRUE;
}

// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] Start
// -----------------------------------------------------------//
// Function :   ExtendSecionSize
// Param    :   WORD nIndex
//              DWORD dwExtendedSectionSize
// Return   :   BOOL
// Comment  :   
// -----------------------------------------------------------//
/*
BOOL ExtendSecionSize(WORD nIndex, DWORD dwExtendedSectionSize)
{
	if(g_szBuffer == NULL || dwExtendedSectionSize <= 0 || nIndex < 0)	return FALSE;
	if(ExtendedPESize(dwExtendedSectionSize) == FALSE)					return FALSE;

	IMAGE_DOS_HEADER dosHeader;
	IMAGE_NT_HEADERS ntHeader;
	IMAGE_SECTION_HEADER sectionHeader;

	memcpy(&dosHeader, g_szBuffer, sizeof(dosHeader));
	memcpy(&ntHeader, g_szBuffer+dosHeader.e_lfanew, sizeof(ntHeader));
	WORD nSectionNum = ntHeader.FileHeader.NumberOfSections;
	
	//1: Check Index
	if(nIndex >= nSectionNum)	return FALSE;
	//2: Section After nIndex Move back dwExtendedSectionSize
	DWORD dwOldPointToRawData;
	DWORD dwUseSize;
	for(int index = nSectionNum - 1; index > nIndex; index--)
	{
		//1:Section Info
		memcpy(&sectionHeader, g_szBuffer+dosHeader.e_lfanew+sizeof(IMAGE_NT_HEADERS) + index*sizeof(IMAGE_SECTION_HEADER), sizeof(sectionHeader));
		dwOldPointToRawData= sectionHeader.PointerToRawData;		// PointerToRawData
		dwUseSize = sectionHeader.Misc.VirtualSize;					// VirtualSize
		
		sectionHeader.PointerToRawData += dwExtendedSectionSize;
// 2014.09.23 Ver1.0[Question 1.1] Begin
//		sectionHeader.VirtualAddress += dwExtendedSectionSize;
// 2014.09.23 Ver1.0[Question 1.1] Begin
		memcpy(g_szBuffer+dosHeader.e_lfanew+sizeof(IMAGE_NT_HEADERS) + index*sizeof(IMAGE_SECTION_HEADER), &sectionHeader, sizeof(sectionHeader));
		
		//2 Section Data
		MoveBuffer(g_szBuffer, dwOldPointToRawData, dwUseSize, dwExtendedSectionSize);
	}
	//3: Extended nIndex Section Size
	memcpy(&sectionHeader, g_szBuffer+dosHeader.e_lfanew+sizeof(IMAGE_NT_HEADERS) + index*sizeof(IMAGE_SECTION_HEADER), sizeof(sectionHeader));
	dwOldPointToRawData= sectionHeader.PointerToRawData;		// PointerToRawData
	dwUseSize = sectionHeader.Misc.VirtualSize;					// VirtualSize
		
	sectionHeader.SizeOfRawData +=  dwExtendedSectionSize;
// 2014.09.23 Ver1.0[Question 1.1] Begin
//	sectionHeader.VirtualAddress += dwExtendedSectionSize;
// 2014.09.23 Ver1.0[Question 1.1] End
	memcpy(g_szBuffer+dosHeader.e_lfanew+sizeof(IMAGE_NT_HEADERS) + index*sizeof(IMAGE_SECTION_HEADER), &sectionHeader, sizeof(sectionHeader));
	
	g_flag = SEC_EXTEND;

	return TRUE;
}*/
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] End

// -----------------------------------------------------------//
// Function :   DeleteSection
// Param    :   WORD nIndex
// Return   :   BOOL
// Comment  :   Only Delete The Last Section
// -----------------------------------------------------------//
BOOL DeleteSection(WORD nIndex)
{
	if(g_szBuffer == NULL || nIndex < 0)	return FALSE;
	
	IMAGE_DOS_HEADER dosHeader;
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] Start
	IMAGE_NT_HEADERS32 ntHeader;
	IMAGE_NT_HEADERS64 ntHeader64;
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] End
	IMAGE_SECTION_HEADER sectionHeader;
	
	memcpy(&dosHeader, g_szBuffer, sizeof(dosHeader));
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] Start
	if(g_PEVerson == X64_PE)
	{
		memcpy(&ntHeader64, g_szBuffer+dosHeader.e_lfanew, sizeof(ntHeader64));	
		memcpy(&sectionHeader, g_szBuffer+dosHeader.e_lfanew+sizeof(IMAGE_NT_HEADERS64)+nIndex*sizeof(IMAGE_SECTION_HEADER), sizeof(sectionHeader));
	}
	else
	{
		memcpy(&ntHeader, g_szBuffer+dosHeader.e_lfanew, sizeof(ntHeader));	
		memcpy(&sectionHeader, g_szBuffer+dosHeader.e_lfanew+sizeof(IMAGE_NT_HEADERS)+nIndex*sizeof(IMAGE_SECTION_HEADER), sizeof(sectionHeader));
	}
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] End
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] Start
	WORD nSectionNum = 0;
	if(g_PEVerson == X64_PE)
	{
		nSectionNum = ntHeader64.FileHeader.NumberOfSections;
	}
	else
	{
		nSectionNum = ntHeader.FileHeader.NumberOfSections;
	}
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] End
	
	DWORD dwDelSecPointerToRawData = sectionHeader.PointerToRawData;	// RVA
	DWORD dwDelSecSize = sectionHeader.SizeOfRawData;					// Size
	//1: Check Index
	if(nIndex >= nSectionNum)	return FALSE;
	//2: Set Section Count
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] Start
	if(g_PEVerson == X64_PE)
	{
		ntHeader64.FileHeader.NumberOfSections -= 1;
	}
	else
	{
		ntHeader.FileHeader.NumberOfSections -= 1;
	}
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] End
	//3
	if(nIndex == nSectionNum - 1)	// delete the last Section 
	{
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] Start
		if(g_PEVerson == X64_PE)
		{
			memset(g_szBuffer+dosHeader.e_lfanew+sizeof(IMAGE_NT_HEADERS64)+nIndex*sizeof(IMAGE_SECTION_HEADER), 0x00, sizeof(IMAGE_SECTION_HEADER));		// Info Clear
			memset(g_szBuffer+sectionHeader.PointerToRawData, 0x00, sectionHeader.SizeOfRawData);								// Data Clear
			ntHeader64.OptionalHeader.SizeOfImage -= sectionHeader.SizeOfRawData;		// Image Size - SizeOfRawData									
			g_dwFileSize -= sectionHeader.SizeOfRawData;							// PE File Size - SizeOfRawData
			memcpy(g_szBuffer+dosHeader.e_lfanew, &ntHeader64, sizeof(ntHeader64));	
		}
		else
		{
			memset(g_szBuffer+dosHeader.e_lfanew+sizeof(IMAGE_NT_HEADERS)+nIndex*sizeof(IMAGE_SECTION_HEADER), 0x00, sizeof(IMAGE_SECTION_HEADER));		// Info Clear
			memset(g_szBuffer+sectionHeader.PointerToRawData, 0x00, sectionHeader.SizeOfRawData);								// Data Clear
			ntHeader.OptionalHeader.SizeOfImage -= sectionHeader.SizeOfRawData;		// Image Size - SizeOfRawData									
			g_dwFileSize -= sectionHeader.SizeOfRawData;							// PE File Size - SizeOfRawData
			memcpy(g_szBuffer+dosHeader.e_lfanew, &ntHeader, sizeof(ntHeader));	
		}
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] End
		g_flag = SEC_DELETE;

		return TRUE;
	}
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] Start
//	else if(nSectionNum - 1 > nIndex > 0)
//	{
//		IMAGE_SECTION_HEADER sectionHeaderBefore;
//		memcpy(&sectionHeaderBefore, g_szBuffer+dosHeader.e_lfanew+sizeof(IMAGE_NT_HEADERS)+(nIndex-1)*sizeof(IMAGE_SECTION_HEADER), sizeof(sectionHeader));
//		sectionHeaderBefore.Misc.VirtualSize += sectionHeader.Misc.VirtualSize;		// VirtualSize ++
//		sectionHeaderBefore.SizeOfRawData += sectionHeader.SizeOfRawData;			// SizeOfRawData
//		memcpy(g_szBuffer+dosHeader.e_lfanew+sizeof(IMAGE_NT_HEADERS)+(nIndex-1)*sizeof(IMAGE_SECTION_HEADER), &sectionHeaderBefore, sizeof(sectionHeader));
//		
//		UINT dwRVA = dosHeader.e_lfanew+sizeof(IMAGE_NT_HEADERS)+(nIndex+1)*sizeof(IMAGE_SECTION_HEADER);
//		DWORD dwSize = (nSectionNum-nIndex)*sizeof(IMAGE_SECTION_HEADER);
//		MoveBuffer(g_szBuffer, dwRVA, dwSize, -sizeof(IMAGE_SECTION_HEADER));
//
//		memcpy(g_szBuffer+dosHeader.e_lfanew, &ntHeader, sizeof(ntHeader));
//	}
//	else 
//	{
//
//	}
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] End
	
	return FALSE;
}

/************************************************************************/
/* Util Function                                                        */
/************************************************************************/
// -----------------------------------------------------------//
// Function :   MoveBuffer
// Param    :   char* szBuffer
//              DWORD dwRVA
//              DWORD dwSize
//              DWORD dwOffset
// Return   :   bool
// Comment  :   
// -----------------------------------------------------------//
bool MoveBuffer(char* szBuffer, DWORD dwRVA,  DWORD dwSize,  DWORD dwOffset)
{
	char* szTemp = (char*)malloc(dwSize);
	if(szTemp == NULL)	return false;
	
	try
	{
		memcpy(szTemp, szBuffer+dwRVA, dwSize);
		memset(szBuffer+dwRVA, 0x00, dwSize);
		memcpy(szBuffer+dwRVA+dwOffset, szTemp, dwSize);
		
		free(szTemp);
		szTemp = NULL;
	}
	catch (CException* )
	{
		return false;
	}
	
	return true;
}

// -----------------------------------------------------------//
// Function :   MoveBuffer2
// Param    :   char* szBuffer
//              DWORD dwRVA
//              DWORD dwSize
//              DWORD dwOffset
// Return   :   bool
// Comment  :   
// -----------------------------------------------------------//
bool MoveBuffer2(char* szBuffer, DWORD dwRVA, DWORD dwSize,  DWORD dwOffset)
{
	try
	{
		if(dwOffset > 0)
		{
			for(DWORD i = dwSize - 1; i >= 0; i--)
			{
				*(szBuffer+dwRVA+i+dwOffset) = *(szBuffer+dwRVA+i);
			}
		}
		else if(dwOffset < 0)
		{
			for(DWORD i = 0; i < dwSize; i++)
			{
				*(szBuffer+dwRVA+i+dwOffset) = *(szBuffer+dwRVA+i);
			}
		}
		else
		{
			return true;
		}
	}
	catch (CException* )
	{
		return false;
	}
	
	return TRUE;
}

// -----------------------------------------------------------//
// Function :   PEAlign
// Param    :   DWORD dwAddress
//              DWORD dwAlignment
// Return   :   DWORD
// Comment  :   
// -----------------------------------------------------------//
DWORD PEAlign(DWORD dwAddress, DWORD dwAlignment)
{
	return ((dwAddress+dwAlignment-1)/dwAlignment)*dwAlignment;
}


// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] Start
// -----------------------------------------------------------//
// Function :   GetPEVersion
// Return   :   void
// Comment  :   GetPEVersion
// -----------------------------------------------------------//
void GetPEVersion()
{
	if(g_szBuffer == NULL)	return;
	
	IMAGE_DOS_HEADER dosHeader;
	IMAGE_NT_HEADERS ntHeader;
	memcpy(&dosHeader, g_szBuffer, sizeof(dosHeader));
	memcpy(&ntHeader, g_szBuffer+dosHeader.e_lfanew, sizeof(ntHeader));
	
	if(ntHeader.FileHeader.Machine == X32_PE)
	{
		g_PEVerson = X32_PE;
	}
	else if(ntHeader.FileHeader.Machine == X64_PE)
	{
		g_PEVerson = X64_PE;
	}
}
// -----------------------------------------------------------//
// Function :   JudgeMemoryNotUsed
// Param    :   char* szBuffer
//              DWORD dwSize
// Return   :   BOOL
// Comment  :   
// -----------------------------------------------------------//
BOOL JudgeMemoryNotUsed(char* szBuffer, DWORD dwSize)
{
	try
	{
		for(DWORD index = 0; index < dwSize; index++)
		{
			if(*(szBuffer+index) != 0)
			{
				return FALSE;
			}
		}
		return TRUE;
	}	
	catch (CException*)
	{
		return FALSE;
	}
	
	return FALSE;
}

// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] End