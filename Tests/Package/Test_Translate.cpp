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
		const data2_tstring_t datas[]
		{
			{xT("UTF-8 is now well-supported"), xT("UTF-8 теперь хорошо поддерживается")},
			{xT("Language"), xT("Язык")}
		};

		for (const auto &it_data : datas) {
			Translate translate;

			Translate::Language langFrom {};
			Translate::Language langTo {};
			{
				translate.langsDetect(it_data.test, &langFrom, &langTo);
				xTEST_EQ((int_t)langFrom, (int_t)Translate::Language::En);
				xTEST_EQ((int_t)langTo,   (int_t)Translate::Language::Ru);
			}

			std::tstring_t textToBrief;
			std::tstring_t textToDetail;
			std::tstring_t textToRaw;
			translate.execute(it_data.test, langFrom, langTo, &textToBrief, &textToDetail, &textToRaw);
			xTEST_EQ(textToBrief, it_data.expect);
			xTEST_EQ(textToDetail, std::tstring_t(xT("n/a")));
			xTEST(!textToRaw.empty());

			// Trace() << xTRACE_VAR(textToBrief);
			// Trace() << xTRACE_VAR(textToDetail);
			// Trace() << xTRACE_VAR(textToRaw);
		} // for (datas)
	}

	return true;
}
//-------------------------------------------------------------------------------------------------
