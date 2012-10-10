/**
 * \file  CxIpcMutex.h
 * \brief mutex
 */


#ifndef xLib_Sync_CxIpcMutexH
#define xLib_Sync_CxIpcMutexH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Common/CxHandleT.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxIpcMutex :
    private CxNonCopyable
    /// mutex
{
    public:
    #if   xOS_ENV_WIN
        typedef CxHandle  handle_t;
    #elif xOS_ENV_UNIX
        typedef sem_t *   handle_t;
    #endif

                          CxIpcMutex();
        virtual          ~CxIpcMutex();

        const handle_t &  hHandle   () const;
            ///< get handle
        void              vCreate   (const std::tstring_t &csName);
            ///< create
        void              vOpen     (const std::tstring_t &csName);
            ///< open
        void              vLock     (const ulong_t &culTimeoutMsec) const;
            ///< unlock by timeout in msec
        void              vUnlock   () const;
            ///< lock

    private:
        handle_t          _m_hHandle;   ///< mutex native handle
        std::tstring_t    _m_sName;     ///< mutex name
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif    //xLib_Sync_CxIpcMutexH
