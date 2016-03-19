/**
 * \file   Test_SmtpClient.h
 * \brief
 */


#include <xLib/xLib.h>
//-------------------------------------------------------------------------------------------------
using namespace xlib;

#if xHAVE_OPENSSL_CRYPTO

class Test_SmtpClient :
    public Unit
{
public:
                   Test_SmtpClient() {}

    virtual void_t unit(std::csize_t &caseLoops) xOVERRIDE;
};

#endif // xHAVE_OPENSSL_CRYPTO
//-------------------------------------------------------------------------------------------------
