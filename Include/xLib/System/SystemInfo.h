/**
 * \file  SystemInfo.h
 * \brief system information
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, system)

class SystemInfo
    /// system information
{
public:
    enum class OsType
        /// OS type
    {
        Unknown,
        // windows family
        Windows3,
        Windows95,
        Windows98,
        WindowsNT,
        Windows2000,
        WindowsXP,
        WindowsXPProx64Edition,
        WindowsServer2003,
        WindowsHomeServer,
        WindowsServer2003R2,
        WindowsVista,
        WindowsServer2008,
        WindowsServer2008R2,
        Windows7,
        // Linux  family
        Linux,
        // BSD family
        FreeBSD,
        // Apple family
        Mac
    };
    xUSING_CONST(OsType);

    enum class OsArch
        /// OS architecture
    {
        Unknown,
        bit32,
        bit64
    };
    xUSING_CONST(OsArch);

    enum class CpuVendor
        /// CPU type
    {
        Unknown,
        Intel,
        Amd
    };
    xUSING_CONST(CpuVendor);

                   SystemInfo() = default;
    virtual       ~SystemInfo() = default;

    // OS
    OsType         os();
        ///< get information about the current OS
    std::tstring_t formatOs() const;
        ///< format OS type
    std::tstring_t distro() const;
        ///< distributive info

    OsArch         osArch();
        ///< get OS architecture
    std::tstring_t formatOsArch();
        ///< format get OS architecture

    std::tstring_t desktopName() const;
        ///< desktop environments

    // users
    std::tstring_t hostName() const;
        ///< get the NetBIOS name of the local computer

    // CPU
    ulong_t        numOfCpus() const;
        ///< get num of CPUs
    ulong_t        currentCpuNum() const;
        ///< get the number of the processor the current thread was running on during
        ///< the call to this function
    CpuVendor      cpuVendor() const;
        ///< get CPU vendor
    std::tstring_t cpuModel() const;
        ///< get CPU model name
    ulong_t        cpuSpeed() const;
        ///< get CPU speed (MHz)
    ulong_t        cpuUsage() const;
        ///< get CPU usage (percentage)

    // RAM
    ulonglong_t    ramTotal() const;
        ///< get total RAM (bytes)
    ulonglong_t    ramAvailable() const;
        ///< get available RAM (bytes)
    ulong_t        ramUsage() const;
        ///< get RAM usage (percentage)

    // HDD
    ulong_t        pageSize() const;
        ///< get Size of a page (bytes)

    // Libs
#if xENV_UNIX
    std::tstring_t glibcVersion() const;
        ///< get glibc version available on the system
    std::tstring_t libPthreadVersion() const;
        ///< get POSIX implementation supplied by C library ("NPTL 2.3.4" or "linuxthreads-0.10")
#endif

private:
    OsType         _osType {};
    OsArch         _osArch {};

    xNO_COPY_ASSIGN(SystemInfo)

xPLATFORM_IMPL:
    // OS
    OsType         _os_impl();
    std::tstring_t _formatOs_impl() const;
    std::tstring_t _distro_impl() const;
    OsArch         _osArch_impl();
    std::tstring_t _hostName_impl() const;

    // users
    std::tstring_t _desktopName_impl() const;

    // CPU
    ulong_t        _numOfCpus_impl() const;
    ulong_t        _currentCpuNum_impl() const;
    std::tstring_t _cpuVendor_impl() const;
    std::tstring_t _cpuModel_impl() const;
    ulong_t        _cpuSpeed_impl() const;
    ulong_t        _cpuUsage_impl() const;

    // RAM
    ulonglong_t    _ramTotal_impl() const;
    ulonglong_t    _ramAvailable_impl() const;
    ulong_t        _ramUsage_impl() const;

    // HDD
    ulong_t        _pageSize_impl() const;
};

xNAMESPACE_END2(xl, system)
//-------------------------------------------------------------------------------------------------

// https://github.com/joyent/node/blob/master/src/platform_linux.cc
