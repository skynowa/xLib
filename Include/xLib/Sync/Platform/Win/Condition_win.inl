/**
 * \file   Condition.inl
 * \brief  condition variable
 */


namespace xl::sync
{

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
Condition::_dtor_impl()
{
    // TODO: [skynowa] Condition::_dtor_impl()
    xTRACE_NOT_IMPLEMENTED
}
//-------------------------------------------------------------------------------------------------
void_t
Condition::_create_impl()
{
    // TODO: [skynowa] Condition::_create_impl()
    xTRACE_NOT_IMPLEMENTED
}
//-------------------------------------------------------------------------------------------------
void_t
Condition::_wait_impl(
    culong_t &a_timeoutMs
)
{
    // TODO: [skynowa] Condition::_wait_impl()
	xUNUSED(a_timeoutMs);

    xTRACE_NOT_IMPLEMENTED
}
//-------------------------------------------------------------------------------------------------
void_t
Condition::_signal_impl()
{
    // TODO: [skynowa] Condition::_signal_impl()
    xTRACE_NOT_IMPLEMENTED
}
//-------------------------------------------------------------------------------------------------
void_t
Condition::_broadcast_impl()
{
    // TODO: [skynowa] Condition::_broadcast_impl()
    xTRACE_NOT_IMPLEMENTED
}
//-------------------------------------------------------------------------------------------------

} // namespace
