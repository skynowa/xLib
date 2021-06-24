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
Translate::execute(
    std::ctstring_t &a_textFrom,		///< source text
    std::tstring_t  *out_textToBrief,	///< [out] target brief translate
    std::tstring_t  *out_textToDetail,	///< [out] target detail translate
    std::tstring_t  *out_textToRaw,		///< [out] target raw translate (HTML) (maybe nullptr)
    std::tstring_t  *out_langFrom,		///< [out] from language ISO code
    std::tstring_t  *out_langTo			///< [out] to language ISO code
)
{
    xTEST(!a_textFrom.empty());
    xTEST_PTR(out_textToBrief);
    xTEST_PTR(out_textToDetail);
    xTEST_NA(out_textToRaw);
    xTEST_PTR(out_langFrom);
    xTEST_PTR(out_langTo);

    bool_t bRv {};

	curl::DataIn baseDataIn;
	{
		std::ctstring_t encoding = xT("UTF-8");

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
		*     <input type="text"   name="q" style="width:65%" maxlength="2048" value="волк"/><br>
		*     <input type="submit" value="Перевести"/>
		* </form>
		*/

		baseDataIn.url            = xT("https://translate.google.com/m");
		baseDataIn.accept         = xT("text/html");
		baseDataIn.acceptEncoding = xT("gzip, deflate");
		baseDataIn.acceptLanguage = xT("en-us,en");
		baseDataIn.acceptCharset  = encoding;

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
		   /**
			* Google Translate query params
			*
			* https://stackoverflow.com/questions/26714426/what-is-the-meaning-of-google-translate-query-params
			*
			* sl - source language code (auto for autodetection)
			* tl - translation language
			* hl - host language
			* q  - source text / word
			* ie - input encoding (a guess)
			* oe - output encoding (a guess)
			* dt - may be included more than once and specifies what to return in the reply
			*
			* Here are some values for dt. If the value is set, the following data will be returned:
			*
			* t  - translation of source text
			* at - alternate translations
			* rm - transcription / transliteration of source and translated texts
			* bd - dictionary, in case source text is one word (you get translations with articles,
			*      reverse translations, etc.)
			* md - definitions of source text, if it's one word
			* ss - synonyms of source text, if it's one word
			* ex - examples
			* rw - See also list
			* dj - Json response with names (dj=1)
			*/

			Language langFrom {};
			Language langTo {};
			_langsDetect(a_textFrom, &langFrom, &langTo);

			std::ctstring_t  sourceLang   = (langFrom == Language::Unknown) ?
				xT("auto") : _langCode(langFrom);
			std::ctstring_t  targetLang   = _langCode(langTo);
			std::ctstring_t  hostLang     = xT("en");

			std::csize_t     querySizeMax = 2048;
			std::ctstring_t &query        = a_textFrom;

			std::ctstring_t  encodingIn   = encoding;
			std::ctstring_t  encodingOut  = encoding;

			xCHECK_DO(query.size() > querySizeMax,
				Cout() << xT("Warning: ") << xTRACE_VAR_2(querySizeMax, query.size()));

			const std::map_tstring_t request
			{
				{xT("sl"), sourceLang},
				{xT("tl"), targetLang},
				{xT("hl"), hostLang},
				{xT("ie"), encodingIn},
				{xT("oe"), encodingOut},
				{xT("q"),  query}
			};

			// Cout() << xTRACE_VAR(request);

			for (const auto &[param, value] : request) {
				baseDataIn.request += param + xT("=") + _http.escape(value) + xT("&");
			}

			baseDataIn.request = String::trimRightChars(baseDataIn.request, xT("&"));

			// [out]
			*out_langFrom = sourceLang;
			*out_langTo   = targetLang;
		}
	}

	// TODO: curl::HttpClient::Request::Post
	curl::DataOut dataOut;
	bRv = _http.request(curl::HttpClient::Request::Get, baseDataIn, &dataOut);
	xTEST(bRv);
	if ( !_http.isSuccess(dataOut) ) {
		// Cout() << xTRACE_VAR(dataOut.body);

		*out_textToBrief  = Format::str(xT("Error: {}"), dataOut.responseCode);
		*out_textToDetail = Format::str(xT("Error: {}"), dataOut.responseCode);

		if (out_textToRaw != nullptr) {
			*out_textToRaw = Format::str(xT("Error: {}"), dataOut.responseCode);
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


/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
Translate::_langsDetect(
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

        // Cout() << "Langs: en-ru";
    }
    else if (isRu) {
        *out_langFrom = Translate::Language::Ru;
        *out_langTo   = Translate::Language::En;

        // Cout() << "Langs: ru-en";
    }
    else if (isMixed) {
        // Cout() << "Langs: mixed-mixed";

        cbool_t isPreferEn = (countEn >= countRu);
        cbool_t isPreferRu = (countRu >  countEn);

        if      (isPreferEn) {
            *out_langFrom = Translate::Language::En;
            *out_langTo   = Translate::Language::Ru;

            // Cout() << "Langs (prefer): en-ru";
        }
        else if (isPreferRu) {
            *out_langFrom = Translate::Language::Ru;
            *out_langTo   = Translate::Language::En;

            // Cout() << "Langs (prefer): ru-en";
        }
        else {
            xTEST(false);
        }
    }
    else if (isUnknown) {
        // TODO: defaults for isUnknown
        *out_langFrom = Translate::Language::Auto;
        *out_langTo   = Translate::Language::Auto;

        // Cout() << "Langs: unknown-unknown";
    }
    else {
        *out_langFrom = Translate::Language::Unknown;
        *out_langTo   = Translate::Language::Unknown;

        Cout() << xTRACE_VAR(countEn);
        Cout() << xTRACE_VAR(countRu);

        xTEST(false);
    }
}
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
	static const std::map<Translate::Language, std::tstring_t> langToCodes
	{
		{Language::Unknown, xT("")},
		{Language::Auto,    xT("auto")},
		{Language::En,      xT("en")},
		{Language::Ru,      xT("ru")}
	};

	auto it = langToCodes.find(a_lang);
	if (it == langToCodes.cend()) {
		return {};
	}

	return it->second;
}
//-------------------------------------------------------------------------------------------------

} // namespace
