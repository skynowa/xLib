/**
 * \file  CxMutex.inl
 * \brief mutex
 */


xNAMESPACE_BEGIN2(xlib, sync)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline void_t
CxMutex::_destruc_impl()
{
    bool_t bRv = false;

    try {
        (void_t)::DeleteCriticalSection(&_handle);

        bRv = true;
    } catch (...) {
        bRv = false;
    }

    xTEST_EQ(bRv, true);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxMutex::_create_impl()
{
    bool_t bRv = false;

    try {
        (void_t)::InitializeCriticalSection(&_handle);

        bRv = true;
    } catch (...) {
        bRv = false;
    }

    xTEST_EQ(bRv, true);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxMutex::_lock_impl()
{
    bool_t bRv = false;

    try {
        (void_t)::EnterCriticalSection(&_handle);

        bRv = true;
    } catch (...) {
        bRv = false;
    }

    xTEST_EQ(bRv, true);
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxMutex::_tryLock_impl()
{
    BOOL blRv = ::TryEnterCriticalSection(&_handle);
    xCHECK_RET(blRv == FALSE, false);

    return true;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxMutex::_unlock_impl()
{
    bool_t bRv = false;

    try {
        (void_t)::LeaveCriticalSection(&_handle);

        bRv = true;
    } catch (...) {
        bRv = false;
    }

    xTEST_EQ(bRv, true);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, sync)
