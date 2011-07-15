/****************************************************************************
* Class name:  CxTest_CxMimeMessage
* Description: test CxMimeMessage
* File name:   CxTest_CxMimeMessage.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxMimeMessageH
#define CxTest_CxMimeMessageH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Net/CxMimeMessage.h>
#include <xLib/Net/CxPop3.h>
#include <xLib/Net/CxSmtp.h>
#include <xLib/Net/CxMimeHeader.h>
//---------------------------------------------------------------------------
class CxTest_CxMimeMessage :
    public CxTest
{
	public:
                     CxTest_CxMimeMessage();
		virtual     ~CxTest_CxMimeMessage();

	    virtual BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxMimeMessageH
