//*-----------------------------------------------------------------------------*/
//* Copyright(C) 2014, liujiquan Company All rights reserved. )
//* FileName :   SharedDll.h
//* Author   :   liujiquan
//* DateTime :   10/15/2014
//* Version  :   1.0
//* Comment  :   
//*-----------------------------------------------------------------------------*/
#ifndef __SHAREDDLL_H_2459134951B94A1895E650CFD52F4215__
#define __SHAREDDLL_H_2459134951B94A1895E650CFD52F4215__
#pragma once

#ifdef SHAREDDLL_EXPORTS
#define SHAREDDLL_API __declspec(dllexport)
#else
#define SHAREDDLL_API __declspec(dllimport)
#endif


SHAREDDLL_API LPCTSTR fnSharedDll(void);

#endif//__SHAREDDLL_H_2459134951B94A1895E650CFD52F4215__