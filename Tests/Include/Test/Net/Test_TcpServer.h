/**
 * \file   Test_TcpServer.h
 * \brief
 */


#pragma once

#include <xLib/Net/TcpServer.h>
#include <xLib/Core/Core.h>
#include <xLib/Test/UnitTest.h>
//-------------------------------------------------------------------------------------------------
class Test_TcpServer :
    public UnitTest
{
public:
                   Test_TcpServer() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
};
//-------------------------------------------------------------------------------------------------
