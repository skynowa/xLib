/**
 * \file   Test_ErrorReport.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/Test.h>
#include <xLib/Debug/ErrorReport.h>
//-------------------------------------------------------------------------------------------------
class Test_ErrorReport :
    public Test
{
public:
                   Test_ErrorReport() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------
