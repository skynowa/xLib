/**
 * \file   CxTest_CxEvent.h
 * \brief
 */


#ifndef CxTest_CxEventH
#define CxTest_CxEventH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Sync/CxEvent.h>
//---------------------------------------------------------------------------
class CxTest_CxEvent :
    public CxTest
{
    public:
                     CxTest_CxEvent();
        virtual     ~CxTest_CxEvent();

        virtual bool bUnit(const ULONGLONG cullBlockLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxEventH
