/**
 * \file   CxTest_CxCriticalSection.h
 * \brief
 */


#ifndef CxTest_CxCriticalSectionH
#define CxTest_CxCriticalSectionH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Sync/CxCriticalSection.h>
//---------------------------------------------------------------------------
class CxTest_CxCriticalSection :
    public CxTest
{
    public:
                     CxTest_CxCriticalSection();
        virtual     ~CxTest_CxCriticalSection();

        virtual bool bUnit(const ulonglong_t cullCaseLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxCriticalSectionH
