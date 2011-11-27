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
        m_sRes = CxLocale::sGetCurrent();
        xTEST_EQ(false, m_sRes.empty());
    }

    //-------------------------------------
    //bSetCurrent
    xTEST_CASE(cullCaseLoops)
    {
        m_bRes = CxLocale::bSetCurrent( CxLocale::sGetCurrent() );
        xTEST_EQ(true, m_bRes);
    }

    //-------------------------------------
    //bSetDefault
    xTEST_CASE(cullCaseLoops)
    {
        m_bRes = CxLocale::bSetDefault();
        xTEST_EQ(true, m_bRes);
    }

    //-------------------------------------
    //bSetCurrent
    xTEST_CASE(cullCaseLoops)
    {
        m_bRes = CxLocale::bSetCurrent(CxLocale::sGetCurrent());
        xTEST_EQ(true, m_bRes);
    }

    return true;
}
//---------------------------------------------------------------------------
