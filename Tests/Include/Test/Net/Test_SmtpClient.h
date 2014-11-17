/**
 * \file   Test_SmtpClient.h
 * \brief
 */


#include <xLib/Core/Core.h>
#include <xLib/Test/Unit.h>
#include <xLib/Net/SmtpClient.h>
//-------------------------------------------------------------------------------------------------
#if xHAVE_OPENSSL_CRYPTO

class Test_SmtpClient :
    public Unit
{
public:
                   Test_SmtpClient() {}

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE;
};

#endif // xHAVE_OPENSSL_CRYPTO
//-------------------------------------------------------------------------------------------------
