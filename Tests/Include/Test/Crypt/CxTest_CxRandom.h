/**
 * \file   CxTest_CxRandom.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Crypt/CxRandom.h>
//------------------------------------------------------------------------------
class CxTest_CxRandom :
    public CxTest
{
public:
                   CxTest_CxRandom();
    virtual       ~CxTest_CxRandom();

    virtual void_t unit(culonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------

