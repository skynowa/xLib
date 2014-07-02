/**
 * \file   Test_Dll.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/UnitTest.h>
#include <xLib/IO/Dll.h>
//-------------------------------------------------------------------------------------------------
class Test_Dll :
    public UnitTest
{
public:
                   Test_Dll() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------
