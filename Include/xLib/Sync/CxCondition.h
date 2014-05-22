/**
 * \file   CxCondition.h
 * \brief  condition variable
 */


#pragma once

#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, sync)

class CxCondition
    /// condition variable
{
public:
                            CxCondition();
        ///< constructor
    virtual                ~CxCondition();
        ///< destructor
#if !xENV_WIN
    const pthread_mutex_t & mutex() const xWARN_UNUSED_RV;
        ///< get mutex handle
    const pthread_cond_t &  handle() const xWARN_UNUSED_RV;
        ///< get handle
#endif

    void_t                  create();
        ///< create
    void_t                  wait(culong_t &timeoutMs);
        ///< wait
    void_t                  signal();
        ///< signal one
    void_t                  broadcast();
        ///< signal all

private:
#if !xENV_WIN
    pthread_mutex_t         _mutex;
    pthread_cond_t          _handle;
#endif

    xNO_COPY_ASSIGN(CxCondition)
};

xNAMESPACE_END2(xlib, sync)
//-------------------------------------------------------------------------------------------------
#include "CxCondition.inl"
