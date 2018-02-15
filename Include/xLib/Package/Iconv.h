/**
 * \file   Iconv.h
 * \brief  Perform character set conversion
 */


#pragma once

#include <xLib/Core/Core.h>

#include <iconv.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, package)

class Iconv
    ///< Perform character set conversion
{
public:
             Iconv(std::ctstring_t &charsetIn, std::ctstring_t &charsetOut,
                 std::csize_t buffSize = 1024, cbool_t ignoreErrors = false);
        ///< constructor
    virtual ~Iconv();
        ///< destructor

    void     convert(std::ctstring_t &input, std::tstring_t *output) const;
    	///< convert string

private:
    xNO_COPY_ASSIGN(Iconv)

	std::csize_t _buffSize {};
	cbool_t  _ignoreErrors {};

	iconv_t  _iconv {};

	void     _checkError() const;
};

xNAMESPACE_END2(xl, package)
//-------------------------------------------------------------------------------------------------
