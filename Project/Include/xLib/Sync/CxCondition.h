/**
 * \file   CxCondition.h
 * \brief
 */


#ifndef xLib_Sync_CxConditionH
#define xLib_Sync_CxConditionH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxCondition :
    public CxNonCopyable
{
public:
                            CxCondition();
        ///< constructor
    virtual                ~CxCondition();
        ///< destructor
#if xOS_ENV_UNIX
    const pthread_mutex_t & mutex      () const xWARN_UNUSED_RESULT;
        ///< get mutex handle
    const pthread_cond_t &  handle     () const xWARN_UNUSED_RESULT;
        ///< get handle
#endif

    void                    create     ();
        ///< create
    void                    wait       (const ulong_t &culTimeoutMs);
        ///< wait
    void                    signal     ();
        ///< signal one
    void                    broadcast  ();
        ///< signal all

private:
#if xOS_ENV_UNIX
    pthread_mutex_t         _m_mutex;
    pthread_cond_t          _m_handle;
#endif
};
//---------------------------------------------------------------------------
#endif // xLib_Sync_CxConditionH
