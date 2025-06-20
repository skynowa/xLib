/**
 * \file  ThreadStorage.cpp
 * \brief thread local storage
 */


#include "ThreadStorage.h"

#include <xLib/Core/Format.h>
#include <xLib/Test/Test.h>
#include <xLib/Debug/Debug.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Debug/StackTrace.h>

#if   xENV_WIN
    #include "Platform/Win/ThreadStorage_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/ThreadStorage_unix.inl"
#endif


namespace xl::sync
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
ThreadStorage::ThreadStorage()
{
	xTEST(!isValid());

    _ctor_impl();

    xTEST(isValid());
}
//-------------------------------------------------------------------------------------------------
/* virtual */
ThreadStorage::~ThreadStorage()
{
    xTEST(isValid());

    _dtor_impl();

    xTEST(!isValid());
}
//-------------------------------------------------------------------------------------------------
bool_t
ThreadStorage::isValid() const
{
    return (_index != _indexInvalid_impl());
}
//-------------------------------------------------------------------------------------------------
bool_t
ThreadStorage::isSet() const
{
    return _isSet_impl();
}
//-------------------------------------------------------------------------------------------------
void_t *
ThreadStorage::value() const
{
	xTEST(isValid());

    return _value_impl();
}
//-------------------------------------------------------------------------------------------------
void_t
ThreadStorage::setValue(
    void_t **a_value
) const
{
    xTEST_PTR(a_value);
    xTEST_PTR(*a_value);
    xTEST(isValid());

    _setValue_impl(a_value);
}
//-------------------------------------------------------------------------------------------------

} // namespace
