/**
 * \file   CxTest_CxSmtpClient.h
 * \brief
 */


#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Net/CxSmtpClient.h>
//-------------------------------------------------------------------------------------------------
#if xHAVE_OPENSSL_CRYPTO

class CxTest_CxSmtpClient :
    public CxTest
{
public:
                   CxTest_CxSmtpClient() {}

    virtual void_t unit(culonglong_t &caseLoops);
};

#endif // xHAVE_OPENSSL_CRYPTO
//-------------------------------------------------------------------------------------------------
