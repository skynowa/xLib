/**
 * \file   Test_Cgi.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/Test.h>
#include <xLib/Net/Cgi.h>
//-------------------------------------------------------------------------------------------------
class Test_Cgi :
    public Test
{
public:
                   Test_Cgi() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------
