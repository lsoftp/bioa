//---------------------------------------------------------------------------
#ifndef _DEBUGPRINTF_H_
#define _DEBUGPRINTF_H_

#include<windows.h>
#include <tchar.h>
#include <stdio.h>
#include "LogFile.h"
//用于输出信息到编译器输出窗口的宏定义
//使用win API，DEBUG版本会执行，RELEASE版本则不会
//还可以使用DebugView，WinDbg等工具查看输出

#ifdef _DEBUG

#define DP(fmt,...) {TCHAR sOut[1024];_stprintf_s(sOut,512,_T(fmt),##__VA_ARGS__);OutputDebugString(sOut);}
#define DP0(fmt) {TCHAR sOut[512];_stprintf_s(sOut,512,_T(fmt));OutputDebugString(sOut);}
#define DP1(fmt,var) {TCHAR sOut[512];_stprintf_s(sOut,512,_T(fmt),var);OutputDebugString(sOut);}
#define DP2(fmt,var1,var2) {TCHAR sOut[512];_stprintf_s(sOut,512,_T(fmt),var1,var2);OutputDebugString(sOut);}
#define DP3(fmt,var1,var2,var3) {TCHAR sOut[512];_stprintf_s(sOut,512,_T(fmt),var1,var2,var3);OutputDebugString(sOut);}

#endif

#ifndef _DEBUG

#define DP(fmt,...)
#define DP0(fmt) ;
#define DP1(fmt, var) ;
#define DP2(fmt,var1,var2) ;
#define DP3(fmt,var1,var2,var3) ;

#endif


#ifdef _DEBUG
#define LOG(format,...) {char mybuf[1024]; sprintf(mybuf,format,##__VA_ARGS__); g_log.Log(mybuf);}
#else
#define LOG(format,... )
#endif

#endif
