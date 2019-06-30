/**
 * \file  Translate.cpp
 * \brief Translate text
 */


#include "Translate.h"

//-------------------------------------------------------------------------------------------------
namespace
{

std::ctstring_t langEn = "en";
std::ctstring_t langRu = "ru";

}
//-------------------------------------------------------------------------------------------------

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
void
Translate::languagesDetect(
    std::ctstring_t                   &a_text,
    Translate::Language *a_langFrom,
    Translate::Language *a_langTo,
    std::tstring_t                    *a_langCodeFrom,
    std::tstring_t                    *a_langCodeTo
) const
{
    xTEST(!a_text.empty());
    xTEST(a_langFrom     != nullptr);
    xTEST(a_langTo       != nullptr);
    xTEST(a_langCodeFrom != nullptr);
    xTEST(a_langCodeTo   != nullptr);

    std::ctstring_t lettersEn = std::tstring_t::fromUtf8("abcdefghijklmnopqrstuvwxyz");
    std::ctstring_t lettersRu = std::tstring_t::fromUtf8("абвгдеёжзийклмнопрстуфхцчшщъыьэюя");

    uint     countEn = 0;
    uint     countRu = 0;

    for (int i = 0; i < a_text.size(); ++ i) {
        cQChar letter = a_text.at(i).toLower();
        xCHECK_DO(!letter.isLetter(), continue);

        xCHECK_DO(lettersEn.contains(letter), ++ countEn);
        xCHECK_DO(lettersRu.contains(letter), ++ countRu);
    }

    cbool_t isEn      = (countEn != 0 && countRu == 0);
    cbool_t isRu      = (countEn == 0 && countRu != 0);
    cbool_t isMixed   = (countEn != 0 && countRu != 0);
    cbool_t isUnknown = (countEn == 0 && countRu == 0);

    if      (isEn) {
        *a_langFrom     = Translate::Language::En;
        *a_langTo       = Translate::Language::Ru;

        *a_langCodeFrom = ::langEn;
        *a_langCodeTo   = ::langRu;

        Trace() << "Langs: en-ru\n";
    }
    else if (isRu) {
        *a_langFrom     = Translate::Language::Ru;
        *a_langTo       = Translate::Language::En;

        *a_langCodeFrom = ::langRu;
        *a_langCodeTo   = ::langEn;

        Trace() << "Langs: ru-en\n";
    }
    else if (isMixed) {
        Trace() << "Langs: mixed-mixed\n";

        cbool_t isPreferEn = (countEn >= countRu);
        cbool_t isPreferRu = (countRu >  countEn);

        if      (isPreferEn) {
            *a_langFrom     = Translate::Language::En;
            *a_langTo       = Translate::Language::Ru;

            *a_langCodeFrom = ::langEn;
            *a_langCodeTo   = ::langRu;

            Trace() << "Langs (prefer): en-ru\n";
        }
        else if (isPreferRu) {
            *a_langFrom     = Translate::Language::Ru;
            *a_langTo       = Translate::Language::En;

            *a_langCodeFrom = ::langRu;
            *a_langCodeTo   = ::langEn;

            Trace() << "Langs (prefer): ru-en\n";
        }
        else {
            xTEST(false);
        }
    }
    else if (isUnknown) {
        *a_langFrom     = Translate::Language::Unknown;
        *a_langTo       = Translate::Language::Unknown;

        *a_langCodeFrom = "";
        *a_langCodeTo   = "";

        Trace() << "Langs: unknown-unknown\n";
    }
    else {
        *a_langFrom     = Translate::Language::Unknown;
        *a_langTo       = Translate::Language::Unknown;

        *a_langCodeFrom = "";
        *a_langCodeTo   = "";

        Trace() << xTRACE_VAR(countEn);
        Trace() << xTRACE_VAR(countRu);

        xTEST(false);
    }
}
//-------------------------------------------------------------------------------------------------
void
Translate::execute(
    std::ctstring_t         &a_textFrom,       ///< source text
    std::ctstring_t         &a_langFrom,       ///< source text language
    std::ctstring_t         &a_langTo,         ///< target text language
    std::tstring_t          *a_textToBrief,    ///< [out] target brief translate
    std::tstring_t          *a_textToDetail,   ///< [out] target detail translate
    std::tstring_t          *a_textToRaw       ///< [out] target raw translate (HTML) (maybe nullptr)
) const
{
    xTEST(!a_textFrom.empty());
    xTEST(!a_langFrom.empty());
    xTEST(!a_langTo.empty());
    xTEST(a_textToBrief  != nullptr);
    xTEST(a_textToDetail != nullptr);
    xTEST_NA(a_textToRaw);

    std::ctstring_t              host  = std::tstring_t("https://translate.google.com");
    QNetworkAccessManager manager;
    QNetworkRequest       request;
    QNetworkReply        *reply = nullptr;

    // request
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
		*     <input type="text" name="q" style="width:65%" maxlength="2048" value=""/><br>
		*     <input type="submit" value="Перевести"/>
		* </form>
		*/

		cQUrl url = std::tstring_t("%1/m").arg(host);
		url.toEncoded();

		QUrlQuery query;
		query.addQueryItem("h1", a_langFrom);
		query.addQueryItem("tl", a_langTo);
		query.addQueryItem("ie", "UTF-8");
		query.addQueryItem("q",  a_textFrom);

		request.setUrl(url);
		request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

		reply = manager.post(request, query.toString(QUrl::FullyEncoded).toUtf8());
		xTEST_PTR(reply);
     }

     _responseParse(reply, a_textToBrief, a_textToDetail, a_textToRaw);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void
Translate::_responseParse(
    QNetworkReply *a_reply,
    std::tstring_t       *a_textToBrief,
    std::tstring_t       *a_textToDetail,
    std::tstring_t       *a_textToRaw
) const
{
    std::tstring_t textToBrief;
    std::tstring_t textToDetail;
    std::tstring_t textToRaw;

    std::tstring_t response;
    bool    isDictionaryText = false;
    {
    #if 0
        cQVariant httpStatusCode = a_reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
        if ( !httpStatusCode.isValid() ) {
            Trace() << xTRACE_VAR(httpStatusCode);
            return;
        }

        int status = httpStatusCode.toInt();
        if (status != 200) {
            std::ctstring_t reason = a_reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
            Trace() << xTRACE_VAR(reason);
        }
    #endif

        if (a_reply->error() != QNetworkReply::NoError) {
            *a_textToBrief  = a_reply->errorString();
            *a_textToDetail = a_reply->errorString();

            if (a_textToRaw != nullptr) {
                *a_textToRaw = a_reply->errorString();
            }

            return;
        }

        for ( ; ; ) {
            QCoreApplication::processEvents(QEventLoop::ExcludeUserInputEvents);

            xCHECK_DO(a_reply->isFinished(), break);
        }

        response = std::tstring_t::fromUtf8(a_reply->readAll());
        xTEST(!response.empty());

        textToRaw        = response;
        isDictionaryText = response.contains("Dictionary:");

        // Trace() << xTRACE_VAR(response);
    }

    // proccess response

    {
        response.replace("Dictionary:", "\n");
        response.replace("<br>", "\n");
    }

    // parse response
    {
        QDomDocument document;
        document.setContent(response);

        QDomNodeList docList = document.elementsByTagName("div");
        xTEST(docList.count() >= 3);

        // out - textToBrief
        textToBrief = docList.at(2).toElement().text();
        xTEST(!textToBrief.empty());

        // out - textToDetail
        if (isDictionaryText) {
            textToDetail = docList.at(5).toElement().text();
            xTEST(!textToDetail.empty());
        } else {
            textToDetail = xT("n/a");
        }
    }

    // out
    {
        a_textToBrief->swap(textToBrief);
        a_textToDetail->swap(textToDetail);

        if (a_textToRaw != nullptr) {
            a_textToRaw->swap(textToRaw);
        }

        // Trace() << xTRACE_VAR(*a_textToBrief);
        // Trace() << xTRACE_VAR(*a_textToDetail);
        // Trace() << xTRACE_VAR(*a_textToRaw);
    }
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, package)
