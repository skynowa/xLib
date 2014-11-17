/**
 * \file   Test_ErrorReport.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/Unit.h>
#include <xLib/Debug/ErrorReport.h>
//-------------------------------------------------------------------------------------------------
class Test_ErrorReport :
    public Unit
{
public:
                   Test_ErrorReport() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
};
//-------------------------------------------------------------------------------------------------
