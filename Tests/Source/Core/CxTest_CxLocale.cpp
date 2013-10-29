/**
 * \file   CxTest_CxLocale.cpp
 * \brief
 */


#include <Test/Core/CxTest_CxLocale.h>


//------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxLocale::unit(
    culonglong_t &a_cullCaseLoops
)
{
    xTEST_CASE("CxLocale::current", a_cullCaseLoops)
    {
        m_sRv = CxLocale::current();
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE("CxLocale::setCurrent", a_cullCaseLoops)
    {
        CxLocale::setCurrent( CxLocale::current() );
    }

    xTEST_CASE("CxLocale::setDefault", a_cullCaseLoops)
    {
        CxLocale::setDefault();
    }

    xTEST_CASE("CxLocale::setCurrent", a_cullCaseLoops)
    {
        CxLocale::setCurrent(CxLocale::current());
    }
}
//------------------------------------------------------------------------------
