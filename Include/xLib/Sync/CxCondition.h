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

xPLATFORM:
    void_t                  _destruct_impl();
    void_t                  _create_impl();
    void_t                  _wait_impl(culong_t &timeoutMs);
    void_t                  _signal_impl();
    void_t                  _broadcast_impl();
};

xNAMESPACE_END2(xlib, sync)
//-------------------------------------------------------------------------------------------------
#include "CxCondition.inl"
