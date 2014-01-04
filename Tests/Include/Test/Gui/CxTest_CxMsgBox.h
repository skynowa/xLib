/**
 * \file   CxTest_CxMsgBoxT.h
 * \brief  test CxMsgBoxT
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Gui/CxMsgBox.h>
//-------------------------------------------------------------------------------------------------
class CxTest_CxMsgBox :
    public CxTest
{
public:
                   CxTest_CxMsgBox() {}

    virtual void_t unit(culonglong_t &caseLoops);
        ///< test unit
};
//-------------------------------------------------------------------------------------------------
