/**
 * \file   CxTest_CxSystemInfo.h
 * \brief
 */


#ifndef CxTest_CxSystemInfoH
#define CxTest_CxSystemInfoH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Common/CxSystemInfo.h>
//------------------------------------------------------------------------------
class CxTest_CxSystemInfo :
    public CxTest
{
public:
                 CxTest_CxSystemInfo();
    virtual     ~CxTest_CxSystemInfo();

    virtual void unit(culonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------
#endif //CxTest_CxSystemInfoH
