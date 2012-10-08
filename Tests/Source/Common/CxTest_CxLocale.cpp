/**
 * \file   CxTest_CxLocale.cpp
 * \brief
 */


#include <Test/Common/CxTest_CxLocale.h>


//---------------------------------------------------------------------------
CxTest_CxLocale::CxTest_CxLocale() {

}
//---------------------------------------------------------------------------
CxTest_CxLocale::~CxTest_CxLocale() {

}
//---------------------------------------------------------------------------
/* virtual */
void
CxTest_CxLocale::vUnit(
    const ulonglong_t &cullCaseLoops
)
{
    xTEST_CASE(CxLocale::sGetCurrent, cullCaseLoops)
    {
        m_sRv = CxLocale::sGetCurrent();
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE(CxLocale::vSetCurrent, cullCaseLoops)
    {
        CxLocale::vSetCurrent( CxLocale::sGetCurrent() );
    }

    xTEST_CASE(CxLocale::vSetDefault, cullCaseLoops)
    {
        CxLocale::vSetDefault();
    }

    xTEST_CASE(CxLocale::vSetCurrent, cullCaseLoops)
    {
        CxLocale::vSetCurrent(CxLocale::sGetCurrent());
    }
}
//---------------------------------------------------------------------------
