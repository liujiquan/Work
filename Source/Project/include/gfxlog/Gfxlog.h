//*-----------------------------------------------------------------------------*/
//* Copyright(C) 2014, liujiquan Company All rights reserved. )
//* FileName :   Gfxlog.h
//* Author   :   liujiquan
//* DateTime :   11/19/2014
//* Version  :   1.0
//* Comment  :   
//*-----------------------------------------------------------------------------*/
#ifndef __GFXLOG_H_2459134951B94A1895E650CFD52F4215__
#define __GFXLOG_H_2459134951B94A1895E650CFD52F4215__
#pragma once

//#ifdef GFXLOG 
//#define GFXLOG_FUNC extern "C"	__declspec( dllexport )
//#else 
//#define GFXLOG_FUNC	extern "C"  __declspec( dllimport )
//#endif

void GfxPutLog(const char *format,...);
void GfxPutLog2(char *format,...);
void GfxPutLog3(char *newFileName,char *format,...);

#endif//__GFXLOG_H_2459134951B94A1895E650CFD52F4215__
