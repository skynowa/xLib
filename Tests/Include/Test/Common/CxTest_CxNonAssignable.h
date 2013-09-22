/**
 * \file   CxTest_CxNonAssignable.h
 * \brief  test CxNonAssignable
 */


#pragma once

#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Common/CxNonAssignable.h>
//------------------------------------------------------------------------------
class CxTest_CxNonAssignable :
    public CxTest
{
public:
                   CxTest_CxNonAssignable();
        ///< constructor
    virtual       ~CxTest_CxNonAssignable();
        ///< destructor

    virtual void_t unit(culonglong_t &cullCaseLoops) xOVERRIDE;
        ///< unit test
};
//------------------------------------------------------------------------------
