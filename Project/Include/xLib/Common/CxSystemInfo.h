/**
 * \file  CxSystemInfo.h
 * \brief system information
 */


#ifndef xLib_Common_CxSystemInfoH
#define xLib_Common_CxSystemInfoH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxSystemInfo :
    private CxNonCopyable
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

    // OS
    static ExOsType       os              () xWARN_UNUSED_RV;
        ///< get information about the current OS
    static std::tstring_t formatOsType    (const ExOsType &otOsType) xWARN_UNUSED_RV;
        ///< format OS type

    static ExOsArch       osArch          () xWARN_UNUSED_RV;
        ///< get OS architecture
    static std::tstring_t formatOsArch    (const ExOsArch &oaOsArch) xWARN_UNUSED_RV;
        ///< format get OS architecture

    static std::tstring_t desktopName     () xWARN_UNUSED_RV;
        ///< desktop environments

    // users
    static std::tstring_t hostName        () xWARN_UNUSED_RV;
        ///< get the NetBIOS name of the local computer
    static bool_t         isUserAdmin     () xWARN_UNUSED_RV;
        ///< is current user an admin
    static std::tstring_t userName        () xWARN_UNUSED_RV;
        ///< get the name of the user associated with the current thread
    static std::tstring_t useHomeDir      () xWARN_UNUSED_RV;
        ///< get home directory of current user
    static std::tstring_t userShellPath   () xWARN_UNUSED_RV;
        ///< get shell path of current user

    // CPU
    static ulong_t        numOfCpus       () xWARN_UNUSED_RV;
        ///< get num of CPUs
    static ulong_t        currentCpuNum   () xWARN_UNUSED_RV;
        ///< get the number of the processor the current thread was running on during the call to this function
    static ExCpuVendor    cpuVendor       () xWARN_UNUSED_RV;
        ///< get CPU vendor
    static std::tstring_t cpuModel        () xWARN_UNUSED_RV;
        ///< get CPU model name
    static ulong_t        cpuSpeed        () xWARN_UNUSED_RV;
        ///< get CPU speed (MHz)
    static ulong_t        cpuUsage        () xWARN_UNUSED_RV;
        ///< get CPU usage (percentage)

    // RAM
    static ulonglong_t    ramTotal        () xWARN_UNUSED_RV;
        ///< get total RAM (bytes)
    static ulonglong_t    ramAvailable    () xWARN_UNUSED_RV;
        ///< get available RAM (bytes)
    static ulong_t        ramUsage        () xWARN_UNUSED_RV;
        ///< get RAM usage (percentage)
    static ulong_t        pageSize        () xWARN_UNUSED_RV;
        ///< get Size of a page (bytes)

private:
                          CxSystemInfo    ();
        ///< constructor
    virtual              ~CxSystemInfo    ();
        ///< destructor

#if xOS_ENV_UNIX
    static void_t         _passwdFileEntry(struct passwd *pwdPasswd);
        ///< get password file entry
#endif
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#endif // xLib_Common_CxSystemInfoH


// https://github.com/joyent/node/blob/master/src/platform_linux.cc
