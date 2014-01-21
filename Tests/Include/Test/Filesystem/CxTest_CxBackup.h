/**
 * \file   CxTest_CxBackup.h
 * \brief  test CxBackup
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Filesystem/CxBackup.h>
//-------------------------------------------------------------------------------------------------
class CxTest_CxBackup :
    public CxTest
{
public:
                   CxTest_CxBackup() {}

    virtual void_t unit(culonglong_t &caseLoops);
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
