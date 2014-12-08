/**
 * \file   Test_Blowfish.h
 * \brief
 */


#pragma once

#include <xLib/xLib.h>
//-------------------------------------------------------------------------------------------------
using namespace xlib;

#if xHAVE_OPENSSL_CRYPTO

class Test_Blowfish :
    public Unit
{
public:
                   Test_Blowfish() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
};

#endif // xHAVE_OPENSSL_CRYPTO
//-------------------------------------------------------------------------------------------------
