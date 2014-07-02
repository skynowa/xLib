/**
 * \file   Test_TcpServer.h
 * \brief
 */


#pragma once

#include <xLib/Net/TcpServer.h>
#include <xLib/Core/xCore.h>
#include <xLib/Test/Test.h>
//-------------------------------------------------------------------------------------------------
class Test_TcpServer :
    public Test
{
public:
                   Test_TcpServer() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------
