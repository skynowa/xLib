/**
 * \file   Test_Format.h
 * \brief  test Format
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/Unit.h>
#include <xLib/Core/Format.h>
//-------------------------------------------------------------------------------------------------
class Test_Format :
    public Unit
    ///< tests for Format
{
public:
                   Test_Format() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
