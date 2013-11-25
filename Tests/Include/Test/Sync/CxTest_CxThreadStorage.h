/**
 * \file   CxTest_CxThreadStorage.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Sync/CxThreadStorage.h>
//------------------------------------------------------------------------------
class CxTest_CxThreadStorage :
    public CxTest
{
public:
                   CxTest_CxThreadStorage() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//------------------------------------------------------------------------------
