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

    virtual  void_t unit(std::csize_t &caseLoops);

private:
    void_t          unit1(std::csize_t &caseLoops);
    void_t          unitPrivate(std::csize_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------
