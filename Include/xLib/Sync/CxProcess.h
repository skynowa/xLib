/**
 * \file  CxProcess.h
 * \brief process
 */


#ifndef xLib_Sync_CxProcessH
#define xLib_Sync_CxProcessH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Common/CxHandleT.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxProcess :
    private CxNonCopyable
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

        static bool     bExec          (const std::tstring_t &csFilePath, const tchar_t *pcszCmdLine, ...);
            ///< execute a file
        static bool     bExit          (const TxId culPid, const uint_t cuiExitCode);
            ///< ends the calling process and all its threads
        static ulong_t  ulWait         (const TxId culPid, const ulong_t culTimeout);
            ///< wait for termonation
        static bool     bTerminate     (const TxId culPid);
            ///< kills the calling process and all of its threads

        //wait

        static TxId     ulGetIdByHandle(const TxHandle &chHandle);
            ///< ge ID by handle
        static TxHandle ulGetHandleById(const TxId &culId);
            ///< ge handle by ID

    private:
                        CxProcess      ();
        virtual        ~CxProcess      ();
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif //xLib_Sync_CxProcessH
