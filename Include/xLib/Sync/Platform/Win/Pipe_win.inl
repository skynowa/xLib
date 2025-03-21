/**
 * \file  Pipe_win.inl
 * \brief Pipe is a section of shared memory that processes use for communication
 */


namespace xl::sync
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
Pipe::_create_impl()
{
}
//-------------------------------------------------------------------------------------------------
std::ssize_t
Pipe::_read_impl(
	cint_t        a_handleRead,	///<
	void_t       *out_buff,		///< [out]
	std::csize_t  a_buffSize	///<
) const
{
	// TODO: _read_impl - impl
	xUNUSED(a_handleRead);
	xUNUSED(out_buff);
	xUNUSED(a_buffSize);

	return -1;
}
//-------------------------------------------------------------------------------------------------
void_t
Pipe::_close_impl(
	cCloseMode a_mode
)
{
	// TODO: _close_impl - impl
	xUNUSED(a_mode);
}
//-------------------------------------------------------------------------------------------------

} // namespace
