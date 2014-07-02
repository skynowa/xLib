/**
 * \file   Test_LastError.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/Test.h>
#include <xLib/Debug/LastError.h>
//-------------------------------------------------------------------------------------------------
class Test_LastError :
    public Test
{
public:
                   Test_LastError() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------

