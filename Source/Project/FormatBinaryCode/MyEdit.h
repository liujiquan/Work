//*-----------------------------------------------------------------------------*/
//* Copyright(C) 2014, liujiquan Company All rights reserved. )
//* FileName :   MyEdit.h
//* Author   :   liujiquan
//* DateTime :   10/9/2014
//* Version  :   1.0
//* Comment  :   
//*-----------------------------------------------------------------------------*/
#ifndef __MYEDIT_H_2459134951B94A1895E650CFD52F4215__
#define __MYEDIT_H_2459134951B94A1895E650CFD52F4215__
#pragma once

class CMyEdit : public CEdit
{
public:
	CMyEdit();
	~CMyEdit();

	DECLARE_MESSAGE_MAP()
public:
	void InitHotKey();
	LRESULT OnHotKey(LPARAM lprarm, WPARAM wparam);
	void OnKeyDown(UINT a, UINT b, UINT c);
	
};


#endif//__MYEDIT_H_2459134951B94A1895E650CFD52F4215__
