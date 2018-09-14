/**
 * \file  Buffer.h
 * \brief CURL client
 *
 * https://www.codesynthesis.com/~boris/data/buffer/buffer-1.0.0/
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN3(xl, package, curl)

class Buffer
	/// buffer
{
public:
	            Buffer();
	           ~Buffer();

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

	xNO_COPY_ASSIGN(Buffer);
};

xNAMESPACE_END3(xl, package, curl)
//-------------------------------------------------------------------------------------------------
