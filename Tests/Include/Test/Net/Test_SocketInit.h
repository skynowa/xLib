/**
 * \file   Test_SocketInit.h
 * \brief
 */


#pragma once

#include <xLib/Net/SocketInit.h>
#include <xLib/Core/Core.h>
#include <xLib/Test/UnitTest.h>
//-------------------------------------------------------------------------------------------------
class Test_SocketInit :
    public UnitTest
{
public:
                   Test_SocketInit() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
};
//-------------------------------------------------------------------------------------------------
