/**
 * \file  Core.h
 * \brief common header for xLib
 */


/**
 * \mainpage
 *
 * This library is cross-platform and can be compiled and used on
 * Windows, Linux, BSD, Apple OS famalies (x86, x64)
 *
 * \author  author:  skynowa \n
 *          e-mail:  skynowa@gmail.com \n
 *          skype:   skynowa777 \n
 *          jabber:  skynowa@jabber.ru \n
 *          ICQ:     627713628 \n
 *          web:     https://bitbucket.org/skynowa/xlib
 *
 * \date    2008 - 2016
 *
 * \section sec_code_convention Code conventions
 */


#pragma once

// config
#include <xLib/Core/SysDefines.h>
#include <xLib/Core/Config.h>

// POSIX
#if xENV_UNIX
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

#if cmOPTION_CPP11
    #include <array>
    #include <forward_list>
    #include <unordered_map>
    #include <unordered_set>
#else
    // #include <xLib/Core/Array.h>
#endif

#include <vector>
#include <list>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <map>
#include <algorithm>
#include <iterator>
#include <utility>
#include <iomanip>
#include <cerrno>
#include <stdexcept>
#include <locale>

// xLib
namespace xlib
{
    namespace core {}
    namespace crypt {}
    namespace db {}
    namespace debug {}
    namespace io {}
    namespace ui {}
    namespace log {}
    namespace net {}
    namespace patterns {}
    namespace sync {}
    namespace system {}
    namespace test {}
    namespace package {}

    using namespace xlib::core;
    using namespace xlib::crypt;
    using namespace xlib::db;
    using namespace xlib::debug;
    using namespace xlib::io;
    using namespace xlib::ui;
    using namespace xlib::log;
    using namespace xlib::net;
    using namespace xlib::patterns;
    using namespace xlib::sync;
    using namespace xlib::system;
    using namespace xlib::test;
    using namespace xlib::package;
}

namespace xl = xlib;

#include <xLib/Core/Preprocessor.h>
#include <xLib/Core/Defines.h>
#include <xLib/Core/Limits.h>

#if   xENV_WIN
    #include "Platform/Win/Core_win.h"
#elif xENV_UNIX
    #include "Platform/Unix/Core_unix.h"

    #if   xENV_LINUX
        #if   xOS_ANDROID
            #include "Platform/Linux/Core_android.h"
        #elif xOS_LINUX
            #include "Platform/Linux/Core_linux.h"
        #endif
    #elif xENV_BSD
        #include "Platform/Bsd/Core_bsd.h"
    #elif xENV_APPLE
        #include "Platform/Apple/Core_apple.h"
    #endif
#endif

#include <xLib/Core/Version.h>
#include <xLib/Core/Types.h>
#include <xLib/Internal/Internal.h>    // internal
#include <xLib/Core/Functions.h>
