/**
 * \file  CxProcess.h
 * \brief process
 */


#ifndef xLib_Sync_CxProcessH
#define xLib_Sync_CxProcessH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxProcess :
    public CxNonCopyable
    /// process
{
    public:
    #if xOS_ENV_WIN
        typedef HANDLE TxHandle; ///< handle
        typedef DWORD  TxId;     ///< ID
    #elif xOS_ENV_UNIX
        typedef pid_t  TxHandle; ///< handle
        typedef pid_t  TxId;     ///< ID
    #endif

        static bool  bExec     (const std::tstring &csFilePath, const tchar *pcszCmdLine, ...);
            ///< execute a file
        static bool  bExit     (const TxId culPid, const UINT cuiExitCode);
            ///< ends the calling process and all its threads
        static bool  bTerminate(const TxId culPid);
            ///< kills the calling process and all of its threads

        //wait

    private:
                     CxProcess ();
        virtual     ~CxProcess ();
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif //xLib_Sync_CxProcessH
