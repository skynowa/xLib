/**
 * \file  CurlBuffer.h
 * \brief CURL client
 */


#pragma once

#include <xLib/Core/Core.h>
#include "CurlBuffer.h"
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, package)

class CurlBuffer
{
public:
	            CurlBuffer() = default;
	           ~CurlBuffer() = default;

	bool        isEmpty() const;

	std::string buffer() const;

	std::size_t size() const;

	void        add(const char *a_buffer, const size_t a_buflen);

	size_t      get(char *a_buffer, const size_t a_buflen) const;

	void        clear();

private:
	char          *_buff {};
	size_t         _size {};
	mutable size_t _read_pos {};

	xNO_COPY_ASSIGN(CurlBuffer);
};

xNAMESPACE_END2(xl, package)
//-------------------------------------------------------------------------------------------------
