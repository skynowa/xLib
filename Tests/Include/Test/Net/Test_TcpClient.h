/**
 * \file   Test_TcpClient.h
 * \brief
 */


#pragma once

#include <xLib/Net/TcpClient.h>
#include <xLib/Core/Core.h>
#include <xLib/Test/UnitTest.h>
//-------------------------------------------------------------------------------------------------
class Test_TcpClient :
    public UnitTest
{
public:
                   Test_TcpClient() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
};
//-------------------------------------------------------------------------------------------------

