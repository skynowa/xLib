/**
 * \file   CxTest_CxCrc32.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Crypt/CxCrc32.h>
#include <xLib/Filesystem/CxFile.h>
//------------------------------------------------------------------------------
class CxTest_CxCrc32 :
    public CxTest
{
public:
                   CxTest_CxCrc32() {}

    virtual void_t unit(culonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------
