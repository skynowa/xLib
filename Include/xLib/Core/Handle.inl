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
#include <xLib/Log/Trace.h>


namespace xl::core
{

/*******************************************************************************
*    public
*
*******************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T, HandlePolicyType valueT>
Handle<T, valueT>::Handle() :
    _handle( null() )
{
}
//-------------------------------------------------------------------------------------------------
template<typename T, HandlePolicyType valueT>
Handle<T, valueT>::Handle(
    const T &a_handle
) :
    _handle(a_handle)
{
    ///+++ xTEST_NA(a_handle);
}
//-------------------------------------------------------------------------------------------------
template<typename T, HandlePolicyType valueT>
Handle<T, valueT>::Handle(
    const Handle &a_handle
) :
    _handle( null() )
{
    xTEST_NA(a_handle);

    _handle = a_handle.clone();
}
//-------------------------------------------------------------------------------------------------
template<typename T, HandlePolicyType valueT>
Handle<T, valueT>::~Handle()
{
    close();
}
//-------------------------------------------------------------------------------------------------


/*******************************************************************************
*    operators
*
*******************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T, HandlePolicyType valueT>
Handle<T, valueT> &
Handle<T, valueT>::operator = (
    const T &a_handle
)
{
    xTEST_NA(a_handle);

    // Try m_Handle.Attach(other.Detach(), if you got an assertion here.

    xCHECK_RET(_handle == a_handle, *this);

    /// TODO: [skynowa] disabled (for remove) - file wasn't close
    ///-- close();

    _handle = a_handle;

    return *this;
}
//-------------------------------------------------------------------------------------------------
template<typename T, HandlePolicyType valueT>
Handle<T, valueT> &
Handle<T, valueT>::operator = (
    const Handle &a_handle
)
{
    xTEST_NA(a_handle);

    xCHECK_RET(this == &a_handle, *this);

    close();

    _handle = a_handle.clone();
    xTEST_NA(_handle);

    return *this;
}
//-------------------------------------------------------------------------------------------------
template<typename T, HandlePolicyType valueT>
/* static */
T
Handle<T, valueT>::null()
{
    return handle_policy_t::null();
}
//-------------------------------------------------------------------------------------------------
template<typename T, HandlePolicyType valueT>
/* static */
std::size_t
Handle<T, valueT>::openMax()
{
    return handle_policy_t::openMax();
}
//-------------------------------------------------------------------------------------------------
template<typename T, HandlePolicyType valueT>
T
Handle<T, valueT>::get() const
{
    return _handle;
}
//-------------------------------------------------------------------------------------------------
template<typename T, HandlePolicyType valueT>
void_t
Handle<T, valueT>::set(
    const T &a_handle
)
{
    xTEST_NA(a_handle);

    _handle = a_handle;
}
//-------------------------------------------------------------------------------------------------
template<typename T, HandlePolicyType valueT>
T
Handle<T, valueT>::clone() const
{
    xCHECK_RET(!isValid(), null());

    return handle_policy_t::clone(_handle);
}
//-------------------------------------------------------------------------------------------------
template<typename T, HandlePolicyType valueT>
void_t
Handle<T, valueT>::setCloseOnExec(
	cbool_t a_flag
)
{
   /**
	* Dealing with Duplicate file Descriptors from Sub-Processes
	*
	* https://oroboro.com/file-handle-leaks-server/
	*
	* When you spawn subprocesses they inherit all the open file descriptors of the parent process
	* unless those descriptors have been specifically flagged as FD_CLOEXEC
	*
	* This is because the operating system doesn’t know which file descriptors will be used by the
	* subprocess for inter-process communication. Or if the subprocess will be the one that will
	* handle an open network socket.
	*
	* Normally when you spawn subprocesses the only file descriptors that need to stay open are
	* the pipes that are connected to STDIN, STDOUT, and STDERR of the child process. But every
	* subprocess is different.
	*
	* Right before your server calls fork() or exec(), call showFdInfo() to make sure that all file
	* descriptors are labeled FD_CLOEXEC except for the ones you need to be duplicated.
	*/

	_setCloseOnExec_impl(a_flag);
}
//-------------------------------------------------------------------------------------------------
template<typename T, HandlePolicyType valueT>
bool_t
Handle<T, valueT>::isValid() const
{
    return handle_policy_t::isValid(_handle);
}
//-------------------------------------------------------------------------------------------------
template<typename T, HandlePolicyType valueT>
void_t
Handle<T, valueT>::attach(
    const T &a_handle
)
{
    xTEST_NA(a_handle);
    xCHECK_DO(!isValid(), return);

    close();

    _handle = a_handle;
}
//-------------------------------------------------------------------------------------------------
template<typename T, HandlePolicyType valueT>
T
Handle<T, valueT>::detach()
{
    T hRv = _handle;

    _handle = null();

    return hRv;
}
//-------------------------------------------------------------------------------------------------
template<typename T, HandlePolicyType valueT>
void_t
Handle<T, valueT>::close()
{
    if ( !isValid() ) {
        _handle = null();
        return;
    }

    handle_policy_t::close(_handle);
}
//-------------------------------------------------------------------------------------------------

} // namespace
