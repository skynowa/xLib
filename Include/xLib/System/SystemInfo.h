/**
 * \file  SystemInfo.h
 * \brief system information
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, system)

class SystemInfo
    /// system information
{
public:
    enum ExOsType
        /// OS type
    {
        otUnknown,
        // windows family
        otWindows3,
        otWindows95,
        otWindows98,
        otWindowsNT,
        otWindows2000,
        otWindowsXP,
        otWindowsXPProx64Edition,
        otWindowsServer2003,
        otWindowsHomeServer,
        otWindowsServer2003R2,
        otWindowsVista,
        otWindowsServer2008,
        otWindowsServer2008R2,
        otWindows7,
        // Linux  family
        otLinux,
        // BSD family
        otFreeBSD,
        // Apple family
        otMac
    };

    enum ExOsArch
        /// OS architecture
    {
        oaUnknown,
        oa32bit,
        oa64bit
    };

    enum ExCpuVendor
        /// CPU type
    {
        cvUnknown,
        cvIntel,
        cvAmd
    };

                   SystemInfo();
        ///< constructor
    virtual       ~SystemInfo() {}
        ///< destructor

    // OS
    ExOsType       os() xWARN_UNUSED_RV;
        ///< get information about the current OS
    std::tstring_t formatOs() xWARN_UNUSED_RV;
        ///< format OS type

    ExOsArch       osArch() xWARN_UNUSED_RV;
        ///< get OS architecture
    std::tstring_t formatOsArch() xWARN_UNUSED_RV;
        ///< format get OS architecture

    std::tstring_t desktopName() const xWARN_UNUSED_RV;
        ///< desktop environments

    // users
    std::tstring_t hostName() const xWARN_UNUSED_RV;
        ///< get the NetBIOS name of the local computer

    // CPU
    ulong_t        numOfCpus() const xWARN_UNUSED_RV;
        ///< get num of CPUs
    ulong_t        currentCpuNum() const xWARN_UNUSED_RV;
        ///< get the number of the processor the current thread was running on during
        ///< the call to this function
    ExCpuVendor    cpuVendor() const xWARN_UNUSED_RV;
        ///< get CPU vendor
    std::tstring_t cpuModel() const xWARN_UNUSED_RV;
        ///< get CPU model name
    ulong_t        cpuSpeed() const xWARN_UNUSED_RV;
        ///< get CPU speed (MHz)
    ulong_t        cpuUsage() const xWARN_UNUSED_RV;
        ///< get CPU usage (percentage)

    // RAM
    ulonglong_t    ramTotal() const xWARN_UNUSED_RV;
        ///< get total RAM (bytes)
    ulonglong_t    ramAvailable() const xWARN_UNUSED_RV;
        ///< get available RAM (bytes)
    ulong_t        ramUsage() const xWARN_UNUSED_RV;
        ///< get RAM usage (percentage)

    // HDD
    ulong_t        pageSize() const xWARN_UNUSED_RV;
        ///< get Size of a page (bytes)

    // Libs
#if xENV_UNIX
    std::tstring_t glibcVersion() const xWARN_UNUSED_RV;
        ///< get glibc version available on the system
    std::tstring_t libPthreadVersion() const xWARN_UNUSED_RV;
        ///< get POSIX implementation supplied by C library ("NPTL 2.3.4" or "linuxthreads-0.10")
#endif

private:
    ExOsType       _osType;
    ExOsArch       _osArch;

    xNO_COPY_ASSIGN(SystemInfo)

xPLATFORM_IMPL:
    // OS
    ExOsType       _os_impl() xWARN_UNUSED_RV;
    std::tstring_t _formatOs_impl() xWARN_UNUSED_RV;
    ExOsArch       _osArch_impl() xWARN_UNUSED_RV;
    std::tstring_t _hostName_impl() const xWARN_UNUSED_RV;

    // users
    std::tstring_t _desktopName_impl() const xWARN_UNUSED_RV;

    // CPU
    ulong_t        _numOfCpus_impl() const xWARN_UNUSED_RV;
    ulong_t        _currentCpuNum_impl() const xWARN_UNUSED_RV;
    std::tstring_t _cpuVendor_impl() const xWARN_UNUSED_RV;
    std::tstring_t _cpuModel_impl() const xWARN_UNUSED_RV;
    ulong_t        _cpuSpeed_impl() const xWARN_UNUSED_RV;
    ulong_t        _cpuUsage_impl() const xWARN_UNUSED_RV;

    // RAM
    ulonglong_t    _ramTotal_impl() const xWARN_UNUSED_RV;
    ulonglong_t    _ramAvailable_impl() const xWARN_UNUSED_RV;
    ulong_t        _ramUsage_impl() const xWARN_UNUSED_RV;

    // HDD
    ulong_t        _pageSize_impl() const xWARN_UNUSED_RV;
};

xNAMESPACE_END2(xlib, system)
//-------------------------------------------------------------------------------------------------
#if cmOPTION_PROJECT_HEADER_ONLY
    #include "SystemInfo.cpp"
#endif


// https://github.com/joyent/node/blob/master/src/platform_linux.cc
