/**
 * \file   Test_HttpClient.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/UnitTest.h>
#include <xLib/Net/HttpClient.h>
//-------------------------------------------------------------------------------------------------
class Test_HttpClient :
    public UnitTest
{
public:
                   Test_HttpClient() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------

