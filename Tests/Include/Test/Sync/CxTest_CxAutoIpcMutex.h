/**
 * \file   CxTest_CxAutoIpcMutex.h
 * \brief
 */


#ifndef CxTest_CxAutoIpcMutexH
#define CxTest_CxAutoIpcMutexH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Sync/CxAutoIpcMutex.h>
//------------------------------------------------------------------------------
class CxTest_CxAutoIpcMutex :
    public CxTest
{
public:
                 CxTest_CxAutoIpcMutex();
    virtual     ~CxTest_CxAutoIpcMutex();

    virtual void unit(const ulonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------
#endif //CxTest_CxAutoIpcMutexH
