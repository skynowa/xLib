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
		Translate translate;

		std::ctstring_t textFrom {xT("UTF-8 is now well-supported and the overwhelmingly "
			"preferred character encoding")};

		Translate::Language langFrom {};
		Translate::Language langTo {};
		{
			translate.languagesDetect(textFrom, &langFrom, &langTo);
			xTEST_EQ((int_t)langFrom, (int_t)Translate::Language::En);
			xTEST_EQ((int_t)langTo,   (int_t)Translate::Language::Ru);
		}

		std::tstring_t textToBrief;
		std::tstring_t textToDetail;
		std::tstring_t textToRaw;
		translate.execute(textFrom, langFrom, langTo, &textToBrief, &textToDetail, &textToRaw);
		xTEST(!textToBrief.empty());
		xTEST(!textToDetail.empty());
		xTEST(!textToRaw.empty());

		Trace() << xTRACE_VAR(textToBrief);
		Trace() << xTRACE_VAR(textToDetail);
		// Trace() << xTRACE_VAR(textToRaw);
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
