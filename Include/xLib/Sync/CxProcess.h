/****************************************************************************
* Class name:  CxProcess
* Description: process
* File name:   CxProcess.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     19.01.2011 22:42:07
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

        static BOOL  bExec            (const tString &csFilePath, LPCTSTR pcszCmdLine, ...);
        static BOOL  bExit            (const ULONG culPid, const UINT cuiExitCode);
        static BOOL  bTerminate       (const ULONG culPid);

        //wait

    private:
                     CxProcess        ();
        virtual     ~CxProcess        ();
};
//---------------------------------------------------------------------------
#endif //xLib_Sync_CxProcessH


//http://www.yolinux.com/TUTORIALS/ForkExecProcesses.html

