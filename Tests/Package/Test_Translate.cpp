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
		std::ctstring_t      textFrom {xT("Coordinate")};
		Translate::cLanguage langFrom {Translate::cLanguage::En};
		Translate::cLanguage langTo   {Translate::cLanguage::Ru};
		std::tstring_t       textToBrief;
		std::tstring_t       textToDetail;
		std::tstring_t       textToRaw;

		Translate translate;
		/// languagesDetect
		translate.execute(textFrom, langFrom, langTo, &textToBrief, &textToDetail, &textToRaw);
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
