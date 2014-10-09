/**
 * \file   Test_Service.h
 * \brief  test Service
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/UnitTest.h>
#include <xLib/Sync/Service.h>
//-------------------------------------------------------------------------------------------------
class Test_Service :
    public UnitTest
    ///< tests for Service
{
public:
                   Test_Service() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
