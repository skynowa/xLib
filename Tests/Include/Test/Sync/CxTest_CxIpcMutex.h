/**
 * \file   CxTest_CxIpcMutex.h
 * \brief
 */


#ifndef CxTest_CxIpcMutexH
#define CxTest_CxIpcMutexH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Sync/CxIpcMutex.h>
//---------------------------------------------------------------------------
class CxTest_CxIpcMutex :
    public CxTest
{
    public:
                     CxTest_CxIpcMutex();
        virtual     ~CxTest_CxIpcMutex();

        virtual bool bUnit(const ulonglong_t cullCaseLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxIpcMutexH
