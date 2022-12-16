/**
 * \file  SystemInfo.inl
 * \brief system information
 */


#include "SystemInfo.h"

#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>
#include <xLib/Core/Format.h>
#include <xLib/Core/Utils.h>
#include <xLib/Fs/Path.h>
#include <xLib/Fs/Dir.h>
#include <xLib/Fs/Dll.h>
#include <xLib/Fs/File.h>
#include <xLib/System/Environment.h>

#if   xENV_WIN
    #include "Platform/Win/SystemInfo_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/SystemInfo_unix.inl"

    #if   xENV_LINUX
        #include "Platform/Linux/SystemInfo_linux.inl"
    #elif xENV_BSD
        #include "Platform/Bsd/SystemInfo_bsd.inl"
    #elif xENV_APPLE
        #include "Platform/Apple/SystemInfo_apple.inl"
    #endif
#endif


namespace xl::system
{

/**************************************************************************************************
*    public - OS
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
SystemInfo::OsType
SystemInfo::os() const
{
    return _os_impl();
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
SystemInfo::formatOs() const
{
    return _formatOs_impl();
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
SystemInfo::distro() const
{
    return _distro_impl();
}
//-------------------------------------------------------------------------------------------------
SystemInfo::OsArch
SystemInfo::osArch() const
{
    return _osArch_impl();
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
SystemInfo::formatOsArch() const
{
    std::tstring_t sRv;

    cOsArch arch = osArch();
    switch (arch) {
    case OsArch::Bit32:
        sRv = xT("32-bit");
        break;
    case OsArch::Bit64:
        sRv = xT("64-bit");
        break;
    case OsArch::Unknown:
        sRv = Const::strUnknown();
        break;
    default:
        sRv = Const::strUnknown();
        break;
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
SystemInfo::desktopName() const
{
    return _desktopName_impl();
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public - Users
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
std::tstring_t
SystemInfo::hostName() const
{
    return _hostName_impl();
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public - CPU
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
ulong_t
SystemInfo::cpusNum() const
{
    return _cpusNum_impl();
}
//-------------------------------------------------------------------------------------------------
ulong_t
SystemInfo::currentCpuNum() const
{
    return _currentCpuNum_impl();
}
//-------------------------------------------------------------------------------------------------
SystemInfo::CpuVendor
SystemInfo::cpuVendor() const
{
    CpuVendor       cvRv  = CpuVendor::Unknown;
    std::ctstring_t value = _cpuVendor_impl();

    if      (value == std::tstring_t(xT("GenuineIntel"))) {
        cvRv = CpuVendor::Intel;
    }
    else if (value == std::tstring_t(xT("AuthenticAMD"))) {
        cvRv = CpuVendor::Amd;
    }
    else {
        cvRv = CpuVendor::Unknown;
    }

    return cvRv;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
SystemInfo::cpuModel() const
{
    return _cpuModel_impl();
}
//-------------------------------------------------------------------------------------------------
ulong_t
SystemInfo::cpuSpeed() const
{
    return _cpuSpeed_impl();
}
//-------------------------------------------------------------------------------------------------
ulong_t
SystemInfo::cpuUsage() const
{
    return _cpuUsage_impl();
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public - RAM
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
ulonglong_t
SystemInfo::ramTotal() const
{
    return _ramTotal_impl();
}
//-------------------------------------------------------------------------------------------------
ulonglong_t
SystemInfo::ramAvailable() const
{
    return _ramAvailable_impl();
}
//-------------------------------------------------------------------------------------------------
ulong_t
SystemInfo::ramUsage() const
{
    return _ramUsage_impl();
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public - HDD
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
ulong_t
SystemInfo::pageSize() const
{
    return _pageSize_impl();
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public - Power supply
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
bool_t
SystemInfo::isPowerSupply() const
{
    return _isPowerSupply_impl();
}
//-------------------------------------------------------------------------------------------------
std::size_t
SystemInfo::powerSupplyLevel() const
{
	xCHECK_RET(!isPowerSupply(), 0);

    return _powerSupplyLevel_impl();
}
//-------------------------------------------------------------------------------------------------
SystemInfo::PowerSupplyStatus
SystemInfo::powerSupplyStatus() const
{
	xCHECK_RET(!isPowerSupply(), PowerSupplyStatus::Unknown);

    return _powerSupplyStatus_impl();
}
//-------------------------------------------------------------------------------------------------

} // namespace
