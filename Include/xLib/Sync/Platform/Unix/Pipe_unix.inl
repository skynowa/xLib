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
	auto handleClose = [this] (FdIndex a_index) -> void
	{
		auto &h = _handles[a_index];
		if (h == 0) {
			return;
		}

		int_t iRv = ::close(h);	h = 0;
		xTEST_EQ(iRv, 0);
	};

	switch (a_mode) {
	case CloseMode::Read:
		handleClose(FdIndex::Read);
		break;
	case CloseMode::Write:
		handleClose(FdIndex::Write);
		break;
	case CloseMode::All:
		handleClose(FdIndex::Read);
		handleClose(FdIndex::Write);
		break;
	}
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, sync)
