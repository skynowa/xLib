/**
 * \file   CxTest_CxSleeper.h
 * \brief
 */


#ifndef CxTest_CxSleeperH
#define CxTest_CxSleeperH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Sync/CxSleeper.h>
//---------------------------------------------------------------------------
class CxTest_CxSleeper :
    public CxTest
{
    public:
                     CxTest_CxSleeper();
        virtual     ~CxTest_CxSleeper();

        virtual BOOL bUnit(const ULONGLONG cullBlockLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxSleeperH
