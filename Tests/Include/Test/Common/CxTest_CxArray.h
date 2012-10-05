/**
 * \file   CxTest_CxArray.h
 * \brief
 */


#ifndef CxTest_CxArrayH
#define CxTest_CxArrayH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Common/CxArray.h>
//---------------------------------------------------------------------------
class CxTest_CxArray :
    public CxTest
{
    public:
                     CxTest_CxArray();
        virtual     ~CxTest_CxArray();

        virtual void vUnit(const ulonglong_t &cullCaseLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxArrayH
