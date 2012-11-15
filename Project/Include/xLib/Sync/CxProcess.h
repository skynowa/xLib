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
    #if   xOS_ENV_WIN
        typedef HANDLE handle_t; ///< handle
        typedef DWORD  id_t;     ///< ID
    #elif xOS_ENV_UNIX
        typedef pid_t  handle_t; ///< handle
        typedef pid_t  id_t;     ///< ID
    #endif

        enum ExWaitResult
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

        void            vCreate        (const std::tstring_t &csFilePath, const tchar_t *pcszParams, ...);
            ///< execute a file
        ExWaitResult    ulWait         (const ulong_t &culTimeout);
            ///< wait for termonation
        void            vKill          (const ulong_t &culTimeout);
            ///< kills the calling process and all of its threads

        handle_t        hHandle        () const;
            ///< get handle
        id_t            ulId           () const;
            ///< get ID
        bool            bIsCurrent     () const;
            ///< is current
        ulong_t         ulExitStatus   () const;
            ///< get termination status

        static id_t     ulIdByHandle   (const handle_t &chHandle);
            ///< get ID by handle
        static handle_t ulHandleById   (const id_t &culId);
            ///< get handle by ID
        static id_t     ulIdByName     (const std::tstring_t &csProcessName);
            ///< get ID by name
        static bool     bIsRunning     (const id_t &culId);
            ///< is process runnig by name (with extension)

    private:
        handle_t        _m_hHandle;
    #if   xOS_ENV_WIN
        HANDLE          _m_hThread;
    #endif
        id_t            _m_ulPid;
        uint_t          _m_uiExitStatus;            ///< exit code

};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif //xLib_Sync_CxProcessH
