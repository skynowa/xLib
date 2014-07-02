/**
 * \file   Test_Exception.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/Test.h>
#include <xLib/Debug/Exception.h>
//-------------------------------------------------------------------------------------------------
class Test_Exception :
    public Test
{
public:
                   Test_Exception() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------

