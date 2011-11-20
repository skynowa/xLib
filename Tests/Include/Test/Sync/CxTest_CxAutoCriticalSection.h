/**
 * \file   CxTest_CxAutoCriticalSection.h
 * \brief
 */


#ifndef CxTest_CxAutoCriticalSectionH
#define CxTest_CxAutoCriticalSectionH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Sync/CxAutoCriticalSection.h>
//---------------------------------------------------------------------------
class CxTest_CxAutoCriticalSection :
    public CxTest
{
    public:
                     CxTest_CxAutoCriticalSection();
        virtual     ~CxTest_CxAutoCriticalSection();

        virtual bool bUnit(const ULONGLONG cullBlockLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxAutoCriticalSectionH
