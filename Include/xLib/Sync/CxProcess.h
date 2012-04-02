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

        enum EWaitResult {
            #if   xOS_ENV_WIN
                wrAbandoned = WAIT_ABANDONED,
                wrObject0   = WAIT_OBJECT_0,
                wrTimeout   = WAIT_TIMEOUT,
                wrFailed    = WAIT_FAILED
            #elif xOS_ENV_UNIX

                wrFailed    = - 1
            #endif
        };


                        CxProcess      ();
        virtual        ~CxProcess      ();

        bool            bCreate        (const std::tstring_t &csFilePath, const tchar_t *pcszCmdLine, ...);
            ///< execute a file
        EWaitResult     ulWait         (const ulong_t culTimeout);
            ///< wait for termonation
        bool            bKill          ();
            ///< kills the calling process and all of its threads

        static TxId     ulGetIdByHandle(const TxHandle chHandle);
            ///< ge ID by handle
        static TxHandle ulGetHandleById(const TxId culId);
            ///< ge handle by ID

    private:
        TxHandle        _m_hHandle;
    #if xOS_ENV_WIN
        HANDLE          _m_hThread;
    #endif
        TxId            _m_ulPid;

};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif //xLib_Sync_CxProcessH
