/**
 * \file  Sleeper.inl
 * \brief sleeper
 */


namespace xl::sync
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
Sleeper::Sleeper() :
    _event(false, false)
{
    _event.create();
}
//-------------------------------------------------------------------------------------------------
void_t
Sleeper::sleep(
    culong_t &a_timeoutMsec  ///< in milliseconds
)
{
    // n/a

    Event::ObjectState osRv = _event.wait(a_timeoutMsec);
    xTEST(osRv == Event::osSignaled || osRv == Event::osTimeout);
}
//-------------------------------------------------------------------------------------------------
void_t
Sleeper::wakeUp()
{
    // n/a

    _event.set();
}
//-------------------------------------------------------------------------------------------------
bool_t
Sleeper::isSleeping() const
{
    // n/a

    return _event.isSignaled();
}
//-------------------------------------------------------------------------------------------------

} // namespace
