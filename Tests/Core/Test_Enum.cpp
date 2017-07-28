/**
 * \file   Test_Enum.cpp
 * \brief  test Enum
 */


#include <xLib/xLib.h>
#include <initializer_list>


//-------------------------------------------------------------------------------------------------
using namespace xl;

xTEST_CLASS(Test_Enum)
xTEST_UNIT(Test_Enum)
//-------------------------------------------------------------------------------------------------
enum TestType
{
	ttUnknown = 0,
	ttFirst   = 1,
	ttSecond  = 2,
	ttThird   = 3,
	ttLast    = ttThird + 1
};
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Enum::unit()
{
    xTEST_CASE("Enum::[TEST_CASE_1]")
    {
    	Enum<TestType, 5> enumerator;
    	enumerator.clear();
    	enumerator.assign(ttLast);

    	for (size_t i = 0; i < enumerator.size(); ++ i) {
    		std::cout << enumerator[i] << std::endl;
    	}


    	// initialzer_list<TestType> data = {ttUnknown, ttFirst, ttSecond, ttThird, ttLast};
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
