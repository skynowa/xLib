/**
 * \file   Test_SocketInit.h
 * \brief
 */


#pragma once

#include <xLib/Net/SocketInit.h>
#include <xLib/Core/xCore.h>
#include <xLib/Test/Test.h>
//-------------------------------------------------------------------------------------------------
class Test_SocketInit :
    public Test
{
public:
                   Test_SocketInit() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------
