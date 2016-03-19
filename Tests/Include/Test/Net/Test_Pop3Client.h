/**
 * \file   Test_Pop3Client.h
 * \brief
 */


#pragma once

#include <xLib/xLib.h>
//-------------------------------------------------------------------------------------------------
using namespace xlib;

#if xHAVE_OPENSSL_CRYPTO

class Test_Pop3Client :
    public Unit
{
public:
                   Test_Pop3Client() {}

    virtual void_t unit(std::csize_t &caseLoops) xOVERRIDE;
};

#endif // xHAVE_OPENSSL_CRYPTO
//-------------------------------------------------------------------------------------------------
