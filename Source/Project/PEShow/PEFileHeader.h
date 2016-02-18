//*-----------------------------------------------------------------------------*/
//* Copyright(C) 2014, liujiquan Company All rights reserved. )
//* FileName :   PEFileHeader.h
//* Author   :   liujiquan
//* DateTime :   9/5/2014
//* Version  :   1.0
//* Comment  :   
//*-----------------------------------------------------------------------------*/
#ifndef __PEFILEHEADER_H_2459134951B94A1895E650CFD52F4215__
#define __PEFILEHEADER_H_2459134951B94A1895E650CFD52F4215__
#pragma once
#include <wtypes.h>

// ITEMTYPE
enum ITEMTYPE
{
	_WORD = 0,
	_DWORD = 1,
	_LONG = 2,
	_BYTE = 3,
	_CHAR = 4,
	_DOUBLE = 5,
	_STRING = 6,
	_NULL = 7,
};
// ITEMDATA
typedef struct tag_ITEMDATA
{
	DWORD dwAddress;		// offset
	ITEMTYPE itemtype;		// type
	union {					// value
		BYTE bVal;
		CHAR cVal;
		WORD wVal;
		DWORD dwVal;
		LONG lVal;
		};
	TCHAR szName[64];		// name
	TCHAR szDesc[64];		// desc

	tag_ITEMDATA()
	{
		dwAddress = 0x00000000;
		itemtype = _BYTE;
		lVal = 0;
		memset(szName, 0x00, 64);
		memset(szDesc, 0x00, 64);
	}
}ITEMDATA;

// DATA
typedef union __DATA
{
	struct {BYTE b0,b1,b2,b3,b4,b5,b6,b7;}bValue;
	struct {WORD w0,w1,w2,w3;}wValue;
	struct {DWORD dw0,dw1;}dwValue;
	DOUBLE dVal;
}DATA;

#endif//__PEFILEHEADER_H_2459134951B94A1895E650CFD52F4215__
