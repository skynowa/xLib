/**
 * \file  xCommon.h
 * \brief common header for xLib
 */

/**
 * \mainpage
 *
 * This library is cross-platform and can be compiled and used on
 * Linux, BSD and Windows
 *
 * \author  skynowa@gmail.com
 * \date    2008 - 2011
 * \section Samples
 * \ref     Units
 */


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

#if xIS_STL_ASSERTING
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
namespace NxLib { }

#if xUSING_NAMESPACE
    using namespace NxLib;
#endif

#if defined(xOS_WIN)
    #include <xLib/Common/Win/xCommon_Win.h>
#elif defined(xOS_LINUX)
    #include <xLib/Common/Linux/xCommon_Linux.h>
#endif

#include <xLib/Common/xTypes.h>
#include <xLib/Common/xFunctions.h>
#include <xLib/Common/xLinking.h>
#include <xLib/Common/CxMacros.h>
#include <xLib/Common/CxConst.h>
#include <xLib/Common/CxNonCopyable.h>
#include <xLib/Debug/xDebug.h>
#include <xLib/Common/CxString.h>
#include <xLib/Common/CxConsole.h>

//checks
#include <xLib/Common/xCheks.h>
//---------------------------------------------------------------------------
#endif  //xLib_Common_xCommonH
