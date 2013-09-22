/**
 * \file   CxTest_CxChar.h
 * \brief
 */


#pragma once

#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Common/CxChar.h>
//------------------------------------------------------------------------------
class CxTest_CxChar :
    public CxTest
{
public:
                   CxTest_CxChar();
    virtual       ~CxTest_CxChar();

    virtual void_t unit(culonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------
