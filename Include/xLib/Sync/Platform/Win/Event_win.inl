/**
 * \file  Event.h
 * \brief event (using between threads)
 */


namespace xl::sync
{

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
    xTEST_EQ(_event, xNATIVE_HANDLE_NULL);

    HANDLE hRv = ::CreateEvent(nullptr, ! _isAutoReset, _initState, nullptr);
    xTEST_DIFF(hRv, static_cast<HANDLE>(nullptr));

    _event = hRv;
    // n/a
}
//-------------------------------------------------------------------------------------------------
void_t
Event::_set_impl()
{
    xTEST_DIFF(_event, xNATIVE_HANDLE_NULL);

    BOOL blRv = ::SetEvent(_event);
    xTEST_DIFF(blRv, FALSE);
}
//-------------------------------------------------------------------------------------------------
void_t
Event::_reset_impl()
{
    xTEST_DIFF(_event, xNATIVE_HANDLE_NULL);

    BOOL blRv = ::ResetEvent(_event);
    xTEST_DIFF(blRv, FALSE);
}
//-------------------------------------------------------------------------------------------------
Event::ObjectState
Event::_wait_impl(
    culong_t &a_timeoutMs /* = xTIMEOUT_INFINITE */  ///< in milliseconds
)
{
    xTEST_DIFF(_event, xNATIVE_HANDLE_NULL);

    ObjectState osRv = ObjectState::osFailed;

    osRv = static_cast<ObjectState>( ::WaitForSingleObject(_event, a_timeoutMs) );

    return osRv;
}
//-------------------------------------------------------------------------------------------------
bool_t
Event::_isSignaled_impl() const
{
    bool_t bRv {};

    DWORD dwRv = ::WaitForSingleObject(_event, 0UL);
    // n/a

    bRv = (_event != xNATIVE_HANDLE_NULL && dwRv == static_cast<DWORD>(ObjectState::osSignaled));

    return bRv;
}
//-------------------------------------------------------------------------------------------------

} // namespace
