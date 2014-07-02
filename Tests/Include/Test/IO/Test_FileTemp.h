/**
 * \file   Test_FileTemp.h
 * \brief  test FileTemp
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/UnitTest.h>
#include <xLib/IO/FileTemp.h>
//-------------------------------------------------------------------------------------------------
class Test_FileTemp :
    public UnitTest
{
public:
                   Test_FileTemp() {}

    virtual void_t unit(culonglong_t &caseLoops);
        ///< unit test
};
//-------------------------------------------------------------------------------------------------

