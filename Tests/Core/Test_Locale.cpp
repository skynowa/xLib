/**
 * \file   Test_Locale.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Locale)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Locale::unit()
{
    xTEST_CASE("current")
    {
        m_sRv = core::Locale().current();
        xTEST(!m_sRv.empty());
    }

    xTEST_CASE("setCurrent")
    {
        core::Locale().setCurrent( core::Locale().current() );
    }

    xTEST_CASE("setDefault")
    {
        core::Locale().setDefault();
    }

    xTEST_CASE("setCurrent")
    {
        core::Locale().setCurrent( core::Locale().current() );
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
