/****************************************************************************
* Class name:  CxSystemInfo
* Description: system information
* File name:   CxSystemInfo.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     09.07.2009 11:52:01
*
*****************************************************************************/


#ifndef xLib_Common_CxSystemInfoH
#define xLib_Common_CxSystemInfoH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxSystemInfo :
    public CxNonCopyable
{
   public:
        enum EOsType {
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
            ///< OS type

        enum EOsArch {
            oaUnknown,
            oa32bit,
            oa64bit
        };
            ///< OS architecture


        static EOsType         osGetOS            ();
            ///< get information about the current OS
        static tString         sFormatOsType      (const EOsType otOsType);
            ///< format OS type

        static EOsArch         oaGetOsArch        ();
            ///< get OS architecture
        static tString         sFormatOsArch      (const EOsArch oaOsArch);
            ///< format get OS architecture

        static tString         sGetComputerName   ();
            ///< get the NetBIOS name of the local computer
        static BOOL            bIsUserAnAdmin     ();
            ///< is current user an admin
        static tString         sGetUserName       ();
            ///< get the name of the user associated with the current thread
        static ULONG           ulGetNumOfCPUs     ();
            ///< get num of CPUs
        static ULONG           ulGetCurrentCpuNum ();
            ///< get the number of the processor the current thread was running on during the call to this function
        static BOOL            bIsUnicodeOS       ();
            ///< is OS support unicode
        static ULONGLONG       ullGetCpuSpeed     ();
            ///< get the CPU speed in MHz

   private:
                               CxSystemInfo       ();
            ///< constructor
        virtual               ~CxSystemInfo       ();
            ///< destructor
};
//---------------------------------------------------------------------------
#endif    //xLib_Common_CxSystemInfoH


// https://github.com/joyent/node/blob/master/src/platform_linux.cc
