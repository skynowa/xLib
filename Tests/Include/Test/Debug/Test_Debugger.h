/**
 * \file   Test_Debugger.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/Test.h>
#include <xLib/Debug/Debugger.h>
//-------------------------------------------------------------------------------------------------
class Test_Debugger :
    public UnitTest
{
public:
                   Test_Debugger() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------

