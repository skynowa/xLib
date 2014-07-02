/**
 * \file   Test_Event.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/UnitTest.h>
#include <xLib/Sync/Event.h>
//-------------------------------------------------------------------------------------------------
class Test_Event :
    public UnitTest
{
public:
                   Test_Event() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------
