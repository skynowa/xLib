/**
 * \file   CxCondition.h
 * \brief
 */


#ifndef xLib_Sync_CxConditionH
#define xLib_Sync_CxConditionH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//------------------------------------------------------------------------------
class CxCondition :
    public CxNonCopyable
{
public:
                            CxCondition();
        ///< constructor
    virtual                ~CxCondition();
        ///< destructor
#if !xOS_ENV_WIN
    const pthread_mutex_t & mutex      () const xWARN_UNUSED_RV;
        ///< get mutex handle
    const pthread_cond_t &  handle     () const xWARN_UNUSED_RV;
        ///< get handle
#endif

    void_t                  create     ();
        ///< create
    void_t                  wait       (culong_t &culTimeoutMs);
        ///< wait
    void_t                  signal     ();
        ///< signal one
    void_t                  broadcast  ();
        ///< signal all

private:
#if xOS_ENV_UNIX
    pthread_mutex_t         _m_mutex;
    pthread_cond_t          _m_handle;
#endif
};
//------------------------------------------------------------------------------
#endif // xLib_Sync_CxConditionH
