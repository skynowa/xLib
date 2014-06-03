/**
 * \file  CxEvent.h
 * \brief event (using between threads)
 */


xNAMESPACE_BEGIN2(xlib, sync)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline void_t
CxEvent::_dectruct_impl()
{
    xNA;
}
//-------------------------------------------------------------------------------------------------
inline const CxEvent::handle_t &
CxEvent::_handle_impl() const
{
    return _event;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxEvent::_create_impl()
{
    xTEST_EQ(_event.isValid(), false);

    HANDLE hRv = ::CreateEvent(xPTR_NULL, ! _isAutoReset, _initState, xPTR_NULL);
    xTEST_DIFF(hRv, static_cast<HANDLE>(xPTR_NULL));

    _event.set(hRv);
    // n/a
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxEvent::_set_impl()
{
    xTEST_EQ(_event.isValid(), true);

    BOOL blRv = ::SetEvent(handle().get());
    xTEST_DIFF(blRv, FALSE);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxEvent::_reset_impl()
{
    xTEST_EQ(_event.isValid(), true);

    BOOL blRv = ::ResetEvent(handle().get());
    xTEST_DIFF(blRv, FALSE);
}
//-------------------------------------------------------------------------------------------------
inline CxEvent::ExObjectState
CxEvent::_wait_impl(
    culong_t &a_timeoutMs /* = xTIMEOUT_INFINITE */  ///< in milliseconds
)
{
    ExObjectState osRv = osFailed;

    xTEST_EQ(_event.isValid(), true);

    osRv = static_cast<ExObjectState>( ::WaitForSingleObject(handle().get(), a_timeoutMs) );

    return osRv;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxEvent::_isSignaled_impl() const
{
    bool_t bRv = false;

    DWORD dwRv = ::WaitForSingleObject(handle().get(), 0UL);
    // n/a

    bRv = (_event.isValid() && dwRv == osSignaled);

    return bRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, sync)
