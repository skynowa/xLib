/**
 * \file   Test_HttpClient.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/Test.h>
#include <xLib/Net/HttpClient.h>
//-------------------------------------------------------------------------------------------------
class Test_HttpClient :
    public Test
{
public:
                   Test_HttpClient() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------

