/**
 * \file   CxTest_CxNonCopyable.h
 * \brief  test CxNonCopyable
 */


#pragma once
#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Core/CxNonCopyable.h>
//------------------------------------------------------------------------------
class CxTest_CxNonCopyable :
    public CxTest
{
public:
                   CxTest_CxNonCopyable();
        ///< constructor
    virtual       ~CxTest_CxNonCopyable();
        ///< destructor

    virtual void_t unit(culonglong_t &cullCaseLoops) xOVERRIDE;
        ///< unit test
};
//------------------------------------------------------------------------------
