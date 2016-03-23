/**
 * \file   Test_[CLASS_NAME].h
 * \brief  test [CLASS_NAME]
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/Unit.h>
#include <xLib/xxxxxxxxx/[CLASS_NAME].h>
//-------------------------------------------------------------------------------------------------
class Test_[CLASS_NAME] :
    public Unit
    ///< tests for [CLASS_NAME]
{
public:
                   Test_[CLASS_NAME]() {}

    virtual bool_t unit() xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
