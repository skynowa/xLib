/**
 * \file   Test_FileTemp.h
 * \brief  test FileTemp
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/Test.h>
#include <xLib/IO/FileTemp.h>
//-------------------------------------------------------------------------------------------------
class Test_FileTemp :
    public Test
{
public:
                   Test_FileTemp() {}

    virtual void_t unit(culonglong_t &caseLoops);
        ///< unit test
};
//-------------------------------------------------------------------------------------------------

