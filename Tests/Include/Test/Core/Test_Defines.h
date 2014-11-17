/**
 * \file   Test_Defines.h
 * \brief  test Defines
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/Unit.h>
#include <xLib/Core/Defines.h>
//-------------------------------------------------------------------------------------------------
class Test_Defines :
    public Unit
{
public:
                   Test_Defines() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
