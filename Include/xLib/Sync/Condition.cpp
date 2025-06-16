/**
 * \file   Condition.cpp
 * \brief  condition variable
 */


#include "Condition.h"

#include <xLib/Core/Format.h>
#include <xLib/Test/Test.h>
#include <xLib/Debug/Debug.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Debug/StackTrace.h>
#include <xLib/Log/LogStream.h>

#if   xENV_WIN
    #include "Platform/Win/Condition_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/Condition_unix.inl"
#endif


namespace xl::sync
{

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* virtual */
Condition::~Condition()
{
    _dtor_impl();
}
//-------------------------------------------------------------------------------------------------
void_t
Condition::create()
{
    _create_impl();
}
//-------------------------------------------------------------------------------------------------
void_t
Condition::wait(
    culong_t &a_timeoutMs
)
{
    _wait_impl(a_timeoutMs);
}
//-------------------------------------------------------------------------------------------------
void_t
Condition::signal()
{
    _signal_impl();
}
//-------------------------------------------------------------------------------------------------
void_t
Condition::broadcast()
{
    _broadcast_impl();
}
//-------------------------------------------------------------------------------------------------

} // namespace
