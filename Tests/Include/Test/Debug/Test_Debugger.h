/**
 * \file   Test_Debugger.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/Test.h>
#include <xLib/Debug/Debugger.h>
//-------------------------------------------------------------------------------------------------
class Test_Debugger :
    public Test
{
public:
                   Test_Debugger() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------

