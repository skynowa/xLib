/**
 * \file   Test_User.h
 * \brief  test User
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/Unit.h>
#include <xLib/System/User.h>
//-------------------------------------------------------------------------------------------------
class Test_User :
    public Unit
    ///< tests for User
{
public:
                   Test_User() {}

    virtual bool_t unit() xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
