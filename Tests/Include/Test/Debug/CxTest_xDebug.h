/**
 * \file   CxTest_xDebug.h
 * \brief  test xDebug
 */


#pragma once

#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Debug/xDebug.h>
//------------------------------------------------------------------------------
class CxTest_xDebug :
    public CxTest
{
public:
                   CxTest_xDebug();
        ///< constructor
    virtual       ~CxTest_xDebug();
        ///< destructor

    virtual void_t unit(culonglong_t &cullCaseLoops);
        ///< unit test
};
//------------------------------------------------------------------------------
