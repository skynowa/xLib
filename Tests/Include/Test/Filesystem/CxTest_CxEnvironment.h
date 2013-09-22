/**
 * \file   CxTest_CxEnvironment.h
 * \brief
 */


#pragma once

#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Filesystem/CxEnvironment.h>
//------------------------------------------------------------------------------
class CxTest_CxEnvironment :
    public CxTest
{
public:
                   CxTest_CxEnvironment();
    virtual       ~CxTest_CxEnvironment();

    virtual void_t unit(culonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------
