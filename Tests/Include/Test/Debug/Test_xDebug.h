/**
 * \file   Test_xDebug.h
 * \brief  test xDebug
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/Test.h>
#include <xLib/Debug/xDebug.h>
//-------------------------------------------------------------------------------------------------
class Test_xDebug :
    public Test
{
public:
                   Test_xDebug() {}

    virtual void_t unit(culonglong_t &caseLoops);
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
