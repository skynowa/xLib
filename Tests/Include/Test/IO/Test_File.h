/**
 * \file   Test_File.h
 * \brief
 */


#pragma once

#include <xLib/xLib.h>
//-------------------------------------------------------------------------------------------------
using namespace xlib;

class Test_File :
    public Unit
{
public:
                    Test_File() {}

    virtual  void_t unit(culonglong_t &caseLoops);

private:
    void_t          unit1(culonglong_t &caseLoops);
    void_t          unitPrivate(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------
