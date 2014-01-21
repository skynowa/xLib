/**
 * \file   CxTest_CxGuid.h
 * \brief  test CxGuid
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Crypt/CxGuid.h>
//-------------------------------------------------------------------------------------------------
class CxTest_CxGuid :
    public CxTest
    ///< tests for CxGuid
{
public:
                   CxTest_CxGuid() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
