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
    /// process
{
    public:
    #if defined(xOS_ENV_WIN)
        typedef HANDLE TxHandle; ///< handle
        typedef DWORD  TxId;     ///< ID
    #elif defined(xOS_ENV_UNIX)
        typedef pid_t  TxHandle; ///< handle
        typedef pid_t  TxId;     ///< ID
    #endif

        static TxId     ulGetCurrId      ();
            ///< process ID of the calling process
        static TxId     ulGetCurrParentId();
            ///< process ID of the parent of the calling process
        static BOOL     bExec            (const std::string_t &csFilePath, const char_t *pcszCmdLine, ...);
            ///< execute a file
        static BOOL     bExit            (const TxId culPid, const UINT cuiExitCode);
            ///< ends the calling process and all its threads
        static BOOL     bTerminate       (const TxId culPid);
            ///< kills the calling process and all of its threads

        //wait

    private:
                     CxProcess        ();
        virtual     ~CxProcess        ();
};
//---------------------------------------------------------------------------
#endif //xLib_Sync_CxProcessH
