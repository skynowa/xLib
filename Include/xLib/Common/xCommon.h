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

//POSIX
#include <sys/types.h>  //must be at the top (it's portable)
#include <fcntl.h>
#include <sys/stat.h>

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
#include <assert.h>

#if xUNICODE
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
#include <locale.h>

//xLib
namespace NxLib { }

#if xUSING_NAMESPACE_NXLIB
    using namespace NxLib;
#endif

#if xOS_ENV_WIN
    #include <xLib/Common/Win/xCommon_Win.h>
#elif xOS_ENV_UNIX
    #include <xLib/Common/Linux/xCommon_Unix.h>
#endif

#include <xLib/Common/xFunctions.h>
#include <xLib/Common/xLinking.h>
#include <xLib/Common/CxMacros.h>
#include <xLib/Common/xTypes.h>

#include <xLib/Common/CxConst.h>
#include <xLib/Common/CxNonCopyable.h>
#include <xLib/Debug/xDebug.h>
#include <xLib/Common/CxString.h>
#include <xLib/Common/CxConsole.h>

//checks
#include <xLib/Common/xCheks.h>
//---------------------------------------------------------------------------
#endif  //xLib_Common_xCommonH
