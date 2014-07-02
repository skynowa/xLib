/**
 * \file   Test_Guid.h
 * \brief  test Guid
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/Test.h>
#include <xLib/Crypt/Guid.h>
//-------------------------------------------------------------------------------------------------
class Test_Guid :
    public Test
    ///< tests for Guid
{
public:
                   Test_Guid() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
