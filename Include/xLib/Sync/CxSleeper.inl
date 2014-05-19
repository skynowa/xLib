/**
 * \file  CxSleeper.inl
 * \brief sleeper
 */


xNAMESPACE_BEGIN2(xlib, sync)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxSleeper::CxSleeper() :
    _event(false, false)
{
    _event.create();
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxSleeper::sleep(
    culong_t &a_timeoutMsec  ///< in milliseconds
)
{
    // n/a

    CxEvent::ExObjectState osRv = _event.wait(a_timeoutMsec);
    xTEST_EQ(osRv == CxEvent::osSignaled || osRv == CxEvent::osTimeout, true);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxSleeper::wakeUp()
{
    // n/a

    _event.set();
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxSleeper::isSleeping() const
{
    // n/a

    return _event.isSignaled();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, sync)
