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
	std::ctstring_t  &a_fmt,
	const ArgsT      &...a_args
)
{
	constexpr std::size_t argsSize {sizeof...(ArgsT)};

	std::tstring_t sRv;
	std::size_t    specifiersFound {};
	std::size_t    posPrev {};

	// for each args
	(_format(a_fmt, a_args, sRv, specifiersFound, posPrev), ...);

	sRv += a_fmt.substr(posPrev, a_fmt.size() - posPrev);

	xTEST_EQ_MSG(argsSize, specifiersFound, xT("Invalid params"));

	return sRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename StreamT>
/* static */
inline std::ctstring_t &
FormatT<StreamT>::_specifier()
{
    static std::ctstring_t sRv(xT("{}"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
template<typename StreamT>
template<typename T>
/* static */
inline void_t
FormatT<StreamT>::_format(
	std::ctstring_t &a_fmt,					///<
	const T         &a_arg,					///<
	std::tstring_t  &out_rv,				///< [out]
	std::size_t     &out_specifiersFound,	///< [out]
	std::size_t     &out_posPrev			///< [out]
)
{
	std::ctstring_t specifier {"{}"};

	std::csize_t pos = a_fmt.find(specifier, out_posPrev);
	if (pos == std::tstring_t::npos) {
		return;
	}

	++ out_specifiersFound;

	static StreamT ss;
	{
		static std::ctstring_t emptyString;
		ss.str( emptyString );
		ss.clear();

		ss << a_arg;
	}

	// [out]
	out_rv += a_fmt.substr(out_posPrev, pos - out_posPrev);
	out_rv += ss.str();

	out_posPrev = pos + specifier.size();
};
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, core)
