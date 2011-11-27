/**
 * \file   CxTest_CxChar.h
 * \brief
 */


#ifndef CxTest_CxCharH
#define CxTest_CxCharH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Common/CxChar.h>
//---------------------------------------------------------------------------
class CxTest_CxChar :
    public CxTest
{
    public:
                     CxTest_CxChar();
        virtual     ~CxTest_CxChar();

        virtual bool bUnit(const ulonglong_t cullCaseLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxCharH
