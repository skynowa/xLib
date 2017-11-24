/**
 * \file  Event.h
 * \brief event (using between threads)
 */


xNAMESPACE_BEGIN2(xl, sync)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
Event::_dectruct_impl()
{
    xNA;
}
//-------------------------------------------------------------------------------------------------
const Event::handle_t &
Event::_handle_impl() const
{
    return _event;
}
//-------------------------------------------------------------------------------------------------
void_t
Event::_create_impl()
{
    xTEST_EQ(_event.isValid(), false);

    HANDLE hRv = ::CreateEvent(xPTR_NULL, ! _isAutoReset, _initState, xPTR_NULL);
    xTEST_DIFF(hRv, static_cast<HANDLE>(xPTR_NULL));

    _event.set(hRv);
    // n/a
}
//-------------------------------------------------------------------------------------------------
void_t
Event::_set_impl()
{
    xTEST_EQ(_event.isValid(), true);

    BOOL blRv = ::SetEvent(handle().get());
    xTEST_DIFF(blRv, FALSE);
}
//-------------------------------------------------------------------------------------------------
void_t
Event::_reset_impl()
{
    xTEST_EQ(_event.isValid(), true);

    BOOL blRv = ::ResetEvent(handle().get());
    xTEST_DIFF(blRv, FALSE);
}
//-------------------------------------------------------------------------------------------------
Event::ObjectState
Event::_wait_impl(
    culong_t &a_timeoutMs /* = xTIMEOUT_INFINITE */  ///< in milliseconds
)
{
    ObjectState osRv = osFailed;

    xTEST_EQ(_event.isValid(), true);

    osRv = static_cast<ObjectState>( ::WaitForSingleObject(handle().get(), a_timeoutMs) );

    return osRv;
}
//-------------------------------------------------------------------------------------------------
bool_t
Event::_isSignaled_impl() const
{
    bool_t bRv = false;

    DWORD dwRv = ::WaitForSingleObject(handle().get(), 0UL);
    // n/a

    bRv = (_event.isValid() && dwRv == osSignaled);

    return bRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, sync)
