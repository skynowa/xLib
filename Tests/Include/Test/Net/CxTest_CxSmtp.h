/**
 * \file   CxTest_CxSmtp.h
 * \brief
 */


#ifndef CxTest_CxSmtpH
#define CxTest_CxSmtpH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Net/CxSmtp.h>
//---------------------------------------------------------------------------
class CxTest_CxSmtp :
    public CxTest
{
public:
                 CxTest_CxSmtp();
    virtual     ~CxTest_CxSmtp();

    virtual void vUnit(const ulonglong_t &cullCaseLoops);
};
//---------------------------------------------------------------------------
#endif //CxTest_CxSmtpH
