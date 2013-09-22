/**
 * \file   CxTest_CxString.h
 * \brief
 */


#pragma once

#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Common/CxString.h>
//------------------------------------------------------------------------------
class CxTest_CxString :
    public CxTest
{
public:
                   CxTest_CxString();
    virtual       ~CxTest_CxString();

    virtual void_t unit(culonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------

