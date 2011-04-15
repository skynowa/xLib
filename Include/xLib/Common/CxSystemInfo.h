/****************************************************************************
* Class name:  CxSystemInfo
* Description: system information
* File name:   CxSystemInfo.h
* Compilers:   Visual C++ 2008
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     09.07.2009 11:52:01
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef xLib_Common_CxSystemInfoH
#define xLib_Common_CxSystemInfoH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxSystemInfo : public CxNonCopyable {
   public:
		//OS version
		enum EOsType {
            otUnknown,

            //windows
            otWindows3,                         //
            otWindows95,                        //
            otWindows98,                        //
            otWindowsNT,                        //
            otWindows2000,	                    //5.0
            otWindowsXP,	                    //5.1
            otWindowsXPProfessionalx64Edition,	//5.2
            otWindowsServer2003,	            //5.2
            otWindowsHomeServer,	            //5.2
            otWindowsServer2003R2,	            //5.2
            otWindowsVista,	                    //6.0
            otWindowsServer2008,	            //6.0
            otWindowsServer2008R2,	            //6.1
            otWindows7,	                        //6.1

            //nix
            otLinux,

            //FreeBSD
            otFreeBSD
        };

		//OS architecture
        enum EOsArchitecture {
            oaUnknown,
            oa32bit,
            oa64bit
        };


		static EOsType         osGetOS            ();
		static EOsArchitecture oaGetOsArchitecture();
		static tString         sFormatOsType      (EOsType otOsType);
		static tString         sGetComputerName   ();
		static BOOL            bIsUserAnAdmin     ();
		static tString         sGetUserName       ();
		static ULONG           ulGetNumOfCPUs     ();
		static ULONG           ulGetCurrentCpuNum ();
		static BOOL            bIsUnicodeOS       ();
		static INT             iGetCpuSpeed       ();

   private:
		                       CxSystemInfo       ();
		virtual               ~CxSystemInfo       ();
};
//---------------------------------------------------------------------------
#endif	//xLib_Common_CxSystemInfoH
