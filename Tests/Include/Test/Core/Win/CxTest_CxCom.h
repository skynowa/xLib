/**
 * \file   CxTest_CxCom.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Core/Win/CxCom.h>
//-------------------------------------------------------------------------------------------------
class CxTest_CxCom :
    public CxTest
{
public:
                   CxTest_CxCom() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------
