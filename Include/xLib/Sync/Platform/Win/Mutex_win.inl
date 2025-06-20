/**
 * \file  Mutex.inl
 * \brief mutex
 */


namespace xl::sync
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
Mutex::_dtor_impl()
{
    bool_t bRv {};

    try {
        (void_t)::DeleteCriticalSection(&_handle);

        bRv = true;
    } catch (...) {
        bRv = false;
    }

    xTEST(bRv);
}
//-------------------------------------------------------------------------------------------------
void_t
Mutex::_create_impl()
{
    bool_t bRv {};

    try {
        (void_t)::InitializeCriticalSection(&_handle);

        bRv = true;
    } catch (...) {
        bRv = false;
    }

    xTEST(bRv);
}
//-------------------------------------------------------------------------------------------------
void_t
Mutex::_lock_impl()
{
    bool_t bRv {};

    try {
        (void_t)::EnterCriticalSection(&_handle);

        bRv = true;
    } catch (...) {
        bRv = false;
    }

    xTEST(bRv);
}
//-------------------------------------------------------------------------------------------------
bool_t
Mutex::_tryLock_impl()
{
    BOOL blRv = ::TryEnterCriticalSection(&_handle);
    xCHECK_RET(blRv == FALSE, false);

    return true;
}
//-------------------------------------------------------------------------------------------------
void_t
Mutex::_unlock_impl()
{
    bool_t bRv {};

    try {
        (void_t)::LeaveCriticalSection(&_handle);

        bRv = true;
    } catch (...) {
        bRv = false;
    }

    xTEST(bRv);
}
//-------------------------------------------------------------------------------------------------

} // namespace
