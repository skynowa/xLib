/**
 * \file  Translate.cpp
 * \brief Translate text
 */


#include "Translate.h"

#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>
#include <xLib/Package/Curl/HttpClient.h>


namespace xl::package
{

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
Translate::langsDetect(
    std::ctstring_t     &a_text,
    Translate::Language *out_langFrom,
    Translate::Language *out_langTo
) const
{
    xTEST(!a_text.empty());
    xTEST_PTR(out_langFrom);
    xTEST_PTR(out_langTo);

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
        // TODO: defaults for isUnknown
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
Translate::langsDetect(
    std::ctstring_t &a_text,
	std::tstring_t  *out_langFrom,
	std::tstring_t  *out_langTo
) const
{
	if (out_langFrom == nullptr) {
		return;
	}

	if (out_langTo == nullptr) {
		return;
	}

	Language langFrom {};
	Language langTo {};
	langsDetect(a_text, &langFrom, &langTo);

	// [out]
	*out_langFrom = _langCode(langFrom);
	*out_langTo   = _langCode(langTo);
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
    xTEST_NA(a_langFrom);
    xTEST_NA(a_langTo);
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

		baseDataIn.url            = xT("https://translate.google.com/m");
		baseDataIn.accept         = "text/html";
		baseDataIn.acceptEncoding = "gzip, deflate";
		baseDataIn.acceptLanguage = "en-us,en";
		baseDataIn.acceptCharset  = "UTF-8";

		// TODO: curl::HttpClient::Request::Post
	#if 0
		std::map_tstring_t headers
		{
			{"content-type", "application/x-www-form-urlencoded"}
		};

		baseDataIn.addHeaders = headers;
	#endif

		// baseDataIn.request
		{
			std::ctstring_t  sourceLang  = (a_langFrom == Language::Unknown) ?
				xT("auto") : _langCode(a_langFrom);
			std::ctstring_t  targetLang  = _langCode(a_langTo);
			std::ctstring_t &hostLang    = xT("en");

			std::csize_t     querySizeMax = 2048;
			std::ctstring_t &query        = a_textFrom;

			std::ctstring_t  encodingIn  = xT("UTF-8");
			std::ctstring_t  encodingOut = xT("UTF-8");

			xCHECK_DO(query.size() > querySizeMax,
				Cout() << "Warning: " << xTRACE_VAR_2(querySizeMax, query.size()));

			const std::map_tstring_t request
			{
				{"sl", sourceLang},
				{"tl", targetLang},
				{"hl", hostLang},
				{"ie", encodingIn},
				{"oe", encodingOut},
				{"q",  query}
			};

			for (const auto &[param, value] : request) {
				baseDataIn.request += param + "=" + http.escape(value) + "&";
			}

			baseDataIn.request = String::trimRightChars(baseDataIn.request, "&");
		}
	}

	// TODO: curl::HttpClient::Request::Post
	curl::DataOut dataOut;
	bRv = http.request(curl::HttpClient::Request::Get, baseDataIn, &dataOut);
	xTEST(bRv);
	if ( !http.isSuccess(dataOut) ) {
		// Cout() << xTRACE_VAR(dataOut.body);

		*out_textToBrief  = xT("Error: ") + std::to_string(dataOut.responseCode);
		*out_textToDetail = xT("Error: ") + std::to_string(dataOut.responseCode);

		if (out_textToRaw != nullptr) {
			*out_textToRaw = xT("Error: ") + std::to_string(dataOut.responseCode);
		}

		return;
	}

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
void_t
Translate::execute(
    std::ctstring_t &a_textFrom,		///< source text
	std::ctstring_t &a_langFrom,		///< source text language
	std::ctstring_t &a_langTo,			///< target text language
    std::tstring_t  *out_textToBrief,	///< [out] target brief translate
    std::tstring_t  *out_textToDetail,	///< [out] target detail translate
    std::tstring_t  *out_textToRaw		///< [out] target raw translate (HTML) (maybe nullptr)
) const
{
	execute(a_textFrom, _codeLang(a_langFrom), _codeLang(a_langTo),
		out_textToBrief, out_textToDetail, out_textToRaw);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
const std::map<Translate::Language, std::tstring_t> Translate::_langToCodes
{
	{Language::Unknown, xT("")},
	{Language::Auto,    xT("auto")},
	{Language::En,      xT("en")},
	{Language::Ru,      xT("ru")}
};
//-------------------------------------------------------------------------------------------------
void_t
Translate::_responseParse(
    const curl::DataOut &a_dataOut,			///<
    std::tstring_t      *out_textToBrief,	///< [out]
    std::tstring_t      *out_textToDetail,	///< [out]
    std::tstring_t      *out_textToRaw		///< [out]
) const
{
    std::tstring_t body = a_dataOut.body;

    bool isDictionaryText {};
    {

		isDictionaryText = (body.find("Dictionary:") != std::tstring_t::npos);
		// TODO: isDictionaryText - rm
		xTEST(!isDictionaryText);
	}

	// proccess body
	if (isDictionaryText) {
		body = String::replaceAll(body, "Dictionary:", "\n");
		body = String::replaceAll(body, "<br>",        "\n");
	}

	// parse body
	{
		// [out]
		*out_textToBrief = String::cut(body, "<div class=\"result-container\">", "</div>");
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
Translate::_langCode(
	cLanguage a_lang
) const
{
	auto it = _langToCodes.find(a_lang);
	if (it == _langToCodes.cend()) {
		return {};
	}

	return it->second;
}
//-------------------------------------------------------------------------------------------------
Translate::Language
Translate::_codeLang(
	std::ctstring_t &a_code
) const
{
	return Algos::mapFindByValue(_langToCodes, a_code);
}
//-------------------------------------------------------------------------------------------------

} // namespace
