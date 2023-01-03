/**
 * \file  Host.cpp
 * \brief system information
 */


#include "Host.h"

#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>
#include <xLib/Core/Format.h>
#include <xLib/Core/Utils.h>
//#include <xLib/Fs/Path.h>
//#include <xLib/Fs/Dir.h>
//#include <xLib/Fs/Dll.h>
//#include <xLib/Fs/File.h>
//#include <xLib/System/Environment.h>
//#include <xLib/System/Info/Os.h>

#if   xENV_WIN
    #include <xLib/System/Info/Platform/Win/Host_win.inl>
#elif xENV_UNIX
    #include <xLib/System/Info/Platform/Unix/Host_unix.inl>

    #if   xENV_LINUX
        #include <xLib/System/Info/Platform/Linux/Host_linux.inl>
    #elif xENV_BSD
        #include <xLib/System/Info/Platform/Bsd/Host_bsd.inl>
    #elif xENV_APPLE
        #include <xLib/System/Info/Platform/Apple/Host_apple.inl>
    #endif
#endif


namespace xl::system::info
{

//-------------------------------------------------------------------------------------------------
std::tstring_t
Host::hostName() const
{
    return _hostName_impl();
}
//-------------------------------------------------------------------------------------------------

} // namespace
