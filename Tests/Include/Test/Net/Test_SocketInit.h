/**
 * \file   Test_SocketInit.h
 * \brief
 */


#pragma once

#include <xLib/Net/SocketInit.h>
#include <xLib/Core/Core.h>
#include <xLib/Test/Unit.h>
//-------------------------------------------------------------------------------------------------
class Test_SocketInit :
    public Unit
{
public:
                   Test_SocketInit() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
};
//-------------------------------------------------------------------------------------------------
