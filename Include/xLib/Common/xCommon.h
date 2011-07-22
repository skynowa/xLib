/****************************************************************************
* Class name:  CxCommon
* Description: common header for xLib
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     23.12.2010 23:24:26
*
*****************************************************************************/


#ifndef xLib_Common_xCommonH
#define xLib_Common_xCommonH
//---------------------------------------------------------------------------
//config
#include <xLib/Common/xConfig.h>
#include <xLib/Common/xDefines.h>

//tracing
#include <xLib/Common/xTracing.h>

//C library
#include <stdio.h>
#include <stdlib.h>
#include <cctype>
#include <cstring>
#include <ctime>
#include <errno.h>
#include <stdarg.h>
#include <time.h>
#include <stddef.h>
#include <math.h>
#include <limits.h>

#if defined(xIS_STL_ASSERTING)
    #include <assert.h>
#endif

#if defined(xUNICODE)
    #include <wchar.h>
    #include <wctype.h>
#endif

//stl
#include <typeinfo>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>
#include <utility>
#include <iomanip>
#include <cerrno>
#include <limits>
#include <stdexcept>

//POSIX
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

//xLib
namespace NxLib {}
#ifndef xNO_USING_NAMESPACE
    using namespace NxLib;
#endif

#if defined(xOS_WIN)
    #include <xLib/Common/Win/xCommon_Win.h>
#elif defined(xOS_LINUX)
    #include <xLib/Common/Linux/xCommon_Linux.h>
#endif

#include <xLib/Common/xTypes.h>
#include <xLib/Common/xLinking.h>
#include <xLib/Common/CxMacros.h>
#include <xLib/Common/CxConst.h>
#include <xLib/Common/CxNonCopyable.h>
#include <xLib/Debug/xDebug.h>
#include <xLib/Common/CxString.h>

//checks
#include <xLib/Common/xCheks.h>

#if !defined(__FILE__)
    #error xLib: __FILE__ not defined
#endif

#if !defined(__LINE__)
    #error xLib: __LINE__ not defined
#endif

#if !defined(xFUNCTION)
    #error xLib: xFUNCTION not defined
#endif

#if !defined(__DATE__)
    #error xLib: __DATE__ not defined
#endif

#if !defined(__TIME__)
    #error xLib: __TIME__ not defined
#endif

//#if !defined(__COUNTER__)
//    #error xLib: COUNTER not defined
//#endif
//---------------------------------------------------------------------------
#endif  //xLib_Common_xCommonH
