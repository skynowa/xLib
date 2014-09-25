/**
 * \file  Sleeper.inl
 * \brief sleeper
 */


#if !xOPTION_HEADER_ONLY
    #include "Sleeper.h"
#endif


xNAMESPACE_BEGIN2(xlib, sync)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
Sleeper::Sleeper() :
    _event(false, false)
{
    _event.create();
}
//-------------------------------------------------------------------------------------------------
inline void_t
Sleeper::sleep(
    culong_t &a_timeoutMsec  ///< in milliseconds
)
{
    // n/a

    Event::ExObjectState osRv = _event.wait(a_timeoutMsec);
    xTEST_EQ(osRv == Event::osSignaled || osRv == Event::osTimeout, true);
}
//-------------------------------------------------------------------------------------------------
inline void_t
Sleeper::wakeUp()
{
    // n/a

    _event.set();
}
//-------------------------------------------------------------------------------------------------
inline bool_t
Sleeper::isSleeping() const
{
    // n/a

    return _event.isSignaled();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, sync)
