/**
 * \file   CxTest_CxPath.h
 * \brief
 */


#pragma once

#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Filesystem/CxPath.h>
//------------------------------------------------------------------------------
class CxTest_CxPath :
    public CxTest
{
public:
                   CxTest_CxPath();
    virtual       ~CxTest_CxPath();

    virtual void_t unit(culonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------
