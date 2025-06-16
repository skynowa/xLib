/**
 * \file  Mutex.cpp
 * \brief mutex
 */


#include "Mutex.h"

#include <xLib/Core/Format.h>
#include <xLib/Test/Test.h>
#include <xLib/Debug/Debug.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Debug/StackTrace.h>

#if   xENV_WIN
    #include "Platform/Win/Mutex_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/Mutex_unix.inl"
#endif


namespace xl::sync
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* virtual */
Mutex::~Mutex()
{
	_dtor_impl();
}
//-------------------------------------------------------------------------------------------------
const Mutex::handle_t &
Mutex::handle() const
{
    return _handle;
}
//-------------------------------------------------------------------------------------------------
void_t
Mutex::create()
{
    _create_impl();
}
//-------------------------------------------------------------------------------------------------
void_t
Mutex::lock()
{
    _lock_impl();
}
//-------------------------------------------------------------------------------------------------
bool_t
Mutex::tryLock()
{
    return _tryLock_impl();
}
//-------------------------------------------------------------------------------------------------
void_t
Mutex::unlock()
{
    _unlock_impl();
}
//-------------------------------------------------------------------------------------------------

} // namespace
