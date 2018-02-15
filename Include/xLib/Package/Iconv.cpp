/**
 * \file   Iconv.cpp
 * \brief  Perform character set conversion
 */


#include "Iconv.h"

#include <xLib/Core/Const.h>
#include <xLib/Core/Utils.h>
#include <xLib/Core/String.h>
#include <xLib/Core/Format.h>
#include <xLib/Log/Trace.h>
#include <xLib/Log/FileLog.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Test/Test.h>

//-------------------------------------------------------------------------------------------------
namespace
{

const iconv_t iconvError = (iconv_t)-1;

}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_BEGIN2(xl, package)

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
	xTEST_EQ(a_charsetIn.empty(), false);
	xTEST_EQ(a_charsetOut.empty(), false);
	xTEST_DIFF(a_buffSize, (std::size_t)0);
	xTEST_NA(a_isSkipErrors);
	xTEST_NA(a_isForceEncoding);

	xCHECK_MSG_DO(_isSkipEncoding, "Skip convert " + a_charsetIn + " -> " + a_charsetOut, return);

	_iconv = ::iconv_open(a_charsetOut.c_str(), a_charsetIn.c_str());
	if (errno == EINVAL) {
		xTEST_FAIL_MSG("Not supported convert " + a_charsetIn + " -> " + a_charsetOut);
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
void
Iconv::convert(
	std::ctstring_t &a_input,	///<
	std::tstring_t  *a_output	///< [out]
) const
{
	xTEST_PTR(a_output);

	xCHECK_DO(_isSkipEncoding, *a_output = a_input; return);

	a_output->clear();

	std::tstring_t sRV;

	// copy the string to a buffer as iconv function requires a non-const char pointer
	std::vec_tchar_t buffIn(a_input.begin(), a_input.end());

	tchar_t *srcPtr  = &buffIn[0];
	size_t   srcSize = a_input.size();

	std::vec_tchar_t buff(_buffSize);

	while (0 < srcSize) {
		tchar_t    *dstPtr  = &buff[0];
		std::size_t dstSize = buff.size();

		std::size_t uiRv = ::iconv(_iconv, &srcPtr, &srcSize, &dstPtr, &dstSize);
		if (uiRv == (size_t)-1) {
			if      (errno == E2BIG)  {
				// ignore this error
			}
			else if (_isSkipErrors) {
				// skip character
				++ srcPtr;
				-- srcSize;
			} else {
				_checkError();
			}
		}

		sRV.append(&buff[0], buff.size() - dstSize);
	}

	sRV.swap(*a_output);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void
Iconv::_checkError() const
{
	switch (errno) {
	case EILSEQ:
		throw std::runtime_error("EILSEQ - Illegal byte sequence");
		break;
	case EINVAL:
		throw std::runtime_error("EINVAL - Invalid argument");
		break;
	default:
		throw std::runtime_error("Unknown error");
		break;
	}
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, package)
