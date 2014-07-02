/**
 * \file  ThreadStorage.inl
 * \brief thread local storage
 */


#include <xLib/Test/xTest.h>
#include <xLib/Debug/xDebug.h>
#include <xLib/Debug/LastError.h>
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


xNAMESPACE_BEGIN2(xlib, sync)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
ThreadStorage::ThreadStorage() :
#if   xENV_WIN
    _index(TLS_OUT_OF_INDEXES)
#elif xENV_UNIX
    _index(static_cast<pthread_key_t>( - 1 ))
#endif
{
    _construct_impl();
}
//-------------------------------------------------------------------------------------------------
/* virtual */
inline
ThreadStorage::~ThreadStorage()
{
    _destruct_impl();
}
//-------------------------------------------------------------------------------------------------
inline bool_t
ThreadStorage::isSet() const
{
    return _isSet_impl();
}
//-------------------------------------------------------------------------------------------------
inline void_t *
ThreadStorage::value() const
{
    return _value_impl();
}
//-------------------------------------------------------------------------------------------------
inline void_t
ThreadStorage::setValue(
    void_t *a_value
) const
{
    xTEST_PTR(a_value);

    _setValue_impl(a_value);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, sync)
