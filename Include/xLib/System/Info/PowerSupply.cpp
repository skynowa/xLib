/**
 * \file  PowerSupply.cpp
 * \brief system information
 */


#include "PowerSupply.h"

#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>
#include <xLib/Core/Format.h>
#include <xLib/Core/Utils.h>
#include <xLib/Fs/Dir.h>
#include <xLib/Fs/FileIO.h>

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
PowerSupply::isPowerSupply() const
{
    return _isPowerSupply_impl();
}
//-------------------------------------------------------------------------------------------------
std::size_t
PowerSupply::powerSupplyLevel() const
{
	xCHECK_RET(!isPowerSupply(), 0);

    return _powerSupplyLevel_impl();
}
//-------------------------------------------------------------------------------------------------
PowerSupply::PowerSupplyStatus
PowerSupply::powerSupplyStatus() const
{
	xCHECK_RET(!isPowerSupply(), PowerSupplyStatus::Unknown);

    return _powerSupplyStatus_impl();
}
//-------------------------------------------------------------------------------------------------

} // namespace
