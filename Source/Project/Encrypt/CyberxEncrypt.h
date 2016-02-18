//*-----------------------------------------------------------------------------*/
//* Copyright(C) 2014, liujiquan Company All rights reserved. )
//* FileName :   CyberxEncrypt.h
//* Author   :   liujiquan
//* DateTime :   12/10/2014
//* Version  :   1.0
//* Comment  :   
//*-----------------------------------------------------------------------------*/
#ifndef __CYBERXENCRYPT_H_2459134951B94A1895E650CFD52F4215__
#define __CYBERXENCRYPT_H_2459134951B94A1895E650CFD52F4215__
#pragma once
#include <afx.h>

CString Encryption(LPCTSTR lpszPlaintext, LPCTSTR lpvKeyData);
void MfxStringToMem(LPTSTR lpszMem, LPCTSTR lpszString);
void MfxAddString(CString& strString,  LPCTSTR lpvSrc, DWORD dwSize);
DWORD MfxMemToString(CString& strString, LPCTSTR lpszMem, DWORD dwSize);
CString Decryption(LPCTSTR lpszCiphertext, LPCTSTR lpvKeyData);
#endif//__CYBERXENCRYPT_H_2459134951B94A1895E650CFD52F4215__
