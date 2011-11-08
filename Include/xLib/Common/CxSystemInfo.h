/**
 * \file  CxSystemInfo.h
 * \brief system information
 */


#ifndef xLib_Common_CxSystemInfoH
#define xLib_Common_CxSystemInfoH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxSystemInfo :
    public CxNonCopyable
    /// system information
{
   public:
        enum EOsType
            /// OS type
        {
            otUnknown,

            //windows
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

            //Linux
            otLinux,

            //BSD
            otFreeBSD
        };

        enum EOsArch
            /// OS architecture
        {
            oaUnknown,
            oa32bit,
            oa64bit
        };

        static EOsType      osGetOS           ();
            ///< get information about the current OS
        static std::string_t sFormatOsType     (const EOsType otOsType);
            ///< format OS type

        static EOsArch      oaGetOsArch       ();
            ///< get OS architecture
        static std::string_t sFormatOsArch     (const EOsArch oaOsArch);
            ///< format get OS architecture

        static std::string_t sGetComputerName  ();
            ///< get the NetBIOS name of the local computer
        static BOOL         bIsUserAnAdmin    ();
            ///< is current user an admin
        static std::string_t sGetUserName      ();
            ///< get the name of the user associated with the current thread
        static ULONG        ulGetNumOfCpus    ();
            ///< get num of CPUs
        static ULONG        ulGetCurrentCpuNum();
            ///< get the number of the processor the current thread was running on during the call to this function
        static BOOL         bIsUnicodeOS      ();
            ///< is OS support unicode
        static ULONGLONG    ullGetCpuSpeed    ();
            ///< get the CPU speed in MHz

   private:
                            CxSystemInfo      ();
            ///< constructor
        virtual            ~CxSystemInfo      ();
            ///< destructor
};
//---------------------------------------------------------------------------
#endif    //xLib_Common_CxSystemInfoH


// https://github.com/joyent/node/blob/master/src/platform_linux.cc
