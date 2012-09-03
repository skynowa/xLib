/**
 * \file   CxTest_CxSemaphore.h
 * \brief  test CxSemaphore
 */


#ifndef CxTest_CxSemaphoreH
#define CxTest_CxSemaphoreH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Sync/CxSemaphore.h>
//---------------------------------------------------------------------------
class CxTest_CxSemaphore :
    public CxTest
{
    public:
                      CxTest_CxSemaphore();
            ///< constructor
        virtual      ~CxTest_CxSemaphore();
            ///< destructor

        virtual bool  bUnit(const ulonglong_t cullBlockLoops);
            ///< unit test

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxSemaphoreH
