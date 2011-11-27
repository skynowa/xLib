/**
 * \file   CxTest_CxString.h
 * \brief
 */


#ifndef CxTest_CxStringH
#define CxTest_CxStringH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Common/CxString.h>
//---------------------------------------------------------------------------
class CxTest_CxString :
    public CxTest
{
    public:
                     CxTest_CxString();
        virtual     ~CxTest_CxString();

        virtual     bool bUnit(const ulonglong_t cullCaseLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxStringH
