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

			std::tstring_t textToBrief;
			std::tstring_t textToDetail;
			std::tstring_t textToRaw;

			translate.execute(it_data.test, &textToBrief, &textToDetail, &textToRaw);
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
