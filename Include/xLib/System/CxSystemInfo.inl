/**
 * \file  CxSystemInfo.inl
 * \brief system information
 */


#include <xLib/Core/CxConst.h>
#include <xLib/Core/CxString.h>
#include <xLib/Core/CxUtils.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxDll.h>
#include <xLib/System/CxEnvironment.h>

#if   xENV_WIN
    #include "Platform/Win/CxSystemInfo_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/CxSystemInfo_unix.inl"

    #if   xENV_LINUX
        #include "Platform/Linux/CxSystemInfo_linux.inl"
    #elif xENV_BSD
        #include "Platform/Bsd/CxSystemInfo_bsd.inl"
    #elif xENV_APPLE
        #include "Platform/Apple/CxSystemInfo_apple.inl"
    #endif
#endif


xNAMESPACE_BEGIN2(xlib, system)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxSystemInfo::CxSystemInfo() :
    _osType(otUnknown),
    _osArch(oaUnknown)
{
}
//-------------------------------------------------------------------------------------------------
inline CxSystemInfo::ExOsType
CxSystemInfo::os()
{
    return _os_impl();
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxSystemInfo::formatOs()
{
    return _formatOs_impl();
}
//-------------------------------------------------------------------------------------------------
inline CxSystemInfo::ExOsArch
CxSystemInfo::osArch()
{
    _osArch = _osArch_impl();

    return _osArch;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxSystemInfo::formatOsArch()
{
    std::tstring_t sRv;

    ExOsArch arch = (_osArch == oaUnknown) ? osArch() : _osArch;
    switch (arch) {
    case CxSystemInfo::oa32bit:
        sRv = xT("32-bit");
        break;
    case CxSystemInfo::oa64bit:
        sRv = xT("64-bit");
        break;
    case CxSystemInfo::oaUnknown:
        sRv = CxConst::strUnknown();
        break;
    default:
        sRv = CxConst::strUnknown();
        break;
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxSystemInfo::desktopName() const
{
    return _desktopName_impl();
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxSystemInfo::hostName() const
{
    return _hostName_impl();
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxSystemInfo::isUserAdmin() const
{
    return _isUserAdmin_impl();
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxSystemInfo::loginUserName() const
{
    return _loginUserName_impl();
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxSystemInfo::userName() const
{
    return _userName_impl();
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxSystemInfo::userHomeDir() const
{
    return _userHomeDir_impl();
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxSystemInfo::userShellPath() const
{
    return _userShellPath_impl();
}
//-------------------------------------------------------------------------------------------------
inline ulong_t
CxSystemInfo::numOfCpus() const
{
    return _numOfCpus_impl();
}
//-------------------------------------------------------------------------------------------------
inline ulong_t
CxSystemInfo::currentCpuNum() const
{
    return _currentCpuNum_impl();
}
//-------------------------------------------------------------------------------------------------
inline CxSystemInfo::ExCpuVendor
CxSystemInfo::cpuVendor() const
{
    ExCpuVendor     cvRv  = cvUnknown;
    std::ctstring_t value = _cpuVendor_impl();

    if      (value == std::tstring_t("GenuineIntel")) {
        cvRv = cvIntel;
    }
    else if (value == std::tstring_t("AuthenticAMD")) {
        cvRv = cvAmd;
    }
    else {
        cvRv = cvUnknown;
    }

    return cvRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxSystemInfo::cpuModel() const
{
    return _cpuModel_impl();
}
//-------------------------------------------------------------------------------------------------
inline ulong_t
CxSystemInfo::cpuSpeed() const
{
    return _cpuSpeed_impl();
}
//-------------------------------------------------------------------------------------------------
inline ulong_t
CxSystemInfo::cpuUsage() const
{
    return _cpuUsage_impl();
}
//-------------------------------------------------------------------------------------------------
inline ulonglong_t
CxSystemInfo::ramTotal() const
{
    return _ramTotal_impl();
}
//-------------------------------------------------------------------------------------------------
inline ulonglong_t
CxSystemInfo::ramAvailable() const
{
    return _ramAvailable_impl();
}
//-------------------------------------------------------------------------------------------------
inline ulong_t
CxSystemInfo::ramUsage() const
{
    return _ramUsage_impl();
}
//-------------------------------------------------------------------------------------------------
inline ulong_t
CxSystemInfo::pageSize() const
{
    return _pageSize_impl();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, system)
