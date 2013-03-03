/**
 * \file   CxTest_CxHandleT.h
 * \brief
 */


#ifndef CxHandleT_CxHandleTH
#define CxHandleT_CxHandleTH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Common/CxHandleT.h>
//------------------------------------------------------------------------------
class CxTest_CxHandleT :
    public CxTest
{
public:
                 CxTest_CxHandleT();
    virtual     ~CxTest_CxHandleT();

    virtual void_t unit(culonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------
#endif //CxHandleT_CxHandleTH
