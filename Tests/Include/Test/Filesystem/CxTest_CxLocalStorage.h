/**
 * \file   CxTest_CxLocalStorage.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Filesystem/CxLocalStorage.h>
//-------------------------------------------------------------------------------------------------
class CxTest_CxLocalStorage :
    public CxTest
{
public:
                    CxTest_CxLocalStorage() {}

    virtual  void_t unit(culonglong_t &caseLoops) xOVERRIDE;
};
//-------------------------------------------------------------------------------------------------
