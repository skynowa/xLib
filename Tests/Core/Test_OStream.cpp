/**
 * \file  Test_OStream.cpp
 * \brief test OStream
 */


#include <xLib/xLib.h>


//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_OStream)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_OStream::unit()
{
    xTEST_CASE("operator << (OStream)")
    {
		ddouble_t d(10.45);

		m_sRv = (OStream() << d).str();
		xTEST_EQ(m_sRv, std::tstring_t("10.45"));
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
