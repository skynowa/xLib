/****************************************************************************
* Class name:  xLog.h
* Description: �� �����������
* File name:   CxTraceLog.h
* Compilers:   Visual C++ 2008
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     01.06.2009 17:45:21
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef xLib_Log_xLogH
#define xLib_Log_xLogH
//---------------------------------------------------------------------------
#include <xLib/Log/CxConsoleLog.h>
#include <xLib/Log/CxDbLog.h>
#include <xLib/Log/CxFileLog.h>
#include <xLib/Log/CxTraceLog.h>

#if defined(xOS_WIN)
    #include <xLib/Log/Win/CxEventLog.h>
    #include <xLib/Log/Win/CxWndLog.h>
#elif defined(xOS_LINUX)

#endif
//---------------------------------------------------------------------------
#endif	//xLib_Log_xLogH
