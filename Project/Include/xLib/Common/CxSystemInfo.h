/**
 * \file  CxSystemInfo.h
 * \brief system information
 */


#ifndef xLib_Common_CxSystemInfoH
#define xLib_Common_CxSystemInfoH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
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
        static ExOsType       osOS              ();
            ///< get information about the current OS
        static std::tstring_t sFormatOsType     (const ExOsType &otOsType);
            ///< format OS type

        static ExOsArch       oaOsArch          ();
            ///< get OS architecture
        static std::tstring_t sFormatOsArch     (const ExOsArch &oaOsArch);
            ///< format get OS architecture

        static std::string    sDesktopName      ();
            ///< desktop environments

        // users
        static std::tstring_t sHostName         ();
            ///< get the NetBIOS name of the local computer
        static bool           bIsUserAnAdmin    ();
            ///< is current user an admin
        static std::tstring_t sUserName         ();
            ///< get the name of the user associated with the current thread
        static std::tstring_t sUseHomeDir       ();
            ///< get home directory of current user
        static std::string    sUserShellPath    ();
            ///< get shell path of current user

        // CPU
        static ulong_t        ulNumOfCpus       ();
            ///< get num of CPUs
        static ulong_t        ulCurrentCpuNum   ();
            ///< get the number of the processor the current thread was running on during the call to this function
        static ExCpuVendor    cvCpuVendor       ();
            ///< get CPU vendor
        static std::tstring_t sCpuModel         ();
            ///< get CPU model name
        static ulong_t        ulCpuSpeed        ();
            ///< get CPU speed (MHz)
        static ulong_t        ulCpuUsage        ();
            ///< get CPU usage (percentage)

        // RAM
        static ulonglong_t    ullRamTotal       ();
            ///< get total RAM (bytes)
        static ulonglong_t    ullRamAvailable   ();
            ///< get available RAM (bytes)
        static ulong_t        ulRamUsage        ();
            ///< get RAM usage (percentage)
        static ulong_t        ulPageSize        ();
            ///< get Size of a page (bytes)

   private:
                              CxSystemInfo      ();
            ///< constructor
        virtual              ~CxSystemInfo      ();
            ///< destructor

    #if xOS_ENV_UNIX
        static void           _passwordFileEntry(struct passwd *pwdPasswd);
            ///< get password file entry
    #endif
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif    //xLib_Common_CxSystemInfoH


// https://github.com/joyent/node/blob/master/src/platform_linux.cc
