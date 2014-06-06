/**
 * \file   CxTest_CxDir.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/IO/CxDir.h>
#include <xLib/IO/CxFile.h>
//-------------------------------------------------------------------------------------------------
class CxTest_CxDir :
    public CxTest
{
public:
                   CxTest_CxDir() {}

    virtual void_t unit(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------
