/**
 * \file   Test_Base64.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/Test.h>
#include <xLib/Crypt/Base64.h>
//-------------------------------------------------------------------------------------------------
class Test_Base64 :
    public Test
{
public:
                   Test_Base64() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------
