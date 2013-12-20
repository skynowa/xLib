/**
 * \file   CxCondition.h
 * \brief
 */


#pragma once

#ifndef xLib_CxConditionH
#define xLib_CxConditionH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
class CxCondition
{
public:
                            CxCondition();
        ///< constructor
    virtual                ~CxCondition();
        ///< destructor
#if !xOS_ENV_WIN
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
#if !xOS_ENV_WIN
    pthread_mutex_t         _mutex;
    pthread_cond_t          _handle;
#endif

    xNO_COPY_ASSIGN(CxCondition)
};
//-------------------------------------------------------------------------------------------------
#include "CxCondition.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxConditionH
