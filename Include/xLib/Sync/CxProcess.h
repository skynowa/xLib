/****************************************************************************
* Class name:  CxProcess
* Description: process
* File name:   CxProcess.h
* Compilers:   Visual C++ 2010, C++ Builder 2010
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     19.01.2011 22:42:07
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef xLib_Sync_CxProcessH
#define xLib_Sync_CxProcessH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxProcess : public CxNonCopyable {
    public:

        static ULONG ulGetCurrId      ();
        static ULONG ulGetCurrParentId();

        static BOOL  bExit            (ULONG ulPid, UINT uiExitCode);
        static BOOL  bTerminate       (ULONG ulPid);
        static BOOL  bExec            (const tString &csFilePath, LPCTSTR pcszCmdLine, ...);
        //wait

    private:
                     CxProcess     ();
        virtual     ~CxProcess     ();
};
//---------------------------------------------------------------------------
#endif //xLib_Sync_CxProcessH


//http://www.yolinux.com/TUTORIALS/ForkExecProcesses.html

