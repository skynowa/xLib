/**
 * \file  CxSleeper.h
 * \brief sleeper
 */


#pragma once

#ifndef xLib_CxSleeperH
#define xLib_CxSleeperH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
#include <xLib/Sync/CxEvent.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxSleeper
    /// sleeper
{
public:
             CxSleeper();
        ///< constructor
    virtual ~CxSleeper() {}
        ///< destructor

    void_t   sleep(culong_t &timeoutMsec);
        ///< sleep
    void_t   wakeUp();
        ///< wake up
    bool_t   isSleeping() xWARN_UNUSED_RV;
        ///< check for sleeping

private:
    CxEvent  _event;    ///< event object

xNO_COPY_ASSIGN(CxSleeper)
};

xNAMESPACE_END(NxLib)
//-------------------------------------------------------------------------------------------------
#include <Sync/CxSleeper.inl>
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxSleeperH
