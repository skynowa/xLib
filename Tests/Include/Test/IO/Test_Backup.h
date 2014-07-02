/**
 * \file   Test_Backup.h
 * \brief  test Backup
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/Test.h>
#include <xLib/IO/Backup.h>
//-------------------------------------------------------------------------------------------------
class Test_Backup :
    public UnitTest
{
public:
                   Test_Backup() {}

    virtual void_t unit(culonglong_t &caseLoops);
        ///< unit test
};
//-------------------------------------------------------------------------------------------------
