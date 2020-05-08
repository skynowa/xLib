/**
 * \file  Pipe_unix.inl
 * \brief Pipe is a section of shared memory that processes use for communication
 */


xNAMESPACE_BEGIN2(xl, sync)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

enum FdIndex : std::size_t
{
	Read  = 0,
	Write = 1
};

int _handles[2] {};

//-------------------------------------------------------------------------------------------------
void_t
Pipe::_construct_impl()
{
}
//-------------------------------------------------------------------------------------------------
void_t
Pipe::_destruct_impl()
{
	::close(_handles[FdIndex::Read]);
	::close(_handles[FdIndex::Write]);
}
//-------------------------------------------------------------------------------------------------
void_t
Pipe::_create_impl()
{
	int_t iRv = ::pipe(_handles);
    xTEST_EQ(iRv, 0);

    _handle = iRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, sync)
