/**
 * \file  IpcSemaphore.inl
 * \brief semaphore
 */


namespace xl::sync
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
IpcSemaphore::_ctor_impl()
{
    xNA;
}
//-------------------------------------------------------------------------------------------------
void_t
IpcSemaphore::_dtor_impl()
{
	xTEST(_isValid());

    xNA;
}
//-------------------------------------------------------------------------------------------------
long_t
IpcSemaphore::_valueMax_impl() const
{
    return xCUSTOM_SEMAPHORE_VALUE_MAX_WIN;
}
//-------------------------------------------------------------------------------------------------
void_t
IpcSemaphore::_create_impl(
    clong_t          a_initialValue,
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

    HANDLE  hRv          = ::CreateSemaphore(nullptr, a_initialValue, valueMax(), winName);
    ulong_t nativeError_ = NativeError::get();
    xTEST_DIFF(hRv, xNATIVE_HANDLE_NULL);
    xTEST_DIFF(nativeError_, static_cast<ulong_t>( ERROR_ALREADY_EXISTS ));

    _handle = hRv;
    _name   = a_name;
}
//-------------------------------------------------------------------------------------------------
void_t
IpcSemaphore::_open_impl(
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

    HANDLE hRv = ::OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, winName);
    xTEST_DIFF(hRv, xNATIVE_HANDLE_NULL);

    _handle = hRv;
    _name   = a_name;
}
//-------------------------------------------------------------------------------------------------
void_t
IpcSemaphore::_post_impl() const
{
   const LONG postValue = 1L;

   BOOL blRv = ::ReleaseSemaphore(_handle, postValue, nullptr);
   xTEST_DIFF(blRv, FALSE);
}
//-------------------------------------------------------------------------------------------------
void_t
IpcSemaphore::_wait_impl(
    culong_t a_timeoutMsec
) const
{
    DWORD dwRv = ::WaitForSingleObject(_handle, a_timeoutMsec);
    xTEST_EQ(dwRv, WAIT_OBJECT_0);
}
//-------------------------------------------------------------------------------------------------
long_t
IpcSemaphore::_value_impl() const
{
    const LONG countRelease {};
    LONG       countPrev {};

    BOOL blRv = ::ReleaseSemaphore(_handle, countRelease, &countPrev);
    xTEST_DIFF(blRv, FALSE);

    return countPrev;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
bool_t
IpcSemaphore::_isValid_impl() const
{
    return _handle != xNATIVE_HANDLE_NULL;
}
//-------------------------------------------------------------------------------------------------

} // namespace
