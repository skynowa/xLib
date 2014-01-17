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
xNAMESPACE_BEGIN(xlib)

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
    bool_t   isSleeping() const xWARN_UNUSED_RV;
        ///< check for sleeping

private:
    CxEvent  _event;    ///< event object

    xNO_COPY_ASSIGN(CxSleeper)
};

xNAMESPACE_END(xlib)
//-------------------------------------------------------------------------------------------------
#include "CxSleeper.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxSleeperH
