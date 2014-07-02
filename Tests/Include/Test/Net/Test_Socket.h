/**
 * \file   Test_Socket.h
 * \brief
 */


#pragma once

#include <xLib/Net/Socket.h>
#include <xLib/Core/xCore.h>
#include <xLib/Test/Test.h>
//-------------------------------------------------------------------------------------------------
class Test_Socket :
    public Test
{
public:
                   Test_Socket() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------

