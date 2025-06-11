/**
 * \file   Iconv.cpp
 * \brief  Perform character set conversion
 *
 * $ iconv --list (list all known coded character sets)
 */


#include "Iconv.h"

#include <xLib/Core/Const.h>
#include <xLib/Core/Utils.h>
#include <xLib/Core/String.h>
#include <xLib/Core/Format.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/StackTrace.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Log/LogStream.h>
#include <xLib/Test/Test.h>

//-------------------------------------------------------------------------------------------------
namespace
{

const iconv_t iconvError { (iconv_t)-1 };

}
//-------------------------------------------------------------------------------------------------

namespace xl::package
{

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
Iconv::Iconv(
	std::ctstring_t &a_charsetIn,
	std::ctstring_t &a_charsetOut,
	std::csize_t     a_buffSize,       /* = 1024 */
	cbool_t          a_isSkipErrors,   /* = false */
	cbool_t          a_isForceEncoding /* = false */
) :
	_buffSize      (a_buffSize),
	_isSkipErrors  (a_isSkipErrors),
	_isSkipEncoding(!a_isForceEncoding && (a_charsetIn == a_charsetOut))
{
	xTEST(!a_charsetIn.empty());
	xTEST(!a_charsetOut.empty());
	xTEST_DIFF(a_buffSize, 0);
	xTEST_NA(a_isSkipErrors);
	xTEST_NA(a_isForceEncoding);

	xCHECK_MSG_DO(_isSkipEncoding, xT("Skip convert ") + a_charsetIn + xT(" -> ") + a_charsetOut,
		return);

	_iconv = ::iconv_open(a_charsetOut.c_str(), a_charsetIn.c_str());
	if (errno == EINVAL) {
		xTEST_FAIL_MSG(xT("Not supported convert ") + a_charsetIn + xT(" -> ") + a_charsetOut);
	}
	xTEST_DIFF(_iconv, ::iconvError);
}
//-------------------------------------------------------------------------------------------------
/* virtual */
Iconv::~Iconv()
{
    xCHECK_DO(_isSkipEncoding, return);

	Utils::freeT(_iconv, ::iconv_close, ::iconvError);
}
//-------------------------------------------------------------------------------------------------
bool_t
Iconv::convert(
	std::ctstring_t &a_input,	///< input string
	std::tstring_t  *a_output	///< [out] result
) const
{
	xTEST_PTR(_iconv);
	xTEST_PTR(a_output);

	if (_isSkipEncoding) {
		*a_output = a_input;
		return true;
	}

	a_output->clear();

	std::tstring_t sRV;

	std::vec_tchar_t buffIn(a_input.cbegin(), a_input.cend());

	tchar_t *srcPtr  = &buffIn[0];
	size_t   srcSize = a_input.size();

	std::vec_tchar_t buff(_buffSize);

	while (srcSize > 0) {
		tchar_t    *dstPtr  = &buff[0];
		std::size_t dstSize = buff.size();

		std::size_t uiRv = ::iconv(_iconv, &srcPtr, &srcSize, &dstPtr, &dstSize);
		if (uiRv == (size_t)-1) {
			if      (errno == E2BIG)  {
				// ignore this error
				LogCout() << xT("E2BIG - Argument list too long");
			}
			else if (_isSkipErrors) {
				// skip character
				++ srcPtr;
				-- srcSize;
			} else {
				_reportError();

				return false;
			}
		}

		sRV.append(&buff[0], buff.size() - dstSize);
	}

	sRV.swap(*a_output);

	return true;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
Iconv::_reportError() const
{
	switch (errno) {
	case EILSEQ:
		LogCout() << xT("EILSEQ - Illegal byte sequence");
		break;
	case EINVAL:
		LogCout() << xT("EINVAL - Invalid argument");
		break;
	default:
		LogCout() << xT("Unknown error");
		break;
	}
}
//-------------------------------------------------------------------------------------------------

} // namespace
