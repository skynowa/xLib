/**
 * \file   Test_MsgBoxT.h
 * \brief  test MsgBoxT
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/UnitTest.h>
#include <xLib/Gui/MsgBox.h>
//-------------------------------------------------------------------------------------------------
class Test_MsgBox :
    public UnitTest
{
public:
                   Test_MsgBox() {}

    virtual void_t unit(culonglong_t &caseLoops);
        ///< test unit
};
//-------------------------------------------------------------------------------------------------
