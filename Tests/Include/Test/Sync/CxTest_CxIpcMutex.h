/**
 * \file   CxTest_CxIpcMutex.h
 * \brief
 */


#ifndef CxTest_CxIpcMutexH
#define CxTest_CxIpcMutexH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Sync/CxIpcMutex.h>
//------------------------------------------------------------------------------
class CxTest_CxIpcMutex :
    public CxTest
{
public:
                 CxTest_CxIpcMutex();
    virtual     ~CxTest_CxIpcMutex();

    virtual void_t unit(culonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------
#endif //CxTest_CxIpcMutexH
