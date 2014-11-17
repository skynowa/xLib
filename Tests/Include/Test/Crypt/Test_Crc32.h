/**
 * \file   Test_Crc32.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/Unit.h>
#include <xLib/Crypt/Crc32.h>
#include <xLib/IO/File.h>
//-------------------------------------------------------------------------------------------------
class Test_Crc32 :
    public Unit
{
public:
                   Test_Crc32() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
};
//-------------------------------------------------------------------------------------------------
