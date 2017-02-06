/**
 * \file  Sleeper.inl
 * \brief sleeper
 */


#if !cmOPTION_PROJECT_HEADER_ONLY
    #include "Sleeper.h"
#endif


xNAMESPACE_BEGIN2(xl, sync)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE
Sleeper::Sleeper() :
    _event(false, false)
{
    _event.create();
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Sleeper::sleep(
    culong_t &a_timeoutMsec  ///< in milliseconds
)
{
    // n/a

    Event::ExObjectState osRv = _event.wait(a_timeoutMsec);
    xTEST_EQ(osRv == Event::osSignaled || osRv == Event::osTimeout, true);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Sleeper::wakeUp()
{
    // n/a

    _event.set();
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Sleeper::isSleeping() const
{
    // n/a

    return _event.isSignaled();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, sync)
