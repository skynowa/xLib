/**
 * \file   CxTest_xDebug.h
 * \brief  test xDebug
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Debug/xDebug.h>
//------------------------------------------------------------------------------
class CxTest_xDebug :
    public CxTest
{
public:
                   CxTest_xDebug() {}

    virtual void_t unit(culonglong_t &caseLoops);
        ///< unit test
};
//------------------------------------------------------------------------------
