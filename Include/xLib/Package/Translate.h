/**
 * \file  Translate.h
 * \brief Translate text
 *
 * https://bitbucket.org/skynowa/iteacher/src/master/Classes/GoogleTranslator.h
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Package/IRestClient.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, package)

class Translate :
	public IRestClient
    ///< Translate text
{
public:
             Translate();
        ///< constructor
    virtual ~Translate() = default;
        ///< destructor

    enum class Language
        ///< detected language
    {
        Unknown,
        En,
        Ru
    };

    void languagesDetect(std::ctstring_t &text, Language *langFrom, Language *langTo,
    		std::tstring_t *langCodeFrom, std::tstring_t *langCodeTo) const;
        ///< detect languages
    void execute(std::ctstring_t &textFrom, std::ctstring_t &langFrom, std::ctstring_t &langTo,
    		std::tstring_t *textToBrief, std::tstring_t *textToDetail, std::tstring_t *textToRaw) const;
        ///< translate text by Google API

private:
    void _responseParse(QNetworkReply *reply, std::tstring_t *textToBrief,
    		std::tstring_t *textToDetail, std::tstring_t *textToRaw) const;
        ///< parse response

private:
    xNO_COPY_ASSIGN(Translate)
};

xNAMESPACE_END2(xl, package)
//-------------------------------------------------------------------------------------------------
