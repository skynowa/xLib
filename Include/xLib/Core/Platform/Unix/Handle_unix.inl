/**
 * \file  Handle.inl
 * \brief handle
 */


#include <xLib/Test/Test.h>
#include <xLib/Debug/Debug.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Debug/StackTrace.h>


namespace xl::core
{

//-------------------------------------------------------------------------------------------------
template<typename T, HandleType typeT>
void_t
Handle<T, valueT>::_setCloseOnExec_impl(
	cbool_t a_flag
)
{
	cint_t flags = ::fcntl(_handle, F_GETFD);
	xTEST_DIFF(flags, - 1);

	flags = a_flag ? (flags | FD_CLOEXEC) : (flags & ~FD_CLOEXEC);

	int_t iRv = ::fcntl(_handle, F_SETFD, flags);
	xTEST_DIFF(iRv, - 1);
}
//-------------------------------------------------------------------------------------------------

} // namespace
