/**
 * \file  Test_Translate.cpp
 * \brief test Translate
 */


#include <xLib/xLib.h>


//-------------------------------------------------------------------------------------------------
using namespace xl;

xTEST_CLASS(Test_Translate)
xTEST_UNIT(Test_Translate)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Translate::unit()
{
    xTEST_CASE("Translate")
    {
		std::ctstring_t textFrom {xT("Coordinate")};
		std::tstring_t  textToBrief;
		std::tstring_t  textToDetail;
		std::tstring_t  textToRaw;

		Translate translate;

		Translate::Language langFrom {};
		Translate::Language langTo {};
		{
			translate.languagesDetect(textFrom, &langFrom, &langTo);
			xTEST_EQ((int_t)langFrom, (int_t)Translate::Language::En);
			xTEST_EQ((int_t)langTo,   (int_t)Translate::Language::Ru);
		}

		translate.execute(textFrom, langFrom, langTo, &textToBrief, &textToDetail, &textToRaw);
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
