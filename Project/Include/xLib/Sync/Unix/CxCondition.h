/**
 * \file   CxCondition.h
 * \brief
 */


#ifndef xLib_Sync_CxConditionH
#define xLib_Sync_CxConditionH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
#if xOS_ENV_UNIX

class CxCondition :
    public CxNonCopyable
{
public:
                            CxCondition();
        ///< constructor
    virtual                ~CxCondition();
        ///< destructor

    const pthread_mutex_t & hMutex     () const;
        ///< get mutex handle
    const pthread_cond_t &  hHandle    () const;
        ///< get handle
    void                    vCreate    ();
        ///< create
    void                    vWait      (const ulong_t &culTimeoutMs);
        ///< wait
    void                    vSignal    ();
        ///< signal one
    void                    vBroadcast ();
        ///< signal all

private:
    pthread_mutex_t         _m_mutex;
    pthread_cond_t          _m_handle;
};

#endif
//---------------------------------------------------------------------------
#endif // xLib_Sync_CxConditionH
