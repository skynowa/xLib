/**
 * \file  Storage.cpp
 * \brief Storage information
 */


#include "Storage.h"

#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>
#include <xLib/Core/Format.h>
#include <xLib/Core/Utils.h>

#if   xENV_WIN
    #include <xLib/System/Info/Platform/Win/Storage_win.inl>
#elif xENV_UNIX
    #include <xLib/System/Info/Platform/Unix/Storage_unix.inl>

    #if   xENV_LINUX
        #include <xLib/System/Info/Platform/Linux/Storage_linux.inl>
    #elif xENV_BSD
        #include <xLib/System/Info/Platform/Bsd/Storage_bsd.inl>
    #elif xENV_APPLE
        #include <xLib/System/Info/Platform/Apple/Storage_apple.inl>
    #endif
#endif


namespace xl::system::info
{

//-------------------------------------------------------------------------------------------------
ulong_t
Storage::pageSize() const
{
    return _pageSize_impl();
}
//-------------------------------------------------------------------------------------------------

} // namespace
