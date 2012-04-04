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

        enum EWaitResult
            /// wait result
        {
            #if   xOS_ENV_WIN
                wrFailed    = WAIT_FAILED,
                wrAbandoned = WAIT_ABANDONED,
                wrObject0   = WAIT_OBJECT_0,
                wrTimeout   = WAIT_TIMEOUT
            #elif xOS_ENV_UNIX
                wrFailed    = - 1,
                wrAbandoned = 0,
                wrObject0   = 1,
                wrTimeout   = 2
            #endif
        };


                        CxProcess      ();
        virtual        ~CxProcess      ();

        bool            bCreate        (const std::tstring_t &csFilePath, const tchar_t *pcszParams, ...);
            ///< execute a file
        EWaitResult     ulWait         (const ulong_t culTimeout);
            ///< wait for termonation
        bool            bKill          (const ulong_t culTimeout);
            ///< kills the calling process and all of its threads

        TxHandle        hGet           () const;
            ///< get handle
        TxId            ulGetId        () const;
            ///< get ID
        bool            bIsCurrent     () const;
            ///< is current
        ulong_t         ulGetExitStatus() const;
            ///< get termination status

        static TxId     ulGetIdByHandle(const TxHandle chHandle);
            ///< ge ID by handle
        static TxHandle ulGetHandleById(const TxId culId);
            ///< ge handle by ID

    private:
        //constants
        static const ulong_t  _ms_culStillActiveTimeout = 2UL;    ///< still active timeout (msec)
        static const ulong_t  _ms_culExitTimeout        = 5000UL; ///< exit timeout (msec)

        TxHandle        _m_hHandle;
    #if xOS_ENV_WIN
        HANDLE          _m_hThread;
    #endif
        TxId            _m_ulPid;
        uint_t          _m_uiExitStatus;            ///< exit code

};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif //xLib_Sync_CxProcessH
