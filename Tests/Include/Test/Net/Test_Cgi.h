/**
 * \file   Test_Cgi.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/Unit.h>
#include <xLib/Net/Cgi.h>
//-------------------------------------------------------------------------------------------------
class Test_Cgi :
    public Unit
{
public:
                   Test_Cgi() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
};
//-------------------------------------------------------------------------------------------------
