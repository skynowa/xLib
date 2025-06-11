/**
 * \file  PowerSupply.cpp
 * \brief Power supply information
 */


#include "PowerSupply.h"

#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>
#include <xLib/Core/Format.h>
#include <xLib/Core/Utils.h>
#include <xLib/Fs/Dir.h>
#include <xLib/Fs/FileIO.h>
#include <xLib/Log/LogStream.h>

#if   xENV_WIN
    #include <xLib/System/Info/Platform/Win/PowerSupply_win.inl>
#elif xENV_UNIX
    #include <xLib/System/Info/Platform/Unix/PowerSupply_unix.inl>

    #if   xENV_LINUX
        #include <xLib/System/Info/Platform/Linux/PowerSupply_linux.inl>
    #elif xENV_BSD
        #include <xLib/System/Info/Platform/Bsd/PowerSupply_bsd.inl>
    #elif xENV_APPLE
        #include <xLib/System/Info/Platform/Apple/PowerSupply_apple.inl>
    #endif
#endif


namespace xl::system::info
{

//-------------------------------------------------------------------------------------------------
bool_t
PowerSupply::isExists() const
{
    return _isExists_impl();
}
//-------------------------------------------------------------------------------------------------
std::size_t
PowerSupply::level() const
{
	xCHECK_RET(!isExists(), 0);

    return _level_impl();
}
//-------------------------------------------------------------------------------------------------
PowerSupply::Status
PowerSupply::status() const
{
	xCHECK_RET(!isExists(), Status::Unknown);

    return _status_impl();
}
//-------------------------------------------------------------------------------------------------

} // namespace
