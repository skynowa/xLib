/**
 * \file   CxTest_CxSmtp.h
 * \brief
 */


#ifndef CxTest_CxSmtpH
#define CxTest_CxSmtpH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Net/CxSmtp.h>
//---------------------------------------------------------------------------
class CxTest_CxSmtp :
    public CxTest
{
    public:
                     CxTest_CxSmtp();
        virtual     ~CxTest_CxSmtp();

        virtual BOOL bUnit(const ULONGLONG cullBlockLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxSmtpH
