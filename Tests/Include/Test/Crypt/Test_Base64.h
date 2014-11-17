/**
 * \file   Test_Base64.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/Unit.h>
#include <xLib/Crypt/Base64.h>
//-------------------------------------------------------------------------------------------------
class Test_Base64 :
    public Unit
{
public:
                   Test_Base64() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
};
//-------------------------------------------------------------------------------------------------
