/**
 * \file   CxTest_CxBlowfish.h
 * \brief
 */


#ifndef CxTest_CxBlowfishH
#define CxTest_CxBlowfishH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Crypt/OpenSSL/CxBlowfish.h>
//------------------------------------------------------------------------------
class CxTest_CxBlowfish :
    public CxTest
{
public:
                 CxTest_CxBlowfish();
    virtual     ~CxTest_CxBlowfish();

    virtual void_t unit(culonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------
#endif //CxTest_CxBlowfishH
