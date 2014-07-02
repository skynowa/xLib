/**
 * \file   Test_Dll.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/Test.h>
#include <xLib/IO/Dll.h>
//-------------------------------------------------------------------------------------------------
class Test_Dll :
    public Test
{
public:
                   Test_Dll() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------
