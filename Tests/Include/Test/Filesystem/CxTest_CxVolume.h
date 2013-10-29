/**
 * \file   CxTest_CxVolume.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Filesystem/CxVolume.h>
//------------------------------------------------------------------------------
class CxTest_CxVolume :
    public CxTest
{
public:
                   CxTest_CxVolume() {}

    virtual void_t unit(culonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------
