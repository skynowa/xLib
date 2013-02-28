/**
 * \file   CxTest_CxLocale.cpp
 * \brief
 */


#include <Test/Common/CxTest_CxLocale.h>


//------------------------------------------------------------------------------
CxTest_CxLocale::CxTest_CxLocale() {

}
//------------------------------------------------------------------------------
CxTest_CxLocale::~CxTest_CxLocale() {

}
//------------------------------------------------------------------------------
/* virtual */
void
CxTest_CxLocale::unit(
    culonglong_t &cullCaseLoops
)
{
    xTEST_CASE("CxLocale::current", cullCaseLoops)
    {
        m_sRv = CxLocale::current();
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE("CxLocale::setCurrent", cullCaseLoops)
    {
        CxLocale::setCurrent( CxLocale::current() );
    }

    xTEST_CASE("CxLocale::setDefault", cullCaseLoops)
    {
        CxLocale::setDefault();
    }

    xTEST_CASE("CxLocale::setCurrent", cullCaseLoops)
    {
        CxLocale::setCurrent(CxLocale::current());
    }
}
//------------------------------------------------------------------------------
