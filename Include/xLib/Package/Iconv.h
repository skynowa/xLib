/**
 * \file   Iconv.h
 * \brief  Perform character set conversion
 */


#pragma once

#include <xLib/Core/Core.h>

#include <iconv.h>
//-------------------------------------------------------------------------------------------------
namespace xl::package
{

class Iconv
    /// Perform character set conversion
{
public:
///@name ctors, dtor
///@{
			 Iconv(std::ctstring_t &charsetIn, std::ctstring_t &charsetOut,
				std::csize_t buffSize = 1024, cbool_t isSkipErrors = false,
				cbool_t isForceEncoding = false);
	virtual ~Iconv();

    xNO_DEFAULT_CONSTRUCT(Iconv);
    xNO_COPY_ASSIGN(Iconv)
///@}

    void convert(std::ctstring_t &input, std::tstring_t *output) const;
    	///< convert string

private:
	std::csize_t _buffSize {};
	cbool_t      _isSkipErrors {};
    cbool_t      _isSkipEncoding {};

	iconv_t      _iconv {};

	void_t _checkError() const;
};

} // namespace
//-------------------------------------------------------------------------------------------------
