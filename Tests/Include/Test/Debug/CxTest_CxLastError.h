/**
 * \file   CxTest_CxLastError.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Debug/CxLastError.h>
//-------------------------------------------------------------------------------------------------
class CxTest_CxLastError :
    public CxTest
{
public:
                   CxTest_CxLastError() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------

