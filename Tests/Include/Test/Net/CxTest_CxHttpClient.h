/**
 * \file   CxTest_CxHttpClient.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Net/CxHttpClient.h>
//-------------------------------------------------------------------------------------------------
class CxTest_CxHttpClient :
    public CxTest
{
public:
                   CxTest_CxHttpClient() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------

