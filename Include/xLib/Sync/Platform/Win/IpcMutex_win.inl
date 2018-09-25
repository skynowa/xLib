/**
 * \file  IpcMutex.inl
 * \brief mutex
 */


xNAMESPACE_BEGIN2(xl, sync)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
IpcMutex::_create_impl(
    std::ctstring_t &a_name
)
{
    ctchar_t       *winName = nullptr;
    std::tstring_t  _winName;

    if (a_name.empty()) {
        winName  = nullptr;
    } else {
        _winName = xT("Global\\") + a_name;
        winName  = _winName.c_str();
    }

    HANDLE hRv = ::CreateMutex(nullptr, FALSE, winName);
    xTEST_DIFF(hRv, xNATIVE_HANDLE_NULL);

    _handle.set(hRv);
    _name = a_name;
}
//-------------------------------------------------------------------------------------------------
void_t
IpcMutex::_open_impl(
    std::ctstring_t &a_name
)
{
    ctchar_t       *winName = nullptr;
    std::tstring_t _winName;

    if (a_name.empty()) {
        winName = nullptr;
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
void_t
IpcMutex::_lock_impl(
    culong_t &a_timeoutMsec
) const
{
    DWORD dwRv = ::WaitForSingleObject(_handle.get(), a_timeoutMsec);
    xTEST_EQ(dwRv, WAIT_OBJECT_0);
    xTEST_DIFF(dwRv, WAIT_ABANDONED);
}
//-------------------------------------------------------------------------------------------------
void_t
IpcMutex::_unlock_impl() const
{
    BOOL blRv = ::ReleaseMutex(_handle.get());
    xTEST_DIFF(blRv, FALSE);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, sync)
