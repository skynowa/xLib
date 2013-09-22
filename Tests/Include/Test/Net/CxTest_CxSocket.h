/**
 * \file   CxTest_CxSocket.h
 * \brief
 */


#pragma once

#include <xLib/Net/CxSocket.h>
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
//------------------------------------------------------------------------------
class CxTest_CxSocket :
    public CxTest
{
public:
                   CxTest_CxSocket();
    virtual       ~CxTest_CxSocket();

    virtual void_t unit(culonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------

