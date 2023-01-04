/**
 * \file  Ram.cpp
 * \brief RAM information
 */


#include "Ram.h"

#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>
#include <xLib/Core/Format.h>
#include <xLib/Core/Utils.h>

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
Ram::total() const
{
    return _total_impl();
}
//-------------------------------------------------------------------------------------------------
ulonglong_t
Ram::available() const
{
    return _available_impl();
}
//-------------------------------------------------------------------------------------------------
ulong_t
Ram::usage() const
{
    return _usage_impl();
}
//-------------------------------------------------------------------------------------------------

} // namespace
