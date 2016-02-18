//*-----------------------------------------------------------------------------*/
//* Copyright(C) 2014, liujiquan Company All rights reserved. )
//* FileName :   EncryptUtil.h
//* Author   :   liujiquan
//* DateTime :   11/4/2014
//* Version  :   1.0
//* Comment  :   
//*-----------------------------------------------------------------------------*/
#ifndef __ENCRYPTUTIL_H_2459134951B94A1895E650CFD52F4215__
#define __ENCRYPTUTIL_H_2459134951B94A1895E650CFD52F4215__
#pragma once
#include <afx.h>
/************************************************************************/
/* Define                                                                     */
/************************************************************************/
#define THUNDER_HEADER_STR	_T("thunder://")
#define QQDL_HEADER_STR		_T("qqdl://")
#define Flashget_HEADER_STR	_T("Flashget://")
/************************************************************************/
/* Struct                                                                     */
/************************************************************************/
enum HEADER
{
	HEADER_NULL = 0,
	THUNDER_HEADER = 1,
	QQDL_HEADER = 2,
	FLASHGET_HEADER = 3
};
/************************************************************************/
/* FUnction                                                             */
/************************************************************************/
HEADER GetHeader(LPCTSTR pszSourceBase64, CString& strSource);						// GetHeader
BOOL   FormatEncryptData(HEADER header, LPTSTR pszSource, CString& szDestData);		// FormatEncryptData
BOOL   FormatDecryptData(HEADER header, LPTSTR pszSource, CString& szDestData);		// FormatDecryptData
CString  DecryptData(CString strSource);											// DecryptData

/************************************************************************/
/* Class                                                                */
/************************************************************************/
#define 	HASHCODE_RSHash			0
#define 	HASHCODE_JSHash			1
#define 	HASHCODE_PJWHash		2
#define 	HASHCODE_ELFHash		3
#define 	HASHCODE_BKDRHash		4
#define 	HASHCODE_SDBMHash		5
#define 	HASHCODE_DJBHash		6
#define 	HASHCODE_DEKHash		7
#define 	HASHCODE_BPHash			8
#define 	HASHCODE_FNVHash		9
#define 	HASHCODE_APHash			10
// GeneralHashFunctionLibrary
class GeneralHashFunctionLibrary
{	
public:
	static long RSHash(CString  str);					// RSHash
	static long JSHash(CString  str);					// JSHash
	static long PJWHash(CString  str);					// PJWHash
	static long ELFHash(CString  str);					// ELFHash
	static long BKDRHash(CString  str);					// BKDRHash
	static long SDBMHash(CString  str);					// SDBMHash
	static long DJBHash(CString  str);					// DJBHash
	static long DEKHash(CString  str);					// DEKHash
	static long BPHash(CString  str);					// BPHash
	static long FNVHash(CString  str);					// FNVHash
	static long APHash(CString  str);					// APHash
	static long HashCode(CString  str, int nIndex = 0);// HashCode
};
#endif//__ENCRYPTUTIL_H_2459134951B94A1895E650CFD52F4215__
