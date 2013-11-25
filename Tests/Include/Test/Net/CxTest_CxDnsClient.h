/**
 * \file   CxTest_CxDnsClient.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Net/CxDnsClient.h>
//------------------------------------------------------------------------------
class CxTest_CxDnsClient :
    public CxTest
{
public:
                   CxTest_CxDnsClient() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//------------------------------------------------------------------------------
