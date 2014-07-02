/**
 * \file   Test_Event.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/Test.h>
#include <xLib/Sync/Event.h>
//-------------------------------------------------------------------------------------------------
class Test_Event :
    public Test
{
public:
                   Test_Event() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------
