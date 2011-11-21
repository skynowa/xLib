/**
 * \file   CxTest_CxCurrentThread.h
 * \brief  test CxCurrentThread
 */


#ifndef CxTest_CxCurrentThreadH
#define CxTest_CxCurrentThreadH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Sync/CxCurrentThread.h>
//---------------------------------------------------------------------------
class CxTest_CxCurrentThread :
    public CxTest
{
    public:
                      CxTest_CxCurrentThread();
            ///< constructor
        virtual      ~CxTest_CxCurrentThread();
            ///< destructor

        virtual bool  bUnit(const ulonglong_t cullBlockLoops);
            ///< unit test

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxCurrentThreadH
