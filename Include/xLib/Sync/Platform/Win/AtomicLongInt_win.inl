/**
 * \file  AtomicLongInt.inl
 * \brief AtomicLongInt operartions with long_t
 */


namespace xl::sync
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
AtomicLongInt &
AtomicLongInt::_addAssign_impl(
    const AtomicLongInt &a_value
)
{
    (void_t)::InterlockedExchangeAdd(&_value, a_value._value);

    return *this;
}
//-------------------------------------------------------------------------------------------------
AtomicLongInt &
AtomicLongInt::_addAssign_impl(
    clong_t &a_value
)
{
    (void_t)::InterlockedExchangeAdd(&_value, a_value);

    return *this;
}
//-------------------------------------------------------------------------------------------------
AtomicLongInt &
AtomicLongInt::_subtractAssign_impl(
    const AtomicLongInt &a_value
)
{
    (void_t)::InterlockedExchangeAdd(&_value, - a_value._value);

    return *this;
}
//-------------------------------------------------------------------------------------------------
AtomicLongInt &
AtomicLongInt::_subtractAssign_impl(
    clong_t &a_value
)
{
    (void_t)::InterlockedExchangeAdd(&_value, - a_value);

    return *this;
}
//-------------------------------------------------------------------------------------------------
AtomicLongInt &
AtomicLongInt::_assign_impl(
    const AtomicLongInt &a_value
)
{
    (void_t)::InterlockedExchange(&_value, a_value._value);

    return *this;
}
//-------------------------------------------------------------------------------------------------
AtomicLongInt &
AtomicLongInt::_assign_impl(
    clong_t &a_value
)
{
    (void_t)::InterlockedExchange(&_value, a_value);

    return *this;
}
//-------------------------------------------------------------------------------------------------
AtomicLongInt &
AtomicLongInt::_inc_impl(
    cint_t a_value
)
{
    if (0 == a_value) {
        (void_t)::InterlockedIncrement(&_value);
    } else {
        (void_t)::InterlockedExchangeAdd(&_value, a_value + 1);
    }

    return *this;
}
//-------------------------------------------------------------------------------------------------
AtomicLongInt &
AtomicLongInt::_decr_impl(
    cint_t a_value
)
{
    if (0 == a_value) {
        (void_t)::InterlockedDecrement(&_value);
    } else {
        (void_t)::InterlockedExchangeAdd(&_value, - (a_value + 1));
    }

    return *this;
}
//-------------------------------------------------------------------------------------------------
long_t
AtomicLongInt::_value_impl() const
{
    return _value;
}
//-------------------------------------------------------------------------------------------------

} // namespace
