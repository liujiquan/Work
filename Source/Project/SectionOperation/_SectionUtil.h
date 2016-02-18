//*-----------------------------------------------------------------------------*/
//* Copyright(C) 2014, liujiquan Company All rights reserved. )
//* FileName :   _SectionUtil.h
//* Author   :   liujiquan
//* DateTime :   9/23/2014
//* Version  :   1.0
//* Comment  :   
//*-----------------------------------------------------------------------------*/
#ifndef ___SECTIONUTIL_H_2459134951B94A1895E650CFD52F4215__
#define ___SECTIONUTIL_H_2459134951B94A1895E650CFD52F4215__
#pragma once
#include <wtypes.h>
/************************************************************************/
/* #define                                                              */
/************************************************************************/
#define SECTION_HEADER		"SEC_"
enum SEC_FLAG
{
	SEC_NULL = 0,
	SEC_INSERT = 1,
	SEC_DELETE = 2,
	SEC_RM_DOS_NT = 3,
	SEC_EXTEND = 4
};

/************************************************************************/
/* Global Function                                                      */
/************************************************************************/
BOOL OpenFile();								// Open File
BOOL CreateNewFile();							// CreateFile
void Release();									// Release
BOOL RemoveInfoBetweenDosHeaderAndNTHeader();	// RemoveInfoBetweenDosHeaderAndNTHeader
BOOL ExtendedPESize(DWORD dwExtendSize);		// Extended PE Size
BOOL InserSection(DWORD dwSectionSize, char* sectionName,char* sectionData, DWORD datasize);	// InserSectionHeader
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] Start
//BOOL ExtendSecionSize(WORD nIndex, DWORD dwExtendedSectionSize);	// ExtendSecionSize
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] End
BOOL DeleteSection(WORD nIndex);				// DeleteSection
DWORD PEAlign(DWORD dwAddress, DWORD dwAlignment);	//PEAlign
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] Start
BOOL JudgeMemoryNotUsed(char* szBuffer, DWORD dwSize);
void GetPEVersion();
#define X64_PE	0x8664							// 62bits PE
#define X32_PE	0x014c							// 32bits PE
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] End
/************************************************************************/
/* Util Function                                                        */
/************************************************************************/
bool MoveBuffer(char* szBuffer, DWORD dwRVA,  DWORD dwSize,  DWORD dwOffset);	// MoveBuffer
bool MoveBuffer2(char* szBuffer, DWORD dwRVA, DWORD dwSize,  DWORD dwOffset);	// MoveBuffer2

#endif//___SECTIONUTIL_H_2459134951B94A1895E650CFD52F4215__


