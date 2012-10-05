/**
 * \file   CxTest_CxCompletionPort.h
 * \brief
 */


#ifndef CxTest_CxCompletionPortH
#define CxTest_CxCompletionPortH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Sync/Win/CxCompletionPort.h>
//---------------------------------------------------------------------------
class CxTest_CxCompletionPort :
    public CxTest
{
    public:
                     CxTest_CxCompletionPort();
        virtual     ~CxTest_CxCompletionPort();

        virtual     void vUnit(const ulonglong_t &cullCaseLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxCompletionPortH
