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
Pipe::_close_impl(
	cCloseMode a_mode
)
{
	int_t iRv {};

	switch (a_mode) {
	case CloseMode::Read:
		if (auto &h = _handles[FdIndex::Read]; h != 0) {
			iRv = ::close(h);	h = 0;
			xTEST_EQ(iRv, 0);
		}
		break;
	case CloseMode::Write:
		if (auto &h = _handles[FdIndex::Write]; h != 0) {
			iRv = ::close(h);	h = 0;
			xTEST_EQ(iRv, 0);
		}
		break;
	case CloseMode::All:
		if (auto &h = _handles[FdIndex::Read]; h != 0) {
			iRv = ::close(h);	h = 0;
			xTEST_EQ(iRv, 0);
		}

		if (auto &h = _handles[FdIndex::Write]; h != 0) {
			iRv = ::close(h);	h = 0;
			xTEST_EQ(iRv, 0);
		}
		break;
	}
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, sync)
