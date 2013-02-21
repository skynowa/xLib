/**
 * \file   CxTest_CxAutoMutex.h
 * \brief
 */


#ifndef CxTest_CxAutoMutexH
#define CxTest_CxAutoMutexH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Sync/CxAutoMutex.h>
//------------------------------------------------------------------------------
class CxTest_CxAutoMutex :
    public CxTest
{
public:
                 CxTest_CxAutoMutex();
    virtual     ~CxTest_CxAutoMutex();

    virtual void unit(const ulonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------
#endif //CxTest_CxAutoMutexH
