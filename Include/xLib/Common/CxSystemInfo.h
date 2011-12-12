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

        static EOsType        osGetOS           ();
            ///< get information about the current OS
        static std::tstring_t sFormatOsType     (const EOsType otOsType);
            ///< format OS type

        static EOsArch        oaGetOsArch       ();
            ///< get OS architecture
        static std::tstring_t sFormatOsArch     (const EOsArch oaOsArch);
            ///< format get OS architecture

        static std::tstring_t sGetComputerName  ();
            ///< get the NetBIOS name of the local computer
        static bool           bIsUserAnAdmin    ();
            ///< is current user an admin
        static std::tstring_t sGetUserName      ();
            ///< get the name of the user associated with the current thread
        static ulong_t        ulGetNumOfCpus    ();
            ///< get num of CPUs
        static ulong_t        ulGetCurrentCpuNum();
            ///< get the number of the processor the current thread was running on during the call to this function
        static ulonglong_t    ullGetCpuSpeed    ();
            ///< get the CPU speed in MHz

   private:
                              CxSystemInfo      ();
            ///< constructor
        virtual              ~CxSystemInfo      ();
            ///< destructor
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif    //xLib_Common_CxSystemInfoH


// https://github.com/joyent/node/blob/master/src/platform_linux.cc
