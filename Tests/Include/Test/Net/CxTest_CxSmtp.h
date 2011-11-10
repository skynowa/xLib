/****************************************************************************
* Class name:  CxTest_CxSmtp
* Description: test CxSmtp
* File name:   CxTest_CxSmtp.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


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
