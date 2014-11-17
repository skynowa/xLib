/**
 * \file   Test_Socket.h
 * \brief
 */


#pragma once

#include <xLib/Net/Socket.h>
#include <xLib/Core/Core.h>
#include <xLib/Test/Unit.h>
//-------------------------------------------------------------------------------------------------
class Test_Socket :
    public Unit
{
public:
                   Test_Socket() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
};
//-------------------------------------------------------------------------------------------------

