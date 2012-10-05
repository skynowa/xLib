/**
 * \file   CxTest_CxCom.h
 * \brief
 */


#ifndef CxTest_CxComH
#define CxTest_CxComH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Common/Win/CxCom.h>
//---------------------------------------------------------------------------
class CxTest_CxCom :
    public CxTest
{
    public:
                     CxTest_CxCom();
        virtual     ~CxTest_CxCom();

        virtual void vUnit(const ulonglong_t &cullCaseLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxComH
