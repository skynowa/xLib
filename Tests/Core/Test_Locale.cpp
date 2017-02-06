/**
 * \file   Test_Locale.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
using namespace xl;

xTEST_CLASS(Test_Locale)
xTEST_UNIT(Test_Locale)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Locale::unit()
{
    xTEST_CASE("current")
    {
        m_sRv = Locale().current();
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE("setCurrent")
    {
        Locale().setCurrent( Locale().current() );
    }

    xTEST_CASE("setDefault")
    {
        Locale().setDefault();
    }

    xTEST_CASE("setCurrent")
    {
        Locale().setCurrent( Locale().current() );
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
