/**
 * \file   Test_Bitset.cpp
 * \brief  test Bitset
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Bitset)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Bitset::unit()
{
	// TEST: Bitset

    xTEST_CASE("Bitset")
    {
        Bitset bits(2);
        std::tcout << xTRACE_VAR(bits) << std::endl;
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
