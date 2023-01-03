/**
 * \file  Ram.cpp
 * \brief system information
 */


#include "Ram.h"

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
    #include <xLib/System/Info/Platform/Win/Ram_win.inl>
#elif xENV_UNIX
    #include <xLib/System/Info/Platform/Unix/Ram_unix.inl>

    #if   xENV_LINUX
        #include <xLib/System/Info/Platform/Linux/Ram_linux.inl>
    #elif xENV_BSD
        #include <xLib/System/Info/Platform/Bsd/Ram_bsd.inl>
    #elif xENV_APPLE
        #include <xLib/System/Info/Platform/Apple/Ram_apple.inl>
    #endif
#endif


namespace xl::system::info
{

//-------------------------------------------------------------------------------------------------
ulonglong_t
Ram::ramTotal() const
{
    return _ramTotal_impl();
}
//-------------------------------------------------------------------------------------------------
ulonglong_t
Ram::ramAvailable() const
{
    return _ramAvailable_impl();
}
//-------------------------------------------------------------------------------------------------
ulong_t
Ram::ramUsage() const
{
    return _ramUsage_impl();
}
//-------------------------------------------------------------------------------------------------

} // namespace
