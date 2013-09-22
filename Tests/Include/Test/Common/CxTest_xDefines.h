/**
 * \file   CxTest_xDefines.h
 * \brief  test xDefines
 */


#pragma once

#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Common/xDefines.h>
//------------------------------------------------------------------------------
class CxTest_xDefines :
    public CxTest
{
public:
                  CxTest_xDefines();
        ///< constructor
    virtual      ~CxTest_xDefines();
        ///< destructor

    virtual void_t unit(culonglong_t &cullCaseLoops);
        ///< unit test
};
//------------------------------------------------------------------------------
