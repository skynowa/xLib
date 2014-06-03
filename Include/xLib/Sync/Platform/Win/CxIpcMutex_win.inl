/**
 * \file  CxIpcMutex.inl
 * \brief mutex
 */


xNAMESPACE_BEGIN2(xlib, sync)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline void_t
CxIpcMutex::_create_impl(
    std::ctstring_t &a_name
)
{
    ctchar_t       *winName = xPTR_NULL;
    std::tstring_t  _winName;

    if (a_name.empty()) {
        winName  = xPTR_NULL;
    } else {
        _winName = xT("Global\\") + a_name;
        winName  = _winName.c_str();
    }

    HANDLE hRv = ::CreateMutex(xPTR_NULL, FALSE, winName);
    xTEST_DIFF(hRv, xNATIVE_HANDLE_NULL);

    _handle.set(hRv);
    _name = a_name;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxIpcMutex::_open_impl(
    std::ctstring_t &a_name
)
{
    ctchar_t       *winName = xPTR_NULL;
    std::tstring_t _winName;

    if (a_name.empty()) {
        winName = xPTR_NULL;
    } else {
        _winName = xT("Global\\") + a_name;
        winName  = _winName.c_str();
    }

    HANDLE hRv = ::OpenMutex(MUTEX_ALL_ACCESS, FALSE, winName);
    xTEST_DIFF(hRv, xNATIVE_HANDLE_NULL);

    _handle.set(hRv);
    _name = a_name;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxIpcMutex::_lock_impl(
    culong_t &a_timeoutMsec
) const
{
    DWORD dwRv = ::WaitForSingleObject(_handle.get(), a_timeoutMsec);
    xTEST_EQ(dwRv, WAIT_OBJECT_0);
    xTEST_DIFF(dwRv, WAIT_ABANDONED);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxIpcMutex::_unlock_impl() const
{
    BOOL blRv = ::ReleaseMutex(_handle.get());
    xTEST_DIFF(blRv, FALSE);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, sync)
