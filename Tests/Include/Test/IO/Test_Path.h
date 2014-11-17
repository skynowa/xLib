/**
 * \file   Test_Path.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/Unit.h>
#include <xLib/IO/Path.h>
//-------------------------------------------------------------------------------------------------
class Test_Path :
    public Unit
{
public:
                   Test_Path() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
};
//-------------------------------------------------------------------------------------------------
