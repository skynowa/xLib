/**
 * \file   CxTest_CxSleeper.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Sync/CxSleeper.h>
//------------------------------------------------------------------------------
class CxTest_CxSleeper :
    public CxTest
{
public:
                   CxTest_CxSleeper() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//------------------------------------------------------------------------------
