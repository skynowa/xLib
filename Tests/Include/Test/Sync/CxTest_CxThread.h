/**
 * \file   CxTest_CxThread.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Sync/CxThread.h>
//------------------------------------------------------------------------------
class CxTest_CxThread :
    public CxTest
{
public:
                   CxTest_CxThread() {}

    virtual void_t unit(culonglong_t &caseLoops);

private:
    void_t         unit1(culonglong_t &caseLoops);
};
//------------------------------------------------------------------------------
