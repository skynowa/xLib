/**
 * \file   Test_SmtpClient.h
 * \brief
 */


#include <xLib/Core/xCore.h>
#include <xLib/Test/Test.h>
#include <xLib/Net/SmtpClient.h>
//-------------------------------------------------------------------------------------------------
#if xHAVE_OPENSSL_CRYPTO

class Test_SmtpClient :
    public Test
{
public:
                   Test_SmtpClient() {}

    virtual void_t unit(culonglong_t &caseLoops);
};

#endif // xHAVE_OPENSSL_CRYPTO
//-------------------------------------------------------------------------------------------------
