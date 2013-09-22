/**
 * \file   CxTest_CxCondition.h
 * \brief  test CxCondition
 */


#pragma once

#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Sync/CxCondition.h>
//------------------------------------------------------------------------------
class CxTest_CxCondition :
    public CxTest
{
public:
                    CxTest_CxCondition();
        ///< constructor
    virtual        ~CxTest_CxCondition();
        ///< destructor

    virtual void_t  unit(culonglong_t &cullCaseLoops) xOVERRIDE;
        ///< unit test
};
//------------------------------------------------------------------------------
