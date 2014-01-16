/**
 * \file  CxSystemInfo.h
 * \brief system information
 */


#pragma once

#ifndef xLib_CxSystemInfoH
#define xLib_CxSystemInfoH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxSystemInfo
    /// system information
{
public:
    enum ExOsType
        /// OS type
    {
        otUnknown,

    #if   xOS_ENV_WIN
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
        otWindows7
    #elif xOS_ENV_UNIX
        // Linux  family
        otLinux,
        // BSD family
        otFreeBSD
    #elif xOS_ENV_MAC
        otMac
    #endif
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

                   CxSystemInfo();
        ///< constructor
    virtual       ~CxSystemInfo() {}
        ///< destructor

    // OS
    ExOsType       os() xWARN_UNUSED_RV;
        ///< get information about the current OS
    std::tstring_t formatOsType() xWARN_UNUSED_RV;
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
    bool_t         isUserAdmin() const xWARN_UNUSED_RV;
        ///< is current user an admin
    std::tstring_t loginUserName() const xWARN_UNUSED_RV;
        ///<
    std::tstring_t userName() const xWARN_UNUSED_RV;
        ///< get the name of the user associated with the current thread
    std::tstring_t useHomeDir() const xWARN_UNUSED_RV;
        ///< get home directory of current user
    std::tstring_t userShellPath() const xWARN_UNUSED_RV;
        ///< get shell path of current user

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

#if xOS_ENV_UNIX
    std::tstring_t glibcFullVersion() const xWARN_UNUSED_RV;
        ///< get glibc version available on the system
    std::tstring_t libPthreadVersion() const xWARN_UNUSED_RV;
        ///< get POSIX implementation supplied by C library ("NPTL 2.3.4" or "linuxthreads-0.10")
#endif


private:
    ExOsType       _osType;
    ExOsArch       _osArch;

#if !xOS_ENV_WIN
    void_t         _passwdFileEntry(passwd *passwdEntry) const;
        ///< get password file entry
#endif

    xNO_COPY_ASSIGN(CxSystemInfo)
};

xNAMESPACE_END(NxLib)
//-------------------------------------------------------------------------------------------------
#include "CxSystemInfo.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxSystemInfoH


// https://github.com/joyent/node/blob/master/src/platform_linux.cc
