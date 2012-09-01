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
    #if xOS_ENV_WIN
        typedef CxHandle  handle_t;
    #elif xOS_ENV_UNIX
        typedef sem_t *   handle_t;
    #endif

                          CxIpcMutex();
        virtual          ~CxIpcMutex();

        const handle_t &  hGet   () const;
            ///< get handle
        bool              bCreate(const std::tstring_t &csName);
            ///< create
        bool              bOpen  (const std::tstring_t &csName);
            ///< open
        bool              bLock  (const ulong_t &culTimeoutMsec) const;
            ///< unlock by timeout in msec
        bool              bUnlock() const;
            ///< lock

    private:
        handle_t          _m_hHandle;   ///< mutex native handle
        std::tstring_t    _m_sName;     ///< mutex name
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif    //xLib_Sync_CxIpcMutexH
