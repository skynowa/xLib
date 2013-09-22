/**
 * \file   CxTest_CxLocalStorage.h
 * \brief
 */


#pragma once

#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Filesystem/CxLocalStorage.h>
//------------------------------------------------------------------------------
class CxTest_CxLocalStorage :
    public CxTest
{
public:
                    CxTest_CxLocalStorage();
    virtual        ~CxTest_CxLocalStorage();

    virtual  void_t unit(culonglong_t &cullCaseLoops) xOVERRIDE;
};
//------------------------------------------------------------------------------
