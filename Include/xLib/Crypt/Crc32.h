/**
 * \file  Crc32.h
 * \brief Crc32
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::crypt
{

class Crc32
    /// Crc32
{
public:
///\name ctors, dtor
///\{
			 Crc32() = default;
	virtual ~Crc32() = default;

	xNO_COPY_ASSIGN(Crc32)
///\}

    ulong_t        calc(uchar_t *buff, culong_t buffSize);
        ///< calculate
    ulong_t        calcFile(std::ctstring_t &filePath);
        ///< calculate

    std::tstring_t formatHex() const;
        ///< format Crc32 like "0AADDEA0"

private:
    ulong_t _crc32 {};
};

} // namespace
//-------------------------------------------------------------------------------------------------
