//*-----------------------------------------------------------------------------*/
//* Copyright(C) 2014, liujiquan Company All rights reserved. )
//* FileName :   URLEncode.h
//* Author   :   liujiquan
//* DateTime :   11/19/2014
//* Version  :   1.0
//* Comment  :   ÖÐÎÄµÄURLEncode Decode (UTF-8/ASCII)
//*-----------------------------------------------------------------------------*/
#ifndef __URLENCODE_H_2459134951B94A1895E650CFD52F4215__
#define __URLENCODE_H_2459134951B94A1895E650CFD52F4215__
#pragma once
#include <afx.h>
//=E5=88=98=E7=BB=A7=E5=85=A8
#define ENCODE_MIME			'='
//%E5%88%98%E7%BB%A7%E5%85%A8
#define ENCODE_URL			'%'

CString TOHEX(BYTE cValue, CHAR c);
BYTE FROMHEX(BYTE bHi, BYTE bLow);
CString UTF8TOASCII(LPCTSTR szUTF8Data);
CString ASCIITOUTF8(LPCTSTR szAsciiData);
CString Encode(CString strSource, BOOL bUTF8, CHAR c);
CString Decode(CString strSource, BOOL bUTF8, CHAR c);

#endif//__URLENCODE_H_2459134951B94A1895E650CFD52F4215__
