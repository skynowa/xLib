/**
 * \file   Condition.h
 * \brief  condition variable
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, sync)

class Condition
    /// condition variable
{
public:
                            Condition();
        ///< constructor
    virtual                ~Condition();
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

    xNO_COPY_ASSIGN(Condition)

xPLATFORM:
    void_t                  _destruct_impl();
    void_t                  _create_impl();
    void_t                  _wait_impl(culong_t &timeoutMs);
    void_t                  _signal_impl();
    void_t                  _broadcast_impl();
};

xNAMESPACE_END2(xlib, sync)
//-------------------------------------------------------------------------------------------------
#if xOPTION_HEADER_ONLY
    #include "Condition.inl"
#endif
