/**
 * \file   CxTest_CxProcess.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Sync/CxProcess.h>
//------------------------------------------------------------------------------
class CxTest_CxProcess :
    public CxTest
{
public:
                   CxTest_CxProcess() {}

    virtual void_t unit(culonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------

