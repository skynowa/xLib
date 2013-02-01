/**
 * \file   CxTest_CxCurrentThread.h
 * \brief  test CxCurrentThread
 */


#ifndef CxTest_CxCurrentThreadH
#define CxTest_CxCurrentThreadH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
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

    virtual void unit(const ulonglong_t &cullCaseLoops);
        ///< unit test
};
//---------------------------------------------------------------------------
#endif //CxTest_CxCurrentThreadH
