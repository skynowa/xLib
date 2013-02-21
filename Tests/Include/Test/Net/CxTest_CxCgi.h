/**
 * \file   CxTest_CxCgi.h
 * \brief
 */


#ifndef CxTest_CxCgiH
#define CxTest_CxCgiH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Net/CxCgi.h>
//------------------------------------------------------------------------------
class CxTest_CxCgi :
    public CxTest
{
public:
                 CxTest_CxCgi();
    virtual     ~CxTest_CxCgi();

    virtual void unit(const ulonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------
#endif //CxTest_CxCgiH
