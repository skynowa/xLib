/**
 * \file   Test_TcpClient.h
 * \brief
 */


#pragma once

#include <xLib/Net/TcpClient.h>
#include <xLib/Core/xCore.h>
#include <xLib/Test/Test.h>
//-------------------------------------------------------------------------------------------------
class Test_TcpClient :
    public Test
{
public:
                   Test_TcpClient() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------

