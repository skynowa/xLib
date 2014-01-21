/**
 * \file   CxTest_CxDll.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Filesystem/CxDll.h>
//-------------------------------------------------------------------------------------------------
class CxTest_CxDll :
    public CxTest
{
public:
                   CxTest_CxDll() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------
