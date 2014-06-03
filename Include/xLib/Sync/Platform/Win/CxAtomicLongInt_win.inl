/**
 * \file  CxAtomicLongInt.inl
 * \brief CxAtomicLongInt operartions with long_t
 */


xNAMESPACE_BEGIN2(xlib, sync)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline CxAtomicLongInt &
CxAtomicLongInt::_addAssign_impl(
    const CxAtomicLongInt &a_value
)
{
    (void_t)::InterlockedExchangeAdd(&_value, a_value._value);

    return *this;
}
//-------------------------------------------------------------------------------------------------
inline CxAtomicLongInt &
CxAtomicLongInt::_addAssign_impl(
    clong_t &a_value
)
{
    (void_t)::InterlockedExchangeAdd(&_value, a_value);

    return *this;
}
//-------------------------------------------------------------------------------------------------
inline CxAtomicLongInt &
CxAtomicLongInt::_subtractAssign_impl(
    const CxAtomicLongInt &a_value
)
{
    (void_t)::InterlockedExchangeAdd(&_value, - a_value._value);

    return *this;
}
//-------------------------------------------------------------------------------------------------
inline CxAtomicLongInt &
CxAtomicLongInt::_subtractAssign_impl(
    clong_t &a_value
)
{
    (void_t)::InterlockedExchangeAdd(&_value, - a_value);

    return *this;
}
//-------------------------------------------------------------------------------------------------
inline CxAtomicLongInt &
CxAtomicLongInt::_assign_impl(
    const CxAtomicLongInt &a_value
)
{
    (void_t)::InterlockedExchange(&_value, a_value._value);

    return *this;
}
//-------------------------------------------------------------------------------------------------
inline CxAtomicLongInt &
CxAtomicLongInt::_assign_impl(
    clong_t &a_value
)
{
    (void_t)::InterlockedExchange(&_value, a_value);

    return *this;
}
//-------------------------------------------------------------------------------------------------
inline CxAtomicLongInt &
CxAtomicLongInt::_inc_impl(
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
inline CxAtomicLongInt &
CxAtomicLongInt::_decr_impl(
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
inline long_t
CxAtomicLongInt::_value_impl() const
{
    return _value;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, sync)
