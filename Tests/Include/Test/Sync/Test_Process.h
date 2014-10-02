/**
 * \file   Test_Process.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/UnitTest.h>
#include <xLib/Sync/Process.h>
//-------------------------------------------------------------------------------------------------
class Test_Process :
    public UnitTest
{
public:
                   Test_Process() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
};
//-------------------------------------------------------------------------------------------------

