/**
 * \file   CxTest_CxProcessInfo.h
 * \brief  test CxProcessInfo
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/System/CxProcessInfo.h>
//------------------------------------------------------------------------------
class CxTest_CxProcessInfo :
    public CxTest
{
public:
                   CxTest_CxProcessInfo() {}

    virtual void_t unit(culonglong_t &cullCaseLoops);
        ///< unit test
};
//------------------------------------------------------------------------------
