/**
 * \file   Format.inl
 * \brief  format string
 */


#include <xLib/Test/Test.h>
#include <xLib/Debug/Debug.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/StdError.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Debug/StackTrace.h>
#include <xLib/Core/OStream.h>


xNAMESPACE_BEGIN2(xl, core)

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
	std::ctstring_view_t  a_fmt,
	const ArgsT          &...a_args
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
};
//-------------------------------------------------------------------------------------------------
template<typename StreamT>
/* static */
inline bool_t
FormatT<StreamT>::_testFmt(
	std::ctstring_view_t a_fmt,
	std::csize_t         a_argsSize,
	std::csize_t         a_specifiersFound
)
{
	std::size_t specifierOpen  {};
	std::size_t specifierClose {};
	{
		for (auto &it_fmt : a_fmt) {
			switch (it_fmt) {
			case _specifier[0]:
				++ specifierOpen;
				break;
			case _specifier[1]:
				++ specifierClose;
				break;
			default:
				break;
			}
		} // for (a_fmt)
	}

	if (specifierOpen != specifierClose) {
		xTEST_MSG(false, xT("specifierOpen != specifierClose"));
		return false;
	}

	if (specifierOpen < a_argsSize) {
		xTEST_MSG(false, xT("specifierOpen < a_argsSize"));
		return false;
	}

	if (specifierOpen > a_argsSize) {
		xTEST_MSG(false, xT("specifierOpen > a_argsSize"));
		return false;
	}

	if (a_argsSize != a_specifiersFound) {
		xTEST_MSG(false, xT("a_argsSize != a_specifiersFound"));
		return false;
	}

	return true;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, core)
