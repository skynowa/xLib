/**
 * \file   CxTest_CxBase64.h
 * \brief
 */


#ifndef CxTest_CxBase64H
#define CxTest_CxBase64H
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Crypt/OpenSSL/CxBase64.h>
//------------------------------------------------------------------------------
#if xOPENSSL_IS_USE

class CxTest_CxBase64 :
    public CxTest
{
public:
                 CxTest_CxBase64();
    virtual     ~CxTest_CxBase64();

    virtual void_t unit(culonglong_t &cullCaseLoops);
};

#endif // xOPENSSL_IS_USE
//------------------------------------------------------------------------------
#endif //CxTest_CxBase64H
