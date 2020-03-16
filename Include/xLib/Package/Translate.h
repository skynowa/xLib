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
    /// Translate text (by Google API)
{
public:
             Translate();
        ///< constructor
    virtual ~Translate() = default;
        ///< destructor

    enum class Language
        ///< detected language
    {
        Unknown = 0,
        Auto    = 1,	// TODO: Auto
        En      = 2,
        Ru      = 3
    };
    xUSING_CONST(Language);

    void_t languagesDetect(std::ctstring_t &text, Language *langFrom, Language *langTo) const;
        ///< detect languages
    void_t execute(std::ctstring_t &textFrom, cLanguage langFrom, cLanguage langTo,
				std::tstring_t *textToBrief, std::tstring_t *textToDetail,
				std::tstring_t *textToRaw) const;
        ///< translate text

private:
    void_t _responseParse(const curl::DataOut &dataOut, std::tstring_t *textToBrief,
    			std::tstring_t *textToDetail, std::tstring_t *textToRaw) const;
        ///< parse response
    std::tstring_t _languageCode(cLanguage lang) const;
        ///< converter

    xNO_COPY_ASSIGN(Translate)
};

xNAMESPACE_END2(xl, package)
//-------------------------------------------------------------------------------------------------
