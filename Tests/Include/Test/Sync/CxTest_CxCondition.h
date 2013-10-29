/**
 * \file   CxTest_CxCondition.h
 * \brief  test CxCondition
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Sync/CxCondition.h>
//------------------------------------------------------------------------------
class CxTest_CxCondition :
    public CxTest
{
public:
                    CxTest_CxCondition() {}

    virtual void_t  unit(culonglong_t &cullCaseLoops) xOVERRIDE;
        ///< unit test
};
//------------------------------------------------------------------------------
