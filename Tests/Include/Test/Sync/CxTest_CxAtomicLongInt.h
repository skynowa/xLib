/**
 * \file   CxTest_CxAtomicLongInt.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Sync/CxAtomicLongInt.h>
//------------------------------------------------------------------------------
class CxTest_CxAtomicLongInt :
    public CxTest
{
public:
                   CxTest_CxAtomicLongInt() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//------------------------------------------------------------------------------
