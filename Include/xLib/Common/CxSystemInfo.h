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
            otWindows3,                 //
            otWindows95,                //
            otWindows98,                //
            otWindowsNT,                //
            otWindows2000,              //5.0
            otWindowsXP,                //5.1
            otWindowsXPProx64Edition,   //5.2
            otWindowsServer2003,        //5.2
            otWindowsHomeServer,        //5.2
            otWindowsServer2003R2,      //5.2
            otWindowsVista,             //6.0
            otWindowsServer2008,        //6.0
            otWindowsServer2008R2,      //6.1
            otWindows7,                 //6.1

            //Linux
            otLinux,

            //BSD
            otFreeBSD
        };

        enum EOsArch {
            oaUnknown,
            oa32bit,
            oa64bit
        };


        static EOsType         osGetOS            ();
        static tString         sFormatOsType      (const EOsType otOsType);

        static EOsArch         oaGetOsArch        ();
        static tString         sFormatOsArch      (const EOsArch oaOsArch);

        static tString         sGetComputerName   ();
        static BOOL            bIsUserAnAdmin     ();
        static tString         sGetUserName       ();
        static ULONG           ulGetNumOfCPUs     ();
        static ULONG           ulGetCurrentCpuNum ();
        static BOOL            bIsUnicodeOS       ();
        static ULONGLONG       ullGetCpuSpeed     ();

   private:
                               CxSystemInfo       ();
        virtual               ~CxSystemInfo       ();
};
//---------------------------------------------------------------------------
#endif    //xLib_Common_CxSystemInfoH


// https://github.com/joyent/node/blob/master/src/platform_linux.cc
