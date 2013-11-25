/**
 * \file   CxTest_CxException.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Debug/CxException.h>
//------------------------------------------------------------------------------
class CxTest_CxException :
    public CxTest
{
public:
                   CxTest_CxException() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//------------------------------------------------------------------------------

