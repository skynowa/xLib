/**
 * \file  CxThreadStorage.inl
 * \brief thread local storage
 */


#include <xLib/Test/xTest.h>
#include <xLib/Debug/xDebug.h>
#include <xLib/Debug/CxLastError.h>
#include <xLib/Debug/CxStdError.h>
#include <xLib/Debug/CxErrorReport.h>
#include <xLib/Debug/CxDebugger.h>
#include <xLib/Debug/CxStackTrace.h>
#include <xLib/Log/CxTrace.h>

#if   xENV_WIN
    #include "Platform/Win/CxThreadStorage_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/CxThreadStorage_unix.inl"

    #if   xENV_LINUX
        // #include "Platform/Linux/CxThreadStorage_linux.inl"
    #elif xENV_BSD
        // #include "Platform/Bsd/CxThreadStorage_bsd.inl"
    #elif xENV_APPLE
        // #include "Platform/Unix/CxThreadStorage_apple.inl"
    #endif
#endif


xNAMESPACE_BEGIN2(xlib, sync)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxThreadStorage::CxThreadStorage() :
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
CxThreadStorage::~CxThreadStorage()
{
    _destruct_impl();
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxThreadStorage::isSet() const
{
    return _isSet_impl();
}
//-------------------------------------------------------------------------------------------------
inline void_t *
CxThreadStorage::value() const
{
    return _value_impl();
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxThreadStorage::setValue(
    void_t *a_value
) const
{
    xTEST_PTR(a_value);

    _setValue_impl(a_value);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, sync)
