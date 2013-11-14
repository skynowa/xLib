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

                   CxSystemInfo() {}
        ///< constructor
    virtual       ~CxSystemInfo() {}
        ///< destructor

    // OS
    ExOsType       os() xWARN_UNUSED_RV;
        ///< get information about the current OS
    std::tstring_t formatOsType(const ExOsType &osType) xWARN_UNUSED_RV;
        ///< format OS type

    ExOsArch       osArch() xWARN_UNUSED_RV;
        ///< get OS architecture
    std::tstring_t formatOsArch(const ExOsArch &osArch) xWARN_UNUSED_RV;
        ///< format get OS architecture

    std::tstring_t desktopName() xWARN_UNUSED_RV;
        ///< desktop environments

    // users
    std::tstring_t hostName() xWARN_UNUSED_RV;
        ///< get the NetBIOS name of the local computer
    bool_t         isUserAdmin() xWARN_UNUSED_RV;
        ///< is current user an admin
    std::tstring_t userName() xWARN_UNUSED_RV;
        ///< get the name of the user associated with the current thread
    std::tstring_t useHomeDir() xWARN_UNUSED_RV;
        ///< get home directory of current user
    std::tstring_t userShellPath() xWARN_UNUSED_RV;
        ///< get shell path of current user

    // CPU
    ulong_t        numOfCpus() xWARN_UNUSED_RV;
        ///< get num of CPUs
    ulong_t        currentCpuNum() xWARN_UNUSED_RV;
        ///< get the number of the processor the current thread was running on during
        ///< the call to this function
    ExCpuVendor    cpuVendor() xWARN_UNUSED_RV;
        ///< get CPU vendor
    std::tstring_t cpuModel() xWARN_UNUSED_RV;
        ///< get CPU model name
    ulong_t        cpuSpeed() xWARN_UNUSED_RV;
        ///< get CPU speed (MHz)
    ulong_t        cpuUsage() xWARN_UNUSED_RV;
        ///< get CPU usage (percentage)

    // RAM
    ulonglong_t    ramTotal() xWARN_UNUSED_RV;
        ///< get total RAM (bytes)
    ulonglong_t    ramAvailable() xWARN_UNUSED_RV;
        ///< get available RAM (bytes)
    ulong_t        ramUsage() xWARN_UNUSED_RV;
        ///< get RAM usage (percentage)
    ulong_t        pageSize() xWARN_UNUSED_RV;
        ///< get Size of a page (bytes)

private:
#if !xOS_ENV_WIN
    void_t         _passwdFileEntry(struct passwd *passwdEntry);
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
