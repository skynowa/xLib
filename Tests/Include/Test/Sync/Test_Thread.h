/**
 * \file   Test_Thread.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/Test.h>
#include <xLib/Sync/Thread.h>
//-------------------------------------------------------------------------------------------------
class Test_Thread :
    public Test
{
public:
                   Test_Thread() {}

    virtual void_t unit(culonglong_t &caseLoops);

private:
    void_t         unit1(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------
