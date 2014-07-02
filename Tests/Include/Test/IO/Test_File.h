/**
 * \file   Test_File.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/UnitTest.h>
#include <xLib/IO/File.h>
//-------------------------------------------------------------------------------------------------
class Test_File :
    public UnitTest
{
public:
                    Test_File() {}

    virtual  void_t unit(culonglong_t &caseLoops);

private:
    void_t          unit1(culonglong_t &caseLoops);
    void_t          unitPrivate(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------
