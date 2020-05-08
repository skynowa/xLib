/**
 * \file  Pipe_unix.inl
 * \brief Pipe is a section of shared memory that processes use for communication
 */


xNAMESPACE_BEGIN2(xl, sync)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
Pipe::_create_impl()
{
	_handles.resize(2);

	int_t iRv = ::pipe(&_handles[0]);
    xTEST_EQ(iRv, 0);

    _handle = iRv;
}
//-------------------------------------------------------------------------------------------------
void_t
Pipe::_close_impl()
{
	int_t iRv {};

	iRv = ::close(_handles[FdIndex::Read]);
	xTEST_EQ(iRv, 0);

	iRv = ::close(_handles[FdIndex::Write]);
	xTEST_EQ(iRv, 0);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, sync)
