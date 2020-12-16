/**
 * \file  Base64.h
 * \brief base64
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::crypt
{

class Base64
    /// Base64
{
public:
///@name ctors, dtor
///@{
			 Base64() = default;
	virtual ~Base64() = default;

	xNO_COPY_ASSIGN(Base64)
///@}

    std::string encode(cuchar_t *bytes, std::csize_t &size);
        ///< encoding
    std::string encode(std::cstring_t &str);
        ///< encoding
    std::string decode(std::cstring_t &str);
        ///< decoding
private:
    bool_t _isValid(cuchar_t &ch);
        ///< check char for validness
};

} // namespace
//-------------------------------------------------------------------------------------------------
/**
 * TODO: OpenSsl - https://gist.github.com/kvelakur/a3ac17ebf5614547ded9
 */
//-------------------------------------------------------------------------------------------------
