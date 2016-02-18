//*-----------------------------------------------------------------------------*/
//* Copyright(C) 2014, liujiquan Company All rights reserved. )
//* FileName :   Base64.h
//* Author   :   liujiquan
//* DateTime :   11/4/2014
//* Version  :   1.0
//* Comment  :   
//*-----------------------------------------------------------------------------*/
#ifndef __BASE64_H_2459134951B94A1895E650CFD52F4215__
#define __BASE64_H_2459134951B94A1895E650CFD52F4215__
#pragma once
#include <afx.h>

/************************************************************************/
/* Function                                                             */
/************************************************************************/
DWORD EncryptBase64(LPTSTR pszBase64, LPCTSTR pszSource, int len);				// EncryptBase64
DWORD DecryptBase64(LPTSTR pszDesryptSource, LPCTSTR pszBase64, int len);		// DecryptBase64
BOOL  GetBase64CodeIndex(BYTE c, BYTE& index);									// GetBase64CodeIndex
CString GetEncryptBase64(CString strSrc);										// GetEncryptBase64
CString GetDecryptBase64(CString strBase64);									// GetDecryptBase64

#endif//__BASE64_H_2459134951B94A1895E650CFD52F4215__

