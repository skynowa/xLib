/**
 * \file  SystemInfo.inl
 * \brief system information
 */


#if !cmOPTION_PROJECT_HEADER_ONLY
    #include "SystemInfo.h"
#endif

#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>
#include <xLib/Core/Format.h>
#include <xLib/Core/Utils.h>
#include <xLib/Fs/Path.h>
#include <xLib/Fs/Dll.h>
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


xNAMESPACE_BEGIN2(xl, system)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE
SystemInfo::SystemInfo() :
    _osType(otUnknown),
    _osArch(oaUnknown)
{
}
//-------------------------------------------------------------------------------------------------
xINLINE SystemInfo::OsType
SystemInfo::os()
{
    return _os_impl();
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
SystemInfo::formatOs()
{
    return _formatOs_impl();
}
//-------------------------------------------------------------------------------------------------
xINLINE SystemInfo::OsArch
SystemInfo::osArch()
{
    _osArch = _osArch_impl();

    return _osArch;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
SystemInfo::formatOsArch()
{
    std::tstring_t sRv;

    OsArch arch = (_osArch == oaUnknown) ? osArch() : _osArch;
    switch (arch) {
    case SystemInfo::oa32bit:
        sRv = xT("32-bit");
        break;
    case SystemInfo::oa64bit:
        sRv = xT("64-bit");
        break;
    case SystemInfo::oaUnknown:
        sRv = Const::strUnknown();
        break;
    default:
        sRv = Const::strUnknown();
        break;
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
SystemInfo::desktopName() const
{
    return _desktopName_impl();
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
SystemInfo::hostName() const
{
    return _hostName_impl();
}
//-------------------------------------------------------------------------------------------------
xINLINE ulong_t
SystemInfo::numOfCpus() const
{
    return _numOfCpus_impl();
}
//-------------------------------------------------------------------------------------------------
xINLINE ulong_t
SystemInfo::currentCpuNum() const
{
    return _currentCpuNum_impl();
}
//-------------------------------------------------------------------------------------------------
xINLINE SystemInfo::CpuVendor
SystemInfo::cpuVendor() const
{
    CpuVendor     cvRv  = cvUnknown;
    std::ctstring_t value = _cpuVendor_impl();

    if      (value == std::tstring_t(xT("GenuineIntel"))) {
        cvRv = cvIntel;
    }
    else if (value == std::tstring_t(xT("AuthenticAMD"))) {
        cvRv = cvAmd;
    }
    else {
        cvRv = cvUnknown;
    }

    return cvRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
SystemInfo::cpuModel() const
{
    return _cpuModel_impl();
}
//-------------------------------------------------------------------------------------------------
xINLINE ulong_t
SystemInfo::cpuSpeed() const
{
    return _cpuSpeed_impl();
}
//-------------------------------------------------------------------------------------------------
xINLINE ulong_t
SystemInfo::cpuUsage() const
{
    return _cpuUsage_impl();
}
//-------------------------------------------------------------------------------------------------
xINLINE ulonglong_t
SystemInfo::ramTotal() const
{
    return _ramTotal_impl();
}
//-------------------------------------------------------------------------------------------------
xINLINE ulonglong_t
SystemInfo::ramAvailable() const
{
    return _ramAvailable_impl();
}
//-------------------------------------------------------------------------------------------------
xINLINE ulong_t
SystemInfo::ramUsage() const
{
    return _ramUsage_impl();
}
//-------------------------------------------------------------------------------------------------
xINLINE ulong_t
SystemInfo::pageSize() const
{
    return _pageSize_impl();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, system)
