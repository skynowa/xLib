/**
 * \file   CxTest_CxSmtp.h
 * \brief
 */


#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Net/CxSmtp.h>
//------------------------------------------------------------------------------
#if xOPENSSL_IS_USE

class CxTest_CxSmtp :
    public CxTest
{
public:
                   CxTest_CxSmtp() {}

    virtual void_t unit(culonglong_t &caseLoops);
};

#endif // xOPENSSL_IS_USE
//------------------------------------------------------------------------------
