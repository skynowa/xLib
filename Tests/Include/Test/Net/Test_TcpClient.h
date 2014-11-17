/**
 * \file   Test_TcpClient.h
 * \brief
 */


#pragma once

#include <xLib/Net/TcpClient.h>
#include <xLib/Core/Core.h>
#include <xLib/Test/Unit.h>
//-------------------------------------------------------------------------------------------------
class Test_TcpClient :
    public Unit
{
public:
                   Test_TcpClient() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
};
//-------------------------------------------------------------------------------------------------

