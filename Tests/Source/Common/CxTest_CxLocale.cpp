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
/*virtual*/
bool
CxTest_CxLocale::bUnit(
    const ulonglong_t cullCaseLoops
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
        m_bRv = CxLocale::bSetCurrent( CxLocale::sGetCurrent() );
        xTEST_EQ(true, m_bRv);
    }

    //-------------------------------------
    //bSetDefault
    xTEST_CASE(cullCaseLoops)
    {
        m_bRv = CxLocale::bSetDefault();
        xTEST_EQ(true, m_bRv);
    }

    //-------------------------------------
    //bSetCurrent
    xTEST_CASE(cullCaseLoops)
    {
        m_bRv = CxLocale::bSetCurrent(CxLocale::sGetCurrent());
        xTEST_EQ(true, m_bRv);
    }

    return true;
}
//---------------------------------------------------------------------------
