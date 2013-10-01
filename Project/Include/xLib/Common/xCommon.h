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
 * \author  author:  skynowa \n
 *          e-mail:  skynowa@gmail.com \n
 *          skype:   skynowa777 \n
 *          jabber:  skynowa@jabber.ru \n
 *          ICQ:     627713628 \n
 *          web:     https://bitbucket.org/skynowa/xlib
 *
 * \date    2008 - 2013
 *
 * \section sec_code_convention Code conventions
 *
 * <pre>
 *   Data:
 *       Nx*          - namespace
 *       Cx*          - class
 *       Sx*          - struct
 *       Ux*          - union
 *       Ex*          - enumeration
 *       p*           - pointer
 *       *T           - template
 *       *_t          - type
 *
 *   Access:
 *       g_*          - global
 *       s_*          - static
 *       m_*          - member of some data structure
 *       fr_*         - friend
 *       a_*          - function param
 *
 *   Modify:
 *       c*           - const
 *       v*           - volatile
 *       m*           - mutable
 *
 *   Types:
 *       a*           - array
 *
 *       v*           - void_t
 *       b*           - bool_t
 *
 *       i*           - int_t
 *       ui*          - unsigned int_t
 *       uc*          - uchar_t                  (unsigned char)
 *       si*          - short_t                  (short int_t)
 *       li*          - long_t                   (long int_t)
 *       lli*         - longlong_t               (long long int_t)
 *       ui*          - uint_t                   (unsigned int_t)
 *       us*          - ushort_t                 (unsigned short int_t)
 *       ul*          - ulong_t                  (unsigned long int_t)
 *       ull*         - ulonglong_t              (unsigned long long int_t)
 *
 *       f*           - float_t
 *       d*           - double
 *       ld*          - long double
 *
 *       sz*          - C-string
 *
 *   STL types:
 *       s*           - std::tstring_t           (std::string)
 *       us*          - std::ustring_t           (std::ustring)
 *
 *       ism*         - std::tistream_t          (std::istream)
 *       osm*         - std::tostream_t          (std::ostream)
 *       iosm*        - std::tiostream_t         (std::iostream)
 *
 *       issm*        - std::tistringstream_t    (std::istringstream)
 *       ossm*        - std::tostringstream_t    (std::ostringstream)
 *       ssm*         - std::tstringstream_t     (std::stringstream)
 *
 *       ifsm*        - std::tifstream_t         (std::ifstream)
 *       ofsm*        - std::tofstream_t         (std::ofstream)
 *       fsm*         - std::tfstream_t          (std::fstream)
 *
 *       v[type]*     - std::vector
 *       d[type]*     - std::deque
 *       l[type]*     - std::list
 *
 *       st[type]*    - std::stack
 *       q[type]*     - std::queue
 *       pq[type]*    - std::priority_queue
 *
 *       s[type]*     - std::set
 *       ms[type]*    - std::multiset
 *       m[type]*     - std::map
 *       mm[type]*    - std::multimap
 *       bs[type]*    - std::bitset
 * </pre>
 *
 */


#pragma once

// config
#include <xLib/Common/xSysDefines.h>
#include <xLib/Common/xConfig.h>

// POSIX
#if !xOS_WIN
    #include <unistd.h>
#endif

#include <sys/types.h>  // must be at the top (it's portable)
#include <fcntl.h>
#include <sys/stat.h>

// C library
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <ctime>
#include <cerrno>
#include <cstdarg>
#include <cstddef>
#include <cmath>
#include <climits>
#include <cassert>
#include <clocale>

#if xUNICODE
    #include <cwchar>
    #include <cwctype>
#endif

// STL
#include <typeinfo>
#include <limits>
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
#include <stdexcept>

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
#elif xOS_ENV_MAC
    #include <xLib/Common/xCommon_Darwin.h>
#endif

#include <xLib/Common/xVersion.h>
#include <xLib/Common/xTypes.h>
#include <xLib/Common/xFunctions.h>
#include <xLib/Common/CxConst.h>
#include <xLib/Common/CxNonCopyable.h>
#include <xLib/Common/CxNonAssignable.h>
#include <xLib/Common/CxNonHeap.h>
#include <xLib/Common/CxNonArrayHeap.h>
#include <xLib/Common/CxUtils.h>
#include <xLib/Debug/xDebug.h>
#include <xLib/Debug/CxException.h>

#include <xLib/Common/xTracing.h>
#include <xLib/Common/xLinking.h>
