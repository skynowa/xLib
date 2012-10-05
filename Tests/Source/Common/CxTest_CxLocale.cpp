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
    //-------------------------------------
    //sGetCurrent
    xTEST_CASE(cullCaseLoops)
    {
        m_sRv = CxLocale::sGetCurrent();
        xTEST_EQ(false, m_sRv.empty());
    }

    //-------------------------------------
    //bSetCurrent
    xTEST_CASE(cullCaseLoops)
    {
        CxLocale::vSetCurrent( CxLocale::sGetCurrent() );
    }

    //-------------------------------------
    //bSetDefault
    xTEST_CASE(cullCaseLoops)
    {
        CxLocale::vSetDefault();
    }

    //-------------------------------------
    //bSetCurrent
    xTEST_CASE(cullCaseLoops)
    {
        CxLocale::vSetCurrent(CxLocale::sGetCurrent());
    }
}
//---------------------------------------------------------------------------
