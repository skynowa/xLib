/**
 * \file   CxTest_CxFileTemp.h
 * \brief  test CxFileTemp
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Filesystem/CxFileTemp.h>
//------------------------------------------------------------------------------
class CxTest_CxFileTemp :
    public CxTest
{
public:
                   CxTest_CxFileTemp() {}

    virtual void_t unit(culonglong_t &cullCaseLoops);
        ///< unit test
};
//------------------------------------------------------------------------------

