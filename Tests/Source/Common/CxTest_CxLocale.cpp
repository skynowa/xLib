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
BOOL
CxTest_CxLocale::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    //-------------------------------------
    //sGetCurrent
    xTEST_BLOCK(cullBlockLoops)
    {
        m_sRes = CxLocale::sGetCurrent();
        xTEST_EQ(false, m_sRes.empty());
    }

    //-------------------------------------
    //bSetCurrent
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = CxLocale::bSetCurrent( CxLocale::sGetCurrent() );
        xTEST_DIFF(FALSE, m_bRes);
    }

    //-------------------------------------
    //bSetDefault
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = CxLocale::bSetDefault();
        xTEST_DIFF(FALSE, m_bRes);
    }

    //-------------------------------------
    //bSetCurrent
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = CxLocale::bSetCurrent(CxLocale::sGetCurrent());
        xTEST_DIFF(FALSE, m_bRes);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
