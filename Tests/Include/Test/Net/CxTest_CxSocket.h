/**
 * \file   CxTest_CxSocket.h
 * \brief
 */


#ifndef CxTest_CxSocketH
#define CxTest_CxSocketH
//------------------------------------------------------------------------------
#include <xLib/Net/CxSocket.h>
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
//------------------------------------------------------------------------------
class CxTest_CxSocket :
    public CxTest
{
public:
                 CxTest_CxSocket();
    virtual     ~CxTest_CxSocket();

    virtual void_t unit(culonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------
#endif //CxTest_CxSocketH
