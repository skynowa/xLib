/**
 * \file   CxTest_CxSleeper.h
 * \brief
 */


#ifndef CxTest_CxSleeperH
#define CxTest_CxSleeperH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Sync/CxSleeper.h>
//---------------------------------------------------------------------------
class CxTest_CxSleeper :
    public CxTest
{
public:
                 CxTest_CxSleeper();
    virtual     ~CxTest_CxSleeper();

    virtual void unit(const ulonglong_t &cullCaseLoops);
};
//---------------------------------------------------------------------------
#endif //CxTest_CxSleeperH
