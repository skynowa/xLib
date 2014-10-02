/**
 * \file   Test_Locale.cpp
 * \brief
 */


#include <Test/Core/Test_Locale.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_Locale::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("Locale::current", a_caseLoops)
    {
        m_sRv = Locale().current();
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE("Locale::setCurrent", a_caseLoops)
    {
        Locale().setCurrent( Locale().current() );
    }

    xTEST_CASE("Locale::setDefault", a_caseLoops)
    {
        Locale().setDefault();
    }

    xTEST_CASE("Locale::setCurrent", a_caseLoops)
    {
        Locale().setCurrent( Locale().current() );
    }
}
//-------------------------------------------------------------------------------------------------
