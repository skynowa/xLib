/**
 * \file   Test_Volume.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/Unit.h>
#include <xLib/IO/Volume.h>
//-------------------------------------------------------------------------------------------------
class Test_Volume :
    public Unit
{
public:
                   Test_Volume() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
};
//-------------------------------------------------------------------------------------------------
