/**
 * \file   CxTest_CxConfig.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Filesystem/CxConfig.h>
//-------------------------------------------------------------------------------------------------
class CxTest_CxConfig :
    public CxTest
{
public:
                    CxTest_CxConfig() {}

    virtual  void_t unit(culonglong_t &caseLoops) xOVERRIDE;
};
//-------------------------------------------------------------------------------------------------
