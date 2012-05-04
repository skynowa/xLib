/**
 * \file   CxTest_CxHandleT.h
 * \brief
 */


#ifndef CxHandleT_CxHandleTH
#define CxHandleT_CxHandleTH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Common/CxHandleT.h>
//---------------------------------------------------------------------------
class CxTest_CxHandleT :
    public CxTest
{
    public:
                     CxTest_CxHandleT();
        virtual     ~CxTest_CxHandleT();

        virtual bool bUnit(const ulonglong_t cullCaseLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxHandleT_CxHandleTH
