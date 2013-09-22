/**
 * \file   CxTest_CxFileTemp.h
 * \brief  test CxFileTemp
 */


#pragma once

#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Filesystem/CxFileTemp.h>
//------------------------------------------------------------------------------
class CxTest_CxFileTemp :
    public CxTest
{
public:
                   CxTest_CxFileTemp();
        ///< constructor
    virtual       ~CxTest_CxFileTemp();
        ///< destructor

    virtual void_t unit(culonglong_t &cullCaseLoops);
        ///< unit test
};
//------------------------------------------------------------------------------

