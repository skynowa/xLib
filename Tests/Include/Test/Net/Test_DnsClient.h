/**
 * \file   Test_DnsClient.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/Test.h>
#include <xLib/Net/DnsClient.h>
//-------------------------------------------------------------------------------------------------
class Test_DnsClient :
    public Test
{
public:
                   Test_DnsClient() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------
