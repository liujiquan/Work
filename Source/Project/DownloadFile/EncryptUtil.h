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
/* FUnction                                                                     */
/************************************************************************/
HEADER GetHeader(LPCTSTR pszSourceBase64, CString& strSource);						// GetHeader
BOOL   FormatEncryptData(HEADER header, LPTSTR pszSource, CString& szDestData);		// FormatEncryptData
BOOL   FormatDecryptData(HEADER header, LPTSTR pszSource, CString& szDestData);		// FormatDecryptData
CString  DecryptData(CString strSource);											// DecryptData

#endif//__ENCRYPTUTIL_H_2459134951B94A1895E650CFD52F4215__
