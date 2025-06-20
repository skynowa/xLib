/**
 * \file   Format.inl
 * \brief  format string
 */


#include <xLib/Test/Test.h>
#include <xLib/Debug/Debug.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/SourceInfo.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Debug/StackTrace.h>
#include <xLib/Core/OStream.h>


namespace xl::core
{

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename StreamT>
template<typename ...ArgsT>
/* static */
inline std::tstring_t
FormatT<StreamT>::str(
	std::ctstring_view_t  a_fmt,		///< format string
	const ArgsT          &...a_args		///< argument
)
{
	constexpr std::size_t argsSize {sizeof...(ArgsT)};
	if constexpr (argsSize == 0) {
		return {a_fmt.cbegin(), a_fmt.cend()};
	}

	std::tstring_t sRv;
	std::size_t    specifiersFound {};
	std::size_t    posPrev {};

	// for each args
	(_format(a_fmt, a_args, sRv, specifiersFound, posPrev), ...);

	sRv += a_fmt.substr(posPrev, a_fmt.size() - posPrev);

	if (_isTest) {
		_testFmt(a_fmt, argsSize, specifiersFound);
	}

	return sRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename StreamT>
template<typename T>
/* static */
inline void_t
FormatT<StreamT>::_format(
	std::ctstring_view_t  a_fmt,				///< format string
	const T              &a_arg,				///< argument
	std::tstring_t       &out_rv,				///< [in,out]
	std::size_t          &out_specifiersFound,	///< [in,out]
	std::size_t          &out_posPrev			///< [in,out]
)
{
	std::csize_t pos = a_fmt.find(_specifier, out_posPrev);
	if (pos == std::tstring_t::npos) {
		return;
	}

	static StreamT ss;
	{
		static std::ctstring_t emptyString;
		ss.str( emptyString );
		ss.clear();

		ss << a_arg;
	}

	// [out]
	{
		out_rv += a_fmt.substr(out_posPrev, pos - out_posPrev);
		out_rv += ss.str();

		++ out_specifiersFound;

		out_posPrev = pos + _specifier.size();
	}
}
//-------------------------------------------------------------------------------------------------
template<typename StreamT>
/* static */
inline bool_t
FormatT<StreamT>::_testFmt(
	std::ctstring_view_t a_fmt,				///< format string
	std::csize_t         a_argsSize,		///< arguments size
	std::csize_t         a_specifiersFound	///< number of found specifiers
)
{
	static_assert(_specifier.size() == 2, xT("Bad _specifier"));

	std::size_t specifierOpenNum  {};
	std::size_t specifierCloseNum {};
	{
		constexpr auto specifierOpen  = _specifier[0];
		constexpr auto specifierClose = _specifier[1];

		for (const auto it_fmt : a_fmt) {
			switch (it_fmt) {
			case specifierOpen:
				++ specifierOpenNum;
				break;
			case specifierClose:
				++ specifierCloseNum;
				break;
			default:
				xNA;
				break;
			}
		} // for (a_fmt)
	}

#ifndef xTEST_FAIL_MSG
    #error "xTEST_FAIL_MSG is not defined"
	// #define xTEST_FAIL_MSG(msg) do { std::cerr << msg << std::endl; } while (0)
#endif

	if (specifierOpenNum != specifierCloseNum) {
		xTEST_FAIL_MSG(xT("specifierOpenNum != specifierCloseNum"));
		return false;
	}

	if (specifierOpenNum < a_argsSize) {
		xTEST_FAIL_MSG(xT("specifierOpenNum < a_argsSize"));
		return false;
	}

	if (specifierOpenNum > a_argsSize) {
		xTEST_FAIL_MSG(xT("specifierOpenNum > a_argsSize"));
		return false;
	}

	if (a_argsSize != a_specifiersFound) {
		xTEST_FAIL_MSG(xT("a_argsSize != a_specifiersFound"));
		return false;
	}

	return true;
}
//-------------------------------------------------------------------------------------------------

} // namespace
