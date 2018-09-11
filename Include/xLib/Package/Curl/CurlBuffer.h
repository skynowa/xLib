/**
 * \file  CurlBuffer.h
 * \brief CURL client
 *
 * https://www.codesynthesis.com/~boris/data/buffer/buffer-1.0.0/
 */


#pragma once

#include <xLib/Core/Core.h>
#include "CurlBuffer.h"
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, package)

class CurlBuffer
	/// buffer
{
public:
	            CurlBuffer();
	           ~CurlBuffer();

	bool        isEmpty() const;
	std::string buffer() const;
	std::size_t size() const;
	size_t      get(char *buff, const size_t buffSize) const;
	void        set(const char *buff, const size_t buffSize);
	void        clear();

private:
	char          *_buff {};
	size_t         _size {};
	mutable size_t _read_pos {};

	xNO_COPY_ASSIGN(CurlBuffer);
};

struct DebugData
	/// debug data
{
	CurlBuffer text;
	CurlBuffer header_in;
	CurlBuffer header_out;
	CurlBuffer data_in;
	CurlBuffer data_out;
	CurlBuffer ssl_data_in;
	CurlBuffer ssl_data_out;
};

xNAMESPACE_END2(xl, package)
//-------------------------------------------------------------------------------------------------
