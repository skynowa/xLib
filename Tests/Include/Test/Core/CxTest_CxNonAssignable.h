/**
 * \file   CxTest_CxNonAssignable.h
 * \brief  test CxNonAssignable
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Core/CxNonAssignable.h>
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
