/**
 * \file   Test_Dir.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/Unit.h>
#include <xLib/IO/Dir.h>
#include <xLib/IO/File.h>
//-------------------------------------------------------------------------------------------------
class Test_Dir :
    public Unit
{
public:
                   Test_Dir() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
};
//-------------------------------------------------------------------------------------------------
