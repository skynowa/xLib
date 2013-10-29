/**
 * \file   CxTest_CxTcpClient.h
 * \brief
 */


#pragma once

#include <xLib/Net/CxTcpClient.h>
#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
//------------------------------------------------------------------------------
class CxTest_CxTcpClient :
    public CxTest
{
public:
                   CxTest_CxTcpClient() {}

    virtual void_t unit(culonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------

