/**
 * \file  Net.cpp
 * \brief system information
 */


#include "Net.h"

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
    #include <xLib/System/Info/Platform/Win/Net_win.inl>
#elif xENV_UNIX
    #include <xLib/System/Info/Platform/Unix/Net_unix.inl>

    #if   xENV_LINUX
        #include <xLib/System/Info/Platform/Linux/Net_linux.inl>
    #elif xENV_BSD
        #include <xLib/System/Info/Platform/Bsd/Net_bsd.inl>
    #elif xENV_APPLE
        #include <xLib/System/Info/Platform/Apple/Net_apple.inl>
    #endif
#endif


namespace xl::system::info
{

//-------------------------------------------------------------------------------------------------
bool_t
Net::isVpnActive() const
{
    return _isVpnActive_impl();
}
//-------------------------------------------------------------------------------------------------

} // namespace
