/**
 * \file  xCommon.h
 * \brief common header for xLib
 */


/**
 * \mainpage
 *
 * This library is cross-platform and can be compiled and used on
 * Linux, FreeBSD and Windows (x86, x64)
 *
 * \author  skynowa@gmail.com
 * \date    2008 - 2012
 *
 * \section sec_code_convention Code conventions
 *
 * <pre>
 *   Data:
 *       Nx          - namespace
 *       Cx          - class
 *       Sx          - struct
 *       Ux          - union
 *       Ex          - enumeration
 *       p           - pointer
 *       T           - template
 *       _t          - type
 *
 *   Access:
 *       g_          - global
 *       s_          - static
 *       m_          - member of some data structure
 *       fr_         - friend
 *       a_          - function param
 *
 *   Modify:
 *       c           - const
 *       v           - volatile
 *       m           - mutable
 *
 *   Types:
 *       a           - array
 *
 *       v           - void
 *       b           - bool
 *
 *       i           - int
 *       ui          - unsigned int
 *       uc          - uchar_t                  (unsigned char)
 *       si          - short_t                  (short int)
 *       li          - long_t                   (long int)
 *       lli         - longlong_t               (long long int)
 *       ui          - uint_t                   (unsigned int)
 *       us          - ushort_t                 (unsigned short int)
 *       ul          - ulong_t                  (unsigned long int)
 *       ull         - ulonglong_t              (unsigned long long int)
 *
 *       f           - float
 *       d           - double
 *       ld          - long double
 *
 *       sz          - C-string
 *
 *   STL types:
 *       s           - std::tstring_t           (std::string)
 *       us          - std::ustring_t           (std::ustring)
 *
 *       ism         - std::tistream_t          (std::istream)
 *       osm         - std::tostream_t          (std::ostream)
 *       iosm        - std::tiostream_t         (std::iostream)
 *
 *       issm        - std::tistringstream_t    (std::istringstream)
 *       ossm        - std::tostringstream_t    (std::ostringstream)
 *       ssm         - std::tstringstream_t     (std::stringstream)
 *
 *       ifsm        - std::tifstream_t         (std::ifstream)
 *       ofsm        - std::tofstream_t         (std::ofstream)
 *       fsm         - std::tfstream_t          (std::fstream)
 *
 *       v[type]     - std::vector
 *       d[type]     - std::deque
 *       l[type]     - std::list
 *
 *       st[type]    - std::stack
 *       q[type]     - std::queue
 *       pq[type]    - std::priority_queue
 *
 *       s[type]     - std::set
 *       ms[type]    - std::multiset
 *       m[type]     - std::map
 *       mm[type]    - std::multimap
 *       bs[type]    - std::bitset
 * </pre>
 *
 * \section sec_samples Samples
 * \ref     Units
 */


#ifndef xLib_Common_xCommonH
#define xLib_Common_xCommonH
//---------------------------------------------------------------------------
// config
#include <xLib/Common/xSysDefines.h>
#include <xLib/Common/xConfig.h>

// POSIX
#include <sys/types.h>  // must be at the top (it's portable)
#include <fcntl.h>
#include <sys/stat.h>

// C library
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

// STL
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

// xLib
namespace NxLib { }

#if xUSING_NAMESPACE_NXLIB
    using namespace NxLib;
#endif

#include <xLib/Common/xDefines.h>

#if   xOS_ENV_WIN
    #include <xLib/Common/xCommon_Win.h>
#elif xOS_ENV_UNIX
    #include <xLib/Common/xCommon_Unix.h>
#endif

#include <xLib/Common/xTypes.h>
#include <xLib/Common/xFunctions.h>
#include <xLib/Common/CxConst.h>
#include <xLib/Common/CxNonCopyable.h>
#include <xLib/Common/CxUtils.h>
#include <xLib/Debug/xDebug.h>

#include <xLib/Common/xTracing.h>
#include <xLib/Common/xCheks.h>
#include <xLib/Common/xLinking.h>
//---------------------------------------------------------------------------
#endif  //xLib_Common_xCommonH
