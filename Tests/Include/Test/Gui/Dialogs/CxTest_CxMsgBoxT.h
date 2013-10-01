/**
 * \file   CxTest_CxMsgBoxT.h
 * \brief  test CxMsgBoxT
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Gui/Dialogs/CxMsgBoxT.h>
//------------------------------------------------------------------------------
class CxTest_CxMsgBoxT :
    public CxTest
{
public:
                   CxTest_CxMsgBoxT();
        ///< constructor
    virtual       ~CxTest_CxMsgBoxT();
        ///< destructor

    virtual void_t unit(culonglong_t &cullCaseLoops);
        ///< test unit
};
//------------------------------------------------------------------------------
