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
#include <xLib/Config.h>

// POSIX
#if xENV_UNIX
    #include <unistd.h>
#endif

#include <sys/types.h>  // must be at the top (it's portable)
#include <fcntl.h>
#include <sys/stat.h>

// STL
#include <xLib/Core/Stl.h>

// xLib
namespace xl
{

namespace core {}
namespace crypt {}
namespace db {}
namespace debug {}
namespace fs {}
namespace ui {}
namespace log {}
namespace net {}
namespace patterns {}
namespace sync {}
namespace system {}
namespace test {}
namespace package {}

using namespace core;
using namespace crypt;
using namespace db;
using namespace debug;
using namespace fs;
using namespace ui;
using namespace log;
using namespace net;
using namespace patterns;
using namespace sync;
using namespace system;
using namespace test;
using namespace package;

} // namespace xl

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
