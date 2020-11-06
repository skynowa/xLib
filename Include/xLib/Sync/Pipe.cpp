/**
 * \file  Pipe.cpp
 * \brief Pipe is a section of shared memory that processes use for communication
 */


#include "Pipe.h"

#if   xENV_WIN
    #include "Platform/Win/Pipe_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/Pipe_unix.inl"
#endif


namespace xl::sync
{

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
Pipe::Pipe()
{
}
//-------------------------------------------------------------------------------------------------
Pipe::~Pipe()
{
	close();
}
//-------------------------------------------------------------------------------------------------
cHandleNative &
Pipe::handle() const
{
    return _handle;
}
//-------------------------------------------------------------------------------------------------
cint_t &
Pipe::handleRead() const
{
    return _handles[FdIndex::Read];
}
//-------------------------------------------------------------------------------------------------
cint_t &
Pipe::handleWrite() const
{
    return _handles[FdIndex::Write];
}
//-------------------------------------------------------------------------------------------------
void_t
Pipe::create()
{
    _create_impl();
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Pipe::readAll() const
{
	std::tstring_t sRv;

	constexpr std::size_t buffSize {1024 * 10};

	for (ssize_t readSize = 1; readSize > 0; ) {
		// Cout() << "ParentOk - Start read: " << a_pipeRead;

		char buff[buffSize + 1] {};
		readSize = _read_impl(handleRead(), buff, buffSize);

		// Cout() << "ParentOk - Stop read, " << xTRACE_VAR(readSize);

		if (readSize == - 1L) {
			xTEST_FAIL;
			break;
		}

		// [out]
		sRv.append(buff, readSize);
	} // for

	return sRv;
}
//-------------------------------------------------------------------------------------------------
void_t
Pipe::close()
{
    _close_impl(CloseMode::All);
}
//-------------------------------------------------------------------------------------------------
void_t
Pipe::closeRead()
{
    _close_impl(CloseMode::Read);
}
//-------------------------------------------------------------------------------------------------
void_t
Pipe::closeWrite()
{
    _close_impl(CloseMode::Write);
}
//-------------------------------------------------------------------------------------------------

} // namespace
