/**
 * \file  Core.h
 * \brief common header for xLib
 */


#pragma once

//-------------------------------------------------------------------------------------------------
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
	/// xLib namespace
{

namespace core {}
namespace interface_ {}
namespace crypt {}
namespace db {}
namespace debug {}
namespace fs {}
namespace algos {}
namespace log {}
namespace net {}
namespace patterns {}
namespace sync {}
namespace system {}
namespace test {}
namespace package {}

} // namespace xl

using namespace xl::core;
using namespace xl::interface_;
using namespace xl::crypt;
using namespace xl::db;
using namespace xl::debug;
using namespace xl::fs;
using namespace xl::algos;
using namespace xl::log;
using namespace xl::net;
using namespace xl::patterns;
using namespace xl::sync;
using namespace xl::system;
using namespace xl::test;
using namespace xl::package;

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
#include <xLib/Core/Type/Types.h>
#include <xLib/Internal/Internal.h>    // internal
#include <xLib/Core/Functions.h>
//-------------------------------------------------------------------------------------------------
