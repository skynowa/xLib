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
	std::ctstring_t  &fmt,
	const ArgsT      &...args
)
{
	constexpr std::size_t argsSize  {sizeof...(ArgsT)};
	std::ctstring_t       specifier {"{}"};

	auto func = [&] (
		const std::tstring_t &a_fmt,		///<
		auto                    a_arg,		///<
		std::tstring_t         *out_rv,		///< [out]
		std::size_t            &out_index,	///< [out]
		std::size_t            &out_posPrev	///< [out]
	) -> void
	{
		std::csize_t pos = a_fmt.find(specifier, out_posPrev);
		if (pos == std::tstring_t::npos) {
			return;
		}

		++ out_index;

		static StreamT ss;
		{
			static const std::tstring_t emptyString;
			ss.str( emptyString );
			ss.clear();

			ss << a_arg;
		}

		// [out]
		*out_rv += a_fmt.substr(out_posPrev, pos - out_posPrev);
		*out_rv += ss.str();

		out_posPrev = pos + specifier.size();
	};

	std::tstring_t sRv;
	std::size_t    index   {};
	std::size_t    posPrev {};

    ( func(fmt, args, &sRv, index, posPrev), ...);

	xTEST_EQ_MSG(argsSize, index, xT("Invalid params"));

	return sRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, core)
