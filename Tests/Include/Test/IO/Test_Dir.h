/**
 * \file   Test_Dir.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/Test.h>
#include <xLib/IO/Dir.h>
#include <xLib/IO/File.h>
//-------------------------------------------------------------------------------------------------
class Test_Dir :
    public UnitTest
{
public:
                   Test_Dir() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------
