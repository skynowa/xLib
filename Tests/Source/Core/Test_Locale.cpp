/**
 * \file   Test_Locale.cpp
 * \brief
 */


#include <Test/Core/Test_Locale.h>


//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Locale)
//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_Locale::unit(
    std::csize_t &a_caseLoops
)
{
    xTEST_CASE("current", a_caseLoops)
    {
        m_sRv = Locale().current();
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE("setCurrent", a_caseLoops)
    {
        Locale().setCurrent( Locale().current() );
    }

    xTEST_CASE("setDefault", a_caseLoops)
    {
        Locale().setDefault();
    }

    xTEST_CASE("setCurrent", a_caseLoops)
    {
        Locale().setCurrent( Locale().current() );
    }
}
//-------------------------------------------------------------------------------------------------
