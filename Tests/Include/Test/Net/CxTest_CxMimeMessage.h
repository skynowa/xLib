/**
 * \file   CxTest_CxMimeMessage.h
 * \brief
 */


#ifndef CxTest_CxMimeMessageH
#define CxTest_CxMimeMessageH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Net/CxMimeMessage.h>
#include <xLib/Net/CxPop3.h>
#include <xLib/Net/CxSmtp.h>
#include <xLib/Net/CxMimeHeader.h>
//------------------------------------------------------------------------------
class CxTest_CxMimeMessage :
    public CxTest
{
public:
                 CxTest_CxMimeMessage();
    virtual     ~CxTest_CxMimeMessage();

    virtual void unit(culonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------
#endif //CxTest_CxMimeMessageH
