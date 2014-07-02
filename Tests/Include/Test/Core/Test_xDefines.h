/**
 * \file   Test_xDefines.h
 * \brief  test xDefines
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/Test.h>
#include <xLib/Core/xDefines.h>
//-------------------------------------------------------------------------------------------------
class Test_xDefines :
    public Test
{
public:
                   Test_xDefines() {}

    virtual void_t unit(culonglong_t &caseLoops);
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
