/**
 * \file  Libs.cpp
 * \brief system information
 */


#include "Libs.h"

#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>
#include <xLib/Core/Format.h>
#include <xLib/Core/Utils.h>

#if   xENV_WIN
    #include <xLib/System/Info/Platform/Win/Libs_win.inl>
#elif xENV_UNIX
    #include <xLib/System/Info/Platform/Unix/Libs_unix.inl>

    #if   xENV_LINUX
        #include <xLib/System/Info/Platform/Linux/Libs_linux.inl>
    #elif xENV_BSD
        #include <xLib/System/Info/Platform/Bsd/Libs_bsd.inl>
    #elif xENV_APPLE
        #include <xLib/System/Info/Platform/Apple/Libs_apple.inl>
    #endif
#endif


namespace xl::system::info
{

} // namespace
