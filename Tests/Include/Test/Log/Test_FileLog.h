/**
 * \file   Test_FileLog.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/Unit.h>
#include <xLib/Log/FileLog.h>
//-------------------------------------------------------------------------------------------------
class Test_FileLog :
    public Unit
{
public:
                   Test_FileLog() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
};
//-------------------------------------------------------------------------------------------------

