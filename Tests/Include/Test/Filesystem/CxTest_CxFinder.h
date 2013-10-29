/**
 * \file   CxTest_CxFinder.h
 * \brief  test CxFinder
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Filesystem/CxFinder.h>
//------------------------------------------------------------------------------
class CxTest_CxFinder :
    public CxTest
    ///< tests for CxFinder
{
public:
                   CxTest_CxFinder() {}

    virtual void_t unit(culonglong_t &cullCaseLoops) xOVERRIDE;
        ///< unit test
};
//------------------------------------------------------------------------------

