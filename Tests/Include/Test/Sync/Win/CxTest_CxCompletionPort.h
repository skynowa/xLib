/**
 * \file   CxTest_CxCompletionPort.h
 * \brief
 */


#ifndef CxTest_CxCompletionPortH
#define CxTest_CxCompletionPortH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Sync/Win/CxCompletionPort.h>
//---------------------------------------------------------------------------
class CxTest_CxCompletionPort :
    public CxTest
{
    public:
                     CxTest_CxCompletionPort();
        virtual     ~CxTest_CxCompletionPort();

        virtual     bool bUnit(const ULONGLONG cullBlockLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxCompletionPortH
