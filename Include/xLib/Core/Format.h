/**
 * \file   Format.h
 * \brief  format string
 */


#pragma once

//-------------------------------------------------------------------------------------------------
#include <xLib/Core/Core.h>
#include <xLib/Core/OStream.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, core)

template<typename StreamT>
class FormatT
    ///< format string
{
public:
    template<typename ...ArgsT>
    static
    std::tstring_t str(std::ctstring_view_t fmt, const ArgsT &...args);

    xNO_DEFAULT_CONSTRUCT(FormatT)
    xNO_COPY_ASSIGN(FormatT)

private:
	static constexpr bool_t              _isTest {true};		///< test formatted string
    static constexpr std::tstring_view_t _specifier {xT("{}")};	///<
        ///< specifier
	template<typename T>
	static
	void_t _format(std::ctstring_view_t fmt, const T &arg, std::tstring_t &rv,
				std::size_t &specifiersFound, std::size_t &posPrev);
		///< format argument
	static
	bool_t _testFmt(std::ctstring_view_t fmt, std::csize_t argsSize, std::csize_t specifiersFound);
		///< test formated string
};

using FormatStd = FormatT<std::tstringstream_t>;
using Format    = FormatT<xl::core::OStream>;

xNAMESPACE_END2(xl, core)
//-------------------------------------------------------------------------------------------------
#include "Format.inl"
