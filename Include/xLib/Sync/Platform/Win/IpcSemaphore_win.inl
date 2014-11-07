/**
 * \file  IpcSemaphore.inl
 * \brief semaphore
 */


xNAMESPACE_BEGIN2(xlib, sync)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE void_t
IpcSemaphore::_construct_impl()
{
    xNA;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
IpcSemaphore::_destruct_impl()
{
    xTEST_EQ(_isValid(), true);

    xNA;
}
//-------------------------------------------------------------------------------------------------
xINLINE long_t
IpcSemaphore::_valueMax_impl() const
{
    return xCUSTOM_SEMAPHORE_VALUE_MAX_WIN;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
IpcSemaphore::_create_impl(
    clong_t         &a_initialValue,
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

    HANDLE  hRv       = ::CreateSemaphore(xPTR_NULL, a_initialValue, valueMax(), winName);
    ulong_t nativeError = NativeError::get();
    xTEST_DIFF(hRv, xNATIVE_HANDLE_NULL);
    xTEST_DIFF(nativeError, static_cast<ulong_t>( ERROR_ALREADY_EXISTS ));

    _handle.set(hRv);
    _name = a_name;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
IpcSemaphore::_open_impl(
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

    HANDLE hRv = ::OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, winName);
    xTEST_DIFF(hRv, xNATIVE_HANDLE_NULL);

    _handle.set(hRv);
    _name = a_name;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
IpcSemaphore::_post_impl() const
{
   const LONG postValue = 1L;

   BOOL blRv = ::ReleaseSemaphore(_handle.get(), postValue, xPTR_NULL);
   xTEST_DIFF(blRv, FALSE);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
IpcSemaphore::_wait_impl(
    culong_t &a_timeoutMsec
) const
{
    DWORD dwRv = ::WaitForSingleObject(_handle.get(), a_timeoutMsec);
    xTEST_EQ(dwRv, WAIT_OBJECT_0);
}
//-------------------------------------------------------------------------------------------------
xINLINE long_t
IpcSemaphore::_value_impl() const
{
    const LONG postValue = 0L;

    BOOL blRv = ::ReleaseSemaphore(_handle.get(), postValue, &liRv);
    xTEST_DIFF(blRv, FALSE);

    return liRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE bool_t
IpcSemaphore::_isValid_impl() const
{
    return _handle.isValid();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, sync)
