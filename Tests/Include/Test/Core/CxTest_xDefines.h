/**
 * \file   CxTest_xDefines.h
 * \brief  test xDefines
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Core/xDefines.h>
//------------------------------------------------------------------------------
class CxTest_xDefines :
    public CxTest
{
public:
                   CxTest_xDefines() {}

    virtual void_t unit(culonglong_t &caseLoops);
        ///< unit test
};
//------------------------------------------------------------------------------
