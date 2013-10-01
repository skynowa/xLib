/**
 * \file   CxTest_CxPkcs11.h
 * \brief
 */


#ifndef CxTest_CxPkcs11H
#define CxTest_CxPkcs11H
//------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>

#if   xOS_ENV_WIN
    #include <xLib/Crypt/Pkcs11/All.h>
#endif
//------------------------------------------------------------------------------
class CxTest_CxPkcs11 :
    public CxTest
{
public:
                 CxTest_CxPkcs11();
    virtual     ~CxTest_CxPkcs11();

    virtual void_t unit(culonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------
#endif //CxTest_CxPkcs11H
