/**
 * \file   Test_CookiePv0.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/Unit.h>
#include <xLib/Net/CookiePv0.h>
//-------------------------------------------------------------------------------------------------
class Test_CookiePv0 :
    public Unit
{
public:
                   Test_CookiePv0() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
};
//-------------------------------------------------------------------------------------------------
