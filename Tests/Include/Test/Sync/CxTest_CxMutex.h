/**
 * \file   CxTest_CxMutex.h
 * \brief
 */


#ifndef CxTest_CxMutexH
#define CxTest_CxMutexH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Sync/CxMutex.h>
//------------------------------------------------------------------------------
class CxTest_CxMutex :
    public CxTest
{
public:
                 CxTest_CxMutex();
    virtual     ~CxTest_CxMutex();

    virtual void_t unit(culonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------
#endif //CxTest_CxMutexH
