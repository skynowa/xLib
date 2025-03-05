/**
 * \file  IpcMutex.cpp
 * \brief IPC mutex
 */


#include "IpcMutex.h"

#include <xLib/Core/Const.h>
#include <xLib/Fs/Path.h>

#if   xENV_WIN
    #include "Platform/Win/IpcMutex_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/IpcMutex_unix.inl"
#endif

namespace xl::sync
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
const IpcMutex::handle_t &
IpcMutex::handle() const
{
    return _handle;
}
//-------------------------------------------------------------------------------------------------
void_t
IpcMutex::create(
    std::ctstring_t &a_name
)
{
	/// xTEST(!_handle.isValid());

#if   xENV_WIN
    // name
#elif xENV_UNIX
    xTEST_GR(Path::nameMaxSize() - 4, a_name.size());
#endif

    _create_impl(a_name);
}
//-------------------------------------------------------------------------------------------------
void_t
IpcMutex::open(
    std::ctstring_t &a_name
)
{
    _open_impl(a_name);
}
//-------------------------------------------------------------------------------------------------
void_t
IpcMutex::lock(
    culong_t &a_timeoutMsec
) const
{
    /// xTEST(_handle.isValid());
    xTEST_NA(a_timeoutMsec);

    _lock_impl(a_timeoutMsec);
}
//-------------------------------------------------------------------------------------------------
void_t
IpcMutex::unlock() const
{
    /// xTEST(_handle.isValid());

    _unlock_impl();
}
//-------------------------------------------------------------------------------------------------

} // namespace
