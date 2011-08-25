/**
 * \file  CxProcess.h
 * \brief process
 */


#ifndef xLib_Sync_CxProcessH
#define xLib_Sync_CxProcessH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxProcess :
    public CxNonCopyable
{
    public:
        static ULONG ulGetCurrId      ();
        static ULONG ulGetCurrParentId();

        static BOOL  bExec            (const std::tstring &csFilePath, LPCTSTR pcszCmdLine, ...);
        static BOOL  bExit            (const ULONG culPid, const UINT cuiExitCode);
        static BOOL  bTerminate       (const ULONG culPid);

        //wait

    private:
                     CxProcess        ();
        virtual     ~CxProcess        ();
};
//---------------------------------------------------------------------------
#endif //xLib_Sync_CxProcessH
