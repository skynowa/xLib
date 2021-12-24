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
namespace xl::package
{

class Translate :
	public IRestClient
    /// Translate text (by Google API, mobile version)
{
public:
///\name ctors, dtor
///\{
			 Translate() = default;
	virtual ~Translate() = default;

	xNO_COPY_ASSIGN(Translate)
///\}

    void_t execute(std::ctstring_t &textFrom, std::tstring_t *textToBrief,
				std::tstring_t *textToDetail, std::tstring_t *textToRaw,
				std::tstring_t *langFrom, std::tstring_t *langTo);
        ///< translate text

private:
    enum class Language
        ///< detected language
    {
        Unknown = 0,
        Auto    = 1,	// TODO: Auto
        En      = 2,
        Ru      = 3
    };
    xUSING_CONST(Language);

    void_t         _langsDetect(std::ctstring_t &text, Language *langFrom, Language *langTo) const;
        ///< detect languages
    void_t         _responseParse(const curl::DataOut &dataOut, std::tstring_t *textToBrief,
						std::tstring_t *textToDetail, std::tstring_t *textToRaw) const;
        ///< parse response
    std::tstring_t _langCode(cLanguage lang) const;
        ///< converter
};

} // namespace
//-------------------------------------------------------------------------------------------------
