/**
 * \file  CurlBuffer.cpp
 * \brief CURL client
 */


#include "CurlBuffer.h"


xNAMESPACE_BEGIN2(xl, package)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
bool
CurlBuffer::isEmpty() const
{
	return (_buff == nullptr || _size == 0);
}
//-------------------------------------------------------------------------------------------------
std::string
CurlBuffer::buffer() const
{
	return {_buff, _size};
}
//-------------------------------------------------------------------------------------------------
std::size_t
CurlBuffer::size() const
{
	return _size;
}
//-------------------------------------------------------------------------------------------------
void
CurlBuffer::add(
	const char   *a_buffer,
	const size_t  a_buflen
)
{
	_buff = (char *)::realloc(_buff, _size + a_buflen + 1);
	if (_buff) {
		::memcpy(_buff + _size, a_buffer, a_buflen);
		_size       += a_buflen;
		_buff[_size] = 0;
	}
}
//-------------------------------------------------------------------------------------------------
size_t
CurlBuffer::get(
	char         *a_buffer,
	const size_t  a_buflen
) const
{
	if (_read_pos < _size) {
		size_t len = ( _size - _read_pos < a_buflen ) ? (_size - _read_pos) : a_buflen;
		::memcpy(a_buffer, _buff + _read_pos, len);
		_read_pos += len;

		return len;
	}

	return 0;
}
//-------------------------------------------------------------------------------------------------
void
CurlBuffer::clear()
{
	if (_buff && _size) {
		::free(_buff);

		_buff = nullptr;
		_size = 0;
	}
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, package)
