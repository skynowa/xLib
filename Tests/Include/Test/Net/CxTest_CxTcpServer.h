/**
 * \file   CxTest_CxTcpServer.h
 * \brief
 */


#pragma once

#include <xLib/Net/CxTcpServer.h>
#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
//------------------------------------------------------------------------------
class CxTest_CxTcpServer :
    public CxTest
{
public:
                   CxTest_CxTcpServer() {}

    virtual void_t unit(culonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------
