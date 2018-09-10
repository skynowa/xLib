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

	void        add(const char *buff, const size_t buffSize);

	size_t      get(char *buff, const size_t buffSize) const;

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
	CurlBuffer header_in;
	CurlBuffer header_out;
	CurlBuffer data_all;
};

xNAMESPACE_END2(xl, package)
//-------------------------------------------------------------------------------------------------
