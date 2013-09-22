/**
 * \file   CxTest_CxConnectionString.h
 * \brief
 */


#pragma once

#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Db/CxConnectionString.h>
//------------------------------------------------------------------------------
class CxTest_CxConnectionString :
    public CxTest
{
public:
                   CxTest_CxConnectionString();
    virtual       ~CxTest_CxConnectionString();

    virtual void_t unit(culonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------

