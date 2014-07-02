/**
 * \file   Test_MsgBoxT.h
 * \brief  test MsgBoxT
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/Test.h>
#include <xLib/Gui/MsgBox.h>
//-------------------------------------------------------------------------------------------------
class Test_MsgBox :
    public Test
{
public:
                   Test_MsgBox() {}

    virtual void_t unit(culonglong_t &caseLoops);
        ///< test unit
};
//-------------------------------------------------------------------------------------------------
