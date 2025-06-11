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
	if ( isGithubCI() ) {
		LogCout() << "GithubCI - skip";
		return true;
	}

	xTEST_CASE("Translate")
	{
		const data2_tstring_t datas[]
		{
			{xT("UTF-8 is now well-supported"), xT("UTF-8 теперь хорошо поддерживается")},
			{xT("Language"), xT("Язык")}
		};

		for (const auto &it_data : datas) {
			Translate translate;

			std::tstring_t textToBrief;
			std::tstring_t textToDetail;
			std::tstring_t textToRaw;
			std::tstring_t langFrom;
			std::tstring_t langTo;

			translate.run(it_data.test, &textToBrief, &textToDetail, &textToRaw, &langFrom, &langTo);
			xTEST_EQ(textToBrief, it_data.expect);
			xTEST_EQ(textToDetail, std::tstring_t(xT("n/a")));
			xTEST(!textToRaw.empty());
			xTEST(!langFrom.empty());
			xTEST(!langTo.empty());

			// LogCout() << xTRACE_VAR(textToBrief);
			// LogCout() << xTRACE_VAR(textToDetail);
			// LogCout() << xTRACE_VAR(textToRaw);
		} // for (datas)
	}

	return true;
}
//-------------------------------------------------------------------------------------------------
