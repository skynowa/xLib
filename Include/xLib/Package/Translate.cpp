/**
 * \file  Translate.cpp
 * \brief Translate text
 */


#include "Translate.h"

#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>
#include <xLib/Package/Curl/HttpClient.h>


xNAMESPACE_BEGIN2(xl, package)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
Translate::Translate() :
	IRestClient()
{
}
//-------------------------------------------------------------------------------------------------
void_t
Translate::languagesDetect(
    std::ctstring_t     &a_text,
    Translate::Language *out_langFrom,
    Translate::Language *out_langTo
) const
{
    xTEST(!a_text.empty());
    xTEST(out_langFrom != nullptr);
    xTEST(out_langTo != nullptr);

    std::ctstring_t lettersEn = xT("abcdefghijklmnopqrstuvwxyz");
    std::ctstring_t lettersRu = xT("абвгдеёжзийклмнопрстуфхцчшщъыьэюя");

    std::size_t countEn {};
    std::size_t countRu {};
	{
	    for (int i = 0; i < a_text.size(); ++ i) {
			core::CharT letter( a_text.at(i)/*.toLower()*/ );
			xCHECK_DO(!letter.isAlpha(), continue);

			xCHECK_DO(lettersEn.find(letter.character()) != std::tstring_t::npos, ++ countEn);
			xCHECK_DO(lettersRu.find(letter.character()) != std::tstring_t::npos, ++ countRu);
		}
	}

    cbool_t isEn      = (countEn != 0 && countRu == 0);
    cbool_t isRu      = (countEn == 0 && countRu != 0);
    cbool_t isMixed   = (countEn != 0 && countRu != 0);
    cbool_t isUnknown = (countEn == 0 && countRu == 0);

    if      (isEn) {
        *out_langFrom = Translate::Language::En;
        *out_langTo   = Translate::Language::Ru;

        // Trace() << "Langs: en-ru\n";
    }
    else if (isRu) {
        *out_langFrom = Translate::Language::Ru;
        *out_langTo   = Translate::Language::En;

        // Trace() << "Langs: ru-en\n";
    }
    else if (isMixed) {
        // Trace() << "Langs: mixed-mixed\n";

        cbool_t isPreferEn = (countEn >= countRu);
        cbool_t isPreferRu = (countRu >  countEn);

        if      (isPreferEn) {
            *out_langFrom = Translate::Language::En;
            *out_langTo   = Translate::Language::Ru;

            // Trace() << "Langs (prefer): en-ru\n";
        }
        else if (isPreferRu) {
            *out_langFrom = Translate::Language::Ru;
            *out_langTo   = Translate::Language::En;

            // Trace() << "Langs (prefer): ru-en\n";
        }
        else {
            xTEST(false);
        }
    }
    else if (isUnknown) {
        *out_langFrom = Translate::Language::Unknown;
        *out_langTo   = Translate::Language::Unknown;

        // Trace() << "Langs: unknown-unknown\n";
    }
    else {
        *out_langFrom = Translate::Language::Unknown;
        *out_langTo   = Translate::Language::Unknown;

        Trace() << xTRACE_VAR(countEn);
        Trace() << xTRACE_VAR(countRu);

        xTEST(false);
    }
}
//-------------------------------------------------------------------------------------------------
void_t
Translate::execute(
    std::ctstring_t &a_textFrom,		///< source text
    cLanguage        a_langFrom,		///< source text language
    cLanguage        a_langTo,			///< target text language
    std::tstring_t  *out_textToBrief,	///< [out] target brief translate
    std::tstring_t  *out_textToDetail,	///< [out] target detail translate
    std::tstring_t  *out_textToRaw		///< [out] target raw translate (HTML) (maybe nullptr)
) const
{
    xTEST(!a_textFrom.empty());
    xTEST_DIFF((int_t)a_langFrom, (int_t)Language::Unknown);
    xTEST_DIFF((int_t)a_langTo, (int_t)Language::Unknown);
    xTEST_PTR(out_textToBrief);
    xTEST_PTR(out_textToDetail);
    xTEST_NA(out_textToRaw);

    bool_t bRv {};

	curl::HttpClient http;

	curl::DataIn baseDataIn;
	{
	   /**
		* HTTP POST request:
		*
		* <form action="/m" class="">
		*     ...
		*     <input type="hidden" name="hl" value="ru"/>
		*     <input type="hidden" name="sl" value="auto"/>
		*     <input type="hidden" name="tl" value="ru"/>
		*     <input type="hidden" name="ie" value="UTF-8"/>
		*     <input type="hidden" name="prev" value="_m"/>
		*     <input type="text"   name="q" style="width:65%" maxlength="2048" value=""/><br>
		*     <input type="submit" value="Перевести"/>
		* </form>
		*/

		baseDataIn.url = xT("https://translate.google.com/m");

		baseDataIn.acceptEncoding = "gzip, deflate";
		baseDataIn.acceptLanguage = "en-us,en";
		baseDataIn.acceptCharset  = "UTF-8";

		// baseDataIn.request
		{
			const std::map_tstring_t request
			{
				{"h1", _languageCode(a_langFrom)},
				{"sl", _languageCode(a_langFrom)},
				{"tl", _languageCode(a_langTo)},
				{"ie", "UTF-8"},
				{"q",  a_textFrom}
			};

			for (auto &it_request_data : request) {
				baseDataIn.request += it_request_data.first + "=" + http.escape(it_request_data.second);
				baseDataIn.request += "&";
			}

			baseDataIn.request = String::trimRightChars(baseDataIn.request, "&");
		}
	}

	curl::DataOut dataOut;

	bRv = http.request(curl::HttpClient::RequestType::Post, baseDataIn, &dataOut);
	xTEST(bRv);
	xTEST(!dataOut.headers.empty());
	xTEST(!dataOut.body.empty());

#if 0
	Cout()
		<< xTRACE_VAR(baseDataIn.request)   << std::endl
		<< xT("\n")
		<< xTRACE_VAR(dataOut.contentType)  << std::endl
		<< xTRACE_VAR(dataOut.effectiveUrl) << std::endl
		<< xTRACE_VAR(dataOut.responseCode) << std::endl
		<< xTRACE_VAR(dataOut.totalTimeSec) << std::endl
		<< xT("\n")
		<< xTRACE_VAR(dataOut.headers)      << std::endl
		<< xTRACE_VAR(dataOut.body.size())  << std::endl
		<< xTRACE_VAR(dataOut.body)         << std::endl;
#endif

     _responseParse(dataOut, out_textToBrief, out_textToDetail, out_textToRaw);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
Translate::_responseParse(
    const curl::DataOut &a_dataOut,			///<
    std::tstring_t      *out_textToBrief,	///< [out]
    std::tstring_t      *out_textToDetail,	///< [out]
    std::tstring_t      *out_textToRaw		///< [out]
) const
{
	if (a_dataOut.responseCode != 200) {
		*out_textToBrief  = xT("Error: ") + a_dataOut.responseCode;
		*out_textToDetail = xT("Error: ") + a_dataOut.responseCode;

		if (out_textToRaw != nullptr) {
			*out_textToRaw = xT("Error: ") + a_dataOut.responseCode;
		}

		return;
	}

    std::tstring_t body = a_dataOut.body;

    bool isDictionaryText {};
    {

		isDictionaryText = (body.find("Dictionary:") != std::tstring_t::npos);
		// TODO: rm
		xTEST(!isDictionaryText);
	}

	// proccess body
	{
	#if 0
		response.replace("Dictionary:", "\n");
		response.replace("<br>", "\n");
	#else
		body = String::replaceAll(body, "Dictionary:", "\n");
		body = String::replaceAll(body, "<br>",        "\n");
	#endif
	}

	// parse body
	{
		// [out]
		*out_textToBrief = String::cut(body, "<div dir=\"ltr\" class=\"t0\">", "</div>");
		xTEST(!out_textToBrief->empty());

		// [out]
		if (isDictionaryText) {
			// TODO: docList.at(5).toElement().text();
			*out_textToDetail = "[TODO]";
			xTEST(!out_textToDetail->empty());
		} else {
			*out_textToDetail = xT("n/a");
		}
	}

    // out
	if (out_textToRaw != nullptr) {
		*out_textToRaw = body;
	}
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Translate::_languageCode(
	cLanguage a_lang
) const
{
	std::map<Language, std::tstring_t> langToCodes
	{
		{Language::Unknown, xT("")},
		{Language::Auto,    xT("auto")},
		{Language::En,      xT("en")},
		{Language::Ru,      xT("ru")}
	};

	auto it = langToCodes.find(a_lang);
	if (it == langToCodes.end()) {
		return {};
	}

	return it->second;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, package)
