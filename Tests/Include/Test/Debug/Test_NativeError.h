/**
 * \file   Test_NativeError.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/Unit.h>
#include <xLib/Debug/NativeError.h>
//-------------------------------------------------------------------------------------------------
class Test_NativeError :
    public Unit
{
public:
                   Test_NativeError() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
};
//-------------------------------------------------------------------------------------------------

