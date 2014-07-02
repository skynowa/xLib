/**
 * \file   Test_DnsClient.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/UnitTest.h>
#include <xLib/Net/DnsClient.h>
//-------------------------------------------------------------------------------------------------
class Test_DnsClient :
    public UnitTest
{
public:
                   Test_DnsClient() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------
