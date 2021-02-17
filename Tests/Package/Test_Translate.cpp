/**
 * \file  Test_Translate.cpp
 * \brief test Translate
 */


#include <xLib/xLib.h>


//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Translate)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Translate::unit()
{
    xTEST_CASE("Translate")
    {
		Translate translate;

		std::ctstring_t textFroms[]
		{
			xT("UTF-8 is now well-supported and the overwhelmingly preferred character encoding"),
			xT("Language")
		};

		for (const auto &it_textFrom : textFroms) {
			Translate::Language langFrom {};
			Translate::Language langTo {};
			{
				translate.langsDetect(it_textFrom, &langFrom, &langTo);
				xTEST_EQ((int_t)langFrom, (int_t)Translate::Language::En);
				xTEST_EQ((int_t)langTo,   (int_t)Translate::Language::Ru);
			}

			std::tstring_t textToBrief;
			std::tstring_t textToDetail;
			std::tstring_t textToRaw;
			translate.execute(it_textFrom, langFrom, langTo, &textToBrief, &textToDetail, &textToRaw);
			xTEST(!textToBrief.empty());
			xTEST(!textToDetail.empty());
			xTEST(!textToRaw.empty());

			Trace() << xTRACE_VAR(textToBrief);
			Trace() << xTRACE_VAR(textToDetail);
			// Trace() << xTRACE_VAR(textToRaw);
		} // for (textFroms)
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
