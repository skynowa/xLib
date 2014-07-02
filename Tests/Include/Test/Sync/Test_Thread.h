/**
 * \file   Test_Thread.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/UnitTest.h>
#include <xLib/Sync/Thread.h>
//-------------------------------------------------------------------------------------------------
class Test_Thread :
    public UnitTest
{
public:
                   Test_Thread() {}

    virtual void_t unit(culonglong_t &caseLoops);

private:
    void_t         unit1(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------
