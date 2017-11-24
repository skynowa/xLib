/**
 * \file  ThreadStorage.inl
 * \brief thread local storage
 */


#include "ThreadStorage.h"

#include <xLib/Test/Test.h>
#include <xLib/Debug/Debug.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/StdError.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Debug/StackTrace.h>
#include <xLib/Log/Trace.h>

#if   xENV_WIN
    #include "Platform/Win/ThreadStorage_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/ThreadStorage_unix.inl"

    #if   xENV_LINUX
        // #include "Platform/Linux/ThreadStorage_linux.inl"
    #elif xENV_BSD
        // #include "Platform/Bsd/ThreadStorage_bsd.inl"
    #elif xENV_APPLE
        // #include "Platform/Unix/ThreadStorage_apple.inl"
    #endif
#endif


xNAMESPACE_BEGIN2(xl, sync)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
ThreadStorage::ThreadStorage() :
#if   xENV_WIN
    _index(TLS_OUT_OF_INDEXES)
#elif xENV_UNIX
    _index(static_cast<index_t>( - 1 ))
#endif
{
    xTEST_EQ(isValid(), false);

    _construct_impl();

    xTEST_EQ(isValid(), true);
}
//-------------------------------------------------------------------------------------------------
/* virtual */
ThreadStorage::~ThreadStorage()
{
    xTEST_EQ(isValid(), true);

    _destruct_impl();

    xTEST_EQ(isValid(), false);
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
    xTEST_EQ(isValid(), true);

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
    xTEST_EQ(isValid(), true);

    _setValue_impl(a_value);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, sync)
