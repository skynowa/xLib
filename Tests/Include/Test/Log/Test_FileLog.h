/**
 * \file   Test_FileLog.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/Test.h>
#include <xLib/Log/FileLog.h>
//-------------------------------------------------------------------------------------------------
class Test_FileLog :
    public Test
{
public:
                   Test_FileLog() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------

