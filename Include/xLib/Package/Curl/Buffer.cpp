/**
 * \file  Buffer.cpp
 * \brief CURL client
 */


#include "Buffer.h"

#include <xLib/Core/Utils.h>


xNAMESPACE_BEGIN3(xl, package, curl)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
Buffer::~Buffer()
{
	clear();
}
//-------------------------------------------------------------------------------------------------
bool
Buffer::isEmpty() const
{
	return (_buff == nullptr || _size == 0);
}
//-------------------------------------------------------------------------------------------------
std::string
Buffer::buffer() const
{
	return {_buff, _size};
}
//-------------------------------------------------------------------------------------------------
std::size_t
Buffer::size() const
{
	return _size;
}
//-------------------------------------------------------------------------------------------------
size_t
Buffer::get(
	char         *a_buff,
	const size_t  a_buffSize
) const
{
	if (_read_pos < _size) {
		const size_t size = (_size - _read_pos < a_buffSize) ? (_size - _read_pos) : a_buffSize;
		::memcpy(a_buff, _buff + _read_pos, size);
		_read_pos += size;

		return size;
	}

	return 0;
}
//-------------------------------------------------------------------------------------------------
void
Buffer::set(
	const char   *a_buff,
	const size_t  a_buffSize
)
{
#if 0
	_buff = static_cast<char *>( ::realloc(_buff, _size + a_buffSize + 1) );
	if (_buff == nullptr) {
		return;
	}

	::memcpy(_buff + _size, a_buff, a_buffSize);
	_size       += a_buffSize;
	_buff[_size] = '\0';
#else
	// test
	void *tmp = _buff;
	_buff=(char*)realloc(_buff, _size + a_buffSize + 1);
	if (_buff)
	{
		memcpy(_buff + _size, a_buff, a_buffSize);
		_size += a_buffSize;
		_buff[_size] = 0;
	}
	else
	{
		if ( tmp != nullptr )
		{
			free(tmp);
		}
	}
#endif
}
//-------------------------------------------------------------------------------------------------
void
Buffer::clear()
{
	if ( isEmpty() ) {
		return;
	}

	Utils::bufferFreeT(_buff);
	_size = 0;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END3(xl, package, curl)
